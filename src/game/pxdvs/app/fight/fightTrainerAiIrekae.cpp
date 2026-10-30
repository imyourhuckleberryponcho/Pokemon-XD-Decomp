#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightPokemon;
struct Pokemon;
struct FightActionData;
struct DeckTrainer;
struct FightOutPokemon { u32 data[0x894 / 4]; };
struct ComboData { u8 type; u8 order; u8 data[10]; };

extern "C" {
u16 HSD_Rand();
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);
u16 fightTrainerDB_GetAiDataId(u16);
DeckTrainer* getDeckTrainerObj__11DeckTrainerFUl(u32);
u16 getComboID__11DeckTrainerCFUc(DeckTrainer*, u8);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u8 pokemon_GetComboPartner(Pokemon*, u8, u8);
u16 pokemon_GetFightTrainerPokemonDataId(Pokemon*);
u16 pokemon_GetHp(Pokemon*);
s16 fightPokemon_GetEntryId(FightPokemon*);
FIGHT_TRAINER* fightFloorGetFightPokemonPtrToFightTrainerPtr(void*, FightPokemon*);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void*, FIGHT_TRAINER*, FightPokemon**, u8, u8);
u16 fightTrainerGetIrekaeFightPokemonAry(FIGHT_TRAINER*, FightPokemon**);
void fightOutPokemonBiosCopy(FightOutPokemon*, FightOutPokemon*);
void fightOutPokemonCreate(FightOutPokemon*, FightPokemon*, u8);
void fightOutPokemonCreateFightAction(FightOutPokemon*, u8, u8, u8, FightActionData*, s32);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon*, u16, u8);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon*, u16);
s8 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
s8 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon*, u16);
u8 fightTrainerAiDB_GetLastValueRevise();
u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16);
u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16);
u8 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(u16);
u8 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16, u8);
s32 fightTrainerAiDB_GetZokuseiReviseValue(u16, u8);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER*, void*, u8);
u16 fightTrainerAiGetFightPokemonSubayasa(FIGHT_TRAINER*, FightPokemon*);
s32 fightTrainerAiGetFightPokemonZokuseiAisyouValue(FIGHT_TRAINER*, FightPokemon*, u8);
u16 fightTrainerAiGetFightOutPokemonBasisSubayasa(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonBasisPhyAtk(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonBasisSpeAtk(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER*, FightOutPokemon*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER*, FightOutPokemon*, u16*, u8, u8);
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER*, FightPokemon*, u16*, u8, u8);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER*, FightPokemon*, u16);
u8 fightTrainerAiIsFightPokemonNokoriHpHikui(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiKie(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntHikui(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightOutPokemon*);
u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(FIGHT_TRAINER*, FightPokemon*);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER*, u16, u8);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER*, u16, FightOutPokemon*);
s32 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER*, u16);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER*, FightOutPokemon*, u16, s32);
u16 fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER*, FightPokemon*, u16, s32);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*, u8);
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*, u8);
u8 fightTrainerCheckCanIrekaeFightPokemon(FightPokemon*);
u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag();
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER*, u16);
s32 fightTrainerAiReviseValueByAddsubDataId(s32, s32, FIGHT_TRAINER*, u16);
s32 fightTrainerAiGetValueAryMaxBanme(s32*, u16, u8);
extern ComboData comboid[];
extern FightActionData fight_action_data_turn;
extern u32* zokusei_data_number;
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER*, void*, u8, FightOutPokemon*);
s32 fightTrainerAiGetFightPokemonIrekaeModosuValue(FIGHT_TRAINER*, FightOutPokemon*, void*);
u16 fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(FIGHT_TRAINER*, FightPokemon*);
u16 fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(FIGHT_TRAINER*, FightOutPokemon*);

