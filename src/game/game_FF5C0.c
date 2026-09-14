#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF5C0.c
 * Boundary evidence: docs/evidence/game_raw_periodic_actor_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D2110
 * - func_150D21CC
 * - func_150D22F4
 * - func_150D2374
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FF5C0/func_150D2110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF5C0/func_150D21CC.s")
void func_150D22D4(s32 arg0);
void func_15149368(s32 arg0);

void func_150D227C(s32 arg0) {
    func_150D22D4(arg0);
    func_1514933C(arg0);
}
void func_150D22A8(s32 arg0) {
    func_150D22D4(arg0);
    func_15149368(arg0);
}
extern u8 D_800D9900;

void func_150D22D4(s32 arg0) {
    D_800D9900--;
}
typedef struct GameFF5C0Params {
    u8 pad0[0x28];
    u8 field_28;
    u8 pad29[0x13];
    u8 field_3C;
    u8 field_3D;
} GameFF5C0Params;

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D22F4 CURRENT (100) */
s32 func_150D22F4(s32 arg0, GameFF5C0Params *arg1, s16 arg2) {
    if (arg1->field_28 == 1) {
        arg0 = func_1517F08C(arg0, arg1->field_3C, 0xFF, 0xFF, 0xFF, arg2);
    } else {
        arg0 = func_1517F08C(arg0, arg1->field_3D, 0, 0, 0, arg2);
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D22F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF5C0/func_150D22F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF5C0/func_150D2374.s")
