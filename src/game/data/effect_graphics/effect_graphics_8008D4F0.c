#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008D4F0[6] = {
    gsSPTexture(0, 0, 0, 0, 0),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(3, 4, 3, 4) | GCCc1w0(3, 4), GCCc0w1(15, 7, 7, 7) | GCCc1w1(15, 3, 4, 7, 7, 7)),
    gsSPGeometryMode(0x20600, 0x0),
    gsDPSetOtherMode(0x82CAF, 0x504A50),
    gsSPEndDisplayList(),
};

Gfx D_8008D520[3] = {
    gsSPMatrix(&D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Vtx D_8008D538[4] = {
    {{ { -625, 0, 0 }, 0, { 0, 0 }, { 255, 255, 255, 16 } }},
    {{ { 625, 31, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } }},
    {{ { 625, -31, 31 }, 0, { 0, 0 }, { 255, 255, 255, 255 } }},
    {{ { 625, -31, -31 }, 0, { 0, 0 }, { 255, 255, 255, 255 } }},
};
