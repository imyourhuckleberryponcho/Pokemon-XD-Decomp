#include <dolphin/types.h>

#pragma optimize_for_size on

struct Hero {
    u8 getHeroStyle() const;
};

struct TrainerEnemyPokemon {
    s16 fightEntryId;
    u8 storeWazaNum;
    u8 expectWazaNum;
    u16 storeWaza[4];
    u16 expectWaza[8];
    u8 tokuseiFlag;
    u8 unk1D;
    u16 storeTokuseiData;
    u8 nowhp1banhikuiFlag;
    u8 lv1banhikuiFlag;
    u8 defense1banhikuiFlag;
    u8 badwazaHaveFlag;
    u8 param1bantakaiFlag;
    u8 unk25;
};

struct FightTrainerAiValueAddsubData {
    u32 value;
    u32 koudouName;
    u32 prefixName;
    u32 name;
    u32 unk10;
};

struct FightTrainerPokemonPartData {
    u32 name;
    u8 unk4[4];
    u8 wazaTypeRevise[14];
    u8 unk16[2];
};

class DeckPokemon {
public:
    u16 pokemonId;
    u8 level;
    u8 friendLevel;
    u16 holdItem;
    u8 role;
    u8 keyPlayer;
    u8 statusRnd[6];
    u8 statusEffort[6];
    u16 waza[4];
    u16 unk1C;
    u8 seikaku : 5;
    u8 sex : 2;
    u8 tokusei : 1;
    u8 unk1F;

    static DeckPokemon* getDeckPokemonObj(u32 id);
    u16 getPokemonID() const;
    u8 getLevel() const;
    u8 getFriendLevel() const;
    u16 getHoldItem() const;
    u8 getRole() const;
    u8 getKeyPlayer() const;
    u8 getStatusRnd(u8 index) const;
    u8 getStatusEffort(u8 index) const;
    u16 getWazaID(u8 index) const;
    u8 getSeikakuID() const;
    u8 getSex() const;
    u8 getTokuseiFlag() const;
};

class DeckTrainer {
public:
    static DeckTrainer* getDeckTrainerObj(u32 id);
    u8 getTrainerKind() const;
    u16 getAIID() const;
    u16 getIntroWZX() const;
    u16 getTrainerPKX() const;
    u16 getTrainerName() const;
    u16 getPokemonDataID(u8 index) const;
    u16 getTrainerItem(u8 index) const;
    u16 getTrainerMsg(u8 index) const;
    void setTrainerKind(u8 kind);
    void setAIID(u16 id);
    void setIntroWZX(u16 id);
    void setTrainerPKX(u16 id);
    void setTrainerName(u16 id);
    void setPokemonDataID(u8 index, u16 id);
    void setTrainerItem(u8 index, u16 id);
    void setTrainerMsg(u8 index, u16 id);
};

