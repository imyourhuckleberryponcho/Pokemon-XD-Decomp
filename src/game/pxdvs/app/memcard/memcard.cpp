// Memory card save/load state machine over the Dolphin CARD API.
#include <dolphin/types.h>
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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

// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
// ---- draft prelude (m2c helper macros; remove when cleaning up) ----
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
enum CARDCallback { CARDCallback_draft_dummy };
struct CARDFileInfo;
struct CARDStat;
struct Gamedata;
struct GamedataSave;
struct Hero;
struct OSCalendarTime;
enum OSTime { OSTime_draft_dummy };

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
    s32 msgType;       // 0x04
    s32 result;        // 0x08
    s32 state;         // 0x0c
    s32 resumeState;   // 0x10
    s32 arg14;         // 0x14
    s32 sectorSize;
    s32 memSize;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 delay;         // 0x34
    u8 pad38[0x3c - 0x38];
    u8 cbDone;
    u8 f3d;
    u8 f3e;
    u8 f3f;
    u8 f40;
    u8 valid;          // 0x41
    u8 pad42[0x50 - 0x42];
    void* buf50;
    void* buf54;
    void* savedata;    // 0x58
    s32 f5c;
    s32 f60;
    int gapp;          // 0x64
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
// ---- draft declarations ----
struct CARDFileInfo {
    u8 _draft[1];
};
struct CARDStat {
    u8 _draft[1];
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
    u8 _draft[1];
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
u8 GSgfxResetDisable(s32*, s32);
s32 GSgfxResetRestore(u8, s32*);
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
extern s32 _memcardBannerImage;
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

// ---- draft declarations ----


extern "C" {
extern s32 jtbl_3110;
}

// ---- draft declarations ----



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
    s32 idx = _memcardStatusPtr->f20;
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
            if (_memcardStatusPtr->kind < 4) {
                if (_memcardStatusPtr->kind < 1) {
                } else {
                    _memcardStatusPtr->msgType = 0xC;
                    _memcardStatusPtr->result = 1;
                    if (_memcardStatusPtr->f40 != 0) {
                        return 0x11;
                    }
                    return 0x2C;
                }
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
#pragma optimize_for_size on
u32 fn_801CC508() {
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp8;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_ret;
    s32 var_ctr;
    s8 *temp_r30;
    s8 *var_r4;

    temp_ret = OSGetTime();
    OSTicksToCalendarTime((OSTime)(temp_ret), (OSCalendarTime*)((OSCalendarTime *) (u32) (u64) temp_ret));
    temp_r30 = M2C_FIELD(_memcardStatusPtr, s8 **, 0x50);
    memset((void*)(temp_r30), 0, 0x6000U);
    temp_r3 = pokecoloGetCountryCode();
    if (temp_r3 != 0) {
        if ((temp_r3 >= 0) && (temp_r3 < 3)) {
            strcpy((char*)(temp_r30), (const char*)(&_memcardBannerImage + 0x3A44));
            strcpy((char*)(temp_r30 + 0x20), (const char*)(&_memcardBannerImage + 0x3A50));
            M2C_FIELD(temp_r30, s8 *, 3) = -0x17;
            M2C_FIELD(temp_r30, s8 *, 0x2A) = (s8) ((((sp18 + 1) / 10) % 10) + 0x30);
            M2C_FIELD(temp_r30, s8 *, 0x2B) = (s8) (((sp18 + 1) % 10) + 0x30);
            M2C_FIELD(temp_r30, s8 *, 0x2D) = (s8) (((sp14 / 10) % 10) + 0x30);
            M2C_FIELD(temp_r30, s8 *, 0x32) = (s8) (((sp1C / 10) % 10) + 0x30);
            M2C_FIELD(temp_r30, s8 *, 0x2E) = (s8) ((sp14 % 10) + 0x30);
            M2C_FIELD(temp_r30, s8 *, 0x33) = (s8) ((sp1C % 10) + 0x30);
        }
    } else {
        strcpy((char*)(temp_r30), (const char*)(&_memcardBannerImage + 0x3A1C));
        strcpy((char*)(temp_r30 + 0x20), (const char*)(&_memcardBannerImage + 0x3A2C));
        M2C_FIELD(temp_r30, s8 *, 0x2F) = (s8) (((sp1C / 10) % 10) + 0x30);
        M2C_FIELD(temp_r30, s8 *, 0x30) = (s8) ((sp1C % 10) + 0x30);
        M2C_FIELD(temp_r30, s8 *, 0x32) = (s8) ((((sp18 + 1) / 10) % 10) + 0x30);
        M2C_FIELD(temp_r30, s8 *, 0x33) = (s8) (((sp18 + 1) % 10) + 0x30);
        M2C_FIELD(temp_r30, s8 *, 0x35) = (s8) (((sp14 / 10) % 10) + 0x30);
        M2C_FIELD(temp_r30, s8 *, 0x36) = (s8) ((sp14 % 10) + 0x30);
    }
    memcpy((void*)(temp_r30 + 0x40), (const void*)(&_memcardBannerImage), 0x1800U);
    memcpy((void*)(temp_r30 + 0x1840), (const void*)(&_memcardBannerImage + 0x1800), 0x2200U);
    var_r4 = temp_r30;
    var_ctr = 0xE9;
    do {
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 4));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 8));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0xC));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x10));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x14));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x18));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x1C));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x20));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x24));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x28));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x2C));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x30));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x34));
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + M2C_FIELD(var_r4, s32 *, 0x38));
        temp_r0 = M2C_FIELD(var_r4, s32 *, 0x3C);
        var_r4 += 0x40;
        M2C_FIELD(temp_r30, s32 *, 0x3A40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x3A40) + temp_r0);
        var_ctr -= 1;
    } while (var_ctr != 0);
    return 0x12U;
}
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
    s16 temp_r6_2;
    u16 var_r29;
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
    u8 *var_r19_2;
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
static u32 _memcardCardOpen() {
    s32 saved_reg_r28;
    s32 sp120;
    s32 sp38;
    u32 sp3C;
    s32 spA4;
    s32 spA8;
    s32 unksp10;
    s32 unksp7C;
    s32 unkspE8;
    s32 spC;
    s32 sp8;
    s32 *temp_r28;
    s32 var_r30;
    s32 temp_r0;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 *temp_r31;
    s32 var_r31;
    u32 var_r3;
    u8 var_r0;
    u8 var_r0_2;

    var_r28 = saved_reg_r28;
    CARDFreeBlocks(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (s32*)(&spC), (s32*)(&sp8));
    temp_r3 = pokecoloGetCountryCode();
    if (temp_r3 != 0) {
        if ((temp_r3 >= 0) && (temp_r3 < 3)) {
            var_r28_2 = 0;
            temp_r30 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x14);
            temp_r31 = (long *)(_memcardStatusPtr + 0x8C);
loop_33:
            var_r29 = CARDFastOpen(temp_r30, var_r28_2, (CARDFileInfo*)((CARDFileInfo *) temp_r31));
            if (var_r29 == 0) {
                var_r29 = CARDGetStatus(temp_r30, var_r28_2, (CARDStat*)(&unksp10));
                if (var_r29 == 0) {
                    temp_r3_2 = pokecoloGetCountryCode();
                    switch (temp_r3_2) {            /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        if ((strcmp((const char*)(&unksp10), (const char*)("PokemonXD")) == 0) && (sp38 == (u32) *"GXXJ") && (sp3C == (s16) *"01")) {
                            var_r0 = 1;
                        } else {
                            goto block_53;
                        }
                        break;
                    case 1:                         /* switch 2 */
                        if ((strcmp((const char*)(&unksp10), (const char*)("PokemonXD")) == 0) && (sp38 == (u32) *"GXXE") && (sp3C == (s16) *"01")) {
                            var_r0 = 1;
                        } else {
                            goto block_53;
                        }
                        break;
                    case 2:                         /* switch 2 */
                        if ((strcmp((const char*)(&unksp10), (const char*)("PokemonXD")) == 0) && (sp38 == (u32) *"GXXP") && (sp3C == (s16) *"01")) {
                            var_r0 = 1;
                        } else {
                            goto block_53;
                        }
                        break;
                    }
                } else {
block_53:
                    var_r0 = 0;
                }
                if (var_r0 != 0) {
                    var_r29 = 0;
                } else {
                    goto block_56;
                }
            } else {
block_56:
                var_r28_2 += 1;
                if (var_r28_2 >= 0x7F) {
                    if (var_r29 == 0) {
                        var_r29 = -4;
                    }
                } else {
                    goto loop_33;
                }
            }
            var_r28 = var_r29;
        }
    } else {
        var_r31 = 0;
        temp_r29 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x14);
        temp_r28 = (long *)(_memcardStatusPtr + 0x8C);
