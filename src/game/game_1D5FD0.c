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
void func_15143874(s16, s32, f32 *, f32 *);
s32 func_150ADA20(void);
f32 func_150ADA68(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8F6C CURRENT (396) */
void func_151A8F6C(void *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 sp24;
    u8 *sp20;
    f32 velocity;
    u8 *state;
    void *saved_arg0;
    f32 *saved_arg2;
    f32 *saved_arg3;

    saved_arg0 = arg0;
    saved_arg2 = arg2;
    saved_arg3 = arg3;
    sp24 = func_150ADA20();
    state = (u8 *)saved_arg0 + 0x28;
    sp20 = state;
    velocity = func_150ADA68() * *(f32 *)((u8 *)saved_arg0 + 0x48);
    func_15143874((s16)(sp24 & 0xFF), (s32)velocity, arg1, arg1 + 2);
    arg1[0] += *(f32 *)(state + 0x10);
    arg1[2] += *(f32 *)(state + 0x18);
    arg1[1] = *(f32 *)(state + 0x14);
    *saved_arg2 = *(f32 *)(state + 0x14);
    *saved_arg3 = *(f32 *)(state + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8F6C */
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
