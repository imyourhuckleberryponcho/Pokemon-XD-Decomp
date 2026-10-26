


#define HSD_FILE_NAME "aobj.c"

#include <sysdolphin/baselib/aobj.h>

#include <math.h>
#include <stdarg.h>
#include <string.h>

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/robj.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/wobj.h>

#pragma pool_strings off


static HSD_ObjAllocData alloc_data;


static s32 nb_deadanim;
static s32 nb_activeanim;
static HSD_SList* endcallback_list;

inline void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj);
inline void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc func);
static inline f32 getLoopedFrame(HSD_AObj* aobj);
double fmod(double x, double y);


void* GSmemGetSysdolAllocator(s32 size);
s32 GSmemGetFreePool(void* pool);
void* GSmemAllocPool(void* pool);
u8 GSmemIsRegistrationPool(void* pool, void* ptr);
void GSmemFreePool(void* pool, void* ptr);

inline HSD_AObj* HSD_AObjAlloc(void);
inline void HSD_AObjFree(HSD_AObj* aobj);
inline static void callbackForeachFunc(HSD_AObj* aobj, void* obj, HSD_Type type, void* func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void FogForeachAnim(HSD_Fog* fog, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void TObjForeachAnim(HSD_TObj* tobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void RObjForeachAnim(HSD_RObj* robj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void WObjForeachAnim(HSD_WObj* wobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void PObjForeachAnim(HSD_PObj* pobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline static void MObjForeachAnim(HSD_MObj* mobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
inline void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame);
inline void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame);
void HSD_AObjInitAllocData(void);
HSD_ObjAllocData* HSD_AObjGetAllocData(void);
u32 HSD_AObjGetFlags(HSD_AObj* aobj);
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjInitEndCallBack(void);
void HSD_AObjInvokeCallBacks(void);
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame);
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc update_func);
HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc);
void HSD_AObjRemove(HSD_AObj* aobj);
static void CObjForeachAnim(HSD_CObj* cobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
static void LObjForeachAnim(HSD_LObj* lobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
static void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
static void JObjForeachAnim(HSD_JObj* obj, HSD_TypeMask mask, Event func, AObj_Arg_Type arg_type, callbackArg* arg);
void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func, AObj_Arg_Type arg_type, ...);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
void _HSD_AObjForgetMemory(void* low, void* high);

inline void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (!aobj) {
        return;
    }

    if (aobj->fobj) {
        HSD_FObjRemoveAll(aobj->fobj);
    }
    aobj->fobj = fobj;
}

inline void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc func)
{
    if (!aobj) {
        return;
    }

    HSD_FObjStopAnimAll(aobj->fobj, obj, func, aobj->framerate);
    aobj->flags |= AOBJ_NO_ANIM;
}

static inline f32 getLoopedFrame(HSD_AObj* aobj)
{

    return aobj->rewind_frame + fmod(aobj->curr_frame - aobj->rewind_frame,
                                     aobj->end_frame - aobj->rewind_frame);
}


inline HSD_AObj* HSD_AObjAlloc(void)
{
    HSD_AObj* new;
    void* pool = GSmemGetSysdolAllocator(sizeof(HSD_AObj));
    if (pool != NULL && GSmemGetFreePool(pool) != 0) {
        new = GSmemAllocPool(pool);
        HSD_ASSERT(502, new);
        return new;
    }
    new = HSD_ObjAlloc(HSD_AObjGetAllocData());
    HSD_ASSERT(509, new);

    memset(new, 0, sizeof(HSD_AObj));
    new->flags = AOBJ_NO_ANIM;
    new->framerate = 1.0F;
    return new;
}

inline void HSD_AObjFree(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    {
        void* pool = GSmemGetSysdolAllocator(sizeof(HSD_AObj));
        if (pool != NULL && GSmemIsRegistrationPool(pool, aobj)) {
            GSmemFreePool(pool, aobj);
        } else {
            HSD_ObjFree(HSD_AObjGetAllocData(), aobj);
        }
    }
}

inline static void callbackForeachFunc(HSD_AObj* aobj, void* obj, HSD_Type type,
                                void* func, AObj_Arg_Type arg_type,
                                callbackArg* arg)
{
    switch (arg_type) {
    case AOBJ_ARG_A:
        (*(void (*)(HSD_AObj*)) func)(aobj);
        return;
    case AOBJ_ARG_AF:
        (*(void (*)(HSD_AObj*, f32)) func)(aobj, arg->f);
        return;
    case AOBJ_ARG_AV:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, arg->v);
        return;
    case AOBJ_ARG_AU:
        (*(void (*)(HSD_AObj*, u32)) func)(aobj, arg->d);
        return;
    case AOBJ_ARG_AO:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, obj);
        return;
    case AOBJ_ARG_AOT:
        (*(void (*)(HSD_AObj*, void*, HSD_Type)) func)(aobj, obj, type);
        return;
    case AOBJ_ARG_AOF:
        (*(void (*)(HSD_AObj*, void*, f32)) func)(aobj, obj, arg->f);
        return;
    case AOBJ_ARG_AOV:
        (*(void (*)(HSD_AObj*, void*, void*)) func)(aobj, obj, arg->v);
        return;
    case AOBJ_ARG_AOU:
        (*(void (*)(HSD_AObj*, void*, u32)) func)(aobj, obj, arg->d);
        return;
    case AOBJ_ARG_AOTF:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, f32)) func)(aobj, obj, type,
                                                            arg->f);
        return;
    case AOBJ_ARG_AOTV:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, void*)) func)(aobj, obj, type,
                                                              arg->v);
        return;
    case AOBJ_ARG_AOTU:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, u32)) func)(aobj, obj, type,
                                                            arg->d);
        return;
    }
}

