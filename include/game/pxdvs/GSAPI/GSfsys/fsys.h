#ifndef GAME_FSYS_H
#define GAME_FSYS_H

#include <dolphin/types.h>
#include <game/gcdata.h>
#include <dolphin/arq.h>

struct GSdvdFile;
struct FsysHeader;

struct FsysGroup {
    gc_be32 id;
    gc_ptr32(char) name;
    gc_be32 headerSize;
    gc_be32 flags;
};

struct FsysWork {
    u32 id;
    u32 unk4;
    u32 unk8;
    u32 file;
    s32 mode;
    s32 status;
    s32 pending;
    FsysGroup* group;
    FsysHeader* header;
    u32 unk24;
    u32 unk28;
    u8 cancel;
    s8 cacheType;
    u8 headerValid;
    u8 pad2F;
    void (*callback)(u32, u32, u32);
    u32 cbArg0;
    u32 cbArg1;
    u32 groupId;
};

struct FsysBlock {
    FsysBlock* prev;
    FsysBlock* next;
    u8* data;
    u32 unkC;
};

typedef gc_ptr32(FsysBlock) FsysBlockSlot;

struct FsysHeader {
    gc_be32 unk0[3];
    gc_be32 resNum;
    gc_be32 flags;
    gc_be32 unk14;
    gc_be32 unk18;
    gc_be32 headerSize;
    gc_be32 unk20[8];
    gc_be32 offsetTable;
};

struct FsysResHeader {
    gc_be32 id;
    gc_be32 unk4;
    gc_be32 size8;
    gc_be32 flags;
    gc_be32 unk10;
    gc_be32 size14;
    gc_ptr32(void) data;
    gc_be32 unk1C;
    gc_be32 type;
    gc_be32 unk24;
    gc_be32 pos;
    gc_ptr32(u8) cache;
    FsysBlockSlot blockA;
    FsysBlockSlot blockB;
    gc_ptr32(GSdvdFile) dvdFile;
    gc_be32 unk3C;
    gc_bes32 pending;
    gc_be32 remaining;
    gc_be32 unk48;
    gc_be32 readBlocks;
    gc_be32 loopPoint;
    gc_be32 loopEnd;
};

typedef FsysWork Fsys;

struct FsysCacheManage {
    FsysCacheManage* prev;
    FsysCacheManage* next;
    u8 used;
    u8 type;
    u8 locked;
    u8 pad0B;
    void* addr;
    u32 size;
    u32 prio;
    u32 uniqueID;
    u32 group;
    u32 id;
};

struct FsysReadRequest {
    u8 unk0[0x10];
    void* data;
};
typedef void (*FsysStreamCallback)(void* data, u32 arg0, u32 arg1);
#ifdef __MWERKS__
#define FSYS_U32_TO_PTR(T, v) ((T)(v))
#else
#define FSYS_U32_TO_PTR(T, v) ((T)(uintptr_t)(v))
#endif

struct FsysArqTrans {
    FsysArqTrans* prev;
    FsysArqTrans* next;
    u8 used;
    u8 pad9[3];
    ARQRequest request;
    void (*callback)(u32);
    Fsys* fsys;
    FsysResHeader* res;
    u32 arg0;

    u32 arg1;
    u32 arg2;
    void* dst;
    u32 size;
};

struct FsysBG {
    FsysBG* prev;
    FsysBG* next;
    u8 used;
    u8 done;
    u8 type;
    u8 started;
    FsysWork* work;
    FsysResHeader* res;
    u8 hdr[4];
    u32 outSize;
    u32 inSize;
    u32 limit;
    u8* window;
    u32 off;
    u32 wpos;
    u32 flags;
    u32 count;
    u32 pos;
    u32 dpos;
    s32 state;
};

#endif
