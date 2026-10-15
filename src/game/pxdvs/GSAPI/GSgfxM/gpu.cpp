#include <dolphin/types.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

struct GSgfx_GCFifoObj { void* base; void* end; u32 size; u32 hi; u32 lo; void* read; void* write; u32 status; u8 bound; u8 enable; u8 pad[0x2A]; u32 breakpointReached; u8 pad50[0x30]; };
struct GPUState { u8 pad[0xC50]; GSgfx_GCFifoObj* fifo; GSgfx_GCFifoObj* spare; void* buffer; void* write; u8 breakpt; u8 drawdone; };
extern "C" { s32 gsgfx_gpu_mode; }
static GSgfx_GCFifoObj _gpuFifo[2];
static s32 _gpuMode; static void* _gpuImmedBuf; static GSgfx_GCFifoObj* _gpuImmedFifo; static GSgfx_GCFifoObj* _gpuBufferFifo; static volatile u32 _gpuNextFifo;
static u8 _gpuIgnoreDrawDone, _gpuIgnoreDrawSync, _gpuIgnoreBreakpoint;
static void (*_gpuDrawDoneUserCB)(void); static void (*_gpuDrawSyncUserCB)(u16); static void (*_gpuBreakpointUserCB)(void);
extern "C" {
extern GPUState* gsgfxState;
void* GSmemAlloc(u32); void GSgfx_GCReset(void);
void* memset(void*, int, u32);

}
void GSgfxRenderAbortFrame(void);
extern "C" s32 GSgfxGPUSetMode(s32);
static void _gpuDrawDoneCallback(void); static void _gpuDrawSyncCallback(u16); static void _gpuBreakpointCallback(void);
void GSgfxGPUGetBPTick(s32* a, s32* b) { *a=-1; *b=-1; }
void GSgfxGPUProcessBlock(GSgfx_GCFifoObj* old, void* buffer, void* ptr) {
 GSgfx_GCFifoObj* f; u32 irq=OSDisableInterrupts(); s32 idx=(s32)_gpuNextFifo; u32 next=(u32)(idx+1); u32 offset=(u32)idx<<7; _gpuNextFifo=next; f=(GSgfx_GCFifoObj*)((u8*)_gpuFifo+offset); if((s32)_gpuNextFifo>1) _gpuNextFifo=0;
 u32 size=GXGetFifoSize((GXFifoObj*)old); void* base=GXGetFifoBase((GXFifoObj*)old);
 f->base=base; f->end=(u8*)base+size-4; f->size=size; f->hi=size-(size>>4); f->lo=size>>1; f->read=base; f->write=base; f->status=0; f->bound=0; f->enable=0;
 GXInitFifoPtrs((GXFifoObj*)f,buffer,ptr); gsgfxState->fifo=old; gsgfxState->spare=f; gsgfxState->buffer=buffer; gsgfxState->write=ptr; gsgfxState->breakpt=0; gsgfxState->drawdone=1;
 GXEnableBreakPt(ptr); GXSetGPFifo((GXFifoObj*)f); OSRestoreInterrupts(irq);
}
void GSgfxGPUInitFifoBase(GSgfx_GCFifoObj* f, void* base, u32 size) {
 f->base=base; f->end=(u8*)base+size-4; f->size=size; f->hi=size-(size>>4); f->lo=size>>1; f->read=base; f->write=base; f->status=0; f->bound=0; f->enable=0;
}
void GSgfxGPUSetBreakpointCallback(void (*cb)(void)) { _gpuBreakpointUserCB=cb; }
void GSgfxGPUSetDrawSyncCallback(void (*cb)(u16)) { _gpuDrawSyncUserCB=cb; }
void GSgfxGPUSetDrawDoneCallback(void (*cb)(void)) { _gpuDrawDoneUserCB=cb; }
void GSgfxGPUEnterBufferedMode(GSgfx_GCFifoObj* f) { GSgfxGPUSetMode(2); GXSetCPUFifo((GXFifoObj*)f); }
static inline void gpuSetReadPtr(GSgfx_GCFifoObj* fifo, void* ptr) {
 u32 irq=OSDisableInterrupts(); void* read; void* write;
 GXGetFifoPtrs((GXFifoObj*)fifo,&read,&write);
 GXInitFifoPtrs((GXFifoObj*)fifo,ptr,write); OSRestoreInterrupts(irq);
}
static inline void gpuSetWritePtr(GSgfx_GCFifoObj* fifo, void* ptr) {
 u32 irq=OSDisableInterrupts(); void* read; void* write;
 GXGetFifoPtrs((GXFifoObj*)fifo,&read,&write);
 GXInitFifoPtrs((GXFifoObj*)fifo,read,ptr); OSRestoreInterrupts(irq);
}
extern "C" s32 GSgfxGPUSetMode(s32 mode) {
    int old;
    if (mode) {
        old = _gpuMode;
        if (old == mode) return old;
        switch (mode) {
        case 1: {
            GSgfxRenderAbortFrame();
            _gpuBufferFifo = (GSgfx_GCFifoObj*)GXGetCPUFifo();
            GXSaveCPUFifo((GXFifoObj*)_gpuBufferFifo);
            GXSaveGPFifo(GXGetGPFifo());
            memset(_gpuImmedBuf, 0, 0x10000);
            DCFlushRange(_gpuImmedBuf, 0x10000);
            gpuSetReadPtr(_gpuImmedFifo, _gpuImmedBuf);
            gpuSetWritePtr(_gpuImmedFifo, _gpuImmedBuf);
            GXSetCPUFifo((GXFifoObj*)_gpuImmedFifo);
            GXSetGPFifo((GXFifoObj*)_gpuImmedFifo);
            GXDisableBreakPt();
            GSgfx_GCReset();
            _gpuIgnoreDrawDone = 1;
            GXDrawDone();
            VIWaitForRetrace();
            _gpuIgnoreDrawDone = 0;
        } break;
        case 2: {
            switch (old) {
            case 0: {
                _gpuIgnoreDrawDone = 1;
                GXDrawDone();
                VIWaitForRetrace();
                _gpuIgnoreDrawDone = 0;
                GXSaveCPUFifo((GXFifoObj*)_gpuImmedFifo);
            } break;
            case 1: {
                GSgfxRenderAbortFrame();
                GXSaveCPUFifo((GXFifoObj*)_gpuImmedFifo);
                GXSetCPUFifo((GXFifoObj*)_gpuBufferFifo);
                GSgfx_GCReset();
            } break;
            }
        } break;
        }
        _gpuMode = mode;
        gsgfx_gpu_mode = mode;
        return old;
    }
    return mode;
}
GSgfx_GCFifoObj* GSgfxGPUGetImmediateFifo(void) { return _gpuImmedFifo; }
void GSgfxGPUShutdown(void) { u8 brk; u8 state; GXGetGPStatus((GXBool*)&state,(GXBool*)&state,(GXBool*)&brk,(GXBool*)&state,(GXBool*)&state); if(brk!=1) GXAbortFrame(); GXSetDrawDoneCallback(0); GXSetDrawSyncCallback(0); GXSetBreakPtCallback(0); }
void GSgfxGPUInit(void) {
 _gpuImmedBuf=GSmemAlloc(0x10000); DCFlushRange(_gpuImmedBuf,0x10000); _gpuImmedFifo=(GSgfx_GCFifoObj*)GXInit(_gpuImmedBuf,0x10000);
 _gpuMode=0; gsgfx_gpu_mode=0; gsgfxState->fifo=0; gsgfxState->spare=0; gsgfxState->buffer=0; gsgfxState->write=0; gsgfxState->breakpt=0; gsgfxState->drawdone=0;
 _gpuIgnoreDrawDone=0; _gpuIgnoreDrawSync=0; _gpuIgnoreBreakpoint=0; _gpuDrawDoneUserCB=0; _gpuDrawSyncUserCB=0; _gpuBreakpointUserCB=0;
 GXSetDrawDoneCallback(_gpuDrawDoneCallback); GXSetDrawSyncCallback(_gpuDrawSyncCallback); GXSetBreakPtCallback(_gpuBreakpointCallback);
}
static void _gpuBreakpointCallback(void) {
    void* ptr;
    GSgfx_GCFifoObj* fifo;
    GSgfx_GCFifoObj* cpu;
    fifo = (GSgfx_GCFifoObj*)GXGetGPFifo();
    if (fifo != _gpuImmedFifo) {
        OSEnableInterrupts();
        u8 brk;
        u8 state;
        do {
            GXGetGPStatus((GXBool*)&state, (GXBool*)&state, (GXBool*)&brk,
                          (GXBool*)&state, (GXBool*)&state);
        } while (brk != 1);
        OSDisableInterrupts();
        GXSaveGPFifo((GXFifoObj*)fifo);
        gsgfxState->breakpt = 1;
        gsgfxState->drawdone = 0;
        cpu = gsgfxState->fifo;
        ptr = gsgfxState->write;
        gpuSetReadPtr(cpu, ptr);
        cpu->breakpointReached = 1;
        if (_gpuIgnoreBreakpoint != 1 && _gpuBreakpointUserCB) _gpuBreakpointUserCB();
    }
}
u32 GSgfxGPUIsIdle(void) { u8 busy; u8 idle; GXGetGPStatus((GXBool*)&busy,(GXBool*)&busy,(GXBool*)&idle,(GXBool*)&busy,(GXBool*)&busy); return ((u32)__cntlzw(1-idle))>>5; }
void GSgfxGPUSetFifoWritePtr(GSgfx_GCFifoObj* f, void* ptr) { u32 irq=OSDisableInterrupts(); void* read; void* write; GXGetFifoPtrs((GXFifoObj*)f,&read,&write); GXInitFifoPtrs((GXFifoObj*)f,read,ptr); OSRestoreInterrupts(irq); }
static void _gpuDrawSyncCallback(u16 token) { if(_gpuIgnoreDrawSync!=1 && _gpuDrawSyncUserCB) _gpuDrawSyncUserCB(token); }
static void _gpuDrawDoneCallback(void) { if(_gpuIgnoreDrawDone!=1 && _gpuDrawDoneUserCB) _gpuDrawDoneUserCB(); }
