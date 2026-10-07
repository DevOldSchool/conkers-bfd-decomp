#include "types.h"

/*
 * Reviewed source unit: src/game/game_F9430.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_particle_composite.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CBF80
 * - func_150CC6B8
 * - func_150CCCB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CBF80.s")
extern f32 D_800BE9A4;

s32 func_150CC638(u8 *arg0) {
    f32 temp_fv0;
    u8 *subrecord;
    s32 temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        subrecord = arg0 + 0x128;
        if (*(s16 *)(arg0 + 0x1C) < 0x20) {
            temp_v0 = *(s16 *)(arg0 + 0x1C) * 8;
            if (temp_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v0;
            }
        }
        if (*(s16 *)subrecord < *(s16 *)((u8 *)arg0 + 0x1C)) {
            temp_fv0 = *(f32 *)(subrecord + 4) * D_800BE9A4;
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
        }
    }
    return 1;
}
typedef struct GameF9430Particle {
    s32 flags, field4;
    s16 kind, duration;
    s32 fieldC, field10;
    u8 color0[4], color1[4];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, size0, size1;
    f32 position[3];
    u8 pad3C[0xC];
    f32 direction[3];
    f32 field54;
    s32 flags58;
    u8 pad5C[4];
    u8 field60, field61, field62;
    s8 field63;
    u8 pad64[0xC];
} GameF9430Particle;

void *func_10022EC0(void *, const void *, u32);
void *func_15130374(s32, u8, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A06CC, D_800A06D0, D_800A06D4, D_800A06D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CC6B8 CURRENT (400) */
s32 func_150CC6B8(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    void *temp_v0;
    GameF9430Particle packet;
    f32 size;
    f32 sp2C;
    f32 magnitude;
    u32 sp24;

    packet.field1D = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = (func_150ADA20() & 0xF) + 0x14;
    packet.fieldC = 0;
    packet.field10 = 0;
    packet.color1[0] = 0xB0;
    packet.color1[1] = 0xA0;
    packet.color1[2] = 0x2A;
    packet.color0[0] = 0x40;
    packet.color0[1] = 0xB;
    packet.color0[2] = 0x6A;
    packet.color0[3] = 0xFF;
    packet.color1[3] = (func_150ADA20() % 156U) + 0x64;
    packet.field1C = 0xFF;
    packet.field60 = 3;
    packet.field61 = 3;
    size = (func_150ADA68() * D_800A06CC) + 300.0f;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.position[2] = arg4;
    packet.size0 = size;
    packet.size1 = size;
    sp24 = func_150ADA20();
    magnitude = ((func_150ADA68() * 200.0f) + 350.0f) * D_800A06D0;
    func_15143794(((s16 *)&arg8)[1], (s16) ((sp24 % 21U) - 0x19), magnitude, &packet.direction);
    packet.flags58 = 0xE05;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field62 = 8;
    packet.field63 = -1;
    packet.field1E = 0xA;
    packet.field20 = 0x19;
    packet.field22 = 0x1B;
    packet.field24 = D_800A06D4;
    sp2C = D_800A06D8;
    temp_v0 = func_15130374((s32) &packet, 1U, 4, ((u8 *)&arg14)[3], 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0xA8, &sp2C, 4U);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CC6B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CC6B8.s")
extern s32 D_800BE9E4;

s32 func_150CC8D4(void *arg0, s32 arg1) {
    f32 *factor;
    s32 remaining;

    factor = (f32 *)((u8 *)arg0 + 0xA8);
    remaining = D_800BE9E4;
    while (remaining != 0) {
        *(f32 *)((u8 *)arg0 + 0x58) *= *factor;
        *(f32 *)((u8 *)arg0 + 0x60) *= *factor;
        remaining--;
    }
    return 1;
}
typedef struct GameF9430TransformParticle {
    f32 field0, field4, size0, size1;
    f32 rotation[3], scale[3], position[3], velocity[3];
    f32 rotationRate[3], field4C;
    s32 flags;
    s16 lifetime;
    u16 resource;
    u8 field58, pad59[3];
    s32 field5C;
    u8 alpha, update, secondary, field63, field64, field65;
    u8 cleanup, special, field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 threshold, rate;
    u8 pad76[6];
} GameF9430TransformParticle;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A06DC, D_800A06E0, D_800A06E4, D_800A06E8;
extern f32 D_800A06EC, D_800A06F0, D_800A06F4, D_800A06F8;

s32 func_150CCA7C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    f32 size;
    GameF9430TransformParticle packet;
    f32 magnitude;
    u32 random;

    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.flags = 0x29E8;
    packet.rotation[0] = 0.0f;
    packet.rotation[1] = 0.0f;
    packet.rotation[2] = 0.0f;
    packet.rotationRate[1] = 0.0f;
    packet.field0 = 1.0f;
    packet.resource = 0x20;
    packet.position[2] = arg4;
    packet.field4 = D_800A06DC;
    random = func_150ADA20();
    magnitude = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16)((random % 44U) - 0x3F),
                 ((magnitude * 200.0f) + 300.0f) * D_800A06E0,
                 packet.velocity);
    packet.rotationRate[0] = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A06E4;
    packet.rotationRate[2] = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A06E8;
    packet.lifetime = (func_150ADA20() % 51U) + 0x32;
    packet.field4C = ((func_150ADA68() * D_800A06EC) + D_800A06F0) * D_800A06F4;
    size = ((func_150ADA68() * 500.0f) + 100.0f) * D_800A06F8;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.size0 = size;
    packet.size1 = size;
    packet.alpha = (func_150ADA20() % 101U) + 0x9B;
    packet.update = 3;
    packet.secondary = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.cleanup = 0;
    packet.special = 0;
    packet.field68 = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.threshold = 0x20;
    packet.rate = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, ((u8 *)&arg14)[3], 0);
    return 1;
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CCCB4 CURRENT (120) */
s32 func_150CCCB4(void *arg0) {
    f32 rate;
    f32 temp_fa0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    rate = D_800BE9A4;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * rate) + (temp_fa0 * rate * rate * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CCCB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CCCB4.s")
