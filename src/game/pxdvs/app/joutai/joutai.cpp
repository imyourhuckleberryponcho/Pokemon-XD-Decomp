#include <dolphin/types.h>

class _JOUTAI {
public:
    u16 joutaiDataId;
    u16 userFightTargetId;
    u8 kaisuu;
    u8 nowKaisuu;
    u8 count;
    u8 unk7;
    u32 buff;
    u16 idBuff;

    void writeJoutaiDataId(u16 id, u16 target);
    s32 checkWriteJoutaiDataId(u16 id);
    u8 isValid();
    void init();
};

extern "C" {

u8 joutaiDataBiosGetWriteMode(u16 id);
u8 joutaiDataBiosGetKaisuuDataId(u16 id);
s32 joutaiDataBiosGetMaxCount(u16 id);
u16 joutaiDataBiosGetSameJoutai(u16 id);
u8 joutaiDataBiosGetUseBanme(u16 id);
u8 joutaiDataBiosGetStatusKind(u16 id);
u16 joutaiDataBiosGetStatus(u16 id);
s32 joutaiBiosGetCount(_JOUTAI* j);
u16 joutaiBiosGetJoutaiDataId(_JOUTAI* j);
u32 joutaiBiosGetBuff(_JOUTAI* j);
void joutaiBiosSetBuff(_JOUTAI* j, u32 v);
u16 joutaiBiosGetIdBuff(_JOUTAI* j);
void joutaiBiosSetIdBuff(_JOUTAI* j, u16 v);
u16 joutaiBiosGetUserFightTargetId(_JOUTAI* j);
s8 joutaiBiosGetKaisuu(_JOUTAI* j);
s8 joutaiBiosGetNowKaisuu(_JOUTAI* j);
void joutaiBiosSetNowKaisuu(_JOUTAI* j, u8 v);
s32 kaisuuGetKaisuu(u32 idx);
void* statusGetStatus(u8 kind, void* p, u16 a, u16 b, u16 c);
u8 joutaiIsJoutaiDataId(void* p, u16 id);

}

static _JOUTAI* _joutaiGetTargetJoutaiPtrAsJoutaiDataId(void* p, u16 id);
static void _joutaiInit(_JOUTAI* j);

void _JOUTAI::writeJoutaiDataId(u16 id, u16 target) {
    if (id != 0) {
        u8 mode = joutaiDataBiosGetWriteMode(id);
        s32 cnt = (mode == 4) ? joutaiBiosGetCount(this) : 0;
        init();
        joutaiDataId = id;
        userFightTargetId = target;
        kaisuu = kaisuuGetKaisuu(joutaiDataBiosGetKaisuuDataId(id));
        if (mode == 4) {
            s32 n = cnt + 1;
            s32 max = joutaiDataBiosGetMaxCount(id);
            if ((u8)max < (u8)n) {
                n = max;
            }
            count = n;
        }
    }
}

s32 _JOUTAI::checkWriteJoutaiDataId(u16 id) {
    if (id == 0) {
        return 1;
    }
    u16 cur = joutaiDataId;
    switch (joutaiDataBiosGetWriteMode(id)) {
    case 0:
        return 2;
    case 1:
        return 2;
    case 2:
        return (isValid() ? 0 : 1) + 1;
    case 3:
        if (isValid() == 0) {
            return 2;
        }
        if (cur != id && id != joutaiDataBiosGetSameJoutai(cur)) {
            return 2;
        }
        return 1;
    case 4:
        if (isValid() == 0) {
            return 2;
        }
        if (cur == id || id == joutaiDataBiosGetSameJoutai(cur)) {
            return 2;
        }
        return 1;
    }
    return 0;
}

u8 _JOUTAI::isValid() {
    return joutaiBiosGetJoutaiDataId(this) != 0;
}

void _JOUTAI::init() {
    joutaiDataId = 0;
    userFightTargetId = 0;
    kaisuu = 0;
    nowKaisuu = 0;
    count = 0;
    buff = 0;
    idBuff = 0;
}

