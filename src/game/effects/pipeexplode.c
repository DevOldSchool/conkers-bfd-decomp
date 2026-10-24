#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/pipeexplode.c
 * Boundary evidence: docs/evidence/boundaries/effects/effects_pipeexplode.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B2740
 * - func_150B2EB4
 * - func_150B3188
 * - func_150B37C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct PipeExplodeState {
    u8 pad0[0x1B];
    u8 unk1B;
} PipeExplodeState;

typedef struct PipeExplodeActor {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0x7A];
    PipeExplodeState *state;
} PipeExplodeActor;

#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B2740.s")
typedef struct {
    f32 field0, field4, field8, fieldC;
    f32 angle[3], scale[3], position[3], velocity[3], acceleration[3];
    f32 field4C;
    s32 flags;
    s16 duration, kind;
    u8 field58, pad59[3];
    s32 field5C;
    u8 color[9], pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 field72, field74;
    u8 pad76[6];
} PipeExplodePacket;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
f32 func_150ADA68(void);
extern f32 D_8009FB8C, D_8009FB90, D_8009FB94, D_8009FB98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B2EB4 CURRENT (1342) */
s32 func_150B2EB4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, s32 arg11, f32 arg12, s32 arg13, s32 arg14) {
    f32 cosYaw, sinYaw, cosPitch, sinPitch, cosTilt, magnitude;
    register f32 radial;
    PipeExplodePacket packet;
    s32 angle;

    cosYaw = func_151423D8(arg8 - 0x40);
    sinYaw = func_151423D8(((u8 *)&arg8)[3]);
    packet.flags = 0x9E8;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.angle[0] = 0.0f;
    packet.angle[1] = 0.0f;
    packet.angle[2] = 0.0f;
    packet.position[0] = *(&arg2);
    packet.position[1] = *(&arg3);
    packet.position[2] = arg4;
    packet.field4 = D_8009FB8C;
    magnitude = func_150ADA68() * 31.0f + 18.0f;
    angle = (s16)(arg9 + (s32)(60.0f * sinYaw * arg10 * arg12) - 0x40);
    cosPitch = func_151423D8(angle - 0x40);
    sinPitch = func_151423D8(angle);
    angle = (s16)((s32)(48.0f * cosYaw) - 0x14);
    cosTilt = func_151423D8(angle - 0x40);
    radial = magnitude * func_151423D8(angle);
    packet.velocity[0] = radial * cosPitch;
    packet.velocity[1] = -magnitude * cosTilt;
    packet.velocity[2] = radial * sinPitch;
    cosYaw = func_150ADA68() * 80.0f;
    packet.acceleration[1] = 0.0f;
    packet.acceleration[0] = cosYaw + -40.0f;
    packet.acceleration[2] = func_150ADA68() * 80.0f + -40.0f;
    packet.duration = 0x64;
    packet.field4C = func_150ADA68() * D_8009FB90 + D_8009FB94;
    packet.field0 = 1.0f;
    sinYaw = func_150ADA68() * 72.5f + D_8009FB98;
    packet.kind = 0x1C;
    packet.field58 = 0;
    packet.field8 = sinYaw;
    packet.field5C = 0;
    packet.color[0] = 0xFF;
    packet.color[1] = 1;
    packet.color[2] = 0;
    packet.color[3] = 0;
    packet.color[4] = 0;
    packet.color[5] = 0;
    packet.color[6] = 0;
    packet.color[7] = 0;
    packet.color[8] = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 1;
    packet.field74 = 0xFF;
    packet.fieldC = sinYaw;
    func_15132A4C(&packet, 3, 0xFF, 0, ((u8 *)&arg14)[3], 0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B2EB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B2EB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B3188.s")
s32 func_150B36AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 scale;

    *(f32 *)((u8 *)arg0 + 0x3C) = *(f32 *)((u8 *)arg0 + 0x10) + arg4;
    if (*(f32 *)((u8 *)arg0 + 0x170) < *(f32 *)((u8 *)arg0 + 0x48)) {
        *(s32 *)((u8 *)arg0 + 0x60) &= ~7;
        *(s32 *)((u8 *)arg0 + 0x60) &= ~8;
        *(s32 *)((u8 *)arg0 + 0x60) &= ~0x40;
        *(s32 *)((u8 *)arg0 + 0x60) &= ~0x20;
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        if (*(s16 *)((u8 *)arg0 + 0x64) > 0x20) {
            *(s16 *)((u8 *)arg0 + 0x64) = 0x20;
        }
    } else {
        scale = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x44) *= scale;
        *(f32 *)((u8 *)arg0 + 0x48) = -*(f32 *)((u8 *)arg0 + 0x48) * scale;
        *(f32 *)((u8 *)arg0 + 0x4C) *= scale;
        *(f32 *)((u8 *)arg0 + 0x50) *= scale;
        *(f32 *)((u8 *)arg0 + 0x54) *= scale;
        *(f32 *)((u8 *)arg0 + 0x58) *= scale;
    }
    return 1;
}
s32 func_150B378C(PipeExplodeActor *arg0) {
    s32 var_v1;
    PipeExplodeState *temp_v0 = arg0->state;

    var_v1 = arg0->unk1C << 4;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0->unk1B) {
        temp_v0->unk1B = var_v1;
    }
    return 1;
}
typedef struct {
    s32 flags;
    s16 life;
    u8 kind, reserved7;
    s32 frame, rate;
    u8 colors[6], reserved16[2];
    s32 renderMode;
    u8 inactiveOptions[12];
} PipeExplodeParticle;

