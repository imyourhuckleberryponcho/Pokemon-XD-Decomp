// WIP: written from asm
#include <dolphin/types.h>
#pragma pool_strings off

struct FsysGroup {
    u32 id;
    char* name;
    u32 headerSize;
    u32 flags;
};

struct FsysHeader {
    u8 unk0[0xC];
    u32 resNum;
    u32 flags;
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
    s8 unk2D;
    u8 unk2E;
    u8 pad2F;
    void (*callback)(u32, u32, u32);
    u32 cbArg0;
    u32 cbArg1;
    u32 groupId;
};

struct FsysBlock {
    u8 unk0[8];
    u8* data;
};

struct FsysResHeader {
    u32 id;
    u8 unk4[4];
    u32 size8;
    u32 flags;
    u8 unk10[4];
    u32 size14;
    void* data;
    u8 unk1C[4];
    u32 type;
    u8 unk24[0xC];
    FsysBlock* blockA;
    FsysBlock* blockB;
    u32 id38;
    u32 unk3C;
    s32 pending;
    u32 unk44;
    u8 unk48[4];
    u32 readBlocks;
    u32 loopPoint;
    u32 loopEnd;
};

struct FsysQue {
    FsysQue* prev;
    FsysQue* next;
    s32 type;
    u32 id;
    u32 idx;
    s32 a;
    s32 b;
    s32 c;
    s8 flag;
    u8 started;
};

struct FsysTag {
    FsysTag* prev;
    FsysTag* next;
    u8 used;
};

