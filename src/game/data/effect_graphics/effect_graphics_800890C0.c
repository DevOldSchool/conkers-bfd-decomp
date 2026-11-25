#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_800890C0[12] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPGeometryMode(0x130200, 0x0),
    gsSPGeometryMode(0x0, 0x400),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(15, 31, 1, 3) | GCCc1w0(15, 31), GCCc0w1(15, 3, 7, 7) | GCCc1w1(15, 1, 3, 3, 7, 7)),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 0),
    gsDPSetEnvColor(0, 0, 0, 0),
    gsDPSetTile(4, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(4, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 252),
    gsDPSetOtherMode(0x82C3F, 0x504DD8),
    gsSPEndDisplayList(),
};
