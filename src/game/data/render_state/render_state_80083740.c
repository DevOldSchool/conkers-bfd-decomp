#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Reconstructed segment-8 OtherMode/EndDL records.
 * Evidence: docs/evidence/data-layout/us_render_state_tables.md
 * Grouping does not claim original C-array boundaries or use of every slot.
 */
Gfx D_80083740[24][2] = {
    { gsDPSetOtherMode(0x182CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC1849D8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC184DD8), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC1849D8), gsSPEndDisplayList() },
};
