#ifndef _HSD_CLASS_H
#define _HSD_CLASS_H

// HSD (HAL sysdolphin) class system, shared by the baselib object files.
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#define HSD_CLASS(o) ((HSD_Class*)(o))
#define HSD_CLASS_INFO(i) ((HSD_ClassInfo*)(i))
#define HSD_CLASS_METHOD(o) (HSD_CLASS(o)->class_info)
#define HSD_PARENT_INFO(i) (HSD_CLASS_INFO(i)->head.parent)

extern HSD_ClassInfo hsdClass;

void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info, char* base_class_library, char* type,
                      s32 info_size, s32 class_size);
HSD_ClassInfo* hsdSearchClassInfo(char* class_name);
void* hsdNew(HSD_ClassInfo* info);
s32 hsdIsDescendantOf(HSD_ClassInfo* info, HSD_ClassInfo* p);

static inline void hsdDelete(void* o) {
    if (o != NULL) {
        HSD_CLASS_METHOD(o)->release(HSD_CLASS(o));
        HSD_CLASS_METHOD(o)->destroy(HSD_CLASS(o));
    }
}

void __assert(const char* file, s32 line, const char* expr);
void HSD_Panic(const char* file, s32 line, const char* msg);
void OSReport(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif
