#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/dvd.h>

#pragma peephole off
#pragma pool_strings off

struct AgbWork {
 s32 mode;
 u8 status;
 u8 pad5[3];
 s32 state;
 s32 active;
 volatile s32 jobType;
 volatile s32 ret;
 volatile s32 result;
 u32 w1C;
 u32 w20;
 s32 w24;
 u32 w28;
 u32 w2C;
 u32 w30;
 u32 w34;
 u32 w38;
 u32 w3C;
 u32 w40;
 s32 w44;
 s32 w48;
 s32 w4C;
 s32 w50;
 s32 w54;
 s32 w58;
 u32 index;
 u32 w60;
 u32 w64;
 s32 w68;
 u32 tick0;
 u32 limit0;
 u32 tick1;
 u32 limit1;
 u32 tick2;
 u32 limit2;
 s32 w84;
 s32 w88;
 u32* buf;
 u32 size;
 s32 arg;
 u32* out;
};

typedef void (*GBACallback)(s32 chan, s32 ret);

extern "C" {
u32 strlen(const char*);
char* strcpy(char*, const char*);
void* memcpy(void*, const void*, unsigned long);
u32 SIProbe(s32 chan);
u32 gba_SIProbe(s32 chan);
s32 GBAGetStatus(s32 chan, void* status);
s32 GBAGetStatusAsync(s32 chan, void* status, GBACallback cb);
s32 GBARead(s32 chan, void* dst, void* status);
s32 GBAReadAsync(s32 chan, void* dst, void* status, GBACallback cb);
s32 GBAWrite(s32 chan, void* src, void* status);
s32 GBAWriteAsync(s32 chan, void* src, void* status, GBACallback cb);
s32 GBAReset(s32 chan, void* status);
s32 GBAResetAsync(s32 chan, void* status, GBACallback cb);
void GBAInit(void);
void gbaCommandSetKeyState(s32 chan, s32 state);
void pokeconv(s32 id, void* buf);
void* GSmemAllocAlign(u32 size, u32 align);
void GSmemFree(void* p);
void GSthreadSwitch(void);
u32 GSdvdOpen(const char* name);
u32 GSdvdGetLength(u32 file);
u8 GSdvdReadAsync(u32 file, void* dst, u32 len, s32 a, s32 b);
s32 GSdvdGetFileInfoStatus(u32 file);
void GSdvdClose(u32 file);
}

#define BUS_CLOCK (*(u32*)0x800000F8)

static AgbWork _gba_wk[4];
static char gba_filenames[0x100];
static u8 gba_pokemon_buf[4][0x278];
static OSAlarm _alarm;
static u8 gbainit_function_flag = 1;
static u32* jbBuf1;
static u32 jbSize1;
static u32 _gameName;
static OSThread* _thread;

static long AGB_Initialize(long ch);
static void _AGB_Work_Clear(long ch);
static void _job_type_clear(long ch, const char* name);
static void _timer_set(long ch, u32 ms);
static u32 SwapEndian(u32 v);
static u32 _PKJBUpGenerateKeyA(void);
static u32 _PKJBUpValidateKeyB(u32 key);
static void _AdjustGbaImageRegistry(u8* image, char* name);
static void _ReadJBCode(const char* name, u8* buf, u32* size);
static u32 _PKJBUpCalcCrc(u32 crc, u32 data);
static u32 _PKJBUpFindBootKey(u32 recv, u32 crc);
static long _AGB_SendWazaText(long ch, u8* data);
static long _AGB_EntryRequest(long ch, u32 value);
static long _AGB_BattleRequest(long ch, const u8* data, int size);
static long _AGB_EntryGetStatus(long ch, u32* out);
static long _AGB_ReturnTitle(long ch);
static long _InitialExchange(long ch);
static long _GBATimerRead(long ch, u8* dst, u8* status, int ms);
static long _SendRecv(long ch, u32 cmd, u32* recv);
static long _BulkSend(long ch, const u8* data, int size);
static long _BulkSend2(long ch, const u8* data, int size);
static long _AGB_ExchangeStart(long ch, u8* data);
static void _alarm_handler(OSAlarm* alarm, OSContext* ctx);
static void _sleep_thread(int ms);
static long _AGB_ExchangeIsPrepared(long ch);
static long _AGB_ExchangeEnd(long ch);
static void _upload_00s(long ch, long ret);
static void _upload_01(long ch, long ret);
static void _upload_02(long ch, long ret);
static void _upload_03(long ch, long ret);
static void _upload_04(long ch, long ret);
static void _upload_05(long ch, long ret);
static void _upload_06(long ch, long ret);
static void _upload_07(long ch, long ret);
static void _upload_08(long ch, long ret);
static void _upload_09(long ch, long ret);
static void _upload_10(long ch, long ret);
static void _upload_11(long ch, long ret);
static void _upload_11s(long ch, long ret);
static void _upload_12(long ch, long ret);
static void _upload_12s(long ch, long ret);
static void _upload_13(long ch, long ret);
static void _upload_13s(long ch, long ret);
static void _upload_14(long ch, long ret);
static void _upload_15(long ch, long ret);
static void _upload_16(long ch, long ret);
static void _upload_16s0(long ch, long ret);
static void _upload_16s(long ch, long ret);
static void _upload_17(long ch, long ret);
static void _upload_17s(long ch, long ret);
static void _upload_18(long ch, long ret);
static void _upload_19(long ch, long ret);
static void _upload_20(long ch, long ret);
static void _upload_21(long ch, long ret);
static void _upload_21s(long ch, long ret);
static void _upload_22(long ch, long ret);
static void _upload_23(long ch, long ret);
static void _upload_23s(long ch, long ret);
static void _upload_24(long ch, long ret);
static void _upload_25(long ch, long ret);
static void _getpokemon_01(long ch, long ret);
static void _getpokemon_01s(long ch, long ret);
static void _getpokemon_02(long ch, long ret);
static void _getpokemon_03(long ch, long ret);
static void _getpokemon_04(long ch, long ret);
static void _getpokemon_05(long ch, long ret);
static void _getpokemon_05s(long ch, long ret);
static void _getpokemon_06(long ch, long ret);
static void _getpokemon_07(long ch, long ret);
static void _getpokemon_07s(long ch, long ret);
static void _getpokemon_08(long ch, long ret);
static void _getpokemon_09(long ch, long ret);
static void _getpokemon_09s(long ch, long ret);
static void _getpokemon_10(long ch, long ret);
static void _getpokemon_11(long ch, long ret);
static void _timer_set(long ch, u32 ms);
static void _job_type_clear(long ch, const char* name);
static void _AGB_Work_Clear(long ch);
static u32 SwapEndian(u32 v);
static u32 _PKJBUpGenerateKeyA(void);
static u32 _PKJBUpValidateKeyB(u32 key);
static u32 _PKJBUpCalcCrc(u32 crc, u32 data);
static u32 _PKJBUpFindBootKey(u32 recv, u32 crc);
static void _ReadJBCode(const char* name, u8* buf, u32* size);
static long _InitialExchange(long ch);
static long _SendRecv(long ch, u32 cmd, u32* recv);
static long _GBATimerRead(long ch, u8* dst, u8* status, int ms);
static long _BulkSend(long ch, const u8* data, int size);
static long _BulkSend2(long ch, const u8* data, int size);
static void _alarm_handler(OSAlarm* alarm, OSContext* ctx);
static void _sleep_thread(int ms);
static long AGB_Initialize(long ch);
static void _AdjustGbaImageRegistry(u8* image, char* name);
static long _AGB_EntryGetStatus(long ch, u32* out);
extern "C" long PKJB_GetKey(long ch, u16* out);

