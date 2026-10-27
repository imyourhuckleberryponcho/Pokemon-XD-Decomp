#include <dolphin/types.h>
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
void msgctrlSetValue(s32 id, u32 value);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
void GSsndPlay(s32, s32, s32);
u32 gamedatasaveGetStatus(void* ptr, u32 kind);
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
    Hero* getHeroPtr();
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
long PKJB_ReturnTitle(long ch);
s32 __copy(void*, u16*, s32);
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
struct MemcardBannerImage {
    u8 banner[0x1800];
    u8 icon[0x2200];
    u8 pad3A00[0x1C];
    char titleUS[0x10];
    char commentUS[0x18];
    char titleEU[0xC];
    char commentEU[1];
};
extern const MemcardBannerImage _memcardBannerImage;
extern s32 jtbl_4196;
}
extern "C++" {
static void _memcardCallback(long, long);
static u32 _memcardCardOpen();
static void _memcardDuplicateSaveData_multi(void* p0);
static s32 _memcardExamineDataPack();
static s32 _memcardExamineHeader();
static void _memcardJobMain(unsigned long p0, unsigned long p1);
static s32 _memcardMergeDataPack();
}

extern "C" {
extern s32 jtbl_3110;
}

static inline void _memcardKeyStep(u16* key)
{
    u32 primes[4] = {0x43, 0x29, 0x17, 0x13};
    u16 v[4];
    v[0] = key[0];
    v[1] = key[1];
    v[2] = key[2];
    v[3] = key[3];
    v[0] = v[0] + primes[0];
    v[1] = v[1] + primes[1];
    v[2] = v[2] + primes[2];
    v[3] = v[3] + primes[3];
    key[0] = (((((((v[1] * 0x10) & 0xF0 & ~0xF) | (v[0] & 0xF)) & ~0xF00) | ((v[2] << 8) & 0xF00)) & ~0xF000) | ((v[3] << 0xC) & 0xF000));
    key[1] = ((((((v[1] & 0xF0 & ~0xF) | ((v[0] >> 4) & 0xF)) & ~0xF00) | ((v[2] << 4) & 0xF00)) & ~0xF000) | ((v[3] << 8) & 0xF000));
    key[2] = (((((((s32)(v[0] & 0xF00) >> 8) | ((s32)(v[1] & 0xF00) >> 4)) & ~0xF00) | (v[2] & 0xF00)) & ~0xF000) | ((v[3] << 4) & 0xF000));
    key[3] = (((((((v[0] >> 0xC) & 0xF & ~0xF0) | ((v[1] >> 8) & 0xF0)) & ~0xF00) | ((v[2] >> 4) & 0xF00)) & ~0xF000) | (v[3] & 0xF000));
}

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE type);
static void* _memcardGetMultiSaveDataToSTRUCT(void* data, long idx);
static void _memcardStoreSaveData_multi(void* data);
static void _memcardDuplicateSaveData_multi(void* data);
static u8 _memcard_Decryption(void* data);
static void _memcard_Encryption(void* data);