inline static void FogForeachAnim(HSD_Fog* fog, HSD_TypeMask mask, Event func,
                           AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mask & FOG_MASK && fog != NULL && fog->aobj != NULL) {
        callbackForeachFunc(fog->aobj, fog, FOG_TYPE, func, arg_type, arg);
    }
}

inline static void TObjForeachAnim(HSD_TObj* tobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; tobj != NULL; tobj = tobj->next) {
        if (mask & TOBJ_MASK && tobj->aobj != NULL) {
            callbackForeachFunc(tobj->aobj, tobj, TOBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

inline static void RObjForeachAnim(HSD_RObj* robj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; robj != NULL; robj = robj->next) {
        if (mask & ROBJ_MASK && robj->aobj != NULL) {
            callbackForeachFunc(robj->aobj, robj, ROBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

inline static void WObjForeachAnim(HSD_WObj* wobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (wobj == NULL) {
        return;
    }

    if (mask & WOBJ_MASK && wobj->aobj != NULL) {
        callbackForeachFunc(wobj->aobj, wobj, WOBJ_TYPE, func, arg_type, arg);
    }
    RObjForeachAnim(wobj->robj, mask, func, arg_type, arg);
}

inline static void PObjForeachAnim(HSD_PObj* pobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; pobj != NULL; pobj = pobj->next) {
        if (mask & POBJ_MASK && pobj->aobj != NULL) {
            callbackForeachFunc(pobj->aobj, pobj, POBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

inline static void MObjForeachAnim(HSD_MObj* mobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mobj == NULL) {
        return;
    }

    if (mask & MOBJ_MASK && mobj->aobj != NULL) {
        callbackForeachFunc(mobj->aobj, mobj, MOBJ_TYPE, func, arg_type, arg);
    }
    TObjForeachAnim(mobj->tobj, mask, func, arg_type, arg);
}

inline void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj) {
        return;
    }
    aobj->rewind_frame = frame;
}

inline void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj) {
        return;
    }
    aobj->end_frame = frame;
}

void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&alloc_data, sizeof(HSD_AObj), 4);
}

HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &alloc_data;
}

u32 HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return aobj ? aobj->flags : 0;
}

