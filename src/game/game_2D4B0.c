#include "types.h"

/*
 * Reviewed source unit: src/game/game_2D4B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

void func_1000E934(void);
void func_10023790(void *, void *, s32);
void func_10008570(s32, u8 *);
void func_100085A4(s32, s32, s32);
extern u8 D_80041E58[];
extern u8 D_80041EA0[];

void func_15000000(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_10023790((D_80041E58 + i * 0x18), (D_80041EA0 + i * 0x20), 8);
        func_10008570(i & 0xFF, (D_80041E58 + i * 0x18));
    }
    func_100085A4(0, 6, 1);
    func_1000E934();
}
