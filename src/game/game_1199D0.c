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
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1199D0SpawnParams {
    void *actor;
    u8 field_4;
    s8 field_5;
    s8 field_6;
    s8 field_7;
    u8 field_8;
    u8 field_9;
    u8 padA[2];
} Game1199D0SpawnParams;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ECA68 CURRENT (1046) */
void func_150ECA68(void *arg0, u8 arg1, u8 arg2, u8 arg3,
                   u8 arg4, u8 arg5, s16 arg6, u8 arg7, s32 arg8) {
    Game1199D0SpawnParams params;
    s16 var_v1;
    s16 temp_t2;
    s32 temp_v0;
    s32 var_v0;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t9;

    params.actor = arg0;
    temp_t9 = *(u8 *)((u8 *)arg0 + 0x3B);
    temp_t2 = arg6;
    temp_t0 = arg4;
    temp_t1 = arg5;
    params.field_5 = arg1;
    params.field_6 = arg2;
    params.field_7 = arg3;
    params.field_4 = temp_t9;
    params.field_8 = temp_t0;
    params.field_9 = temp_t1;
    if (temp_t2 == -1) {
        var_v1 = 0x12C;
    } else {
        var_v1 = temp_t2;
    }
    if (temp_t2 == -1) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    temp_v0 = func_15149130((s16)var_v1, -1, 0x5D, -1, var_v0,
                             0x45, 0xC, arg7, arg8);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &params, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ECA68 */
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
