#include "types.h"

/*
 * Reviewed source unit: src/game/game_32200.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

void *func_10003C40(s32, s32, s32, s32);
void func_10023A10(void *, void *, s32);
extern s32 D_80082FA0;
extern u8 D_80084300[];
extern void *D_800C3FC0;
extern void *D_800C3FC4[];

void func_15004D50(void) {
    void **var_s1;
    void *temp_v0;
    s32 var_s0;

    D_800C3FC0 = D_80084300;
    var_s0 = 1;
    if (D_80082FA0 > 0) {
        var_s1 = D_800C3FC4;
        do {
            temp_v0 = func_10003C40(0x50, 1, 2, 0);
            *var_s1 = temp_v0;
            func_10023A10(D_800C3FC0, temp_v0, 0x50);
            var_s0 += 1;
            var_s1 += 1;
        } while (D_80082FA0 >= var_s0);
    }
}
