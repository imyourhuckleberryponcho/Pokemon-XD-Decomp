#ifndef GAME_SAVELAYOUT_H
#define GAME_SAVELAYOUT_H
#include <dolphin/types.h>
#include <game/bitfield.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/menuCBRecords.h>

struct SaveFileHeader {
    char gameTitle[0x20];
    char fileComment[0x20];
    u8 banner[0x1800];
    u8 icon[0x2200];
    s32 checksum;
    u8 zero[0x25BC];
};

struct SaveSlot {
    u8 magic[3];
    u8 zero3;
    s32 saveCounter;
    u8 pack[0x27FD0];
    u8 randomTail[0x28];
};

struct SaveHalves {
    u16 lo;
    u16 hi;
};
struct SavePackHeader {
    u16 key[4];
    SaveHalves sum3;
    SaveHalves sum2;
    SaveHalves sum1;
    SaveHalves sum0;
    u16 sizeGamedata;
    u16 sizeHero;
    u16 sizePcboxLo;
    u16 sizeMailbox;
    u16 sizeSodateya;
    u16 sizeMemo;
    u16 sizeTool;
    u16 sizeDarkpokemon;
    u16 sizeFlags;
    u16 sizeExRibbon;
    u16 sizeYobi1;
    u16 sizeYobi2;
    u16 sizeYobi3;
    u16 sizeYobi4;
    u16 sizeRelive;
    u16 sizeAnywaySave;
    SaveHalves offGamedata;
    SaveHalves offHero;
    SaveHalves offPcbox;
    SaveHalves offMailbox;
    SaveHalves offSodateya;
    SaveHalves offMemo;
    SaveHalves offTool;
    SaveHalves offDarkpokemon;
    SaveHalves offFlags;
    SaveHalves offExRibbon;
    SaveHalves offYobi1;
    SaveHalves offYobi2;
    SaveHalves offYobi3;
    SaveHalves offYobi4;
    SaveHalves offRelive;
    SaveHalves offAnywaySave;
    u16 flagLevel0Bytes;
    u16 flagLevel1Bytes;
    u16 flagLevel2Bytes;
    u16 battleDiskBitsBytes;
    u16 sizePcboxHi;
    u16 bingoBitsBytes;
    u8 unused84[0x1C];
};

struct SaveGamedataAttest {
    u8 verId;
    u8 genId;
    u8 areaId;
    u8 langareaId;
};
struct SaveGamedataSave {
    u64 memcardID;
    u32 savecount;
    u32 savernd;
    u32 parChecksum;
    u32 floorid;
    f32 unk18;
    u32 prevfloorid;
    u8 floorposindex;
    u8 optionNoVibration;
    u8 optionAudio;
    u8 language;
    u8 unk24[4];
    f64 playtime;
    u32 sysHeadChecksum;
};
struct SaveGamedata {
    SaveGamedataAttest attest;
    u8 pad4[4];
    SaveGamedataSave save;
    u16 zukanFlags;
    u8 pad42[2];
    u32 playdata44[16];
    u8 pad84[4];
};

struct SaveHero {
    Hero hero;
    u8 unkTail[0x978 - sizeof(Hero)];
};

struct SaveItemSlot {
    u16 itemDataId;
    u16 num;
};
struct SavePcBoxBox {
    u16 name[9];
    u16 nameTerm;
    Pokemon pokemon[30];
};
struct SavePcbox {
    SavePcBoxBox box[8];
    SaveItemSlot item[235];
    s32 lastViewBox;
    u32 unkBC10[16];
};

struct SaveMailbox {
    u16 ids[32];
    u16 count;
    u8 unread[4];
    u8 sortMode;
    u8 unk47;
    u16 sendCnt;
};

struct SaveSodateya {
    u8 active;
    u8 level;
    u16 steps;
    s32 dp;
    Pokemon pokemon;
};

struct SaveMemoEntry {
    u16 id;
    u16 pad;
    u32 trainerRnd;
    u32 rnd;
};
struct SaveMemo {
    u16 count;
    u16 pad;
    SaveMemoEntry entries[500];
};

struct SaveTool {
    MenuCBRule rule[6];
    s8 working;
    u8 pad361[3];
};

struct SaveDarkPokemon {
    GC_BITS9(u32 status : 3,
             u32 reserved0 : 1,
             u32 snatchInfoLevel : 3,
             u32 snatchFromWho : 2,
             u32 revers : 1,
             u32 update : 1,
             u32 wazaNew : 3,
             u32 where : 3,
             u32 unk0 : 15)
    GC_BITS4(u32 poolExp : 20,
             u32 catchBallId : 4,
             u32 information : 1,
             u32 unk4 : 7)
    u8 unk08[3];
    u8 statusRnd[6];
    u8 unk11[2];
    u8 snatchIndex;
    u16 orgTrainer;
    u16 catchFloorId;
    u16 poolFriendLevel;
    u16 pokemonID;
    u32 rnd;
    u32 escapeOrSnatchTime;
    s32 darkPoint;
    u16 trainerName[10];
    u16 trainerNameTerm;
    u16 darkPokemonID;
    u8 reversPattern;
    u8 unk41[3];
    u32 walkCount;
};
struct SaveDarkpokemonList {
    SaveDarkPokemon entry[128];
};

struct SaveFlags {
    u32 level0[8];
    u32 level1[0x20];
    u32 level2[0x180];
    u32 battleDiskSellOut[2];
    u32 bingoBits[2];
    u32 unk6B0;
};

struct SaveExRibbon {
    u8 no[11];
};

struct SaveAnywayHeader {
    char magic[4];
    u32 totalSize;
    u32 scriptStateSize;
    u32 pushStateSize;
    u32 unk10;
    u32 maxTotal;
    u16 maxFloorID;
    u8 pad1A[6];
};
struct SaveAnywaySave {
    SaveAnywayHeader header;
    u8 data[0xC800 - 0x20];
};
struct SaveFloorPushHeader {
    u32 magic;
    u32 totalSize;
};
struct SaveFloorPushRecord {
    u32 moduleUID;
    u32 recordSize;
};
struct SaveColsysState {
    u16 magic;
    u16 pad;
    u16 flags[64];
};
struct SavePeopleFlags {
    GC_BITS7(u8 active : 1, u8 display : 1, u8 flag2 : 1, u8 flag150 : 1, u8 flag3 : 1, u8 flag4A : 1, u8 unused0 : 2)
    GC_BITS3(u8 moveType : 3, u8 motion : 3, u8 mode : 2)
    GC_BITS2(u8 targetType : 2, u8 unused2 : 6)
    u8 unused3[2];
};

struct SaveReliveStage {
    Pokemon dancer[4];
    Pokemon visitor;
    s8 hit;
    u8 pad3D5[3];
};
struct SaveReliveHall {
    SaveReliveStage stage[9];
};

struct SaveYobi1 { u8 data[0x400]; };
struct SaveYobi2 { u8 data[0x800]; };
struct SaveYobi3 { u8 data[0x1000]; };
struct SaveYobi4 { u8 data[0x2000]; };

#endif
