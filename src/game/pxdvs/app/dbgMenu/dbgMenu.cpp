#include <dolphin/types.h>

struct tagWINDOW_WORK {
    u8 unk0[4];
    s32 menuID;
    u8 unk8[0x94];
    s16 top;
    s16 cursor;
};

struct DbgMenuData {
    u8 end : 1;
    u8 flags : 7;
    u8 unk1;
    s16 link;
    u32 msgID;
    s32 (*func)(s32, s32);
};

extern "C" {

void* GSgfxLayerFindByID(s32);
u32 GSmsgGetRect(u32);
s32 dbgMenuGetRootMenu(void);
void menuClose(s32);
s8 menuDataBiosGetDispMax(s32);
u8 menuIsCheck(s32);
s32 menuOpenCustom(s32, ...);
struct DbgKeyInfo {
    u16 unk0;
    u8 unk2[4];
    u16 repeat;
};
DbgKeyInfo* windowGetKeyInfo(void);
tagWINDOW_WORK* windowSearchID(s32);

extern s32 _menu_data_number;
extern s32* _pCursor;
extern u32 (*debugMenuDataGetNum)(void);
extern DbgMenuData* (*debugMenuDataGetPtr)(s32);

}

static s32 _dbgMenuSub(s32);
static s32 _dbgMenuGetMenuNum(tagWINDOW_WORK*, s32*);
static s32 _dbgMenuCheckTerminate(tagWINDOW_WORK*, s32);
static s32 _dbgMenuGetMenuNo(s32);
static s32 _dbgMenuGetMsgID(tagWINDOW_WORK*, s32);
static s32 _dbgMenuGetItemNo(tagWINDOW_WORK*, s32);

inline s32 debugMenuGetNum(void) {
    if (debugMenuDataGetNum == 0) {
        return 0;
    }
    return debugMenuDataGetNum();
}

inline DbgMenuData* dbgMenuGetPtr(s32 index) {
    if (debugMenuDataGetPtr == 0) {
        return 0;
    }
    return debugMenuDataGetPtr(index);
}

typedef s32 (*DbgMenuFunc)(s32, s32);

inline DbgMenuFunc dbgMenuGetFunc(s32 index) {
    DbgMenuData* data = dbgMenuGetPtr(index);
    if (data == 0) {
        return 0;
    }
    return data->func;
}

inline s16 dbgMenuGetLink(s32 index) {
    DbgMenuData* data = dbgMenuGetPtr(index);
    if (data == 0) {
        return 0;
    }
    return data->link;
}

static inline s16 _dbgMenuGetLink(s32 item) {
    s16 link;

    if (item <= 0 || debugMenuGetNum() <= item) {
        return 0;
    }
    link = dbgMenuGetLink(item);
    if (link <= 0 || debugMenuGetNum() <= link) {
        link = 0;
    }
    return link;
}

static inline tagWINDOW_WORK* _dbgMenuGetWin(s32 depth) {
    s32 id = _menu_data_number + depth;
    return windowSearchID(depth < 0 ? 0 : id + 1);
}

static inline s32 _dbgMenuGetIndex(tagWINDOW_WORK* window) {
    s32 index = -1;
    s32 base = _menu_data_number + 1;
    s32 id = window->menuID;
    index = id < base ? index : id - base;
    return index;
}

static s32 _dbgLayerID = -1;
static u8 _dbgMenuEnable;
static s32* _pCursorUnused;
static u8 _dbgMenuMode;

static inline s32 _isOpen(void) {
    s32 open = menuIsCheck(_menu_data_number + 1) != 0;
    return open;
}

static inline void _close(void) {
    _dbgMenuMode = 0;
    menuClose(_menu_data_number + 1);
}

extern "C" {

s32 dbgMenuGetLayerID(void) {
    return _dbgLayerID;
}

void dbgMenuSetLayerID(s32 id) {
    _dbgLayerID = id;
}

void dbgMenuCursor(tagWINDOW_WORK* window) {
    s32 count;
    s32 repeat = windowGetKeyInfo()->repeat;
    count = (s8)_dbgMenuGetMenuNum(window, 0);
    s16 cursor;
    s16 top;
    s8 visible = menuDataBiosGetDispMax(window->menuID);

    if (count < visible) {
        visible = count;
    }
    top = window->top;
    cursor = window->cursor;
    if (repeat & 1) {
        cursor -= 1;
    } else if (repeat & 2) {
        cursor += 1;
    }
    if (cursor < 0) {
        top += cursor;
        cursor = 0;
        if (top < 0) {
            cursor = (s8)(visible - 1);
            top = (s8)(count - visible);
        }
    } else if (cursor >= visible) {
        top = top + (cursor - (visible - 1));
        cursor = (s8)(visible - 1);
        if (top + cursor >= count) {
            cursor = top = 0;
        }
    }
    window->top = top;
    window->cursor = cursor;
}

u8 dbgMenuGetEnable(void) {
    return _dbgMenuEnable;
}

void dbgMenuSetEnable(u8 enable) {
    _dbgMenuEnable = enable;
}

s32 dbgMenuIsOpen(void) {
    return _isOpen();
}

void dbgMenuClose(void) {
    _close();
}

void dbgMenuMain(u8 mode) {
    u32 count;

    if (_dbgLayerID == -1 || GSgfxLayerFindByID(_dbgLayerID) == 0) {
        if (_isOpen()) {
            _close();
        }
    } else {
        if (debugMenuDataGetNum == 0) {
            count = 0;
        } else {
            count = debugMenuDataGetNum();
        }
        if (count != 0 && _dbgMenuEnable != 0) {
            if (!_isOpen()) {
                _dbgMenuMode = mode;
                do {
                } while (_dbgMenuSub(0) >= 0 && _dbgMenuMode == 1);
            }
        }
    }
}

}

