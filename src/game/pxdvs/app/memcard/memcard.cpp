#include <dolphin/types.h>
#include <game/gcptr.h>
#include <game/statusval.h>
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif

#pragma pool_strings off
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
typedef void (*CARDCallback)(s32 chan, s32 result);
struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
};
struct CARDStat {
    char fileName[32];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
    u32 offsetBanner;
    u32 offsetBannerTlut;
    u32 offsetIcon[8];
    u32 offsetIconTlut;
    u32 offsetData;
};
struct Gamedata;
struct GamedataSave;
struct Hero;
struct OSCalendarTime;
typedef s64 OSTime;

extern "C" {
void GSthreadSwitch(void);
void CARDInit(void);
void winMsgClose(bool flag);
void GSgappTerminate(int id);
void GSmemFree(void* ptr);
void* GSmemAllocAlign(u32 size, u32 align);
int GSgappCreate(s32 type, u8 priority, void* arg, void* func);
void* savedataGetStatus(void* save, s32 kind);
u32 HSD_Rand(void);
void menuCBBios_RuleEditSaveON(int);
void* memset(void*, int, u32);
void* memcpy(void*, const void*, u32);
s32 winMsgOpen(s8 type, s32 msg, bool a, bool b);
void msgctrlSetValue(s32 id, GCuptr value);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
void GSsndPlay(s32, s32, s32);
StatusU32 gamedatasaveGetStatus(void* ptr, u32 kind);
void gamedatasaveSetStatus(void* ptr, u32 kind, u32 value);
}

struct MemcardStatus {
    volatile s32 kind;
    volatile s32 msgType;
    s32 result;
    s32 state;
    s32 resumeState;
    s32 arg14;
    s32 sectorSize;
    s32 memSize;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 delay;
    u32 writeTicks;
    u8 cbDone;
    u8 f3d;
    u8 f3e;
    u8 f3f;
    u8 f40;
    u8 valid;
    u8 pad42[0x48 - 0x42];
    u64 serial;
    void* buf50;
    void* buf54;
    void* savedata;
    s32 f5c;
    s32 f60;
    int gapp;
    u8 pad68[0x8c - 0x68];
    CARDFileInfo fileInfo;
    CARDStat stat;
};

static u8 _memcardStatusBuf[0x210] __attribute__((aligned(8)));
static u16 _memcard_encrypt_key[4];
static u8 _memcardInitializeFlag;
static u8 _memcard_new_saveDataCrateFlag;
static MemcardStatus* _memcardStatusPtr;
static u8 _memcard_anySaveOFF_Flag;
static u8 _memcard_gba2mode;
static void _memcardJobMain(u32, u32);
extern "C" {
void memcardFinalizeTask(void);
s32 memcardGetTaskResult(void);
void memcardSetupTask(s32 kind, s32 type, s32 arg);
struct GamedataSave;
u64 gamedatasaveBiosGetMemcardID(GamedataSave* save);
GamedataSave* gamedatasaveBiosGetPtr(void* gamedata);
}

enum MEMCARD_MSGTYPE {
    MSG_M13 = -13, MSG_M9 = -9, MSG_M8 = -8, MSG_M6 = -6, MSG_M5 = -5, MSG_M4 = -4, MSG_M3 = -3, MSG_M2 = -2,
    MSG_0 = 0, MSG_1, MSG_2, MSG_3, MSG_4, MSG_5, MSG_6, MSG_7, MSG_8, MSG_9, MSG_10,
    MSG_11, MSG_12, MSG_13, MSG_14, MSG_15, MSG_16, MSG_17, MSG_18, MSG_19
};
struct Gamedata {
    u8 _draft[1];
};
struct Hero {
    u8 _draft[1];
    void setRestertPos();
    static Hero* getHeroPtr();
};
struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
};

extern "C" {
s32 CARDCancel(CARDFileInfo* fileInfo);
s32 CARDCheckAsync(s32 chan, CARDCallback callback);
s32 CARDClose(CARDFileInfo* fileInfo);
s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo, CARDCallback callback);
s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);
s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo* fileInfo);
s32 CARDFormatAsync(s32 chan, CARDCallback callback);
s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed);
s32 CARDGetAttributes(s32 chan, s32 fileNo, u8* attr);
s32 CARDGetResultCode(s32 chan);
s32 CARDGetSerialNo(s32 chan, u64* serialNo);
s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat);
s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback, CARDCallback attachCallback);
s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize);
s32 CARDReadAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset, CARDCallback callback);
s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat, CARDCallback callback);
s32 CARDUnmount(s32 chan);
s32 CARDWriteAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset, CARDCallback callback);
u8 GSgfxResetDisable();
void GSgfxResetRestore(u8);
asm OSTime OSGetTime(void);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td);
s32 PKJB_ReturnTitle(s32 ch);
#ifdef __MWERKS__
s32 __copy(void*, u16*, s32);
#else
#define __copy(to, from, n) (memcpy((to), (from), (u32)(n)))
#endif
u32 floorGetNextFloorID();
u8 floorMakeSaveData(u8** data, u32* size);
void floorMemoryCardSaveCallback(void);
u32 fn_801CC508();
void gamedatasaveBiosSetMemcardID(GamedataSave* save, u64 value);
s32 gbaCommandChangePokemonEnd(s32);
bool gbaCommandIsConnected(s32 gba);
s32 pokecoloGetCountryCode(void);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dst, const char* src);
#ifndef __MWERKS__
extern "C" u8* PortXD_GetDolTable(const char* name);
#endif
extern s32 jtbl_4196;
}
extern "C++" {
static void _memcardCallback(s32, s32);
static u32 _memcardCardOpen();
static void _memcardDuplicateSaveData_multi(void* p0);
static s32 _memcardExamineDataPack();
static s32 _memcardExamineHeader();
static void _memcardJobMain(u32 p0, u32 p1);
static s32 _memcardMergeDataPack();
}

#ifdef __MWERKS__
static const u8 _memcardBannerImage[0x1800] ATTRIBUTE_ALIGN(4) = {
#include "memcard/banner.inc"
};
static const u8 _memcardIconImage[0x2200] ATTRIBUTE_ALIGN(4) = {
#include "memcard/icon.inc"
};
#endif
extern "C" {
#ifdef __MWERKS__
extern s32 jtbl_3110;
#else
static const s32 jtbl_3110[4] = { 0x43, 0x29, 0x17, 0x13 };
#endif
}

static inline void _memcardKeyStep(u16* key)
{
    u32 primes[4] = {0x43, 0x29, 0x17, 0x13};
    u16 v[4];
    int j;
    for (j = 0; j < 4; j++) {
        v[j] = key[j];
    }
    for (j = 0; j < 4; j++) {
        v[j] = v[j] + primes[j];
    }
    key[0] = (((((((v[1] * 0x10) & 0xF0 & ~0xF) | (v[0] & 0xF)) & ~0xF00) | ((v[2] << 8) & 0xF00)) & ~0xF000) | ((v[3] << 0xC) & 0xF000));
    key[1] = ((((((v[1] & 0xF0 & ~0xF) | ((v[0] >> 4) & 0xF)) & ~0xF00) | ((v[2] << 4) & 0xF00)) & ~0xF000) | ((v[3] << 8) & 0xF000));
    key[2] = (((((((s32)(v[0] & 0xF00) >> 8) | ((s32)(v[1] & 0xF00) >> 4)) & ~0xF00) | (v[2] & 0xF00)) & ~0xF000) | ((v[3] << 4) & 0xF000));
    key[3] = (((((((v[0] >> 0xC) & 0xF & ~0xF0) | ((v[1] >> 8) & 0xF0)) & ~0xF00) | ((v[2] >> 4) & 0xF00)) & ~0xF000) | (v[3] & 0xF000));
}

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE type);
static void* _memcardGetMultiSaveDataToSTRUCT(void* data, s32 idx);
static void _memcardStoreSaveData_multi(void* data);
static void _memcardDuplicateSaveData_multi(void* data);
static u8 _memcard_Decryption(void* data);
static void _memcard_Encryption(void* data);

extern "C" {

void memcardInitialize(void)
{
    if (!_memcardInitializeFlag) {
        u32 lo;
        u16 hi;
        CARDInit();
        lo = HSD_Rand();
        hi = HSD_Rand();
        _memcardStatusPtr = (MemcardStatus*)(_memcardStatusBuf + (((hi << 16) | lo) & 0xf8));
        _memcardStatusPtr->kind = 0;
        _memcardStatusPtr->buf50 = 0;
        _memcardStatusPtr->buf54 = 0;
        _memcardStatusPtr->f2c = 0;
        _memcardInitializeFlag = 1;
    }
}
}