struct FsysTOC {
    u8 unk0[8];
    u32 count;
    u8 unkC[4];
    u32 groupOffset;
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

struct FsysDataType {
    s32 unk0;
    s32 type;
    void* (*pre)(u32, u32, u32);
    void (*post)(u32, u32, u32);
};

struct OSLinkRes {
    u8 unk0[0x1C];
    u32 unk1C;
    u8 unk20[0x14];
    void (*linkFunc)(void);
    void (*unlinkFunc)(void);
    u8 unk3C[0xC];
    u32 count;
};

extern "C" {

extern u32 _fsysBlockByteSize;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void GSthreadSwitch(void);
void GSdvdInit(void);
s32 GSdvdGetDriveStatus(void);
bool _fsysMemFreeCacheGroup(u32);
void* GSresGetResource(u32, u32);
u32 GSresAllocResourceAlign(u32, u32, u32, u32, void*);
void OSLinkFixed(void*, void*);
void OSUnlink(void*);
void GSmovieStreamPostFunc(u32, u32);
s32 GSmovieStreamPreFunc(void);
void GSsndStreamPostFunc(u32, u32);
s32 GSsndStreamPreFunc(void);
u32 _fsysStreamGetCacheSize(void);
s32 _fsysStreamGetData(FsysWork*, u32, u32, u32, u32, u32, u32, u32);


static FsysWork* _fsysGetWork(u32 id, u8 flag);
FsysResHeader* _fsysGetResHeader(FsysWork* work, u32 index);
FsysHeader* _fsysGetHeader(FsysWork* work);
u32 _fsysID2Index(FsysWork* work, u32 id);
void _fsysMemSet(void* dst, s32 c, u32 size);
static void _fsysFreeStatus(u32 id);
static s32 _fsysOSUnLink(u32, u32, u32);
void GSfsysOSUnLink(u32, u32, u32);
u8 GSfsysReadIDEX(u32 id, u32 idx, s32 a, s32 b, s32 c);
u8 GSfsysReadID(u32 id, u32 idx);
u8 GSfsysCancel(u32 id);
s32 GSfsysGetStatus(u32 id);
u8 GSfsysPreRead(u32 id);
u8 GSfsysRead(u32 id);
s32 GSfsysCancelWait(u32 id);
static s32 _fsysWait(u32 id, u8 flag);
static u8 _fsysPreReadExec(u32 id, s8 keep, s32 a, s32 b, s32 c, s32 prio);
static s32 _fsysReadStreamingExec(u32 id, s32 a, s32 b);
static u8 _fsysRequest(s32 type, u32 id, u32 idx, s8 flag, s32 a, s32 b, s32 c, s32 prio);
static void _fsysQueExec(void);
static u8 _fsysQueExecSub(FsysQue* que);
static void _fsysDelQueManage(FsysQue* que);
static u8 _fsysAddQueManage(FsysQue* que, s32 prio);
static FsysQue* _fsysGetQueManage(u32 id, u32 idx);
static FsysQue* _fsysGetNewQueManage(s32 type, u32 id, u32 idx, s8 flag, s32 a, s32 b, s32 c);
static s32 _fsysExec(u32 id, s32 idx, s32 mode, s8 flag, s32 a, s32 b, s32 c);
static FsysWork* _fsysGetNewWork(void);
static FsysGroup* _fsysGetGROUP(u32 id);
static s32 _fsysOpenFile(FsysWork* work);
static void _fsysOffTOCFlag(u32 id, u32 flag);
s32 _fsysIncCacheUniqueGroupID(void);
u8 GSfsysInit2(s32, s32, s32);
static void _fsysForegroundTask(FsysWork*);
static void _fsysHeaderSizeReadDvdCallback(s32, u32);
static void _fsysOnTOCFlag(u32, u32);
static u8 _fsysCheckExpandCompleteAll(FsysWork*);
static u8 _fsysCheckExpandComplete(FsysWork*, u32);
s32 _fsysGetActiveTask(s32);
static u8 _fsysCloseFile(FsysWork*, u8);
static s32 _fsysGetFilename(FsysWork*, char*);
void _fsysResHeaderSetTaskStatus(FsysResHeader*, u32);
void _fsysWorkSetTaskStatus(FsysWork*, u32);
static void _fsysDelBGWork(FsysBG*);
void _fsysAddBGWork(FsysBG*);
FsysBG* _fsysGetNewBGWork(void);
void _fsysDelTAG(FsysTag*, FsysTag**);
void _fsysAddTAG(FsysTag*, FsysTag**);
static FsysWork* _fsysGetNewWork_Sub(s32);
FsysWork* _fsysInfo2Work(u32);
void* GSmemAllocAlign(u32, u32);
u32 GSdvdOpen(const char*);
s32 GSdvdGetLength(u32);
s32 GSdvdRead(u32, void*, s32, s32);
s32 GSdvdClose(u32);
u8 GSdvdReadAsync(u32, void*, s32, s32, void (*)(s32, u32));
void _fsysFree(void*);
u32 _fsysAlloc(u32);
void _fsysSetLockCacheFlag(u32, u32, s32);
void _fsysSetLockCacheFlagGroup(u32, s32);
void _fsysStreamFreeCacheAll(FsysWork*);
void _fsysMemFreeHeader(FsysWork*);
void _fsysReadRequest(FsysWork*);
void _fsysSeekRequest(FsysWork*);
void _fsysReadDataExec(FsysWork*, FsysResHeader*);
u8 _fsysExpandFileExec(FsysWork*, FsysResHeader*);
u32 _fsysStreamGetNormalCacheSize(void);
u32 _fsysStreamGetMinimumCacheSize(void);
void OSReport(const char*, ...);
int sprintf(char*, const char*, ...);
u8 _fsysInitBlock(s32);
u8 _fsysInitCache(s32, s32);
void* GSgappCreate(u32, u32, u32, void (*)(void));
void GSgappSetName(void*, const char*);
static u8 _fsysInitTOC(void);
static void* _fsysDoMalloc(u32);
FsysDataType* _fsysGetDataType(u32);
void* _fsysGetResource(u32, u32, u32, FsysResHeader*);
static void GSfsysDaemonForeground(void);
static void GSfsysDaemonBackground(void);
static void _fsysBackgroundTaskNormalType(FsysBG*, u8);
static void _fsysBackgroundTaskCompressType(FsysBG*);
static u8 _fsysBGTaskCancel(FsysBG*);
s32 _fsysGetTransLength(u32, u32);
void _fsysFreeBlock(FsysBlock**, s32);
void _fsysFreeBlockAll(FsysBlock**);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
void DCFlushRange(void*, u32);

static u8 headerTop[0x20];
static FsysQue* _fsysQueManageRoot[3];
static u8 _initFlag;
static FsysTOC* _fsysTOC;
static FsysWork* _fsysWork;
static FsysBG* _fsysBGWork;
static FsysBG* _fsysBGWorkRoot;
static FsysQue* _fsysQueManage;
static FsysQue* _fsysQueManageExec;
static void* _fsysDaemonForegroundHDL;
static void* _fsysDaemonBackgroundHDL;
static u8* _headerTop;
static u32 _fsysQueManageMax;
static u32 _fsysBGWorkIndex;
static u32 _fsysBGWorkMax;
static u32 _fsysWorkIndex;
static u32 _fsysWorkMax;

s32 GSfsysStreamMoviePreFunc(u32 arg);
s32 GSfsysStreamMovieHeaderPostFunc(void);
s32 GSfsysStreamMovieHeaderPreFunc(void);
s32 GSfsysStreamPreFunc(u32 arg);
s32 GSfsysStreamHeaderPostFunc(void);
s32 GSfsysStreamHeaderPreFunc(void);
u32 GSfsysOSLinkPreFunc(u32 a, u32 b, u32 size);
void* GSfsysOSLinkPostFunc(u32 a, u32 b);
typedef void* (*PreFn)(u32, u32, u32);
typedef void (*PostFn)(u32, u32, u32);
u32 floorReadAntPostFunc(u32, u32, u32);
u32 floorReadAntPreFunc(u32, u32, u32);
u32 floorReadBGMPostFunc(u32, u32, u32);
u32 floorReadBGMPreFunc(u32, u32, u32);
u32 floorReadCameraPostFunc(u32, u32, u32);
u32 floorReadCameraPreFunc(u32, u32, u32);
u32 floorReadColPostFunc(u32, u32, u32);
u32 floorReadColPreFunc(u32, u32, u32);
u32 floorReadDeckPostFunc(u32, u32, u32);
u32 floorReadDeckPreFunc(u32, u32, u32);
u32 floorReadEncodeRelPostFunc(u32, u32, u32);
u32 floorReadEncodeRelPreFunc(u32, u32, u32);
u32 floorReadFontPostFunc(u32, u32, u32);
u32 floorReadFontPreFunc(u32, u32, u32);
u32 floorReadGFLPostFunc(u32, u32, u32);
u32 floorReadGFLPreFunc(u32, u32, u32);
u32 floorReadGSWPostFunc(u32, u32, u32);
u32 floorReadGSWPreFunc(u32, u32, u32);
u32 floorReadMapPostFunc(u32, u32, u32);
u32 floorReadMapPreFunc(u32, u32, u32);
u32 floorReadMsgPostFunc(u32, u32, u32);
u32 floorReadMsgPreFunc(u32, u32, u32);
u32 floorReadNormalPreFunc(u32, u32, u32);
u32 floorReadNotLinkedParticlePostFunc(u32, u32, u32);
u32 floorReadNotLinkedParticlePreFunc(u32, u32, u32);
u32 floorReadObjPostFunc(u32, u32, u32);
u32 floorReadObjPreFunc(u32, u32, u32);
u32 floorReadPKXPostFunc(u32, u32, u32);
u32 floorReadPKXPreFunc(u32, u32, u32);
u32 floorReadParticlePostFunc(u32, u32, u32);
u32 floorReadParticlePreFunc(u32, u32, u32);
u32 floorReadScriptPostFunc(u32, u32, u32);
u32 floorReadScriptPreFunc(u32, u32, u32);
u32 floorReadTexPostFunc(u32, u32, u32);
u32 floorReadTexPreFunc(u32, u32, u32);
u32 floorReadWZXPostFunc(u32, u32, u32);
u32 floorReadWZXPreFunc(u32, u32, u32);

FsysDataType fsys_datatype[] = {
    {800, 0, (PreFn)floorReadNormalPreFunc, 0},
    {600, 1, (PreFn)floorReadMapPreFunc, (PostFn)floorReadMapPostFunc},
    {700, 2, (PreFn)floorReadObjPreFunc, (PostFn)floorReadObjPostFunc},
    {800, 3, (PreFn)floorReadColPreFunc, (PostFn)floorReadColPostFunc},
    {300, 4, (PreFn)floorReadBGMPreFunc, (PostFn)floorReadBGMPostFunc},
    {400, 5, (PreFn)floorReadMsgPreFunc, (PostFn)floorReadMsgPostFunc},
    {500, 6, (PreFn)floorReadFontPreFunc, (PostFn)floorReadFontPostFunc},
    {200, 7, (PreFn)floorReadScriptPreFunc, (PostFn)floorReadScriptPostFunc},
    {800, 8, 0, 0},
    {900, 9, (PreFn)floorReadTexPreFunc, (PostFn)floorReadTexPostFunc},
    {800, 10, (PreFn)floorReadParticlePreFunc, (PostFn)floorReadParticlePostFunc},
    {800, 11, 0, 0},
    {800, 12, (PreFn)floorReadCameraPreFunc, (PostFn)floorReadCameraPostFunc},
    {800, 13, 0, 0},
    {100, 14, (PreFn)GSfsysOSLinkPreFunc, (PostFn)GSfsysOSLinkPostFunc},
    {700, 15, (PreFn)floorReadPKXPreFunc, (PostFn)floorReadPKXPostFunc},
    {800, 16, (PreFn)floorReadWZXPreFunc, (PostFn)floorReadWZXPostFunc},
    {950, 17, (PreFn)floorReadGFLPreFunc, (PostFn)floorReadGFLPostFunc},
    {800, 18, (PreFn)floorReadNotLinkedParticlePreFunc, (PostFn)floorReadNotLinkedParticlePostFunc},
    {100, 19, (PreFn)floorReadEncodeRelPreFunc, (PostFn)floorReadEncodeRelPostFunc},
    {100, 20, (PreFn)GSfsysStreamHeaderPreFunc, (PostFn)GSfsysStreamHeaderPostFunc},
    {200, 21, (PreFn)GSfsysStreamPreFunc, 0},
    {100, 22, (PreFn)GSfsysStreamMovieHeaderPreFunc, (PostFn)GSfsysStreamMovieHeaderPostFunc},
    {200, 23, (PreFn)GSfsysStreamMoviePreFunc, 0},
    {900, 24, (PreFn)floorReadGSWPreFunc, (PostFn)floorReadGSWPostFunc},
    {700, 25, (PreFn)floorReadAntPreFunc, (PostFn)floorReadAntPostFunc},
    {800, 26, (PreFn)floorReadDeckPreFunc, (PostFn)floorReadDeckPostFunc},
};
s32 fsys_datatype_number = 27;

u32 GSfsysStreamGetCacheSize(void) {
    return _fsysStreamGetCacheSize();
}

u32 GSfsysGetInvalidID(void) {
    return 0xFFFF;
}

void GSfsysStreamSetLoopPoint(u32 gid, u32 id, u32 point, u32 end) {
    FsysWork* work;
    FsysResHeader* res;

    if (_initFlag) {
        work = _fsysGetWork(gid, 0);
        if (work != 0) {
            if (id == 0) {
                res = _fsysGetResHeader(work, 1);
            } else {
                res = _fsysGetResHeader(work, _fsysID2Index(work, id));
            }
            if (res != 0) {
                res->loopPoint = point;
                res->loopEnd = end;
            }
        }
    }
}

void GSfsysStreamSetLoopFlag(u32 gid, u32 id, u8 flag) {
    FsysWork* work;
    FsysResHeader* res;

    if (_initFlag) {
        work = _fsysGetWork(gid, 0);
        if (work != 0) {
            if (id == 0) {
                res = _fsysGetResHeader(work, 1);
            } else {
                res = _fsysGetResHeader(work, _fsysID2Index(work, id));
            }
            if (res != 0) {
                if (flag == 0) {
                    res->flags |= 0x800;
                } else {
                    res->flags &= ~0x800;
                }
            }
        }
    }
}

s32 GSfsysStreamGetData(u32 gid, u32 id, u32 dst, u32 size, u32 offset, u32 a, u32 b, u32 c) {
    if (!_initFlag) {
        return 0;
    }
    FsysWork* work = _fsysGetWork(gid, 0);
    if (work == 0) {
        _fsysMemSet((void*)dst, 0, size);
        return 0;
    }
    return _fsysStreamGetData(work, id, dst, size, offset, a, b, c);
}

s32 GSfsysStreamMoviePreFunc(u32 arg) {
    FsysWork* work;

    if (!_initFlag) {
        return 0;
    }
    work = _fsysGetWork(arg, 0);
    if (work == 0) {
        return 0;
    }
    GSmovieStreamPostFunc(arg, work->cbArg1);
    return 0;
}

s32 GSfsysStreamMovieHeaderPostFunc(void) {
    if (!_initFlag) {
        return 0;
    }
    return 0;
}

s32 GSfsysStreamMovieHeaderPreFunc(void) {
    if (_initFlag == 0) {
        return 0;
    }
    return GSmovieStreamPreFunc();
}

s32 GSfsysStreamPreFunc(u32 arg) {
    FsysWork* work;

    if (!_initFlag) {
        return 0;
    }
    work = _fsysGetWork(arg, 0);
    if (work == 0) {
        return 0;
    }
    GSsndStreamPostFunc(arg, work->cbArg1);
    return 0;
}

s32 GSfsysStreamHeaderPostFunc(void) {
    if (!_initFlag) {
        return 0;
    }
    return 0;
}

s32 GSfsysStreamHeaderPreFunc(void) {
    if (_initFlag == 0) {
        return 0;
    }
    return GSsndStreamPreFunc();
}

u8 GSfsysInit(void) {
    GSdvdInit();
    return GSfsysInit2(0, 0, 0);
}

s32 GSfsysGetDriveStatus(void) {
    if (_initFlag == 0) {
        return -1;
    }
    return GSdvdGetDriveStatus();
}

void GSfsysFreeCache(s32 group) {
    if (_initFlag) {
        while (_fsysMemFreeCacheGroup(group)) {
        }
    }
}

void GSfsysFree(u32 id) {
    FsysHeader* header;
    FsysWork* work;
    s32 i;
    BOOL intr;

    if (_initFlag) {
        intr = OSDisableInterrupts();
        _fsysFreeStatus(id);
        work = _fsysGetWork(id, 0);
        if (work != 0) {
            header = _fsysGetHeader(work);
            if (header != 0) {
                for (i = 0; i < header->resNum; i++) {
                    FsysResHeader* res = _fsysGetResHeader(work, i);
                    if (res != 0) {
                        res->flags &= ~0x8;
                    }
                }
            }
        }
        OSRestoreInterrupts(intr);
    }
}

u32 GSfsysOSLinkPreFunc(u32 a, u32 b, u32 size) {
    u32 res = GSresAllocResourceAlign(size, 0x20, a, b, (void*)_fsysOSUnLink);
    if (res == 0) {
        res = 0;
    }
    return res;
}

void* GSfsysOSLinkPostFunc(u32 a, u32 b) {
    OSLinkRes* res = (OSLinkRes*)GSresGetResource(a, b);
    u8* end;
    if (res == 0) {
        return 0;
    }
    if (res->unk1C < 3) {
        return 0;
    }
    end = (u8*)res + res->count * 0x4C;
    OSLinkFixed(res, (void*)(((u32)end + 0x1F) & ~0x1F));
    if (res->linkFunc != 0) {
        res->linkFunc();
    }
    return res;
}

static s32 _fsysOSUnLink(u32 unused, u32 a, u32 b) {
    if (_initFlag == 0) {
        return 0;
    }
    GSfsysOSUnLink(a, b, 0);
    return 1;
}

void GSfsysOSUnLink(u32 a, u32 b, u32 unused) {
    OSLinkRes* res;

    if (_initFlag != 0) {
        res = (OSLinkRes*)GSresGetResource(a, b);
        if (res != 0) {
            if (res->unlinkFunc != 0) {
                res->unlinkFunc();
            }
            OSUnlink(res);
        }
    }
}

s32 GSfsysReadIDEXWait(u32 id, u32 idx, s32 a, s32 b, s32 c) {
    if (_initFlag == 0) {
        return 0;
    }
    while (1) {
        if (GSfsysReadIDEX(id, idx, a, b, c) == 1) {
            break;
        }
        GSthreadSwitch();
    }
    return _fsysWait(id, 0);
}

s32 GSfsysReadIDWait(u32 id, u32 idx) {
    if (_initFlag == 0) {
        return 0;
    }
    while (1) {
        if (GSfsysReadID(id, idx) == 1) {
            break;
        }
        GSthreadSwitch();
    }
    return _fsysWait(id, 0);
}

u8 GSfsysReadIDEX(u32 id, u32 idx, s32 a, s32 b, s32 c) {
    return _fsysRequest(1, id, idx, 0, a, b, c, 1);
}

u8 GSfsysReadID(u32 id, u32 idx) {
    return _fsysRequest(1, id, idx, 0, 0, 0, 0, 1);
}

s32 GSfsysCancelWait(u32 id) {
    if (GSfsysCancel(id) == 0) {
        return 0;
    }
    return _fsysWait(id, 0);
}

u8 GSfsysCancel(u32 id) {
    FsysWork* work;

    if (_initFlag == 0) {
        return 0;
    }
    if (GSfsysGetStatus(id) <= 0) {
        return 0;
    }
    work = _fsysGetWork(id, 1);
    if (work == 0) {
        return 0;
    }
    work->cancel = 1;
    return 1;
}

s32 GSfsysPreReadWait(u32 id) {
    if (_initFlag == 0) {
        return 0;
    }
    while (1) {
        if (GSfsysPreRead(id) == 1) {
            break;
        }
        GSthreadSwitch();
    }
    return _fsysWait(id, 0);
}

u8 GSfsysPreReadKeepCache(u32 id) {
    return _fsysPreReadExec(id, 1, 0, 0, 0, 1);
}

u8 GSfsysPreRead(u32 id) {
    return _fsysPreReadExec(id, 0, 0, 0, 0, 1);
}

static u8 _fsysPreReadExec(u32 id, s8 keep, s32 a, s32 b, s32 c, s32 prio) {
    return _fsysRequest(2, id, 0xFFFF, keep, a, b, c, prio);
}

s32 GSfsysReadWait(u32 id) {
    FsysWork* work;

    if (_initFlag == 0) {
        return 0;
    }
    work = _fsysGetWork(id, 1);
    if (work != 0 && work->mode == 2) {
        GSfsysCancelWait(id);
    }
    while (1) {
        if (GSfsysRead(id) == 1) {
            break;
        }
        GSthreadSwitch();
    }
    return _fsysWait(id, 0);
}

s32 GSfsysWait(u32 id) {
    return _fsysWait(id, 1);
}

static s32 _fsysWait(u32 id, u8 flag) {
    s32 status;

    if (_initFlag == 0) {
        return 0;
    }
    while (1) {
        status = GSfsysGetStatus(id);
        if (status == 0) {
            return 1;
        }
        if (status == -1) {
            if (flag == 1) {
                return 1;
            }
        } else if (status <= -2) {
            return 0;
        }
        GSthreadSwitch();
    }
}

s32 GSfsysReadStreamingEX(u32 id, s32 idx, s32 arg) {
    return _fsysReadStreamingExec(id, idx, arg);
}

s32 GSfsysReadStreaming(u32 id) {
    return _fsysReadStreamingExec(id, 0xFFFF, 0);
}

static s32 _fsysReadStreamingExec(u32 id, s32 idx, s32 arg) {
    if (_initFlag == 0) {
        return 0;
    }
    if (GSfsysGetStatus(id) <= 0) {
        return _fsysExec(id, idx, 4, 0, 0, 0, arg);
    }
    GSfsysCancelWait(id);
    return _fsysExec(id, idx, 4, 0, 0, 0, arg);
}

u8 GSfsysRead(u32 id) {
    return _fsysRequest(1, id, 0xFFFF, 0, 0, 0, 0, 1);
}

static u8 _fsysRequest(s32 type, u32 id, u32 idx, s8 flag, s32 a, s32 b, s32 c, s32 prio) {
    FsysQue* que;

    if (_initFlag == 0) {
        return 0;
    }
    if (type < 0 || prio >= 6) { // retail checks prio here, not type
        return 0;
    }
    if (prio < 0 || prio >= 3) {
        return 0;
    }
    que = _fsysGetQueManage(id, idx);
    if (que != 0 && que->started == 0 && (type == 2 || type == 3)) {
        _fsysDelQueManage(que);
    }
    que = _fsysGetNewQueManage(type, id, idx, flag, a, b, c);
    if (que == 0) {
        return 0;
    }
    if (_fsysAddQueManage(que, prio) == 1) {
        _fsysQueExec();
    }
    return 1;
}

static void _fsysQueExec(void) {
    FsysQue** rp;
    FsysQue* que;
    FsysQue* next;
    s32 i;

    if (_fsysQueManageExec != 0) {
        if (_fsysQueExecSub(_fsysQueManageExec) == 0) {
            return;
        }
        _fsysQueManageExec = 0;
    }
    for (i = 0; i < 3; i++) {
        que = _fsysQueManageRoot[i];
        while (que != 0) {
            next = que->next;
            if (_fsysQueExecSub(que) == 0) {
                _fsysQueManageExec = que;
                return;
            }
            que = next;
        }
    }
}

static u8 _fsysQueExecSub(FsysQue* que) {
    if (que->started == 0) {
        que->started = 1;
        switch (que->type) {
        case 5:
            GSfsysCancel(que->id);
            return 0;
        default:
            _fsysDelQueManage(que);
            return 1;
        case 1:
        case 2:
        case 3:
        case 4:
            _fsysExec(que->id, que->idx, que->type, que->flag, que->a, que->b, que->c);
            return 0;
        }
    }
    if (GSfsysGetStatus(que->id) <= 0) {
        _fsysDelQueManage(que);
        return 1;
    }
    return 0;
}

static void _fsysDelQueManage(FsysQue* que) {
    s32 i;

    if (que->prev != 0) {
        que->prev->next = que->next;
    }
    if (que->next != 0) {
        que->next->prev = que->prev;
    }
    for (i = 0; i < 3; i++) {
        if (que == _fsysQueManageRoot[i]) {
            _fsysQueManageRoot[i] = que->next;
            break;
        }
    }
    que->id = 0;
}

static u8 _fsysAddQueManage(FsysQue* que, s32 prio) {
    FsysQue* p;
    FsysQue* root;
    u8 first;

    root = _fsysQueManageRoot[prio];
    if (root == 0) {
        _fsysQueManageRoot[prio] = que;
        first = 1;
    } else {
        p = root;
        while (p->next != 0) {
            p = p->next;
        }
        p->next = que;
        first = 0;
        que->prev = p;
    }
    return first;
}

static FsysQue* _fsysGetQueManage(u32 id, u32 idx) {
    s32 i;
    FsysQue* que;

    for (i = 0; i < 3; i++) {
        for (que = _fsysQueManageRoot[i]; que != 0; que = que->next) {
            if (que->id == id) {
                if (idx != 0xFFFF && que->idx == idx) {
                    return que;
                }
                return que;
            }
        }
    }
    return 0;
}

static FsysQue* _fsysGetNewQueManage(s32 type, u32 id, u32 idx, s8 flag, s32 a, s32 b, s32 c) {
    u32 n;
    FsysQue* p = _fsysQueManage;
    FsysQue* ret = 0;
    s32 i = 0;

    for (n = 0; n < _fsysQueManageMax; n++) {
        if (p->id == 0) {
            ret = &_fsysQueManage[i];
            ret->prev = 0;
            ret->next = 0;
            ret->type = type;
            ret->id = id;
            ret->idx = idx;
            ret->a = a;
            ret->b = b;
            ret->c = c;
            ret->flag = flag;
            ret->started = 0;
            break;
        }
        p++;
        i++;
    }
    return ret;
}

static s32 _fsysExec(u32 id, s32 idx, s32 mode, s8 flag, s32 a, s32 b, s32 c) {
    enum TsE { TsE0 };
    BOOL intr;
    FsysWork* work;
    enum TsE gid = (enum TsE)(id);

    intr = OSDisableInterrupts();
    _fsysFreeStatus(id);
    work = _fsysGetWork(id, 0);
    if (work == 0) {
        work = _fsysGetNewWork();
        if (work == 0) {
            OSRestoreInterrupts(intr);
            return 0;
        }
        work->header = 0;
        work->groupId = _fsysIncCacheUniqueGroupID();
    }
    work->id = gid;
    work->unk8 = idx;
    work->file = 0;
    work->mode = mode;
    work->status = 2;
    work->pending = 0xFFFF;
    work->unk24 = 0;
    work->unk28 = 0;
    work->cancel = 0;
    work->unk2D = flag;
    work->callback = (void (*)(u32, u32, u32))a;
    work->cbArg0 = b;
    work->cbArg1 = c;
    work->group = _fsysGetGROUP(gid);
    _fsysOpenFile(work);
    OSRestoreInterrupts(intr);
    return 1;
}

static void _fsysFreeStatus(u32 id) {
    FsysWork* work;

    _fsysOffTOCFlag(id, 1);
    work = _fsysGetWork(id, 0);
    if (work != 0) {
        work->status = 1;
    }
}

s32 GSfsysGetStatus(u32 id) {
    FsysGroup* group;
    FsysWork* work;

    if (_initFlag == 0) {
        return -2;
    }
    group = _fsysGetGROUP(id);
    if (group == 0) {
        return -1;
    }
    if (group->flags & 1) {
        return 0;
    }
    work = _fsysGetWork(id, 0);
    if (work == 0) {
        return -1;
    }
    switch (work->status) {
    case 12:
        return 0;
    case 1:
        return -1;
    case -999:
        return -2;
    default:
        return 1;
    }
}

void _fsysDebugNames(s32 i) {
    const char* names[] = {"READ", "PREREAD", "STREAMING"};
    OSReport(names[i]);
}

void _fsysDebugStatus(s32 i) {
    OSReport("[%d]HEADERSIZE_READ", i);
    OSReport("[%d]HEADERSIZE_READ_WAIT", i);
    OSReport("[%d]START", i);
    OSReport("[%d]%s:---", i);
    OSReport("[%d]%s:[%d]ERROR_READDATAEXEC", i);
    OSReport("[%d]%s:[%d]ERROR_EXPANDFILE", i);
    OSReport("[%d]%s:[%d]ERROR_STREAMING", i);
    OSReport("[%d]%s:[%d]STREAMING_COMPLETE", i);
    OSReport("[%d]%s:[%d]READY", i);
    OSReport("[%d]%s:[%d]NONE", i);
    OSReport("[%d]%s:[%d]default", i);
    OSReport("[%d]SEEK", i);
    OSReport("[%d]READ_COMPLETE", i);
    OSReport("[%d]ERROR", i);
    OSReport("[%d]ERROR_READ", i);
    OSReport("[%d]ERROR_PREREAD", i);
    OSReport("[%d]ERROR_SEEK", i);
    OSReport("[%d]ERROR_FILEOPEN", i);
    OSReport("[%d]ERROR_FILECLOSE", i);
    OSReport("[%d]COMPLETE", i);
    OSReport("[%d]ERROR_WAIT", i);
    OSReport("[%d]COMPLETE_WAIT", i);
    OSReport("[%d]READY", i);
    OSReport("[%d]READY_WAIT", i);
    OSReport("[%d]NONE", i);
    OSReport("[%d]default", i);
}

u8 GSfsysInit2(s32 unused, s32 a, s32 b) {
    u32 i;

    if (_initFlag == 1) {
        return 0;
    }
    _fsysQueManageRoot[0] = 0;
    _fsysWorkIndex = 0;
    _fsysBGWorkIndex = 0;
    _fsysQueManageRoot[1] = 0;
    _fsysQueManageRoot[2] = 0;
    _fsysQueManageExec = 0;
    if (_fsysInitBlock(unused) == 0) {
        return 0;
    }
    if (_fsysInitCache(a, b) == 0) {
        return 0;
    }
    _fsysWorkMax = 4;
    _fsysBGWorkMax = 0x10;
    _fsysQueManageMax = 0x18;
    _fsysWork = (FsysWork*)_fsysDoMalloc(0x100);
    if (_fsysWork == 0) {
        return 0;
    }
    _fsysBGWork = (FsysBG*)_fsysDoMalloc(_fsysBGWorkMax * sizeof(FsysBG));
    if (_fsysBGWork == 0) {
        return 0;
    }
    _fsysQueManage = (FsysQue*)_fsysDoMalloc(_fsysQueManageMax * sizeof(FsysQue));
    if (_fsysQueManage == 0) {
        return 0;
    }
    for (i = 0; i < _fsysWorkMax; i++) {
        _fsysWork[i].status = 0;
        _fsysWork[i].pending = 0xFFFF;
        _fsysWork[i].header = 0;
        _fsysWork[i].unk2E = 0;
    }
    for (i = 0; i < _fsysBGWorkMax; i++) {
        _fsysBGWork[i].used = 0;
    }
    for (i = 0; i < _fsysQueManageMax; i++) {
        _fsysQueManage[i].id = 0;
    }
    if (_fsysInitTOC() == 0) {
        return 0;
    }
    _fsysDaemonForegroundHDL = GSgappCreate(1, 0x14, 0, GSfsysDaemonForeground);
    GSgappSetName(_fsysDaemonForegroundHDL, "GSfsysDaemonForeground");
    _fsysDaemonBackgroundHDL = GSgappCreate(1, 0x13, 0, GSfsysDaemonBackground);
    GSgappSetName(_fsysDaemonBackgroundHDL, "GSfsysDaemonBackground");
    _initFlag = 1;
    return 1;
}

static void GSfsysDaemonBackground(void) {
    FsysBG* bg;

    for (bg = _fsysBGWorkRoot; bg != 0; bg = bg->next) {
        if (bg->started == 0) {
            bg->started = 1;
            FsysDataType* dt = _fsysGetDataType(bg->res->type);
            void* data;
            if (dt->pre != 0) {
                data = dt->pre(bg->work->id, bg->res->id, bg->res->size8);
            } else {
                data = _fsysGetResource((bg->res->size8 + 0x1F) & ~0x1F, bg->work->id, bg->res->id, bg->res);
            }
            bg->res->data = data;
        }
        if (bg->res->data == 0) {
            _fsysBackgroundTaskNormalType(bg, 0);
        } else if (bg->type == 1) {
            _fsysBackgroundTaskCompressType(bg);
        } else {
            _fsysBackgroundTaskNormalType(bg, 1);
        }
    }
}

static void _fsysBackgroundTaskNormalType(FsysBG* bg, u8 copy) {
    FsysBlock* block;
    u8* dst;

    if (bg->done != 1) {
        while (1) {
            if (_fsysBGTaskCancel(bg) == 1) {
                return;
            }
            block = bg->res->blockB;
            if (block == 0) {
                return;
            }
            if (copy == 1) {
                dst = (u8*)bg->res->data + bg->pos;
                s32 tmp2 = _fsysGetTransLength(bg->res->size14, bg->pos);
                memcpy(dst, block->data, tmp2);
            }
            _fsysFreeBlock(&bg->res->blockB, 1);
            bg->pos += _fsysBlockByteSize;
            if (bg->pos >= bg->res->size14) {
                break;
            }
        }
        DCFlushRange(bg->res->data, bg->res->size14);
        bg->done = 1;
    }
}

static void _fsysBackgroundTaskCompressType(FsysBG* bg) {
    FsysBlock* block;
    u8 b;
    u32 wpos;
    u32 flags;
    u32 count;
    u32 pos;
    u32 dpos;
    u8* dest;
    u8* window;
    u32 limit;
    u32 blockSize;
    s32 state;
    u32 in;
    u32 off;
    s32 len;
    s32 k;

    if (bg->done == 1) {
        return;
    }
    if (_fsysBGTaskCancel(bg) == 1) {
        return;
    }
    block = bg->res->blockB;
    if (block == 0) {
        return;
    }
    if (bg->window == 0) {
        bg->window = (u8*)_fsysAlloc(0x1011);
        if (bg->window == 0) {
            return;
        }
        memset(bg->window, 0, 0xFEE);
        memcpy(&bg->hdr, block->data, 0x10);
        bg->wpos = 0xFEE;
        bg->flags = 0;
        bg->limit = bg->inSize - 0x10;
        bg->state = 0;
        in = 0x10;
    } else {
        in = 0;
    }
    count = bg->count;
    flags = bg->flags;
    wpos = bg->wpos;
    off = bg->off;
    pos = bg->pos;
    dpos = bg->dpos;
    dest = (u8*)bg->res->data;
    limit = bg->limit;
    blockSize = _fsysBlockByteSize;
    window = bg->window;
    state = bg->state;

    while (1) {
        u8* src = block->data;
        switch (state) {
        case 1:
            goto read_flags;
        case 2:
            goto read_literal;
        case 3:
            goto read_off;
        case 4:
            goto read_len;
        case 0:        default:
            break;
        }
    next:
        flags >>= 1;
        if (flags & 0x100) {
            goto have_flags;
        }
    read_flags:
        pos++;
        b = src[in];
        in++;
        if (pos > limit) {
            goto done;
        }
        if (in > blockSize) {
            state = 1;
            pos--;
            goto done;
        }
        flags = b | 0xFF00;
    have_flags:
        if (!(flags & 1)) {
            goto read_off;
        }
    read_literal:
        pos++;
        b = src[in];
        in++;
        if (pos > limit) {
            goto done;
        }
        if (in > blockSize) {
            state = 2;
            pos--;
            goto done;
        }
        dest[dpos] = b;
        dpos++;
        window[wpos] = b;
        wpos = (wpos + 1) & 0xFFF;
        goto step;
    read_off:
        pos++;
        off = src[in];
        in++;
        if (pos > limit) {
            goto done;
        }
        if (in > blockSize) {
            state = 3;
            pos--;
            goto done;
        }
    read_len:
        pos++;
        b = src[in];
        in++;
        if (pos > limit) {
            goto done;
        }
        if (in > blockSize) {
            state = 4;
            pos--;
            goto done;
        }
        len = (b & 0xF) + 2;
        off |= (b << 4) & 0xF00;
        for (k = 0; k <= len; k++) {
            u8 c = window[(off + k) & 0xFFF];
            window[wpos] = c;
            dest[dpos] = c;
            dpos++;
            wpos = (wpos + 1) & 0xFFF;
        }
    step:
        count++;
        goto next;
    done:
        _fsysFreeBlock(&bg->res->blockB, 1);
        if (pos > limit) {
            DCFlushRange(bg->res->data, bg->outSize);
            bg->done = 1;
            return;
        }
        if (_fsysBGTaskCancel(bg) == 1) {
            return;
        }
        block = bg->res->blockB;
        if (block == 0) {
            break;
        }
        in = 0;
    }
    bg->count = count;
    bg->flags = flags;
    bg->off = off;
    bg->wpos = wpos;
    bg->pos = pos;
    bg->dpos = dpos;
    bg->state = state;
}

void _fsysMemSet(void* dst, s32 c, u32 size) {
    if (dst != 0) {
        memset(dst, c, size);
        DCFlushRange(dst, size);
    }
}

static u8 _fsysBGTaskCancel(FsysBG* bg) {
    if (bg->work->cancel == 1) {
        _fsysFreeBlockAll(&bg->res->blockA);
        _fsysFreeBlockAll(&bg->res->blockB);
        bg->done = 1;
        return 1;
    }
    return 0;
}

static void GSfsysDaemonForeground(void) {
    FsysBG* bg;
    FsysBG* next;
    FsysWork* work;
    FsysResHeader* res;
    FsysResHeader* prev;
    u32 idx;
    u32 i;

    for (bg = _fsysBGWorkRoot; bg != 0; bg = next) {
        next = bg->next;
        if (bg->done == 1) {
            res = bg->res;
            work = bg->work;
            idx = _fsysID2Index(work, res->id);
            if (idx != 0) {
                prev = _fsysGetResHeader(work, idx - 1);
            } else {
                prev = 0;
            }
            if (_fsysID2Index(work, work->unk8) != 0xFFFF || prev == 0 || (prev->flags & 8)) {
                FsysDataType* dt = _fsysGetDataType(res->type);
                if (work->cancel == 0) {
                    if (dt->post != 0) {
                        if (res->flags & 0x80000000) {
                            dt->post(work->id, res->id, res->size8);
                        } else {
                            dt->post(work->id, res->id, res->size14);
                        }
                    }
                }
                if (bg->window != 0) {
                    _fsysFree(bg->window);
                    bg->window = 0;
                }
                _fsysDelBGWork(bg);
                res->flags |= 8;
                _fsysSetLockCacheFlag(work->id, _fsysID2Index(work, res->id), 0);
            } else if (prev != 0 && (prev->flags & 8) == 0) {
                OSReport("<1>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", work->id, _fsysID2Index(work, res->id));
            } else {
                OSReport("<2>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", work->id, _fsysID2Index(work, res->id));
            }
        }
    }
    for (i = 0; i < _fsysWorkMax; i++) {
        _fsysForegroundTask(&_fsysWork[i]);
    }
    _fsysQueExec();
}

static void _fsysForegroundTask(FsysWork* work) {
    BOOL intr;

    intr = OSDisableInterrupts();
    if (work->pending != 0xFFFF) {
        work->status = work->pending;
        work->pending = 0xFFFF;
    }
    OSRestoreInterrupts(intr);
    switch (work->status) {
    case -999:
        break;
    default:
        OSReport("_fsysForegroundTask:ERROR...:%d\n", work->id);
        if (_fsysCloseFile(work, 1) == 0) {
            _fsysWorkSetTaskStatus(work, -997);
            break;
        }
    case -998:
        OSReport("_fsysForegroundTask:ERROR_FILEOPEN:%d\n", work->id);
        _fsysOpenFile(work);
        break;
    case -997:
        OSReport("_fsysForegroundTask:ERROR_FILECLOSE:%d\n", work->id);
        _fsysWorkSetTaskStatus(work, -999);
        break;
    case 3:
        if (_headerTop == 0) {
            _headerTop = headerTop;
            _fsysWorkSetTaskStatus(work, 4);
            if (GSdvdReadAsync(work->file, _headerTop, 0x20, 0, _fsysHeaderSizeReadDvdCallback) == 0) {
                _headerTop = 0;
                _fsysWorkSetTaskStatus(work, 3);
            }
        }
        break;
    case 5:
        switch (work->mode) {
        case 1:
            _fsysWorkSetTaskStatus(work, 6);
            _fsysReadRequest(work);
            break;
        case 4:
            _fsysWorkSetTaskStatus(work, 9);
            _fsysReadRequest(work);
            break;
        case 2:
            _fsysWorkSetTaskStatus(work, 7);
            _fsysReadRequest(work);
            break;
        case 3:
            _fsysWorkSetTaskStatus(work, 8);
            _fsysSeekRequest(work);
            break;
        default:
            _fsysWorkSetTaskStatus(work, -1000);
            break;
        }
        break;
    case 6:
    case 7:
    case 9:
        _fsysCheckExpandCompleteAll(work);
        break;
    case 10:
        switch (work->mode) {
        case 1:
            if (_fsysCheckExpandCompleteAll(work) == 0) {
                break;
            }
        case 4:
            _fsysWorkSetTaskStatus(work, 11);
            break;
        default:
        case 3:
            _fsysWorkSetTaskStatus(work, -1000);
            break;
        }
        break;
    case 11:
        if (_fsysCloseFile(work, 0) == 0) {
            _fsysWorkSetTaskStatus(work, -997);
        } else {
            if (work->mode >= 5 || work->mode < 3) {
                _fsysOnTOCFlag(work->id, 1);
            }
            _fsysWorkSetTaskStatus(work, 12);
        }
        break;
    }
    intr = OSDisableInterrupts();
    if (work->pending != 0xFFFF) {
        work->status = work->pending;
        work->pending = 0xFFFF;
    }
    OSRestoreInterrupts(intr);
}

static void _fsysHeaderSizeReadDvdCallback(s32 result, u32 handle) {
    FsysWork* work = _fsysInfo2Work((u16)handle);

    if (work == 0) {
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 3);
    } else if (result < 0) {
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 3);
    } else {
        FsysGroup* group = work->group;
        group->headerSize = *(u32*)(_headerTop + 0x1C);
        _headerTop = 0;
        _fsysWorkSetTaskStatus(work, 5);
    }
}

