#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EB6C0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BE210
 * - func_151BE4B8
 * - func_151BE558
 * - func_151BE604
 * - func_151BE644
 * - func_151BE674
 * - func_151BE6A0
 * - func_151BE6CC
 * - func_151BE788
 * - func_151BE7C8
 * - func_151BE7F8
 * - func_151BE824
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800AA89C;
extern f32 D_800AA8A0;
extern f32 D_800AA8A4;
extern f32 D_800AA8A8;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BE210 CURRENT (2235) */
s32 func_151BE210(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    *(f32 *)((u8 *)arg0 + 0x134) = (f32) (*(f32 *)((u8 *)arg0 + 0x134) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x134) < 0.0f) {
        temp_s0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)temp_s0 + 0x24) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0 + 0x10)) + *(f32 *)((u8 *)temp_s0 + 8));
    }
    temp_s0_2 = (void *)(arg0 + 0x110);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x18) - temp_fv0) * D_800AA89C));
    *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x28) - D_800BE9A4);
    if (*(f32 *)((u8 *)temp_s0_2 + 0x28) < 0.0f) {
        *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)temp_s0_2 + 0x1C) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x14)) + *(f32 *)((u8 *)temp_s0_2 + 0xC));
        } else {
            *(f32 *)((u8 *)temp_s0_2 + 0x1C) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x20)) + *(f32 *)((u8 *)temp_s0_2 + 0xC));
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_s0_2 + 0x1C) - temp_fv0_2) * D_800AA8A0));
    *(f32 *)((u8 *)temp_s0_2 + 0x38) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x38) - D_800BE9A4);
    if (*(f32 *)((u8 *)temp_s0_2 + 0x38) < 0.0f) {
        *(f32 *)((u8 *)temp_s0_2 + 0x38) = (f32) (func_150ADA68() * 10.0f);
        *(f32 *)((u8 *)temp_s0_2 + 0x34) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_s0_2 + 0x30)) + *(f32 *)((u8 *)temp_s0_2 + 0x2C));
    }
    temp_fv0_3 = *(f32 *)((u8 *)temp_s0_2 + 0x3C);
    *(f32 *)((u8 *)temp_s0_2 + 0x3C) = (f32) (temp_fv0_3 + ((*(f32 *)((u8 *)temp_s0_2 + 0x34) - temp_fv0_3) * D_800AA8A8));
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) *(f32 *)((u8 *)temp_s0_2 + 0x3C);
    temp_fv1 = *(f32 *)((u8 *)temp_s0_2 + 0x40);
    temp_fa0 = *(f32 *)((u8 *)temp_s0_2 + 0x44);
    *(f32 *)((u8 *)temp_s0_2 + 0x40) = (f32) (temp_fv1 + ((*(f32 *)((u8 *)temp_s0_2 + 0x48) - temp_fv1) * D_800AA8A4));
    *(f32 *)((u8 *)temp_s0_2 + 0x44) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x4C) - temp_fa0) * D_800AA8A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BE210 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE604.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE674.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE6A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE6CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE788.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE7C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE7F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EB6C0/func_151BE824.s")