class DeckTrainerAI {
public:
    static DeckTrainerAI* getDeckTrainerAIObj(u32 id);
    u8 getTotalCorrection() const;
    void setTotalCorrection(u8 v);
    u8 getLastPPDetermRate() const;
    void setLastPPDetermRate(u8 v);
    u8 getLowHPDetermRate() const;
    void setLowHPDetermRate(u8 v);
    u8 getAnnihilateDetermRate() const;
    void setAnnihilateDetermRate(u8 v);
    u8 getHitRate() const;
    void setHitRate(u8 v);
    u8 getItemUseRate() const;
    void setItemUseRate(u8 v);
    u8 getPokeChgRate() const;
    void setPokeChgRate(u8 v);
    u8 getStatusDetermValTotalMin() const;
    void setStatusDetermValTotalMin(u8 v);
    u8 getStatusDetermValTotalMax() const;
    void setStatusDetermValTotalMax(u8 v);
    u8 getRespectPokemonCondJuge() const;
    void setRespectPokemonCondJuge(bool v);
    u8 getRespectWazaRiskJudge() const;
    void setRespectWazaRiskJudge(bool v);
    u8 getRespectWazaHit() const;
    void setRespectWazaHit(bool v);
    u8 getRespectRole() const;
    void setRespectRole(bool v);
    u8 getRespectWazaAssmntVal() const;
    void setRespectWazaAssmntVal(bool v);
    u8 getSelectRandomWaza() const;
    void setSelectRandomWaza(bool v);
    u8 getSelectRandomDefence() const;
    void setSelectRandomDefence(bool v);
    u8 getCalcWazaDamage() const;
    void setCalcWazaDamage(bool v);
    u8 getAbilityDetermination() const;
    void setAbilityDetermination(bool v);
    u8 getAttrDetermination() const;
    void setAttrDetermination(bool v);
    u8 getRespectKeyPlayer() const;
    void setRespectKeyPlayer(bool v);
    u8 getSelectAceBoss() const;
    void setSelectAceBoss(bool v);
    u8 getOrder() const;
    void setOrder(bool v);
    u8 getNotSameWeekPoint() const;
    void setNotSameWeekPoint(bool v);
    u8 getSelectRandomPokemon() const;
    void setSelectRandomPokemon(bool v);
    u8 getWazaKindParam(u8 i) const;
    void setWazaKindParam(u8 i, u8 v);
    u16 getWazaKindID(u8 i) const;
    void setWazaKindID(u8 i, u16 v);
    u8 getAttrTypeParam(u8 i) const;
    void setAttrTypeParam(u8 i, u8 v);
    u8 getAttrTypeID(u8 i) const;
    void setAttrTypeID(u8 i, u8 v);
    u8 getStatusDetermValMin(u8 i) const;
    u8 getStatusDetermValMax(u8 i) const;
};

extern "C" {

FightTrainerAiValueAddsubData* fightTrainerAiValueAddsubDataBiosGetPtr(u16 id);
FightTrainerPokemonPartData* fightTrainerPokemonPartDataBiosGetPtr(u16 id);
DeckTrainer* fightTrainerDataBiosGetPtr(u16 id);
TrainerEnemyPokemon* fightTrainerGetFightEntryIdToEnemyPokemonPtr(u8* t, s16 id);
bool fightTrainerEnemyPokemonRegistAry(TrainerEnemyPokemon* ary, u16 num, s16 id);
Hero* savedataGetStatus(void* save, s32 kind);
void* fightTrainer_GetFightTrainerEnemyPokemonAryPtr(u8* t, u8 i);

void fightTrainer_SetEnemyPokemonRegist(u8* t, s16 id) {
    if (t != 0) {
        TrainerEnemyPokemon* ary = (TrainerEnemyPokemon*)fightTrainer_GetFightTrainerEnemyPokemonAryPtr(t, 0);
        if (ary != 0) {
            fightTrainerEnemyPokemonRegistAry(ary, 12, id);
        }
    }
}

void fightTrainer_SetEnemyParam1bantakaiFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->param1bantakaiFlag = v;
        }
    }
}

void fightTrainer_SetEnemyBadwazaHaveFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->badwazaHaveFlag = v;
        }
    }
}

void fightTrainer_SetEnemyDefense1banhikuiFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->defense1banhikuiFlag = v;
        }
    }
}

void fightTrainer_SetEnemyLv1banhikuiFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->lv1banhikuiFlag = v;
        }
    }
}

void fightTrainer_SetEnemyNowhp1banhikuiFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->nowhp1banhikuiFlag = v;
        }
    }
}

void fightTrainer_SetEnemyStoreTokuseiData(u8* t, s16 id, u16 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->storeTokuseiData = v;
        }
    }
}

void fightTrainer_SetEnemyTokuseiFlag(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->tokuseiFlag = v;
        }
    }
}

void fightTrainer_SetEnemyExpectWazaData(u8* t, s16 id, u8 index, u16 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->expectWaza[index] = v;
        }
    }
}

void fightTrainer_SetEnemyStoreWazaData(u8* t, s16 id, u8 index, u16 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->storeWaza[index] = v;
        }
    }
}

void fightTrainer_SetEnemyExpectWazaNum(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->expectWazaNum = v;
        }
    }
}