u8 fightTrainerAiIrekae_SelComboPartner(FIGHT_TRAINER* trainer, FightPokemon* pokemon, FightOutPokemon* partner)
{
    Pokemon* p = fightPokemonGetPokemonPtr(pokemon);
    DeckTrainer* deck = getDeckTrainerObj__11DeckTrainerFUl(fightTrainer_GetFightTrainerDataId(trainer));
    for (u8 i = 0; i < 4; i++) {
        u16 id = getComboID__11DeckTrainerCFUc(deck, i);
        if (id == 0) continue;
        ComboData* combo = &comboid[id];
        u8 order = combo->order;
        if (combo->type == 2) {
            if (partner == 0) continue;
            Pokemon* other = fightOutPokemonGetPokemonPtr(partner);
            u8 otherFirst = pokemon_GetComboPartner(other, i, 1);
            u8 otherSecond = pokemon_GetComboPartner(other, i, 0);
            u8 first = pokemon_GetComboPartner(p, i, 1);
            u8 second = pokemon_GetComboPartner(p, i, 0);
            if (order == 0 && ((otherFirst == 1 && second == 1) || (otherSecond == 1 && first == 1))) return 1;
            if (order == 1 && otherFirst == 1 && second == 1) return 2;
        }
        if (combo->type == 1) {
            u8 first = pokemon_GetComboPartner(p, i, 1);
            u8 second = pokemon_GetComboPartner(p, i, 0);
            if (first == 1 || second == 1) {
                if (order == 0) return 1;
                if (order == 1) return 0;
            }
        }
    }
    return 0;
}

s32 fightTrainerAiSelectFightActionIrekae(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void* target)
{
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    if (fightTrainerAiGetFightPokemonIrekaeModosuValue(trainer, pokemon, target) <= 0) return 0;
    s16 entry = fightTrainerAiSelectIrekaeDasuFightPokemon(trainer, target, 1, pokemon);
    if (entry < 0) return 0;
    fightOutPokemonCreateFightAction(pokemon, 0, 9, 0, &fight_action_data_turn, entry);
    return 1;
}

