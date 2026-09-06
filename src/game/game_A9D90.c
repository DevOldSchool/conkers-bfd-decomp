#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9D90.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507C8FC
 * - func_1507CD0C
 * - func_1507CD64
 * - func_1507D158
 * - func_1507D1D8
 * - func_1507D4F8
 * - func_1507D754
 * - func_1507DB44
 * - func_1507DB6C
 * - func_1507DE4C
 * - func_1507DF10
 * - func_1507DFE4
 * - func_1507E114
 * - func_1507E1D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA9D90Inner {
    u8 pad0[0x120];
    u8 field_120;
    u8 pad121[3];
    s16 field_124;
} GameA9D90Inner;

typedef struct GameA9D90Object {
    u8 pad0[0x31C];
    GameA9D90Inner *field_31C;
} GameA9D90Object;

void func_1507C8E0(GameA9D90Object *arg0, s32 arg1) {
    arg0->field_31C->field_120 = 2;
    arg0->field_31C->field_124 = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D158.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DE4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
