#include <dolphin/types.h>

typedef void (*GSgappFunc)(int id, void* arg);

enum {
    GAPP_TYPE_FREE,
    GAPP_TYPE_NORMAL,
    GAPP_TYPE_BACKGROUND,
    GAPP_TYPE_VSYNC,
};

// A "game application" job: a callback run every frame, in the background or on vsync.
struct Gapp {
    Gapp* prev;
    Gapp* next;
    s32 type;
    s32 pauseLevel;
    u8 priority;
    u8 blocked;
    u8 unk12[2];
    char name[32];
    void* arg;
    GSgappFunc func;
};

extern "C" {

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void* GSmemAlloc(u32 size);
void* memcpy(void* dst, const void* src, unsigned long n);
void OSSetIdleFunction(void (*func)(void*), void* param, void* stack, u32 stackSize);
void GSgfxVideoSetVSyncCallback(void (*func)(void));

void gappBackgroundCallback(void);
void gappVSyncCallback(void);

static Gapp* _gappStructList;
static u32 _gappMaxJobs;
static u32 _gappMaxBkgndJobs;
static u32 _gappTotalJobs;
static bool _gappPause;
static void* _gappBkgndStackPtr;
static Gapp* _gappCurrentGapp;
static Gapp* _gappListTop;
static Gapp* _gappCreateBGJobRequestListTop;

#define GAPP_ID(g) (((u32)(g) - (u32)_gappStructList) / sizeof(Gapp) + 1)

static inline void _gappRun(s32 type) {
    Gapp* gapp;
    Gapp* next;
    for (gapp = _gappListTop; gapp != NULL; gapp = next) {
        next = gapp->next;
        if (gapp->type == type && !gapp->blocked && (!_gappPause || gapp->pauseLevel == 0)) {
            _gappCurrentGapp = gapp;
            gapp->func(GAPP_ID(gapp), gapp->arg);
        }
    }
    _gappCurrentGapp = NULL;
}

// Inserts into the run list, sorted by priority.
static inline void _gappInsert(Gapp* gapp) {
    Gapp* next;
    Gapp* pos = _gappListTop;
    while ((next = pos->next) != NULL && pos->priority < gapp->priority) {
        pos = next;
    }
    if (next == NULL && pos->priority < gapp->priority) {
        gapp->prev = pos;
        gapp->next = NULL;
        pos->next = gapp;
    } else {
        if (pos->prev != NULL) {
            pos->prev->next = gapp;
        }
        gapp->prev = pos->prev;
        gapp->next = pos;
        pos->prev = gapp;
        if (_gappListTop == pos) {
            _gappListTop = gapp;
        }
    }
}

static inline Gapp* _gappFindFree(s32 type) {
    Gapp* gapp;
    u32 num;
    if (type == GAPP_TYPE_BACKGROUND) {
        gapp = &_gappStructList[_gappMaxJobs];
        num = _gappMaxBkgndJobs;
    } else {
        gapp = _gappStructList;
        num = _gappMaxJobs;
    }
    for (; num != 0; num--, gapp++) {
        if (gapp->type == GAPP_TYPE_FREE) {
            return gapp;
        }
    }
    return NULL;
}

void GSgappSetName(int id, const char* name) {
    if (name != NULL) {
        Gapp* gapp = &_gappStructList[id - 1];
        memcpy(gapp->name, name, sizeof(gapp->name) - 1);
        gapp->name[sizeof(gapp->name) - 1] = '\0';
    }
}

void GSgappUnblock(int id) {
    Gapp* gapp = &_gappStructList[id - 1];
    gapp->blocked = false;
}

void GSgappSetPauseLevel(int id, s32 level) {
    Gapp* gapp = &_gappStructList[id - 1];
    gapp->pauseLevel = level;
}

void GSgappPauseOff(void) {
    _gappPause = false;
}

void GSgappPauseOn(void) {
    _gappPause = true;
}

void GSgappBlock(int id) {
    Gapp* gapp = &_gappStructList[id - 1];
    gapp->blocked = true;
}

void GSgappTerminate(int id) {
    Gapp* gapp = &_gappStructList[id - 1];
    BOOL intr = OSDisableInterrupts();
    if (gapp->prev != NULL) {
        gapp->prev->next = gapp->next;
    }
    if (gapp->next != NULL) {
        gapp->next->prev = gapp->prev;
    }
    if (_gappListTop == gapp) {
        _gappListTop = gapp->next;
    }
    gapp->prev = NULL;
    gapp->next = NULL;
    OSRestoreInterrupts(intr);
    gapp->type = GAPP_TYPE_FREE;
}

void GSgappUpdate(void) {
    _gappRun(GAPP_TYPE_NORMAL);
}

int GSgappCreate(s32 type, u8 priority, void* arg, GSgappFunc func) {
    Gapp* gapp = _gappFindFree(type);
    if (gapp == NULL) {
        return 0;
    }
    gapp->prev = NULL;
    gapp->next = NULL;
    gapp->type = type;
    gapp->priority = priority;
    gapp->blocked = false;
    gapp->arg = arg;
    gapp->func = func;
    gapp->pauseLevel = 0;
    gapp->name[0] = '\0';
    if (_gappListTop == NULL) {
        _gappListTop = gapp;
    } else {
        BOOL intr = OSDisableInterrupts();
        if (gapp->type == GAPP_TYPE_BACKGROUND) {
 // Background jobs are linked in by the idle thread.
            gapp->next = _gappCreateBGJobRequestListTop;
            _gappCreateBGJobRequestListTop = gapp;
        } else {
            _gappInsert(gapp);
        }
        OSRestoreInterrupts(intr);
    }
    return GAPP_ID(gapp);
}

void GSgappInit(u32 maxJobs, u32 maxBkgndJobs) {
    u32 i;
    _gappMaxJobs = maxJobs;
    _gappMaxBkgndJobs = maxBkgndJobs;
    _gappTotalJobs = maxJobs + maxBkgndJobs;
    _gappCurrentGapp = NULL;
    _gappStructList = (Gapp*)GSmemAlloc(_gappTotalJobs * sizeof(Gapp));
    if (_gappStructList != NULL) {
        for (i = 0; i < _gappTotalJobs; i++) {
            _gappStructList[i].type = GAPP_TYPE_FREE;
        }
        _gappBkgndStackPtr = GSmemAlloc(0x2000);
        OSSetIdleFunction((void (*)(void*))gappBackgroundCallback, NULL, (u8*)_gappBkgndStackPtr + 0x1FFC, 0x1FFC);
        GSgfxVideoSetVSyncCallback(gappVSyncCallback);
    }
}

void gappBackgroundCallback(void) {
    for (;;) {
        Gapp* gapp;
        Gapp* next;
        BOOL intr;
        _gappRun(GAPP_TYPE_BACKGROUND);
        intr = OSDisableInterrupts();
        for (gapp = _gappCreateBGJobRequestListTop; gapp != NULL; gapp = next) {
            next = gapp->next;
            _gappInsert(gapp);
        }
        _gappCreateBGJobRequestListTop = NULL;
        OSRestoreInterrupts(intr);
    }
}

void gappVSyncCallback(void) {
    _gappRun(GAPP_TYPE_VSYNC);
}

}