static void _getpokemon_01(long ch, long ret);
static void _getpokemon_01s(long ch, long ret);
static void _getpokemon_02(long ch, long ret);
static void _getpokemon_03(long ch, long ret);
static void _getpokemon_04(long ch, long ret);
static void _getpokemon_05(long ch, long ret);
static void _getpokemon_05s(long ch, long ret);
static void _getpokemon_06(long ch, long ret);
static void _getpokemon_07(long ch, long ret);
static void _getpokemon_07s(long ch, long ret);
static void _getpokemon_08(long ch, long ret);
static void _getpokemon_09(long ch, long ret);
static void _getpokemon_09s(long ch, long ret);
static void _getpokemon_10(long ch, long ret);
static void _getpokemon_11(long ch, long ret);

static void _upload_00s(long ch, long ret);
static void _upload_01(long ch, long ret);
static void _upload_02(long ch, long ret);
static void _upload_03(long ch, long ret);
static void _upload_04(long ch, long ret);
static void _upload_05(long ch, long ret);
static void _upload_06(long ch, long ret);
static void _upload_07(long ch, long ret);
static void _upload_08(long ch, long ret);
static void _upload_09(long ch, long ret);
static void _upload_10(long ch, long ret);
static void _upload_11(long ch, long ret);
static void _upload_11s(long ch, long ret);
static void _upload_12(long ch, long ret);
static void _upload_12s(long ch, long ret);
static void _upload_13(long ch, long ret);
static void _upload_13s(long ch, long ret);
static void _upload_14(long ch, long ret);
static void _upload_15(long ch, long ret);
static void _upload_16(long ch, long ret);
static void _upload_16s0(long ch, long ret);
static void _upload_16s(long ch, long ret);
static void _upload_17(long ch, long ret);
static void _upload_17s(long ch, long ret);
static void _upload_18(long ch, long ret);
static void _upload_19(long ch, long ret);
static void _upload_20(long ch, long ret);
static void _upload_21(long ch, long ret);
static void _upload_21s(long ch, long ret);
static void _upload_22(long ch, long ret);
static void _upload_23(long ch, long ret);
static void _upload_23s(long ch, long ret);
static void _upload_24(long ch, long ret);
static void _upload_25(long ch, long ret);

static long AGB_Initialize(long ch) {
    if (ch < 0 || ch > 3) {
        return 0;
    }
    if (_gba_wk[ch].mode != 0) {
        return 0;
    }
    _AGB_Work_Clear(ch);
    _gba_wk[ch].mode = 0;
    return 1;
}

extern "C" {

void AGB_Terminate_init(void) {
    for (long i = 0; i < 4; i++) {
        _AGB_Work_Clear(i);
        _job_type_clear(i, __FUNCTION__);
    }
}

}

extern "C" {

long AGB_Terminate(long ch) {
    if (ch < 0 || ch > 3) {
        return 0;
    }
    _gba_wk[ch].active = 0;
    _gba_wk[ch].result = 0;
    _gba_wk[ch].jobType = 0;
    if (_gba_wk[ch].mode != 0) {
        _gba_wk[ch].result = 4;
    }
    _job_type_clear(ch, __FUNCTION__);
    return 1;
}

}

extern "C" {

long AGB_GetStatus(long ch) {
    if (ch < 0 || ch > 3) {
        return 1;
    }
    return _gba_wk[ch].result;
}

}

extern "C" {

u8 AGB_IsComplete(long ch) {
    if (ch < 0 || ch > 3) {
        return 0;
    }
    if (_gba_wk[ch].mode != 0) {
        switch (_gba_wk[ch].jobType) {
        case 1:
            _upload_00s(ch, 0);
            break;
        case 2:
            _upload_16s0(ch, 0);
            break;
        case 3:
            _upload_16s(ch, 0);
            break;
        }
    }
    return _gba_wk[ch].mode == 0;
}

}

