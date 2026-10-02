#include "types.h"

/*
 * Reviewed source unit: src/game/game_34ED0.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_80044B20;
extern u8 D_800B0DC0;
extern u8 D_800E9D00;

void func_15007A20(void) {
    func_100226F0(&D_800B0DC0, &D_800E9D00 - &D_800B0DC0);
    func_100226F0(&D_80044B20, 0x3E000);
}