static s32 _dbgMenuSub(s32 depth) {
    s32 result;
    s32 menuID;
    s32 layer;
    s32 selected;
    s32* cursor;
    tagWINDOW_WORK* window;
    s32 item;
    s16 link;
    DbgMenuFunc func;

    result = 0;
    menuID = _menu_data_number + 1 + depth;
    for (;;) {
        layer = depth < 0 ? 0 : _menu_data_number + depth;
        cursor = &_pCursor[_dbgMenuGetMenuNo(layer)];
        selected = menuOpenCustom(menuID, layer, cursor, 0, 1, 0);
        window = windowSearchID(menuID);
        if (window != 0) {
            *cursor = window->top + window->cursor;
        } else {
            *cursor = 0;
        }
        if (selected == -1) {
            if (depth == 0) {
                result = -1;
            }
            break;
        }
        item = _dbgMenuGetItemNo(window, window->top + window->cursor);
        link = _dbgMenuGetLink(item);
        if (link != 0) {
            func = dbgMenuGetFunc(item);
            if (func != 0) {
                selected = func(item, window->top + window->cursor);
            } else {
                selected = 1;
            }
            if (selected == 0) {
                menuClose(_menu_data_number + 1);
                return 1;
            }
            if (selected != -1 && link != 1 && _dbgMenuSub(depth + 1) == 1) {
                return 1;
            }
            continue;
        }
        menuClose(_menu_data_number + 1);
        func = dbgMenuGetFunc(item);
        if (func != 0) {
            func(item, window->top + window->cursor);
        }
        return 1;
    }
    menuClose(menuID);
    return result;
}

static s32 _dbgMenuGetMenuNum(tagWINDOW_WORK* window, s32* width) {
    s32 i;
    u32 w;
    s32 msg;

    if (width != 0) {
        *width = 0;
    }
    i = 0;
    do {
        msg = _dbgMenuGetMsgID(window, i);
        if (width != 0) {
            w = GSmsgGetRect(msg) >> 16;
            if (*width < (s32)w) {
                *width = w;
            }
        }
    } while (_dbgMenuCheckTerminate(window, i++) == 0);
    return i;
}

static s32 _dbgMenuCheckTerminate(tagWINDOW_WORK* window, s32 index) {
    DbgMenuData* data;
    u8 result;

    data = dbgMenuGetPtr(_dbgMenuGetItemNo(window, index));
    if (data == 0) {
        result = 1;
    } else {
        result = data->end != 0;
    }
    return result;
}

static s32 _dbgMenuGetMenuNo(s32 depth) {
    tagWINDOW_WORK* window;
    s32 item;
    s16 link;
    s32 i;
    s32 count;
    DbgMenuData* data;
    u8 end;

    window = windowSearchID(depth);
    if (window != 0) {
        item = _dbgMenuGetItemNo(window, window->top + window->cursor);
        link = _dbgMenuGetLink(item);
        count = 0;
        for (i = 0; i < link; i++) {
            data = dbgMenuGetPtr(i);
            if (data == 0) {
                end = 1;
            } else {
                end = data->end != 0;
            }
            if (end) {
                count++;
            }
        }
    } else {
        count = 0;
        for (i = 0; i < dbgMenuGetRootMenu(); i++) {
            data = dbgMenuGetPtr(i);
            if (data == 0) {
                end = 1;
            } else {
                end = data->end != 0;
            }
            if (end) {
                count++;
            }
        }
    }
    return count;
}

static s32 _dbgMenuGetMsgID(tagWINDOW_WORK* window, s32 index) {
    DbgMenuData* data;

    data = dbgMenuGetPtr(_dbgMenuGetItemNo(window, index));
    if (data == 0) {
        return 0;
    }
    return data->msgID;
}

static s32 _dbgMenuGetItemNo(tagWINDOW_WORK* window, s32 index) {
    int depth;
    s32 base;
    s32 item;
    tagWINDOW_WORK* parent;

    depth = _dbgMenuGetIndex(window);
    if (depth < 0) {
        return 0;
    }
    if (depth == 0) {
        base = dbgMenuGetRootMenu();
    } else {
        parent = _dbgMenuGetWin(depth - 1);
        if (parent == 0) {
            item = dbgMenuGetRootMenu();
        } else {
            item = _dbgMenuGetItemNo(parent, parent->top + parent->cursor);
        }
        base = _dbgMenuGetLink(item);
    }
    return base + index;
}
