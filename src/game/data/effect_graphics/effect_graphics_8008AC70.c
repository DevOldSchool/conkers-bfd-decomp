#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008AC70[5] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x0),
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(32768, 32768, 0, 0, 1),
    gsSPEndDisplayList(),
};

Gfx D_8008AC98[6] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 19, 1, 0x80000),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 2, 1, 0x0),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x0),
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
