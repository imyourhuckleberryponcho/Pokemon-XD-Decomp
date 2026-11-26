#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/gcptr.h>
#include <game/statusval.h>
#include <game/pcboxes.h>

enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };
struct DarkPokemon {
    void setPlace(darkPokemonWhere, u8);
};
struct Pokemon {
    u8 data[0xC4];
    DarkPokemon* getDarkPokemon();
};
extern "C" {
bool pokemonCheckValid(Pokemon*);
void pokemonInit(Pokemon*);
void pokemonInitAry(Pokemon*, u16);
void pokemonAllKaihuku(Pokemon*);
}

struct PCBoxItem {
    u32 data;
};

struct PCBoxBox {
    u16 name[10];
    Pokemon pokemon[30];
};

extern "C" {
void* savedataGetStatus(PCARG(s32, void*), s32);
void msgctrlSetValue(s32, GCuptr);
u16* GSmsgMakeGScharStr(u16*, s32, u32);
void itemInitAry(void*, u16);
void* memcpy(void*, const void*, unsigned long);
void GScharCpy(u16*, u16*);
void itemReplace(void*, void*);
u8* itemDataBiosGetPtr(u16);
u8 itemCheckValid(void*);
StatusS32 itemGetStatus(void*, u32, u32, u32);
s32 itemDecItemDataIdAry(void*, u16, u16, PCARG(u16, u32), s16, u16, u32);
s32 itemAddItemDataIdAry(void*, u16, u16, PCARG(u16, u32), s16, u16, u32, u32);
}
s32 menuPcBoxGetLastViewBox();
void menuPocketDebugMakePokemonBySN(Pokemon&, u16, bool, f32);

struct PCBOX;
#ifndef __MWERKS__
static inline PCBoxBox* pcboxBoxPtr(PCBOX* base, s32 b);
#endif

struct PCBOX {
public:
    PCBoxBox box[8];
    PCBoxItem item[235];
    s32 lastViewBox;
    static s8 lastWatchBoxID;

    static PCBOX* getPointer();
    bool isPokemonFull();
    s8 getPokemonBoxNbEmptySlot(s8);
    s8 getPokemonBoxNbUsedSlot(s8);
    void* getPokemonBoxName(s8);
    bool delPokemon(s8, s8);
    bool addPokemonLastWatchBox(Pokemon*);
    bool addPokemon(Pokemon*, s8);
    bool setPokemon(Pokemon*, s8, s8);
    Pokemon* getPokemon(s8, s8);
    inline s32 setPokemonImpl(Pokemon*, s8, s8);
    inline s32 delPokemonImpl(s8, s8);
    void init();

    static inline Pokemon* getRecord(PCBOX* base, s8 b, s8 i) {
        if (b < 0 || b >= PC_PCBOX_COUNT()) {
            return 0;
        }
        if (i < 0 || i >= 30) {
            return 0;
        }
#ifdef __MWERKS__
        return &base->box[b].pokemon[i];
#else
        PCBoxBox* bx = pcboxBoxPtr(base, b);
        return bx != 0 ? &bx->pokemon[i] : 0;
#endif
    }
};

s8 PCBOX::lastWatchBoxID;

#ifndef __MWERKS__
extern "C" {
s32 (*PortXD_PcBoxCount)(void) = 0;
void* (*PortXD_PcBoxExtraBox)(s32 box) = 0;
s32 (*PortXD_PcBoxGetLastView)(void) = 0;
void (*PortXD_PcBoxSetLastView)(s32 box) = 0;

s32 pcboxCount(void) {
    if (PortXD_PcBoxCount == 0 || PortXD_PcBoxExtraBox == 0) {
        return PC_PCBOX_GC;
    }
    s32 n = PortXD_PcBoxCount();
    if (n < PC_PCBOX_GC) {
        n = PC_PCBOX_GC;
    }
    if (n > PC_PCBOX_MAX) {
        n = PC_PCBOX_MAX;
    }
    return n;
}

void pcboxMakeDefaultName(u16* dst, s32 boxNumber1Based) {
    msgctrlSetValue(0x34, boxNumber1Based);
    GSmsgMakeGScharStr(dst, 9, 0x3b39);
}
}