static void _fsysOffTOCFlag(u32 id, u32 flag) {
    FsysGroup* group = _fsysGetGROUP(id);
    if (group != 0) {
        group->flags &= ~flag;
    }
}

static void _fsysOnTOCFlag(u32 id, u32 flag) {
    FsysGroup* group = _fsysGetGROUP(id);
    if (group != 0) {
        group->flags |= flag;
    }
}

static u8 _fsysCheckExpandCompleteAll(FsysWork* work) {
    FsysHeader* header;
    u8 ok;
    s32 i;

    header = _fsysGetHeader(work);
    if (header == 0) {
        return 0;
    }
    ok = 1;
    if (_fsysID2Index(work, work->unk8) != 0xFFFF) {
        if (work->mode == 4) {
            if (_fsysCheckExpandComplete(work, _fsysID2Index(work, work->unk8)) == 0) {
                ok = 0;
            }
            if (_fsysCheckExpandComplete(work, _fsysID2Index(work, work->cbArg1)) == 0) {
                ok = 0;
            }
        } else {
            return _fsysCheckExpandComplete(work, _fsysID2Index(work, work->unk8));
        }
    } else {
        for (i = 0; i < header->resNum; i++) {
            if (_fsysCheckExpandComplete(work, i) == 0) {
                ok = 0;
            }
        }
    }
    return ok;
}

