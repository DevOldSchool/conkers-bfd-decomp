#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DCA70.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AF6D4
 * - func_151AFC08
 * - func_151AFEA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern f32 D_800AA0F0;
extern f32 D_800AA0FC;

s32 func_151AF5C0(f32 *arg0, void *arg1, s32 arg2, u8 arg3) {
    f32 position[3];
    f32 *var_a0;
    s32 var_a2;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a0 = &D_800AA0FC;
    } else {
        var_a0 = &D_800AA0F0;
    }
    if (arg3 == 1) {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0x800;
    } else {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0x640;
    }
    func_15143134(var_a0, arg0, var_a2);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 100.0f;
    position[2] = arg0[2];
    func_1504715C((void *)arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 500.0f, (void *)arg2);
}
s32 func_151AF6C0(s32 arg0, s32 arg1) {
    return 0xC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AF6D4.s")
s32 func_151AFBD4(void *arg0) {
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
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AFC08 CURRENT (670) */
s32 func_151AFC08(u8 *arg0) {
    f32 temp_fv0;
    s32 temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        if (*(s16 *)((u8 *)arg0 + 0x1C) < 0x20) {
            temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
            if (temp_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v0;
            }
        }
        if (*(s16 *)((u8 *)arg0 + 0x128) < *(s16 *)((u8 *)arg0 + 0x1C)) {
            temp_fv0 = *(f32 *)((u8 *)(arg0 + 0x128) + 4) * D_800BE9A4;
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AFC08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFC08.s")
typedef struct Game1DCA70Particle {
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
} Game1DCA70Particle;

void *func_10022EC0(void *, const void *, u32);
void *func_15130374(s32, u8, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800AA110, D_800AA114, D_800AA118, D_800AA11C;

s32 func_151AFC88(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    void *temp_v0;
    Game1DCA70Particle packet;
    f32 size;
    f32 sp2C;
    f32 fraction;
    u32 sp24;

    packet.field1D = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = (func_150ADA20() & 0xF) + 0x19;
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
    packet.size1 = (func_150ADA68() * 202.0f) + 101.0f;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.position[2] = arg4;
    size = packet.size1;
    packet.size0 = size;
    sp24 = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16) ((sp24 % 21U) - 0x14), ((fraction * D_800AA110) + 500.0f) * D_800AA114, &packet.direction);
    packet.flags58 = 0xE05;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field62 = 6;
    packet.field63 = -1;
    packet.field1E = 0xF;
    packet.field20 = 0x11;
    packet.field22 = 0x19;
    packet.field24 = D_800AA118;
    sp2C = D_800AA11C;
    temp_v0 = func_15130374((s32) &packet, 1U, 4, ((u8 *)&arg14)[3], 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0xA8, &sp2C, 4U);
    }
    return 1;
}

extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AFEA4 CURRENT (100) */
s32 func_151AFEA4(void *arg0, s32 arg1) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_151AFEA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DCA70/func_151AFEA4.s")