s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FIGHT_TRAINER* trainer, void*, u8, FightOutPokemon* pokemon)
{
    FightPokemon* candidate;
    FightOutPokemon* opponent;
    FightOutPokemon saved;
    FightPokemon* party[24];
    FightPokemon* candidates[6];
    s32 values[6];
    FightOutPokemon* opponents[8];
    FightOutPokemon* active[8];
    u16 moves[8];
    u16 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    u16 type;
    u16 move;
    u8 revise = fightTrainerAiDB_GetLastValueRevise();
    u8 weather = fightTrainerAiGetFightFloorNowTenkouDataId(trainer, 0, 1);
    for (u8 i = 0; i < 6; i++) values[i] = 0;
    fightOutPokemonBiosCopy(&saved, pokemon);
    if (fightOutPokemonCheckFightOut(pokemon) == 1) fightOutPokemonIsFightActionAttackWazaOut(pokemon, 0xE2, 0);
    u16 count = fightTrainerGetIrekaeFightPokemonAry(trainer, candidates);
    u16 opponentCount = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, opponents, 0, 1);
    u16 partyCount = fightFloorGetFightTrainerFightPokemonPtrAry(0, trainer, party, 1, 1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, active, 1, 1);
    if (count == 0) return -1;
    if (fightTrainerAiDB_GetPokemonSelectRandomFlag(ai) == 1) {
        candidate = candidates[(u16)(HSD_Rand() % count)];
        if (candidate != 0) {
            fightFloorGetFightPokemonPtrToFightTrainerPtr(0, candidate);
            return fightPokemon_GetEntryId(candidate);
        }
    }
    s32 maxAffinity = -65535;
    u16 minId = 65535;
    u32 maxSpeed = 0;
    for (u8 i = 0; i < count; i++) {
        candidate = candidates[i];
        if (candidate != 0 && fightPokemon_GetEntryId(candidate) >= 0) {
            int speed = fightTrainerAiGetFightPokemonSubayasa(trainer, candidate);
            s32 affinity = fightTrainerAiGetFightPokemonZokuseiAisyouValue(trainer, candidate, 2);
            u16 id = pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(candidate));
            if (maxSpeed < speed) maxSpeed = speed;
            if (maxAffinity < affinity) maxAffinity = affinity;
            if (minId > id) minId = id;
        }
    }
    if (fightTrainerAiDB_GetPokemonDataOrderOutFlag(ai) == 1) {
        for (u8 i = 0; i < count; i++) {
            candidate = candidates[i];
            if (candidate != 0 && fightPokemon_GetEntryId(candidate) >= 0) {
                fightFloorGetFightPokemonPtrToFightTrainerPtr(0, candidate);
                if (minId >= pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(candidate))) {
                    fightFloorGetFightPokemonPtrToFightTrainerPtr(0, candidate);
                    return fightPokemon_GetEntryId(candidate);
                }
            }
        }
    }
    s32 partyCountLong;
    s32 reviseLong;
    partyCountLong = partyCount;
    reviseLong = revise;
    s32 reviseRange = revise * 2 + 1;
    for (u8 i = 0; i < count; i++) {
        candidate = candidates[i];
        if (candidate == 0 || fightPokemon_GetEntryId(candidate) < 0) continue;
        fightFloorGetFightPokemonPtrToFightTrainerPtr(0, candidate);
        fightOutPokemonCreate(pokemon, candidate, 0);
        u16 moveCount = fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer, pokemon, moves, 0, 1);
        u8 canHit = 0;
        for (u8 j = 0; j < opponentCount; j++) {
            opponent = opponents[j];
            if (opponent != 0) {
                for (u16 k = 0; k < moveCount; k++) {
                    u16 move = moves[k];
                    if (move != 0 && move != 0x176 && fightTrainerAiWazaDoWazaHitFunc(trainer, pokemon, move, opponent) == 1) { canHit = 1; break; }
                }
                if (canHit == 1) break;
            }
        }
        fightOutPokemonBiosCopy(pokemon, &saved);
        moveCount = fightTrainerAiGetFightPokemonWazaDataIdAry(trainer, candidate, moves, 0, 1);
        u8 combo = fightTrainerAiIrekae_SelComboPartner(trainer, candidate, active[0]);
        if (combo == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x1B);
        if (combo == 2) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x1C);
        u8 key = fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer, candidate);
        if (key == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x1D);
        if (key == 2) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x1E);
        if (key == 3) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x1F);
        for (u8 j = 0; j < 2; j++) {
            u16 type = fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(ai, j);
            if (type != 9 && fightTrainerAiIsFightPokemonZokuseiDataId(trainer, candidate, type) == 1)
                values[i] = fightTrainerAiReviseValueByAddsubDataId(values[i], fightTrainerAiDB_GetZokuseiReviseValue(ai, j), trainer, 0x20);
        }
        if (fightTrainerAiIsFightPokemonNokoriHpHikui(trainer, candidate) == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x21);
        if (canHit == 0) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x22);
        if (maxSpeed <= fightTrainerAiGetFightPokemonSubayasa(trainer, candidate)) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x24);
        if (maxAffinity <= fightTrainerAiGetFightPokemonZokuseiAisyouValue(trainer, candidate, 2)) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x23);
        for (u8 j = 0; j < opponentCount; j++) {
            opponent = opponents[j];
            if (opponent != 0) {
                for (u16 k = 0; k < moveCount; k++) {
                    move = moves[k];
                    if (move == 0) continue;
                    type = fightTrainerAiGetWazaZokuseiDataId(trainer, move, pokemon);
                    if (type != 9 && fightTrainerAiIsWazaTypeId(trainer, move, 1) != 0 && fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer, opponent, type, fightTrainerAiGetWazaIryoku(trainer, move)) == 0x41)
                        values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x25);
                }
            }
        }
        for (u8 j = 0; j < opponentCount; j++) {
            opponent = opponents[j];
            if (opponent != 0) {
                u16 n = fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer, opponent, moves, 0, 0);
                for (u16 k = 0; k < n; k++) {
                    u16 move = moves[k];
                    if (move == 0) continue;
                    u16 type = fightTrainerAiGetWazaZokuseiDataId(trainer, move, opponent);
                    if (type != 9 && fightTrainerAiIsWazaTypeId(trainer, move, 1) != 0 && fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer, candidate, type, fightTrainerAiGetWazaIryoku(trainer, move)) == 0x41)
                        values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x26);
                }
            }
        }
        if (fightTrainerAiDB_GetPokemonSelectWeakPointFlag(ai) == 1) {
            for (u16 type = 0; type < *zokusei_data_number; type++) {
                if (type != 9 && fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer, candidate, type, 1) == 0x41) {
                    for (u8 j = 0; j < partyCountLong; j++) {
                        FightPokemon* other = party[j];
                        if (other != 0 && fightFloorGetFightPokemonPtrToFightTrainerPtr(0, other) != 0) {
                            u8 state = fightTrainerCheckCanIrekaeFightPokemon(other);
                            if (state == 1) continue;
                            if ((state == 2 || state == 3) && fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer, other, type, 1) == 0x41)
                                values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x27);
                        }
                    }
                }
            }
        }
        u16 add = fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(trainer, candidate);
        if (add != 0) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, add);
        if (weather == 2) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, candidate, 0x21) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(trainer, candidate, 0x2C) == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x2C);
        } else if (weather == 1) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, candidate, 0x22) == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x2D);
        } else if (weather == 3) {
            u8 immune = 0;
            if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, candidate, 8) == 1) immune = 1;
            if (fightTrainerAiIsFightPokemonZokuseiDataId(trainer, candidate, 8) == 1 || fightTrainerAiIsFightPokemonZokuseiDataId(trainer, candidate, 5) == 1 || fightTrainerAiIsFightPokemonZokuseiDataId(trainer, candidate, 4) == 1) immune = 1;
            if (immune == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x2E);
        } else if (weather == 4) {
            if (fightTrainerAiIsFightPokemonZokuseiDataId(trainer, candidate, 0xF) == 1) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x2F);
        }
        for (u8 j = 0; j < opponentCount; j++) {
            opponent = opponents[j];
            if (opponent != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, opponent, 0x22) == 1) {
                u16 waza = fightOutPokemon_GetMotoWazaDataId(opponent);
                s32 damage = fightTrainerAiWazaDoWazaDamageFightPokemonFunc(trainer, opponent, waza, candidate, 0);
                if (damage >= pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(candidate))) values[i] = fightTrainerAiAddValueByAddsubDataId(values[i], trainer, 0x31);
            }
        }
        if (dbgMenuFightGetFightTrainerAiLastValueReviseFlag() == 1) values[i] = fightTrainerAiAddValue(values[i], HSD_Rand() % reviseRange - reviseLong);
    }
    s32 index = fightTrainerAiGetValueAryMaxBanme(values, count, 1);
    if (index < 0) return -1;
    candidate = candidates[index];
    if (candidate == 0) return -1;
    fightFloorGetFightPokemonPtrToFightTrainerPtr(0, candidate);
    return fightPokemon_GetEntryId(candidate);
}

