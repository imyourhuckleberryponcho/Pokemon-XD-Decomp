#include <dolphin/mtx.h>
#include <game/gcdata.h>

struct GSmtx {
    PC_KEEP_INLINE GSmtx() {}

    Mtx m;
};

static inline GSmtx GSmtxMakeIdentity() {
    GSmtx mtx;
    PSMTXIdentity(mtx.m);
    return mtx;
}

extern "C" {
GSmtx mtxIdent = GSmtxMakeIdentity();
}
