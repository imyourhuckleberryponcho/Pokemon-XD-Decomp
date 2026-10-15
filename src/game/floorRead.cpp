#include <dolphin/types.h>

#pragma peephole off
#pragma pool_strings off

struct _HSD_SceneDesc {
    void** models;
    void* cameras;
    void** lights;
    void** fog;
};

struct ArchiveBuf {
    u8 header[0x60];
    u8 payload[1];
};

typedef void* (*FloorPostFunc)(u32, u32, u32);
typedef s32 (*FloorUnloadFunc)(void*, u32, u32);

extern "C" {
void* memset(void*, int, u32);
void FlashSystemInit(u32, void*);
void FlashSystemRelease(u32);
void GScameraFree();
void* GScameraLoad(void*);
void GScolsys2LoadCCD(void*);
void GScolsys2UnloadCCD();
void GSfsysFree(u32);
void GSfsysOSLinkPostFunc(u32, u32, u32);
u8 GSfsysReadIDEXWait(u32, u32, void (*)(s32, void*, s32), u32, u32);
void GSlensFlareFree();
void* GSlensFlareLoad(void*);
void GSlightFree();
void* GSlightLoad(void*);
void GSmodelLinkToGSparticleBank(void*, void*);
void GSmsgClose(u32);
void GSmsgFontClose(u32);
void GSmsgFontOpen(void*);
void GSmsgOpen(void*);
void GSparticleFree();
void* GSparticleLoad(void*);
void* GSresAllocResourceAlign(u32, u32, u32, u32, FloorUnloadFunc);
void GSresFreeResource(u32, u32);
void* GSresGetResource(u32, u32);
void GSresIsUniqueID(u32, u32, u32);
void GSresLockResource(u32, u32);
void GSresRegisterResource(void*, u32, u32, FloorUnloadFunc);
void GSresUnlockResource(u32, u32);
void GStextureFree(void*);
void GStextureLoad(void*);
void GSthreadSwitch();
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void HSD_ArchiveParse(void*, void*, u32);
u8 Load__12WazaSequenceFPUcUlUl(void*, u32, u32);
u8 ModelSequence_Load(void*, u32, u32);
void Unload__12WazaSequenceFPUc();
void Unload__13ModelSequenceFPUc();
void* antGetGStexture__FPv(void*);
void antReadPostFunc__FPvUl(void*, u32);
void deckRegister(u32, u32);
void deckUnRegister(u32, u32);
void floorAddResource(u32, u32);
void* floorDataBiosGetCurrentPtr();
void floorDataBiosSetMapResID(void*, u32);
void floorExecSoundScript();
u32 floorGetCurrentGroupID();
void floorInitMap(u32, u32);
u8 floorIsPop();
u8 floorIsPush();
void floorMappingScript(void*);
void floorSetLightInfo(u32, u32);
u8 floorSound_playEnvSound(s32);
void floorUnmappingScript(u32);
s32 fn_8010B208(void*);
s32 pokecoloGetLanguage();
void soundStopEnv(s32);
}

class FloorPostCallManager {
public:
    FloorPostCallManager();
    void update();
    void add(u32 a, u32 b, u32 c, FloorPostFunc func);

private:
    struct Entry {
        u32 used;
        u32 a;
        u32 b;
        u32 c;
        FloorPostFunc func;
    };
    Entry entries[8];
};

static FloorPostCallManager _postFuncManager;
static u8 _floorReadingResource;

static void _fsysLoadCallbak(s32, void*, s32);
static void _registerCamera(u32 group, u32 id, _HSD_SceneDesc* desc);
static _HSD_SceneDesc* _makeArchiveHeader(u32 group, u32 id, u32 size);
static s32 _unloadObject(void*, u32, u32);
static s32 _unloadWZX(void*, u32, u32);
static s32 _unloadPKX(void*, u32, u32);
static s32 _unloadGSW(void*, u32, u32);
static s32 _unloadFlare(void*, u32, u32);
static s32 _unloadParticles(void*, u32, u32);
static s32 _unloadCamera(void*, u32, u32);
static s32 _unloadLight(void*, u32, u32);
static s32 _unloadScript(void*, u32, u32);
static s32 _unloadFont(void*, u32, u32);
static s32 _unloadMsg(void*, u32, u32);
static s32 _unloadColsys(void*, u32, u32);
static s32 _unloadTexture(void*, u32, u32);
static s32 _unloadDeckData(void*, u32, u32);
static s32 _unloadTextureForAnt(void*, u32, u32);