u32 _fsysID2Index(FsysWork* work, u32 id) {
    FsysHeader* header;
    FsysResHeader* res;
    u32 i;

    if (id == 0xFFFF) {
        return 0xFFFF;
    }
    header = _fsysGetHeader(work);
    if (header != 0) {
        for (i = 0; i < header->resNum; i++) {
            res = _fsysGetResHeader(work, i);
            if (res != 0 && res->id == id) {
                return i;
            }
        }
    }
    return 0xFFFF;
}

static u8 _fsysCheckExpandComplete(FsysWork* work, u32 idx) {
    FsysResHeader* res;
    BOOL intr;
    u8 done;

    res = _fsysGetResHeader(work, idx);
    if (res == 0) {
        return 0;
    }
    intr = OSDisableInterrupts();
    if (res->pending != 0xFFFF) {
        res->unk3C = res->pending;
        res->pending = 0xFFFF;
    }
    OSRestoreInterrupts(intr);
    if (!(res->flags & 8)) {
        switch (res->unk3C) {
        case 3:
            _fsysReadDataExec(work, res);
            break;
        case 4:
            if (_fsysExpandFileExec(work, res) == 1) {
                _fsysReadDataExec(work, res);
            }
            break;
        case 5:
            if (work->cancel == 1) {
                _fsysWorkSetTaskStatus(work, 10);
                _fsysResHeaderSetTaskStatus(res, 1);
            } else {
                if (_fsysGetActiveTask(1) + (s32)(_fsysGetActiveTask(2)) == 0) {
                    if (res->unk44 <= _fsysStreamGetNormalCacheSize()) {
                        _fsysReadDataExec(work, res);
                    }
                } else if (res->unk44 <= _fsysStreamGetMinimumCacheSize()) {
                    _fsysReadDataExec(work, res);
                }
            }
            break;
        case 2:
            if (work->cancel == 1) {
                _fsysWorkSetTaskStatus(work, 10);
                _fsysResHeaderSetTaskStatus(res, 1);
            }
            break;
        case 0:
        case 1:
            break;
        }
        done = 0;
    } else {
        done = 1;
    }
    intr = OSDisableInterrupts();
    if (res->pending != 0xFFFF) {
        res->unk3C = res->pending;
        res->pending = 0xFFFF;
    }
    OSRestoreInterrupts(intr);
    return done;
}

