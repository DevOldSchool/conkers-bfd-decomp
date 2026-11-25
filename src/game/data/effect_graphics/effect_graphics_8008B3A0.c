#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008B3A0[7] = {
    gsSPGeometryMode(0x600, 0x0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(1, 3, 1, 3) | GCCc1w0(1, 3), GCCc0w1(15, 7, 7, 7) | GCCc1w1(15, 1, 3, 7, 7, 7)),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x1),
    gsDPSetBlendColor(0, 0, 0, 1),
    gsSPEndDisplayList(),
};