extern "C" {

s32 memcardTaskCall(s32 kind, s32 type, s32 arg)
{
    s32 result;
    if (kind == 1) {
        memset(savedataGetStatus(0, 0), 0, 0x27fd0);
        menuCBBios_RuleEditSaveON(0);
    }
    if (kind == 0xe) {
        kind = 4;
        _memcard_anySaveOFF_Flag = 1;
    } else {
        _memcard_anySaveOFF_Flag = 0;
    }
    memcardSetupTask(kind, type, arg);
    do {
        GSthreadSwitch();
        result = memcardGetTaskResult();
    } while (result == 0);
    memcardFinalizeTask();
    return result;
}
}

extern "C" {

void memcardSetupTask(s32 kind, s32 type, s32 arg)
{
    if (_memcardStatusPtr->kind != 0) {
        do {
            GSthreadSwitch();
        } while (!memcardGetTaskResult());
        memcardFinalizeTask();
    }
    if (type == 0) {
        type = 2;
    }
    _memcardStatusPtr->kind = kind;
    _memcardStatusPtr->arg14 = arg;
    _memcardStatusPtr->f5c = type;
    _memcardStatusPtr->result = 0;
    _memcardStatusPtr->state = 0;
    _memcardStatusPtr->msgType = 0;
    _memcardStatusPtr->f3e = 0;
    _memcardStatusPtr->buf50 = GSmemAllocAlign(0x28400, 0x20);
    _memcardStatusPtr->buf54 = GSmemAllocAlign(0xa000, 0x20);
    _memcardStatusPtr->gapp = GSgappCreate(1, 0x17, 0, (void*)_memcardJobMain);
    _memcardStatusPtr->savedata = savedataGetStatus(0, 0);
}
}

extern "C" {

s32 memcardGetTaskResult(void)
{
    if (_memcardStatusPtr->state == 0x30) {
        _memcardStatusPtr->msgType = _memcardMsgOpen((MEMCARD_MSGTYPE)_memcardStatusPtr->msgType);
        _memcardStatusPtr->state = _memcardStatusPtr->resumeState;
    }
    if (_memcardStatusPtr->state != 0x32) {
        return 0;
    }
    return _memcardStatusPtr->result;
}
}

extern "C" {

u8 memcardIsMemCardValid(void)
{
    return _memcardStatusPtr->valid;
}
}

extern "C" {

bool memcardCheckTaskWaitGBA(void)
{
    return _memcardStatusPtr->state == 0x31;
}
}

extern "C" {

void memcardUnlockWaitGBA(u8 flag)
{
    if (_memcardStatusPtr->state == 0x31 && flag) {
        u32 lo, hi;
        _memcardStatusPtr->state = _memcardStatusPtr->resumeState;
        lo = HSD_Rand();
        hi = HSD_Rand();
        _memcardStatusPtr->delay = ((hi << 16) | lo) % 60;
        _memcardStatusPtr->delay++;
        u16 r = HSD_Rand();
        _memcardStatusPtr->delay += r % 60;
    } else {
        _memcardStatusPtr->msgType = 0xf;
        _memcardStatusPtr->state = 0x2b;
    }
}
}

extern "C" {

void memcardFinalizeTask(void)
{
    if (_memcardStatusPtr->kind != 0) {
        if (_memcardStatusPtr->kind != 8) {
            winMsgClose(1);
        }
        GSgappTerminate(_memcardStatusPtr->gapp);
        GSmemFree(_memcardStatusPtr->buf54);
        _memcardStatusPtr->buf54 = 0;
        GSmemFree(_memcardStatusPtr->buf50);
        _memcardStatusPtr->buf50 = 0;
    }
    _memcardStatusPtr->kind = 0;
}
}

extern "C" {

void* memcardMemAllocForSavedata(void)
{
    return GSmemAllocAlign(0x27fd0, 0x20);
}
}

extern "C" {

void* memcardMemFreeForSavedata(void* ptr)
{
    GSmemFree(ptr);
    return 0;
}
}

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE type)
{
    u8 ask = 0;
    u8 retry = 0;
    int initial;
    int msg;
    switch (type) {
    case MSG_0:
        return 0;
    case MSG_1:
        msg = 0x6a;
        break;
    case MSG_2:
        switch (_memcardStatusPtr->kind) {
        case 5:
        case 6:
        case 7:
        case 13:
            msg = 0x6c;
            break;
        default:
            msg = 0x90;
            break;
        }
        break;
    case MSG_3:
        msg = 0x84;
        break;
    case MSG_4:
        msg = 0x73;
        break;
    case MSG_5:
        msg = 0x7b;
        break;
    case MSG_6:
        msg = 0x83;
        ask = 1;
        initial = 0;
        break;
    case MSG_7:
        msg = 0x71;
        ask = 1;
        initial = 0;
        retry = 1;
        break;
    case MSG_8:
        msg = 0x7a;
        ask = 1;
        initial = 1;
        break;
    case MSG_9:
        msg = 0x74;
        break;
    case MSG_10:
        switch (_memcardStatusPtr->kind) {
        case 5:
        case 6:
        case 7:
        case 13:
            msg = 0x6d;
            break;
        default:
            msg = 0x91;
            break;
        }
        GSsndPlay(0x1d, 0, 0);
        break;
    case MSG_11:
        msg = 0x85;
        break;
    case MSG_12:
        msg = 0x81;
        GSsndPlay(0x1d, 0, 0);
        break;
    case MSG_13:
        msg = 0x79;
        break;
    case MSG_14:
        msg = 0x9b;
        break;
    case MSG_15:
        switch (_memcardStatusPtr->kind) {
        case 5:
        case 6:
        case 7:
        case 13:
            msg = 0x9b;
            break;
        default:
            msg = 0x97;
            break;
        }
        break;
    case MSG_16:
        msg = 0x72;
        break;
    case MSG_17:
        msg = 0x7c;
        if (_memcardStatusPtr->kind != 2) {
            winMsgOpen((s8)_memcardStatusPtr->f5c, 0x7c, 1, 1);
            msg = 0x80;
        }
        break;
    case MSG_18:
        msg = 0x7d;
        break;
    case MSG_M2:
        msg = 0x77;
        break;
    case MSG_M3:
        msg = 0x70;
        break;
    case MSG_M4:
        msg = 0x6f;
        break;
    case MSG_M5:
        msg = 0x76;
        break;
    case MSG_M13:
    case MSG_M6:
        switch (_memcardStatusPtr->kind) {
        case 1:
        case 2:
            msg = 0x7e;
            if (_memcardStatusPtr->f60 == 0x32) {
                break;
            }
        default:
            msg = 0x6e;
            break;
        }
        break;
    case MSG_M9:
    case MSG_M8:
        msg = 0x78;
        msgctrlSetValue(0x2f, 0x2b);
        break;
    case MSG_19:
        winMsgOpen((s8)_memcardStatusPtr->f5c, 0x7c, 1, 1);
        msg = 0x80;
        break;
    default:
        msg = 0x6e;
        break;
    }
    winMsgOpen((s8)_memcardStatusPtr->f5c, msg, 1, 1);
    if (ask) {
        if (menuSubOpenYesNo(0, 0x3c, 0xaa, initial)) {
            ask = 0;
        } else {
            ask = 1;
            if (retry) {
                winMsgOpen((s8)_memcardStatusPtr->f5c, 0xf3, 1, 1);
                if (menuSubOpenYesNo(0, 0x3c, 0xaa, 1)) {
                    ask = 0;
                } else {
                    ask = 1;
                }
            }
        }
    }
    return ask;
}

static void* _memcardGetMultiSaveDataToSTRUCT(void* data, s32 idx)
{
    u8* p = (u8*)data;
    u32 hi, lo;
    u32 ret = (u32)p + 0xa0;
    switch (idx) {
    case 1:
        hi = *(u16*)(p + 0x3a);
        lo = *(u16*)(p + 0x38);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 2:
        hi = *(u16*)(p + 0x3e);
        lo = *(u16*)(p + 0x3c);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 3:
        hi = *(u16*)(p + 0x42);
        lo = *(u16*)(p + 0x40);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 23:
        hi = *(u16*)(p + 0x5a);
        lo = *(u16*)(p + 0x58);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 10:
        hi = *(u16*)(p + 0x46);
        lo = *(u16*)(p + 0x44);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 11:
        hi = *(u16*)(p + 0x4a);
        lo = *(u16*)(p + 0x48);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 12:
        hi = *(u16*)(p + 0x4e);
        lo = *(u16*)(p + 0x4c);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 14:
        hi = *(u16*)(p + 0x52);
        lo = *(u16*)(p + 0x50);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 15:
        hi = *(u16*)(p + 0x56);
        lo = *(u16*)(p + 0x54);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 16:
        hi = *(u16*)(p + 0x5e);
        lo = *(u16*)(p + 0x5c);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 22:
        hi = *(u16*)(p + 0x76);
        lo = *(u16*)(p + 0x74);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 17:
        hi = *(u16*)(p + 0x62);
        lo = *(u16*)(p + 0x60);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 18:
        hi = *(u16*)(p + 0x66);
        lo = *(u16*)(p + 0x64);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 19:
        hi = *(u16*)(p + 0x6a);
        lo = *(u16*)(p + 0x68);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 20:
        hi = *(u16*)(p + 0x6e);
        lo = *(u16*)(p + 0x6c);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    case 21:
        hi = *(u16*)(p + 0x72);
        lo = *(u16*)(p + 0x70);
        ret = (hi << 16) + ret;
        ret = lo + ret;
        break;
    }
    return (void*)ret;
}

