


#include <dolphin/types.h>

#pragma pool_strings off

void __assert(const char* file, s32 line, const char* expr);
void* HSD_Alloc(u32 size);
void HSD_Free(void* ptr);
void* HSD_HashSearch(void* hash, void* key, s32* found);

struct HSD_Class;
struct HSD_ClassInfo;

typedef struct HSD_ClassInfoHead {
    void (*info_init)(void);
    u32 flags;
    char* library;
    char* class_name;
    s16 obj_size;
    s16 info_size;
    struct HSD_ClassInfo* parent;
    struct HSD_ClassInfo* next;
    struct HSD_ClassInfo* child;
    u32 nb_exist;
    u32 nb_peak;
} HSD_ClassInfoHead;

typedef struct HSD_ClassInfo {
    HSD_ClassInfoHead head;
    struct HSD_Class* (*alloc)(struct HSD_ClassInfo* c);
    s32 (*init)(struct HSD_Class* o);
    void (*release)(struct HSD_Class* o);
    void (*destroy)(struct HSD_Class* o);
    void (*amnesia)(struct HSD_ClassInfo* c);
} HSD_ClassInfo;

typedef struct HSD_Class {
    HSD_ClassInfo* class_info;
} HSD_Class;

#define HSD_CLASS_INFO_INIT(info) \
    if (!((info)->head.flags & 1)) { \
        (info)->head.info_init(); \
    }

static void _hsdClassInfoInit(void);

HSD_ClassInfo hsdClass = { { _hsdClassInfoInit } };

static void* info_hash;
static s32 nb_memory_list;
static void* memory_list;

void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info, char* base_class_library,
                      char* type, s32 info_size, s32 class_size) {
    class_info->head.flags = 1;
    class_info->head.library = base_class_library;
    class_info->head.class_name = type;
    class_info->head.obj_size = class_size;
    class_info->head.info_size = info_size;
    class_info->head.parent = parent_info;
    class_info->head.child = NULL;
    class_info->head.next = NULL;
    class_info->head.nb_exist = 0;
    class_info->head.nb_peak = 0;
    if (parent_info != NULL) {
        HSD_CLASS_INFO_INIT(parent_info);
        if (!(class_info->head.obj_size >= parent_info->head.obj_size)) {
            __assert("class.c", 102, "class_info->head.obj_size >= parent_info->head.obj_size");
        }
        if (!(class_info->head.info_size >= parent_info->head.info_size)) {
            __assert("class.c", 103, "class_info->head.info_size >= parent_info->head.info_size");
        }
        memcpy(&class_info->alloc, &parent_info->alloc, parent_info->head.info_size - sizeof(HSD_ClassInfoHead));
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

void* hsdAllocMemPiece(u32 size) { return HSD_Alloc(size); }

void hsdFreeMemPiece(void* mem, u32 size) { HSD_Free(mem); }

static HSD_Class* _hsdClassAlloc(HSD_ClassInfo* info) {
    HSD_Class* obj = (HSD_Class*)HSD_Alloc(info->head.obj_size);
    if (obj != NULL) {
        info->head.nb_exist++;
        if (info->head.nb_exist > info->head.nb_peak) {
            info->head.nb_peak = info->head.nb_exist;
        }
    }
    return obj;
}

static s32 _hsdClassInit(HSD_Class* o) { return 0; }

static void _hsdClassRelease(HSD_Class* o) {}

static void _hsdClassDestroy(HSD_Class* o) {
    o->class_info->head.nb_exist--;
    HSD_Free(o);
}

static void _hsdClassAmnesia(HSD_ClassInfo* info) {
    info->head.nb_exist = 0;
    info->head.nb_peak = 0;
    if (info == &hsdClass) {
        nb_memory_list = 0;
        memory_list = NULL;
        info_hash = NULL;
    }
}

static void _hsdClassInfoInit(void) {
    hsdInitClassInfo(&hsdClass, NULL, "sysdolphin_base_library", "hsd_class", sizeof(HSD_ClassInfo),
                     sizeof(HSD_Class));
    hsdClass.alloc = _hsdClassAlloc;
    hsdClass.init = _hsdClassInit;
    hsdClass.release = _hsdClassRelease;
    hsdClass.destroy = _hsdClassDestroy;
    hsdClass.amnesia = _hsdClassAmnesia;
}

HSD_Class* hsdNew(HSD_ClassInfo* info) {
    HSD_Class* obj;
    HSD_CLASS_INFO_INIT(info);
    obj = info->alloc(info);
    if (obj == NULL) {
        return NULL;
    }
    HSD_CLASS_INFO_INIT(info);
    memset(obj, 0, info->head.obj_size);
    obj->class_info = info;
    if (info->init(obj) < 0) {
        info->destroy(obj);
        return NULL;
    }
    return obj;
}

BOOL hsdIsDescendantOf(HSD_ClassInfo* info, HSD_ClassInfo* p) {
    HSD_ClassInfo* tmp;
    HSD_ClassInfo* c;
    if (info == NULL || p == NULL) {
        return FALSE;
    }
    tmp = c = info;
    HSD_CLASS_INFO_INIT(tmp);
    HSD_CLASS_INFO_INIT(p);
    for (; c != NULL; c = c->head.parent) {
        if (c == p) {
            return TRUE;
        }
    }
    return FALSE;
}

HSD_ClassInfo* hsdSearchClassInfo(char* class_name) {
    if (info_hash != NULL) {
        return (HSD_ClassInfo*)HSD_HashSearch(info_hash, class_name, NULL);
    }
    return NULL;
}
