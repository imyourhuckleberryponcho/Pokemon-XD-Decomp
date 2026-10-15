#include <dolphin/types.h>

extern "C" {

s32 _menuToolSelect;

void menuToolSetSelect(s32 select) { _menuToolSelect = select; }

void menuToolInit(void) { _menuToolSelect = 0; }

}
