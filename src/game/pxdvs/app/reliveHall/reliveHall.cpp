// STATUS: 27/36 exact with extra_cflags ["-inline", "noauto,deferred"] (25 without); LAYOUT/CONST/CALLS/DATA all OK with the flags.
// File is written bottom-to-top (deferred). Aisyou helper exists twice on purpose: exported reliveHallPokemonToAisyou plus a
// static inline copy used by the callers (target inlines it). VISITOR_OR_NULL is a macro (the target recomputes this+0x310).
// Not exact: debugPokemonSetup 89% ((mode != 1) hoisting), isReliveReadyDarkLugiaExist 88%, heroWalkReliveCallBack 93%
// (cur register), getReliveGiveStageQuantity 96%, getPassionWoBonus 97%, getState 98.7% (pair-sum register allocation:
// inlined aisyou x/y/st registers), getTempo 99.5%, checkWithBackupSet 99.8%, reliveHallPokemonToAisyou 99.6%.
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

enum FootStepCounter { FOOTSTEP_0 };

struct FlagEtcData {
    u8 pad[0x428];
    u32 reliveOpenFlag; // 0x428
};

struct ReliveHallData {
    u16 a0;
    u16 steps; // 0x02
};

extern "C" {
u32 GSflagGet(u32 f);
void* GSmemAllocClr(u32 size);
void GSmemFree(void* p);
void GSthreadSwitch();
bool darkPokemonBiosGetInformationFlag(u16 id);
bool darkPokemonBiosGetReliveFlag(u16 id);
u16 darkPokemonBiosGetSteps(u16 id);
void darkPokemonBiosSetSteps(u16 id, u32 steps);
s32 heroMoveAddStepCallback(void (*cb)(long, FootStepCounter, long), s32);
void heroMoveInitEvent();
void heroMoveSetColision(s32 on);
void heroMoveTermEvent();
int memcmp(const void*, const void*, u32);
void* memcpy(void*, const void*, u32);
void* memmove(void*, const void*, u32);
void* memset(void*, int, u32);
void menuScriptInfoRelive(Pokemon* p, u32 a, s32 b);
void pokemonAddDp(Pokemon* p, f32 dp);
void pokemonAllKaihuku(Pokemon* p);
bool pokemonCheckValid(Pokemon* p);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon* p);
u8 pokemonDataBiosGetZokuseiDataId(void* pdata, u16 idx);
void* savedataGetStatus(void* save, s32 kind);
u16 zokuseiGetWazaJoutai(u16 a, u16 b);
extern FlagEtcData* flag_etc;
extern ReliveHallData* relivehall_data;
extern u32* zokusei_data_number;
}
void menuPocketDebugMakeDarkPokemonByID(Pokemon& p, u16 id, f32 mult);
void menuPocketDebugMakePokemonByID(Pokemon& p, u16 id, bool dark, f32 mult);

struct PokemonRaw {
    u8 d[0xC4];
};

class CReliveHall;

class CReliveStage {
public:
    u8 dancer[4][0xC4];
    u8 visitor[0xC4];
    s8 hit; // 0x3D4
    u8 pad3D5[3];

    s32 getState();
    bool isLugiaReliveReady();
    bool isReliveReady();
    Pokemon* heroWalkReliveCallBack(long steps, bool pay);
    bool isPokemonZokuseiAllUnique(bool withVisitor);
    s32 getTempo();
    s32 getPassionWoBonus();
    bool isBonusGet();
    s32 getPassion();
    void pickupVisitor(Pokemon& out);
    void insertDancer(Pokemon& in, long slot);
    void pickupDancer(Pokemon& out, long slot);
    void exchangeVisitor(Pokemon& p);
    void exchangeDancer(Pokemon& p, long slot);
    s32 getDancerQuantity();
    Pokemon* getDancerPointer(long i);
    void putVisitor(Pokemon& p);
    Pokemon* getVisitorPointer();
    void init();
};

class CReliveHall {
public:
    CReliveStage stage[9];

    static bool isOpen();
    void debugPokemonSetup(long mode);
    void checkWithBackupSet();
    void allocMakeBackup();
    static CReliveHall* getPointer();
    bool isReliveReadyDarkLugiaExist();
    s32 getReliveReadyVisitorQuantity();
    bool isReliveReadyPokemonExist();
    Pokemon* heroWalkReliveCallBack(long steps);
    s32 getReliveGiveStageQuantity();
    void init();
    CReliveStage* getStage(long i);
};

