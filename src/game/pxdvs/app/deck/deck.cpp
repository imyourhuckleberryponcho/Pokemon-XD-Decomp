#include <dolphin/types.h>
#pragma pool_strings off

// Trainer/Pokemon deck tables, loaded from a "DECK" chunk file (deckRegister).
// The unit was built with -inline deferred: functions are written here in reverse object order.

class CChank {
public:
    char* m_data;
    char* m_end;
    s32 m_count;

    CChank();
    virtual ~CChank() {}
    char* searchSubChankID(const char* id);
};

class CChankBlock : public CChank {
public:
    virtual ~CChankBlock() {}
    bool loadFromMemory(char* data, char* id);
};

struct PokemonWaza {
    u16 id;
};

class Pokemon {
public:
    u8 getSex() const;
    u8 getSeikaku() const;
    u8 getLevel() const;
    u16 getFriendLevel() const;
    bool isTokuseiFlag() const;
    PokemonWaza* getPokemonWaza(u16 index);
};

class DarkPokemon {
public:
    void init();
    void setDarkPoint(f32 point);
    void setPokemonID(u16 id);
    void setDarkPokemonID(u16 id);

    u8 unk0[0x48];
};

struct DeckStatusDetermVal {
    u8 max : 4;
    u8 min : 4;
};

class DeckTrainerAI {
public:
    static DeckTrainerAI* getDeckTrainerAIObj(u32 index);

    void setTotalCorrection(u8 value);
    u8 getTotalCorrection() const;
    void setWazaKindParam(u8 index, u8 value);
    u8 getWazaKindParam(u8 index) const;
    void setWazaKindID(u8 index, u16 value);
    u16 getWazaKindID(u8 index) const;
    void setAttrTypeParam(u8 index, u8 value);
    u8 getAttrTypeParam(u8 index) const;
    void setAttrTypeID(u8 index, u8 value);
    u8 getAttrTypeID(u8 index) const;
    void setLastPPDetermRate(u8 value);
    u8 getLastPPDetermRate() const;
    void setLowHPDetermRate(u8 value);
    u8 getLowHPDetermRate() const;
    u8 getAnnihilateDetermRate() const;
    void setHitRate(u8 value);
    u8 getHitRate() const;
    void setItemUseRate(u8 value);
    u8 getItemUseRate() const;
    void setPokeChgRate(u8 value);
    u8 getPokeChgRate() const;
    void setStatusDetermValTotalMin(u8 value);
    u8 getStatusDetermValTotalMin() const;
    void setStatusDetermValTotalMax(u8 value);
    u8 getStatusDetermValTotalMax() const;
    u8 getStatusDetermValMin(u8 index) const;
    u8 getStatusDetermValMax(u8 index) const;
    void setRespectPokemonCondJuge(bool value);
    bool getRespectPokemonCondJuge() const;
    void setRespectWazaRiskJudge(bool value);
    bool getRespectWazaRiskJudge() const;
    void setRespectWazaHit(bool value);
    bool getRespectWazaHit() const;
    void setRespectRole(bool value);
    bool getRespectRole() const;
    void setRespectWazaAssmntVal(bool value);
    bool getRespectWazaAssmntVal() const;
    void setSelectRandomWaza(bool value);
    bool getSelectRandomWaza() const;
    void setSelectRandomDefence(bool value);
    bool getSelectRandomDefence() const;
    void setCalcWazaDamage(bool value);
    bool getCalcWazaDamage() const;
    void setAbilityDetermination(bool value);
    bool getAbilityDetermination() const;
    void setAttrDetermination(bool value);
    bool getAttrDetermination() const;
    void setRespectKeyPlayer(bool value);
    bool getRespectKeyPlayer() const;
    void setSelectAceBoss(bool value);
    bool getSelectAceBoss() const;
    void setOrder(bool value);
    bool getOrder() const;
    void setNotSameWeekPoint(bool value);
    bool getNotSameWeekPoint() const;
    void setSelectRandomPokemon(bool value);
    bool getSelectRandomPokemon() const;

