// Compiled as C with deferred inlining (see configure.py): functions come out in reverse
// source order, and functions defined later can be inlined into earlier ones.
#include <dolphin/types.h>
#include <libc/stdarg.h>

#pragma pool_strings off

typedef s32 OSHeapHandle;

void OSReport(const char* msg, ...);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void OSSetArenaLo(void* addr);
u32 OSGetPhysicalMemSize(void);
OSHeapHandle OSCreateHeap(void* start, void* end);
void OSDestroyHeap(OSHeapHandle heap);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);
s32 OSCheckHeap(OSHeapHandle heap);
void __assert(const char* file, s32 line, const char* expr);


typedef struct HSD_ObjAllocData {
    u8 flags;
    u8 unk1[7];
    u32 used;
    u32 free;
    u32 peak;
} HSD_ObjAllocData;

typedef struct HSD_MemoryCallbacks {
    void* (*alloc)(u32 size);
    void (*free)(void* ptr);
    void (*clear)(void);
    s32 (*remain)(void);
    s32 (*check_own)(void* ptr);
} HSD_MemoryCallbacks;

typedef struct HSD_MemReport {
    u32 total;
    u32 system;
    u32 xfb;
    u32 audio;
    u32 heap;
} HSD_MemReport;

typedef enum HSD_InitParam {
    HSD_INIT_HEAP_SIZE,
    HSD_INIT_ARENA,
    HSD_INIT_MEMORY_CALLBACKS,
} HSD_InitParam;

void _HSD_MemSetCallbacks(HSD_MemoryCallbacks* cb, u32 size);
void HSD_ObjSetHeap(u32 size, void* ptr);
void HSD_StateInvalidate(s32 state);
void HSD_IDSetup(void);
void hsdForgetClassLibrary(const char* name);
void HSD_ListInitAllocData(void);
void HSD_AObjInitAllocData(void);
void HSD_FObjInitAllocData(void);
void HSD_IDInitAllocData(void);
void HSD_VecInitAllocData(void);
void HSD_MtxInitAllocData(void);
void HSD_RObjInitAllocData(void);
void HSD_RenderInitAllocData(void);
void HSD_ShadowInitAllocData(void);
void _HSD_AObjForgetMemory(void* lo, void* hi);
void _HSD_DispForgetMemory(void* lo, void* hi);
void _HSD_IDForgetMemory(void* lo, void* hi);
void _HSD_ObjAllocForgetMemory(void* lo, void* hi);
void _HSD_RandForgetMemory(void* lo, void* hi);
void _HSD_RObjForgetMemory(void* lo, void* hi);
HSD_ObjAllocData* HSD_AObjGetAllocData(void);
HSD_ObjAllocData* HSD_FObjGetAllocData(void);
HSD_ObjAllocData* HSD_IDGetAllocData(void);
HSD_ObjAllocData* HSD_SListGetAllocData(void);
HSD_ObjAllocData* HSD_DListGetAllocData(void);
HSD_ObjAllocData* HSD_VecGetAllocData(void);
HSD_ObjAllocData* HSD_MtxGetAllocData(void);
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);
HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
HSD_ObjAllocData* HSD_RenderGetAllocData(void);
HSD_ObjAllocData* HSD_ChanGetAllocData(void);
HSD_ObjAllocData* HSD_TevRegGetAllocData(void);

void HSD_OSInit(void);
static inline void HSD_ObjInit(void);
static void* _HSD_MemAllocDefaultCB(u32 size);
static void _HSD_MemFreeDefaultCB(void* ptr);
static s32 _HSD_MemGetRemainDefaultCB(void);
static void _HSD_MemClearDefaultCB(void);
static s32 _HSD_MemCheckOwnDefaultCB(void* ptr);

static HSD_MemReport memReport;
static OSHeapHandle hsd_heap = -1;

// Declared in reverse: this file's data comes out in reverse source order.
static s32 shown;
static s32 iparam_memory_callbacks;
static s32 iparam_heap_size;
static s32 init_done;
static void* hsd_heap_next_arena_hi;
static void* hsd_heap_next_arena_lo;
static void* hsd_heap_arena_hi;
static void* hsd_heap_arena_lo;

#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

void HSD_Init(void) {
    HSD_OSInit();
    HSD_StateInvalidate(-1);
    HSD_IDSetup();
    HSD_ObjInit();
    init_done = TRUE;
}

static inline void _HSD_CreateHeap(void);

