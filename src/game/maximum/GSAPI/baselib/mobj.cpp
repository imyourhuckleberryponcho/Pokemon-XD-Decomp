
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/debug.h>
#pragma pool_strings off



#include <sysdolphin/baselib/aobj.h>




#include <sysdolphin/baselib/state.h>
#define MOBJ_ASSERT(line, cond, expr) ((cond) ? ((void)0) : __assert("mobj.c", line, expr))


























#include <string.h>

















HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list);
void MObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
void HSD_MObjAddShadowTexture(HSD_TObj* tobj);
void HSD_MObjRemove(HSD_MObj* mobj);
void HSD_MObjAddTObjNext(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TObj* next);
void HSD_MObjAddTObj(HSD_MObj* mobj, HSD_TObj* tobj);
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj);
void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha);
void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode);
void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode);
void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 rendermode);
void HSD_MObjCompileTev(HSD_MObj* mobj);
void HSD_MObjAnim(HSD_MObj* mobj);
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc);
void HSD_MObjSetDefaultClass(HSD_ClassInfo* info);
int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc);
void HSD_MObjSetCurrent(HSD_MObj* mobj);
u32 HSD_MObjGetFlags(HSD_MObj* mobj);
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj);
void MObjRelease(HSD_Class* obj);
void MObjAmnesia(HSD_ClassInfo* info);
void MObjInfoInit(void);
HSD_TObj* tobj_shadows;
HSD_TObj* tobj_toon;
static HSD_MObj* current_mobj;
static HSD_ClassInfo* default_class;
HSD_MObjInfo hsdMObj = {{{ MObjInfoInit }}};
static inline f32 MObjClampAnim(f32 value)
{
    if (value <= 0.0F) {
        return 0.0F;
    }
    if (value >= 1.0F) {
        return 1.0F;
    }
    return value;
}
void HSD_MObjSetCurrent(HSD_MObj* mobj) { current_mobj = mobj; }

u32 HSD_MObjGetFlags(HSD_MObj* mobj) { return mobj ? mobj->rendermode : 0; }

void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags) { if (mobj) mobj->rendermode |= flags; }

void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags) { if (mobj) mobj->rendermode &= ~flags; }

void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags) {
    if (mobj) {
        if (flags & MOBJ_ANIM) {
            HSD_AObjRemove(mobj->aobj);
            mobj->aobj = NULL;
        }
        if (flags & TOBJ_ANIM) HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}

void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL) {
        return;
    }
    if (matanim == NULL) {
        return;
    }
    if (mobj->aobj != NULL) {
        HSD_AObjRemove(mobj->aobj);
    }
    mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
    HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
}

void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL) {
        return;
    }
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

void MObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_MObj* mobj = obj;

    if (mobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        if (mobj->mat != NULL) {
            mobj->mat->ambient.r = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_AMBIENT_G:
        if (mobj->mat != NULL) {
            mobj->mat->ambient.g = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_AMBIENT_B:
        if (mobj->mat != NULL) {
            mobj->mat->ambient.b = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_DIFFUSE_R:
        if (mobj->mat != NULL) {
            mobj->mat->diffuse.r = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_DIFFUSE_G:
        if (mobj->mat != NULL) {
            mobj->mat->diffuse.g = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_DIFFUSE_B:
        if (mobj->mat != NULL) {
            mobj->mat->diffuse.b = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_ALPHA:
        if (mobj->mat != NULL) {
            mobj->mat->alpha = MObjClampAnim(1.0F - val->fv);
        }
        break;
    case HSD_A_M_SPECULAR_R:
        if (mobj->mat != NULL) {
            mobj->mat->specular.r = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_SPECULAR_G:
        if (mobj->mat != NULL) {
            mobj->mat->specular.g = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_SPECULAR_B:
        if (mobj->mat != NULL) {
            mobj->mat->specular.b = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_PE_REF0:
        if (mobj->pe != NULL) {
            mobj->pe->ref0 = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_PE_REF1:
        if (mobj->pe != NULL) {
            mobj->pe->ref1 = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        if (mobj->pe != NULL) {
            mobj->pe->dst_alpha = (u8) (255.0F * MObjClampAnim(val->fv));
        }
        break;
    }
}

void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_AObjInterpretAnim(mobj->aobj, mobj, HSD_MOBJ_METHOD(mobj)->update);
        HSD_TObjAnimAll(mobj->tobj);
    }
}

int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

void HSD_MObjSetDefaultClass(HSD_ClassInfo* info)
{
    if (info != NULL) {
        MOBJ_ASSERT(334, hsdIsDescendantOf(info, &hsdMObj), "hsdIsDescendantOf(info, &hsdMObj)");
    }
    default_class = info;
}

HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc != NULL) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (mobjdesc->class_name == NULL ||
            (info = hsdSearchClassInfo(mobjdesc->class_name)) == NULL)
        {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            MOBJ_ASSERT(373, mobj, "mobj");
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}

HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp* diff;
    HSD_TExp* spec;
    HSD_TExp* ext;
    HSD_TExp* alpha;
    HSD_TExp* exp;
    static u8 one = 255;
    HSD_TExp* cnst;
    HSD_TObj* tobj;
    HSD_TObj* toon = NULL;
    u32 done = 0;
    s32 diffuse_bits;
    u32 alpha_bits;

    if (list == NULL) __assert("mobj.c", 395, "list");

    *list = NULL;
    for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        }
    }

    diffuse_bits = mobj->rendermode & RENDER_DIFFUSE_BITS;
    if (diffuse_bits == RENDER_DIFFUSE_MAT0) {
        diffuse_bits = RENDER_DIFFUSE_MAT;
    }
    alpha_bits = mobj->rendermode & RENDER_ALPHA_BITS;
    if (alpha_bits == RENDER_ALPHA_COMPAT) {
        alpha_bits = diffuse_bits << RENDER_ALPHA_SHIFT;
    }

    exp = HSD_TExpTev(list);

    if (mobj->rendermode & RENDER_DIFFUSE) {
        switch (diffuse_bits) {
        case RENDER_DIFFUSE_VTX:
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_1,
                            HSD_TEXP_ZERO);
            break;
        default:
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8,
                                list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_RGB, cnst);
            break;
        }
        switch (alpha_bits) {
        case RENDER_ALPHA_VTX:
            cnst = HSD_TExpCnst(&one, HSD_TE_X, HSD_TE_U8, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X,
                            cnst);
            break;
        default:
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32,
                                list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X,
                            cnst);
            break;
        }
    } else {
        switch (diffuse_bits) {
        case RENDER_DIFFUSE_MAT:
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8,
                                list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_RGB, cnst);
            break;
        case RENDER_DIFFUSE_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_RGB,
                            toon != NULL ? HSD_TEXP_TEX : HSD_TEXP_RAS);
            break;
        default:
            cnst = HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8,
                                list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_RGB,
                            toon != NULL ? HSD_TEXP_TEX : HSD_TEXP_RAS,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_RGB, cnst);
            break;
        }
        switch (alpha_bits) {
        case RENDER_ALPHA_MAT:
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32,
                                list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X,
                            cnst);
            break;
        case RENDER_ALPHA_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                            HSD_TEXP_RAS);
            break;
        default:
            cnst = HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32,
                                list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                            HSD_TEXP_RAS, HSD_TE_X, cnst, HSD_TE_0,
                            HSD_TEXP_ZERO);
            break;
        }
    }

    diff = exp;
    alpha = exp;

    for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
        if ((tobj->flags & (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT)) &&
            tobj->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(tobj)->make_texp(
                tobj, (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT), done,
                &diff, &alpha, list);
        }
    }
    done |= (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT);

    if (mobj->rendermode & RENDER_DIFFUSE) {
        if (alpha_bits & RENDER_ALPHA_VTX) {
            exp = HSD_TExpTev(list);
            HSD_TExpOrder(exp, NULL, GX_COLOR1A1);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_RGB, diff);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
            diff = exp;
            alpha = exp;
        }
        exp = HSD_TExpTev(list);
        if (toon != NULL) {
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_TEX, HSD_TE_0,
                            HSD_TEXP_ZERO);
        } else {
            HSD_TExpOrder(exp, NULL, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0,
                            HSD_TEXP_ZERO);
        }
        diff = exp;
        if (alpha_bits & RENDER_ALPHA_VTX) {
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha,
                            HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        alpha = exp;
    }

    if (mobj->rendermode & RENDER_SPECULAR) {
        cnst = HSD_TExpCnst(&mobj->mat->specular, HSD_TE_RGB, HSD_TE_U8,
                            list);
        exp = HSD_TExpTev(list);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
        spec = exp;

        for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
            if ((tobj->flags & TEX_LIGHTMAP_SPECULAR) &&
                tobj->id != GX_TEXMAP_NULL)
            {
                HSD_TOBJ_METHOD(tobj)->make_texp(tobj, TEX_LIGHTMAP_SPECULAR,
                                                 done, &spec, &alpha, list);
            }
        }
        done |= TEX_LIGHTMAP_SPECULAR;

        exp = HSD_TExpTev(list);
        HSD_TExpOrder(exp, NULL, GX_COLOR1A1);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, spec,
                        HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        spec = exp;

        exp = HSD_TExpTev(list);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_RGB, spec, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
        diff = exp;
    }

    ext = diff;

    for (tobj = tobj_top; tobj != NULL; tobj = tobj->next) {
        if ((tobj->flags & TEX_LIGHTMAP_EXT) && tobj->id != GX_TEXMAP_NULL) {
            HSD_TOBJ_METHOD(tobj)->make_texp(tobj, TEX_LIGHTMAP_EXT, done,
                                             &ext, &alpha, list);
        }
    }

    if (ext != alpha || HSD_TExpGetType(ext) != HSD_TE_TEV ||
        HSD_TExpGetType(alpha) != HSD_TE_TEV)
    {
        exp = HSD_TExpTev(list);
        HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, ext);
        HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha);
        return exp;
    }

    return ext;
}

