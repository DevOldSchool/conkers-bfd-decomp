#include "types.h"

/*
 * Reviewed source unit: src/game/game_188F90.c
 * Boundary evidence: docs/evidence/game_reconciled_pointer_singleton_15bae0.md
 */

void func_1516972C(u8 *);
s32 func_1514401C(u8, void *, void *, u8);
extern s32 (*D_8008B078[])(u8 *);
extern s32 (*D_8008B07C[])(u8 *);
extern s32 D_800BE9E4;

void func_1515BAE0(u8 *arg0) {
    s8 temp_v0;
    struct { s8 value; } temp_v0_2;
    u8 var_v1;

    var_v1 = 0;
    if (arg0[0x11] & 1) {
        *(s16 *)(arg0 + 0x14) =
            (s16)(*(s16 *)(arg0 + 0x14) - D_800BE9E4);
        if (*(s16 *)(arg0 + 0x14) < 0) {
            var_v1 = 1;
        }
    }
    if (var_v1 == 0) {
        temp_v0 = *(s8 *)(arg0 + 0x38);
        if (temp_v0 != -1) {
            if (D_8008B078[temp_v0](arg0) == 0) {
                var_v1 = 1;
            }
        }
        if (*(s32 *)(arg0 + 0x1C) != 0) {
            var_v1 = func_1514401C(arg0[0x10], arg0 + 0x1C,
                                   arg0 + 0x18, arg0[0x12]);
        }
    }
    if (var_v1 != 0) {
        (temp_v0_2.value) = *(s8 *)(arg0 + 0x39);
        if ((temp_v0_2.value) != -1) {
            if (D_8008B07C[(temp_v0_2.value)](arg0) != 0) {
                func_1516972C(arg0);
            }
        } else {
            func_1516972C(arg0);
        }
    }
}
