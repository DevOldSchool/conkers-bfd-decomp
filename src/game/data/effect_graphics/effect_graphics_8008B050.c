#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008B050[3] = {
    gsDPPipeSync(),
    gsSPTexture(32768, 32768, 0, 0, 1),
    gsSPEndDisplayList(),
};

Gfx D_8008B068[2] = {
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