static void _memcardStoreSaveData_multi(void* data)
{
    void* src;
    void* dst;
    u32 n;
    u8* extra;
    void* tail;
    void* tail2;
    void* tail3;
    src = _memcardGetMultiSaveDataToSTRUCT(data, 1);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 1);
    n = *(u16*)((u8*)data + 0x18);
    if (n > 0x88) {
        n = 0x88;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 2);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 2);
    n = *(u16*)((u8*)data + 0x1a);
    if (n > 0x978) {
        n = 0x978;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 3);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 3);
    n = *(u16*)((u8*)data + 0x80) << 16;
    n += *(u16*)((u8*)data + 0x1c);
    if (n > 0xbc50) {
        n = 0xbc50;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 10);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 10);
    n = *(u16*)((u8*)data + 0x1e);
    if (n > 0x4a) {
        n = 0x4a;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 11);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 11);
    n = *(u16*)((u8*)data + 0x20);
    if (n > 0xcc) {
        n = 0xcc;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 12);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 12);
    n = *(u16*)((u8*)data + 0x22);
    if (n > 0x1774) {
        n = 0x1774;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 14);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 14);
    n = *(u16*)((u8*)data + 0x24);
    if (n > 0x364) {
        n = 0x364;
    }
    memcpy(dst, src, n);
    src = _memcardGetMultiSaveDataToSTRUCT(data, 15);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 15);
    n = *(u16*)((u8*)data + 0x26);
    if (n > 0x2400) {
        n = 0x2400;
    }
    memcpy(dst, src, n);
    extra = (u8*)_memcardGetMultiSaveDataToSTRUCT(data, 0x17);
    n = *(u16*)((u8*)data + 0x28);
    if (n == 0x6b4) {
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 4), extra, *(u16*)((u8*)data + 0x78));
        extra += *(u16*)((u8*)data + 0x78);
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 5), extra, *(u16*)((u8*)data + 0x7a));
        extra += *(u16*)((u8*)data + 0x7a);
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 6), extra, *(u16*)((u8*)data + 0x7c));
        extra += *(u16*)((u8*)data + 0x7c);
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 0x18), extra, *(u16*)((u8*)data + 0x7e));
        extra += *(u16*)((u8*)data + 0x7e);
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 0x1b), extra, *(u16*)((u8*)data + 0x82));
    } else {
        memcpy(savedataGetStatus(_memcardStatusPtr->savedata, 0x17), extra, n);
    }
    tail = _memcardGetMultiSaveDataToSTRUCT(data, 16);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 16);
    n = *(u16*)((u8*)data + 0x2a);
    if (n > 0xb) {
        n = 0xb;
    }
    memcpy(dst, tail, n);
    tail2 = _memcardGetMultiSaveDataToSTRUCT(data, 22);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 22);
    n = *(u16*)((u8*)data + 0x36);
    if (n > 0xc800) {
        n = 0xc800;
    }
    memcpy(dst, tail2, n);
    tail3 = _memcardGetMultiSaveDataToSTRUCT(data, 21);
    dst = savedataGetStatus(_memcardStatusPtr->savedata, 21);
    n = *(u16*)((u8*)data + 0x34);
    if (n > 0x2298) {
        n = 0x2298;
    }
    memcpy(dst, tail3, n);
    _memcardGetMultiSaveDataToSTRUCT(data, 0x11);
    _memcardGetMultiSaveDataToSTRUCT(data, 0x12);
    _memcardGetMultiSaveDataToSTRUCT(data, 0x13);
    _memcardGetMultiSaveDataToSTRUCT(data, 0x14);
}

static void _memcardCallback(s32, s32)
{
    _memcardStatusPtr->cbDone = 1;
}

struct _MemcardSector {
    s32 v;
    u8 pad[0x1fc];
};

static inline u8 _memcardCheckSum(u8* pack)
{
    u8* data = pack + 8;
    s32 sum = pack[0] + pack[1];
    sum += pack[2];
    sum += pack[3];
    sum += pack[4];
    sum += pack[5];
    sum += pack[6];
    sum += pack[7];
    if (*(u16*)(pack + 0x20) == 0x88) {
        if (sum == (s32)gamedatasaveGetStatus(_memcardGetMultiSaveDataToSTRUCT(data, 1), 0xd)) {
            return 1;
        }
        return 0;
    }
    return 1;
}

static s32 _memcardExamineDataPack()
{
    u8* pack = (u8*)_memcardStatusPtr->buf50;
    u8 ok = _memcard_Decryption(pack + 8);
    if (ok) {
        ok = _memcardCheckSum(pack);
    }
    if (ok) {
        _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
    }
    if (ok) {
        if (_memcardStatusPtr->kind != 3) {
            _memcardStatusPtr->f2c = *(s32*)(pack + 4);
            if (_memcardStatusPtr->f30 > _memcardStatusPtr->f2c) {
                _memcardStatusPtr->f2c = _memcardStatusPtr->f30;
                _memcardStatusPtr->msgType = 5;
                switch (_memcardStatusPtr->kind) {
                case 1:
                case 2:
                    _memcardStoreSaveData_multi(pack + 8);
                    _memcardStatusPtr->resumeState = 0x25;
                    break;
                default:
                    _memcardStatusPtr->resumeState = 0x24;
                    break;
                }
                return 0x30;
            }
        }
        switch (_memcardStatusPtr->kind) {
        case 1:
        case 2:
        case 3:
            _memcardStoreSaveData_multi(pack + 8);
            _memcardStatusPtr->msgType = 0xc;
            _memcardStatusPtr->result = 3;
            if (_memcardStatusPtr->f40) {
                return 0x11;
            }
            return 0x2c;
        default:
            return 0x24;
        }
    }
    s32 rf_t = _memcardStatusPtr->f20;
    s32 idx = rf_t;
    ((_MemcardSector*)((u8*)_memcardStatusPtr->buf50 + 0x28004))[idx].v = 0;
    return 0x1f;
}

static inline bool _memcardHeaderValid(u8* h)
{
    u8 ok = 0;
    if (h[0] == 1 && h[1] == 1 && h[2] == 1) {
        ok = 1;
    }
    return ok;
}

static inline void _memcardDecryptHeader(u8* pack)
{
    int i;
    int k;
    int n = 4;
    int off = 8;
    int cnt = 0x3E;
    u16* d = (u16*)(pack + 8);
    _memcard_encrypt_key[0] = *(u16*)(pack + 8);
    _memcard_encrypt_key[1] = *(u16*)(pack + 10);
    _memcard_encrypt_key[2] = *(u16*)(pack + 12);
    _memcard_encrypt_key[3] = *(u16*)(pack + 14);
    for (i = 4; i < 0xFC; i += 4) {
        for (k = 0; k < 4; k++) {
            d[i + k] -= _memcard_encrypt_key[k];
        }
        _memcardKeyStep(_memcard_encrypt_key);
    }
}

