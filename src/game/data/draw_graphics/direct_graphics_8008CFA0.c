#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
/* The RSP command stores the physical alias of this matrix. */
extern Mtx D_80089470;

Gfx D_8008CFA0[9] = {
    gsSPMatrix((u32)&D_80089470 - 0x80000000U, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsDPPipeSync(),
    gsSPGeometryMode(0xFFFF, 0x0),
    gsSPGeometryMode(0x0, 0x100005),
    gsDPSetOtherMode(0x182C3F, 0xC184B50),
    gsDPSetCombine(GCCc0w0(1, 4, 7, 7) | GCCc1w0(0, 4), GCCc0w1(15, 7, 7, 2) | GCCc1w1(5, 0, 4, 3, 7, 7)),
    gsSPTexture(65535, 65535, 0, 1, 1),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPEndDisplayList(),
};
