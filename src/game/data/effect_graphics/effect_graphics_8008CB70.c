#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008CB70[4] = {
    gsSPDisplayList(D_800873D0),
    gsDPSetCombine(GCCc0w0(3, 1, 3, 1) | GCCc1w0(3, 1), GCCc0w1(5, 5, 7, 7) | GCCc1w1(5, 3, 1, 5, 7, 7)),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0x5049D8),
    gsSPEndDisplayList(),
};

Gfx D_8008CB90[2] = {
    gsSPDisplayList(D_80087408),
    gsSPEndDisplayList(),
};
