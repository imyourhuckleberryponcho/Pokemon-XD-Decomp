#include <dolphin/types.h>
#pragma pool_strings off

typedef struct DVDFileInfo {
    u8 raw[0x3C];
} DVDFileInfo;

typedef struct GSDVDWork GSDVDWork;
struct GSDVDWork {
    u8 active;
    u8 pad[3];
    DVDFileInfo fileInfo;
    void (*callback)(s32, GSDVDWork*);
    void* addr;
    u32 length;
};

typedef struct InAddr {
    u32 addr;
} InAddr;

typedef void (*DVDCallback)(s32, DVDFileInfo*);

#ifdef __cplusplus
extern "C" {
#endif
int DVDSeekAsyncPrio(DVDFileInfo* fileInfo, s32 offset, DVDCallback callback, s32 prio);
s32 DVDGetCommandBlockStatus(DVDFileInfo* fileInfo);
s32 DVDGetDriveStatus(void);
s32 DVDClose(DVDFileInfo* fileInfo);
int DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
s32 DVDConvertPathToEntrynum(const char* path);
int DVDOpen(const char* path, DVDFileInfo* fileInfo);
void DVDInit(void);
void DVDSetAutoFatalMessaging(int enable);
u8* DVDGetCurrentDiskID(void);
void DCInvalidateRange(void* addr, u32 nBytes);
u32 OSDisableInterrupts(void);
void OSRestoreInterrupts(u32 level);
void GSlogWrite(const char*, ...);
void GSlogSetIP(InAddr* addr, u32 port);
void GSnetworkSetIP(InAddr* addr, InAddr* mask, InAddr* gateway);
void GSgfxResetDisable(void);
void winMsgOpenError(u32 msg, u32 a, u32 b);
void winMsgCloseError(u32 a);
s32 pokecoloGetRomVersion(void);
s32 pokecoloGetCountryCode(void);
int GSgappCreate(s32 type, u8 priority, void* arg, void (*func)(void));
void GSgappSetName(int id, const char* name);
void* GSmemAllocAlign(u32 size, u32 align);
#ifdef __cplusplus
}
#endif

static u32 _maxDvdWork;
static GSDVDWork* _dvdWork;
static int _GappHandle;
static u32 _errorState;
u8 _GCClientON;
u8 _ReportServerON;
static u16 _ReportServerPort;
u8 _DvdServerON;
static u16 _DvdServerPort;
static u8 _initFlag;
static InAddr _DvdServerAddr = {0};
static InAddr _ReportServerAddr = {0};
static InAddr _GCClientAddr = {0};
static InAddr _Netmask = {0};
static InAddr _Gateway = {0};
static u32 _errorMsg_CoverOpen = 1;
static u32 _errorMsg_NoDisc = 1;
static u32 _errorMsg_WrongDisc = 1;
static u32 _errorMsg_Retry = 1;
static u32 _errorMsg_FatalError = 1;
static const char* _diskid_gameName = "GXXJ";
static const char* _diskid_company = "01";

s32 GSdvdGetDriveStatus(void);
static void _gsdvdErrorTask(void);
static void _gsdvdError_MsgOpen(u32 msg);
static void _errorTask_State_None(s32 state);
static void _AsyncCallback(s32 result, DVDFileInfo* info);
static void _AsyncReadCallback(s32 result, DVDFileInfo* info);
static GSDVDWork* _info2work(DVDFileInfo* info);
static u32 _SOInetAtoN(const char* str, void* out);
static void _freeDvdWork(GSDVDWork* work);
static GSDVDWork* _getNewDvdWork(void);
static void _initDvdWork(void);
static void* _dvdDoMalloc(u32 size);

u32 GSdvdFstRefresh(void) {
    return 0;
}

