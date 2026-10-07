#include "types.h"

/*
 * Reviewed source unit: src/game/game_111670.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E41C0
 * - func_150E42F8
 * - func_150E4550
 * - func_150E4928
 * - func_150E4CBC
 * - func_150E4E04
 * - func_150E5558
 * - func_150E5810
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern s16 D_800D99F0[];
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E41C0 CURRENT (2357) */
void func_150E41C0(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 zero;
    f32 horizontal;
    f32 depth;
    f32 trig;
    f32 cosine;
    f32 angle;

    x = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    y = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
    z = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x300);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x398);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    horizontal = 500.0f * trig;
    depth = -500.0f * cosine;
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    zero = 0.0f;
    x = (s32)((f32)x + (zero + (depth * trig)));
    z = (s32)((f32)z + ((depth * cosine) - zero));
    y = (s32)((f32)y + horizontal);
    D_800D99F0[0] = x;
    D_800D99F0[2] = z;
    D_800D99F0[1] = y;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E41C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E41C0.s")
/* Call context: func_1510F8CC: matched US definition in src/game/game_13BB20.c */
s32 func_1510F8CC(s32);

s32 func_150ADA20(void);                                /* extern */
void func_150E4550(f32, f32, f32, s32, s32, s32, s32); /* extern */
s32 func_1510F8D8(s32, s32, s32, s32 *);        /* extern */
extern f32 D_800A1060;
extern s32 D_800DBE3C;
extern s32 D_800DBE4C;
extern s32 *D_800DBE5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E42F8 CURRENT (80) */
void func_150E42F8(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_a2;
    s32 sp70;
    s32 temp_v0_2;
    s32 sp68;
    s32 temp_lo;
    s32 var_s3;
    f32 temp_fs0;
    s32 sp58;

    sp58 = 0;
    var_s3 = 0;
    sp70 = (s32) D_800D99F0[0];
    sp68 = (s32) D_800D99F0[2];
    if (arg0 > 0) {
        temp_fs0 = D_800A1060;
        do {
            temp_s0 = (func_150ADA20() % 500) + sp70;
            temp_a2 = (func_150ADA20() % 500) + sp68;
            temp_v0 = func_1510F8D8(temp_s0, 0x2710, temp_a2, &sp58);
            if ((temp_fs0 != (f32) temp_v0) && (sp58 != 0)) {
                temp_lo = (s32) (sp58 - D_800DBE3C) / 12;
                if ((temp_lo >= 0) && (temp_lo < D_800DBE4C)) {
                    temp_v0_2 = func_1510F8CC(D_800DBE5C[temp_lo]);
                    if (temp_v0_2 != 0) {
                        func_150E4550((f32) temp_s0, (f32) temp_v0, (f32) temp_a2, 0, temp_v0_2, sp58, 0xFF);
                    }
                }
            }
            var_s3 += 1;
        } while (var_s3 != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E42F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E42F8.s")
void func_150E4514(s32 arg0) {
    func_150E41C0();
    func_150E42F8(arg0 / 30);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4928.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4CBC CURRENT (175) */
void func_150E4CBC(void *arg0) {
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_a1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
    if (temp_v0 < 9) {
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x96) * ((s32) (temp_v0 * 0x5A) / 9)) * 0.00390625f);
    } else {
        temp_a1 = *(u8 *)((u8 *)arg0 + 0xB4);
        *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x96) * (0x5A - ((s32) ((temp_v0 * 0x5A) - 0x32A) / 600))) * 0.00390625f);
        temp_t0 = D_800BE9E4 * 0x11;
        if (temp_t0 < (s32) temp_a1) {
            *(u8 *)((u8 *)arg0 + 0xB4) = (u8) (temp_a1 - temp_t0);
            temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
        } else {
            *(s16 *)((u8 *)arg0 + 0x98) = -1;
            temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
        }
    }
    *(s16 *)((u8 *)arg0 + 0xA2) = (s16) ((s32) ((f32) *(s16 *)((u8 *)arg0 + 0x94) * 14.0f) >> 8);
    if (temp_v0 >= 0x261) {
        *(s16 *)((u8 *)arg0 + 0x98) = -1;
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x90);
    }
    *(s32 *)((u8 *)arg0 + 0x90) = (s32) (temp_v0 + D_800BE9E4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4CBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4CBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4E04.s")
typedef struct Game111670Effect {
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
} Game111670Effect;

void func_100226F0(void *, s32);
f32 func_150484A0(f32, f32);
f32 func_150ADA68(void);
s32 func_151EF610(void);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A1140, D_800A1144, D_800A1148, D_800A114C;
extern f32 D_800A1150, D_800A1154, D_800A1158, D_800A115C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E5558 CURRENT (40) */
void func_150E5558(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    Game111670Effect packet;
    f32 pitch;
    register f32 yaw;
    f32 fraction, one;

    func_100226F0(&packet, 0x7C);
    if (arg4 != 0.0f) {
        pitch = func_150484A0(arg3, arg4) * D_800A1140;
    } else {
        pitch = 90.0f;
    }
    if (arg5 != 0.0f) {
        yaw = func_150484A0(arg3, arg5) * D_800A1144;
    } else {
        yaw = 90.0f;
    }
    one = 1.0f;
    packet.angle[1] = yaw;
    packet.angle[2] = pitch;
    packet.scale[0] = one;
    packet.scale[1] = one;
    packet.scale[2] = one;
    packet.field0 = one;
    packet.field8 = D_800A1148;
    packet.fieldC = D_800A1148;
    packet.position[0] = arg0;
    packet.position[1] = arg1;
    packet.position[2] = arg2;
    packet.angle[0] = 0.0f;
    if (arg6 == 4) {
        packet.kind = 6;
        packet.field4 = D_800A114C;
    } else if (arg6 == 9) {
        packet.kind = 8;
        packet.field4 = D_800A1150;
    } else {
        packet.kind = 7;
        packet.field4 = D_800A1154;
    }
    packet.duration = func_151EF610() % 60 + 60;
    packet.flags = 0x29E9;
    fraction = func_150ADA68();
    packet.field4C = D_800A1158;
    yaw = fraction * D_800A115C + 1.5f;
    packet.velocity[0] = yaw * arg3;
    packet.velocity[1] = -yaw * arg4;
    packet.velocity[2] = yaw * arg5;
    packet.acceleration[0] = func_150ADA68() * 6.0f + -3.0f;
    packet.acceleration[2] = func_150ADA68() * 6.0f + -3.0f;
    fraction = func_150ADA68() * 6.0f + -3.0f;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.acceleration[1] = fraction;
    packet.color[0] = 0xFF;
    packet.color[1] = 1;
    packet.color[2] = 0;
    packet.color[3] = 3;
    packet.color[4] = 0;
    packet.color[5] = 0;
    packet.color[6] = 0;
    packet.color[7] = 0;
    packet.color[8] = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 0x20;
    packet.field74 = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E5558 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5558.s")

typedef struct Game111670Point {
    f32 values[3];
} Game111670Point;

typedef struct Game111670Triangle {
    Game111670Point vertices[3];
} Game111670Triangle;

typedef struct Game111670PackedPoint {
    s16 values[3];
} Game111670PackedPoint;

typedef struct Game111670Motion {
    u8 pad0[0x10];
    f32 heightFactor, bounce;
    u8 pad18[0x24];
    f32 height;
    u8 pad40[4];
    f32 velocity[3], acceleration[3];
    u8 pad5C[4];
    u32 flags;
} Game111670Motion;

void func_15048F58(void *, void *, void *);
void func_15049148(void *, f32, void *);
f32 func_150AD900(f32 *, f32 *);
f32 func_150AD930(void *);
void func_15049350(Game111670Triangle);
extern f32 D_800A1160, D_800A1164, D_800A1168;
extern f32 D_800CC210, D_800CC214, D_800CC218;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E5810 CURRENT (942) */
s32 func_150E5810(Game111670Motion *motion, s32 unused1, s32 unused2, s32 unused3,
                  f32 height, Game111670PackedPoint *vertices) {
    Game111670Triangle triangle;
    f32 value;
    f32 vertical;
    f32 factor;
    register s32 i;
    f32 velocity[3];
    f32 normal[3];
    f32 unit[3];

    motion->height = motion->heightFactor * D_800A1160 + height;
    vertical = motion->velocity[1];
    if (vertical > -2.0f) {
        motion->velocity[0] = 0.0f;
        motion->flags &= ~0x6FU;
        motion->velocity[1] = 0.0f;
        motion->velocity[2] = 0.0f;
    } else {
        if (vertices != 0) {
            for (i = 0; i != 3; i++) {
                triangle.vertices[i].values[0] = vertices[i].values[0];
                triangle.vertices[i].values[1] = vertices[i].values[1];
                triangle.vertices[i].values[2] = vertices[i].values[2];
            }
            func_15049350(triangle);
            normal[0] = -D_800CC210;
            normal[1] = -D_800CC214;
            normal[2] = -D_800CC218;
            value = func_150AD930(normal);
            if (D_800A1164 < value) {
                func_15049148(normal, 1.0f / value, unit);
                velocity[0] = motion->velocity[0];
                velocity[1] = motion->velocity[1];
                velocity[2] = motion->velocity[2];
                func_15049148(unit,
                              2.0f * func_150AD900(unit, velocity),
                              normal);
                func_15048F58(velocity, normal, normal);
                value = motion->bounce;
                factor = D_800A1168;
                motion->velocity[0] = value * normal[0] * factor;
                motion->velocity[1] = value * normal[1];
                motion->velocity[2] = value * normal[2] * factor;
            }
        } else {
            value = motion->bounce;
            motion->velocity[0] *= value;
            motion->velocity[1] = -vertical * value;
            motion->velocity[2] *= value;
        }
        value = motion->bounce;
        motion->acceleration[0] *= value;
        motion->acceleration[1] *= value;
        motion->acceleration[2] *= value;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E5810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5810.s")
