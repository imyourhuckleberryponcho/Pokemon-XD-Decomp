// Message-control commands (msgctrl): written in reverse order (the unit was built with
// -inline deferred, functions come out last-defined first).
#include <dolphin/types.h>
#pragma peephole off

struct MsgCtrl {
    u8 unk0;
    u8 activeFlag;
    u8 shadow;
    u8 talkSE;
    f32 f04;
    f32 f08;
    f32 f0c;
    f32 f10;
    u8 pad14[0xc];
    s16 font;
    u8 pad22;
    u8 unk23;
    u32 color;
    u8 pad28[4];
    u8* saved;
    u8* stream;
    u8 pad34[0xd];
    u8 indentOff;
    s8 lineSpace;
    s8 baseLineBias;
    u8 flags;
    u8 pending;
    u8 waitFlag;
    u8 waitFlag2;
    u8 pad48[2];
    s16 wait;
    u8 align;
    u8 ruby;
    u8 pad4e[0x1a];
    f32 f68;
};

struct FightOutPokemon;

extern "C" {
s32 GSsndGetStatus(u16);
void soundOpenPlay(u16, s32, s32);
void GSsndPlayNow(u32);
void GSmsgAdjustAlign(MsgCtrl*);
void GSmsgSetColor(MsgCtrl*);
void GSmsgSetFontInfo(MsgCtrl*);
void GSmsgInitRuby(MsgCtrl*);
void* GSmsgGetGSchar(s32);
u8 menuIsCheck(s32);
void peopleSetTalkFlagCallback();
void peopleSetTalkKeyWaitCallback();
s32 pokecoloGetCountryCode();
s32 pokecoloGetLanguage();
void* fightTrainerKindDataBiosGetPtr(u16);
void* fightTrainerKindDataBiosGetPrefixName(void*);
void* pokemonDataBiosGetPtr(u16);
void* pokemonDataBiosGetName(void*);
void* wazaDataBiosGetPtr(u16);
void* wazaDataBiosGetName(void*);
void* itemDataBiosGetPtr(u16);
void* itemDataBiosGetName(void*);
void* savedataGetStatus(s32, s32);
void* heroBiosGetNamePtr(void*);
void* heroBiosGetHizukiNamePtr(void*);
s32 fightFloorGetStatus(s32, s32, s32, s32);
void* fightTargetGetPtrAsNowFightType(s32, FightOutPokemon*);
void* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(s32, FightOutPokemon*);
void* fightSideGetValidFightTrainerPtr(void*, u16);
u8 fightTrainerCheckDoFight(void*);
void* fightTrainerGetNamePtr(void*);
u8 fightFloorIsNowEncountTuusinTaisen(s32);
u8 fightTargetIsHostSide(FightOutPokemon*, s32);
void* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
extern u32* msg_palette_number;
extern u8* msg_palette;
}

static inline void* getTrainer(FightOutPokemon* m)
{
    return fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, m);
}

static u32 _EV_STR_BUF0;
static u32 _EV_STR_BUF1;
static u32 _EV_STR_BUF2;
static u32 _ATTACK_MONS;
static u32 _DEFENCE_MONS;
static u32 _CLIENT_MONS;
static u32 _TSUIKA_MONS;
static u32 _MY_NAME;
static u32 _MY_MONS;
static u32 _MY_MONS2;
static u32 _ENEMY_MONS;
static u32 _ENEMY_MONS2;
static u32 _ENEMY_TMONS;
static u32 _ENEMY_TMONS2;
static u32 _SPEABI_NAMEA;
static u32 _SPEABI_NAMED;
static u32 _SPEABI_NAMEC;
static u32 _SPEABI_NAMET;
static u32 _CLIENTNOWORK;
static u32 _SIDE_ATTACK_NAMEHA;
static u32 _SIDE_ATTACK_NAMEWO;
static u32 _SIDE_ATTACK_NAMENO;
static u32 _TRAINER_TYPE;
static u32 _TRAINER_NAME;
static u32 _TRAINER_LOSE;
static u32 _TRAINER_ENENAME;
static u32 _TRAINER_ENENAME2;
static u32 _TRAINER_CLIENTNO;
static u32 _WAZA_NAME;
static u32 _ITEM_NAME;
static u32 _PASO_NAME;
static u32 _SIDE_DEFENCE_NAMEHA;
static u32 _SIDE_DEFENCE_NAMEWO;
static u32 _SIDE_DEFENCE_NAMENO;
static u16 _Item;
static u16 _Item2;
static u32 _Digit;
static u32 _Digit2;
static u32 _MsgID;
static u32 _Pokemon;
static u32 _Pokemon2;
static u32 _MenuDigit;
static u32 _MenuDigit2;
static u32 _MenuPokemon;
static u32 _MenuMsg;
static u32 _MenuMsg2;
static u16 _Waza;
static u32 _Money;
static u32 _Time;
static u32 _String;
static u32 _String2;
static u16 _PokemonID;
static u32 _MenuMoney;
static u32 _MenuMsgID;
static u32 _MenuMsgID2;
static u16 _Tribe;
static u16 _Npc;
static u16 _SndID;