static inline PCBoxBox* pcboxBoxPtr(PCBOX* base, s32 b) {
    if (b < 0 || b >= pcboxCount()) {
        return 0;
    }
    if (b < PC_PCBOX_GC) {
        return &base->box[b];
    }
    return (PCBoxBox*)PortXD_PcBoxExtraBox(b);
}
#endif

PCBOX* PCBOX::getPointer() {
    return (PCBOX*)savedataGetStatus(0, 3);
}

inline s32 PCBOX::setPokemonImpl(Pokemon* src, s8 b, s8 i) {
    PCBOX* base = this;
    if (base == 0) {
        base = PCBOX::getPointer();
    }
    Pokemon* p = PCBOX::getRecord(base, b, i);
    if (p == 0) {
        return 0;
    }
    memcpy(p, src, sizeof(Pokemon));
    pokemonAllKaihuku(p);
    DarkPokemon* dark = p->getDarkPokemon();
    if (dark) {
        dark->setPlace(place2, b);
    }
    return 1;
}

extern "C" {

static inline void fillBox(s8 b, int& sn) {
    u8 box = b;
    for (int j = 0; j < 30; j++) {
        Pokemon pk;
        menuPocketDebugMakePokemonBySN(pk, sn++, j == 1, 0.5f);
        PCBOX::getPointer()->setPokemonImpl(&pk, box, j);
    }
}

static inline void fillAll() {
    int sn = 0;
    for (int i = 0; i < 8; i++) {
        int b = i;
        for (int j = 0; j < 30; j++) {
            Pokemon pk;
            menuPocketDebugMakePokemonBySN(pk, sn++, j == 1, 0.5f);
            PCBOX::getPointer()->setPokemonImpl(&pk, b, j);
        }
    }
}

void pcboxDebugPokemonSetupFull() {
    PCBOX* pcbox = PCBOX::getPointer();
    for (int i = 0; i < 8; i++) {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(pcbox->box[i].name, 9, 0x3b39);
        pokemonInitAry(pcbox->box[i].pokemon, 30);
    }
    itemInitAry(pcbox->item, 235);
    pcbox->lastViewBox = 0;
    PCBOX::getPointer();
    fillAll();
}

static inline void fillBoxLast(s8 b, int& sn) {
    u8 box = b;
    for (int j = 0; j < 30; j++) {
        Pokemon pk;
        menuPocketDebugMakePokemonBySN(pk, sn++, false, 0.0f);
        PCBOX::getPointer()->setPokemonImpl(&pk, box, j);
    }
}

static inline void fillBoxFew(s8 b, int& sn, Pokemon& pk) {
    int box = b;
    for (int j = 0; j < 3; j++) {
        menuPocketDebugMakePokemonBySN(pk, sn++, j % 10 == 0, 0.1f);
        PCBOX::getPointer()->setPokemonImpl(&pk, box, j);
    }
}

static inline void fillAllFew(Pokemon& pk) {
    int sn = 0;
    for (int i = 0; i < 8; i++) {
        if (i == 7) {
            int box = i;
            for (int j = 0; j < 30; j++) {
                Pokemon pk2;
                menuPocketDebugMakePokemonBySN(pk2, sn++, false, 0.0f);
                PCBOX::getPointer()->setPokemonImpl(&pk2, box, j);
            }
        } else {
            int box = i;
            for (int j = 0; j < 3; j++) {
                menuPocketDebugMakePokemonBySN(pk, sn++, j % 10 == 0, 0.1f);
                PCBOX::getPointer()->setPokemonImpl(&pk, box, j);
            }
        }
    }
}

void pcboxDebugPokemonSetup() {
    Pokemon pk;
    PCBOX* pcbox = PCBOX::getPointer();
    for (int i = 0; i < 8; i++) {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(pcbox->box[i].name, 9, 0x3b39);
        pokemonInitAry(pcbox->box[i].pokemon, 30);
    }
    itemInitAry(pcbox->item, 235);
    pcbox->lastViewBox = 0;
    PCBOX::getPointer();
    fillAllFew(pk);
}

}

