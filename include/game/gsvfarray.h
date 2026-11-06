#ifndef GAME_GSVFARRAY_H
#define GAME_GSVFARRAY_H
#ifdef __MWERKS__
#define GSGFX_VF_SET_ARRAY_NATIVE GSgfxVFSetArray
#else
struct GSgfxVF;
#define GSGFX_VF_ARRAY_NATIVE 0x8000
extern "C" void GSgfxVFSetArrayNative(GSgfxVF* vf, s32 type, s32 compData, void* array, s32 stride, u32 size);
#define GSGFX_VF_SET_ARRAY_NATIVE(vf, type, comp, array, stride, size)                                          \
    GSgfxVFSetArrayNative((GSgfxVF*)(vf), (type), (comp), (void*)(array), (stride), (u32)(size))
#endif
#endif
