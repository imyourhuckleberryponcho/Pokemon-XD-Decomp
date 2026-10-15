#include <dolphin/mtx.h>

extern "C" {
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void* memcpy(void* dst, const void* src, u32 n);
extern Mtx mtxIdent;
}

struct GSmtx {
    Mtx m;
};

struct GSgfxMatrixStackEntry {
    u32 flags;
    Mtx mtx;
    Mtx unk34;
};

class GSgfxMatrixStack {
public:
    GSgfxMatrixStack(u32 count);
    ~GSgfxMatrixStack();
    void push(GSmtx* mtx);
    void pushMult(GSmtx* mtx);
    void pop();

    GSgfxMatrixStackEntry* mBase;
    GSgfxMatrixStackEntry* mTop;
    GSgfxMatrixStackEntry* mLast;
};

void GSgfxMatrixStack::pop() { mTop--; }

void GSgfxMatrixStack::pushMult(GSmtx* mtx) {
    mTop++;
    PSMTXConcat(mTop[-1].mtx, mtx->m, mTop->mtx);
    mTop->flags |= 1;
}

void GSgfxMatrixStack::push(GSmtx* mtx) {
    mTop++;
    if (mtx == NULL) {
        PSMTXCopy(mTop[-1].mtx, mTop->mtx);
    } else {
        PSMTXCopy(mtx->m, mTop->mtx);
    }
    mTop->flags |= 1;
}

GSgfxMatrixStack::~GSgfxMatrixStack() {
    GSmemFree(mBase);
    mBase = 0;
}

GSgfxMatrixStack::GSgfxMatrixStack(u32 count) {
    mBase = (GSgfxMatrixStackEntry*)GSmemAlloc(count * sizeof(GSgfxMatrixStackEntry));
    mTop = mBase;
    mLast = mBase + (count - 1);
    memcpy(mTop->mtx, mtxIdent, sizeof(Mtx));
    mTop->flags |= 1;
}
