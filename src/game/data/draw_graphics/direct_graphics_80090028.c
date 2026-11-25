#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_80090028[6] = {
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombine(GCCc0w0(1, 5, 5, 1) | GCCc1w0(1, 5), GCCc0w1(15, 7, 7, 7) | GCCc1w1(15, 5, 1, 7, 7, 7)),
    gsDPSetOtherMode(0x2C3F, 0x504244),
    gsSPEndDisplayList(),
};
