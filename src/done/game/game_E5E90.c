#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_E5E90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 */

typedef struct GameE5E90Object {
    u8 pad00;
    u8 field01;
    u8 pad02[0xA];
    u8 field0C;
    u8 pad0D[3];
    f32 field10;
    f32 damping;
    u8 pad18[8];
    Vec3f position;
    u8 pad2C[0xC];
    Vec3f origin;
    Vec3f velocity;
    Vec3f spin;
    u8 pad5C[4];
    s32 flags;
    u8 pad64[0xE];
    u8 field72;
    u8 pad73[5];
    u8 field78;
    u8 pad79[0xAF];
    s32 field128;
    u8 pad12C[0x14];
    f32 timer;
    u8 pad144[8];
    s32 field14C;
    u8 pad150[0x18];
    s32 field168;
} GameE5E90Object;

typedef struct GameE5E90Descriptor {
    u8 kind;
    u8 field01;
    s16 mode;
    s16 lifetime;
    u8 pad06[2];
    s32 field08;
    s32 field0C;
    u8 color[4];
    f32 scale14;
    f32 scale18;
    Vec3f position;
    Vec3f velocity;
    Vec3f acceleration;
    s32 flags;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    u8 pad48[8];
    s32 field50;
    s16 field54;
    s16 field56;
} GameE5E90Descriptor;

typedef struct GameE5E90Particle {
    u8 pad000[0x128];
    f32 field128[2];
} GameE5E90Particle;

typedef struct GameE5E90Burst {
    Vec3f position;
    f32 sizeBase, sizeRange, growthBase, growthRange, speedBase, speedRange;
    s16 countBase, countRange, yawBase, yawRange, pitchBase, pitchRange;
    s16 fadeBase, fadeRange, lifeBase, lifeRange;
    u8 green, enabled, red, pad3B;
    s32 callbacks[6];
    u8 blue, alphaBase, alphaRange, pad57;
    s32 field58, field5C;
    s32 flags[7];
    u8 field7C, field7D, pad7E[2];
    s16 field80, field82;
    s32 field84;
} GameE5E90Burst;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, f32, f32);
f32 func_150ADA68(void);
void *func_1513D594(s32, s32, u8, u8, u8, u8, s16, f32, f32, s32, s32, s32, s32, u8, s32, u8, s32);
void func_15151A38(GameE5E90Burst *, u8, s32);
extern u8 D_800A4AA0[];

