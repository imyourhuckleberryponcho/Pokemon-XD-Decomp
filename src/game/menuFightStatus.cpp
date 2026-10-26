#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off

struct MenuFightStatusState {
    u8 unk0[0x16];
    u8 darkFlag;
    u8 level;
    s16 maxHP;
    s16 hp;
    union {
        u32 maxExp;
        f32 maxExpF;
    };
    union {
        u32 exp;
        f32 expF;
    };
    u16 spriteID;
    u16 faceID;
    u8 kind;
    u8 sex;
    u8 unk2A[3];
    u8 hideFlag;
};

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    u8 unk2[2];
    s32 id;
    u8 unk8[0x24];
    u32 seq;
    u8 unk30[0x38];
    void* source;
    u8 unk6C[0x27];
    u8 colorAlpha;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
    u8 unk8[0x4C];
    s16 width;
    s16 height;
    u8 unk58[0xC];
    union {
        u32 color;
        u8 rgba[4];
    };
};

class GSgfxVF;
class GSgfxLayer {
public:
    u8 pad0[0xD34];
    u8 colorCount;
    u8 padD35[3];
    u32 colorMode;
    u8 padD3C[0x16A8 - 0xD3C];
    u32 flagsA;
    u32 flagsB;
    u8 pad16B0[0x1760 - 0x16B0];
    u32 flagsC;
    u32 flagsD;
    u8 pad1768[0x1998 - 0x1768];
    u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

class DeckDarkPokemon {
public:
    u8 getPlayerLevel() const;
};
class DarkPokemon {
public:
    u16 getDarkPokemonID() const;
};
class Pokemon {
public:
    DarkPokemon* getDarkPokemon();
    u8 isDarkPokemon() const;
};
struct MENU_POKEMON_STATUS;

struct MenuFightStatusAnim {
    s16 hpFrom;
    s16 hpFrames;
    s16 hpTime;
    u16 expDone;
    u32 expFrom;
    s16 expFrames;
    s16 expTime;
};

static f32 menuFightStatusPercent(f32 value, f32 max) {
    if (max <= 0.0f) {
        return 0.0f;
    }
    return value * 100.0f / max;
}

extern "C" {

void GSthreadSwitch(void);
void GSsndPlayNow(s32);
void GSsndStopNow(s32);
void* memcpy(void*, const void*, u32);
f32 timeGetLastFrameSec(void);
void* GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s16, s32, u32, u32);
void msgctrlSetValue(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, u8);
u8 winSpriteGetDisp(tagSPRITE_WORK*);
DeckDarkPokemon* deckGetDeckDarkPokemon(u32);
u8 fightKind_CheckFightKind(s32);
s32 menuFightGetStatus(void);
void menuFightSetSeq(void);
void menuFightSetStatus(s32);
u32 menuSeqBiosGetPtr(s32);
void* windowAllocMemory(tagWINDOW_WORK*, s32);
void menuFaceDispFromID(tagWINDOW_WORK*, tagSPRITE_WORK*, u16);
void windowDrawSprite2(s32, s32, s32, s32, s32, tagWINDOW_WORK*, u16, s32, s32);
s32 menuCloseSync(s32, s32);
s32 menuGetCursorItemID(s32);
u16 gamedataBiosGetFlag(void*, u16, u16);
s32 fightFloorGetStatus(s32, u32, s32, s32);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
void* fightFloorGetNowPtr(void);
void* fightFloorGetValidFightSidePtr(void*, u16);
void* fightSideGetValidFightTrainerPtr(void*, u16);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*, void*, void**, u8, u8);
u8 fightTrainerIsGcHero(void*);
Pokemon* fightOutPokemonGetPokemonPtr(void*);
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
GSgfxVF* GSgfxVFGetPredef(s32);
f64 sin(f64);
u32 windowSearchID(s32);
MenuFightStatusAnim* windowGetFreeWork(void*);
MenuFightStatusState* windowGetAllocPtr(void*);

