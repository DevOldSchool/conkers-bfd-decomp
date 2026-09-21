#include "types.h"

/*
 * Reviewed source unit: src/game/game_117FC0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EAE24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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
    f32 field1C;
    u8 pad20[0x14];
    s32 field34;
    s8 field38;
    s8 field39;
    u8 pad3A[2];
    s32 field3C;
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
s32 func_150ADA20(void);
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
        effect.field34 = 0;
        effect.field38 = 0;
        effect.field39 = 0;
        effect.field3C = 0;
        effect.field1C = D_800A1460;
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
    f32 x;
    f32 y;
    f32 velocityX;
    f32 velocityY;
    f32 z;
    s32 field2C;
    f32 timer;
    f32 alternateHeight;
} Game117FC0Motion;

s32 func_15046C80(f32 *, s32, s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EAE24 CURRENT (955) */
s32 func_150EAE24(Game117FC0Motion *arg0) {
    f32 position[4];
    s32 result;
    void *values;

    arg0->x += arg0->velocityX * D_800BE9A4;
    arg0->y += arg0->velocityY * D_800BE9A4;
    position[0] = arg0->x;
    position[1] = arg0->z;
    position[2] = arg0->y;
    arg0->position->x = (s16) (s32) arg0->x;
    arg0->position->y = (s16) (s32) arg0->y;
    if (func_15046C80(position, 0, arg0->field2C, &arg0->alternateHeight) != 0) {
        values = &arg0->x;
        arg0->position->height = (s16) (s32) *((f32 *) ((u8 *) values + 0x1C));
    } else {
        values = &arg0->x;
        arg0->position->height = (s16) (s32) *((f32 *) ((u8 *) values + 0x10));
    }
    *((f32 *) ((u8 *) values + 0x18)) -= D_800BE9A4;
    result = 1;
    if (*((f32 *) ((u8 *) values + 0x18)) <= 0.0f) {
        result = 0;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EAE24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117FC0/func_150EAE24.s")
