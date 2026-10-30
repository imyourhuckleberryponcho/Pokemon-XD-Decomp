#include <dolphin/types.h>
#pragma pool_strings off
#pragma peephole off

enum GSgfxLayerID { GSgfxLayerID0 };
struct tagWINDOW_WORK;
struct tagSPRITE_WORK {
    u8 pad0[0x50];
    s16 x;
    s16 y;
};

struct _DEFINETEXT;
struct _DEFINESHAPE;
struct _DEFINESPRITE;
struct _DEFINEFONT2;
struct _DEFINEMORPHSHAPE;
struct _PLACEOBJECT2;
struct _SHAPERECORD;
struct FLASHMATRIX;
struct FLASHMATRIXF;
struct FLASHCXFORM;

extern "C" {
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
int strcmp(const char*, const char*);
void* operator new(unsigned long);
void* operator new[](unsigned long);
void operator delete(void*);
void operator delete[](void*);
}

extern "C" {
int GSgfxLayerFindByID(int id);
void GSgfxLayerSetActive(int id);
u8 GSgfxVideoGetVsyncRate();
void* GSmemAlloc(u32 size);
void GSmemFree(void* p);
void GSmsgPrint2(int layer, s32 x, s32 y, void* text, s32 msgId);
void GSprimSetBlendMode(s32 mode);
u32 GStextureLoad(void* tex);
u8 flcalcBlend(u8 a, u8 b, f32 t);
s32 flcalcBlendColor(s32 a, s32 b, f32 t);
void flcalcConvFlashMatrix(FLASHMATRIXF* out, FLASHMATRIX* in);
void flcalcCreateCxform(FLASHCXFORM* out, s32 color);
void flcalcMatrixCopy(FLASHMATRIXF* dst, FLASHMATRIXF* src);
void flcalcMatrixScale(FLASHMATRIXF* out, FLASHMATRIXF* in, f32* scale);
void flcalcMatrixTranslate(FLASHMATRIXF* out, FLASHMATRIXF* in, f32* trans);
void flcalcMulCxform(FLASHCXFORM* out, FLASHCXFORM* a, FLASHCXFORM* b);
void flcalcMulMatrixf(FLASHMATRIXF* out, FLASHMATRIXF* a, FLASHMATRIXF* b);
void flcalcUnitCxform(void* cx);
void flcalcUnitMatrix(FLASHMATRIXF* m);
void flcalcUnitMatrix2(void* m);
void msgctrlSetValue(s32 id, s32 value);
u32 timeGetLastFrameTime();
void vectorGraph(u32 a0, void* fills, void* lines, _SHAPERECORD* rec, FLASHMATRIXF* parent, FLASHMATRIXF* mat, FLASHCXFORM* cx, u8 flags);
void vectroGraphSetBlendMode(s32 src, s32 dst);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* s);
}
struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer* layer);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))

struct CharEntry {
    u8 type;
    u8 pad1[3];
    void* data;
};

struct DepthEntry {
    u16 charId;
    u8 pad2[2];
    u8 matrix[0x18];
    f32 ratio;
    u8 cxform[0x10];
    s32 clipDepth;
    u8* place;
    u16* names;
    u8 flags;
    u8 pad3D[3];
};

struct SpriteTab {
    u16 frames;
    DepthEntry* depth;
};

struct LabelNode {
    u16 frame;
    char* name;
    LabelNode* next;
};

struct FlashMenu {
    s32 pos;
    s32 startPos;
    u8* data;
    s32 frame;
    s16 curDepth;
    s16 pad12;
    s32 inSprite;
    s32 spriteId;
    u16 spriteFrame;
    u8 relocate;
    u8 pad1F;
    s32 drawCount;
    u8 loopFlag;
    u8 stopFlag;
    u8 pad26[2];
    u32 loopStart;
    u32 loopEnd;
    s32 totalFrames;
    s32 userArg;
    CharEntry* dict;
    DepthEntry* depth;
    SpriteTab* sprites;
    u32 curTime;
    f32 fps;
    struct {
        s32 id;
        void* tex;
    } tex[30];
    LabelNode* labels;

    FlashMenu();
    ~FlashMenu();
    void* GetGStexture(long id);
    void Draw(tagWINDOW_WORK* w, tagSPRITE_WORK* s);
    void Update();
    void Init(void* d, unsigned long arg);
    void Release();
    void InitDataPointer();
    void DrawText(_DEFINETEXT* t, FLASHMATRIXF* parent, FLASHMATRIXF* m, FLASHCXFORM* cx, u8 flags);
    void DrawSprite(_DEFINESPRITE* sp, FLASHMATRIXF* parent, FLASHCXFORM* cx, u16 depthIdx, u8 flags);
    void DrawSub(GSgfxLayerID id, tagWINDOW_WORK* w, tagSPRITE_WORK* s);
    u8 ParseTag(unsigned long tag, unsigned long len, bool a, bool b, bool c);
    void ParsePlaceObject2(bool b);
    u16 GetFrameFromLabel(char* name);
    void ParaseTextRecord(_DEFINETEXT* t);
    void ParseDefineFont2Sub(_DEFINEFONT2* f);
    void ParseDefineMorphShapeSub(_DEFINEMORPHSHAPE* m);
    void ParsePlaceObject2Sub(_PLACEOBJECT2* p);
    void ParseDefineShapeSub(_DEFINESHAPE* s);
    void BlendShapeRecord(_SHAPERECORD* out, _SHAPERECORD* a, _SHAPERECORD* b, f32 t);
    u32 GetPlayFrame();
    void SetPlayFrame(unsigned long f);

    inline bool needFix() { return AT(u32, data, 0x14) == 0 && relocate != 0; }
    inline void runTags(u32 frameNo);
    static inline u16 defaultCount(u16& n) {
        if (n == 0) {
            return n = 0x28;
        } else {
            return n;
        }
    }
    inline u8* fixup(u8*& p, u8* base) {
        if (AT(u32, data, 0x14) == 0 && relocate != 0) {
            return p = base + (u32)p;
        } else {
            return p;
        }
    }
    inline void fixPtr(void** p, u8* base) {
        if (needFix()) *p = base + (u32)*p;
    }
};