extern "C" {

void memcardInitialize(void)
{
    if (!_memcardInitializeFlag) {
        u32 lo, hi;
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
        _memcardStatusPtr->delay += (int)(u16)HSD_Rand() % 60;
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

static void* _memcardGetMultiSaveDataToSTRUCT(void* data, long idx)
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

static void _memcardCallback(long, long)
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
    int n = 4;
    int off = 8;
    int cnt = 0x3E;
    u16* d = (u16*)(pack + 8);
    _memcard_encrypt_key[0] = *(u16*)(pack + 8);
    _memcard_encrypt_key[1] = *(u16*)(pack + 10);
    _memcard_encrypt_key[2] = *(u16*)(pack + 12);
    _memcard_encrypt_key[3] = *(u16*)(pack + 14);
    for (i = 4; i < 0xFC; i += 4) {
        d[i] -= _memcard_encrypt_key[0];
        d[i + 1] -= _memcard_encrypt_key[1];
        d[i + 2] -= _memcard_encrypt_key[2];
        d[i + 3] -= _memcard_encrypt_key[3];
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
    const MemcardBannerImage* img = &_memcardBannerImage;
    OSCalendarTime ct;
    s8* buf;
    s32* p;
    int i;

    OSTicksToCalendarTime(OSGetTime(), &ct);
    buf = (s8*)_memcardStatusPtr->buf50;
    memset(buf, 0, 0x6000);
    switch (pokecoloGetCountryCode()) {
    case 0:
        strcpy((char*)buf, img->titleUS);
        strcpy((char*)buf + 0x20, img->commentUS);
        buf[0x2F] = ct.year / 10 % 10 + '0';
        buf[0x30] = ct.year % 10 + '0';
        buf[0x32] = (ct.mon + 1) / 10 % 10 + '0';
        buf[0x33] = (ct.mon + 1) % 10 + '0';
        buf[0x35] = ct.mday / 10 % 10 + '0';
        buf[0x36] = ct.mday % 10 + '0';
        break;
    case 1:
    case 2:
        strcpy((char*)buf, img->titleEU);
        strcpy((char*)buf + 0x20, img->commentEU);
        buf[3] = 0xE9;
        buf[0x32] = ct.year / 10 % 10 + '0';
        buf[0x33] = ct.year % 10 + '0';
        buf[0x2A] = (ct.mon + 1) / 10 % 10 + '0';
        buf[0x2B] = (ct.mon + 1) % 10 + '0';
        buf[0x2D] = ct.mday / 10 % 10 + '0';
        buf[0x2E] = ct.mday % 10 + '0';
        break;
    }
    memcpy(buf + 0x40, img->banner, 0x1800);
    memcpy(buf + 0x1840, img->icon, 0x2200);
    p = (s32*)buf;
    for (i = 0; i < 0xE90; i++) {
        *(s32*)(buf + 0x3A40) += p[i];
    }
    return 0x12;
}
#pragma optimize_for_size on
extern "C++" {
static void _memcardDuplicateSaveData_multi(void* p0) {
    u8 *var_r18_2;
    u8 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    u16 sp16;
    u16 sp14;
    u16 sp12;
    u16 sp10;
    u32 spC;
    u8 *sp8;
    s16 temp_r0_2;
    s16 temp_r5;
    u8 *var_r19_2;
    u32 var_r29;
    s16 var_r30;
    s16 var_r9;
    s32 temp_r3_7;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r9;
    s32 var_ctr;
    s32 var_r19;
    s32 var_r3;
    s32 var_r4;
    u16 *temp_r18_2;
    u16 *temp_r3_6;
    u16 *var_r18;
    u16 temp_r20;
    u16 temp_r6;
    u16 temp_r8_2;
    u16 temp_r9_2;
    s16 var_r27;
    u32 temp_r0_4;
    u32 temp_r0_5;
    u32 temp_r0_6;
    u32 temp_r0_7;
    u8 *temp_r7_2;
    u8 *var_r28;
    u8 *var_r4_2;
    u8 *var_r8;
    u8 temp_r0;
    u8 temp_r0_3;
    u8 temp_r0_8;
    u8 temp_r3;
    u8 temp_r3_10;
    u8 temp_r4;
    u8 *temp_r18;
    u8 *temp_r18_3;
    u8 *temp_r19;
    u8 *temp_r21;
    u8 *temp_r26;
    u8 *temp_r26_2;
    u8 *temp_r26_3;
    u8 *temp_r3_2;
    u8 *temp_r3_3;
    u8 *temp_r3_4;
    u8 *temp_r3_5;
    u8 *temp_r3_8;
    u8 *temp_r3_9;
    u8 *temp_r4_2;
    u8 *temp_r6_3;
    s8 sp37;
    s16 temp_r6_2;
    u8 *var_r21;
    u8 *var_r22;
    u8 *var_r24;
    u8 *var_r25;

    switch (*(s32 *)_memcardStatusPtr) {

    case 0xB:
            gamedatasaveSetStatus((Gamedata*)(NULL), 5U, floorGetNextFloorID());

        break;

    }
    var_r19 = 0;
    var_r18 = (unsigned short *)(&_memcard_encrypt_key);
    do {
        var_r19 += 1;
        *var_r18 = HSD_Rand();
        var_r18 += 2;
    } while (var_r19 < 4);
    var_r3 = 0;
    var_r4 = 0;
    var_ctr = 0x4FFA;
    if (0x13FE8 > 0) {
        do {
            temp_r9 = (var_r3 + 1) * 2;
            *((u8 *)p0 + var_r4) = *((u8 *)p0 + var_r4) + M2C_FIELD(&_memcard_encrypt_key, u16 *, 0);
            temp_r8 = (var_r3 + 2) * 2;
            temp_r7 = (var_r3 + 3) * 2;
            var_r3 += 4;
            var_r4 += 8;
            *((u8 *)p0 + temp_r9) = *((u8 *)p0 + temp_r9) + M2C_FIELD(&_memcard_encrypt_key, u16 *, 2);
            *((u8 *)p0 + temp_r8) = *((u8 *)p0 + temp_r8) + M2C_FIELD(&_memcard_encrypt_key, u16 *, 4);
            *((u8 *)p0 + temp_r7) = *((u8 *)p0 + temp_r7) + M2C_FIELD(&_memcard_encrypt_key, u16 *, 6);
            temp_r9_2 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 0) + M2C_FIELD(&jtbl_3110, s32 *, 0);
            temp_r8_2 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 2) + M2C_FIELD(&jtbl_3110, s32 *, 4);
            sp12 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 2);
            temp_r20 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 6) + M2C_FIELD(&jtbl_3110, s32 *, 0xC);
            sp16 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 6);
            temp_r6 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 4) + M2C_FIELD(&jtbl_3110, s32 *, 8);
            sp24 = M2C_FIELD(&jtbl_3110, s32 *, 0xC);
            sp10 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 0);
            sp12 = temp_r8_2;
            sp14 = M2C_FIELD(&_memcard_encrypt_key, u16 *, 4);
            sp10 = temp_r9_2;
            sp18 = M2C_FIELD(&jtbl_3110, s32 *, 0);
            sp1C = M2C_FIELD(&jtbl_3110, s32 *, 4);
            sp20 = M2C_FIELD(&jtbl_3110, s32 *, 8);
            sp14 = temp_r6;
            sp16 = temp_r20;
            M2C_FIELD(&_memcard_encrypt_key, u16 *, 0) = ((((((temp_r8_2 * 0x10) & 0xF0 & ~0xF) | (temp_r9_2 & 0xF)) & ~0xF00) | ((temp_r6 << 8) & 0xF00)) & ~0xF000) | ((temp_r20 << 0xC) & 0xF000);
            M2C_FIELD(&_memcard_encrypt_key, u16 *, 2) = (u16) ((((((temp_r8_2 & 0xF0 & ~0xF) | ((temp_r9_2 >> 4U) & 0xF)) & ~0xF00) | ((temp_r6 << 4) & 0xF00)) & ~0xF000) | ((temp_r20 << 8) & 0xF000));
            M2C_FIELD(&_memcard_encrypt_key, u16 *, 4) = (u16) (((((((s32) (temp_r9_2 & 0xF00) >> 8) | ((s32) (temp_r8_2 & 0xF00) >> 4)) & ~0xF00) | (temp_r6 & 0xF00)) & ~0xF000) | ((temp_r20 << 4) & 0xF000));
            M2C_FIELD(&_memcard_encrypt_key, u16 *, 6) = (u16) (((((((temp_r9_2 >> 0xCU) & 0xF & ~0xF0) | ((temp_r8_2 >> 8U) & 0xF0)) & ~0xF00) | ((temp_r6 >> 4U) & 0xF00)) & ~0xF000) | (temp_r20 & 0xF000));
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    M2C_FIELD(p0, s16 *, 0x18) = 0x88;
    M2C_FIELD(p0, s16 *, 0x1A) = 0x978;
    M2C_FIELD(p0, s16 *, 0x1C) = 0xBC50;
    M2C_FIELD(p0, s16 *, 0x80) = 0;
    M2C_FIELD(p0, s16 *, 0x1E) = 0x4A;
    M2C_FIELD(p0, s16 *, 0x20) = 0xCC;
    M2C_FIELD(p0, s16 *, 0x22) = 0x1774;
    M2C_FIELD(p0, s16 *, 0x24) = 0x364;
    M2C_FIELD(p0, s16 *, 0x26) = 0x2400;
    M2C_FIELD(p0, s16 *, 0x28) = 0x6B4;
    M2C_FIELD(p0, s16 *, 0x2A) = 0xB;
    M2C_FIELD(p0, s16 *, 0x36) = 0xC800;
    M2C_FIELD(p0, s16 *, 0x2C) = 0x400;
    M2C_FIELD(p0, s16 *, 0x2E) = 0x800;
    M2C_FIELD(p0, s16 *, 0x30) = 0x1000;
    M2C_FIELD(p0, s16 *, 0x32) = 0x2000;
    M2C_FIELD(p0, s16 *, 0x34) = 0x2298;
    M2C_FIELD(p0, s16 *, 0) = HSD_Rand();
    M2C_FIELD(p0, s16 *, 2) = HSD_Rand();
    M2C_FIELD(p0, s16 *, 4) = HSD_Rand();
    var_r8 = &sp28;
    M2C_FIELD(p0, s16 *, 6) = HSD_Rand();
    temp_r7_2 = var_r8;
    var_r9 = 0;
    while (var_r9 < 0xF) {
        temp_r0 = var_r9 + 1;
        temp_r4 = var_r9 + 2;
        *var_r8 = temp_r0;
        temp_r6_2 = var_r9 + 3;
        temp_r5 = var_r9 + 4;
        temp_r7_2[(s16) temp_r0] = temp_r4;
        temp_r3 = var_r9 + 5;
        temp_r7_2[(s16) temp_r4] = (u8) temp_r6_2;
        temp_r0_2 = temp_r5;
        var_r8 += 5;
        var_r9 += 5;
        temp_r7_2[temp_r6_2] = (u8) temp_r5;
        temp_r7_2[temp_r0_2] = temp_r3;
    }
    M2C_FIELD(p0, s16 *, 0x38) = 0;
    sp37 = -1;
    M2C_FIELD(p0, s16 *, 0x3A) = 0;
    temp_r3_2 = (unsigned char *)(savedataGetStatus((void*)(NULL), 1));
    var_r29 = 0xA0;
    var_r27 = 0xF;
    M2C_FIELD(p0, s32 *, 0xA0) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0);
    M2C_FIELD(p0, f64 *, 0xA8) = (f64) M2C_FIELD(temp_r3_2, f64 *, 8);
    M2C_FIELD(p0, f64 *, 0xB0) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x10);
    M2C_FIELD(p0, f64 *, 0xB8) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x18);
    M2C_FIELD(p0, f64 *, 0xC0) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x20);
    M2C_FIELD(p0, f64 *, 0xC8) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x28);
    M2C_FIELD(p0, f64 *, 0xD0) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x30);
    M2C_FIELD(p0, f64 *, 0xD8) = (f64) M2C_FIELD(temp_r3_2, f64 *, 0x38);
    M2C_FIELD(p0, u16 *, 0xE0) = (u16) M2C_FIELD(temp_r3_2, u16 *, 0x40);
    M2C_FIELD(p0, s32 *, 0xE4) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x44);
    M2C_FIELD(p0, s32 *, 0xE8) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x48);
    M2C_FIELD(p0, s32 *, 0xEC) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x4C);
    M2C_FIELD(p0, s32 *, 0xF0) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x50);
    M2C_FIELD(p0, s32 *, 0xF4) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x54);
    M2C_FIELD(p0, s32 *, 0xF8) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x58);
    M2C_FIELD(p0, s32 *, 0xFC) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x5C);
    M2C_FIELD(p0, s32 *, 0x100) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x60);
    M2C_FIELD(p0, s32 *, 0x104) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x64);
    M2C_FIELD(p0, s32 *, 0x108) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x68);
    M2C_FIELD(p0, s32 *, 0x10C) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x6C);
    M2C_FIELD(p0, s32 *, 0x110) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x70);
    M2C_FIELD(p0, s32 *, 0x114) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x74);
    M2C_FIELD(p0, s32 *, 0x118) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x78);
    M2C_FIELD(p0, s32 *, 0x11C) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x7C);
    M2C_FIELD(p0, s32 *, 0x120) = (s32) M2C_FIELD(temp_r3_2, s32 *, 0x80);
    while (var_r27 != 0) {
        var_r30 = HSD_Rand() % var_r27;
        var_r28 = &(&sp28)[var_r30];
        temp_r0_3 = *var_r28;
        if ((u32) (s8) temp_r0_3 <= 0xFU) {
            switch ((s8) temp_r0_3) {
            case 1:
                if ((*(s32 *)_memcardStatusPtr != 8) && (*(s32 *)_memcardStatusPtr != 0xD) && (*(s32 *)_memcardStatusPtr != 7) && ((u8) _memcard_anySaveOFF_Flag == 0)) {
                    ((Hero*)(((Hero*)(_memcardStatusPtr))->getHeroPtr()))->setRestertPos();
                }
                M2C_FIELD(p0, u16 *, 0x3C) = var_r29;
                M2C_FIELD(p0, s16 *, 0x3E) = (s16) (var_r29 >> 0x10U);
                memcpy((void*)(((u8*)(p0) + 0xA0) + var_r29), (const void*)(savedataGetStatus((void*)(NULL), 2)), 0x978U);
                var_r29 += 0x990;
                break;
            case 2:
                M2C_FIELD(p0, u16 *, 0x40) = var_r29;
                M2C_FIELD(p0, s16 *, 0x42) = (s16) (var_r29 >> 0x10U);
                temp_r26 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_3 = (unsigned char *)(savedataGetStatus((void*)(NULL), 3));
                var_r24 = temp_r26;
                var_r25 = temp_r3_3;
                do {
                    var_r21 = var_r24 + 0x14;
                    var_r22 = var_r25 + 0x14;
                    M2C_FIELD(var_r24, s32 *, 0) = (s32) M2C_FIELD(var_r25, s32 *, 0);
                    M2C_FIELD(var_r24, s32 *, 4) = (s32) M2C_FIELD(var_r25, s32 *, 4);
                    M2C_STRUCT_COPY(var_r24, var_r25, 0xA);
loop_20:
                    memcpy((void*)(var_r21), (const void*)(var_r22), 0xC4U);
                    var_r21 += 0xC4;
                    var_r22 += 0xC4;
                    if (var_r21 < (u8 *) (var_r24 + 0x170C)) {
                        goto loop_20;
                    }
                    var_r24 += 0x170C;
                    var_r25 += 0x170C;
                } while (var_r24 < (u8 *) (temp_r26 + 0xB860));
                temp_r6_3 = temp_r26 + 0xB85C;
                temp_r4_2 = temp_r3_3 + 0xB85C;
                M2C_STRUCT_COPY((s32) temp_r6_3 + 4, (s32) temp_r4_2 + 4, 0x3A8);
                M2C_FIELD((temp_r6_3 + 0x3A8), s32 *, 4) = (s32) M2C_FIELD((temp_r4_2 + 0x3A8), s32 *, 4);
                var_r29 += 0xBC60;
                M2C_FIELD(temp_r26, s32 *, 0xBC0C) = (s32) M2C_FIELD(temp_r3_3, s32 *, 0xBC0C);
                M2C_STRUCT_COPY(temp_r26 + 0x10000, temp_r3_3 + 0x10000, 0x40);
                break;
            case 3:
                M2C_FIELD(p0, u16 *, 0x44) = var_r29;
                M2C_FIELD(p0, s16 *, 0x46) = (s16) (var_r29 >> 0x10U);
                temp_r26_2 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_4 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0xA));
                var_r29 += 0x60;
                M2C_FIELD(temp_r26_2, s32 *, 0) = (s32) M2C_FIELD(temp_r3_4, s32 *, 0);
                M2C_FIELD(temp_r26_2, s32 *, 4) = (s32) M2C_FIELD(temp_r3_4, s32 *, 4);
                M2C_STRUCT_COPY(temp_r26_2, temp_r3_4, 0x3A);
                M2C_FIELD(temp_r26_2, s32 *, 0x42) = (s32) M2C_FIELD(temp_r3_4, s32 *, 0x42);
                M2C_FIELD(temp_r26_2, u8 *, 0x46) = (u8) M2C_FIELD(temp_r3_4, u8 *, 0x46);
                M2C_FIELD(temp_r26_2, u8 *, 0x47) = (u8) M2C_FIELD(temp_r3_4, u8 *, 0x47);
                M2C_FIELD(temp_r26_2, u16 *, 0x48) = (u16) M2C_FIELD(temp_r3_4, u16 *, 0x48);
                break;
            case 4:
                M2C_FIELD(p0, u16 *, 0x48) = var_r29;
                M2C_FIELD(p0, s16 *, 0x4A) = (s16) (var_r29 >> 0x10U);
                temp_r18 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_5 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0xB));
                M2C_FIELD(temp_r18, u8 *, 0) = (u8) M2C_FIELD(temp_r3_5, u8 *, 0);
                M2C_FIELD(temp_r18, u8 *, 1) = (u8) M2C_FIELD(temp_r3_5, u8 *, 1);
                M2C_FIELD(temp_r18, u16 *, 2) = (u16) M2C_FIELD(temp_r3_5, u16 *, 2);
                M2C_FIELD(temp_r18, s32 *, 4) = (s32) M2C_FIELD(temp_r3_5, s32 *, 4);
                memcpy((void*)(temp_r18 + 8), (const void*)(temp_r3_5 + 8), 0xC4U);
                var_r29 += 0xE0;
                break;
            case 5:
                M2C_FIELD(p0, u16 *, 0x4C) = var_r29;
                M2C_FIELD(p0, s16 *, 0x4E) = (s16) (var_r29 >> 0x10U);
                temp_r18_2 = (unsigned short *)(((u8*)(p0) + 0xA0) + var_r29);
                temp_r3_6 = (unsigned short *)(savedataGetStatus((void*)(NULL), 0xC));
                *temp_r18_2 = *temp_r3_6;
                M2C_STRUCT_COPY((s32) temp_r18_2 + 4, (s32) temp_r3_6 + 4, 0x1770);
                var_r29 += 0x1790;
                break;
            case 6:
                M2C_FIELD(p0, u16 *, 0x50) = var_r29;
                M2C_FIELD(p0, s16 *, 0x52) = (s16) (var_r29 >> 0x10U);
                temp_r18_3 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_7 = (long)(savedataGetStatus((void*)(NULL), 0xE));
                M2C_STRUCT_COPY(temp_r18_3, temp_r3_7, 0x360);
                var_r29 += 0x380;
                M2C_FIELD(temp_r18_3, u8 *, 0x360) = (u8) M2C_FIELD(temp_r3_7, u8 *, 0x360);
                break;
            case 7:
                M2C_FIELD(p0, u16 *, 0x54) = var_r29;
                M2C_FIELD(p0, s16 *, 0x56) = (s16) (var_r29 >> 0x10U);
                M2C_STRUCT_COPY(((u8*)(p0) + 0xA0) + var_r29, savedataGetStatus((void*)(NULL), 0xF), 0x2400);
                var_r29 += 0x2410;
                break;
            case 8:
                M2C_FIELD(p0, u16 *, 0x58) = var_r29;
                M2C_FIELD(p0, s16 *, 0x5A) = (s16) (var_r29 >> 0x10U);
                M2C_FIELD(p0, s16 *, 0x78) = (s16) (((s32)savedataGetStatus((void*)(NULL), 7) * 4) & 0xFFFC);
                M2C_FIELD(p0, s16 *, 0x7A) = (s16) (((s32)savedataGetStatus((void*)(NULL), 8) * 4) & 0xFFFC);
                M2C_FIELD(p0, s16 *, 0x7C) = (s16) (((s32)savedataGetStatus((void*)(NULL), 9) * 4) & 0xFFFC);
                M2C_FIELD(p0, s16 *, 0x7E) = (s16) (((s32)savedataGetStatus((void*)(NULL), 0x19) * 4) & 0xFFFC);
                M2C_FIELD(p0, s16 *, 0x82) = (s16) (((s32)savedataGetStatus((void*)(NULL), 0x1C) * 4) & 0xFFFC);
                temp_r26_3 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_8 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0x17));
                M2C_FIELD(temp_r26_3, s32 *, 0) = (s32) M2C_FIELD(temp_r3_8, s32 *, 0);
                M2C_FIELD(temp_r26_3, s32 *, 4) = (s32) M2C_FIELD(temp_r3_8, s32 *, 4);
                M2C_STRUCT_COPY(temp_r26_3, temp_r3_8, 0x18);
                M2C_STRUCT_COPY((s32) (temp_r26_3 + 0x1C) + 4, (s32) (temp_r3_8 + 0x1C) + 4, 0x80);
                M2C_STRUCT_COPY((s32) (temp_r26_3 + 0x9C) + 4, (s32) (temp_r3_8 + 0x9C) + 4, 0x600);
                var_r29 += 0x6D0;
                M2C_FIELD(temp_r26_3, s32 *, 0x6A0) = (s32) M2C_FIELD(temp_r3_8, s32 *, 0x6A0);
                M2C_FIELD(temp_r26_3, s32 *, 0x6A4) = (s32) M2C_FIELD(temp_r3_8, s32 *, 0x6A4);
                M2C_STRUCT_COPY(temp_r26_3, temp_r3_8, 0xC);
                break;
            case 9:
                M2C_FIELD(p0, u16 *, 0x5C) = var_r29;
                M2C_FIELD(p0, s16 *, 0x5E) = (s16) (var_r29 >> 0x10U);
                __copy((void *)(((u8*)(p0) + 0xA0) + var_r29), (unsigned short *)(savedataGetStatus((void*)(NULL), 0x10)), (long)(0xB));
                var_r29 += 0x20;
                break;
            case 15:
                if ((*(s32 *)_memcardStatusPtr != 8) && (*(s32 *)_memcardStatusPtr != 0xD) && (*(s32 *)_memcardStatusPtr != 7) && ((u8) _memcard_anySaveOFF_Flag == 0)) {
                    floorMakeSaveData((u8**)(&sp8), (u32*)(&spC));
                }
                M2C_FIELD(p0, u16 *, 0x74) = var_r29;
                M2C_FIELD(p0, s16 *, 0x76) = (s16) (var_r29 >> 0x10U);
                temp_r19 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r3_9 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0x16));
                if ((*(s32 *)_memcardStatusPtr != 8) && (*(s32 *)_memcardStatusPtr != 0xD) && (*(s32 *)_memcardStatusPtr != 7) && ((u8) _memcard_anySaveOFF_Flag == 0)) {
                    memcpy((void*)(temp_r3_9), (const void*)(sp8), spC);
                    GSmemFree((void*)(sp8));
                }
                if ((u8) _memcard_anySaveOFF_Flag == 0) {
                    memcpy((void*)(temp_r19), (const void*)(temp_r3_9), 0xC800U);
                } else {
                    memset((void*)(temp_r19), 0, 0xC800U);
                }
                var_r29 += 0xC810;
                break;
            case 10:
                M2C_FIELD(p0, u16 *, 0x60) = var_r29;
                temp_r0_4 = var_r29 >> 0x10U;
                var_r29 += 0x410;
                M2C_FIELD(p0, s16 *, 0x62) = (s16) temp_r0_4;
                break;
            case 11:
                M2C_FIELD(p0, u16 *, 0x64) = var_r29;
                temp_r0_5 = var_r29 >> 0x10U;
                var_r29 += 0x810;
                M2C_FIELD(p0, s16 *, 0x66) = (s16) temp_r0_5;
                break;
            case 12:
                M2C_FIELD(p0, u16 *, 0x68) = var_r29;
                temp_r0_6 = var_r29 >> 0x10U;
                var_r29 += 0x1010;
                M2C_FIELD(p0, s16 *, 0x6A) = (s16) temp_r0_6;
                break;
            case 13:
                M2C_FIELD(p0, u16 *, 0x6C) = var_r29;
                temp_r0_7 = var_r29 >> 0x10U;
                var_r29 += 0x2010;
                M2C_FIELD(p0, s16 *, 0x6E) = (s16) temp_r0_7;
                break;
            case 14:
                M2C_FIELD(p0, u16 *, 0x70) = var_r29;
                M2C_FIELD(p0, s16 *, 0x72) = (s16) (var_r29 >> 0x10U);
                var_r19_2 = ((u8*)(p0) + 0xA0) + var_r29;
                temp_r21 = var_r19_2 + 0x2298;
                var_r18_2 = (unsigned char *)(savedataGetStatus((void*)(NULL), 0x15));
                do {
                    memcpy((void*)(var_r19_2), (const void*)(var_r18_2), 0xC4U);
                    memcpy((void*)(var_r19_2 + 0xC4), (const void*)(var_r18_2 + 0xC4), 0xC4U);
                    memcpy((void*)(var_r19_2 + 0x188), (const void*)(var_r18_2 + 0x188), 0xC4U);
                    memcpy((void*)(var_r19_2 + 0x24C), (const void*)(var_r18_2 + 0x24C), 0xC4U);
                    memcpy((void*)(var_r19_2 + 0x310), (const void*)(var_r18_2 + 0x310), 0xC4U);
                    temp_r0_8 = M2C_FIELD(var_r18_2, u8 *, 0x3D4);
                    var_r18_2 += 0x3D8;
                    M2C_FIELD(var_r19_2, u8 *, 0x3D4) = temp_r0_8;
                    var_r19_2 += 0x3D8;
                } while (var_r19_2 < temp_r21);
                var_r29 += 0x22B0;
                break;
            }
        }
        var_r4_2 = &(&sp28)[var_r30];
        while (var_r30 < var_r27) {
            temp_r3_10 = M2C_FIELD(var_r4_2, u8 *, 1);
            var_r4_2 += 1;
            var_r30 += 1;
            *var_r28 = temp_r3_10;
            var_r28 += 1;
        }
        var_r27 -= 1;
    }
}
}

