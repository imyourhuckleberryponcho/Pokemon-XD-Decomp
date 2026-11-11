#ifndef GAME_EXPLIMIT_H
#define GAME_EXPLIMIT_H
#ifdef __MWERKS__
#define EXP_LEVEL_LIMIT 100
#else
#ifdef __cplusplus
extern "C" {
#endif
extern unsigned char xdExpLevelLimit;
#ifdef __cplusplus
}
#endif
#define EXP_LEVEL_LIMIT xdExpLevelLimit
#endif
#endif