static u16 half_digit_code[16] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46};
static u16 full_digit_code[16] = {0xFF10,0xFF11,0xFF12,0xFF13,0xFF14,0xFF15,0xFF16,0xFF17,0xFF18,0xFF19,0xFF21,0xFF22,0xFF23,0xFF24,0xFF25,0xFF26};

extern "C" {

void msgctrlInitValue()
{
    _MenuPokemon = 0;
    _MenuMsg = 0;
    _MenuMsg2 = 0;
    _Pokemon = 0;
    _Pokemon2 = 0;
    _String = 0;
    _String2 = 0;
}

void msgctrlSetValue(s32 id, u32 value)
{
    switch (id) {
    case 0x2D: _Item = (u16)value; break;
    case 0x2E: _Item2 = (u16)value; break;
    case 0x2F: _Digit = value; break;
    case 0x30: _Digit2 = value; break;
    case 0x31: _MsgID = value; break;
    case 0x32: _Pokemon = value; break;
    case 0x33: _Pokemon2 = value; break;
    case 0x34: _MenuDigit = value; break;
    case 0x35: _MenuDigit2 = value; break;
    case 0x36: _MenuPokemon = value; break;
    case 0x37: _MenuMsg = value; break;
    case 0x51: _MenuMsg2 = value; break;
    case 0x39: _Waza = (u16)value; break;
    case 0x4D: _String = value; break;
    case 0x57: _String2 = value; break;
    case 0x4E: _PokemonID = (u16)value; break;
    case 0x4B: _Money = value; break;
    case 0x4C: _Time = value; break;
    case 0x50: _MenuMoney = value; break;
    case 0x55: _MenuMsgID = value; break;
    case 0x56: _MenuMsgID2 = value; break;
    case 0x58: _Tribe = (u16)value; break;
    case 0x59: _Npc = (u16)value; break;
    case 0x5D: _SndID = (u16)value; break;
    case 0x5F: _MenuDigit = value; break;
    case 0x60: _MenuDigit2 = value; break;
    case 0x63: _Money = value; break;
    case 0x64: _Time = value; break;
    case 0x69: _MenuMoney = value; break;
    case 0xD: _EV_STR_BUF0 = value; break;
    case 0xE: _EV_STR_BUF1 = value; break;
    case 0x41: _EV_STR_BUF2 = value; break;
    case 0xF: _ATTACK_MONS = value; break;
    case 0x10: _DEFENCE_MONS = value; break;
    case 0x11: _CLIENT_MONS = value; break;
    case 0x12: _TSUIKA_MONS = value; break;
    case 0x13: _MY_NAME = value; break;
    case 0x14: _MY_MONS = value; break;
    case 0x15: _MY_MONS2 = value; break;
    case 0x16: _ENEMY_MONS = value; break;
    case 0x17: _ENEMY_MONS2 = value; break;
    case 0x18: _ENEMY_TMONS = value; break;
    case 0x19: _ENEMY_TMONS2 = value; break;
    case 0x1A: _SPEABI_NAMEA = value; break;
    case 0x1B: _SPEABI_NAMED = value; break;
    case 0x1C: _SPEABI_NAMEC = value; break;
    case 0x1D: _SPEABI_NAMET = value; break;
    case 0x1E: _CLIENTNOWORK = value; break;
    case 0x1F: _SIDE_ATTACK_NAMEHA = value; break;
    case 0x20: _SIDE_ATTACK_NAMEWO = value; break;
    case 0x21: _SIDE_ATTACK_NAMENO = value; break;
    case 0x22: _TRAINER_TYPE = value; break;
    case 0x23: _TRAINER_NAME = value; break;
    case 0x24: _TRAINER_LOSE = value; break;
    case 0x25: _TRAINER_ENENAME = value; break;
    case 0x26: _TRAINER_ENENAME2 = value; break;
    case 0x27: _TRAINER_CLIENTNO = value; break;
    case 0x28: _WAZA_NAME = value; break;
    case 0x29: _ITEM_NAME = value; break;
    case 0x2A: _PASO_NAME = value; break;
    case 0x42: _SIDE_DEFENCE_NAMEHA = value; break;
    case 0x43: _SIDE_DEFENCE_NAMEWO = value; break;
    case 0x44: _SIDE_DEFENCE_NAMENO = value; break;
    }
}

}

