#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_119370.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 */

typedef struct Game119370Actor {
    u8 pad0[0x1D4];
    u8 *matrices;
} Game119370Actor;

typedef struct Game119370Light {
    u8 kind;
    s8 mode;
    s16 lifetime;
    u8 field4;
} Game119370Light;

s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *,
                  void *, f32);
void func_15145EA4(f32 **, f32 **, s32, s32);
f32 func_150ADA68(void);
void *func_15102B38(s32, u8, s32, s32, f32 *, s16, u8, f32, s32, u8, s32, s16, u8, s32);
s32 func_151C229C(f32 *, f32 *, s32, s32, u8, s32, f32, f32, f32, f32, f32, u8, void *, u8, u8, u8,
                  u8, u8, u8, s8, s32, f32, u8, s8, s32, u8, s32);
extern f32 D_800A1500[3];
extern f32 D_800A150C[3];
extern u8 D_800A1518[];
extern u8 D_800A1530[];
extern u8 D_800A1548[];
extern f32 D_800A154C;
extern f32 D_800A1550, D_800A1554, D_800A1558;
extern f32 D_800A155C, D_800A1560, D_800A1564;

s32 func_150EBEC0(Game119370Actor *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    Vec3f start;
    Vec3f direction;
    Vec3f position;
    Vec3f *velocity;
    Vec3f offset;
    f32 *inputs[2];
    f32 *outputs[2];
    f32 *input;
    f32 *output;
    Vec3f hit;
    f32 scatter[2];
    Game119370Light light;
    s32 lightPosition[3];
    f32 motion[2];
    f32 random2;
    u32 random;
    f32 random1;
    u32 scratch;

    if (arg0 == NULL) {
        return 0;
    }
    if (((u8 *)&arg1)[3] >= 2) {
        return 0;
    }
    if (arg0->matrices == NULL) {
        return 0;
    }
    inputs[0] = D_800A1500;
    inputs[1] = D_800A150C;
    outputs[0] = &start.x;
    outputs[1] = &direction.x;
    func_15145EA4(inputs, outputs, (s32)(arg0->matrices + 0x80), 2);
    direction.x -= start.x;
    direction.y -= start.y;
    direction.z -= start.z;
    {
        u8 *bone;

        value = ((u8 *)&arg1)[3];
        input = (f32 *)(D_800A1518 + value * 12);
        output = &position.x;
        scratch = (u32)(arg0->matrices + (D_800A1548[value] << 6));
        bone = &D_800A1548[value];
        func_15145EA4(&input, &output, scratch, 1);
        if (func_150AC9C0(start.x, start.y, start.z, direction.x, direction.y, direction.z, NULL,
                          NULL, &hit.x, &hit.y, &hit.z, NULL, NULL, NULL, 0.0f) != 0) {
            void func_15143874(s16, f32, f32 *, f32 *);

            random = func_150ADA20();
            random1 = func_150ADA68();
            func_15143874((s16)(random & 0xFF), random1 * 80.0f, &scatter[0], &scatter[1]);
            hit.x += scatter[0];
            hit.z += scatter[1];
            velocity = &offset;
            offset.x = hit.x - position.x;
            offset.y = hit.y - position.y;
            offset.z = hit.z - position.z;
        } else {
            velocity = &direction;
        }
        random1 = func_150ADA68();
        random2 = func_150ADA68();
        func_150ADA20();
        value = func_151C229C(&position.x, &velocity->x, 0, 0, 0, 0, 130.0f, D_800A154C,
                              random1 * 18.0f + 29.0f, random2 * 400.0f + 262.0f, 100.0f, 255,
                              arg0, 1, 1, 0, 0, 0, 1, 3, 0x1A, 0.0f, 255, -1, 0, ((u8 *)&arg2)[3],
                              arg3);
        {
            s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

            light.kind = 3;
            light.mode = -1;
            light.lifetime = func_150ADA20() % 3U + 3;
            light.field4 = 0;
            lightPosition[0] = position.x;
            lightPosition[1] = position.y;
            lightPosition[2] = position.z;
            scratch = func_150ADA20() % 13U + 90;
            func_151602C0((u8 *)&light, lightPosition, scratch, 255, 255, 255, 255, 0, 0,
                          ((u8 *)&arg2)[3], arg3);
        }
        motion[1] = (func_150ADA68() * D_800A1550 + D_800A1554) * D_800A1558;
        motion[0] = (func_150ADA68() * D_800A155C + 968.0f) * D_800A1560;
        scratch = func_150ADA20();
        random = func_150ADA20();
        random1 = func_150ADA68();
        func_15102B38((s32)arg0, *bone, (s32)(D_800A1518 + ((u8 *)&arg1)[3] * 12),
                      (s32)(D_800A1530 + ((u8 *)&arg1)[3] * 12), motion, scratch % 6U + 6,
                      random % 52U + 0xC1, random1 * D_800A1564 + 4000.0f,
                      (s32)&position, 255, 0, -1, ((u8 *)&arg2)[3], arg3);
    }
    return value;
}
s32 func_150EC3D4(void *arg0, void *arg1) {
    s32 temp_v0;

    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (temp_v0 == 0xFF) {
        return 0;
    }
    if ((temp_v0 == 0) || (temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) ||
        (temp_v0 == 4) || (temp_v0 == 0x28) || (temp_v0 == 0x77)) {
        return 1;
    }
    return 0;
}
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);

void func_150EC45C(void *arg0) {
    func_151C3B0C(arg0, 1.0f, 1.0f, 1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
}
