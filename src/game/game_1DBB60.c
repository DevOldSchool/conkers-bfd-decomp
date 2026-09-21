#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DBB60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AE6B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1DBB60Vec3;

void func_10010FFC(s32, s32, s32, s32, s32, void *);
s32 func_15045800(f32 *, u16, f32, void *);
void func_151ABE40(f32 *, void *, s32, u8, s32);
extern f32 D_800A9D70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE6B0 CURRENT (502) */
void func_151AE6B0(void *arg0) {
    u8 *object;
    f32 position[3];
    void *sp28;
    f32 height;
    void *target;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position[0] = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A9D70 < height) {
        position[1] = height + 100.0f;
    } else {
        position[1] = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp28 = target;
    position[2] = *(f32 *)(object + 0x1C);
    if (func_15045800(position, 0, position[1] - 300.0f, target) != 0) {
        position[1] = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(position, sp28, 5,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE6B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DBB60/func_151AE6B0.s")
