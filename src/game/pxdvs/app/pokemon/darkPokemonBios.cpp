#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/memcard/savedata.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

class DeckDarkPokemon {
public:
    bool isScenarioPokemon() const;
    u16 getDarkWaza(s8 index) const;
    u8 getPlayerLevel() const;
    u8 getSnatchRatio() const;
    u16 getInitDarkPoint() const;
};

extern "C" {

extern u16 darkPokemonList[];
extern u32 darkPokemonList_number;

DarkPokemon* darkPokemonGetDarkPokemon(u32 id);
DeckDarkPokemon* deckGetDeckDarkPokemon(u32 id);
u32 deckGetDarkPokemonSize(void);
u32 fightFloorGetStatus(s32, s32, s32, s32);
u16* darkPokemonListBiosGetDPList(u16 index);
u16 darkPokemonBiosGetInitDarkPoint(u16 id);

u16 darkPokemonListBiosGetPokemonID(u16 index) {
    u16* list = darkPokemonListBiosGetDPList(index);
    if (list != NULL) {
        return *list;
    }
    return 0;
}

u16* darkPokemonListBiosGetDPList(u16 index) {
    u16* list = &darkPokemonList[index];
    if (index < darkPokemonList_number) {
        return list;
    }
    return 0;
}

u32 darkpokemonBiosGetScenarioNum(void) {
    u16 i;
    u32 count = 0;
    for (i = 0; i < deckGetDarkPokemonSize(); i++) {
        DeckDarkPokemon* deck = deckGetDeckDarkPokemon(i);
        if (deck != NULL && deck->isScenarioPokemon()) {
            count++;
        }
    }
    return count;
}

u16 darkPokemonBiosGetSteps(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark == NULL) {
        return 0;
    }
    return dark->getWalkCount();
}

void darkPokemonBiosSetSteps(u16 id, u16 steps) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setWalkCount(steps);
    }
}

void darkPokemonBiosSetInfomation(u16 id, s32 level) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setSnatchInfoLevel(level);
    }
}

u32 darkPokemonBiosGetRnd(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        return dark->getRnd();
    }
    return 0;
}

void darkPokemonBiosSetRnd(u16 id, u32 rnd) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setRnd(rnd);
    }
}

s32 darkPokemonBiosGetStatusRnd(u16 id, s32 index) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        return (s8)dark->getStatusRnd(index);
    }
    return 0;
}

void darkPokemonBiosSetStatusRnd(u16 id, s32 index, s32 value) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setStatusRnd(index, value);
    }
}

BOOL darkPokemonBiosGetFightFlag(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL && dark->getStatus() >= 1) {
        return TRUE;
    }
    return FALSE;
}

void darkPokemonBiosSetFightFlag(u16 id) {
    u32 floorId;
    u32 catchFloorId;
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        floorId = fightFloorGetStatus(0, 0, 0x4A, 0);
        catchFloorId = dark->getCatchFloorId();
        if (dark->getStatus() == 0 && catchFloorId != 0xB5) {
            Hero* hero = (Hero*)savedataGetStatus(0, 2);
            u8 count = hero->getMeetDarkPokemonCount();
            hero->setMeetDarkPokemonCount(count + 1);
            dark->setSnatchIndex(count);
            dark->addStatus(darkPokemonStatus1);
            dark->setCatchFloorId(floorId);
            dark->setUpdate(true);
        }
        if (catchFloorId == 0xB5) {
            dark->addStatus(darkPokemonStatus1);
            dark->setCatchFloorId(floorId);
            dark->setUpdate(true);
        }
    }
}

BOOL darkPokemonBiosGetSnatchSuccessFlag(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL && dark->getStatus() >= 3) {
        return TRUE;
    }
    return FALSE;
}

BOOL darkPokemonBiosGetReliveFlag(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL && dark->getStatus() == 4) {
        return TRUE;
    }
    return FALSE;
}

void darkPokemonBiosSetReliveFlag(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setStatus(darkPokemonStatusRelive);
    }
}

bool darkPokemonBiosGetInformationFlag(u16 id) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        return dark->isInformation();
    }
    return false;
}

void darkPokemonBiosSetInformationFlag(u16 id, bool information) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(id);
    if (dark != NULL) {
        dark->setInformation(information);
    }
}

u16 darkPokemonBiosGetTemotiDarkWaza(u16 id, s32 index) {
    DeckDarkPokemon* deck = deckGetDeckDarkPokemon(id);
    if (deck != NULL) {
        return deck->getDarkWaza(index);
    }
    return 0;
}

u8 darkPokemonBiosGetLevel(u16 id) {
    DeckDarkPokemon* deck = deckGetDeckDarkPokemon(id);
    if (deck != NULL) {
        return deck->getPlayerLevel();
    }
    return 0;
}

u8 darkPokemonBiosGetHokakuritu(u16 id) {
    DeckDarkPokemon* deck = deckGetDeckDarkPokemon(id);
    if (deck != NULL) {
        return deck->getSnatchRatio();
    }
    return 0;
}

u16 darkPokemonBiosGetDarkPoint(u16 id) { return darkPokemonBiosGetInitDarkPoint(id); }

u16 darkPokemonBiosGetInitDarkPoint(u16 id) {
    DeckDarkPokemon* deck = deckGetDeckDarkPokemon(id);
    if (deck != NULL) {
        return deck->getInitDarkPoint();
    }
    return 0;
}

}
