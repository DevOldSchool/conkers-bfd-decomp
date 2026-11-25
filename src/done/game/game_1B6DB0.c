#include "types.h"
#include "game_functions.h"
#include "game_view.h"

/*
 * Reviewed source unit: src/game/game_1B6DB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 */

typedef struct {
    u8 pad0;
    u8 field01;
    u8 pad2[0xA];
    u8 field0C;
    u8 padD[3];
    s16 field10;
    s16 field12;
    s16 field14;
    s16 field16;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    s16 field48;
    s16 field4A;
    f32 field4C;
    f32 field50;
    s16 field54;
    s16 field56;
    s32 field58;
    s32 field5C;
    s16 field60;
    u8 pad62[2];
    f32 field64;
    f32 field68;
    s16 *field6C;
    u8 field70;
} Game1B6DB0Effect;

void *func_10022EC0(void *, const void *, u32);
void func_1510F800(s32);
s32 func_1510FD20(s32, s32);

void func_15189900(void *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 var_v0;
    Game1B6DB0Effect *effect;

    effect = func_15167A68(0x1A, 1, 0x78, 1, 0xFF, 1);
    if (effect != 0) {
        func_10022EC0((u8 *)effect + 0x10, arg0, 0x50);
        func_1510F800(0);
        effect->field6C = (s16 *)func_1510FD20(
            (s32)(effect->field18 + (effect->field24 * 0.5f)),
            (s32)(effect->field20 + (effect->field2C * 0.5f)));
        if (arg1 != 0) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        temp_fv0 = effect->field28;
        effect->field70 = var_v0;
        effect->field60 = 0;
        effect->field64 = 0.0f;
        if (temp_fv0 < 0.0f) {
            effect->field68 = effect->field1C + temp_fv0;
            return;
        }
        effect->field68 = effect->field1C;
    }
}
typedef struct Game1B6DB0Spawn {
    f32 x, y, z;
    s16 lifetime, field0E;
    s32 field10;
    u8 field14, kind;
} Game1B6DB0Spawn;

typedef struct Game1B6DB0Motion {
    f32 size, vx, vy, vz, scale, field14;
    u8 field18, field19, field1A, alpha;
    s16 field1C, field1E;
} Game1B6DB0Motion;

typedef struct Game1B6DB0Particle {
    u8 pad0[0x98];
    f32 *data;
} Game1B6DB0Particle;

typedef struct Game1B6DB0Options {
    s32 field00, field04, field08, field0C, field10, field14, field18;
    u8 field1C, field1D;
} Game1B6DB0Options;

f32 func_150ADA68(void);
extern s32 D_80082FA0;
extern f32 D_800A73A0;
extern f32 D_800A73A4;
extern u8 D_800BE630[];
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

