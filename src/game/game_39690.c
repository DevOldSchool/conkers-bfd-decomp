#include "types.h"

/*
 * Reviewed source unit: src/game/game_39690.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500C1E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
typedef struct Game39690Record {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} Game39690Record;

extern u8 D_800DDE80;
extern u8 D_800DDF5C;
extern u8 D_800DDF60;
extern u8 D_800DDF68;
extern u8 D_800DDF73;
extern s32 D_800DDF78;
extern s32 D_800DDF7C;
extern s32 D_800DDF80;
extern Game39690Record D_800DDF84;
extern Game39690Record D_800DDFA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500C1E0 CURRENT (3835) */
void func_1500C1E0(void) {
    u8 *var_v0;
    u8 *var_v0_2;
    Game39690Record *var_v0_3;
    u8 *var_v1;

    var_v1 = &D_800DDF5C;
    var_v0 = &D_800DDF60;
    do {
        var_v1 += 1;
        var_v0 += 1;
        var_v0[-1] = 0;
        var_v1[-1] = 0;
    } while ((u32)var_v1 < (u32)&D_800DDF60);
    var_v0_2 = &D_800DDF68;
    do {
        var_v0_2 += 1;
        ((s8 *)var_v0_2)[-1] = -2;
    } while ((u32)var_v0_2 < (u32)&D_800DDF73);
    func_100226F0(&D_800DDE80, 0xDC);
    D_800DDF78 = 0;
    D_800DDF7C = 0;
    var_v0_3 = &D_800DDF84;
    D_800DDF80 = 0;
    do {
        var_v0_3 += 1;
        var_v0_3[-1].field_4 = 0;
        var_v0_3[-1].field_8 = 0;
        var_v0_3[-1].field_C = 0;
        var_v0_3[-1].field_0 = 0;
    } while (var_v0_3 != &D_800DDFA4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500C1E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_39690/func_1500C1E0.s")
