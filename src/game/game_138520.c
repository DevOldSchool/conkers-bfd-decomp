#include "types.h"

/*
 * Reviewed source unit: src/game/game_138520.c
 * Boundary evidence: docs/evidence/game_raw_view_command_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510B070
 * - func_1510B128
 * - func_1510B3B0
 * - func_1510B458
 * - func_1510B51C
 * - func_1510B5F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B128.s")
void func_1510B128(s32, f32, f32, f32, f32);
extern f32 D_800D9AC0[];
extern s8 D_800D9AF0;
extern s32 D_80082FA0;

void func_1510B32C(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    void *temp_v0;

    func_1510B128(arg0, arg1, arg2, arg3, 0.0f);
    temp_v0 = (void *)((u8 *)D_800D9AC0 + (arg0 * 0xC));
    *(f32 *)((u8 *)temp_v0 + 0) = arg3;
    *(f32 *)((u8 *)temp_v0 + 4) = arg1;
    *(f32 *)((u8 *)temp_v0 + 8) = arg2;
    D_800D9AF0 = 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510B3B0 CURRENT (280) */
void func_1510B3B0(void) {
    f32 *var_s0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_s1;

    var_s1 = 0;
    if (D_80082FA0 >= 0) {
        var_s0 = D_800D9AC0;
        do {
            temp_fv0 = var_s0[0];
            if (-1.0f != temp_fv0) {
                temp_fv1 = temp_fv0;
                func_1510B128(var_s1, var_s0[1], var_s0[2], temp_fv1, 0.0f);
                var_s0[0] = -1.0f;
            }
            var_s1 += 1;
            var_s0 += 3;
        } while (D_80082FA0 >= var_s1);
    }
    D_800D9AF0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510B3B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B458.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138520/func_1510B5F8.s")