struct FlashHeader {
    u8 pad0[6];
    u16 frames;
    u8 pad8[0x10];
    u16 numChars;
    u16 numDepth;
};

struct FlTagName {
    s32 id;
    const char* name;
};
static FlTagName _fltagnametable[41] = {
    { 0, "stagEnd" },
    { 1, "stagShowFrame" },
    { 2, "stagDefineShape" },
    { 3, "stagFreeCharacter" },
    { 4, "stagPlaceObject" },
    { 5, "stagRemoveObject" },
    { 6, "stagDefineBits" },
    { 7, "stagDefineButton" },
    { 8, "stagJPEGTables" },
    { 9, "stagSetBackgroundColor" },
    { 0xA, "stagDefineFont" },
    { 0xB, "stagDefineText" },
    { 0xC, "stagDoAction" },
    { 0xD, "stagDefineFontInfo" },
    { 0xE, "stagDefineSound" },
    { 0xE, "stagDefineSound" },
    { 0x11, "stagDefineButtonSound" },
    { 0x12, "stagSoundStreamHead" },
    { 0x13, "stagSoundStreamBlock" },
    { 0x14, "stagDefineBitsLossless" },
    { 0x15, "stagDefineBitsJPEG2" },
    { 0x16, "stagDefineShape2" },
    { 0x17, "stagDefineButtonCxform" },
    { 0x18, "stagProtect" },
    { 0x1A, "stagPlaceObject2" },
    { 0x1C, "stagRemoveObject2" },
    { 0x20, "stagDefineShape3" },
    { 0x21, "stagDefineText2" },
    { 0x22, "stagDefineButton2" },
    { 0x23, "stagDefineBitsJPEG3" },
    { 0x24, "stagDefineBitsLossless2" },
    { 0x25, "stagDefineEditText" },
    { 0x27, "stagDefineSprite" },
    { 0x28, "stagNameCharacter" },
    { 0x2B, "stagFrameLabel" },
    { 0x2D, "stagSoundStreamHead2" },
    { 0x2E, "stagDefineMorphShape" },
    { 0x30, "stagDefineFont2" },
    { 0x38, "stagExportAssets" },
    { 0x39, "stagImportAssets" },
    { -1, 0 },
};

static u8 _drawflag = 1;

void* FlashMenu::GetGStexture(long id) {
    for (int i = 0; i < 30; i++) {
        if (tex[i].id == id) return tex[i].tex;
    }
    return 0;
}

FlashMenu::~FlashMenu() {}

FlashMenu::FlashMenu() {
    curDepth = 0;
    relocate = 0;
    drawCount = 0;
}

inline void FlashMenu::runTags(u32 frameNo) {
    if (AT(u16, data, 6) > frameNo) {
        pos = startPos;
        frame = frameNo;
        inSprite = 0;
        u8* p = data + pos;
        while (ParseTag(AT(u32, p, 0), AT(u32, p, 4), false, false, false) == 0) {
            p = data + pos;
        }
    }
}

void FlashMenu::Draw(tagWINDOW_WORK* w, tagSPRITE_WORK* s) {
    GSgfxLayerID layer;
    int i;
    u32 rate;
    u32 dt;
    u32 next;
    FlashHeader* hdr;
    DepthEntry* d;
    if (dict != 0) {
        layer = (GSgfxLayerID)winSpriteGetLayerID(w, s);
        GSgfxLayerSetActive(layer);
        GSgfxLayerFindByID(layer);
        DrawSub(layer, w, s);
        next = curTime;
        if (stopFlag == 0) {
            rate = GSgfxVideoGetVsyncRate();
            dt = timeGetLastFrameTime();
            if (dt >= 10) dt = 1;
            if (dt == 0) fps = (f32)rate;
            else fps = (f32)rate / (f32)dt;
            next += dt;
            if (next > loopEnd) {
                if (loopFlag != 0) {
                    next = loopStart;
                    d = depth;
                    hdr = (FlashHeader*)data;
                    for (i = 0; i < hdr->numDepth; d++, i++) {
                        d->ratio = 0.0f;
                        d->clipDepth = 0;
                        d->place = 0;
                        flcalcUnitCxform(d->cxform);
                    }
                } else {
                    next = loopEnd;
                }
            }
            curTime = next;
        }
        GSgfxLayerSetActive(7);
    }
}

#pragma push
#pragma optimize_for_size on
void FlashMenu::Update() {
    DepthEntry* d;
    SpriteTab* st;
    FlashHeader* hdr;
    int i;
    int j;
    s32 off;
    if (dict != 0) {
        d = depth;
        for (i = 0, hdr = (FlashHeader*)data; i < hdr->numDepth; i++, d++) {
            d->clipDepth = 0;
            d->place = 0;
            d->charId = 0;
            d->ratio = 0.0f;
            flcalcUnitCxform(d->cxform);
            flcalcUnitMatrix2(d->matrix);
        }
        for (i = off = 0; i < hdr->numChars; off += 8, i++) {
            for (int j_loop = 0; j_loop < hdr->numDepth; j_loop++) {
                st = (SpriteTab*)((u8*)sprites + off);
                st->depth[j_loop].charId = 0;
                st->depth[j_loop].ratio = 0.0f;
                st->depth[j_loop].clipDepth = 0;
                st->depth[j_loop].place = 0;
                st->depth[j_loop].flags = 0;
                flcalcUnitMatrix2(st->depth[j_loop].matrix);
                flcalcUnitCxform(st->depth[j_loop].cxform);
            }
        }
        GSprimSetup2DRender(0);
        GSprimSetBlendMode(1);
        runTags(curTime);
        drawCount = 0;
    }
}
#pragma pop

