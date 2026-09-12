#include "types.h"

/*
 * Reviewed source unit: src/game/game_13F9D0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15112520
 * - func_15112A80
 * - func_15113180
 * - func_15113218
 * - func_151135C4
 * - func_151137D4
 * - func_15113C88
 * - func_15113E54
 * - func_15114050
 * - func_151140C4
 * - func_15114188
 * - func_15114348
 * - func_1511473C
 * - func_151148A8
 * - func_1511490C
 * - func_151149AC
 * - func_15114A1C
 * - func_15114B94
 * - func_15114D24
 * - func_15114F44
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112A80.s")
extern s32 D_800DBEF0;
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113180 CURRENT (215) */
void func_15113180(void) {
    s32 var_v0;
    s32 var_v1;
    u8 temp_a1;
    void *temp_a0;
    void *temp_a0_2;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DBEF0 > 0) {
        do {
            temp_a0 = D_800DBEF4 + var_v1;
            *(u8 *)((u8 *)temp_a0 + 0x6F) = (u8) (*(u8 *)((u8 *)temp_a0 + 0x6F) & ~0x40);
            temp_a0_2 = D_800DBEF4 + var_v1;
            temp_a1 = *(u8 *)((u8 *)temp_a0_2 + 0x6F);
            if (((temp_a1 & 0xF) || ((*(u8 *)((u8 *)temp_a0_2 + 0x70) & 4) == 4)) && (*(s32 *)((u8 *)temp_a0_2 + 0x38) != 0)) {
                *(u8 *)((u8 *)temp_a0_2 + 0x6F) = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DBEF0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113180 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113218.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151135C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151137D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113C88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113E54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151140C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_1511473C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151148A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_1511490C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151149AC CURRENT (410) */
s32 func_151149AC(s32 arg0) {
    s32 temp_t6;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return 0;
    }
    var_v1 = 0;
    if (D_800DBEF0 > 0) {
        var_a2 = 0;
        var_a3 = D_800DBEF4;
loop_4:
        var_v1 += 1;
        var_a3 += 0xA0;
        if (temp_t6 == *(u8 *)((u8 *)var_a3 + 0x72)) {
            return var_a2 + D_800DBEF4;
        }
        var_a2 += 0xA0;
        if (var_v1 >= D_800DBEF0) {
            /* Duplicate return node #7. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_4;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151149AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151149AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114A1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114B94.s")
s32 func_15114CC4(void *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x18);
    if ((temp_v1 != 0) && ((*arg2 != 0) || (*(s32 *)((u8 *)arg0 + 0x1C) == 0))) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 1;
        *(s16 *)((u8 *)arg0 + 2) = (s16) *(s16 *)((u8 *)temp_v1 + 0x10);
        *(s16 *)((u8 *)arg0 + 4) = (s16) *(s16 *)((u8 *)temp_v1 + 0x12);
        *(s16 *)((u8 *)arg0 + 6) = (s16) *(s16 *)((u8 *)temp_v1 + 0x14);
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114D24.s")
extern s32 func_1001001C(s32 (*arg0)(void *, s32, s32 *, s32), s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15114F04(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15114CC4, arg0, 0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114F44.s")
