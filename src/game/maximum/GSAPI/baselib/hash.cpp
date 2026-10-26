
#include <dolphin/types.h>

#pragma pool_strings off

void __assert(const char* file, s32 line, const char* expr);

typedef struct HSD_HashEntry {
    struct HSD_HashEntry* next;
    void* key;
    void* value;
} HSD_HashEntry;

struct HSD_Hash;

typedef struct HSD_HashInfo {
    u8 parent[0x3C];
    u32 (*hash)(struct HSD_Hash* hash, void* key);
    s32 (*compare)(struct HSD_Hash* hash, void* key0, void* key1);
} HSD_HashInfo;

typedef struct HSD_Hash {
    HSD_HashInfo* class_info;
    HSD_HashEntry** table;
    u32 table_size;
} HSD_Hash;

static inline HSD_HashEntry* HashSearchEntry(HSD_Hash* hash, void* key) {
    HSD_HashEntry* entry;
    u32 idx = hash->class_info->hash(hash, key);
    if (!(idx < hash->table_size)) {
        __assert("hash.c", 113, "idx < hash->table_size");
    }
    entry = hash->table[idx];
    if (entry == NULL) {
        return NULL;
    }
    for (; entry != NULL; entry = entry->next) {
        if (hash->class_info->compare(hash, entry->key, key) == 0) {
            return entry;
        }
    }
    return NULL;
}

void* HSD_HashSearch(HSD_Hash* hash, void* key, s32* found) {
    HSD_HashEntry* entry = HashSearchEntry(hash, key);
    if (found != NULL) {
        *found = entry != NULL;
    }
    return entry != NULL ? entry->value : NULL;
}
