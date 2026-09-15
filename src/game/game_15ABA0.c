#include "types.h"

/*
 * Reviewed source unit: src/game/game_15ABA0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512D748
 * - func_1512D980
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800DC2C0[];

void func_1512D6F0(void *arg0) {
    void *temp_v0;

    temp_v0 = D_800DC2C0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0x68);
    *(s32 *)((u8 *)temp_v0 + 0x50) = 5;
    *(f32 *)((u8 *)temp_v0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x58) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x5C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x60) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x28) = -1.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D748.s")
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_1512D6F0: unique active declaration in the allowed source */
f32 func_15047D60(f32);
s32 func_150ADA20();                                /* extern */
extern f32 D_800A36F0;
extern f32 D_800A36F4;
extern f32 D_800A36F8;
extern f32 D_800A36FC;
extern f32 D_800A3700;
extern f32 D_800A3704;
extern f32 D_800A3708;
extern f32 D_800A370C;
extern u8 D_800BE9A0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D980 CURRENT (5344) */
void func_1512D980(void *arg0) {
    f32 sp20;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1_2;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_ft3;
    void *temp_s0;

    temp_s0 = (*(u8 *)((u8 *)arg0 + 0x23D) * 0x68) + D_800DC2C0;
    if (func_150ADA20() & 1) {
        var_fa1 = 1.0f;
    } else {
        var_fa1 = -1.0f;
    }
    temp_fv1 = *(f32 *)((u8 *)temp_s0 + 0x28);
    if ((temp_fv1 != -1.0f) && (*(s32 *)((u8 *)temp_s0 + 0x50) != 5) && !(*(s32 *)((u8 *)arg0 + 0x84) & 0x80000)) {
        sp20 = var_fa1;
        *(f32 *)((u8 *)temp_s0 + 0x54) = (f32) (func_15047D60(temp_fv1 * D_800A36F0 * *(f32 *)((u8 *)temp_s0 + 0) * 360.0f * D_800A36F4) * (var_fa1 * *(f32 *)((u8 *)temp_s0 + 0x2C)));
        *(f32 *)((u8 *)temp_s0 + 0x58) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x28) * D_800A36F8 * *(f32 *)((u8 *)temp_s0 + 4) * 360.0f * D_800A36FC) * (1.0f * *(f32 *)((u8 *)temp_s0 + 0x2C)));
        *(f32 *)((u8 *)temp_s0 + 0x5C) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x28) * D_800A3700 * *(f32 *)((u8 *)temp_s0 + 8) * 360.0f * D_800A3704) * (-1.0f * *(f32 *)((u8 *)temp_s0 + 0x2C)));
        temp_fa0 = *(f32 *)((u8 *)temp_s0 + 0x2C);
        temp_fa1 = *(f32 *)((u8 *)temp_s0 + 0x3C);
        temp_fv1_2 = *(f32 *)((u8 *)temp_s0 + 0x28);
        *(f32 *)((u8 *)temp_s0 + 0x60) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x28) * D_800A3708 * *(f32 *)((u8 *)temp_s0 + 0xC) * 360.0f * D_800A370C) * (-1.0f * temp_fa0));
        if ((temp_fv1_2 <= temp_fa1) && (temp_fa0 >= 0.0f)) {
            if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x30)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 0) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 1;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) + (*(f32 *)((u8 *)temp_s0 + 0x40) * D_800BE9A4));
            } else if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x34)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 1) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 2;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) - (*(f32 *)((u8 *)temp_s0 + 0x44) * D_800BE9A4));
            } else if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x38)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 2) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 3;
                }
            } else if (temp_fv1_2 < temp_fa1) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 3) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 4;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) - (*(f32 *)((u8 *)temp_s0 + 0x4C) * D_800BE9A4));
            } else {
                func_1512D6F0(arg0);
            }
            var_ft3 = (f32) D_800BE9A0;
            if ((s32) D_800BE9A0 < 0) {
                var_ft3 += 4294967296.0f;
            }
            *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) + var_ft3);
            return;
        }
        *(s32 *)((u8 *)temp_s0 + 0x50) = 5;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D980.s")