loop_5:
        var_r30 = CARDFastOpen(temp_r29, var_r31, (CARDFileInfo*)((CARDFileInfo *) temp_r28));
        if (var_r30 == 0) {
            var_r30 = CARDGetStatus(temp_r29, var_r31, (CARDStat*)(&unksp7C));
            if (var_r30 == 0) {
                temp_r3_3 = pokecoloGetCountryCode();
                switch (temp_r3_3) {                /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    if ((strcmp((const char*)(&unksp7C), (const char*)("PokemonXD")) == 0) && (spA4 == (u32) *"GXXJ") && (spA8 == (s16) *"01")) {
                        var_r0_2 = 1;
                    } else {
                        goto block_25;
                    }
                    break;
                case 1:                             /* switch 1 */
                    if ((strcmp((const char*)(&unksp7C), (const char*)("PokemonXD")) == 0) && (spA4 == (u32) *"GXXE") && (spA8 == (s16) *"01")) {
                        var_r0_2 = 1;
                    } else {
                        goto block_25;
                    }
                    break;
                case 2:                             /* switch 1 */
                    if ((strcmp((const char*)(&unksp7C), (const char*)("PokemonXD")) == 0) && (spA4 == (u32) *"GXXP") && (spA8 == (s16) *"01")) {
                        var_r0_2 = 1;
                    } else {
                        goto block_25;
                    }
                    break;
                }
            } else {
block_25:
                var_r0_2 = 0;
            }
            if (var_r0_2 != 0) {
                var_r30 = 0;
            } else {
                goto block_28;
            }
        } else {
block_28:
            var_r31 += 1;
            if (var_r31 >= 0x7F) {
                if (var_r30 == 0) {
                    var_r30 = -4;
                }
            } else {
                goto loop_5;
            }
        }
        var_r28 = var_r30;
    }
    switch (var_r28) {                              /* switch 3; irregular */
    case 0:                                         /* switch 3 */
        M2C_FIELD(_memcardStatusPtr, s8 *, 0x3E) = 1;
        var_r28 = CARDGetStatus(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), M2C_FIELD(_memcardStatusPtr, s32 *, 0x90), (CARDStat*)(&unkspE8));
        if (var_r28 == 0) {
            if ((u32) (sp120 + 0x10000) != -1U) {
                if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0) == 0xC) {
                    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 2;
                    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0xB;
                    return 0x30U;
                }
                var_r3 = 0x19;
                if ((s32) (u16)M2C_FIELD(_memcardStatusPtr, s32 *, 0) == 3) {
                    return 0x1CU;
                }
                /* Duplicate return node #82. Try simplifying control flow for better match */
                return var_r3;
            }
            var_r28 = -4;
            spC += 0x56000;
            sp8 += 1;
        case -4:                                    /* switch 3 */
            temp_r0 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
            switch (temp_r0) {                      /* switch 4; irregular */
            case 1:                                 /* switch 4 */
                if (spC < 0x56000) {
                    var_r28 = -9;
                    goto block_81;
                }
                if (sp8 < 1) {
                    var_r28 = -8;
                    goto block_81;
                }
                M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 6;
                M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0xA;
                return 0x30U;
            case 9:                                 /* switch 4 */
                M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 2;
                M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0xB;
                return 0x30U;
            }
        } else {
        default:                                    /* switch 3 */
block_81:
            var_r3 = 0x2B;
            M2C_FIELD(_memcardStatusPtr, s32 *, 4) = var_r28;
            return var_r3;
        }
        break;
    }
}
}


static s32 _memcardMergeDataPack()
{
    u8* data = (u8*)_memcardStatusPtr->buf50 + 8;
    void* save = _memcardGetMultiSaveDataToSTRUCT(data, 1);
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
    sums[0] = 0;
    sums[1] = 0;
    sums[2] = 0;
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
    stored[0] = d[10] | (d[11] << 16);
    stored[1] = d[8] | (d[9] << 16);
    stored[3] = d[4] | (d[5] << 16);
    d[10] = 0;
    d[11] = 0;
    d[8] = 0;
    d[9] = 0;
    d[6] = 0;
    d[7] = 0;
    d[4] = 0;
    d[5] = 0;
    _memcardSumBlocks(d, sums);
    return sums[0] == stored[0] && sums[1] == stored[1] && sums[2] == stored[2] && sums[3] == stored[3];
}

static void _memcard_Encryption(void* data)
{
    u16* d = (u16*)data;
    u32 sums[4];
    volatile int i;
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
        d[i] = d[i] + _memcard_encrypt_key[0];
        d[i + 1] += _memcard_encrypt_key[1];
        d[i + 2] += _memcard_encrypt_key[2];
        d[i + 3] += _memcard_encrypt_key[3];
        _memcardKeyStep(_memcard_encrypt_key);
    }
}
extern "C++" {
static void _memcardJobMain(u32 p0, u32 p1) {
    s32 var_r31;
    s32 saved_reg_r31;
    s32 unksp14;
    s32 unksp24;
    u64 sp20;
    u64 sp18;
    u64 sp10;
    u8 sp8;
    Gamedata *temp_r3_7;
    GamedataSave *temp_ret;
    GamedataSave *temp_ret_2;
    s32 *var_r3_26;
    s32 *var_r7;
    s32 temp_cr0_eq;
    s32 temp_r0_10;
    s32 temp_r0_11;
    s32 temp_r0_12;
    s32 temp_r0_13;
    s32 temp_r0_14;
    s32 temp_r0_15;
    s32 temp_r0_16;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_7;
    s32 temp_r0_8;
    s32 temp_r27;
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 temp_r4;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_ret_3;
    s32 temp_ret_7;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r29_2;
    s32 var_r30;
    s32 saved_reg_r30;
    s32 var_r3;
    s32 var_r3_10;
    s32 var_r3_11;
    s32 var_r3_12;
    s32 var_r3_13;
    s32 var_r3_14;
    s32 var_r3_15;
    s32 var_r3_16;
    s32 var_r3_17;
    s32 var_r3_18;
    s32 var_r3_19;
    s32 var_r3_20;
    s32 var_r3_21;
    s32 var_r3_22;
    s32 var_r3_23;
    s32 var_r3_24;
    s32 var_r3_25;
    s32 var_r3_27;
    s32 var_r3_28;
    s32 var_r3_29;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r3_6;
    s32 var_r3_7;
    s32 var_r3_8;
    s32 var_r3_9;
    s32 var_r5_6;
    s32 var_r6;
    s8 *var_r27;
    u32 temp_r0;
    u32 temp_r0_6;
    u32 temp_r0_9;
    u32 temp_r27_3;
    u32 temp_r29_3;
    u32 temp_r29_4;
    u32 temp_r3_10;
    u32 temp_r3_5;
    u32 temp_r5;
    u32 temp_ret_4;
    u32 var_r0;
    u32 var_r0_2;
    u32 var_r0_3;
    u32 var_r0_4;
    u32 var_r0_5;
    u32 var_r0_6;
    u32 var_r0_7;
    u32 var_r0_8;
    u32 var_r0_9;
    u32 var_r29;
    u32 var_r4;
    u32 var_r5;
    u32 var_r5_10;
    u32 var_r5_11;
    u32 var_r5_12;
    u32 var_r5_2;
    u32 var_r5_3;
    u32 var_r5_4;
    u32 var_r5_5;
    u32 var_r5_7;
    u32 var_r5_8;
    u32 var_r5_9;
    u32 var_r6_2;
    u8 temp_r0_5;
    u8 temp_ret_5;
    u8 temp_ret_6;
    u8 *temp_r27_2;
    u8 *temp_r28;
    u8 *temp_r29_2;
    u8 *temp_r3_6;

    var_r30 = saved_reg_r30;
    var_r31 = saved_reg_r31;
    var_r4 = p1;
    _memcard_new_saveDataCrateFlag = 1;
loop_1:
    temp_r0 = M2C_FIELD(_memcardStatusPtr, u32 *, 0xC);
    switch (temp_r0) {
    case 0:
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x60) = 0x32;
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) = 0U;
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3F) = GSgfxResetDisable((long *)(_memcardStatusPtr), (long)(0));
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3C) = 0U;
    _memcard_gba2mode = 0;
    GSgfxResetRestore((unsigned char)(M2C_FIELD(_memcardStatusPtr, u8 *, 0x3F)), (long *)(_memcardStatusPtr));
    temp_r0_2 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_2 == 4) {
        goto block_11;
    }
    if (temp_r0_2 >= 4) {
        goto block_8;
    }
    if (temp_r0_2 >= 3) {
        goto block_14;
    }
    if (temp_r0_2 >= 1) {
        goto block_10;
    }
    goto block_14;
block_8:
    if (temp_r0_2 == 8) {
        goto block_14;
    }
    goto block_14;
block_10:
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x41) = 0U;
    goto block_14;
block_11:
    if (gamedatasaveGetStatus((Gamedata*)(NULL), 4U) != 0) {
        goto block_13;
    }
    M2C_FIELD(_memcardStatusPtr, s32 *, 0) = 9;
block_13:
    floorMemoryCardSaveCallback();
block_14:
    var_r4 = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x24) = 0;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 1U;
    goto block_396;
    case 1:
    var_r3 = CARDProbeEx(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (s32*)(_memcardStatusPtr + 0x18), (s32*)(_memcardStatusPtr + 0x1C));
    temp_r27 = var_r3;
    if (var_r3 != 0) {
        goto block_17;
    }
    var_r3 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_17:
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r3;
    if (temp_r27 == 0) {
        goto block_22;
    }
    if (temp_r27 >= 0) {
        goto block_23;
    }
    if (temp_r27 >= -1) {
        goto block_21;
    }
    goto block_23;
block_21:
    var_r4 = 1;
    goto block_26;
block_22:
    var_r4 = 2;
    goto block_26;
block_23:
    temp_r3 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x24);
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x24) = (s32) (temp_r3 + 1);
    if (temp_r3 >= 6) {
        goto block_25;
    }
    var_r4 = 1;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = -1;
    goto block_26;
block_25:
    var_r4 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = temp_r27;
block_26:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r4;
    goto block_396;
    case 2:
    var_r3_2 = CARDMountAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x54)), (CARDCallback)((s32) _memcardCallback), (CARDCallback)(0));
    if (var_r3_2 != 0) {
        goto block_29;
    }
    var_r3_2 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_29:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_2;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 3U;
    goto block_396;
    case 3:
    var_r3_3 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_3 == -1) {
        goto block_32;
    }
    goto block_33;
block_32:
    var_r3_3 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_3;
block_33:
    if (var_r3_3 == -6) {
        goto block_42;
    }
    if (var_r3_3 >= -6) {
        goto block_37;
    }
    if (var_r3_3 == -0xD) {
        goto block_42;
    }
    goto block_43;
block_37:
    if (var_r3_3 == 0) {
        goto block_42;
    }
    if (var_r3_3 >= 0) {
        goto block_43;
    }
    if (var_r3_3 >= -1) {
        goto block_41;
    }
    goto block_43;
block_41:
    var_r0 = 3;
    goto block_44;
block_42:
    var_r0 = 4;
    goto block_44;
block_43:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_3;
block_44:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0;
    goto block_396;
    case 4:
    var_r3_4 = CARDCheckAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (CARDCallback)(0));
    if (var_r3_4 != 0) {
        goto block_47;
    }
    var_r3_4 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_47:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_4;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 5U;
    goto block_396;
    case 5:
    var_r3_5 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_5 == -1) {
        goto block_50;
    }
    goto block_51;
block_50:
    var_r3_5 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r3_5;
block_51:
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0x1C) == 0x2000) {
        goto block_53;
    }
    var_r3_5 = -6;
block_53:
    if (var_r3_5 == -6) {
        goto block_71;
    }
    if (var_r3_5 >= -6) {
        goto block_57;
    }
    if (var_r3_5 == -0xD) {
        goto block_71;
    }
    goto block_76;
block_57:
    if (var_r3_5 == 0) {
        goto block_62;
    }
    if (var_r3_5 >= 0) {
        goto block_76;
    }
    if (var_r3_5 >= -1) {
        goto block_61;
    }
    goto block_76;
block_61:
    var_r4 = 5;
    goto block_77;
block_62:
    temp_r0_3 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_3 == 9) {
        goto block_70;
    }
    if (temp_r0_3 >= 9) {
        goto block_66;
    }
    if (temp_r0_3 == 3) {
        goto block_70;
    }
    goto block_67;
block_66:
    if (temp_r0_3 == 0xB) {
        goto block_70;
    }
block_67:
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x41) == 0) {
        goto block_70;
    }
    CARDGetSerialNo(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (u64*)(&sp20));
    if (((unksp24 ^ M2C_FIELD(_memcardStatusPtr, s32 *, 0x4C)) | ((s32) sp20 ^ M2C_FIELD(_memcardStatusPtr, s32 *, 0x48))) == 0) {
        goto block_70;
    }
    var_r4 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0x10;
    goto block_77;
block_70:
    var_r4 = 9;
    goto block_77;