extern "C" {
u32 floorReadMakeFogResID(u32 id);
u32 floorReadMakeCameraResID(u32 id);
u32 floorReadMakeLightResID(u32 id);
u32 floorReadMakeModelResID(u32 id);
u32 floorReadMakeObjResID(u32 id);
void* floorReadNormalPreFunc(u32 group, u32 id, u32 size);

void floorDelayPostFunc() {
    _postFuncManager.update();
}

void* floorReadResourceID(u32 group, u32 id) {
    if (group == 0) {
        group = floorGetCurrentGroupID();
    }
    void* res = GSresGetResource(group, id);
    if (res != 0) {
        return res;
    }
    if (_floorReadingResource) {
        while (_floorReadingResource) {
            GSthreadSwitch();
        }
    }
    _floorReadingResource = 1;
    while (!GSfsysReadIDEXWait(group, id, _fsysLoadCallbak, 0, id)) {
        GSthreadSwitch();
    }
    GSfsysFree(group);
    floorAddResource(group, id);
    res = GSresGetResource(group, id);
    _floorReadingResource = 0;
    return res;
}
}

static void _fsysLoadCallbak(s32, void*, s32) {}

extern "C" {

_HSD_SceneDesc* floorRegisterCamera(u32 group, u32 id) {
    void* res = GSresGetResource(group, id);
    if (res == 0) {
        return 0;
    }
    _HSD_SceneDesc* desc = (_HSD_SceneDesc*)HSD_ArchiveGetPublicAddress(res, "scene_data");
    if (desc == 0) {
        return 0;
    }
    _registerCamera(group, floorReadMakeCameraResID(id), desc);
    return desc;
}

_HSD_SceneDesc* floorRegisterLight(u32 group, u32 id) {
    s32 i = 0;
    void* res = GSresGetResource(group, id);
    if (res == 0) {
        return 0;
    }
    _HSD_SceneDesc* desc = (_HSD_SceneDesc*)HSD_ArchiveGetPublicAddress(res, "scene_data");
    if (desc == 0) {
        return 0;
    }
    if (desc->lights != 0) {
        u32 base = floorReadMakeLightResID(id);
        s32 off = 0;
        while (*(void**)((u8*)desc->lights + off) != 0) {
            void* l = GSlightLoad(*(void**)((u8*)desc->lights + off));
            if (l != 0) {
                GSresRegisterResource(l, group, base | i, _unloadLight);
            }
            off += 4;
            i++;
        }
    }
    return desc;
}

void* floorReadDeckPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    if (res != 0) {
        deckRegister(group, id);
    }
    return res;
}

void* floorReadDeckPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadDeckData);
    GSresLockResource(group, id);
    return res;
}
}

static s32 _unloadDeckData(void* p, u32 group, u32 id) {
    deckUnRegister(group, id);
    return 1;
}

extern "C" {
void* floorReadAntPostFunc(u32 group, u32 id, u32 size) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    antReadPostFunc__FPvUl(res, size);
    GStextureLoad(antGetGStexture__FPv(res));
    return res;
}

void* floorReadAntPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadTextureForAnt);
    GSresLockResource(group, id);
    return res;
}
}

static s32 _unloadTextureForAnt(void* p, u32, u32) {
    GStextureFree(antGetGStexture__FPv(p));
    return 1;
}

extern "C" {
void* floorReadGSWPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    FlashSystemInit(id, res);
    return res;
}

void* floorReadGSWPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadGSW);
    GSresLockResource(group, id);
    return res;
}

void* floorReadEncodeRelPostFunc(u32 group, u32 id, u32 size) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    GSfsysOSLinkPostFunc(group, id, size);
    return res;
}

void* floorReadEncodeRelPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    if (res == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    return res;
}

void* floorReadGFLPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    GSresGetResource(group, id);
    void* res = GSresGetResource(group, floorReadMakeObjResID(id));
    void* f = GSlensFlareLoad(res);
    if (f != 0) {
        GSresRegisterResource(f, group, id, _unloadFlare);
    }
    return res;
}

void* floorReadGFLPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

u32 floorReadBGMPostFunc() {
    return 0;
}

void* floorReadBGMPreFunc(u32 group, u32 id, u32 size) {
    return floorReadNormalPreFunc(group, id, size);
}

void* floorReadNotLinkedParticlePostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, floorReadMakeObjResID(id));
    void* p = GSparticleLoad(res);
    if (p != 0) {
        GSresRegisterResource(p, group, id, _unloadParticles);
    }
    return res;
}

void* floorReadNotLinkedParticlePreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

struct FloorData {
    u32 pad;
    u32 mapResID;
};

void* floorReadParticlePostFunc(u32 group, u32 id, u32 size) {
    s32 i = 0;
    FloorData* fd = (FloorData*)floorDataBiosGetCurrentPtr();
    if (GSresGetResource(floorGetCurrentGroupID(), fd->mapResID) == 0) {
        _postFuncManager.add(group, id, size, (FloorPostFunc)floorReadParticlePostFunc);
        return 0;
    }
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, floorReadMakeObjResID(id));
    void* p = GSparticleLoad(res);
    if (p != 0) {
        GSresRegisterResource(p, group, id, _unloadParticles);
        fd = (FloorData*)floorDataBiosGetCurrentPtr();
        _HSD_SceneDesc* desc = (_HSD_SceneDesc*)HSD_ArchiveGetPublicAddress(GSresGetResource(floorGetCurrentGroupID(), fd->mapResID), "scene_data");
        if (GSresGetResource(floorGetCurrentGroupID(), fd->mapResID) == 0) {
            return 0;
        }
        if (desc == 0) {
            return 0;
        }
        if (desc->models != 0) {
            u32 base = floorReadMakeModelResID(fd->mapResID);
            s32 off = 0;
            while (*(void**)((u8*)desc->models + off) != 0) {
                void* m = GSresGetResource(floorGetCurrentGroupID(), base | i);
                if (m != 0) {
                    GSmodelLinkToGSparticleBank(m, p);
                }
                off += 4;
                i++;
            }
        }
    }
    return res;
}

void* floorReadParticlePreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

void* floorReadWZXPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    if (res == 0) {
        return 0;
    }
    if (Load__12WazaSequenceFPUcUlUl(res, group, id)) {
        return res;
    }
    return 0;
}

void* floorReadWZXPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadWZX);
    GSresLockResource(group, id);
    return res;
}

void* floorReadPKXPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    if (res == 0) {
        return 0;
    }
    if (ModelSequence_Load(res, group, id)) {
        return res;
    }
    return 0;
}

void* floorReadPKXPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadPKX);
    if (res == 0) {
        return 0;
    }
    GSresIsUniqueID(group, id, 0);
    GSresLockResource(group, id);
    return res;
}

void* floorReadTexPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    GStextureLoad(res);
    return res;
}

void* floorReadTexPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadTexture);
    GSresLockResource(group, id);
    return res;
}

void* floorReadColPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    GScolsys2LoadCCD(res);
    return res;
}

void* floorReadColPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadColsys);
    GSresLockResource(group, id);
    return res;
}

_HSD_SceneDesc* floorReadCameraPostFunc(u32 group, u32 id, u32 size) {
    _HSD_SceneDesc* desc = _makeArchiveHeader(group, floorReadMakeObjResID(id), size);
    _registerCamera(group, id, desc);
    return desc;
}

void* floorReadCameraPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, floorReadMakeObjResID(id), 0);
    if (res == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    return (u8*)res + 0x60;
}

_HSD_SceneDesc* floorReadObjPostFunc(u32 group, u32 id, u32 size) {
    s32 i = 0;
    _HSD_SceneDesc* desc = _makeArchiveHeader(group, id, size);
    if (desc == 0) {
        return 0;
    }
    u32 base = floorReadMakeModelResID(id);
    if (desc->models != 0) {
        s32 off = 0;
        while (*(void**)((u8*)desc->models + off) != 0) {
            GSresRegisterResource(*(void**)((u8*)desc->models + off), group, base | i, 0);
            off += 4;
            i++;
        }
    }
    return desc;
}

void* floorReadObjPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, id, _unloadObject);
    if (res == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    return (u8*)res + 0x60;
}

_HSD_SceneDesc* floorReadMapPostFunc(u32 group, u32 id, u32 size) {
    s32 i = 0;
    s32 j = 0;
    _HSD_SceneDesc* desc = _makeArchiveHeader(group, id, size);
    if (desc == 0) {
        return 0;
    }
    if (desc->models != 0) {
        u32 base = floorReadMakeModelResID(id);
        s32 off = 0;
        while (*(void**)((u8*)desc->models + off) != 0) {
            GSresRegisterResource(*(void**)((u8*)desc->models + off), group, base | i, 0);
            off += 4;
            i++;
        }
    }
    if (desc->lights != 0) {
        u32 base = floorReadMakeLightResID(id);
        s32 off = 0;
        while (*(void**)((u8*)desc->lights + off) != 0) {
            void* l = GSlightLoad(*(void**)((u8*)desc->lights + off));
            if (l != 0) {
                GSresRegisterResource(l, group, base | j, _unloadLight);
            }
            off += 4;
            j++;
        }
        floorSetLightInfo(base, j);
    } else {
        floorSetLightInfo(0, 0);
    }
    _registerCamera(group, floorReadMakeCameraResID(id), desc);
    if (desc->fog != 0 && *desc->fog != 0) {
        GSresRegisterResource(*desc->fog, group, floorReadMakeFogResID(id), 0);
    }
    floorInitMap(group, id);
    return desc;
}

void* floorReadMapPreFunc(u32 group, u32 id, u32 size) {
    void* res = GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, id, 0);
    if (res == 0) {
        return 0;
    }
    floorDataBiosSetMapResID(floorDataBiosGetCurrentPtr(), id);
    GSresLockResource(group, id);
    return (u8*)res + 0x60;
}

void* floorReadScriptPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    if (floorIsPop() == 0 && res != 0) {
        floorMappingScript(res);
        if (floorSound_playEnvSound(0) == 0) {
            soundStopEnv(0);
        }
        floorExecSoundScript();
    }
    return res;
}

void* floorReadScriptPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop() != 0) {
        return 0;
    }
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadScript);
    GSresLockResource(group, id);
    return res;
}

void* floorReadFontPostFunc(u32 group, u32 id) {
    if (floorIsPop() != 0) {
        return 0;
    }
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    if (res != 0) {
        GSmsgFontOpen(res);
    }
    return res;
}

void* floorReadFontPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop() != 0) {
        return 0;
    }
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadFont);
    GSresLockResource(group, id);
    return res;
}

void* floorReadMsgPostFunc(u32 group, u32 id) {
    if (floorIsPop() != 0) {
        return 0;
    }
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    s32 lang = pokecoloGetLanguage();
    if (lang != fn_8010B208(res)) {
        GSresFreeResource(group, id);
        return res;
    }
    if (res != 0) {
        GSmsgOpen(res);
    }
    return res;
}

void* floorReadMsgPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop() != 0) {
        return 0;
    }
    void* res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadMsg);
    GSresLockResource(group, id);
    return res;
}

void* floorReadNormalPreFunc(u32 group, u32 id, u32 size) {
    return GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
}
}

