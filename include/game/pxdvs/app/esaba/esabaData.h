#ifndef GAME_ESABADATA_H
#define GAME_ESABADATA_H

#include <dolphin/types.h>

struct EsaEntry {
    u8 minLevel;
    u8 maxLevel;
    u16 id;
    u32 prob;
    u32 rate;
};

struct EsaHead {
    u32 count;
};

struct EsaTable {
    EsaHead* head;
    EsaEntry* entries;
};

struct EsaData {
    u32 flagNum;
    u32 flag4;
    u32 flag8;
    u32 flagID;
    u32 flagRnd;
    u32 flag14;
    EsaTable** table;
};

struct EsaAppData {
    u16 limitA;
    u16 limitB;
    u16 stepMax;
    u16 randMod;
    u16 unk8;
    u16 pad;
    u32 unkC;
    u32 flagKind;
    u32 flagCheck;
};

#endif
