#include <dolphin/types.h>

struct DeckDataVirtualItem {
    u8 num;
    u8 unk1;
    u16 id;
};

struct DeckDataVirtual {
    u8 unk0;
    u8 turnLimit;
    u8 pokemonNum;
    u8 unk3[5];
    u32 allyDeck;
    u32 enemyDeck;
    u32 title;
    u32 explanation1;
    u32 explanation2;
    u32 flag;
    u8 allyJoutai[6];
    u8 enemyJoutai[6];
    DeckDataVirtualItem items[4];
};

extern "C" {
extern u32* deckdata_virtual_number;
extern DeckDataVirtual* deckdata_virtual;
void GSflagSet(u32 flag, s32 on);
bool GSflagTest(u32 flag);
}

static inline DeckDataVirtual* _deckDataVirtualGetPtr(u16 id) {
    if (id >= *deckdata_virtual_number) {
        return 0;
    }
    return &deckdata_virtual[id];
}

void deckDataVirtualDB_SetFlagData(u16 id, bool on) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck != NULL) {
        GSflagSet(deck->flag, on);
    }
}

bool deckDataVirtualDB_GetFlagData(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return false;
    }
    return GSflagTest(deck->flag);
}

u32 deckDataVirtualDB_GetFlag(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->flag;
}

u8 deckDataVirtualDB_GetItemNum(u16 id, u8 index) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return deck->items[index].num;
}

u16 deckDataVirtualDB_GetItemID(u16 id, u8 index) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    if (index >= 4) {
        return 0;
    }
    return deck->items[index].id;
}

u8 deckDataVirtualDB_GetEnemyJoutai(u16 id, u8 index) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return deck->enemyJoutai[index];
}

u8 deckDataVirtualDB_GetAllyJoutai(u16 id, u8 index) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    if (index >= 6) {
        return 0;
    }
    return deck->allyJoutai[index];
}

u32 deckDataVirtualDB_GetExplanetion2(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->explanation2;
}

u32 deckDataVirtualDB_GetExplanetion1(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->explanation1;
}

u32 deckDataVirtualDB_GetTitle(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->title;
}

u32 deckDataVirtualDB_GetEnemyDeck(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->enemyDeck;
}

u32 deckDataVirtualDB_GetAllyDeck(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->allyDeck;
}

u8 deckDataVirtualDB_GetPokemonNum(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->pokemonNum;
}

u8 deckDataVirtualDB_GetTurnLimit(u16 id) {
    DeckDataVirtual* deck = _deckDataVirtualGetPtr(id);
    if (deck == NULL) {
        return 0;
    }
    return deck->turnLimit;
}

DeckDataVirtual* deckDataVirtual_GetPtr(u16 id) { return _deckDataVirtualGetPtr(id); }
