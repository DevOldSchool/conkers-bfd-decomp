#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_177B50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514A6A0
 * - func_1514AB5C
 * - func_1514AD9C
 * - func_1514AF74
 * - func_1514B034
 * - func_1514B364
 * - func_1514B8E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514A6A0.s")
typedef struct { f32 x, y, z; } Game177B50Vector;
typedef struct {
    Game177B50Vector position;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 color26[4];
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 field2F;
    s32 field30;
    u8 field34;
    u8 pad35[3];
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
} Game177B50Particle;

void *func_15149550(f32 *, u8, u8, u8, u8, s32);
f32 func_150ADA68(void);
u32 func_150ADA20(void);
extern f32 D_800A57B0, D_800A57B4, D_800A57B8, D_800A57BC;
extern f32 D_800A57C0, D_800A57C4, D_800A57C8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514AB5C CURRENT (14) */
void func_1514AB5C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4,
                   f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   s16 arg9, s16 arg10, u8 arg11) {
    Game177B50Particle particle;
    f32 radius;
    f32 xScale;
    f32 sine;
    f32 cosine;
    f32 yScale;
    u8 angle;

    if (arg4 > 0) {
        particle.field20 = 0x6231;
        particle.field22 = 0x1A4D;
        particle.color26[0] = 0;
        particle.color26[1] = 0;
        particle.color26[2] = 0;
        particle.color26[3] = 0xFF;
        particle.field2A = 1;
        particle.field2C = 0xFF;
        particle.field2D = 0xFF;
        particle.field30 = 0;
        particle.field2E = 0;
        particle.field2F = arg11;
        particle.field34 = 0xF;
        particle.position.y = arg1;
        particle.field38 = 0.0f;
        particle.field40 = 0.045f;
        particle.field44 = 0.7f;
        do {
            angle = func_150ADA20() & 0xFF;
            sine = func_151423D8(angle - 0x40);
            cosine = func_151423D8(angle);
            radius = func_150ADA68() * arg3;
            xScale = func_150ADA68() * arg6 + arg5;
            yScale = func_150ADA68();
            particle.position.x = radius * sine + arg0;
            particle.position.z = radius * cosine + arg2;
            particle.field0C = 22.6f * xScale;
            particle.field14 = 13.786f * xScale;
            yScale = yScale * arg8 + arg7;
            particle.field10 = 57.969f * yScale;
            particle.field18 = 42.714f * yScale;
            particle.field1C = 118.763f * yScale;
            particle.field24 = func_150ADA20() % (u32)(arg10 + 1) + arg9;
            func_15149550(&particle.position.x, 0xA, 0, 0, 0xFF, 1);
            arg4 -= 1;
        } while (arg4 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514AB5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AB5C.s")

extern f32 D_800A57CC, D_800A57D0, D_800A57D4, D_800A57D8;
extern f32 D_800A57DC, D_800A57E0, D_800A57E4, D_800A57E8;
extern f32 D_800A57EC, D_800A57F0, D_800A57F4, D_800A57F8;
extern f32 D_800A57FC, D_800A5800, D_800A5804;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514AD9C CURRENT (14) */
void func_1514AD9C(Game177B50Vector *arg0, s32 arg1, s32 arg2) {
    Game177B50Particle particle;
    f32 x_scale;
    f32 y_scale;
    f32 random_y;

    particle.field20 = 0x6231;
    particle.field22 = 0x1A4D;
    particle.position = *arg0;
    particle.color26[0] = 0;
    particle.color26[1] = 0;
    particle.color26[2] = 0;
    particle.color26[3] = 0xFF;
    particle.field2D = 0xFF;
    particle.field2E = 0;
    particle.field2F = 1;
    particle.field30 = 0;
    particle.field2A = 1;
    particle.field34 = 0x1C;
    particle.field3C = 0.0f;
    particle.field40 = D_800A57CC;
    particle.field44 = D_800A57D0;
    x_scale = (func_150ADA68() * D_800A57D4 + D_800A57D8) * D_800A57DC;
    random_y = func_150ADA68();
    particle.field0C = D_800A57E0 * x_scale;
    particle.field14 = D_800A57E4 * x_scale;
    y_scale = (random_y * D_800A57E8 + D_800A57EC) * D_800A57F0;
    particle.field10 = D_800A57F4 * y_scale;
    particle.field18 = D_800A57F8 * y_scale;
    particle.field1C = D_800A57FC * y_scale;
    particle.field24 = func_150ADA20() % 17U + 0x10;
    particle.field38 = (func_150ADA68() * D_800A5800 + 50.0f) * D_800A5804;
    particle.field2C = func_150ADA20() % 156U + 0x64;
    func_15149550(&particle.position.x, 10, 0, 0, (u8)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514AD9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AD9C.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514AF74 CURRENT (630) */
s32 func_1514AF74(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 rate;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x50);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    rate = D_800BE9A4;
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x4C);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + ((temp_fa1 * rate) + (0.5f * temp_ft5 * rate * rate)));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (temp_fa1 + (temp_ft5 * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 10.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 10.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514AF74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AF74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B364.s")
s32 func_1514B844(void *arg0) {
    s16 temp_v1;
    s32 temp_a0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v1 < 0x10) {
        temp_a0 = temp_v1 * 0x10;
        if (temp_a0 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
            *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_a0;
        }
    }
    return 1;
}
extern f32 D_800BE9A4;

s32 func_1514B87C(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    return 1;
}
s32 func_1514B8B0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x10) {
        temp_v1 = temp_v0 * 0x10;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800A4AA0[];
extern f32 D_800A5860, D_800A5864, D_800A5868, D_800A586C;
extern f32 D_800A5870, D_800A5874, D_800A5878, D_800A587C, D_800A5880, D_800A5884;

typedef struct {
    s8 kind, mode;
    u16 texture;
    s16 lifetime;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 color[4];
    f32 field14, field18;
    Game177B50Vector position, origin, scale;
    s32 flags;
    u8 field44, field45, field46, field47;
    s32 field48;
    u8 pad4C[8];
    s16 field54, field56;
} Game177B50Descriptor;

typedef struct {
    f32 values[14];
    Game177B50Vector direction;
    Game177B50Vector velocity;
} Game177B50Motion;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514B8E4 CURRENT (460) */
void *func_1514B8E4(Game177B50Vector *arg0, f32 *arg1, s16 arg2, u8 arg3,
                     Game177B50Vector *arg4, f32 arg5, f32 arg6, f32 arg7,
                     u8 arg8, u8 arg9, u8 arg10, s32 arg11, u8 arg12,
                     s16 arg13, s16 arg14, s32 arg15, u8 arg16, s32 arg17) {
    void *result;
    Game177B50Descriptor particle;
    Game177B50Motion motion;
    s32 flag1;
    s32 timed;
    s32 flag2;

    if (arg4 != NULL) {
        motion.direction = *arg4;
    } else {
        motion.direction.x = 0.0f;
        motion.direction.y = 0.0f;
        motion.direction.z = 0.0f;
    }
    motion.velocity.x = arg5;
    motion.values[7] = 0.0f;
    motion.values[8] = 0.0f;
    motion.values[12] = 0.0f;
    particle.fieldC = 0x3E3F;
    motion.values[13] = D_800A5860;
    motion.values[11] = D_800A5860;
    motion.values[9] = D_800A5864;
    motion.velocity.y = arg6;
    motion.velocity.z = arg7;
    motion.values[10] = D_800A5868;
    motion.values[0] = arg1[0] * D_800A586C;
    motion.values[2] = arg1[0] * D_800A5870;
    motion.values[4] = arg1[0] * D_800A5874;
    particle.field14 = 0.0f;
    motion.values[1] = arg1[1] * D_800A5878;
    motion.values[3] = arg1[1] * D_800A587C;
    motion.values[6] = arg1[1] * D_800A5880;
    motion.values[5] = arg1[1] * D_800A5884;
    particle.field18 = 0.0f;
    particle.mode = 0;
    particle.texture = 0x2203;
    particle.kind = arg11;
    if (arg2 == -1) particle.lifetime = 300;
    else particle.lifetime = arg2;
    particle.field8 = 0;
    particle.color[0] = 255;
    particle.color[1] = 255;
    particle.color[2] = 255;
    particle.color[3] = 255;
    particle.position = *arg0;
    particle.origin.x = arg0->x;
    particle.origin.y = arg0->y + 100.0f;
    particle.origin.z = arg0->z;
    particle.scale.x = 1.0f;
    particle.scale.y = 1.0f;
    particle.scale.z = 1.0f;
    flag1 = (arg12 & 1) ? 0x800000 : 0;
    timed = (arg2 == -1) ? 0 : 1;
    flag2 = (arg12 & 2) ? 0x2000000 : 0;
    particle.flags = flag2 | timed | 0x40000 | 0x80000 | 0x200000 | 0x400000 | flag1 | 0x40000000;
    particle.field45 = 255;
    particle.field46 = 0;
    particle.field47 = 7;
    particle.field48 = 0;
    particle.field44 = arg3;
    particle.field54 = arg13;
    particle.field56 = arg14;
    if (func_150ADA20() & 1) flag2 = 1;
    else flag2 = 0;
    result = func_1513D2F0((s32)&particle, (s32)D_800A4AA0, arg8, arg9, arg10,
                           0x1C, flag2 | 2, 0, 0, arg15 + 0x50, arg16, arg17);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x110, &motion, 0x50);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514B8E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B8E4.s")
extern f32 D_800A5888;
extern f32 D_800A588C;
extern f32 D_800A5890;

s32 func_1514BC08(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (*(f32 *)((u8 *)arg1 + 0x1C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x1C) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)arg1 + 0x10) = (f32) (*(f32 *)((u8 *)arg1 + 0) + *(f32 *)((u8 *)arg1 + 8) * func_150ADA68());
    }
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) += (*(f32 *)((u8 *)arg1 + 0x10) - temp_fv0) * D_800A5888;
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (*(f32 *)((u8 *)arg1 + 0x20) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x20) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x20) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg1 + 0xC) * func_150ADA68());
        } else {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68());
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) += (*(f32 *)((u8 *)arg1 + 0x14) - temp_fv0_2) * D_800A588C;
    *(f32 *)((u8 *)arg1 + 0x30) = (f32) (*(f32 *)((u8 *)arg1 + 0x30) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x30) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x30) = (f32) (func_150ADA68() * 7.0f);
        *(f32 *)((u8 *)arg1 + 0x2C) = (f32) (*(f32 *)((u8 *)arg1 + 0x24) + *(f32 *)((u8 *)arg1 + 0x28) * func_150ADA68());
    }
    temp_fv0_3 = *(f32 *)((u8 *)arg1 + 0x34);
    *(f32 *)((u8 *)arg1 + 0x34) += (*(f32 *)((u8 *)arg1 + 0x2C) - temp_fv0_3) * D_800A5890;
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) *(f32 *)((u8 *)arg1 + 0x34);
    return 1;
}