static inline s8 nbEmptyImpl(PCBOX* base, s8 b) {
    u8* pokemon;
    s8 count = 0;
    s8 index;
    PCBOX* self = base;
    if (!self) {
        self = PCBOX::getPointer();
    }
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        count = -1;
    }
#ifndef __MWERKS__
    else if (pcboxBoxPtr(self, b) == 0) {
        count = -1;
    }
#endif
    else {
        index = 0;
#ifdef __MWERKS__
        pokemon = (u8*)self + (s32)b * sizeof(PCBoxBox);
#else
        pokemon = (u8*)pcboxBoxPtr(self, b);
#endif
        while (index < 30) {
            Pokemon* rec;
            if (b < 0 || b >= PC_PCBOX_COUNT()) {
                rec = 0;
            } else if (index < 0 || index >= 30) {
                rec = 0;
            } else {
                rec = (Pokemon*)(pokemon + 0x14);
            }
            if (rec != 0 && pokemonCheckValid(rec)) {
                count++;
            }
            pokemon += sizeof(Pokemon);
            index++;
        }
    }
    s8 ret = -1;
    if (count >= 0) {
        ret = 30 - count;
    }
    return ret;
}

bool PCBOX::isPokemonFull() {
    for (int i = 0; i < PC_PCBOX_COUNT(); i++) {
        if (nbEmptyImpl(getPointer(), i) != 0) {
            return false;
        }
    }
    return true;
}

s8 PCBOX::getPokemonBoxNbEmptySlot(s8 b) {
    return nbEmptyImpl(this, b);
}

s8 PCBOX::getPokemonBoxNbUsedSlot(s8 b) {
    s8 index;
    s8 count = 0;
    u8* pokemon;
    PCBOX* self = this;
    if (!self) {
        self = getPointer();
    }
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        count = -1;
    }
#ifndef __MWERKS__
    else if (pcboxBoxPtr(self, b) == 0) {
        count = -1;
    }
#endif
    else {
        index = 0;
#ifdef __MWERKS__
        pokemon = (u8*)self + (s32)b * sizeof(PCBoxBox);
#else
        pokemon = (u8*)pcboxBoxPtr(self, b);
#endif
        while (index < 30) {
            Pokemon* rec;
            if (b < 0 || b >= PC_PCBOX_COUNT()) {
                rec = 0;
            } else if (index < 0 || index >= 30) {
                rec = 0;
            } else {
                rec = (Pokemon*)(pokemon + 0x14);
            }
            if (rec != 0 && pokemonCheckValid(rec)) {
                count++;
            }
            pokemon += sizeof(Pokemon);
            index++;
        }
    }
    return count;
}

void* PCBOX::getPokemonBoxName(s8 b) {
    PCBOX* self = this;
    if (!self) {
        self = getPointer();
    }
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        return 0;
    }
#ifdef __MWERKS__
    return &self->box[b];
#else
    return pcboxBoxPtr(self, b);
#endif
}

inline s32 PCBOX::delPokemonImpl(s8 b, s8 i) {
    PCBOX* base = this;
    if (base == 0) {
        base = PCBOX::getPointer();
    }
    Pokemon* p = PCBOX::getRecord(base, b, i);
    if (p == 0) {
        return 0;
    }
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    pokemonInit(p);
    return 1;
}

bool PCBOX::delPokemon(s8 b, s8 i) {
    return (bool)delPokemonImpl(b, i);
}

bool PCBOX::addPokemonLastWatchBox(Pokemon* p) {
    return addPokemon(p, -1);
}

extern "C" s32 pcboxAddPokemon(PCBOX*, Pokemon*, s8);

bool PCBOX::addPokemon(Pokemon* p, s8 b) {
    return pcboxAddPokemon(this, p, b) != 0;
}

bool PCBOX::setPokemon(Pokemon* src, s8 b, s8 i) {
    return (bool)setPokemonImpl(src, b, i);
}

Pokemon* PCBOX::getPokemon(s8 b, s8 i) {
    PCBOX* self = this;
    if (!self) {
        self = getPointer();
    }
    return getRecord(self, b, i);
}

