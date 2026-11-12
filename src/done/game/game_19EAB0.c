#include "types.h"

/*
 * Reviewed source unit: src/game/game_19EAB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

void func_151717FC(void *, f32, f32, f32, f32, f32, s32, s32, s32, s32, f32, u8, s32);
extern f32 D_800A6FC0;
extern f32 D_800A6FC4;

void func_15171600(void *arg0, u8 arg1, s32 arg2) {
    switch (*((u8 *)arg0 + 0x72)) { /* irregular */
    case 0xEB:
        func_151717FC(arg0, 400.0f, 500.0f, 0.0f, D_800A6FC0, 0.0f, 2, 5, 0x14, 0x14, 1.0f, arg1, arg2);
        return;
    case 0xF6:
        func_151717FC(arg0, 200.0f, 400.0f, -1800.0f, -1000.0f, -1200.0f, 2, 5, 4, 0xA, 1.0f, arg1, arg2);
        return;
    case 0xF8:
        func_151717FC(arg0, 100.0f, 160.0f, -2500.0f, D_800A6FC4, 0.0f, 2, 5, 4, 4, 0.5f, arg1, arg2);
        return;
    case 0xF9:
        func_151717FC(arg0, 200.0f, 100.0f, 100.0f, -300.0f, 0.0f, 1, 5, 4, 4, 1.0f, arg1, arg2);
        return;
    }
}
void func_151700D8(f32 *, f32, f32, s32, f32, s32, s32, s32, s32, s32);

void func_151717FC(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, u8 arg11, s32 arg12) {
    f32 vertices[4][3];
    f32 x;
    f32 y;
    f32 z;

    x = *(s16 *)((u8 *)arg0 + 0x10) + arg3;
    y = *(s16 *)((u8 *)arg0 + 0x12) + arg4;
    z = *(s16 *)((u8 *)arg0 + 0x14) + arg5;
    vertices[0][0] = arg1 + x;
    vertices[0][1] = y;
    vertices[0][2] = arg2 + z;
    vertices[1][0] = x - arg1;
    vertices[1][1] = y;
    vertices[1][2] = arg2 + z;
    vertices[2][0] = x - arg1;
    vertices[2][1] = y;
    vertices[2][2] = z - arg2;
    vertices[3][0] = arg1 + x;
    vertices[3][1] = y;
    vertices[3][2] = z - arg2;
    func_151700D8(vertices[0], x, z, arg7, arg10, arg6, arg8, arg9, arg11, arg12);
}
