#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1E30A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_reconciled_empty_stub_splits.md
 */

typedef struct Game1E30A0Spawn {
    f32 field0, field4, field8, fieldC;
    Vec3f rotation, scale, position, velocity, acceleration;
    f32 field4C;
    s32 flags;
    s16 lifetime, resource;
    u8 field58;
    u8 pad59[3];
    s32 field5C;
    u8 field60, field61, field62, field63, field64, field65, field66, field67, field68;
    u8 pad69;
    u8 field6A;
    u8 pad6B;
    s32 field6C;
    u8 field70;
    u8 pad71;
    s16 step, rate;
    u8 tail76[6];
} Game1E30A0Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_15002FB4(s32);
void D_1500310C(void);
extern s8 D_8008FDA8;
extern f32 D_800AA430;

void *func_151B5BF0(Vec3f *arg0, Vec3f *arg1,
                   f32 arg2, Vec3f *arg3, Vec3f *arg4,
                   f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                   u8 arg10, u8 arg11, u8 arg12, s32 arg13) {
    void *result;
    Game1E30A0Spawn spawn;
    f32 extra[2];
    s32 step;

    extra[1] = arg2;
    extra[0] = 0.0f;
    spawn.fieldC = arg2;
    spawn.field8 = arg2;
    spawn.field0 = D_800AA430 * arg2;
    spawn.field4 = arg9;
    spawn.rotation = *arg3;
    spawn.scale.x = 1.0f;
    spawn.scale.y = 1.0f;
    spawn.scale.z = 1.0f;
    spawn.position = *arg0;
    spawn.flags = 0xB908;
    spawn.field4C = arg5;
    if (arg6 == -1) {
        spawn.lifetime = 300;
        step = 0x100 >> arg10;
    } else {
        step = 0x100 >> arg10;
        spawn.lifetime = arg6 + step;
        spawn.flags = 0xB988;
    }
    if (arg1 != 0) {
        spawn.velocity = *arg1;
        spawn.flags |= 0x20;
    } else {
        spawn.velocity.x = 0.0f;
        spawn.velocity.y = 0.0f;
        spawn.velocity.z = 0.0f;
    }
    {
        u32 checksum = 0;
        u32 cursor = (u32)func_15002FB4;
        u32 end = (u32)D_1500310C;

        if (cursor < end) {
            do {
                checksum += *(u32 *)cursor;
                cursor += 4;
                checksum <<= 1;
            } while (cursor < end);
        }
        if (checksum != 0x80D2D760U) {
            D_8008FDA8 = -1;
        }
    }
    if (arg4 != 0) {
        spawn.acceleration = *arg4;
        spawn.flags |= 0x40;
    } else {
        spawn.acceleration.x = 0.0f;
        spawn.acceleration.y = 0.0f;
        spawn.acceleration.z = 0.0f;
    }
    if (arg11 != 0) {
        spawn.flags |= 1;
    }
    spawn.resource = 2;
    spawn.field60 = arg7;
    spawn.field58 = 0;
    spawn.field5C = 0;
    spawn.field61 = 5;
    spawn.field62 = 0;
    spawn.field63 = 6;
    spawn.field64 = 0;
    spawn.field65 = 0;
    spawn.field66 = 2;
    spawn.field67 = 0;
    spawn.field68 = 2;
    spawn.field6A = 0;
    spawn.field6C = 0;
    spawn.field70 = 0;
    spawn.step = step;
    spawn.rate = 0xFF / step;
    result = func_15132A4C(&spawn, 3, 0xFF, 8, arg12, arg13);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, extra, sizeof(extra));
    }
    return result;
}

void func_151B5E8C(void) {

}
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_15047D60(f32);
void func_15133894(void *);
extern f32 D_800AA434;
extern f32 D_800AA438;
extern f32 D_800AA43C;
extern f32 D_800AA440;
extern f32 D_800BE9A4;

typedef struct Game1E30A0Wobble { f32 a; f32 b; } Game1E30A0Wobble;
typedef struct Game1E30A0Actor { u8 pad0[0x18]; f32 f18; f32 f1C; u8 pad20[0x18]; f32 x; f32 y; f32 z; u8 pad44[0x170-0x44]; Game1E30A0Wobble s; } Game1E30A0Actor;
void func_151B5E94(Game1E30A0Actor *arg0) {
    f32 value;
    Game1E30A0Wobble *values = &arg0->s;
    values->a += D_800AA434 * D_800BE9A4;
    if (values->a > D_800AA438) {
        values->a = 0.0f;
        func_10010F88(0x502, 0x5DC0U, 0, 0, -1, (s32)arg0->x, (s32)arg0->y, (s32)arg0->z, 0x64, 0x1F4);
    }
    if (values->a < D_800AA43C) {
        f32 t = func_15047D60(values->a);
        value = values->b + (t * (D_800AA440 * values->b));
        arg0->f1C = value;
        arg0->f18 = value;
    } else {
        value = values->b;
        arg0->f1C = value;
        arg0->f18 = value;
    }
    func_15133894(arg0);
}
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, void *);

void func_151B5FCC(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0 & 0xFFFF, arg0);
        *(s32 *)((u8 *)arg0 + 0x88) = 0;
    }
}
