#include <dolphin/types.h>

// Purification Chamber tutorial: scripted button sequences and message timing.
#pragma peephole off

struct CState {
    u32 current, next, reserved8, index;
    f32 time;
    u32 reserved14;
    u8 work[0x40];
    u8 reserved58[0x4C];
    u32 tutorialTimer;
    void update();
    inline void advance() { next = current + 1; memset(work, 0, sizeof(work)); }
};
struct ReliveTutorial {
    u8 reserved[0x15D];
    u8 finished, cancelled, reserved15F;
    CState state;
};
class CMetaMenu;
struct CInfoWindow {
    u8 reserved[0x30];
    u16 buttons;
    u8 reserved32[2];
    void exec(CMetaMenu&, u32, bool);
};
class CMetaMenu {
    u8 reserved[0x244];
    CInfoWindow info;
    u8 reserved278[0xB0];
    ReliveTutorial* tutorial;
    u8 updated, reserved32D;
    u16 cachedInput;
public:
 // Preserve the retail virtual-table slots following the menu's data members.
    virtual void reservedVirtual0();
    virtual u8 tutorialReady();
    virtual void reservedVirtual2();
    virtual void tutorialClose();
    u16 tutorialManagePrime();
    void tutorialManageUpdate();
    u16 tutorialManage();
    void tutorialMessage(u32);
};
struct WindowKeyInfo { u8 reserved[4]; u16 buttons; };
extern "C" {
WindowKeyInfo* windowGetKeyInfo();
u8 GSgfxVideoGetVsyncRate();
}

u16 CMetaMenu::tutorialManagePrime()
{
    CState& state = tutorial->state;
    if (tutorial->finished) return 0x20;
    if (windowGetKeyInfo()->buttons == 0x20) {
        ReliveTutorial* t = tutorial;
        t->finished = 1;
        t->cancelled = 1;
        return 0x20;
    }
    state.tutorialTimer++;
    if (!tutorialReady()) return 0;
    if (state.tutorialTimer < (u32)(0.9f * (f32)GSgfxVideoGetVsyncRate())) return 0;
    state.tutorialTimer = 0;
    u16 input = 0;
    state.update();
    switch (state.current) {
    case 0: {
        tutorialMessage(0xd138);
        state.advance();
        break;
    }
    case 1: {
        if (!state.time) tutorialMessage(0xd139);
        static u16 tbl[] = { 0x0, 0x400, 0x400, 0x400, 0x400 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 2: {
        if (!state.time) tutorialMessage(0xd13a);
        static u16 tbl[] = { 0x0, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 3: {
        tutorialMessage(0xd13b);
        state.advance();
        break;
    }
    case 4: {
        if (!state.time) tutorialMessage(0xd13c);
        static u16 tbl[] = { 0x0, 0x8, 0x8, 0x8, 0x8, 0x10, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 5: {
        if (!state.time) tutorialMessage(0xd13d);
        static u16 tbl[] = { 0x0, 0x2, 0x2, 0x2, 0x2, 0x2 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 6: {
        input = 0x10;
        state.advance();
        break;
    }
    case 7: {
        tutorialMessage(0xd13e);
        state.advance();
        break;
    }
    case 8: {
        if (!state.time) tutorialMessage(0xd13f);
        static u16 tbl[] = { 0x0, 0x200, 0x400, 0x400 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 9: {
        if (!state.time) tutorialMessage(0xd140);
        static u16 tbl[] = { 0x0, 0x200 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 10: {
        if (!state.time) tutorialMessage(0xd141);
        static u16 tbl[] = { 0x0, 0x1, 0x10, 0x10, 0x40 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 11: {
        if (!state.time) tutorialMessage(0xd142);
        static u16 tbl[] = { 0x0, 0x100, 0x8, 0x8, 0x8, 0x10, 0x20 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 12: {
        if (!state.time) tutorialMessage(0xd143);
        static u16 tbl[] = { 0x0, 0x1, 0x1, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 13: {
        if (!state.time) tutorialMessage(0xd144);
        static u16 tbl[] = { 0x0, 0x2, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 14: {
        static u16 tbl[] = { 0x0, 0x100, 0x8, 0x8, 0x10, 0x20 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 15: {
        if (!state.time) tutorialMessage(0xd145);
        static u16 tbl[] = { 0x0, 0x1, 0x8 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 16: {
        static u16 tbl[] = { 0x0, 0x4 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 17: {
        if (!state.time) tutorialMessage(0xd146);
        static u16 tbl[] = { 0x0, 0x8, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 18: {
        static u16 tbl[] = { 0x0, 0x100, 0x2, 0x8, 0x8, 0x8, 0x10, 0x20 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 19: {
        if (!state.time) tutorialMessage(0xd147);
        u16 tbl[] = { 0x0, 0x1, 0x9, 0x1, 0x8, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 20: {
        if (!state.time) tutorialMessage(0xd148);
        static u16 tbl[] = { 0x0, 0x100, 0x10, 0x20 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 21: {
        if (!state.time) tutorialMessage(0xd149);
        static u16 tbl[] = { 0x0, 0x1, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 22: {
        if (!state.time) tutorialMessage(0xd14a);
        static u16 tbl[] = { 0x0, 0x40 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 23: {
        if (!state.time) tutorialMessage(0xd14b);
        static u16 tbl[] = { 0x0, 0x10, 0x2, 0x10, 0xa, 0x10 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 24: {
        tutorialMessage(0xd14c);
        state.advance();
        break;
    }
    case 25: {
        if (!state.time) tutorialMessage(0xd14d);
        static u16 tbl[] = { 0x0, 0x20, 0x2 };
        if (state.index < sizeof(tbl) / sizeof(tbl[0])) input = tbl[state.index];
        else state.advance();
        break;
    }
    case 26: {
        ReliveTutorial* t = tutorial;
        t->finished = 1;
        t->cancelled = 0;
        input = 0x10;
        break;
    }
    }
    return input;
}

void CMetaMenu::tutorialManageUpdate()
{
    updated = 0;
}

u16 CMetaMenu::tutorialManage()
{
    if (updated) return cachedInput;
    updated = 1;
    cachedInput = tutorialManagePrime();
    return cachedInput;
}

void CMetaMenu::tutorialMessage(u32 message)
{
    info.exec(*this, message, true);
    if (info.buttons == 0x20) {
        tutorialClose();
        ReliveTutorial* t = tutorial;
        t->finished = 1;
        t->cancelled = 1;
    }
}