typedef struct {
    f32 position[3];
    s16 life, flags;
    s32 mode;
    u8 reserved14, capacity, reserved16[2];
    u8 inactiveOptions[4];
} PipeExplodeTrail;

typedef struct {
    f32 width, velocityX, velocityY, velocityZ, acceleration;
    u8 reserved14[4];
    u8 flags, texture, color, alpha;
    u8 inactiveFade[4];
} PipeExplodeMotion;

typedef struct {
    s32 words[7];
    u8 colorMode, alphaMode, reserved1E[2];
} PipeExplodeRender;

typedef struct { s16 kind[3]; } PipeExplodeKinds;

extern PipeExplodeKinds D_80088700;

typedef struct PipeExplodeEntry {
    f32 x, y, z;
    u8 padC[8];
} PipeExplodeEntry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B37C8 CURRENT (830) */
s32 func_150B37C8(PipeExplodeActor *arg0, s32 arg1, s32 arg2, s32 arg3,
                   f32 arg4, s32 arg5) {
    u8 *state;
    PipeExplodeEntry *points;
    PipeExplodeParticle particle;
    f32 size;
    PipeExplodeKinds kinds;
    PipeExplodeTrail trail;
    PipeExplodeMotion motion;
    PipeExplodeRender render;

    state = (u8 *)arg0->state;
    points = *(PipeExplodeEntry **)((u8 *)arg0 + 0x94);
    kinds = D_80088700;
    state[0x20] = 4;
    size = func_150ADA68() * 50.0f + 50.0f;
    particle.kind = kinds.kind[func_150ADA20() % 3U];
    particle.frame = 0;
    particle.rate = 0;
    particle.flags = 0x11;
    particle.life = 0x96;
    particle.colors[0] = state[0x1B];
    particle.colors[1] = state[0x1A];
    particle.colors[2] = 0;
    particle.colors[3] = 0;
    particle.colors[4] = 0;
    particle.colors[5] = 0xFF;
    particle.renderMode = 0x30002;
    /* The disabled option flags leave these copied bytes unused. */
    func_1513C73C((s32)&particle, 1, 0, arg5, points[*(s8 *)((u8 *)arg0 + 0x2D)].x, arg4,
                  points[*(s8 *)((u8 *)arg0 + 0x2D)].z, size, size, func_150ADA20() & 0xFF,
                  (func_150ADA20() & 1) + (func_150ADA20() & 1), 0, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
    render.words[0] = 0;
    render.words[1] = 1;
    render.words[2] = 0x160600;
    render.words[3] = 3;
    render.words[4] = 0x10;
    render.words[5] = 0x80;
    render.words[6] = 0x20;
    render.colorMode = 0;
    render.alphaMode = 9;
    trail.mode = 1;
    trail.flags = 1;
    motion.texture = state[0x19];
    motion.flags = 8;
    motion.color = state[0x1A];
    motion.alpha = state[0x1B];
    size = arg4;
    trail.position[0] = points[*(s8 *)((u8 *)arg0 + 0x2D)].x;
    trail.position[1] = size;
    trail.position[2] = points[*(s8 *)((u8 *)arg0 + 0x2D)].z;
    trail.life = 0x3C;
    trail.capacity = ((u8 *)arg0)[0x25];
    motion.width = *(f32 *)state * 0.75f;
    motion.acceleration = *(f32 *)(state + 0x10);
    motion.velocityX = *(f32 *)(state + 4);
    motion.velocityY = func_150ADA68() * 15.0f + 15.0f;
    motion.velocityZ = *(f32 *)(state + 0xC);
    func_15147DA0(&trail, &motion, 0, 1, 7, 0, 0, 0, 0, 0, 0, &render, 0,
                  ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B37C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B37C8.s")
