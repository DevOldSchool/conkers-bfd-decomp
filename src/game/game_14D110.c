#include "types.h"

/*
 * Reviewed source unit: src/game/game_14D110.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511FC60
 * - func_15120158
 * - func_15121490
 * - func_151216F8
 * - func_151218C4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_1511FC60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_15120158.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_15121490.s")
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151216F8 CURRENT (400) */
void func_151216F8(void *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x23E);
    if (temp_v0 != 0) {
        if (temp_v0 == 0x34) {
            *(f32 *)((u8 *)arg0 + 0x190) = 80.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 350.0f;
            return;
        }
        if ((temp_v0 == 0x3B) && ((D_800BE9F0 == 0x41) || (D_800BE9F0 == 0x3C))) {
            *(f32 *)((u8 *)arg0 + 0x190) = -12.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = -28.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 106.0f;
            return;
        }
        if ((temp_v0 == 2) || (temp_v0 == 0xA) || (temp_v0 == 0x13)) {
            *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s32 *)((u8 *)arg0 + 0x84) | 0x80);
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 135.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if ((temp_v0 == 0x12) && (D_800BE9F0 == 0x3C)) {
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 180.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0xF) {
            *(f32 *)((u8 *)arg0 + 0x190) = 10.0f;
            *(f32 *)((u8 *)arg0 + 0x784) = 480.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x38) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            *(f32 *)((u8 *)arg0 + 0x190) = 5.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        if (temp_v0 == 0x15) {
            *(f32 *)((u8 *)arg0 + 0x784) = 110.0f;
            *(f32 *)((u8 *)arg0 + 0x190) = 25.0f;
            *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
            return;
        }
        *(f32 *)((u8 *)arg0 + 0x190) = 5.0f;
        *(f32 *)((u8 *)arg0 + 0x784) = 75.0f;
        *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
        return;
    }
    *(f32 *)((u8 *)arg0 + 0x784) = 90.0f;
    *(f32 *)((u8 *)arg0 + 0x190) = 25.0f;
    *(f32 *)((u8 *)arg0 + 0x99C) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151216F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_151216F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14D110/func_151218C4.s")