void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE | 0x10000);
        aobj->flags |= flags;
    }
}

void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE | 0x10000);
        aobj->flags &= ~flags;
    }
}

void HSD_AObjInitEndCallBack(void)
{
    nb_deadanim = 0;
    nb_activeanim = 0;
}

void HSD_AObjInvokeCallBacks(void)
{
    HSD_SList* list;

    if (nb_deadanim != 0 && nb_activeanim == 0) {
        list = endcallback_list;
        while (list) {
            void (*func)(void) = list->data;
            (*func)();
            list = list->next;
        }
    }
}

void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    u32 flags;

    if (!aobj) {
        return;
    }

    aobj->curr_frame = frame;

    flags = aobj->flags & ~AOBJ_NO_ANIM;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}

void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func)
{
    f32 rate = 0;

    if (!aobj || aobj->flags & AOBJ_NO_ANIM) {
        return;
    }

    if (aobj->flags & AOBJ_FIRST_PLAY) {
        aobj->flags &= 0xF7FFFFFF;
        rate = 0.0F;
    } else {
        rate = aobj->framerate;
        aobj->curr_frame += aobj->framerate;
    }

    if ((aobj->flags & AOBJ_LOOP) && aobj->end_frame <= aobj->curr_frame) {
        if (aobj->rewind_frame < aobj->end_frame) {
            HSD_FObjStopAnimAll(aobj->fobj, obj, update_func, rate);
            aobj->curr_frame = getLoopedFrame(aobj);
            HSD_FObjReqAnimAll(aobj->fobj, aobj->curr_frame);
        } else {
            aobj->curr_frame = aobj->end_frame;
        }
        rate = 0.0F;
        aobj->flags |= AOBJ_REWINDED;
    } else {
        aobj->flags &= 0xFBFFFFFF;
    }

    if (aobj->flags & AOBJ_NO_UPDATE) {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, NULL, rate);
    } else {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, update_func, rate);
    }


    if (aobj->flags & AOBJ_NO_ANIM) {
        nb_deadanim += 1;
    } else {
        nb_activeanim += 1;
    }
}

HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc)
{
    HSD_FObjDesc* fobjdesc;
    HSD_AObj* aobj;

    u8 _[4];

    HSD_FObj* fobj;
    HSD_IDKey id;
    HSD_Obj* phi_r30;

    if (aobjdesc != NULL) {
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, aobjdesc->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, aobjdesc->end_frame);
        fobjdesc = aobjdesc->fobjdesc;
        fobj = HSD_FObjLoadDesc(fobjdesc);
        HSD_AObjSetFObj(aobj, fobj);
        id = (HSD_IDKey) aobjdesc->obj_id;
        if (id != 0U) {
            phi_r30 = HSD_IDGetDataFromTable(0, id, 0);
            if (phi_r30 != NULL) {
                ref_INC(phi_r30);
            } else {
                phi_r30 = (HSD_Obj*) HSD_JObjLoadJoint(
                    (HSD_Joint*) aobjdesc->obj_id);
            }
            if (aobj != NULL) {
                if (aobj->hsd_obj != NULL) {
                    HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
                }
                aobj->hsd_obj = phi_r30;
            }
        }
        return aobj;
    }
    return NULL;
}

void HSD_AObjRemove(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    if (aobj) {
        if (aobj->fobj) {
            HSD_FObjRemoveAll(aobj->fobj);
        }
        aobj->fobj = NULL;
    }

    if (aobj) {
        if (aobj->hsd_obj != NULL) {
            HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
        }
        aobj->hsd_obj = NULL;
    }
    HSD_AObjFree(aobj);
}

