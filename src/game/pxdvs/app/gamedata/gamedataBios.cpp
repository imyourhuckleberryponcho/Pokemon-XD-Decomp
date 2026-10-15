#include <dolphin/types.h>

struct GamedataAttest {
    u8 verId;
    u8 genId;
    u8 areaId;
    u8 langareaId;
};

struct Gamedata {
    GamedataAttest attest;
};

extern "C" {

void gamedataAttestBiosSetLangareaId(GamedataAttest* attest, u8 id) {
    if (attest != NULL) {
        attest->langareaId = id;
    }
}

void gamedataAttestBiosSetAreaId(GamedataAttest* attest, u8 id) {
    if (attest != NULL) {
        attest->areaId = id;
    }
}

void gamedataAttestBiosSetGenId(GamedataAttest* attest, u8 id) {
    if (attest != NULL) {
        attest->genId = id;
    }
}

void gamedataAttestBiosSetVerId(GamedataAttest* attest, u8 id) {
    if (attest != NULL) {
        attest->verId = id;
    }
}

u8 gamedataAttestBiosGetLangareaId(GamedataAttest* attest) {
    if (attest == NULL) {
        return 0;
    }
    return attest->langareaId;
}

u8 gamedataAttestBiosGetAreaId(GamedataAttest* attest) {
    if (attest == NULL) {
        return 0;
    }
    return attest->areaId;
}

u8 gamedataAttestBiosGetGenId(GamedataAttest* attest) {
    if (attest == NULL) {
        return 0;
    }
    return attest->genId;
}

u8 gamedataAttestBiosGetVerId(GamedataAttest* attest) {
    if (attest == NULL) {
        return 0;
    }
    return attest->verId;
}

void gamedataAttestBiosCopy(GamedataAttest* dst, GamedataAttest* src) {
    if (dst != NULL && src != NULL) {
        dst->verId = src->verId;
        dst->genId = src->genId;
        dst->areaId = src->areaId;
        dst->langareaId = src->langareaId;
    }
}

void gamedataBiosSetGamedataAtttestPtr(Gamedata* gamedata, GamedataAttest* attest) {
    if (gamedata == NULL || attest == NULL) {
        return;
    }
    gamedata->attest.verId = attest->verId;
    gamedata->attest.genId = attest->genId;
    gamedata->attest.areaId = attest->areaId;
    gamedata->attest.langareaId = attest->langareaId;
}

GamedataAttest* gamedataBiosGetGamedataAtttestPtr(Gamedata* gamedata) {
    if (gamedata == NULL) {
        return 0;
    }
    return &gamedata->attest;
}

}
