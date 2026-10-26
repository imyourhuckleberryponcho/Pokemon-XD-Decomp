#include <dolphin/types.h>

#pragma dont_inline on

struct FightKoukaData;
struct FightTarget;

extern "C" {

FightKoukaData* fightKoukaDataBiosGetPtr(u16 id);
u16 fightKoukaDataBiosGetKoukaDataId(FightKoukaData* data);
u16 fightKoukaDataBiosGetFightTargetDataId(FightKoukaData* data);
u16 fightKoukaDataBiosGetFightJoukenDataId(FightKoukaData* data);
u8 fightFloor_GetFightType(s32);
FightTarget* fightTargetGetPtr(u16 targetDataId, void* fightPokemon, s32 fightType);
u8 fightJoukenExec(u16 joukenDataId, void* fightPokemon);
void koukaExec(s32 koukaDataId, FightTarget* target, void* fightPokemon, s32);
BOOL fightKoukaDoJoukenAndKouka(void* fightPokemon, u16 joukenDataId, u16 targetDataId, u16 koukaDataId);

u16 fightKoukaDataGetKoukaDataId(u16 id) {
    return fightKoukaDataBiosGetKoukaDataId(fightKoukaDataBiosGetPtr(id));
}

u16 fightKoukaDataGetFightTargetDataId(u16 id) {
    return fightKoukaDataBiosGetFightTargetDataId(fightKoukaDataBiosGetPtr(id));
}

u16 fightKoukaDataGetFightJoukenDataId(u16 id) {
    return fightKoukaDataBiosGetFightJoukenDataId(fightKoukaDataBiosGetPtr(id));
}

BOOL fightKoukaDoFightKoukaJoukenAndKouka(void* fightPokemon, u16 id) {
    u16 joukenDataId = fightKoukaDataGetFightJoukenDataId(id);
    u16 targetDataId = fightKoukaDataGetFightTargetDataId(id);
    u16 koukaDataId = fightKoukaDataGetKoukaDataId(id);
    return fightKoukaDoJoukenAndKouka(fightPokemon, joukenDataId, targetDataId, koukaDataId);
}

BOOL fightKoukaDoJoukenAndKouka(void* fightPokemon, u16 joukenDataId, u16 targetDataId, u16 koukaDataId) {
    BOOL result = FALSE;
    FightTarget* target = fightTargetGetPtr(targetDataId, fightPokemon, fightFloor_GetFightType(0));
    if (fightJoukenExec(joukenDataId, fightPokemon) == 1) {
        koukaExec(koukaDataId, target, fightPokemon, 0);
        result = TRUE;
    }
    return result;
}

}
