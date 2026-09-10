#include "types.h"

/*
 * Reviewed source unit: src/game/game_1449A0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151174F0
 * - func_15117518
 * - func_15117770
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_151172D8(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151174F0 CURRENT (185) */
void func_151174F0(f32 *arg0) {
    *arg0 = func_151172D8(*arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151174F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1449A0/func_151174F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1449A0/func_15117518.s")
f32 func_15117518(void *arg0, f32 arg1);            /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15117770 CURRENT (185) */
void func_15117770(f32 *arg0) {
    *arg0 = func_15117518(*arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15117770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1449A0/func_15117770.s")
void func_15117798(u8 *arg0) {
    *(f32 *)(arg0 + 8) = func_15117518(arg0, *(f32 *)(arg0 + 8));
}
