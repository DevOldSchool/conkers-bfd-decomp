#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EC0E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md
 */

s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

s32 func_150BEC30(f32 *arg0, void *arg1, void *arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x19;
        break;
    case 5:
        var_a1 = 0x16;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
    default:
        var_a1 = 0x10;
        break;
    }
    func_15142314((void *)*(s32 *)((u8 *)arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, arg2);
}

s32 func_150BED28(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x12;
    }
    return -1;
}
s32 func_150BEC30(f32 *, void *, void *, u8);
void func_15141F78(s32, void *, f32, s32, f32 *, s32);
extern f32 D_800A00D0;
extern f32 D_800A00D4;
extern f32 D_800A00D8;

void func_150BED4C(void *arg0, s32 arg1, s32 arg2) {
    f32 position[3];
    s32 work[9];

    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
    if (func_150BEC30(position, arg0, work, (u8)arg1) != 0) {
        func_15141F78(0xB, work,
                      (f32)arg2 * D_800A00D0 * 2,
                      (u32)(*(f32 *)((u8 *)arg0 + 0x40) * D_800A00D4) & 0xFF,
                      position, (u8)arg1);
        if (arg2 >= 0x4C) {
            func_15142180(2, position, work[6], 3.232f, D_800A00D8);
        }
    }
}
