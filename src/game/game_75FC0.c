#include "types.h"

/*
 * Reviewed source unit: src/game/game_75FC0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15048B10
 * - func_15048C30
 * - func_15048F20
 * - func_15048FC8
 * - func_150490A8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048B10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048C30.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048F20 CURRENT (30) */
void func_15048F20(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)arg1 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048F20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048F20.s")
void func_15048F58(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) - *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) - *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) - *(f32 *)((u8 *)arg1 + 8));
}
void func_15048F90(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048FC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_150490A8.s")
void func_15049148(void *arg0, f32 arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
}
f32 func_150AD930();                                /* extern */

void func_1504917C(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 var_fv1;

    temp_fv0 = func_150AD930();
    var_fv1 = temp_fv0;
    if (temp_fv0 != 0.0f) {
        var_fv1 = 1.0f / temp_fv0;
    }
    *(f32 *)((u8 *)arg1 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * var_fv1);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * var_fv1);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * var_fv1);
}
void func_150491EC(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8));
    func_1504917C(arg2, arg2);
}
