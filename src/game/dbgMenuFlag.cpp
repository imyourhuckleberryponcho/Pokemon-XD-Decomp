#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct WindowKeyInfo {
    u16 trigger;
    u8 unk2[4];
    u16 repeat;
};

struct FlagCursor {
    s16 top;
    s16 pos;
};
union FlagCursorU {
    u32 raw;
    FlagCursor c;
};

struct FlagWindow {
    u8 unk0[4];
    s32 menu;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x68];
    s32 selection;
    u8 unk8C[0x10];
    FlagCursor cursor;
};

struct FlagDataInfo {
    u32 num;
    s16 first;
};

struct FlagData {
    u8 unk0[4];
    s16 next;
};

struct FlagEtc {
    u8 type;
    u8 unk1;
    u16 floor;
    u16 pokedoru;
    u8 unk6[2];
    u32 flagValue;
    void* script;
    f32 x;
    f32 y;
    f32 z;
    void* msg;
};

extern "C" {
int sprintf(char* buf, const char* fmt, ...);
WindowKeyInfo* windowGetKeyInfo(void);
s32 GSflagGet(s32);
void GSflagOff(s32);
void GSflagOn(s32);
void GSflagSet(s32, s32);
s32 GSfloorGetCurrent(void);
u8 GSfloorIsFloorPushed(void);
u32 GSinputButtonsPressed(s32);
u32 GSmsgGetRect(void*);
void GSprint(s32 layer, s32 x, s32 y, u32 color, const char* fmt, ...);
void GSsndPlayNow(s32);
void GSthreadSwitch(void);
void appScriptCommonCall(void*);
s32 dbgMenuGetLayerID(void);
void floorChangePos(s32 floor, s32, f32, f32, f32);
void heroBiosSetPokedoru(void*, u16);
void heroSetFollowerWithID(s32, s32);
void menuClose(s32);
u8 menuDataBiosGetDispMax(s32);
s32 menuOpen(s32, s32);
void menuSubDrawSimpleWindow(s32, s32, s32, s32, s32);
void menuSubDrawTriangle(s32, s32, s32, s32, s32, s32, s32);
u8 menuSubOpenNumberInputDigit(s32, s32*);
void* savedataGetStatus(s32, s32);

extern FlagData* flag_data;
extern FlagDataInfo* flag_data_number;
extern FlagEtc* flag_etc;
extern u32* flag_etc_number;
}

static FlagCursor _dbgMenuFlagCursor = {0, 0};

extern "C" {
static char* _dbgMenuFlagInfoGetMsg(s32 index);
static u16 _dbgMenuFlagGetID(s32 index);
static s32 _dbgMenuFlagGetMenuNum(FlagWindow* window, s32* maxWidth);
}

extern "C" {

void dbgMenuFlagInfoDraw(FlagWindow* window) {
    s32 height;
    s32 disp;
    s32 count;
    s32 y;
    s32 i;
    s32 color;
    y = 0x28;
    disp = menuDataBiosGetDispMax(window->menu);
    count = flag_data_number->num;
    if (count > disp) {
        count = disp;
    }
    height = count * 13;
    menuSubDrawSimpleWindow(window->layer, 0x1E, 0x28, 0x7D, height);
    if (_dbgMenuFlagCursor.top > 0) {
        menuSubDrawTriangle(window->layer, 0x46, 0x21, 0x5A, 0x21, 0x50, 0x17);
    }
    if ((u32)(flag_data_number->num - _dbgMenuFlagCursor.top) > disp) {
        menuSubDrawTriangle(window->layer, 0x46, height + 0x2F, 0x5A, height + 0x2F, 0x50, height + 0x39);
    }
    for (i = 0; i < count; i++) {
        if (_dbgMenuFlagCursor.pos == i) {
            color = 0xFF0000FF;
        } else {
            color = -1;
        }
        GSprint(window->layer, 0x1E, y, color, _dbgMenuFlagInfoGetMsg(i + _dbgMenuFlagCursor.top));
        GSprint(window->layer, 0x82, y, color, "%d", GSflagGet(i + _dbgMenuFlagCursor.top));
        y += 13;
    }
}

void dbgMenuFlagInfoCursor(FlagWindow* window) {
    u16 repeat = windowGetKeyInfo()->repeat;
    u16 trigger = windowGetKeyInfo()->trigger;
    s16 total = flag_data_number->num;
    s16 disp = menuDataBiosGetDispMax(window->menu);
    FlagCursorU u;
    if (total < disp) {
        disp = total;
    }
    u.raw = *(u32*)&_dbgMenuFlagCursor;
    if (repeat & 1) {
        u.c.pos--;
    } else if (repeat & 2) {
        u.c.pos++;
    }
    if (repeat & 4) {
        u.c.pos = u.c.pos - (menuDataBiosGetDispMax(window->menu) - 1);
    } else if (repeat & 8) {
        u.c.pos = menuDataBiosGetDispMax(window->menu) + u.c.pos - 1;
    }
    if (u.c.pos < 0) {
        u.c.top += u.c.pos;
        u.c.pos = 0;
        if (u.c.top < 0) {
            u.c.pos = disp - 1;
            u.c.top = total - disp;
        }
    } else if (u.c.pos >= disp) {
        u.c.top += u.c.pos - (disp - 1);
        u.c.pos = disp - 1;
        if (u.c.top + u.c.pos >= total) {
            u.c.top = 0;
            u.c.pos = 0;
        }
    }
    if (trigger & 0x80) {
        GSflagOn(u.c.top + u.c.pos);
    } else if (trigger & 0x40) {
        GSflagOff(u.c.top + u.c.pos);
    }
    *(u32*)&_dbgMenuFlagCursor = u.raw;
    window->selection = u.c.top + u.c.pos;
}

static char* _dbgMenuFlagInfoGetMsg(s32 index) {
    static char buff[0x80];
    _dbgMenuFlagGetID(index);
    sprintf(buff, "[%4d]", index);
    return buff;
}

static u16 _dbgMenuFlagGetID(s32 index) {
    s16 v;
    s32 i;
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= flag_data_number->num) {
        return 0;
    }
    v = flag_data_number->first;
    if (index != 0) {
        for (i = 0; i < index - 1; i++) {
            v = flag_data[v].next;
        }
        v = flag_data[v].next;
    }
    return v;
}

