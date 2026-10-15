#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

#pragma pool_strings off
#pragma peephole off

struct GSgfxLayer;

// Debug settings that can be passed on the command line as "name-value:name-value...".
struct SystemVars {
    s32 debugSysvars;
    s32 gsMemSize;
    s32 perfbar;
    s32 errorTrap;
    s32 dispMemSize;
    s32 btldbgMenuFlag;
    s32 btldbgDeckGrp;
    s32 btldbgEncountId;
    s32 btldbgStoryEncountId;
    s32 btldbgHundredEncountId;
    s32 btldbgImasuguEncountId;
    s32 btldbgVirtualEncountId;
    s32 btldbgBingoEncountId;
    s32 btldbgColosseumEncountId;
    s32 btldbgItemSet1;
    s32 btldbgAutoEncount;
    s32 flddbgPokedoru;
    s32 flddbgPokecoupon;
    char localIp[16];
    char gamecubeIp[16];
    s32 serverPort;
    s32 outputPort;
    char netmask[16];
    char gateway[16];
    s32 heroColiDisableBut;
};

enum {
    SYSVARS_BOOL,
    SYSVARS_INT,
    SYSVARS_FLOAT,
    SYSVARS_STRING,
};

struct sysvarsFuncEntry {
    const char* name;
    void (*func)(void* data, char* value);
    s32 type;
    void* data;
};

extern "C" {
void GSgfxGPUSetMode(s32 mode);
void GSgfxRender(void);
void GSprimDraw2DQuad(GXColor color, f32 x, f32 y, f32 w, f32 h);
void GSprimSetTextColor(GXColor color);
void GSprimSetTextWidth(f32 width);
void GSprimSetTextSize(f32 w, f32 h);
void GSprimWriteStr(f32 x, f32 y, const char* fmt, ...);
int stricmp(const char* a, const char* b);
int atoi(const char* s);
double atof(const char* s);
char* strcpy(char* dst, const char* src);
}

void GSprimSetup2DRender(GSgfxLayer* layer);

static void _sysvarsProcess(char* args);
static void _sysvarsProcessData(sysvarsFuncEntry* entry, char* value);
static sysvarsFuncEntry* _sysvarsFindEntry(char* name);
static void _sysvarsPerfbar(void* data, char* value);
static void _sysvarsGSmemSize(void* data, char* value);

extern "C" {

SystemVars systemVars = {
    0, 24, 0, 1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, -1, -1, "", "", 0, 0, "", "", 0,
};

}

static sysvarsFuncEntry _sysvarsFuncList[] = {
    { "debugsysvars", NULL, SYSVARS_BOOL, &systemVars.debugSysvars },
    { "gsmemsize", _sysvarsGSmemSize, SYSVARS_INT, &systemVars.gsMemSize },
    { "perfbar", _sysvarsPerfbar, SYSVARS_INT, &systemVars.perfbar },
    { "errortrap", NULL, SYSVARS_BOOL, &systemVars.errorTrap },
    { "dispmemsize", NULL, SYSVARS_BOOL, &systemVars.dispMemSize },
    { "btldbg_menuflag", NULL, SYSVARS_BOOL, &systemVars.btldbgMenuFlag },
    { "btldbg_deckgrp", NULL, SYSVARS_INT, &systemVars.btldbgDeckGrp },
    { "btldbg_encountid", NULL, SYSVARS_INT, &systemVars.btldbgEncountId },
    { "btldbg_story_encountid", NULL, SYSVARS_INT, &systemVars.btldbgStoryEncountId },
    { "btldbg_hundred_encountid", NULL, SYSVARS_INT, &systemVars.btldbgHundredEncountId },
    { "btldbg_imasugu_encountid", NULL, SYSVARS_INT, &systemVars.btldbgImasuguEncountId },
    { "btldbg_virtual_encountid", NULL, SYSVARS_INT, &systemVars.btldbgVirtualEncountId },
    { "btldbg_bingo_encountid", NULL, SYSVARS_INT, &systemVars.btldbgBingoEncountId },
    { "btldbg_colosseum_encountid", NULL, SYSVARS_INT, &systemVars.btldbgColosseumEncountId },
    { "btldbg_itemset1", NULL, SYSVARS_BOOL, &systemVars.btldbgItemSet1 },
    { "btldbg_auto_encount", NULL, SYSVARS_BOOL, &systemVars.btldbgAutoEncount },
    { "flddbg_pokedoru", NULL, SYSVARS_INT, &systemVars.flddbgPokedoru },
    { "flddbg_pokecoupon", NULL, SYSVARS_INT, &systemVars.flddbgPokecoupon },
    { "localip", NULL, SYSVARS_STRING, systemVars.localIp },
    { "gamecubeip", NULL, SYSVARS_STRING, systemVars.gamecubeIp },
    { "serverport", NULL, SYSVARS_INT, &systemVars.serverPort },
    { "outputport", NULL, SYSVARS_INT, &systemVars.outputPort },
    { "netmask", NULL, SYSVARS_STRING, systemVars.netmask },
    { "gateway", NULL, SYSVARS_STRING, systemVars.gateway },
    { "hero_coli_disable_but", NULL, SYSVARS_BOOL, &systemVars.heroColiDisableBut },
    { NULL, NULL, 0, NULL },
};

