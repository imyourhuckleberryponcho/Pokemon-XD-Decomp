#include <dolphin/types.h>

#pragma peephole off

#pragma pool_strings off

struct MenuFaceData {
    u8 rareFlag : 1;
    u8 unk0 : 7;
    u8 unk1[3];
    u32 texID;
};

extern "C" {
void GSlogWrite(const char* fmt, ...);
extern u32* poke_face_number;
extern MenuFaceData* poke_face;
}

static MenuFaceData* _menuFaceBiosGetPtr(u16 id);

bool menuFaceBiosGetRareFlag(u16 id) {
    MenuFaceData* data = _menuFaceBiosGetPtr(id);
    if (data == NULL) {
        return false;
    }
    return data->rareFlag != 0;
}

u32 menuFaceBiosGetTexID(u16 id) {
    MenuFaceData* data = _menuFaceBiosGetPtr(id);
    if (data == NULL) {
        return 0;
    }
    return data->texID;
}

static MenuFaceData* _menuFaceBiosGetPtr(u16 id) {
    if (id >= *poke_face_number) {
        GSlogWrite("[%s] 範囲外アクセスです\n", __FUNCTION__);
        return 0;
    }
    return &poke_face[id];
}
