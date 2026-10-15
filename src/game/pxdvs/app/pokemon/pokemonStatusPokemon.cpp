#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
#include <game/relglobal.h>

struct DarkPokemonCatchBall {
    u8 flags : 4;
    u8 ballId : 4;
};

struct DarkPokemonStatusBits {
    u8 status : 3;
    u8 reserved : 1;
    u8 snatchInfoLevel : 3;
    u8 snatchFromWho : 1;
};

struct DarkPokemonPoolExpBits {
    u32 exp : 20;
    u32 unused : 12;
};

struct DarkPokemonReverseBits {
    u8 unused : 1;
    u8 revers : 1;
    u8 reserved : 6;
};

struct DarkPokemonInformationBits {
    u8 information : 1;
    u8 reserved : 7;
};

struct DarkPokemonUpdateBits {
    u8 unused : 1;
    u8 revers : 1;
    u8 update : 1;
    u8 reserved : 5;
};

struct DarkPokemonPlaceBits {
    u32 unused : 14;
    u32 where : 3;
    u32 reserved : 15;
};

struct DarkPokemonWazaNewBits {
    u8 unused : 3;
    u8 wazaNew : 3;
    u8 reserved : 2;
};

extern "C" {
extern u16* legendPokemonData;
extern u32* legendPokemonData_number;
const char* pokemonDB_GetName(u16);
bool pokemonCheckValid(Pokemon*);
u8 pokemonGetSex(Pokemon*);
u8 darkPokemonBiosGetReliveFlag(u16);
void GScharLenCpy(void* dst, const void* src, s32 len);
}

struct DarkPokemonStatusRndArray {
    u8 unused[0x0B];
    u8 rnd[6];
};

struct DarkPokemonWhereBits {
    u8 where : 3;
    u8 reserved : 5;
};

