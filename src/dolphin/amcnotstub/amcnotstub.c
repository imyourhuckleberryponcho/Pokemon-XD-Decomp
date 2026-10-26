#include <dolphin.h>

__declspec(weak) int AMC_IsStub(void);

__declspec(weak) int AMC_IsStub(void) {
    return 0;
}