    u8 selectRandomPokemon : 1;      // 0x00
    u8 notSameWeekPoint : 1;
    u8 order : 1;
    u8 selectAceBoss : 1;
    u8 respectKeyPlayer : 1;
    u8 attrDetermination : 1;
    u8 abilityDetermination : 1;
    u8 calcWazaDamage : 1;
    u8 selectRandomDefence : 1;      // 0x01
    u8 selectRandomWaza : 1;
    u8 respectWazaAssmntVal : 1;
    u8 respectRole : 1;
    u8 respectWazaHit : 1;
    u8 respectWazaRiskJudge : 1;
    u8 respectPokemonCondJuge : 1;
    u8 unk1_0 : 1;
    u8 unk2[2];
    DeckStatusDetermVal statusDetermVal[8];  // 0x04
    u8 statusDetermValTotalMax;      // 0x0C
    u8 statusDetermValTotalMin;      // 0x0D
    u8 pokeChgRate;                  // 0x0E
    u8 itemUseRate;                  // 0x0F
    u8 hitRate;                      // 0x10
    u8 annihilateDetermRate;         // 0x11
    u8 lowHPDetermRate;              // 0x12
    u8 lastPPDetermRate;             // 0x13
    u8 attrTypeID[2];                // 0x14
    u8 attrTypeParam[2];             // 0x16
    u16 wazaKindID[2];               // 0x18
    u8 wazaKindParam[2];             // 0x1C
    u8 totalCorrection;              // 0x1E
    u8 unk1F;
};

class DeckDarkPokemon {
public:
    static DeckDarkPokemon* getDeckDarkPokemonObj(u32 index);

    u8 getUnderTakerFlag() const;
    u8 getRevers() const;
    bool isScenarioPokemon() const;
    u16 getDarkWaza(s8 index) const;
    u16 getBonusExp() const;
    u16 getInitDarkPoint() const;
    u16 getDeckPokemonID() const;
    u8 getPlayerLevel() const;
    u8 getSnatchRatio() const;
    u8 getWorth() const;

    u8 worth;                 // 0x00
    u8 snatchRatio;           // 0x01
    u8 playerLevel;           // 0x02
    u8 scenarioPokemon : 1;   // 0x03
    u8 unk3 : 7;
    u32 deckPokemonID;        // 0x04
    u16 initDarkPoint;        // 0x08
    u16 bonusExp;             // 0x0A
    u16 darkWaza[4];          // 0x0C
    u8 revers;                // 0x14
    u8 underTakerFlag;        // 0x15
    u8 unk16[2];
};

class DeckPokemon {
public:
    static DeckPokemon* getDeckPokemonObj(u32 index);

    u8 getRandomSetting() const;
    u8 getTokuseiFlag() const;
    u8 getSex() const;
    u8 getSeikakuID() const;
    u8 getComboPartnerAll() const;
    u16 getWazaID(u8 index) const;
    u8 getStatusEffort(u8 index) const;
    u8 getStatusRnd(u8 index) const;
    u8 getKeyPlayer() const;
    u8 getRole() const;
    u16 getHoldItem() const;
    u8 getFriendLevel() const;
    u8 getLevel() const;
    u16 getPokemonID() const;

    void setPokemonID(u16 value) {
        if (this != 0) {
            pokemonID = value;
        }
    }
    void setSex(u8 value) {}
    void setSeikakuID(u8 value) {
        if (this != 0) {
            seikakuID = value;
        }
    }
    void setLevel(u8 value) {
        if (this != 0) {
            level = value;
        }
    }
    void setStatusEffort(u8 index, u8 value) {
        if (this != 0) {
            if (index < 6) {
                statusEffort[index] = value;
            }
        }
    }
    void setStatusRnd(u8 index, u8 value) {
        if (this != 0) {
            if (index < 6) {
                statusRnd[index] = value;
            }
        }
    }
    void setFriendLevel(u8 value) {
        if (this != 0) {
            friendLevel = value;
        }
    }
    void setTokuseiFlag(u8 value) {
        if (this != 0) {
            tokuseiFlag = value;
        }
    }
    void setWazaID(u8 index, u16 value) {
        if (this != 0) {
            if (index < 4) {
                wazaID[index] = value;
            }
        }
    }