s32 _fsysGetActiveTask(s32 mode) {
    FsysWork* w = _fsysWork;
    s32 n = 0;
    u32 i;

    for (i = 0; i < _fsysWorkMax; i++, w++) {
        switch (w->status) {
        case 0:
        case 1:
        case 12:
        case -999:
            break;
        default:
            if (mode == w->mode) {
                n++;
            }
            break;
        }
    }
    return n;
}

static u8 _fsysCloseFile(FsysWork* work, u8 flag) {
    BOOL intr;
    u32 file;

    if (flag == 0) {
        if (work->callback != 0 && work->mode != 4) {
            work->callback(work->mode, work->cbArg0, work->cbArg1);
        }
    }
    intr = OSDisableInterrupts();
    _fsysSetLockCacheFlagGroup(work->id, 0);
    _fsysStreamFreeCacheAll(work);
    OSRestoreInterrupts(intr);
    file = work->file;
    work->file = 0;
    return GSdvdClose(file);
}

static s32 _fsysOpenFile(FsysWork* work) {
    char name[0x80];

    _fsysGetFilename(work, name);
    work->file = GSdvdOpen(name);
    if (work->file == 0) {
        _fsysWorkSetTaskStatus(work, -998);
        return 0;
    }
    if (work->group->headerSize == 0) {
        _fsysWorkSetTaskStatus(work, 3);
    } else {
        _fsysWorkSetTaskStatus(work, 5);
    }
    return 1;
}

