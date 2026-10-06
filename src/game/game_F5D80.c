#include "types.h"

/*
 * Reviewed source unit: src/game/game_F5D80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_composite_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C88D0
 * - func_150C8A68
 * - func_150C8DB8
 * - func_150C99B4
 * - func_150C9BDC
 * - func_150C9DC4
 * - func_150CA07C
 * - func_150CA150
 * - func_150CB008
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
f32 func_15047D60(f32);
f32 func_15047C00(f32);
void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern f32 D_800A0528;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C88D0 CURRENT (2675) */
void *func_150C88D0(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 angle;
    f32 zero;
    u8 *effect;
    s32 count;
    s32 index;
    s32 offset;
    s32 five;

    count = *(s32 *)(arg0 + 0x14);
    effect = func_15167A68(0x31, arg3, arg1 + (count * 8) + (count * 0xA0) + 0x408,
                           1, arg2, 1);
    five = 5;
    if (effect == 0) {
        return 0;
    }
    func_10022EC0(effect + 0x10, arg0, 0x30);
    *(u8 **)(effect + 0x360) = effect + 0x368;
    *(u8 **)(effect + 0x54) = effect + (*(s32 *)(arg0 + 0x14) * 8) + 0x368;
    zero = 0.0f;
    *(u8 **)(effect + 0x58) = effect + (*(s32 *)(arg0 + 0x14) * 8) + ((*(s32 *)(arg0 + 0x14) * five) * 0x10) + 0x3B8;
    *(f32 *)(effect + 0x40) = zero;
    *(f32 *)(effect + 0x44) = zero;
    *(u8 **)(effect + 0x364) = effect + (*(s32 *)(arg0 + 0x14) * 8) + ((*(s32 *)(arg0 + 0x14) * five) * 0x20) + 0x408;
    *(f32 *)(effect + 0x50) = zero;
    *(s16 *)(effect + 0x4C) = *(s16 *)(effect + 0x28);
    *(f32 *)(effect + 0x48) = D_800A0528 / (f32)*(s32 *)(effect + 0x24);
    angle = zero;
    index = 0;
    offset = 0;
    if (*(s32 *)(effect + 0x24) > 0) {
        do {
            *(f32 *)(*(u8 **)(effect + 0x360) + offset) = func_15047D60(angle);
            index++;
            *(f32 *)(*(u8 **)(effect + 0x360) + offset + 4) = func_15047C00(angle);
            offset += 8;
            angle += *(f32 *)(effect + 0x48);
        } while (index < *(s32 *)(effect + 0x24));
    }
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C88D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C88D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8A68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C8DB8.s")
typedef struct GameF5D80Vector {
    f32 values[3];
} GameF5D80Vector;

typedef struct GameF5D80Particle {
    s32 flags, field4;
    s16 kind, duration;
    s32 fieldC, field10;
    u8 color0[4], color1[4];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, size0, size1;
    GameF5D80Vector position;
    f32 velocity[3];
    f32 direction[3];
    f32 field54;
    s32 flags58;
    u8 pad5C[4];
    u8 field60, field61;
    s8 field62, field63;
    u8 pad64[0xC];
} GameF5D80Particle;

typedef struct GameF5D80Emitter {
    u8 pad0;
    u8 group;
    u8 pad2[0xA];
    u8 mode;
    u8 padD[0x13];
    f32 scale;
} GameF5D80Emitter;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15130374(s32, u8, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800A0570, D_800A0574, D_800A0578, D_800A057C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C99B4 CURRENT (10) */
void func_150C99B4(GameF5D80Emitter *arg0, GameF5D80Vector *arg1, u8 arg2, s32 arg3) {
    GameF5D80Particle packet;
    f32 fraction;
    s16 angle;
    f32 magnitude;
    s32 flip0;
    s32 flip1;

    packet.field1D = 0x26;
    packet.kind = 0xC01;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = func_150ADA20() % 81U + 25;
    packet.fieldC = 0;
    packet.field10 = 0;
    packet.field60 = 5;
    packet.field61 = 5;
    packet.color0[0] = 0;
    packet.color0[1] = 0;
    packet.color0[2] = 0;
    packet.color0[3] = 0xFF;
    packet.color1[0] = 0;
    packet.color1[1] = 0;
    packet.color1[2] = 0;
    packet.color1[3] = func_150ADA20() % 156U + 100;
    packet.field1C = 0xFF;
    packet.size0 = packet.size1 = func_150ADA68() * 500.0f + 500.0f;
    packet.position = *arg1;
    packet.velocity[0] = 0.0f;
    packet.velocity[1] = 0.0f;
    packet.velocity[2] = 0.0f;
    packet.field54 = (func_150ADA68() * D_800A0570 + -1416.0f) * D_800A0574;
    packet.field1E = 20;
    packet.field20 = 12;
    packet.field22 = 0;
    packet.field24 = 1.0f;
    flip0 = (func_150ADA20() & 1) ? 0x40 : 0;
    flip1 = (func_150ADA20() & 1) ? 0x80 : 0;
    packet.flags58 = 7 | flip1 | flip0 | 0x200;
    packet.field62 = -1;
    packet.field63 = -1;
    angle = func_150ADA20() % 11U - 18;
    fraction = func_150ADA68();
    magnitude = (arg0->scale * D_800A0578) * fraction + arg0->scale * D_800A057C;
    func_15143794(arg2, angle, magnitude, &packet.direction);
    func_15130374((s32)&packet, 1, 0, arg0->mode, arg0->group);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C99B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C99B4.s")
typedef struct GameF5D80Actor {
    s32 active;
    u8 kind;
    u8 pad05[0xF];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[8];
    f32 radius;
    u8 pad2C[0x39];
    u8 enabled65;
    u8 pad66[0x14];
    u16 sound;
    u8 pad7C[0xD];
    u8 state89;
    u8 pad8A[0x9A];
    u8 owner, disabled;
    u8 pad126[0x16];
    u8 mode13C;
    u8 pad13D[0xDB];
    s32 counter218;
    u8 pad21C[0x16];
    u8 state232;
    u8 pad233[0xF9];
} GameF5D80Actor;
typedef struct GameF5D80Wave {
    u8 pad00[0x10];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[0x28];
    f32 radius;
} GameF5D80Wave;
extern u8 D_800CC2D0[];
extern u8 D_800D121C[];
void func_1505D024(void *, s32, s32, s32);
f32 sqrtf(f32);
__pragma(1, sqrtf);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C9BDC CURRENT (1177) */
void func_150C9BDC(GameF5D80Wave *arg0, s32 arg1) {
    GameF5D80Actor *actor;
    f32 dx, dz, adjusted, distance, delta;
    s32 active;
    s32 kind;

    actor = (GameF5D80Actor *)D_800CC2D0;
    do {
        active = actor->active;
        if ((active != 0) && (actor->radius < 20.0f) &&
            (actor->disabled == 0) &&
            (((kind = actor->kind) == 0x53) || (active == 1))) {
            dx = actor->x - arg0->x;
            dz = actor->z - arg0->z;
            distance = sqrtf(dx * dx + dz * dz) - 100.0f;
            adjusted = distance;
            if ((kind == 0x53) && (actor->mode13C == 0)) {
                adjusted = distance - 150.0f;
            }
            delta = arg0->radius - adjusted;
            if ((delta >= 0.0f) && (delta < 250.0f)) {
                if (kind == 0x53) {
                    actor->state89 = 0xA;
                    actor->counter218 = 0;
                    actor->state232 = 0x13;
                    if (D_800CC2D0[actor->owner * 0x32C + 0x65] != 0) {
                        actor->state232 = 0x14;
                    }
                } else {
                    func_1505D024(actor, 0x6000E, actor->sound, -1);
                }
            }
        }
        actor++;
    } while (actor != (GameF5D80Actor *)D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C9BDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9BDC.s")
typedef struct GameF5D80Burst {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    s8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    s8 field66;
    s8 field67;
    s8 field68;
    u8 pad69[0x1];
    s8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    s8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 unknown76[6];
} GameF5D80Burst;

void func_150CCD90(f32, f32 *, f32 *, f32 *);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A0580, D_800A0584, D_800A0588, D_800A058C;
extern f32 D_800A0590, D_800A0594, D_800A0598, D_800A059C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C9DC4 CURRENT (991) */
void func_150C9DC4(GameF5D80Emitter *arg0, GameF5D80Vector *arg1,
                   s32 arg2, s32 arg3) {
    struct {
        f32 third, second, first;
        GameF5D80Burst packet;
    } work;
    u32 random;
    register f32 fraction;

    func_150CCD90(arg1->values[2], &work.first, &work.second, &work.third);
    *(GameF5D80Vector *)&work.packet.field28 = *arg1;
    work.packet.field1C = 1.0f;
    work.packet.field20 = 1.0f;
    work.packet.field24 = 1.0f;
    work.packet.field50 = 0x29E8;
    work.packet.field10 = func_150ADA68() * 360.0f;
    work.packet.field14 = func_150ADA68() * 360.0f;
    work.packet.field18 = func_150ADA68() * 360.0f;
    work.packet.field56 = 0x20;
    work.packet.field4 = D_800A0580;
    work.packet.field44 = 0.0f;
    work.packet.field0 = 1.0f;
    random = func_150ADA20();
    func_15143794(((u8 *)&arg2)[3], (s16)((random % 26U) - 0x2D),
                 ((func_150ADA68() * 81.0f) + 60.0f) * arg0->scale * D_800A0584,
                 &work.packet.field34);
    work.packet.field40 = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A0588;
    work.packet.field48 = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A058C;
    work.packet.field54 = (func_150ADA20() % 41U) + 0x28;
    work.packet.field4C = ((func_150ADA68() * D_800A0590) + D_800A0594) * D_800A0598;
    fraction = func_150ADA68() * 400.0f;
    work.packet.field58 = 0;
    work.packet.field5C = 0;
    work.packet.field8 = work.packet.fieldC = (fraction + 199.0f) * D_800A059C;
    work.packet.field60 = (func_150ADA20() % 101U) + 0x9B;
    work.packet.field61 = 7;
    work.packet.field62 = 0;
    work.packet.field63 = 0;
    work.packet.field64 = 0;
    work.packet.field65 = 0;
    work.packet.field66 = 0;
    work.packet.field67 = 0;
    work.packet.field68 = 0;
    work.packet.field6A = 2;
    work.packet.field6C = 0;
    work.packet.field70 = 0;
    work.packet.field72 = 0x20;
    work.packet.field74 = 7;
    func_15132A4C(&work.packet, 3, 0xFF, 0, arg0->mode, arg0->group);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C9DC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150C9DC4.s")

extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CA07C CURRENT (120) */
s32 func_150CA07C(void *arg0) {
    f32 rate;
    f32 temp_fa0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    rate = D_800BE9A4;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * rate) + (temp_fa0 * rate * rate * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x48) = temp_fa0 * D_800BE9A4 + temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CA07C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA07C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CA150.s")
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

void func_150CA930(void *arg0) {
    s16 sp3E;

    sp3E = (s16)((func_150ADA20() % 21U) + 0xA);
    func_1514C678(*(f32 *)((u8 *)arg0 + 0),
                  *(f32 *)((u8 *)arg0 + 4),
                  *(s32 *)((u8 *)arg0 + 8),
                  (func_150ADA68() * 59.0f) + 170.0f,
                  0, 0xFF, (s32)sp3E, 0x13, 0, 0.0f, 0, 0xFF);
}
s32 func_150CA9D0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}


void *func_15130374(s32, u8, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800A05AC, D_800A05B0, D_800A05B4, D_800A05B8;

s32 func_150CAA04(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    void *temp_v0;
    GameF5D80Particle packet;
    f32 size;
    f32 sp2C;
    f32 fraction;
    u32 sp24;

    packet.field1D = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = (func_150ADA20() % 26U) + 0x19;
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
    size = (func_150ADA68() * D_800A05AC) + 800.0f;
    packet.position.values[0] = arg2;
    packet.position.values[1] = arg3;
    packet.position.values[2] = arg4;
    packet.size0 = size;
    packet.size1 = size;
    sp24 = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16) ((sp24 % 12U) - 0x15), ((fraction * 300.0f) + 498.0f) * D_800A05B0, &packet.direction);
    packet.flags58 = 0xE05;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field62 = 9;
    packet.field63 = -1;
    packet.field1E = 0x19;
    packet.field20 = 0xA;
    packet.field22 = 0x20;
    packet.field24 = D_800A05B4;
    sp2C = D_800A05B8;
    temp_v0 = func_15130374((s32) &packet, 1U, 4, ((u8 *)&arg14)[3], 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0xA8, &sp2C, 4U);
    }
    return 1;
}

extern s32 D_800BE9E4;

s32 func_150CAC28(void *arg0, s32 arg1) {
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
typedef struct GameF5D80EffectPacket {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    s8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    s8 field66;
    s8 field67;
    s8 field68;
    u8 pad69[0x1];
    s8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    s8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 unknown76[0xA];
} GameF5D80EffectPacket;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A05BC, D_800A05C0, D_800A05C4, D_800A05C8;
extern f32 D_800A05CC, D_800A05D0, D_800A05D4, D_800A05D8;

s32 func_150CADD0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    GameF5D80EffectPacket packet;
    f32 fraction;
    u32 random;

    packet.field28 = arg2;
    packet.field2C = arg3;
    packet.field30 = arg4;
    packet.field24 = packet.field20 = packet.field1C = 1.0f;
    packet.field50 = 0x29E8;
    packet.field18 = packet.field14 = packet.field10 = 0.0f;
    packet.field44 = 0.0f;
    packet.field0 = 1.0f;
    packet.field56 = 0x20;
    packet.field4 = D_800A05BC;
    random = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16)((random % 21U) - 0x28),
                 ((fraction * 204.0f) + 500.0f) * D_800A05C0, &packet.field34);
    packet.field40 = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A05C4;
    packet.field48 = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A05C8;
    packet.field54 = (func_150ADA20() % 51U) + 0x32;
    packet.field4C = ((func_150ADA68() * 1008.0f) + D_800A05CC) * D_800A05D0;
    fraction = ((func_150ADA68() * D_800A05D4) + 200.0f) * D_800A05D8;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.field8 = fraction;
    packet.fieldC = fraction;
    packet.field60 = (func_150ADA20() % 76U) + 0xB4;
    packet.field61 = 4;
    packet.field62 = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 0x20;
    packet.field74 = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, ((u8 *)&arg14)[3], 0);
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CB008 CURRENT (120) */
s32 func_150CB008(void *arg0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150CB008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5D80/func_150CB008.s")