static u16* _msgctrlMakeDigit(u16* buf, s32 len, u32 val, s32 mode)
{
    u32* pv = &val;
    u8 neg = 0;
    u32 base = 10;
    s32 count = 0;
    s32 minDigits = 1;
    u16* digits;
    len--;
    buf[len] = 0;
    switch (mode) {
    case 0:
    case 5:
    case 6:
        if ((s32)*pv < 0) {
            *pv = -(s32)*pv;
            neg = 1;
        }
        break;
    case 2:
    case 8:
        minDigits = 10;
        break;
    case 3:
    case 9:
        base = 16;
        minDigits = 8;
        break;
    case 1:
    case 4:
    case 7:
    case 10:
        break;
    }
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if (pokecoloGetCountryCode() == 0) {
            digits = full_digit_code;
        } else {
            digits = half_digit_code;
        }
        break;
    case 5:
        digits = full_digit_code;
        break;
    default:
        digits = half_digit_code;
        break;
    }
    while (val != 0) {
        if ((mode == 4 || mode == 10) && count != 0 && count % 3 == 0) {
            switch (pokecoloGetLanguage()) {
            case 3:
            case 6:
                buf[--len] = 0x2E;
                break;
            case 4:
            case 5:
                break;
            case 2:
            default:
                buf[--len] = 0x2C;
                break;
            }
        }
        u32 v = val;
        len--;
        count++;
        val = v / base;
        buf[len] = digits[v - val * base];
    }
    for (; count < minDigits; count++) {
        buf[--len] = digits[0];
    }
    if (neg) {
        len--;
        buf[len] = 0x2D;
    }
    return buf + len;
}

