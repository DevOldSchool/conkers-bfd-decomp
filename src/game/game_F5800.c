#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5800.c
 * Boundary evidence: docs/evidence/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C8350
 * - func_150C851C
 * - func_150C8600
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE4E0;
extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C8350 CURRENT (1840) */
void func_150C8350(void) {
    s16 temp_a1;
    s16 temp_a1_3;
    s16 var_a0;
    s16 var_a2;
    s32 temp_a1_2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_t0;
    s32 var_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *var_v0;

    var_v1 = 0;
    do {
        var_v0 = D_800BE4E0 + var_v1;
        var_a0 = *(s16 *)((u8 *)var_v0 + 6);
        temp_a1 = *(s16 *)((u8 *)var_v0 + 8);
        if (var_a0 != temp_a1) {
            var_a2 = temp_a1;
            if (var_a0 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = var_a2 - var_a0;
            var_t0 = temp_a1_2;
            temp_t7 = D_800BE9E4 * 0x10;
            if (temp_a1_2 < 0) {
                var_t0 = -temp_a1_2;
            }
            if (var_t0 < temp_t7) {
                *(s16 *)((u8 *)var_v0 + 6) = var_a2;
                var_v0 = D_800BE4E0 + var_v1;
            } else {
                if (temp_a1_2 < 0) {
                    var_a1 = -1;
                } else {
                    var_a1 = 1;
                }
                *(s16 *)((u8 *)var_v0 + 6) = (s16) (var_a0 + (temp_t7 * var_a1));
                var_v0 = D_800BE4E0 + var_v1;
            }
            var_a0 = *(s16 *)((u8 *)var_v0 + 6);
        }
        *(s16 *)((u8 *)var_v0 + 4) = (s16) (*(s16 *)((u8 *)var_v0 + 4) + (var_a0 * *(s8 *)((u8 *)var_v0 + 2) * D_800BE9A0));
        temp_v0 = D_800BE4E0 + var_v1;
        temp_a1_3 = *(s16 *)((u8 *)temp_v0 + 4);
        if (temp_a1_3 >= 0x500) {
            *(s16 *)((u8 *)temp_v0 + 4) = (s16) (temp_a1_3 - 0x500);
            temp_v0_2 = D_800BE4E0 + var_v1;
            *(s16 *)((u8 *)temp_v0_2 + 4) = (s16) (0x500 - *(s16 *)((u8 *)temp_v0_2 + 4));
            temp_v0_3 = D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)temp_v0_3 + 2) = (s8) -*(s8 *)((u8 *)temp_v0_3 + 2);
            temp_v0_4 = D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)temp_v0_4 + 4) >= 0x500) {
                *(s16 *)((u8 *)temp_v0_4 + 4) = 0x4FF;
            }
        } else if (temp_a1_3 < 0) {
            *(s16 *)((u8 *)temp_v0 + 4) = (s16) -temp_a1_3;
            temp_v0_5 = D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)temp_v0_5 + 2) = (s8) -*(s8 *)((u8 *)temp_v0_5 + 2);
            temp_v0_6 = D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)temp_v0_6 + 4) < 0) {
                *(s16 *)((u8 *)temp_v0_6 + 4) = 0;
            }
        }
        var_v1 += 0xA;
    } while (var_v1 != 0x64);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C8350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8350.s")
void func_150C84F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8350();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C851C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8600.s")
