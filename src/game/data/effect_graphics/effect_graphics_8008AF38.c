#include "game_effect_graphics.h"

/* Source-only reconstruction of this bounded native data range.
 * Evidence: docs/evidence/data-layout/us_effect_graphics.md
 */

Gfx D_8008AF38[9] = {
    gsDPPipeSync(),
    gsSPVertex(D_800A6170, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_8008AF80[7] = {
    gsDPPipeSync(),
    gsSPVertex(D_800A61C0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(2, 3, 0, 0),
    gsSPEndDisplayList(),
};

/* Only selectors 0..3 are established by the native producer.
 * The following pointer and its geometry are deliberately excluded.
 */

Gfx * D_8008AFB8[4] = {
    D_8008AE60,
    D_8008AEA8,
    D_8008AF38,
    D_8008AF80,
};