namespace {
s32 _heroCallBackHandle;
s32 _tempoBase[5] = { 0, 5, 0xE, 0x1B, 0x30 };
s32 _tempoGood[5] = { 0, 6, 6, 6, 12 };
s32 _tempoNormal[5] = { 0, 2, 2, 2, 4 };
s32 _bonusStageBonusTbl[10] = { 0, 0, 1, 5, 0xA, 0xF, 0x19, 0x23, 0x32, 0x64 };
void _heroCallBackFunc(long, FootStepCounter, long);
}
static CReliveHall* _pRelivehallCopy;

static inline Pokemon* stageDancer(CReliveStage* s, int i) {
    return (Pokemon*)s->dancer[i];
}
static inline Pokemon* stageVisitor(CReliveStage* s) {
    return (Pokemon*)s->visitor;
}

static inline CReliveHall* hallPtr() {
    return (CReliveHall*)savedataGetStatus(savedataGetStatus(0, 0), 0x15);
}

// Pokemon pointer if it is a valid slot, else 0
static inline Pokemon* validOrNull(Pokemon* p) {
    return pokemonCheckValid(p) ? p : 0;
}

static inline s32 countDancers(CReliveStage* s) {
    s32 n = 0;
    for (; n < 4; n++) {
        if (!pokemonCheckValid((Pokemon*)s->dancer[n])) break;
    }
    return n;
}

namespace {
extern u16 jyoutai2levelTbl[4];
}

static inline s32 jyoutaiLevel(u16 st) {
    for (s32 k = 0; k < 4; k++) {
        if ((s32)st == (s32)jyoutai2levelTbl[k]) {
            s32 r = k - 1;
            return r & ~(r >> 31);
        }
    }
    return 0x7B;
}

// compatibility ("aisyou") of two Pokemon, by their types

static inline s32 pairAisyou(Pokemon* a, Pokemon* b) {
    Pokemon* ps[2];
    s32 z[2][2];
    ps[0] = a;
    ps[1] = b;
    if (a == 0 || b == 0) return -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            z[i][j] = pokemonDataBiosGetZokuseiDataId(ps[i]->getPokemonDataPtr(), (u16)j);
        }
    }
    s32 best = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            s32 x = z[0][i];
            s32 y = z[1][j];
            s32 v;
            if (x == 0 && y == 0) {
                v = 2;
            } else {
                v = jyoutaiLevel((u16)(zokuseiGetWazaJoutai((u16)x, (u16)y)));
            }
            if (best < v) best = v;
        }
    }
    return best;
}

// tempo points for one neighbouring pair
static inline s32 pairScore(s32 n, s32 rel) {
    s32 add;
    switch (rel) {
    case -1:
        add = 0;
        break;
    case 0:
        add = 0;
        break;
    case 1:
        add = _tempoNormal[n];
        break;
    case 2:
        add = _tempoGood[n];
        break;
    }
    return add;
}

static inline s32 pairSum(CReliveStage* s, s32 n) {
    s32 add;
    s32 i;
    s32 sum = 0;
    for (i = 0; i < n; i++) {
        Pokemon* a = validOrNull(stageDancer(s, i));
        Pokemon* b = validOrNull(stageDancer(s, (i + 1) % n));
        s32 rel = pairAisyou(a, b);
        switch (rel) {
        case -1:
            add = 0;
            break;
        case 0:
            add = 0;
            break;
        case 1:
            add = _tempoNormal[n];
            break;
        case 2:
            add = _tempoGood[n];
            break;
        }
        sum += add;
    }
    return sum;
}

#define VISITOR_OR_NULL(s) (pokemonCheckValid(stageVisitor(s)) ? stageVisitor(s) : 0)

static inline s32 findEmptySlot(CReliveStage* s) {
    for (s32 i = 0; i < 4; i++) {
        if (!pokemonCheckValid((Pokemon*)s->dancer[i])) return i;
    }
    return -1;
}

static inline void pokemonSetupAfterInsert(CReliveHall* hall, CReliveStage* stage, Pokemon* p) {
    pokemonAllKaihuku(p);
    CReliveHall* h = hallPtr();
    s32 idx = ((u8*)stage - (u8*)h) / 984;
    DarkPokemon* dp = p->getDarkPokemon();
    if (dp != 0) {
        dp->setPlace(place3, (u8)idx);
    }
}