static void _AGB_Work_Clear(long ch) {
    _gba_wk[ch].w1C = 0;
    _gba_wk[ch].w20 = 0;
    _gba_wk[ch].w24 = 0;
    _gba_wk[ch].w28 = 0;
    _gba_wk[ch].w2C = 0;
    _gba_wk[ch].w30 = 0;
    _gba_wk[ch].w34 = 0;
    _gba_wk[ch].w38 = 0;
    _gba_wk[ch].w3C = 0;
    _gba_wk[ch].w40 = 0;
    _gba_wk[ch].w44 = 0;
    _gba_wk[ch].w48 = 0;
    _gba_wk[ch].w4C = 0;
    _gba_wk[ch].w50 = 0;
    _gba_wk[ch].w54 = 0;
    _gba_wk[ch].w58 = 0;
    _gba_wk[ch].tick0 = 0;
    _gba_wk[ch].limit0 = 0;
    _gba_wk[ch].tick1 = 0;
    _gba_wk[ch].limit1 = 0;
    _gba_wk[ch].tick2 = 0;
    _gba_wk[ch].limit2 = 0;
    _gba_wk[ch].w84 = 0;
    _gba_wk[ch].w88 = 0;
    _gba_wk[ch].index = 0;
    _gba_wk[ch].w60 = 0;
    _gba_wk[ch].w64 = 0;
    _gba_wk[ch].w68 = 0;
    _gba_wk[ch].active = 0;
    _gba_wk[ch].result = 0;
    _gba_wk[ch].jobType = 0;
}

static void _job_type_clear(long ch, const char* name) {
    _gba_wk[ch].active = 0;
    _gba_wk[ch].mode = 0;
    _gba_wk[ch].jobType = 0;
}

static void _timer_set(long ch, u32 ms) {
    _gba_wk[ch].limit0 = ms * ((BUS_CLOCK / 4) / 1000);
    _gba_wk[ch].tick0 = OSGetTick();
}

static u32 SwapEndian(u32 v) {
    return (v >> 24) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 24);
}

static u32 _PKJBUpGenerateKeyA(void) {
    u32 i = 0;
    u32 key;
    u32 v;
    int j;
    u32 count;
    do {
        if (i > 0x20) {
            key = 0xDD654321;
        } else {
            key = (OSGetTick() & 0xFFFFFF) | 0xDD000000;
        }
        count = 0;
        v = key;
        for (j = 0; j < 32; j++) {
            if (v & 1) {
                count++;
            }
            v >>= 1;
        }
        i++;
    } while (count < 10 || count > 24);
    return key;
}

static u32 _PKJBUpValidateKeyB(u32 key) {
    if ((key & 0xFF) != 0xEE) {
        OSReport("_PKJBUpValidateKeyB: invalid key (d7-d0): 0x%x\n", key);
        return 0;
    }
    u32 result = key & 0xFFFFFF00;
    int i;
    u32 count = 0;
    for (i = 0; i < 24; i++) {
        if (key & 0x80000000) {
            count++;
        }
        key <<= 1;
    }
    if (count < 7 || count > 14) {
        OSReport("_PKJBUpValidateKeyB: invalid key (d31-d8): 0x%x\n");
        return 0;
    }
    return result;
}

static void _AdjustGbaImageRegistry(u8* image, char* name) {
    long i = 0xA0;
    int sum = 0xE7;
    image[0xAC] = name[0];
    image[0xAD] = name[1];
    image[0xAE] = name[2];
    image[0xAF] = name[3];
    for (; i < 0xBD; i++) {
        sum -= image[i];
    }
    image[i] = (u8)sum;
}

static void _ReadJBCode(const char* name, u8* buf, u32* size) {
    u32 file = GSdvdOpen(name);
    if (file == 0) {
        return;
    }
    *size = GSdvdGetLength(file);
    if (*size == 0 || *size > 0x20000) {
        return;
    }
    *size = (*size + 0x1F) & 0xFFFFFFE0;
    if (GSdvdReadAsync(file, buf, *size, 0, 0) != 0) {
        do {
            GSthreadSwitch();
        } while (GSdvdGetFileInfoStatus(file) != 0);
        GSdvdClose(file);
        _AdjustGbaImageRegistry(buf, (char*)&_gameName);
    }
}

static u32 _PKJBUpCalcCrc(u32 crc, u32 data) {
    u32 x = crc ^ data;
    int i;
    for (i = 32; i > 0; i--) {
        if (x & 1) {
            x >>= 1;
            x ^= 0xA1C1;
        } else {
            x >>= 1;
        }
    }
    return x;
}

static u32 _PKJBUpFindBootKey(u32 recv, u32 crc) {
    OSReport("from GBA recvData = 0x%08x, GC resultCrc = 0x%08x\n", recv, crc);
    u32 key;
    u32 hi = recv >> 8;
    u32 i;
    for (i = 0, key = 0xFFFFFFFF; i < 0x100; key += 0x01000000, i++) {
        if (hi == _PKJBUpCalcCrc(key, crc)) {
            u32 bootKey = _PKJBUpCalcCrc(key, 0xBB) | 0xBB000000;
            OSReport("KeyC found! 0x%08x, return bootKey = 0x%08x\n", key, bootKey);
            return bootKey;
        }
    }
    OSReport("*************** ERROR: KeyC NOT FOUND 0x%08x, 0x%08x ***************\n", recv, crc);
    return 0;
}

extern "C" {

long PKJB_GetKey(long ch, u16* out) {
    u32 recv;
    long r = _InitialExchange(ch);
    if (r != 0) {
        return r;
    }
    r = _SendRecv(ch, 0xAA, &recv);
    if (r != 0) {
        return r;
    }
    if ((recv >> 24) != 0xAA) {
        return 0xF;
    }
    *out = SwapEndian(recv) >> 16;
    return 0;
}

}

extern "C" {

long PKJB_IdleSend(long ch) {
    u32 word;
    u8 status;
    if (gba_SIProbe(ch) != 0x40000) {
        return 1;
    }
    word = 0x11;
    if (GBAWrite(ch, &word, &status) != 0) {
        return 2;
    }
    return 0;
}

}

extern "C" {

long PKJB_SendWazaText(long ch, u8* data) {
    long key = ch + 1;
    gbaCommandSetKeyState(key, 2);
    long r = _AGB_SendWazaText(ch, data);
    gbaCommandSetKeyState(key, 1);
    return r;
}

}

