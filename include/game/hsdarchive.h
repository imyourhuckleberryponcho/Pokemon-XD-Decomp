#ifndef GAME_HSDARCHIVE_H
#define GAME_HSDARCHIVE_H

#include <dolphin/types.h>
#include <game/gcdata.h>

typedef struct HSD_ArchiveHeader {
    gc_be32 file_size;
    gc_be32 data_size;
    gc_be32 nb_reloc;
    gc_be32 nb_public;
    gc_be32 nb_extern;
    u8 version[4];
    gc_be32 pad[2];
} HSD_ArchiveHeader;

typedef struct HSD_ArchivePublicInfo {
    gc_be32 offset;
    gc_be32 symbol;
} HSD_ArchivePublicInfo;

typedef struct HSD_ArchiveExternInfo {
    gc_be32 offset;
    gc_be32 symbol;
} HSD_ArchiveExternInfo;

typedef struct HSD_Archive {
    HSD_ArchiveHeader header;
    u8* data;
    gc_be32* reloc_info;
    HSD_ArchivePublicInfo* public_info;
    HSD_ArchiveExternInfo* extern_info;
    char* symbols;
    struct HSD_Archive* next;
    char* name;
    u32 flags;
    void* top_ptr;
} HSD_Archive;

#ifdef __MWERKS__
#define HSD_ARCHIVE_SIZE 0x44
#else
#define HSD_ARCHIVE_SIZE sizeof(HSD_Archive)
#endif

#endif
