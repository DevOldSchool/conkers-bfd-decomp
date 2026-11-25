#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008A470[5] = {
    gsDPPipeSync(),
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(32768, 32768, 0, 0, 1),
    gsDPSetConvert(0, 0, 0, 0, 0, 255),
    gsSPEndDisplayList(),
};

Gfx D_8008A498[5] = {
    gsDPPipeSync(),
    gsSPTexture(0, 0, 0, 0, 0),
    gsDPPipeSync(),
    gsDPSetConvert(175, -33, 7, 222, 114, 42),
    gsSPEndDisplayList(),
};
