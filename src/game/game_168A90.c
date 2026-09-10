#include "types.h"

/*
 * Reviewed source unit: src/game/game_168A90.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1513B5E0
 * - func_1513B798
 * - func_1513B83C
 * - func_1513B968
 * - func_1513B9A8
 * - func_1513B9DC
 * - func_1513BA10
 * - func_1513BA44
 * - func_1513BA78
 * - func_1513BAE8
 * - func_1513BBFC
 * - func_1513BEB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B798.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B968.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B9A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B9DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BA10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BA44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BA78.s")
s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BAE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A4A84;
extern f32 D_800A4A88;
extern f32 D_800A4A8C;
extern f32 D_800A4A90;
extern f32 D_800A4A94;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513BEB0 CURRENT (919) */
s32 func_1513BEB0(u8 *arg0) {
    f32 temp_fv0;
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_s0_2 = (void *)(temp_s0 + 0xF8);
    *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x100) + (D_800A4A84 * D_800BE9A4));
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 8));
    *(f32 *)((u8 *)temp_s0_2 + 8) = temp_fv0;
    *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) + (D_800A4A88 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (func_15047D60(temp_fv0) * D_800A4A8C);
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0xC) + (D_800A4A90 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 0x10) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0x10) + (D_800A4A94 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 0xC));
    *(f32 *)((u8 *)temp_s0_2 + 0x10) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 0x10));
    if (*(f32 *)((u8 *)temp_s0 + 0xF8) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0xF8) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0 + 0xF8) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xF8) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0xF8) < 0.0f);
    }
    if (*(f32 *)((u8 *)temp_s0_2 + 4) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 4) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0_2 + 4) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0_2 + 4) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 4) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0_2 + 4) < 0.0f);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513BEB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BEB0.s")
