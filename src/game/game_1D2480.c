#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D2480.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A4FD0
 * - func_151A5070
 * - func_151A5170
 * - func_151A561C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A4FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A5070.s")
typedef void (*Func151A5130Callback)(s32 arg0, void *arg1, s16 arg2, s32 arg3);
extern Func151A5130Callback D_8008F900[];

void func_151A5130(s32 arg0, void *arg1, s16 arg2, s32 arg3) {
    D_8008F900[((u8 *) arg1)[0x14]](arg0, arg1, arg2, arg3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A5170.s")
extern void (*D_8008F904[])(void *, s32, u8);

void func_151A55D4(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008F904[*(u8 *)((u8 *)arg0 + 0x19)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A8D70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A561C CURRENT (720) */
void func_151A561C(s32 arg0, s32 arg1) {
    s32 sp1C;
    s32 temp_a3;

    temp_a3 = arg1 & 0xFF;
    sp1C = D_800A8D70;
    func_15169260(&sp1C, 1, arg0, temp_a3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A561C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2480/func_151A561C.s")