void HSD_MObjCompileTev(HSD_MObj* mobj)
{
    HSD_TObj* tobj;
    HSD_TObj** tail;
    HSD_TExp* texp;

    tail = NULL;
    if (mobj != NULL) {
        if (mobj->tevdesc != NULL) {
            HSD_TExpFreeTevDesc(mobj->tevdesc);
            mobj->tevdesc = NULL;
        }
        if (mobj->texp != NULL) {
            HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
            mobj->texp = NULL;
        }
        tobj = mobj->tobj;
        if (mobj->rendermode & RENDER_SHADOW) {
            if (tobj_shadows != NULL) {
                tail = &tobj;
                while (*tail != NULL) {
                    tail = &(*tail)->next;
                }
                *tail = tobj_shadows;
            }
        }
        if (mobj->rendermode & RENDER_TOON) {
            if (tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
                tobj_toon->next = tobj;
                tobj = tobj_toon;
            }
        }
        HSD_TObjAssignResources(tobj);
        texp = HSD_MOBJ_METHOD(mobj)->make_texp(mobj, tobj, &mobj->texp);
        HSD_TExpCompile(texp, &mobj->tevdesc, &mobj->texp);
        if (tail != NULL) {
            *tail = NULL;
        }
    }
}

void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 rendermode)
{
    MOBJ_ASSERT(798, mobj->tevdesc, "mobj->tevdesc");
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, rendermode);
}

void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj* tobj;
    HSD_TObj** tail;

    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (rendermode & RENDER_SPECULAR) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }

    tobj = mobj->tobj;
    tail = NULL;

    if ((rendermode & RENDER_SHADOW) && tobj_shadows != NULL) {
        tail = &tobj;
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = tobj_shadows;
    }
    if ((rendermode & RENDER_TOON) && tobj_toon != NULL &&
        tobj_toon->imagedesc != NULL)
    {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
    HSD_SetupRenderModeWithCustomPE(rendermode, mobj->pe);
    if (tail != NULL) {
        *tail = NULL;
    }
}

void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObjSetup(NULL);
}

