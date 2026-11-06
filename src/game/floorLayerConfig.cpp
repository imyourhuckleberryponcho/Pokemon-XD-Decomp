#include <dolphin/types.h>
#include <game/gcptr.h>

#pragma peephole off
#pragma pool_strings off

enum GSgfxLayerPass {};
enum GSgfxLayerOffset {};

struct _GSgfxLayerData {
    s32 id;
    const char* name;
    u32 unk8;
    bool clearColor;
    bool clearAlpha;
    bool clearDepth;
    bool visible;
    u32 width;
    u32 height;
    u32 format;
};

enum GSgfxLayerID {};
enum GSgfxLayerType {};
#include <game/gsgfxlayer.h>

struct GSgfxLayer : public GSgfxLayerData {
public:
    void SetPassRedirect(GSgfxLayerPass pass, bool enable, GSgfxLayer* target, GSgfxLayerPass targetPass,
                         GSgfxLayerOffset offset);
};

class GSgfxLayerConfig {
public:
    static void Setup(_GSgfxLayerData* data);
};

struct FloorLayerConfig {
    _GSgfxLayerData* config;
    u32 floorID;
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(GCsptr id);
s32 GSgfxLayerFindByName_C(const char* name);
void dbgMenuSetLayerID(s32 id);
}

static const char* g_layer_names[] = {
    "background", "background distortion", "main", "main distortion",
    "secondary", "secondary distortion", "filter", "menu",
};

#define LAYER(id) id, g_layer_names[id]
#define LAYER_END {-1, 0, 0, LAYER_FLAGS(0), 0, 0, 0}
#define LAYER_FLAGS(v) (bool)(((v) >> 24) & 0xFF), (bool)(((v) >> 16) & 0xFF), (bool)(((v) >> 8) & 0xFF), (bool)((v) & 0xFF)

static _GSgfxLayerData _empty_layer_config[] = {
    {LAYER(2), 0, LAYER_FLAGS(1), 0x50000, 0x50000, 0x10},
    LAYER_END,
};

static _GSgfxLayerData _map_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x60000, 0x30000, 0x10},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x50000, 0x50000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x10000, 0x20000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x2000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0, 0x18000, 8},
    LAYER_END,
};

static _GSgfxLayerData _fight_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x40000, 0x40000, 0x10},
    {LAYER(1), 1, LAYER_FLAGS(0), 0, 0x20000, 0x10},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x80000, 0x50000, 0x10},
    {LAYER(3), 1, LAYER_FLAGS(0), 0, 0x10000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x20000, 0x84800, 0x10},
    {LAYER(5), 1, LAYER_FLAGS(0), 0, 0x14000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x4000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0, 0x20000, 0x10},
    LAYER_END,
};

static _GSgfxLayerData _menu_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x40000, 0x40000, 0x20},
    {0xFF, "menu extra", 0, LAYER_FLAGS(0x101), 0x20000, 0x40000, 0x10},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x50000, 0x50000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x10000, 0x40000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x2000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0x20000, 0x40000, 0x10},
    LAYER_END,
};

static _GSgfxLayerData _evolution_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x40000, 0x40000, 0x20},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x50000, 0x50000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x40000, 0x40000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x2000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0x20000, 0x40000, 0x10},
    LAYER_END,
};

static _GSgfxLayerData _M6_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x70000, 0x30000, 0x10},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x50000, 0x50000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x10000, 0x20000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x2000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0, 0x18000, 8},
    LAYER_END,
};

static _GSgfxLayerData _M6_out_bf_layer_config[] = {
    {LAYER(0), 0, LAYER_FLAGS(1), 0x50000, 0x40000, 0x10},
    {LAYER(1), 1, LAYER_FLAGS(0), 0, 0x20000, 0x10},
    {LAYER(2), 0, LAYER_FLAGS(1), 0x80000, 0x50000, 0x10},
    {LAYER(3), 1, LAYER_FLAGS(0), 0, 0x10000, 0x10},
    {LAYER(4), 0, LAYER_FLAGS(0x101), 0x20000, 0x84800, 0x10},
    {LAYER(5), 1, LAYER_FLAGS(0), 0, 0x14000, 0x10},
    {LAYER(6), 0, LAYER_FLAGS(1), 0, 0x4000, 1},
    {LAYER(7), 0, LAYER_FLAGS(1), 0, 0x20000, 0x10},
    LAYER_END,
};

static FloorLayerConfig _floor_layer_config_list[] = {
    {_M6_layer_config, 0x99},
    {_M6_out_bf_layer_config, 0x21E},
    {_evolution_layer_config, 0x386},
};

static _GSgfxLayerData* g_empty_layer_config = _empty_layer_config;
static _GSgfxLayerData* g_map_layer_config = _map_layer_config;
static _GSgfxLayerData* g_fight_layer_config = _fight_layer_config;
static _GSgfxLayerData* g_menu_layer_config = _menu_layer_config;
static FloorLayerConfig* g_floor_layer_config_list = _floor_layer_config_list;
static u32 g_floor_layer_config_count = 3;

static s32 _menu_extra_layer_id;

extern "C" {

void floorLayerConfigLoad(void) {}

s32 floorGetMenuLayerID(void) {
    return _menu_extra_layer_id;
}

void floorLayerConfig(u32 floorID, u8 kind) {
    u32 i;
    for (i = 0; i < g_floor_layer_config_count; i++) {
        if (floorID == g_floor_layer_config_list[i].floorID) {
            GSgfxLayerConfig::Setup(g_floor_layer_config_list[i].config);
            dbgMenuSetLayerID(GSgfxLayerFindByName_C("debug menu"));
            return;
        }
    }
    switch (kind) {
    case 5:
    case 6:
        GSgfxLayerConfig::Setup(g_menu_layer_config);
        _menu_extra_layer_id = GSgfxLayerFindByName_C("menu extra");
        break;
    case 7:
        GSgfxLayerConfig::Setup(g_menu_layer_config);
        _menu_extra_layer_id = GSgfxLayerFindByName_C("menu");
        break;
    case 1:
        GSgfxLayerConfig::Setup(g_map_layer_config);
    {
        GSgfxLayer* background = GSgfxLayerFindByID(0);
        GSgfxLayer* mainLayer = GSgfxLayerFindByID(2);
        background->SetPassRedirect((GSgfxLayerPass)1, true, mainLayer, (GSgfxLayerPass)0, (GSgfxLayerOffset)2);
    }
        break;
    case 2:
    case 4:
        GSgfxLayerConfig::Setup(g_fight_layer_config);
        break;
    default:
        GSgfxLayerConfig::Setup(g_empty_layer_config);
        break;
    }
    dbgMenuSetLayerID(GSgfxLayerFindByName_C("debug menu"));
}

}
