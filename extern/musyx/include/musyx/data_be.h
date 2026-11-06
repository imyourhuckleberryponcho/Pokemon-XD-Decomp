#ifndef _MUSYX_DATA_BE_H_
#define _MUSYX_DATA_BE_H_

#if defined(__MWERKS__) || MUSY_TARGET != MUSY_TARGET_DOLPHIN
#define MSETHILO(p, v) (*(p) = (v))
#define MAUXSWAP(buf) ((void)0)
#else
#define MSETHILO(p, v) (((unsigned short*)(p))[0] = (unsigned short)((unsigned long)(v) >> 16), ((unsigned short*)(p))[1] = (unsigned short)(v))
static inline void musyAuxSwap(void* buf) {
  unsigned long* w = (unsigned long*)buf;
  int i;
  for (i = 0; i < 480; ++i) {
    w[i] = (w[i] >> 16) | (w[i] << 16);
  }
}
#define MAUXSWAP(buf) musyAuxSwap(buf)
#endif

#if defined(__MWERKS__) || MUSY_TARGET != MUSY_TARGET_DOLPHIN
#define MD16(x) (x)
#define MD32(x) (x)
#define MD16S(x) (x)
#define MD32S(x) (x)
#define MLE16(x) ((x) >> 8 | (x) << 8)
#else
#define MLE16(x) (x)
static inline unsigned short musyDataSwap16(unsigned short v) { return (unsigned short)((v >> 8) | (v << 8)); }
static inline unsigned long musyDataSwap32(unsigned long v) {
  return (v >> 24) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 24);
}
#define MD16(x) musyDataSwap16((unsigned short)(x))
#define MD32(x) musyDataSwap32((unsigned long)(x))
#define MD16S(x) ((short)musyDataSwap16((unsigned short)(x)))
#define MD32S(x) ((long)musyDataSwap32((unsigned long)(x)))
#endif

#endif
