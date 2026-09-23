#include "types.h"

/*
 * Reviewed source unit: src/game/game_803A0.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052F9C
 * - func_1505327C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, f32, f32, f32, f32, s32);

void func_15052EF0(u8 *arg0) {
    *(s8 *)((u8 *)arg0 + 0x125) = 0x64;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    func_1505E650(arg0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}
extern u8 D_800CC2D0[];

void func_15052F58(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = D_800CC2D0 + (arg0 * 0x32C);
    temp_v0[0x13C] = 0;
    *(s32 *)(temp_v0 + 0x218) = 0;
    temp_v0[0x232] = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_15052F9C.s")
void func_15043FF0(f32 *, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505327C CURRENT (1140) */
void func_1505327C(u8 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    u8 *actor;
    u8 *object;
    struct {
        u8 pad[8];
        f32 position[3];
    } local;

    actor = (arg0[0x124] * 0x32C) + D_800CC2D0;
    if (actor[0x89] != 0 || actor[0x104] != 0) {
        return;
    }
    object = *(u8 **)(actor + 0x31C);
    if (object == 0 || object[0x6B] == 0) {
    actor[0x125] = 0xFF;
    *(f32 *)(actor + 0x20) = arg1;
    *(f32 *)(actor + 0x24) = arg2;
    actor[0x83] = 0xFF;
    actor[0x89] = 0xFF;
    *(u16 *)(actor + 0x76) = *(u16 *)(arg0 + 0x7A);
    *(s32 *)(arg0 + 0x218) = 0;
    arg0[0x232] = arg3;
    func_1505E650(actor, 0x32, 0x3FA66666, 0x40800000, 0.0f, 0.0f, 0);
    (*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C))[0x30] = 0x46;
    *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x28) = *(f32 *)(arg0 + 0x14);
    *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x2C) = *(f32 *)(arg0 + 0x1C);
    if (*(s32 *)(arg0 + 0x1D4) != 0 && arg4 != -1) {
        func_15043FF0(local.position, *(u8 **)(arg0 + 0x1D4) + (arg4 << 6));
        *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x28) = local.position[0];
        *(f32 *)(*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C) + 0x2C) = local.position[2];
    }
    (*(u8 **)(D_800CC2D0 + (arg0[0x124] * 0x32C) + 0x31C))[0x27] = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505327C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_1505327C.s")