#pragma optimize_for_size reset
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
    sums[2] = 0;
    sums[0] = 0;
    sums[1] = 0;
    sums[3] = 0;
    _memcard_encrypt_key[0] = d[0];
    _memcard_encrypt_key[1] = d[1];
    _memcard_encrypt_key[2] = d[2];
    _memcard_encrypt_key[3] = d[3];
    for (i = 4; i < 0x13FE8; i += 4) {
        d[i] -= _memcard_encrypt_key[0];
        d[i + 1] -= _memcard_encrypt_key[1];
        d[i + 2] -= _memcard_encrypt_key[2];
        d[i + 3] -= _memcard_encrypt_key[3];
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
    u32 sums[8];
    volatile int i;
    sums[1] = 0;
    sums[2] = 0;
    sums[3] = 0;
    sums[0] = 0;
    _memcard_encrypt_key[0] = d[0];
    _memcard_encrypt_key[1] = d[1];
    _memcard_encrypt_key[2] = d[2];
    _memcard_encrypt_key[3] = d[3];
    d[11] = 0;
    d[8] = 0;
    d[9] = 0;
    d[6] = 0;
    d[10] = 0;
    d[4] = 0;
    d[5] = 0;
    _memcardSumBlocks(d, sums);
    d[10] = sums[0];
    d[4] = sums[3];
    d[7] = 0;
    d[8] = sums[1];
    d[7] = sums[2] >> 16;
    d[6] = sums[2];
    d[11] = sums[0] >> 16;
    d[9] = sums[1] >> 16;
    d[5] = sums[3] >> 16;
    for (i = 4; i < 0x13FE8; i += 4) {
        d[i] = d[i] + _memcard_encrypt_key[0];
        d[i + 1] += _memcard_encrypt_key[1];
        d[i + 2] += _memcard_encrypt_key[2];
        d[i + 3] += _memcard_encrypt_key[3];
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
