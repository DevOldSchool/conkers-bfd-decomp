#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008A1D0[4] = {
    gsDPPipeSync(),
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(32768, 32768, 0, 0, 1),
    gsSPEndDisplayList(),
};

Gfx D_8008A1F0[2] = {
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
