#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

#define INTEGER_PAIR(a, b) (((u32)(u16)(a) << 16) | (u16)(b))

Mtx D_80089470 = { {
    { INTEGER_PAIR(1, 0), INTEGER_PAIR(0, 0), INTEGER_PAIR(0, 1), INTEGER_PAIR(0, 0) },
    { INTEGER_PAIR(0, 0), INTEGER_PAIR(1, 0), INTEGER_PAIR(0, 0), INTEGER_PAIR(0, 1) },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
} };

#undef INTEGER_PAIR
