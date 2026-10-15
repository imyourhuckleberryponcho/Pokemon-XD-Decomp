#include <dolphin/types.h>

#pragma peephole off

struct _GSgfxInitParms {
    u8 unk0;
    u8 unk4_pad[3];
    u8 unk4;
    u8 unk5;
    u16 unk6;
    s32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
};

void GSgfxInit(_GSgfxInitParms* parms);

struct SystemVars {
    s32 debug;
    s32 memSize;
    u8 unk8[4];
    s32 unkC;
    u8 unk10[0x38];
    u8 dvdServer[0x10];
    u8 gcClient0[0x10];
    u32 dvdServerPort;
    u32 reportServerPort;
    u8 gcClient1[0x10];
    u8 gcClient2[0x10];
};

extern "C" {

extern SystemVars systemVars;

void pokecoloInitRomVersion(void);
void* memset(void* dst, int c, unsigned long n);
void sysvarsReadSettings(int* argc, char*** argv);
u32 OSGetConsoleSimulatedMemSize(void);
void OSSetArenaHi(void* hi);
void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaLo(void* lo);
void* GSmemInit(void* lo, void* hi, s32);
void GSfsysCreateLocalHeap(void);
void GSfsysCreateCacheHeap(void);
void floorCreateLocalHeap(void);
s32 GSmemCreateHeap(void* lo, void* hi);
void GSmemSetCurrentHeap(s32 heap);
void GSmemInitSysdolAllocator(void);
s32 pokecoloGetCountryCode(void);
void sysvarsShowDebug(void);
void ARInit(u32* stack, u32 num);
void ARQInit(void);
void AIInit(u8* stack);
void ARQSetChunkSize(u32 size);
void GSlogInit(u32 size, s32);
void GSscratchInit(s32);
void GSdvdSetDVDServer(void* server, u16 port);
void GSdvdSetReportServer(void* server, u16 port, s32);
void GSdvdSetGCClient(void*, void*, void*, s32);
void pokecoloMain(int argc, char** argv);

static u8 aiStackMem[0x4000];
static u32 aramMemArray[2];
s32 g_hFloorHeap;
s32 g_hSysdolphineHeap;

void main(int argc, char** argv) {
    _GSgfxInitParms parms;
    void* lo;
    void* hi;

    pokecoloInitRomVersion();
    memset((void*)0x80001800, 0, 0x1800);
    sysvarsReadSettings(&argc, &argv);

    if (OSGetConsoleSimulatedMemSize() > 0x1800000) {
        if (systemVars.memSize == 24) {
            OSSetArenaHi((void*)0x817ED780);
        } else if (systemVars.memSize == 48) {
            OSSetArenaHi((void*)0x82DED720);
        }
    }

    lo = OSGetArenaLo();
    OSGetArenaHi();
    OSSetArenaLo(GSmemInit(lo, OSGetArenaHi(), 4));
    GSfsysCreateLocalHeap();
    GSfsysCreateCacheHeap();
    floorCreateLocalHeap();

    lo = OSGetArenaLo();
    hi = OSGetArenaHi();
    g_hFloorHeap = GSmemCreateHeap(lo, hi);
    GSmemSetCurrentHeap(g_hFloorHeap);
    OSSetArenaLo(hi);
    g_hSysdolphineHeap = g_hFloorHeap;
    GSmemInitSysdolAllocator();

    parms.unk0 = systemVars.unkC != 0;
    parms.unkC = 0x50000;
    parms.unk10 = 0x50000;
    parms.unk14 = 0x10;
    switch (pokecoloGetCountryCode()) {
    case 0:
    case 1:
        parms.unk8 = 0;
        break;
    case 2:
        parms.unk8 = 1;
        break;
    }
    parms.unk4 = 2;
    parms.unk6 = 0x1E0;
    GSgfxInit(&parms);

    if (systemVars.debug == 1) {
        sysvarsShowDebug();
    }

    ARInit(aramMemArray, 2);
    ARQInit();
    AIInit(aiStackMem + sizeof(aiStackMem) - 8);
    ARQSetChunkSize(0x8000);
    GSlogInit(0x8000, 2);
    GSscratchInit(0);
    GSdvdSetDVDServer(systemVars.dvdServer, systemVars.dvdServerPort);
    GSdvdSetReportServer(systemVars.dvdServer, systemVars.reportServerPort, 1);
    GSdvdSetGCClient(systemVars.gcClient0, systemVars.gcClient1, systemVars.gcClient2, 1);
    pokecoloMain(argc, argv);
}

}
