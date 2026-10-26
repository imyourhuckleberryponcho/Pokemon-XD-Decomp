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
    u16* srcImage;
    GStexture* texture;
    s16 heightTemp;
    u32 image;
    s32 width;
    s32 height;
    s32 size;
    s32 scratch;

    srcImage = NULL;
    width = (s16)GStextureGetXsize(base);
    heightTemp = (s16)GStextureGetYsize(base);
    height = heightTemp;
    texture = GStextureCreate(width, height, GStextureGetFormat(base), GStextureGetTlutFormat(base),
                              GStextureGetMiplevels(base));
    image = (u32)GStextureLockImage(texture, 0);
    if (image == 0) {
        goto fail;
    }

    srcImage = GStextureLockImage(base, 0);
    if (srcImage == NULL) {
        goto fail;
    }

    size = width * height;
    scratch = size * (s32)sizeof(u16);
    memcpy((void*)image, srcImage, scratch);
    DCFlushRange((void*)image, scratch);
    GStextureUnlockImage(base);

    GStextureConvertFromHW(texture);
    GStextureConvertFromHW(spot);
    srcImage = GStextureLockImage(spot, 0);
    if (srcImage == NULL) {
        goto fail;
    }

    {
        u16* end;
        s16 spotHeight;
        s32 row;
        s32 i;
        s32 x;
        s32 start;
        const u8* coords;
        s32 dstIndex;
        s16 srcIndex;
        s32 y;
        s32 dx;
        s32 dy;

        scratch = (s16)GStextureGetXsize(spot);
        spotHeight = (s16)GStextureGetYsize(spot);
        if (scratch > (width >> 2) || spotHeight > (height >> 2)) {
            goto fail;
        }

        end = (u16*)image + (size - 1);
        i = 0;
        coords = gPachiruCoords[0];
        for (; (s16)i < 4;) {
            dy = (s16)((s16)((seed >> 4) & 0xF) - 8);
            dstIndex = (s16)(seed & 0xF) - 8;
            dx = (s16)dstIndex;
            seed >>= 8;
            y = (s32)(3.4f * (f32)dy) + coords[1];
            x = (s32)(3.4f * (f32)dx);
            dy = y * width;
            x = x + coords[0];
            start = (s16)(x + dy);

            for (row = 0; (s16)row < spotHeight; row++) {
                srcIndex = (s16)(row * scratch);
                dstIndex = (s16)(start + row * width);
                if (dstIndex >= 0) {
                    u16* src;
                    u16* dst;
                    s32 col;

                    dst = (u16*)image + dstIndex;
                    if (dst <= end) {
                        src = srcImage + srcIndex;
                        for (col = 0; (s16)col < scratch;) {
                            if (dst <= end && *src > *dst) {
                                *dst = *src;
                            }
                            col++;
                            dst++;
                            src++;
                        }
                    }
                }
            }
            coords += 2;
            i++;
        }
        GStextureUnlockImage(texture);
        GStextureUnlockImage(spot);
        GStextureConvertToHW(spot);
        GStextureConvertToHW(texture);
        return texture;
    }

fail:
    GSlogWrite("Failed to create Patchiru texture\n");
    if (image != 0) {
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
