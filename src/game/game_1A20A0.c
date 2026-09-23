#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A20A0.c
 * Boundary evidence: docs/evidence/game_raw_model_debris_family.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15174BF0
 * - func_15174FA4
 * - func_15175390
 * - func_15175958
 * - func_1517685C
 * - func_15176B84
 * - func_15176DF0
 * - func_151770C8
 * - func_1517725C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174BF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174FA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517685C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15176B84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15176DF0.s")
typedef struct Game1770C8Packet {
    u8 bytes[0x30];
    f32 position[3];
    u8 pad[8];
} Game1770C8Packet;

void func_150A7790(void *, s32);
void func_150A8050(void *, s32, s32, s32);
s32 func_1510AEE0(void *, s32, s32, s32, f32, f32, f32, f32, s32, s32);
void *func_15176DF0(void *, void *, s16);
extern u8 D_800BE9C0;
extern f32 D_800D35E0;
extern f32 D_800D9B20;
extern u8 D_800D9C10[];
extern u8 D_800DDE80[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151770C8 CURRENT (3270) */
void *func_151770C8(u8 *arg0, u8 *arg1, s16 arg2) {
    Game1770C8Packet packet;
    u8 *var_s1;
    u8 temp_v0;

    var_s1 = arg0;
    if (func_1510AEE0(D_800D9C10 + (arg2 << 6),
                       *(s32 *)(arg1 + 0x98), *(s32 *)(arg1 + 0x9C),
                       *(s32 *)(arg1 + 0xA0), D_800D9B20, 4000.0f,
                       D_800D35E0, *(&D_800D35E0 + 1), 0, 0) == 0) {
        temp_v0 = arg1[0x91];
        switch (temp_v0) {
        case 0:
            func_150A8050(&packet, *(s32 *)(arg1 + 0xA8),
                           *(s32 *)(arg1 + 0xAC), *(s32 *)(arg1 + 0xB0));
            packet.position[0] = *(f32 *)(arg1 + 0x98);
            packet.position[1] = *(f32 *)(arg1 + 0x9C);
            packet.position[2] = *(f32 *)(arg1 + 0xA0);
            func_150A7790(&packet, (s32)(arg1 + (D_800BE9C0 << 6) + 0x10));
            *(s32 *)(var_s1 + 0) = 0xDA380003;
            *(void **)(var_s1 + 4) = arg1 + (D_800BE9C0 << 6) + 0x10;
            var_s1 += 8;
            *(s32 *)(var_s1 + 0) = 0xDB060004;
            *(s32 *)(var_s1 + 4) = *(s32 *)(D_800DDE80 + 0xCC);
            var_s1 += 8;
            *(s32 *)(var_s1 + 0) = 0xDE000000;
            *(s32 *)(var_s1 + 4) = *(s32 *)(D_800DDE80 + 0xD4);
            var_s1 += 8;
            break;
        default:
        case 1:
        case 2:
        case 3:
            var_s1 = func_15176DF0(var_s1, arg1, arg2);
            break;
        }
    }
    return var_s1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151770C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_151770C8.s")
typedef struct Game17725CState {
    u8 pad0[0x18];
    f32 scale;
    f32 increment;
    u8 pad20[4];
    f32 angle;
    f32 magnitude;
    u8 pad2C[4];
    f32 firstRadius;
    f32 secondRadius;
} Game17725CState;

typedef struct Game17725CEntry {
    u8 *model;
    u8 pad[0x10];
} Game17725CEntry;

f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern Game17725CState D_8008D0B0[];
extern f32 D_800A71AC;
extern f32 D_800A71B0;
extern f32 D_800A71B4;
extern f32 D_800A71B8;
extern Game17725CEntry D_800DDE88[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517725C CURRENT (1884) */
void func_1517725C(u8 arg0) {
    Game17725CState *state;
    u8 *model;
    f32 trig;
    f32 amount;
    s32 x;
    s32 y;
    s32 index;

    index = arg0;
    state = &D_8008D0B0[index];
    model = D_800DDE88[index].model;
    state->scale = func_150AD78C(state->angle * D_800A71AC) * state->magnitude;
    amount = state->scale * D_800A71B0;
    trig = func_150AD78C(amount);
    x = (s32)(state->firstRadius * func_150AD780(amount));
    y = (s32)(state->firstRadius * trig);
    *(s16 *)(model + 0xA0) = -x;
    *(s16 *)(model + 0xB0) = -x;
    *(s16 *)(model + 0x110) = x;
    *(s16 *)(model + 0x120) = x;
    *(s16 *)(model + 0x112) = y;
    *(s16 *)(model + 0x122) = y;
    *(s16 *)(model + 0xA2) = y;
    *(s16 *)(model + 0xB2) = y;
    state->scale = func_150AD78C((state->angle - 30.0f) * D_800A71B4) * state->magnitude;
    amount = state->scale * D_800A71B8;
    trig = func_150AD78C(amount);
    x = (s32)(state->secondRadius * func_150AD780(amount));
    y = (s32)(state->secondRadius * trig);
    *(s16 *)(model + 0xE0) = -x;
    *(s16 *)(model + 0x130) = x;
    *(s16 *)(model + 0xE2) = y;
    *(s16 *)(model + 0x132) = y;
    state->angle += state->increment;
    if (state->angle >= 360.0f) {
        state->angle -= 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517725C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517725C.s")
