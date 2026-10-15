#include <dolphin/types.h>

struct GamedataSave {
    u64 memcardID;
    u32 savecount;
    u32 savernd;
    u32 parChecksum;
    u32 floorid;
    f32 unk18;
    u32 prevfloorid;
    u8 floorposindex;
    u8 optionNoVibration;
    u8 optionAudio;
    u8 unk23;
    u8 unk24[4];
    f64 playtime;
    u32 sysHeadChecksum;
};

struct Gamedata {
    u8 unk0[8];
    GamedataSave save;
    u8 playdata[1];
};

extern "C" {

void gamedataBiosSetZukanFLag(u16* flags, u16 bit, u16 on) {
    if (flags == NULL) {
        return;
    }
    if (bit > 16) {
        return;
    }
    u16 mask = 1 << bit;
    if (on == 1) {
        *flags |= mask;
    } else {
        *flags &= ~mask;
    }
}

bool gamedataBiosGetZukanFlag(u16* flags, u16 bit) {
    if (flags != NULL) {
        if (bit > 16) {
            return false;
        }
        u16 mask = 1 << bit;
        mask &= *flags;
        return mask != 0;
    }
    return false;
}

void* gamedatasaveBiosGetplaydata(Gamedata* gamedata) {
    if (gamedata == NULL) {
        return NULL;
    }
    return gamedata->playdata;
}

void gamedatasaveBiosSetSysHeadChecksum(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->sysHeadChecksum = value;
    }
}

u32 gamedatasaveBiosGetSysHeadChecksum(GamedataSave* save) {
    if (save != NULL) {
        return save->sysHeadChecksum;
    }
    return 0;
}

void fn_801577B4(GamedataSave* save, u8 value) {
    if (save != NULL) {
        save->unk23 = value;
    }
}

u8 fn_801577C4(GamedataSave* save) {
    if (save != NULL) {
        return save->unk23;
    }
    return 0;
}

void gamedatasaveBiosSetParChecksum(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->parChecksum = value;
    }
}

u32 gamedatasaveBiosGetParChecksum(GamedataSave* save) {
    if (save != NULL) {
        return save->parChecksum;
    }
    return 0;
}

void gamedatasaveBiosSetOptionAudio(GamedataSave* save, u8 value) {
    if (save != NULL) {
        save->optionAudio = value;
    }
}

void gamedatasaveBiosSetOptionNoVibration(GamedataSave* save, u8 value) {
    if (save != NULL) {
        save->optionNoVibration = value;
    }
}

void gamedatasaveBiosSetFloorposindex(GamedataSave* save, u8 value) {
    if (save != NULL) {
        save->floorposindex = value;
    }
}

void gamedatasaveBiosSetPrevfloorid(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->prevfloorid = value;
    }
}

void gamedatasaveBiosSetPlaytime(GamedataSave* save, f64 value) {
    if (save != NULL) {
        save->playtime = value;
    }
}

void gamedatasaveBiosSetFloorid(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->floorid = value;
    }
}

void gamedatasaveBiosSetSavecount(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->savecount = value;
    }
}

void gamedatasaveBiosSetMemcardID(GamedataSave* save, u64 value) {
    if (save != NULL) {
        save->memcardID = value;
    }
}

void gamedatasaveBiosSetSavernd(GamedataSave* save, u32 value) {
    if (save != NULL) {
        save->savernd = value;
    }
}

u8 gamedatasaveBiosGetOptionAudio(GamedataSave* save) {
    if (save != NULL) {
        return save->optionAudio;
    }
    return 0;
}

u8 gamedatasaveBiosGetOptionNoVibration(GamedataSave* save) {
    if (save != NULL) {
        return save->optionNoVibration;
    }
    return 0;
}

u8 gamedatasaveBiosGetFloorposindex(GamedataSave* save) {
    if (save != NULL) {
        return save->floorposindex;
    }
    return 0;
}

u32 gamedatasaveBiosGetPrevfloorid(GamedataSave* save) {
    if (save != NULL) {
        return save->prevfloorid;
    }
    return 0;
}

f64 gamedatasaveBiosGetPlaytime(GamedataSave* save) {
    if (save != NULL) {
        return save->playtime;
    }
    return 0.0;
}

u32 gamedatasaveBiosGetFloorid(GamedataSave* save) {
    if (save != NULL) {
        return save->floorid;
    }
    return 0;
}

u32 gamedatasaveBiosGetSavecount(GamedataSave* save) {
    if (save != NULL) {
        return save->savecount;
    }
    return 0;
}

u64 gamedatasaveBiosGetMemcardID(GamedataSave* save) {
    if (save != NULL) {
        return save->memcardID;
    }
    return 0;
}

u32 gamedatasaveBiosGetSavernd(GamedataSave* save) {
    if (save != NULL) {
        return save->savernd;
    }
    return 0;
}

void gamedatasaveBiosSetPtr(Gamedata* gamedata, GamedataSave* save) {
    if (gamedata == NULL || save == NULL) {
        return;
    }
    gamedata->save.memcardID = save->memcardID;
    gamedata->save.savecount = save->savecount;
    gamedata->save.savernd = save->savernd;
    gamedata->save.parChecksum = save->parChecksum;
    gamedata->save.floorid = save->floorid;
    gamedata->save.unk18 = save->unk18;
    gamedata->save.prevfloorid = save->prevfloorid;
    gamedata->save.floorposindex = save->floorposindex;
    gamedata->save.optionNoVibration = save->optionNoVibration;
    gamedata->save.optionAudio = save->optionAudio;
    gamedata->save.unk23 = save->unk23;
    gamedata->save.playtime = save->playtime;
    gamedata->save.sysHeadChecksum = save->sysHeadChecksum;
}

GamedataSave* gamedatasaveBiosGetPtr(Gamedata* gamedata) {
    if (gamedata == NULL) {
        return 0;
    }
    return &gamedata->save;
}

void gamedatasaveInit(Gamedata* gamedata) {
    GamedataSave* save = gamedatasaveBiosGetPtr(gamedata);
    if (save != NULL) {
        save->savecount = 0;
    }
}

}
