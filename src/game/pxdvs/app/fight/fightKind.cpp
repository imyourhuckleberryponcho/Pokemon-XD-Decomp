#include <dolphin/types.h>

// Built with -O4,s (see configure.py).

struct FightKindData {
    u8 backSaveDataFlag;
    u8 doBadgeCheckFlag;
    u8 doZukanMitaFlag;
    u8 doZukanTukamaetaFlag;
    u8 useItemFlag;
    u8 callFlag;
    u8 nigeruFlag;
    u8 drawFlag;
    u8 getExpFlag;
    u8 getOkaneFlag;
    u8 okanePoolFlag;
    u8 getNekoniKobanFlag;
    u8 getFriendFlag;
    u8 getInfectPokerusFlag;
    u8 doCriticalAttackFlag;
    u8 doHizukiAiFlag;
    u8 doHizukiMiyaburiFlag;
    u8 doItemSoubiTokukoutokubouupFlag;
    u8 keikentihueruFlag;
    u8 bossFlag;
    u8 dorobouFlag;
    u8 monohiroiFlag;
    u8 darkpokemonHypermodeFlag;
    u8 pokemonStatusMenuSubbarFlag;
    u8 hostEnemyMsgFlag;
    u8 regulationFlag;
    u8 unk1A[2];
    u32 name;
};

extern "C" {

extern u32* fight_kind_data_number;
extern FightKindData* fight_kind_data;
u16 fightGetFightEncountDataId(void);
void* fightEncountDataBiosGetPtr(u16 id);
u8 fightEncountDataBiosGetFightKind(void* data);

u8 fightKind_CheckFightKind(u8 kind) {
    return fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightGetFightEncountDataId())) == kind;
}

u8 fightKindDataBiosGetRegulationFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->regulationFlag ? 1 : 0;
}

u32 fightKindDataBiosGetName(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->name;
}

u8 fightKindDataBiosGetHostEnemyMsgFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->hostEnemyMsgFlag ? 1 : 0;
}

u8 fightKindDataBiosGetPokemonStatusMenuSubbarFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->pokemonStatusMenuSubbarFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDarkpokemonHypermodeFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->darkpokemonHypermodeFlag ? 1 : 0;
}

u8 fightKindDataBiosGetMonohiroiFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->monohiroiFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDorobouFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->dorobouFlag ? 1 : 0;
}

u8 fightKindDataBiosGetBossFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->bossFlag ? 1 : 0;
}

u8 fightKindDataBiosGetKeikentihueruFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->keikentihueruFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doItemSoubiTokukoutokubouupFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoHizukiMiyaburiFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doHizukiMiyaburiFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoHizukiAiFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doHizukiAiFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoCriticalAttackFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doCriticalAttackFlag ? 1 : 0;
}

u8 fightKindDataBiosGetGetInfectPokerusFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->getInfectPokerusFlag ? 1 : 0;
}

u8 fightKindDataBiosGetGetFriendFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->getFriendFlag ? 1 : 0;
}

u8 fightKindDataBiosGetGetNekoniKobanFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->getNekoniKobanFlag ? 1 : 0;
}

u8 fightKindDataBiosGetGetOkaneFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->getOkaneFlag ? 1 : 0;
}

u8 fightKindDataBiosGetOkanePoolFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->okanePoolFlag ? 1 : 0;
}

u8 fightKindDataBiosGetGetExpFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->getExpFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDrawFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->drawFlag ? 1 : 0;
}

u8 fightKindDataBiosGetNigeruFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->nigeruFlag ? 1 : 0;
}

u8 fightKindDataBiosGetCallFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->callFlag ? 1 : 0;
}

u8 fightKindDataBiosGetUseItemFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->useItemFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoZukanTukamaetaFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doZukanTukamaetaFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoZukanMitaFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doZukanMitaFlag ? 1 : 0;
}

u8 fightKindDataBiosGetDoBadgeCheckFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->doBadgeCheckFlag ? 1 : 0;
}

FightKindData* fightKindDataBiosGetPtr(u16 id) {
    if (id > *fight_kind_data_number) {
        return 0;
    }
    return &fight_kind_data[id];
}

u8 fightKindDataBiosGetBackSaveDataFlag(FightKindData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->backSaveDataFlag ? 1 : 0;
}

}
