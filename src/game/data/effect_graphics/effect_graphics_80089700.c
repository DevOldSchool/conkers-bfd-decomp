#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_80089700[6] = {
    gsDPPipeSync(),
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x0),
    gsDPSetBlendColor(0, 0, 0, 32),
    gsSPEndDisplayList(),
};

Gfx D_80089730[6] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x0),
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPGeometryMode(0xF0000, 0x0),
    gsSPGeometryMode(0x0, 0x200005),
    gsSPEndDisplayList(),
};