block_71:
    temp_r0_4 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_4 == 9) {
        goto block_75;
    }
    if (temp_r0_4 >= 9) {
        goto block_76;
    }
    if (temp_r0_4 == 1) {
        goto block_75;
    }
    goto block_76;
block_75:
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 7;
    var_r4 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 6;
    goto block_77;
block_76:
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = var_r3_5;
    var_r4 = 0x2B;
block_77:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r4;
    goto block_396;
    case 6:
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 4) == 0) {
        goto block_82;
    }
    var_r4 = (u32) (u64) CARDFormatAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (CARDCallback)(0));
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x3C) == 0) {
        goto block_81;
    }
    var_r5 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0;
    goto block_83;
block_81:
    var_r4 = 7;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x60) = 7;
    var_r5 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 4;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 7;
    goto block_83;
block_82:
    var_r5 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0;
block_83:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5;
    goto block_396;
    case 7:
    GSgfxResetDisable(&jtbl_4196, (s32) var_r4);
    var_r3_6 = CARDFormatAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (CARDCallback)(0));
    var_r4 = (u32) _memcardStatusPtr;
    if ((u8) M2C_FIELD(var_r4, u8 *, 0x3C) == 0) {
        goto block_86;
    }
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_6;
    var_r0_2 = 0x2B;
    goto block_89;
block_86:
    if (var_r3_6 != 0) {
        goto block_88;
    }
    var_r3_6 = CARDGetResultCode(M2C_FIELD(var_r4, s32 *, 0x14));
block_88:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_2 = 8;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_6;
block_89:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_2;
    goto block_396;
    case 8:
    var_r3_7 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_7 == -1) {
        goto block_92;
    }
    goto block_93;
block_92:
    var_r3_7 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_7;
block_93:
    if (var_r3_7 == 0) {
        goto block_98;
    }
    if (var_r3_7 >= 0) {
        goto block_99;
    }
    if (var_r3_7 >= -1) {
        goto block_97;
    }
    goto block_99;
block_97:
    var_r5_2 = 8;
    goto block_100;
block_98:
    GSgfxResetRestore(M2C_FIELD(_memcardStatusPtr, u8 *, 0x3F), (s32 *) var_r4);
    var_r4 = 0x32;
    var_r5_2 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x60) = 0x32;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 9;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 9;
    goto block_100;
block_99:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_2 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_7;
block_100:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_2;
    goto block_396;
    case 9:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, u32 *, 0xC) = _memcardCardOpen();
    goto block_396;
    case 10:
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 4) != 0) {
        goto block_104;
    }
    var_r5_3 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0;
    goto block_105;
block_104:
    var_r4 = 0xD;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 3;
    var_r5_3 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x60) = 0xD;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0xB;
block_105:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_3;
    goto block_396;
    case 11:
    GSgfxResetDisable(&jtbl_4196, (s32) var_r4);
    temp_r3_2 = pokecoloGetCountryCode();
    if (temp_r3_2 == 0) {
        goto block_110;
    }
    if (temp_r3_2 < 0) {
        goto block_112;
    }
    if (temp_r3_2 >= 3) {
        goto block_112;
    }
    goto block_111;
block_110:
    var_r30 = CARDDeleteAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (const char*)("PokemonXD"), (CARDCallback)(0));
    goto block_112;
block_111:
    var_r30 = CARDDeleteAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (const char*)("PokemonXD"), (CARDCallback)(0));
block_112:
    var_r3_8 = var_r30;
    if (var_r30 != 0) {
        goto block_114;
    }
    var_r3_8 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_114:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_8;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0xCU;
    goto block_396;
    case 12:
    var_r3_9 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_9 == -1) {
        goto block_117;
    }
    goto block_118;
block_117:
    var_r3_9 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_9;
block_118:
    if (var_r3_9 == -1) {
        goto block_124;
    }
    if (var_r3_9 >= -1) {
        goto block_122;
    }
    if (var_r3_9 == -4) {
        goto block_125;
    }
    goto block_128;
block_122:
    if (var_r3_9 >= 1) {
        goto block_128;
    }
    goto block_125;
block_124:
    var_r5_4 = 0xC;
    goto block_129;
block_125:
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0) != 0xC) {
        goto block_127;
    }
    var_r5_4 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0xA;
    goto block_129;
block_127:
    var_r5_4 = 0xD;
    goto block_129;
block_128:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_4 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_9;
block_129:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_4;
    goto block_396;
    case 13:
    temp_r3_3 = pokecoloGetCountryCode();
    if (temp_r3_3 == 0) {
        goto block_134;
    }
    if (temp_r3_3 < 0) {
        goto block_136;
    }
    if (temp_r3_3 >= 3) {
        goto block_136;
    }
    goto block_135;
block_134:
    var_r31 = CARDCreateAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (const char*)("PokemonXD"), 0x56000U, (CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (CARDCallback)(0));
    goto block_136;
block_135:
    var_r31 = CARDCreateAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (const char*)("PokemonXD"), 0x56000U, (CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (CARDCallback)(0));
block_136:
    var_r3_10 = var_r31;
    if (var_r31 != 0) {
        goto block_138;
    }
    var_r3_10 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_138:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_10;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0xEU;
    goto block_396;
    case 14:
    var_r3_11 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_11 == -1) {
        goto block_141;
    }
    goto block_142;
block_141:
    var_r3_11 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_11;
block_142:
    if (var_r3_11 == 0) {
        goto block_147;
    }
    if (var_r3_11 >= 0) {
        goto block_148;
    }
    if (var_r3_11 >= -1) {
        goto block_146;
    }
    goto block_148;
block_146:
    var_r5_5 = 0xE;
    goto block_149;
block_147:
    var_r5_5 = 0xF;
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3E) = 1U;
    goto block_149;
block_148:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_5 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_11;
block_149:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_5;
    goto block_396;
    case 15:
    CARDGetAttributes(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), M2C_FIELD(_memcardStatusPtr, s32 *, 0x90), (u8*)(&sp8));
    temp_r0_5 = sp8 | 0x18;
    sp8 = temp_r0_5;
    var_r3_12 = CARDSetAttributesAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), M2C_FIELD(_memcardStatusPtr, s32 *, 0x90), temp_r0_5, (CARDCallback)(0));
    if (var_r3_12 != 0) {
        goto block_152;
    }
    var_r3_12 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_152:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_12;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x10U;
    goto block_396;
    case 16:
    var_r3_13 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_13 == -1) {
        goto block_155;
    }
    goto block_156;
block_155:
    var_r3_13 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_13;
block_156:
    if (var_r3_13 == 0) {
        goto block_161;
    }
    if (var_r3_13 >= 0) {
        goto block_162;
    }
    if (var_r3_13 >= -1) {
        goto block_160;
    }
    goto block_162;
block_160:
    var_r0_3 = 0x10;
    goto block_163;
block_161:
    var_r0_3 = 0x11;
    goto block_163;
block_162:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_3 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_13;
block_163:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_3;
    goto block_396;
    case 17:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, u32 *, 0xC) = fn_801CC508();
    goto block_396;
    case 18:
    var_r5_6 = 0x6000;
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) == 0) {
        goto block_167;
    }
    var_r5_6 = 0x4000;
