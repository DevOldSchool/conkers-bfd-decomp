#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_116D40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 */

typedef struct Game116D40Spawn {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 colors14[9];
    u8 field1D;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Vec3f position30;
    Vec3f field3C;
    Vec3f field48;
    f32 field54;
    s32 field58;
    s32 field5C;
    s8 fields60[6];
    u8 fields66[0xA];
} Game116D40Spawn;

typedef struct Game116D40Burst {
    f32 first, second, width, height;
    Vec3f angles, scale, position, velocity, acceleration;
    f32 scalar4C;
    s32 flags;
    s16 life, kind;
    u8 byte58, pad59[3];
    s32 word5C;
    u8 colors[9], pad69, variant, pad6B;
    void *parent;
    u8 parentKind, pad71;
    s16 value72, value74;
    u8 pad76[10];
} Game116D40Burst;

typedef struct Game116D40Flash {
    u8 field0;
    s8 field1;
    s16 field2;
    s8 field4;
    u8 pad5[3];
} Game116D40Flash;

f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void *func_15130374(s32, u8, s32, u8, s32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
s32 func_151602C0(void *, Vec3i *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150E9890(void *arg0, void *arg1, f32 arg2, u8 arg3, s32 arg4) {
    Game116D40Spawn spawn;
    Game116D40Burst burst;
    Game116D40Flash flash;
    Vec3i pos;
    s32 i;

    spawn.field1E = spawn.field22 = spawn.fieldA = (func_150ADA20() % 31U) + 20;
    spawn.field20 = 0xFF / spawn.field22;
    spawn.colors14[7] = 0xFF;
    spawn.field28 = spawn.field2C = (func_150ADA68() * 608.0f + 808.0f) * arg2;
    spawn.field24 = (func_150ADA68() * 18.0f + 1016.0f) * 0.001f;
    spawn.field1D = 0x16;
    spawn.field8 = 0x2001;
    spawn.field0 = 0x200005;
    spawn.field4 = 0;
    spawn.fieldC = 0;
    spawn.field10 = 0;
    spawn.colors14[3] = 0xFF;
    spawn.colors14[8] = 0xFF;
    spawn.field58 = 0x800E05;
    spawn.fields60[0] = 3;
    spawn.fields60[1] = 3;
    spawn.fields60[2] = -1;
    spawn.fields60[3] = -1;
    spawn.field3C.x = 0.0f;
    spawn.field3C.y = 0.0f;
    spawn.field3C.z = 0.0f;
    if (func_150ADA20() & 1) {
        spawn.field58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        spawn.field58 |= 0x80;
    }
    spawn.colors14[4] = 0xFF;
    spawn.colors14[5] = 0x8E;
    spawn.colors14[6] = 0x13;
    spawn.colors14[0] = 0x2F;
    spawn.colors14[1] = 0;
    spawn.colors14[2] = 0;
    spawn.position30 = *(Vec3f *)arg0;
    spawn.field48 = *(Vec3f *)arg1;
    spawn.field54 = 0.0f;
    func_15130374((s32)&spawn, 0, 0, arg3, arg4);
    i = (func_150ADA20() & 7) + 5;
    burst.flags = 0x21E8;
    burst.kind = 0x1B;
    burst.first = 0.0f;
    burst.angles.x = 0.0f;
    burst.angles.y = 0.0f;
    burst.angles.z = 0.0f;
    burst.acceleration.y = 0.0f;
    burst.byte58 = 0;
    burst.word5C = 0;
    burst.colors[1] = 1;
    burst.colors[2] = 0;
    burst.colors[3] = 0;
    burst.colors[4] = 0;
    burst.colors[5] = 0;
    burst.colors[6] = 0;
    burst.colors[7] = 0;
    burst.colors[8] = 0;
    burst.variant = 2;
    burst.parent = NULL;
    burst.parentKind = 0;
    burst.value72 = 0x14;
    burst.value74 = 0xC;
    burst.scale.x = 1.0f;
    burst.scale.y = 1.0f;
    burst.scale.z = 1.0f;
    burst.second = 0.2f;
    for (; i > 0; i--) {
        burst.position = *(Vec3f *)arg0;
        burst.life = (func_150ADA20() % 41U) + 29;
        burst.colors[0] = (func_150ADA20() % 76U) + 180;
        func_15143794((s16)(func_150ADA20() & 0xFF), (s16)-(func_150ADA20() % 65U),
                      (func_150ADA68() * 2031.0f + 1641.0f) * 0.01f, &burst.velocity);
        burst.width = burst.height = (func_150ADA68() * 3047.0f + 1016.0f) * 0.0001f * arg2;
        burst.scalar4C = (func_150ADA68() * 99.0f + -206.0f) * 0.01f;
        burst.acceleration.x = func_150ADA68() * 101.0f + -49.0f;
        burst.acceleration.z = func_150ADA68() * 101.0f + -49.0f;
        func_15132A4C(&burst, 3, 0xFF, 0, arg3, arg4);
    }
    flash.field0 = 3;
    flash.field1 = -1;
    flash.field2 = (func_150ADA20() % 13U) + 8;
    flash.field4 = 0;
    pos.x = ((Vec3f *)arg0)->x;
    pos.y = ((Vec3f *)arg0)->y;
    pos.z = ((Vec3f *)arg0)->z;
    func_151602C0(&flash, &pos, (func_150ADA20() % 31U) + 70, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg3, arg4);
}
typedef struct Game116D40EmitterState {
    s32 target;
    f32 base;
    f32 range;
    f32 offset;
    f32 spread;
    f32 accumulator;
} Game116D40EmitterState;

f32 func_150ADA68(void);
void func_1514470C(s32, void *);
void func_15143794(s16, s16, f32, void *);
void func_150E9890(void *, void *, f32, u8, s32);
extern f32 D_800BE9A4;

void func_150E9E34(u8 *arg0) {
    Game116D40EmitterState *state;
    Vec3f sp80;
    Vec3f sp74;
    f32 value;
    u32 first;
    u32 second;

    state = (Game116D40EmitterState *)(arg0 + 0x28);
    state->accumulator += (state->base + func_150ADA68() * state->range) * D_800BE9A4;
    if (state->accumulator > 1.0f) {
        do {
            value = func_150ADA68() * state->spread + state->offset;
            func_1514470C(state->target, &sp80);
            first = func_150ADA20();
            second = func_150ADA20();
            func_15143794((s16)(first & 0xFF),
                           (s16)(0x40 - (second % 129U)),
                           func_150ADA68() * 600.0f * 0.01f,
                           &sp74);
            func_150E9890(&sp80, &sp74, value, arg0[0xC], arg0[1]);
            state->accumulator -= 1.0f;
        } while (state->accumulator > 1.0f);
    }
}
