#include "types.h"

/*
 * Reviewed source unit: src/game/game_1104D0.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E3020
 * - func_150E3208
 * - func_150E33CC
 * - func_150E3414
 * - func_150E3514
 * - func_150E35DC
 * - func_150E36BC
 * - func_150E3738
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3020.s")
/* Call context: func_150AD9A0: unique active project prototype */
s32 func_150AD9A0(s32, s32, s32, s16);
void *func_150E3020(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E3208 CURRENT (100) */
s32 func_150E3208(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;

    temp_v0 = func_150E3020(arg0, arg1, arg2, arg3, arg4, arg5, arg6, (f32) func_150AD9A0(arg0 - arg3, arg1 - arg4, arg2 - arg5, (s16) arg3) / (f32) arg7, 0, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return *(u8 *)((u8 *)temp_v0 + 0x48) + 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E3208 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3208.s")
/* Call context: func_150E3020: unique active project prototype */
void * func_150E3020(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s32);

s32 func_150E32D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    void *temp_v0;

    temp_v0 = func_150E3020(arg0, arg1, arg2, 0, 0, 0, arg4, arg5, arg3, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return *(u8 *)((u8 *)temp_v0 + 0x48) + 1;
    }
    return 0;
}
/* Call context: func_150E3020: unique active project prototype */

void func_150E3340(void *arg0, void *arg1, s32 arg2, s16 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    temp_a0 = *(s32 *)((u8 *)arg1 + 0);
    temp_a1 = *(s32 *)((u8 *)arg1 + 4);
    temp_a2 = *(s32 *)((u8 *)arg1 + 8);
    func_150E3020(temp_a0, temp_a1, temp_a2, temp_a0, temp_a1, temp_a2, 0x1A, 10.0f, 0, *(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 4), *(f32 *)((u8 *)arg0 + 8), arg2, (s32) arg3);
}
void func_1000E7A0(s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E33CC CURRENT (170) */
s32 func_150E33CC(s32 arg0, s32 arg1, void **arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 == 0) {
        return 1;
    }
    func_1000E7A0(2, temp_v0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E33CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E33CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3414.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3514.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E35DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E36BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3738.s")
