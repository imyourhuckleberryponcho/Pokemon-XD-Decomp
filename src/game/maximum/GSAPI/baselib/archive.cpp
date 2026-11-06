#include <dolphin/types.h>
#include <dolphin/os.h>
#include <game/hsdarchive.h>
#ifndef __MWERKS__
#include <string.h>
#endif

#pragma pool_strings off

int strcmp(const char* a, const char* b);

static inline void Locate(HSD_Archive* archive) {
    u32 i;
    gc_be32* ptr;

    for (i = 0; i < GC_BE32(archive->header.nb_reloc); i++) {
        ptr = (gc_be32*)(archive->data + GC_BE32(archive->reloc_info[i]));
        GC_ADDBE32(*ptr, GC_ADDR32(archive->data));
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
    if (GC_BE32(archive->header.file_size) != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data format\n");
        return -1;
    }
    offset = sizeof(HSD_ArchiveHeader);
    if (GC_BE32(archive->header.data_size) != 0) {
        archive->data = src + offset;
        offset += GC_BE32(archive->header.data_size);
    }
    if (GC_BE32(archive->header.nb_reloc) != 0) {
        archive->reloc_info = (gc_be32*)(src + offset);
        offset += GC_BE32(archive->header.nb_reloc) * 4;
    }
    if (GC_BE32(archive->header.nb_public) != 0) {
        archive->public_info = (HSD_ArchivePublicInfo*)(src + offset);
        offset += GC_BE32(archive->header.nb_public) * sizeof(HSD_ArchivePublicInfo);
    }
    if (GC_BE32(archive->header.nb_extern) != 0) {
        archive->extern_info = (HSD_ArchiveExternInfo*)(src + offset);
        offset += GC_BE32(archive->header.nb_extern) * sizeof(HSD_ArchiveExternInfo);
    }
    if (offset < GC_BE32(archive->header.file_size)) {
        archive->symbols = (char*)(src + offset);
    }
    archive->top_ptr = src;
    Locate(archive);
    return 0;
}

void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbol) {
    u32 i;
    for (i = 0; i < GC_BE32(archive->header.nb_public); i++) {
        if (strcmp(archive->symbols + GC_BE32(archive->public_info[i].symbol), symbol) == 0) {
            return archive->data + GC_BE32(archive->public_info[i].offset);
        }
    }
    return NULL;
}