s32 menuFightStatusWaitAnimeEXP(s32 id, u8 wait) {
    u32 window;

    for (;;) {
        window = windowSearchID(id);
        if (window == 0) {
            return 0;
        }
        if (windowGetFreeWork((void*)window)->expFrames == 0) {
            return 0;
        }
        if (wait != 0) {
            GSthreadSwitch();
        } else {
            return 1;
        }
    }
}

void menuFightStatusStartAnimEXP(s32 id, u32 exp) {
    u32 window;
    MenuFightStatusState* state;
    MenuFightStatusAnim* anim;
    u32 diff;

    window = windowSearchID(id);
    if (window != 0) {
        state = windowGetAllocPtr((void*)window);
        anim = windowGetFreeWork((void*)window);
        if (exp > state->exp) {
            diff = exp - state->exp;
        } else {
            diff = state->exp - exp;
        }
        anim->expFrames = diff * 100 / state->maxExp;
        if (anim->expFrames < 15) {
            anim->expFrames = 15;
        }
        anim->expFrom = state->exp;
        state->exp = exp;
        anim->expTime = 0;
        if (exp == state->maxExp) {
            anim->expDone = 1;
        }
        GSsndPlayNow(0x24);
    }
}

s32 menuFightStatusWaitAnimeHP(s32 id, u8 wait) {
    u32 window;

    for (;;) {
        window = windowSearchID(id);
        if (window == 0) {
            return 0;
        }
        if (windowGetFreeWork((void*)window)->hpFrames == 0) {
            return 0;
        }
        if (wait != 0) {
            GSthreadSwitch();
        } else {
            return 1;
        }
    }
}

void menuFightStatusStartAnimHP(s32 id, s16 hp) {
    u32 window;
    MenuFightStatusState* state;
    MenuFightStatusAnim* anim;
    s32 diff;

    window = windowSearchID(id);
    if (window != 0) {
        state = windowGetAllocPtr((void*)window);
        anim = windowGetFreeWork((void*)window);
        diff = state->hp - hp;
        if (diff < 0) {
            diff = -diff;
        }
        anim->hpFrames = diff * 100 / state->maxHP;
        if (anim->hpFrames <= 0) {
            anim->hpFrames = 1;
        }
        anim->hpFrom = state->hp;
        state->hp = hp;
        anim->hpTime = 0;
    }
}

void menuFightStatusSetActive(void) {
}

void menuFightStatusSetHP(s32 id, s16 hp) {
    u32 window = windowSearchID(id);
    if (window != 0) {
        windowGetAllocPtr((void*)window)->hp = hp;
    }
}

}

static void menuUpdateStatusTime(void);
static f32 menuStatusTime;
static f32 menuStatusOldTime;
static s32 menuFightDrawDarkPanel(tagWINDOW_WORK*, tagSPRITE_WORK*, Pokemon*, MENU_POKEMON_STATUS*);

