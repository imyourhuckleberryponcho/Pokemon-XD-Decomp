// WIP (NonMatching): only HSD_SetupPEMode differs, in the register numbers chosen for the
// inlined HSD_StateSet* variables (same instructions otherwise).
// Compiled as C with deferred inlining (see configure.py): functions come out in reverse
// source order, and the HSD_StateSet* functions defined later are inlined into HSD_SetupPEMode.
// Based on the Melee decomp's state.c; XD's channel setup differs (local channel tables).
#include <dolphin/types.h>

#pragma pool_strings off

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct HSD_Chan {
    struct HSD_Chan* next;
    s32 chan;
    u32 flags;
    GXColor amb_color;
    GXColor mat_color;
    u8 enable;
    s32 amb_src;
    s32 mat_src;
    s32 light_mask;
    s32 diff_fn;
    s32 attn_fn;
    u32 unk2C;
} HSD_Chan;

typedef struct HSD_LObj {
    u8 unk0[8];
    u16 flags;
    u8 unkA[6];
    GXColor color;
} HSD_LObj;

typedef struct HSD_PEDesc {
    u8 flags;
    u8 ref0;
    u8 ref1;
    u8 dst_alpha;
    u8 type;
    u8 src_factor;
    u8 dst_factor;
    u8 logic_op;
    u8 z_comp;
    u8 alpha_comp0;
    u8 alpha_op;
    u8 alpha_comp1;
} HSD_PEDesc;

typedef struct HSD_TevDesc {
    struct HSD_TevDesc* next;
    u32 flags;
    u32 stage;
    u32 coord;
    u32 map;
    u32 color;
    u32 tevmode;
    u8 unk1C[0x70];
} HSD_TevDesc;

enum {
    HSD_STATE_NONE = 0,
    HSD_STATE_PRIMITIVE = 1 << 0,
    HSD_STATE_VTX_ATTR = 1 << 1,
    HSD_STATE_COLOR_CHANNEL = 1 << 2,
    HSD_STATE_TEV_STAGE = 1 << 3,
    HSD_STATE_TEV_REGISTER = 1 << 4,
    HSD_STATE_TEX_COORD_GEN = 1 << 5,
    HSD_STATE_RENDER_MODE = 1 << 6,
};

u32 HSD_LObjGetLightMaskSpecular(void);
u32 HSD_LObjGetLightMaskDiffuse(void);
u32 HSD_LObjGetLightMaskAlpha(void);
s32 HSD_LObjGetNbActive(void);
HSD_LObj* HSD_LObjGetActiveByIndex(s32 i);
HSD_LObj* HSD_LObjGetActiveByID(s32 id);
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess);
void HSD_SetupChannel(HSD_Chan* ch);
void HSD_MulColor(GXColor* a, GXColor* b, GXColor* out);
void HSD_DisableChannelLighting(s32 mask);
void HSD_StateSetNumChans(s32 n);
s32 HSD_StateGetNumTevStages(void);
s32 HSD_StateAssignTev(void);
void HSD_SetupTevStage(HSD_TevDesc* desc);
void HSD_SetTevRegAll(void);
void HSD_StateSetNumTevStages(void);
void HSD_StateSetNumTexGens(void);
void HSD_ClearVtxDesc(void);
void _HSD_StateInvalidateColorChannel(void);
void _HSD_StateInvalidateTevStage(void);
void _HSD_StateInvalidateTevRegister(void);
void _HSD_StateInvalidateTexCoordGen(void);
void GXSetLineWidth(u8 width, s32 texOffsets);
void GXSetPointSize(u8 size, s32 texOffsets);
void GXSetCullMode(s32 mode);
void GXSetBlendMode(s32 type, s32 src, s32 dst, s32 op);
void GXSetZMode(u8 enable, s32 func, u8 update);
void GXSetAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1);
void GXSetColorUpdate(u8 update);
void GXSetAlphaUpdate(u8 update);
void GXSetDstAlpha(u8 enable, u8 alpha);
void GXSetZCompLoc(u8 beforeTex);
void GXSetDither(u8 dither);

