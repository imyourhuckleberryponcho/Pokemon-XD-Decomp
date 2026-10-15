#include <dolphin/types.h>

#pragma pool_strings off

extern "C" {

struct HSD_ClassInfo;

struct HSD_ClassInfoHead {
    void (*info_init)(void);
    u32 flags;
    char* library;
    char* class_name;
    s16 obj_size;
    s16 info_size;
    HSD_ClassInfo* parent;
    HSD_ClassInfo* next;
    HSD_ClassInfo* child;
    u32 nb_exist;
    u32 nb_peak;
};

struct HSD_ClassInfo {
    HSD_ClassInfoHead head;
    void* (*alloc)(HSD_ClassInfo* c);
    int (*init)(void* o);
    void (*release)(void* o);
    void (*destroy)(void* o);
    void (*amnesia)(HSD_ClassInfo* c);
};

struct HSD_ObjInfo {
    HSD_ClassInfo parent;
};

struct HSD_Obj {
    void* class_parent;
    u16 ref_count;
    u16 ref_count_individual;
};

extern HSD_ClassInfo hsdClass;
void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info, const char* base_class_library,
                      const char* type, s32 info_size, s32 class_size);

static void ObjInfoInit(void);

HSD_ObjInfo hsdObj = { { { ObjInfoInit } } };

static void ObjInfoInit(void) {
    hsdInitClassInfo(&hsdObj.parent, &hsdClass, "sysdolphin_base_library", "hsd_obj", sizeof(HSD_ObjInfo),
                     sizeof(HSD_Obj));
}

}