static s32 _memcardExamineHeader()
{
    s32 bestCount = 0;
    s32 best = -1;
    s32 i;
    s32 off = 0x28000;
    for (i = 0; i < 2; i++, off += 0x200) {
        u8 ok = 0;
        u8* h = (u8*)_memcardStatusPtr->buf50 + off;
        if (h[0] == 1 && h[1] == 1 && h[2] == 1) {
            ok = 1;
        }
        if (ok == 0) {
            _memcardStatusPtr->msgType = 0x13;
            return 0x2B;
        }
        if (*(s32*)(h + 4) > bestCount) {
            bestCount = *(s32*)(h + 4);
            best = i;
            if (*(s32*)(h + 4) > _memcardStatusPtr->f30) {
                _memcardStatusPtr->f30 = *(s32*)(h + 4);
            }
        }
    }
    _memcardStatusPtr->f20 = best;
    switch (_memcardStatusPtr->kind) {
    case 10:
    case 11:
        _memcardDuplicateSaveData_multi((u8*)_memcardStatusPtr->buf50 + 8);
        _memcardStatusPtr->f2c = _memcardStatusPtr->f30;
        return 0x25;
    case 1:
    case 2:
    case 3:
    case 5:
    case 7:
    case 9:
    case 13:
        if (best == -1) {
            if (_memcardStatusPtr->f30 > 0) {
                switch (_memcardStatusPtr->kind) {
                case 3:
                    break;
                case 9:
                    return 0xB;
                default:
                    _memcardStatusPtr->msgType = 0x11;
                    return 0x2B;
                }
            }
            switch (_memcardStatusPtr->kind) {
            case 1:
            case 2:
            case 3:
                _memcardStatusPtr->msgType = 0xC;
                _memcardStatusPtr->result = 1;
                if (_memcardStatusPtr->f40 != 0) {
                    return 0x11;
                }
                return 0x2C;
            }
            memset(_memcardStatusPtr->buf50, 0, 0x28000);
            _memcardDuplicateSaveData_multi((u8*)_memcardStatusPtr->buf50 + 8);
            _memcard_new_saveDataCrateFlag = 1;
            _memcardStatusPtr->f2c = 0;
            _memcard_new_saveDataCrateFlag = 0;
            _memcardStatusPtr->f20 = -1;
            return 0x24;
        } else {
            return 0x20;
        }
        break;
    case 4:
    case 6:
    case 8:
        if (best != -1 && bestCount <= _memcardStatusPtr->f2c) {
            u8* pack = (u8*)_memcardStatusPtr->buf50 + 0x30000 - 0x8000 + (best << 9);
            u64 myId;
            u64 saveId;
            myId = gamedatasaveBiosGetMemcardID(gamedatasaveBiosGetPtr(savedataGetStatus(0, 1)));
            _memcardDecryptHeader(pack);
            if (pack + 8 == 0) {
                saveId = gamedatasaveBiosGetMemcardID(gamedatasaveBiosGetPtr(savedataGetStatus(pack + 8, 1)));
            } else {
                saveId = gamedatasaveBiosGetMemcardID((GamedataSave*)((u8*)_memcardGetMultiSaveDataToSTRUCT(pack + 8, 1) + 8));
            }
            if (myId == saveId) {
                if (_memcardStatusPtr->kind == 6) {
                    _memcardStatusPtr->f20 = best;
                    return 0x20;
                }
                _memcardDuplicateSaveData_multi((u8*)_memcardStatusPtr->buf50 + 8);
                return 0x25;
            }
        }
    default:
        _memcardStatusPtr->msgType = 0x13;
        return 0x2B;
    }
}
extern "C" {
u32 fn_801CC508() {
#ifndef __MWERKS__
    const u8* _memcardBannerImage = PortXD_GetDolTable("_memcardBannerImage");
    const u8* _memcardIconImage = PortXD_GetDolTable("_memcardIconImage");
#endif
    OSCalendarTime ct;
    s8* buf;
    s32* p;
    int i;

    OSTicksToCalendarTime(OSGetTime(), &ct);
    buf = (s8*)_memcardStatusPtr->buf50;
    memset(buf, 0, 0x6000);
    switch (pokecoloGetCountryCode()) {
    case 0:
        strcpy((char*)buf, "\x83\x7C\x83\x50\x83\x82\x83\x93\x82\x77\x82\x63");
        strcpy((char*)buf + 0x20, "\x83\x5A\x81\x5B\x83\x75\x83\x74\x83\x40\x83\x43\x83\x8B Yy/Mm/Dd");
        buf[0x2F] = ct.year / 10 % 10 + '0';
        buf[0x30] = ct.year % 10 + '0';
        buf[0x32] = (ct.mon + 1) / 10 % 10 + '0';
        buf[0x33] = (ct.mon + 1) % 10 + '0';
        buf[0x35] = ct.mday / 10 % 10 + '0';
        buf[0x36] = ct.mday % 10 + '0';
        break;
    case 1:
    case 2:
        strcpy((char*)buf, "POKeMON XD");
        strcpy((char*)buf + 0x20, "SAVE FILE Mm/Dd/20Yy");
        buf[3] = 0xE9;
        buf[0x32] = ct.year / 10 % 10 + '0';
        buf[0x33] = ct.year % 10 + '0';
        buf[0x2A] = (ct.mon + 1) / 10 % 10 + '0';
        buf[0x2B] = (ct.mon + 1) % 10 + '0';
        buf[0x2D] = ct.mday / 10 % 10 + '0';
        buf[0x2E] = ct.mday % 10 + '0';
        break;
    }
    memcpy(buf + 0x40, _memcardBannerImage, 0x1800);
    memcpy(buf + 0x1840, _memcardIconImage, 0x2200);
    p = (s32*)buf;
    for (i = 0; i < 0xE90; i++) {
        *(s32*)(buf + 0x3A40) += p[i];
    }
    return 0x12;
}
extern "C++" {
struct MemcardSave1 {
    s32 a;
    f64 d[7];
    u16 h;
    s32 w[16];
};
struct MemcardPokemon {
    u32 data[0xC4 / 4];
    MemcardPokemon& operator=(const MemcardPokemon& o) {
        memcpy(this, &o, sizeof(MemcardPokemon));
        return *this;
    }
};
struct MemcardBoxName {
    u16 data[9];
};
struct MemcardBox {
    MemcardBoxName name;
    MemcardPokemon pokemon[30];
};
struct MemcardBlock3AC {
    u32 data[0x3AC / 4];
};
struct MemcardBlock40 {
    u32 data[0x40 / 4];
};
struct MemcardPcBoxes {
    MemcardBox box[8];
    MemcardBlock3AC block3AC;
    u32 tailA;
    MemcardBlock40 tailB;
};
struct MemcardBlock4 {
    u16 data[2];
};
struct MemcardSave10 {
    MemcardBlock40 a;
    u16 a2;
    MemcardBlock4 b;
    u8 c;
    u8 d;
    u16 e;
};
struct MemcardSave11 {
    u8 a;
    u8 b;
    u16 c;
    u32 d;
    MemcardPokemon pokemon;
};
struct MemcardBlock1770 {
    u32 data[0x1770 / 4];
};
struct MemcardSave12 {
    u16 a;
    MemcardBlock1770 b;
};
struct MemcardBlock360 {
    u32 data[0x360 / 4];
};
struct MemcardSave14 {
    MemcardBlock360 a;
    u8 b;
};
struct MemcardSave15 {
    u32 data[0x2400 / 4];
};
struct MemcardBlock20 {
    u32 data[0x20 / 4];
};
struct MemcardBlock80 {
    u32 data[0x80 / 4];
};
struct MemcardBlock600 {
    u32 data[0x600 / 4];
};
struct MemcardBlock14 {
    u32 data[0x14 / 4];
};
struct MemcardSave23 {
    MemcardBlock20 a;
    MemcardBlock80 b;
    MemcardBlock600 c;
    MemcardBlock14 d;
};
struct MemcardTeam {
    MemcardPokemon pokemon0;
    MemcardPokemon pokemon1;
    MemcardPokemon pokemon2;
    MemcardPokemon pokemon3;
    MemcardPokemon pokemon4;
    u8 flag;
};
struct MemcardSave21 {
    MemcardTeam team[9];
};

#define MEMCARD_SECTION(data, off) ((u8*)(data) + 0xA0 + (off))
#define MEMCARD_SET_OFFSET(h, i, off) ((h)[i] = (off), (h)[(i) + 1] = (off) >> 16)

static void _memcardDuplicateSaveData_multi(void* data)
{
    u16* d = (u16*)data;
    u8* base;
    u32 off;
    s16 left;
    s16 pick;
    s8* slot;
    s16 j;
    int i;
    int k;
    s8 order[16];
    u32 floorSize;
    u8* floorData;

    if (_memcardStatusPtr->kind == 0xB) {
        gamedatasaveSetStatus(0, 5, floorGetNextFloorID());
    }
    {
        u16* key = _memcard_encrypt_key;
        for (i = 0; i < 4; i++) {
            *key++ = HSD_Rand();
        }
    }
    for (i = 0; i < 0x13FE8; i += 4) {
        for (k = 0; k < 4; k++) {
            d[i + k] += _memcard_encrypt_key[k];
        }
        _memcardKeyStep(_memcard_encrypt_key);
    }
    d[0x18 / 2] = 0x88;
    d[0x1A / 2] = 0x978;
    d[0x1C / 2] = 0xBC50;
    d[0x80 / 2] = 0;
    d[0x1E / 2] = 0x4A;
    d[0x20 / 2] = 0xCC;
    d[0x22 / 2] = 0x1774;
    d[0x24 / 2] = 0x364;
    d[0x26 / 2] = 0x2400;
    d[0x28 / 2] = 0x6B4;
    d[0x2A / 2] = 0xB;
    d[0x36 / 2] = 0xC800;
    d[0x2C / 2] = 0x400;
    d[0x2E / 2] = 0x800;
    d[0x30 / 2] = 0x1000;
    d[0x32 / 2] = 0x2000;
    d[0x34 / 2] = 0x2298;
    d[0] = HSD_Rand();
    d[1] = HSD_Rand();
    d[2] = HSD_Rand();
    d[3] = HSD_Rand();
    for (j = 0; j < 15; j++) {
        order[j] = j + 1;
    }
    d[0x38 / 2] = 0;
    order[15] = -1;
    d[0x3A / 2] = 0;
    *(MemcardSave1*)((u8*)data + 0xA0) = *(MemcardSave1*)savedataGetStatus(0, 1);
    off = 0xA0;
    left = 15;
    while (left != 0) {
        pick = (u16)HSD_Rand() % left;
        slot = &order[pick];
        switch (*slot) {
        case 1:
            if (_memcardStatusPtr->kind != 8 && _memcardStatusPtr->kind != 0xD && _memcardStatusPtr->kind != 7 && !_memcard_anySaveOFF_Flag) {
                Hero::getHeroPtr()->setRestertPos();
            }
            MEMCARD_SET_OFFSET(d, 0x3C / 2, off);
            base = MEMCARD_SECTION(data, off);
            memcpy(base, savedataGetStatus(0, 2), 0x978);
            off += 0x990;
            break;
        case 2:
            MEMCARD_SET_OFFSET(d, 0x40 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardPcBoxes*)base = *(MemcardPcBoxes*)savedataGetStatus(0, 3);
            off += 0xBC60;
            break;
        case 3:
            MEMCARD_SET_OFFSET(d, 0x44 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave10*)base = *(MemcardSave10*)savedataGetStatus(0, 10);
            off += 0x60;
            break;
        case 4:
            MEMCARD_SET_OFFSET(d, 0x48 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave11*)base = *(MemcardSave11*)savedataGetStatus(0, 11);
            off += 0xE0;
            break;
        case 5:
            MEMCARD_SET_OFFSET(d, 0x4C / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave12*)base = *(MemcardSave12*)savedataGetStatus(0, 12);
            off += 0x1790;
            break;
        case 6:
            MEMCARD_SET_OFFSET(d, 0x50 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave14*)base = *(MemcardSave14*)savedataGetStatus(0, 14);
            off += 0x380;
            break;
        case 7:
            MEMCARD_SET_OFFSET(d, 0x54 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave15*)base = *(MemcardSave15*)savedataGetStatus(0, 15);
            off += 0x2410;
            break;
        case 8:
            MEMCARD_SET_OFFSET(d, 0x58 / 2, off);
            d[0x78 / 2] = (GCuptr)savedataGetStatus(0, 7) * 4;
            d[0x7A / 2] = (GCuptr)savedataGetStatus(0, 8) * 4;
            d[0x7C / 2] = (GCuptr)savedataGetStatus(0, 9) * 4;
            d[0x7E / 2] = (GCuptr)savedataGetStatus(0, 0x19) * 4;
            d[0x82 / 2] = (GCuptr)savedataGetStatus(0, 0x1C) * 4;
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave23*)base = *(MemcardSave23*)savedataGetStatus(0, 0x17);
            off += 0x6D0;
            break;
        case 9:
            MEMCARD_SET_OFFSET(d, 0x5C / 2, off);
            base = MEMCARD_SECTION(data, off);
            __copy(base, (u16*)savedataGetStatus(0, 0x10), 0xB);
            off += 0x20;
            break;
        case 15:
            if (_memcardStatusPtr->kind != 8 && _memcardStatusPtr->kind != 0xD && _memcardStatusPtr->kind != 7 && !_memcard_anySaveOFF_Flag) {
                floorMakeSaveData(&floorData, &floorSize);
            }
            MEMCARD_SET_OFFSET(d, 0x74 / 2, off);
            base = MEMCARD_SECTION(data, off);
            {
                void* floorSave = savedataGetStatus(0, 0x16);
                if (_memcardStatusPtr->kind != 8 && _memcardStatusPtr->kind != 0xD && _memcardStatusPtr->kind != 7 && !_memcard_anySaveOFF_Flag) {
                    memcpy(floorSave, floorData, floorSize);
                    GSmemFree(floorData);
                }
                if (!_memcard_anySaveOFF_Flag) {
                    memcpy(base, floorSave, 0xC800);
                } else {
                    memset(base, 0, 0xC800);
                }
            }
            off += 0xC810;
            break;
        case 10:
            MEMCARD_SET_OFFSET(d, 0x60 / 2, off);
            off += 0x410;
            break;
        case 11:
            MEMCARD_SET_OFFSET(d, 0x64 / 2, off);
            off += 0x810;
            break;
        case 12:
            MEMCARD_SET_OFFSET(d, 0x68 / 2, off);
            off += 0x1010;
            break;
        case 13:
            MEMCARD_SET_OFFSET(d, 0x6C / 2, off);
            off += 0x2010;
            break;
        case 14:
            MEMCARD_SET_OFFSET(d, 0x70 / 2, off);
            base = MEMCARD_SECTION(data, off);
            *(MemcardSave21*)base = *(MemcardSave21*)savedataGetStatus(0, 0x15);
            off += 0x22B0;
            break;
        }
        for (; pick < left; pick++) {
            order[pick] = order[pick + 1];
        }
        left--;
    }
}
}

}

