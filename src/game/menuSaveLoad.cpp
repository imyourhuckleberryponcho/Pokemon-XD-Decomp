#include <dolphin/types.h>

// Menu files were built without the peephole optimizer.
#pragma peephole off

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    void* seq;
};

struct tagSPRITE_WORK {
    u8 unk0[6];
    s16 id;
};

struct FlagEtc {
    u8 unk0[0x148];
    u32 storyClearFlag;
};

class menuSaveload {
public:
    menuSaveload();
    ~menuSaveload();
    void Main();
    bool ComfirmOverwriting();
    void SaveParameterSet();
    bool IsReport();
    void Ctrl(tagWINDOW_WORK* window);
    void _menuClose(long menuID);

    u32 m_playTime;
};

extern "C" {
extern FlagEtc* flag_etc;
void fadeSet(s32 type, f32 time);
u32 GSflagGet(u32 flag);
bool GSflagTest(u32 flag);
void winSpriteSetDisp(tagSPRITE_WORK* sprite, s32 disp);
s32 darkPokemonGetReliveNum(void);
s32 darkPokemonGetSnatchSuccessNum(void);
s32 menuOpen(s32 menuID, s32);
void winMsgOpen(s32, s32 msgID, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
u32 floorGetNextFloorID(void);
void gamedatasaveSetStatus(void* save, s32 kind, u32 value);
u32 gamedatasaveGetStatus(void* save, s32 kind);
s32 memcardTaskCall(s32, s32, s32);
void* memcardMemAllocForSavedata(void);
void* memcardMemFreeForSavedata(void* ptr);
void* savedataGetStatus(void* save, s32 kind);
u32 heroGetStatus(void* hero, s32, s32);
void* memcpy(void* dst, const void* src, unsigned long n);
u32 pokecoloGetPlayTimeValue(void);
void pokecoloSetPlayTime(f64 time);
s32 pokecoloGetRomVersion(void);
void msgctrlSetValue(s32 id, u32 value);
void winSeqSetMenu(void* seq, s32 menu);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
}

static void _SaveParameterSet();

static menuSaveload* _saveload;
static u32 _PrevPlayTime;

#define SAVEDATA_SIZE 0x27FD0

extern "C" {

void menuSaveLoadCtrl(tagWINDOW_WORK* window) {
    if (_saveload != NULL) {
        _saveload->Ctrl(window);
        return;
    }
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            fadeSet(2, 0.5f);
            window->seqSet = 1;
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            fadeSet(3, 0.5f);
            window->seqSet = 1;
        }
        break;
    }
}

void menuReport(void) {
    _saveload = new menuSaveload;
    _saveload->Main();
    delete _saveload;
    _saveload = NULL;
}

s32 menuSaveLoadHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    bool cleared;
    if (GSflagGet(0x3C4) < flag_etc->storyClearFlag) {
        cleared = false;
    } else {
        cleared = true;
    }
    switch (sprite->id) {
    case 0x267:
    case 0x26F:
        if (!cleared) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0x26B:
        if (!cleared) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
        if (_saveload != NULL) {
            _saveload->SaveParameterSet();
        } else {
            _SaveParameterSet();
        }
        break;
    case 0x266:
    case 0x26A:
    case 0x26E:
        if (darkPokemonGetReliveNum() != 0) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    return 0;
}

}

menuSaveload::~menuSaveload() {}

menuSaveload::menuSaveload() {
    m_playTime = 0;
}

void menuSaveload::Main() {
    if (IsReport()) {
        menuOpen(0x64, 0);
        winMsgOpen(2, 0x3BF2, 1, 1);
        if (menuSubOpenYesNo(0, 0x1C2, 0xC0, 0) == 0 && ComfirmOverwriting()) {
            u32 floor = floorGetNextFloorID();
            gamedatasaveSetStatus(NULL, 5, floor);
            memcardTaskCall(4, 2, 0);
        }
        winMsgClose(1);
        _menuClose(0x64);
    } else {
        winMsgOpen(2, 0x3BE9, 1, 1);
        winMsgClose(1);
    }
}

// Asks before overwriting a save from a different playthrough.
bool menuSaveload::ComfirmOverwriting() {
    int ok = TRUE;
    void* backup = memcardMemAllocForSavedata();
    memcpy(backup, savedataGetStatus(NULL, 0), SAVEDATA_SIZE);
    if (memcardTaskCall(3, 2, 0) == 3 && gamedatasaveGetStatus(NULL, 4) != 0) {
        u32 hero = heroGetStatus(savedataGetStatus(backup, 2), 2, 0);
        if (hero == heroGetStatus(NULL, 2, 0) ||
            gamedatasaveGetStatus(backup, 4) == 0) {
            m_playTime = pokecoloGetPlayTimeValue();
            SaveParameterSet();
            winMsgOpen(2, 0x3BF3, 1, 1);
            if (menuSubOpenYesNo(0, 0x1C2, 0xC0, 1) != 0) {
                ok = FALSE;
            } else {
                ok = TRUE;
            }
            m_playTime = pokecoloGetPlayTimeValue() - m_playTime;
        }
    }
    memcpy(savedataGetStatus(NULL, 0), backup, SAVEDATA_SIZE);
    pokecoloSetPlayTime(m_playTime + pokecoloGetPlayTimeValue());
    m_playTime = 0;
    memcardMemFreeForSavedata(backup);
    return ok != 0;
}

static void _SaveParameterSet() {
    u32 time = pokecoloGetPlayTimeValue();
    if (_PrevPlayTime != 0) {
        time = _PrevPlayTime;
    }
    msgctrlSetValue(0x4C, time);
    msgctrlSetValue(0x34, darkPokemonGetSnatchSuccessNum());
    msgctrlSetValue(0x35, darkPokemonGetReliveNum());
}

void menuSaveload::SaveParameterSet() {
    u32 time = pokecoloGetPlayTimeValue();
    if (m_playTime != 0) {
        time = m_playTime;
    }
    msgctrlSetValue(0x4C, time);
    msgctrlSetValue(0x34, darkPokemonGetSnatchSuccessNum());
    msgctrlSetValue(0x35, darkPokemonGetReliveNum());
}

bool menuSaveload::IsReport() {
    if (pokecoloGetRomVersion() == 1) {
        return false;
    }
    return GSflagTest(0x3DE);
}

void menuSaveload::Ctrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x17F);
            window->seqSet = 1;
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x185);
            window->seqSet = 1;
        }
        break;
    }
}

void menuSaveload::_menuClose(long menuID) {
    menuClose(menuID);
    menuCloseSync(menuID, 1);
}
