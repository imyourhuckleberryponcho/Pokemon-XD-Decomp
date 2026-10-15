#include <dolphin/types.h>

enum GSgfxLayerID {};
enum GSgfxLayerOffset {
    LAYER_OFFSET_NONE = 0,
    LAYER_OFFSET_ABOVE = 1,
    LAYER_OFFSET_BELOW = 2,
    LAYER_OFFSET_TOP = 3,
    LAYER_OFFSET_BOTTOM = 4,
};
enum GSgfxLayerType {};

struct _GSgfxLayerData {
    GSgfxLayerID id;
    char* name;
    GSgfxLayerType type;
    bool clearColor;
    bool clearAlpha;
    bool clearDepth;
    bool visible;
    u32 width;
    u32 height;
    u32 count;
};

struct GSgfxLayerVec {
    u8* first;
    u8* unk4;
    u8* last;
};

class GSgfxLayer {
public:
    GSgfxLayer(GSgfxLayerID id, char* name, u32 width, u32 height, u32 count, GSgfxLayerType type);
    ~GSgfxLayer();
    static GSgfxLayer* GetLayerList();
    void SetPriority(GSgfxLayerOffset offset, GSgfxLayer* relative);
    void SetLayerType(GSgfxLayerType type);
    void SetWantClearFlags(bool color, bool alpha, bool depth);
    void SetPassVisibility(bool a, bool b);
    void SetLayerVisibility(bool visible);

    GSgfxLayer* next;
    u8 unk4[0x24];
    GSgfxLayerID id;
    u8 unk2C[0x181C - 0x2C];
    u32 width;
    u8 unk1820[0x18D8 - 0x1820];
    u32 height;
    u8 unk18DC[0x19A0 - 0x18DC];
    GSgfxLayerVec* items;
    u8 unk19A4[0x19B3 - 0x19A4];
    u8 unk19B3;
    u8 unk19B4[0x1A14 - 0x19B4];
};

class GSgfxLayerConfig {
public:
    static void Move(GSgfxLayerID id, GSgfxLayerID relative, GSgfxLayerOffset offset);
    static void Remove(GSgfxLayerID id);
    static GSgfxLayerID Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                            bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset);
    static void Setup(_GSgfxLayerData* data);
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByName(char* name);
void GSgfxLayerSetActive(GSgfxLayerID id);
}

#define ROUND_UP_32(x) (((x) + 31) & ~31)

static inline GSgfxLayer* FindLayer(GSgfxLayerID id) {
    GSgfxLayer* layer;
    for (layer = GSgfxLayer::GetLayerList(); layer != NULL; layer = layer->next) {
        if (layer->id == id) {
            return layer;
        }
    }
    return NULL;
}

// Layer IDs 8-15 are handed out to layers created at run time.
static inline GSgfxLayerID FindFreeID() {
    u32 id;
    for (id = 8; id < 16; id++) {
        bool used = false;
        GSgfxLayer* layer;
        for (layer = GSgfxLayer::GetLayerList(); layer != NULL; layer = layer->next) {
            if (id == layer->id) {
                used = true;
                break;
            }
        }
        if (!used) {
            return (GSgfxLayerID)id;
        }
    }
    return (GSgfxLayerID)-1;
}

void GSgfxLayerConfig::Move(GSgfxLayerID id, GSgfxLayerID relative, GSgfxLayerOffset offset) {
    GSgfxLayer* layer = FindLayer(id);
    if (layer != NULL) {
        GSgfxLayer* rel = FindLayer(relative);
        if (rel == NULL) {
            switch (offset) {
            case LAYER_OFFSET_ABOVE:
                offset = LAYER_OFFSET_TOP;
                break;
            case LAYER_OFFSET_BELOW:
                offset = LAYER_OFFSET_BOTTOM;
                break;
            }
        }
        layer->SetPriority(offset, rel);
    }
}

void GSgfxLayerConfig::Remove(GSgfxLayerID id) {
    GSgfxLayer* layer = FindLayer(id);
    if (layer != NULL) {
        delete layer;
    }
}