    u16 pokemonID;            // 0x00
    u8 level;                 // 0x02
    u8 friendLevel;           // 0x03
    u16 holdItem;             // 0x04
    u8 role;                  // 0x06
    u8 keyPlayer;             // 0x07
    u8 statusRnd[6];          // 0x08
    u8 statusEffort[6];       // 0x0E
    u16 wazaID[4];            // 0x14
    u8 unk1C;
    u8 comboPartnerAll;       // 0x1D
    u8 seikakuID : 5;         // 0x1E
    u8 sex : 2;
    u8 tokuseiFlag : 1;
    u8 randomSetting : 1;     // 0x1F
    u8 unk1F : 7;
};

class DeckTrainer {
public:
    static DeckTrainer* getDeckTrainerObj(u32 index);

    u8 getComboActive(u8 index) const;
    u16 getComboID(u8 index) const;
    u16 getFixedActionID() const;
    void setAIID(u16 value);
    u16 getAIID() const;
    void setPokemonDataID(u8 index, u16 value);
    u16 getDarkPokemonDataID(u8 index) const;
    u16 getPokemonDataID(u8 index) const;
    void setTrainerMsg(u8 index, u16 value);
    u16 getTrainerMsg(u8 index) const;
    void setIntroWZX(u16 value);
    u16 getIntroWZX() const;
    void setTrainerPKX(u16 value);
    u16 getTrainerPKX() const;
    void setTrainerItem(u8 index, u16 value);
    u16 getTrainerItem(u8 index) const;
    void setTrainerName(u16 value);
    u16 getTrainerName() const;
    void setTrainerKind(u8 value);
    u8 getTrainerKind() const;

    u16 getMsgOffset() const {
        if (this == 0) {
            return 0;
        }
        return msgOffset;
    }
    bool isDarkPokemon(u8 index) const {
        if (this == 0) {
            return false;
        }
        if (index >= 6) {
            return false;
        }
        return (darkPokemonFlags & (1 << index)) != 0;
    }

    u16 msgOffset;            // 0x00
    u8 unk2[2];
    u8 darkPokemonFlags;      // 0x04
    u8 trainerKind;           // 0x05
    u16 trainerName;          // 0x06
    u16 trainerItem[4];       // 0x08
    u16 trainerPKX;           // 0x10
    u16 introWZX;             // 0x12
    u16 trainerMsg[4];        // 0x14
    u16 pokemonDataID[6];     // 0x1C
    u16 aiID;                 // 0x28
    u16 fixedActionID;        // 0x2A
    u16 comboID[4];           // 0x2C
    u8 comboActive[4];        // 0x34
};

struct FightEncountData;

