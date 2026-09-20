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
void func_151AE984(f32 *, s32, s32, s32, s32, s32);
void func_151AEAB4(f32 *, s32, u8);
extern f32 D_800A9D84;
extern f32 D_800A9D88;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBD40/func_151AE984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBD40/func_151AEAB4.s")