extern "C" {

void joutaiCopy(void* dstBase, void* srcBase, u16 id) {
    if (id != 0) {
        _JOUTAI* dst = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(dstBase, id);
        if (dst != 0) {
            if (joutaiIsJoutaiDataId(srcBase, id)) {
                _JOUTAI* src = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(srcBase, id);
                if (src != 0) {
                    dst->joutaiDataId = src->joutaiDataId;
                    dst->userFightTargetId = src->userFightTargetId;
                    dst->kaisuu = src->kaisuu;
                    dst->nowKaisuu = src->nowKaisuu;
                    dst->count = src->count;
                    dst->unk7 = src->unk7;
                    dst->buff = src->buff;
                    dst->idBuff = src->idBuff;
                }
            }
        }
    }
}

void joutaiSetBuff(void* base, u16 id, u32 value) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            joutaiBiosSetBuff(j, value);
        }
    }
}

u32 joutaiGetBuff(void* base, u16 id) {
    if (id == 0) {
        return 0;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return 0;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return 0;
    }
    return joutaiBiosGetBuff(j);
}

void joutaiSetIdBuff(void* base, u16 id, u16 value) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            joutaiBiosSetIdBuff(j, value);
        }
    }
}

u16 joutaiGetIdBuff(void* base, u16 id) {
    if (id == 0) {
        return 0;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return 0;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return 0;
    }
    return joutaiBiosGetIdBuff(j);
}

u16 joutaiGetUserFightTargetId(void* base, u16 id) {
    if (id == 0) {
        return 0;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return 0;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return 0;
    }
    return joutaiBiosGetUserFightTargetId(j);
}

void joutaiSetKaisuuJoutaiDataId(void* base, u16 id, s8 value) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            j->kaisuu = value;
        }
    }
}

void joutaiSetNowKaisuuJoutaiDataId(void* base, u16 id, u8 value) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            joutaiBiosSetNowKaisuu(j, value);
        }
    }
}

s8 joutaiGetNowKaisuuJoutaiDataId(void* base, u16 id) {
    if (id == 0) {
        return -1;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return -1;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return -1;
    }
    return joutaiBiosGetNowKaisuu(j);
}

s8 joutaiGetKaisuuJoutaiDataId(void* base, u16 id) {
    if (id == 0) {
        return -1;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return -1;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return -1;
    }
    return joutaiBiosGetKaisuu(j);
}

void joutaiSetCountAsJoutaiDataId(void* base, u16 id, u8 value) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            j->count = value;
        }
    }
}

s32 joutaiGetCountAsJoutaiDataId(void* base, u16 id) {
    if (id == 0) {
        return -1;
    }
    if (!joutaiIsJoutaiDataId(base, id)) {
        return -1;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return -1;
    }
    return (u8)joutaiBiosGetCount(j);
}

void joutaiWriteJoutaiDataId(void* base, u16 id, u16 target) {
    if (id != 0) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            j->writeJoutaiDataId(id, target);
        }
    }
}

s32 joutaiCheckWriteJoutaiDataId(void* base, u16 id) {
    if (id == 0) {
        return 1;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return 0;
    }
    return j->checkWriteJoutaiDataId(id);
}

u8 joutaiIsJoutaiDataId(void* base, u16 id) {
    if (id == 0) {
        return 0;
    }
    _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
    if (j == 0) {
        return 0;
    }
    if (j->isValid() == 1 && id == joutaiBiosGetJoutaiDataId(j)) {
        return 1;
    }
    return 0;
}

void joutaiInitJoutaiDataId(void* base, u16 id) {
    if (id != 0 && joutaiIsJoutaiDataId(base, id)) {
        _JOUTAI* j = _joutaiGetTargetJoutaiPtrAsJoutaiDataId(base, id);
        if (j != 0) {
            _joutaiInit(j);
        }
    }
}

void joutaiInitAry(_JOUTAI* ary, u16 num) {
    if (ary != 0) {
        u16 i;
        for (i = 0; i < num; i++) {
            _joutaiInit(ary + i);
        }
    }
}

}

static void _joutaiInit(_JOUTAI* j) {
    if (j != 0) {
        j->init();
    }
}

static _JOUTAI* _joutaiGetTargetJoutaiPtrAsJoutaiDataId(void* p, u16 id) {
    u16 banme = joutaiDataBiosGetUseBanme(id);
    u8 kind = joutaiDataBiosGetStatusKind(id);
    u16 status = joutaiDataBiosGetStatus(id);
    u8* s = (u8*)statusGetStatus(kind, p, 0, status, 0);
    if (s == 0) {
        return 0;
    }
    return (_JOUTAI*)(s + banme * 16);
}