static s32 _fsysGetFilename(FsysWork* work, char* out) {
    FsysGroup* group = _fsysGetGROUP(work->id);

    if (group == 0) {
        return 0;
    }
    sprintf(out, "%s.fsys", group->name);
    return 1;
}

void _fsysResHeaderSetTaskStatus(FsysResHeader* res, u32 status) {
    BOOL intr = OSDisableInterrupts();
    res->pending = status;
    OSRestoreInterrupts(intr);
}

void _fsysWorkSetTaskStatus(FsysWork* work, u32 status) {
    BOOL intr = OSDisableInterrupts();
    work->pending = status;
    OSRestoreInterrupts(intr);
}

static FsysGroup* _fsysGetGROUP(u32 id) {
    FsysGroup* g = (FsysGroup*)((u8*)_fsysTOC + _fsysTOC->groupOffset);
    u32 n = _fsysTOC->count;
    u32 i;

    for (i = 0; i < n; i++, g++) {
        if (g->id == id) {
            return g;
        }
    }
    return 0;
}

static void _fsysDelBGWork(FsysBG* bg) {
    _fsysDelTAG((FsysTag*)bg, (FsysTag**)&_fsysBGWorkRoot);
}

void _fsysAddBGWork(FsysBG* bg) {
    _fsysAddTAG((FsysTag*)bg, (FsysTag**)&_fsysBGWorkRoot);
}

