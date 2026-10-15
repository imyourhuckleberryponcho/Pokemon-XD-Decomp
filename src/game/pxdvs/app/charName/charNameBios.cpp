#include <dolphin/types.h>

#pragma pool_strings off
#pragma peephole off

struct CharName {
    u16 hearFlag;
    u8 unk2[2];
    u32 nameID;
};

extern "C" {

void GSlogWrite(const char* fmt, ...);

extern u32* char_name_number;
extern CharName* char_name;

static inline CharName* charNameBiosGetPtr(u16 id) {
    if (id >= *char_name_number) {
        GSlogWrite("[%s]: テーブルインデックスが範囲外です\n", __FUNCTION__);
        return 0;
    }
    return &char_name[id];
}

u16 charNameBiosSearchIndex(u32 nameID) {
    for (u16 i = 0; i < *char_name_number; i++) {
        if (nameID == char_name[i].nameID) {
            return i;
        }
    }
    return 0;
}

u32 charNameBiosGetNameID(u16 id) {
    CharName* name = charNameBiosGetPtr(id);
    if (name == NULL) {
        return 0;
    }
    return name->nameID;
}

u16 charNameBiosGetHearFlag(u16 id) {
    CharName* name = charNameBiosGetPtr(id);
    if (name == NULL) {
        return 0;
    }
    return name->hearFlag;
}

}
