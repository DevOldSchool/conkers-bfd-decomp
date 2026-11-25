#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
/* The RSP command stores the physical alias of this matrix. */
extern Mtx D_80089470;

Gfx D_80084160[6] = {
    gsDPPipeSync(),
    gsSPMatrix((u32)&D_80089470 - 0x80000000U, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPGeometryMode(0x0, 0x620004),
    gsSPGeometryMode(0x110000, 0x0),
    gsDPSetConvert(0, 0, 0, 0, 0, 255),
    gsSPEndDisplayList(),
};
