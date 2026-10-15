#include <dolphin/types.h>

struct FightKoukaData {
    u16 fightJoukenDataId;
    u16 fightTargetDataId;
    u16 koukaDataId;
};

extern "C" {

extern FightKoukaData fight_kouka_data[];
extern u32 fight_kouka_data_number;

u16 fightKoukaDataBiosGetKoukaDataId(FightKoukaData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->koukaDataId;
}

u16 fightKoukaDataBiosGetFightTargetDataId(FightKoukaData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightTargetDataId;
}

u16 fightKoukaDataBiosGetFightJoukenDataId(FightKoukaData* data) {
    if (data == NULL) {
        return 0;
    }
    return data->fightJoukenDataId;
}

FightKoukaData* fightKoukaDataBiosGetPtr(u16 id) {
    if (id >= fight_kouka_data_number) {
        return 0;
    }
    return &fight_kouka_data[id];
}

}
