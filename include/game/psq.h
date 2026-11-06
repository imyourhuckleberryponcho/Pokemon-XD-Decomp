#ifndef GAME_PSQ_H
#define GAME_PSQ_H

#ifndef __MWERKS__

static inline float psq_load_gqr(const void* p, int gqr) {
    switch (gqr) {
    case 2: return (float)*(const unsigned char*)p;
    case 3: return (float)*(const unsigned short*)p;
    case 4: return (float)*(const signed char*)p;
    case 5: return (float)*(const short*)p;
    case 6: return (float)*(const short*)p * (1.0f / 64.0f);
    default: return *(const float*)p;
    }
}

static inline float psq_clamp(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

static inline void psq_store_gqr(void* p, float v, int gqr) {
    switch (gqr) {
    case 2: *(unsigned char*)p = (unsigned char)psq_clamp(v, 0.0f, 255.0f); break;
    case 3: *(unsigned short*)p = (unsigned short)psq_clamp(v, 0.0f, 65535.0f); break;
    case 4: *(signed char*)p = (signed char)psq_clamp(v, -128.0f, 127.0f); break;
    case 5: *(short*)p = (short)psq_clamp(v, -32768.0f, 32767.0f); break;
    case 6: *(short*)p = (short)psq_clamp(v * 64.0f, -32768.0f, 32767.0f); break;
    default: *(float*)p = v; break;
    }
}

#define PSQ_LOAD(ptr, off, gqr) psq_load_gqr((const char*)(ptr) + (off), (gqr))
#define PSQ_STORE(ptr, off, val, gqr) psq_store_gqr((char*)(ptr) + (off), (val), (gqr))

#endif

#endif
