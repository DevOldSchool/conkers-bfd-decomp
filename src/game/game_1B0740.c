#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B0740.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15183290
 * - func_151838B0
 * - func_15183974
 * - func_151839F0
 * - func_15183ACC
 * - func_15183BA4
 * - func_15183C28
 * - func_15183D28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183290.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_151838B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_151839F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183ACC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183C28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183D28.s")
s32 func_15184118(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x57) != 0)) {
        return 1;
    }
    return 0;
}
