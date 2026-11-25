#include "types.h"
#define F3DEX_GBI_2
#include "PR/mbi.h"

/* Reconstructed segment-8 OtherMode/EndDL records.
 * Evidence: docs/evidence/data-layout/us_render_state_tables.md
 * Grouping does not claim original C-array boundaries or use of every slot.
 */
Gfx D_800838C0[24][2] = {
    { gsDPSetOtherMode(0x182CAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x182CAF, 0xC192278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ACAF, 0xC192278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x18ECAF, 0xC192278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x192CAF, 0xC192278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ACAF, 0xC192278), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC192078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC193078), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC192D58), gsSPEndDisplayList() },
    { gsDPSetOtherMode(0x19ECAF, 0xC192278), gsSPEndDisplayList() },
};
