#include "types.h"

/*
 * Reviewed source unit: src/game/game_3E620.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15011170
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F4D5C(s32, s8, u8, u8, s32);
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern u8 D_1000EB00;
extern u8 D_1000EF40;
extern s8 D_80088B40;
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15011170 CURRENT (148) */
void func_15011170(void) {
    void *volatile texture;

    D_80088B40 = 0;
    func_150F4D5C(D_800DBFF0, 0, 0, 0xFF, 1);
    func_1000FA64(0x6C, -0xDFC, -0x222, -0x17F1, 0x4650, 0x457, 0x44C, (texture = &D_1000EB00), 0, 0, 8, 0);
    func_1000FA64(0x6C, -0xB71, -0x461, -0x86E, 0x4650, 0x636, 0x62C, texture, 0, 0, 8, 0);
    func_1000FA64(0x6C, 0x1F1, -0x42F, -0x839, 0x4650, 0x7F8, 0x7EE, texture, 0, 0, 8, 0);
    func_1000FA64(0x61F, 0x1A, 0, 0, 0x2EE0, 0x9C4, 0x708, (texture = &D_1000EF40), 0, 0, 0x48, 0);
    func_1000FA64(0x61F, 0x1B, 0, 0, 0x1F40, 0x7D0, 0x3E8, texture, 0, 0, 0x48, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15011170 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3E620/func_15011170.s")
