#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Reconstructed segment-8 OtherMode/EndDL records.
 * Evidence: docs/evidence/data-layout/us_render_state_tables.md
 * Grouping does not claim original C-array boundaries or use of every slot.
 */
Gfx D_800832C0[24][2] = {
    { gsDPSetOtherMode(0x182C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x7C27008), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x7C24000), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x7C24000), gsSPEndDisplayList() },
};
