#include "types.h"

/*
 * Reviewed source unit: src/game/game_156160.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15128CB0
 * - func_15129934
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game156160State {
    u8 pad0[0x23D];
    u8 field_23D;
} Game156160State;

typedef struct Game156160Record {
    u8 pad0[2];
    s16 field_2;
    f32 field_4;
    f32 field_8;
    u8 padC[0x18];
} Game156160Record;

extern s16 D_80089550;
extern f32 D_800A3610;
extern Game156160Record D_800DC028[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_156160/func_15128CB0.s")

void func_151298C0(Game156160State *arg0, s32 arg1) {
    if (D_80089550 != 0) {
        D_800DC028[arg0->field_23D].field_2 = 0;
        D_800DC028[arg0->field_23D].field_4 = -1.0f;
        D_800DC028[arg0->field_23D].field_8 = D_800A3610;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_156160/func_15129934.s")