extern "C" {

// Shows all settings on screen for 15 seconds.
void sysvarsShowDebug(void) {
    GXColor bgColor = { 0, 0, 0, 0xFF };
    GXColor textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    u32 frames = 900;

    GSgfxGPUSetMode(1);
    while (frames-- != 0) {
        sysvarsFuncEntry* entry;
        f32 y;
        GSprimSetup2DRender(NULL);
        GSprimDraw2DQuad(bgColor, 0.0f, 0.0f, 640.0f, 480.0f);
        GSprimSetTextColor(textColor);
        GSprimSetTextWidth(2.0f);
        GSprimSetTextSize(12.0f, 12.0f);
        y = 40.0f;
        for (entry = _sysvarsFuncList; entry->name != NULL; y += 14.0f, entry++) {
            switch (entry->type) {
            case SYSVARS_BOOL:
            case SYSVARS_INT:
                GSprimWriteStr(100.0f, y, "%s=%d", entry->name, *(s32*)entry->data);
                break;
            case SYSVARS_FLOAT:
                GSprimWriteStr(100.0f, y, "%s=%f", entry->name, *(f32*)entry->data);
                break;
            case SYSVARS_STRING:
                GSprimWriteStr(100.0f, y, "%s=%s", entry->name, (char*)entry->data);
                break;
            }
        }
        GSprimWriteStr(500.0f, 400.0f, "%d", frames / 60);
        GSgfxRender();
    }
    GSgfxGPUSetMode(2);
}

void sysvarsReadSettings(int* argc, char*** argv) {
    int i;
    if (*argc >= 2) {
        _sysvarsProcess((*argv)[1]);
        for (i = 1; i < *argc; i++) {
            (*argv)[i] = (*argv)[i + 1];
        }
        (*argc)--;
    }
}

}

static void _sysvarsProcess(char* args) {
    while (*args != '\0') {
        char* name = args;
        sysvarsFuncEntry* entry;
        char* value;
        while (*args != '\0' && *args != '-') {
            args++;
        }
        if (*args == '-') {
            *args = '\0';
            entry = _sysvarsFindEntry(name);
            args++;
            value = args;
            while (*args != '\0' && *args != ':') {
                args++;
            }
            if (*args == ':') {
                *args = '\0';
                args++;
            }
            if (entry != NULL) {
                _sysvarsProcessData(entry, value);
            }
        }
    }
}

static void _sysvarsProcessData(sysvarsFuncEntry* entry, char* value) {
    if (entry->func == NULL) {
        switch (entry->type) {
        case SYSVARS_BOOL: {
            s32* data = (s32*)entry->data;
            if (stricmp(value, "off") == 0 || stricmp(value, "false") == 0 || stricmp(value, "0") == 0) {
                *data = 0;
            } else if (stricmp(value, "on") == 0 || stricmp(value, "true") == 0 || stricmp(value, "1") == 0) {
                *data = 1;
            }
            break;
        }
        case SYSVARS_INT: {
            s32* data = (s32*)entry->data;
            *data = atoi(value);
            break;
        }
        case SYSVARS_FLOAT: {
            f32* data = (f32*)entry->data;
            *data = atof(value);
            break;
        }
        case SYSVARS_STRING:
            strcpy((char*)entry->data, value);
            break;
        }
    } else {
        entry->func(entry->data, value);
    }
}

static sysvarsFuncEntry* _sysvarsFindEntry(char* name) {
    sysvarsFuncEntry* entry;
    for (entry = _sysvarsFuncList; entry->name != NULL; entry++) {
        if (stricmp(name, entry->name) == 0) {
            return entry;
        }
    }
    return NULL;
}

static void _sysvarsPerfbar(void* data, char* value) {
    if (stricmp(value, "off") == 0) {
        *(s32*)data = 0;
    } else if (stricmp(value, "simple") == 0) {
        *(s32*)data = 1;
    } else if (stricmp(value, "detail") == 0) {
        *(s32*)data = 2;
    }
}

static void _sysvarsGSmemSize(void* data, char* value) {
    if (stricmp(value, "24") == 0) {
        *(s32*)data = 24;
    } else if (stricmp(value, "48") == 0) {
        *(s32*)data = 48;
    }
}
