#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Evidence: docs/evidence/data-layout/us_scene_ui.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Both terminated lists are submitted by the native UI model renderer. */
Gfx D_80090110[3] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, 0, G_ON),
    gsSPEndDisplayList(),
};

Gfx D_80090128[2] = {
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};