void PCBOX::init() {
    PCBoxBox* cur;
    int i;
    PCBOX* self;
    self = this;
    if (this == 0) {
        self = getPointer();
    }
    i = 0;
    cur = self->box;
    do {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(cur->name, 9, 0x3b39);
        pokemonInitAry(cur->pokemon, 30);
        i++;
        cur++;
    } while (i < 8);
    itemInitAry(self->item, 235);
    self->lastViewBox = 0;
}

extern "C" {

static inline void* pcboxItemSlot(PCBOX* base, s16 idx) {
    if (idx < 0 || idx >= 235) {
        return 0;
    }
    return &base->item[idx];
}

s32 pcboxSwapItemSlot(PCBOX* base, s16 a, s16 b) {
    PCBOX* p = base;
    if (!p) {
        p = PCBOX::getPointer();
    }
    void* i1 = pcboxItemSlot(p, a);
    if (i1 == 0) {
        return 0;
    }
    p = base;
    if (!p) {
        p = PCBOX::getPointer();
    }
    void* i2 = pcboxItemSlot(p, b);
    if (i2 == 0) {
        return 0;
    }
    itemReplace(i1, i2);
    return 1;
}

static inline PCBOX* pcboxGetSaveStatus(PCBOX* base) {
    if (base == 0) {
        base = PCBOX::getPointer();
    }
    return base;
}

static inline s16 pcboxFindItem(PCBOX* status, u16 id) {
    int i;
    for (i = 0; i < 235; i++) {
        if (itemCheckValid(&status->item[i])) {
            if (itemGetStatus(&status->item[i], 0, 0x1b, 0) == id) {
                break;
            }
        }
    }
    if (i < 235) {
        return i;
    }
    return -1;
}

u16 pcboxGetItemCapacity(PCBOX* base, u16 id) {
    PCBOX* status = pcboxGetSaveStatus(base);
    if (!itemDataBiosGetPtr(id)) {
        return 0;
    }
    s16 idx = pcboxFindItem(status, id);
    u16 num;
    if (idx >= 0) {
        void* it = pcboxItemSlot(status, idx);
        if (it == 0) {
            num = 0xFFFF;
        } else if (!itemCheckValid(it)) {
            num = 0xFFFF;
        } else {
            num = itemGetStatus(it, 0, 0x1c, 0);
        }
        if (num > 999) {
            num = 0;
        }
    } else {
        num = 0;
    }
    return 999 - num;
}

u16 pcboxDelItem(PCBOX* base, u16 id, u16 num) {
    PCBOX* status = pcboxGetSaveStatus(base);
    if (num == 0) {
        return num;
    }
    if (!itemDataBiosGetPtr(id)) {
        return num;
    }
    s16 idx = pcboxFindItem(status, id);
    if (idx < 0) {
        return num;
    }
    return itemDecItemDataIdAry(status->item, 235, id, num, idx, 999, 0);
}

u16 pcboxAddItem(PCBOX* base, u16 id, u16 num) {
    PCBOX* status = pcboxGetSaveStatus(base);
    if (num == 0) {
        return num;
    }
    if (!itemDataBiosGetPtr(id)) {
        return num;
    }
    s16 idx = pcboxFindItem(status, id);
    return itemAddItemDataIdAry(status->item, 235, id, num, idx, 999, 0, 0);
}

void* pcboxGetItem(PCBOX* base, s16 idx) {
    PCBOX* status = pcboxGetSaveStatus(base);
    return pcboxItemSlot(status, idx);
}

u16 pcboxGetNbItemSlot() {
    return 235;
}

s8 pcboxGetNbPokemonBox() {
#ifdef __MWERKS__
    return 8;
#else
    return (s8)pcboxCount();
#endif
}

s8 pcboxGetPokemonBoxNbEmptySlot(PCBOX* base, s8 b) {
    s8 index;
    s8 count = 0;
    u8* pokemon;
    if (!base) {
        base = PCBOX::getPointer();
    }
    PCBOX* self = base;
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        count = -1;
    }
#ifndef __MWERKS__
    else if (pcboxBoxPtr(self, b) == 0) {
        count = -1;
    }
#endif
    else {
        index = 0;
#ifdef __MWERKS__
        pokemon = (u8*)self + (s32)b * sizeof(PCBoxBox);
#else
        pokemon = (u8*)pcboxBoxPtr(self, b);
#endif
        while (index < 30) {
            Pokemon* rec;
            if (b < 0 || b >= PC_PCBOX_COUNT()) {
                rec = 0;
            } else if (index < 0 || index >= 30) {
                rec = 0;
            } else {
                rec = (Pokemon*)(pokemon + 0x14);
            }
            if (rec != 0 && pokemonCheckValid(rec)) {
                count++;
            }
            pokemon += sizeof(Pokemon);
            index++;
        }
    }
    if (count < 0) {
        return -1;
    }
    return 30 - count;
}

