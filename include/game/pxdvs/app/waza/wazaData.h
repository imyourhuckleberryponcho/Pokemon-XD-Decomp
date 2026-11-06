#ifndef GAME_WAZADATA_H
#define GAME_WAZADATA_H

#include <dolphin/types.h>

struct WazaData {
    u8 pri;
    u8 pp;
    u8 zokuseiDataId;
    u8 rangeId;
    u8 avg;
    u8 addFightKoukaAvg;
    u8 dageki;
    u8 mamoru;
    u8 majikku;
    u8 yokodori;
    u8 oumugaesi;
    u8 oujanosirusi;
    u8 yubiwohuru;
    u8 monomane;
    u8 nekonote;
    u8 negoto;
    u8 bouon;
    u8 pressure;
    u8 hidenFlag;
    u8 darkWazaKind;
    u8 riskFlag;
    u8 compatible;
    u8 unk16[2];
    s16 iryoku;
    u16 fightKoukaDataId;
    u16 seqId;
    u16 wazaFuncDataId;
    u32 name;
    u32 fightAttackTunagiMsgId;
    u32 fightAttackMsgId;
    u32 doc;
    u32 wazawzxdataId;
    u8 typeId[3];
    u8 pad37;
};

#endif
