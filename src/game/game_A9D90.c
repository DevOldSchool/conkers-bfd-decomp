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
void func_15181D70(s32, s32);
extern s32 D_80082FA0;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507CD0C CURRENT (35) */
void func_1507CD0C(void *arg0) {
    s32 temp_a1;
    s32 temp_lo;

    temp_a1 = (u8 *)arg0 - &D_800CC2D0;
    temp_lo = temp_a1 / 812;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x120) = 3;
    if (D_80082FA0 >= temp_lo) {
        func_15181D70(temp_lo, temp_a1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507CD0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
typedef struct GameA9D90EntityIdRecord {
    u8 field_0;
    u8 pad_1[0x32B];
} GameA9D90EntityIdRecord;

extern GameA9D90EntityIdRecord D_800CC40F[];
void func_1509BFB0(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507D158 CURRENT (100) */
void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(3, temp_v0 | 0x2000, arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507D158 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D158.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")
void func_1503DE70(void *arg0, s32 arg1, s32 arg2);

void func_1507DB44(void *arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DE4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E114.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