void CReliveStage::init() {
    memset(this, 0, 0x3D8);
    pokemonInitAry((u32)stageDancer(this, 0), 4);
    pokemonInit((u32)stageVisitor(this));
}

Pokemon* CReliveStage::getVisitorPointer() {
    return VISITOR_OR_NULL(this);
}

void CReliveStage::putVisitor(Pokemon& p) {
    memcpy(visitor, &p, 0xC4);
    pokemonSetupAfterInsert(0, this, (Pokemon*)visitor);
    pokemonInit((u32)&p);
}

Pokemon* CReliveStage::getDancerPointer(long i) {
    Pokemon* p = stageDancer(this, i);
    if (pokemonCheckValid(p)) return p;
    return 0;
}

s32 CReliveStage::getDancerQuantity() {
    s32 n = 0;
    for (; n < 4; n++) {
        if (!pokemonCheckValid((Pokemon*)dancer[n])) break;
    }
    return n;
}

void CReliveStage::exchangeDancer(Pokemon& p, long slot) {
    Pokemon* dst = stageDancer(this, slot);
    PokemonRaw tmp = *(PokemonRaw*)dst;
    memcpy(dst, &p, 0xC4);
    memcpy(&p, &tmp, 0xC4);
    pokemonSetupAfterInsert(0, this, dst);
}

void CReliveStage::exchangeVisitor(Pokemon& p) {
    Pokemon* dst = stageVisitor(this);
    PokemonRaw tmp = *(PokemonRaw*)dst;
    memcpy(dst, &p, 0xC4);
    memcpy(&p, &tmp, 0xC4);
    pokemonSetupAfterInsert(0, this, dst);
}

void CReliveStage::pickupDancer(Pokemon& out, long slot) {
    Pokemon* src = stageDancer(this, slot);
    memcpy(&out, src, 0xC4);
    long next = slot + 1;
    long cnt = 4 - next;
    if (cnt != 0) memmove(src, dancer[next], cnt * 0xC4);
    pokemonInit((u32)(Pokemon*)dancer[3]);
}

void CReliveStage::insertDancer(Pokemon& in, long slot) {
    long next = slot + 1;
    long cnt = 4 - next;
    if (cnt != 0) memmove(dancer[next], dancer[slot], cnt * 0xC4);
    Pokemon* dst = stageDancer(this, slot);
    memcpy(dst, &in, 0xC4);
    pokemonSetupAfterInsert(0, this, dst);
    pokemonInit((u32)&in);
}

void CReliveStage::pickupVisitor(Pokemon& out) {
    memcpy(&out, visitor, 0xC4);
    pokemonInit((u32)stageVisitor(this));
}

s32 CReliveStage::getPassion() {
    s32 p = getPassionWoBonus();
    if (isBonusGet()) {
        p += _bonusStageBonusTbl[hallPtr()->getReliveGiveStageQuantity()];
    }
    return p;
}

bool CReliveStage::isBonusGet() {
    s32 p = getPassionWoBonus();
    bool r = false;
    if (isPokemonZokuseiAllUnique(true) && p == 0xC0) r = true;
    return r;
}

s32 CReliveStage::getPassionWoBonus() {
    Pokemon* v = VISITOR_OR_NULL(this);
    if (v == 0) return 0;
    s32 n = countDancers(this);
    s32 base = _tempoBase[n];
    s32 sum = pairSum(this, n);
    s32 total = sum + base;
    if (total == 0) return 0;
    Pokemon* hit = validOrNull(stageDancer(this, this->hit));
    f32 mult[3] = { 1.0f, 1.5f, 2.0f };
    s32 rel = pairAisyou(v, hit);
    f32 m;
    if (rel == -1) m = 0.0f;
    else m = mult[rel];
    return (s32)((f32)total * m);
}

s32 CReliveStage::getTempo() {
    s32 n;
    s32 base;
    s32 sum;
    s32 i;
    n = countDancers(this);
    base = _tempoBase[n];
    sum = 0;
    for (i = 0; i < n; i++) {
        Pokemon* a = validOrNull(stageDancer(this, i));
        Pokemon* b = validOrNull(stageDancer(this, (i + 1) % n));
        s32 add;
        s32 rel = pairAisyou(a, b);
        switch (rel) {
        case -1:
            add = 0;
            break;
        case 0:
            add = 0;
            break;
        case 1:
            add = _tempoNormal[n];
            break;
        case 2:
            add = _tempoGood[n];
            break;
        }
        sum += add;
    }
    return sum + base;
}

