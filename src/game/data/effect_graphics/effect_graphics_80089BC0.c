#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_80089BC0[9] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 12, 2, 0x2000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 19, 1, 0x80000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 9, 3, 0xC00),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 6, 2, 0x80),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 2, 0x20),
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(32768, 32768, 0, 0, 1),
    gsSPEndDisplayList(),
};

Gfx D_80089C08[2] = {
    gsSPTexture(0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
