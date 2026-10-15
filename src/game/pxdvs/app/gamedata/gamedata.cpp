#include <dolphin/types.h>

struct Gamedata;
struct GamedataSave;
struct GamedataAttest;

extern "C" {
void* savedataGetStatus(void*, u16);
void* gamedatasaveBiosGetplaydata(Gamedata*);
bool gamedataBiosGetZukanFlag(void*, u16);
void gamedataBiosSetZukanFLag(void*, u16, u16);
GamedataSave* gamedatasaveBiosGetPtr(Gamedata*);
void gamedatasaveBiosSetPtr(Gamedata*, GamedataSave*);
void gamedatasaveBiosSetSavernd(GamedataSave*, u32);
void gamedatasaveBiosSetSavecount(GamedataSave*, u32);
void gamedatasaveBiosSetFloorid(GamedataSave*, u32);
void gamedatasaveBiosSetPlaytime(GamedataSave*, f64);
void gamedatasaveBiosSetPrevfloorid(GamedataSave*, u32);
void gamedatasaveBiosSetFloorposindex(GamedataSave*, u8);
void gamedatasaveBiosSetOptionNoVibration(GamedataSave*, u8);
void gamedatasaveBiosSetOptionAudio(GamedataSave*, u8);
void gamedatasaveBiosSetParChecksum(GamedataSave*, u32);
void gamedatasaveBiosSetSysHeadChecksum(GamedataSave*, u32);
void fn_801577B4(GamedataSave*, u8);
u32 gamedatasaveBiosGetSavernd(GamedataSave*);
u32 gamedatasaveBiosGetSavecount(GamedataSave*);
u32 gamedatasaveBiosGetFloorid(GamedataSave*);
f64 gamedatasaveBiosGetPlaytime(GamedataSave*);
u32 gamedatasaveBiosGetPrevfloorid(GamedataSave*);
u8 gamedatasaveBiosGetFloorposindex(GamedataSave*);
u8 gamedatasaveBiosGetOptionNoVibration(GamedataSave*);
u8 gamedatasaveBiosGetOptionAudio(GamedataSave*);
u32 gamedatasaveBiosGetParChecksum(GamedataSave*);
u32 gamedatasaveBiosGetSysHeadChecksum(GamedataSave*);
u8 fn_801577C4(GamedataSave*);
void gamedatasaveInit(Gamedata*);
void gamedataBiosSetGamedataAtttestPtr(Gamedata*, GamedataAttest*);
GamedataAttest* gamedataBiosGetGamedataAtttestPtr(Gamedata*);
void gamedataAttestBiosSetVerId(GamedataAttest*, u8);
void gamedataAttestBiosSetGenId(GamedataAttest*, u8);
void gamedataAttestBiosSetAreaId(GamedataAttest*, u8);
void gamedataAttestBiosSetLangareaId(GamedataAttest*, u8);
u8 gamedataAttestBiosGetVerId(GamedataAttest*);
u8 gamedataAttestBiosGetGenId(GamedataAttest*);
u8 gamedataAttestBiosGetAreaId(GamedataAttest*);
u8 gamedataAttestBiosGetLangareaId(GamedataAttest*);

void gamedataInit(void*);
void gamedataAttestInit(GamedataAttest*);
void gamedataAttestCreate(GamedataAttest*, u8, u8, u8, u8);
}

static inline void gamedataSetStatusInline(Gamedata* ptr, u32 kind, u32 value) {
    GamedataAttest* attest;

    if ((u16)kind == 0 || (u16)kind >= 7) {
        return;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return;
        }
    }
    attest = gamedataBiosGetGamedataAtttestPtr(ptr);
    if (attest == 0) {
        return;
    }
    switch ((u16)kind) {
    case 1:
        gamedataBiosSetGamedataAtttestPtr(ptr, (GamedataAttest*)value);
        break;
    case 2:
        gamedataAttestBiosSetVerId(attest, (u8)value);
        break;
    case 3:
        gamedataAttestBiosSetGenId(attest, (u8)value);
        break;
    case 4:
        gamedataAttestBiosSetAreaId(attest, (u8)value);
        break;
    case 5:
        gamedataAttestBiosSetLangareaId(attest, (u8)value);
        break;
    default:
        break;
    }
}

