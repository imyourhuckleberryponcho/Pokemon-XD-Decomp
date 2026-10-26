#include <dolphin/types.h>
#include <dolphin/os.h>

#pragma pool_strings off

typedef struct HSD_ArchiveHeader {
    u32 file_size;
    u32 data_size;
    u32 nb_reloc;
    u32 nb_public;
    u32 nb_extern;
    u8 version[4];
    u32 pad[2];
} HSD_ArchiveHeader;

typedef struct HSD_ArchivePublicInfo {
    u32 offset;
    u32 symbol;
} HSD_ArchivePublicInfo;

typedef struct HSD_ArchiveExternInfo {
    u32 offset;
    u32 symbol;
} HSD_ArchiveExternInfo;

typedef struct HSD_Archive {
    HSD_ArchiveHeader header;
    u8* data;
    u32* reloc_info;
    HSD_ArchivePublicInfo* public_info;
    HSD_ArchiveExternInfo* extern_info;
    char* symbols;
    struct HSD_Archive* next;
    char* name;
    u32 flags;
    void* top_ptr;
} HSD_Archive;

int strcmp(const char* a, const char* b);

static inline void Locate(HSD_Archive* archive) {
    u32 i;
    u32* ptr;

    for (i = 0; i < archive->header.nb_reloc; i++) {
        ptr = (u32*)(archive->data + archive->reloc_info[i]);
        *ptr += (u32)archive->data;
    }
}

s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 file_size) {
    u32 offset;

    if (archive == NULL) {
        return -1;
    }
    memset(archive, 0, sizeof(HSD_Archive));
    archive->flags |= 1;
    memcpy(&archive->header, src, sizeof(HSD_ArchiveHeader));
    if (archive->header.file_size != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data format\n");
        return -1;
    }
    offset = sizeof(HSD_ArchiveHeader);
    if (archive->header.data_size != 0) {
        archive->data = src + offset;
        offset += archive->header.data_size;
    }
    if (archive->header.nb_reloc != 0) {
        archive->reloc_info = (u32*)(src + offset);
        offset += archive->header.nb_reloc * 4;
    }
    if (archive->header.nb_public != 0) {
        archive->public_info = (HSD_ArchivePublicInfo*)(src + offset);
        offset += archive->header.nb_public * sizeof(HSD_ArchivePublicInfo);
    }
    if (archive->header.nb_extern != 0) {
        archive->extern_info = (HSD_ArchiveExternInfo*)(src + offset);
        offset += archive->header.nb_extern * sizeof(HSD_ArchiveExternInfo);
    }
    if (offset < archive->header.file_size) {
        archive->symbols = (char*)(src + offset);
    }
    archive->top_ptr = src;
    Locate(archive);
    return 0;
}

void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbol) {
    u32 i;
    for (i = 0; i < archive->header.nb_public; i++) {
        if (strcmp(archive->symbols + archive->public_info[i].symbol, symbol) == 0) {
            return archive->data + archive->public_info[i].offset;
        }
    }
    return NULL;
}