void fightTrainer_SetEnemyStoreWazaNum(u8* t, s16 id, u8 v) {
    if (t != 0) {
        TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
        if (p != 0) {
            p->storeWazaNum = v;
        }
    }
}

void fightTrainer_SetSequencePtr(u8* t, u32 v) {
    if (t == 0) return;
    *(u32*)(t + 0x3544) = v;
}

void fightTrainer_SetControllerId(u8* t, u8 v) {
    if (t == 0) return;
    *(u8*)(t + 0x3540) = v;
}

void fightTrainer_SetNigeruCount(u8* t, u8 v) {
    if (t == 0) return;
    *(u8*)(t + 0x3539) = v;
}

void fightTrainer_SetKoban(u8* t, u32 v) {
    if (t == 0) return;
    *(u32*)(t + 0x353c) = v;
}

void fightTrainer_SetOkaneBai(u8* t, u8 v) {
    if (t == 0) return;
    *(u8*)(t + 0x3538) = v;
}

void fightTrainer_SetFightTrainerDataId(u8* t, u16 v) {
    if (t == 0) return;
    *(u16*)(t + 0x0) = v;
}

void fightTrainerAiValueAddsubDB_SetPrefixName(u16 id, u32 v) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d != 0) {
        d->prefixName = v;
    }
}

void fightTrainerAiValueAddsubDB_SetKoudouName(u16 id, u32 v) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d != 0) {
        d->koudouName = v;
    }
}

void fightTrainerAiValueAddsubDB_SetName(u16 id, u32 v) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d != 0) {
        d->name = v;
    }
}

void fightTrainerAiValueAddsubDB_SetValue(u16 id, u32 v) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d != 0) {
        d->value = v;
    }
}

u8 fightTrainer_GetEnemyParam1bantakaiFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->param1bantakaiFlag;
}

u8 fightTrainer_GetEnemyBadwazaHaveFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->badwazaHaveFlag;
}

u8 fightTrainer_GetEnemyDefense1banhikuiFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->defense1banhikuiFlag;
}

u8 fightTrainer_GetEnemyLv1banhikuiFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->lv1banhikuiFlag;
}

u8 fightTrainer_GetEnemyNowhp1banhikuiFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->nowhp1banhikuiFlag;
}

u16 fightTrainer_GetEnemyStoreTokuseiData(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->storeTokuseiData;
}

u8 fightTrainer_GetEnemyTokuseiFlag(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->tokuseiFlag;
}

u16 fightTrainer_GetEnemyExpectWazaData(u8* t, s16 id, u8 index) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    if (index > 8) {
        return 0;
    }
    return p->expectWaza[index];
}

u16 fightTrainer_GetEnemyStoreWazaData(u8* t, s16 id, u8 index) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return p->storeWaza[index];
}

u8 fightTrainer_GetEnemyStoreWazaNum(u8* t, s16 id) {
    if (t == 0) {
        return 0;
    }
    TrainerEnemyPokemon* p = fightTrainerGetFightEntryIdToEnemyPokemonPtr(t, id);
    if (p == 0) {
        return 0;
    }
    return p->storeWazaNum;
}

void* fightTrainer_GetFightTrainerEnemyPokemonAryPtr(u8* t, u8 i) {
    if (t == 0) return 0;
    if (i >= 12) return 0;
    return t + 0x3578 + i * 0x26;
}

u32 fightTrainer_GetSequencePtr(u8* t) {
    if (t == 0) return 0;
    return *(u32*)(t + 0x3544);
}

void* fightTrainer_GetFightActionBuffPtr(u8* t) {
    if (t == 0) return 0;
    return t + 0x3548;
}

u8 fightTrainer_GetControllerId(u8* t) {
    if (t == 0) return 0;
    return *(u8*)(t + 0x3540);
}

u8 fightTrainer_GetNigeruCount(u8* t) {
    if (t == 0) return 0;
    return *(u8*)(t + 0x3539);
}

u32 fightTrainer_GetKoban(u8* t) {
    if (t == 0) return 0;
    return *(u32*)(t + 0x353c);
}