static void _registerCamera(u32 group, u32 id, _HSD_SceneDesc* desc) {
    if (desc != 0) {
        void* cam = GScameraLoad(desc->cameras);
        if (cam != 0) {
            GSresRegisterResource(cam, group, id, _unloadCamera);
        }
    }
}

static _HSD_SceneDesc* _makeArchiveHeader(u32 group, u32 id, u32 size) {
    GSresUnlockResource(group, id);
    void* res = GSresGetResource(group, id);
    HSD_ArchiveParse(res, ((ArchiveBuf*)res)->payload, size);
    return (_HSD_SceneDesc*)HSD_ArchiveGetPublicAddress(res, "scene_data");
}

static s32 _unloadObject(void*, u32 group, u32 id) {
    s32 i = 0;
    void* res = GSresGetResource(group, id);
    if (res == 0) {
        return 0;
    }
    _HSD_SceneDesc* desc = (_HSD_SceneDesc*)HSD_ArchiveGetPublicAddress(res, "scene_data");
    u32 base = floorReadMakeModelResID(id);
    if (desc->models != 0) {
        s32 off = 0;
        while (*(void**)((u8*)desc->models + off) != 0) {
            GSresFreeResource(group, base | i);
            off += 4;
            i++;
        }
    }
    return desc != 0;
}

static s32 _unloadWZX(void*, u32, u32) {
    Unload__12WazaSequenceFPUc();
    return 1;
}

static s32 _unloadPKX(void* p, u32, u32) {
    if (p != 0) {
        Unload__13ModelSequenceFPUc();
    }
    return 1;
}

static s32 _unloadGSW(void*, u32, u32 id) {
    FlashSystemRelease(id);
    return 1;
}

static s32 _unloadFlare(void*, u32, u32) {
    GSlensFlareFree();
    return 1;
}

static s32 _unloadParticles(void*, u32, u32) {
    GSparticleFree();
    return 1;
}

static s32 _unloadCamera(void*, u32, u32) {
    GScameraFree();
    return 1;
}

static s32 _unloadLight(void*, u32, u32) {
    GSlightFree();
    return 1;
}

static s32 _unloadScript(void* p, u32, u32) {
    if (floorIsPush() != 0) {
        return 0;
    }
    floorUnmappingScript((u32)p);
    return 1;
}

static s32 _unloadFont(void* p, u32, u32) {
    if (floorIsPush() != 0) {
        return 0;
    }
    GSmsgFontClose((u32)p);
    return 1;
}

static s32 _unloadMsg(void* p, u32, u32) {
    if (floorIsPush() != 0) {
        return 0;
    }
    GSmsgClose((u32)p);
    return 1;
}

static s32 _unloadColsys(void*, u32, u32) {
    GScolsys2UnloadCCD();
    return 1;
}

static s32 _unloadTexture(void* texture, u32, u32) {
    GStextureFree(texture);
    return 1;
}

extern "C" {
u32 floorReadMakeFogResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1A00;
}

u32 floorReadMakeCameraResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1800;
}

u32 floorReadMakeLightResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1600;
}

u32 floorReadMakeModelResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1000;
}

u32 floorReadMakeObjResID(u32 id) {
    return (id & 0x7FFF0000) | 0x400;
}
}

inline void FloorPostCallManager::update() {
    Entry* e = entries;
    for (; e != entries + 8; e++) {
        if (e->used != 0) {
            e->func(e->a, e->b, e->c);
            memset(e, 0, sizeof(Entry));
        }
    }
}

inline void FloorPostCallManager::add(u32 a, u32 b, u32 c, FloorPostFunc func) {
    Entry* e = entries;
    for (; e != entries + 8; e++) {
        if (e->used == 0) {
            e->used = 1;
            e->a = a;
            e->b = b;
            e->c = c;
            e->func = func;
            return;
        }
    }
}

#pragma dont_inline on
inline FloorPostCallManager::FloorPostCallManager() {
    memset(this, 0, sizeof(entries));
}
