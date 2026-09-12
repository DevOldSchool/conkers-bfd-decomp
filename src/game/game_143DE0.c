#include "types.h"

/*
 * Reviewed source unit: src/game/game_143DE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15116930
 * - func_151169B4
 * - func_15116BAC
 * - func_15116D7C
 * - func_15116EA4
 * - func_151172D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116930 CURRENT (245) */
void func_15116930(void *arg0, void *arg1) {
    void *temp_t0;
    s32 temp_t3;
    s32 temp_t4;
    u8 temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x73);
        if (!(temp_v0 & 3) && !(temp_v0 & 4)) {
            temp_t3 = temp_v0 & 0xFFFC;
            temp_t4 = temp_t3 | 2;
            temp_t0 = *(void **)((u8 *)arg1 + 0x31C);
            if (*(u8 *)((u8 *)temp_t0 + 0x57) == 1) {
                *(u8 *)((u8 *)arg0 + 0x73) = temp_t3;
                *(u8 *)((u8 *)arg0 + 0x73) = temp_t4;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116930.s")
void func_151169B4(void);

void func_15116984(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x73) & 2) {
        func_151169B4();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_151169B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116BAC.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116D7C CURRENT (3985) */
void func_15116D7C(f32 *arg0) {
    f32 *var_a1;
    f32 *var_a2;
    f32 *var_a3;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa0_4;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 var_v1;

    temp_fv0 = (f32) *(s32 *)((u8 *)arg0 + 0x3C) * 0.00390625f;
    var_v1 = 0;
    var_a1 = arg0 + 0x60;
    var_a2 = arg0 + 0x7C;
    var_a3 = arg0;
    do {
        temp_fa1 = *var_a1;
        temp_fa0 = *var_a2;
        var_v1 += 4;
        if (temp_fa1 != temp_fa0) {
            if (temp_fa0 < temp_fa1) {
                *var_a1 = temp_fa1 - temp_fv0;
                temp_fa0_2 = *var_a2;
                if (*var_a1 < temp_fa0_2) {
                    *var_a1 = temp_fa0_2;
                }
            } else {
                *var_a1 = temp_fa1 + temp_fv0;
                temp_fa0_3 = *var_a2;
                if (temp_fa0_3 < *var_a1) {
                    *var_a1 = temp_fa0_3;
                }
            }
        }
        var_a1 += 4;
        var_a2 += 4;
        *var_a3 += *var_a1 * (f32) D_800BE9E4;
        temp_fa0_4 = *var_a3;
        if (temp_fa0_4 < 0.0f) {
            *var_a3 = temp_fa0_4 + 360.0f;
        } else if (temp_fa0_4 >= 360.0f) {
            *var_a3 = temp_fa0_4 - 360.0f;
        }
        var_a3 += 4;
    } while (var_v1 != 0xC);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116D7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116D7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_151172D8.s")
