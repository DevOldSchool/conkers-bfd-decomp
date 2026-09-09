#include "types.h"

/*
 * Reviewed source unit: src/game/game_AC030.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507EB80
 * - func_1507EBB8
 * - func_1507EC38
 * - func_1507EE58
 * - func_1507EEB8
 * - func_1507EEF4
 * - func_1507EFD0
 * - func_1507F454
 * - func_1507F54C
 * - func_1507F640
 * - func_1507FC2C
 * - func_1507FEA0
 * - func_1507FF94
 * - func_1507FFD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(u32);
extern s32 D_800BE9F0;

#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EB80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EBB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EC38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EE58.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 CURRENT (525) */
void func_1507EEB8(s32 arg0, u8 *arg1) {
    u8 temp_t7;
    u8 *temp_v0;

    temp_v0 = (void *)(arg1 + 4);
    temp_t7 = *(u8 *)((u8 *)temp_v0 + -1);
    *(u8 *)((u8 *)temp_v0 + -1) = (u8) *(u8 *)((u8 *)temp_v0 + -2);
    *(u8 *)((u8 *)temp_v0 + -2) = (u8) *(u8 *)((u8 *)temp_v0 + -3);
    *(u8 *)((u8 *)temp_v0 + -3) = (u8) *(u8 *)((u8 *)temp_v0 + -4);
    *(u8 *)((u8 *)arg1 + 4) = temp_t7;
    *(s8 *)((u8 *)arg1 + 0) = (s8) (arg0 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507EEB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EEF4.s")
void func_1507EFA0(s32 arg0, u8 *arg1) {
    s32 var_v0;
    u8 *var_v1;

    var_v0 = 4;
    var_v1 = arg1 + 4;
loop_1:
    var_v0 -= 1;
    if (arg0 == *var_v1) {
        *var_v1 = 0;
        return;
    }
    var_v1 -= 1;
    if (var_v0 < 0) {
        return;
    }
    goto loop_1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507EFD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F454.s")
s32 func_1507F4C0(s32 arg0) {
    s32 sp20;
    s32 var_v1;
    u32 var_a0;
    u32 sp1C;

    if (arg0 == 0) {
        var_v1 = 0xB4;
        var_a0 = 0x3C;
        goto block_7;
    }
    if (D_800BE9F0 == 0x31) {
        return 0;
    }
    var_v1 = 0;
    if (arg0 == 1) {
        var_v1 = 0x3C;
        var_a0 = 0x3C;
    } else {
        var_a0 = 0x1E;
    }
block_7:
    sp20 = var_v1;
    sp1C = var_a0;
    return (func_150ADA20(var_a0) % var_a0) + var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507F640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FC2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FEA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FF94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AC030/func_1507FFD8.s")
