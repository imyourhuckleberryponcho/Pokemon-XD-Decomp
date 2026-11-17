#ifndef GAME_PORTXD_JP_H
#define GAME_PORTXD_JP_H

#ifndef __MWERKS__
#ifdef __cplusplus
extern "C" int PortXD_TextIsJapanese(void);
#else
int PortXD_TextIsJapanese(void);
#endif
#define PORT_COUNTRY_DISP() (PortXD_TextIsJapanese() ? 0 : pokecoloGetCountryCode())
#ifndef PORT_TEXT_JP
#define PORT_TEXT_JP() PortXD_TextIsJapanese()
#endif
#else
#define PORT_COUNTRY_DISP() pokecoloGetCountryCode()
#ifndef PORT_TEXT_JP
#define PORT_TEXT_JP() 0
#endif
#endif

#endif