GSgfxLayerID GSgfxLayerConfig::Add(char* name, u32 width, u32 height, u32 count, GSgfxLayerType type, bool clearColor,
                                   bool clearAlpha, bool clearDepth, GSgfxLayerID relative, GSgfxLayerOffset offset) {
    static _GSgfxLayerData data;
    GSgfxLayer* layer = GSgfxLayerFindByName(name);
    GSgfxLayer* rel;

 // Recreate a layer of the same name if its size changed.
    if (layer != NULL) {
        if (ROUND_UP_32(width) != layer->width || ROUND_UP_32(height) != layer->height ||
            ROUND_UP_32(count) != ((u32)layer->items->last - (u32)layer->items->first) / 0x30 + 1) {
            delete layer;
            layer = NULL;
        }
    }
    if (layer == NULL) {
        GSgfxLayerID newID = FindFreeID();
        if (newID != -1) {
            layer = new GSgfxLayer(newID, name, width, height, count, (GSgfxLayerType)0);
        }
        if (layer == NULL) {
            return (GSgfxLayerID)-1;
        }
    }

    data.id = layer->id;
    data.name = name;
    data.type = type;
    data.clearColor = clearColor;
    data.clearAlpha = clearAlpha;
    data.clearDepth = clearDepth;
    data.visible = true;
    data.width = width;
    data.height = height;
    data.count = count;

    rel = FindLayer(relative);
    layer->SetLayerType(data.type);
    layer->SetWantClearFlags(data.clearColor, data.clearAlpha, data.clearDepth);
    if (rel != NULL) {
        layer->SetPriority(offset, rel);
    } else {
        switch (offset) {
        case LAYER_OFFSET_ABOVE:
        case LAYER_OFFSET_TOP:
            layer->SetPriority(LAYER_OFFSET_TOP, NULL);
            break;
        case LAYER_OFFSET_BELOW:
        case LAYER_OFFSET_BOTTOM:
            layer->SetPriority(LAYER_OFFSET_BOTTOM, NULL);
            break;
        default:
            layer->SetPriority(LAYER_OFFSET_NONE, NULL);
            break;
        }
    }
    layer->SetPassVisibility(true, true);
    layer->unk19B3 = false;
    layer->SetLayerVisibility(data.visible);
    return layer->id;
}

// Replaces all layers with the ones in the table (terminated by id -1).
void GSgfxLayerConfig::Setup(_GSgfxLayerData* data) {
    GSgfxLayer* layer;
    GSgfxLayer* prev;
    _GSgfxLayerData* cur;

    layer = GSgfxLayer::GetLayerList();
    while (layer != NULL) {
        GSgfxLayer* next = layer->next;
        delete layer;
        layer = next;
    }

    cur = data;
    prev = NULL;
    while (cur->id != -1) {
        layer = FindLayer(cur->id);
        if (layer == NULL) {
            if (cur->id == 0xFF) {
                GSgfxLayerID newID = FindFreeID();
                if (newID != -1) {
                    layer = new GSgfxLayer(newID, cur->name, cur->width, cur->height, cur->count, (GSgfxLayerType)0);
                }
            } else {
                layer = new GSgfxLayer(cur->id, cur->name, cur->width, cur->height, cur->count, (GSgfxLayerType)0);
            }
            if (layer == NULL) {
                cur++;
                continue;
            }
        }
        layer->SetLayerType(cur->type);
        layer->SetWantClearFlags(cur->clearColor, cur->clearAlpha, cur->clearDepth);
        if (prev != NULL) {
            layer->SetPriority(LAYER_OFFSET_BELOW, prev);
        } else {
            layer->SetPriority(LAYER_OFFSET_BOTTOM, NULL);
        }
        layer->SetPassVisibility(true, true);
        layer->unk19B3 = false;
        layer->SetLayerVisibility(cur->visible);
        prev = layer;
        cur++;
    }
    GSgfxLayerSetActive(GSgfxLayer::GetLayerList()->id);
}
