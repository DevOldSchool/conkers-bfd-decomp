#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_800859A0[5] = {
    gsDPPipeSync(),
    gsDPSetOtherMode(0x2C0F, 0x504244),
    gsDPSetTile(4, 2, 0, 0, 1, 0, 2, 0, 0, 2, 0, 0),
    gsDPSetCombine(GCCc0w0(15, 31, 3, 1) | GCCc1w0(15, 31), GCCc0w1(15, 3, 7, 7) | GCCc1w1(15, 3, 1, 3, 7, 7)),
    gsSPEndDisplayList(),
};
