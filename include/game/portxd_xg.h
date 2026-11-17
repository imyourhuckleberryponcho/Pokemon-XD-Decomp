#ifndef GAME_PORTXD_XG_H
#define GAME_PORTXD_XG_H

#ifndef __MWERKS__
#ifdef __cplusplus
extern "C" int PortXD_IsXG(void);
#else
int PortXD_IsXG(void);
#endif
#define XG_ON() PortXD_IsXG()
#define XG(xd, xg) (PortXD_IsXG() ? (xg) : (xd))
#define XG_CONST(n, call) (PortXD_IsXG() ? (n) : (call))
#else
#define XG_ON() 0
#define XG(xd, xg) (xd)
#define XG_CONST(n, call) (call)
#endif

#ifndef __MWERKS__
#ifdef __cplusplus
extern "C" int PortXD_XG_IsShadowWaza(u16 wazaID);
#else
int PortXD_XG_IsShadowWaza(u16 wazaID);
#endif
#define XG_SHADOW_KEY(w) (PortXD_IsXG() ? (PortXD_XG_IsShadowWaza((u16)(w)) ? 0x165 : 1) : (w))
#else
#define XG_SHADOW_KEY(w) (w)
#endif

#endif
