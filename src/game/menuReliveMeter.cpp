// WIP: the five entry/helper functions match (540 bytes). The 3,704-byte
// renderer remains NonMatching: arithmetic reassociation and register allocation
// still differ (121 strict instruction differences). Uses -O4,p and peephole off.

#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>
#pragma peephole off

struct GSgfxVF;
class GSgfxLayer {
public:
    u8 pad0[0xD34]; u8 colorCount; u8 padD35[3]; u32 colorMode;
    u8 padD3C[0x16A8-0xD3C]; u32 flagsA; u32 flagsB;
    u8 pad16B0[0x1760-0x16B0]; u32 flagsC; u32 flagsD;
    u8 pad1768[0x1998-0x1768]; u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};
class DarkPokemon { public: s32 getInitDarkPointDirect() const; s32 getDarkPointDirect() const; };
class Pokemon { public: DarkPokemon* getDarkPokemon(); u8 isDarkPokemon() const; };
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFGetPredef(s32);
f32 timeGetLastFrameSec();
f64 sin(f64);
}
static f32 max_alpha  =  255.0f;
static f32 meterCount;
static void _menuDrawReliveMeterSub(DarkPokemon*, s32, s32, s32, s32, u8, GSgfxLayer*);
static void _menuDrawReliveMeterSubDpValue(s32, s32, s32, s32, s32, s32, u8, GSgfxLayer*);

inline void setup(GSgfxLayer* layer, u32 primitive) {
    layer->primitive  =  primitive;
    layer->colorCount  =  6;
    layer->colorMode  =  0;
    layer->flagsB |=  4; layer->flagsA |=  1;
    layer->flagsD |=  4; layer->flagsC |=  1;
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));
}
inline void vertex(s32 x, s32 y, const GXColor& c) {
    GXWGFifo.s16  =  x; GXWGFifo.s16  =  y;
    GXWGFifo.u8 = c.r; GXWGFifo.u8 = c.g; GXWGFifo.u8 = c.b; GXWGFifo.u8 = c.a;
}
inline void rect(GSgfxLayer* layer, s32 x0, s32 y0, s32 x1, s32 y1, GXColor c) {
    setup(layer, 0x80); layer->beginSurface(4);
    vertex(x0, y0, c); vertex(x1, y0, c); vertex(x1, y1, c); vertex(x0, y1, c);
    layer->endSurface();
}
inline void line(GSgfxLayer* layer, s32 x0, s32 y0, s32 x1, s32 y1, GXColor c) {
    setup(layer, 0xA8); layer->beginSurface(2);
    vertex(x0, y0, c); vertex(x1, y1, c); layer->endSurface();
}
extern "C" {
void menuDrawReliveMeter3(Pokemon* p, s32 x, s32 y, s32 w, s32 h, u8 alpha, s32 layerId) {
    GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
    if (layer) _menuDrawReliveMeterSub(p->getDarkPokemon(), x, y, w, h, alpha, layer);
}
void menuDrawReliveMeterByDarkPokemon(DarkPokemon* p, s32 x, s32 y, s32 w, s32 h, u8 alpha, s32 layerId) {
    GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
    if (layer) _menuDrawReliveMeterSub(p, x, y, w, h, alpha, layer);
}
void menuDrawReliveMeter(Pokemon* p, s32 w, s32 h, s32 layerId) {
    if (p->isDarkPokemon()) {
        GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
        if (layer) _menuDrawReliveMeterSub(p->getDarkPokemon(), 0, 0, w, h, 255, layer);
    }
}
void menuDrawReliveUpdate() {meterCount += timeGetLastFrameSec();}
}
static void _menuDrawReliveMeterSub(DarkPokemon* p, s32 x, s32 y, s32 w, s32 h, u8 alpha, GSgfxLayer* layer) {
    s32 initial = p->getInitDarkPointDirect();
    s32 current = p->getDarkPointDirect();
    _menuDrawReliveMeterSubDpValue(initial, current, x, y, w, h, alpha, layer);
}
static void _menuDrawReliveMeterSubDpValue(s32 initial, s32 current, s32 x, s32 y, s32 w, s32 h, u8 alpha, GSgfxLayer* layer) {
    s32 bars;
    if (initial == 0) return;
    s32 gap = 2;
    s32 scale = w*100/210;
    s32 width = scale*40/100;
    s32 height = (h*100/16)*14/100;
    GXColor color;
    if (scale < 50) gap /= 2;
    color.r = color.g = color.b = 0;
    color.a = alpha;
 // Black border enclosing five gauge segments.
    rect(layer, x, (u16)y, width*5+(gap*4+2+x), height+y+2, color);
    color.r = color.g = color.b = 117;
    color.a = alpha;
    s32 i;
    for (i = 0; i < 5; i++) rect(layer, i*(width+gap)+x+1, y+1, i*(width+gap)+x+1+width, height+y+1, color);
 // Filled bars use a purple body with lighter/darker horizontal edges.
    if (current) {
        s32 percent = current*100/initial;
        bars = percent/20+1;
        if (bars > 5) bars = 5;
        color.r = 134;
        color.g = 0;
        color.b = 225;
        color.a = alpha;
        for (i = 0; i < bars; i++) {
            s32 start = i*(width+gap)+1;
            color.r = 134;
            color.g = 0;
            color.b = 225;
            color.a = alpha;
            if (bars == i+1) {
                percent -= i*20;
                rect(layer, start+x, y+1, start+x+width*percent/20, height+y+1, color);
                color.r = 174;
                color.g = 54;
                color.b = 225;
                color.a = alpha;
                line(layer, start+x, y+2, start+x+width*percent/20, y+2, color);
                color.r = 108;
                color.g = 0;
                color.b = 181;
                color.a = alpha;
                line(layer, start+x, (int)(height+y)+1, start+x+width*percent/20, (int)(height+y)+1, color);
            } else {
                rect(layer, start+x, y+1, start+x+width, height+y+1, color);
                color.r = 174;
                color.g = 54;
                color.b = 225;
                color.a = alpha;
                line(layer, start+x, y+2, start+x+width, y+2, color);
                color.r = 108;
                color.g = 0;
                color.b = 181;
                color.a = alpha;
                line(layer, start+x, (int)(height+y)+1, start+x+width, (int)(height+y)+1, color);
            }
        }
    } else {
        color.r = color.g = color.b = 255;
 // When the gauge reaches zero, pulse the white meter with elapsed time.
        f32 a = 150.0f*(1.0f+(f32)sin(6.2831855f*meterCount));
        if (a >= max_alpha) a = max_alpha;
        u16 opacity = (u16)a*alpha/255;
        for (i = 0; i < 5; i++) {
            s32 start = i*(width+gap)+1;
            color.a = opacity;
            rect(layer, start+x, y+1, start+x+width, height+y+1, color);
            color.a = opacity*75/100;
            line(layer, start+x, y+1, start+x+width, y+1, color);
            line(layer, start+x+1, y+1, start+x+1, height+y+1, color);
            line(layer, start+(width+x), y+1, start+(width+x), height+y+1, color);
            line(layer, start+x, (int)(height+y)+1, start+x+width, (int)(height+y)+1, color);
        }
    }
}