extern "C++" {
static inline u8 _memcardIsOwnFile(s32 result, CARDStat* stat) {
    if (result == 0) {
        switch (pokecoloGetCountryCode()) {
        case 0:
            if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXJ" &&
                *(u16*)stat->company == *(u16*)"01") {
                return 1;
            }
            break;
        case 1:
            if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXE" &&
                *(u16*)stat->company == *(u16*)"01") {
                return 1;
            }
            break;
        case 2:
            if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXP" &&
                *(u16*)stat->company == *(u16*)"01") {
                return 1;
            }
            break;
        }
    }
    return 0;
}

static inline s32 _memcardSearchFile(void) {
    CARDFileInfo* info = &_memcardStatusPtr->fileInfo;
    s32 chan = _memcardStatusPtr->arg14;
    s32 result;
    s32 i;

    for (i = 0; i < 0x7F; i++) {
        result = CARDFastOpen(chan, i, info);
        if (result == 0) {
            CARDStat stat;
            result = CARDGetStatus(chan, i, &stat);
            if (_memcardIsOwnFile(result, &stat)) {
                return 0;
            }
        }
    }
    if (result == 0) {
        result = -4;
    }
    return result;
}

static u32 _memcardCardOpen() {
    s32 freeBytes;
    s32 freeFiles;
    CARDStat stat;
    s32 error;

    CARDFreeBlocks(_memcardStatusPtr->arg14, &freeBytes, &freeFiles);
    switch (pokecoloGetCountryCode()) {
    case 0:
        error = _memcardSearchFile();
        break;
    case 1:
    case 2:
        error = _memcardSearchFile();
        break;
    }
    switch (error) {
    case 0:
        _memcardStatusPtr->f3e = 1;
        error = CARDGetStatus(_memcardStatusPtr->arg14, _memcardStatusPtr->fileInfo.fileNo, &stat);
        if (error != 0) {
            break;
        }
        if (stat.commentAddr != 0xFFFFFFFF) {
            if (_memcardStatusPtr->kind == 0xC) {
                _memcardStatusPtr->msgType = 2;
                _memcardStatusPtr->resumeState = 0xB;
                return 0x30;
            }
            if (_memcardStatusPtr->kind == 3) {
                return 0x1C;
            }
            return 0x19;
        }
        freeBytes += 0x56000;
        freeFiles++;
        error = -4;
    case -4:
        switch (_memcardStatusPtr->kind) {
        case 1:
            if (freeBytes < 0x56000) {
                error = -9;
                break;
            }
            if (freeFiles < 1) {
                error = -8;
                break;
            }
            _memcardStatusPtr->msgType = 6;
            _memcardStatusPtr->resumeState = 0xA;
            return 0x30;
        case 9:
            _memcardStatusPtr->msgType = 2;
            _memcardStatusPtr->resumeState = 0xB;
            return 0x30;
        }
        break;
    }
    _memcardStatusPtr->msgType = error;
    return 0x2B;
}
}

#pragma dont_inline on
static s32 _memcardMergeDataPack()
{
    void* save;
    u8* data = (u8*)_memcardStatusPtr->buf50 + 8;
    save = _memcardGetMultiSaveDataToSTRUCT(data, 1);
    switch (_memcardStatusPtr->kind) {
    case 9:
        _memcardDuplicateSaveData_multi(data);
        _memcardStoreSaveData_multi(data);
        break;
    case 13:
        {
            void* src = savedataGetStatus(0, 0xe);
            memcpy(_memcardGetMultiSaveDataToSTRUCT(data, 0xe), src, 0x364);
        }
        break;
    }
    gamedatasaveSetStatus(save, 9, (u8)gamedatasaveGetStatus(0, 9));
    gamedatasaveSetStatus(save, 10, (u8)gamedatasaveGetStatus(0, 10));
    gamedatasaveSetStatus(save, 11, (u8)gamedatasaveGetStatus(0, 11));
    return 0x25;
}
#pragma dont_inline reset

