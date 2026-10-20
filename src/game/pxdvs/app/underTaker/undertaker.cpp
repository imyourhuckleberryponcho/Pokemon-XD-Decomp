// STATUS: 5/8 exact (CallBack 98.8%, _appearMirabo 95.7%, SetPlace 92%: register order and rand%2 scheduling); LAYOUT+CONST OK, default flags.
#include <dolphin/types.h>

struct UnderTakerPlace {
    u16 weight;
    u16 id;
    u32 msgID;
};

struct UnderTakerData {
    u16 threshold;
    u16 lowChance;
    u16 midChance;
    u16 randMod;
    u16 maxCount;
    u16 limit;
    u32 flagStart;
    u32 flagCounter;
    u32 flagLevel;
    u32 flagID;
    u32 flagAway;
    u32 flagDisable;
    u32 unk24;
    u32 etcLow;
    u32 etcHigh;
    u32 flagSide;
    UnderTakerPlace places[7];
};

struct FlagEtcEntry {
    u8 unk0[8];
    u32 flagValue;
    u8 unkC[0x20 - 0xC];
};

struct WorldMapXDInfo {
    u8 unk0[0x94];
    u32 flagA;
    u8 unk98[0x190 - 0x98];
    u32 flagB;
};

extern "C" {
extern UnderTakerData* undertakerdata;
extern FlagEtcEntry* flag_etc;
extern WorldMapXDInfo* worldmapXD_data;

u32 GSflagGet(u32);
void GSflagSet(u32, s32);
u8 GSflagTest(u32);
void GSthreadSwitch(void);
s32 HSD_Rand(void);
u32 floorGetCurrent(void);
u8 darkpokemonCheckUnderTaker(void);
void menuIntUnderTakerMenuClose(void);
void menuIntUnderTakerMenuOpen(void);
void heroMoveInitEvent(void);
void heroMoveSetColision(s32);
void heroMoveTermEvent(void);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
u16 esabaGetPokemonID(s32);
}

static void _appearMirabo(void);

static inline UnderTakerPlace* _getPlace(s32 index) {
    if (index >= 7) {
        return 0;
    }
    return &undertakerdata->places[index];
}

static inline bool _isInRange(void) {
    u32 f = GSflagGet(0x3C4);
    if (f >= flag_etc[undertakerdata->etcLow].flagValue && f <= flag_etc[undertakerdata->etcHigh].flagValue) {
        return true;
    }
    return false;
}

static inline void _clearFlags(void) {
    GSflagSet(undertakerdata->flagID, 0);
    GSflagSet(undertakerdata->flagCounter, 0);
    GSflagSet(undertakerdata->flagLevel, 0);
    menuIntUnderTakerMenuClose();
}

static inline void _disappearWithMessage(void) {
    _clearFlags();
    heroMoveInitEvent();
    heroMoveSetColision(1);
    winMsgOpen(3, 0x3E85, 1, 1);
    winMsgClose(1);
    heroMoveTermEvent();
}

static inline bool _isSpecialFloor(u32 floor) {
    if (GSflagTest(worldmapXD_data->flagA) && floor != 0x71) {
        return true;
    }
    return false;
}

static inline bool _isFloorB(u32 floor) {
    u32 flagB = worldmapXD_data->flagB;
    if (GSflagTest(0x8D1) && GSflagTest(flagB) && floor != 0x3B) {
        return true;
    }
    return false;
}

static inline void _pickEsaba(u32& sel) {
    s32 candidates[3];
    s32 table[3] = {0x5A, 0x5B, 0x5C};
    s32 count = 0;
    s32 j;
    for (j = 0; j <= 2; j++) {
        if (esabaGetPokemonID(j) == 0) {
            candidates[count++] = j;
        }
    }
    if (count == 0) {
        sel = 0;
    } else {
        u16 idx = (u16)HSD_Rand() % count;
        sel = table[candidates[idx]];
    }
}

static inline void _setPlace(u32 place) {
    GSflagSet(undertakerdata->flagID, place);
    GSflagSet(undertakerdata->flagAway, 0);
    u16 side = HSD_Rand();
    GSflagSet(undertakerdata->flagSide, (u8)(side % 2));
    heroMoveInitEvent();
    heroMoveSetColision(1);
    GSthreadSwitch();
    menuIntUnderTakerMenuOpen();
    winMsgOpen(3, 0x3E84, 1, 1);
    winMsgClose(1);
    menuIntUnderTakerMenuClose();
    heroMoveTermEvent();
}

