#include "types.h"

/*
 * Reviewed source unit: src/game/game_105760.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D82BC
 * - func_150D83D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D82B0(s32 arg0) {

}
extern s32 D_80090298[];
extern f32 D_800A0B10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D82BC CURRENT (1250) */
s32 func_150D82BC(u8 *arg0, u8 *arg1) {
    f32 temp_fv0;
    s32 *temp_a0;
    s32 temp_ft1;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_a2;
    s8 **temp_t9;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg1 + 0x2D0);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s16 *)(arg0 + 0x18) = D_80090298[6];
    if (*(u16 *)(arg1 + 0x84) == 0xD) {
        temp_fv0 = *(f32 *)(temp_v0 + 8);
        if ((temp_fv0 >= 23.0f) && (temp_fv0 <= 40.0f)) {
            *(s16 *)(arg0 + 0x18) = D_80090298[7];
            temp_t9 = *(s8 ***)(arg0 + 0x24);
            temp_fv0 = *(f32 *)(temp_v0 + 8);
            temp_v1 = (s32)*temp_t9;
            temp_fv0 = (temp_fv0 - 23.0f) * D_800A0B10;
            var_a1 = 0;
            if (*(s8 *)temp_v1 != -0xE) {
                do {
                    var_a1++;
                } while (*(s8 *)((var_a1 * 8) + temp_v1) != -0xE);
            }
            temp_a0 = (s32 *)(temp_v1 + (var_a1 * 8));
            temp_v0_2 = *temp_a0;
            temp_ft1 = (s32)((70.0f * temp_fv0) + 2.0f);
            var_a2 = temp_ft1;
            if (temp_ft1 < 0) {
                var_a2 = temp_ft1 + ((temp_v0_2 >> 12) & 0xFFF);
            }
            *temp_a0 = ((var_a2 & 0xFFF) << 12) | 0xF2000000 | 2;
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D82BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D82BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D83D8.s")
