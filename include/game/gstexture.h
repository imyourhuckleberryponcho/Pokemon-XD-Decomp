#ifndef GAME_GSTEXTURE_H
#define GAME_GSTEXTURE_H
#include <dolphin/types.h>

#ifndef __MWERKS__
#define GSTEXTURE_PC_TLUTDATA 0x70
#define GSTEXTURE_PC_TEXOBJ 0x80
#define GSTEXTURE_PC_TEXOBJ_SIZE 0x40
#define GSTEXTURE_PC_TLUTOBJ 0xC0
#define GSTEXTURE_PC_TLUTOBJ_SIZE 0x28
#define GSTEXTURE_PC_SIZE 0xF0
extern "C" struct GStexture* GStextureResolve(void* tex);
#endif

#ifndef GSTEXTURE_NO_GX
#include <dolphin/gx.h>

struct GStexture {
    u16 width;
    u16 height;
    u8 bitsPerPixel;
    u8 mipLevels;
    u8 inUse;
    u8 dirty;
    s32 format;
    u32 tlutFormat;
    u32 wrapS;
    u32 wrapT;
    s32 minFilter;
    s32 magFilter;
    u32 mipFilter;
    void* memHandle;
    void* mipData[8];
    void* tlutData;
    u32 totalSize;
    u16 refCount;
    u16 pad52;
    GXTexObj texObj;
    GXTlutObj tlutObj;
#ifndef __MWERKS__
    void* pcDisc;
#endif
};

#ifndef __MWERKS__
#include <game/gcdata.h>
#include <stddef.h>
struct GStextureDisc {
    gc_be16 width;
    gc_be16 height;
    u8 bitsPerPixel;
    u8 mipLevels;
    u8 inUse;
    u8 dirty;
    gc_bes32 format;
    gc_be32 tlutFormat;
    gc_be32 wrapS;
    gc_be32 wrapT;
    gc_bes32 minFilter;
    gc_bes32 magFilter;
    gc_be32 mipFilter;
    gc_be32 memHandle;
    gc_be32 mipData[8];
    gc_be32 tlutData;
    gc_be32 totalSize;
    gc_be16 refCount;
    gc_be16 pad52;
    u32 pcMagic;
    GStexture* pcRecord;
    u8 pad60[0x80 - 0x60];
};
#define GSTEXTURE_PC_MAGIC 0x50435458u
static_assert(offsetof(GStexture, tlutData) == GSTEXTURE_PC_TLUTDATA, "GSTEXTURE_PC_*");
static_assert(offsetof(GStexture, texObj) == GSTEXTURE_PC_TEXOBJ, "GSTEXTURE_PC_*");
static_assert(sizeof(GXTexObj) == GSTEXTURE_PC_TEXOBJ_SIZE, "GSTEXTURE_PC_*");
static_assert(offsetof(GStexture, tlutObj) == GSTEXTURE_PC_TLUTOBJ, "GSTEXTURE_PC_*");
static_assert(sizeof(GXTlutObj) == GSTEXTURE_PC_TLUTOBJ_SIZE, "GSTEXTURE_PC_*");
static_assert(sizeof(GStexture) == GSTEXTURE_PC_SIZE, "GSTEXTURE_PC_*");
#endif
#endif

#endif