block_167:
    var_r3_14 = CARDWriteAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)), var_r5_6, 0, (CARDCallback)(0));
    if (var_r3_14 != 0) {
        goto block_169;
    }
    var_r3_14 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_169:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_14;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x13U;
    goto block_396;
    case 19:
    var_r3_15 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_15 == -1) {
        goto block_172;
    }
    goto block_173;
block_172:
    var_r3_15 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_15;
block_173:
    if (var_r3_15 == 0) {
        goto block_178;
    }
    if (var_r3_15 >= 0) {
        goto block_181;
    }
    if (var_r3_15 >= -1) {
        goto block_177;
    }
    goto block_181;
block_177:
    var_r0_4 = 0x13;
    goto block_182;
block_178:
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) == 0) {
        goto block_180;
    }
    var_r0_4 = 0x2C;
    goto block_182;
block_180:
    var_r0_4 = 0x14;
    goto block_182;
block_181:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_4 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_15;
block_182:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_4;
    goto block_396;
    case 20:
    temp_r27_2 = M2C_FIELD(_memcardStatusPtr, u8 **, 0x50);
    memset((void*)(temp_r27_2), 0, 0x2000U);
    var_r4 = 0;
    M2C_FIELD(temp_r27_2, s8 *, 0) = 1;
    M2C_FIELD(temp_r27_2, s8 *, 1) = 1;
    M2C_FIELD(temp_r27_2, s8 *, 2) = 1;
    M2C_FIELD(temp_r27_2, s8 *, 3) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) = 0;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x15U;
    goto block_396;
    case 21:
    var_r3_16 = CARDWriteAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)), 0x2000, (M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) * 0x28000) + 0x6000, (CARDCallback)(0));
    if (var_r3_16 != 0) {
        goto block_186;
    }
    var_r3_16 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_186:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_16;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x16U;
    goto block_396;
    case 22:
    var_r3_17 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_17 == -1) {
        goto block_189;
    }
    goto block_190;
block_189:
    var_r3_17 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_17;
block_190:
    if (var_r3_17 == 0) {
        goto block_195;
    }
    if (var_r3_17 >= 0) {
        goto block_198;
    }
    if (var_r3_17 >= -1) {
        goto block_194;
    }
    goto block_198;
block_194:
    var_r0_5 = 0x16;
    goto block_199;
block_195:
    var_r4 = (u32) _memcardStatusPtr;
    temp_r0_6 = M2C_FIELD(var_r4, u32 *, 0x20) + 1;
    M2C_FIELD(var_r4, u32 *, 0x20) = temp_r0_6;
    if (temp_r0_6 >= 2U) {
        goto block_197;
    }
    var_r0_5 = 0x15;
    goto block_199;
block_197:
    var_r0_5 = 0x17;
    goto block_199;
block_198:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_5 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_17;
block_199:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_5;
    goto block_396;
    case 23:
    temp_r3_4 = CARDGetStatus(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), M2C_FIELD(_memcardStatusPtr, s32 *, 0x90), (CARDStat*)((CARDStat *) (_memcardStatusPtr + 0xA0)));
    if (temp_r3_4 != 0) {
        goto block_204;
    }
    M2C_FIELD(_memcardStatusPtr, s32 *, 0xD8) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0xD0) = 0x40;
    M2C_FIELD(_memcardStatusPtr, u8 *, 0xCE) = (u8) ((M2C_FIELD(_memcardStatusPtr, u8 *, 0xCE) & 0xFFFFFFFC) | 2);
    M2C_FIELD(_memcardStatusPtr, u8 *, 0xCE) = (u8) (M2C_FIELD(_memcardStatusPtr, u8 *, 0xCE) & 0xFFFFFFFB);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFFFFC) | 1);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFFFFC) | 1);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFFFF3) | 4);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFFFF3) | 4);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFFFCF) | 0x10);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFFFCF) | 0x10);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFFF3F) | 0x40);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFFF3F) | 0x40);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFFCFF) | 0x100);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFFCFF) | 0x100);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFF3FF) | 0x400);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFF3FF) | 0x400);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFFCFFF) | 0x1000);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFFCFFF) | 0x1000);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD4) & 0xFFFF3FFF) | 0x4000);
    M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) = (u16) ((M2C_FIELD(_memcardStatusPtr, u16 *, 0xD6) & 0xFFFF3FFF) | 0x4000);
    var_r3_18 = CARDSetStatusAsync(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), M2C_FIELD(_memcardStatusPtr, s32 *, 0x90), (CARDStat*)((CARDStat *) (_memcardStatusPtr + 0xA0)), (CARDCallback)(0));
    if (var_r3_18 != 0) {
        goto block_203;
    }
    var_r3_18 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_203:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_6 = 0x18;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_18;
    goto block_205;
block_204:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_6 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = temp_r3_4;
block_205:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_6;
    goto block_396;
    case 24:
    var_r3_19 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_19 == -1) {
        goto block_208;
    }
    goto block_209;
block_208:
    var_r3_19 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_19;
block_209:
    if (var_r3_19 == 0) {
        goto block_214;
    }
    if (var_r3_19 >= 0) {
        goto block_217;
    }
    if (var_r3_19 >= -1) {
        goto block_213;
    }
    goto block_217;
block_213:
    var_r5_7 = 0x18;
    goto block_218;
block_214:
    var_r4 = (u32) _memcardStatusPtr;
    if ((s32) M2C_FIELD(var_r4, s32 *, 0) != 9) {
        goto block_216;
    }
    _memcardDuplicateSaveData_multi((void*)(M2C_FIELD(var_r4, s32 *, 0x50) + 8));
    var_r4 = 0;
    var_r5_7 = 0x25;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x2C) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) = -1;
    goto block_218;
block_216:
    M2C_FIELD(var_r4, s32 *, 4) = 0xB;
    var_r5_7 = 0x2C;
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = 2;
    goto block_218;
block_217:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_7 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_19;
block_218:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_7;
    goto block_396;
    case 25:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x1AU;
    goto block_396;
    case 26:
    var_r3_20 = CARDReadAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)), 0x4000, 0, (CARDCallback)(0));
    if (var_r3_20 != 0) {
        goto block_222;
    }
    var_r3_20 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_222:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_20;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x1BU;
    goto block_396;
    case 27:
    var_r3_21 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    var_r29 = 0U;
    if (var_r3_21 == -1) {
        goto block_225;
    }
    goto block_226;
block_225:
    var_r3_21 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_21;
block_226:
    if (var_r3_21 == 0) {
        goto block_231;
    }
    if (var_r3_21 >= 0) {
        goto block_236;
    }
    if (var_r3_21 >= -1) {
        goto block_230;
    }
    goto block_236;
block_230:
    var_r0_7 = 0x1B;
    goto block_237;
block_231:
    var_r4 = (u32) M2C_FIELD(_memcardStatusPtr, u8 **, 0x50);
    var_r5_8 = var_r4;
    var_ctr = 0xE9;