extern "C" {

u32 msgctrlCR(MsgCtrl* o)
{
    o->f0c = o->f04;
    o->f10 += o->f68 * (f32)(o->unk23 + o->lineSpace);
    return 0;
}

u32 msgctrlKeyEnd(MsgCtrl* o)
{
    if (o->flags & 2) {
        o->pending = 1;
    }
    if (menuIsCheck(10)) {
        o->pending = 0;
    }
    if (o->pending) {
        o->pending = 0;
    } else {
        o->stream -= 3;
    }
    return 1;
}

u32 msgctrlCheckEnd(MsgCtrl* o)
{
    if (o->flags & 2) {
        o->pending = 1;
    }
    if (menuIsCheck(10)) {
        o->pending = 0;
    }
    if (o->pending) {
        o->pending = 0;
    } else {
        o->stream -= 3;
        o->waitFlag2 = 1;
    }
    return 1;
}

u32 msgctrlCheckWait(MsgCtrl* o)
{
    if (o->flags & 2) {
        o->pending = 1;
    }
    if (menuIsCheck(10)) {
        o->pending = 0;
    }
    if (o->activeFlag == 0) {
        if (o->pending) {
            o->pending = 0;
            o->saved = o->stream;
            if (*o->stream != 0) {
                peopleSetTalkKeyWaitCallback();
            }
            if (!(o->flags & 2)) {
                GSsndPlayNow(0x11);
            }
        } else {
            o->stream -= 3;
            o->waitFlag2 = 1;
        }
    } else {
        o->f0c = o->f04;
        o->f10 = o->f08;
    }
    return 1;
}

u32 msgctrlKeyWait(MsgCtrl* o)
{
    if (o->flags & 2) {
        o->pending = 1;
    }
    if (menuIsCheck(10)) {
        o->pending = 0;
    }
    if (o->activeFlag == 0) {
        if (o->pending) {
            o->pending = 0;
            o->saved = o->stream;
            if (*o->stream != 0) {
                peopleSetTalkKeyWaitCallback();
            }
            if (!(o->flags & 2)) {
                GSsndPlayNow(0x11);
            }
        } else {
            o->stream -= 3;
            o->waitFlag = 1;
        }
    } else {
        o->f0c = o->f04;
        o->f10 = o->f08;
    }
    return 1;
}

u32 msgctrlRubyStart(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        GSmsgInitRuby(o);
    }
    o->ruby = 1;
    return 0;
}

u32 msgctrlRubyTop(MsgCtrl* o)
{
    o->ruby = 2;
    return 0;
}

u32 msgctrlRubyEnd(MsgCtrl* o)
{
    o->ruby = 0;
    return 0;
}

u32 msgctrlFont(MsgCtrl* o)
{
    if (o->activeFlag == 0) {
        o->font = *o->stream;
        GSmsgSetFontInfo(o);
    } else {
        o->font = *o->stream;
        GSmsgSetFontInfo(o);
    }
    o->stream++;
    return 0;
}

u32 msgctrlColor(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        u32* p = (u32*)o->stream;
        u8 low = o->color;
        o->color = *p;
        o->color &= ~0xFF;
        o->color |= low;
        GSmsgSetColor(o);
    }
    o->stream += 4;
    return 0;
}

u32 msgctrlPalette(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        u32 c = o->color;
        u8 idx = *o->stream;
        if (idx >= *msg_palette_number) {
            idx = 0;
        }
        u32 off = idx * 4;
        u32 r = msg_palette[off];
        u32 g = msg_palette[off + 1];
        u32 b = msg_palette[off + 2];
        u32 al = msg_palette[off + 3];
        o->color = ((c >> 24) * r / 255 << 24)
                 | ((c >> 16 & 0xFF) * g / 255 << 16)
                 | ((c >> 8 & 0xFF) * b / 255 << 8)
                 | ((c & 0xFF) * al / 255);
        GSmsgSetColor(o);
        o->color = c;
    }
    o->stream++;
    return 0;
}

u32 msgctrlWait(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        goto adv;
    }
    if (o->wait == 0) {
        o->wait = *o->stream + 1;
    }
    if (--o->wait <= 0) {
        o->wait = 0;
        goto adv;
    }
    o->stream -= 3;
    return 1;
adv:
    o->stream++;
    return 0;
}

void* msgctrlHero()
{
    return heroBiosGetNamePtr(savedataGetStatus(0, 2));
}

void* msgctrlHizuki()
{
    return heroBiosGetHizukiNamePtr(savedataGetStatus(0, 2));
}

void* msgctrlItem()
{
    void* r = itemDataBiosGetName(itemDataBiosGetPtr(_Item));
    if (r == 0) {
        return (void*)0x3AD2;
    }
    return r;
}

void* msgctrlItem2()
{
    void* r = itemDataBiosGetName(itemDataBiosGetPtr(_Item2));
    if (r == 0) {
        return (void*)0x3AD2;
    }
    return r;
}

}

extern "C" {


u16* msgctrlDigit()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Digit, 0);
}