extern "C" {

FightEncountData* fightEncountDataBiosGetPtr(u16 id);
u16 fightEncountDataBiosGetFightTrainerDataId(FightEncountData* data, u8 index);
void* GSresGetResource(u32, u32);
void* savedataGetStatus(void* save, u16 kind);
u16 darkPokemonListBiosGetPokemonID(u16 index);
u16 pokemonGetStatus(Pokemon* pokemon, u32 kind, u16 id, u32 arg);

static DeckTrainer* _deckTrainer;
static DeckPokemon* _deckPokemon;
static DeckDarkPokemon* _deckDarkPokemon;
static DeckTrainerAI* _deckTrainerAI;
static u32 _deckTrainerSize;
static u32 _deckPokemonSize;
static u32 _deckDarkPokemonSize;
static u32 _deckTrainerAISize;
static char* _deckIDNameStr;

u8 DeckTrainer::getTrainerKind() const {
    if (this == 0) {
        return 0;
    }
    return trainerKind;
}

void DeckTrainer::setTrainerKind(u8 value) {
    if (this != 0) {
        trainerKind = value;
    }
}

u16 DeckTrainer::getTrainerName() const {
    if (this == 0) {
        return 0;
    }
    return trainerName;
}

void DeckTrainer::setTrainerName(u16 value) {
    if (this != 0) {
        trainerName = value;
    }
}

u16 DeckTrainer::getTrainerItem(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return trainerItem[index];
}

void DeckTrainer::setTrainerItem(u8 index, u16 value) {
    if (this != 0) {
        if (index < 4) {
            trainerItem[index] = value;
        }
    }
}

u16 DeckTrainer::getTrainerPKX() const {
    if (this == 0) {
        return 0;
    }
    return trainerPKX;
}

void DeckTrainer::setTrainerPKX(u16 value) {
    if (this != 0) {
        trainerPKX = value;
    }
}

u16 DeckTrainer::getIntroWZX() const {
    if (this == 0) {
        return 0;
    }
    return introWZX;
}

void DeckTrainer::setIntroWZX(u16 value) {
    if (this != 0) {
        introWZX = value;
    }
}

u16 DeckTrainer::getTrainerMsg(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return trainerMsg[index];
}

void DeckTrainer::setTrainerMsg(u8 index, u16 value) {
    if (this != 0) {
        if (index < 4) {
            trainerMsg[index] = value;
        }
    }
}

u16 DeckTrainer::getPokemonDataID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    u32 id = pokemonDataID[index];
    if (isDarkPokemon(index)) {
        DeckDarkPokemon* dark = DeckDarkPokemon::getDeckDarkPokemonObj(id);
        if (dark == 0) {
            return 0;
        }
        return dark->getDeckPokemonID();
    }
    return id;
}

u16 DeckTrainer::getDarkPokemonDataID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    if (isDarkPokemon(index)) {
        return pokemonDataID[index];
    }
    return 0;
}

void DeckTrainer::setPokemonDataID(u8 index, u16 value) {
    if (this != 0) {
        if (index < 6) {
            pokemonDataID[index] = value;
        }
    }
}

u16 DeckTrainer::getAIID() const {
    if (this == 0) {
        return 0;
    }
    return aiID;
}

void DeckTrainer::setAIID(u16 value) {
    if (this != 0) {
        aiID = value;
    }
}

u16 DeckTrainer::getFixedActionID() const {
    if (this == 0) {
        return 0;
    }
    return fixedActionID;
}

u16 DeckTrainer::getComboID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return comboID[index];
}

u8 DeckTrainer::getComboActive(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return comboActive[index];
}

u16 DeckPokemon::getPokemonID() const {
    if (this == 0) {
        return 0;
    }
    return pokemonID;
}

u8 DeckPokemon::getLevel() const {
    if (this == 0) {
        return 0;
    }
    return level;
}

u8 DeckPokemon::getFriendLevel() const {
    if (this == 0) {
        return 0;
    }
    return friendLevel;
}

u16 DeckPokemon::getHoldItem() const {
    if (this == 0) {
        return 0;
    }
    return holdItem;
}

u8 DeckPokemon::getRole() const {
    if (this == 0) {
        return 0;
    }
    return role;
}

u8 DeckPokemon::getKeyPlayer() const {
    if (this == 0) {
        return 0;
    }
    return keyPlayer;
}

u8 DeckPokemon::getStatusRnd(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return statusRnd[index];
}

u8 DeckPokemon::getStatusEffort(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return statusEffort[index];
}

u16 DeckPokemon::getWazaID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return wazaID[index];
}

u8 DeckPokemon::getComboPartnerAll() const {
    if (this == 0) {
        return 0;
    }
    return comboPartnerAll;
}

u8 DeckPokemon::getSeikakuID() const {
    if (this == 0) {
        return 0;
    }
    return seikakuID;
}

u8 DeckPokemon::getSex() const {
    if (this == 0) {
        return 0;
    }
    return sex;
}