s32 pcboxSetPokemonBoxName(PCBOX* base, s8 b, u16* name) {
    if (!base) {
        base = PCBOX::getPointer();
    }
    PCBOX* self = base;
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        return 0;
    }
    if (name == 0) {
        return 0;
    }
    int len;
    u16* p;
    p = name;
    len = 0;
    while (*p != 0) {
        p++;
        len++;
    }
    if (len > 8) {
        return 0;
    }
#ifdef __MWERKS__
    GScharCpy(self->box[b].name, name);
#else
    PCBoxBox* bx = pcboxBoxPtr(self, b);
    if (bx == 0) {
        return 0;
    }
    GScharCpy(bx->name, name);
#endif
    return 1;
}

void* pcboxGetPokemonBoxName(PCBOX* base, s8 b) {
    if (!base) {
        base = PCBOX::getPointer();
    }
    PCBOX* self = base;
    if (b < 0 || b >= PC_PCBOX_COUNT()) {
        return 0;
    }
#ifdef __MWERKS__
    return &self->box[b];
#else
    return pcboxBoxPtr(self, b);
#endif
}

static inline s8 findEmptySlot(PCBOX* base, s8 b) {
    int j;
    for (j = 0; j < 30; j++) {
        Pokemon* p = PCBOX::getRecord(base, b, j);
        if (p != 0 && !pokemonCheckValid(p)) {
            break;
        }
    }
    s8 r = -1;
    if (j < 30) {
        r = j;
    }
    return r;
}

s32 pcboxAddPokemon(PCBOX* base, Pokemon* src, s8 box) {
    PCBOX* self = base;
    s8 idx;
    bool found;
    if (base == 0) {
        self = PCBOX::getPointer();
    }
    if (box < -1 || box >= PC_PCBOX_COUNT()) {
        return 0;
    }
    if (src == 0) {
        return 0;
    }
    if (box == -1) {
        found = false;
        box = menuPcBoxGetLastViewBox();
        for (; box < PC_PCBOX_COUNT(); box++) {
            idx = findEmptySlot(self, box);
            if (idx >= 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            for (box = 0; box < menuPcBoxGetLastViewBox(); box++) {
                idx = findEmptySlot(self, box);
                if (idx >= 0) {
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return 0;
        }
    } else {
        idx = findEmptySlot(self, box);
        if (idx < 0) {
            return 0;
        }
    }
    if (self == 0) {
        self = PCBOX::getPointer();
    }
    Pokemon* rec = PCBOX::getRecord(self, box, idx);
    if (rec == 0) {
        return 0;
    }
    memcpy(rec, src, sizeof(Pokemon));
    pokemonAllKaihuku(rec);
    DarkPokemon* dark = rec->getDarkPokemon();
    if (dark) {
        dark->setPlace(place2, box);
    }
    return 1;
}

void pcboxInit(PCBOX* base) {
    PCBOX* self;
    int i;
    PCBoxBox* cur;
    self = base;
    if (base == 0) {
        self = PCBOX::getPointer();
    }
    i = 0;
    cur = self->box;
    do {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(cur->name, 9, 0x3b39);
        pokemonInitAry(cur->pokemon, 30);
        i++;
        cur++;
    } while (i < 8);
    itemInitAry(self->item, 235);
    self->lastViewBox = 0;
}

void pcboxSetStatus() {
}

s32 pcboxGetStatus() {
    return 0;
}

}
