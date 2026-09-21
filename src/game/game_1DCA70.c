#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DCA70.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AF6D4
 * - func_151AFC08
 * - func_151AFC88
 * - func_151AFEA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern f32 D_800AA0F0;
extern f32 D_800AA0FC;

s32 func_151AF5C0(f32 *arg0, void *arg1, s32 arg2, u8 arg3) {
    f32 position[3];
    f32 *var_a0;
    s32 var_a2;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a0 = &D_800AA0FC;
    } else {
        var_a0 = &D_800AA0F0;
    }
    if (arg3 == 1) {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0x800;
    } else {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0x640;
    }
    func_15143134(var_a0, arg0, var_a2);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 100.0f;
    position[2] = arg0[2];
    func_1504715C((void *)arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 500.0f, (void *)arg2);
}
s32 func_151AF6C0(s32 arg0, s32 arg1) {
    return 0xC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AF6D4.s")
s32 func_151AFBD4(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AFC08 CURRENT (775) */
s32 func_151AFC08(u8 *arg0) {
    f32 temp_fv0;
    s16 temp_v1;
    s32 temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
        if (temp_v1 < 0x20) {
            temp_v0 = temp_v1 * 8;
            if (temp_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v0;
            }
        }
        if (*(s16 *)((u8 *)arg0 + 0x128) < *(s16 *)((u8 *)arg0 + 0x1C)) {
            temp_fv0 = *(f32 *)((u8 *)(arg0 + 0x128) + 4) * D_800BE9A4;
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AFC08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFC08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFC88.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AFEA4 CURRENT (13905) */
s32 func_151AFEA4(void *arg0, s32 arg1) {
    f32 var_ft5;
    f32 var_ft5_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;

    var_v1 = D_800BE9E4;
    if (var_v1 != 0) {
        temp_a2 = -(var_v1 & 3);
        temp_a1 = var_v1 + temp_a2;
        if (temp_a2 != 0) {
            var_v1 -= 1;
            var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (temp_a1 != var_v1) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
                    var_v1 -= 1;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (temp_a1 != var_v1);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            if (var_v1 != 0) {
                goto block_5;
            }
        } else {
block_5:
            var_v1_2 = var_v1 - 4;
            var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (var_v1_2 != 0) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
                    var_v1_2 -= 4;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (var_v1_2 != 0);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AFEA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFEA4.s")