u8 DeckPokemon::getTokuseiFlag() const {
    if (this == 0) {
        return 0;
    }
    return tokuseiFlag;
}

u8 DeckPokemon::getRandomSetting() const {
    if (this == 0) {
        return 0;
    }
    return randomSetting;
}

u8 DeckDarkPokemon::getWorth() const {
    if (this == 0) {
        return 0;
    }
    return worth;
}

u8 DeckDarkPokemon::getSnatchRatio() const {
    if (this == 0) {
        return 0;
    }
    return snatchRatio;
}

u8 DeckDarkPokemon::getPlayerLevel() const {
    if (this == 0) {
        return 0;
    }
    return playerLevel;
}

u16 DeckDarkPokemon::getDeckPokemonID() const {
    if (this == 0) {
        return 0;
    }
    return deckPokemonID;
}

u16 DeckDarkPokemon::getInitDarkPoint() const {
    if (this == 0) {
        return 0;
    }
    return initDarkPoint;
}

u16 DeckDarkPokemon::getBonusExp() const {
    if (this == 0) {
        return 0;
    }
    return bonusExp;
}

u16 DeckDarkPokemon::getDarkWaza(s8 index) const {
    if (this == 0) {
        return 0;
    }
    if (index < 0 || index >= 4) {
        return 0;
    }
    return darkWaza[index];
}

bool DeckDarkPokemon::isScenarioPokemon() const {
    if (this == 0) {
        return 0;
    }
    return scenarioPokemon == 1;
}

u8 DeckDarkPokemon::getRevers() const {
    if (this == 0) {
        return 0;
    }
    return revers;
}

u8 DeckDarkPokemon::getUnderTakerFlag() const {
    if (this == 0) {
        return 0;
    }
    return underTakerFlag;
}

bool DeckTrainerAI::getSelectRandomPokemon() const {
    if (this == 0) {
        return 0;
    }
    return selectRandomPokemon;
}

void DeckTrainerAI::setSelectRandomPokemon(bool value) {
    if (this != 0) {
        selectRandomPokemon = value;
    }
}

bool DeckTrainerAI::getNotSameWeekPoint() const {
    if (this == 0) {
        return 0;
    }
    return notSameWeekPoint;
}

void DeckTrainerAI::setNotSameWeekPoint(bool value) {
    if (this != 0) {
        notSameWeekPoint = value;
    }
}

bool DeckTrainerAI::getOrder() const {
    if (this == 0) {
        return 0;
    }
    return order;
}

void DeckTrainerAI::setOrder(bool value) {
    if (this != 0) {
        order = value;
    }
}

bool DeckTrainerAI::getSelectAceBoss() const {
    if (this == 0) {
        return 0;
    }
    return selectAceBoss;
}

void DeckTrainerAI::setSelectAceBoss(bool value) {
    if (this != 0) {
        selectAceBoss = value;
    }
}

bool DeckTrainerAI::getRespectKeyPlayer() const {
    if (this == 0) {
        return 0;
    }
    return respectKeyPlayer;
}

void DeckTrainerAI::setRespectKeyPlayer(bool value) {
    if (this != 0) {
        respectKeyPlayer = value;
    }
}

bool DeckTrainerAI::getAttrDetermination() const {
    if (this == 0) {
        return 0;
    }
    return attrDetermination;
}

void DeckTrainerAI::setAttrDetermination(bool value) {
    if (this != 0) {
        attrDetermination = value;
    }
}

bool DeckTrainerAI::getAbilityDetermination() const {
    if (this == 0) {
        return 0;
    }
    return abilityDetermination;
}

void DeckTrainerAI::setAbilityDetermination(bool value) {
    if (this != 0) {
        abilityDetermination = value;
    }
}

bool DeckTrainerAI::getCalcWazaDamage() const {
    if (this == 0) {
        return 0;
    }
    return calcWazaDamage;
}

void DeckTrainerAI::setCalcWazaDamage(bool value) {
    if (this != 0) {
        calcWazaDamage = value;
    }
}

