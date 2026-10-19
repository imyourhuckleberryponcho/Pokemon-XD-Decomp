// Mew move teacher quiz: asks Mew-themed questions, scores personality points and picks a move template.
#include <dolphin/types.h>

struct MEWPOINTS {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s32 state;
};

struct MWAZA {
    u16 waza;
    u16 flags;
};

struct TemplateData {
    u16 valid;
    u16 kind;
    u16 waza[4];
};

struct WazaTmplTblEntry {
    TemplateData* ptr;
};

#define RAND16() ((u32)(u16)HSD_Rand())

extern MWAZA mWazaTbl[];
extern WazaTmplTblEntry wazaTmplTbl[];

extern "C" {
u32 HSD_Rand();
s32 GSfloorGetCurrent(void);
s32 GSfsysReadWait(u32 id);
void GSresFreeGroup(u32 grp);
void msgctrlSetValue(s32 id, u32 value);
s32 winMsgOpenFieldWithSE(s32 msg, bool a, bool b, u8 se);
void winMsgClose(bool flag);
s32 menuSubOpenSelect3(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
s32 menuOpen(s32 menuID, s32);
void menuClose(s32 menuID);
void menuCloseSync(s32 menuID, s32);
void heroMoveInitEvent();
void heroMoveTermEvent();
void GSthreadSwitch(void);
s32 menuMewWazaGetMenuDataID(void);
}

static s32 mewans1[3] = {0xC6FC, 0xC6FD, 0xC6FE};
static s32 mewans2[4] = {0xC700, 0xC701, 0xC702, 0xC703};
static s32 mewans3[4] = {0xC705, 0xC706, 0xC707, 0xC708};
static s32 mewques4[3] = {0xC709, 0xC70C, 0xC70F};
static s32 mewques5[5] = {0xC712, 0xC715, 0xC718, 0xC71B, 0xC71E};
static s32 mewans4[6] = {0xC70B, 0xC70A, 0xC70D, 0xC70E, 0xC710, 0xC711};
static s32 mewans5[10] = {0xC713, 0xC714, 0xC716, 0xC717, 0xC71A, 0xC719, 0xC71C, 0xC71D, 0xC71F, 0xC720};

struct WrkWaza {
    u16 w[4];
};

struct WrkTmplt {
    u16 valid;
    u16 kind;
    WrkWaza waza;
};

static WrkTmplt _wrktmplt;
MEWPOINTS mewPoints;

static inline void _openRandomMsg() {
    s32 local[5] = {0xC727, 0xC728, 0xC729, 0xC72A, 0xC72C};
    winMsgOpenFieldWithSE(local[RAND16() % 5], 1, 0, 1);
}

static inline void _scale(MEWPOINTS* mp, u8 sel, u32 rem, s32 base) {
    if (sel == 0) {
        mp->a = ((s32)(rem + base) * mp->a) >> 8;
    } else {
        s16 c = mp->c;
        s32 ac = c < 0 ? -c : c;
        s32 ab = mp->b < 0 ? -mp->b : mp->b;
        if (ab > ac) {
            s16 ad = mp->d;
            if (ad < 0) {
                ad = -ad;
            }
            s32 ab2 = mp->b < 0 ? -mp->b : mp->b;
            if (ab2 > ad) {
                mp->b = ((s32)(rem + base) * mp->b) >> 8;
                return;
            }
        }
        s16 b = mp->b;
        if (b < 0) {
            b = -b;
        }
        s32 ac2 = c < 0 ? -c : c;
        if (ac2 > b) {
            s16 ad = mp->d;
            if (ad < 0) {
                ad = -ad;
            }
            s32 ac3 = c < 0 ? -c : c;
            if (ac3 > ad) {
                mp->c = ((s32)(rem + base) * c) >> 8;
                return;
            }
        }
        mp->d = ((s32)(rem + base) * mp->d) >> 8;
    }
}

static s32 _mewSequence(MEWPOINTS* mp);
static void _question_3(MEWPOINTS* mp);
static void _question_4(MEWPOINTS* mp);
static void _question_5(MEWPOINTS* mp);
static s32 _tmplSelect(MEWPOINTS* mp);
static TemplateData* _getWazaFromTmpl(long idx, MEWPOINTS* mp);
static s32 _fillTmplate(u16* tmpl, MEWPOINTS* mp);
static s32 _searchwaza(MWAZA* tbl, long mode, u16* used, long usedCount, long nth);

static s32 _mewSequence(MEWPOINTS* mp) {
    s32 q1[2];
    s32 q2[2];
    s32 sel;
    s32 res;
    u32 y;
    u32 x;

    heroMoveInitEvent();
    GSthreadSwitch();
    mp->a = 0;
    mp->b = 0;
    mp->c = 0;
    mp->d = 0;
    mp->state = 0;
    winMsgOpenFieldWithSE(0xC6FB, 1, 0, 1);
    x = RAND16() % 3;
    y = x;
    while (y == x) {
        y = RAND16() % 3;
    }
    q1[0] = mewans1[x];
    q1[1] = mewans1[y];
    do {
        res = menuSubOpenSelect3(0, q1, 2, 0x34, 0xd1, 0, 2, 1, 0);
    } while (res < 0);
    sel = y;
    if (res == 0) {
        sel = x;
    }
    winMsgClose(1);
    switch (sel) {
    case 0:
        mp->a += 2;
        mp->c = RAND16() % 3 + 1;
        break;
    case 1:
        mp->a += 3;
        mp->c = 1;
        break;
    case 2:
        mp->a += 4;
        mp->c = -((s32)(RAND16() % 3) - 1);
        break;
    }
    _openRandomMsg();
    winMsgOpenFieldWithSE(0xC6FF, 1, 0, 1);
    x = HSD_Rand() & 3;
    y = x;
    while (y == x) {
        y = HSD_Rand() & 3;
    }
    q2[0] = mewans2[x];
    q2[1] = mewans2[y];
    do {
        res = menuSubOpenSelect3(0, q2, 2, 0x34, 0xd1, 0, 2, 1, 0);
    } while (res < 0);
    sel = y;
    if (res == 0) {
        sel = x;
    }
    winMsgClose(1);
    switch (sel) {
    case 0:
        mp->b += 2;
        break;
    case 1:
        mp->b -= 2;
        break;
    case 2:
        mp->d += 3;
        break;
    case 3:
        mp->b = RAND16() % 7 - 3;
        break;
    }
    _question_3(mp);
    _question_4(mp);
    _question_5(mp);
    {
        s16 d = mp->d;
        if (d > 0) {
            mp->a = mp->a + (RAND16() % (d * 2 + 1) - mp->d);
            if (mp->a < 0) {
                mp->a = 0;
            }
        }
    }
    {
        TemplateData* t = _getWazaFromTmpl(_tmplSelect(mp), mp);
        s32 mid;
        s8 yn;
        if (t == 0) {
            return -1;
        }
        _wrktmplt.valid = t->valid;
        _wrktmplt.kind = t->kind;
        *(WrkWaza*)&_wrktmplt.waza = *(WrkWaza*)&t->waza;
        if (_fillTmplate(_wrktmplt.waza.w, mp) != 0) {
            return -1;
        }
        winMsgOpenFieldWithSE(0xC721, 1, 0, 1);
        mid = menuMewWazaGetMenuDataID();
        winMsgClose(1);
        menuOpen((u16)mid, 0);
        yn = menuSubOpenYesNo(1, 0x196, 0xc0, 0);
        menuClose((u16)mid);
        menuCloseSync((u16)mid, 1);
        heroMoveTermEvent();
        return yn;
    }
}

static void _question_3(MEWPOINTS* mp) {
    s32 q[2];
    s32 res;
    u32 x;
    u32 y;
    u32 sel;

    _openRandomMsg();
    winMsgOpenFieldWithSE(0xC704, 1, 0, 1);
    x = HSD_Rand() & 3;
    y = x;
    while (y == x) {
        y = HSD_Rand() & 3;
    }
    q[0] = mewans3[x];
    q[1] = mewans3[y];
    do {
        res = menuSubOpenSelect3(0, q, 2, 0x34, 0xd1, 0, 2, 1, 0);
    } while (res < 0);
    sel = y;
    if (res == 0) {
        sel = x;
    }
    winMsgClose(1);
    switch (sel) {
    case 0:
        mp->b += 2;
        break;
    case 1:
        mp->b = (s16)(RAND16() % 3) + mp->b + 1;
        break;
    case 2:
        mp->c = (s16)(RAND16() % 3) + mp->c + 1;
        break;
    case 3:
        if (RAND16() % 10 < 5) {
            mp->b -= 2;
        } else {
            mp->c = (s16)(RAND16() % 5) + mp->c - 1;
        }
        break;
    }
}

static void _question_4(MEWPOINTS* mp) {
    s32 q[2];
    s32 res;
    u32 r;

    _openRandomMsg();
    r = RAND16() % 3;
    winMsgOpenFieldWithSE(mewques4[r], 1, 0, 1);
    q[0] = mewans4[r * 2];
    q[1] = mewans4[r * 2 + 1];
    do {
        res = menuSubOpenSelect3(0, q, 2, 0x34, 0xd1, 0, 2, 1, 0);
    } while (res < 0);
    winMsgClose(1);
    switch (r) {
    case 0:
        if ((u8)res == 0) {
            mp->d -= 3;
            mp->a <<= 1;
        } else {
            mp->d += 3;
            mp->a = mp->a * ((s16)(RAND16() % 3) + 1);
        }
        break;
    case 1:
        if ((u8)res == 0) {
            mp->d = mp->d - ((s16)(RAND16() % 3) + 2);
            mp->a <<= 1;
        } else {
            mp->d = (RAND16() % 3) + mp->d + 2;
            mp->a = mp->a * ((s16)(RAND16() % 3) + 1);
        }
        break;
    case 2:
        if ((u8)res == 0) {
            mp->d = mp->d - ((HSD_Rand() & 3) + 1);
            mp->a <<= 1;
        } else {
            mp->d = (HSD_Rand() & 3) + mp->d + 1;
            mp->a = mp->a * ((s16)(RAND16() % 3) + 1);
        }
        break;
    }
}

static void _question_5(MEWPOINTS* mp) {
    s32 q[2];
    s32 res;
    u32 r;

    r = RAND16() % 5;
    winMsgOpenFieldWithSE(mewques5[r], 1, 0, 1);
    q[0] = mewans5[r * 2];
    q[1] = mewans5[r * 2 + 1];
    do {
        res = menuSubOpenSelect3(0, q, 2, 0x34, 0xd1, 0, 2, 1, 0);
    } while (res < 0);
    winMsgClose(1);
    switch (r) {
    case 0:
        _scale(mp, res, RAND16() % 487, 0x99);
        if ((u8)res == 0) {
            mp->state = 1;
        } else {
            mp->state = 2;
        }
        break;
    case 1:
        _scale(mp, res, RAND16() % 384, 0xb3);
        break;
    case 2:
        _scale(mp, res, RAND16() % 308, 0xcc);
        break;
    case 3:
        _scale(mp, res, RAND16() % 204, 0x100);
        break;
    case 4:
        _scale(mp, res, RAND16() % 51, 0x133);
        break;
    }
}

static s32 _tmplSelect(MEWPOINTS* mp) {
    u8 kinds[3];
    s32 vals[3];
    s32 i;
    s32 j;

    vals[0] = mp->b;
    vals[1] = mp->c;
    vals[2] = mp->d;
    kinds[0] = 'A';
    kinds[1] = 'S';
    kinds[2] = 'B';
    for (i = 0; i < 2; i++) {
        for (j = i + 1; j < 3; j++) {
            if (vals[i] < vals[j]) {
                s32 tv = vals[i];
                u8 tk = kinds[i];
                vals[i] = vals[j];
                kinds[i] = kinds[j];
                vals[j] = tv;
                kinds[j] = tk;
            }
        }
    }
    if (kinds[0] == 'S' && vals[0] != vals[1]) {
        return 0;
    }
    if (kinds[0] == 'B' && vals[0] != vals[1]) {
        return 1;
    }
    if (kinds[0] == 'A' && vals[0] != vals[1]) {
        if (kinds[2] == 'B' && vals[1] > vals[2] && vals[2] <= 0) {
            return 2;
        }
        return 3;
    }
    if (kinds[2] == 'S' && vals[0] == vals[1] && vals[0] > vals[2]) {
        return 3;
    }
    if (kinds[2] == 'B' && vals[0] == vals[1] && vals[0] > vals[2]) {
        return 2;
    }
    if (kinds[2] == 'A' && vals[0] == vals[1] && vals[0] > vals[2]) {
        return 4;
    }
    {
        s16 t = mp->b;
        if (t < 0) {
            t = -t;
        }
        mp->a = mp->a + t;
        t = mp->c;
        if (t < 0) {
            t = -t;
        }
        mp->a = mp->a + t;
        t = mp->d;
        if (t < 0) {
            t = -t;
        }
        mp->a = mp->a + t;
    }
    return 5;
}

static TemplateData* _getWazaFromTmpl(long idx, MEWPOINTS* mp) {
    TemplateData* tbl = wazaTmplTbl[idx].ptr;
    u16 kind;
    s32 chance;
    TemplateData* e;
    s32 count;
    s32 pick;
    s32 j;

    switch (idx) {
    case 0: {
        s16 b = mp->b;
        s16 d = mp->d;
        if (b > d && b >= 0) {
            kind = 3;
        } else if (b >= 0) {
            kind = 2;
        } else {
            kind = 1;
        }
        chance = 100;
        if (mp->state == 1) {
            if (RAND16() % 100 < 30) {
                return &tbl[10 + RAND16() % 3];
            }
        }
        if (mp->state == 2) {
            if (RAND16() % 100 < 30) {
                return &tbl[7 + RAND16() % 3];
            }
        }
        break;
    }
    case 1:
        kind = 1;
        chance = 60;
        break;
    case 2:
    case 5:
        kind = 1;
        chance = 100;
        break;
    case 3:
        kind = 1;
        chance = 70;
        break;
    case 4:
        kind = 1;
        chance = 70;
        break;
    }
    if (chance == 100 || chance > RAND16() % 100) {
        count = 0;
        for (e = tbl; e->valid != 0; e++) {
            if (e->kind == kind) {
                count++;
            }
        }
        if (count == 0) {
            return 0;
        }
        pick = RAND16() % count;
        j = 0;
        for (e = tbl; e->valid != 0; e++) {
            if (e->kind == kind) {
                if (j == pick) {
                    return e;
                }
                j++;
            }
        }
        return 0;
    } else {
        count = 0;
        for (e = tbl; e->valid != 0; e++) {
            if (e->kind != kind) {
                count++;
            }
        }
        if (count == 0) {
            return 0;
        }
        pick = RAND16() % count;
        j = 0;
        for (e = tbl; e->valid != 0; e++) {
            if (e->kind != kind) {
                if (j == pick) {
                    return e;
                }
                j++;
            }
        }
        return 0;
    }
}

static s32 _fillTmplate(u16* tmpl, MEWPOINTS* mp) {
    s32 start;
    s32 skip;
    MWAZA* base;
    MWAZA* cur;
    s32 i;
    s32 tries;
    s32 n;
    s32 v;

    if (mp->a > 12) {
        skip = mp->a - 12;
        start = 48;
    } else {
        start = mp->a * 4;
        skip = 0;
    }
    start = 48 - start;
    skip *= 4;
    base = &mWazaTbl[start];
    cur = base;
    for (i = 0; i < 4; i++) {
        if (tmpl[i] & 0x8000) {
            tries = 0;
            for (;;) {
                n = _searchwaza(cur, tmpl[i], tmpl, i, 0);
                if (n != 0) {
                    v = RAND16() % (n / 2 + (n / 8 + 1));
                    if (v >= n) {
                        v = 0;
                    }
                    if (skip != 0) {
                        if (skip > v) {
                            skip -= v;
                            v = 0;
                        } else {
                            v -= skip;
                            skip = 0;
                        }
                    }
                    tmpl[i] = _searchwaza(cur, tmpl[i], tmpl, i, v + 1);
                    cur += v + 1;
                    break;
                }
                if (tries < 2) {
                    cur = base;
                    tries++;
                    continue;
                }
                tmpl[i] = 0x800F;
                if (base != mWazaTbl) {
                    base--;
                }
                cur = base;
            }
        }
    }
    return 0;
}

static s32 _searchwaza(MWAZA* tbl, long mode, u16* used, long usedCount, long nth) {
    s32 count = 0;
    u16 ok = 0;
    for (;; tbl++) {
        u16 w = tbl->waza;
        s32 j;
        if (w == 0) {
            return count;
        }
        switch (mode) {
        case 0x8001:
            if (tbl->flags & 1) {
                ok = w;
            }
            break;
        case 0x8002:
            if (tbl->flags & 2) {
                ok = w;
            }
            break;
        case 0x8003:
            break;
        case 0x8004:
            if (tbl->flags & 4) {
                ok = w;
            }
            break;
        case 0x8005:
            break;
        case 0x8008:
            if (tbl->flags & 8) {
                ok = w;
            }
            break;
        case 0x800C:
            if (tbl->flags & 0xC) {
                ok = w;
            }
            break;
        case 0x800F:
            ok = w;
            break;
        case 0x8102:
            if (!(tbl->flags & 2)) {
                ok = w;
            }
            break;
        }
        if (ok != 0) {
            for (j = 0; j < usedCount; j++) {
                if (ok == used[j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok != 0) {
                count++;
                if (nth != 0 && count == nth) {
                    return ok;
                }
            }
        }
        ok = 0;
    }
}

extern "C" {
s32 mewWazaSequence() {
    u32 floor = GSfloorGetCurrent();
    s32 r;
    if (floor != 0x15) {
        GSfsysReadWait(0x9ef);
        msgctrlSetValue(0x59, 0x1772);
    }
    r = _mewSequence(&mewPoints);
    if (floor != 0x15) {
        GSresFreeGroup(0x9ef);
    }
    return r;
}

u16 mewWazaGet(long index) {
    return _wrktmplt.waza.w[index];
}
}
