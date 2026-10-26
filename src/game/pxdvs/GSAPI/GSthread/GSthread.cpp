#include <dolphin/types.h>
#include <libc/stdarg.h>
#pragma pool_strings off

struct GSthread {
    GSthread* prev;
    GSthread* next;
    u8 active;
    u8 blocked;
    u8 sleeping;
    u8 affinity;
    u32 group;
    u32 stackSize;
    u8 running;
    u8 pending;
    u8 usesFPU;
    u8 autoStart;
    u32 result;
    void* entry;
    u32* stack;
    u32* ctx;
    s32 heap;
    u32 savedLR;
    char name[0x20];
};

extern "C" {
void* memcpy(void*, const void*, u32);
void GSlogWrite(const char*, ...);
void* GSmemAlloc(u32 size);
s32 GSmemGetCurrentHeap(void);
void* GSmemAllocHeap(s32 heap, u32 size);
void* GSmemAllocAlignHeap(s32 heap, u32 size, u32 align);
void GSmemFreeHeap(s32 heap, void* ptr);
u8 GSscratchIsPtr(void* ptr);
void GSscratchFree(void* ptr);
s32 GSscratchStore(void* source, void* destination, u32 size);
void GSscratchWaitForCompletion(void);
void DCFlushRange(void*, u32);
void GSthreadTerminate(GSthread* thread);
void GSthreadSwitch(void);
}

static GSthread* _activeThread;
static GSthread* _nextThread;
static GSthread* _threadListTop;
static u8 _rescan;
static u32 _saveLRReg;
static u32 _usesFPURegisters;
static u32 _tempGPR2;
static u32 _tempGPR1;
static u32* _destRegStatePtr;
static u32* _threadRegStatePtr;
static u32* _localRegStatePtr;
static GSthread* _threadList;
static u32 _maxThreads;
static u32 _GSthreadRegisterState[0x22];