void FlashMenu::Init(void* d, unsigned long arg) {
    int j;
    u16 nDepth;
    FlashHeader* hdr;
    u8* p;
    s32 i;
    u16 nChars;
    s32 depthBytes;
    GSgfxLayer* layer = (GSgfxLayer*)GSgfxLayerFindByID(7);
    userArg = arg;
    GSprimSetup2DRender(layer);
    GSprimSetBlendMode(1);
    dict = (CharEntry*)GSmemAlloc(0x640);
    nChars = defaultCount(AT(u16, d, 0x18));
    nDepth = defaultCount(AT(u16, (u16)d, 0x1A));
    sprites = (SpriteTab*)GSmemAlloc(((nChars * 8) + 0x1F) & 0xFFFFFFE0);
    depthBytes = nChars;
    depthBytes *= 2;
    for (i = 0; i < nChars; i++) {
        sprites[i].depth = 0;
        sprites[i].depth = (DepthEntry*)new u8[nDepth << 6];
        for (j = 0; j < nDepth; j++) {
            sprites[i].depth[j].names = 0;
            sprites[i].depth[j].names = (u16*)new u8[depthBytes];
        }
    }
    depth = (DepthEntry*)GSmemAlloc(((nDepth << 6) + 0x1F) & 0xFFFFFFE0);
    for (j = 0; j < nDepth; j++) {
        u32 j_c = j;
        depth[j_c].names = 0;
        depth[j_c].names = (u16*)new u8[depthBytes];
    }
    labels = 0;
    pos = 0x30;
    frame = 0;
    relocate = 0;
    for (i = 0; i < nChars; i++) sprites[i].frames = 0;
    startPos = pos;
    data = (u8*)d;
    hdr = (FlashHeader*)data;
    p = (u8*)hdr + pos;
    inSprite = 0;
    frame = 0;
    relocate = 1;
    for (i = 0; i < 30; i++) {
        tex[i].id = 0;
        tex[i].tex = 0;
    }
    InitDataPointer();
    curTime = 0;
    fps = 0.0f;
    for (u32 i_loop = 0; i_loop < hdr->numDepth; i_loop++) {
        for (j = 0; j < hdr->numChars; j++) {
            u8 j_c = j;
            depth[i_loop].names[j_c] = 0;
        }
    }
    while (1) {
        FlTagName* t = _fltagnametable;
        while (t->id != (s32)AT(u32, p, 0) && t->id >= 0) t++;
        if (ParseTag(AT(u32, p, 0), AT(u32, p, 4), true, false, true) == 0) {
            p = data + pos;
            continue;
        }
        break;
    }
    if (relocate != 0 && AT(void*, hdr, 0x14) == 0) {
        AT(void*, hdr, 0x14) = data;
    }
    loopStart = 0;
    loopEnd = frame - 1;
    loopFlag = 0;
    stopFlag = 0;
    totalFrames = frame;
}

void FlashMenu::Release() {
    FlashHeader* hdr = (FlashHeader*)data;
    if (dict != 0) {
        if (dict != 0) GSmemFree(dict);
        dict = 0;
    }
    for (u16 i = 0; i < hdr->numChars; i++) {
        if (sprites[i].depth != 0) {
            for (u16 j = 0; j < hdr->numDepth; j++) {
                if (sprites[i].depth[j].names != 0) {
                    delete[] sprites[i].depth[j].names;
                    sprites[i].depth[j].names = 0;
                }
            }
            delete[] sprites[i].depth;
            sprites[i].depth = 0;
        }
    }
    if (sprites != 0) {
        if (sprites != 0) GSmemFree(sprites);
        sprites = 0;
    }
    for (u16 i = 0; i < hdr->numDepth; i++) {
        if (depth[i].names != 0) {
            delete[] depth[i].names;
            depth[i].names = 0;
        }
    }
    if (depth != 0) {
        if (depth != 0) GSmemFree(depth);
        depth = 0;
    }
    LabelNode* n = labels;
    do {
        if (n != 0) {
            LabelNode* next = n->next;
            n = n->next;
            delete n;
        }
    } while (n != 0);
}

void FlashMenu::InitDataPointer() {
    SpriteTab* st;
    int j;
    DepthEntry* d;
    FlashHeader* hdr;
    s32 i;
    CharEntry* c;
    s32 off;
    c = dict;
    d = depth;
    hdr = (FlashHeader*)data;
    i = 0;
    while (i < 0xC8) {
        c->type = 0;
        c->data = 0;
        c++;
        i++;
    }
    for (i = 0; i < hdr->numDepth; d++, i++) {
        d->clipDepth = 0;
        d->place = 0;
        d->charId = 0;
        d->ratio = 0.0f;
        d->flags = 0;
        flcalcUnitCxform(d->cxform);
        flcalcUnitMatrix2(d->matrix);
    }
    for (i = 0, off = 0; i < hdr->numChars; i++, off += 8) {
        for (j = 0; j < hdr->numDepth; j++) {
            st = (SpriteTab*)((u8*)sprites + off);
            st->depth[j].charId = 0;
            st->depth[j].ratio = 0.0f;
            st->depth[j].clipDepth = 0;
            st->depth[j].place = 0;
            st->depth[j].flags = 0;
            flcalcUnitMatrix2(st->depth[j].matrix);
            flcalcUnitCxform(st->depth[j].cxform);
        }
    }
}

