#include <dolphin/types.h>

// Built with -O4,s (see configure.py).

struct FightOutPokemon;
struct Pokemon;

struct FightOutPokemonEnemy {
    u8 unk0[0xC];
};

extern "C" {

FightOutPokemon* fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(FightOutPokemonEnemy* enemy);
void fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(FightOutPokemonEnemy* enemy, FightOutPokemon* target);
void fightOutPokemonEnemyBiosSetOumuWazaDataId(FightOutPokemonEnemy* enemy, u16 id);
void fightOutPokemonEnemyBiosSetInitHp(FightOutPokemonEnemy* enemy, u16 hp);
void fightOutPokemonEnemyBiosSetDamage(FightOutPokemonEnemy* enemy, u16 damage);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fightOutPokemon);
u16 pokemon_GetHp(Pokemon* pokemon);
bool fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy* enemy);
void fightOutPokemonEnemyInit(FightOutPokemonEnemy* enemy);

FightOutPokemonEnemy* fightOutPokemonEnemySearchAry(FightOutPokemonEnemy* ary, u16 count, FightOutPokemon* target) {
    FightOutPokemonEnemy* enemy;
    u16 i;
    if (ary == NULL) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        enemy = &ary[i];
        if (fightOutPokemonEnemyCheckValid(enemy) &&
            fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy) == target) {
            return enemy;
        }
    }
    return 0;
}

bool fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy* enemy) {
    return fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy) != 0;
}

void fightOutPokemonEnemyCreate(FightOutPokemonEnemy* enemy, FightOutPokemon* target) {
    if (enemy != NULL && target != NULL) {
        fightOutPokemonEnemyInit(enemy);
        fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(enemy, target);
        u16 hp = pokemon_GetHp(fightOutPokemonGetPokemonPtr(target));
        fightOutPokemonEnemyBiosSetInitHp(enemy, hp);
    }
}

void fightOutPokemonEnemyInitAry(FightOutPokemonEnemy* ary, u16 count) {
    if (ary != NULL) {
        for (u16 i = 0; i < count; i++) {
            fightOutPokemonEnemyInit(&ary[i]);
        }
    }
}

void fightOutPokemonEnemyInit(FightOutPokemonEnemy* enemy) {
    fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(enemy, 0);
    fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy, 0);
    fightOutPokemonEnemyBiosSetInitHp(enemy, 0);
    fightOutPokemonEnemyBiosSetDamage(enemy, 0);
}

}