u8 fightTrainer_GetOkaneBai(u8* t) {
    if (t == 0) return 0;
    return *(u8*)(t + 0x3538);
}

void* fightTrainer_GetFightoutPokemonBuffPtr(u8* t) {
    if (t == 0) return 0;
    return t + 0x2ca4;
}

void* fightTrainer_GetFightoutPokemonPtr(u8* t, u16 i) {
    if (t == 0) return 0;
    if (i >= 2) return 0;
    return t + 0x1b7c + i * 0x894;
}

void* fightTrainer_GetFightPokemonPtr(u8* t, u16 i) {
    if (t == 0) return 0;
    if (i >= 6) return 0;
    return t + 0x97c + i * 0x300;
}

u16 fightTrainer_GetFightTrainerDataId(u8* t) {
    if (t == 0) return 0;
    return *(u16*)(t + 0x0);
}

void* fightTrainer_GetHeroPtr(u8* t) {
    if (t == 0) return 0;
    return t + 0x4;
}

u32 fightTrainerAiValueAddsubDB_GetPrefixName(u16 id) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    return d->prefixName;
}

u32 fightTrainerAiValueAddsubDB_GetKoudouName(u16 id) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    return d->koudouName;
}

u32 fightTrainerAiValueAddsubDB_GetName(u16 id) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    return d->name;
}

u32 fightTrainerAiValueAddsubDB_GetValue(u16 id) {
    FightTrainerAiValueAddsubData* d = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    return d->value;
}

void fightTrainerAiDB_SetParamStoreFlag(u16 id, u8 v) {
}

u8 fightTrainerAiDB_GetParamStoreFlag(u16 id) {
    return 1;
}

void fightTrainerAiDB_SetParamExpectFlag(u16 id, u8 v) {
}

u8 fightTrainerAiDB_GetParamExpectFlag(u16 id) {
    return 1;
}

void fightTrainerAiDB_SetComboValue(u16 id, u8 v) {
}

u8 fightTrainerAiDB_GetComboValue(u16 id) {
    return 100;
}

void fightTrainerAiDB_SetLastValueRevise(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setTotalCorrection(v);
    }
}

u8 fightTrainerAiDB_GetLastValueRevise(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getTotalCorrection();
}

void fightTrainerAiDB_SetWazaTypeReviseValue(u16 id, u8 index, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0 && index < 2) {
        ai->setWazaKindParam(index, v);
    }
}

u8 fightTrainerAiDB_GetWazaTypeReviseValue(u16 id, u8 index) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return ai->getWazaKindParam(index);
}

void fightTrainerAiDB_SetWazaTypeReviseTypeDataId(u16 id, u8 index, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0 && index < 2) {
        ai->setWazaKindID(index, v);
    }
}

u8 fightTrainerAiDB_GetWazaTypeReviseTypeDataId(u16 id, u8 index) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return ai->getWazaKindID(index);
}

void fightTrainerAiDB_SetZokuseiReviseValue(u16 id, u8 index, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0 && index < 2) {
        ai->setAttrTypeParam(index, v);
    }
}

u8 fightTrainerAiDB_GetZokuseiReviseValue(u16 id, u8 index) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return ai->getAttrTypeParam(index);
}

void fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(u16 id, u8 index, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0 && index < 2) {
        ai->setAttrTypeID(index, v);
    }
}

u8 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16 id, u8 index) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    return ai->getAttrTypeID(index);
}

void fightTrainerAiDB_SetWazaNokoriPpValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setLastPPDetermRate(v);
    }
}

u8 fightTrainerAiDB_GetWazaNokoriPpValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getLastPPDetermRate();
}

void fightTrainerAiDB_SetNokoriHpValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setLowHPDetermRate(v);
    }
}

u8 fightTrainerAiDB_GetNokoriHpValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getLowHPDetermRate();
}

u8 fightTrainerAiDB_GetStrokeValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getAnnihilateDetermRate();
}

void fightTrainerAiDB_SetWazaAvgValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setHitRate(v);
    }
}