static inline u32 gamedataGetStatusInline(Gamedata* ptr, u32 kind) {
    GamedataAttest* attest;

    if ((u16)kind == 0 || (u16)kind >= 7) {
        return 0;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return 0;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return 0;
        }
    }
    attest = gamedataBiosGetGamedataAtttestPtr(ptr);
    if (attest == 0) {
        return 0;
    }
    switch ((u16)kind) {
    case 1:
        return (u32)attest;
    case 2:
        return gamedataAttestBiosGetVerId(attest);
    case 3:
        return gamedataAttestBiosGetGenId(attest);
    case 4:
        return gamedataAttestBiosGetAreaId(attest);
    case 5:
        return gamedataAttestBiosGetLangareaId(attest);
    default:
        return 0;
    }
}

extern "C" {

bool gamedataBiosGetFlag(Gamedata* ptr, u16 kind, u16 bit) {
    if (kind == 0 || kind >= 0x10) {
        return false;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return false;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return false;
        }
    }
    void* playdata = gamedatasaveBiosGetplaydata(ptr);
    if (playdata == 0) {
        return false;
    }
    switch (kind) {
    case 0xE:
        return gamedataBiosGetZukanFlag(playdata, bit);
    default:
        return false;
    }
}

void gamedatasaveSetStatus(Gamedata* ptr, u32 kind, u32 value) {
    GamedataSave* save;

    if ((u16)kind == 0 || (u16)kind >= 0x10) {
        return;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return;
        }
    }
    save = gamedatasaveBiosGetPtr(ptr);
    if (save == 0) {
        return;
    }
    switch ((u16)kind) {
    case 1:
        gamedatasaveBiosSetPtr(ptr, (GamedataSave*)value);
        break;
    case 2:
        gamedatasaveBiosSetSavernd(save, value);
        break;
    case 3:
        break;
    case 4:
        gamedatasaveBiosSetSavecount(save, value);
        break;
    case 5:
        gamedatasaveBiosSetFloorid(save, value);
        break;
    case 6:
        gamedatasaveBiosSetPlaytime(save, (f32)(s32)value);
        break;
    case 7:
        gamedatasaveBiosSetPrevfloorid(save, value);
        break;
    case 8:
        gamedatasaveBiosSetFloorposindex(save, (u8)value);
        break;
    case 9:
        gamedatasaveBiosSetOptionNoVibration(save, (u8)value);
        break;
    case 10:
        gamedatasaveBiosSetOptionAudio(save, (u8)value);
        break;
    case 12:
        gamedatasaveBiosSetParChecksum(save, value);
        break;
    case 13:
        gamedatasaveBiosSetSysHeadChecksum(save, value);
        break;
    case 11:
        fn_801577B4(save, (u8)value);
        break;
    default:
        break;
    }
}

u32 gamedatasaveGetStatus(Gamedata* ptr, u32 kind) {
    Gamedata* base = 0;
    GamedataSave* save;

    if ((u16)kind == 0 || (u16)kind >= 0x10) {
        return 0;
    }
    if (ptr == 0) {
        base = (Gamedata*)savedataGetStatus(0, 0);
        if (base == 0) {
            return 0;
        }
        ptr = (Gamedata*)savedataGetStatus(base, 1);
        if (ptr == 0) {
            return 0;
        }
    }
    save = gamedatasaveBiosGetPtr(ptr);
    if (save == 0) {
        return 0;
    }
    switch ((u16)kind) {
    case 1:
        return (u32)base;
    case 2:
        return gamedatasaveBiosGetSavernd(save);
    case 3:
        break;
    case 4:
        return gamedatasaveBiosGetSavecount(save);
    case 5:
        return gamedatasaveBiosGetFloorid(save);
    case 6:
        return (s32)gamedatasaveBiosGetPlaytime(save);
    case 7:
        return gamedatasaveBiosGetPrevfloorid(save);
    case 8:
        return gamedatasaveBiosGetFloorposindex(save);
    case 9:
        return gamedatasaveBiosGetOptionNoVibration(save);
    case 10:
        return gamedatasaveBiosGetOptionAudio(save);
    case 12:
        return gamedatasaveBiosGetParChecksum(save);
    case 13:
        return gamedatasaveBiosGetSysHeadChecksum(save);
    case 11:
        return fn_801577C4(save);
    default:
        break;
    }
    return 0;
}

void gamedataCreate(Gamedata* ptr, u8 ver, u8 gen, u8 area, u8 langarea) {
    if (ptr == 0) {
        return;
    }
    gamedataInit(ptr);
    GamedataAttest* attest = (GamedataAttest*)gamedataGetStatusInline(ptr, 1);
    if (attest == 0) {
        return;
    }
    gamedataAttestCreate(attest, ver, gen, area, langarea);
}