void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe);
void HSD_StateSetLineWidth(u8 width);
void HSD_StateSetCullMode(s32 mode);
void HSD_StateSetBlendMode(s32 type, s32 src_factor, s32 dst_factor, s32 op);
void HSD_StateSetZMode(s32 enable, s32 func, s32 update);
void HSD_StateSetPointSize(u8 size);
void HSD_StateSetAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1);
void HSD_StateSetColorUpdate(s32 enable);
void HSD_StateSetAlphaUpdate(s32 enable);
void HSD_StateSetDstAlpha(s32 enable, u8 alpha);
void HSD_StateSetZCompLoc(s32 before_tex);
void HSD_StateSetDither(s32 dither);
static void _HSD_StateInvalidatePrimitive(void);
static void _HSD_StateInvalidateVtxAttr(void);
static void _HSD_StateInvalidateRenderMode(void);

static u8 state_line_width;
static u8 state_point_size;
static s32 state_cull_mode;
static s32 state_blend_type;
static s32 state_src_factor;
static s32 state_dst_factor;
static s32 state_logic_op;
static u8 state_z_enable;
static s32 state_z_func;
static u8 state_z_update;
static s32 state_alpha_comp0;
static u8 state_alpha_ref0;
static s32 state_alpha_op;
static s32 state_alpha_comp1;
static u8 state_alpha_ref1;
static u8 state_color_update;
static u8 state_alpha_update;
static u8 state_enable_dst_alpha;
static u8 state_dst_alpha;
static u8 state_before_tex;
static u8 state_dither;

static struct matstate_t {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    u8 alpha;
    f32 shininess;
} matstate;

static inline f32 HSD_ClampFloat(f32 val, f32 min, f32 max) {
    if (val <= min) {
        return min;
    }
    if (val >= max) {
        return max;
    }
    return val;
}

void HSD_SetupChannelMode(u32 rendermode) {
    u32 diffuse_src;
    u32 alpha_src;
    s32 specular = FALSE;
    s32 vtx_alpha = FALSE;

    diffuse_src = rendermode & 3;
    if (diffuse_src == 0) {
        diffuse_src = 1;
    }
    alpha_src = rendermode & 0x6000;
    if (alpha_src == 0) {
        alpha_src = diffuse_src << 13;
    }

    if (rendermode & 8) {
        static HSD_Chan ch = {NULL, 1, 0, {0, 0, 0, 0}, {0xFF, 0xFF, 0xFF, 0xFF}, 1, 0, 0, 0, 0, 0, 0};
        s32 i;
        s32 n;

        ch.light_mask = HSD_LObjGetLightMaskSpecular();
        HSD_SetupChannel(&ch);
        specular = TRUE;
        n = HSD_LObjGetNbActive();
        for (i = 0; i < n; i++) {
            HSD_LObj* lobj = HSD_LObjGetActiveByIndex(i);
            if (lobj != NULL) {
                HSD_LObjSetup(lobj, lobj->color, matstate.shininess);
            }
        }
    }

    if (rendermode & 4) {
        static HSD_Chan ch = {NULL, 0, 0, {0, 0, 0, 0}, {0xFF, 0xFF, 0xFF, 0xFF}, 1, 0, 0, 0, 2, 1, 0};
        static HSD_Chan ch_a = {NULL, 2, 0, {0, 0, 0, 0}, {0, 0, 0, 0}, 1, 0, 0, 0, 2, 1, 0};
        static HSD_Chan ch_vtx_a = {NULL, 2, 0, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0, 1, 0, 2, 1, 0};
        static GXColor dark_matter = {0, 0, 0, 0xFF};
        HSD_LObj* lobj;
        u8 amb_alpha;

        lobj = HSD_LObjGetActiveByID(0x100);
        if (lobj != NULL && (lobj->flags & 4)) {
            HSD_MulColor(&matstate.ambient, &lobj->color, &ch.amb_color);
        } else {
            ch.amb_color = dark_matter;
        }
        ch.mat_src = (diffuse_src >> 1) & 1;
        ch.light_mask = HSD_LObjGetLightMaskDiffuse();
        HSD_SetupChannel(&ch);

        if (alpha_src & 0x4000) {
            ch_a.chan = 3;
            vtx_alpha = TRUE;
            HSD_SetupChannel(&ch_vtx_a);
        } else {
            ch_a.chan = 2;
        }
        ch_a.light_mask = HSD_LObjGetLightMaskAlpha();
        if (lobj != NULL && (lobj->flags & 0x10)) {
            amb_alpha = lobj->color.a;
        } else {
            amb_alpha = 0;
        }
        if (ch_a.light_mask != 0) {
            ch_a.enable = 1;
            ch_a.mat_color.a = 0xFF;
            ch_a.amb_color.a = amb_alpha;
        } else {
            ch_a.enable = 0;
            ch_a.mat_color.a = amb_alpha;
        }
        HSD_SetupChannel(&ch_a);
    } else {
        static HSD_Chan ch = {NULL, 0, 0, {0, 0, 0, 0}, {0xFF, 0xFF, 0xFF, 0xFF}, 0, 0, 1, 0, 0, 2, 0};
        static HSD_Chan ch_a = {NULL, 2, 0, {0, 0, 0, 0}, {0, 0, 0, 0xFF}, 0, 0, 1, 0, 0, 2, 0};

        ch.mat_src = (diffuse_src >> 1) & 1;
        HSD_SetupChannel(&ch);
        ch_a.mat_src = (alpha_src >> 14) & 1;
        HSD_SetupChannel(&ch_a);
    }

    if (specular) {
        if (!vtx_alpha) {
            HSD_DisableChannelLighting(3);
        }
        HSD_StateSetNumChans(2);
    } else if (vtx_alpha) {
        HSD_DisableChannelLighting(1);
        HSD_StateSetNumChans(2);
    } else {
        HSD_DisableChannelLighting(5);
        HSD_StateSetNumChans(1);
    }
}