static long _AGB_SendWazaText(long ch, u8* data) {
    u32 recv;
    u32 limit = ((BUS_CLOCK / 4) / 1000) * 5;
    u32 start = OSGetTick();
    long r;
    int timeout;
    do {
        timeout = OSGetTick() - start > limit;
        r = _InitialExchange(ch);
    } while (r == 1 && !timeout);
    if (r != 0) {
        return r;
    }
    r = _SendRecv(ch, 0x88, &recv);
    if (r != 0) {
        return r;
    }
    if ((recv >> 24) != 0x88) {
        return 0xF;
    }
    return _BulkSend2(ch, data, 0x780);
}

extern "C" {

long PKJB_EntryRequest(long ch, u32 value) {
    int timeout;
    u32 start;
    long key = ch + 1;
    long r;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = ((BUS_CLOCK / 4) / 1000) * 100;
    start = OSGetTick();
    do {
        timeout = OSGetTick() - start > limit;
        r = _AGB_EntryRequest(ch, value);
    } while (r == 1 && !timeout);
    gbaCommandSetKeyState(key, r != 0 ? 1 : 3);
    return r;
}

}

static long _AGB_EntryRequest(long ch, u32 value) {
    u32 recv;
    u32 word;
    u8 status;
    long r = _InitialExchange(ch);
    if (r != 0) {
        return r;
    }
    word = 0x77;
    r = _SendRecv(ch, 0x77, &recv);
    if (r != 0) {
        return r;
    }
    if ((recv >> 24) != 0x77) {
        return 0xF;
    }
    word = SwapEndian(value);
    GBAWrite(ch, &word, &status);
    u32 limit = ((BUS_CLOCK / 4) / 1000) * 100;
    u32 start = OSGetTick();
    while (1) {
        if (OSGetTick() - start > limit) {
            return 0x10;
        }
        if (GBAGetStatus(ch, &status) != 0) {
            return 0x11;
        }
        if ((status & 2) == 0) {
            return 0;
        }
    }
}

extern "C" {

long PKJB_BattleRequest(long ch, const u8* data, int size) {
    int timeout;
    u32 start;
    long key = ch + 1;
    long r;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = ((BUS_CLOCK / 4) / 1000) * 100;
    start = OSGetTick();
    do {
        timeout = OSGetTick() - start > limit;
        r = _AGB_BattleRequest(ch, data, size);
    } while (r == 1 && !timeout);
    gbaCommandSetKeyState(key, r != 0 ? 1 : 3);
    return r;
}

}

static long _AGB_BattleRequest(long ch, const u8* data, int size) {
    u32 recv;
    long r = _InitialExchange(ch);
    if (r != 0) {
        return r;
    }
    r = _SendRecv(ch, 0x66, &recv);
    if (r != 0) {
        return r;
    }
    if ((recv >> 24) != 0x66) {
        return 0xF;
    }
    return _BulkSend2(ch, data, size);
}

extern "C" {

long PKJB_EntryGetStatus(long ch, u32* out) {
    return _AGB_EntryGetStatus(ch, out);
}

}

static long _AGB_EntryGetStatus(long ch, u32* out) {
    u32 sendWord;
    u32 data;
    u8 status;
    if (gba_SIProbe(ch) != 0x40000) {
        return 1;
    }
    if (GBAGetStatus(ch, &status) != 0) {
        return 2;
    }
    if ((status & 8) == 0) {
        sendWord = 0x11;
        GBAWrite(ch, &sendWord, &status);
        return -1;
    }
    if (GBARead(ch, &data, &status) != 0) {
        return 3;
    }
    *out = data;
    return 0;
}

extern "C" {

long PKJB_BattleGetStatus(long ch, u32* out) {
    long r = _AGB_EntryGetStatus(ch, out);
    if (r >= 0) {
        gbaCommandSetKeyState(ch + 1, 1);
    }
    return r;
}

}

extern "C" {

long PKJB_ReturnTitle(long ch) {
    long key = ch + 1;
    gbaCommandSetKeyState(key, 2);
    long r = _AGB_ReturnTitle(ch);
    gbaCommandSetKeyState(key, 1);
    return r;
}

}

static long _AGB_ReturnTitle(long ch) {
    u32 word;
    u16 key;
    u8 status;
    long r = _InitialExchange(ch);
    if (r != 0) {
        return r;
    }
    word = 0x60;
    r = GBAWrite(ch, &word, &status);
    if (r != 0) {
        return 0xB;
    }
    u32 limit = (BUS_CLOCK >> 2) * 3;
    u32 start = OSGetTick();
    while (1) {
        if (OSGetTick() - start > limit) {
            return 0x10;
        }
        long k = PKJB_GetKey(ch, &key);
        GSthreadSwitch();
        if (k == 0) {
            return r;
        }
    }
}

static long _InitialExchange(long ch) {
    u32 data;
    u8 status;
    if (gba_SIProbe(ch) != 0x40000) {
        return 1;
    }
    if (GBAReset(ch, &status) != 0) {
        return 2;
    }
    long r = _GBATimerRead(ch, (u8*)&data, &status, 100);
    if (r != 0) {
        return r + 2;
    }
    if (data != _gameName) {
        return 6;
    }
    if (GBAGetStatus(ch, &status) != 0) {
        return 7;
    }
    if (GBAWrite(ch, &data, &status) != 0) {
        return 8;
    }
    u32 limit = ((BUS_CLOCK / 4) / 1000) * 100;
    u32 start = OSGetTick();
    while (1) {
        if (OSGetTick() - start > limit) {
            return 9;
        }
        if (GBAGetStatus(ch, &status) != 0) {
            return 0xA;
        }
        if ((status & 2) == 0) {
            return 0;
        }
    }
}

static long _GBATimerRead(long ch, u8* dst, u8* status, int ms) {
    u8 st;
    u32 limit = ms * ((BUS_CLOCK / 4) / 1000);
    u32 start = OSGetTick();
    while (1) {
        if (OSGetTick() - start > limit) {
            return 1;
        }
        if (GBAGetStatus(ch, &st) != 0) {
            return 2;
        }
        if ((st & 0xA) == 8) {
            if (GBARead(ch, dst, status) != 0) {
                return 3;
            }
            return 0;
        }
    }
}