u8 fightTrainerAiDB_GetWazaAvgValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getHitRate();
}

void fightTrainerAiDB_SetItemValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setItemUseRate(v);
    }
}

u8 fightTrainerAiDB_GetItemValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getItemUseRate();
}

void fightTrainerAiDB_SetIrekaeValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setPokeChgRate(v);
    }
}

u8 fightTrainerAiDB_GetIrekaeValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getPokeChgRate();
}

void fightTrainerAiDB_SetAbicntMinValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setStatusDetermValTotalMin(v);
    }
}

u8 fightTrainerAiDB_GetAbicntMinValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValTotalMin();
}

void fightTrainerAiDB_SetAbicntMaxValue(u16 id, u8 v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setStatusDetermValTotalMax(v);
    }
}

u8 fightTrainerAiDB_GetAbicntMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValTotalMax();
}

u8 fightTrainerAiDB_GetAvoidMinValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMin(6);
}

u8 fightTrainerAiDB_GetAvoidMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(6);
}

u8 fightTrainerAiDB_GetNimblenessMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(4);
}

u8 fightTrainerAiDB_GetSpeDefMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(3);
}

u8 fightTrainerAiDB_GetSpeAtkMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(2);
}

u8 fightTrainerAiDB_GetPhyDefMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(1);
}

u8 fightTrainerAiDB_GetPhyAtkMaxValue(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getStatusDetermValMax(0);
}

void fightTrainerAiDB_SetPokemonJoutaiFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectPokemonCondJuge(v);
    }
}

u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectPokemonCondJuge();
}

void fightTrainerAiDB_SetWazaRiskFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectWazaRiskJudge(v);
    }
}

u8 fightTrainerAiDB_GetWazaRiskFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectWazaRiskJudge();
}

void fightTrainerAiDB_SetWazaHitFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectWazaHit(v);
    }
}

u8 fightTrainerAiDB_GetWazaHitFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectWazaHit();
}

void fightTrainerAiDB_SetPartFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectRole(v);
    }
}

u8 fightTrainerAiDB_GetPartFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectRole();
}

void fightTrainerAiDB_SetWazaInitValueFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectWazaAssmntVal(v);
    }
}

u8 fightTrainerAiDB_GetWazaInitValueFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectWazaAssmntVal();
}

void fightTrainerAiDB_SetWazaRndSelectFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setSelectRandomWaza(v);
    }
}

u8 fightTrainerAiDB_GetWazaRndSelectFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getSelectRandomWaza();
}

void fightTrainerAiDB_SetDefensePokemonRndSelectFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setSelectRandomDefence(v);
    }
}

u8 fightTrainerAiDB_GetDefensePokemonRndSelectFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getSelectRandomDefence();
}

void fightTrainerAiDB_SetWazaDamageFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setCalcWazaDamage(v);
    }
}

u8 fightTrainerAiDB_GetWazaDamageFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getCalcWazaDamage();
}

void fightTrainerAiDB_SetTokuseiCheckFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setAbilityDetermination(v);
    }
}

u8 fightTrainerAiDB_GetTokuseiCheckFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getAbilityDetermination();
}

void fightTrainerAiDB_SetZokuseiCheckFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setAttrDetermination(v);
    }
}

u8 fightTrainerAiDB_GetZokuseiCheckFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getAttrDetermination();
}

void fightTrainerAiDB_SetKeyPlayerFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setRespectKeyPlayer(v);
    }
}

u8 fightTrainerAiDB_GetKeyPlayerFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getRespectKeyPlayer();
}

void fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setSelectAceBoss(v);
    }
}

u8 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getSelectAceBoss();
}

void fightTrainerAiDB_SetPokemonDataOrderOutFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setOrder(v);
    }
}

u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getOrder();
}

void fightTrainerAiDB_SetPokemonSelectWeakPointFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setNotSameWeekPoint(v);
    }
}

u8 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getNotSameWeekPoint();
}

void fightTrainerAiDB_SetPokemonSelectRandomFlag(u16 id, bool v) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai != 0) {
        ai->setSelectRandomPokemon(v);
    }
}