void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe) {
    if (pe != NULL) {
        HSD_StateSetColorUpdate(pe->flags & 1);
        HSD_StateSetAlphaUpdate(pe->flags & 2);
        HSD_StateSetDstAlpha(pe->flags & 4, pe->dst_alpha);
        HSD_StateSetBlendMode(pe->type, pe->src_factor, pe->dst_factor, pe->logic_op);
        HSD_StateSetZMode(pe->flags & 0x10, pe->z_comp, pe->flags & 0x20);
        HSD_StateSetZCompLoc(pe->flags & 8);
        HSD_StateSetAlphaCompare(pe->alpha_comp0, pe->ref0, pe->alpha_op, pe->alpha_comp1, pe->ref1);
        HSD_StateSetDither(pe->flags & 0x40);
        return;
    }
    HSD_StateSetColorUpdate(1);
    HSD_StateSetAlphaUpdate(0);
    HSD_StateSetDstAlpha(0, 0);
    HSD_StateSetBlendMode((flags & 0x40000000) ? 1 : 0, 4, 5, 0xF);
    HSD_StateSetZMode(1, (flags & 0x08000000) ? 7 : 3, (flags & 0x20000000) ? FALSE : TRUE);
    if (!(flags & 0x20000000) && (flags & 0x40000000)) {
        HSD_StateSetZCompLoc(0);
        HSD_StateSetAlphaCompare(4, 0, 0, 4, 0);
    } else {
        HSD_StateSetZCompLoc(1);
        HSD_StateSetAlphaCompare(7, 0, 0, 7, 0);
    }
    HSD_StateSetDither(0);
}

static inline void setupTevMode_last(void) {
    if (!HSD_StateGetNumTevStages()) {
        HSD_TevDesc tevdesc;
        tevdesc.flags = 0;
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = 0xFF;
        tevdesc.map = 0xFF;
        tevdesc.color = 4;
        tevdesc.tevmode = 4;
        HSD_SetupTevStage(&tevdesc);
    }
}

void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe) {
    setupTevMode_last();
    HSD_SetupPEMode(rendermode, pe);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_SetupChannelMode(rendermode);
}

void HSD_SetupRenderMode(u32 rendermode) {
    HSD_SetupRenderModeWithCustomPE(rendermode, NULL);
}

void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular, f32 alpha) {
    f32 a;

    matstate.ambient = ambient;
    matstate.diffuse = diffuse;
    matstate.specular = specular;
    a = HSD_ClampFloat(alpha, 0.0f, 1.0f);
    matstate.alpha = 255.0f * a;
}

void HSD_SetMaterialShininess(f32 shininess) {
    matstate.shininess = shininess;
}

void HSD_StateSetLineWidth(u8 width) {
    if (state_line_width != width) {
        GXSetLineWidth(width, 0);
        state_line_width = width;
    }
}

void HSD_StateSetCullMode(s32 mode) {
    if (state_cull_mode != mode) {
        GXSetCullMode(mode);
        state_cull_mode = mode;
    }
}

void HSD_StateSetBlendMode(s32 type, s32 src_factor, s32 dst_factor, s32 op) {
    if (state_blend_type != type || state_src_factor != src_factor || state_dst_factor != dst_factor ||
        state_logic_op != op) {
        GXSetBlendMode(type, src_factor, dst_factor, op);
        state_blend_type = type;
        state_src_factor = src_factor;
        state_dst_factor = dst_factor;
        state_logic_op = op;
    }
}

