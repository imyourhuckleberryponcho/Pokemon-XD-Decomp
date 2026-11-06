#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/gcptr.h>
#include <game/gcfield.h>
#include <game/fightrecords.h>

extern "C" void* memcpy(void*, const void*, u32);
struct Pokemon {
    u8 data[0xC4];
    Pokemon& operator=(const Pokemon& o) {
        memcpy(this, &o, 0xC4);
        return *this;
    }
};
struct u64x { u32 a, b; };
struct Joutai16 { u32 w[4]; };
struct ArrA { u64x v[4]; };
struct ArrB { Joutai16 v[32]; };
struct ArrJ { Joutai16 v[0x34]; };
struct FightWazaBuf { u32 w[43]; };
struct FightItemBuf { u32 w[2]; };
struct ActionBuf { u32 w0[2]; void* p8; void* pC; u32 w10; void* p14; void* p18; u32 w1C[5]; };

struct FightPokemon {
    void* moto;
    Pokemon buff;
    Joutai16 joutai[1];
    s16 entryId;
    u8 darkOut0;
    u8 darkOut1;
    u8 darkOut2;
    u8 darkOut3;
    u16 pad;
};

struct FightOutPokemon {
    void* moto;
    void* fightPokemon;
    FightPokemon hensin;
    ArrA a;
    ArrB b;
    ArrJ joutai;
    FightWazaBuf waza;
    FightWazaBuf keepWaza;
    FightItemBuf item;
    u32 x7a8;
    void* sequence;
    u8 abi0, abi1, abi2, abi3, abi4, abi5, abi6, abi7;
    u16 hensinMotoPkxId;
    u16 s7ba;
    u16 turnCount;
    s16 meet[12];
    ActionBuf action;
    u16 zokusei[2];
    u16 tokusei;
    u32 wazaMenuCur;
    u8 g0, g1, g2, g3;
    u16 sketch, lastSelect, lastUse, lastRecv, hitWaza, hitZ;
    s16 gamanValue;
    u16 gamanTarget, oumu, s82a;
    u8 namake, successCnt;
    u16 usedItem, stockItem, s832;
    s16 damageAtkValue;
    u16 damageAtkTarget;
    s16 damageSpeValue;
    u16 damageSpeTarget;
    u8 flag0; u8 flag1; u8 flag2; u8 flag3; u8 flag4; u8 flag5; u8 flag6; u8 flag7; u8 flag8; u8 flag9; u8 flag10; u8 flag11; u8 flag12; u8 flag13; u8 flag14; u8 flag15; u8 flag16; u8 flag17; u8 flag18; u8 flag19; u8 flag20;
    u32 kaigara;
    s16 myAtkValue;
    u16 myAtkTarget;
    s16 mySpeValue;
    u16 mySpeTarget;
    u8 kizetu, u861;
    s16 irekaeTarget;
    FightOutPokemonEnemy enemy[4];
};

#pragma optimize_for_size on
extern "C" {

void fightOutPokemonBiosCopy(FightOutPokemon* dst, const FightOutPokemon* src) {
    if (dst == 0) { return; }
    if (src == 0) { return; }
    *dst = *src;
}

void fightOutPokemonBiosSetOumuWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x828, FightOutPokemon, oumu) = v;
}

void fightOutPokemonBiosSetGamanDamageTargetId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x826, FightOutPokemon, gamanTarget) = v;
}

void fightOutPokemonBiosSetGamanDamageValue(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x824, FightOutPokemon, gamanValue) = v;
}

void fightOutPokemonBiosSetHitWazaZokuseiDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x822, FightOutPokemon, hitZ) = v;
}

void fightOutPokemonBiosSetHitWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x820, FightOutPokemon, hitWaza) = v;
}

void fightOutPokemonBiosSetLastReceiveWazaTargetDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x81e, FightOutPokemon, lastRecv) = v;
}

void fightOutPokemonBiosSetLastUseWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x81c, FightOutPokemon, lastUse) = v;
}

void fightOutPokemonBiosSetLastSelectWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x81a, FightOutPokemon, lastSelect) = v;
}

void fightOutPokemonBiosSetSketchWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x818, FightOutPokemon, sketch) = v;
}

void* fightOutPokemonBiosGetKeepFightWazaPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x6f4, FightOutPokemon, keepWaza);
}

u16 fightOutPokemonBiosGetOumuWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x828, FightOutPokemon, oumu);
}

u16 fightOutPokemonBiosGetGamanDamageTargetId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x826, FightOutPokemon, gamanTarget);
}

