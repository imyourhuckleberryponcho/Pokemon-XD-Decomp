#include <dolphin/types.h>

struct GSthread;

// A countdown timer driven by its own thread (limit in seconds).
struct FightTimer {
    bool over;
    u8 infinite;
    f32 elapsed;
    f32 limit;
    GSthread* thread;
};

extern "C" {

s32 menuCBRule_GetCommandTimeLimit(void);
s32 menuCBRule_GetBattleTimeLimit(void);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
void GSthreadBlock(GSthread* thread);
void GSthreadTerminate(GSthread* thread);
void GSthreadSwitch(void);
u32 GSfloorGetCurrentFloorGroupID(void);
GSthread* GSthreadCreate(s32, u32 group, u32 stackSize, s32, s32, void (*func)(FightTimer*));
void GSthreadSetArgs(GSthread* thread, s32 num, ...);

void fightTimerTerminate(FightTimer* timer);
bool fightTimerIsOver(FightTimer* timer);
f32 fightTimerGetNokoriTime(FightTimer* timer);
bool fightTimerBlock(FightTimer* timer);
void fightTimerStart(FightTimer* timer);
void fightTimerInit(FightTimer* timer, f32 limit);
void fightTimerThreadFunc(FightTimer* timer);

static FightTimer gCommandTimer;
static FightTimer gBattleTimer;

// Unknown function that was dead-stripped from the final link; it put 0.0f and 60.0f first in .sdata2.
f32 fightTimerSecondsToFrames(f32 seconds) {
    if (seconds < 0.0f) {
        return 0.0f;
    }
    return seconds * 60.0f;
}

void fightTimerCommandTerminate(void) {
    fightTimerTerminate(&gCommandTimer);
}

bool fightTimerCommandIsOver(void) {
    return fightTimerIsOver(&gCommandTimer);
}

f32 fightTimerCommandGetNokoriTime(void) {
    return fightTimerGetNokoriTime(&gCommandTimer);
}

bool fightTimerCommandBlock(void) {
    return fightTimerBlock(&gCommandTimer);
}

void fightTimerCommandStart(void) {
    fightTimerStart(&gCommandTimer);
}

void fightTimerCommandInit(void) {
    fightTimerInit(&gCommandTimer, menuCBRule_GetCommandTimeLimit());
}

bool fightTimerAllIsOver(void) {
    return fightTimerIsOver(&gBattleTimer);
}

f32 fightTimerAllGetNokoriTime(void) {
    return fightTimerGetNokoriTime(&gBattleTimer);
}

bool fightTimerAllBlock(void) {
    return fightTimerBlock(&gBattleTimer);
}

void fightTimerAllStart(void) {
    fightTimerStart(&gBattleTimer);
}

void fightTimerAllInit(void) {
    fightTimerInit(&gBattleTimer, menuCBRule_GetBattleTimeLimit());
}

void fightTimerAllTerminate(void) {
    fightTimerTerminate(&gBattleTimer);
}

bool fightTimerIsOver(FightTimer* timer) {
    if (timer->infinite == 1) {
        return false;
    }
    if (timer->thread == NULL) {
        return true;
    }
    return timer->over;
}

f32 fightTimerGetNokoriTime(FightTimer* timer) {
    if (timer->infinite == 1) {
        return -3600.0f;
    }
    if (timer->thread == NULL) {
        return 0.0f;
    }
    return timer->limit - timer->elapsed / GSgfxVideoGetVsyncRate();
}

bool fightTimerBlock(FightTimer* timer) {
    if (timer->infinite == 1) {
        return false;
    }
    if (timer->thread == NULL) {
        return false;
    }
    GSthreadBlock(timer->thread);
    return true;
}

void fightTimerStart(FightTimer* timer) {
    GSthread* thread;
    if (timer->infinite != 1) {
        thread = GSthreadCreate(1, GSfloorGetCurrentFloorGroupID(), 0x4000, 1, 0, fightTimerThreadFunc);
        if (thread != NULL) {
            timer->thread = thread;
            GSthreadSetArgs(thread, 1, timer);
        }
    }
}

void fightTimerTerminate(FightTimer* timer) {
    if (timer->thread != NULL) {
        GSthreadTerminate(timer->thread);
    }
    timer->over = false;
    timer->elapsed = 0.0f;
    timer->limit = 0.0f;
    timer->thread = NULL;
    timer->infinite = 0;
}

// A negative limit means no time limit.
#pragma dont_inline on
void fightTimerInit(FightTimer* timer, f32 limit) {
    if (timer->thread != NULL) {
        fightTimerTerminate(timer);
    }
    timer->over = false;
    timer->elapsed = 0.0f;
    if (limit < 0.0f) {
        timer->infinite = 1;
        timer->limit = -3600.0f;
    } else {
        timer->infinite = 0;
        timer->limit = limit;
    }
    timer->thread = NULL;
}
#pragma dont_inline reset

void fightTimerThreadFunc(FightTimer* timer) {
    timer->elapsed = 0.0f;
    while (timer->elapsed < 60.0f * timer->limit) {
        GSthreadSwitch();
        timer->elapsed += GSgfxVideoGetLastRenderTime();
    }
    timer->over = true;
    for (;;) {
        GSthreadSwitch();
    }
}

}
