// Memory card save/load state machine over the Dolphin CARD API.
#include <dolphin/types.h>

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
}





enum MEMCARD_MSGTYPE {
    MSG_M13 = -13, MSG_M9 = -9, MSG_M8 = -8, MSG_M6 = -6, MSG_M5 = -5, MSG_M4 = -4, MSG_M3 = -3, MSG_M2 = -2,
    MSG_0 = 0, MSG_1, MSG_2, MSG_3, MSG_4, MSG_5, MSG_6, MSG_7, MSG_8, MSG_9, MSG_10,
    MSG_11, MSG_12, MSG_13, MSG_14, MSG_15, MSG_16, MSG_17, MSG_18, MSG_19
};
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
            if (_memcardStatusPtr->f60 != 0x32) {
                msg = 0x6e;
            }
            break;
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
