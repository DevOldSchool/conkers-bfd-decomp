#include "types.h"

/*
 * Reviewed source unit: src/game/game_E7DE0.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BA930
 * - func_150BAA14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern f32 D_8009FE60;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BA930 CURRENT (30) */
s32 func_150BA930(f32 *arg0, u8 *arg1, void *arg2, u8 arg3) {
    f32 position[3];
    f32 value;

    arg0[0] = *(f32 *)(arg1 + 0x14);
    value = *(f32 *)(arg1 + 0x180);
    if (D_8009FE60 < value) {
        arg0[1] = value;
    } else {
        arg0[1] = *(f32 *)(arg1 + 0x18);
    }
    arg0[2] = *(f32 *)(arg1 + 0x1C);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 100.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 100.0f, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BA930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7DE0/func_150BA930.s")
s32 func_150BAA00(s32 arg0, s32 arg1) {
    return 9;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7DE0/func_150BAA14.s")
