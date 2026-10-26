#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
    void clear() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

class NullSequence {
public:
    virtual ~NullSequence();
    virtual void Update(f32 dt);
    virtual void GetPosition(GSvec* pos);
    virtual void GetRotation(GSvec* rot);
    virtual void GetScale(GSvec* scale);
    virtual void SetPosition(GSvec* pos);
    virtual void SetRotation(GSvec* rot);
    virtual void SetScale(GSvec* scale);
    virtual void SetVisibility(bool visible);

    u16 m_unk4;
    bool m_visible;
    u8 m_unk7;
    s32 m_kind;
};

class ModelSequence : public NullSequence {
public:
    u8 unkC[0x50 - 0xC];
    s8 modelSize;
    u8 unk51[4];
    u8 facing;
    u8 hasParent;
    u8 unk57[0x78 - 0x57];
    ModelSequence* child;
    ModelSequence* parent;

    void LinkTo(ModelSequence* p) {
        if (parent != 0) {
            parent->child = 0;
        }
        parent = hasParent ? p : 0;
    }
};

static inline ModelSequence* AsM(NullSequence* seq) {
    ModelSequence* r;
    if (seq->m_kind == 1) {
        r = (ModelSequence*)seq;
    } else {
        r = 0;
    }
    return r;
}
static inline ModelSequence* ToModelInPlace(ModelSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    seq = seq->m_kind == 1 ? seq : 0;
    return seq;
}

static inline ModelSequence* ToModel(NullSequence* seq) {
    if (seq == 0) {
        return 0;
    }
    return AsM(seq);
}

struct BattleGridEntry {
    ModelSequence* slot;
    ModelSequence* pokemon[2];
    u16 count;
    u8 arg1;
    u8 arg2;
};

struct BattleGrid {
    BattleGridEntry entries[4];
    u16 count;
    u16 pokemonCount;
};

struct BattleGridFull : BattleGrid {
    bool saved[12];
    bool backup[12];
};

extern "C" {
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
void GSlogWrite(const char*, ...);
void Sequence_CopyState(NullSequence*, NullSequence*);
void wazaSequenceSysGetActiveWazaNum(void);
}

BattleGrid gBattleGrid;
static bool gSavedVisibilityCodes[12];
static bool gBackupVisibilityCodes[12];
static s32 g_max_model_size;
static u8 gVisibilityChanged;
static u8 gVisibilityBackedUp;

