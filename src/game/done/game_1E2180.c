#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E2180.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 */

typedef struct Game1E2180EffectPacket {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 pad9[3];
    void *fieldC;
    s8 field10;
    u8 pad11[3];
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    s16 field28;
    s8 field2A;
    s8 field2B;
    s8 field2C;
    s8 field2D;
    u8 pad2E[2];
} Game1E2180EffectPacket;

typedef struct Game1E2180Actor {
    u8 pad0[0x3B];
    u8 field3B;
} Game1E2180Actor;

typedef struct Game1E2180Locals {
    s32 classification;
    s8 flag;
    u8 pad5[3];
    Game1E2180EffectPacket packet;
} Game1E2180Locals;

s32 func_15134070(void *);
u32 func_1513418C(void *, s32, u8, s32);
void func_1516962C(s32, void *, s32);
u32 func_150ADA20(void);
void *func_10022EC0(void *, const void *, u32);
extern u8 D_800A3FE6[];

u32 func_151B4CD0(Game1E2180Actor *arg0, u8 arg1, s32 arg2) {
    u32 result;
    Game1E2180Locals locals;
    u32 unused;

    if (arg0 == 0) {
        return 0;
    }
    locals.classification = func_15134070(arg0);
    if (locals.classification == 0x63) {
        return 0;
    }
    if (D_800A3FE6[locals.classification * 0x10] == 2) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    locals.packet.field0 = 0;
    locals.packet.field4 = 0;
    locals.packet.field8 = arg0->field3B;
    locals.packet.field14 = 0.0f;
    locals.packet.field18 = -27.0f;
    locals.packet.field1C = 16.0f;
    locals.packet.field20 = 15.0f;
    locals.packet.field24 = 0.448f;
    locals.packet.field10 = 2;
    locals.packet.field2A = 6;
    locals.packet.fieldC = arg0;
    locals.packet.field28 = (func_150ADA20() % 21U) + 0x28;
    locals.packet.field2B = 8;
    locals.packet.field2C = -1;
    locals.packet.field2D = 7;
    if (D_800A3FE6[locals.classification * 0x10] == 1) {
        locals.flag = 1;
    } else {
        locals.flag = 0;
    }
    result = func_1513418C(&locals.packet, 1, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x58, &locals.flag, 1);
    }
    return result;
}
void func_151B4EA4(f32 *, f32, f32, f32, s32, s32);

void func_151B4E4C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    f32 sp24[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp24[2] = arg2;
    func_151B4EA4(sp24, arg3, arg4, arg5, *(u8 *)((u8 *)arg6 + 0x58), *(u8 *)((u8 *)arg6 + 0xC));
}
f32 func_150ADA68(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                   f32, f32, s32, s32, s32, s32, s32, s32);
void func_151B4EA4(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4,
                   s32 arg5) {
    f32 factor = 0.20500001f;
    f32 vector[3];

    vector[0] = -arg1 * factor;
    vector[1] = -arg2 * factor;
    vector[2] = -arg3 * factor;
    func_151D9014(arg0, vector, (u8)arg4,
                   (func_150ADA68() * 0.497f) + -1.0f,
                   (func_150ADA20() % 31U) + 0x14,
                   (func_150ADA20() % 101U) + 0x9B,
                   (func_150ADA68() * 152.0f) + 109.0f,
                   func_150ADA20() & 1, 1.7f, 1.7f,
                   0, 0, 1, 0, (u8)arg5, 1);
}
