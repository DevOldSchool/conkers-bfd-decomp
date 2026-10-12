#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1199D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EC520
 * - func_150EC6B0
 * - func_150ECA68
 * - func_150ECC70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151432BC(s32, f32 *, f32 *, f32 *, s32);
void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A1570;
extern f32 D_800A1574;
extern f32 D_800BE9A4;

typedef struct Game1199D0Motion {
    f32 value68;
    f32 value6C;
    s32 value70;
    f32 value74;
    f32 value78;
} Game1199D0Motion;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EC520 CURRENT (262) */
void func_150EC520(u8 *arg0, void *arg1) {
    Game1199D0Motion motion;
    u8 *state;
    s32 spawned;

    if (func_151464B8(*(s32 *)(arg0 + 0x30), arg1) == 0) {
        state = arg0 + 0x28;
        *(f32 *)(state + 0xC) +=
            (D_800A1570 + func_150ADA68() * D_800A1574) *
            *(f32 *)(state + 4) * D_800BE9A4;
        if (*(f32 *)(state + 0xC) > 1.0f) {
            motion.value78 = 0.0f;
            do {
                func_151432BC(*(s32 *)state, &motion.value6C, &motion.value74,
                               &motion.value68, (s32)&motion.value70);
                spawned = func_15149130((s16)((func_150ADA20() % 131U) + 0x50),
                                         -1, 0x5A, -1, 1, 0, 0x10,
                                         arg0[0xC], arg0[1]);
                if (spawned != 0) {
                    func_10022EC0((u8 *)spawned + 0x28, &motion.value6C, 0x10);
                }
                *(f32 *)(state + 0xC) -= 1.0f;
            } while (*(f32 *)(state + 0xC) > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EC520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150EC520.s")
typedef struct GameEC6B0Vector { s32 x, y, z; } GameEC6B0Vector;
typedef struct GameEC6B0Packet {
    u32 field00, field04;
    s16 field08, field0A;
    u32 field0C, field10;
    u8 field14, field15, field16, field17;
    u8 field18, field19, field1A, field1B, field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, scaleX, scaleY;
    GameEC6B0Vector position;
    f32 field3C, field40, field44, field48, field4C, field50, speed;
    u32 flags;
    u8 pad5C[4];
    s8 field60, field61, field62, field63, field64, field65;
    u8 pad66[0xA];
} GameEC6B0Packet;
typedef struct GameEC6B0Extension {
    u8 field0, field1, field2, field3;
    f32 x, y, z;
} GameEC6B0Extension;
typedef struct GameEC6B0State {
    GameEC6B0Vector position;
    f32 counter;
} GameEC6B0State;
extern f32 D_800A1578, D_800A157C, D_800A1580;
extern f32 D_800A1584, D_800A1588, D_800A158C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EC6B0 CURRENT (2136) */
void func_150EC6B0(u8 *arg0) {
    s32 firstFlip;
    GameEC6B0Packet packet;
    GameEC6B0Extension extension;
    s32 secondFlip;
    GameEC6B0State *state;
    void *result;
    f32 baseSpeed;
    f32 speedRange;

    state = (GameEC6B0State *)(arg0 + 0x28);
    state->counter += (1352.0f + func_150ADA68() * D_800A1578) * D_800A157C * D_800BE9A4;
    if (state->counter > 1.0f) {
        packet.field1D = 0x6C;
        packet.field08 = 0x5103;
        packet.field00 = 0x200005;
        packet.field1E = 0x46;
        packet.field20 = 3;
        packet.flags = 0x80DE07;
        packet.field60 = 8;
        packet.field61 = 6;
        extension.field0 = 0;
        extension.field1 = 0;
        packet.field04 = 0;
        packet.field0C = 0;
        packet.field10 = 0;
        packet.field62 = 0x16;
        packet.field63 = -1;
        packet.field64 = -1;
        packet.field65 = 0;
        packet.field22 = 0x46;
        packet.field14 = 0x47;
        packet.field15 = 0xC2;
        packet.field16 = 0;
        packet.field17 = 0xFF;
        packet.field18 = 0xC0;
        packet.field19 = 0x49;
        packet.field1A = 0;
        packet.field1C = 0xFF;
        extension.z = D_800A1580;
        packet.field24 = D_800A1584;
        packet.position = state->position;
        baseSpeed = D_800A1588;
        speedRange = D_800A158C;
        packet.field3C = 0.0f;
        packet.field40 = 0.0f;
        packet.field44 = 0.0f;
        packet.field48 = 0.0f;
        packet.field4C = 0.0f;
        packet.field50 = 0.0f;
        do {
            extension.field2 = func_150ADA20() % 5U + 4;
            extension.field3 = func_150ADA20() % 5U + 4;
            extension.x = func_150ADA68() * 11.0f;
            extension.y = func_150ADA68() * 11.0f;
            packet.speed = func_150ADA68() * speedRange + baseSpeed;
            packet.flags &= ~0xC0;
            firstFlip = func_150ADA20() & 1 ? 0x80 : 0;
            secondFlip = func_150ADA20() & 1 ? 0x40 : 0;
            packet.flags |= secondFlip | firstFlip;
            packet.field1B = func_150ADA20() % 101U + 0x64;
            packet.field0A = func_150ADA20() % 51U + 0x50;
            packet.scaleX = packet.scaleY = func_150ADA68() * 80.0f + 92.0f;
            result = func_15130280(&packet, 0, NULL, 0x10, arg0[0xC], arg0[1]);
            if (result != NULL) func_10022EC0((u8 *)result + 0xA8, &extension, 0x10);
            state->counter -= 1.0f;
        } while (state->counter > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EC6B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150EC6B0.s")
void *func_10022EC0(void *, const void *, u32);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ECA68 CURRENT (125) */
void func_150ECA68(void *arg0, u8 arg1, u8 arg2, u8 arg3,
                   u8 arg4, u8 arg5, s16 arg6, u8 arg7, s32 arg8) {
    s32 var_v1;
    s16 temp_t2;
    Game1199D0SpawnParams params;
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

void func_150ECC00(void *arg0, u8 arg1, s32 arg2) {
    func_151C9AC0(arg0, arg1, arg2);
    func_150ECA68(arg0, 0, 0xFF, 0, 0xFF, 4, -1, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1199D0/func_150ECC70.s")
