#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_80084350[6] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsSPGeometryMode(0x170600, 0x0),
    gsDPSetCombine(GCCc0w0(1, 4, 7, 7) | GCCc1w0(1, 4), GCCc0w1(15, 7, 7, 4) | GCCc1w1(15, 7, 7, 7, 7, 4)),
    gsDPSetOtherMode(0x82C3F, 0x552230),
    gsSPEndDisplayList(),
};
