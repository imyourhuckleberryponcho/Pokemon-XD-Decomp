#include <game/pxdvs/app/memcard/savedata.hpp>

struct BINGO_PANEL_dd_ {
    u8 type;
    u8 tokusei;
    u8 unk2[2];
    u16 no;
    u16 waza;
    u16 hosei;
};

struct BINGO_GRID_dd_ {
    u8 grid;
    u8 pos;
};

struct BINGO_DATA_dd_ {
    u8 no;
    u8 unk1[2];
    u8 level;
    u8 unk4;
    u8 ball;
    u8 unk6[0x10 - 6];
    u16 score[10];
    BINGO_PANEL_dd_ panel[14];
    BINGO_GRID_dd_ grid[3];
    u8 unkB6[2];
};

struct BingoSave {
    u32 flags;
    u32 plus;
};

class bingo_bios {
public:
    bool isClearPlus(u32 index);
    void setClearPlus(u32 index);
    void setClear(u32 index);
    static void setSelect(u32 index);
    bool isSelect(u32 index);
    bool isClear(u32 index);
    u32 getClearLv();
    u16 getScore(BINGO_DATA_dd_* data, u8 index);
    u8 getGridPos(BINGO_DATA_dd_* data, u32 index);
    u8 getGridGrid(BINGO_DATA_dd_* data, u32 index);
    static u8 getPanelHoseiVal(BINGO_DATA_dd_* data, u32 index);
    static u8 getPanelHoseiKind(BINGO_DATA_dd_* data, u32 index);
    u16 getPanelWaza(BINGO_DATA_dd_* data, u32 index);
    u16 getPanelNo(BINGO_DATA_dd_* data, u32 index);
    u8 getPanelTokusei(BINGO_DATA_dd_* data, u32 index);
    u8 getPanelType(BINGO_DATA_dd_* data, u32 index);
    u8 getBall(BINGO_DATA_dd_* data);
    u8 getLevel(BINGO_DATA_dd_* data);
    u8 getNo(BINGO_DATA_dd_* data);
    static u8 getStaticIdx(u8 index);
    static void setStaticIdx(u8 idx0, u8 idx1);
    static u8 getStaticResult();
    static void setStaticResult(u8 result);
    static void decStaticBall();
    static u8 getStaticBall();
    static void setStaticBall(u8 ball);
    static BINGO_DATA_dd_* getStaticSheet();
    static void setStaticNo(u8 no);

    static u8 mStaticNo;
    static u8 mStaticBall;
    static u8 mStaticIdx[2];
    static u8 mStaticResult;
};

extern "C" {
extern u32* bingo_data_number;
extern BINGO_DATA_dd_* bingo_data;
}

u8 bingo_bios::mStaticNo;
u8 bingo_bios::mStaticBall;
u8 bingo_bios::mStaticIdx[2];
u8 bingo_bios::mStaticResult;

bool bingo_bios::isClearPlus(u32 index) {
    if (index >= *bingo_data_number) {
        return false;
    }
    BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
    return (save->plus & (1 << index)) ? 1 : 0;
}

void bingo_bios::setClearPlus(u32 index) {
    if (index < *bingo_data_number) {
        BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
        save->plus |= 1 << index;
    }
}

void bingo_bios::setClear(u32 index) {
    if (index < *bingo_data_number) {
        BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
        save->flags |= 1 << (index * 2);
    }
}

void bingo_bios::setSelect(u32 index) {
    BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
    save->flags |= 2 << (index * 2);
}

bool bingo_bios::isSelect(u32 index) {
    if (index >= *bingo_data_number) {
        return false;
    }
    BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
    return (save->flags & (2 << (index * 2))) ? 1 : 0;
}

bool bingo_bios::isClear(u32 index) {
    if (index >= *bingo_data_number) {
        return false;
    }
    BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
    return (save->flags & (1 << (index * 2))) ? 1 : 0;
}

u32 bingo_bios::getClearLv() {
    BingoSave* save = (BingoSave*)savedataGetStatus(0, 0x1B);
    u32 lvTable[4] = { 0, 1, 2, 3 };
    u32 counts[4] = { 3, 6, 9, *bingo_data_number };
    s32 i;
    s32 max = 0;
    u32 count = 0;
    s32 extra = 0;
    s32 lv;
    for (i = 0; i < *bingo_data_number; i++) {
        if ((save->flags & (1 << (i * 2))) && i != 10) {
            if (max < i) {
                max = i;
            }
            count++;
        }
    }
    if (max < 3) {
        lv = 0;
    } else if (max < 6) {
        lv = 1;
    } else if (max < 9) {
        lv = 2;
    } else {
        lv = 3;
    }
    if (count == counts[lv]) {
        extra = 1;
    }
    lv += extra;
    for (i = 0; i < counts[lv]; i++) {
        if (i != 10) {
            save->flags |= 2 << (i * 2);
        }
    }
    return lvTable[lv];
}

u16 bingo_bios::getScore(BINGO_DATA_dd_* data, u8 index) {
    if (index >= 10) {
        return 0;
    }
    return data->score[index];
}

u8 bingo_bios::getGridPos(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 3) {
        return 0;
    }
    return data->grid[index].pos;
}

u8 bingo_bios::getGridGrid(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 3) {
        return 0;
    }
    return data->grid[index].grid;
}

u8 bingo_bios::getPanelHoseiVal(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return data->panel[index].hosei;
}

u8 bingo_bios::getPanelHoseiKind(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return (data->panel[index].hosei >> 12) & 0xF;
}

u16 bingo_bios::getPanelWaza(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return data->panel[index].waza;
}

u16 bingo_bios::getPanelNo(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return data->panel[index].no;
}

u8 bingo_bios::getPanelTokusei(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return data->panel[index].tokusei;
}

u8 bingo_bios::getPanelType(BINGO_DATA_dd_* data, u32 index) {
    if (index >= 14) {
        return 0;
    }
    return data->panel[index].type;
}

u8 bingo_bios::getBall(BINGO_DATA_dd_* data) {
    if (data != NULL) {
        return data->ball;
    }
    return 0;
}

u8 bingo_bios::getLevel(BINGO_DATA_dd_* data) {
    if (data != NULL) {
        return data->level;
    }
    return 0;
}

u8 bingo_bios::getNo(BINGO_DATA_dd_* data) {
    if (data != NULL) {
        return data->no;
    }
    return 0;
}

u8 bingo_bios::getStaticIdx(u8 index) {
    if (index >= 2) {
        return 0;
    }
    return mStaticIdx[index];
}

void bingo_bios::setStaticIdx(u8 idx0, u8 idx1) {
    mStaticIdx[0] = idx0;
    mStaticIdx[1] = idx1;
}

u8 bingo_bios::getStaticResult() { return mStaticResult; }

void bingo_bios::setStaticResult(u8 result) { mStaticResult = result; }

void bingo_bios::decStaticBall() {
    if (mStaticBall != 0) {
        mStaticBall--;
    }
}

u8 bingo_bios::getStaticBall() { return mStaticBall; }

void bingo_bios::setStaticBall(u8 ball) { mStaticBall = ball; }

BINGO_DATA_dd_* bingo_bios::getStaticSheet() {
    if (*bingo_data_number <= mStaticNo) {
        return 0;
    }
    return &bingo_data[mStaticNo];
}

void bingo_bios::setStaticNo(u8 no) { mStaticNo = no; }