void FlashMenu::DrawText(_DEFINETEXT* t, FLASHMATRIXF* parent, FLASHMATRIXF* m, FLASHCXFORM* cx, u8 flags) {
    u8* font;
    u8 mat[0x18];
    u8 mat2[0x18];
    u8 cxf[0x10];
    f32 scale[2];
    f32 trans[2];
    u8* rec = AT(u8*, t, 0x2C);
    u8* r;
    u16 fontId = 0;
    s16 x = 0;
    s16 y = 0;
    u16 height = 0;
    s32 color = 0;
    s32 advance = 0;
    flcalcMatrixCopy((FLASHMATRIXF*)mat, m);
    while (1) {
        switch (rec[0]) {
        case 0:
            break;
        case 1: {
            u8* r = AT(u8*, rec, 4);
            u8 f = r[0];
            if ((f & 8) != 0) fontId = AT(u16, r, 2);
            if ((f & 4) != 0) color = AT(s32, r, 0xC);
            if ((f & 1) != 0) x = AT(s16, r, 4) / 20;
            if ((f & 2) != 0) y = AT(s16, (u16)r, 6) / 20;
            if ((f & 8) != 0) height = AT(u16, r, 8) / 20;
            break;
        }
        case 2: {
            r = AT(u8*, rec, 4);
            font = (u8*)dict[fontId].data;
            if (font != 0) {
                u8* glyph = AT(u8*, r, 4);
                for (int i = 0; i < AT(s32, r, 0); glyph += 8, i++) {
                    flcalcCreateCxform((FLASHCXFORM*)cxf, color);
                    flcalcMulCxform((FLASHCXFORM*)cxf, (FLASHCXFORM*)cxf, cx);
                    s32 adv = AT(s32, glyph, 4);
                    flcalcMatrixCopy((FLASHMATRIXF*)mat, m);
                    if (parent != 0) flcalcMatrixCopy((FLASHMATRIXF*)mat2, parent);
                    else flcalcUnitMatrix((FLASHMATRIXF*)mat2);
                    f32 sc = (f32)adv;
                    sc *= 0.0009765625f;
                    scale[1] = sc;
                    scale[0] = sc;
                    flcalcMatrixScale((FLASHMATRIXF*)mat, (FLASHMATRIXF*)mat, scale);
                    trans[0] = (f32)x;
                    trans[1] = (f32)y;
                    flcalcMatrixTranslate((FLASHMATRIXF*)mat, (FLASHMATRIXF*)mat, trans);
                    s32 cur = advance;
                    AT(f32, mat, 0x10) += (f32)cur;
                    advance += height;
                    u8* shape = AT(u8**, font, 0x1C)[AT(u16, glyph, 0)];
                    if (AT(u32, AT(u8*, shape, 0x18), 8) != 0) {
                        vectorGraph(userArg, shape + 4, shape + 0xC, AT(_SHAPERECORD*, shape, 0x18), (FLASHMATRIXF*)mat2, (FLASHMATRIXF*)mat, (FLASHCXFORM*)cxf, (u16)flags);
                    }
                }
            }
            break;
        }
        }
        u8* next = AT(u8*, rec, 8);
        if (next == 0) break;
        rec = next;
    }
}

void FlashMenu::DrawSprite(_DEFINESPRITE* sp, FLASHMATRIXF* parent, FLASHCXFORM* cx, u16 depthIdx, u8 flags) {
    enum TsE { TsE0 };
    u8 mat[0x18];
    u8 cxf[0x10];
    s32 sp38[1];
    u8 hdrBlend[0x1C];
    u8* hdr = data;
    u32 di = 0;
    s32 off = 0;
    u8* ms;
    u8* recs;
    u8 mat2[0x18];
    while (di < AT(u16, (u16)hdr, 0x1A)) {
        DepthEntry* e = (DepthEntry*)((u8*)sprites[*(u16*)sp].depth + off);
        if (e->place != 0) {
            CharEntry* ch = &dict[e->charId];
            flcalcConvFlashMatrix((FLASHMATRIXF*)mat, (FLASHMATRIX*)e->matrix);
            curDepth = di;
            f32 ratio = e->ratio;
            flcalcMulMatrixf((FLASHMATRIXF*)mat2, (FLASHMATRIXF*)mat, parent);
            flcalcMulCxform((FLASHCXFORM*)cxf, (FLASHCXFORM*)e->cxform, cx);
            e->flags = flags | e->flags | *e->place;
            if ((ch->type & 1) != 0) {
                enum TsE fl = (enum TsE)(e->flags);
                ms = (u8*)ch->data;
                memset(hdrBlend, 0, 0x1C);
                recs = AT(u8*, ms, 0xC);
                s32 ro = 0;
                s32 so = 0;
                for (int k = 0; k < AT(s32, ms, 8); k++, ro += 0xD4, so += 0x80) {
                    u8* r = recs + ro;
                    if (r[0] == 0) {
                        AT(s32, AT(u8*, hdrBlend, 4), so + 4) = flcalcBlendColor(AT(s32, r, 4), AT(s32, r, 8), ratio);
                    } else if ((r[0] & 0x10) != 0) {
                        u8* src = r + 0x3C;
                        u8* dst = AT(u8*, hdrBlend, 4) + so + 0x20;
                        for (int g = 0; g < r[0x3C]; g++, src += 0xC, dst += 8) {
                            dst[4] = flcalcBlend(src[4], src[5], ratio);
                            AT(s32, dst, 8) = flcalcBlendColor(AT(s32, src, 8), AT(s32, src, 0xC), ratio);
                        }
                    }
                }
                BlendShapeRecord(AT(_SHAPERECORD*, AT(u8*, ms, 0x30), 0x18), AT(_SHAPERECORD*, AT(u8*, ms, 0x28), 0x18),
                                 AT(_SHAPERECORD*, AT(u8*, ms, 0x2C), 0x18), ratio);
                vectorGraph(userArg, hdrBlend, hdrBlend + 8, AT(_SHAPERECORD*, AT(u8*, ms, 0x30), 0x18), parent, (FLASHMATRIXF*)mat, (FLASHCXFORM*)cxf, (u16)fl);
            }
            if ((ch->type & 4) != 0) {
                u16* child = (u16*)ch->data;
                if (child != (u16*)sp) {
                    runTags(curTime);
                    DepthEntry* e2 = (DepthEntry*)((u8*)sprites[*(u16*)sp].depth + off);
                    flcalcConvFlashMatrix((FLASHMATRIXF*)mat, (FLASHMATRIX*)e2->matrix);
                    flcalcMulMatrixf((FLASHMATRIXF*)mat2, (FLASHMATRIXF*)mat, parent);
                    flcalcMulCxform((FLASHCXFORM*)cxf, (FLASHCXFORM*)e2->cxform, cx);
                    DrawSprite((_DEFINESPRITE*)child, (FLASHMATRIXF*)mat2, (FLASHCXFORM*)cxf, di, e->flags);
                }
            }
            if ((ch->type & 2) != 0) {
                u8* shape = (u8*)ch->data;
                if (_drawflag != 0) {
                    vectorGraph(userArg, shape + 4, shape + 0xC, AT(_SHAPERECORD*, shape, 0x18), parent, (FLASHMATRIXF*)mat, (FLASHCXFORM*)cxf, e->flags);
                }
                drawCount++;
            }
            if ((ch->type & 0x10) != 0) {
                u8* et = (u8*)ch->data;
                s32 cmpv = (u16)AT(u32, et, 0x1C);
                if (cmpv != 0) {
                    f32 tmp[12];
                    s32 text = AT(s32, et, 4);
                    u16 kind = AT(u16, et, 0xE) / 20;
                    if (parent != 0) flcalcMulMatrixf((FLASHMATRIXF*)tmp, (FLASHMATRIXF*)mat, parent);
                    else flcalcMatrixCopy((FLASHMATRIXF*)tmp, (FLASHMATRIXF*)mat);
                    u16 tmp1 = AT(s32, (u16)et, 0x1C);
                    msgctrlSetValue(0x37, tmp1);
                    f32* tf = (f32*)tmp;
                    switch (kind) {
                    case 13:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4278);
                        break;
                    case 22:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4275);
                        break;
                    default:
                    case 18:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4276);
                        break;
                    }
                }
            }
            if ((ch->type & 0x20) != 0) {
                DrawText((_DEFINETEXT*)ch->data, parent, (FLASHMATRIXF*)mat, cx, e->flags);
            }
        }
        off += 0x40;
        di++;
    }
    u16 id = *(u16*)sp;
    u16 limit = sprites[id].frames;
    if (stopFlag == 0 && limit != 0) {
        u16 cur = AT(u16*, depth[depthIdx].names, 0)[id];
        u32 dt = timeGetLastFrameTime();
        GSgfxVideoGetVsyncRate();
        u16 next = cur + dt;
        if (next >= limit) {
            next = 0;
            DepthEntry* e = sprites[id].depth;
            for (u32 i = 0; i < AT(u16, data, 0x1A); e++, i++) {
                e->ratio = 0.0f;
                e->clipDepth = 0;
                e->place = 0;
                flcalcUnitCxform(e->cxform);
            }
        }
        depth[depthIdx].names[id] = next;
    }
}