FsysBG* _fsysGetNewBGWork(void) {
    u32 i;
    FsysBG* bg;
    FsysBG* ret = 0;

    OSDisableInterrupts();
    i = _fsysBGWorkIndex;
    while (ret == 0) {
        bg = &_fsysBGWork[i];
        if (bg->used == 0) {
            bg->prev = 0;
            bg->next = 0;
            ret = bg;
            bg->used = 1;
            bg->done = 0;
            bg->type = 0;
            bg->started = 0;
            bg->work = 0;
            bg->res = 0;
            bg->hdr[0] = 0;
            bg->hdr[1] = 0;
            bg->hdr[2] = 0;
            bg->hdr[3] = 0;
            bg->outSize = 0;
            bg->inSize = 0;
            bg->limit = 0;
            bg->window = 0;
            bg->off = 0;
            bg->wpos = 0;
            bg->flags = 0;
            bg->count = 0;
            bg->pos = 0;
            bg->dpos = 0;
            bg->state = 0;
        }
        i++;
        if (i >= _fsysBGWorkMax) {
            i = 0;
        }
        if (i == _fsysBGWorkIndex) {
            break;
        }
    }
    _fsysBGWorkIndex = i;
    OSRestoreInterrupts(0);
    return ret;
}

void _fsysDelTAG(FsysTag* tag, FsysTag** root) {
    BOOL intr = OSDisableInterrupts();
    if (tag->prev != 0) {
        tag->prev->next = tag->next;
    }
    if (tag->next != 0) {
        tag->next->prev = tag->prev;
    }
    if (tag == *root) {
        *root = tag->next;
    }
    tag->used = 0;
    tag->prev = 0;
    tag->next = 0;
    OSRestoreInterrupts(intr);
}

