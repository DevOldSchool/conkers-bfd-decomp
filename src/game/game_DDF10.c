#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_DDF10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B0A60
 * - func_150B0D20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150ADA68();                                /* extern */
extern f32 D_8009F870;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B0A60 CURRENT (1840) */
void func_150B0A60(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, s16 *arg5) {
    f32 sp1C;
    f32 temp_fa0;
    f32 var_fv0;
    f32 x;

    *arg5 = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40) * D_8009F870) - 128.0f);
    sp1C = func_150ADA68() * 248.0f;
    temp_fa0 = func_150ADA68() + -0.5f;
    if (sp1C < 122.0f) {
        x = (f32) ((*(f32 *)((u8 *)arg3 + 0) * temp_fa0 * 122.0f) + (*(f32 *)((u8 *)arg2 + 0) * -31.5f));
        *(f32 *)((u8 *)arg4 + 4) = 0.0f;
        *(f32 *)((u8 *)arg4 + 0) = x;
        *(f32 *)((u8 *)arg4 + 8) = (f32) ((*(f32 *)((u8 *)arg3 + 4) * temp_fa0 * 122.0f) + (*(f32 *)((u8 *)arg2 + 4) * -31.5f));
    } else {
        f32 magnitude = 61.0f;
        var_fv0 = magnitude;
        sp1C -= 122.0f;
        if (sp1C < 63.0f) {
            var_fv0 = -magnitude;
            *arg5 += 0x40;
        } else {
            *arg5 -= 0x40;
        }
        x = (f32) ((*(f32 *)((u8 *)arg3 + 0) * var_fv0) + (*(f32 *)((u8 *)arg2 + 0) * 63.0f * temp_fa0));
        *(f32 *)((u8 *)arg4 + 4) = 0.0f;
        *(f32 *)((u8 *)arg4 + 0) = x;
        *(f32 *)((u8 *)arg4 + 8) = (f32) ((*(f32 *)((u8 *)arg3 + 4) * var_fv0) + (*(f32 *)((u8 *)arg2 + 4) * 63.0f * temp_fa0));
    }
    *(f32 *)((u8 *)arg4 + 0) = (f32) (*(f32 *)((u8 *)arg4 + 0) + *(f32 *)((u8 *)arg0 + 0x14));
    *(f32 *)((u8 *)arg4 + 4) = (f32) (*(f32 *)((u8 *)arg4 + 4) + *(f32 *)((u8 *)arg1 + 0x118));
    *(f32 *)((u8 *)arg4 + 8) = (f32) (*(f32 *)((u8 *)arg4 + 8) + *(f32 *)((u8 *)arg0 + 0x1C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B0A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0A60.s")
extern void func_150B0C58(void *arg0, u8 arg1, s32 arg2);

void func_150B0C34(void *arg0) {
    func_150B0C58(arg0, 0xFF, 1);
}
void *func_10022EC0(void *, const void *, u32);
typedef struct GameDDF10B0C58Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} GameDDF10B0C58Packet;

void func_150B0C58(void *arg0, u8 arg1, s32 arg2) {
    GameDDF10B0C58Packet packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x58, -1, 0, 0x43, 0xC, arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
}
void func_150B0CE0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_150B0A60(void *, void *, void *, void *, void *, s16 *);
void func_1514373C(f32, f32, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
u32 func_150ADA20(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                  f32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_8009F860[], D_8009F868[];
extern f32 D_8009F874, D_8009F878, D_8009F87C, D_8009F880, D_8009F884;
extern f32 D_8009F888, D_8009F88C, D_8009F890, D_8009F894;
extern f32 D_800A5480[3], D_800BE9A4;
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B0D20 CURRENT (774) */
void func_150B0D20(u8 *arg0) {
    f32 randomSize;
    u8 *owner;
    f32 randomAlpha;
    f32 randomRange, velocityScale, scale;
    f32 forward[2], side[2];
    u8 *motion;
    f32 position[3], velocity[3];
    s16 angle;
    u32 choice, other;
    GameDDF10B0C58Packet *state;
    u8 *player;

    owner = *(u8 **)(arg0 + 0x28);
    state = (GameDDF10B0C58Packet *)(arg0 + 0x28);
    if (*(s32 *)owner == 0 || state->type != owner[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    player = D_800CC2D0 + owner[0x124] * 0x32C;
    choice = 0;
    if ((*(u8 **)(player + 0x31C))[0x4F] == 2) {
        randomSize = *(f32 *)(owner + 0x3C);
        randomAlpha = *(f32 *)(player + 0x44) * D_8009F874;
        if (randomSize < randomAlpha) {
            randomSize = randomAlpha;
        }
        if (randomSize > 26.0f) {
            choice = 1;
        }
    }
    if (choice != 0) {
        state->value += (D_8009F860[choice] + func_150ADA68() * D_8009F868[choice]) * D_800BE9A4;
        if (state->value > 1.0f) {
            if (func_1515C0F8((struct Game1890A0State *)owner, &motion) == 0) {
                motion = (u8 *)D_800A5480;
            }
            func_1514373C(*(f32 *)(owner + 0x40) * D_8009F878, 1.0f,
                          &forward[0], &forward[1]);
            randomRange = D_8009F87C;
            scale = D_8009F880;
            side[1] = -forward[0];
            velocityScale = D_8009F884;
            side[0] = forward[1];
            do {
                func_150B0A60(owner, player, forward, side, position, &angle);
                choice = func_150ADA20();
                randomAlpha = func_150ADA68() * randomRange;
                func_15143794(angle, (s16)(choice % 26U - 41),
                              randomSize = (randomSize = D_8009F888) + randomAlpha, velocity);
                velocity[0] -= *(f32 *)(motion + 0) * velocityScale;
                velocity[2] -= *(f32 *)(motion + 8) * velocityScale;
                randomSize = func_150ADA68();
                other = func_150ADA20();
                choice = func_150ADA20();
                randomAlpha = func_150ADA68();
                func_151D9014(position, velocity, 5,
                              randomSize * D_8009F88C + D_8009F890,
                              other % 21U + 20, choice % 101U + 155,
                              randomAlpha * 50.0f + 80.0f,
                              func_150ADA68() < D_8009F894,
                              scale, scale, 1, 0, 1, 0, arg0[0xC], arg0[1]);
                state->value -= 1.0f;
            } while (state->value > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B0D20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDF10/func_150B0D20.s")
