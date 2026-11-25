#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008AE60[9] = {
    gsDPPipeSync(),
    gsSPVertex(D_800A6080, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_8008AEA8[7] = {
    gsDPPipeSync(),
    gsSPVertex(D_800A60D0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(2, 3, 0, 0),
    gsSPEndDisplayList(),
};
