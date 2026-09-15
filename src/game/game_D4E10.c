#include "types.h"

/*
 * Reviewed source unit: src/game/game_D4E10.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A7960
 * - func_150A7A00
 * - func_150A7A14
 * - func_150A7A48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7960 CURRENT (4335) */
void func_150A7960(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft0;

    *(s32 *)&temp_fv0 = arg1;
    *(s32 *)&temp_fv1 = arg2;
    *(s32 *)&temp_ft0 = arg3;
    *arg4 = (arg0[0] * temp_fv0) + (arg0[4] * temp_fv1) + ((arg0[8] * temp_ft0) + arg0[12]);
    *arg5 = (arg0[1] * temp_fv0) + (arg0[5] * temp_fv1) + ((arg0[9] * temp_ft0) + arg0[13]);
    *arg6 = (arg0[2] * temp_fv0) + (arg0[6] * temp_fv1) + ((arg0[10] * temp_ft0) + arg0[14]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7960 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7960.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7A00 CURRENT (9418) */
void func_150A7A00(void) {
    func_150A7960();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7A00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A00.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7A14 CURRENT (9305) */
void func_150A7A14(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7A14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A48.s")