extern "C" {

void underTakerMenuResore(void) {
}

u32 underTakerGetMiraboPlace(void) {
    return GSflagGet(undertakerdata->flagID);
}

void underTakerCallBackFunc(s32 unused0, s32 unused1, u16 amount) {
    if (GSflagTest(undertakerdata->flagStart) && !GSflagTest(undertakerdata->flagDisable) &&
        darkpokemonCheckUnderTaker()) {
        if (GSflagGet(undertakerdata->flagID) == 0) {
            u32 level;
            u16 cur = GSflagGet(undertakerdata->flagCounter);
            u32 total = cur + amount;
            if ((u16)total >= undertakerdata->threshold) {
                u16 high;
                u16 low = undertakerdata->lowChance;
                u16 mid = undertakerdata->midChance;
                u16 mod = undertakerdata->randMod;
                high = low + mid;
                u16 rnd = (u16)HSD_Rand() % mod;
                if (rnd < low) {
                    level = (u16)GSflagGet(undertakerdata->flagLevel) + 1;
                    if ((u16)level >= undertakerdata->maxCount - 1) {
                        if (_isInRange()) {
                            level--;
                        } else {
                            _appearMirabo();
                        }
                    }
                    GSflagSet(undertakerdata->flagLevel, (u16)level);
                } else if (rnd < high) {
                    level = (u16)GSflagGet(undertakerdata->flagLevel);
                    if (level != 0) {
                        level--;
                    }
                    GSflagSet(undertakerdata->flagLevel, (u16)level);
                }
                total = (total - undertakerdata->threshold) & 0xFFFF;
            }
            GSflagSet(undertakerdata->flagCounter, (u16)total);
        } else if (_isInRange()) {
            _disappearWithMessage();
        } else {
            u16 cur = GSflagGet(undertakerdata->flagAway);
            u32 away = cur + amount;
            if ((u16)away >= undertakerdata->limit) {
                _disappearWithMessage();
            }
            GSflagSet(undertakerdata->flagAway, (u16)away);
        }
    }
}

void underTakerMiraboDisAppear(void) {
    _clearFlags();
}

}

static void _appearMirabo(void) {
    u16 total = 0;
    u16 rnd;
    u16 sum;
    u32 sel;
    u32 floor;
    s32 i;
    UnderTakerPlace* place;

    i = 0;
    for (;;) {
        place = _getPlace(i);
        if (place == 0) {
            break;
        }
        total += place->weight;
        i++;
    }
    rnd = (u16)HSD_Rand() % total;
    sum = 0;
    i = 0;
    for (;;) {
        place = _getPlace(i);
        if (place == 0) {
            break;
        }
        sum += place->weight;
        if (rnd < sum) {
            sel = place->id;
            break;
        }
        i++;
    }
    floor = floorGetCurrent();
    if (sel == undertakerdata->places[0].id) {
        floor = floorGetCurrent();
        if (!_isSpecialFloor(floor)) {
            _pickEsaba(sel);
        }
    } else if (sel == undertakerdata->places[1].id) {
        floor = floorGetCurrent();
        if (!_isFloorB(floor)) {
            floor = floorGetCurrent();
            if (_isSpecialFloor(floor)) {
                sel = undertakerdata->places[0].id;
            } else {
                sel = 0;
            }
            if (sel == 0) {
                _pickEsaba(sel);
            }
        }
    } else if (sel == undertakerdata->places[2].id) {
        if (esabaGetPokemonID(0) != 0 || floor == sel) {
            floor = floorGetCurrent();
            if (_isSpecialFloor(floor)) {
                sel = undertakerdata->places[0].id;
            } else {
                sel = 0;
            }
        }
    } else if (sel == undertakerdata->places[3].id) {
        if (esabaGetPokemonID(1) != 0 || floor == sel) {
            floor = floorGetCurrent();
            if (_isSpecialFloor(floor)) {
                sel = undertakerdata->places[0].id;
            } else {
                sel = 0;
            }
        }
    } else if (sel == undertakerdata->places[4].id) {
        if (esabaGetPokemonID(2) != 0 || floor == sel) {
            floor = floorGetCurrent();
            if (_isSpecialFloor(floor)) {
                sel = undertakerdata->places[0].id;
            } else {
                sel = 0;
            }
        }
    }
    if (sel != 0) {
        _setPlace(sel);
    } else {
        GSflagSet(undertakerdata->flagCounter, 0);
        GSflagSet(undertakerdata->flagLevel, (u16)(undertakerdata->maxCount - 2));
    }
}

extern "C" {

s32 undertakerGetPlace(u32* out) {
    s32 n = 0;
    if (GSflagTest(undertakerdata->flagStart) && !GSflagTest(undertakerdata->flagDisable) &&
        darkpokemonCheckUnderTaker()) {
        u32 ids[7];
        s32 i;
        u32 floor;
        i = 0;
        for (;;) {
            UnderTakerPlace* place = _getPlace(i);
            if (place == 0) {
                break;
            }
            ids[i] = place->id;
            i++;
        }
        out[n++] = 0;
        floor = floorGetCurrent();
        if (!_isSpecialFloor(floor)) {
            out[n] = ids[0];
            n++;
        }
        floor = floorGetCurrent();
        if (!_isFloorB(floor)) {
            out[n] = ids[1];
            n++;
        }
        for (i = 0; i <= 2; i++) {
            if (esabaGetPokemonID(i) == 0) {
                out[n++] = ids[i + 2];
            }
        }
    }
    return n;
}

void undertakerSetPlace(u32 place) {
    _setPlace(place);
}

u32 undertakerGetStartFlagID(void) {
    return undertakerdata->flagStart;
}

}
