#ifndef GAME_GCFIELD_H
#define GAME_GCFIELD_H
#ifdef __MWERKS__
#define THIS_F(Tp, off, m) M2C_FIELD(this, Tp, off)
#define THIS_FP(Tp, off, m) M2C_FIELD(this, Tp, off)
#else
#include <game/gcptr.h>
#define THIS_F(Tp, off, m) (*(Tp)&this->m)
#define THIS_FP(Tp, off, m) (*(GCuptr*)&this->m)
#endif

#ifdef __MWERKS__
#define RAW_F(Tp, p, off, S, m) (*(Tp)((p) + (off)))
#define RAW_FP(Tp, p, off, S, m) (*(Tp)((p) + (off)))
#define RAW_P(Tp, p, off, S, m) ((Tp)((p) + (off)))
#define RAW_A(p, off, S, m) ((p) + (off))
#define RAW_AI(p, off, i, k, S, m) ((p) + (off) + (i) * (k))
#else
#include <game/gcptr.h>
#define RAW_F(Tp, p, off, S, m) (*(Tp)&((S*)(p))->m)
#define RAW_FP(Tp, p, off, S, m) (*(GCuptr*)&((S*)(p))->m)
#define RAW_P(Tp, p, off, S, m) ((Tp)&((S*)(p))->m)
#define RAW_A(p, off, S, m) ((u8*)&((S*)(p))->m)
#define RAW_AI(p, off, i, k, S, m) ((u8*)&((S*)(p))->m[i])
#endif
#endif