bool DeckTrainerAI::getSelectRandomDefence() const {
    if (this == 0) {
        return 0;
    }
    return selectRandomDefence;
}

void DeckTrainerAI::setSelectRandomDefence(bool value) {
    if (this != 0) {
        selectRandomDefence = value;
    }
}

bool DeckTrainerAI::getSelectRandomWaza() const {
    if (this == 0) {
        return 0;
    }
    return selectRandomWaza;
}

void DeckTrainerAI::setSelectRandomWaza(bool value) {
    if (this != 0) {
        selectRandomWaza = value;
    }
}

bool DeckTrainerAI::getRespectWazaAssmntVal() const {
    if (this == 0) {
        return 0;
    }
    return respectWazaAssmntVal;
}

void DeckTrainerAI::setRespectWazaAssmntVal(bool value) {
    if (this != 0) {
        respectWazaAssmntVal = value;
    }
}

bool DeckTrainerAI::getRespectRole() const {
    if (this == 0) {
        return 0;
    }
    return respectRole;
}

void DeckTrainerAI::setRespectRole(bool value) {
    if (this != 0) {
        respectRole = value;
    }
}

bool DeckTrainerAI::getRespectWazaHit() const {
    if (this == 0) {
        return 0;
    }
    return respectWazaHit;
}

void DeckTrainerAI::setRespectWazaHit(bool value) {
    if (this != 0) {
        respectWazaHit = value;
    }
}

bool DeckTrainerAI::getRespectWazaRiskJudge() const {
    if (this == 0) {
        return 0;
    }
    return respectWazaRiskJudge;
}

void DeckTrainerAI::setRespectWazaRiskJudge(bool value) {
    if (this != 0) {
        respectWazaRiskJudge = value;
    }
}

bool DeckTrainerAI::getRespectPokemonCondJuge() const {
    if (this == 0) {
        return 0;
    }
    return respectPokemonCondJuge;
}

void DeckTrainerAI::setRespectPokemonCondJuge(bool value) {
    if (this != 0) {
        respectPokemonCondJuge = value;
    }
}

u8 DeckTrainerAI::getStatusDetermValMax(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return statusDetermVal[index].max;
}

u8 DeckTrainerAI::getStatusDetermValMin(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return statusDetermVal[index].min;
}

u8 DeckTrainerAI::getStatusDetermValTotalMax() const {
    if (this == 0) {
        return 0;
    }
    return statusDetermValTotalMax;
}

void DeckTrainerAI::setStatusDetermValTotalMax(u8 value) {
    if (this != 0) {
        statusDetermValTotalMax = value;
    }
}

u8 DeckTrainerAI::getStatusDetermValTotalMin() const {
    if (this == 0) {
        return 0;
    }
    return statusDetermValTotalMin;
}

void DeckTrainerAI::setStatusDetermValTotalMin(u8 value) {
    if (this != 0) {
        statusDetermValTotalMin = value;
    }
}

u8 DeckTrainerAI::getPokeChgRate() const {
    if (this == 0) {
        return 0;
    }
    return pokeChgRate;
}

void DeckTrainerAI::setPokeChgRate(u8 value) {
    if (this != 0) {
        pokeChgRate = value;
    }
}

u8 DeckTrainerAI::getItemUseRate() const {
    if (this == 0) {
        return 0;
    }
    return itemUseRate;
}

void DeckTrainerAI::setItemUseRate(u8 value) {
    if (this != 0) {
        itemUseRate = value;
    }
}

u8 DeckTrainerAI::getHitRate() const {
    if (this == 0) {
        return 0;
    }
    return hitRate;
}

void DeckTrainerAI::setHitRate(u8 value) {
    if (this != 0) {
        hitRate = value;
    }
}

u8 DeckTrainerAI::getAnnihilateDetermRate() const {
    if (this == 0) {
        return 0;
    }
    return annihilateDetermRate;
}

u8 DeckTrainerAI::getLowHPDetermRate() const {
    if (this == 0) {
        return 0;
    }
    return lowHPDetermRate;
}