void func_15189A00(Game1B6DB0Effect *arg0) {
    Game1B6DB0Effect *effect;
    s32 found;
    s32 i;
    u8 player;
    f32 *values;
    f32 dx, dy, dz;
    Game1B6DB0Particle *particle;
    Game1B6DB0Spawn spawn;
    Game1B6DB0Motion motion;
    f32 height;
    Game1B6DB0Options options;
    s32 flag;

    effect = arg0;
    if (effect->field6C == NULL || func_151464B8(effect->field6C) == 0) {
        effect->field60 -= D_800BE9E4;
        if (effect->field60 < 0) {
            effect->field60 += 50;
            found = 0;
            for (i = 0; i <= D_80082FA0 && found == 0; i++) {
                player = D_800BE630[i];
                values = &D_800DBFF0[player].unk2F8;
                dx = values[0] - arg0->field18;
                dy = values[1] - arg0->field1C;
                dz = values[2] - arg0->field20;
                if (dx * dx + dy * dy + dz * dz < D_800A73A0) {
                    found = 1;
                }
            }
            if (found == 0) {
                return;
            }
        }
        effect->field64 += (effect->field38 + func_150ADA68() * effect->field3C) * D_800BE9A4;
        if (effect->field64 > 1.0f) {
            height = effect->field68;
            spawn.field10 = 1;
            spawn.field0E = 5;
            motion.field1C = 0x10;
            motion.field1E = 0xF;
            motion.field14 = D_800A73A4;
            motion.field18 = 0x48;
            motion.field19 = 3;
            motion.field1A = 0xFF;
            options.field00 = 0;
            options.field04 = 1;
            options.field08 = 0x160600;
            options.field0C = 3;
            options.field10 = 0x22;
            options.field14 = 0x80;
            options.field18 = 0x20;
            options.field1C = 0;
            options.field1D = 7;
            do {
                spawn.kind = func_150ADA20() % (u32)(effect->field5C + 1) + effect->field58;
                {
                    f32 random;

                    random = func_150ADA68();
                    spawn.x = arg0->field18 + random * effect->field24;
                    spawn.y = arg0->field1C + random * effect->field28;
                    spawn.z = arg0->field20 + random * effect->field2C;
                }
                motion.size = func_150ADA68() * effect->field44 + effect->field40;
                {
                    s16 yaw, pitch;
                    f32 speed;
                    f32 sinYaw, cosYaw, sinPitch, cosPitch;
                    f32 horizontal;

                    yaw = effect->field10 - func_150ADA20() % (u32)(effect->field12 * 2 + 1) - -effect->field12;
                    pitch = func_150ADA20() % (u32)(effect->field16 + 1) + effect->field14;
                    speed = func_150ADA68() * effect->field34 + effect->field30;
                    sinYaw = func_151423D8(yaw);
                    cosYaw = func_151423D8(yaw - 0x40);
                    sinPitch = func_151423D8(pitch);
                    cosPitch = func_151423D8(pitch - 0x40);
                    horizontal = speed * sinPitch;
                    motion.vx = horizontal * cosYaw;
                    motion.vy = -speed * cosPitch;
                    motion.vz = horizontal * sinYaw;
                }
                motion.scale = func_150ADA68() * effect->field50 + effect->field4C;
                motion.alpha = func_150ADA20() % (u32)(effect->field4A + 1) + effect->field48;
                spawn.lifetime = func_150ADA20() % (u32)(effect->field56 + 1) + effect->field54;
                if (effect->field70 & 1) {
                    flag = 10;
                } else {
                    flag = 0;
                }
                particle = func_15147DA0(&spawn, &motion, 8, 1, flag,
                                         0, 0, 0, 0, 0, 0, &options, 0, effect->field0C, effect->field01);
                if (particle != NULL) {
                    values = particle->data;
                    func_10022EC0(&values[18], &height, 4);
                }
                effect->field64 -= 1.0f;
            } while (effect->field64 > 1.0f);
        }
    }
}
typedef struct Game1B6DB0RoutePoint {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[8];
} Game1B6DB0RoutePoint;

typedef struct Game1B6DB0Emitter {
    f32 scale;
    u8 pad4[0x17];
    u8 field_1B;
    u8 pad1C[4];
    s8 field_20;
    u8 pad21[0x27];
    f32 height;
} Game1B6DB0Emitter;

typedef struct Game1B6DB0RouteObject {
    u8 pad0;
    u8 field_01;
    u8 pad2[0xA];
    u8 field_0C;
    u8 padD[0x20];
    s8 route_index;
    u8 pad2E[0x66];
    Game1B6DB0RoutePoint *route;
    Game1B6DB0Emitter *emitter;
} Game1B6DB0RouteObject;

u8 func_151D8E20(void);
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);
f32 func_150ADA68(void);
extern f64 D_800A73A8;
extern f32 D_800A73B0;

s32 func_15189EBC(Game1B6DB0RouteObject *arg0) {
    f64 chance;
    Game1B6DB0Emitter *emitter;
    Game1B6DB0RoutePoint *point;
    f32 position[3];

    point = arg0->route;
    emitter = arg0->emitter;
    if (point[arg0->route_index].y < emitter->height) {
        chance = (f64)func_150ADA68();
        if (chance < D_800A73A8) {
            position[0] = point[arg0->route_index].x;
            position[1] = emitter->height;
            position[2] = point[arg0->route_index].z;
            func_151DBCBC(func_151D8E20() & 0xFF, emitter->scale * 6.0f,
                          emitter->field_1B, 0, position, arg0->field_0C,
                          arg0->field_01);
        }
        emitter->field_20 = 4;
        emitter->height = D_800A73B0;
    }
    return 1;
}
