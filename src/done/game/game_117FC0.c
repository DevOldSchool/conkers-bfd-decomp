#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_117FC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 */

typedef struct Game117FC0Vec2 {
    f32 x;
    f32 y;
} Game117FC0Vec2;

typedef struct Game117FC0Effect {
    Game117FC0Vec2 position;
    Game117FC0Vec2 velocity;
    f32 height;
    f32 field14;
    f32 lifetime;
    Game71820Hit hit;
} Game117FC0Effect;

typedef struct Game117FC0Descriptor {
    u8 field0;
    s8 field1;
    s16 field2;
    s8 field4;
} Game117FC0Descriptor;

typedef struct Game117FC0Emitter {
    f32 values[15];
    u8 colour[4];
} Game117FC0Emitter;

typedef struct Game117FC0Actor {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x1B];
    Game117FC0Emitter emitter;
} Game117FC0Actor;

void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A1460;
extern f32 D_800BE9A4;

void func_150EAB10(Game117FC0Actor *arg0) {
    s32 unused;
    Game117FC0Effect effect;
    Game117FC0Descriptor descriptor;
    s32 unusedB0;
    Game117FC0Vec2 end;
    Game117FC0Vec2 start;
    f32 speed;
    f32 length;
    f32 random;
    s32 position[3];
    s32 result;
    Game117FC0Emitter *emitter;

    emitter = &arg0->emitter;
    emitter->values[12] += (emitter->values[10] + func_150ADA68() * emitter->values[11]) * D_800BE9A4;
    if (emitter->values[12] > 1.0f) {
        effect.hit.object = 0;
        effect.hit.flags = 0;
        effect.hit.active = 0;
        effect.hit.field20 = 0;
        effect.hit.height = D_800A1460;
        effect.height = emitter->values[8];
        effect.field14 = emitter->values[9];
        descriptor.field0 = 2;
        descriptor.field1 = 0x13;
        descriptor.field2 = 0x12C;
        descriptor.field4 = 0;
        do {
            speed = emitter->values[13] + emitter->values[14] * func_150ADA68();
            if (speed != 0.0f) {
                random = func_150ADA68();
                start.x = emitter->values[0] + emitter->values[4] * random;
                start.y = emitter->values[1] + emitter->values[5] * random;
                random = func_150ADA68();
                end.x = emitter->values[2] + emitter->values[6] * random;
                end.y = emitter->values[3] + emitter->values[7] * random;
                effect.velocity.x = end.x - start.x;
                effect.velocity.y = end.y - start.y;
                length = sqrtf(effect.velocity.x * effect.velocity.x + effect.velocity.y * effect.velocity.y);
                if (length != 0.0f) {
                    random = 1.0f / length;
                    effect.velocity.x *= random;
                    effect.velocity.y *= random;
                    if (func_150ADA20() & 1) {
                        effect.position = start;
                    } else {
                        effect.position = end;
                        effect.velocity.x = -effect.velocity.x;
                        effect.velocity.y = -effect.velocity.y;
                    }
                    effect.velocity.x *= speed;
                    effect.velocity.y *= speed;
                    effect.lifetime = length / speed;
                    position[0] = (s32)effect.position.x;
                    position[1] = (s32)emitter->values[8];
                    position[2] = (s32)effect.position.y;
                    result = func_151602C0((u8 *)&descriptor, position,
                        emitter->colour[3], emitter->colour[0], emitter->colour[1],
                        emitter->colour[2], 0xFF, 0, 0x40, arg0->fieldC, arg0->field1);
                    if (result != 0) {
                        func_10022EC0((u8 *)result + 0x18, &effect, 0x40);
                    }
                }
            }
            emitter->values[12] -= 1.0f;
        } while (emitter->values[12] > 1.0f);
    }
}
typedef struct {
    u8 pad0[0xE];
    s16 x;
    s16 height;
    s16 y;
} Game117FC0Position;

typedef struct {
    u8 pad0[0x14];
    Game117FC0Position *position;
    Game117FC0Effect effect;
} Game117FC0Motion;

s32 func_15046C80(Vec3f *, u16, f32, Game71820Hit *);

s32 func_150EAE24(Game117FC0Motion *arg0) {
    Game117FC0Effect *effect = &arg0->effect;
    Vec3f position;

    arg0->effect.position.x += arg0->effect.velocity.x * D_800BE9A4;
    arg0->effect.position.y += arg0->effect.velocity.y * D_800BE9A4;
    position.x = arg0->effect.position.x;
    position.y = arg0->effect.height;
    position.z = arg0->effect.position.y;
    arg0->position->x = (s16)(s32)arg0->effect.position.x;
    arg0->position->y = (s16)(s32)arg0->effect.position.y;
    if (func_15046C80(&position, 0, arg0->effect.field14, &arg0->effect.hit) != 0) {
        arg0->position->height = (s16)(s32)effect->hit.height;
    } else {
        arg0->position->height = (s16)(s32)effect->height;
    }
    effect->lifetime -= D_800BE9A4;
    if (effect->lifetime <= 0.0f) {
        return 0;
    }
    return 1;
}