void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha)
{
    if (mobj == NULL || mobj->mat == NULL) {
        return;
    }
    mobj->mat->alpha = alpha;
}

HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return NULL;
    }
    return mobj->tobj;
}

void HSD_MObjAddTObj(HSD_MObj* mobj, HSD_TObj* tobj)
{
    if (mobj == NULL || tobj == NULL) {
        return;
    }
    tobj->next = mobj->tobj;
    mobj->tobj = tobj;
}

void HSD_MObjAddTObjNext(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TObj* next)
{
    if (mobj == NULL || tobj == NULL || next == NULL) {
        return;
    }
    HSD_TObjAddNext(tobj, next);
}

void HSD_MObjRemove(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_CLASS_METHOD(mobj)->release((HSD_Class*) mobj);
        HSD_CLASS_METHOD(mobj)->destroy((HSD_Class*) mobj);
    }
}

HSD_MObj* HSD_MObjAlloc(void)
{
    HSD_MObj* mobj = hsdNew(default_class != NULL ? default_class : &hsdMObj.parent);
    MOBJ_ASSERT(1098, mobj, "mobj");
    return mobj;
}

HSD_Material* HSD_MaterialAlloc(void)
{
    HSD_Material* mat = hsdAllocMemPiece(sizeof(HSD_Material));
    MOBJ_ASSERT(1126, mat, "mat");
    memset(mat, 0, sizeof(HSD_Material));
    mat->alpha = 1.0F;
    return mat;
}

void HSD_MObjAddShadowTexture(HSD_TObj* tobj)
{
    HSD_TObj* cur;
    HSD_TObj** shadowList;
    HSD_TObj** list;

    MOBJ_ASSERT(1173, tobj, "tobj");

    for (cur = tobj_shadows; cur != NULL; cur = cur->next) {
        if (cur == tobj) {
            return;
        }
    }

    shadowList = &tobj_shadows;
    list = shadowList;
    tobj->next = *list;
    tobj_shadows = tobj;
}

void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj) {
    HSD_TObj** link;
    HSD_TObj* current;
    if (tobj) {
        for (link = &tobj_shadows; *link; link = &(*link)->next) {
            if (*link == tobj) {
                *link = tobj->next;
                tobj->next = NULL;
                return;
            }
        }
    } else {
        while ((current = tobj_shadows) != NULL) {
            tobj = current->next;
            current->next = NULL;
            tobj_shadows = tobj;
        }
    }
}

void MObjRelease(HSD_Class* obj) {
    HSD_MObj* mobj = (HSD_MObj*)obj;
    HSD_AObjRemove(mobj->aobj);
    hsdFreeMemPiece(mobj->mat, sizeof(HSD_Material));
    HSD_TObjRemoveAll(mobj->tobj);
    if (mobj->tevdesc) HSD_TExpFreeTevDesc(mobj->tevdesc);
    if (mobj->texp) HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
    if (mobj->pe) hsdFreeMemPiece(mobj->pe, sizeof(HSD_PEDesc));
    hsdMObj.parent.head.parent->release(obj);
}

void MObjAmnesia(HSD_ClassInfo* info) {
    if (info == default_class) default_class = NULL;
    if (info == (HSD_ClassInfo*)&hsdMObj) {
        tobj_toon = NULL;
        tobj_shadows = NULL;
    }
    hsdMObj.parent.head.parent->amnesia(info);
}

void MObjInfoInit(void) {
    hsdInitClassInfo((HSD_ClassInfo*)&hsdMObj, &hsdClass,
                    "sysdolphin_base_library", "hsd_mobj", sizeof(HSD_MObjInfo), sizeof(HSD_MObj));
    hsdMObj.parent.release = MObjRelease;
    hsdMObj.parent.amnesia = MObjAmnesia;
    hsdMObj.setup = HSD_MObjSetup;
    hsdMObj.unset = HSD_MObjUnset;
    hsdMObj.load = MObjLoad;
    hsdMObj.make_texp = MObjMakeTExp;
    hsdMObj.setup_tev = MObjSetupTev;
    hsdMObj.update = MObjUpdateFunc;
}