void dbgMenuFlagCursor(FlagWindow* window) {
    u16 repeat = windowGetKeyInfo()->repeat;
    s8 total = _dbgMenuFlagGetMenuNum(window, 0);
    s8 disp = menuDataBiosGetDispMax(window->menu);
    FlagCursorU u;
    if (total - 48 < disp) {
        disp = total;
    }
    u.raw = *(u32*)&window->cursor;
    if (repeat & 1) {
        u.c.pos--;
    } else if (repeat & 2) {
        u.c.pos++;
    }
    if (repeat & 4) {
        u.c.pos = u.c.pos - (disp - 1);
    } else if (repeat & 8) {
        u16 rf_t = u.c.pos;
        u.c.pos = disp + rf_t - 1;
    }
    if (u.c.pos < 0) {
        u.c.top += u.c.pos;
        u.c.pos = 0;
        if (u.c.top < 0) {
            u.c.pos = disp - 1;
            u.c.top = total - disp;
        }
    } else if (u.c.pos >= disp) {
        u.c.top += u.c.pos - (disp - 1);
        u.c.pos = disp - 1;
        if (u.c.top + u.c.pos >= total) {
            u.c.top = 0;
            u.c.pos = 0;
        }
    }
    s16 rf_t = u.raw;
    *(u32*)&window->cursor = rf_t;
    window->selection = u.c.top + (u.c.pos + 1);
}

void dbgMenuFlagSetEtc(s32 index);

s32 dbgMenuFlagCheck(void) {
    s32 i;
    int id;
    s32 value;
    if (GSfloorIsFloorPushed()) {
        GSsndPlayNow(0x13);
        for (i = 0; (u32)i < 15; i++) {
            GSprint(dbgMenuGetLayerID(), 200, 240, -1, "このフロアからフロアチェンジはおこなえません");
            GSthreadSwitch();
        }
        return -1;
    }
    if (GSinputButtonsPressed(1) & 0x20) {
        for (;;) {
            id = menuOpen(0x27, 1);
            if (id >= 0) {
                if (menuSubOpenNumberInputDigit(GSflagGet(id), &value)) {
                    GSflagSet(id, value);
                }
            } else if (id == -1) {
                menuClose(0x27);
                return -1;
            } else {
                break;
            }
        }
    } else {
        id = menuOpen(0xB, 1);
        menuClose(0xB);
        if (id > 0) {
            dbgMenuFlagSetEtc(id);
        } else if (id == -1) {
            return -1;
        }
    }
    return 0;
}

void dbgMenuFlagSetEtc(s32 index) {
    GSflagSet(0x3C4, flag_etc[index].flagValue);
    GSflagSet(0x3DE, 1);
    switch (flag_etc[index].type) {
    case 0:
        heroSetFollowerWithID(0, 0);
        break;
    case 1:
        heroSetFollowerWithID(1, 0);
        break;
    case 2:
        heroSetFollowerWithID(2, 0);
        break;
    case 3:
        heroSetFollowerWithID(3, 0);
        break;
    }
    heroBiosSetPokedoru(savedataGetStatus(0, 2), flag_etc[index].pokedoru);
    if (flag_etc[index].script != 0) {
        appScriptCommonCall(flag_etc[index].script);
    }
    {
        u32 floor = flag_etc[index].floor;
        if (floor == 0) {
            floor = GSfloorGetCurrent();
        }
        floorChangePos(floor, 0, flag_etc[index].x, flag_etc[index].y, flag_etc[index].z);
    }
}

static s32 _dbgMenuFlagGetMenuNum(FlagWindow* window, s32* maxWidth) {
    s32 offset;
    u32 i;
    s32 count;
    if (maxWidth != 0) {
        *maxWidth = 0;
    }
    count = 0;
    for (i = 0, offset = 0; i < *flag_etc_number; i++) {
        void* msg = *(void**)((u8*)flag_etc + offset + 0x1C);
        if (msg != 0) {
            if (msg != 0) {
                count++;
                if (maxWidth != 0) {
                    s32 w = GSmsgGetRect(msg) >> 16;
                    if (*maxWidth < w) {
                        *maxWidth = w;
                    }
                }
            }
        }
        offset += 0x20;
    }
    return count;
}

}