loop_232:
    temp_r0_7 = M2C_FIELD(var_r5_8, s32 *, 0x3C);
    temp_r29 = var_r29 + M2C_FIELD(var_r5_8, s32 *, 0) + M2C_FIELD(var_r5_8, s32 *, 4) + M2C_FIELD(var_r5_8, s32 *, 8) + M2C_FIELD(var_r5_8, s32 *, 0xC) + M2C_FIELD(var_r5_8, s32 *, 0x10) + M2C_FIELD(var_r5_8, s32 *, 0x14) + M2C_FIELD(var_r5_8, s32 *, 0x18) + M2C_FIELD(var_r5_8, s32 *, 0x1C) + M2C_FIELD(var_r5_8, s32 *, 0x20) + M2C_FIELD(var_r5_8, s32 *, 0x24) + M2C_FIELD(var_r5_8, s32 *, 0x28) + M2C_FIELD(var_r5_8, s32 *, 0x2C) + M2C_FIELD(var_r5_8, s32 *, 0x30) + M2C_FIELD(var_r5_8, s32 *, 0x34) + M2C_FIELD(var_r5_8, s32 *, 0x38);
    var_r5_8 += 0x40;
    var_r29 = temp_r29 + temp_r0_7;
    var_ctr -= 1;
    if (var_ctr != 0) {
        goto loop_232;
    }
    if (var_r29 == (u32) M2C_FIELD(var_r4, u32 *, 0x3A40)) {
        goto block_235;
    }
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) = 1U;
block_235:
    var_r0_7 = 0x1C;
    goto block_237;
block_236:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_7 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_21;
block_237:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_7;
    goto block_396;
    case 28:
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x30) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) = 0;
    temp_r0_8 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_8 == 3) {
        goto block_246;
    }
    if (temp_r0_8 >= 3) {
        goto block_242;
    }
    if (temp_r0_8 >= 1) {
        goto block_244;
    }
    goto block_247;
block_242:
    if (temp_r0_8 == 8) {
        goto block_246;
    }
    goto block_247;
block_244:
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) == 0) {
        goto block_246;
    }
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 5;
    goto block_248;
block_246:
    var_r4 = 0x1D;
    goto block_249;
block_247:
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 2;
block_248:
    var_r4 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0x1D;
block_249:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r4;
    goto block_396;
    case 29:
    temp_r4 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x20);
    var_r3_22 = CARDReadAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(((temp_r4 << 9) + 0x30000 + M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)) - 0x8000), 0x200, (temp_r4 * 0x28000) + 0x6000, (CARDCallback)(0));
    if (var_r3_22 != 0) {
        goto block_252;
    }
    var_r3_22 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_252:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_22;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x1EU;
    goto block_396;
    case 30:
    var_r3_23 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_23 == -1) {
        goto block_255;
    }
    goto block_256;
block_255:
    var_r3_23 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_23;
block_256:
    if (var_r3_23 == 0) {
        goto block_261;
    }
    if (var_r3_23 >= 0) {
        goto block_264;
    }
    if (var_r3_23 >= -1) {
        goto block_260;
    }
    goto block_264;
block_260:
    var_r0_8 = 0x1E;
    goto block_265;
block_261:
    var_r4 = (u32) _memcardStatusPtr;
    temp_r0_9 = M2C_FIELD(var_r4, u32 *, 0x20) + 1;
    M2C_FIELD(var_r4, u32 *, 0x20) = temp_r0_9;
    if (temp_r0_9 >= 2U) {
        goto block_263;
    }
    var_r0_8 = 0x1D;
    goto block_265;
block_263:
    var_r0_8 = 0x1F;
    goto block_265;
block_264:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_8 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_23;
block_265:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_8;
    goto block_396;
    case 31:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, u32 *, 0xC) = _memcardExamineHeader();
    goto block_396;
    case 32:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x21U;
    goto block_396;
    case 33:
    var_r3_24 = CARDReadAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)), 0x28000, (M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) * 0x28000) + 0x6000, (CARDCallback)(0));
    if (var_r3_24 != 0) {
        goto block_270;
    }
    var_r3_24 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_270:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_24;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x22U;
    goto block_396;
    case 34:
    var_r3_25 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_25 == -1) {
        goto block_273;
    }
    goto block_274;
block_273:
    var_r3_25 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x28) = var_r3_25;
block_274:
    if (var_r3_25 == 0) {
        goto block_279;
    }
    if (var_r3_25 >= 0) {
        goto block_280;
    }
    if (var_r3_25 >= -1) {
        goto block_278;
    }
    goto block_280;
block_278:
    var_r0_9 = 0x22;
    goto block_281;
block_279:
    var_r0_9 = 0x23;
    goto block_281;
block_280:
    var_r4 = (u32) _memcardStatusPtr;
    var_r0_9 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_25;
block_281:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r0_9;
    goto block_396;
    case 35:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, u32 *, 0xC) = _memcardExamineDataPack();
    goto block_396;
    case 36:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, u32 *, 0xC) = _memcardMergeDataPack();
    goto block_396;
    case 37:
    CARDGetSerialNo(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (u64*)(&sp18));
    temp_ret = gamedatasaveBiosGetPtr((Gamedata*)(savedataGetStatus((void*)(NULL), 1)));
    gamedatasaveBiosSetMemcardID((GamedataSave*)(temp_ret), (u64) (u32) (u64) temp_ret);
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x2C) = (s32) (M2C_FIELD(_memcardStatusPtr, s32 *, 0x2C) + 1);
    temp_r3_5 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) + 1;
    temp_r5 = temp_r3_5 >> 0x1FU;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) = (s32) (((temp_r3_5 & 1) ^ temp_r5) - temp_r5);
    temp_r29_2 = M2C_FIELD(_memcardStatusPtr, u8 **, 0x50);
    M2C_FIELD(temp_r29_2, u8 *, 0) = 1U;
    temp_r3_6 = temp_r29_2 + 8;
    M2C_FIELD(temp_r29_2, u8 *, 1) = 1U;
    M2C_FIELD(temp_r29_2, u8 *, 2) = 1U;
    M2C_FIELD(temp_r29_2, u8 *, 3) = 0U;
    M2C_FIELD(temp_r29_2, s32 *, 4) = (s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0x2C);
    if (temp_r3_6 != NULL) {
        goto block_286;
    }
    temp_ret_2 = gamedatasaveBiosGetPtr((Gamedata*)(savedataGetStatus((void*)(temp_r3_6), 1)));
    gamedatasaveBiosSetMemcardID((GamedataSave*)(temp_ret_2), (u64) (u32) (u64) temp_ret_2);
    goto block_287;
block_286:
    temp_ret_3 = (long)(_memcardGetMultiSaveDataToSTRUCT((void*)(temp_r3_6), 1));
    gamedatasaveBiosSetMemcardID((GamedataSave*)(temp_ret_3 + 8), (u64) (u32) (u64) temp_ret_3);
block_287:
    temp_r0_10 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_10 >= 8) {
        goto block_290;
    }
    if (temp_r0_10 == 4) {
        goto block_291;
    }
    goto block_294;
block_290:
    if (temp_r0_10 >= 0xC) {
        goto block_294;
    }
block_291:
    temp_r28 = temp_r29_2 + 8;
    if (temp_r28 != NULL) {
        goto block_293;
    }
    temp_r27_3 = gamedatasaveGetStatus((Gamedata*)(savedataGetStatus((void*)(temp_r28), 1)), 4U);
    gamedatasaveSetStatus((Gamedata*)(savedataGetStatus((void*)(temp_r28), 1)), 4U, temp_r27_3 + 1);
    goto block_294;
block_293:
    temp_r3_7 = (Gamedata *)(_memcardGetMultiSaveDataToSTRUCT((void*)(temp_r28), 1));
    gamedatasaveSetStatus((Gamedata*)(temp_r3_7), 4U, gamedatasaveGetStatus((Gamedata*)(temp_r3_7), 4U) + 1);
