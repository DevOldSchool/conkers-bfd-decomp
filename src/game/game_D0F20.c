#include "types.h"

/*
 * Reviewed source unit: src/game/game_D0F20.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A3A70
 * - func_150A3FC4
 * - func_150A43E0
 * - func_150A44F0
 * - func_150A4B04
 * - func_150A4FA0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A3A70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A3FC4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A43E0 CURRENT (7000) */
void func_150A43E0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A43E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A43E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A44F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A4B04.s")
s32 func_150A3BAC(u8 *, u8 *);
extern s16 D_800C5918[];
extern u8 D_800CC2D0;
extern u8 D_800D35DC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A4FA0 CURRENT (6700) */
s32 func_150A4FA0(void) {
    u8 *var_a2;
    s32 index;
    u8 *end;

    var_a2 = &D_800CC2D0;
    end = &D_800CC2D0 + 0x4F4C;
    index = -1;
loop_1:
    index++;
    if (var_a2 != end) {
        var_a2 += 0x32C;
        if ((index != (D_800D35DC - 1)) &&
            (*(s32 *)(var_a2 - 0x32C) != 0) &&
            (*(s32 *)(var_a2 - 0x234) & 0x4000) &&
            (*(s32 *)(var_a2 - 0xC8) != 0) &&
            (*(s32 *)(var_a2 - 0xC4) != 0) &&
            (D_800C5918[var_a2[-0x328]] != 0)) {
            return func_150A3BAC(var_a2, end);
        }
        goto loop_1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A4FA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0F20/func_150A4FA0.s")
