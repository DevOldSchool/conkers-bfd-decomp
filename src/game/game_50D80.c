#include "types.h"

/*
 * Reviewed source unit: src/game/game_50D80.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150238D8
 * - func_15023BB0
 * - func_15023DE0
 * - func_15024130
 * - func_150241B4
 * - func_150242F8
 * - func_1502460C
 * - func_150265CC
 * - func_15029BB8
 * - func_1502A8A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150238D0(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150238D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15023BB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15023DE0.s")
void func_1502A8A0(s32, u8, u16, s32, s32);
extern s32 D_800C3D50;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15024130 CURRENT (564) */
void func_15024130(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 *var_s4;
    void *temp_v0;

    var_s0 = 0;
    if (arg0 > 0) {
        var_s4 = &D_800C3D50;
        var_s1 = 0;
        do {
            temp_v0 = (void *)((u8 *)(*var_s4) + var_s1);
            func_1502A8A0(*(s32 *)((u8 *)temp_v0 + 0), *(u8 *)((u8 *)temp_v0 + 8), *(u16 *)((u8 *)temp_v0 + 0xA), *(s32 *)((u8 *)temp_v0 + 4), arg1);
            var_s0 += 1;
            var_s1 += 0xC;
        } while (var_s0 != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15024130 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15024130.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150241B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150242F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502460C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150265CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15029BB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502A8A0.s")
