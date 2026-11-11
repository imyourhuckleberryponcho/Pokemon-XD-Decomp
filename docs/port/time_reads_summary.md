# Clock reads in game code - review summary

Source: docs/port/time_reads.json (359 sites, all reviewed by reading the code; see each row's note).

## The key fact (corrected 2026-11-08 by the main session after checking the code)

The game is TIME-BASED, not frame-locked. pokecoloMain's start-up calls GSgfxVideoSetLockFrameRate(0) and
GSgfxVideoSetLockFrameActive(1) (pokecolo.cpp:549-550), so in a normal run GSgfxVideoGetLastRenderTime() returns
_videoState.realTime (video.cpp:411), not lockRate + 1. realTime = renderTime of the last finished frame
(GSgfxVideoSetupNextFrame, video.cpp:358), and renderTime is measured when a frame's drawing is DONE (GSgfxVideoSetXFBReady -> setXFBReadyImpl, video.cpp:290; corrected 2026-11-08 03:39 by the port):
  renderTime = (OSGetTime() - lastTime) / (OS_TIMER_CLOCK / vsyncRate)      (video.cpp:308 / 450)
= the real time since the previous draw-done in VSYNC UNITS: ~1.0 at 60 fps, ~2.0 when the game runs locked at 30 fps
(GSgfxVideoSetLockFrameRate(1): field, world map, move demo, script menus, many fade effects; lockCount makes the
flip wait lockRate extra vsyncs), and more on a lag frame. timeGetLastFrameTime() / timeGetLastFrameSec() pass this on.
So every "dt" row below (animation, frame_pacing, camera, movement, text speed, fades, script thread time) advances by
the MEASURED frame time. GSgfxRenderIsPaused() == 1 gives 0.

PC rule: the value must be the same number of vsyncs the GameCube would have measured for that frame (1.0 per frame
at 60 fps, 2.0 in lockRate 1 scenes, plus the extra vsyncs of a lag frame if the port wants Original lag behaviour).
Measuring the PC's own wall time between draw-dones gives the same result only while the PC presents exactly on a 60 Hz
vsync; faster presentation gives dt < 1 (movement per frame smaller, but rows that COUNT frames or test `dt != 0` then
behave differently). lockRate + 1 is only returned when the lock is switched off (debug menu, dbgMenuSub.cpp:210).
Note: the per-row notes below were written assuming the fixed 1-frame value; their "what it influences" is still
right, but read "1 tick" there as "the measured frame time in vsyncs".

## Counts per influence

| influence | sites |
|---|---|
| animation | 92 |
| frame_pacing | 86 |
| timeout | 53 |
| wait_loop | 42 |
| ui | 28 |
| camera | 19 |
| profiling | 16 |
| sound | 6 |
| effect | 6 |
| other | 4 |
| play_time | 4 |
| rng | 2 |
| battle_wait | 1 |

(timeout is mostly 50 GBA-link tick timeouts in agbCommunication.cpp.)

## Where PC speed can change GAMEPLAY (most important first)

1. RNG seed: `GSmathInit` (GSmath/init.cpp:40) seeds `__hsd_rand_seed_hold` with `OSGetTime()` once at start. This
   is the only real-clock RNG seed. Seed from the real clock (or a fixed value for reproducible runs). The GBA link
   key (agbCommunication.cpp:378, `OSGetTick()`) is a separate link-only random.
2. Battle waits and timer: `_fightMainWaitFrameSub` (fightMain.cpp:434) waits N logic ticks for every battle message
   and animation delay; `fightTimerThreadFunc` (fightTimer.cpp:170) counts `60*limit` ticks for the command / turn
   timer and then forces the timer over; `fightTimerGetNokoriTime` (fightTimer.cpp:111) shows the time left. All
   count ticks, not wall time.
3. Script pacing: Tiga script threads are advanced by frame seconds (tiga.cpp:438/442/886, floorManager.cpp:1077
   `script->executeThread`), `scriptWaitTime` (script.cpp:796), `_peopleMoveCheckTime` (script.cpp:955), `_soundWait`
   (sound.cpp:268), `menuSubSleep` (menuSub.cpp:389), plus the AppScript global 0x9F that exposes the vsync rate
   to scripts (appScript.cpp:630). Every cutscene/event wait follows the tick rate.
4. Player and NPC movement: heroMove.cpp:1054 (`30*lastFrameTime/vsyncRate`), `_heroMoveSlowStopFactor`
   (heroMove.cpp:1755), people.cpp 1018-1020 (daemon scale; skips the update when the frame time is 0), 1414-1451
   NPC turn, 1503/1536 random-move timers, 1615-1616 patrol, 2414-2432 `peopleMoveAlongAngle`; gimmickBox.cpp
   (box push/jump) 458-1012. Movement per tick is constant, so on-screen speed = tick rate.
5. Text and message windows: GSmsg.cpp:2444 (characters printed per tick = last frame time), cursor counters 2554/2565.
6. Fades gating scene changes: fade.cpp:131 and all fade_effect.cpp `timeGetLastFrameTime() != 0` gates (42 sites);
   fade completion releases the code waiting for it (transitions between field and battle).
7. Title screen idle timer (menuTitle.cpp:416 starts the demo after a delay), key repeat (menu.cpp:1243/1274,
   GSinput.cpp:524), evolution / relive / ant scene waits (evolution.cpp 369/662/675, pokemonRelive.cpp, ant.cpp:188):
   timing only, no state change.

## Real clock (wall time) sites - must keep REAL time on PC

- RNG seed: GSmath/init.cpp:40.
- Play time: pokecolo.cpp:572-579 (`pokecoloMain` measures real microseconds per loop -> `_frameTime`;
  `pokecoloGetFrameTime()` feeds `_countPlayTime` and the logo-movie timer in menuLogoDemo.cpp:997). This is the
  one place where PC speed does NOT change play time: it counts real seconds, so a fast PC does not inflate it.
- Save calendar stamp: memcard.cpp:1317. Save buffer offset: pokecolo.cpp:616 (OSGetTime low bits; memory
  placement only).
- Soft-reset fade: reset.cpp:287 uses the measured real render time (cosmetic).
- Video: video.cpp:307/449/665 measure the real render time; it is only used as the game dt if the debug lock is on.
- Movie audio track pick: GSmovie.cpp:800-804 (any value works).

## Real-time hardware timeouts (not gameplay)

- GBA link cable (agbCommunication.cpp, 50 sites): `OSGetTick` deadlines for every link step. The PC needs a stub or
  an always-succeed / fail-fast link layer.
- Render watchdog (render.cpp:202): aborts a frame if the GPU stays busy for 3 vsync periods; not needed on PC.

## Profiling / debug only (no gameplay effect)

perfbar.cpp (17 sites), shape editor (GSshape.cpp), light editor (lightEditor.cpp), debug free camera (camera.cpp
1112-1155), fight debug menu (fightMain.cpp:257), debug lock frame (dbgMenuSub.cpp).

## 50 Hz (PAL) corrections

`GSgfxVideoGetVsyncRate() == 50` branches: animation.cpp 598/639/651/919, GScamera.cpp:1016, GSlight.cpp:383,
GSparticle.cpp:2183 (extra particle step every 5th frame). They do nothing at 60 Hz.