block_294:
    temp_r3_8 = (long)(_memcardGetMultiSaveDataToSTRUCT((void*)(temp_r29_2 + 8), 1));
    var_r5_9 = 0;
    var_r6 = 0;
    var_r7 = (s32 *)0x80001800;
    var_ctr_2 = 0xC0;
loop_295:
    temp_r5_2 = var_r5_9 + *var_r7 + M2C_FIELD((((var_r6 + 1) * 4) + 0x80000000), s32 *, 0x1800) + M2C_FIELD((((var_r6 + 2) * 4) + 0x80000000), s32 *, 0x1800) + M2C_FIELD((((var_r6 + 3) * 4) + 0x80000000), s32 *, 0x1800) + M2C_FIELD((((var_r6 + 4) * 4) + 0x80000000), s32 *, 0x1800);
    var_r7 += 0x20;
    temp_r0_11 = M2C_FIELD((((var_r6 + 7) * 4) + 0x80000000), s32 *, 0x1800);
    temp_r5_3 = temp_r5_2 + M2C_FIELD((((var_r6 + 5) * 4) + 0x80000000), s32 *, 0x1800) + M2C_FIELD((((var_r6 + 6) * 4) + 0x80000000), s32 *, 0x1800);
    var_r6 += 8;
    var_r5_9 = temp_r5_3 + temp_r0_11;
    var_ctr_2 -= 1;
    if (var_ctr_2 != 0) {
        goto loop_295;
    }
    gamedatasaveSetStatus((Gamedata*)((Gamedata *) temp_r3_8), 0xCU, var_r5_9);
    gamedatasaveSetStatus((Gamedata*)(_memcardGetMultiSaveDataToSTRUCT((void*)(temp_r29_2 + 8), 1)), 0xDU, M2C_FIELD(temp_r29_2, u8 *, 0) + M2C_FIELD(temp_r29_2, u8 *, 1) + M2C_FIELD(temp_r29_2, u8 *, 2) + M2C_FIELD(temp_r29_2, u8 *, 3) + (u8) M2C_FIELD(temp_r29_2, s32 *, 4) + M2C_FIELD(temp_r29_2, u8 *, 5) + M2C_FIELD(temp_r29_2, u8 *, 6) + M2C_FIELD(temp_r29_2, u8 *, 7));
    _memcard_Encryption((void*)(temp_r29_2 + 8));
    var_r28 = 0x27;
    var_r27 = (signed char *)(temp_r29_2 + 0x27FD8);
loop_297:
    temp_ret_4 = HSD_Rand();
    var_r4 = (u32) (u64) temp_ret_4;
    temp_cr0_eq = var_r28 == 0;
    *var_r27 = temp_ret_4;
    var_r27 += 1;
    var_r28 -= 1;
    if (temp_cr0_eq == 0) {
        goto loop_297;
    }
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x26U;
    goto block_396;
    case 38:
    var_r3_26 = (s32 *)0x30000;
    var_r29_2 = 0x28000;
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0) != 8) {
        goto block_301;
    }
    var_r3_26 = (s32 *)0x20000;
    var_r29_2 = 0x26000;
block_301:
    GSgfxResetDisable(var_r3_26, (s32) var_r4);
    var_r3_27 = CARDWriteAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50)), var_r29_2, (M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) * 0x28000) + 0x6000, (CARDCallback)(0));
    if (var_r3_27 != 0) {
        goto block_303;
    }
    var_r3_27 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_303:
    var_r4 = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r3_27;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0x38) = 0U;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x27U;
    goto block_396;
    case 39:
    var_r3_28 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r3_28 == -1) {
        goto block_306;
    }
    goto block_307;
block_306:
    var_r3_28 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r3_28;
block_307:
    var_r4 = M2C_FIELD(_memcardStatusPtr, u32 *, 0x38);
    M2C_FIELD(_memcardStatusPtr, u32 *, 0x38) = (u32) (var_r4 + 1);
    if (var_r3_28 == 0) {
        goto block_312;
    }
    if (var_r3_28 >= 0) {
        goto block_327;
    }
    if (var_r3_28 >= -1) {
        goto block_311;
    }
    goto block_327;
block_311:
    var_r5_10 = 0x27;
    goto block_328;
block_312:
    var_r4 = (u32) _memcardStatusPtr;
    _memcard_gba2mode = 0;
    temp_r0_12 = M2C_FIELD(var_r4, s32 *, 0);
    if (temp_r0_12 == 8) {
        goto block_320;
    }
    if (temp_r0_12 >= 8) {
        goto block_318;
    }
    if (temp_r0_12 == 4) {
        goto block_322;
    }
    if (temp_r0_12 >= 4) {
        goto block_323;
    }
    if (temp_r0_12 >= 1) {
        goto block_321;
    }
    goto block_323;
block_318:
    if (temp_r0_12 >= 0xC) {
        goto block_323;
    }
    goto block_322;
block_320:
    M2C_FIELD(var_r4, s32 *, 0x10) = 0x28;
    var_r5_10 = 0x31;
    _memcard_gba2mode = 1;
    goto block_328;
block_321:
    M2C_FIELD(var_r4, s32 *, 4) = 0x12;
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = 3;
    goto block_324;
block_322:
    temp_r29_3 = gamedatasaveGetStatus((Gamedata*)(savedataGetStatus((void*)(NULL), 1)), 4U);
    gamedatasaveSetStatus((Gamedata*)(savedataGetStatus((void*)(NULL), 1)), 4U, temp_r29_3 + 1);
block_323:
    var_r4 = 0xA;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0xA;
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = 4;
block_324:
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) = 1U;
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x40) == 0) {
        goto block_326;
    }
    var_r5_10 = 0x11;
    goto block_328;
block_326:
    var_r5_10 = 0x2C;
    goto block_328;
block_327:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_10 = 0x2B;
    M2C_FIELD(var_r4, s32 *, 4) = var_r3_28;
block_328:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_10;
    goto block_396;
    case 40:
    temp_r3_9 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x34);
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x34) = (s32) (temp_r3_9 - 1);
    if (temp_r3_9 == 0) {
        goto block_331;
    }
    var_r4 = 0x28;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = -1;
    goto block_332;
block_331:
    var_r4 = 0x29;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = 0;
block_332:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r4;
    goto block_396;
    case 41:
    temp_ret_5 = gbaCommandIsConnected(2);
    var_r4 = (u32) (u64) temp_ret_5;
    if (temp_ret_5 != 0) {
        goto block_335;
    }
    var_r6_2 = 0x2B;
    goto block_338;
block_335:
    var_r3_29 = CARDWriteAsync((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)), (void*)(M2C_FIELD(_memcardStatusPtr, u8 **, 0x50) + 0x26000), 0x2000, (M2C_FIELD(_memcardStatusPtr, s32 *, 0x20) * 0x28000) + 0x6000 + 0x26000, (CARDCallback)(0));
    if (var_r3_29 != 0) {
        goto block_337;
    }
    var_r3_29 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