u16* msgctrlDigit2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Digit2, 0);
}

u32 msgctrlMsgID()
{
    return _MsgID;
}

u32 msgctrlPokemon()
{
    return _Pokemon;
}

u32 msgctrlPokemon2()
{
    return _Pokemon2;
}

u16* msgctrlMenuDigit()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 0);
}

u16* msgctrlMenuDigit2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 0);
}

u32 msgctrlMenuPokemon()
{
    return _MenuPokemon;
}

u32 msgctrlMenuMsg()
{
    return _MenuMsg;
}

u32 msgctrlMenuMsg2()
{
    return _MenuMsg2;
}

void* msgctrlWaza()
{
    return wazaDataBiosGetName(wazaDataBiosGetPtr(_Waza));
}

u16* msgctrlMenuDigitH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 6);
}

u16* msgctrlMenuDigitH2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 6);
}

u16* msgctrlMenuUDigitH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 7);
}

u16* msgctrlMenuUDigitH2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 7);
}

u16* msgctrlMenuHexH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 9);
}

u16* msgctrlMenuHexH2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 9);
}

u16* msgctrlMenuZDigitH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 8);
}

u16* msgctrlMenuZDigitH2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 8);
}

u16* msgctrlMoneyH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Money, 10);
}

u16* msgctrlTimeH()
{
    static u16 buff[16];
    static u16 buff2[16];
    static u16* top;
    u32 minutes;
    u32 hours = _Time / 3600;
    s32 n = 0;
    minutes = (_Time - hours * 3600) / 60;
    if (hours >= 100) {
        top = _msgctrlMakeDigit(buff2, 0x10, hours / 100, 6);
        buff[n++] = *top;
    }
    if (hours >= 10) {
        hours -= hours / 100 * 100;
        top = _msgctrlMakeDigit(buff2, 0x10, hours / 10, 6);
        buff[n++] = *top;
    }
    top = _msgctrlMakeDigit(buff2, 0x10, hours - hours / 10 * 10, 6);
    buff[n++] = *top;
    buff[n++] = 0x3A;
    top = _msgctrlMakeDigit(buff2, 0x10, minutes / 10, 6);
    buff[n++] = *top;
    top = _msgctrlMakeDigit(buff2, 0x10, minutes % 10, 6);
    buff[n++] = *top;
    buff[n] = 0;
    return buff;
}

u16* msgctrlMenuMoneyH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuMoney, 10);
}

u16* msgctrlDigitH()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Digit, 6);
}

u16* msgctrlDigitH2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Digit2, 6);
}

u32 msgctrlEvStrBuf0()
{
    return _EV_STR_BUF0;
}

u32 msgctrlEvStrBuf1()
{
    return _EV_STR_BUF1;
}

u32 msgctrlEvStrBuf2()
{
    return _EV_STR_BUF2;
}

