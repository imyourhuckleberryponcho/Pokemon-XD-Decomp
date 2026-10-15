#include <dolphin/types.h>

// Debug menu: load/save the game state from/to files on the host PC (DVD emulation).
#pragma peephole off
#pragma pool_strings off
// Nothing references these debug functions; keep them anyway.
#pragma force_active on

typedef struct GSdvdFile GSdvdFile;

extern void* now_savedata_ptr;
u8 GSdvdOpenTest(const char* name);
GSdvdFile* GSdvdOpen(const char* name);
GSdvdFile* GSdvdCreate(const char* name);
s32 GSdvdRead(GSdvdFile* file, void* buf, u32 size, u32 offset);
s32 GSdvdWrite(GSdvdFile* file, void* buf, u32 size, u32 offset);
void GSdvdClose(GSdvdFile* file);
void* GSmemAllocAlign(u32 size, u32 align);
void GSmemFree(void* ptr);
void memcard_debug_Load(void* data);
void memcard_debug_Load2(void);
void memcard_debug_Save(void* data);
void* savedataGetStatus(void* save, s32 kind);
void gamedataSetStatus(void* data, s32 kind, s32 value);
s32 pokecoloGetCountryCode(void);
void* memcardMemAllocForSavedata(void);
void* memcardMemFreeForSavedata(void* ptr);
s32 memcardTaskCall(s32, s32, s32);
void* memcpy(void* dst, const void* src, unsigned long n);
void __assert(const char* file, int line, const char* expr);
void winMsgOpen(s32, s32 msgID, s32, s32);
void winMsgClose(s32);

static char* saveFileName[] = {
    "HDSaveData1.DSV1", "HDSaveData2.DSV1", "HDSaveData3.DSV1", "HDSaveData4.DSV1", "HDSaveData5.DSV1",
    "HDSaveData_1.DSV2", "HDSaveData_2.DSV2", "HDSaveData_3.DSV2", "HDSaveData_4.DSV2", "HDSaveData_5.DSV2",
};

static void* bk_savedataPtr;
static void* dbgMenuSaveData;

#define DEBUG_SAVE_SIZE 0x28000
#define SAVEDATA_SIZE 0x27FD0
#define SAVEDATA_BODY_SIZE 0x27FC0

// Slots 0-4 are full debug saves (DSV1), 5-9 raw save data (DSV2).
#pragma dont_inline on
static u8 _memcard_debug_type_check(s32 slot) {
    switch (slot) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return TRUE;
    default:
        return FALSE;
    }
}
#pragma dont_inline reset

s32 dbgMenuMemcardDebugLoad(void* menu, s32 slot) {
    GSdvdFile* file;
    void* status;

    if (GSdvdOpenTest(saveFileName[slot])) {
        file = GSdvdOpen(saveFileName[slot]);
        if (file == NULL) {
            return 0;
        }
    } else {
        return 0;
    }

    if (_memcard_debug_type_check(slot)) {
        dbgMenuSaveData = GSmemAllocAlign(DEBUG_SAVE_SIZE, 0x20);
        GSdvdRead(file, dbgMenuSaveData, DEBUG_SAVE_SIZE, 0);
        GSdvdClose(file);
        memcard_debug_Load((u8*)dbgMenuSaveData + 8);
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = NULL;
    } else {
        GSdvdRead(file, now_savedata_ptr, SAVEDATA_BODY_SIZE, 0);
        GSdvdClose(file);
        memcard_debug_Load2();
    }

 // Region-specific game settings.
    status = savedataGetStatus(NULL, 1);
    switch (pokecoloGetCountryCode()) {
    case 0:
        gamedataSetStatus(status, 2, 11);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 1);
        gamedataSetStatus(status, 5, 1);
        break;
    case 1:
        gamedataSetStatus(status, 2, 11);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 2);
        gamedataSetStatus(status, 5, 2);
        break;
    case 2:
        gamedataSetStatus(status, 2, 11);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 3);
        gamedataSetStatus(status, 5, 8);
        break;
    }
    return 0;
}

s32 dbgMenuMemcardDebugSave(void* menu, s32 slot) {
    GSdvdFile* file;

    if (_memcard_debug_type_check(slot)) {
        dbgMenuSaveData = GSmemAllocAlign(DEBUG_SAVE_SIZE, 0x20);
        memcard_debug_Save((u8*)dbgMenuSaveData + 8);
        if (GSdvdOpenTest(saveFileName[slot])) {
            file = GSdvdOpen(saveFileName[slot]);
        } else {
            file = GSdvdCreate(saveFileName[slot]);
        }
        if (file != NULL) {
            GSdvdWrite(file, dbgMenuSaveData, DEBUG_SAVE_SIZE, 0);
            GSdvdClose(file);
        }
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = NULL;
    } else {
        bk_savedataPtr = memcardMemAllocForSavedata();
        if (bk_savedataPtr == NULL) {
            __assert("dbgMenuMemcard.c", 501, "bk_savedataPtr &&\"メモリー不足\"");
        }
        memcpy(bk_savedataPtr, savedataGetStatus(NULL, 0), SAVEDATA_SIZE);
        if (memcardTaskCall(2, 2, 0) == 3) {
            if (GSdvdOpenTest(saveFileName[slot])) {
                file = GSdvdOpen(saveFileName[slot]);
            } else {
                file = GSdvdCreate(saveFileName[slot]);
            }
            if (file != NULL) {
                GSdvdWrite(file, now_savedata_ptr, SAVEDATA_BODY_SIZE, 0);
                GSdvdClose(file);
            }
        }
        memcpy(savedataGetStatus(NULL, 0), bk_savedataPtr, SAVEDATA_SIZE);
        bk_savedataPtr = memcardMemFreeForSavedata(bk_savedataPtr);
        if (bk_savedataPtr != NULL) {
            __assert("dbgMenuMemcard.c", 534, "!bk_savedataPtr &&\"メモリー解放失敗\"");
        }
    }
    return 0;
}

s32 dbgMenuMemcardDelete(void) {
    memcardTaskCall(12, 2, 0);
    return 0;
}

s32 dbgMenuMemcardLoad(void) {
    memcardTaskCall(2, 2, 0);
    winMsgOpen(2, 0xF2, 1, 1);
    winMsgClose(1);
    return 0;
}

s32 dbgMenuMemcardSave(void) {
    memcardTaskCall(11, 2, 0);
    return 0;
}
