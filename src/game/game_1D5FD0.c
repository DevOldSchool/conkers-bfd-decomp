#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D5FD0.c
 * Boundary evidence: docs/evidence/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A8B20
 * - func_151A8CEC
 * - func_151A8F6C
 * - func_151A9024
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8B20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8CEC.s")
typedef struct {
    u8 pad_0[0x2C];
    s32 field_2C;
} Game1D5FD0State;

void func_151432BC(s32, f32 *, f32 *, f32 *, s32);

void func_151A8F1C(Game1D5FD0State *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    func_151432BC(arg0->field_2C, arg1, arg1 + 2, arg2, arg3);
    arg1[1] = *arg2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8F6C.s")
void func_151A931C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9024 CURRENT (537) */
void func_151A9024(void *arg0, s32 arg1, s32 arg2) {
    arg2 = arg2 & 0xFF;
    if (*(u8 *)((u8 *)arg0 + 0x4C) != 1) {
        return;
    }
    func_151A931C((s32) arg0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9024 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A9024.s")
