#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6B40.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9690
 * - func_151B9964
 * - func_151B9CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1E6B40Packet {
    void *resource;
    u32 packed;
    s32 mode;
    s16 flags, scale;
    s16 x, y, z, velocityX, velocityZ, decay;
    u8 pad1C[3], reserved;
    s16 fall, acceleration, scaleX, scaleZ, contact;
    u8 enabled, phase, red, green, blue;
    u8 alpha;
    u8 pad30[4];
    s16 trailing;
    u8 pad36[2];
} Game1E6B40Packet;
f32 func_15047D60(f32);
f32 func_15047C00(f32);
u32 func_150ADA20(void);
void func_15167D84(void *, s32, s32, s32, u8, s32);
extern void *D_8008CA4C[];
extern f32 D_800AA580;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9690 CURRENT (6044) */
void func_151B9690(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
    f32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
    s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16) {
    Game1E6B40Packet packet;
    s32 initialHeight;
    f32 deltaX, deltaZ, radius;
    s32 incrementedHeight;
    f32 sine, cosine;
    s32 lifetime;
    f32 magnitude;
    u8 red, green, blue;
    s32 range;
    f32 angle;

    initialHeight = *(s16 *)((u8 *)&arg3 + 2);
    arg6 += 180.0f;
    angle = (arg6 + (f32)(s32)(func_150ADA20() %
        (u32)*(s16 *)((u8 *)&arg7 + 2) -
        (u32)(*(s16 *)((u8 *)&arg7 + 2) >> 1))) * D_800AA580;
    sine = func_15047D60(angle);
    cosine = func_15047C00(angle);
    angle = (f32)*(s16 *)((u8 *)&arg10 + 2);
    range = *(s16 *)((u8 *)&arg11 + 2);
    if (range == 0) {
        range = 1;
    }
    *(s16 *)((u8 *)&arg11 + 2) = range;
    magnitude = angle + (f32)(s32)(func_150ADA20() %
        (u32)*(s16 *)((u8 *)&arg11 + 2) -
        (u32)(*(s16 *)((u8 *)&arg11 + 2) >> 1));
    radius = (f32)*(s16 *)((u8 *)&arg12 + 2);
    incrementedHeight = *(s16 *)((u8 *)&arg3 + 2) + 1;
    *(s16 *)((u8 *)&arg3 + 2) = incrementedHeight;
    deltaX = (f32)*(s16 *)((u8 *)&arg2 + 2) + radius * sine;
    deltaZ = (f32)*(s16 *)((u8 *)&arg4 + 2) + radius * cosine;
    *(s16 *)((u8 *)&arg2 + 2) = (s16)(s32)deltaX;
    *(s16 *)((u8 *)&arg4 + 2) = (s16)(s32)deltaZ;
    lifetime = *(s16 *)((u8 *)&arg8 + 2) +
        (s32)(func_150ADA20() % (u32)*(s16 *)((u8 *)&arg9 + 2) -
        (u32)(*(s16 *)((u8 *)&arg9 + 2) >> 1));
    if (arg1 == 0 || arg1 == 1) {
        blue = 0xFF;
        green = 0xFF;
        red = 0xFF;
    } else {
        red = 0x68;
        switch (arg1) {
        case 2:
            green = 0x38;
            blue = 0x10;
            break;
        case 3:
        default:
            blue = 0xFF;
            green = 0xFF;
            red = 0xFF;
            break;
        }
    }
    packet.packed = ((u32)*(s16 *)((u8 *)&arg13 + 2) << 16) | (initialHeight & 0xFFFF);
    packet.resource = D_8008CA4C[arg0];
    packet.scale = 0x100;
    packet.x = *(s16 *)((u8 *)&arg2 + 2);
    packet.mode = arg1;
    packet.flags = 0;
    packet.decay = *(s16 *)((u8 *)&arg14 + 2);
    packet.reserved = 0;
    packet.fall = lifetime;
    packet.acceleration = -0xA0;
    packet.scaleX = *(s16 *)((u8 *)&arg14 + 2);
    packet.scaleZ = *(s16 *)((u8 *)&arg14 + 2);
    packet.contact = 0x190;
    packet.enabled = 0;
    packet.y = *(s16 *)((u8 *)&arg3 + 2);
    packet.z = *(s16 *)((u8 *)&arg4 + 2);
    packet.velocityX = (s16)(s32)(magnitude * sine);
    packet.velocityZ = (s16)(s32)(magnitude * cosine);
    packet.phase = func_150ADA20();
    packet.alpha = 0xFF;
    packet.trailing = 0;
    packet.red = red;
    packet.green = green;
    packet.blue = blue;
    func_15167D84(&packet, 0, 0, -1, *(u8 *)((u8 *)&arg15 + 3), arg16);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9690 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9690.s")

typedef struct Game1E6B40Pulse {
    u8 pad0;
    u8 kind;
    u8 pad2[0xA];
    u8 owner;
    u8 padD[7];
    s32 packed;
    s32 mode;
    u8 pad1C[4];
    s16 x, y, z;
    u8 pad26[4];
    s16 decay;
    u8 pad2C[4];
    s16 fall;
    u8 pad32[2];
    s16 scaleX, scaleZ, contact;
    u8 pad3A;
    u8 phase;
    u8 pad3C[3];
    u8 alpha;
} Game1E6B40Pulse;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150489B0(u8);
f32 func_15048A40(u8);
u32 func_150ADA20(void);
void func_15171D4C(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800BE9E4;
extern f32 D_800AA584, D_800AA588, D_800AA58C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9964 CURRENT (860) */
void func_151B9964(Game1E6B40Pulse *arg0) {
    f32 decay;
    volatile s16 height;
    s32 packed;
    s32 mode;
    u8 phase;
    s16 scale;
    register s16 y;
    register s32 target;
    register s32 value;

    mode = arg0->mode;
    if (mode == 1) {
        target = arg0->phase;
        phase = (u8)((u32)target + (u32)D_800BE9E4 * 4U + (u32)D_800BE9E4 * 2U);
        arg0->phase = phase;
        arg0->decay = (s16)(s32)((f32)arg0->decay * D_800AA584);
        decay = (f32)arg0->decay;
        arg0->scaleX = (s16)(s32)((func_15048A40(phase) + 3.0f) * decay * D_800AA588);
        arg0->scaleZ = (s16)(s32)((func_150489B0(phase) + 3.0f) * decay * D_800AA58C);
    } else {
        scale = arg0->scaleX;
        target = arg0->packed >> 16;
        if (target != scale) {
            value = (s32)((u32)scale - (u32)D_800BE9E4 * 4U);
            if (value < target) {
                value = target;
            }
            arg0->scaleZ = (s16)value;
            arg0->scaleX = (s16)value;
        }
    }
    packed = arg0->packed;
    y = arg0->y;
    if ((s16)packed >= y) {
        arg0->contact = 0;
        if (mode == 0) {
            height = (s16)packed;
            if ((s32)(func_150ADA20() & 0xFF) < 0x40) {
                y = height;
                func_15171D4C((f32)arg0->x, (f32)y, (f32)arg0->z,
                    0xA, 0, 0x13, 0.0f, 0, 0x32, 0xF, 0x100, 0,
                    arg0->owner, arg0->kind);
            }
            if ((s32)(func_150ADA20() & 0xFF) < 0xF) {
                func_150ADA20();
                func_10010F88(0x70, 0x1388, 0, 0, 0, arg0->x, height, arg0->z, 0x1F4, 0x7D0);
            }
        }
    } else {
        value = y - (s16)packed;
        if (arg0->fall < 0 && value < 0x40) {
            arg0->alpha = value * 4;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9964 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9964.s")
void *func_15167A68(s32, s32, s32, s32, s32, s32);

void func_151B9BF0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4,
    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 arg10, s16 arg11,
    s16 arg12, s32 arg13, u8 arg14, s32 arg15) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(7, arg15, 0x2C, 0, (s32)arg14, 1);
    if (temp_v0 != 0) {
        *(s8 *)(temp_v0 + 0x14) = (s8)arg0;
        *(s8 *)(temp_v0 + 0x15) = (s8)arg1;
        *(s16 *)(temp_v0 + 0x16) = arg2;
        *(s16 *)(temp_v0 + 0x18) = arg3;
        *(s16 *)(temp_v0 + 0x1A) = arg4;
        *(s16 *)(temp_v0 + 0x1C) = arg5;
        *(s16 *)(temp_v0 + 0x1E) = arg6;
        *(s16 *)(temp_v0 + 0x20) = arg7;
        *(s16 *)(temp_v0 + 0x22) = arg8;
        *(s16 *)(temp_v0 + 0x24) = arg9;
        *(s16 *)(temp_v0 + 0x26) = arg10;
        *(s16 *)(temp_v0 + 0x28) = arg11;
        *(s16 *)(temp_v0 + 0x2A) = arg12;
        *(s32 *)(temp_v0 + 0x10) = arg13;
    }
}
void func_1516972C(u8 *);
void func_151B9690(s32, s32, s32, s32, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800BE9E4;

typedef struct Game1E6B40Controller {
    u8 pad00[0x28];
    s16 count;
    s16 lifetime;
} Game1E6B40Controller;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9CB0 CURRENT (1910) */
void func_151B9CB0(u8 *arg0) {
    s32 remaining;
    s16 x, y, z;
    const Game1E6B40Controller *controller;
    s32 i;
    f32 *position;

    position = *(f32 **)(arg0 + 0x10);
    controller = (const Game1E6B40Controller *)arg0;
    if (position == 0) {
        x = *(s16 *)(arg0 + 0x16);
        y = *(s16 *)(arg0 + 0x18);
        z = *(s16 *)(arg0 + 0x1A);
    } else {
        x = (s16)(s32)position[0];
        y = (s16)(s32)position[1];
        z = (s16)(s32)position[2];
    }
    i = 0;
    if (controller->count > 0) {
        do {
            func_151B9690(arg0[0x14], arg0[0x15], x, y, z, -0x50,
                0.0f, 0x168, *(s16 *)(arg0 + 0x1C), *(s16 *)(arg0 + 0x1E),
                *(s16 *)(arg0 + 0x20), *(s16 *)(arg0 + 0x22), 0xF,
                *(s16 *)(arg0 + 0x24), *(s16 *)(arg0 + 0x26), arg0[0xC], arg0[1]);
            i++;
        } while (i < controller->count);
        i = 0;
    }
    do {
        func_151B9690(arg0[0x14], arg0[0x15], x, y, z, -0x50,
            0.0f, 0x168, (*(s16 *)(arg0 + 0x1C) * 3) / 2,
            *(s16 *)(arg0 + 0x1E) * 2, *(s16 *)(arg0 + 0x20),
            *(s16 *)(arg0 + 0x22), 0xF, *(s16 *)(arg0 + 0x24),
            *(s16 *)(arg0 + 0x26), arg0[0xC], arg0[1]);
        i++;
    } while (i != 4);
    remaining = *(s16 *)(arg0 + 0x2A) - D_800BE9E4;
    if (remaining < 0) {
        func_1516972C(arg0);
        return;
    }
    *(s16 *)(arg0 + 0x2A) = remaining;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6B40/func_151B9CB0.s")
