#ifndef _pobj_h_
#define _pobj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dat_macros.h>

#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/list.h>

#define HSD_MTX_RIGID 1
#define HSD_MTX_ENVELOPE 2

struct HSD_PObj {
    HSD_Class parent;
    HSD_PObj* next;
    HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
 /// #u8 primitive, #u16 vtxcnt, #u16* indices
    u8* display;
    union HSD_PObjUnion {
        HSD_JObj* jobj;
        HSD_ShapeSet* shape_set;
        HSD_SList* envelope_list;
    } u;
    HSD_AObj* aobj;
};

/// Envelopes of one vertex matrix, up to one with a null joint.
typedef gc_ptr32(HSD_EnvelopeDesc) HSD_EnvelopeList DAT_TERMINATED(0);

/// GX commands: primitives indexing a shape's vertex arrays, in 32-byte
/// blocks.
typedef u8 HSD_DisplayList DAT_BLOB;

/// One attribute's vertex data, as #GXSetArray takes it: elements of
/// `stride` bytes, which a shape's display lists index.
typedef u8 HSD_VertexArray DAT_BLOB;

struct HSD_PObjDesc {
    gc_ptr32(char) class_name;
    gc_ptr32(HSD_PObjDesc) next;
    gc_ptr32(HSD_VtxDescList) verts DAT_TERMINATED(GX_VA_NULL);
    gc_be16 flags;
    gc_be16 n_display;
 /// As #GXCallDisplayList takes it (#PObjDispSimplePrimitive).
    gc_ptr32(HSD_DisplayList) display DAT_COUNT(n_display << 5);
    union HSD_PObjDesc_u {
        gc_ptr32(HSD_Joint) joint DAT_IF((flags & 0x3000) == POBJ_SKIN);
        gc_ptr32(HSD_ShapeSetDesc) shape_set DAT_IF((flags & 0x3000) == POBJ_SHAPEANIM);
        gc_ptr32(HSD_EnvelopeList) envelope_p DAT_TERMINATED(0)
            DAT_IF((flags & 0x3000) == POBJ_ENVELOPE);
    } u;
};

struct HSD_VtxDescList {
    gc_enum32(GXAttr) attr;
    gc_enum32(GXAttrType) attr_type;
    gc_enum32(GXCompCnt) comp_cnt;
    gc_enum32(GXCompType) comp_type;
    u8 frac;
    gc_be16 stride;
 /// @todo Its length is the largest index the display lists use.
    gc_ptr32(HSD_VertexArray) vertex;
};

struct HSD_Envelope {
    HSD_Envelope* next;
    HSD_JObj* jobj;
    f32 weight;
};

struct HSD_EnvelopeDesc {
    gc_ptr32(HSD_Joint) joint;
    gc_bef32 weight;
};

struct HSD_ShapeSet {
    u16 flags;
    u16 nb_shape;
    int nb_vertex_index;
    HSD_VtxDescList* vertex_desc;
    gc_ptr32(u8)* vertex_idx_list DAT_COUNT(nb_shape);
    s32 nb_normal_index;
    HSD_VtxDescList* normal_desc;
    gc_ptr32(u8)* normal_idx_list DAT_COUNT(nb_shape);
    union HSD_ShapeSet_blend {
        f32* bp;
        f32 bl;
    } blend;
};

struct HSD_ShapeSetDesc {
    gc_be16 flags;
    gc_be16 nb_shape;
    gc_bes32 nb_vertex_index;
    gc_ptr32(HSD_VtxDescList) vertex_desc;
    gc_ptr32(gc_ptr32(u8)) vertex_idx_list DAT_COUNT(nb_shape);
    gc_bes32 nb_normal_index;
    gc_ptr32(HSD_VtxDescList) normal_desc;
    gc_ptr32(gc_ptr32(u8)) normal_idx_list DAT_COUNT(nb_shape);
};

struct HSD_ShapeAnim {
    gc_ptr32(HSD_ShapeAnim) next;
    gc_ptr32(HSD_AObjDesc) aobjdesc;
};

struct HSD_ShapeAnimJoint {
    gc_ptr32(HSD_ShapeAnimJoint) child;
    gc_ptr32(HSD_ShapeAnimJoint) next;
    gc_ptr32(HSD_ShapeAnimDObj) shapeanimdobj;
};

struct HSD_PObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    void (*setup_mtx)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    s32 (*load)(HSD_PObj* pobj, HSD_PObjDesc* desc);
    HSD_ObjUpdateFunc update;
};

extern HSD_PObjInfo hsdPObj;

#define HSD_POBJ(o) ((HSD_PObj*) (o))
#define HSD_POBJ_INFO(i) ((HSD_PObjInfo*) (i))
#define HSD_POBJ_METHOD(o) HSD_POBJ_INFO(HSD_CLASS_METHOD(o))

HSD_PObjInfo* HSD_PObjGetDefaultClass(void);
void HSD_PObjSetDefaultClass(HSD_PObjInfo* info);
HSD_PObj* HSD_PObjAlloc(void);
void HSD_PObjFree(HSD_PObj*);

u32 HSD_PObjGetFlags(HSD_PObj* pobj);
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags);
void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
void HSD_ClearVtxDesc(void);
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc*);

void HSD_PObjClearMtxMark(void* obj, u32 mark);
void HSD_PObjSetMtxMark(int idx, void* obj, u32 mark);
void HSD_PObjGetMtxMark(int idx, void** obj, u32* mark);
void HSD_PObjAddAnim(HSD_PObj*, HSD_ShapeAnim*);
void HSD_PObjAddAnimAll(HSD_PObj*, HSD_ShapeAnim*);
void HSD_PObjAnim(HSD_PObj* pobj);
void HSD_PObjAnimAll(HSD_PObj*);
void HSD_PObjResolveRefs(HSD_PObj*, HSD_PObjDesc*);
void HSD_PObjResolveRefsAll(HSD_PObj*, HSD_PObjDesc*);
void HSD_PObjRemove(HSD_PObj*);
void HSD_PObjRemoveAll(HSD_PObj*);

void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, u32 flags);

void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

#endif