static long _SendRecv(long ch, u32 cmd, u32* recv) {
    u32 status;
    if (GBAWrite(ch, &cmd, &status) != 0) {
        return 0xB;
    }
    long r = _GBATimerRead(ch, (u8*)recv, (u8*)&status, 100);
    if (r != 0) {
        return r + 0xB;
    }
    return 0;
}

static long _BulkSend(long ch, const u8* data, int size) {
    u32 word;
    u8 status;
    u32 start;
    u32 limit;
    int i = 0;
    while (i < size) {
        word = *(u32*)(data + i);
        if (GBAWrite(ch, &word, &status) != 0) {
            return 0x10;
        }
        limit = ((BUS_CLOCK / 4) / 1000) * 100;
        start = OSGetTick();
        while (1) {
            if (OSGetTick() - start > limit) {
                return 0x11;
            }
            if (GBAGetStatus(ch, &status) != 0) {
                return 0x12;
            }
            if ((status & 2) == 0) {
                break;
            }
        }
        i += 4;
    }
    return 0;
}

static long _BulkSend2(long ch, const u8* data, int size) {
    u32 word;
    u8 status;
    int i = 0;
    while (i < size) {
        word = *(u32*)(data + i);
        if (GBAWrite(ch, &word, &status) != 0) {
            return 0x10;
        }
        u32 limit = ((BUS_CLOCK / 4) / 1000) * 100;
        u32 start = OSGetTick();
        while (1) {
            if (OSGetTick() - start > limit) {
                return 0x11;
            }
            if (GBAGetStatus(ch, &status) != 0) {
                return 0x12;
            }
            if ((status & 2) == 0) {
                break;
            }
        }
        if (i % 64 == 0) {
            GSthreadSwitch();
        }
        i += 4;
    }
    return 0;
}

extern "C" {

long PKJB_ExchangeStart(long ch, u8* data) {
    int timeout;
    u32 start;
    long key = ch + 1;
    long r;
    u32 limit;
    gbaCommandSetKeyState(key, 2);
    limit = ((BUS_CLOCK / 4) / 1000) * 100;
    start = OSGetTick();
    do {
        timeout = OSGetTick() - start > limit;
        r = _AGB_ExchangeStart(ch, data);
    } while (r == 1 && !timeout);
    gbaCommandSetKeyState(key, r != 0 ? 1 : 3);
    return r;
}

}

static long _AGB_ExchangeStart(long ch, u8* data) {
    u32 recv;
    u32 limit = ((BUS_CLOCK / 4) / 1000) * 100;
    u32 start = OSGetTick();
    while (1) {
        if (OSGetTick() - start > limit) {
            return 1;
        }
        if (gba_SIProbe(ch) == 0x40000) {
            long r = _InitialExchange(ch);
            if (r != 0) {
                return r;
            }
            r = _SendRecv(ch, 0x55, &recv);
            if (r != 0) {
                return r;
            }
            if ((recv >> 24) != 0x55) {
                return 0xF;
            }
            _BulkSend(ch, data, 0x78);
            return 0;
        }
    }
}

static void _alarm_handler(OSAlarm* alarm, OSContext* ctx) {
    OSResumeThread(_thread);
}

static void _sleep_thread(int ms) {
    _thread = OSGetCurrentThread();
    OSCreateAlarm(&_alarm);
    BOOL level = OSDisableInterrupts();
    OSSetAlarm(&_alarm, ms * ((BUS_CLOCK / 4) / 1000), _alarm_handler);
    OSSuspendThread(_thread);
    OSRestoreInterrupts(level);
}

extern "C" {

long PKJB_ExchangeIsPrepared(long ch) {
    long r = _AGB_ExchangeIsPrepared(ch);
    if (r == 0 || r >= 3) {
        gbaCommandSetKeyState(ch + 1, 1);
    }
    return r;
}

}

static long _AGB_ExchangeIsPrepared(long ch) {
    u32 data;
    u8 status;
    _sleep_thread(1);
    if (gba_SIProbe(ch) != 0x40000) {
        return 1;
    }
    if (GBAGetStatus(ch, &status) != 0) {
        return 2;
    }
    if ((status & 8) == 0) {
        return -1;
    }
    if (GBARead(ch, &data, &status) != 0) {
        return 3;
    }
    if (data != 0) {
        return 4;
    }
    return 0;
}

extern "C" {

long PKJB_ExchangeEnd(long ch) {
    long key = ch + 1;
    gbaCommandSetKeyState(key, 2);
    long r = _AGB_ExchangeEnd(ch);
    gbaCommandSetKeyState(key, 1);
    return r;
}

}

static long _AGB_ExchangeEnd(long ch) {
    u32 data;
    u8 status;
    long r = _InitialExchange(ch);
    if (r != 0) {
        return r;
    }
    r = _SendRecv(ch, 0x44, &data);
    if (r != 0) {
        return r;
    }
    if ((data >> 24) != 0x44) {
        return 0xF;
    }
    r = _GBATimerRead(ch, (u8*)&data, &status, 30000);
    if (r != 0) {
        return r + 0xF;
    }
    if (data != 0) {
        return 0x13;
    }
    return 0;
}

extern "C" {

long AGB_Prepare(const char* name) {
    if (strlen(name) >= 0x7F) {
        return 0;
    }
    strcpy(gba_filenames, name);
    DVDDiskID* diskId = DVDGetCurrentDiskID();
    memcpy(&_gameName, diskId, 4);
    if (gbainit_function_flag) {
        GBAInit();
        gbainit_function_flag = 0;
    }
    _ReadJBCode(name, (u8*)jbBuf1, &jbSize1);
    return 1;
}

}

