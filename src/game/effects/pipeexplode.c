#include "types.h"

/*
 * Reviewed source unit: src/game/effects/pipeexplode.c
 * Boundary evidence: docs/evidence/effects_pipeexplode.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B2740
 * - func_150B2EB4
 * - func_150B3188
 * - func_150B36AC
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
f32 func_151423D8(u8);
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B36AC CURRENT (2535) */
s32 func_150B36AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    if (*(f32 *)((u8 *)arg0 + 0x170) < temp_fv0) {
        temp_t7 = *(s32 *)((u8 *)arg0 + 0x60) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t7;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t9;
        *(s32 *)((u8 *)arg0 + 0x60) = temp_t1;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (temp_t1 & ~0x20);
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        if (*(s16 *)((u8 *)arg0 + 0x64) >= 0x21) {
            *(s16 *)((u8 *)arg0 + 0x64) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (-temp_fv0 * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B36AC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B36AC.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/pipeexplode/func_150B37C8.s")
