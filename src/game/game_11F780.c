#include "types.h"

/*
 * Reviewed source unit: src/game/game_11F780.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F22D0
 * - func_150F2390
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad_0[0x1D4];
    s32 field_1D4;
} Game11F780State;

typedef struct {
    s32 fields[3];
} Game11F780Work;

void func_150F22D0(Game11F780Work *, void *, u8, void *);
void func_151C329C(Game11F780Work *, s32, s32);

void func_15143134(f32 *, f32 *, s32);
extern f32 D_800A1920;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F22D0 CURRENT (944) */
void func_150F22D0(Game11F780Work *arg0, void *arg1, u8 arg2, void *arg3) {
    s32 temp_t6;
    s32 var_v0;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {
    case 3:
        var_v0 = 0x29;
        break;
    case 4:
        var_v0 = 0x2D;
        break;
    case 5:
        var_v0 = 0x31;
        break;
    case 6:
        var_v0 = 0x35;
        break;
    case 7:
        var_v0 = 0x39;
        break;
    case 8:
        var_v0 = 0x3D;
        break;
    default:
        return;
    }
    func_15143134(&D_800A1920, (f32 *)arg0,
                  ((Game11F780State *)arg1)->field_1D4 + (var_v0 << 6));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F22D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F780/func_150F22D0.s")

s32 func_150F237C(s32 arg0, s32 arg1) {
    return 0xE;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2390 CURRENT (498) */
void func_150F2390(void *arg0, s32 arg1, void *arg2) {
    Game11F780Work sp1C;
    void *temp_a3;

    temp_a3 = arg0;
    if (((Game11F780State *)temp_a3)->field_1D4 != 0) {
        func_150F22D0(&sp1C, temp_a3, arg1, temp_a3);
        func_151C329C(&sp1C, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2390 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F780/func_150F2390.s")
