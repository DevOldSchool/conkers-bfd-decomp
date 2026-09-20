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
extern u16 D_800C3C9A;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150241B4 CURRENT (1735) */
void func_150241B4(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 *var_v0_2;
    s32 temp_a0;
    s32 temp_at;
    s32 temp_s0;
    s32 var_a0;
    s32 var_a2;
    u8 *temp_v0;
    u8 *var_v0;
    u8 *var_v1;

    temp_s0 = *arg1;
    var_a2 = temp_s0;
    if (temp_s0 >= (s32) D_800C3C9A) {
        func_15024130(temp_s0, arg6);
        *arg1 = 0;
        return;
    }
    var_a0 = 0;
    if (temp_s0 > 0) {
        var_v0 = arg0;
loop_4:
        if (*(s32 *)((u8 *)var_v0 + 4) >= arg5) {
            var_a2 = var_a0;
        } else {
            var_a0 += 1;
            var_v0 += 0xC;
            if (var_a0 < temp_s0) {
                goto loop_4;
            }
        }
    }
    temp_a0 = temp_s0 - 1;
    if (temp_a0 >= var_a2) {
        var_v0_2 = (void *)(arg0 + (temp_a0 * 0xC));
        var_v1 = (void *)(var_v0_2 + 0xC);
        do {
            temp_at = *var_v0_2;
            var_v1 -= 0xC;
            var_v0_2 -= 0xC;
            *(s32 *)((u8 *)var_v1 + 0xC) = temp_at;
            *(s32 *)((u8 *)var_v1 + 0x10) = (s32) *(s32 *)((u8 *)var_v0_2 + 0x10);
            *(s32 *)((u8 *)var_v1 + 0x14) = (s32) *(s32 *)((u8 *)var_v0_2 + 0x14);
        } while ((u32) var_v1 >= (u32) ((var_a2 * 0xC) + arg0 + 0xC));
    }
    temp_v0 = (void *)(arg0 + (var_a2 * 0xC));
    *(s32 *)((u8 *)temp_v0 + 0) = arg2;
    *(s8 *)((u8 *)temp_v0 + 8) = (s8) arg3;
    *(s32 *)((u8 *)temp_v0 + 4) = arg5;
    *(s16 *)((u8 *)temp_v0 + 0xA) = (s16) arg4;
    *arg1 += 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150241B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150241B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150242F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502460C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150265CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15029BB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502A8A0.s")
