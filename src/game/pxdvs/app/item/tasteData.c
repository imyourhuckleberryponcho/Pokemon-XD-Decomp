#include <dolphin/types.h>

// Per-nature flavor preference: -1 dislikes, 0 neutral, 1 likes.
typedef struct TasteData {
    u32 msgId;
    s8 nature[25];
    u8 pad[3];
} TasteData;

TasteData taste_data[] = {
    {0x00004FC3, {0, 1, 1, 1, 1, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0}},
    {0x00004FC4, {0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 1, 1, 1, 0, 1, 0, 0, 0, -1, 0}},
    {0x00004FC5, {0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 1, 1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0}},
    {0x00004FC6, {0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 1, 1, 1, 1, 0}},
    {0x00004FC7, {0, -1, 0, 0, 0, 1, 0, 1, 1, 1, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0}},
};

u32 taste_data_number = sizeof(taste_data) / sizeof(taste_data[0]);
