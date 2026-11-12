#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_DC360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_selected_particle_resource_groups.md
 */

f32 func_150ADA68(void);

typedef struct GameDC360Spawn {
    f32 x, y, z;
    s16 lifetime, field0E;
    s32 field10;
    u8 field14, kind;
} GameDC360Spawn;

typedef struct GameDC360Motion {
    f32 size, vx, vy, vz, scale;
    u8 pad14[4];
    u8 field18, field19, field1A, alpha;
    u8 pad1C[4];
} GameDC360Motion;

typedef struct GameDC360Options {
    s32 field00, field04, field08, field0C, field10, field14, field18;
    u8 field1C, field1D;
} GameDC360Options;

void func_150AEEB0(void *arg0, u8 arg1) {
    f32 speed;
    GameDC360Spawn spawn;
    GameDC360Motion motion;
    s32 count, active;
    GameDC360Options options;
    f32 sinAngle, cosAngle, cosPitch, sinPitch;
    u8 angle, pitch;

    count = 30;
    active = 1;
    if (arg0 != 0) {
        options.field00 = 0;
        options.field04 = 1;
        options.field08 = 0x160600;
        options.field0C = 3;
        options.field10 = 0x10;
        options.field14 = 0x80;
        options.field18 = 0x20;
        options.field1C = 0;
        options.field1D = 9;
        spawn.field10 = 1;
        spawn.field0E = 1;
        motion.field19 = 8;
        motion.field1A = 0xFF - ((*(u32 *)((u8 *)arg0 + 0x184) >> 5) & 3) * 64;
        motion.field18 = 0x28;
        motion.alpha = 0xFF;
        do {
            angle = func_150ADA20() & 0xFF;
            pitch = -(func_150ADA20() % 21U + 0x28);
            sinPitch = func_151423D8(pitch);
            cosPitch = func_151423D8(pitch - 0x40);
            sinAngle = func_151423D8(angle);
            cosAngle = func_151423D8(angle - 0x40);
            speed = func_150ADA68() * 5.0f + 10.0f;
            spawn.x = *(f32 *)((u8 *)arg0 + 0x14) + 100.0f * cosAngle;
            spawn.y = *(f32 *)((u8 *)arg0 + 0x18) + 15.0f * func_150ADA68();
            spawn.z = *(f32 *)((u8 *)arg0 + 0x1C) + 100.0f * sinAngle;
            spawn.kind = func_150ADA20() % 7U + 3;
            spawn.lifetime = func_150ADA20() % 26U + 0x23;
            motion.size = func_150ADA68() * 6.0f + 2.0f;
            motion.scale = func_150ADA68() + 1.0f;
            motion.vx = speed * sinPitch * cosAngle;
            motion.vy = -speed * cosPitch;
            motion.vz = speed * sinPitch * sinAngle;
            if (func_15147DA0(&spawn, &motion, 0, 1, 3, 0, 0, 0, 0, 0, 0,
                             &options, 0, arg1, 0) == 0) {
                active = 0;
            }
        } while (active != 0 && --count != 0);
    }
}
s32 func_150AF1C0(void *arg0) {
    u8 *temp_v0;
    s32 var_v1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    var_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v1 *= 32;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)(temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
