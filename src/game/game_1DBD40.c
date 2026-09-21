#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DBD40.c
 * Boundary evidence: docs/evidence/game_raw_emission_trio.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AE984
 * - func_151AEAB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150ADA68(void);
u32 func_150ADA20(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);
void func_151AE984(f32 *, s32, s32, s32, s32, s32);
void func_151AEAB4(f32 *, s32, u8);
extern f32 D_800A9D84;
extern f32 D_800A9D88;
extern f32 D_800A9D8C;
extern f32 D_800A9D90;
extern f32 D_800A9D94;

void func_151AE890(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, u8 *arg6) {
    f32 sp2C[3];
    s32 var_a1;
    f32 temp_fv0;
    s32 var_v0;

    sp2C[0] = arg0;
    sp2C[1] = arg1;
    sp2C[2] = arg2;
    temp_fv0 = func_150ADA68();
    if (!(temp_fv0 < D_800A9D84)) {
        if (temp_fv0 < 0.25f) {
            temp_fv0 = func_150ADA68();
            var_a1 = (0.0f < temp_fv0) ? 1 : 0;
            func_151AEAB4(sp2C, var_a1, arg6[0xC]);
            return;
        }
        temp_fv0 = func_150ADA68();
        var_v0 = (D_800A9D88 < temp_fv0) ? 1 : 0;
        func_151AE984(sp2C, arg3, arg4, arg5, var_v0, arg6[0xC]);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE984 CURRENT (443) */
void func_151AE984(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4,
                   s32 arg5) {
    f32 sp58[3];
    u32 sp50;
    u32 sp4C;
    f32 sp48;

    sp58[0] = -arg1 * D_800A9D8C;
    sp58[1] = -arg2 * D_800A9D8C;
    sp58[2] = -arg3 * D_800A9D8C;
    sp48 = func_150ADA68();
    sp4C = func_150ADA20();
    sp50 = func_150ADA20();
    func_151D9014(arg0, sp58, 0, (sp48 * D_800A9D90) + D_800A9D94,
                  (sp4C % 31U) + 0x3C, (sp50 % 101U) + 0x9B,
                  (func_150ADA68() * 219.0f) + 77.0f, (u8)arg4,
                  1.0f, 1.0f, 0, 0, 1, 0, (u8)arg5, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBD40/func_151AE984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBD40/func_151AEAB4.s")