void HSD_OSInit(void) {
    u32 arenaLo;
    u32 arenaHi;

    arenaLo = (u32)OSGetArenaLo();
    arenaHi = (u32)OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (u32)OSGetArenaHi() + (u32)OSGetArenaLo() - memReport.xfb - memReport.audio;

    if (!iparam_memory_callbacks) {
        HSD_MemoryCallbacks cb;
        cb.alloc = _HSD_MemAllocDefaultCB;
        cb.free = _HSD_MemFreeDefaultCB;
        cb.remain = _HSD_MemGetRemainDefaultCB;
        cb.clear = _HSD_MemClearDefaultCB;
        cb.check_own = _HSD_MemCheckOwnDefaultCB;
        _HSD_MemSetCallbacks(&cb, sizeof(cb));

        if (hsd_heap_next_arena_lo != NULL && hsd_heap_next_arena_hi != NULL) {
            hsd_heap_arena_lo = hsd_heap_next_arena_lo;
            hsd_heap_arena_hi = hsd_heap_next_arena_hi;
            hsd_heap_next_arena_lo = NULL;
            hsd_heap_next_arena_hi = NULL;
            hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
            OSSetCurrentHeap(hsd_heap);
            memReport.heap = (u32)hsd_heap_arena_hi - (u32)hsd_heap_arena_lo;
            HSD_ObjSetHeap(memReport.heap, NULL);
        } else {
            u32 lo = OSRoundUp32B(OSGetArenaLo());
            u32 hi = (u32)OSGetArenaHi();
            hsd_heap_arena_lo = (void*)lo;
            if (iparam_heap_size > 0) {
                hsd_heap_arena_hi = (void*)(lo + iparam_heap_size);
                if ((u32)hsd_heap_arena_hi > hi) {
                    hsd_heap_arena_hi = (void*)hi;
                }
                hsd_heap_arena_hi = (void*)OSRoundDown32B(hsd_heap_arena_hi);
            } else {
                hsd_heap_arena_hi = (void*)OSRoundDown32B(hi);
            }
            _HSD_CreateHeap();
            OSSetArenaLo(hsd_heap_arena_hi);
        }
    }
}

static inline void _HSD_CreateHeap(void) {
    hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(hsd_heap);
    memReport.heap = (u32)hsd_heap_arena_hi - (u32)hsd_heap_arena_lo;
    HSD_ObjSetHeap(memReport.heap, NULL);
}

// Not called in XD (removed by the linker); only its message string is left in the game.
void HSD_InitReportMissingArgument(void) {
    OSReport("missing argument.\n");
}

static inline void _HSD_MemCheckDefault(void);

static void* _HSD_MemAllocDefaultCB(u32 size) {
    void* addr;
    if (size == 0) {
        return NULL;
    }
    _HSD_MemCheckDefault();
    addr = OSAllocFromHeap(hsd_heap, size);
    if (addr == NULL) {
        __assert("initialize.c", 206, "addr");
    }
    return addr;
}

static void _HSD_MemFreeDefaultCB(void* ptr) {
    _HSD_MemCheckDefault();
    OSFreeToHeap(hsd_heap, ptr);
}

static s32 _HSD_MemGetRemainDefaultCB(void) {
    _HSD_MemCheckDefault();
    return OSCheckHeap(hsd_heap);
}

static void _HSD_MemClearDefaultCB(void) {
    OSDestroyHeap(hsd_heap);
    if (hsd_heap_next_arena_lo != NULL && hsd_heap_next_arena_hi != NULL) {
        hsd_heap_arena_lo = hsd_heap_next_arena_lo;
        hsd_heap_arena_hi = hsd_heap_next_arena_hi;
        hsd_heap_next_arena_lo = NULL;
        hsd_heap_next_arena_hi = NULL;
    }
    hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(hsd_heap);
}

static s32 _HSD_MemCheckOwnDefaultCB(void* ptr) {
    s32 own = FALSE;
    if (hsd_heap_arena_lo <= ptr && ptr < hsd_heap_arena_hi) {
        own = TRUE;
    }
    return own;
}

// The default heap callbacks may only be used when the game didn't install its own.
static inline void _HSD_MemCheckDefault(void) {
    if (iparam_memory_callbacks) {
        __assert("initialize.c", 255, "!iparam_memory_callbacks");
    }
}

