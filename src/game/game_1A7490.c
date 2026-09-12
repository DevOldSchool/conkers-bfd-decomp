#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A7490.c
 * Boundary evidence: docs/evidence/game_raw_quad_actor_effect_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15179FE0
 * - func_1517A1EC
 * - func_1517A3A0
 * - func_1517A644
 * - func_1517A84C
 * - func_1517A958
 * - func_1517A9A8
 * - func_1517AA20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_15179FE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A1EC.s")
s32 func_1517A394(s32 arg0) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A3A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A84C.s")
extern s16 D_800DD450;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A958 CURRENT (115) */
s32 func_1517A958(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a0;

    var_a0 = arg0;
    D_800DD450 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        var_a0 = func_1517A394(var_a0);
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A958 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A9A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517AA20.s")
void func_1510B7B4(s32 arg0, s32 arg1);

void func_1517AB7C(s32 arg0, s32 arg1, s16 arg2) {
    func_1510B7B4(arg0, arg2);
}
