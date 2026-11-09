#include "types.h"

/*
 * Reviewed source unit: src/game/game_CBAF0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_callback_families.md
 */

extern void func_1001263C(s32 arg0, s32 arg1, s32 arg2);
extern void func_151F2D6C(s32 arg0, s32 arg1);
extern void func_151F2BA8(void);
extern s32 D_800D3840;

s32 func_1509E640(s32 arg0, s32 arg1, s32 *arg2) {
    switch (arg1) {
    case 0: {
        s32 var_a1 = 0x7FFF;
        if (D_800D3840 >= 3) {
            var_a1 = arg2[2];
        }
        func_1001263C(arg0, var_a1, 0x40);
        return 1;
    }
    case 1:
        if (D_800D3840 == 4) {
            func_151F2D6C(arg2[2], arg2[3]);
        } else {
            func_151F2D6C(arg2[2], 0);
        }
        return 1;
    case 2:
        func_151F2BA8();
        return 1;
    default:
        return 0;
    }
}
s32 func_151F2CDC();                                /* extern */

s32 func_1509E6F0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return func_151F2CDC() == 1;
    }
    return 0;
}
