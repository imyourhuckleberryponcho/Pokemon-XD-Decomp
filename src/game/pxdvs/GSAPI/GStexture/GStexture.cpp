#include <dolphin/types.h>
#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

#pragma pool_strings off

#include <game/gstexture.h>

extern "C" {
void* memcpy(void*, const void*, u32);
void GSmemFree(void*);
void* GSmemAlloc(u32 size);
}
void GSgfxRenderWaitForDrawComplete();
extern "C" {
void* memset(void*, int, u32);
void GSlogWrite(const char* fmt, ...);
void* GSmemAllocAlign(u32 size, u32 align);
void GSgfxVideoGetEFBSize(u16* w, u16* h);
}

static u16 _texXformBuf[0xA00];
static GStexture* _textureStructList;
static u32 _textureStructCount;

#ifndef __MWERKS__
static_assert(sizeof(GStextureDisc) == 0x80, "GStextureDisc");
#define GSTEXTURE_PC_LOADED 0x5043

extern "C" GStexture* GStextureResolve(void* p)
{
    GStextureDisc* d = (GStextureDisc*)p;
    if (d != 0 && d->pcMagic == GSTEXTURE_PC_MAGIC && d->pcRecord != 0 && d->pcRecord->pad52 == GSTEXTURE_PC_LOADED &&
        d->pcRecord->pcDisc == p) {
        return d->pcRecord;
    }
    return (GStexture*)p;
}

static GStexture* _textureFromDisc(GStextureDisc* d)
{
    GStexture* tex = GStextureResolve(d);
    s32 i;

    if (tex != (GStexture*)d) {
        return tex;
    }
    tex = (GStexture*)GSmemAlloc(sizeof(GStexture));
    if (tex == 0) {
        return 0;
    }
    memset(tex, 0, sizeof(GStexture));
    tex->width = d->width;
    tex->height = d->height;
    tex->bitsPerPixel = d->bitsPerPixel;
    tex->mipLevels = d->mipLevels;
    tex->inUse = d->inUse;
    tex->dirty = d->dirty;
    tex->format = d->format;
    tex->tlutFormat = d->tlutFormat;
    tex->wrapS = d->wrapS;
    tex->wrapT = d->wrapT;
    tex->minFilter = d->minFilter;
    tex->magFilter = d->magFilter;
    tex->mipFilter = d->mipFilter;
    for (i = 0; i < tex->mipLevels && i < 8; i++) {
        tex->mipData[i] = (u8*)d + (u32)d->mipData[i];
    }
    if ((u32)d->tlutData != 0) {
        tex->tlutData = (u8*)d + (u32)d->tlutData;
    }
    tex->totalSize = d->totalSize;
    tex->refCount = d->refCount;
    tex->pad52 = GSTEXTURE_PC_LOADED;
    tex->pcDisc = d;
    d->pcRecord = tex;
    d->pcMagic = GSTEXTURE_PC_MAGIC;
    return tex;
}
#endif