extern "C" {

long AGB_Upload(long ch, long type) {
    if (!AGB_Initialize(ch)) {
        return 0;
    }
    _AGB_Work_Clear(ch);
    _gba_wk[ch].mode = 2;
    _gba_wk[ch].result = 3;
    _gba_wk[ch].active = 1;
    if (type == 0) {
        _gba_wk[ch].limit1 = (BUS_CLOCK >> 2) * 7;
    } else {
        _gba_wk[ch].limit1 = (BUS_CLOCK >> 2) * 7;
    }
    _gba_wk[ch].tick1 = OSGetTick();
    _gba_wk[ch].size = jbSize1;
    _gba_wk[ch].buf = jbBuf1;
    gbaCommandSetKeyState(ch + 1, 0);
    _upload_00s(ch, 0);
    return 1;
}

}

static void _upload_00s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x2710;
        _gba_wk[ch].jobType = 0;
        _gba_wk[ch].ret = SIProbe(ch);
        if (_gba_wk[ch].ret == 0x40000) {
            _gba_wk[ch].ret = GBAResetAsync(ch, &_gba_wk[ch].status, _upload_01);
            if (_gba_wk[ch].ret == 2) {
                _gba_wk[ch].jobType = 1;
            }
        } else {
            if (OSGetTick() - _gba_wk[ch].tick1 >= _gba_wk[ch].limit1) {
                _job_type_clear(ch, __FUNCTION__);
                _gba_wk[ch].result = 2;
                return;
            }
            _gba_wk[ch].jobType = 1;
        }
    }
}

static void _upload_01(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 1;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else {
            _timer_set(ch, 0x7D);
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_02);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_02(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 2;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else if (_gba_wk[ch].status == 0x18) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w38, &_gba_wk[ch].status, _upload_03);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else if (OSGetTick() - _gba_wk[ch].tick0 <= _gba_wk[ch].limit0) {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_02);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            goto fail;
        }
    }
}

static void _upload_03(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 3;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else {
            u32 t = _gba_wk[ch].w38 + 0xBEA80000;
            if (t != 0x564A && t != 0x5645) {
                if (OSGetTick() - _gba_wk[ch].tick1 >= _gba_wk[ch].limit1) {
                    _job_type_clear(ch, __FUNCTION__);
                    _gba_wk[ch].result = 2;
                    return;
                }
                goto fail;
            }
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_04);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_04(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 4;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else if (_gba_wk[ch].status == 0x10) {
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w38, &_gba_wk[ch].status, _upload_05);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            goto fail;
        }
    }
}

static void _upload_05(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 5;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else {
            _timer_set(ch, 0x7D);
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_06);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_06(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 6;
        if (ret == 1) {
        fail:
            _gba_wk[ch].jobType = 1;
        } else {
            u8 st = _gba_wk[ch].status;
            if ((st & 0x30) == 0x10) {
                if (!(st & 2)) {
                    _gba_wk[ch].w38 = _PKJBUpGenerateKeyA();
                    _gba_wk[ch].w1C = SwapEndian(_gba_wk[ch].w38);
                    _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w1C, &_gba_wk[ch].status, _upload_07);
                    if (_gba_wk[ch].ret == 2) {
                        _job_type_clear(ch, __FUNCTION__);
                        _gba_wk[ch].result = 1;
                        return;
                    }
                }
                if (OSGetTick() - _gba_wk[ch].tick0 <= _gba_wk[ch].limit0) {
                    _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_06);
                    if (_gba_wk[ch].ret == 2) {
                        goto fail;
                    }
                } else {
                    goto fail;
                }
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_07(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 7;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            _timer_set(ch, 0x7D);
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_08);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_08(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 8;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else if (_gba_wk[ch].status == 0x38) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w34, &_gba_wk[ch].status, _upload_09);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else if (OSGetTick() - _gba_wk[ch].tick0 <= _gba_wk[ch].limit0) {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_08);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            goto fail;
        }
    }
}

static void _upload_09(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 9;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            u32 sp8;
            _gba_wk[ch].w30 = _PKJBUpValidateKeyB(SwapEndian(_gba_wk[ch].w34));
            if (_gba_wk[ch].w30 != 0) {
                u32 sz = (_gba_wk[ch].size + 7) & 0xFFFFFFF8;
                sp8 = sz;
                _gba_wk[ch].size = sz;
                sp8 = SwapEndian((sz >> 3) - 1);
                _gba_wk[ch].ret = GBAWriteAsync(ch, &sp8, &_gba_wk[ch].status, _upload_10);
                if (_gba_wk[ch].ret == 2) {
                    goto fail;
                }
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_10(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xA;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            _timer_set(ch, 0x7D);
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_11);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_11(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xB;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            u8 st = _gba_wk[ch].status;
            if ((st & 0x30) == 0x30) {
                if (!(st & 2)) {
                    _gba_wk[ch].w28 = _gba_wk[ch].w38 ^ _gba_wk[ch].w30;
                    _gba_wk[ch].w24 = (_gba_wk[ch].w38 ^ _gba_wk[ch].w30) * 0x6177614B + 1;
                    _gba_wk[ch].w20 = 0x30;
                    _gba_wk[ch].index = 0;
                    _upload_11s(ch, ret);
                } else if (OSGetTick() - _gba_wk[ch].tick0 <= _gba_wk[ch].limit0) {
                    _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_11);
                    if (_gba_wk[ch].ret == 2) {
                        goto fail;
                    }
                } else {
                    goto fail;
                }
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_11s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3F3;
        _gba_wk[ch].w60 = SwapEndian(*(u32*)((u8*)_gba_wk[ch].buf + _gba_wk[ch].index));
        if (_gba_wk[ch].index >= 0xA0) {
            _gba_wk[ch].w64 = _gba_wk[ch].w60;
            _gba_wk[ch].w60 = _gba_wk[ch].w60 - _gba_wk[ch].w28;
            _gba_wk[ch].w60 = _gba_wk[ch].w60 ^ _gba_wk[ch].w24;
            _gba_wk[ch].w28 = _PKJBUpCalcCrc(_gba_wk[ch].w28, _gba_wk[ch].w64);
            _gba_wk[ch].w24 = _gba_wk[ch].w24 * 0x6177614B + 1;
        }
        _gba_wk[ch].w2C = SwapEndian(_gba_wk[ch].w60);
        while (1) {
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w2C, &_gba_wk[ch].status, _upload_12);
            if (_gba_wk[ch].ret != 2) {
                break;
            }
            if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
                _job_type_clear(ch, __FUNCTION__);
                _gba_wk[ch].result = 1;
                break;
            }
        }
    }
}

