#include "types.h"
#include "game_vec.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_E7380.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

typedef struct GameE7380Actor {
    u8 pad0[0x14];
    Vec3f position;
} GameE7380Actor;

typedef struct GameE7380Triangle {
    s16 words[9];
} GameE7380Triangle;

typedef struct GameE7380Particle {
    s32 flags;
    s16 lifetime;
    u8 kind;
    u8 mode;
    s32 field8;
    s32 fieldC;
    u8 field10;
    u8 field11;
    u8 field12;
    u8 field13;
    u8 field14;
    u8 field15;
    u8 field16;
    u8 field17;
    s32 field18;
    u8 pad1C[6];
    s16 field22;
    s16 field24;
    u8 pad26[2];
} GameE7380Particle;

typedef struct GameE7380Spray {
    s16 countBase;
    s16 countRange;
    Vec3f position;
    Vec3f normal;
    GameE7380Triangle triangle;
    u8 pad2E[2];
    f32 spread;
    u8 field34;
    u8 field35;
    u16 field36;
    s16 field38;
    s16 field3A;
    f32 scaleBase;
    f32 scaleRange;
    s32 flags;
    u8 lifeBase;
    u8 lifeRange;
    u8 pad4A[2];
    f32 durationBase;
    f32 durationRange;
    f32 speedBase;
    f32 speedRange;
    u8 field5C;
    u8 field5D;
    u8 pad5E[2];
    s32 field60;
    s32 field64;
    s16 field68;
    s16 field6A;
    f32 field6C;
    f32 jitter;
} GameE7380Spray;

s32 func_150A3058(s32, s16, s16, s16);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, s32, s32, u8, s32);
s32 func_15145C90(s32);
f32 func_150ADA68(void);
void func_151511FC(GameE7380Spray *, u8, s32);
void func_151E7EF8(void);
void func_151E7F60(void);
extern u8 D_80084060;

void func_150B9ED0(void *arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    GameE7380Actor *actor;
    s32 *cursor;
    s32 *end;
    s32 sum;

    actor = arg0;
    if (actor != NULL) {
        sum = 0;
        end = (s32 *)func_151E7F60;
        for (cursor = (s32 *)func_151E7EF8; cursor < end; cursor++) {
            sum += ~*cursor;
        }
        if (sum != 0x3843095E) {
            D_80084060 = 0xFF;
        }
        if (func_150A3058(2, actor->position.x, actor->position.y, actor->position.z) != 0) {
            return;
        }
        if (func_150A3058(1, actor->position.x, actor->position.y, actor->position.z) != 0) {
            return;
        }
        {
            f32 y;
            void *result;
            s32 found;
            f32 dz;
            f32 dy;
            f32 dx;
            Vec3f hit;
            GameE7380Triangle triangle;
            s32 surface;
            GameE7380Particle particle;
            GameE7380Spray spray;

            y = actor->position.y + 80.0f;
            dx = -(actor->position.x - arg1);
            dy = 0.0f;
            dz = -(actor->position.z - arg2);
            found = func_150AC9C0(actor->position.x, y, actor->position.z, dx, dy, dz, NULL, triangle.words,
                    &hit.x, &hit.y, &hit.z, NULL, &surface, NULL, 0.0f);
            if (found == 0) {
                return;
            }
            if (func_15145C90(surface) != 0) {
                particle.kind = 6;
                particle.mode = 0;
                particle.flags = 0x9F01;
                particle.lifetime = (func_150ADA20() % 51U) + 100;
                particle.field8 = 0;
                particle.fieldC = 0;
                particle.field10 = (func_150ADA20() % 101U) + 155;
                particle.field11 = 0xFF;
                particle.field12 = 0xFF;
                particle.field13 = 0xFF;
                particle.field14 = 0xFF;
                particle.field15 = 0xFF;
                particle.field18 = 0x3B0002;
                particle.field16 = 0;
                particle.field17 = 7;
                particle.field22 = 0x19;
                particle.field24 = 0xA;
                result = func_1513C650((s32)&particle, 0, 0, (s32)&triangle, hit.x, hit.y, hit.z,
                    func_150ADA68() * 20.0f + 40.0f, func_150ADA68() * 20.0f + 40.0f,
                    func_150ADA20() & 0xFF,
                    (func_150ADA20() & 1) * 2 + (func_150ADA20() & 1), 3, 0xFF, 0, arg3, arg4);
            }
            spray.countBase = 0xF;
            spray.countRange = 0xA;
            spray.position = hit;
            spray.normal.x = -dx;
            spray.normal.y = -dy;
            spray.normal.z = -dz;
            spray.triangle = triangle;
            spray.spread = D_8009FE10;
            spray.scaleBase = 7.0f;
            spray.scaleRange = 10.0f;
            spray.durationBase = D_8009FE14;
            spray.durationRange = D_8009FE18;
            spray.field34 = 7;
            spray.field36 = 0x3B01;
            spray.field35 = 0;
            spray.field38 = 0x1A;
            spray.field3A = 0x14;
            spray.flags = 0x5C0001;
            spray.lifeBase = 100;
            spray.lifeRange = 155;
            spray.field5C = 0;
            spray.field5D = 7;
            spray.field60 = 3;
            spray.field64 = 0xFF;
            spray.field68 = 0xA;
            spray.field6A = 0x19;
            spray.speedBase = D_8009FE1C;
            spray.speedRange = D_8009FE20;
            spray.field6C = D_8009FE24;
            spray.jitter = D_8009FE28;
            func_151511FC(&spray, arg3, arg4);
        }
    }
}
typedef struct GameE7380Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameE7380Object;

s32 func_150BA35C(GameE7380Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x40) {
        arg0->field_28 = value * 4;
    }

    return 1;
}
extern f32 D_800BE9A4;

s32 func_150BA37C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x114) = (f32) (*(f32 *)((u8 *)arg0 + 0x114) + (D_8009FE2C * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x34) += *(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x3C) += *(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x11C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x44) += *(f32 *)((u8 *)arg0 + 0x120) * D_800BE9A4;
    return 1;
}
s32 func_150BA424(void *arg0) {
    f32 temp_fv0;
    s32 var_v0;
    s32 var_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x38) - *(f32 *)((u8 *)arg0 + 0x124);
    if (temp_fv0 < 0.0f) {
        return 0;
    }
    var_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v0 *= 0x10;
    if (var_v0 >= 0x100) {
        var_v0 = 0xFF;
    }
    var_v1 = (s32) temp_fv0 * 4;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < var_v0) {
        *(s8 *)((u8 *)arg0 + 0x5C) = var_v1;
    } else {
        *(s8 *)((u8 *)arg0 + 0x5C) = var_v0;
    }
    if ((s32) (u8) *(s8 *)((u8 *)arg0 + 0x5C) < 0) {
        return 0;
    }
    return 1;
}
