#pragma pool_strings off
#include <dolphin/types.h>

struct GStexture;
struct GSmaterial;
struct GSmodel;
struct GSpart;

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
u16 GStextureGetXsize(GStexture* texture);
u16 GStextureGetYsize(GStexture* texture);
u8 GStextureGetMiplevels(GStexture* texture);
u32 GStextureGetTlutFormat(GStexture* texture);
u32 GStextureGetFormat(GStexture* texture);
GStexture* GStextureCreate(u16 width, u16 height, u32 format, u32 tlutFormat, u8 mipLevels);
u16* GStextureLockImage(GStexture* texture, s32 level);
void GStextureUnlockImage(GStexture* texture);
void GStextureConvertFromHW(GStexture* texture);
void GStextureConvertToHW(GStexture* texture);
void* memcpy(void* dst, const void* src, unsigned long n);
void DCFlushRange(void* addr, u32 size);
void GSlogWrite(const char* fmt, ...);
}

static u8 gPachiruCoords[4][2] = { { 0x06, 0x07 }, { 0x5B, 0x06 }, { 0x1E, 0x41 }, { 0x44, 0x41 } };

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spot, u32 seed);

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

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spotTex, u32 seed) {
    u16* output;
    u16* source;
    GStexture* texture;
    u16* outputPixels;
    u16* sourcePixels;
    u16* lastOutputPixel;
    s16 baseWidth;
    s16 baseHeight;
    s16 spotWidth;
    s16 spotHeight;
    s32 pixelCount;
    s32 size;
    s16 column;
    s16 row;
    s16 spot;
    s32 startPixel;
    s32 x;
    s32 y;
    s16 outputIndex;
    s16 sourceIndex;

    sourcePixels = NULL;
    baseWidth = GStextureGetXsize(base);
    baseHeight = GStextureGetYsize(base);
    texture = GStextureCreate(baseWidth, baseHeight, GStextureGetFormat(base), GStextureGetTlutFormat(base),
                              GStextureGetMiplevels(base));
    outputPixels = GStextureLockImage(texture, 0);
    if (outputPixels == NULL) {
        goto fail;
    }
    sourcePixels = GStextureLockImage(base, 0);
    if (sourcePixels == NULL) {
        goto fail;
    }

    pixelCount = baseWidth * baseHeight;
    size = pixelCount * 2;
    memcpy(outputPixels, sourcePixels, size);
    DCFlushRange(outputPixels, size);
    GStextureUnlockImage(base);

    GStextureConvertFromHW(texture);
    GStextureConvertFromHW(spotTex);
    sourcePixels = GStextureLockImage(spotTex, 0);
    if (sourcePixels == NULL) {
        goto fail;
    }

    spotWidth = GStextureGetXsize(spotTex);
    spotHeight = GStextureGetYsize(spotTex);
    if (spotWidth > (baseWidth >> 2) || spotHeight > (baseHeight >> 2)) {
        goto fail;
    }

    lastOutputPixel = outputPixels + (pixelCount - 1);
    for (spot = 0; spot < 4; spot++) {
        x = (s32)(3.4f * (s16)((s16)(seed & 0xF) - 8));
        y = (s32)(3.4f * (s16)((s16)((seed >> 4) & 0xF) - 8));
        seed >>= 8;
        y += gPachiruCoords[spot][1];
        x += gPachiruCoords[spot][0];
        startPixel = (s16)(x + y * baseWidth);
        for (row = 0; row < spotHeight; row++) {
            sourceIndex = row * spotWidth;
            outputIndex = startPixel + row * baseWidth;
            if (outputIndex >= 0) {
                output = outputPixels + outputIndex;
                if (output <= lastOutputPixel) {
                    source = sourcePixels + sourceIndex;
                    for (column = 0; column < spotWidth;) {
                        if (output <= lastOutputPixel && *source > *output) {
                            *output = *source;
                        }
                        column++;
                        output++;
                        source++;
                    }
                }
            }
        }
    }

    GStextureUnlockImage(texture);
    GStextureUnlockImage(spotTex);
    GStextureConvertToHW(spotTex);
    GStextureConvertToHW(texture);
    return texture;

fail:
    GSlogWrite("Failed to create Patchiru texture\n");
    if (outputPixels != NULL) {
        GStextureUnlockImage(texture);
    }
    if (sourcePixels != NULL) {
        GStextureUnlockImage(spotTex);
    }
    if (texture != NULL) {
        GStextureFree(texture);
    }
    return NULL;
}