static void _upload_12(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xC;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            if ((_gba_wk[ch].status & 0x30) == _gba_wk[ch].w20) {
                _gba_wk[ch].w20 ^= 0x10;
                _timer_set(ch, 0x7D);
                _upload_12s(ch, ret);
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_12s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3F4;
        while (1) {
            if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
                _job_type_clear(ch, __FUNCTION__);
                _gba_wk[ch].result = 1;
                return;
            }
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_13);
            if (_gba_wk[ch].ret != 2) {
                break;
            }
        }
    }
}

static void _upload_13(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xD;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            u8 st = _gba_wk[ch].status;
            if (st & 0x20) {
                if (!(st & 2)) {
                    _gba_wk[ch].index += 4;
                    if (_gba_wk[ch].index < _gba_wk[ch].size) {
                        _upload_11s(ch, ret);
                        return;
                    }
                    _gba_wk[ch].limit0 = (BUS_CLOCK >> 2) * 10;
                    _gba_wk[ch].tick0 = OSGetTick();
                    _upload_13s(ch, ret);
                } else {
                    _upload_12s(ch, ret);
                }
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_13s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3F5;
        if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_14);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_14(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xE;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            u8 st = _gba_wk[ch].status;
            if ((st & 0x30) == 0x30) {
                if ((st & 0xA) == 8) {
                    _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w2C, &_gba_wk[ch].status, _upload_15);
                    if (_gba_wk[ch].ret == 2) {
                        goto fail;
                    }
                } else {
                    _upload_13s(ch, ret);
                }
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_15(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xF;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            u32 v = _gba_wk[ch].w2C;
            u32 top = v >> 24;
            if (top == 0xFF) {
                _gba_wk[ch].w34 = _PKJBUpFindBootKey(SwapEndian(v), _gba_wk[ch].w28);
                if (_gba_wk[ch].w34 == 0) {
                    goto fail;
                }
                _gba_wk[ch].w34 = SwapEndian(_gba_wk[ch].w34);
                _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w34, &_gba_wk[ch].status, _upload_16);
                if (_gba_wk[ch].ret == 2) {
                    goto fail;
                }
            } else if (top == 0xCC) {
                _upload_13s(ch, ret);
            } else {
                goto fail;
            }
        }
    }
}

static void _upload_16(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x10;
        if (ret == 1) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
        } else {
            _gba_wk[ch].limit0 = BUS_CLOCK >> 2;
            _gba_wk[ch].tick0 = OSGetTick();
            _upload_16s0(ch, ret);
        }
    }
}

static void _upload_16s0(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xD8;
        _gba_wk[ch].jobType = 0;
        if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            return;
        }
        _gba_wk[ch].ret = SIProbe(ch);
        if (_gba_wk[ch].ret != 0x40000) {
            _gba_wk[ch].limit2 = (BUS_CLOCK >> 2) * 8;
            _gba_wk[ch].tick2 = OSGetTick();
            _gba_wk[ch].ret = GBAResetAsync(ch, &_gba_wk[ch].status, _upload_17);
            if (_gba_wk[ch].ret == 2) {
                _upload_16s(ch, ret);
            }
        } else {
            _gba_wk[ch].jobType = 2;
        }
    }
}

static void _upload_16s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3F8;
        _gba_wk[ch].jobType = 0;
        if (OSGetTick() - _gba_wk[ch].tick2 > _gba_wk[ch].limit2) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            return;
        }
        _gba_wk[ch].ret = SIProbe(ch);
        if (_gba_wk[ch].ret != 0x40000) {
            _gba_wk[ch].jobType = 3;
            return;
        }
        _gba_wk[ch].ret = GBAResetAsync(ch, &_gba_wk[ch].status, _upload_17);
        if (_gba_wk[ch].ret == 2) {
            _gba_wk[ch].jobType = 3;
        }
    }
}

static void _upload_17(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 17;
        if (ret == 1) {
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].w44 = 5;
            _gba_wk[ch].limit1 = _gba_wk[ch].w44 * ((BUS_CLOCK / 4) / 1000);
            _gba_wk[ch].tick1 = OSGetTick();
            _upload_17s(ch, ret);
        }
    }
}

static void _upload_17s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 1017;
        if (OSGetTick() - _gba_wk[ch].tick1 > _gba_wk[ch].limit1) {
        fail:
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_18);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_18(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 18;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else if ((_gba_wk[ch].status & 0xA) == 8) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _upload_19);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _upload_17s(ch, ret);
        }
    }
}

static void _upload_19(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 19;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else if (_gameName == _gba_wk[ch].w40) {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_20);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            goto fail;
        }
    }
}

static void _upload_20(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 20;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _upload_21);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_21(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x15;
        if (ret == 1) {
            _upload_16s(ch, ret);
        } else {
            _timer_set(ch, 0x7D);
            _upload_21s(ch, ret);
        }
    }
}

static void _upload_21s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 1021;
        if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
        fail:
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_22);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_22(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 22;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else if (!(_gba_wk[ch].status & 2)) {
            _gba_wk[ch].w3C = 0xAA;
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w3C, &_gba_wk[ch].status, _upload_23);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _upload_21s(ch, ret);
        }
    }
}

static void _upload_23(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 23;
        if (ret == 1) {
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].w44 = 100;
            _gba_wk[ch].limit1 = _gba_wk[ch].w44 * ((BUS_CLOCK / 4) / 1000);
            _gba_wk[ch].tick1 = OSGetTick();
            _upload_23s(ch, ret);
        }
    }
}

static void _upload_23s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 1023;
        if (OSGetTick() - _gba_wk[ch].tick1 > _gba_wk[ch].limit1) {
        fail:
            _upload_16s(ch, ret);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _upload_24);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _upload_24(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 24;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else if ((_gba_wk[ch].status & 0xA) == 8) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _upload_25);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _upload_23s(ch, ret);
        }
    }
}