s32 func_150B89E0(GameE5E90Object *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    GameE5E90Descriptor descriptor;
    GameE5E90Particle *object;
    f32 rate;

    arg0->origin.y = arg0->field10 + arg4;
    if (arg0->timer > 15.0f) {
        if (arg0->timer > 30.0f) {
            descriptor.field54 = 0x19;
            descriptor.field56 = 0xA;
            descriptor.kind = 4;
            descriptor.field01 = 0;
            descriptor.mode = 0x3B02;
            descriptor.lifetime = (func_150ADA20() % 31U) + 0x28;
            descriptor.field08 = 0;
            descriptor.field0C = 0;
            descriptor.color[0] = 0xFF;
            descriptor.color[1] = 0xFF;
            descriptor.color[2] = 0xFF;
            descriptor.color[3] = 0xFF;
            descriptor.scale14 = descriptor.scale18 =
                (func_150ADA68() * 25.0f + 25.0f) * D_8009FDB0;
            descriptor.flags = 0x0C5C0001;
            descriptor.field44 = 0xFF;
            descriptor.field45 = 0xFF;
            descriptor.field46 = 0;
            descriptor.field47 = 7;
            descriptor.position.x = arg1;
            descriptor.velocity.x = 0.0f;
            descriptor.velocity.y = 0.0f;
            descriptor.velocity.z = 0.0f;
            descriptor.acceleration.x = 0.0f;
            descriptor.acceleration.y = 0.0f;
            descriptor.acceleration.z = 0.0f;
            descriptor.position.y = arg4;
            descriptor.position.z = arg3;
            rate = (func_150ADA68() * 80.0f + 50.0f) * D_8009FDB4;
            descriptor.field50 = arg0->field128;
            object = func_1513D594((s32)&descriptor, (s32)D_800A4AA0, 0x18, 0, 0,
                                   (func_150ADA20() & 1) * 2 + (func_150ADA20() & 1),
                                   func_150ADA20() & 0xFF, 500.0f, 500.0f, 0,
                                   arg5, arg0->field14C, arg0->field168, 0, 8,
                                   arg0->field0C, arg0->field01);
            if (object != NULL) {
                /* The original copies 8 bytes from the 4-byte rate local. */
                func_10022EC0(object->field128, &rate, 8);
            }
            {
                GameE5E90Burst burst;

                burst.position.x = arg1;
                burst.position.y = arg4;
                burst.position.z = arg3;
                burst.sizeBase = 3.0f;
                burst.sizeRange = 3.0f;
                burst.growthBase = D_8009FDB8;
                burst.growthRange = 0;
                burst.speedBase = 10.0f;
                burst.speedRange = 10.0f;
                burst.countBase = 6;
                burst.countRange = 6;
                burst.yawBase = 0;
                burst.yawRange = 0xFF;
                burst.pitchBase = -0x3F;
                burst.pitchRange = 0x1D;
                burst.fadeBase = 3;
                burst.fadeRange = 3;
                burst.lifeBase = 0x32;
                burst.lifeRange = 0x14;
                burst.green = 1;
                burst.enabled = 0x21;
                burst.red = 0x48;
                burst.callbacks[0] = 1;
                burst.callbacks[1] = 0;
                burst.callbacks[2] = 0;
                burst.callbacks[3] = 0;
                burst.callbacks[4] = 0;
                burst.callbacks[5] = 0;
                burst.blue = 0;
                burst.alphaBase = 0x9B;
                burst.alphaRange = 0x64;
                burst.field58 = arg0->field14C;
                burst.field5C = arg0->field168;
                burst.flags[0] = 0;
                burst.flags[1] = 0x220005;
                burst.flags[2] = 0x1D0600;
                burst.flags[3] = 1;
                burst.flags[4] = 0x3B;
                burst.flags[5] = 0x80;
                burst.flags[6] = 0x20;
                burst.field7C = 0;
                burst.field7D = 7;
                burst.field80 = 0xA;
                burst.field82 = 0x19;
                burst.field84 = arg0->field128;
                func_15151A38(&burst, arg0->field0C, arg0->field01);
            }
            func_10010F88(D_80088734[func_150ADA20() & 1], 0x7D00, 0, 0, 0,
                          arg0->origin.x, arg4 + 25.0f, arg0->origin.z, 1000, 4000);
            return 0;
        }
        arg0->velocity.x *= arg0->damping;
        arg0->velocity.y = -arg0->velocity.y * arg0->damping;
        arg0->velocity.z *= arg0->damping;
        arg0->spin.x *= arg0->damping;
        arg0->spin.y *= arg0->damping;
        arg0->spin.z *= arg0->damping;
        func_10010F88(D_8008873C, 0x7D00, 0, 0, 0, arg0->origin.x, arg0->origin.y,
                      arg0->origin.z, 1000, 4000);
    } else {
        f32 matrix[4][4];

        arg0->field72 = 1;
        arg0->field78 = 1;
        arg0->flags &= ~0xFF;
        func_150A8050(matrix, arg0->position.x, arg0->position.y, arg0->position.z);
        func_150A7960(matrix, 0.0f, 0.0f, 200.0f, &arg0->position.x, &arg0->position.y,
                      &arg0->position.z);
        arg0->position.x += arg0->origin.x;
        arg0->position.y += arg0->origin.y;
        arg0->position.z += arg0->origin.z;
    }
    return 1;
}

typedef struct GameE5E90Surface {
    s16 data[9];
} GameE5E90Surface;

typedef struct GameE5E90SurfaceBurst {
    Vec3f position;
    Vec3f normal;
    GameE5E90Surface surface;
    u8 pad2A[2];
    f32 spread;
    f32 sizeBase, sizeRange, growthBase, growthRange, speedBase, speedRange;
    s16 countBase, countRange, fadeBase, fadeRange, lifeBase, lifeRange;
    u8 green, enabled, red, pad57;
    s32 callbacks[6];
    u8 blue, alphaBase, alphaRange, pad73;
    s32 field74, field78;
    s32 flags[7];
    u8 field98, field99, pad9A[2];
    s16 field9C, field9E;
    s32 fieldA0;
} GameE5E90SurfaceBurst;

typedef struct GameE5E90Target {
    u8 pad00[0x14];
    Vec3f position;
} GameE5E90Target;

s32 func_150A3058(s32, s16, s16, s16);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *,
                  s32 *, void *, f32);
