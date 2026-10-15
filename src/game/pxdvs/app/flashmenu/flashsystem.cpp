// STATUS (rough draft, rd_fs): 15/15 functions, 0 exact, byte-weighted ~74%, default flags, LAYOUT/CONST/CALLS/DATA OK.
// All functions share the inlined flashFind(id) slot search (target: loop index doubles as the result, `if (hit) {} else i++`
// shape with an early-out branch; ours keeps an extra register copy). Fix that one idiom and all 15 should jump.
#include <dolphin/types.h>

extern "C" void GSthreadSwitch();
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;

struct FlashMenu {
    u8 pad0[0x24];
    u8 loopFlag;
    u8 pad25[3];
    u32 loopStart;
    u32 loopEnd;
    u8 pad30[0x110];

    FlashMenu();
    ~FlashMenu();
    void* GetGStexture(long id);
    void Draw(tagWINDOW_WORK* w, tagSPRITE_WORK* s);
    void Update();
    s32 Init(void* d, unsigned long arg);
    void Release();
    u16 GetFrameFromLabel(char* name);
    u32 GetPlayFrame();
    void SetPlayFrame(unsigned long f);
};

struct FlashEntry {
    FlashMenu* menu;
    u32 id;
};

static FlashEntry _flashmenu[10];

// find the slot of an active flash menu by its id
static inline FlashEntry* flashFind(u32 id) {
    int i = 0;
    FlashEntry* e = _flashmenu;
    int c = 0;
    for (; c < 10; c++, e++) {
        if (e->menu != 0 && id == e->id) break;
        i++;
    }
    if (c == 10) i = -1;
    FlashEntry* r;
    if (i >= 0) {
        r = &_flashmenu[i];
        if (r->menu != 0) {
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }
    return r;
}

extern "C" {

void FlashSystemPlayAndWait(u32 id, char* from, char* to) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->loopStart = e->menu->GetFrameFromLabel(from);
        e->menu->loopEnd = e->menu->GetFrameFromLabel(to);
    }
    e = flashFind(id);
    if (e != 0) {
        e->menu->loopFlag = 0;
    }
    e = flashFind(id);
    if (e != 0) {
        e->menu->SetPlayFrame(e->menu->GetFrameFromLabel(from));
    }
    e = flashFind(id);
    u16 target;
    if (e != 0) {
        target = e->menu->GetFrameFromLabel(to);
    } else {
        target = 0;
    }
    u32 now;
    do {
        e = flashFind(id);
        if (e != 0) {
            now = e->menu->GetPlayFrame();
        } else {
            now = 0;
        }
        GSthreadSwitch();
    } while (now < target);
}

s32 FlashSystemIsLastFrame(u32 id) {
    s32 r = 0;
    FlashEntry* e = flashFind(id);
    u8 loop;
    if (e != 0) {
        loop = e->menu->loopFlag;
    } else {
        loop = 0;
    }
    if (loop == 0) {
        e = flashFind(id);
        u32 now;
        if (e != 0) {
            now = e->menu->GetPlayFrame();
        } else {
            now = 0;
        }
        e = flashFind(id);
        u32 end;
        if (e != 0) {
            end = e->menu->loopEnd;
        } else {
            end = 0;
        }
        if (now >= end) r = 1;
    }
    return r;
}

u16 FlashSystemGetFrameFromLabel(u32 id, char* label) {
    FlashEntry* e = flashFind(id);
    if (e != 0) return e->menu->GetFrameFromLabel(label);
    return 0;
}

s32 FlashSystemSetNowFrameLabel(u32 id, char* label) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->SetPlayFrame(e->menu->GetFrameFromLabel(label));
    }
    return 0;
}

s32 FlashSystemSetPlayFrameLabel(u32 id, char* from, char* to) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->loopStart = e->menu->GetFrameFromLabel(from);
        e->menu->loopEnd = e->menu->GetFrameFromLabel(to);
    }
    return 1;
}

void FlashSystemSetLoopFlag(u32 id, s32 loop) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->loopFlag = loop;
    }
}

s32 FlashSystemSetNowFrame(u32 id, u32 frame) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->SetPlayFrame(frame);
    }
    return 0;
}

s32 FlashSystemGetEndFrame(u32 id) {
    FlashEntry* e = flashFind(id);
    if (e != 0) return e->menu->loopEnd;
    return 0;
}

u32 FlashSystemGetNowFrame(u32 id) {
    FlashEntry* e = flashFind(id);
    if (e != 0) return e->menu->GetPlayFrame();
    return 0;
}

s32 FlashSystemGetGStexture(u32 id, long texId) {
    FlashEntry* e = flashFind(id);
    if (e != 0) return (s32)e->menu->GetGStexture(texId);
    return 0;
}

void FlashSystemRelease(u32 id) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->Release();
        delete e->menu;
        e->menu = 0;
        e->id = 0;
    }
}

void FlashSystemDraw(u32 id, tagWINDOW_WORK* w, tagSPRITE_WORK* s) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->Draw(w, s);
    }
}

void FlashSystemPlay(u32 id) {
    FlashEntry* e = flashFind(id);
    if (e != 0) {
        e->menu->Update();
    }
}

s32 FlashSystemInit(u32 id, void* data) {
    int i = 0;
    FlashEntry* e = _flashmenu;
    FlashEntry* slot = 0;
    for (int c = 0; c < 10; c++, e++, i++) {
        if (e->menu == 0) {
            slot = &_flashmenu[i];
            break;
        }
    }
    if (slot != 0) {
        slot->menu = new FlashMenu();
        s32 r = slot->menu->Init(data, id);
        slot->id = id;
        return r;
    }
    return 0;
}

s32 FlashSystemInitAll(void) {
    for (int i = 0; i < 10; i++) {
        _flashmenu[i].menu = 0;
        _flashmenu[i].id = 0;
    }
    return 1;
}

}
