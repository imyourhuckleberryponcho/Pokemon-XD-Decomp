#ifndef GAME_DECLSPEC_H
#define GAME_DECLSPEC_H

#ifdef __MWERKS__
#define DECL_SECTION(s) __declspec(section s)
#define DECL_WEAK __declspec(weak)
#else
#define DECL_SECTION(s)
#define DECL_WEAK
#endif

#endif
