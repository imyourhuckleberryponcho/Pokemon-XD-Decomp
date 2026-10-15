#ifndef HSD_COMPAT_H
#define HSD_COMPAT_H

// XD: names the Melee headers use that XD's Dolphin SDK headers spell differently.
#include <dolphin/mtx.h>

// Use the explicit line numbers in HSD_ASSERT (as the Melee decomp does when matching).
#ifndef MUST_MATCH
#define MUST_MATCH
#endif

typedef Vec Vec3;

#endif
