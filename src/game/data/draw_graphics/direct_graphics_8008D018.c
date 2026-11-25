#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_8008D018[7] = {
    gsSPGeometryMode(0x3F0605, 0x0),
    gsSPGeometryMode(0x0, 0x200005),
    gsSPTexture(0, 0, 0, 0, 0),
    gsDPPipeSync(),
    gsDPSetCombine(GCCc0w0(15, 31, 7, 7) | GCCc1w0(15, 31), GCCc0w1(15, 4, 7, 4) | GCCc1w1(15, 7, 7, 4, 7, 4)),
    gsDPSetConvert(175, -33, 7, 222, 114, 42),
    gsSPEndDisplayList(),
};
