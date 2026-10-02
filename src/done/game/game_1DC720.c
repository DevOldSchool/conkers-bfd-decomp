#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DC720.c
 * Boundary evidence: docs/evidence/game_raw_buffer_stream_families.md
 */

typedef struct Game1DC720EffectPacket {
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
} Game1DC720EffectPacket;

typedef struct Game1DC720Actor {
    u8 pad0[0x3B];
    u8 field3B;
} Game1DC720Actor;

extern f32 D_800A9DCC;
extern f32 D_800A9DD0;
void func_1516962C(s32, void *, s32);
u32 func_1513418C(void *, s32, u8, s32);

u32 func_151AF270(Game1DC720Actor *arg0, u8 arg1, s32 arg2) {
    s32 unused;
    Game1DC720EffectPacket packet;

    if (arg0 == 0) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    packet.field0 = 0;
    packet.field4 = 0;
    packet.field8 = arg0->field3B;
    packet.field10 = 1;
    packet.field14 = 0.0f;
    packet.field18 = 0.0f;
    packet.field2A = 6;
    packet.field1C = 0.0f;
    packet.field20 = D_800A9DCC;
    packet.field24 = D_800A9DD0;
    packet.field28 = 0x140;
    packet.field2B = 0xA;
    packet.field2C = -1;
    packet.field2D = 9;
    packet.fieldC = arg0;
    return func_1513418C(&packet, 0, arg1, arg2);
}
typedef struct {
    u8 pad_0[0xC];
    u8 field_C;
} Game1DC720State;

void func_151AF388(f32 *, f32, f32, f32, s32);

void func_151AF338(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                   Game1DC720State *arg6) {
    f32 sp24[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp24[2] = arg2;
    func_151AF388(sp24, arg3, arg4, arg5, arg6->field_C);
}
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32,
                   f32, f32, s32, s32, s32, s32, s32, s32);
extern const f32 D_800A9DD4;
extern const f32 D_800A9DD8;
extern const f32 D_800A9DDC;
extern const f32 D_800A9DE0;

void func_151AF388(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
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
