#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Vtx D_8008B3E0[6] = {
    {{ { -400, -34, -40 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { -400, -34, 40 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { -400, 34, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 0, -34, -40 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 0, -34, 40 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 0, 34, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
};

Gfx D_8008B440[7] = {
    gsSPGeometryMode(0x0, 0x400),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(15, 31, 7, 7) | GCCc1w0(15, 31), GCCc0w1(15, 1, 7, 1) | GCCc1w1(15, 7, 7, 1, 7, 1)),
    gsDPSetBlendColor(0, 0, 0, 1),
    gsDPSetOtherMode(0x82CAF, 0x504B50),
    gsSPEndDisplayList(),
};