// Not called in XD (removed by the linker); its table is still in the game's data.
OSHeapHandle HSD_CreateMainHeap(void* lo, void* hi) {
    s32 i;
    void (*cb_table[])(void* lo, void* hi) = {
        _HSD_AObjForgetMemory, _HSD_DispForgetMemory, _HSD_IDForgetMemory, _HSD_ObjAllocForgetMemory,
        _HSD_RandForgetMemory, _HSD_RObjForgetMemory, NULL,
    };
    hsdForgetClassLibrary("sysdolphin_base_library");
    HSD_ObjInit();
    for (i = 0; cb_table[i] != NULL; i++) {
        cb_table[i](hsd_heap_next_arena_lo, hsd_heap_next_arena_hi);
    }
    if (lo != NULL) {
        hsd_heap_next_arena_lo = lo;
    }
    if (hi != NULL) {
        hsd_heap_next_arena_hi = hi;
    }
    OSDestroyHeap(hsd_heap);
    hsd_heap = OSCreateHeap(hsd_heap_next_arena_lo, hsd_heap_next_arena_hi);
    OSSetCurrentHeap(hsd_heap);
    HSD_ObjSetHeap((u32)hsd_heap_next_arena_hi - (u32)hsd_heap_next_arena_lo, NULL);
    return hsd_heap;
}

static inline void HSD_ObjInit(void) {
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
}

static inline u32 HSD_ObjAllocGetUsing(HSD_ObjAllocData* data) {
    if (data == NULL) {
        __assert("objalloc.h", 205, "data");
    }
    return data->used;
}

static inline u32 HSD_ObjAllocGetFreed(HSD_ObjAllocData* data) {
    if (data == NULL) {
        __assert("objalloc.h", 221, "data");
    }
    return data->free;
}

static inline u32 HSD_ObjAllocGetPeak(HSD_ObjAllocData* data) {
    if (data == NULL) {
        __assert("objalloc.h", 237, "data");
    }
    return data->peak;
}

typedef struct HSD_ObjDumpStat_types {
    HSD_ObjAllocData* (*func)(void);
    char* label;
} HSD_ObjDumpStat_types;

// Not called in XD (removed by the linker); its table is still in the game's data.
void HSD_ObjDumpStat(void) {
    HSD_ObjDumpStat_types types[] = {
        {HSD_AObjGetAllocData, "aobj"},     {HSD_FObjGetAllocData, "fobj"},
        {HSD_IDGetAllocData, "id"},         {HSD_SListGetAllocData, "slist"},
        {HSD_DListGetAllocData, "dlist"},   {HSD_VecGetAllocData, "vec"},
        {HSD_MtxGetAllocData, "mtx"},       {HSD_RObjGetAllocData, "robj"},
        {HSD_RvalueObjGetAllocData, "rval"}, {HSD_ShadowGetAllocData, "shadow"},
        {HSD_RenderGetAllocData, "render"}, {HSD_ChanGetAllocData, "chan"},
        {HSD_TevRegGetAllocData, "tevreg"}, {NULL, NULL},
    };
    s32 i;

    for (i = 0; types[i].label != NULL; i++) {
        OSReport("objalloc: %s\tusing %d\tfreed %d\tpeak %d\n", types[i].label,
                 HSD_ObjAllocGetUsing(types[i].func()), HSD_ObjAllocGetFreed(types[i].func()),
                 HSD_ObjAllocGetPeak(types[i].func()));
    }
}

s32 HSD_SetInitParameter(HSD_InitParam param, ...) {
    va_list ap;
    s32 ok = FALSE;

    if (init_done) {
        if (!shown) {
            OSReport("init parameter should be set before invoking HSD_Init().\n");
            shown = TRUE;
        }
        return FALSE;
    }

    va_start(ap, param);
    switch (param) {
    case HSD_INIT_HEAP_SIZE: {
        u32 size = va_arg(ap, u32);
        if (size < OSGetPhysicalMemSize()) {
            iparam_heap_size = size;
            ok = TRUE;
        }
        break;
    }
    case HSD_INIT_ARENA: {
        void* lo = va_arg(ap, void*);
        void* hi = va_arg(ap, void*);
        ok = TRUE;
        hsd_heap_next_arena_lo = lo;
        hsd_heap_next_arena_hi = hi;
        break;
    }
    case HSD_INIT_MEMORY_CALLBACKS: {
        HSD_MemoryCallbacks cb;
        cb.alloc = va_arg(ap, void*);
        cb.free = va_arg(ap, void*);
        cb.clear = va_arg(ap, void*);
        cb.remain = va_arg(ap, void*);
        cb.check_own = va_arg(ap, void*);
        if (va_arg(ap, void*) != NULL) {
            OSReport("ERROR in HSD_SetInitParameter():\n");
            OSReport("  HSD_INIT_MEMORY_CALLBACKS was given invalid arguments.\n");
        } else {
            _HSD_MemSetCallbacks(&cb, sizeof(cb));
            iparam_memory_callbacks = TRUE;
            ok = TRUE;
        }
        break;
    }
    }
    return ok;
}