bool CReliveStage::isPokemonZokuseiAllUnique(bool withVisitor) {
    u8* seen = (u8*)__alloca(*zokusei_data_number);
    memset(seen, 0, *zokusei_data_number);
    s32 n = countDancers(this);
    s32 total = n;
    if (withVisitor) total = n + 1;
    for (s32 i = 0; i < total; i++) {
        Pokemon* p;
        if (i == n) {
            p = VISITOR_OR_NULL(this);
            if (p == 0) break;
        } else {
            p = validOrNull(stageDancer(this, i));
        }
        s32 last = -1;
        for (int j = 0; j < 2; j++) {
            int z = pokemonDataBiosGetZokuseiDataId(p->getPokemonDataPtr(), (u16)j);
            if (j == 1 && z == last) break;
            last = z;
            if (seen[z] != 0) return false;
            seen[z] = 1;
        }
    }
    return true;
}

Pokemon* CReliveStage::heroWalkReliveCallBack(long steps, bool pay) {
    u32 cur;
    if ((s16)getPassion() == 0) return 0;
    Pokemon* v = VISITOR_OR_NULL(this);
    if (v->getPokemonDataId() == 0xF9) return 0;
    u16 id = pokemonBiosGetDarkpokemonDataId(v);
    if (darkPokemonBiosGetReliveFlag(id) != 0) return 0;
    if (v->getDarkPointDirect() == 0) return 0;
    cur = darkPokemonBiosGetSteps(id);
    if (cur >= relivehall_data->steps && pay) {
        pokemonAddDp(v, (f32)-getPassion());
        darkPokemonBiosSetSteps(id, cur - relivehall_data->steps);
        if (v->getDarkPointDirect() != 0) return 0;
        return v;
    }
    darkPokemonBiosSetSteps(id, (u16)(cur + steps));
    return 0;
}

bool CReliveStage::isReliveReady() {
    Pokemon* v = VISITOR_OR_NULL(this);
    if (v == 0) return false;
    if (isLugiaReliveReady()) return true;
    bool r = v->getDarkPoint() <= 0.0f;
    if (r) {
        s32 n = countDancers(this);
        r = n != 0;
    }
    return r;
}

bool CReliveStage::isLugiaReliveReady() {
    Pokemon* v = VISITOR_OR_NULL(this);
    if (v == 0) return false;
    bool r = false;
    if (hallPtr()->isReliveReadyDarkLugiaExist() && v->getPokemonDataId() == 0xF9) r = true;
    return r;
}

s32 CReliveStage::getState() {
    if (isReliveReady()) return 3;
    s32 n = countDancers(this);
    s32 base = _tempoBase[n];
    s32 sum = pairSum(this, n);
    s32 total = sum + base;
    if (total == 0) return 0;
    s32 r = 1;
    if (total == 0x60) r = 2;
    return r;
}

CReliveStage* CReliveHall::getStage(long i) {
    return &stage[i];
}

void CReliveHall::init() {
    memset(this, 0, 0x2298);
    for (u32 i = 0; i < 9; i++) {
        memset(&stage[i], 0, 0x3D8);
        pokemonInitAry((u32)stageDancer(&stage[i], 0), 4);
        pokemonInit((u32)stageVisitor(&stage[i]));
    }
}

s32 CReliveHall::getReliveGiveStageQuantity() {
    s32 count = 0;
    for (s32 i = 0; i < 9; i++) {
        CReliveStage* st = &hallPtr()->stage[i];
        s32 n = countDancers(st);
        s32 base = _tempoBase[n];
        s32 sum = pairSum(st, n);
        u8 ok = 0;
        if (st->isPokemonZokuseiAllUnique(false) && sum + base == 0x60) ok = 1;
        if (ok != 0) count++;
    }
    return count;
}

Pokemon* CReliveHall::heroWalkReliveCallBack(long steps) {
    Pokemon* found = 0;
    for (u32 i = 0; i < 9; i++) {
        if (found == 0) found = stage[i].heroWalkReliveCallBack(steps, true);
        else stage[i].heroWalkReliveCallBack(steps, false);
    }
    return found;
}

bool CReliveHall::isReliveReadyPokemonExist() {
    for (u32 i = 0; i < 9; i++) {
        if (stage[i].isReliveReady()) return true;
    }
    return false;
}