void DeckTrainerAI::setLowHPDetermRate(u8 value) {
    if (this != 0) {
        lowHPDetermRate = value;
    }
}

u8 DeckTrainerAI::getLastPPDetermRate() const {
    if (this == 0) {
        return 0;
    }
    return lastPPDetermRate;
}

void DeckTrainerAI::setLastPPDetermRate(u8 value) {
    if (this != 0) {
        lastPPDetermRate = value;
    }
}

u8 DeckTrainerAI::getAttrTypeID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return attrTypeID[index];
}

void DeckTrainerAI::setAttrTypeID(u8 index, u8 value) {
    if (this != 0) {
        attrTypeID[index] = value;
    }
}

u8 DeckTrainerAI::getAttrTypeParam(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return attrTypeParam[index];
}

void DeckTrainerAI::setAttrTypeParam(u8 index, u8 value) {
    if (this != 0) {
        attrTypeParam[index] = value;
    }
}

u16 DeckTrainerAI::getWazaKindID(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return wazaKindID[index];
}

void DeckTrainerAI::setWazaKindID(u8 index, u16 value) {
    if (this != 0) {
        wazaKindID[index] = value;
    }
}

u8 DeckTrainerAI::getWazaKindParam(u8 index) const {
    if (this == 0) {
        return 0;
    }
    return wazaKindParam[index];
}

void DeckTrainerAI::setWazaKindParam(u8 index, u8 value) {
    if (this != 0) {
        wazaKindParam[index] = value;
    }
}

u8 DeckTrainerAI::getTotalCorrection() const {
    if (this == 0) {
        return 0;
    }
    return totalCorrection;
}

void DeckTrainerAI::setTotalCorrection(u8 value) {
    if (this != 0) {
        totalCorrection = value;
    }
}

void deckInit(void) {
    _deckTrainer = 0;
    _deckPokemon = 0;
    _deckDarkPokemon = 0;
    _deckTrainerAI = 0;
    _deckIDNameStr = 0;
    _deckTrainerSize = 0;
    _deckPokemonSize = 0;
    _deckDarkPokemonSize = 0;
    _deckTrainerAISize = 0;
}

void deckRegister(u32 kind, u32 id) {
    CChankBlock chank;
    char* data = (char*)GSresGetResource(kind, id);
    char* sub;

    if (data == 0) {
        return;
    }
    if (!chank.loadFromMemory(data, "DECK")) {
        return;
    }
    if ((sub = chank.searchSubChankID("DDPK")) != 0) {
        _deckDarkPokemonSize = *(u32*)(sub + 8);
        _deckDarkPokemon = (DeckDarkPokemon*)(sub + 0x10);
    }
    if ((sub = chank.searchSubChankID("DTNR")) != 0) {
        _deckTrainerSize = *(u32*)(sub + 8);
        _deckTrainer = (DeckTrainer*)(sub + 0x10);
    }
    if ((sub = chank.searchSubChankID("DPKM")) != 0) {
        _deckPokemonSize = *(u32*)(sub + 8);
        _deckPokemon = (DeckPokemon*)(sub + 0x10);
    }
    if ((sub = chank.searchSubChankID("DTAI")) != 0) {
        _deckTrainerAISize = *(u32*)(sub + 8);
        _deckTrainerAI = (DeckTrainerAI*)(sub + 0x10);
    }
    if ((sub = chank.searchSubChankID("DSTR")) != 0) {
        _deckIDNameStr = sub + 0x10;
    }
}

void deckUnRegister(u32 kind, u32 id) {
    CChankBlock chank;
    char* data = (char*)GSresGetResource(kind, id);

    if (data == 0) {
        return;
    }
    if (!chank.loadFromMemory(data, "DECK")) {
        return;
    }
    if (chank.searchSubChankID("DDPK") != 0) {
        _deckDarkPokemonSize = 0;
        _deckDarkPokemon = 0;
    }
    if (chank.searchSubChankID("DTNR") != 0) {
        _deckTrainerSize = 0;
        _deckTrainer = 0;
    }
    if (chank.searchSubChankID("DPKM") != 0) {
        _deckPokemonSize = 0;
        _deckPokemon = 0;
    }
    if (chank.searchSubChankID("DTAI") != 0) {
        _deckTrainerAISize = 0;
        _deckTrainerAI = 0;
    }
    if (chank.searchSubChankID("DSTR") != 0) {
        _deckIDNameStr = 0;
    }
}

