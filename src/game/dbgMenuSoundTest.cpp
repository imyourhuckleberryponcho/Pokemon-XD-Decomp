#include <dolphin/types.h>

// Debug menu units were built without the peephole optimizer.
#pragma peephole off

extern "C" {

extern u32* snd_test_se_number;
extern u16* snd_test_se;
extern u32* snd_test_nakigoe_number;
extern u16* snd_test_nakigoe;
extern u32* snd_test_env_number;
extern u16* snd_test_env;
extern u32* snd_test_bgm_number;
extern u16* snd_test_bgm;

void GSsndSetMasterVolume(s32 volume, s32, s32, s32);
s32 GSsndGetStatus(u16 id);
void GSsndClose(u16 id);
void soundOpenPlay(u16 id, s32, s32 volume);
void soundOpenPlayEnv(u16 id, s32, s32 volume);
s32 menuOpen(s32 menuID, s32);
void menuClose(s32 menuID);

static void sndPlay(u16 id, BOOL bgm);

// Nothing references these, but the original link kept them.
#pragma force_active on

s32 dbgMenuSoundTestChangeSE(s32 item) {
    switch (item) {
    case 0x155:
        GSsndSetMasterVolume(0x7F, 0, 0, 1);
        break;
    case 0x156:
        GSsndSetMasterVolume(0, 0, 0, 1);
        break;
    }
    return 0;
}

s32 dbgMenuSoundTestChangeBGM(s32 item) {
    switch (item) {
    case 0x153:
        GSsndSetMasterVolume(0x7F, 0, 1, 0);
        break;
    case 0x154:
        GSsndSetMasterVolume(0, 0, 1, 0);
        break;
    }
    return 0;
}

s32 dbgMenuSoundTestNAKIGOE(void) {
    s32 index;
    while ((index = menuOpen(2, 1)) != -1) {
        if (index < *snd_test_nakigoe_number) {
            sndPlay(snd_test_nakigoe[index], FALSE);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestSE(void) {
    s32 index;
    while ((index = menuOpen(2, 1)) != -1) {
        if (index < *snd_test_se_number) {
            sndPlay(snd_test_se[index], FALSE);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestENV(void) {
    s32 index;
    s32 i;
    while ((index = menuOpen(2, 1)) != -1) {
        if (index < *snd_test_env_number) {
            for (i = 0; i < *snd_test_env_number; i++) {
                if (index != i) {
                    switch (GSsndGetStatus(snd_test_env[i])) {
                    case 1:
                    case 2:
                    case 3:
                        GSsndClose(snd_test_env[i]);
                        break;
                    }
                }
            }
            sndPlay(snd_test_env[index], FALSE);
        }
    }
    menuClose(2);
    return -1;
}

s32 dbgMenuSoundTestBGM(void) {
    s32 index;
    s32 i;
    while ((index = menuOpen(2, 1)) != -1) {
        if (index < *snd_test_bgm_number) {
            for (i = 0; i < *snd_test_bgm_number; i++) {
                if (index != i) {
                    GSsndGetStatus(snd_test_bgm[i]);
                }
            }
            sndPlay(snd_test_bgm[index], TRUE);
        }
    }
    menuClose(2);
    return -1;
}

#pragma force_active reset

static void sndPlay(u16 id, BOOL bgm) {
    s32 status = GSsndGetStatus(id);
    if (status != 0 && status >= 0 && status < 4) {
        GSsndClose(id);
        return;
    }
    if (bgm) {
        soundOpenPlay(id, 0, 0x7F);
    } else {
        soundOpenPlayEnv(id, 0, 0x7F);
    }
}

}
