#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_800873D0[7] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(15, 31, 3, 1) | GCCc1w0(15, 31), GCCc0w1(15, 1, 7, 7) | GCCc1w1(15, 3, 1, 1, 7, 7)),
    gsDPSetBlendColor(0, 0, 0, 32),
    gsSPGeometryMode(0x110000, 0x0),
    gsDPSetOtherMode(0x2C0F, 0x55307C),
    gsSPEndDisplayList(),
};

Gfx D_80087408[1] = {
    gsSPEndDisplayList(),
};
