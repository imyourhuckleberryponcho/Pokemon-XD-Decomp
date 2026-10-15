// STATUS: 4/12 exact. Work in progress.
#include <dolphin/types.h>

extern "C" {

// Global data
extern u8 _menuOffScreenEnable;
extern u8 _menuOffScreenUsing;
extern u8 _menuOffScreenDisp;
extern u8 _menuOffScreenType;
extern void* _menuOffScreenTex;
extern f32 _menuOffScreenStartRate;
extern f32 _menuOffScreenCurrRate;
extern f32 _menuOffScreenEndRate;
extern f32 _menuOffScreenTime;
extern f32 _menuOffScreenCnt;
extern u8 _menuOffScreenPrio;

// Forward decls
void menuOffScreenDraw(void);
void menuOffScreenFadeSync(u8 param);
void menuOffScreenFadeSet(f32 f1, f32 f2);

// Functions in target order

void menuOffScreenDraw(void) {
 // TODO: implement
}

void menuOffScreenFadeSync(u8 param) {
 // TODO: implement
}

void menuOffScreenFadeSet(f32 f1, f32 f2) {
    f32 f0 = 0.0f;  // This should be a constant
    f32 f3 = _menuOffScreenCurrRate;

    _menuOffScreenType = 1;
    _menuOffScreenStartRate = f3;
    _menuOffScreenEndRate = f1;
    _menuOffScreenCurrRate = f0;
    _menuOffScreenTime = f2;
    _menuOffScreenCnt = f0;

    if (f0 == f2) {
        _menuOffScreenTime = 0.0f;
        _menuOffScreenCnt = 0.0f;
    }
}

u8 menuOffScreenSetPriority(u8 val) {
    u8 old = _menuOffScreenPrio;
    _menuOffScreenPrio = val;
    return old;
}

u8 menuOffScreenSetDisp(u8 val) {
    u8 old = _menuOffScreenDisp;
    _menuOffScreenDisp = val;
    return old;
}

u8 menuOffScreenIsDoing(void) {
    return _menuOffScreenUsing;
}

void* menuOffScreenGetPtr(void) {
    return _menuOffScreenTex;
}

u8 menuOffScreenCheckEnable(u8 param) {
    return 0;
}

void menuOffScreenRelease(void) {
}

void menuOffScreenCreate(u32 param) {
}

void menuOffScreenInit(u32 param) {
}

void _menuCBOffScreen__FP9GStextureUlPv(void) {
}

}  // extern "C"