s32 func_15145C90(s32);
void func_15151670(GameE5E90SurfaceBurst *, u8, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

s32 func_150B8F44(GameE5E90Object *arg0, GameE5E90Target *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 height;

    height = arg0->timer - fabsf(arg0->velocity.y);
    if (height > 6.0f) {
        if (func_150A3058(1, arg1->position.x, arg1->position.y, arg1->position.z) == 0) {
            Vec3f delta;
            Vec3f hit;
            GameE5E90Surface surface;
            s32 id;
            GameE5E90Descriptor descriptor;
            GameE5E90Particle *object;
            f32 rate;

            delta.x = arg0->origin.x - arg2;
            delta.y = arg0->origin.y - arg3;
            delta.z = arg0->origin.z - arg4;
            if (func_150AC9C0(arg2, arg3, arg4, delta.x, delta.y, delta.z, NULL, surface.data,
                              &hit.x, &hit.y, &hit.z, NULL, &id, NULL, 0.0f) != 0) {
                switch (func_15145C90(id)) {
                case 0:
                    break;
                default:
                    descriptor.field54 = 0x19;
                    descriptor.field56 = 0xA;
                    descriptor.kind = 4;
                    descriptor.field01 = 0;
                    descriptor.mode = 0x3B02;
                    descriptor.lifetime = (func_150ADA20() % 31U) + 0x28;
                    descriptor.field08 = 0;
                    descriptor.field0C = 0;
                    descriptor.color[0] = 0xFF;
                    descriptor.color[1] = 0xFF;
                    descriptor.color[2] = 0xFF;
                    descriptor.color[3] = 0xFF;
                    descriptor.scale14 = descriptor.scale18 =
                        (func_150ADA68() * 25.0f + 25.0f) * D_8009FDBC;
                    descriptor.position = hit;
                    descriptor.flags = 0x0C5C0001;
                    descriptor.field44 = 0xFF;
                    descriptor.field45 = 0xFF;
                    descriptor.field46 = 0;
                    descriptor.field47 = 7;
                    descriptor.velocity.x = 0.0f;
                    descriptor.velocity.y = 0.0f;
                    descriptor.velocity.z = 0.0f;
                    descriptor.acceleration.x = 0.0f;
                    descriptor.acceleration.y = 0.0f;
                    descriptor.acceleration.z = 0.0f;
                    rate = (func_150ADA68() * 80.0f + 50.0f) * D_8009FDC0;
                    descriptor.field50 = arg0->field128;
                    object = func_1513D594((s32)&descriptor, (s32)D_800A4AA0, 0x18, 0, 0,
                                           (func_150ADA20() & 1) * 2 + (func_150ADA20() & 1),
                                           func_150ADA20() & 0xFF, 500.0f, 500.0f, 0,
                                           (s32)&surface, arg0->field14C, arg0->field168, 0, 8,
                                           arg0->field0C, arg0->field01);
                    if (object != NULL) {
                        /* The original copies 8 bytes from the 4-byte rate local. */
                        func_10022EC0(object->field128, &rate, 8);
                    }
                    break;
                }
                {
                    GameE5E90SurfaceBurst burst;

                    burst.normal.x = -delta.x;
                    burst.normal.y = -delta.y;
                    burst.normal.z = -delta.z;
                    burst.surface = surface;
                    burst.spread = 502.0f;
                    burst.position = hit;
                    burst.sizeBase = 3.0f;
                    burst.sizeRange = 3.0f;
                    burst.growthBase = D_8009FDC4;
                    burst.growthRange = D_8009FDC8;
                    burst.speedBase = D_8009FDCC;
                    burst.speedRange = D_8009FDD0;
                    burst.countBase = 6;
                    burst.countRange = 6;
                    burst.fadeBase = 3;
                    burst.fadeRange = 3;
                    burst.lifeBase = 0x32;
                    burst.lifeRange = 0x14;
                    burst.green = 1;
                    burst.enabled = 0x21;
                    burst.red = 0x48;
                    burst.callbacks[0] = 1;
                    burst.callbacks[1] = 0;
                    burst.callbacks[2] = 0;
                    burst.callbacks[3] = 0;
                    burst.callbacks[4] = 0;
                    burst.callbacks[5] = 0;
                    burst.blue = 0;
                    burst.alphaBase = 0x9B;
                    burst.alphaRange = 0x64;
                    burst.field74 = arg0->field14C;
                    burst.field78 = arg0->field168;
                    burst.flags[0] = 0;
                    burst.flags[1] = 0x220005;
                    burst.flags[2] = 0x1D0600;
                    burst.flags[3] = 1;
                    burst.flags[4] = 0x3B;
                    burst.flags[5] = 0x80;
                    burst.flags[6] = 0x20;
                    burst.field98 = 0;
                    burst.field99 = 7;
                    burst.field9C = 0xA;
                    burst.field9E = 0x19;
                    burst.fieldA0 = arg0->field128;
                    func_15151670(&burst, arg0->field0C, arg0->field01);
                }
            }
        }
        func_10010F88(D_80088734[func_150ADA20() & 1], 0x7D00, 0, 0, 0,
                      arg0->origin.x, arg0->origin.y, arg0->origin.z, 1000, 4000);
        return 0;
    }
    arg0->velocity.x = 0.0f;
    arg0->velocity.z = 0.0f;
    if (arg0->velocity.y > 0.0f) {
        arg0->velocity.y *= arg0->damping;
    }
    arg0->origin.x = arg1->position.x;
    arg0->origin.y = arg1->position.y;
    arg0->origin.z = arg1->position.z;
    arg0->spin.x *= arg0->damping;
    arg0->spin.y *= arg0->damping;
    arg0->spin.z *= arg0->damping;
    func_10010F88(D_8008873C, 0xFA00, 0, 0, 0, arg1->position.x, arg1->position.y,
                  arg1->position.z, 1000, 4000);
    return 1;
}
