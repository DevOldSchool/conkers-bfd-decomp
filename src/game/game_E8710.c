#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8710.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BB260
 * - func_150BB408
 * - func_150BB450
 * - func_150BB498
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BB260 CURRENT (13905) */
s32 func_150BB260(void *arg0, s32 arg1) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150BB260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB408.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BB450 CURRENT (10) */
s32 func_150BB450(void *arg0) {
    s16 temp_lo;
    s16 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xB0)) {
        temp_lo = temp_v0 * *(s16 *)((u8 *)arg0 + 0xB2);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_lo;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BB450 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB450.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB498.s")
