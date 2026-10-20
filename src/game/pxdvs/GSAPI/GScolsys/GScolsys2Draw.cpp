// STATUS: NOT linkable yet. Needs extra_cflags=["-inline noauto,deferred"]; source is written
// bottom-to-top (the object has drawHitMdl, drawWalkMdl, makeDisplayListFixedObj, GScolsys2Draw in that
// order) and needs the inline_depth/inline_max_size pragmas so drawObj is expanded into both callers.
// fcheck with those flags: LAYOUT OK, CONST OK; drawHitMdl 99.84%, drawWalkMdl 98.98%, GScolsys2Draw
// 98.41%, makeDisplayListFixedObj 98.11%. Remaining diffs: only saved-register numbering and stack slot
// order of the face-drawing inline expansions (and two swapped hoisted lbz in drawHitMdl).
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#include <libc/string.h>
#pragma inline_depth(8)
#pragma inline_max_size(10000)

struct Vec3 {
    f32 x, y, z;
};

struct GSmtx {
    f32 m[3][4];
};

struct Color4 {
    u8 r, g, b, a;
};

struct CCD_NIBBLES {
    u8 hi : 4;
    u8 lo : 4;
};

struct CCD_WALKTRI {
    Vec3 v[3];
    Vec3 normal;
    CCD_NIBBLES attr;
    CCD_NIBBLES layer;
    u8 pad32[2];
};

struct CCD_TRI_GROUP {
    u8* data;
    u32 count;
};

struct CCD_HITMDL_HEAD : CCD_TRI_GROUP {};
struct CCD_WALKMDL_HEAD : CCD_TRI_GROUP {};

struct CCD_DRAW_OBJ {
    u8 unk0[0x24];
    CCD_WALKMDL_HEAD* walk;  // 0x24
    CCD_HITMDL_HEAD* hit;    // 0x28
    CCD_TRI_GROUP* group2C;
    CCD_TRI_GROUP* group30;
    CCD_HITMDL_HEAD* hit34;
    CCD_TRI_GROUP* group38;
    u16 flags;               // 0x3C
    u8 pad3E[2];
};

struct CCD_DRAW_FILEHEAD {
    CCD_DRAW_OBJ* objs;
    u32 numObjs;
};

struct GScolsysLayerEnt {
    u8 unk0[0x24];
    u16 flags;
    u8 pad26[2];
};

struct GScolsysLayer {
    GScolsysLayerEnt ents[88];
};

struct GScolsys2Data {
    u32 unk0;
    GScolsysLayer layers[1];
    u32 cur;     // 0xDC4
    void* buf;   // 0xDC8
    void* dl;    // 0xDCC
};

struct ColsysDL {
    u32 w[4];
};

extern GScolsys2Data GScolsys2;
static ColsysDL _colsysDL;

extern "C" {
void PSMTXMultVec(const GSmtx* m, const Vec3* src, Vec3* dst);
CCD_DRAW_FILEHEAD* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjMatrix(GSmtx* m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx* m, u32 index);
void GScolsys2HumanDispColision(void);
void floorMapSetDisp(int on);
void GSgfxDLPrimitiveType(int type);
void GSgfxDLBeginSurface(int count);
void GSgfxDLEndSurface(void);
void GSgfxDLBegin(void* dl, void* buf, u32 size, u32 flags);
void GSgfxDLEnd(void);
void GSgfxDLDraw(void* dl);
u32 GSinputButtonsPressed(int pad);
void GSgfxLayerSetActive(int layer);
void GScameraLoadActiveCameraMatrix(int cam);
void GSgfxCullMode(int mode);
void GSgfxSetupRenderAndSelect(void* buf);
void GSgfxBlendMode(int a, int b, int c);
void GSgfxZCompare(int a, int b);
void GSgfxPixelMode(int a, int b, int c);
}

static inline void putVtx(const Vec3& v, const Color4& c) {
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u8 = c.r;
    GXWGFifo.u8 = c.g;
    GXWGFifo.u8 = c.b;
    GXWGFifo.u8 = c.a;
}

static void drawHitMdl(CCD_HITMDL_HEAD* head, GSmtx* mtx, GSmtx* rot);
static void drawWalkMdl(CCD_WALKMDL_HEAD* head, GSmtx* mtx, GSmtx* rot);
static void* makeDisplayListFixedObj();

static inline void drawObj(CCD_DRAW_OBJ* obj, GSmtx* mtx, GSmtx* rot) {
    if (obj->walk != 0) {
        drawWalkMdl(obj->walk, mtx, rot);
    }
    if (obj->hit != 0) {
        drawHitMdl(obj->hit, mtx, rot);
    }
    {
        CCD_TRI_GROUP* group = obj->group2C;
        if (group != 0) {
            Color4 color = {0xFF, 0x00, 0xFF, 0xC0};
            Vec3 v;
            u8* tri = group->data;
            u32 i;
            GSgfxDLPrimitiveType(0x90);
            for (i = 0; i < group->count; i++, tri += 0x34) {
                int j;
                GSgfxDLBeginSurface(3);
                for (j = 0; j < 3; j++) {
                    PSMTXMultVec(mtx, (Vec3*)(tri + j * 12), &v);
                    putVtx(v, color);
                }
                GSgfxDLEndSurface();
            }
        }
    }
    {
        CCD_TRI_GROUP* group = obj->group30;
        if (group != 0) {
            Color4 color = {0xFF, 0xFF, 0x00, 0xC0};
            Vec3 v;
            u8* tri = group->data;
            u32 i;
            GSgfxDLPrimitiveType(0x90);
            for (i = 0; i < group->count; i++, tri += 0x34) {
                int j;
                GSgfxDLBeginSurface(3);
                for (j = 0; j < 3; j++) {
                    PSMTXMultVec(mtx, (Vec3*)(tri + j * 12), &v);
                    putVtx(v, color);
                }
                GSgfxDLEndSurface();
            }
        }
    }
    if (obj->hit34 != 0) {
        drawHitMdl(obj->hit34, mtx, rot);
    }
    {
        CCD_TRI_GROUP* group = obj->group38;
        if (group != 0) {
            Color4 color = {0x00, 0xFF, 0xFF, 0xC0};
            Vec3 v;
            u8* tri = group->data;
            u32 i;
            GSgfxDLPrimitiveType(0x90);
            for (i = 0; i < group->count; i++, tri += 0x30) {
                int j;
                GSgfxDLBeginSurface(3);
                for (j = 0; j < 3; j++) {
                    PSMTXMultVec(mtx, (Vec3*)(tri + j * 12), &v);
                    putVtx(v, color);
                }
                GSgfxDLEndSurface();
            }
        }
    }
}

