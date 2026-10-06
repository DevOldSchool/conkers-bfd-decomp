#include "types.h"

/*
 * Reviewed source unit: src/game/game_E35C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6110
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE35C0Owner {
    s16 x, y, z, radius, height;
    u8 pad0A[0xA];
    u8 state;
} GameE35C0Owner;

typedef struct GameE35C0Payload {
    GameE35C0Owner *owner;
    f32 accumulator;
    u8 state;
} GameE35C0Payload;

typedef struct GameE35C0Object {
    u8 pad00;
    u8 flags01;
    u8 pad02[0xA];
    u8 flags0C;
    u8 pad0D[0x1B];
    GameE35C0Payload effect;
} GameE35C0Object;

typedef struct GameE35C0Position {
    f32 x, y, z;
} GameE35C0Position;

typedef struct GameE35C0Descriptor {
    f32 field00, field04, field08, field0C, field10;
    s16 field14, field16, field18, field1A, field1C;
    u8 pad1E[2];
    s32 field20, field24;
    u8 field28, field29, field2A, field2B, field2C;
    u8 pad2D[3];
} GameE35C0Descriptor;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514373C(f32, f32, f32 *, f32 *);
void func_151494E0(s32, u8);
s32 func_15106F98(void *, void *, s32, void *, f32, u8, u8, s32);
extern f32 D_8009FCBC, D_8009FCC0, D_8009FCC4, D_8009FCC8, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6110 CURRENT (1456) */
void func_150B6110(GameE35C0Object *arg0) {
    GameE35C0Descriptor descriptor;
    GameE35C0Position first;
    GameE35C0Position second;
    GameE35C0Owner *owner;
    GameE35C0Payload *effect;
    u8 angle;
    u32 random;
    u8 oldState;
    u8 newState;
    f32 spread;

    owner = arg0->effect.owner;
    oldState = arg0->effect.state;
    newState = owner->state;
    arg0->effect.state = newState;
    if (owner->state == 1) {
        if (oldState != newState) {
            func_151494E0(0, 0x4A);
        }
    } else {
        effect = &arg0->effect;
        effect->accumulator += (D_8009FCBC + func_150ADA68() * D_8009FCC0) * D_800BE9A4;
        if (effect->accumulator > 1.0f) {
            descriptor.field14 = 40;
            descriptor.field00 = 35.0f;
            descriptor.field04 = 35.0f;
            descriptor.field16 = 0;
            descriptor.field18 = 4;
            descriptor.field1A = 3;
            descriptor.field1C = 7;
            descriptor.field20 = 4;
            descriptor.field24 = 3;
            descriptor.field28 = 0x7E;
            descriptor.field29 = 0xF9;
            descriptor.field2A = 0xFF;
            descriptor.field2B = 0x7F;
            descriptor.field2C = 0x80;
            descriptor.field08 = 76.0f;
            descriptor.field0C = 103.0f;
            descriptor.field10 = D_8009FCC4;
            spread = D_8009FCC8;
            first.y = (f32)(owner->y + owner->height);
            second.y = (f32)(owner->y + owner->height);
            do {
                random = func_150ADA20();
                angle = random;
                func_1514373C((f32)(random & 0xFF), (f32)owner->radius, &first.x, &first.z);
                first.x += (f32)owner->x;
                first.z += (f32)owner->z;
                angle += func_150ADA20() % 129U + 0x40;
                func_1514373C((f32)(u32)angle, (f32)owner->radius, &second.x, &second.z);
                second.x += (f32)owner->x;
                second.z += (f32)owner->z;
                func_15106F98(&first, &second, 4, &descriptor, spread, 1, arg0->flags0C, arg0->flags01);
                effect->accumulator -= 1.0f;
            } while (effect->accumulator > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6110 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E35C0/func_150B6110.s")