static void _upload_25(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 25;
        if (ret == 1) {
        fail:
            _upload_16s(ch, ret);
        } else if ((_gba_wk[ch].w40 >> 24) == 0xAA) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 0;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            goto fail;
        }
    }
}

extern "C" {

long AGB_GetPokemon(long ch, s32 id, u32* out) {
    if (!AGB_Initialize(ch)) {
        return 0;
    }
    long key = ch + 1;
    gbaCommandSetKeyState(key, 2);
    _AGB_Work_Clear(ch);
    _gba_wk[ch].mode = 4;
    _gba_wk[ch].result = 3;
    _gba_wk[ch].active = 1;
    _gba_wk[ch].arg = id;
    _gba_wk[ch].out = out;
    _gba_wk[ch].ret = SIProbe(ch);
    if (_gba_wk[ch].ret != 0x40000) {
    fail:
        _job_type_clear(ch, __FUNCTION__);
        _gba_wk[ch].result = 1;
        gbaCommandSetKeyState(key, 1);
        return 0;
    } else {
        _gba_wk[ch].ret = GBAResetAsync(ch, &_gba_wk[ch].status, _getpokemon_01);
        if (_gba_wk[ch].ret == 2) {
            goto fail;
        }
        return 1;
    }
}

}

static void _getpokemon_01(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 1;
        if (ret == 1) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].w44 = 5;
            _gba_wk[ch].limit1 = _gba_wk[ch].w44 * ((BUS_CLOCK / 4) / 1000);
            _gba_wk[ch].tick1 = OSGetTick();
            _getpokemon_01s(ch, ret);
        }
    }
}

static void _getpokemon_01s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3E9;
        if (OSGetTick() - _gba_wk[ch].tick1 > _gba_wk[ch].limit1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _getpokemon_02);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_02(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 2;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if ((_gba_wk[ch].status & 0xA) == 8) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _getpokemon_03);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_01s(ch, ret);
        }
    }
}

static void _getpokemon_03(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 3;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if (_gameName == _gba_wk[ch].w40) {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _getpokemon_04);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            goto fail;
        }
    }
}

static void _getpokemon_04(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 4;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _getpokemon_05);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_05(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 5;
        if (ret == 1) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _timer_set(ch, 0x7D);
            _getpokemon_05s(ch, ret);
        }
    }
}

static void _getpokemon_05s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3ED;
        if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _getpokemon_06);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_06(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 6;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if (!(_gba_wk[ch].status & 2)) {
            _gba_wk[ch].w3C = 0x99;
            _gba_wk[ch].ret = GBAWriteAsync(ch, &_gba_wk[ch].w3C, &_gba_wk[ch].status, _getpokemon_07);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_05s(ch, ret);
        }
    }
}

static void _getpokemon_07(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 7;
        if (ret == 1) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].w44 = 100;
            _gba_wk[ch].limit1 = _gba_wk[ch].w44 * ((BUS_CLOCK / 4) / 1000);
            _gba_wk[ch].tick1 = OSGetTick();
            _getpokemon_07s(ch, ret);
        }
    }
}

static void _getpokemon_07s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3EF;
        if (OSGetTick() - _gba_wk[ch].tick1 > _gba_wk[ch].limit1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _getpokemon_08);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_08(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 8;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if ((_gba_wk[ch].status & 0xA) == 8) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w40, &_gba_wk[ch].status, _getpokemon_09);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_07s(ch, ret);
        }
    }
}

static void _getpokemon_09(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 9;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if ((_gba_wk[ch].w40 >> 24) == 0x99) {
            _gba_wk[ch].index = 0;
            _gba_wk[ch].buf = (u32*)gba_pokemon_buf[ch];
            _timer_set(ch, 0x7D);
            _getpokemon_09s(ch, ret);
        } else {
            goto fail;
        }
    }
}

static void _getpokemon_09s(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0x3F1;
        if (OSGetTick() - _gba_wk[ch].tick0 > _gba_wk[ch].limit0) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else {
            _gba_wk[ch].ret = GBAGetStatusAsync(ch, &_gba_wk[ch].status, _getpokemon_10);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        }
    }
}

static void _getpokemon_10(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xA;
        if (ret == 1) {
        fail:
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
        } else if (_gba_wk[ch].status & 8) {
            _gba_wk[ch].ret = GBAReadAsync(ch, &_gba_wk[ch].w1C, &_gba_wk[ch].status, _getpokemon_11);
            if (_gba_wk[ch].ret == 2) {
                goto fail;
            }
        } else {
            _getpokemon_09s(ch, ret);
        }
    }
}

static void _getpokemon_11(long ch, long ret) {
    if (_gba_wk[ch].active) {
        _gba_wk[ch].state = 0xB;
        if (ret == 1) {
            _job_type_clear(ch, __FUNCTION__);
            _gba_wk[ch].result = 1;
            gbaCommandSetKeyState(ch + 1, 1);
            return;
        }
        *(u32*)((u8*)_gba_wk[ch].buf + _gba_wk[ch].index) = _gba_wk[ch].w1C;
        _gba_wk[ch].index += 4;
        if (_gba_wk[ch].index < 0x278) {
            _timer_set(ch, 0x7D);
            _getpokemon_09s(ch, ret);
            return;
        }
        pokeconv(_gba_wk[ch].arg, _gba_wk[ch].buf);
        u8* b = (u8*)_gba_wk[ch].buf;
        *_gba_wk[ch].out = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
        _job_type_clear(ch, __FUNCTION__);
        _gba_wk[ch].result = 0;
        gbaCommandSetKeyState(ch + 1, 1);
    }
}

extern "C" {

void AGB_FileBuffAlloc(void) {
    jbBuf1 = (u32*)GSmemAllocAlign(0x20000, 0x20);
}

}

extern "C" {

void AGB_FileBuffFree(void) {
    GSmemFree(jbBuf1);
    jbBuf1 = 0;
}

}