extern "C" {

void threadSaveGPRRegisters(void);
void threadSaveFPRRegisters(void);
void threadLoadGPRRegisters(void);
void threadLoadFPRRegisters(void);
void threadExecute(void);
void fn_80103420(void);
static void _threadSwitch(void);
static void threadRemoveFromList(GSthread* thread);
static void threadInsertIntoList(GSthread* thread);
void threadExecutePass(u32 group, u8 groupOnly);
static void threadExitFunc(u32 result);
static void threadRun(GSthread* thread, u32* ctx, u8* scratch);
static void threadInitialize(GSthread* thread);
static u8* threadDMAStackToScratch(u32* stack, u32 size, u8 flag);
static GSthread* threadFindNext(GSthread* from, u32 group, u8 groupOnly);
static GSthread* threadFindUnused(void);

asm void threadLoadGPRRegisters(void) {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr
    lwz r0, 0x0(r3)
    lwz r2, 0x8(r3)
    lwz r4, 0x10(r3)
    lwz r5, 0x14(r3)
    lwz r6, 0x18(r3)
    lwz r7, 0x1c(r3)
    lwz r8, 0x20(r3)
    lwz r9, 0x24(r3)
    lwz r10, 0x28(r3)
    lwz r11, 0x2c(r3)
    lwz r12, 0x30(r3)
    lwz r13, 0x34(r3)
    lwz r14, 0x38(r3)
    lwz r15, 0x3c(r3)
    lwz r16, 0x40(r3)
    lwz r17, 0x44(r3)
    lwz r18, 0x48(r3)
    lwz r19, 0x4c(r3)
    lwz r20, 0x50(r3)
    lwz r21, 0x54(r3)
    lwz r22, 0x58(r3)
    lwz r23, 0x5c(r3)
    lwz r24, 0x60(r3)
    lwz r25, 0x64(r3)
    lwz r26, 0x68(r3)
    lwz r27, 0x6c(r3)
    lwz r28, 0x70(r3)
    lwz r29, 0x74(r3)
    lwz r30, 0x78(r3)
    lwz r31, 0x7c(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadLoadFPRRegisters(void) {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr
    addi r3, r3, 0x88
    lfd f0, 0x0(r3)
    lfd f1, 0x8(r3)
    lfd f2, 0x10(r3)
    lfd f3, 0x18(r3)
    lfd f4, 0x20(r3)
    lfd f5, 0x28(r3)
    lfd f6, 0x30(r3)
    lfd f7, 0x38(r3)
    lfd f8, 0x40(r3)
    lfd f9, 0x48(r3)
    lfd f10, 0x50(r3)
    lfd f11, 0x58(r3)
    lfd f12, 0x60(r3)
    lfd f13, 0x68(r3)
    lfd f14, 0x70(r3)
    lfd f15, 0x78(r3)
    lfd f16, 0x80(r3)
    lfd f17, 0x88(r3)
    lfd f18, 0x90(r3)
    lfd f19, 0x98(r3)
    lfd f20, 0xa0(r3)
    lfd f21, 0xa8(r3)
    lfd f22, 0xb0(r3)
    lfd f23, 0xb8(r3)
    lfd f24, 0xc0(r3)
    lfd f25, 0xc8(r3)
    lfd f26, 0xd0(r3)
    lfd f27, 0xd8(r3)
    lfd f28, 0xe0(r3)
    lfd f29, 0xe8(r3)
    lfd f30, 0xf0(r3)
    lfd f31, 0xf8(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadSaveGPRRegisters(void) {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr
    stw r0, 0x0(r3)
    stw r2, 0x8(r3)
    stw r3, 0xc(r3)
    stw r4, 0x10(r3)
    stw r5, 0x14(r3)
    stw r6, 0x18(r3)
    stw r7, 0x1c(r3)
    stw r8, 0x20(r3)
    stw r9, 0x24(r3)
    stw r10, 0x28(r3)
    stw r11, 0x2c(r3)
    stw r12, 0x30(r3)
    stw r13, 0x34(r3)
    stw r14, 0x38(r3)
    stw r15, 0x3c(r3)
    stw r16, 0x40(r3)
    stw r17, 0x44(r3)
    stw r18, 0x48(r3)
    stw r19, 0x4c(r3)
    stw r20, 0x50(r3)
    stw r21, 0x54(r3)
    stw r22, 0x58(r3)
    stw r23, 0x5c(r3)
    stw r24, 0x60(r3)
    stw r25, 0x64(r3)
    stw r26, 0x68(r3)
    stw r27, 0x6c(r3)
    stw r28, 0x70(r3)
    stw r29, 0x74(r3)
    stw r30, 0x78(r3)
    stw r31, 0x7c(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadSaveFPRRegisters(void) {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr
    addi r3, r3, 0x88
    stfd f0, 0x0(r3)
    stfd f1, 0x8(r3)
    stfd f2, 0x10(r3)
    stfd f3, 0x18(r3)
    stfd f4, 0x20(r3)
    stfd f5, 0x28(r3)
    stfd f6, 0x30(r3)
    stfd f7, 0x38(r3)
    stfd f8, 0x40(r3)
    stfd f9, 0x48(r3)
    stfd f10, 0x50(r3)
    stfd f11, 0x58(r3)
    stfd f12, 0x60(r3)
    stfd f13, 0x68(r3)
    stfd f14, 0x70(r3)
    stfd f15, 0x78(r3)
    stfd f16, 0x80(r3)
    stfd f17, 0x88(r3)
    stfd f18, 0x90(r3)
    stfd f19, 0x98(r3)
    stfd f20, 0xa0(r3)
    stfd f21, 0xa8(r3)
    stfd f22, 0xb0(r3)
    stfd f23, 0xb8(r3)
    stfd f24, 0xc0(r3)
    stfd f25, 0xc8(r3)
    stfd f26, 0xd0(r3)
    stfd f27, 0xd8(r3)
    stfd f28, 0xe0(r3)
    stfd f29, 0xe8(r3)
    stfd f30, 0xf0(r3)
    stfd f31, 0xf8(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadExecute(void) {
    nofralloc
    stwu r1, -0xc(r1)
    stw r3, 0xc(r1)
    mflr r3
    stw r3, 0x8(r1)
    lwz r3, _localRegStatePtr
    stw r3, _destRegStatePtr
    bl threadSaveGPRRegisters
    stw r1, 0x4(r3)
    lwz r3, _threadRegStatePtr
    stw r3, _destRegStatePtr
    bl threadLoadGPRRegisters
    lwz r5, _usesFPURegisters
    cmplwi r5, 0x0
    beq L_skipFPR
    bl threadLoadFPRRegisters
L_skipFPR:
    lwz r5, 0x84(r3)
    mtlr r5
    lwz r1, 0x4(r3)
    li r5, 0x0
    subi r5, r5, 0x1
    stw r5, 0x0(r1)
    lwz r5, 0x80(r3)
    mtctr r5
    lwz r5, 0x14(r3)
    lwz r3, 0xc(r3)
    bctr
}

asm void fn_80103420(void) {
    nofralloc
    lwz r3, 0x8(r1)
    mtlr r3
    lwz r3, 0xc(r1)
    addi r1, r1, 0xc
    blr
}

static asm void _threadSwitch(void) {
    nofralloc
    stw r3, _tempGPR1
    stw r5, _tempGPR2
    mflr r5
    lwz r3, _threadRegStatePtr
    stw r3, _destRegStatePtr
    bl threadSaveGPRRegisters
    stw r5, 0x80(r3)
    lwz r5, _tempGPR1
    stw r5, 0xc(r3)
    lwz r5, _tempGPR2
    stw r5, 0x14(r3)
    stw r1, 0x4(r3)
    lwz r5, _usesFPURegisters
    cmplwi r5, 0x0
    beq L_skipFPR2
    bl threadSaveFPRRegisters
L_skipFPR2:
    lwz r3, _localRegStatePtr
    stw r3, _destRegStatePtr
    bl threadLoadGPRRegisters
    lwz r5, 0x84(r3)
    mtlr r5
    lwz r1, 0x4(r3)
    lwz r5, 0x14(r3)
    lwz r3, 0xc(r3)
    blr
}

void GSthreadSetName(GSthread* thread, const char* name) {
    if (thread) {
        memcpy(thread->name, name, 0x1F);
        thread->name[0x1F] = 0;
    }
}

void GSthreadSetGroupID(GSthread* thread, u32 group) {
    if (thread) {
        thread->group = group;
    }
}

void GSthreadSwitch(void) {
    register GSthread* t = _activeThread;
    if (t) {
        asm {
            mflr r5
            stw r5, _saveLRReg
            stw r5, 0x2c(t)
        }
        _threadSwitch();
    }
}

GSthread* GSthreadGetCurrentThread(void) {
    return _activeThread;
}

void GSthreadUnblockGroup(u32 group) {
    u32 i;
    if (group == 0) {
        return;
    }
    for (i = 0; i < _maxThreads; i++) {
        GSthread* t = &_threadList[i];
        if (t->group == group) {
            t->sleeping = 0;
        }
    }
    _rescan = 1;
}

void GSthreadBlockGroup(u32 group) {
    u32 i;
    if (group == 0) {
        return;
    }
    for (i = 0; i < _maxThreads; i++) {
        GSthread* t = &_threadList[i];
        if (t->group == group) {
            t->sleeping = 1;
        }
    }
    _rescan = 1;
}

void GSthreadUnblock(GSthread* thread) {
    if (thread == 0) {
        return;
    }
    thread->blocked = 0;
    _rescan = 1;
}

void GSthreadBlock(GSthread* thread) {
    if (thread == 0) {
        return;
    }
    thread->blocked = 1;
    _rescan = 1;
}

void GSthreadExecuteAll(void) {
    threadExecutePass(0, 0);
}

void GSthreadExecuteGroup(u32 group) {
    threadExecutePass(group, 1);
}

u32 GSthreadClose(GSthread* thread) {
    u32 result;
    if (thread == 0) {
        return 0;
    }
    if (thread->autoStart == 1) {
        return 0;
    }
    result = thread->result;
    thread->active = 0;
    return result;
}

u8 GSthreadIsRunning(GSthread* thread) {
    if (thread == 0) {
        return 0;
    }
    return thread->running;
}

void GSthreadTerminateGroup(u32 group) {
    GSthread* t;
    for (t = _threadListTop; t != 0; t = t->next) {
        if (t->group == group) {
            GSthreadTerminate(t);
        }
    }
}

void GSthreadTerminate(GSthread* thread) {
    if (thread == 0) {
        return;
    }
    if (thread == _activeThread || thread == _nextThread) {
        thread->pending = 1;
        if (thread == _nextThread) {
            _rescan = 1;
        }
    } else {
        thread->running = 0;
        thread->active = 0;
        threadRemoveFromList(thread);
        if (thread->stack) {
            GSmemFreeHeap(thread->heap, thread->stack);
            thread->stack = 0;
        }
        if (thread->ctx) {
            GSmemFreeHeap(thread->heap, thread->ctx);
            thread->ctx = 0;
        }
    }
}

void GSthreadSetArgs(GSthread* thread, s32 count, ...) {
    va_list args;
    u32 reg;
    s32 i;
    u32* stack;
    s32 direct;
    u32* ctx;
    u32 idx;

    if (thread == 0) {
        return;
    }
    if (thread->running == 1) {
        return;
    }
    stack = thread->stack;
    ctx = thread->ctx;
    va_start(args, count);
    reg = 3;
    direct = 8;
    if (count < 8) {
        direct = count;
    }
    for (i = 0; i < direct; i++) {
        ctx[reg++] = *(u32*)__va_arg(args, 1);
    }
    if (count > 8) {
        ctx[1] -= (count - i) * 4;
        idx = (ctx[1] >> 2) + 2;
        for (i = 8; i < count; i++) {
            stack[idx++] = *(u32*)__va_arg(args, 1);
        }
    }
}

GSthread* GSthreadCreate(u8 affinity, u32 group, u32 stackSize, u8 usesFPU, u8 autoStart, void* entry) {
    s32 heap;
    GSthread* thread;

    if (usesFPU == 0) {
        GSlogWrite("GSthreadCreate. Warning: 'usesFPU==FALE' OK?\n");
    }
    thread = threadFindUnused();
    if (thread == 0) {
        return 0;
    }
    heap = GSmemGetCurrentHeap();
    thread->stack = (u32*)GSmemAllocAlignHeap(heap, stackSize, 0x20);
    if (thread->stack == 0) {
        return 0;
    }
    u32 ctxSize = 0x88;
    if (usesFPU) {
        ctxSize = 0x188;
    }
    thread->ctx = (u32*)GSmemAllocHeap(heap, ctxSize);
    if (thread->ctx == 0) {
        return 0;
    }
    thread->active = 1;
    thread->group = group;
    thread->stackSize = stackSize;
    thread->running = 0;
    thread->pending = 0;
    thread->usesFPU = usesFPU;
    thread->entry = entry;
    thread->blocked = 0;
    thread->sleeping = 0;
    thread->affinity = affinity;
    thread->prev = 0;
    thread->next = 0;
    thread->autoStart = autoStart;
    thread->heap = heap;
    thread->savedLR = 0;
    thread->name[0] = 0;
    threadInitialize(thread);
    threadInsertIntoList(thread);
    _rescan = 1;
    return thread;
}

u32 GSthreadInit(u32 maxThreads) {
    u32 i;
    _maxThreads = maxThreads;
    _threadList = (GSthread*)GSmemAlloc(maxThreads * sizeof(GSthread));
    if (_threadList == 0) {
        return 0;
    }
    for (i = 0; i < _maxThreads; i++) {
        _threadList[i].active = 0;
    }
    _activeThread = 0;
    _threadListTop = 0;
    GSlogWrite("GSthread: Init OK, maximum of %d threads\n", _maxThreads);
    return 1;
}

static void threadRemoveFromList(GSthread* thread) {
    if (thread == 0) {
        return;
    }
    if (thread->prev) {
        thread->prev->next = thread->next;
    }
    if (thread->next) {
        thread->next->prev = thread->prev;
    }
    if (_threadListTop == thread) {
        _threadListTop = thread->next;
    }
}

static void threadInsertIntoList(GSthread* thread) {
    GSthread* next;
    GSthread* cur;
    if (thread == 0) {
        return;
    }
    if (_threadListTop == 0) {
        _threadListTop = thread;
        return;
    }
    cur = _threadListTop;
    while ((next = cur->next) != 0 && cur->affinity < thread->affinity) {
        cur = next;
    }
    if (next == 0 && cur->affinity < thread->affinity) {
        thread->prev = cur;
        thread->next = 0;
        cur->next = thread;
        return;
    }
    if (cur->prev) {
        cur->prev->next = thread;
    }
    thread->prev = cur->prev;
    thread->next = cur;
    cur->prev = thread;
    if (_threadListTop == cur) {
        _threadListTop = thread;
    }
}

void threadExecutePass(u32 group, u8 groupOnly) {
    u32* ctx;
    u32* stack;
    u8* scratch;
    u32* nextStack;
    u8* nextScratch;
    GSthread* thread;
    GSthread* next;

    thread = threadFindNext(0, group, groupOnly);
    if (thread == 0) {
        return;
    }
    stack = thread->stack;
    ctx = thread->ctx;
    scratch = threadDMAStackToScratch(stack, thread->stackSize, 1);
    while (thread != 0) {
        next = threadFindNext(thread, group, groupOnly);
        _nextThread = next;
        if (next != 0) {
            nextStack = next->stack;
            nextScratch = threadDMAStackToScratch(nextStack, next->stackSize, 0);
        }
        threadRun(thread, ctx, scratch);
        if (thread->pending != 0) {
            if (GSscratchIsPtr(scratch)) {
                GSscratchFree(scratch);
            }
            GSthreadTerminate(thread);
        } else if (GSscratchIsPtr(scratch)) {
            DCFlushRange(stack, thread->stackSize);
            GSscratchStore(stack, scratch, thread->stackSize);
            GSscratchWaitForCompletion();
            GSscratchFree(scratch);
        }
        if (_rescan == 0 || _nextThread == threadFindNext(thread, group, groupOnly)) {
            thread = _nextThread;
            if (thread != 0) {
                ctx = thread->ctx;
                scratch = nextScratch;
                stack = nextStack;
            }
        } else {
            if (GSscratchIsPtr(nextScratch)) {
                GSscratchWaitForCompletion();
                GSscratchFree(nextScratch);
            }
            if (_nextThread != 0 && _nextThread->pending != 0) {
                GSthread* dead = _nextThread;
                _nextThread = 0;
                GSthreadTerminate(dead);
            }
            _nextThread = threadFindNext(thread, group, groupOnly);
            thread = _nextThread;
            if (thread != 0) {
                stack = thread->stack;
                ctx = thread->ctx;
                scratch = threadDMAStackToScratch(stack, thread->stackSize, 1);
            }
        }
        _rescan = 0;
    }
}

static void threadExitFunc(u32 result) {
    GSthread* thread = _activeThread;
    thread->result = result;
    if (thread->autoStart == 1) {
        GSthreadTerminate(thread);
    } else {
        thread->pending = 1;
        thread->running = 0;
        threadRemoveFromList(thread);
        _rescan = 1;
    }
    GSthreadSwitch();
}

static void threadRun(GSthread* thread, u32* ctx, u8* scratch) {
    _activeThread = thread;
    thread->running = 1;
    ctx[1] = (u32)scratch + ctx[1];
    _GSthreadRegisterState[0x84 / 4] = (u32)fn_80103420;
    _localRegStatePtr = _GSthreadRegisterState;
    _threadRegStatePtr = ctx;
    _usesFPURegisters = thread->usesFPU;
    threadExecute();
    ctx[1] = ctx[1] - (u32)scratch;
    _activeThread = 0;
}

static void threadInitialize(GSthread* thread) {
    u32* ctx;
    u32* stack;
    if (thread == 0) {
        return;
    }
    ctx = thread->ctx;
    stack = thread->stack;
    _destRegStatePtr = ctx;
    threadSaveGPRRegisters();
    if (thread->usesFPU) {
        threadSaveFPRRegisters();
    }
    ctx[1] = thread->stackSize - 8;
    ctx[0x80 / 4] = (u32)thread->entry;
    ctx[0x84 / 4] = (u32)threadExitFunc;
    *stack = -1;
}

static u8* threadDMAStackToScratch(u32* stack, u32 size, u8 flag) {
}

static GSthread* threadFindNext(GSthread* from, u32 group, u8 groupOnly) {
    GSthread* t;
    if (from == 0) {
        t = _threadListTop;
    } else {
        t = from->next;
    }
    while (t != 0) {
        if (t->active != 0 && t->blocked == 0 && t->sleeping == 0 && t->pending == 0) {
            if (groupOnly == 0 || t->group == group) {
                return t;
            }
        }
        t = t->next;
    }
    return 0;
}

static GSthread* threadFindUnused(void) {
    GSthread* t = _threadList;
    u32 n;
    for (n = _maxThreads; n != 0; n--) {
        if (t->active == 0) {
            return t;
        }
        t++;
    }
    return 0;
}

}