void FlashMenu::DrawSub(GSgfxLayerID id, tagWINDOW_WORK* w, tagSPRITE_WORK* s) {
    u8 hdrBlend[0x1C];
    u8 mat[0x18];
    u8 cxf[0x10];
    u8* ms;
    u8* hdr = data;
    u8* r;
    vectroGraphSetBlendMode(4, 5);
    s32 off = 0;
    for (u16 di = 0; di < AT(u16, hdr, 0x1A); off += 0x40, di++) {
        DepthEntry* e = (DepthEntry*)((u8*)depth + off);
        if (e->place != 0) {
            curDepth = di;
            CharEntry* ch = &dict[e->charId];
            flcalcConvFlashMatrix((FLASHMATRIXF*)mat, (FLASHMATRIX*)e->matrix);
            e->flags = e->flags | *e->place;
            AT(f32, mat, 0x10) += (f32)s->x;
            AT(f32, mat, 0x14) += (f32)s->y;
            if ((e->flags & 0x40) != 0) vectroGraphSetBlendMode(2, 5);
            if ((ch->type & 1) != 0) {
                u8 fl = e->flags;
                f32 ratio = e->ratio;
                ms = (u8*)ch->data;
                memset(hdrBlend, 0, 0x1C);
                u8* recs = AT(u8*, ms, 0xC);
                volatile s32 ro = 0;
                int k;
                s32 so;
                for (k = 0, so = 0; k < AT(s32, ms, 8); k++, ro += 0xD4, so += 0x80) {
                    r = recs + ro;
                    if (r[0] == 0) {
                        AT(s32, AT(u8*, hdrBlend, 4), so + 4) = flcalcBlendColor(AT(s32, r, 4), AT(s32, r, 8), ratio);
                    } else if ((r[0] & 0x10) != 0) {
                        volatile u8* src = r + 0x3C;
                        u8* dst = AT(u8*, hdrBlend, 4) + so + 0x20;
                        for (int g = 0; g < r[0x3C]; g++, src += 0xC, dst += 8) {
                            dst[4] = flcalcBlend(src[4], src[5], ratio);
                            AT(s32, dst, 8) = flcalcBlendColor(AT(s32, src, 8), AT(s32, src, 0xC), ratio);
                        }
                    }
                }
                BlendShapeRecord(AT(_SHAPERECORD*, AT(u8*, ms, 0x30), 0x18), AT(_SHAPERECORD*, AT(u8*, ms, 0x28), 0x18),
                                 AT(_SHAPERECORD*, AT(u8*, ms, 0x2C), 0x18), (u16)ratio);
                vectorGraph(userArg, hdrBlend, hdrBlend + 8, AT(_SHAPERECORD*, AT(u8*, ms, 0x30), 0x18), 0, (FLASHMATRIXF*)mat, (FLASHCXFORM*)e->cxform, fl);
            }
            if ((ch->type & 4) != 0) {
                u16* child = (u16*)ch->data;
                runTags(curTime);
                DrawSprite((_DEFINESPRITE*)child, (FLASHMATRIXF*)mat, (FLASHCXFORM*)e->cxform, di, e->flags);
            }
            if ((ch->type & 2) != 0) {
                u8* shape = (u8*)ch->data;
                if (_drawflag != 0) {
                    vectorGraph(userArg, shape + 4, shape + 0xC, AT(_SHAPERECORD*, shape, 0x18), 0, (FLASHMATRIXF*)mat, (FLASHCXFORM*)e->cxform, e->flags);
                }
                drawCount++;
            }
            if ((ch->type & 0x10) != 0) {
                u8* et = (u8*)ch->data;
                s32 cmpv = AT(u32, et, 0x1C);
                if (cmpv != 0) {
                    f32* tf = (f32*)mat;
                    s32 text = AT(s32, et, 4);
                    u16 kind = AT(u16, et, 0xE) / 20;
                    u16 tmp1 = AT(s32, (u16)et, 0x1C);
                    msgctrlSetValue(0x37, (u8)tmp1);
                    switch (kind) {
                    case 13:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4278);
                        break;
                    case 22:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4275);
                        break;
                    default:
                    case 18:
                        GSmsgPrint2(7, (s32)tf[4], (s32)tf[5], (void*)text, 0x4276);
                        break;
                    }
                }
            }
            if ((ch->type & 0x20) != 0) {
                DrawText((_DEFINETEXT*)ch->data, 0, (FLASHMATRIXF*)mat, (FLASHCXFORM*)e->cxform, e->flags);
            }
        }
    }
}