s32 CReliveHall::getReliveReadyVisitorQuantity() {
    s32 n = 0;
    for (u32 i = 0; i < 9; i++) {
        if (stage[i].isReliveReady()) n++;
    }
    return n;
}

bool CReliveHall::isReliveReadyDarkLugiaExist() {
    for (u32 i = 0; i < 9; i++) {
        Pokemon* v = VISITOR_OR_NULL(&stage[i]);
        if (v == 0 || v->getPokemonDataId() != 0xF9) continue;
        for (u32 s = 0; s < 9; s++) {
            CReliveStage* st = &stage[s];
            s32 n = countDancers(st);
            s32 sum = pairSum(st, n);
            if (sum + _tempoBase[n] != 0x60) return false;
        }
        return true;
    }
    return false;
}

CReliveHall* CReliveHall::getPointer() {
    return hallPtr();
}

void CReliveHall::allocMakeBackup() {
    _pRelivehallCopy = (CReliveHall*)GSmemAllocClr(0x2298);
    memcpy(_pRelivehallCopy, this, 0x2298);
}

static inline CReliveStage* _backupStage(u32 i) {
    return &_pRelivehallCopy->stage[i];
}

void CReliveHall::checkWithBackupSet() {
    for (u32 i = 0; i < 9; i++) {
        CReliveStage* cur = &stage[i];
        if (memcmp(cur, _backupStage(i), 0x3D8) != 0) {
            Pokemon* v = VISITOR_OR_NULL(cur);
            if (v != 0) {
                darkPokemonBiosSetSteps(pokemonBiosGetDarkpokemonDataId(v), 0);
            }
        }
    }
    for (u32 i = 0; i < 9; i++) {
        CReliveStage* old = _backupStage(i);
        Pokemon* ov = VISITOR_OR_NULL(old);
        if (ov != 0) {
            u16 id = pokemonBiosGetDarkpokemonDataId(ov);
            u8 found = 0;
            for (u32 j = 0; j < 9; j++) {
                Pokemon* nv = VISITOR_OR_NULL(&stage[j]);
                if (nv != 0 && id == pokemonBiosGetDarkpokemonDataId(nv)) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) darkPokemonBiosSetSteps(id, 0);
        }
    }
    if (_pRelivehallCopy != 0) {
        GSmemFree(_pRelivehallCopy);
        _pRelivehallCopy = 0;
    }
}

bool CReliveHall::isOpen() {
    return flag_etc->reliveOpenFlag <= GSflagGet(0x3C4);
}

void CReliveHall::debugPokemonSetup(long mode) {
    static f32 darkRateTbl[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0 };
    if (mode == 0 || mode == 1) {
        u8 tmp[0xC4];
        static u16 tempMaxTbl2294[4] = { 0xB9, 0x118, 0x183, 0x132 };
        static u16 tempMaxTbl2298[3] = { 0x186, 0x124, 0x138 };
        static u16 dptbl[9] = { 0x44, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1 };
        memset(this, 0, 0x2298);
        for (u32 i = 0; i < 9; i++) {
            memset(&stage[i], 0, 0x3D8);
            pokemonInitAry((u32)stageDancer(&stage[i], 0), 4);
            pokemonInit((u32)stageVisitor(&stage[i]));
        }
        u32 base = 0;
        for (s32 s = 0; s < 8; s++, base += 2) {
            s32 counts[10] = { 4, 3, 2, 1, 1, 1, 1, 1, 1, 0 };
            u16 id = base;
            for (s32 d = 0; d < counts[s]; d++, id++) {
                s32 pick;
                if (s == 0) pick = tempMaxTbl2294[d];
                else if (s == 1) pick = tempMaxTbl2298[d];
                else pick = id;
                menuPocketDebugMakePokemonByID(*(Pokemon*)tmp, (u8)pick, false, 0.0f);
                s32 slot = findEmptySlot(&stage[s]);
                Pokemon* dst = stageDancer(&stage[s], slot);
                memcpy(dst, tmp, 0xC4);
                pokemonSetupAfterInsert(this, &stage[s], dst);
                pokemonInit((u32)(Pokemon*)tmp);
            }
            menuPocketDebugMakePokemonByID(*(Pokemon*)tmp, dptbl[s], true, darkRateTbl[(mode != 1) * 10 + s]);
            memcpy(stageVisitor(&stage[s]), tmp, 0xC4);
            pokemonSetupAfterInsert(this, &stage[s], stageVisitor(&stage[s]));
            pokemonInit((u32)(Pokemon*)tmp);
            stage[s].hit = 0;
        }
        return;
    }
    if (mode == 2) {
        u8 tmp[0xC4];
        static u16 tempMaxTbl2317[4] = { 0xB9, 0x118, 0x183, 0x132 };
        static u16 dptbl2[9] = { 0x49, 1, 2, 3, 4, 5, 6, 7, 8 };
        memset(this, 0, 0x2298);
        for (u32 i = 0; i < 9; i++) {
            memset(&stage[i], 0, 0x3D8);
            pokemonInitAry((u32)stageDancer(&stage[i], 0), 4);
            pokemonInit((u32)stageVisitor(&stage[i]));
        }
        for (s32 s = 0; s < 9; s++) {
            for (s32 d = 0; d < 4; d++) {
                menuPocketDebugMakePokemonByID(*(Pokemon*)tmp, tempMaxTbl2317[d], false, 0.0f);
                s32 slot = findEmptySlot(&stage[s]);
                Pokemon* dst = stageDancer(&stage[s], slot);
                memcpy(dst, tmp, 0xC4);
                pokemonSetupAfterInsert(this, &stage[s], dst);
                pokemonInit((u32)(Pokemon*)tmp);
            }
            menuPocketDebugMakeDarkPokemonByID(*(Pokemon*)tmp, dptbl2[s], darkRateTbl[10 + s]);
            memcpy(stageVisitor(&stage[s]), tmp, 0xC4);
            pokemonSetupAfterInsert(this, &stage[s], stageVisitor(&stage[s]));
            pokemonInit((u32)(Pokemon*)tmp);
            stage[s].hit = 0;
        }
    }
}

