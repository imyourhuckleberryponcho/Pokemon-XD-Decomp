// WIP (NonMatching): pachiruEffectFree/Create match; _pachiruEffectCreateTexture differs in register
// choice (texture/dstImage swapped) and in the spot-offset math ordering inside the main loop.
#include <dolphin/types.h>

struct GStexture;
struct GSmaterial;
struct GSmodel;
struct GSpart;

// Material of the Pachirisu model whose texture gets randomized spots.
struct PachiruEffect {
    GSmaterial* material;
    GStexture* texture;
};

extern "C" {
void GStextureFree(GStexture* texture);
GSpart* GSmodelGetPart(GSmodel* model, s32 index);
GSmaterial* GSpartGetMaterial(GSpart* part, s32 index);
GStexture* GSresGetResource(u32 group, u32 id);
void GSmaterialSetTexture(GSmaterial* material, GStexture* texture);
void GSpartFree(GSpart* part);
int GStextureGetXsize(GStexture* texture);
int GStextureGetYsize(GStexture* texture);
u32 GStextureGetMiplevels(GStexture* texture);
u32 GStextureGetTlutFormat(GStexture* texture);
u32 GStextureGetFormat(GStexture* texture);
GStexture* GStextureCreate(u16 width, u16 height, u32 format, u32 tlutFormat, u32 mipLevels);
u16* GStextureLockImage(GStexture* texture, s32 level);
void GStextureUnlockImage(GStexture* texture);
void GStextureConvertFromHW(GStexture* texture);
void GStextureConvertToHW(GStexture* texture);
void* memcpy(void* dst, const void* src, unsigned long n);
void DCFlushRange(void* addr, u32 size);
void GSlogWrite(const char* fmt, ...);
}

// Where the four spots go on the base texture (x, y).
static u8 gPachiruCoords[4][2] = { { 0x06, 0x07 }, { 0x5B, 0x06 }, { 0x1E, 0x41 }, { 0x44, 0x41 } };

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spot, unsigned long seed);

extern "C" {

void pachiruEffectFree(PachiruEffect* effect) {
    effect->material = NULL;
    if (effect->texture != NULL) {
        GStextureFree(effect->texture);
        effect->texture = NULL;
    }
}

bool pachiruEffectCreate(PachiruEffect* effect, GSmodel* model, u32 seed) {
    bool ok = false;
    GSpart* part;
    GStexture* base;
    GStexture* spot;

    if (model == NULL) {
        return false;
    }
    part = GSmodelGetPart(model, 2);
    if (part == NULL) {
        return false;
    }
    effect->material = NULL;
    effect->texture = NULL;
    effect->material = GSpartGetMaterial(part, 0);
    if (effect->material != NULL) {
        base = GSresGetResource(0x387, 0x0F7D1200);
        if (base != NULL) {
            spot = GSresGetResource(0x387, 0x0F7E1200);
            if (spot != NULL) {
                effect->texture = _pachiruEffectCreateTexture(base, spot, seed);
                if (effect->texture != NULL) {
                    GSmaterialSetTexture(effect->material, effect->texture);
                    ok = true;
                }
            }
        }
    }
    if (!ok) {
        if (effect->texture != NULL) {
            GStextureFree(effect->texture);
            effect->texture = NULL;
        }
        effect->material = NULL;
    }
    GSpartFree(part);
    return ok;
}

}

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spot, unsigned long seed) {
    u16* dstImage;
    GStexture* texture;
    u16* srcImage = NULL;
    s16 width;
    s16 height;
    s16 spotWidth;
    s32 size;
    s16 spotHeight;
    u16* end;
    s16 i;

    width = GStextureGetXsize(base);
    height = GStextureGetYsize(base);
    dstImage = (u16*)GStextureGetMiplevels(base);
    texture = GStextureCreate(width, height, GStextureGetFormat(base), GStextureGetTlutFormat(base), (u32)dstImage);
    dstImage = GStextureLockImage(texture, 0);
    if (dstImage == NULL) {
        goto fail;
    }
    srcImage = GStextureLockImage(base, 0);
    if (srcImage == NULL) {
        goto fail;
    }
    size = width * height;
    memcpy(dstImage, srcImage, size * 2);
    DCFlushRange(dstImage, size * 2);
    GStextureUnlockImage(base);
    GStextureConvertFromHW(texture);
    GStextureConvertFromHW(spot);
    srcImage = GStextureLockImage(spot, 0);
    if (srcImage == NULL) {
        goto fail;
    }
    spotWidth = GStextureGetXsize(spot);
    spotHeight = GStextureGetYsize(spot);
    if (spotWidth > (width >> 2) || spotHeight > (height >> 2)) {
        goto fail;
    }
    end = dstImage + (size - 1);
    for (i = 0; i < 4; i++) {
        s16 dy = ((seed >> 4) & 0xF) - 8;
        s16 dx = (seed & 0xF) - 8;
        s16 start;
        s16 srcOfs;
        s32 dstOfs;
        s16 row;
        seed >>= 8;
        start = ((s32)(3.4f * dx) + gPachiruCoords[i][0]) + ((s32)(3.4f * dy) + gPachiruCoords[i][1]) * width;
        srcOfs = 0;
        dstOfs = 0;
        for (row = 0; row < spotHeight; row++) {
            s16 idx = start + dstOfs;
            if (idx >= 0) {
                u16* dst = dstImage + idx;
                if (dst <= end) {
                    u16* src = srcImage + srcOfs;
                    s16 col;
                    for (col = 0; col < spotWidth; col++, dst++, src++) {
                        if (dst <= end && *src > *dst) {
                            *dst = *src;
                        }
                    }
                }
            }
            srcOfs += spotWidth;
            dstOfs += width;
        }
    }
    GStextureUnlockImage(texture);
    GStextureUnlockImage(spot);
    GStextureConvertToHW(spot);
    GStextureConvertToHW(texture);
    return texture;

fail:
    GSlogWrite("Failed to create Patchiru texture\n");
    if (dstImage != NULL) {
        GStextureUnlockImage(texture);
    }
    if (srcImage != NULL) {
        GStextureUnlockImage(spot);
    }
    if (texture != NULL) {
        GStextureFree(texture);
    }
    return NULL;
}
