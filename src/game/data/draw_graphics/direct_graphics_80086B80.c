#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_80086B80[4] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(15, 31, 7, 7) | GCCc1w0(15, 31), GCCc0w1(15, 1, 7, 1) | GCCc1w1(15, 7, 7, 1, 7, 1)),
    gsSPEndDisplayList(),
};