s32 reliveHallPokemonToAisyou(Pokemon* a, Pokemon* b) {
    Pokemon* ps[2];
    s32 z[2][2];
    ps[0] = a;
    ps[1] = b;
    if (a == 0 || b == 0) return -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            z[i][j] = pokemonDataBiosGetZokuseiDataId(ps[i]->getPokemonDataPtr(), (u16)j);
        }
    }
    s32 best = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            s32 x = z[0][i];
            s32 y = z[1][j];
            s32 v;
            if (x == 0 && y == 0) {
                v = 2;
            } else {
                v = jyoutaiLevel((u16)(zokuseiGetWazaJoutai((u16)x, (u16)y)));
            }
            if (best < v) best = v;
        }
    }
    return best;
}

namespace {
void _heroCallBackFunc(long, FootStepCounter, long steps) {
    if (GSflagGet(0x3C4) >= flag_etc->reliveOpenFlag) {
        Pokemon* p = hallPtr()->heroWalkReliveCallBack(steps);
        if (p != 0) {
            if (darkPokemonBiosGetInformationFlag(pokemonBiosGetDarkpokemonDataId(p)) == 0) {
                heroMoveInitEvent();
                heroMoveSetColision(1);
                GSthreadSwitch();
                DarkPokemon* dp = p->getDarkPokemon();
                darkPokemonWhere where;
                u8 floor;
                dp->getPlace(where, floor);
                menuScriptInfoRelive(p, (u32)((3 - where) | (where - 3)) >> 31, where);
                heroMoveTermEvent();
            }
        }
    }
}
}

extern "C" void reliveHallInfomationPokemonDP0(Pokemon* p) {
    if (darkPokemonBiosGetInformationFlag(pokemonBiosGetDarkpokemonDataId(p)) == 0) {
        heroMoveInitEvent();
        heroMoveSetColision(1);
        GSthreadSwitch();
        DarkPokemon* dp = p->getDarkPokemon();
        darkPokemonWhere where;
        u8 floor;
        dp->getPlace(where, floor);
        menuScriptInfoRelive(p, (u32)((3 - where) | (where - 3)) >> 31, where);
        heroMoveTermEvent();
    }
}

extern "C" void reliveHallCallBackInit(void) {
    _heroCallBackHandle = heroMoveAddStepCallback(_heroCallBackFunc, 0);
}

extern "C" void reliveHallDebugPokemonSetup(long mode) {
    hallPtr()->debugPokemonSetup(mode);
}

namespace {
u16 jyoutai2levelTbl[4] = { 0x43, 0x42, 0x3F, 0x41 };
}
