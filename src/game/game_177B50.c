#include "types.h"

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
 * - func_1514BC08
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
f32 func_151423D8(u8);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B8E4.s")
extern f32 D_800A5888;
extern f32 D_800A588C;
extern f32 D_800A5890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BC08 CURRENT (40) */
s32 func_1514BC08(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (*(f32 *)((u8 *)arg1 + 0x1C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x1C) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)arg1 + 0x10) = (f32) (*(f32 *)((u8 *)arg1 + 0) + (func_150ADA68() * *(f32 *)((u8 *)arg1 + 8)));
    }
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) += (*(f32 *)((u8 *)arg1 + 0x10) - temp_fv0) * D_800A5888;
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (*(f32 *)((u8 *)arg1 + 0x20) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x20) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x20) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + (func_150ADA68() * *(f32 *)((u8 *)arg1 + 0xC)));
        } else {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (*(f32 *)((u8 *)arg1 + 4) + (func_150ADA68() * *(f32 *)((u8 *)arg1 + 0x18)));
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) += (*(f32 *)((u8 *)arg1 + 0x14) - temp_fv0_2) * D_800A588C;
    *(f32 *)((u8 *)arg1 + 0x30) = (f32) (*(f32 *)((u8 *)arg1 + 0x30) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x30) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x30) = (f32) (func_150ADA68() * 7.0f);
        *(f32 *)((u8 *)arg1 + 0x2C) = (f32) (*(f32 *)((u8 *)arg1 + 0x24) + (func_150ADA68() * *(f32 *)((u8 *)arg1 + 0x28)));
    }
    temp_fv0_3 = *(f32 *)((u8 *)arg1 + 0x34);
    *(f32 *)((u8 *)arg1 + 0x34) += (*(f32 *)((u8 *)arg1 + 0x2C) - temp_fv0_3) * D_800A5890;
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) *(f32 *)((u8 *)arg1 + 0x34);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BC08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514BC08.s")