u8 FlashMenu::ParseTag(unsigned long tag, unsigned long len, bool a, bool b, bool c) {
    s32 sid;
    u8* t;
    u8* x;
    u8 done = 0;
    if (tag != 0) pos += 8;
    switch (tag) {
    case 0:
        loopStart = 0;
        inSprite--;
        if (inSprite < 0) done = 1;
        else pos += 8;
        break;
    case 1: {
        s32 v = AT(s32, data, pos);
        if (c != 0 && inSprite == 0) frame++;
        if (inSprite != 0) {
            spriteFrame = (u16)v;
        } else if (a == 0 && (u16)v > curTime) {
            done = 1;
        }
        break;
    }
    case 2:
        if (c != 0) ParseDefineShapeSub((_DEFINESHAPE*)this);
        break;
    case 11: {
        u16* t = (u16*)(data + pos);
        s32 o = *t * 8;
        dict[*t].type = 0x20;
        dict[*t].data = t;
        ParaseTextRecord((_DEFINETEXT*)t);
        break;
    }
    case 12: {
        u8** t = (u8**)(data + pos);
        u8* r;
        if (AT(u32, data, 0x14) == 0 && relocate != 0) {
            r = (u8*)t + (u32)*t;
            *t = r;
        } else {
            r = *t;
        }
        while (r != 0) {
            x = AT(u8*, (u16)r, 4);
            if (x != 0 && AT(u32, data, 0x14) == 0 && relocate != 0) AT(u8*, r, 4) = (u8*)t + (u32)x;
            u8* n = AT(u8*, r, 8);
            if (n != 0) {
                if (AT(u32, data, 0x14) == 0 && relocate != 0) {
                    r = (u8*)t + (u32)n;
                    AT(u8*, r, 8) = r;
                } else {
                    r = AT(u8*, r, 8);
                }
            } else {
                r = n;
            }
        }
        break;
    }
    case 20: {
        u8* t = data + ((pos + 0x1F) & 0xFFFFFFE0);
        if (c != 0) {
            void* tx;
            if (AT(u32, data, 0x14) == 0 && relocate != 0) {
                tx = t + AT(u32, t, 0x10);
                AT(void*, t, 0x10) = tx;
            } else {
                tx = AT(void*, t, 0x10);
            }
            if (c != 0 && GStextureLoad(tx) != 0) {
                u16 id = AT(u16, t, 2);
                for (int i = 0; i < 30; i++) {
                    if (tex[i].id != id) {
                        if (tex[i].id == 0) {
                            tex[i].id = id;
                            tex[i].tex = tx;
                        } else {
                            continue;
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    case 22:
        if (c != 0) ParseDefineShapeSub((_DEFINESHAPE*)this);
        break;
    case 26:
        ParsePlaceObject2(c);
        break;
    case 28: {
        u16 v = AT(u16, data, pos);
        if (inSprite != 0) {
            sid = spriteId;
            if (spriteFrame <= AT(u16*, depth[curDepth].names, 0)[sid]) {
                DepthEntry* e = (DepthEntry*)((u8*)sprites[sid].depth + (v << 6));
                e->clipDepth = 0;
                e->place = 0;
            }
        } else {
            depth[v].clipDepth = 0;
            depth[v].place = 0;
        }
        break;
    }
    case 32:
        if (c != 0) ParseDefineShapeSub((_DEFINESHAPE*)this);
        break;
    case 33: {
        u16* t = (u16*)(data + pos);
        s32 o = *t * 8;
        dict[*t].type = 0x20;
        dict[*t].data = t;
        ParaseTextRecord((_DEFINETEXT*)t);
        break;
    }
    case 36: {
        t = data + ((pos + 0x1F) & 0xFFFFFFE0);
        if (c != 0) {
            void* tx;
            if (AT(u32, data, 0x14) == 0 && relocate != 0) {
                tx = t + AT(u32, t, 0x10);
                AT(void*, t, 0x10) = tx;
            } else {
                tx = AT(void*, t, 0x10);
            }
            if (c != 0 && GStextureLoad(tx) != 0) {
                u16 id = AT(u16, t, 2);
                for (int i = 0; i < 30; i++) {
                    if (tex[i].id != id) {
                        if (tex[i].id == 0) {
                            tex[i].id = id;
                            tex[i].tex = tx;
                        } else {
                            continue;
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    case 37: {
        u8* t = data + pos;
        s32 o = AT(u16, t, 8) * 8;
        dict[AT(u16, t, 8)].type = 0x10;
        dict[AT(u16, t, 8)].data = t;
        if ((AT(u16, t, 0xA) & 0x80) != 0) {
            u16* s;
            if (AT(u32, data, 0x14) == 0 && relocate != 0) {
                s = (u16*)(t + AT(u32, t, 0x1C));
                AT(u16*, t, 0x1C) = s;
            } else {
                s = AT(u16*, t, 0x1C);
            }
            while (*s != 0) s += 2;
        }
        break;
    }
    case 39: {
        u8* t = data + pos;
        dict[AT(u16, t, 0)].type = 4;
        dict[AT(u16, t, 0)].data = t;
        inSprite++;
        spriteId = AT(u16, t, 0);
        sprites[spriteId].frames = AT(u16, t, 2);
        break;
    }
    case 43: {
        u8** t = (u8**)(data + pos);
        if (AT(u32, data, 0x14) == 0 && relocate != 0) *t += (u32)t;
        if (c != 0) {
            LabelNode* n = labels;
            if (n != 0) {
                while (n->next != 0) n = n->next;
                LabelNode* nn = new LabelNode;
                n->next->name = (char*)*t;
                n->next->frame = frame;
                n->next = nn->next;
            } else {
                LabelNode* nn = new LabelNode;
                if (labels < nn) labels = nn;
                labels->frame = frame;
                labels->name = (char*)*t;
            }
        }
        break;
    }
    case 48:
        ParseDefineFont2Sub((_DEFINEFONT2*)(data + pos));
        break;
    case 46:
        ParseDefineMorphShapeSub((_DEFINEMORPHSHAPE*)(data + pos));
        break;
    }
    pos += len;
    return done;
}

void FlashMenu::ParsePlaceObject2(bool b) {
    ParsePlaceObject2Sub((_PLACEOBJECT2*)(data + pos));
}

u16 FlashMenu::GetFrameFromLabel(char* name) {
    LabelNode* n = labels;
    if (n != 0) {
        LabelNode* c = n;
        for (;;) {
            if (c == 0) break;
            if (strcmp(name, c->name) == 0) return c->frame;
            c = c->next;
        }
    }
    return 0;
}

void FlashMenu::ParaseTextRecord(_DEFINETEXT* t) {
    u8* rec = fixup(AT(u8*, t, 0x2C), (u8*)t);
    while (1) {
        switch (rec[0]) {
        case 0:
            break;
        case 1:
            if (AT(u32, data, 0x14) == 0 && relocate != 0) AT(u8*, rec, 4) = (u8*)t + AT(u32, rec, 4);
            break;
        case 2: {
            u8* r = fixup(AT(u8*, rec, 4), (u8*)t);
            if (AT(u32, data, 0x14) == 0 && relocate != 0) AT(u8*, r, 4) = (u8*)t + AT(u32, r, 4);
            for (int i = 0; i < r[0]; i++) {}
            break;
        }
        }
        u8* n = AT(u8*, (s32)rec, 8);
        if (n == 0) break;
        rec = fixup(AT(u8*, rec, 8), (u8*)t);
    }
}

#pragma push
#pragma peephole on
void FlashMenu::ParseDefineFont2Sub(_DEFINEFONT2* f) {
    u16 n = AT(u16, f, 4);
    s32 o = AT(u16, f, 0) * 8;
    dict[AT(u16, f, 0)].type = 8;
    dict[AT(u16, f, 0)].data = f;
    if (n != 0) {
        if (AT(u32, f, 0x14) != 0) {
            for (int i = 0; i < n; i++) {}
        }
        u8** glyphs;
        if (needFix()) {
            glyphs = (u8**)((u8*)f + AT(u32, f, 0x1C));
            AT(u8***, f, 0x1C) = (u8***)glyphs;
        } else {
            glyphs = AT(u8**, f, 0x1C);
        }
        for (int i = 0; i < n; glyphs++, i++) {
            u8* g;
            if (needFix()) {
                g = (u8*)f + (u32)*glyphs;
                *glyphs = g;
            } else {
                g = *glyphs;
            }
            ParseDefineShapeSub((_DEFINESHAPE*)g);
        }
        u8* t = AT(u8*, f, 0x10);
        if (t != 0) {
            if (needFix()) AT(u8*, f, 0x10) = (u8*)f + (u32)t;
            for (int i = 0; i < n; i++) {}
        }
    }
}
#pragma pop

void FlashMenu::ParseDefineMorphShapeSub(_DEFINEMORPHSHAPE* m) {
    if (AT(u32, m, 8) != 0) {
        s32 ro = 0;
        for (int k = 0; k < (s32)AT(u32, m, 8); k++, ro += 0xD4) {
            u8* base;
            if (needFix()) {
                base = (u8*)m + AT(u32, m, 0xC);
                AT(u8*, m, 0xC) = base;
            } else {
                base = AT(u8*, m, 0xC);
            }
            u8* r = base + ro;
            if ((r[0] & 0x10) != 0) {
                for (int i = 0; i < (u8)(r[0x3C]); i++) {}
            }
        }
    }
    if (needFix()) AT(u8*, m, 0x14) = (u8*)m + AT(u32, m, 0x14);
    u32 cnt = AT(u32, m, 0x10);
    if (cnt != 0) {
        for (s32 i = 0; i < (s32)cnt; i++) {}
    }
    if (needFix()) AT(u8*, m, 0x1C) = (u8*)m + AT(u32, m, 0x1C);
    if (needFix()) AT(u8*, m, 0x24) = (u8*)m + AT(u32, m, 0x24);
    u8* s;
    if (needFix()) {
        s = (u8*)m + AT(u32, m, 0x28);
        AT(u8*, m, 0x28) = s;
    } else {
        s = AT(u8*, m, 0x28);
    }
    ParseDefineShapeSub((_DEFINESHAPE*)s);
    if (needFix()) {
        s = (u8*)m + AT(u32, m, 0x2C);
        AT(u8*, m, 0x2C) = s;
    } else {
        s = AT(u8*, m, 0x2C);
    }
    ParseDefineShapeSub((_DEFINESHAPE*)s);
    if (needFix()) {
        s = (u8*)m + AT(u32, m, 0x30);
        AT(u8*, m, 0x30) = s;
    } else {
        s = AT(u8*, m, 0x30);
    }
    ParseDefineShapeSub((_DEFINESHAPE*)s);
    dict[AT(u16, m, 0)].type = 1;
    dict[AT(u16, m, 0)].data = m;
}

void FlashMenu::ParsePlaceObject2Sub(_PLACEOBJECT2* p) {
    s32 sid;
    s32 dd;
    u8 fl = AT(u8, p, 0);
    s32 d = AT(u16, p, 8);
    if (inSprite != 0) {
        sid = spriteId;
        if (spriteFrame <= AT(u16*, depth[curDepth].names, 0)[(u16)sid]) {
            DepthEntry* e = (DepthEntry*)((u8*)sprites[sid].depth + (d << 6));
            e->clipDepth = 0;
            e->place = (u8*)p;
        }
    } else {
        depth[d].clipDepth = 0;
        depth[d].place = (u8*)p;
    }
    if ((fl & 2) != 0) {
        s32 ch = AT(u16, p, 4);
        s32 dd = AT(u16, p, 8);
        if (inSprite != 0) {
            s32 sid = spriteId;
            sprites[sid].depth[dd].charId = spriteFrame > AT(u16*, depth[curDepth].names, 0)[(u16)sid] ? sprites[sid].depth[dd].charId : ch;
        } else {
            depth[dd].charId = (u16)ch;
        }
    }
    if ((fl & 4) != 0) {
        s32 dd = AT(u16, p, 8);
        if (inSprite != 0) {
            sid = spriteId;
            if (spriteFrame <= AT(u16*, depth[curDepth].names, 0)[(u16)sid]) {
                memcpy(sprites[sid].depth[dd].matrix, (u8*)p + 0xC, 0x18);
            }
        } else {
            memcpy(depth[dd].matrix, (u8*)p + 0xC, 0x18);
        }
    }
    if ((fl & 8) != 0) {
        s32 dd = AT(u16, p, 8);
        if (inSprite != 0) {
            sid = spriteId;
            if (spriteFrame <= AT(u16*, depth[curDepth].names, 0)[sid]) {
                memcpy(sprites[sid].depth[dd].cxform, (u8*)p + 0x24, 0x10);
            }
        } else {
            memcpy(depth[dd].cxform, (u8*)p + 0x24, 0x10);
        }
    }
    if ((fl & 0x10) != 0) {
        u32 ratio = AT(u32, p, 0x34);
        dd = AT(u16, p, 8);
        if (inSprite != 0) {
            s32 sid = spriteId;
            if (spriteFrame <= AT(u16*, depth[curDepth].names, 0)[(u16)sid]) {
                sprites[sid].depth[dd].ratio = (f32)ratio / 65536.0f;
            }
        } else {
            depth[dd].ratio = (f32)ratio / 65536.0f;
        }
    }
    if ((fl & 0x20) != 0 && needFix()) {
        AT(u8*, p, 0x38) = (u8*)p + AT(u32, p, 0x38);
    }
}

#pragma push
#pragma peephole on
void FlashMenu::ParseDefineShapeSub(_DEFINESHAPE* s) {
    enum TsE { TsE0 };
    int n;
    u8* styles;
    if (needFix()) {
        styles = (u8*)s + AT(u32, s, 8);
        AT(u8*, s, 8) = styles;
    } else {
        styles = AT(u8*, s, 8);
    }
    u8* st = styles;
    for (int i = 0; i < (s32)AT(u32, s, 4); st += 0x80, i++) {
        if ((*styles & 0x10) != 0) {
            u8 n = st[0x20];
            for (int j = 0; j < n; j++) {}
        }
    }
    enum TsE nLines = (enum TsE)(AT(s32, s, 0xC));
    if (needFix()) AT(u8*, s, 0x10) = (u8*)s + AT(u32, s, 0x10);
    for (int i = 0; i < nLines; i++) {}
    u8* rec;
    if (needFix()) {
        rec = (u8*)s + AT(u32, s, 0x18);
        AT(u8*, s, 0x18) = rec;
    } else {
        rec = AT(u8*, s, 0x18);
    }
    dict[AT(u16, s, 0)].type = 2;
    dict[AT(u16, s, 0)].data = s;
    while (1) {
        if (AT(u8*, rec, 8) == 0) {
            break;
        }
        switch (rec[0]) {
        case 0:
            break;
        case 1: {
            u8* d;
            if (needFix()) {
                d = (u8*)s + AT(u32, rec, 4);
                AT(u8*, rec, 4) = d;
            } else {
                d = AT(u8*, rec, 4);
            }
            if ((d[0] & 0x10) != 0) {
                n = AT(s32, d, 0x10);
                if (needFix()) AT(u8*, d, 0x14) = (u8*)s + AT(u32, d, 0x14);
                for (int i = 0; i < n; i++) {}
                int m = AT(s32, d, 0x18);
                if (needFix()) AT(u8*, d, 0x1C) = (u8*)s + AT(u32, d, 0x1C);
                for (int i = 0; i < m; i++) {}
            }
            break;
        }
        case 2: {
            u8* d;
            if (needFix()) {
                d = (u8*)s + AT(u32, rec, 4);
                AT(u8*, rec, 4) = d;
            } else {
                d = AT(u8*, rec, 4);
            }
            if ((u16)AT(s32, d, 4) != 0 && (u16)AT(s32, d, 8) == 0) {}
            break;
        }
        case 3:
            if (needFix()) AT(u8*, rec, 4) = (u8*)s + AT(u32, rec, 4);
            break;
        }
        if (needFix()) {
            u8* n = (u8*)s + AT(u32, rec, 8);
            rec = n;
            AT(u8*, rec, 8) = n;
        } else {
            rec = AT(u8*, rec, 8);
        }
    }
}
#pragma pop

void FlashMenu::BlendShapeRecord(_SHAPERECORD* out, _SHAPERECORD* a, _SHAPERECORD* b, f32 t) {
    u8* pb = (u8*)b;
    u8* pa = (u8*)a;
    u8* po = (u8*)out;
    u8 loop = 1;
    u8 skip = 0;
    do {
        switch (pa[0]) {
        case 0:
            loop = 0;
            break;
        case 1: {
            u8* ra = AT(u8*, pa, 4);
            u8* rb = AT(u8*, pb, 4);
            u8* ro = AT(u8*, po, 4);
            if ((ra[0] & 1) != 0) {
                AT(s32, ro, 4) = flcalcBlend(ra[4], rb[4], t);
                AT(s32, ro, 8) = flcalcBlend(ra[8], rb[8], t);
                if (pb[0] != 1) skip = 1;
            } else {
                skip = 1;
            }
            break;
        }
        case 2: {
            u8* ra = AT(u8*, pa, 4);
            u8* rb = AT(u8*, pb, 4);
            u8* ro = AT(u8*, po, 4);
            AT(s32, ro, 4) = flcalcBlend(ra[4], rb[4], t);
            AT(s32, ro, 8) = flcalcBlend(ra[8], rb[8], t);
            break;
        }
        case 3: {
            u8* ra = AT(u8*, pa, 4);
            u8* rb = AT(u8*, pb, 4);
            u8* ro = AT(u8*, po, 4);
            AT(s32, ro, 0) = flcalcBlend(ra[0], rb[0], t);
            AT(s32, (u16)ro, 4) = flcalcBlend(ra[4], rb[4], t);
            AT(s32, ro, 8) = flcalcBlend(ra[8], rb[8], t);
            AT(s32, ro, 0xC) = flcalcBlend(ra[0xC], rb[0xC], t);
            break;
        }
        }
        pa = AT(u8*, pa, 8);
        po = AT(u8*, po, 8);
        if (skip == 0) pb = AT(u8*, pb, 8);
        skip = 0;
        if (AT(u32, (u16)pa, 8) == 0) loop = 0;
    } while (loop != 0);
}

u32 FlashMenu::GetPlayFrame() {
    return curTime;
}

void FlashMenu::SetPlayFrame(unsigned long f) {
    curTime = f;
}