s32 fightTrainerAiGetFightPokemonIrekaeModosuValue(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon, void*)
{
    u16 outerIndex;
    u16 move;
    u16 innerIndex;
    FightOutPokemon* opponent;
    u16 hp;
    u8 hit;
    u16 count;
    u16 speed;
    s32 value;
    u8 canKO;
    u8 canHit;
    u16 moveCount;
    FightOutPokemon* opponents[8];
    u16 moves[8];
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    value = 0;
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    speed = fightTrainerAiGetFightOutPokemonBasisSubayasa(trainer, pokemon);
    moveCount = fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer, pokemon, moves, 0, 1);
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, opponents, 0, 1);
    canKO = 0;
    canHit = 0;
    for (outerIndex = 0; outerIndex < count; outerIndex++) {
        opponent = opponents[outerIndex];
        if (opponent != 0) {
            hp = fightTrainerAiGetFightOutPokemonNowHp(trainer, opponent);
            for (innerIndex = 0; innerIndex < moveCount; innerIndex++) {
                move = moves[innerIndex];
                if (move != 0 && move != 0x176) {
                    hit = fightTrainerAiWazaDoWazaHitFunc(trainer, pokemon, move, opponent);
                    if (hit == 1) canHit = 1;
                    if (fightTrainerAiIsFightOutPokemonJoutaiKie(trainer, opponent) == 1) canHit = 1;
                    if (fightTrainerAiIsWazaTypeId(trainer, move, 1) != 0 && hp < fightTrainerAiWazaDoWazaDamageFunc(trainer, pokemon, move, opponent, 0) && hit == 1) canKO = 1;
                }
            }
        }
    }
    if (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) != 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 1);
    if (fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer, pokemon) == 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 2);
    else if (fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer, pokemon) != 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 3);
    if (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer, pokemon) == 1) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 4);
    if (fightTrainerAiIsFightOutPokemonAllAbiCntHikui(trainer, pokemon) == 1) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 5);
    if (canHit == 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 6);
    if (canKO == 1) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 7);
    if (fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer, pokemon) == 1) {
        for (u16 i = 0; i < count; i++) {
            if (opponents[i] != 0 && fightTrainerAiGetFightOutPokemonBasisSubayasa(trainer, opponents[i]) > speed) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 8);
        }
    }
    u16 add = fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(trainer, pokemon);
    if (add != 0) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, add);
    for (u16 i = 0; i < count; i++) {
        opponent = opponents[i];
        if (opponent != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, opponent, 0x22) == 1) {
            s32 damage = fightTrainerAiWazaDoWazaDamageFunc(trainer, pokemon, fightOutPokemon_GetMotoWazaDataId(opponent), opponent, 0);
            if (damage >= fightOutPokemonNowHpWaruValue(pokemon, 1)) value = fightTrainerAiAddValueByAddsubDataId(value, trainer, 0x1A);
        }
    }
    return value;
}

