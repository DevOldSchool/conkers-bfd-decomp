#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Native directly submitted display list.
 * Evidence: docs/evidence/data-layout/us_model_draw_data.md
 */
extern Mtx D_80089470;

Gfx D_8008D448[10] = {
    gsDPSetFillColor(0xFFFFFFFF),
    gsDPSetOtherMode(0x302C3F, 0x0),
    gsSPGeometryMode(0x2F0001, 0x0),
    gsDPSetScissorFrac(0, 0, 0, 260, 260),
    gsDPFillRectangle(0, 0, 63, 63),
    gsDPPipeSync(),
    gsDPSetScissorFrac(0, 4, 4, 252, 252),
    gsSPTexture(65535, 65535, 0, 0, 0),
    gsDPSetOtherMode(0x82C3F, 0x0),
    gsSPEndDisplayList(),
};