static void _gsdvdErrorTask(void) {
    s32 driveState = GSdvdGetDriveStatus();

    switch (_errorState) {
    case 0:
        _errorTask_State_None(driveState);
        break;
    case 1:
        _gsdvdError_MsgOpen(_errorMsg_CoverOpen);
        _errorState = 2;
        break;
    case 2:
        GSlogWrite("[GSDVD_ERROR_STATE_COVEROPEN_WAIT]  status = %d\n", driveState);
        if (driveState != 5 && driveState != 2) {
            winMsgCloseError(1);
            _errorState = 0;
        }
        break;
    case 3:
        _gsdvdError_MsgOpen(_errorMsg_NoDisc);
        _errorState = 4;
        break;
    case 4:
        if (driveState != 4) {
            winMsgCloseError(1);
            _errorState = 0;
        }
        break;
    case 5:
        _gsdvdError_MsgOpen(_errorMsg_WrongDisc);
        _errorState = 6;
        break;
    case 6:
        if (driveState != 6) {
            winMsgCloseError(1);
            _errorState = 0;
        }
        break;
    case 7:
        _gsdvdError_MsgOpen(_errorMsg_Retry);
        _errorState = 8;
        break;
    case 8:
        if (driveState != 11) {
            winMsgCloseError(1);
            _errorState = 0;
        }
        break;
    case 9:
        GSgfxResetDisable();
        _gsdvdError_MsgOpen(_errorMsg_FatalError);
        _errorState = 10;
        break;
    case 10:
        break;
    }
}

static void _gsdvdError_MsgOpen(u32 msg) {
    if (msg != 1) {
        winMsgOpenError(msg, 1, 1);
    }
}

static void _errorTask_State_None(s32 state) {
    switch (state) {
    case -1:
        _errorState = 9;
        break;
    case 5:
        _errorState = 1;
        break;
    case 4:
        _errorState = 3;
        break;
    case 6:
        _errorState = 5;
        break;
    case 11:
        _errorState = 7;
        break;
    }
}

void GSdvdSetErrorMsg(u32 coverOpen, u32 noDisc, u32 wrongDisc, u32 retry, u32 fatal) {
    _errorMsg_CoverOpen = coverOpen;
    _errorMsg_NoDisc = noDisc;
    _errorMsg_WrongDisc = wrongDisc;
    _errorMsg_Retry = retry;
    _errorMsg_FatalError = fatal;
}

u8 GSdvdSeekAsync(GSDVDWork* work, s32 offset, void (*callback)(s32, GSDVDWork*)) {
    if (_initFlag == 0) {
        return 0;
    }
    if (work == 0) {
        return 0;
    }
    work->callback = callback;
    return DVDSeekAsyncPrio(&work->fileInfo, offset, (DVDCallback)_AsyncCallback, 2);
}

s32 GSdvdGetFileInfoStatus(GSDVDWork* work) {
    if (_initFlag == 0) {
        return -1;
    }
    if (work == 0) {
        return -1;
    }
    return DVDGetCommandBlockStatus(&work->fileInfo);
}

s32 GSdvdGetDriveStatus(void) {
    if (_initFlag == 0) {
        return -1;
    }
    return DVDGetDriveStatus();
}

s32 GSdvdWrite(void) {
    return -1;
}

u32 GSdvdRemove(void) {
    if (_initFlag == 0) {
        return 0;
    }
    return 0;
}

u32 GSdvdCreate(void) {
    if (_initFlag == 0) {
    }
    return 0;
}

u32 GSdvdGetLength(GSDVDWork* work) {
    if (_initFlag == 0) {
        return 0;
    }
    if (work == 0) {
        return 0;
    }
    return *(u32*)&work->fileInfo.raw[0x34];
}

s32 GSdvdClose(GSDVDWork* work) {
    if (_initFlag == 0) {
        return 0;
    }
    if (work == 0) {
        return 0;
    }
    _freeDvdWork(work);
    return DVDClose(&work->fileInfo);
}

u8 GSdvdReadAsync(GSDVDWork* work, void* buf, s32 len, s32 offset, void (*callback)(s32, GSDVDWork*)) {
    if (_initFlag == 0) {
        return 0;
    }
    if (work == 0) {
        return 0;
    }
    work->callback = callback;
    if ((u32)buf & 0x1F) {
        return 0;
    }
    if (len & 0x1F) {
        return 0;
    }
    if (offset & 3) {
        return 0;
    }
    work->addr = buf;
    work->length = len;
    return DVDReadAsyncPrio(&work->fileInfo, buf, len, offset, (DVDCallback)_AsyncReadCallback, 2);
}

s32 GSdvdRead(GSDVDWork* work, void* buf, s32 len, s32 offset) {
    if (_initFlag == 0) {
        return -1;
    }
    if (work == 0) {
        return -1;
    }
    if ((u32)buf & 0x1F) {
        return -1;
    }
    if (len & 0x1F) {
        return -1;
    }
    if (offset & 3) {
        return -1;
    }
    return DVDReadPrio(&work->fileInfo, buf, len, offset, 2);
}

u8 GSdvdOpenTest(const char* path) {
    if (_initFlag == 0) {
        return 0;
    }
    return DVDConvertPathToEntrynum(path) != -1;
}