extern "C" {
void memcard_debug_Save(void* data)
{
    memcardSetupTask(0xb, 2, 0);
    _memcardDuplicateSaveData_multi(data);
    _memcard_Encryption(data);
    memcardFinalizeTask();
}
}

static inline void _memcardSumBlocks(u16* data, u32* sums)
{
    int i;
    int k;
    for (i = 0; i < 4; i++) {
        for (k = i * 0x4FFA; k < (i + 1) * 0x4FFA; k++) {
            sums[i] += data[k];
        }
    }
}

static u8 _memcard_Decryption(void* data)
{
    u16* d = (u16*)data;
    u32 sums[10];
    u32 stored[4];
    int i;
    int k;
    sums[2] = 0;
    sums[0] = 0;
    sums[1] = 0;
    sums[3] = 0;
    _memcard_encrypt_key[0] = d[0];
    _memcard_encrypt_key[1] = d[1];
    _memcard_encrypt_key[2] = d[2];
    _memcard_encrypt_key[3] = d[3];
    for (i = 4; i < 0x13FE8; i += 4) {
        for (k = 0; k < 4; k++) {
            d[i + k] -= _memcard_encrypt_key[k];
        }
        _memcardKeyStep(_memcard_encrypt_key);
    }
    stored[2] = d[6] | (d[7] << 16);
    stored[3] = d[4] | (d[5] << 16);
    stored[1] = d[8] | (d[9] << 16);
    stored[0] = d[10] | (d[11] << 16);
    d[10] = 0;
    d[11] = 0;
    d[8] = 0;
    d[9] = 0;
    d[6] = 0;
    d[7] = 0;
    d[4] = 0;
    d[5] = 0;
    _memcardSumBlocks(d, sums);
    if (sums[0] == stored[0] && sums[1] == stored[1] && sums[2] == stored[2] && sums[3] == stored[3]) {
        return 1;
    }
    return 0;
}

static void _memcard_Encryption(void* data)
{
    u16* d = (u16*)data;
    u32 sums[4];
    int i;
    int k;
    sums[0] = 0;
    sums[1] = 0;
    sums[2] = 0;
    sums[3] = 0;
    _memcard_encrypt_key[0] = d[0];
    _memcard_encrypt_key[1] = d[1];
    _memcard_encrypt_key[2] = d[2];
    _memcard_encrypt_key[3] = d[3];
    d[10] = 0;
    d[11] = 0;
    d[8] = 0;
    d[9] = 0;
    d[6] = 0;
    d[7] = 0;
    d[4] = 0;
    d[5] = 0;
    _memcardSumBlocks(d, sums);
    d[10] = sums[0];
    d[11] = sums[0] >> 16;
    d[8] = sums[1];
    d[9] = sums[1] >> 16;
    d[6] = sums[2];
    d[7] = sums[2] >> 16;
    d[4] = sums[3];
    d[5] = sums[3] >> 16;
    for (i = 4; i < 0x13FE8; i += 4) {
        for (k = 0; k < 4; k++) {
            d[i + k] += _memcard_encrypt_key[k];
        }
        _memcardKeyStep(_memcard_encrypt_key);
    }
}
extern "C++" {
#define CARD_STAT_BANNER_MASK 3
#define CARD_STAT_ANIM_MASK 4
#define CARD_STAT_ICON_MASK 3
#define CARD_STAT_SPEED_MASK 3
#define CARDSetBannerFormat(stat, f) \
    ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_BANNER_MASK) | (f)))
#define CARDSetIconAnim(stat, f) \
    ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_ANIM_MASK) | (f)))