s16 fightOutPokemonBiosGetGamanDamageValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(s16*, p, 0x824, FightOutPokemon, gamanValue);
}

u16 fightOutPokemonBiosGetHitWazaZokuseiDataId(u8* p) {
    if (p == 0) return 9;
    return RAW_F(u16*, p, 0x822, FightOutPokemon, hitZ);
}

u16 fightOutPokemonBiosGetHitWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x820, FightOutPokemon, hitWaza);
}

u16 fightOutPokemonBiosGetLastReceiveWazaTargetDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x81e, FightOutPokemon, lastRecv);
}

u16 fightOutPokemonBiosGetLastUseWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x81c, FightOutPokemon, lastUse);
}

u16 fightOutPokemonBiosGetLastSelectWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x81a, FightOutPokemon, lastSelect);
}

u16 fightOutPokemonBiosGetSketchWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x818, FightOutPokemon, sketch);
}

void fightOutPokemonEnemyBiosSetDamage(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x8, FightOutPokemonEnemy, damage) = v;
}

void fightOutPokemonEnemyBiosSetInitHp(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x6, FightOutPokemonEnemy, initHp) = v;
}

void fightOutPokemonEnemyBiosSetOumuWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x4, FightOutPokemonEnemy, oumuWaza) = v;
}

void fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(u8* p, GCuptr v) {
    if (p == 0) return;
    RAW_FP(u32*, p, 0x0, FightOutPokemonEnemy, target) = v;
}

PCRET(u16) fightOutPokemonEnemyBiosGetDamage(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x8, FightOutPokemonEnemy, damage);
}

u16 fightOutPokemonEnemyBiosGetInitHp(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x6, FightOutPokemonEnemy, initHp);
}

u16 fightOutPokemonEnemyBiosGetOumuWazaDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x4, FightOutPokemonEnemy, oumuWaza);
}

GCuptr fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_FP(u32*, p, 0x0, FightOutPokemonEnemy, target);
}

void* fightOutPokemonBiosGetFightOutPokemonEnemyPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 4) return 0;
    return RAW_AI(p, 0x864, i, 12, FightOutPokemon, enemy);
}

void fightOutPokemonBiosSetIrekaeTargetEntryId(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x862, FightOutPokemon, irekaeTarget) = v;
}

s16 fightOutPokemonBiosGetIrekaeTargetEntryId(u8* p) {
    if (p == 0) return -1;
    return RAW_F(s16*, p, 0x862, FightOutPokemon, irekaeTarget);
}

void fightOutPokemonBiosSetKizetuFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x860, FightOutPokemon, kizetu) = v;
}

u8 fightOutPokemonBiosGetKizetuFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x860, FightOutPokemon, kizetu);
}

void fightOutPokemonBiosSetMyselfDamageSpeTargetId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x85e, FightOutPokemon, mySpeTarget) = v;
}

void fightOutPokemonBiosSetMyselfDamageSpeValue(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x85c, FightOutPokemon, mySpeValue) = v;
}

void fightOutPokemonBiosSetMyselfDamageAtkTargetId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x85a, FightOutPokemon, myAtkTarget) = v;
}

void fightOutPokemonBiosSetMyselfDamageAtkValue(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x858, FightOutPokemon, myAtkValue) = v;
}

void fightOutPokemonBiosSetKaigaraDamageValue(u8* p, u32 v) {
    if (p == 0) return;
    RAW_F(u32*, p, 0x854, FightOutPokemon, kaigara) = v;
}

void fightOutPokemonBiosSetItemKoraetaFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x850, FightOutPokemon, flag20) = v;
}

void fightOutPokemonBiosSetIrekaetaFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84f, FightOutPokemon, flag19) = v;
}

void fightOutPokemonBiosSetNoPressureFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84e, FightOutPokemon, flag18) = v;
}

void fightOutPokemonBiosSetDoTraceFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84d, FightOutPokemon, flag17) = v;
}

void fightOutPokemonBiosSetDoIkakuFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84c, FightOutPokemon, flag16) = v;
}

void fightOutPokemonBiosSetVanishoffFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84b, FightOutPokemon, flag15) = v;
}

void fightOutPokemonBiosSetReceivesWazaHiraishinFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x84a, FightOutPokemon, flag14) = v;
}

void fightOutPokemonBiosSetDoClearbodyFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x849, FightOutPokemon, flag13) = v;
}

void fightOutPokemonBiosSetFightActionFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x848, FightOutPokemon, flag12) = v;
}

void fightOutPokemonBiosSetPassPpdecFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x847, FightOutPokemon, flag11) = v;
}

void fightOutPokemonBiosSetHirumuNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x846, FightOutPokemon, flag10) = v;
}

void fightOutPokemonBiosSetIchamonNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x845, FightOutPokemon, flag9) = v;
}

void fightOutPokemonBiosSetChouhatsuNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x844, FightOutPokemon, flag8) = v;
}

void fightOutPokemonBiosSetKanashibariNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x843, FightOutPokemon, flag7) = v;
}

void fightOutPokemonBiosSetMeroMeroNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x842, FightOutPokemon, flag6) = v;
}

void fightOutPokemonBiosSetHuuinNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x841, FightOutPokemon, flag5) = v;
}

void fightOutPokemonBiosSetItemNigeruFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x840, FightOutPokemon, flag4) = v;
}

void fightOutPokemonBiosSetTameWazaFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x83f, FightOutPokemon, flag3) = v;
}

void fightOutPokemonBiosSetOutWazaKoukanaiFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x83e, FightOutPokemon, flag2) = v;
}

void fightOutPokemonBiosSetKonranMyselfAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x83d, FightOutPokemon, flag1) = v;
}

void fightOutPokemonBiosSetMahiNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x83c, FightOutPokemon, flag0) = v;
}

u16 fightOutPokemonBiosGetMyselfDamageSpeTargetId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x85e, FightOutPokemon, mySpeTarget);
}

s16 fightOutPokemonBiosGetMyselfDamageSpeValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(s16*, p, 0x85c, FightOutPokemon, mySpeValue);
}

u16 fightOutPokemonBiosGetMyselfDamageAtkTargetId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x85a, FightOutPokemon, myAtkTarget);
}

s16 fightOutPokemonBiosGetMyselfDamageAtkValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(s16*, p, 0x858, FightOutPokemon, myAtkValue);
}

u32 fightOutPokemonBiosGetKaigaraDamageValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u32*, p, 0x854, FightOutPokemon, kaigara);
}

u8 fightOutPokemonBiosGetItemKoraetaFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x850, FightOutPokemon, flag20);
}

u8 fightOutPokemonBiosGetIrekaetaFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84f, FightOutPokemon, flag19);
}

u8 fightOutPokemonBiosGetNoPressureFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84e, FightOutPokemon, flag18);
}

u8 fightOutPokemonBiosGetDoTraceFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84d, FightOutPokemon, flag17);
}

u8 fightOutPokemonBiosGetDoIkakuFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84c, FightOutPokemon, flag16);
}

u8 fightOutPokemonBiosGetVanishoffFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84b, FightOutPokemon, flag15);
}

u8 fightOutPokemonBiosGetReceivesWazaHiraishinFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x84a, FightOutPokemon, flag14);
}

u8 fightOutPokemonBiosGetDoClearbodyFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x849, FightOutPokemon, flag13);
}

u8 fightOutPokemonBiosGetFightActionFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x848, FightOutPokemon, flag12);
}

u8 fightOutPokemonBiosGetPassPpdecFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x847, FightOutPokemon, flag11);
}

u8 fightOutPokemonBiosGetHirumuNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x846, FightOutPokemon, flag10);
}

u8 fightOutPokemonBiosGetIchamonNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x845, FightOutPokemon, flag9);
}

u8 fightOutPokemonBiosGetChouhatsuNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x844, FightOutPokemon, flag8);
}

u8 fightOutPokemonBiosGetKanashibariNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x843, FightOutPokemon, flag7);
}

u8 fightOutPokemonBiosGetMeroMeroNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x842, FightOutPokemon, flag6);
}

u8 fightOutPokemonBiosGetHuuinNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x841, FightOutPokemon, flag5);
}

u8 fightOutPokemonBiosGetItemNigeruFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x840, FightOutPokemon, flag4);
}

u8 fightOutPokemonBiosGetTameWazaFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x83f, FightOutPokemon, flag3);
}

u8 fightOutPokemonBiosGetOutWazaKoukanaiFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x83e, FightOutPokemon, flag2);
}

u8 fightOutPokemonBiosGetKonranMyselfAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x83d, FightOutPokemon, flag1);
}

u8 fightOutPokemonBiosGetMahiNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x83c, FightOutPokemon, flag0);
}

void* fightOutPokemonBiosGetWazaMenuCurPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x810, FightOutPokemon, wazaMenuCur);
}

void fightOutPokemonBiosSetTokuseiDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x80c, FightOutPokemon, tokusei) = v;
}

