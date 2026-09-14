#include "types.h"

/*
 * Reviewed source unit: src/game/game_33660.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15006234
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game33660Table {
    void *items[4];
} Game33660Table;

void func_10023790(void *, void *, s32);
void func_100237C0(s32, void *, s32);
void func_15007644(void);
extern u8 D_800BE900[];
extern u8 D_800BE2D0[];
extern s32 D_800BE9E0;
extern Game33660Table D_800BE730;
extern u8 D_800BE748[];
extern u8 D_800BE74E[];
extern u8 D_800BE754[];
extern u8 D_800BE75A[];

void func_150061B0(void) {
    func_10023790(D_800BE900, D_800BE2D0, 8);
    func_100237C0(5, D_800BE900, D_800BE9E0);
    D_800BE730.items[0] = D_800BE748;
    D_800BE730.items[1] = D_800BE74E;
    D_800BE730.items[2] = D_800BE754;
    D_800BE730.items[3] = D_800BE75A;
    func_15007644();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_33660/func_15006234.s")
