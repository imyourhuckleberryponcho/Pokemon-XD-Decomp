#include <dolphin/types.h>

#pragma pack(push, 1)
// Arguments of the WS_STATUS_* move-sequence commands, as laid out in the script data.
struct WsStatusCmd {
    u8 opcode;
    u8 side;
    u32* kind;
    u8* index;
    u16 id;
    u8* sub;
    void* value;
};
#pragma pack(pop)

extern "C" {

WsStatusCmd* fightSeq_GetWazaSeq(void);
void fightSeq_NextWazaSeq(s32 size);
void statusSetStatus(u8 side, u32 kind, u8 index, u16 id, u8 sub, u32 value);
u32 statusGetStatus(u8 side, u32 kind, u8 index, u16 id, u8 sub);

void WS_STATUS_SET32(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u32* value = (u32*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    statusSetStatus(side, k, i, id, sb, *value);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

void WS_STATUS_SET16(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u16* value = (u16*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    statusSetStatus(side, k, i, id, sb, *value);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

void WS_STATUS_SET8(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u8* value = (u8*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    statusSetStatus(side, k, i, id, sb, *value);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

void WS_STATUS_GET32(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u32* value = (u32*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    *value = statusGetStatus(side, k, i, id, sb);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

void WS_STATUS_GET16(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u16* value = (u16*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    *value = statusGetStatus(side, k, i, id, sb);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

void WS_STATUS_GET8(void) {
    WsStatusCmd* cmd = fightSeq_GetWazaSeq();
    u32* kind = cmd->kind;
    u8 side = cmd->side;
    u8* index = cmd->index;
    u16 id = cmd->id;
    u8* sub = cmd->sub;
    u32 k;
    u8 i;
    u8 sb;
    u8* value = (u8*)cmd->value;
    if (kind == NULL) {
        k = 0;
    } else {
        k = *kind;
    }
    if (index == NULL) {
        i = 0;
    } else {
        i = *index;
    }
    if (sub == NULL) {
        sb = 0;
    } else {
        sb = *sub;
    }
    *value = statusGetStatus(side, k, i, id, sb);
    fightSeq_NextWazaSeq(sizeof(WsStatusCmd));
}

}
