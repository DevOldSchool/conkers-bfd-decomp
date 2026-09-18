#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E2490.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 */

typedef struct Game1E2490EffectPacket {
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
} Game1E2490EffectPacket;

extern f32 D_800AA3E0;
extern f32 D_800AA3E4;
u32 func_1513418C(void *, s32, u8, s32);

u32 func_151B4FE0(void *arg0, u8 arg1, s32 arg2) {
    s32 unused;
    Game1E2490EffectPacket packet;

    if (arg0 == 0) {
        return 0;
    }
    packet.field0 = 0;
    packet.field4 = 0;
    packet.field8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field10 = 2;
    packet.field14 = 0.0f;
    packet.field18 = -27.0f;
    packet.field2A = 2;
    packet.field1C = 16.0f;
    packet.field20 = D_800AA3E0;
    packet.field24 = D_800AA3E4;
    packet.field28 = 0x12C;
    packet.field2B = 9;
    packet.field2C = -1;
    packet.field2D = 8;
    packet.fieldC = arg0;
    return func_1513418C((void *)&packet, 0, arg1, arg2);
}
typedef struct {
    u8 pad_0[0xC];
    u8 field_C;
} Game1E2490Data;

void func_151B50F4(f32 *, f32, f32, f32, s32);

void func_151B50A4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Game1E2490Data *arg6) {
    f32 sp24[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp24[2] = arg2;
    func_151B50F4(sp24, arg3, arg4, arg5, arg6->field_C);
}
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                   f32, f32, s32, s32, s32, s32, s32, s32);
void func_151B50F4(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 factor = 0.13000001f;
    f32 vector[3];
    u8 flag;

    vector[0] = -arg1 * factor;
    vector[1] = -arg2 * factor;
    vector[2] = -arg3 * factor;
    if (func_150ADA20() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_151D9014(arg0, vector, 0,
                   (func_150ADA68() * 0.126f) + -0.702f,
                   (func_150ADA20() & 0xF) + 0xA,
                   (func_150ADA20() % 45U) + 0x89,
                   (func_150ADA68() * 202.0f) + 142.0f,
                   flag, 1.7f, 1.7f, 0, 0, 1, 0,
                   (u8)arg4, 1);
}