GSDVDWork* GSdvdOpen(const char* path) {
    GSDVDWork* work;
    if (_initFlag == 0) {
        return 0;
    }
    work = _getNewDvdWork();
    if (work == 0) {
        return 0;
    }
    if (!DVDOpen(path, &work->fileInfo)) {
        _freeDvdWork(work);
        return 0;
    }
    return work;
}

void GSdvdSetGCClient(const char* ip, const char* mask, const char* gateway, u8 on) {
    _SOInetAtoN(ip, &_GCClientAddr);
    _SOInetAtoN(mask, &_Netmask);
    _SOInetAtoN(gateway, &_Gateway);
    _GCClientON = 1;
    if (on == 1) {
        GSnetworkSetIP(&_GCClientAddr, &_Netmask, &_Gateway);
    }
}

void GSdvdSetReportServer(const char* ip, u32 port, u8 on) {
    _SOInetAtoN(ip, &_ReportServerAddr);
    _ReportServerPort = port;
    _ReportServerON = 1;
    if (on == 1) {
        GSlogSetIP(&_ReportServerAddr, port);
    }
}

void GSdvdSetDVDServer(const char* ip, u16 port) {
    _SOInetAtoN(ip, &_DvdServerAddr);
    _DvdServerPort = port;
    _DvdServerON = 1;
}

u32 GSdvdInit(u32 maxWork) {
    u8* id;
    if (_initFlag == 1) {
        return 0;
    }
    _maxDvdWork = maxWork;
    _dvdWork = (GSDVDWork*)_dvdDoMalloc(maxWork * sizeof(GSDVDWork));
    if (_dvdWork == 0) {
        return 0;
    }
    _initDvdWork();
    DVDInit();
    if (pokecoloGetRomVersion() != 4) {
        switch (pokecoloGetCountryCode()) {
        case 0:
            _diskid_gameName = "GXXJ";
            break;
        case 1:
            _diskid_gameName = "GXXE";
            break;
        case 2:
            _diskid_gameName = "GXXP";
            break;
        }
        id = DVDGetCurrentDiskID();
        id[0] = _diskid_gameName[0];
        id[1] = _diskid_gameName[1];
        id[2] = _diskid_gameName[2];
        id[3] = _diskid_gameName[3];
        id[4] = _diskid_company[0];
        id[5] = _diskid_company[1];
        id[6] = 0;
        id[7] = 0;
    }
    DVDSetAutoFatalMessaging(1);
    _GappHandle = GSgappCreate(1, 0x13, 0, _gsdvdErrorTask);
    GSgappSetName(_GappHandle, "GSdvdErrorTask");
    _initFlag = 1;
    return 1;
}

static void _AsyncCallback(s32 result, DVDFileInfo* info) {
    GSDVDWork* work = _info2work(info);
    if (work != 0 && work->callback != 0) {
        work->callback(result, work);
    }
}

static void _AsyncReadCallback(s32 result, DVDFileInfo* info) {
    GSDVDWork* work = _info2work(info);
    if (work != 0 && work->callback != 0) {
        DCInvalidateRange(work->addr, work->length);
        work->callback(result, work);
    }
}

static GSDVDWork* _info2work(DVDFileInfo* info) {
    GSDVDWork* cursor;
    GSDVDWork* base;
    u32 i;

    cursor = base = _dvdWork;
    for (i = 0; i < _maxDvdWork; cursor++, i++) {
        if (cursor->active != 0 && &cursor->fileInfo == info) {
            return &base[i];
        }
    }
    return 0;
}

static u32 _SOInetAtoN(const char* str, void* out) {
    return 0;
}

static void _freeDvdWork(GSDVDWork* work) {
    u32 en = OSDisableInterrupts();
    work->active = 0;
    OSRestoreInterrupts(en);
}

static GSDVDWork* _getNewDvdWork(void) {
    u32 i;
    u32 en = OSDisableInterrupts();
    GSDVDWork* r = 0;
    for (i = 0; i < _maxDvdWork; i++) {
        if (_dvdWork[i].active != 1) {
            _dvdWork[i].active = 1;
            r = &_dvdWork[i];
            break;
        }
    }
    OSRestoreInterrupts(en);
    return r;
}

static void _initDvdWork(void) {
    u32 i;
    for (i = 0; i < _maxDvdWork; i++) {
        _dvdWork[i].active = 0;
    }
}

static void* _dvdDoMalloc(u32 size) {
    return GSmemAllocAlign(size, 0x20);
}