extern "C" {

void GStextureConvertToHW(GStexture* tex)
{
    s32 y;
    u16* data;
    u16* src;
    u16* dst;
    s32 off;
    s32 x;

    if ((tex->format != 0x44 && tex->format != 0x90) || (tex->width & 2) || (tex->height & 2)) {
        return;
    }
    tex->refCount++;
    data = (u16*)tex->mipData[0];
    for (y = 0; y < tex->height; y += 4) {
        dst = _texXformBuf;
        for (x = 0, off = 0; x < tex->width; x += 4) {
            src = (u16*)((u8*)data + y * tex->width * 2 + off);
            off += 8;
            dst[0] = *src++;
            dst[1] = *src++;
            dst[2] = *src++;
            dst[3] = *src++;
            src = (u16*)((u8*)src + tex->width * 2 - 8);
            dst[4] = *src++;
            dst[5] = *src++;
            dst[6] = *src++;
            dst[7] = *src++;
            src = (u16*)((u8*)src + tex->width * 2 - 8);
            dst[8] = *src++;
            dst[9] = *src++;
            dst[10] = *src++;
            dst[11] = *src++;
            src = (u16*)((u8*)src + tex->width * 2 - 8);
            dst[12] = *src++;
            dst[13] = *src++;
            dst[14] = *src++;
            dst[15] = *src++;
            dst += 16;
        }
        memcpy((u8*)data + y * tex->width * 2, _texXformBuf, tex->width * 8);
    }
    DCStoreRange(tex->mipData[0], tex->totalSize);
    GXInvalidateTexAll();
    tex->refCount--;
}

void GStextureConvertFromHW(GStexture* tex)
{
    u16* data;
    s32 y;
    s32 x;
    u16* src;
    u16* dst;

    if ((tex->format != 0x44 && tex->format != 0x90) || (tex->width & 2) || (tex->height & 2)) {
        return;
    }
    {
        {
            tex->refCount++;
            data = (u16*)tex->mipData[0];
            for (y = 0; y < tex->height; y += 4) {
                dst = _texXformBuf;
                src = (u16*)((u8*)data + y * tex->width * 2);
                for (x = 0; x < tex->width; x += 4) {
                    u16* d = dst;
                    *d++ = src[0];
                    *d++ = src[1];
                    *d++ = src[2];
                    *d++ = src[3];
                    d = (u16*)((u8*)d + tex->width * 2 - 8);
                    *d++ = src[4];
                    *d++ = src[5];
                    *d++ = src[6];
                    *d++ = src[7];
                    d = (u16*)((u8*)d + tex->width * 2 - 8);
                    *d++ = src[8];
                    *d++ = src[9];
                    *d++ = src[10];
                    *d++ = src[11];
                    d = (u16*)((u8*)d + tex->width * 2 - 8);
                    *d++ = src[12];
                    *d++ = src[13];
                    *d++ = src[14];
                    *d++ = src[15];
                    src += 16;
                    dst += 4;
                }
                memcpy((u8*)data + y * tex->width * 2, _texXformBuf, tex->width * 8);
            }
            DCStoreRange(tex->mipData[0], tex->totalSize);
            GXInvalidateTexAll();
            tex->refCount--;
        }
    }
}

s32 GStextureGetGXformat(GStexture* tex, u8 alpha)
{
    switch (tex->format) {
    case 0x00:
        return 0x08;
    case 0x01:
        return 0x09;
    case 0x30:
        return 0x0A;
    case 0x40:
        return 0x00;
    case 0x41:
        return 0x02;
    case 0x42:
        return 0x01;
    case 0x43:
        return 0x03;
    case 0x44:
        return 0x04;
    case 0x45:
        return 0x06;
    case 0x90:
        return 0x05;
    case 0xB0:
        return 0x0E;
    case 0xA0:
        if (alpha != 0) {
            return 1;
        }
        return 0x27;
    case 0xA1:
        if (alpha != 0) {
            return 1;
        }
        return 0x28;
    case 0xA2:
        if (alpha != 0) {
            return 1;
        }
        return 0x29;
    case 0xA3:
        if (alpha != 0) {
            return 1;
        }
        return 0x2A;
    default:
        return -1;
    }
}

u32 GStextureGetTlutFormat(GStexture* tex)
{
    return tex->tlutFormat;
}

u32 GStextureGetFormat(GStexture* tex)
{
    return tex->format;
}

u8 GStextureGetMiplevels(GStexture* tex)
{
    return (u8)(tex->mipLevels - 1);
}

u16 GStextureGetYsize(GStexture* tex)
{
    return tex->height;
}

u16 GStextureGetXsize(GStexture* tex)
{
    return tex->width;
}

#pragma push
#pragma scheduling off
u32 GStextureUnlockImage(GStexture* tex)
{
    DCStoreRange(tex->mipData[0], tex->totalSize);
    GXInvalidateTexAll();
    return tex->refCount--;
}
#pragma pop

void* GStextureLockImage(GStexture* tex, u8 level)
{
    if (level >= 8) {
        return 0;
    }
    tex->refCount++;
    return tex->mipData[level];
}

static inline void _textureApplyWrap(GStexture* tex)
{
    GXTexWrapMode s;
    GXTexWrapMode t;

    switch (tex->wrapS) {
    case 0:
        s = GX_CLAMP;
        break;
    case 1:
        s = GX_REPEAT;
        break;
    case 2:
        s = GX_MIRROR;
        break;
    }
    switch (tex->wrapT) {
    case 0:
        t = GX_CLAMP;
        break;
    case 1:
        t = GX_REPEAT;
        break;
    case 2:
        t = GX_MIRROR;
        break;
    }
    GXInitTexObjWrapMode(&tex->texObj, s, t);
    tex->dirty = 1;
}

void GStextureSetFilter(GStexture* tex, s32 minFilter, s32 magFilter, u32 mipFilter)
{
    tex->minFilter = minFilter;
    tex->magFilter = magFilter;
    tex->mipFilter = mipFilter;
    GXTexFilter min = (GXTexFilter)minFilter;

    switch (tex->mipFilter) {
    case 0:
        if (tex->minFilter == 2) {
            min = GX_LINEAR;
        } else {
            min = GX_NEAR;
        }
        break;
    case 1:
        if (tex->minFilter == 2) {
            min = GX_LIN_MIP_NEAR;
        } else {
            min = GX_NEAR_MIP_NEAR;
        }
        break;
    case 2:
        if (tex->minFilter == 2) {
            min = GX_LIN_MIP_LIN;
        } else {
            min = GX_NEAR_MIP_LIN;
        }
        break;
    }
    GXInitTexObjLOD(&tex->texObj, min, (GXTexFilter)(tex->magFilter == 2 ? 1 : 0), 0.0f, (f32)(tex->mipLevels - 1), 0.0f, 0, 0,
                    (GXAnisotropy)0);
    tex->dirty = 1;
}

void GStextureSetWrap(GStexture* tex, u32 wrapS, u32 wrapT)
{
    tex->wrapS = wrapS;
    tex->wrapT = wrapT;
    _textureApplyWrap(tex);
}

void GStextureFree(GStexture* tex)
{
#ifndef __MWERKS__
    tex = GStextureResolve(tex);
#endif
    if (tex->inUse != 0) {
        GSgfxRenderWaitForDrawComplete();
        tex->inUse = 0;
        if (tex->memHandle != 0) {
            GSmemFree(tex->memHandle);
        }
    }
#ifndef __MWERKS__
    if (tex->pad52 == GSTEXTURE_PC_LOADED) {
        GSgfxRenderWaitForDrawComplete();
        ((GStextureDisc*)tex->pcDisc)->pcMagic = 0;
        GSmemFree(tex);
    }
#endif
}

static inline s32 _textureGetGXFormat(GStexture* tex)
{
    switch (tex->format) {
    case 0x00:
        return 0x08;
    case 0x01:
        return 0x09;
    case 0x30:
        return 0x0A;
    case 0x40:
        return 0x00;
    case 0x41:
        return 0x02;
    case 0x42:
        return 0x01;
    case 0x43:
        return 0x03;
    case 0x44:
        return 0x04;
    case 0x45:
        return 0x06;
    case 0x90:
        return 0x05;
    case 0xB0:
        return 0x0E;
    case 0xA0:
        return 1;
    case 0xA1:
        return 1;
    case 0xA2:
        return 1;
    case 0xA3:
        return 1;
    default:
        return -1;
    }
}

static inline void _textureInitObjs(GStexture* tex)
{
    GXTlutFmt tlutFmt;
    u16 tlutEntries = 0;
    s32 gxFmt;

    if (tex->tlutData != 0) {
        switch (tex->format) {
        case 0x00:
            gxFmt = 8;
            break;
        case 0x01:
            gxFmt = 9;
            break;
        case 0x30:
            gxFmt = 10;
            break;
        default:
            gxFmt = -1;
            break;
        }
        switch (tex->format) {
        case 0x00:
            tlutEntries = 0x10;
            break;
        case 0x01:
            tlutEntries = 0x100;
            break;
        case 0x30:
            tlutEntries = 0x400;
            break;
        }
        switch (tex->tlutFormat) {
        case 1:
            tlutFmt = GX_TL_IA8;
            break;
        case 2:
            tlutFmt = GX_TL_RGB565;
            break;
        case 3:
            tlutFmt = GX_TL_RGB5A3;
            break;
        }
        GXInitTlutObj(&tex->tlutObj, tex->tlutData, tlutFmt, tlutEntries);
        GXInitTexObjCI(&tex->texObj, tex->mipData[0], tex->width, tex->height, (GXCITexFmt)gxFmt, GX_CLAMP, GX_CLAMP,
                       tex->mipLevels > 1, 0);
    } else {
        gxFmt = _textureGetGXFormat(tex);
        GXInitTexObj(&tex->texObj, tex->mipData[0], tex->width, tex->height, (GXTexFmt)gxFmt, GX_CLAMP, GX_CLAMP,
                     tex->mipLevels > 1);
    }
}

static inline void _textureCalcSize(GStexture* tex, s32 levels, u32 baseSize)
{
    u32 size = baseSize;
    s32 i;

    tex->totalSize = 0;
    for (i = 0; i < levels; i++) {
        tex->totalSize += (size + 31) & ~31;
        size >>= 1;
    }
}

GStexture* GStextureCreateFromMemory(GStexture* tex, u16 width, u32 height, void* data, s32 format, s32 tlutFormat,
                                     u32 mipLevels)
{
    s32 tlutEntries = 0;
    u32 size;
    int i;
    s32 levels;

    memset(tex, 0, sizeof(GStexture));
    tex->width = width;
    tex->height = height;
    switch (format) {
    case 0x00:
        tlutEntries = 0x10;
    case 0x40:
    case 0xB0:
        tex->bitsPerPixel = 4;
        break;
    case 0x01:
        tlutEntries = 0x100;
    case 0x41:
    case 0x42:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
        tex->bitsPerPixel = 8;
        break;
    case 0x30:
        tlutEntries = 0x400;
    case 0x43:
    case 0x44:
    case 0x90:
        tex->bitsPerPixel = 16;
        break;
    case 0x45:
        tex->bitsPerPixel = 32;
        break;
    default:
        return 0;
    }
    levels = mipLevels;
    levels = (u8)(levels + 1);
    tex->inUse = 1;
    tex->format = format;
    tex->mipLevels = levels;
    tex->dirty = 1;
    tex->tlutFormat = tlutFormat;
    tex->wrapS = 0;
    tex->wrapT = 0;
    tex->minFilter = 2;
    tex->magFilter = 2;
    tex->mipData[1] = 0;
    tex->memHandle = 0;
    tex->mipData[0] = data;
    tex->mipFilter = 0;
    tex->tlutData = 0;
    size = (tex->bitsPerPixel * (width * height)) >> 3;
    _textureCalcSize(tex, levels, size);
    if (tlutEntries != 0) {
        if (tlutFormat != 0 && tlutFormat >= 0 && tlutFormat < 4) {
            tex->totalSize += (tlutEntries << 4) >> 3;
        } else {
            return 0;
        }
    }
    size = (tex->bitsPerPixel * (width * height)) >> 3;
    for (i = 1; i < 8; i++) {
        if (i < tex->mipLevels) {
            tex->mipData[i] = (u8*)tex->mipData[i - 1] + size;
            size >>= 1;
        } else {
            tex->mipData[i] = 0;
        }
    }
    if (tlutFormat < 4 && tlutFormat >= 1) {
        tex->tlutData = (u8*)tex->mipData[tex->mipLevels - 1] + size;
    } else {
        tex->tlutData = 0;
    }
    _textureInitObjs(tex);
    DCStoreRange(tex->mipData[0], tex->totalSize);
    return tex;
}

static inline GStexture* _textureGetFree(void)
{
    GStexture* tex = _textureStructList;
    u32 i;

    for (i = 0; i < _textureStructCount; i++, tex++) {
        if (tex->inUse == 0) {
            return tex;
        }
    }
    return 0;
}

GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels)
{
    u16 h;
    u16 w;
    GStexture* tex;
    s32 tlutEntries;
    s32 align;
    s32 mask;
    u32 size;
    int i;
    u16 aw, ah;
    u16 tw, th;
    u8 maxMips;

    w = width;
    h = height;
    if (w == 0 && h == 0) {
        GSgfxVideoGetEFBSize(&w, &h);
    }
    if (w > 0x400 || h > 0x400 || w < 4 || h < 4) {
        return 0;
    }
    switch (format) {
    case 0x00:
    case 0x40:
    case 0x41:
    case 0xB0:
        align = 8;
        break;
    case 0x01:
    case 0x42:
    case 0x43:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
        align = 4;
        break;
    case 0x30:
    case 0x44:
    case 0x45:
    case 0x90:
        align = 4;
        break;
    default:
        GSlogWrite("GStexture: invalid texture format\n");
        return 0;
    }
    mask = align - 1;
    aw = (w + mask) & ~mask;
    ah = (h + mask) & ~mask;
    if (aw != w || ah != h) {
        GSlogWrite("GStexture: warning -- texture size adjusted from [%d,%d] to [%d,%d]\n", w, h, aw, ah);
    }
    w = aw;
    h = ah;
    tw = aw;
    th = ah;
    for (maxMips = 0; tw > 4 && th > 4 && maxMips < 7; maxMips++) {
        tw >>= 1;
        th >>= 1;
    }
    if (mipLevels > maxMips) {
        mipLevels = maxMips;
    }
    tex = _textureGetFree();
    if (tex == 0) {
        return 0;
    }
    tlutEntries = 0;
    switch (format) {
    case 0x00:
        tlutEntries = 0x10;
    case 0x40:
    case 0xB0:
        tex->bitsPerPixel = 4;
        break;
    case 0x01:
        tlutEntries = 0x100;
    case 0x41:
    case 0x42:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
        tex->bitsPerPixel = 8;
        break;
    case 0x30:
        tlutEntries = 0x400;
    case 0x43:
    case 0x44:
    case 0x90:
        tex->bitsPerPixel = 16;
        break;
    case 0x45:
        tex->bitsPerPixel = 32;
        break;
    default:
        return 0;
    }
    size = (u32)(tex->bitsPerPixel * (w * h)) >> 3;
    mipLevels++;
    _textureCalcSize(tex, mipLevels, size);
    if (tlutEntries != 0) {
        if (tlutFormat != 0 && tlutFormat >= 0 && tlutFormat < 4) {
            tex->totalSize += (tlutEntries << 4) >> 3;
        } else {
            return 0;
        }
    }
    tex->memHandle = GSmemAllocAlign(tex->totalSize, 0x20);
    if (tex->memHandle == 0) {
        return 0;
    }
    tex->mipData[0] = tex->memHandle;
    DCStoreRange(tex->mipData[0], tex->totalSize);
    tex->inUse = 1;
    tex->width = w;
    tex->height = h;
    tex->mipLevels = mipLevels;
    tex->format = format;
    tex->tlutFormat = tlutFormat;
    tex->wrapS = 0;
    tex->wrapT = 0;
    tex->minFilter = 2;
    tex->magFilter = 2;
    if (mipLevels > 1) {
        tex->mipFilter = 2;
    } else {
        tex->mipFilter = 0;
    }
    tex->refCount = 0;
    tex->pad52 = 0;
    size = (u32)(tex->bitsPerPixel * (w * h)) >> 3;
    for (i = 1; i < 8; i++) {
        if (i < tex->mipLevels) {
            tex->mipData[i] = (u8*)tex->mipData[i - 1] + size;
            size >>= 1;
        } else {
            tex->mipData[i] = 0;
        }
    }
    switch (tlutFormat) {
    case 1:
    case 2:
    case 3:
        tex->tlutData = (u8*)tex->mipData[tex->mipLevels - 1] + size;
        break;
    default:
        tex->tlutData = 0;
        break;
    }
    _textureInitObjs(tex);
    tex->dirty = 1;
    return tex;
}