void* msgctrlAttackMons()
{
    void* trainer;
    FightOutPokemon* mon = (FightOutPokemon*)_ATTACK_MONS;
    trainer = getTrainer(mon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(mon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(mon);
}

void* msgctrlDeffenceMons()
{
    void* trainer;
    FightOutPokemon* mon = (FightOutPokemon*)_DEFENCE_MONS;
    trainer = getTrainer(mon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(mon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(mon);
}

void* msgctrlClientMos()
{
    void* trainer;
    FightOutPokemon* mon = (FightOutPokemon*)_CLIENT_MONS;
    trainer = getTrainer(mon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(mon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(mon);
}

void* msgctrlTsuikaMons()
{
    void* trainer;
    FightOutPokemon* mon = (FightOutPokemon*)_TSUIKA_MONS;
    trainer = getTrainer(mon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(mon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(mon);
}

u32 msgctrlMyName()
{
    return _MY_NAME;
}

u32 msgctrlMyMons()
{
    return _MY_MONS;
}

u32 msgctrlMyMons2()
{
    return _MY_MONS2;
}

u32 msgctrlEnemyMons()
{
    return _ENEMY_MONS;
}

u32 msgctrlEnemyMons2()
{
    return _ENEMY_MONS2;
}

u32 msgctrlEnemyTmons()
{
    return _ENEMY_TMONS;
}

u32 msgctrlEnemyTmons2()
{
    return _ENEMY_TMONS2;
}

u32 msgctrlSpeabiNamea()
{
    return _SPEABI_NAMEA;
}

u32 msgctrlSpeabiNamed()
{
    return _SPEABI_NAMED;
}

u32 msgctrlSpeabiNamec()
{
    return _SPEABI_NAMEC;
}

u32 msgctrlSpeabiNamet()
{
    return _SPEABI_NAMET;
}

void* msgctrlClientnowork()
{
    void* trainer;
    FightOutPokemon* mon = (FightOutPokemon*)_CLIENTNOWORK;
    trainer = getTrainer(mon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(mon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(mon);
}

}

static void* _msgctrlSideName(FightOutPokemon* mon, u8 kind)
{
    u16 status = fightFloorGetStatus(0, 0, 0x14, 0);
    void* side = fightTargetGetPtrAsNowFightType(2, mon);
    void* self = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, mon);
    void* t;
    u16 count = 0;
    u16 i;
    for (i = 0; i < 2; i++) {
        t = fightSideGetValidFightTrainerPtr(side, i);
        if (t != 0 && fightTrainerCheckDoFight(t) != 0) {
            if (count == 0) {
                msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(t));
            } else if (count == 1) {
                msgctrlSetValue(0x57, (u32)fightTrainerGetNamePtr(t));
            }
            count++;
        }
    }
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && self != 0) {
        if (count <= 1) {
            msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(self));
            if (kind == 0) {
                return GSmsgGetGSchar(0x4FE5);
            } else if (kind == 1) {
                return GSmsgGetGSchar(0x4FE8);
            }
            return GSmsgGetGSchar(0x4FEA);
        }
        if (kind == 0) {
            return GSmsgGetGSchar(0x4FE6);
        } else if (kind == 1) {
            return GSmsgGetGSchar(0x4FE9);
        }
        return GSmsgGetGSchar(0x4FEB);
    }
    if (fightTargetIsHostSide(mon, status) == 1) {
        if (kind == 0) {
            return GSmsgGetGSchar(0x4F6A);
        } else if (kind == 1) {
            return GSmsgGetGSchar(0x4F6C);
        }
        return GSmsgGetGSchar(0x4F68);
    }
    if (kind == 0) {
        return GSmsgGetGSchar(0x4F69);
    } else if (kind == 1) {
        return GSmsgGetGSchar(0x4F6B);
    }
    return GSmsgGetGSchar(0x4F67);
}

extern "C" {

void* msgctrlSideAttackNameha()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_ATTACK_NAMEHA, 0);
}

void* msgctrlSideAttackNamewo()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_ATTACK_NAMEWO, 1);
}

void* msgctrlSideAttackNameno()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_ATTACK_NAMENO, 2);
}

void* msgctrlSideDefenceNameha()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_DEFENCE_NAMEHA, 0);
}

void* msgctrlSideDefenceNamewo()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_DEFENCE_NAMEWO, 1);
}

void* msgctrlSideDefenceNameno()
{
    return _msgctrlSideName((FightOutPokemon*)_SIDE_DEFENCE_NAMENO, 2);
}

u32 msgctrlTrainerType()
{
    return _TRAINER_TYPE;
}

u32 msgctrlTrainerName()
{
    return _TRAINER_NAME;
}

u32 msgctrlTrainerLose()
{
    return _TRAINER_LOSE;
}

u32 msgctrlTrainerEnename()
{
    return _TRAINER_ENENAME;
}

u32 msgctrlTrainerEnename2()
{
    return _TRAINER_ENENAME2;
}

u32 msgctrlTrainerClientno()
{
    return _TRAINER_CLIENTNO;
}

u32 msgctrlWazaName()
{
    return _WAZA_NAME;
}

u32 msgctrlItemName()
{
    return _ITEM_NAME;
}

u32 msgctrlPasoName()
{
    return _PASO_NAME;
}