void HSD_StateSetZMode(s32 enable, s32 func, s32 update) {
    u8 on = enable ? TRUE : FALSE;
    u8 write = update ? TRUE : FALSE;
    if (state_z_enable != on || state_z_func != func || state_z_update != write) {
        GXSetZMode(on, func, write);
        state_z_enable = on;
        state_z_func = func;
        state_z_update = write;
    }
}

void HSD_StateSetPointSize(u8 size) {
    if (state_point_size != size) {
        GXSetPointSize(size, 0);
        state_point_size = size;
    }
}

void HSD_StateSetAlphaCompare(s32 comp0, u8 ref0, s32 op, s32 comp1, u8 ref1) {
    if (state_alpha_comp0 != comp0 || state_alpha_ref0 != ref0 || state_alpha_op != op ||
        state_alpha_comp1 != comp1 || state_alpha_ref1 != ref1) {
        GXSetAlphaCompare(comp0, ref0, op, comp1, ref1);
        state_alpha_comp0 = comp0;
        state_alpha_ref0 = ref0;
        state_alpha_op = op;
        state_alpha_comp1 = comp1;
        state_alpha_ref1 = ref1;
    }
}

void HSD_StateSetColorUpdate(s32 enable) {
    u8 on = enable ? TRUE : FALSE;
    if (state_color_update != on) {
        GXSetColorUpdate(on);
        state_color_update = on;
    }
}

void HSD_StateSetAlphaUpdate(s32 enable) {
    u8 on = enable ? TRUE : FALSE;
    if (state_alpha_update != on) {
        GXSetAlphaUpdate(on);
        state_alpha_update = on;
    }
}

void HSD_StateSetDstAlpha(s32 enable, u8 alpha) {
    u8 on = enable ? TRUE : FALSE;
    if (state_enable_dst_alpha != on || state_dst_alpha != alpha) {
        GXSetDstAlpha(on, alpha);
        state_enable_dst_alpha = on;
        state_dst_alpha = alpha;
    }
}

void HSD_StateSetZCompLoc(s32 before_tex) {
    u8 on = before_tex ? TRUE : FALSE;
    if (state_before_tex != on) {
        GXSetZCompLoc(on);
        state_before_tex = on;
    }
}

void HSD_StateSetDither(s32 dither) {
    u8 on = dither ? TRUE : FALSE;
    if (state_dither != on) {
        GXSetDither(on);
        state_dither = on;
    }
}

static void _HSD_StateInvalidatePrimitive(void) {
    state_point_size = 0;
    state_cull_mode = -1;
    state_line_width = 0xFF;
}

static void _HSD_StateInvalidateVtxAttr(void) {
    HSD_ClearVtxDesc();
}

static void _HSD_StateInvalidateRenderMode(void) {
    state_blend_type = -1;
    state_src_factor = -1;
    state_dst_factor = -1;
    state_logic_op = -1;
    state_z_enable = -1;
    state_z_func = -1;
    state_z_update = -1;
    state_alpha_comp0 = -1;
    state_alpha_ref0 = 0;
    state_alpha_op = -1;
    state_alpha_comp1 = -1;
    state_alpha_ref1 = 0;
    state_color_update = -1;
    state_alpha_update = -1;
    state_enable_dst_alpha = -1;
    state_dst_alpha = 0;
    state_before_tex = -1;
    state_dither = -1;
}

void HSD_StateInvalidate(s32 mask) {
    static struct {
        s32 mask;
        void (*func)(void);
    } invalidate_funcs[] = {
        {HSD_STATE_PRIMITIVE, _HSD_StateInvalidatePrimitive},
        {HSD_STATE_VTX_ATTR, _HSD_StateInvalidateVtxAttr},
        {HSD_STATE_COLOR_CHANNEL, _HSD_StateInvalidateColorChannel},
        {HSD_STATE_TEV_STAGE, _HSD_StateInvalidateTevStage},
        {HSD_STATE_TEV_REGISTER, _HSD_StateInvalidateTevRegister},
        {HSD_STATE_TEX_COORD_GEN, _HSD_StateInvalidateTexCoordGen},
        {HSD_STATE_RENDER_MODE, _HSD_StateInvalidateRenderMode},
        {HSD_STATE_NONE},
    };
    s32 i;
    s32 m;
    for (i = 0; (m = invalidate_funcs[i].mask) != HSD_STATE_NONE; i++) {
        if (mask & m) {
            invalidate_funcs[i].func();
        }
    }
}
