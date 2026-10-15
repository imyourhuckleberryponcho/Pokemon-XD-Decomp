#include <dolphin/types.h>

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

u8 joutaiDataBiosGetMaxCount(u16 id) {
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

JoutaiData* joutaiDataBiosGetDataPtr(u16 id) {
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

u8 joutaiBiosGetCount(Joutai* joutai) {
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