block_337:
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r3_29;
    var_r6_2 = 0x2A;
    temp_r3_10 = M2C_FIELD(_memcardStatusPtr, u32 *, 0x38);
    temp_r5_4 = MULTU_HI(0xAF286BCB, temp_r3_10);
    M2C_FIELD(_memcardStatusPtr, u32 *, 0x38) = (u32) ((u32) (((u32) (temp_r3_10 - temp_r5_4) >> 1U) + temp_r5_4) >> 4U);
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x38) = (s32) (M2C_FIELD(var_r4, s32 *, 0x38) + 1);
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3D) = 0U;
block_338:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r6_2;
    goto block_396;
    case 42:
    var_r27_2 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x28);
    if (var_r27_2 == -1) {
        goto block_341;
    }
    goto block_342;
block_341:
    var_r27_2 = CARDGetResultCode(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14));
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) = var_r27_2;
block_342:
    if (var_r27_2 == 0) {
        goto block_354;
    }
    if (var_r27_2 >= 0) {
        goto block_357;
    }
    if (var_r27_2 >= -1) {
        goto block_346;
    }
    goto block_357;
block_346:
    var_r4 = (u32) _memcardStatusPtr;
    M2C_FIELD(var_r4, s32 *, 0x38) = (s32) (M2C_FIELD(var_r4, s32 *, 0x38) - 1);
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x3D) != 0) {
        goto block_353;
    }
    temp_ret_6 = gbaCommandIsConnected(2);
    var_r4 = (u32) (u64) temp_ret_6;
    if (temp_ret_6 != 0) {
        goto block_349;
    }
    var_r4 = (u32) (u64) CARDCancel((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)));
    var_r5_11 = 0x2B;
    goto block_358;
block_349:
    if ((s32) M2C_FIELD(_memcardStatusPtr, u32 *, 0x38) >= 3) {
        goto block_353;
    }
    temp_ret_7 = gbaCommandChangePokemonEnd(2);
    var_r4 = (u32) (u64) temp_ret_7;
    if (temp_ret_7 == 0) {
        goto block_352;
    }
    var_r4 = (u32) (u64) CARDCancel((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)));
    var_r5_11 = 0x2B;
    goto block_358;
block_352:
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3D) = 1U;
block_353:
    var_r5_11 = 0x2A;
    goto block_358;
block_354:
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x3D) != 0) {
        goto block_356;
    }
    gbaCommandChangePokemonEnd(2);
block_356:
    temp_r29_4 = gamedatasaveGetStatus((Gamedata*)(savedataGetStatus((void*)(NULL), 1)), 4U);
    gamedatasaveSetStatus((Gamedata*)(savedataGetStatus((void*)(NULL), 1)), 4U, temp_r29_4 + 1);
    var_r4 = 0;
    var_r5_11 = 0x2C;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0;
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = 4;
    goto block_358;
block_357:
    var_r4 = (u32) (u64) PKJB_ReturnTitle(1);
    var_r5_11 = 0x2B;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = var_r27_2;
block_358:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_11;
    goto block_396;
    case 43:
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = -1;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x2CU;
    goto block_396;
    case 44:
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x3E) == 0) {
        goto block_362;
    }
    CARDGetSerialNo(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14), (u64*)(&sp10));
    CARDClose((CARDFileInfo*)((CARDFileInfo *) (_memcardStatusPtr + 0x8C)));
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x3E) = 0U;
block_362:
    var_r4 = (u32) (u64) GSgfxResetRestore(M2C_FIELD(_memcardStatusPtr, u8 *, 0x3F), (s32 *) (u32) (u64) CARDUnmount(M2C_FIELD(_memcardStatusPtr, s32 *, 0x14)));
    if ((u8) M2C_FIELD(_memcardStatusPtr, u8 *, 0x3C) == 0) {
        goto block_365;
    }
    if ((u8) _memcard_gba2mode != 0) {
        goto block_365;
    }
    var_r5_12 = 0;
    goto block_375;
block_365:
    temp_r0_13 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
    if (temp_r0_13 == 8) {
        goto block_369;
    }
    if (temp_r0_13 >= 8) {
        goto block_370;
    }
    if (temp_r0_13 == 3) {
        goto block_369;
    }
    goto block_370;
block_369:
    var_r5_12 = 0x32;
    goto block_375;
block_370:
    temp_r0_14 = M2C_FIELD(_memcardStatusPtr, s32 *, 8);
    if (temp_r0_14 >= 5) {
        goto block_374;
    }
    if (temp_r0_14 >= 1) {
        goto block_373;
    }
    goto block_374;
block_373:
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x4C) = unksp14;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x48) = (s32) sp10;
    M2C_FIELD(_memcardStatusPtr, u8 *, 0x41) = 1U;
block_374:
    var_r4 = (u32) _memcardStatusPtr;
    var_r5_12 = 0x30;
    M2C_FIELD(var_r4, s32 *, 4) = (s32) M2C_FIELD(var_r4, s32 *, 4);
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0x2D;
block_375:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r5_12;
    goto block_396;
    case 45:
    temp_r0_15 = M2C_FIELD(_memcardStatusPtr, s32 *, 0);
        switch (temp_r0_15) { case 4: goto sw2_c4; case 5: goto sw2_c5; case 6: goto sw2_c6; case 7: goto sw2_c7; case 9: goto sw2_c9; case 10: goto sw2_c10; case 11: goto sw2_c11; case 13: goto sw2_c13; case 1: goto sw2_c1; case 0: goto sw2_c0; case 2: goto sw2_c2; case 3: goto sw2_c3; case 8: goto sw2_c8; case 12: goto sw2_c12; default: goto block_389; }                            /* switch 2; jump table: jtbl_4197 */
sw2_c4:;
sw2_c5:;
sw2_c6:;
sw2_c7:;
sw2_c9:;
sw2_c10:;
sw2_c11:;
sw2_c13:;
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 8) == 4) {
        goto block_389;
    }
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0xF;
    var_r4 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0x32;
    goto block_390;
sw2_c1:;
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 8) != -1) {
        goto block_389;
    }
    temp_r0_16 = M2C_FIELD(_memcardStatusPtr, s32 *, 0x60);
    if (temp_r0_16 == 0xD) {
        goto block_386;
    }
    if (temp_r0_16 >= 0xD) {
        goto block_387;
    }
    if (temp_r0_16 == 7) {
        goto block_385;
    }
    goto block_387;
block_385:
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0xD;
    goto block_388;
block_386:
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 0xE;
    goto block_388;
block_387:
    var_r4 = 0x2E;
    goto block_390;
block_388:
    var_r4 = 0x30;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0x2E;
    goto block_390;
sw2_c0:;
sw2_c2:;
sw2_c3:;
sw2_c8:;
sw2_c12:;
block_389:
    var_r4 = 0x32;
block_390:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = var_r4;
    goto block_396;
    case 46:
    var_r4 = 0x2F;
    M2C_FIELD(_memcardStatusPtr, s32 *, 4) = 8;
    M2C_FIELD(_memcardStatusPtr, s32 *, 0x10) = 0x2F;
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x30U;
    goto block_396;
    case 47:
    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 4) == 0) {
        goto block_394;
    }
    M2C_FIELD(_memcardStatusPtr, s32 *, 8) = 5;
block_394:
    M2C_FIELD(_memcardStatusPtr, u32 *, 0xC) = 0x32U;
    goto block_396;
    return;
    }
block_396:

    if ((s32) M2C_FIELD(_memcardStatusPtr, s32 *, 0x28) != -1) {
        goto loop_1;
    }
    return;
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
