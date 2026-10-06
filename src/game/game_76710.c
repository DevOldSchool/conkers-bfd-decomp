#include "types.h"

/*
 * Reviewed source unit: src/game/game_76710.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150492CC
 * - func_15049350
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game76710CallArgs {
    s32 words[9];
} Game76710CallArgs;

s32 func_150AAD98(Game76710CallArgs);

s32 func_15049260(Game76710CallArgs arg0) {
    return func_150AAD98(arg0);
}
extern f32 D_80099080;
extern f32 D_800CC220;
extern f32 D_800CC224;
extern f32 D_800CC228;
extern f32 D_800CC22C;
extern f32 D_800CC230;
extern f32 D_800CC234;
extern f32 D_800CC238;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150492CC CURRENT (950) */
void func_150492CC(f32 arg0, f32 arg1, f32 arg2) {
    D_800CC220 = arg0;
    D_800CC224 = arg1;
    D_800CC228 = arg2;
    D_800CC22C = arg0 / 2.0f;
    D_800CC230 = arg1 / 2.0f;
    D_800CC234 = arg2 / 2.0f;
    if (arg0 == 0.0f) {
        arg0 = D_80099080;
    }
    D_800CC238 = arg1 / arg0;
    *(f32 *)((u8 *)&D_800CC238 + 4) = arg2 / arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150492CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_150492CC.s")
extern f32 D_800CC210;
extern f32 D_800CC214;
extern f32 D_800CC218;
extern f32 D_800CC21C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049350 CURRENT (414) */
void func_15049350(Game76710CallArgs args) {
    f32 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)&args.words[0] - *(f32 *)&args.words[3];
    sp0 = *(f32 *)&args.words[0];
    temp_fv1 = *(f32 *)&args.words[1] - *(f32 *)&args.words[4];
    sp4 = *(f32 *)&args.words[1];
    temp_fa0 = *(f32 *)&args.words[2] - *(f32 *)&args.words[5];
    temp_fa1 = *(f32 *)&args.words[0] - *(f32 *)&args.words[6];
    temp_ft4 = *(f32 *)&args.words[1] - *(f32 *)&args.words[7];
    temp_ft5 = *(f32 *)&args.words[2] - *(f32 *)&args.words[8];
    temp_ft1 = (temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4);
    D_800CC210 = temp_ft1;
    spC = (-temp_fv0 * temp_ft5) + (temp_fa0 * temp_fa1);
    D_800CC214 = spC;
    sp8 = (temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1);
    D_800CC218 = sp8;
    D_800CC21C = (*(f32 *)&args.words[2] * sp8) + ((temp_ft1 * sp0) + (spC * sp4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_15049350.s")
