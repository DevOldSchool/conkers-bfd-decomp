#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Vtx D_8008CD90[6] = {
    {{ { 7, 4, 0 }, 0, { 9234, 8351 }, { 254, 254, 254, 255 } }},
    {{ { -7, 4, 0 }, 0, { 8200, 8334 }, { 254, 254, 254, 255 } }},
    {{ { 0, 1, 3 }, 0, { 8720, 8107 }, { 254, 254, 254, 255 } }},
    {{ { 7, 14, 0 }, 0, { 9202, 9040 }, { 254, 254, 254, 255 } }},
    {{ { -7, 14, 0 }, 0, { 8213, 9024 }, { 254, 254, 254, 255 } }},
    {{ { 0, 21, 4 }, 0, { 8698, 9694 }, { 254, 254, 254, 255 } }},
};

Gfx D_8008CDF0[6] = {
    gsSPVertex(D_8008CD90, 6, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(4, 1, 3, 0),
    gsSP1Triangle(5, 4, 3, 0),
    gsSPEndDisplayList(),
};

Gfx D_8008CE20[4] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0x5049D8),
    gsSPDisplayList(D_8008CE60),
    gsSPEndDisplayList(),
};

Gfx D_8008CE40[4] = {
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0x504240),
    gsSPDisplayList(D_8008CE60),
    gsSPEndDisplayList(),
};

Gfx D_8008CE60[9] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 20, 2, 0x0),
    gsDPSetCombine(GCCc0w0(1, 4, 1, 3) | GCCc1w0(1, 4), GCCc0w1(15, 7, 7, 7) | GCCc1w1(15, 1, 3, 7, 7, 7)),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 16, 1, 0x0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPGeometryMode(0x110600, 0x0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 12, 2, 0x2000),
    gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
