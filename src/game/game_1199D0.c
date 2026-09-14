#include "types.h"

/*
 * Reviewed source unit: src/game/game_1199D0.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EC520
 * - func_150EC6B0
 * - func_150ECA68
 * - func_150ECC70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150EC520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150EC6B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150ECA68.s")
void func_150ECB4C(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

typedef struct Game1199D0Actor {
    s32 field_0;
    u8 pad4[0x37];
    u8 field_3B;
} Game1199D0Actor;

typedef struct Game1199D0Params {
    Game1199D0Actor *actor;
    u8 field_4;
    u8 field_5;
    u8 field_6;
    u8 field_7;
    u8 field_8;
    u8 field_9;
} Game1199D0Params;

typedef struct Game1199D0State {
    u8 pad0[0xE];
    s16 field_E;
    u8 pad10[0x18];
    Game1199D0Params params;
} Game1199D0State;

void func_1502EA98(Game1199D0Actor *, u8, u8, u8, s32, s32, s32);

void func_150ECB8C(Game1199D0State *arg0) {
    Game1199D0Params *params = &arg0->params;
    Game1199D0Actor *actor = arg0->params.actor;

    if ((actor->field_0 == 0) || (actor->field_3B != params->field_4)) {
        arg0->field_E = -1;
        return;
    }
    func_1502EA98(actor, params->field_5, params->field_6, params->field_7,
                  params->field_8, 0, params->field_9);
}
void func_150ECA68(void *, u8, u8, u8, u8, u8, s16, u8, s32);
void func_151C9AC0(void *, u8, s32);

void func_150ECC00(void *arg0, u8 arg1, s32 arg2) {
    func_151C9AC0(arg0, arg1, arg2);
    func_150ECA68(arg0, 0, 0xFF, 0, 0xFF, 4, -1, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150ECC70.s")
