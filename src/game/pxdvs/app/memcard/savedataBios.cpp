#include <dolphin/types.h>

struct Savedata;

extern "C" {

extern Savedata* now_savedata_ptr;
extern u8 pokecolo_savedata[];

void* savedataBiosGetAnywaySavePtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x10E80;
}

void* savedataBiosGetRelivePtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x1D690;
}

void* savedataBiosGetYobi4Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x21570;
}

void* savedataBiosGetYobi3Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x20560;
}

void* savedataBiosGetYobi2Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x1FD50;
}

void* savedataBiosGetYobi1Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x1F940;
}

void* savedataBiosGetFlagSavedataPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x10790;
}

void* savedataBiosGetExRibbonPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x10E60;
}

void* savedataBiosGetDarkpokemonPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xE380;
}

void* savedataBiosGetToolPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xE000;
}

void* savedataBiosGetMemoDataPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xC870;
}

void* savedataBiosGetSodateyaPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xC790;
}

void* savedataBiosGetMailboxPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xC730;
}

void* savedataBiosGetFlagLevel2Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x10830;
}

void* savedataBiosGetFlagLevel1Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x107B0;
}

void* savedataBiosGetFlagLevel0Ptr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x10790;
}

void* savedataBiosGetPcboxPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xAD0;
}

void* savedataBiosGetHeroPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0x140;
}

void* savedataBiosGetGamedataPtr(Savedata* savedata) {
    if (savedata == NULL) {
        return NULL;
    }
    return (u8*)savedata + 0xA0;
}

void savedataBiosSetNowSavedataPtr(Savedata* savedata) {
    if (savedata != NULL) {
        now_savedata_ptr = savedata;
    }
}

Savedata* savedataBiosGetNowSavedataPtr(void) { return now_savedata_ptr; }

Savedata* savedataBiosGetSavedataBufferPtr(void) { return (Savedata*)pokecolo_savedata; }

}
