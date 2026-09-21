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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7A48 CURRENT (7454) */
void func_150A7A48(f32 *arg0, f32 *arg1, f32 *arg2) {
    register f32 b00;
    register f32 b01;
    register f32 b02;
    register f32 b03;
    register f32 b10;
    register f32 b11;
    register f32 b12;
    register f32 b13;
    register f32 b20;
    register f32 b21;
    register f32 b22;
    register f32 b23;
    register f32 b30;
    register f32 b31;
    register f32 b32;
    register f32 b33;
    register f32 x0;
    register f32 x1;
    register f32 x2;
    register f32 x3;
    s32 count;

    b00 = arg1[0];
    b01 = arg1[1];
    b02 = arg1[2];
    b03 = arg1[3];
    b10 = arg1[4];
    b11 = arg1[5];
    b12 = arg1[6];
    b13 = arg1[7];
    b20 = arg1[8];
    b21 = arg1[9];
    b22 = arg1[10];
    b23 = arg1[11];
    b30 = arg1[12];
    b31 = arg1[13];
    b32 = arg1[14];
    b33 = arg1[15];
    count = 4;
    do {
        arg0 += 4;
        x0 = arg0[-4];
        x1 = arg0[-3];
        x2 = arg0[-2];
        x3 = arg0[-1];
        arg2 += 4;
        arg2[-4] = (x0 * b00) + (x1 * b10) + (x2 * b20) + (x3 * b30);
        arg2[-3] = (x0 * b01) + (x1 * b11) + (x2 * b21) + (x3 * b31);
        arg2[-2] = (x0 * b02) + (x1 * b12) + (x2 * b22) + (x3 * b32);
        arg2[-1] = (x0 * b03) + (x1 * b13) + (x2 * b23) + (x3 * b33);
        count--;
    } while (count != 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7A48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A48.s")
