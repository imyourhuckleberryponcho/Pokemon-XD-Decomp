// Compiled as C with deferred inlining (see configure.py), which emits functions and data in
// reverse source order.
#include <dolphin/types.h>

#pragma pool_strings off

void __assert(const char* file, s32 line, const char* expr);

typedef struct HSD_ObjAllocData {
    u8 unk0[0x2C];
} HSD_ObjAllocData;

typedef struct IDEntry {
    struct IDEntry* next;
    u32 id;
    void* data;
} IDEntry;

typedef struct HSD_IDTable {
    IDEntry* table[101];
} HSD_IDTable;

void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* obj);
void HSD_ObjAllocInit(HSD_ObjAllocData* data, u32 size, u32 align);

static HSD_ObjAllocData alloc_data;
static HSD_IDTable default_table;

HSD_ObjAllocData* HSD_IDGetAllocData(void) { return &alloc_data; }

void HSD_IDInitAllocData(void) { HSD_ObjAllocInit(&alloc_data, sizeof(IDEntry), 4); }

void HSD_IDSetup(void) { memset(&default_table, 0, sizeof(HSD_IDTable)); }

void HSD_IDInsertToTable(HSD_IDTable* table, u32 id, void* data) {
    IDEntry* entry;
    IDEntry* new_entry;
    u32 hash;

    if (table == NULL) {
        table = &default_table;
    }
    hash = id % 101;
    for (entry = table->table[hash]; entry != NULL; entry = entry->next) {
        if (entry->id == id) {
            break;
        }
    }
    if (entry != NULL) {
        entry->id = id;
        entry->data = data;
    } else {
        new_entry = (IDEntry*)HSD_ObjAlloc(&alloc_data);
        if (new_entry == NULL) {
            __assert("id.c", 67, "entry");
        }
        memset(new_entry, 0, sizeof(IDEntry));
        new_entry->id = id;
        new_entry->data = data;
        new_entry->next = table->table[hash];
        table->table[hash] = new_entry;
    }
}

void HSD_IDRemoveByIDFromTable(HSD_IDTable* table, u32 id) {
    IDEntry* entry;
    IDEntry* prev;
    u32 hash;

    if (table == NULL) {
        table = &default_table;
    }
    prev = NULL;
    hash = id % 101;
    for (entry = table->table[hash]; entry != NULL; entry = entry->next) {
        if (entry->id == id) {
            if (prev != NULL) {
                prev->next = entry->next;
            } else {
                table->table[hash] = entry->next;
            }
            HSD_ObjFree(&alloc_data, entry);
            return;
        }
        prev = entry;
    }
}

void* HSD_IDGetDataFromTable(HSD_IDTable* table, u32 id, s32* success) {
    IDEntry* entry;

    if (table == NULL) {
        table = &default_table;
    }
    for (entry = table->table[id % 101]; entry != NULL; entry = entry->next) {
        if (entry->id == id) {
            if (success != NULL) {
                *success = 1;
            }
            return entry->data;
        }
    }
    if (success != NULL) {
        *success = 0;
    }
    return NULL;
}

void _HSD_IDForgetMemory(void) { memset(&default_table, 0, sizeof(HSD_IDTable)); }