u16 fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(FIGHT_TRAINER* trainer, FightPokemon* pokemon)
{
    FightOutPokemon* opponents[8];
    u8 weather = fightTrainerAiGetFightFloorNowTenkouDataId(trainer, 0, 1);
    u16 abilities[10] = { 1, 2, 0x23, 0x24, 0x2D, 0x32, 0x35, 0x36, 0x3B, 0x46 };
    u16 count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, trainer, opponents, 0, 1);
    if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, pokemon, 0x16) == 1) {
        for (u16 i = 0; i < count; i++) {
            u16 physical = fightTrainerAiGetFightOutPokemonBasisPhyAtk(trainer, opponents[i]);
            u16 special = fightTrainerAiGetFightOutPokemonBasisSpeAtk(trainer, opponents[i]);
            if (physical >= special) return 0x28;
        }
    }
    if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, pokemon, 0x24) == 1) {
        for (u16 i = 0; i < count; i++) {
            u16 j;
            u8 excluded = 0;
            for (j = 0; j < 10; j++) {
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer, opponents[i], abilities[j]) == 1) { excluded = 1; break; }
            }
            if (excluded != 1) return 0x29;
        }
    }
    if (weather != 0) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, pokemon, 0x4D) == 1) return 0x2A;
        if (fightTrainerAiIsFightPokemonTokuseiDataId(trainer, pokemon, 0xD) == 1) return 0x2B;
    }
    return 0;
}

u16 fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(FIGHT_TRAINER* trainer, FightOutPokemon* pokemon)
{
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 9) == 1) return 9;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0xA) == 1) return 0xA;
    s8 duration = fightOutPokemonGetKaisuuJoutaiDataId(pokemon, 0x1E);
    s8 elapsed = fightOutPokemonGetNowKaisuuJoutaiDataId(pokemon, 0x1E);
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x1E) == 1 && fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer, pokemon) == 0 && elapsed + 1 >= duration) return 0xB;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0xE) == 1) return 0xC;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x17) == 1) return 0xD;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x18) == 1) return 0xE;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x19) == 1) return 0xF;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x1B) == 1) return 0x10;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x1C) == 1) return 0x11;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x1D) == 1) return 0x12;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x26) == 1) return 0x13;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x27) == 1) return 0x14;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x28) == 1) return 0x15;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x29) == 1) return 0x16;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x2A) == 1) return 0x17;
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer, pokemon, 0x30) == 1) return 0x18;
    return 0;
}
}
