#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008CC30[5] = {
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPGeometryMode(0x110600, 0x0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8008CC58[3] = {
    gsSPGeometryMode(0x0, 0x400),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