GStexture* GStextureLoad(GStexture* tex)
{
    s32 i;
    int j;
    GXTexFilter min;

#ifdef __MWERKS__
    for (i = 0; i < tex->mipLevels; i++) {
        tex->mipData[i] = (u8*)tex + (u32)tex->mipData[i];
    }
    for (j = tex->mipLevels; j < 8; j++) {
        tex->mipData[j] = 0;
    }
    if (tex->tlutData != 0) {
        tex->tlutData = (u8*)tex + (u32)tex->tlutData;
    }
#else
    tex = _textureFromDisc((GStextureDisc*)tex);
    if (tex == 0) {
        return 0;
    }
#endif
    _textureInitObjs(tex);
    _textureApplyWrap(tex);
    switch (tex->mipFilter) {
    case 0:
        if (tex->minFilter == 2) {
            min = GX_LINEAR;
        } else {
            min = GX_NEAR;
        }
        break;
    case 1:
        if (tex->minFilter == 2) {
            min = GX_LIN_MIP_NEAR;
        } else {
            min = GX_NEAR_MIP_NEAR;
        }
        break;
    case 2:
        if (tex->minFilter == 2) {
            min = GX_LIN_MIP_LIN;
        } else {
            min = GX_NEAR_MIP_LIN;
        }
        break;
    }
    GXInitTexObjLOD(&tex->texObj, min, (GXTexFilter)(tex->magFilter == 2 ? 1 : 0), 0.0f, (f32)(tex->mipLevels - 1), 0.0f, 0, 0,
                    (GXAnisotropy)0);
    tex->dirty = 1;
    tex->dirty = 1;
    tex->memHandle = 0;
    DCStoreRange(tex->mipData[0], tex->totalSize);
    return tex;
}

void GStextureInit(u32 count)
{
    u32 i;

    _textureStructCount = count;
#ifdef __MWERKS__
    _textureStructList = (GStexture*)GSmemAlloc(count << 7);
#else
    _textureStructList = (GStexture*)GSmemAlloc(count * sizeof(GStexture));
#endif
    if (_textureStructList != 0) {
        for (i = 0; i < _textureStructCount; i++) {
            _textureStructList[i].inUse = 0;
        }
    }
}

s32 GXFmtToGStextureFmt(u32 fmt)
{
    switch (fmt) {
    case 8:
        return 0x00;
    case 9:
        return 0x01;
    case 10:
        return 0x30;
    case 0:
        return 0x40;
    case 2:
        return 0x41;
    case 1:
        return 0x42;
    case 3:
        return 0x43;
    case 4:
        return 0x44;
    case 6:
        return 0x45;
    case 5:
        return 0x90;
    case 14:
        return 0xB0;
    case 0x27:
        return 0xA0;
    case 0x28:
        return 0xA1;
    case 0x29:
        return 0xA2;
    case 0x2A:
        return 0xA3;
    default:
        return -1;
    }
}
}
