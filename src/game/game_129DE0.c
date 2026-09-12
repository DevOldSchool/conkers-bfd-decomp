#include "types.h"

/*
 * Reviewed source unit: src/game/game_129DE0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 */

s32 func_150FC930(void *arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 == 0x12) || (temp_v0 == 0x23) || (temp_v0 == 0x73) || (temp_v0 == 0x8A)) {
        return 0;
    }
    return 1;
}
void func_150FC974(void *arg0);
void func_1516972C(void *arg0);
void func_1514933C(s32 arg0);

void func_150FC974(void *arg0) {
    volatile void **field_38 = (volatile void **)((u8 *)arg0 + 0x38);

    if (*field_38 != 0) {
        func_1516972C((void *)*field_38);
    }
}
void func_150FC9A4(s32 arg0) {
    func_150FC974((void *)arg0);
    func_1514933C(arg0);
}