void gamedataInit(void* ptr) {
    u16 i;
    GamedataAttest* attest = (GamedataAttest*)gamedataGetStatusInline((Gamedata*)ptr, 1);
    if (attest == 0) { return; }
    gamedataAttestInit(attest);
    gamedatasaveInit((Gamedata*)ptr);
    for (i = 0; i < 0x10; i++) {
        Gamedata* g = (Gamedata*)ptr;
        if (g == 0) {
            g = (Gamedata*)savedataGetStatus(0, 0);
            if (g == 0) { continue; }
            g = (Gamedata*)savedataGetStatus(g, 1);
            if (g == 0) { continue; }
        }
        void* playdata = gamedatasaveBiosGetplaydata(g);
        if (playdata != 0) { gamedataBiosSetZukanFLag(playdata, i, 0); }
    }
}

void gamedataAttestCreate(GamedataAttest* ptr, u8 ver, u8 gen, u8 area, u8 langarea) {
    if (ptr == 0) {
        return;
    }
    if (ver == 0) {
        return;
    }
    if (gen == 0) {
        return;
    }
    if (area == 0) {
        return;
    }
    if (langarea == 0) {
        return;
    }
    gamedataAttestInit(ptr);
    gamedataSetStatusInline((Gamedata*)ptr, 2, ver);
    gamedataSetStatusInline((Gamedata*)ptr, 3, gen);
    gamedataSetStatusInline((Gamedata*)ptr, 4, area);
    gamedataSetStatusInline((Gamedata*)ptr, 5, langarea);
}

u32 gamedataAttestCheckValid(Gamedata* ptr) {
    if (ptr == 0) {
        return 0;
    }
    if ((s32)gamedataGetStatusInline(ptr, 2) == 0) {
        return 0;
    }
    if ((s32)gamedataGetStatusInline(ptr, 3) == 0) {
        return 0;
    }
    if ((s32)gamedataGetStatusInline(ptr, 4) == 0) {
        return 0;
    }
    return gamedataGetStatusInline(ptr, 5) != 0;
}

void gamedataAttestInit(GamedataAttest* ptr) {
    if (ptr == 0) {
        return;
    }
    gamedataSetStatusInline((Gamedata*)ptr, 2, 0);
    gamedataSetStatusInline((Gamedata*)ptr, 3, 0);
    gamedataSetStatusInline((Gamedata*)ptr, 4, 0);
    gamedataSetStatusInline((Gamedata*)ptr, 5, 0);
}

void gamedataSetStatus(Gamedata* ptr, u32 kind, u32 value) {
    GamedataAttest* base;

    if ((u16)kind == 0 || (u16)kind >= 7) {
        return;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return;
        }
    }
    base = gamedataBiosGetGamedataAtttestPtr(ptr);
    if (base == 0) {
        return;
    }
    switch ((u16)kind) {
    case 1:
        gamedataBiosSetGamedataAtttestPtr(ptr, (GamedataAttest*)value);
        break;
    case 2:
        gamedataAttestBiosSetVerId(base, (u8)value);
        break;
    case 3:
        gamedataAttestBiosSetGenId(base, (u8)value);
        break;
    case 4:
        gamedataAttestBiosSetAreaId(base, (u8)value);
        break;
    case 5:
        gamedataAttestBiosSetLangareaId(base, (u8)value);
        break;
    default:
        break;
    }
}

u32 gamedataGetStatus(Gamedata* ptr, u32 kind) {
    GamedataAttest* base;

    if ((u16)kind == 0 || (u16)kind >= 7) {
        return 0;
    }
    if (ptr == 0) {
        ptr = (Gamedata*)savedataGetStatus(0, 0);
        if (ptr == 0) {
            return 0;
        }
        ptr = (Gamedata*)savedataGetStatus(ptr, 1);
        if (ptr == 0) {
            return 0;
        }
    }
    base = gamedataBiosGetGamedataAtttestPtr(ptr);
    if (base == 0) {
        return 0;
    }
    switch ((u16)kind) {
    case 1:
        return (u32)base;
    case 2:
        return gamedataAttestBiosGetVerId(base);
    case 3:
        return gamedataAttestBiosGetGenId(base);
    case 4:
        return gamedataAttestBiosGetAreaId(base);
    case 5:
        return gamedataAttestBiosGetLangareaId(base);
    default:
        return 0;
    }
}

}