void _fsysAddTAG(FsysTag* tag, FsysTag** root) {
    FsysTag* p;
    BOOL intr = OSDisableInterrupts();
    if (*root == 0) {
        *root = tag;
    } else {
        p = *root;
        while (p->next != 0) {
            p = p->next;
        }
        p->next = tag;
        tag->prev = p;
    }
    OSRestoreInterrupts(intr);
}

static FsysWork* _fsysGetNewWork(void) {
    FsysWork* w;

    w = _fsysGetNewWork_Sub(1);
    if (w != 0) {
        return w;
    }
    w = _fsysGetNewWork_Sub(0);
    if (w != 0) {
        return w;
    }
    return 0;
}

static FsysWork* _fsysGetNewWork_Sub(s32 flag) {
    FsysWork* ret = 0;
    FsysWork* w;
    u32 i;

    i = _fsysWorkIndex;
    while (ret == 0) {
        w = &_fsysWork[i];
        switch (w->status) {
        case 12:
            if (flag == 1) {
                break;
            }
        case -999:
        case 0:
        case 1:
            ret = w;
            if (w->header != 0) {
                _fsysMemFreeHeader(w);
            }
            break;
        }
        i++;
        if (i >= _fsysWorkMax) {
            i = 0;
        }
        if (i == _fsysWorkIndex) {
            break;
        }
    }
    _fsysWorkIndex = i;
    return ret;
}

static FsysWork* _fsysGetWork(u32 id, u8 flag) {
    FsysWork* w = _fsysWork;
    u32 i;

    for (s32 i = 0; i < _fsysWorkMax; w++, i++) {
        if (flag == 1) {
            switch (w->status) {
            case 0:
            case 12:
            case -999:
                continue;
            }
        } else if (w->status == 0) {
            continue;
        }
        if (id == w->id) {
            return &_fsysWork[i];
        }
    }
    return 0;
}

FsysWork* _fsysInfo2Work(u32 handle) {
    FsysWork* w;
    FsysHeader* header;
    FsysResHeader* res;
    u32 i;
    s32 j;

    for (i = 0; i < _fsysWorkMax; i++) {
        w = &_fsysWork[i];
        switch (w->status) {
        case 0:
        case 1:
        case 12:
        case -999:
            continue;
        }
        if (w->file == handle) {
            return w;
        }
        header = _fsysGetHeader(w);
        if (header != 0 && (header->flags & 1)) {
            for (j = 0; j < header->resNum; j++) {
                res = _fsysGetResHeader(w, j);
                if (res != 0 && res->id38 == handle) {
                    return w;
                }
            }
        }
    }
    return 0;
}

static u8 _fsysInitTOC(void) {
    s32 size;
    u32 file;
    FsysGroup* g;
    u32 i;

    file = GSdvdOpen("gsfsys.toc");
    if (file == 0) {
        return 0;
    }
    size = (GSdvdGetLength(file) + 0x1F) & ~0x1F;
    _fsysTOC = (FsysTOC*)_fsysDoMalloc(size);
    if (_fsysTOC == 0) {
        return 0;
    }
    if (GSdvdRead(file, _fsysTOC, size, 0) < 0) {
        GSdvdClose(file);
        return 0;
    }
    GSdvdClose(file);
    g = (FsysGroup*)((u8*)_fsysTOC + _fsysTOC->groupOffset);
    for (i = 0; i < _fsysTOC->count; i++) {
        g->name = (char*)((u32)g->name + (u32)_fsysTOC);
        g->flags = 0;
        g++;
    }
    return 1;
}

static void* _fsysDoMalloc(u32 size) {
    return GSmemAllocAlign(size, 0x20);
}

}
