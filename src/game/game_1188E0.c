#include "types.h"

/*
 * Reviewed source unit: src/game/game_1188E0.c
 * Boundary evidence: docs/evidence/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EB484
 * - func_150EB614
 * - func_150EB8C4
 * - func_150EBC80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1188E0Vector;

void func_150EB484(Game1188E0Vector *, f32 *, void *);

void func_150EB430(Game1188E0Vector *arg0, Game1188E0Vector *arg1, void *arg2) {
    f32 sp1C[3];
    Game1188E0Vector *temp_a3 = arg1;

    sp1C[0] = arg0->x + temp_a3->x;
    sp1C[1] = arg0->y + temp_a3->y;
    sp1C[2] = arg0->z + temp_a3->z;
    func_150EB484(arg0, sp1C, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB614.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB8C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EBC80.s")