void Pokemon::setReversMode(bool revers) {
    DarkPokemon* dark = getDarkPokemon();
    if (dark != nullptr) {
        dark->setReversMode(revers);
    }
}
bool Pokemon::isReversMode() const {
    DarkPokemon* dark = getDarkPokemon();
    if (dark == nullptr) {
        return false;
    }
    return dark->isReversMode();
}
bool Pokemon::isLegend() const {
    if (getPokemonDataId() == 0) {
        return false;
    }
    u16 id;
    for (u32 i = 0; i < *legendPokemonData_number; i++) {
        id = legendPokemonData[i];
        if (id == 0) {
            return false;
        }
        if (id == getPokemonDataId()) {
            return true;
        }
    }
    return false;
}
bool Pokemon::isHatena() const {
    u16 id = getPokemonDataId();
    if (id == 0) {
        return true;
    }
    if (pokemonDB_GetName(id) == 0) {
        return true;
    }
    if (id >= *pokemon_data_number) {
        return true;
    }
    return false;
}
bool Pokemon::checkValid() const {
    return pokemonCheckValid(const_cast<Pokemon*>(this));
}
void Pokemon::setPoolFriendLevel(u16 data) {
    DarkPokemon* dark = getDarkPokemon();
    if (dark != nullptr) {
        u16 finalData = 0xFF;
        if (data < finalData) {
            finalData = data;
        }
        dark->setPoolFriendLevel(finalData);
    }
}
void Pokemon::setPoolExp(u32 data) {
    DarkPokemon* dark = getDarkPokemon();
    if (dark != nullptr) {
        dark->setPoolExp(data);
    }
}
void Pokemon::setDarkPoint(f32 data) {
    DarkPokemon* dark = getDarkPokemon();
    if (dark != nullptr) {
        f32 finalData = 6553500.0f;
        if (data < finalData) {
            finalData = data;
        }
        dark->setDarkPoint(finalData);
    }
}
void Pokemon::setDarkPointDirect(s32 data) {
    DarkPokemon* dark = getDarkPokemon();
    if (dark != nullptr) {
        s32 finalData = 0x640000 - 100;
        if (data < finalData) {
            finalData = data;
        }
        dark->setDarkPointDirect(finalData);
    }
}
u32 Pokemon::getPoolFriendLevel() const {
    DarkPokemon* dark = getDarkPokemon();
    if (dark == nullptr) {
        return 0;
    }
    return dark->getPoolFriendLevel();
}
u32 Pokemon::getPoolExp() const {
    DarkPokemon* dark = getDarkPokemon();
    if (dark == nullptr) {
        return 0;
    }
    return dark->getPoolExp();
}
f32 Pokemon::getDarkPoint() const {
    DarkPokemon* dark = getDarkPokemon();
    if (dark == nullptr) {
        return -1.0f;
    }
    return dark->getDarkPoint();
}
s32 Pokemon::getDarkPointDirect() const {
    DarkPokemon* dark = getDarkPokemon();
    if (dark == nullptr) {
        return -1;
    }
    return dark->getDarkPointDirect();
}
DarkPokemon* Pokemon::getDarkPokemon() const {
    return darkPokemonGetDarkPokemon(getDarkpokemonDataID());
}
DarkPokemon* Pokemon::getDarkPokemon() {
    return darkPokemonGetDarkPokemon(getDarkpokemonDataID());
}
bool Pokemon::isDarkPokemon() const {
    u16 id = getDarkpokemonDataID();
    if (id == 0) {
        return false;
    }
    return darkPokemonBiosGetReliveFlag(id) == 0;
}
u8 Pokemon::getSex() const {
    return pokemonGetSex(const_cast<Pokemon*>(this));
}
bool Pokemon::isTokuseiFlag() const {
    if (pokemonDataBiosGetTokuseiDataId(static_cast<PokemonData*>(getPokemonDataPtr()), 1) == 0) {
        return false;
    }
    return flags.bits.tokusei;
}
bool Pokemon::isRareParam(u32 a, u32 b) {
    return (a >> 16 ^ (a & 0xFFFF) ^ b >> 16 ^ (b & 0xFFFF)) < 8;
}
u32 DarkPokemon::getWalkCount() const {
    return *reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(this) + 0x44);
}
void DarkPokemon::setWalkCount(u32 count) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x44) = count;
}
void DarkPokemon::setReversPattern(u8 pattern) {
    *(reinterpret_cast<u8*>(this) + 0x40) = pattern;
}
u8 DarkPokemon::getReversPattern() const {
    return *(reinterpret_cast<const u8*>(this) + 0x40);
}
u16 DarkPokemon::getInitDarkPointDirect() const {
    u16 id = *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x3E);
    return darkPokemonBiosGetDarkPoint(id);
}
void DarkPokemon::setCatchBallID(u16 ballId) {
    reinterpret_cast<DarkPokemonCatchBall*>(reinterpret_cast<u8*>(this) + 0x06)->ballId = ballId;
}
u8 DarkPokemon::getCatchBallID() const {
    return *(reinterpret_cast<const u8*>(this) + 0x06) & 0x0F;
}
void DarkPokemon::setDarkPokemonID(u16 id) {
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x3E) = id;
}
u16 DarkPokemon::getDarkPokemonID() const {
    return *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x3E);
}
void DarkPokemon::setPokemonID(u16 id) {
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x1A) = id;
}
u16 DarkPokemon::getPokemonID() const {
    return *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x1A);
}
bool DarkPokemon::isSnach() const {
    return getStatus() >= 3;
}
bool DarkPokemon::isRelive() const {
    return getStatus() == 4;
}
void DarkPokemon::setTrainerName(const u16* name) {
    for (u32 i = 0; i < 10; i++) {
        *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x28 + i * 2) = name[i];
    }
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x3C) = 0;
}
const u16* DarkPokemon::getTrainerName() const {
    return reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x28);
}
void DarkPokemon::setStatusRnd(u8 index, u8 value) {
    u8* p = reinterpret_cast<u8*>(this);
    u32 i = index;
    if (i < 6) {
        (p + i)[0x0B] = value;
    }
}

u8 DarkPokemon::getStatusRnd(u8 index) const {
    const u8* p = reinterpret_cast<const u8*>(this);
    u32 i = index;
    if (i < 6) {
        return (p + i)[0x0B];
    }
    return 0;
}

