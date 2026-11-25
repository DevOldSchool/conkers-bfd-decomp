#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_800889E0[4] = {
    gsDPPipeSync(),
    gsSPGeometryMode(0x20600, 0x0),
    gsDPSetCombine(GCCc0w0(15, 31, 7, 7) | GCCc1w0(15, 31), GCCc0w1(15, 1, 7, 1) | GCCc1w1(15, 7, 7, 1, 7, 1)),
    gsSPEndDisplayList(),
};