u16 fightOutPokemonBiosGetTokuseiDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x80c, FightOutPokemon, tokusei);
}

void fightOutPokemonBiosSetZokuseiDataId(u8* p, u8 i, u16 v) {
    if (p == 0) return;
    if (i >= 2) return;
    RAW_P(u16*, p, 0x808, FightOutPokemon, zokusei)[i] = v;
}

u16 fightOutPokemonBiosGetZokuseiDataId(u8* p, u8 i) {
    if (p == 0) return 0;
    if (i >= 2) return 0;
    return RAW_P(u16*, p, 0x808, FightOutPokemon, zokusei)[i];
}

void* fightOutPokemonBiosGetFightActionBuffPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x7d8, FightOutPokemon, action);
}

void fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(u8* p, u8 i, s16 v) {
    if (p == 0) return;
    if (i >= 12) return;
    RAW_P(s16*, p, 0x7be, FightOutPokemon, meet)[i] = v;
}

s16 fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(u8* p, u8 i) {
    if (p == 0) return -1;
    if (i >= 12) return -1;
    return RAW_P(s16*, p, 0x7be, FightOutPokemon, meet)[i];
}

void fightOutPokemonBiosSetDamageSpeTargetId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x83a, FightOutPokemon, damageSpeTarget) = v;
}

void fightOutPokemonBiosSetDamageSpeValue(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x838, FightOutPokemon, damageSpeValue) = v;
}

void fightOutPokemonBiosSetDamageAtkTargetId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x836, FightOutPokemon, damageAtkTarget) = v;
}

void fightOutPokemonBiosSetDamageAtkValue(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0x834, FightOutPokemon, damageAtkValue) = v;
}

void fightOutPokemonBiosSetSuccessCnt(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x82d, FightOutPokemon, successCnt) = v;
}

void fightOutPokemonBiosSetStockItemDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x830, FightOutPokemon, stockItem) = v;
}

void fightOutPokemonBiosSetUsedItemDataId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x82e, FightOutPokemon, usedItem) = v;
}

void fightOutPokemonBiosSetNamakeFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x82c, FightOutPokemon, namake) = v;
}

u16 fightOutPokemonBiosGetDamageSpeTargetId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x83a, FightOutPokemon, damageSpeTarget);
}

s16 fightOutPokemonBiosGetDamageSpeValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(s16*, p, 0x838, FightOutPokemon, damageSpeValue);
}

u16 fightOutPokemonBiosGetDamageAtkTargetId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x836, FightOutPokemon, damageAtkTarget);
}

s16 fightOutPokemonBiosGetDamageAtkValue(u8* p) {
    if (p == 0) return 0;
    return RAW_F(s16*, p, 0x834, FightOutPokemon, damageAtkValue);
}

u8 fightOutPokemonBiosGetSuccessCnt(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x82d, FightOutPokemon, successCnt);
}

u16 fightOutPokemonBiosGetStockItemDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x830, FightOutPokemon, stockItem);
}

u16 fightOutPokemonBiosGetUsedItemDataId(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x82e, FightOutPokemon, usedItem);
}

u8 fightOutPokemonBiosGetNamakeFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x82c, FightOutPokemon, namake);
}

void fightOutPokemonBiosSetSequencePtr(u8* p, GCuptr v) {
    if (p == 0) return;
    RAW_FP(u32*, p, 0x7ac, FightOutPokemon, sequence) = v;
}

GCuptr fightOutPokemonBiosGetSequencePtr(u8* p) {
    if (p == 0) return 0;
    return RAW_FP(u32*, p, 0x7ac, FightOutPokemon, sequence);
}

void fightOutPokemonBiosSetFightoutTurnCount(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x7bc, FightOutPokemon, turnCount) = v;
}

void fightOutPokemonBiosSetHensinMotoPkxId(u8* p, u16 v) {
    if (p == 0) return;
    RAW_F(u16*, p, 0x7b8, FightOutPokemon, hensinMotoPkxId) = v;
}

void fightOutPokemonBiosSetAbicntAvoid(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b6, FightOutPokemon, abi6) = v;
}

void fightOutPokemonBiosSetAbicntAverage(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b5, FightOutPokemon, abi5) = v;
}

void fightOutPokemonBiosSetAbicntNimbleness(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b4, FightOutPokemon, abi4) = v;
}

void fightOutPokemonBiosSetAbicntSpeDef(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b3, FightOutPokemon, abi3) = v;
}

void fightOutPokemonBiosSetAbicntSpeAtk(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b2, FightOutPokemon, abi2) = v;
}