#define CARDSetIconFormat(stat, n, f) \
    ((stat)->iconFormat = (u16)(((stat)->iconFormat & ~(CARD_STAT_ICON_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, f) \
    ((stat)->iconSpeed = (u16)(((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconAddress(stat, addr) ((stat)->iconAddr = (u32)(addr))
#define CARDSetCommentAddress(stat, addr) ((stat)->commentAddr = (u32)(addr))

static inline s32 _memcardPollResult(void)
{
    s32 result = _memcardStatusPtr->f28;

    if (result != -1) {
        return result;
    }
    result = CARDGetResultCode(_memcardStatusPtr->arg14);
    _memcardStatusPtr->f28 = result;
    return result;
}

static inline void _memcardSetRequestResult(s32 result)
{
    if (result == 0) {
        result = CARDGetResultCode(_memcardStatusPtr->arg14);
    }
    _memcardStatusPtr->f28 = result;
}

static inline s32 _memcardAsk(s32 msg, s32 resume)
{
    _memcardStatusPtr->msgType = msg;
    _memcardStatusPtr->resumeState = resume;
    return 0x30;
}

static inline s32 _memcardSaveOffset(s32 slot)
{
    return slot * 0x28000 + 0x6000;
}

static inline s32 _memcardCheckCard(void)
{
    u64 serial;
    s32 result = _memcardPollResult();

    if (_memcardStatusPtr->memSize != 0x2000) {
        result = -6;
    }
    switch (result) {
    case -1:
        return 5;
    case 0:
        switch (_memcardStatusPtr->kind) {
        case 3:
        case 9:
        case 11:
            break;
        default:
            if (_memcardStatusPtr->valid) {
                CARDGetSerialNo(_memcardStatusPtr->arg14, &serial);
                if (serial != _memcardStatusPtr->serial) {
                    _memcardStatusPtr->msgType = 0x10;
                    return 0x2B;
                }
            }
            break;
        }
        return 9;
    case -6:
    case -13:
        switch (_memcardStatusPtr->kind) {
        case 1:
        case 9:
            return _memcardAsk(7, 6);
        }
        break;
    }
    _memcardStatusPtr->msgType = result;
    return 0x2B;
}

static inline s32 _memcardCheckIconFile(void)
{
    u32 checksum = 0;
    u8* file;
    u32 i;
    s32 result = _memcardPollResult();

    switch (result) {
    case -1:
        return 0x1B;
    case 0:
        file = (u8*)_memcardStatusPtr->buf50;
        for (i = 0; i < 0xE90; i++) {
            checksum += ((u32*)file)[i];
        }
        if (checksum != *(u32*)(file + 0x3A40)) {
            _memcardStatusPtr->f40 = 1;
        }
        return 0x1C;
    }
    _memcardStatusPtr->msgType = result;
    return 0x2B;
}

static inline s32 _memcardBeginHeaderRead(void)
{
    _memcardStatusPtr->f30 = 0;
    _memcardStatusPtr->f20 = 0;
    switch (_memcardStatusPtr->kind) {
    case 1:
    case 2:
        if (_memcardStatusPtr->f40 != 0) {
            _memcardStatusPtr->msgType = 5;
            break;
        }
    case 3:
    case 8:
        return 0x1D;
    default:
        _memcardStatusPtr->msgType = 2;
        break;
    }
    _memcardStatusPtr->resumeState = 0x1D;
    return 0x30;
}

static inline void _memcardSetSaveId(void* data, u64 serial)
{
    if (data == NULL) {
        gamedatasaveBiosSetMemcardID(gamedatasaveBiosGetPtr(savedataGetStatus(data, 1)), serial);
    } else {
        gamedatasaveBiosSetMemcardID((GamedataSave*)((u8*)_memcardGetMultiSaveDataToSTRUCT(data, 1) + 8), serial);
    }
}

static inline void _memcardCountSave(void* data)
{
    if (data == NULL) {
        gamedatasaveSetStatus(savedataGetStatus(data, 1), 4, gamedatasaveGetStatus(savedataGetStatus(data, 1), 4) + 1);
    } else {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(data, 1);
        gamedatasaveSetStatus(gamedata, 4, gamedatasaveGetStatus(gamedata, 4) + 1);
    }
}

static inline void _memcardFillRandom(u8* random, s32 count)
{
    while (count-- != 0) {
        *random++ = HSD_Rand();
    }
}

static inline s32 _memcardSaveSetup(void)
{
    u64 serial;
    u8* pack;

    CARDGetSerialNo(_memcardStatusPtr->arg14, &serial);
    _memcardSetSaveId(NULL, serial);
    _memcardStatusPtr->f2c++;
    _memcardStatusPtr->f20 = (_memcardStatusPtr->f20 + 1) % 2;
    pack = (u8*)_memcardStatusPtr->buf50;
    pack[0] = 1;
    pack[1] = 1;
    pack[2] = 1;
    pack[3] = 0;
    *(s32*)(pack + 4) = _memcardStatusPtr->f2c;
    _memcardSetSaveId(pack + 8, serial);
    switch (_memcardStatusPtr->kind) {
    case 4:
    case 8:
    case 9:
    case 10:
    case 11:
        _memcardCountSave(pack + 8);
        break;
    }
    {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
        u32 sum = 0;
        u32 i;

        for (i = 0; i < 0x600; i++) {
            sum += ((u32*)0x80001800)[i];
        }
        gamedatasaveSetStatus(gamedata, 0xC, sum);
    }
    {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
        u32 sum = 0;
        s32 i;

        for (i = 0; i < 8; i++) {
            sum += pack[i];
        }
        gamedatasaveSetStatus(gamedata, 0xD, sum);
    }
    _memcard_Encryption(pack + 8);
    _memcardFillRandom(pack + 0x27FD8, 0x28);
    return 0x26;
}

static inline s32 _memcardCheckWrite(void)
{
    s32 result = _memcardPollResult();

    _memcardStatusPtr->writeTicks++;
    switch (result) {
    case -1:
        return 0x27;
    case 0:
        _memcard_gba2mode = 0;
        switch (_memcardStatusPtr->kind) {
        case 8:
            _memcardStatusPtr->resumeState = 0x28;
            _memcard_gba2mode = 1;
            return 0x31;
        case 1:
        case 2:
        case 3:
            _memcardStatusPtr->msgType = 0x12;
            _memcardStatusPtr->result = 3;
            break;
        case 4:
        case 9:
        case 10:
        case 11:
            _memcardCountSave(NULL);
        default:
            _memcardStatusPtr->msgType = 10;
            _memcardStatusPtr->result = 4;
            break;
        }
        _memcardStatusPtr->f40 = 1;
        if (_memcardStatusPtr->f40 != 0) {
            return 0x11;
        }
        return 0x2C;
    }
    _memcardStatusPtr->msgType = result;
    return 0x2B;
}

static inline s32 _memcardPollResultInto(s32* result)
{
    *result = _memcardStatusPtr->f28;
    if (*result != -1) {
        return *result;
    }
    *result = CARDGetResultCode(_memcardStatusPtr->arg14);
    _memcardStatusPtr->f28 = *result;
    return *result;
}

static inline s32 _memcardCheckLastWrite(void)
{
    s32 result;

    switch (_memcardPollResultInto(&result)) {
    case -1:
        _memcardStatusPtr->writeTicks--;
        if (_memcardStatusPtr->f3d == 0) {
            if (gbaCommandIsConnected(2) == 0) {
                CARDCancel(&_memcardStatusPtr->fileInfo);
                return 0x2B;
            }
            if ((s32)_memcardStatusPtr->writeTicks < 3) {
                if (gbaCommandChangePokemonEnd(2) != 0) {
                    CARDCancel(&_memcardStatusPtr->fileInfo);
                    return 0x2B;
                }
                _memcardStatusPtr->f3d = 1;
            }
        }
        return 0x2A;
    case 0:
        if (_memcardStatusPtr->f3d == 0) {
            gbaCommandChangePokemonEnd(2);
        }
        _memcardCountSave(NULL);
        _memcardStatusPtr->msgType = 0;
        _memcardStatusPtr->result = 4;
        return 0x2C;
    }
    PKJB_ReturnTitle(1);
    _memcardStatusPtr->msgType = result;
    return 0x2B;
}

static inline s32 _memcardEndAccess(void)
{
    u64 serial;

    if (_memcardStatusPtr->f3e != 0) {
        CARDGetSerialNo(_memcardStatusPtr->arg14, &serial);
        CARDClose(&_memcardStatusPtr->fileInfo);
        _memcardStatusPtr->f3e = 0;
    }
    CARDUnmount(_memcardStatusPtr->arg14);
    GSgfxResetRestore(_memcardStatusPtr->f3f);
    if (_memcardStatusPtr->cbDone != 0 && _memcard_gba2mode == 0) {
        return 0;
    }
    switch (_memcardStatusPtr->kind) {
    case 3:
    case 8:
        return 0x32;
    }
    switch (_memcardStatusPtr->result) {
    case 1:
    case 2:
    case 3:
    case 4:
        _memcardStatusPtr->serial = serial;
        _memcardStatusPtr->valid = 1;
        break;
    }
    _memcardStatusPtr->msgType = _memcardStatusPtr->msgType;
    _memcardStatusPtr->resumeState = 0x2D;
    return 0x30;
}

static inline s32 _memcardFinishTask(void)
{
    switch (_memcardStatusPtr->kind) {
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 13:
        if (_memcardStatusPtr->result != 4) {
            return _memcardAsk(0xF, 0x32);
        }
        break;
    case 1:
        if (_memcardStatusPtr->result == -1) {
            switch (_memcardStatusPtr->f60) {
            case 7:
                _memcardStatusPtr->msgType = 13;
                break;
            case 13:
                _memcardStatusPtr->msgType = 14;
                break;
            default:
                return 0x2E;
            }
            _memcardStatusPtr->resumeState = 0x2E;
            return 0x30;
        }
        break;
    }
    return 0x32;
}

static void _memcardJobMain(u32, u32)
{
    s32 next;
    s32 result;
    s32 status;

    _memcard_new_saveDataCrateFlag = 1;
    do {
        switch (_memcardStatusPtr->state) {
        case 0:
            _memcardStatusPtr->f28 = 0;
            _memcardStatusPtr->f60 = 0x32;
            _memcardStatusPtr->f40 = 0;
            _memcardStatusPtr->f3f = GSgfxResetDisable();
            _memcardStatusPtr->cbDone = 0;
            _memcard_gba2mode = 0;
            GSgfxResetRestore(_memcardStatusPtr->f3f);
            switch (_memcardStatusPtr->kind) {
            case 1:
            case 2:
                _memcardStatusPtr->valid = 0;
                break;
            case 4:
                if (gamedatasaveGetStatus(NULL, 4) == 0) {
                    _memcardStatusPtr->kind = 9;
                }
                floorMemoryCardSaveCallback();
                break;
            case 8:
                break;
            }
            _memcardStatusPtr->f24 = 0;
            _memcardStatusPtr->state = 1;
            break;

        case 1:
            status = CARDProbeEx(_memcardStatusPtr->arg14, &_memcardStatusPtr->sectorSize,
                                 &_memcardStatusPtr->memSize);
            _memcardSetRequestResult(status);
            switch (status) {
            case -1:
                next = 1;
                break;
            case 0:
                next = 2;
                break;
            default:
                if (_memcardStatusPtr->f24++ < 6) {
                    _memcardStatusPtr->f28 = -1;
                    next = 1;
                } else {
                    _memcardStatusPtr->msgType = status;
                    next = 0x2B;
                }
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 2:
            _memcardSetRequestResult(CARDMountAsync(_memcardStatusPtr->arg14, _memcardStatusPtr->buf54,
                                                    _memcardCallback, NULL));
            _memcardStatusPtr->state = 3;
            break;

        case 3:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 3;
                break;
            case 0:
            case -6:
            case -13:
                next = 4;
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 4:
            _memcardSetRequestResult(CARDCheckAsync(_memcardStatusPtr->arg14, NULL));
            _memcardStatusPtr->state = 5;
            break;

        case 5:
            _memcardStatusPtr->state = _memcardCheckCard();
            break;

        case 6:
            if (_memcardStatusPtr->msgType != 0) {
                CARDFormatAsync(_memcardStatusPtr->arg14, NULL);
                if (_memcardStatusPtr->cbDone != 0) {
                    _memcardStatusPtr->msgType = 0;
                    next = 0x2B;
                } else {
                    _memcardStatusPtr->f60 = 7;
                    next = _memcardAsk(4, 7);
                }
            } else {
                _memcardStatusPtr->msgType = 0;
                next = 0x2B;
            }
            _memcardStatusPtr->state = next;
            break;

        case 7:
            GSgfxResetDisable();
            result = CARDFormatAsync(_memcardStatusPtr->arg14, NULL);
            if (_memcardStatusPtr->cbDone != 0) {
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
            } else {
                _memcardSetRequestResult(result);
                next = 8;
            }
            _memcardStatusPtr->state = next;
            break;

        case 8:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 8;
                break;
            case 0:
                GSgfxResetRestore(_memcardStatusPtr->f3f);
                _memcardStatusPtr->f60 = 0x32;
                next = _memcardAsk(9, 9);
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 9:
            _memcardStatusPtr->state = _memcardCardOpen();
            break;

        case 10:
            if (_memcardStatusPtr->msgType == 0) {
                _memcardStatusPtr->msgType = 0;
                next = 0x2B;
            } else {
                _memcardStatusPtr->msgType = 3;
                _memcardStatusPtr->f60 = 13;
                _memcardStatusPtr->resumeState = 11;
                next = 0x30;
            }
            _memcardStatusPtr->state = next;
            break;

        case 11: {
            s32 deleted;

            GSgfxResetDisable();
            switch (pokecoloGetCountryCode()) {
            case 0:
                deleted = CARDDeleteAsync(_memcardStatusPtr->arg14, "PokemonXD", NULL);
                break;
            case 1:
            case 2:
                deleted = CARDDeleteAsync(_memcardStatusPtr->arg14, "PokemonXD", NULL);
                break;
            }
            _memcardSetRequestResult(deleted);
            _memcardStatusPtr->state = 12;
            break;
        }

        case 12:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 12;
                break;
            case 0:
            case -4:
                if (_memcardStatusPtr->kind == 12) {
                    _memcardStatusPtr->msgType = 10;
                    next = 0x2B;
                } else {
                    next = 13;
                }
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 13: {
            s32 created;

            switch (pokecoloGetCountryCode()) {
            case 0:
                created = CARDCreateAsync(_memcardStatusPtr->arg14, "PokemonXD", 0x56000,
                                          &_memcardStatusPtr->fileInfo, NULL);
                break;
            case 1:
            case 2:
                created = CARDCreateAsync(_memcardStatusPtr->arg14, "PokemonXD", 0x56000,
                                          &_memcardStatusPtr->fileInfo, NULL);
                break;
            }
            _memcardSetRequestResult(created);
            _memcardStatusPtr->state = 14;
            break;
        }

        case 14:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 14;
                break;
            case 0:
                _memcardStatusPtr->f3e = 1;
                next = 15;
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 15: {
            u8 attributes;

            CARDGetAttributes(_memcardStatusPtr->arg14, _memcardStatusPtr->fileInfo.fileNo, &attributes);
            attributes |= 0x18;
            _memcardSetRequestResult(CARDSetAttributesAsync(_memcardStatusPtr->arg14,
                                                            _memcardStatusPtr->fileInfo.fileNo, attributes,
                                                            NULL));
            _memcardStatusPtr->state = 16;
            break;
        }

        case 16:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 16;
                break;
            case 0:
                next = 17;
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 17:
            _memcardStatusPtr->state = fn_801CC508();
            break;

        case 18:
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->fileInfo, _memcardStatusPtr->buf50,
                                                    _memcardStatusPtr->f40 != 0 ? 0x4000 : 0x6000, 0, NULL));
            _memcardStatusPtr->state = 19;
            break;

        case 19:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 19;
                break;
            case 0:
                if (_memcardStatusPtr->f40 != 0) {
                    next = 0x2C;
                } else {
                    next = 20;
                }
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 20: {
            u8* header = (u8*)_memcardStatusPtr->buf50;

            memset(header, 0, 0x2000);
            header[0] = 1;
            header[1] = 1;
            header[2] = 1;
            header[3] = 0;
            _memcardStatusPtr->f20 = 0;
            _memcardStatusPtr->state = 21;
            break;
        }

        case 21:
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->fileInfo, _memcardStatusPtr->buf50, 0x2000,
                                                    _memcardSaveOffset(_memcardStatusPtr->f20), NULL));
            _memcardStatusPtr->state = 22;
            break;

        case 22:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 22;
                break;
            case 0:
                if ((u32)++_memcardStatusPtr->f20 < 2) {
                    next = 21;
                } else {
                    next = 23;
                }
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 23: {
            s32 i;

            result = CARDGetStatus(_memcardStatusPtr->arg14, _memcardStatusPtr->fileInfo.fileNo,
                                   &_memcardStatusPtr->stat);
            if (result == 0) {
                CARDSetCommentAddress(&_memcardStatusPtr->stat, 0);
                CARDSetIconAddress(&_memcardStatusPtr->stat, 0x40);
                CARDSetBannerFormat(&_memcardStatusPtr->stat, 2);
                CARDSetIconAnim(&_memcardStatusPtr->stat, 0);
                for (i = 0; i < 8; i++) {
                    CARDSetIconFormat(&_memcardStatusPtr->stat, i, 1);
                    CARDSetIconSpeed(&_memcardStatusPtr->stat, i, 1);
                }
                _memcardSetRequestResult(CARDSetStatusAsync(_memcardStatusPtr->arg14,
                                                            _memcardStatusPtr->fileInfo.fileNo,
                                                            &_memcardStatusPtr->stat, NULL));
                next = 24;
            } else {
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
            }
            _memcardStatusPtr->state = next;
            break;
        }

        case 24:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 24;
                break;
            case 0:
                if (_memcardStatusPtr->kind == 9) {
                    _memcardDuplicateSaveData_multi((u8*)_memcardStatusPtr->buf50 + 8);
                    _memcardStatusPtr->f2c = 0;
                    _memcardStatusPtr->f20 = -1;
                    next = 0x25;
                } else {
                    _memcardStatusPtr->msgType = 11;
                    _memcardStatusPtr->result = 2;
                    next = 0x2C;
                }
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 25:
            _memcardStatusPtr->state = 26;
            break;

        case 26:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->fileInfo, _memcardStatusPtr->buf50, 0x4000, 0,
                                                   NULL));
            _memcardStatusPtr->state = 27;
            break;

        case 27:
            _memcardStatusPtr->state = _memcardCheckIconFile();
            break;

        case 28:
            _memcardStatusPtr->state = _memcardBeginHeaderRead();
            break;

        case 29:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->fileInfo,
                                                   (u8*)_memcardStatusPtr->buf50 +
                                                       (_memcardStatusPtr->f20 * 0x200 + 0x28000),
                                                   0x200, _memcardSaveOffset(_memcardStatusPtr->f20), NULL));
            _memcardStatusPtr->state = 30;
            break;

        case 30:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 30;
                break;
            case 0:
                if ((u32)++_memcardStatusPtr->f20 < 2) {
                    next = 29;
                } else {
                    next = 31;
                }
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 31:
            _memcardStatusPtr->state = _memcardExamineHeader();
            break;

        case 32:
            _memcardStatusPtr->state = 33;
            break;

        case 33:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->fileInfo, _memcardStatusPtr->buf50, 0x28000,
                                                   _memcardSaveOffset(_memcardStatusPtr->f20), NULL));
            _memcardStatusPtr->state = 34;
            break;

        case 34:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 34;
                break;
            case 0:
                next = 35;
                break;
            default:
                _memcardStatusPtr->msgType = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->state = next;
            break;

        case 35:
            _memcardStatusPtr->state = _memcardExamineDataPack();
            break;

        case 36:
            _memcardStatusPtr->state = _memcardMergeDataPack();
            break;

        case 37:
            _memcardStatusPtr->state = _memcardSaveSetup();
            break;

        case 38: {
            s32 length = _memcardStatusPtr->kind == 8 ? 0x26000 : 0x28000;

            GSgfxResetDisable();
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->fileInfo, _memcardStatusPtr->buf50, length,
                                                    _memcardSaveOffset(_memcardStatusPtr->f20), NULL));
            _memcardStatusPtr->writeTicks = 0;
            _memcardStatusPtr->state = 0x27;
            break;
        }

        case 39:
            _memcardStatusPtr->state = _memcardCheckWrite();
            break;

        case 40:
            if (_memcardStatusPtr->delay-- != 0) {
                _memcardStatusPtr->f28 = -1;
                next = 0x28;
            } else {
                _memcardStatusPtr->f28 = 0;
                next = 0x29;
            }
            _memcardStatusPtr->state = next;
            break;

        case 41:
            if (gbaCommandIsConnected(2) == 0) {
                next = 0x2B;
            } else {
                _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->fileInfo,
                                                        (u8*)_memcardStatusPtr->buf50 + 0x26000, 0x2000,
                                                        _memcardSaveOffset(_memcardStatusPtr->f20) + 0x26000,
                                                        NULL));
                _memcardStatusPtr->writeTicks /= 19;
                _memcardStatusPtr->writeTicks++;
                _memcardStatusPtr->f3d = 0;
                next = 0x2A;
            }
            _memcardStatusPtr->state = next;
            break;

        case 42:
            _memcardStatusPtr->state = _memcardCheckLastWrite();
            break;

        case 43:
            _memcardStatusPtr->result = -1;
            _memcardStatusPtr->state = 0x2C;
            break;

        case 44:
            _memcardStatusPtr->state = _memcardEndAccess();
            break;

        case 45:
            _memcardStatusPtr->state = _memcardFinishTask();
            break;

        case 46:
            _memcardStatusPtr->state = _memcardAsk(8, 0x2F);
            break;

        case 47:
            if (_memcardStatusPtr->msgType != 0) {
                _memcardStatusPtr->result = 5;
            }
            _memcardStatusPtr->state = 0x32;
            break;

        case 48:
        case 49:
        case 50:
            return;
        }
    } while (_memcardStatusPtr->f28 != -1);
}
}

extern "C" {
void memcard_debug_Load(void* data)
{
    memcardSetupTask(2, 2, 0);
    _memcard_Decryption(data);
    _memcardStoreSaveData_multi(data);
    _memcardStatusPtr->valid = 1;
    memcardFinalizeTask();
    {
        s32* p = (s32*)savedataGetStatus(0, 1);
        if (p[4] == 0) {
            p[4]++;
        }
    }
}
}

extern "C" {
void memcard_debug_Load2(void)
{
    _memcardStatusPtr->valid = 1;
}
}