extern "C" {
void menuFightDrawCheckDark(tagWINDOW_WORK*, tagSPRITE_WORK*);
void menuFightDrawParam(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    static f32 cFlash = 0.0f;
    MenuFightStatusState* state = windowGetAllocPtr(window);
    MenuFightStatusAnim* anim = windowGetFreeWork(window);
    u32 color;
    s16 flag = 0;
    u32 barColor;
    s32 bar;
    s32 hp;
    void* trainer;
    void* ary[6];
    s32 count;
    u32 msg;
    GSgfxLayer* layer;
    f32 cur;
    f32 max;
    s16 shown;
    u16 barID;
    s32 x;
    s16 from;
    s32 curI;
    s32 maxI;
    u8 c;
    f32 ratio;
    s32 hit;
    s32 item;
    u32 t;
    u8 val;
    f32 sv;

    menuFightDrawCheckDark(window, sprite);
    if (winSpriteGetDisp(sprite) == 0) {
        return;
    }
    color = window->colorAlpha | 0xFFFFFF00;
    switch (sprite->id) {
    case 0xD5:
    case 0xD6:
    case 0xEF:
        if (state->sex == 2) {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0xD7:
    case 0xD8:
    case 0xF0:
        if (state->sex == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0xD2:
    case 0xED:
        menuFaceDispFromID(window, sprite, state->faceID);
        break;
    case 0xF4:
        flag = 1;
    case 0xE8: {
        if (fightFloorGetStatus(0, 0, 0x32, 0) != 0 && flag != 0) {
            break;
        }
        if (anim->hpFrames != 0) {
            f32 v = (f32)anim->hpTime / (f32)anim->hpFrames * (f32)(state->hp - anim->hpFrom) + (f32)anim->hpFrom;
            hp = (s32)v;
            if ((s16)hp == 0 && v > 0.0f) {
                hp = 1;
            }
        } else {
            hp = state->hp;
        }
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x20, 0, color, 0x42C2);
        msgctrlSetValue(0x5F, (s16)hp);
        {
            s16 w = GSmsgGetRect(0x4272) >> 16;
            shown = 0x18 - w;
        }
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), shown, 1, color, 0x4272);
        msgctrlSetValue(0x5F, state->maxHP);
        shown = GSmsgGetRect(0x4272) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->width - shown, 1, color, 0x4272);
        break;
    }
    case 0xEA:
    case 0xF7:
        winSpriteSetDisp(sprite, 1);
        if (state->hideFlag != 0) {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0xE9:
    case 0xF5:
        if (state->hideFlag == 0) {
            if (menuCBBios_CurrentlyWorkingToolBattle() == 0 && state->sex != 0) {
                trainer = fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(), 0), 0);
                fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(), trainer, ary, 0, 0);
                if (window->id == 0x37) {
                    if (fightTrainerIsGcHero(trainer) == 0) {
                        fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(), trainer, ary, 1, 0);
                        if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[0]), (MENU_POKEMON_STATUS*)state) != 0) {
                            break;
                        }
                    }
                } else if (window->id == 0x40) {
                    if (fightTrainerIsGcHero(trainer) == 0) {
                        count = fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(), trainer, ary, 1, 0);
                        if (count == 1) {
                            if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[0]), (MENU_POKEMON_STATUS*)state) != 0) {
                                break;
                            }
                        } else {
                            if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[1]), (MENU_POKEMON_STATUS*)state) != 0) {
                                break;
                            }
                        }
                    }
                } else if (window->id == 0x38) {
                    fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(), trainer, ary, 0, 0);
                    if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[0]), (MENU_POKEMON_STATUS*)state) != 0) {
                        break;
                    }
                } else if (window->id == 0x41) {
                    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(), trainer, ary, 0, 0);
                    if (count == 1) {
                        if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[0]), (MENU_POKEMON_STATUS*)state) != 0) {
                            break;
                        }
                    } else {
                        if (menuFightDrawDarkPanel(window, sprite, fightOutPokemonGetPokemonPtr(ary[1]), (MENU_POKEMON_STATUS*)state) != 0) {
                            break;
                        }
                    }
                }
            }
                msgctrlSetValue(0x5F, state->level);
            shown = GSmsgGetRect(0x4272) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->width - shown, 1, window->colorAlpha | 0xFFFFFF00, 0x4272);
        }
        break;
    case 0xE7:
    case 0xF3: {
        msgctrlSetValue(0x37, (s32)state->unk0);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 1, color, 0x4279);
        shown = (GSmsgGetRect(0x4279) >> 16) + 4;
        switch (state->kind) {
        case 0:
            msg = 0x9C5;
            break;
        case 1:
            msg = 0x9C6;
            break;
        case 2:
        default:
            msg = 0;
            break;
        }
        if (msg != 0) {
            msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(msg));
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), shown, 0, color, 0x4278);
        }
        break;
    }
    case 0xEB:
    case 0xF8:
        windowDrawSprite2(0, 0, sprite->width, sprite->height, color, window, state->spriteID, 0, winSpriteGetLayerID(window, sprite));
        break;
    case 0xDA:
    case 0xF2: {
        layer = GSgfxLayerFindByID(winSpriteGetLayerID(window, sprite));
        if (layer == 0) {
            break;
        }
        if (anim->hpFrames != 0) {
            cur = (f32)anim->hpTime / (f32)anim->hpFrames * (f32)(state->hp - anim->hpFrom) + (f32)anim->hpFrom;
        } else {
            cur = state->hp;
        }
        max = state->maxHP;
        if (anim->hpFrames != 0) {
            from = anim->hpFrom;
            if (from <= 0) {
                barColor = 0;
            } else if ((f32)from <= 20.0f * max / 100.0f) {
                barColor = 0x80000000;
            } else if ((f32)from <= 50.0f * max / 100.0f) {
                barColor = 0x64640000;
            } else {
                barColor = 0x00800000;
            }
            barColor |= window->colorAlpha;
            x = (s32)((max - 1.0f + (f32)(from * sprite->width)) / max);
            layer->primitive = 0x98;
            layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
            layer->beginSurface(4);
            GXPosition2s16(0, 0);
            GXColor1u32(barColor);
            GXPosition2s16(0, x);
            GXColor1u32(barColor);
            GXPosition2s16(0, sprite->height);
            GXColor1u32(barColor);
            GXPosition2s16(x, sprite->height);
            GXColor1u32(barColor);
            layer->endSurface();
        }
        if (cur <= 0.0f) {
            barID = 0;
        } else if (cur <= 20.0f * max / 100.0f) {
            barID = 0xA0;
        } else if (cur <= 50.0f * max / 100.0f) {
            barID = 0x9F;
        } else {
            barID = 0x90;
        }
        x = (s32)((cur * (f32)sprite->width + (max - 1.0f)) / max);
        if (barID != 0) {
            windowDrawSprite2(0, 0, x, sprite->height, color, window, barID, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0xDC: {
        if (anim->expFrames != 0) {
            curI = (s32)((f32)anim->expTime / (f32)anim->expFrames * (f32)(state->exp - anim->expFrom) + (f32)anim->expFrom);
        } else {
            curI = state->exp;
        }
        maxI = state->maxExp;
        if (curI > maxI) {
            curI = maxI;
        }
        if (maxI > 0) {
            shown = (maxI + curI * sprite->width - 1) / maxI;
            if (shown != 0) {
                cFlash = 0.0f;
                windowDrawSprite2(0, 0, shown, sprite->height, color, window, 0x92, 0, winSpriteGetLayerID(window, sprite));
            } else if (anim->expDone != 0) {
                windowDrawSprite2(0, 0, sprite->width, sprite->height, color, window, 0x92, 0, winSpriteGetLayerID(window, sprite));
                layer = GSgfxLayerFindByID(winSpriteGetLayerID(window, sprite));
                c = (s32)(255.0f - 254.0f * cFlash);
                layer->primitive = 0x80;
                layer->colorCount = 6;
                layer->colorMode = 0;
                layer->flagsB |= 4;
                layer->flagsA |= 1;
                layer->flagsD |= 4;
                layer->flagsC |= 1;
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));
                layer->beginSurface(4);
                GXPosition2s16(0, 0);
                GXColor4u8(c, c, c, c);
                GXPosition2s16(sprite->width, 0);
                GXColor4u8(c, c, c, c);
                GXPosition2s16(sprite->width, sprite->height);
                GXColor4u8(c, c, c, c);
                GXPosition2s16(0, sprite->height);
                GXColor4u8(c, c, c, c);
                layer->endSurface();
                cFlash += timeGetLastFrameSec();
                if (1.0 <= cFlash) {
                    cFlash = 1.0f;
                    anim->expDone = 0;
                }
            }
        }
        break;
    }
    case 0xE6: {
        ratio = state->expF / state->maxExpF;
        if (ratio < 0.2f) {
            bar = (s32)((f32)sprite->width * (ratio / 0.2f));
        } else {
            bar = sprite->width;
        }
        if ((s16)bar < 0) {
            bar = 0;
        }
        windowDrawSprite2(0, 0, bar, sprite->height, color, window, 0x91, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0xE5: {
        ratio = state->expF / state->maxExpF;
        if (ratio < 0.4f) {
            bar = (s32)((f32)sprite->width * ((ratio - 0.2f) / 0.2f));
        } else {
            bar = sprite->width;
        }
        if ((s16)bar < 0) {
            bar = 0;
        }
        windowDrawSprite2(0, 0, bar, sprite->height, color, window, 0x91, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0xE4: {
        ratio = state->expF / state->maxExpF;
        if (ratio < 0.6f) {
            bar = (s32)((f32)sprite->width * ((ratio - 0.4f) / 0.2f));
        } else {
            bar = sprite->width;
        }
        if ((s16)bar < 0) {
            bar = 0;
        }
        windowDrawSprite2(0, 0, bar, sprite->height, color, window, 0x91, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0xE3: {
        ratio = state->expF / state->maxExpF;
        if (ratio < 0.8f) {
            bar = (s32)((f32)sprite->width * ((ratio - 0.6f) / 0.2f));
        } else {
            bar = sprite->width;
        }
        if ((s16)bar < 0) {
            bar = 0;
        }
        windowDrawSprite2(0, 0, bar, sprite->height, color, window, 0x91, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0xE2: {
        ratio = state->expF / state->maxExpF;
        if (ratio < 1.0f) {
            bar = (s32)((f32)sprite->width * ((ratio - 0.8f) / 0.2f));
        } else {
            bar = sprite->width;
        }
        if ((s16)bar < 0) {
            bar = 0;
        }
        windowDrawSprite2(0, 0, bar, sprite->height, color, window, 0x91, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0xF6:
        winSpriteSetDisp(sprite, 0);
        if (gamedataBiosGetFlag(0, 0xE, 0) != 0) {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0xD1:
        flag = 1;
    case 0xD0:
    case 0xEC: {
        hit = 0;
        winSpriteSetDisp(sprite, 0);
        if (menuCloseSync(0x5C, 0) != 0) {
            item = menuGetCursorItemID(0x5C);
            switch (window->id) {
            case 0x37:
                if (item == 0x138) {
                    hit = 1;
                }
                break;
            case 0x40:
                if (item == 0x139) {
                    hit = 1;
                }
                break;
            case 0x38:
                if (item == 0x13A) {
                    hit = 1;
                }
                break;
            case 0x41:
                if (item == 0x13B) {
                    hit = 1;
                }
                break;
            }
            t = (u32)(100.0f * menuStatusTime) % 100;
            sprite->color = 0xFFFFFFFF;
            sv = sin(3.14f * (0.01f * (f32)t));
            val = (200.0f * sv);
            sprite->rgba[1] -= val;
            sprite->rgba[2] -= val;
            if (hit != 0) {
                if (flag != 0) {
                    if (fightFloorGetStatus(0, 0, 0x32, 0) != 0) {
                        winSpriteSetDisp(sprite, 1);
                    }
                } else {
                    winSpriteSetDisp(sprite, 1);
                }
            }
        }
        break;
    }
    }
}
}

static s32 menuFightDrawDarkPanel(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, Pokemon* pokemon, MENU_POKEMON_STATUS*) {
    s16 x;

    if (pokemon != 0 && pokemon->isDarkPokemon()) {
        msgctrlSetValue(0x37, (s32)GSmsgGetGSchar(0x4443));
        x = GSmsgGetRect(0x4278) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->width - x, 0, window->colorAlpha | 0xFFFFFF00, 0x4278);
        msgctrlSetValue(0x5F, deckGetDeckDarkPokemon(pokemon->getDarkPokemon()->getDarkPokemonID())->getPlayerLevel());
        x = sprite->width - x - (GSmsgGetRect(0x4272) >> 16);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 1, window->colorAlpha | 0xFFFFFF00, 0x4272);
        return 1;
    }
    return 0;
}

extern "C" {

void menuFightDrawCheckDark(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    MenuFightStatusState* state = windowGetAllocPtr(window);
    s16 id = sprite->id;
    u8 dark = state->darkFlag;
    u8 disp = 1;

    switch (id) {
    case 0xD3:
    case 0xD4:
    case 0xDB:
    case 0xDC:
    case 0xEE:
        if (state->sex != 0) {
            disp = 0;
        } else {
            disp = 1;
        }
        break;
    case 0xD5:
    case 0xD6:
    case 0xDD:
    case 0xDE:
    case 0xDF:
    case 0xE0:
    case 0xE1:
    case 0xE2:
    case 0xE3:
    case 0xE4:
    case 0xE5:
    case 0xE6:
    case 0xEF:
        if (state->sex != 0) {
            disp = 1;
        } else {
            disp = 0;
        }
        break;
    }
    switch (id) {
    case 0xD4:
    case 0xD6:
    case 0xDB:
    case 0xDC:
    case 0xDD:
    case 0xDE:
    case 0xDF:
    case 0xE0:
    case 0xE1:
    case 0xE2:
    case 0xE3:
    case 0xE4:
    case 0xE5:
    case 0xE6:
        if (dark == 1) {
            disp = 0;
        }
        break;
    }
    winSpriteSetDisp(sprite, disp);
}

s32 menuFightStatusCtrl(tagWINDOW_WORK* window) {
    MenuFightStatusAnim* anim;
    MenuFightStatusState* state;
    u32 flag;

    anim = windowGetFreeWork(window);
    flag = 0;
    if (window->state == 0) {
        state = (MenuFightStatusState*)windowAllocMemory(window, 0x30);
        if (state != 0) {
            memcpy(state, window->source, 0x30);
            if (fightKind_CheckFightKind(0xD) != 0) {
                state->darkFlag = 1;
            }
            if (fightKind_CheckFightKind(0xE) != 0) {
                state->darkFlag = 1;
            }
            if (fightKind_CheckFightKind(0xF) != 0) {
                state->darkFlag = 1;
            }
            if (menuFightGetStatus() != 0) {
                menuFightSetSeq();
            }
        }
    } else if (window->state == 1) {
        if (menuFightGetStatus() != 0) {
            if (window->seq == menuSeqBiosGetPtr(0x1A5)) {
                flag = 1;
            }
            if (window->seq == menuSeqBiosGetPtr(0x1A9)) {
                flag = 1;
            }
            if (flag != 0) {
                menuFightSetStatus(0);
            }
        }
    }
    windowGetAllocPtr(window);
    if (anim->hpFrames != 0) {
        anim->hpTime += (s32)(60.0f * timeGetLastFrameSec());
        if (anim->hpTime > anim->hpFrames) {
            anim->hpFrames = 0;
        }
    }
    if (anim->expFrames != 0) {
        anim->expTime += (s32)(60.0f * timeGetLastFrameSec());
        if (anim->expTime > anim->expFrames) {
            anim->expFrames = 0;
            GSsndStopNow(0x24);
        }
    }
    menuUpdateStatusTime();
    return 0;
}

}

static void menuUpdateStatusTime(void) {
    f32 time = timeGetLastFrameSec();
    if (time != menuStatusOldTime) {
        menuStatusOldTime = time;
        menuStatusTime += time;
    }
}
