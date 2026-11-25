#include <dolphin/types.h>
#include <game/pcret.h>
#include <game/pcjoutai.h>

struct JoutaiData {
    u8 statusKind;
    u8 useBanme;
    u8 writeMode;
    u8 maxCount;
    u8 kaisuuDataId;
    u8 unk5[3];
    u16 status;
    u16 sameJoutai;
    u8 unkC[4];
    u32 name;
};

struct Joutai {
    u16 joutaiDataId;
    u16 userFightTargetId;
    u8 kaisuu;
    u8 nowKaisuu;
    u8 count;
    u8 unk7;
    u32 buff;
    u16 idBuff;
};

extern "C" {

extern JoutaiData joutai_data[];
extern u32 joutai_data_number;

JoutaiData* joutaiDataBiosGetDataPtr(u16 id);

u8 joutaiDataBiosGetKaisuuDataId(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->kaisuuDataId;
}

PCRET(u8) joutaiDataBiosGetMaxCount(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->maxCount;
}

u16 joutaiDataBiosGetSameJoutai(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->sameJoutai;
}

u8 joutaiDataBiosGetWriteMode(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->writeMode;
}

u8 joutaiDataBiosGetUseBanme(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->useBanme;
}

u16 joutaiDataBiosGetStatus(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->status;
}

u8 joutaiDataBiosGetStatusKind(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->statusKind;
}

u32 joutaiDataBiosGetName(u16 id) {
    JoutaiData* data = joutaiDataBiosGetDataPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->name;
}

#ifndef __MWERKS__
extern JoutaiData joutai_data_pc[];
extern u32 joutai_data_pc_number;
#endif

JoutaiData* joutaiDataBiosGetDataPtr(u16 id) {
#ifndef __MWERKS__
    if (id >= PC_JOUTAI_FIRST && (u32)(id - PC_JOUTAI_FIRST) < joutai_data_pc_number) {
        return &joutai_data_pc[id - PC_JOUTAI_FIRST];
    }
#endif
    if (id >= joutai_data_number) {
        return 0;
    }
    return &joutai_data[id];
}

void joutaiBiosSetIdBuff(Joutai* joutai, u16 value) {
    if (joutai != NULL) {
        joutai->idBuff = value;
    }
}

void joutaiBiosSetBuff(Joutai* joutai, u32 value) {
    if (joutai != NULL) {
        joutai->buff = value;
    }
}

void joutaiBiosSetNowKaisuu(Joutai* joutai, u8 value) {
    if (joutai != NULL) {
        joutai->nowKaisuu = value;
    }
}

u16 joutaiBiosGetIdBuff(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->idBuff;
}

u32 joutaiBiosGetBuff(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->buff;
}

PCRET(u8) joutaiBiosGetCount(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->count;
}

u8 joutaiBiosGetNowKaisuu(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->nowKaisuu;
}

u8 joutaiBiosGetKaisuu(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->kaisuu;
}

u16 joutaiBiosGetUserFightTargetId(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->userFightTargetId;
}

u16 joutaiBiosGetJoutaiDataId(Joutai* joutai) {
    if (joutai == NULL) {
        return 0;
    }
    return joutai->joutaiDataId;
}

}