void deckInitDarkPokemon(void) {
    DarkPokemon* dark;
    DeckDarkPokemon* deck = _deckDarkPokemon;
    u16 id;
    s32 i;

    dark = (DarkPokemon*)savedataGetStatus(0, 0xF);
    if (dark != 0) {
        for (i = 0; i < 0x80; i++, deck++, dark++) {
            id = darkPokemonListBiosGetPokemonID(i);
            dark->init();
            dark->setDarkPoint(deck->getInitDarkPoint());
            dark->setPokemonID(id);
            dark->setDarkPokemonID(i);
        }
    }
}

DeckDarkPokemon* deckGetDeckDarkPokemon(u32 index) {
    if (index < 0x80) {
        return &_deckDarkPokemon[index];
    }
    return 0;
}

u32 deckGetDarkPokemonSize(void) {
    return 0x80;
}

DeckTrainer* DeckTrainer::getDeckTrainerObj(u32 index) {
    if (_deckTrainerSize <= index) {
        return 0;
    }
    return &_deckTrainer[index];
}

u32 deckGetTrainerSize(void) {
    return _deckTrainerSize;
}

DeckPokemon* DeckPokemon::getDeckPokemonObj(u32 index) {
    if (_deckPokemonSize <= index) {
        return 0;
    }
    return &_deckPokemon[index];
}

DeckDarkPokemon* DeckDarkPokemon::getDeckDarkPokemonObj(u32 index) {
    if (_deckDarkPokemonSize <= index) {
        return 0;
    }
    return &_deckDarkPokemon[index];
}

DeckTrainerAI* DeckTrainerAI::getDeckTrainerAIObj(u32 index) {
    if (_deckTrainerAISize <= index) {
        return 0;
    }
    return &_deckTrainerAI[index];
}

u32 getDeckResourceID(u8 kind) {
    switch (kind) {
    case 1:
        return 0x18503400;
    case 2:
        return 0x184E3400;
    case 3:
        return 0x184F3400;
    case 4:
        return 0x18513400;
    case 5:
        return 0x184B3400;
    case 6:
        return 0x184C3400;
    case 7:
        return 0x195F3400;
    }
}

void deckCreate(u16 deckID, u16 pokemonID, Pokemon* pokemon) {
    DeckPokemon* deck = DeckPokemon::getDeckPokemonObj(deckID);
    u16 rndKind[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    u16 effortKind[6] = {0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};
    u8 j;
    u8 i;

    deck->setPokemonID(pokemonID);
    deck->setSex(pokemon->getSex());
    deck->setSeikakuID(pokemon->getSeikaku());
    deck->setLevel(pokemon->getLevel());
    for (i = 0; i < 6; i++) {
        deck->setStatusEffort(i, pokemonGetStatus(pokemon, 0, effortKind[i], 0));
        deck->setStatusRnd(i, pokemonGetStatus(pokemon, 0, rndKind[i], 0));
    }
    deck->setFriendLevel(pokemon->getFriendLevel());
    deck->setTokuseiFlag(pokemon->isTokuseiFlag());
    for (j = 0; j < 4; j++) {
        deck->setWazaID(j, pokemon->getPokemonWaza(j)->id);
    }
}

char* getDeckMsgID(u16 encountID, u8 index) {
    u16 id = fightEncountDataBiosGetFightTrainerDataId(fightEncountDataBiosGetPtr(encountID), index);
    return _deckIDNameStr + DeckTrainer::getDeckTrainerObj(id)->getMsgOffset();
}

}
