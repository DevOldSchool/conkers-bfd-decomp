#include "types.h"

/*
 * Reviewed source unit: src/game/game_EC420.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BEF7C
 * - func_150BF0F4
 * - func_150BF21C
 * - func_150BF760
 * - func_150BFA7C
 * - func_150BFFE0
 * - func_150C01DC
 * - func_150C04C0
 * - func_150C0648
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150BEF70(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BEF7C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BF0F4 CURRENT (1515) */
s32 func_150BF0F4(void *arg0) {
    s16 temp_v1_2;
    s32 var_v1;
    u8 temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x26);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != temp_v1) {
            var_v0 += D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x27);
            if ((s32) temp_v1 < (s32) var_v0) {
                var_v0 = temp_v1;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else if (var_v0 != 0) {
        var_v0 -= D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x2F);
        if ((s32) var_v0 < 0) {
            var_v0 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) + (*(s8 *)((u8 *)arg0 + 0x2D) * D_800BE9E4));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x14);
    *(s16 *)((u8 *)arg0 + 0x16) = (s16) (*(s16 *)((u8 *)arg0 + 0x16) + (*(s8 *)((u8 *)arg0 + 0x2E) * D_800BE9E4));
    if ((temp_v1_2 <= 0) || (temp_v1_2 <= 0)) {
        *(s16 *)((u8 *)arg0 + 0x16) = 0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)arg0 + 0x16);
        return 1;
    }
    var_v1 = *(u8 *)((u8 *)arg0 + 0x2C) + D_800BE9E4;
    if (var_v1 >= 0x80) {
        var_v1 = 0x7F;
    }
    *(u8 *)((u8 *)arg0 + 0x2C) = (u8) var_v1;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BF0F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF0F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF21C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFA7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C01DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C04C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C0648.s")