extern "C" {

BattleGrid* battleGridGetPtr(void) {
    return &gBattleGrid;
}

u16 battleGridGetNumPokemonsForTrainer(NullSequence* seq) {
    BattleGridEntry* g = gBattleGrid.entries;
    ModelSequence* trainer = ToModel(seq);
    u16 i;
    if (trainer == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++, g++) {
        if (g->slot == trainer) {
            return g->count;
        }
    }
    return 0;
}

void battleGridRestoreModelVisibilityFlags(void) {
    bool* backup;
    BattleGridFull* grid = (BattleGridFull*)&gBattleGrid;
    BattleGridEntry* g = grid->entries;
    u16 i;
    u16 j;
    u16 idx = 0;
    if (gVisibilityBackedUp) {
        backup = grid->backup;
        for (i = 0; i < 4; i++, g++) {
            if (g->slot != 0) {
                g->slot->NullSequence::SetVisibility(grid->backup[idx]);
            }
            idx++;
            for (j = 0; j < 2; idx++, j++) {
                if (g->pokemon[j] != 0) {
                    g->pokemon[j]->NullSequence::SetVisibility(backup[idx]);
                }
            }
        }
        gVisibilityBackedUp = 0;
        memcpy(grid->saved, grid->backup, 12);
    }
}

void battleGridBackupModelVisibilityFlags(void) {
    BattleGridEntry* g = gBattleGrid.entries;
    u16 idx = 0;
    u16 i;
    u16 j;
    memset(gBackupVisibilityCodes, 0, 12);
    for (i = 0; i < 4; i++, g++) {
        if (g->slot != 0) {
            gBackupVisibilityCodes[idx] = g->slot->m_visible;
        }
        idx++;
        for (j = 0; j < 2; idx++, j++) {
            if (g->pokemon[j] != 0) {
                gBackupVisibilityCodes[idx] = g->pokemon[j]->m_visible;
            }
        }
    }
    gVisibilityBackedUp = 1;
}

void battleGridResetModelVisibilityFlags(void) {
    BattleGridEntry* g = gBattleGrid.entries;
    u16 i;
    u16 j;
    u16 idx = 0;
    if (gVisibilityChanged) {
        for (i = 0; i < 4; i++, g++) {
            if (g->slot != 0) {
                g->slot->NullSequence::SetVisibility(gSavedVisibilityCodes[idx]);
            }
            idx++;
            for (j = 0; j < 2; idx++, j++) {
                if (g->pokemon[j] != 0) {
                    g->pokemon[j]->NullSequence::SetVisibility(gSavedVisibilityCodes[idx]);
                }
            }
        }
        gVisibilityChanged = 0;
    }
}

void battleGridStoreModelVisibilityFlags(void) {
    BattleGridEntry* g = gBattleGrid.entries;
    u16 idx = 0;
    u16 i;
    u16 j;
    memset(gSavedVisibilityCodes, 0, 12);
    for (i = 0; i < 4; i++, g++) {
        if (g->slot != 0) {
            gSavedVisibilityCodes[idx] = g->slot->m_visible;
        }
        idx++;
        for (j = 0; j < 2; idx++, j++) {
            if (g->pokemon[j] != 0) {
                gSavedVisibilityCodes[idx] = g->pokemon[j]->m_visible;
            }
        }
    }
    gVisibilityChanged = 1;
}

void battleGridHideModelsExcept(NullSequence* seq) {
    BattleGridEntry* g = gBattleGrid.entries;
    u16 idx = 0;
    u16 i;
    u16 j;
    g = gBattleGrid.entries;
    ModelSequence* except = ToModel(seq);
    battleGridResetModelVisibilityFlags();
    memset(gSavedVisibilityCodes, 0, 12);
    for (i = 0; i < 4; i++, g++) {
        if (g->slot != 0) {
            gSavedVisibilityCodes[idx] = g->slot->m_visible;
            if (g->slot != except) {
                g->slot->SetVisibility(false);
            }
        }
        idx++;
        for (j = 0; j < 2; idx++, j++) {
            if (g->pokemon[j] != 0) {
                gSavedVisibilityCodes[idx] = g->pokemon[j]->m_visible;
                if (g->pokemon[j] != except) {
                    g->pokemon[j]->SetVisibility(false);
                }
            }
        }
    }
    gVisibilityChanged = 1;
}

void battleGridReset(void) {
    memset(&gBattleGrid, 0, 0x44);
    g_max_model_size = 0;
    gVisibilityChanged = 0;
}

static inline f32 GetBaseDistance() {
    f32 distance;
    switch (g_max_model_size) {
    case -2:
    case -1:
        distance = 0.875f;
        break;
    case 1:
        distance = 1.4f;
        break;
    case 2:
        distance = 1.8f;
        break;
    case 3:
        distance = 2.4f;
        break;
    default:
        distance = 1.0f;
        break;
    }
    return distance;
}

static inline void PlaceModel(ModelSequence* m, GSvec* pos, GSvec* rot, u8 mirrored) {
    if (m != 0) {
        m->SetPosition(pos);
        m->SetRotation(rot);
        m->facing = mirrored;
    }
}

void battleGridUpdate(void) {
    enum TsE { TsE0 };
    u16 i;
    enum TsE count = (enum TsE)(gBattleGrid.count);
    BattleGridEntry* g = gBattleGrid.entries;
    wazaSequenceSysGetActiveWazaNum();
    if (count != 0) {
        f32 distance;
        f32 negDistance;
        f32 slotXMirror;
        f32 modelXMirror;
        f32 slotX;
        f32 modelX;
        f32 depthScale;
        f32 soloOffset;
        f32 pairOffset;
        GSvec pos;
        GSvec rot;
        GSvec slotPos;
        GSvec pairPos;
        s16 b;
        BattleGridEntry* e;
        bool found;
        u16 a;

        found = false;
        e = gBattleGrid.entries;
        g_max_model_size = -2;
        for (a = 0; a < 4; a++, e++) {
            if (e->slot != 0) {
                for (b = 0; b < 2; b++) {
                    ModelSequence* m = e->pokemon[b];
                    if (m != 0) {
                        s32 size = m->modelSize;
                        found = true;
                        if (size > g_max_model_size) {
                            g_max_model_size = size;
                        }
                    }
                }
            }
        }
        if (!found) {
            g_max_model_size = 0;
        }
        distance = GetBaseDistance();

        slotPos.clear();
        pos.clear();
        rot.clear();

        negDistance = -distance;
        slotXMirror = 65.0f * negDistance;
        modelXMirror = 40.0f * negDistance;
        slotX = 65.0f * distance;
        modelX = 40.0f * distance;
        depthScale = -30.0f * distance;
        soloOffset = -12.5f * distance;
        pairOffset = 30.0f * distance;

        for (i = 0; i < 4; i++, g++) {
            if (g->slot != 0) {
                f32 depth;
                g->slot->LinkTo(0);
                if (g->arg1 != 0) {
                    slotPos.x = slotXMirror;
                    pos.x = modelXMirror;
                    rot.y = 1.5707964f;
                } else {
                    slotPos.x = slotX;
                    pos.x = modelX;
                    rot.y = -1.5707964f;
                }
                depth = depthScale * (f32)(s8)g->arg2;
                slotPos.z = depth;
                pos.z = depth;
                switch (g->count) {
                case 0:
                    break;
                case 1:
                    slotPos.z = depth + soloOffset;
                    if (g->pokemon[0] != 0) {
                        g->pokemon[0]->LinkTo(g->slot);
                        PlaceModel(g->pokemon[0], &pos, &rot, g->arg1);
                    } else {
                        g->pokemon[1]->LinkTo(g->slot);
                        PlaceModel(g->pokemon[1], &pos, &rot, g->arg1);
                    }
                    break;
                case 2:
                    pairPos = pos;
                    g->pokemon[0]->LinkTo(g->slot);
                    g->pokemon[1]->LinkTo(g->slot);
                    if (g->arg1 != 0) {
                        pairPos.z = pos.z - pairOffset;
                        PlaceModel(g->pokemon[0], &pairPos, &rot, g->arg1);
                        pairPos.z = pos.z + pairOffset;
                        PlaceModel(g->pokemon[1], &pairPos, &rot, g->arg1);
                    } else {
                        pairPos.z = pos.z - pairOffset;
                        PlaceModel(g->pokemon[1], &pairPos, &rot, g->arg1);
                        pairPos.z = pos.z + pairOffset;
                        PlaceModel(g->pokemon[0], &pairPos, &rot, g->arg1);
                    }
                    break;
                }
                PlaceModel(g->slot, &slotPos, &rot, g->arg1);
                g->slot->NullSequence::SetVisibility(true);
            }
        }
    }
}

f32 battleGridGetUnscaledDistance(bool side) {
    if (side) {
        return 40.0f;
    }
    return 65.0f;
}

f32 battleGridGetDistance(bool side) {
    f32 distance = GetBaseDistance();
    if (side) {
        return 40.0f * distance;
    }
    return 65.0f * distance;
}

void battleGridGetNormalisedScale(GSvec* scale) {
    f32 v = GetBaseDistance();
    f32 ratio = 65.0f / 38.0f;
    v = v * ratio;
    scale->x = v;
    scale->y = v;
    scale->z = v;
}

void battleGridRemovePokemon(NullSequence* seq) {
    BattleGridEntry* g = gBattleGrid.entries;
    ModelSequence* pokemon = ToModel(seq);
    u16 i;
    u16 j;
    if (pokemon != 0) {
        for (i = 0; i < 4; i++, g++) {
            for (j = 0; j < 2; j++) {
                if (g->pokemon[j] == pokemon) {
                    g->pokemon[j] = 0;
                    g->count--;
                    gBattleGrid.pokemonCount--;
                    pokemon->SetVisibility(false);
                    pokemon->facing = 0;
                    pokemon->LinkTo(0);
                    return;
                }
            }
        }
    }
}

void battleGridReplacePokemon(NullSequence* oldSeq, NullSequence* newSeq) {
    BattleGridEntry* g = gBattleGrid.entries;
    ModelSequence* oldP = ToModelInPlace((ModelSequence*)oldSeq);
    ModelSequence* newP = ToModel(newSeq);
    u16 i;
    u16 j;
    if (oldP == 0 || newP == 0) {
        GSlogWrite("battleGridReplacePokemon: NULL argument");
        return;
    }
    for (i = 0; i < 4; i++, g++) {
        for (j = 0; j < 2; j++) {
            if (g->pokemon[j] == oldP) {
                oldP->LinkTo(0);
                g->pokemon[j] = newP;
                newP->LinkTo(g->slot);
                oldP->SetVisibility(false);
                newP->facing = oldP->facing;
                oldP->facing = 0;
                Sequence_CopyState(newSeq, oldSeq);
                return;
            }
        }
    }
}

void battleGridAddPokemon(NullSequence* slotSeq, NullSequence* pokemonSeq) {
    BattleGridEntry* g = gBattleGrid.entries;
    ModelSequence* slot = ToModel(slotSeq);
    ModelSequence* pokemon = ToModel(pokemonSeq);
    BattleGrid* grid;
    u16 i;
    u16 j;
    if (slot == 0 || pokemon == 0) {
        return;
    }
    grid = &gBattleGrid;
    if (grid->pokemonCount >= 8) {
        return;
    }
    for (i = 0; i < 4; i++, g++) {
        if (g->slot == slot) {
            if (g->count >= 2) {
                return;
            }
            for (j = 0; j < 2; j++) {
                if (g->pokemon[j] == 0) {
                    g->pokemon[j] = pokemon;
                    pokemon->LinkTo(slot);
                    g->count++;
                    grid->pokemonCount++;
                    pokemon->facing = g->arg1;
                    return;
                }
            }
        }
    }
}

void battleGridAddTrainer(NullSequence* seq, u8 arg1, u8 arg2) {
    ModelSequence* trainer = ToModel(seq);
    BattleGrid* grid;
    BattleGridEntry* e;
    if (trainer != 0) {
        grid = &gBattleGrid;
        if (grid->count < 4) {
            e = grid->entries;
            if (e->slot != 0) {
                e = &grid->entries[1];
                if (e->slot != 0) {
                    e++;
                    if (e->slot != 0) {
                        e++;
                        if (e->slot != 0) {
                            e++;
                        }
                    }
                }
            }
            memset(e, 0, 0x10);
            e->slot = trainer;
            e->arg1 = arg1;
            e->arg2 = arg2;
            trainer->facing = arg1;
            grid->count++;
        }
    }
}

}