void DarkPokemon::setInformation(bool information) {
    reinterpret_cast<DarkPokemonInformationBits*>(reinterpret_cast<u8*>(this) + 0x07)->information = information;
}
bool DarkPokemon::isInformation() const {
    return reinterpret_cast<const DarkPokemonInformationBits*>(reinterpret_cast<const u8*>(this) + 0x07)->information != 0;
}
void DarkPokemon::setUpdate(bool update) {
    reinterpret_cast<DarkPokemonUpdateBits*>(reinterpret_cast<u8*>(this) + 0x01)->update = update;
}
bool DarkPokemon::isUpdate() const {
    return reinterpret_cast<const DarkPokemonUpdateBits*>(reinterpret_cast<const u8*>(this) + 0x01)->update != 0;
}
void DarkPokemon::setEscapeTime(u32 time) {
    if (reinterpret_cast<const DarkPokemonWhereBits*>(this)->where < 3) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x20) = time;
    }
}
u32 DarkPokemon::getEscapeTime() const {
    if (reinterpret_cast<const DarkPokemonWhereBits*>(this)->where < 3) {
        return *reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(this) + 0x20);
    }
    return 0;
}
void DarkPokemon::setSnatchTime(u32 time) {
    if (reinterpret_cast<const DarkPokemonWhereBits*>(this)->where >= 3) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x20) = time;
    }
}
void DarkPokemon::setRnd(u32 rnd) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x1C) = rnd;
}
u32 DarkPokemon::getRnd() const {
    return *reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(this) + 0x1C);
}
void DarkPokemon::setCatchFloorId(u16 floorId) {
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x16) = floorId;
}
u16 DarkPokemon::getCatchFloorId() const {
    return *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x16);
}
void DarkPokemon::setOrgTrainer(u16 trainer) {
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x14) = trainer;
}
u16 DarkPokemon::getOrgTrainer() const {
    return *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x14);
}
void DarkPokemon::setSnatchIndex(u8 index) {
    *(reinterpret_cast<u8*>(this) + 0x13) = index;
}
u8 DarkPokemon::getSnatchIndex() const {
    return *(reinterpret_cast<const u8*>(this) + 0x13);
}
void DarkPokemon::getPlace(darkPokemonWhere& where, u8& floor) const {
    where = static_cast<darkPokemonWhere>(reinterpret_cast<const DarkPokemonPlaceBits*>(this)->where);
    floor = *(reinterpret_cast<const u8*>(this) + 0x11);
}
void DarkPokemon::setWazaNew(u8 index, bool isNew) {
    if (index >= 3) {
        return;
    }
    DarkPokemonWazaNewBits* bits = reinterpret_cast<DarkPokemonWazaNewBits*>(reinterpret_cast<u8*>(this) + 0x01);
    if (isNew) {
        bits->wazaNew = bits->wazaNew | (1 << index);
    } else {
        bits->wazaNew = bits->wazaNew & ~(1 << index);
    }
}
bool DarkPokemon::isWazaNew(u8 index) const {
    if (index >= 3) {
        return false;
    }
    return (reinterpret_cast<const DarkPokemonWazaNewBits*>(reinterpret_cast<const u8*>(this) + 0x01)->wazaNew & (1 << index)) != 0;
}
void DarkPokemon::setPoolFriendLevel(u16 level) {
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0x18) = level;
}
u32 DarkPokemon::getPoolFriendLevel() const {
    return *reinterpret_cast<const u16*>(reinterpret_cast<const u8*>(this) + 0x18);
}
void DarkPokemon::setPoolExp(u32 exp) {
    DarkPokemonPoolExpBits* bits = reinterpret_cast<DarkPokemonPoolExpBits*>(reinterpret_cast<u8*>(this) + 0x04);
    bits->exp = exp;
}
u32 DarkPokemon::getPoolExp() const {
    return *reinterpret_cast<const u32*>(reinterpret_cast<const u8*>(this) + 0x04) >> 12;
}
void DarkPokemon::setDarkPointDirect(s32 value) {
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x24) = value;
}
s32 DarkPokemon::getDarkPointDirect() const {
    return *reinterpret_cast<const s32*>(reinterpret_cast<const u8*>(this) + 0x24);
}
void DarkPokemon::setReversMode(bool revers) {
    reinterpret_cast<DarkPokemonReverseBits*>(reinterpret_cast<u8*>(this) + 0x01)->revers = revers;
}
bool DarkPokemon::isReversMode() const {
    return reinterpret_cast<const DarkPokemonReverseBits*>(reinterpret_cast<const u8*>(this) + 0x01)->revers != 0;
}
void DarkPokemon::setSnatchFromWho(darkPokemonSnatchWho who) {
    u16* value = reinterpret_cast<u16*>(this);
    *value = (*value & ~0x0180) | ((static_cast<u16>(who) & 3) << 7);
}
darkPokemonSnatchWho DarkPokemon::getSnatchFromWho() const {
    return static_cast<darkPokemonSnatchWho>((*reinterpret_cast<const u16*>(this) >> 7) & 3);
}
void DarkPokemon::setSnatchInfoLevel(u8 level) {
    reinterpret_cast<DarkPokemonStatusBits*>(this)->snatchInfoLevel = level;
}
s32 DarkPokemon::getStatus() const {
    return reinterpret_cast<const DarkPokemonStatusBits*>(this)->status;
}
void DarkPokemon::addStatus(darkPokemonStatus status) {
    DarkPokemonStatusBits* bits = reinterpret_cast<DarkPokemonStatusBits*>(this);
    if ((u32)bits->status < (u32)status) {
        bits->status = status;
    }
}
void DarkPokemon::setStatus(darkPokemonStatus status) {
    reinterpret_cast<DarkPokemonStatusBits*>(this)->status = status;
}
void DarkPokemon::init() {
    memset(this, 0, 0x48);
}
void Pokemon::setConditionTurnNow(u8 data) {
    conditionTurnNow = data;
}
u8 Pokemon::getConditionTurnNow() const {
    return conditionTurnNow;
}
void Pokemon::setConditionTurn(u8 data) {
    conditionTurn = data;
}
u8 Pokemon::getConditionTurn() const {
    return conditionTurn;
}
void Pokemon::setConditionCount(u8 data) {
    conditionCount = data;
}
u8 Pokemon::getConditionCount() const {
    return conditionCount;
}
void Pokemon::setCondition(u8 data) {
    condition = data;
}
u8 Pokemon::getCondition() const {
    return condition;
}
u16 Pokemon::getDarkpokemonDataID() const {
    return darkPokemonDataID;
}
void Pokemon::setPara1Amari(u16 data) {
    para1Amari = data;
}
void Pokemon::setAmari(u16 data) {
    amari = data;
}
void Pokemon::setPcboxMark(u8 data) {
    pcboxMark = data;
}
void Pokemon::setFriendLevel(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    friendLevel = finalData;
}
void Pokemon::setNimblenessRnd(u16 data) {
    statusRnd.setNimbleness(data);
}
void Pokemon::setSpeDefRnd(u16 data) {
    statusRnd.setSpeDef(data);
}
void Pokemon::setSpeAtkRnd(u16 data) {
    statusRnd.setSpeAtk(data);
}
void Pokemon::setPhyDefRnd(u16 data) {
    statusRnd.setPhyDef(data);
}
void Pokemon::setPhyAtkRnd(u16 data) {
    statusRnd.setPhyAtk(data);
}
void Pokemon::setMaxHpRnd(u16 data) {
    statusRnd.setMaxHp(data);
}
void Pokemon::setNimblenessEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    nimblenessEffort = finalData;
}
void Pokemon::setSpeDefEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    speDefEffort = finalData;
}
void Pokemon::setSpeAtkEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    speAtkEffort = finalData;
}
void Pokemon::setPhyDefEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    phyDefEffort = finalData;
}
void Pokemon::setPhyAtkEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    phyAtkEffort = finalData;
}
void Pokemon::setMaxHpEffort(u16 data) {
    u16 finalData = 0xFF;
    if (data < finalData) {
        finalData = data;
    }
    maxHpEffort = finalData;
}
void Pokemon::setNimbleness(u16 data) {
    nimbleness = data;
}
void Pokemon::setSpeDef(u16 data) {
    speDef = data;
}
void Pokemon::setSpeAtk(u16 data) {
    speAtk = data;
}
void Pokemon::setPhyDef(u16 data) {
    phyDef = data;
}
void Pokemon::setPhyAtk(u16 data) {
    phyAtk = data;
}
void Pokemon::setMaxHp(u16 data) {
    maxHp = data;
}
void Pokemon::setHp(u16 data) {
    hp = data;
    u16 hpCap = getMaxHp();
    if (hpCap < hp) {
        hp = hpCap;
    }
}
void Pokemon::setItemDataId(u16 data) {
    itemDataID = data;
}
void Pokemon::setExp(u32 data) {
    exp = data;
}
void Pokemon::setNicknameOrgPtr(u16* name) {
    if (name != nullptr) {
        GScharLenCpy(nicknameOrg, name, 11);
    }
}
void Pokemon::setNicknamePtr(u16* name) {
    if (name != nullptr) {
        GScharLenCpy(nickname, name, 11);
        setNicknameOrgPtr(name);
    }
}
void Pokemon::setCatchTrainerNamePtr(u16* name) {
    if (name != nullptr) {
        GScharLenCpy(catchTrainerName, name, 11);
    }
}
void Pokemon::setCatchTrainerRnd(u32 data) {
    catchTrainerRnd = data;
}
void Pokemon::setCatchTrainerSex(u8 data) {
    catchTrainerSex = data;
}
void Pokemon::setCatchBallId(u8 data) {
    catchBallId = data;
}
void Pokemon::setCatchLevel(u8 data) {
    catchLevel = data;
}
void Pokemon::setCatchFloorId(u16 data) {
    catchFloorId = data;
}
void Pokemon::setRnd(u32 data) {
    rnd = data;
}
u16 Pokemon::getPara1Amari() const {
    return para1Amari;
}
u16 Pokemon::getAmari() const {
    return amari;
}
bool Pokemon::isFuseiFlag() const {
    return flags.bits.fusei;
}
u8 Pokemon::getPcboxMark() const {
    return pcboxMark;
}
u16 Pokemon::getFriendLevel() const {
    return friendLevel;
}
u16 Pokemon::getItemDataId() const {
    return itemDataID;
}
u8 Pokemon::getLevel() const {
    return level;
}
u16 Pokemon::getHp() const {
    return hp;
}
char* Pokemon::getNicknamePtr() {
    return &nickname[0];
}
u8 Pokemon::getNimblenessRnd() const {
    return statusRnd.getNimbleness();
}
u8 Pokemon::getSpeDefRnd() const {
    return statusRnd.getSpeDef();
}
u8 Pokemon::getSpeAtkRnd() const {
    return statusRnd.getSpeAtk();
}
u8 Pokemon::getPhyDefRnd() const {
    return statusRnd.getPhyDef();
}
u8 Pokemon::getPhyAtkRnd() const {
    return statusRnd.getPhyAtk();
}
u8 Pokemon::getMaxHpRnd() const {
    return statusRnd.getMaxHp();
}
u16 Pokemon::getNimblenessEffort() const {
    return nimblenessEffort;
}
u16 Pokemon::getSpeDefEffort() const {
    return speDefEffort;
}
u16 Pokemon::getSpeAtkEffort() const {
    return speAtkEffort;
}
u16 Pokemon::getPhyDefEffort() const {
    return phyDefEffort;
}
u16 Pokemon::getPhyAtkEffort() const {
    return phyAtkEffort;
}
u16 Pokemon::getMaxHpEffort() const {
    return maxHpEffort;
}
u16 Pokemon::getNimbleness() const {
    return nimbleness;
}
u16 Pokemon::getSpeDef() const {
    return speDef;
}
u16 Pokemon::getSpeAtk() const {
    return speAtk;
}
u16 Pokemon::getPhyDef() const {
    return phyDef;
}
u16 Pokemon::getPhyAtk() const {
    return phyAtk;
}
u16 Pokemon::getMaxHp() const {
    return maxHp;
}
Attest* Pokemon::getAttest() {
    return &attest;
}
u32 Pokemon::getRnd() const {
    return rnd;
}
u16 Pokemon::getPokemonDataId() const {
    return dataID;
}
bool Pokemon::isRare() const {
    return isRareParam(getCatchTrainerRnd(), getRnd());
}
u8 Pokemon::getSeikaku() const {
    return getRnd() % 25;
}
void Pokemon::initCondition() {
    condition = 0;
    conditionCount = 0;
    conditionTurn = 0;
    conditionTurnNow = 0;
}
void Pokemon::copyCondition(const Pokemon* poke) {
    condition = poke->condition;
    conditionCount = poke->conditionCount;
    conditionTurn = poke->conditionTurn;
    conditionTurnNow = poke->conditionTurnNow;
}
Ribbon* Pokemon::getRibbon() {
    return &ribbon;
}
PokemonWaza* Pokemon::getPokemonWaza(u16 wazaNum) {
    if (wazaNum < MAX_WAZA)
    {
        return &wazas[wazaNum];
    }
    return nullptr;
}
void* Pokemon::getPokemonDataPtr() const {
    u32 num = getPokemonDataId();
    u32 maxNum = *pokemon_data_number;
    if (num >= maxNum) {
        return nullptr;
    }

    return &pokemon_data[num];
}
u32 Pokemon::getCatchTrainerRnd() const {
    return catchTrainerRnd;
}
void Pokemon::clear() {
    memset(this, 0, sizeof(Pokemon));
}
void PokemonStatusRnd::setNimbleness(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    nimbleness = finalData;
}
void PokemonStatusRnd::setSpeDef(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    speDef = finalData;
}
void PokemonStatusRnd::setSpeAtk(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    speAtk = finalData;
}
void PokemonStatusRnd::setPhyDef(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    phyDef = finalData;
}
void PokemonStatusRnd::setPhyAtk(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    phyAtk = finalData;
}
void PokemonStatusRnd::setMaxHp(u8 data) {
    u16 finalData = 0x1f;
    if (data < 0x1f) {
        finalData = data;
    }
    maxHp = finalData;
}
u32 PokemonStatusRnd::getNimbleness() const {
    return nimbleness;
}
u32 PokemonStatusRnd::getSpeDef() const {
    return speDef;
}
u32 PokemonStatusRnd::getSpeAtk() const {
    return speAtk;
}
u32 PokemonStatusRnd::getPhyDef() const {
    return phyDef;
}
u32 PokemonStatusRnd::getPhyAtk() const {
    return phyAtk;
}
u32 PokemonStatusRnd::getMaxHp() const {
    return maxHp;
}