u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16 id) {
    DeckTrainerAI* ai = DeckTrainerAI::getDeckTrainerAIObj(id);
    if (ai == 0) {
        return 0;
    }
    return ai->getSelectRandomPokemon();
}

void fightTrainerPokemonPartDB_SetWazaTypeRevise(u16 id, u8 index, u8 v) {
    FightTrainerPokemonPartData* d = fightTrainerPokemonPartDataBiosGetPtr(id);
    if (d != 0 && index < 14) {
        d->wazaTypeRevise[index] = v;
    }
}

u8 fightTrainerPokemonPartDB_GetWazaTypeRevise(u16 id, u8 index) {
    FightTrainerPokemonPartData* d = fightTrainerPokemonPartDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    if (index >= 14) {
        return 0;
    }
    return d->wazaTypeRevise[index];
}

void fightTrainerPokemonPartDB_SetName(u16 id, u32 v) {
    FightTrainerPokemonPartData* d = fightTrainerPokemonPartDataBiosGetPtr(id);
    if (d != 0) {
        d->name = v;
    }
}

u32 fightTrainerPokemonPartDB_GetName(u16 id) {
    FightTrainerPokemonPartData* d = fightTrainerPokemonPartDataBiosGetPtr(id);
    if (d == 0) {
        return 0;
    }
    return d->name;
}

void fightTrainerPokemonDB_SetPpCnt(u16 id, u32 v) {
}

u32 fightTrainerPokemonDB_GetPpCnt(u16 id) {
    return 0;
}

void fightTrainerPokemonDB_SetDarkPokemonFlag(u16 id, u32 v) {
}

u32 fightTrainerPokemonDB_GetDarkPokemonFlag(u16 id) {
    return 0;
}

void fightTrainerPokemonDB_SetItemBallId(u16 id, u32 v) {
}

u32 fightTrainerPokemonDB_GetItemBallId(u16 id) {
    return 0;
}

void fightTrainerPokemonDB_SetNickname(u16 id, u32 v) {
}

u32 fightTrainerPokemonDB_GetNickname(u16 id) {
    return 0;
}

void fightTrainerPokemonDB_SetPartDataId(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->role = v;
    }
}

u8 fightTrainerPokemonDB_GetPartDataId(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getRole();
}

void fightTrainerPokemonDB_SetKeyPlayerFlag(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->keyPlayer = v;
    }
}

u8 fightTrainerPokemonDB_GetKeyPlayerFlag(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getKeyPlayer();
}

void fightTrainerPokemonDB_SetWazaDataId(u16 id, u8 index, u16 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->waza[index] = v;
    }
}

u16 fightTrainerPokemonDB_GetWazaDataId(u16 id, u8 index) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getWazaID(index);
}

void fightTrainerPokemonDB_SetStatusEffort(u16 id, u8 index, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0 && index < 6) {
        p->statusEffort[index] = v;
    }
}

u8 fightTrainerPokemonDB_GetStatusEffort(u16 id, u8 index) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return p->getStatusEffort(index);
}

void fightTrainerPokemonDB_SetStatusRnd(u16 id, u8 index, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0 && index < 6) {
        p->statusRnd[index] = v;
    }
}

u8 fightTrainerPokemonDB_GetStatusRnd(u16 id, u8 index) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return p->getStatusRnd(index);
}

void fightTrainerPokemonDB_SetItemDataId(u16 id, u16 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->holdItem = v;
    }
}

u16 fightTrainerPokemonDB_GetItemDataId(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getHoldItem();
}

void fightTrainerPokemonDB_SetTokuseiFlag(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->tokusei = v;
    }
}

u8 fightTrainerPokemonDB_GetTokuseiFlag(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getTokuseiFlag();
}

void fightTrainerPokemonDB_SetSeikakuDataId(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->seikaku = v;
    }
}

u8 fightTrainerPokemonDB_GetSeikakuDataId(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getSeikakuID();
}

void fightTrainerPokemonDB_SetSexDataId(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->sex = v;
    }
}