extern "C" {
void GScolsys2Draw(void) {
    CCD_DRAW_FILEHEAD* head;
    u32 i;
    CCD_DRAW_OBJ* obj;
    GScolsysLayerEnt* ent;
    GSmtx mtx;
    GSmtx rot;

    head = GScolsys2GetCCDFileHead();
    if (head == 0) {
        return;
    }
    if (GSinputButtonsPressed(1) & 0x40) {
        floorMapSetDisp(0);
    } else if (GSinputButtonsPressed(1) & 0x20) {
        floorMapSetDisp(1);
    }
    GSgfxLayerSetActive(2);
    GScameraLoadActiveCameraMatrix(2);
    GSgfxCullMode(1);
    GSgfxSetupRenderAndSelect(GScolsys2.buf);
    GSgfxBlendMode(1, 4, 5);
    GSgfxZCompare(1, 3);
    GSgfxPixelMode(1, 1, 1);
    obj = head->objs;
    ent = GScolsys2.layers[GScolsys2.cur].ents;
    for (i = 0; i < head->numObjs; i++, obj++, ent++) {
        if (ent->flags & 1) {
            continue;
        }
        if (!(obj->flags & 1)) {
            continue;
        }
        GScolsys2GetObjMatrix(&mtx, i);
        GScolsys2GetObjRotMatrix(&rot, i);
        drawObj(obj, &mtx, &rot);
    }
    if (GScolsys2.dl == 0) {
        GScolsys2.dl = makeDisplayListFixedObj();
    }
    if (GScolsys2.dl != 0) {
        GSgfxDLDraw(GScolsys2.dl);
    }
    GScolsys2HumanDispColision();
}
}
static void* makeDisplayListFixedObj() {
    CCD_DRAW_FILEHEAD* head;
    u32 i;
    CCD_DRAW_OBJ* obj;
    GSmtx mtx;
    GSmtx rot;

    head = GScolsys2GetCCDFileHead();
    if (head == 0) {
        return 0;
    }
    memset(&_colsysDL, 0, sizeof(_colsysDL));
    GSgfxDLBegin(&_colsysDL, GScolsys2.buf, 0x400, 0x8000);
    obj = head->objs;
    for (i = 0; i < head->numObjs; i++, obj++) {
        if (obj->flags & 1) {
            continue;
        }
        GScolsys2GetObjMatrix(&mtx, i);
        GScolsys2GetObjRotMatrix(&rot, i);
        drawObj(obj, &mtx, &rot);
    }
    GSgfxDLEnd();
    return &_colsysDL;
}

static void drawWalkMdl(CCD_WALKMDL_HEAD* head, GSmtx* mtx, GSmtx* rot) {
    Color4 color;
    Vec3 v;
    CCD_WALKTRI* tri;
    u32 i;

    GSgfxDLPrimitiveType(0x90);
    tri = (CCD_WALKTRI*)head->data;
    for (i = 0; i < head->count; i++, tri++) {
        int j;
        int level;
        memset(&color, 0, sizeof(color));
        color.a = 0xC0;
        level = tri->attr.hi;
        color.g = (u8)(127.0f * ((f32)level / 15.0f) + 128.0f);
        if ((level = tri->attr.lo + 1) >= 16) {
            level = 0;
        }
        color.b = (u8)(255.0f * ((f32)level / 15.0f));
        level = tri->layer.hi;
        if (level > 0) {
            color.r = level * 4 + 0xC0;
        }
        GSgfxDLBeginSurface(3);
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->v[j], &v);
            GXWGFifo.f32 = v.x;
            GXWGFifo.f32 = 0.1f + v.y;
            GXWGFifo.f32 = v.z;
            GXWGFifo.u8 = color.r;
            GXWGFifo.u8 = color.g;
            GXWGFifo.u8 = color.b;
            GXWGFifo.u8 = color.a;
        }
        GSgfxDLEndSurface();
    }
}

static void drawHitMdl(CCD_HITMDL_HEAD* head, GSmtx* mtx, GSmtx* rot) {
    Color4 color = {0xFF, 0xFF, 0xFF, 0xFF};
    Color4 c2;
    u32 i;
    Vec3 verts[3];
    u8* tri = head->data;

    c2 = color;

    for (i = 0; i < head->count; i++, tri += 0x34) {
        int j;
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, (Vec3*)(tri + j * 12), &verts[j]);
        }
        GSgfxDLPrimitiveType(0xA8);
        for (j = 0; j < 3; j++) {
            int next = j + 1;
            if (next >= 3) {
                next = 0;
            }
            GSgfxDLBeginSurface(2);
            putVtx(verts[j], c2);
            putVtx(verts[next], c2);
            GSgfxDLEndSurface();
        }
    }
}

