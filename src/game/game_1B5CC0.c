#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5CC0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15188810
 * - func_1518894C
 * - func_15188A58
 * - func_15188AD0
 * - func_15188B74
 * - func_15188D00
 * - func_15188E48
 * - func_15188F84
 * - func_15189118
 * - func_151895A4
 * - func_151895CC
 * - func_151895F4
 * - func_151897A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188810.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_1518894C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15188A58 CURRENT (55) */
void func_15188A58(void *arg0, void **arg1) {
    void *temp_v0;
    void *var_a1;
    void *var_v1;

    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    temp_v0 = *arg1;
    if (temp_v0 != 0) {
        var_a1 = *(void **)((u8 *)temp_v0 + 0xC);
        var_v1 = temp_v0;
        if (var_a1 != 0) {
            do {
                var_v1 = var_a1;
                var_a1 = *(void **)((u8 *)var_a1 + 0xC);
            } while (var_a1 != 0);
        }
        *(void **)((u8 *)var_v1 + 0xC) = arg0;
        return;
    }
    *arg1 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15188A58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188A58.s")
extern void *D_800DF7C8;

void func_15188A9C(s32 arg0) {
    void *var_v0;

    var_v0 = D_800DF7C8;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s32 *)((u8 *)var_v0 + 0x10)) {
                *(s16 *)((u8 *)var_v0 + 6) = 0;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 0xC);
        } while (var_v0 != 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188AD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188B74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188E48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188F84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15189118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151895A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151895CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151895F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151897A4.s")
void func_151898C0(s32 arg0, s32 arg1) {
    void *var_v0;

    var_v0 = D_800DF7C8;
    if (var_v0 != 0) {
loop_1:
        if (arg0 == *(s32 *)((u8 *)var_v0 + 0x10)) {
            *(s32 *)((u8 *)var_v0 + 0x14) = arg1;
            return;
        }
        var_v0 = *(void **)((u8 *)var_v0 + 0xC);
        if (var_v0 == 0) {

        } else {
            goto loop_1;
        }
    }
}