void fightOutPokemonBiosSetAbicntPhyDef(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b1, FightOutPokemon, abi1) = v;
}

void fightOutPokemonBiosSetAbicntPhyAtk(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0x7b0, FightOutPokemon, abi0) = v;
}

void fightOutPokemonBiosSetFightPokemonPtr(u8* p, GCuptr v) {
    if (p == 0) return;
    RAW_FP(u32*, p, 0x4, FightOutPokemon, fightPokemon) = v;
}

void fightOutPokemonBiosSetMotoFightPokemonPtr(u8* p, GCuptr v) {
    if (p == 0) return;
    RAW_FP(u32*, p, 0x0, FightOutPokemon, moto) = v;
}

void fightPokemonBiosSetHokakuFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0xdd, FightPokemon, darkOut3) = v;
}

u8 fightPokemonBiosGetHokakuFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0xdd, FightPokemon, darkOut3);
}

void fightPokemonBiosSetDarkOutFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0xdc, FightPokemon, darkOut2) = v;
}

void fightPokemonBiosSetLevelUpFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0xdb, FightPokemon, darkOut1) = v;
}

void fightPokemonBiosSetCatchEntryFlag(u8* p, u8 v) {
    if (p == 0) return;
    RAW_F(u8*, p, 0xda, FightPokemon, darkOut0) = v;
}

void fightPokemonBiosSetEntryId(u8* p, s16 v) {
    if (p == 0) return;
    RAW_F(s16*, p, 0xd8, FightPokemon, entryId) = v;
}

void fightPokemonBiosSetMotoPokemonPtr(u8* p, GCuptr v) {
    if (p == 0) return;
    RAW_FP(u32*, p, 0x0, FightPokemon, moto) = v;
}

u16 fightOutPokemonBiosGetFightoutTurnCount(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u16*, p, 0x7bc, FightOutPokemon, turnCount);
}

u8 fightOutPokemonBiosGetAbicntAvoid(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b6, FightOutPokemon, abi6);
}

u8 fightOutPokemonBiosGetAbicntAverage(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b5, FightOutPokemon, abi5);
}

u8 fightOutPokemonBiosGetAbicntNimbleness(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b4, FightOutPokemon, abi4);
}

u8 fightOutPokemonBiosGetAbicntSpeDef(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b3, FightOutPokemon, abi3);
}

u8 fightOutPokemonBiosGetAbicntSpeAtk(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b2, FightOutPokemon, abi2);
}

u8 fightOutPokemonBiosGetAbicntPhyDef(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b1, FightOutPokemon, abi1);
}

u8 fightOutPokemonBiosGetAbicntPhyAtk(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0x7b0, FightOutPokemon, abi0);
}

void* fightOutPokemonBiosGetFightItemPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x7a0, FightOutPokemon, item);
}

void* fightOutPokemonBiosGetFightWazaPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x648, FightOutPokemon, waza);
}

void* fightOutPokemonBiosGetFightoutJoutaiPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 0x34) return 0;
    return RAW_AI(p, 0x308, i, 16, FightOutPokemon, joutai.v);
}

void* fightOutPokemonBiosGetFightPokemonHensinBuffPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x8, FightOutPokemon, hensin);
}

GCuptr fightOutPokemonBiosGetFightPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_FP(u32*, p, 0x4, FightOutPokemon, fightPokemon);
}

GCuptr fightOutPokemonBiosGetMotoFightPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_FP(u32*, p, 0x0, FightOutPokemon, moto);
}

u8 fightPokemonBiosGetDarkOutFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0xdc, FightPokemon, darkOut2);
}

u8 fightPokemonBiosGetLevelUpFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0xdb, FightPokemon, darkOut1);
}

u8 fightPokemonBiosGetCatchEntryFlag(u8* p) {
    if (p == 0) return 0;
    return RAW_F(u8*, p, 0xda, FightPokemon, darkOut0);
}

s16 fightPokemonBiosGetEntryId(u8* p) {
    if (p == 0) return -1;
    return RAW_F(s16*, p, 0xd8, FightPokemon, entryId);
}

void* fightPokemonBiosGetFightJoutaiPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 1) return 0;
    return RAW_AI(p, 0xc8, i, 16, FightPokemon, joutai);
}

void* fightPokemonBiosGetPokemonBuffPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_A(p, 0x4, FightPokemon, buff);
}

GCuptr fightPokemonBiosGetMotoPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return RAW_FP(u32*, p, 0x0, FightPokemon, moto);
}

}
