#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008B480[3] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPGeometryMode(0x130600, 0x0),
    gsSPEndDisplayList(),
};

Gfx D_8008B498[2] = {
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPEndDisplayList(),
};
