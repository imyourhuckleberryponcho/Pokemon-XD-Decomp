#include <dolphin/mtx.h>

struct GSmtx {
    GSmtx() {}

    Mtx m;
};

static inline GSmtx GSmtxMakeIdentity() {
    GSmtx mtx;
    PSMTXIdentity(mtx.m);
    return mtx;
}

GSmtx mtxIdent = GSmtxMakeIdentity();
