#include <dolphin/types.h>

#pragma pool_strings off

extern "C" {

void GSlogWrite(const char* fmt, ...);

extern u32* table_res_number;
extern void** table_res;

void* tableResBiosGetResPtr(u32 index) {
    if (index >= *table_res_number) {
        GSlogWrite("[%s]: テーブルインデックスが範囲外です\n", __FUNCTION__);
        return NULL;
    }
    return table_res[index];
}

}