u8 fightTrainerPokemonDB_GetSexDataId(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getSex();
}

void fightTrainerPokemonDB_SetFriend(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->friendLevel = v;
    }
}

u8 fightTrainerPokemonDB_GetFriend(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getFriendLevel();
}

void fightTrainerPokemonDB_SetLevel(u16 id, u8 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->level = v;
    }
}

u8 fightTrainerPokemonDB_GetLevel(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getLevel();
}

void fightTrainerPokemonDB_SetPokemonDataId(u16 id, u16 v) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p != 0) {
        p->pokemonId = v;
    }
}

u16 fightTrainerPokemonDB_GetPokemonDataId(u16 id) {
    DeckPokemon* p = DeckPokemon::getDeckPokemonObj(id);
    if (p == 0) {
        return 0;
    }
    return p->getPokemonID();
}

u32 fightTrainerDB_GetSexDataId(u16 id) {
    return 0;
}

void fightTrainerDB_SetTemotiItemDataId(u16 id, u8 index, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0 && index < 4) {
        t->setTrainerItem(index, v);
    }
}

u16 fightTrainerDB_GetTemotiItemDataId(u16 id, u8 index) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return t->getTrainerItem(index);
}

void fightTrainerDB_SetAiDataId(u16 id, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0) {
        t->setAIID(v);
    }
}

u16 fightTrainerDB_GetAiDataId(u16 id) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    return t->getAIID();
}

void fightTrainerDB_SetTemotiPokemonId(u16 id, u8 index, u16 v) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id < 5000 && t != 0) {
        t->setPokemonDataID(index, v);
    }
}

u16 fightTrainerDB_GetTemotiPokemonId(u16 id, u8 index) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    return t->getPokemonDataID(index);
}

void fightTrainerDB_SetSerihuMsgId(u16 id, u8 index, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0 && index < 4) {
        t->setTrainerMsg(index, v);
    }
}

u16 fightTrainerDB_GetSerihuMsgId(u16 id, u8 index) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return t->getTrainerMsg(index);
}

void fightTrainerDB_SetSyoukaiWzxDataId(u16 id, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0) {
        t->setIntroWZX(v);
    }
}

u16 fightTrainerDB_GetSyoukaiWzxDataId(u16 id) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    return t->getIntroWZX();
}

void fightTrainerDB_SetPkxDataId(u16 id, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0) {
        t->setTrainerPKX(v);
    }
}

u16 fightTrainerDB_GetPkxDataId(u16 id) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (t->getTrainerKind() == 1 || id == 5000) {
        Hero* hero = savedataGetStatus(0, 2);
        if (hero != 0) {
            switch (hero->getHeroStyle()) {
            case 0:
                return 1;
            case 1:
                return 3;
            case 2:
                return 2;
            }
        }
    }
    switch (id) {
    case 5001:
        return 9;
    case 5002:
        return 8;
    case 5003:
        return 7;
    case 5004:
        return 6;
    case 5005:
        return 5;
    case 5006:
        return 4;
    }
    if (t == 0) {
        return 0;
    }
    return t->getTrainerPKX();
}

void fightTrainerDB_SetKindDataId(u16 id, u8 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0) {
        t->setTrainerKind(v);
    }
}

u8 fightTrainerDB_GetKindDataId(u16 id) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    switch (id) {
    case 5000:
        return 1;
    case 5001:
    case 5003:
    case 5005:
        return 2;
    case 5002:
    case 5004:
    case 5006:
        return 3;
    }
    if (t == 0) {
        return 0;
    }
    return t->getTrainerKind();
}

void fightTrainerDB_SetName(u16 id, u16 v) {
    DeckTrainer* t = fightTrainerDataBiosGetPtr(id);
    if (t != 0) {
        t->setTrainerName(v);
    }
}

u16 fightTrainerDB_GetName(u16 id) {
    DeckTrainer* t = DeckTrainer::getDeckTrainerObj(id);
    if (id >= 5000) {
        return 0;
    }
    if (t == 0) {
        return 0;
    }
    return t->getTrainerName();
}

}
