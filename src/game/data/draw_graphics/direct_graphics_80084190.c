#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_80084190[5] = {
    gsDPPipeSync(),
    gsSPGeometryMode(0x570000, 0x0),
    gsDPSetEnvColor(0, 0, 0, 0),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
    gsSPEndDisplayList(),
};
