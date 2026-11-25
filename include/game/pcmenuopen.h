#ifndef GAME_PCMENUOPEN_H
#define GAME_PCMENUOPEN_H
#if !defined(__MWERKS__) && defined(__cplusplus)
#include <game/gcptr.h>

extern "C" s32 menuOpenCustom(s32 menu_id, s32 parent_id, s32* cursor_out, u32 close_flags, u8 check_cursor,
                              s32 open_param, ...);

extern "C++" {
template <class T> inline GCuptr pc_menu_arg(T* p) { return (GCuptr)p; }
template <class T> inline GCuptr pc_menu_arg(T v) {
    return sizeof(T) <= 4 ? (GCuptr)(u32)v : (GCuptr)v;
}
GCuptr pc_menu_arg(float) = delete;
GCuptr pc_menu_arg(double) = delete;

template <class... A>
inline s32 pc_menuOpenCustom(s32 menu_id, s32 parent_id, s32* cursor_out, u32 close_flags, u8 check_cursor,
                             s32 open_param, A... args) {
    return (menuOpenCustom)(menu_id, parent_id, cursor_out, close_flags, check_cursor, open_param,
                            pc_menu_arg(args)...);
}
}
#define menuOpenCustom pc_menuOpenCustom
#endif

#endif