static void CObjForeachAnim(HSD_CObj* cobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (cobj == NULL) {
        return;
    }

    if (mask & COBJ_MASK && cobj->aobj != NULL) {
        callbackForeachFunc(cobj->aobj, cobj, COBJ_TYPE, func, arg_type, arg);
    }
    WObjForeachAnim(cobj->eyepos, mask, func, arg_type, arg);
    WObjForeachAnim(cobj->interest, mask, func, arg_type, arg);
}

static void LObjForeachAnim(HSD_LObj* lobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; lobj != NULL; lobj = lobj->next) {
        if (mask & LOBJ_MASK && lobj->aobj != NULL) {
            callbackForeachFunc(lobj->aobj, lobj, LOBJ_TYPE, func, arg_type,
                                arg);
        }
        WObjForeachAnim(lobj->position, mask, func, arg_type, arg);
        WObjForeachAnim(lobj->interest, mask, func, arg_type, arg);
    }
}

static void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; dobj != NULL; dobj = dobj->next) {
        if (mask & DOBJ_MASK && dobj->aobj != NULL) {
            callbackForeachFunc(dobj->aobj, dobj, DOBJ_TYPE, func, arg_type,
                                arg);
        }
        MObjForeachAnim(dobj->mobj, mask, func, arg_type, arg);
        PObjForeachAnim(dobj->pobj, mask, func, arg_type, arg);
    }
}

static void JObjForeachAnim(HSD_JObj* obj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    HSD_ASSERT(747, obj);

    if (mask & JOBJ_MASK && obj->aobj != NULL) {
        callbackForeachFunc(obj->aobj, obj, JOBJ_TYPE, func, arg_type, arg);
    }
    if (union_type_dobj(obj)) {
        DObjForeachAnim(obj->u.dobj, mask, func, arg_type, arg);
    }
    RObjForeachAnim(obj->robj, mask, func, arg_type, arg);
    if (!(obj->flags & JOBJ_INSTANCE)) {
        for (obj = obj->child; obj != NULL; obj = obj->next) {
            JObjForeachAnim(obj, mask, func, arg_type, arg);
        }
    }
}

void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func,
                     AObj_Arg_Type arg_type, ...)
{
    va_list ap;
    callbackArg arg;

    if (obj == NULL) {
        return;
    }

    va_start(ap, arg_type);
    switch (arg_type) {
    case AOBJ_ARG_A:
    case AOBJ_ARG_AO:
    case AOBJ_ARG_AOT:
        break;
    case AOBJ_ARG_AF:
    case AOBJ_ARG_AOF:
    case AOBJ_ARG_AOTF:
        arg.f = va_arg(ap, f64);
        break;
    case AOBJ_ARG_AV:
    case AOBJ_ARG_AOV:
    case AOBJ_ARG_AOTV:
        arg.v = va_arg(ap, void*);
        break;
    case AOBJ_ARG_AU:
    case AOBJ_ARG_AOU:
    case AOBJ_ARG_AOTU:
        arg.d = va_arg(ap, u32);
        break;
    default:
        HSD_Panic(HSD_FILE_NAME, 858, "unexpected argument format.\n");
        break;
    }

    switch (type) {
    case JOBJ_TYPE:
        JObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case DOBJ_TYPE:
        DObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case MOBJ_TYPE:
        MObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case POBJ_TYPE:
        PObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case TOBJ_TYPE:
        TObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case LOBJ_TYPE:
        LObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case COBJ_TYPE:
        CObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case ROBJ_TYPE:
        RObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case WOBJ_TYPE:
        WObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case FOG_TYPE:
        FogForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    default:
        HSD_Panic(HSD_FILE_NAME, 894, "unexpected type of object.\n");
        break;
    }
    va_end(ap);
}

void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate)
{
    if (!aobj) {
        return;
    }
    aobj->framerate = rate;
}

void _HSD_AObjForgetMemory(void* low, void* high)
{
    endcallback_list = NULL;
}
