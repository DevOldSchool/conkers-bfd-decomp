#include "types.h"

/*
 * Reviewed source unit: src/game/game_173D40.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15146970
 * - func_15146A98
 * - func_15146BF8
 * - func_15146D60
 * - func_15146E84
 * - func_15147040
 * - func_151470FC
 * - func_15147318
 * - func_15147478
 * - func_151475D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15142314(s32, s32, void *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

s32 func_15146890(f32 *arg0, void *arg1, s32 arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a1 = 0x13;
    } else {
        var_a1 = 0x17;
    }
    func_15142314(*(s32 *)((u8 *)arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C((void *)arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, (void *)arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146A98.s")
void func_15146BF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15146BB8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8(arg0, arg1, arg2, 0);
}
void func_15146BD8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8(arg0, arg1, arg2, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146BF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146D60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146E84.s")
s32 func_15146890(f32 *, void *, s32, u8);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147040 CURRENT (210) */
void func_15147040(void *arg0, s32 arg1, s32 arg2) {
    f32 coordinates[3];
    s16 sp42;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        func_15146890(coordinates, arg0, 0, (u8)arg1);
        sp42 = (s16)((func_150ADA20() % 11U) + 5);
        func_1514C678(coordinates[0], coordinates[1], *(s32 *)&coordinates[2], func_150ADA68() * 11.0f,
                      0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147040 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147040.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_151470FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147318.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147478.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_151475D8.s")