u32 msgctrlSetPeopleTalkFlag()
{
    peopleSetTalkFlagCallback();
    return 0;
}

u32 msgctrlSeOff()
{
    return 0;
}

u32 msgctrlSeOn()
{
    return 0;
}

u16* msgctrlMenuUDigit()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 1);
}

u16* msgctrlMenuUDigit2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 1);
}

u16* msgctrlMenuHex()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 3);
}

u16* msgctrlMenuHex2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 3);
}

u16* msgctrlMenuZDigit()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 2);
}

u16* msgctrlMenuZDigit2()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit2, 2);
}

u16* msgctrlMoney()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _Money, 4);
}

u16* msgctrlTime()
{
    static u16 buff[16];
    static u16 buff2[16];
    static u16* top;
    u32 minutes;
    u32 hours = _Time / 3600;
    s32 n = 0;
    minutes = (_Time - hours * 3600) / 60;
    if (hours >= 100) {
        top = _msgctrlMakeDigit(buff2, 0x10, hours / 100, 0);
        buff[n++] = *top;
    }
    if (hours >= 10) {
        hours -= hours / 100 * 100;
        top = _msgctrlMakeDigit(buff2, 0x10, hours / 10, 0);
        buff[n++] = *top;
    }
    top = _msgctrlMakeDigit(buff2, 0x10, hours - hours / 10 * 10, 0);
    buff[n++] = *top;
    buff[n++] = 0x3A;
    top = _msgctrlMakeDigit(buff2, 0x10, minutes / 10, 0);
    buff[n++] = *top;
    top = _msgctrlMakeDigit(buff2, 0x10, minutes % 10, 0);
    buff[n++] = *top;
    buff[n] = 0;
    return buff;
}

u32 msgctrlString()
{
    return _String;
}

void* msgctrlPokemonID()
{
    return pokemonDataBiosGetName(pokemonDataBiosGetPtr(_PokemonID));
}

u16* msgctrlMenuFullDigit()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuDigit, 5);
}

u16* msgctrlMenuMoney()
{
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 0x10, _MenuMoney, 4);
}

u32 msgctrlShadow(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        o->shadow = *o->stream;
    }
    o->stream++;
    return 0;
}

u32 msgctrlAlign(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        o->align = *o->stream;
        GSmsgAdjustAlign(o);
    }
    o->stream++;
    return 0;
}

u32 msgctrlTalkSE(MsgCtrl* o)
{
    if (o->activeFlag == 0) {
        o->talkSE = *o->stream;
    }
    o->stream++;
    return 0;
}

u32 msgctrlMenuMsgID()
{
    return _MenuMsgID;
}

u32 msgctrlMenuMsgID2()
{
    return _MenuMsgID2;
}

u32 msgctrlString2()
{
    return _String2;
}

void* msgctrlTribe()
{
    return fightTrainerKindDataBiosGetPrefixName(fightTrainerKindDataBiosGetPtr(_Tribe));
}

u16 msgctrlNpc()
{
    return _Npc;
}

u32 msgctrlIndentOff(MsgCtrl* o)
{
    o->indentOff = 1;
    return 0;
}

u32 msgctrlLineSpace(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        o->lineSpace = *o->stream;
    }
    o->stream++;
    return 0;
}

u32 msgctrlBaseLineBias(MsgCtrl* o)
{
    if (o->activeFlag != 0) {
        o->baseLineBias = *o->stream;
    }
    o->stream++;
    return 0;
}

u32 msgctrlSndPlay(MsgCtrl* o)
{
    if (o->activeFlag == 0) {
        u16 h = _SndID;
        if (h != 0) {
            soundOpenPlay(h, 0, 0xFF);
        }
    }
    return 0;
}

u32 msgctrlSndWait(MsgCtrl* o)
{
    if (o->activeFlag == 0) {
        u16 h = _SndID;
        if (h == 0) {
            return 0;
        }
        if (GSsndGetStatus(h) == 2) {
            o->stream -= 3;
        }
    }
    return 1;
}

}
