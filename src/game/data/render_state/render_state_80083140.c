#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Reconstructed segment-8 OtherMode/EndDL records.
 * Evidence: docs/evidence/data-layout/us_render_state_tables.md
 * Grouping does not claim original C-array boundaries or use of every slot.
 */
Gfx D_80083140[24][2] = {
    { gsDPSetOtherMode(0x182C3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182C3F, 0x4D12278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18AC3F, 0x4D12278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18EC3F, 0x4D12278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192C3F, 0x4D12278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19AC3F, 0x4D12278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x4D12078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x4D13078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x4D12D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19EC3F, 0x4D12278), gsSPEndDisplayList() },
};
