#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DBB60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

void func_10010FFC(s32, s32, s32, s32, s32, void *);
s32 func_15045800(f32 *, u16, f32, void *);
void func_151ABE40(f32 *, void *, s32, u8, s32);
extern f32 D_800A9D70;

void func_151AE6B0(void *arg0) {
    u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    {
        f32 position[3];
        f32 height;

        position[0] = *(f32 *)(object + 0x14);
        height = *(f32 *)(object + 0x118);
        if (D_800A9D70 < height) {
            position[1] = height + 100.0f;
        } else {
            position[1] = *(f32 *)(object + 0x18) + 150.0f;
        }
        position[2] = *(f32 *)(object + 0x1C);
        if (func_15045800(position, 0, position[1] - 300.0f, (u8 *)arg0 + 0x34) != 0) {
            position[1] = *(f32 *)((u8 *)arg0 + 0x34);
            func_151ABE40(position, (u8 *)arg0 + 0x34, 5, *(u8 *)((u8 *)arg0 + 0xC),
                          *(u8 *)((u8 *)arg0 + 1));
            func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
        }
    }
}
