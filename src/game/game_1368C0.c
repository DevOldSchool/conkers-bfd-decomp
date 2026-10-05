#include "types.h"

/*
 * Reviewed source unit: src/game/game_1368C0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15109410
 * - func_151094FC
 * - func_15109848
 * - func_15109C20
 * - func_15109ED4
 * - func_15109FB8
 * - func_1510A40C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1368C0Spawn9410 {
    void *source;
    u8 type;
    u8 pad5[3];
    f32 zero;
    f32 value;
    s8 field_10;
    s8 field_11;
    u8 pad12[2];
} Game1368C0Spawn9410;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109410 CURRENT (85) */
s32 func_15109410(void *arg0, s16 arg1, s8 arg2, s8 arg3,
                   f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    Game1368C0Spawn9410 spawn;
    s16 type;
    s32 enabled;
    s32 result;

    if (arg0 == 0) {
        return 0;
    }
    enabled = 0;
    if (arg1 < 0) {
        type = 0x12C;
    } else {
        enabled = 1;
        type = arg1;
    }
    spawn.zero = 0.0f;
    spawn.value = arg4;
    spawn.field_10 = arg2;
    spawn.field_11 = arg3;
    spawn.source = arg0;
    spawn.type = *(u8 *)((u8 *)arg0 + 0x3B);
    result = func_15149130(type, -1, 0x1A, -1, enabled, 0x1A,
                          arg5 + 0x14, arg6, arg7);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &spawn, 0x14U);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109410 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109410.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_151094FC.s")
typedef struct Game1368C0EmitterVector {
    f32 x;
    f32 y;
    f32 z;
} Game1368C0EmitterVector;

typedef struct Game1368C0EmitterParticle {
    s32 field0;
    s32 field4;
    Game1368C0EmitterVector position8;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s32 field34;
    s32 field38;
    s16 field3C;
    s16 field3E;
    s16 field40;
    u8 fields42[23];
    s32 field5C;
    s32 field60;
    s16 field64;
    s16 field66;
    s16 field68;
    u8 field6A;
    f32 field6C;
    s8 fields70[4];
} Game1368C0EmitterParticle;

typedef struct Game1368C0EmitterSpawn {
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
    Game1368C0EmitterVector position30;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
    s32 field58;
    s32 field5C;
    s8 fields60[6];
    /* The constructor copies a full 0x70-byte record; these fields are unused here. */
    u8 fields66[0xA];
} Game1368C0EmitterSpawn;

typedef struct Game1368C0EmitterOwner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
} Game1368C0EmitterOwner;

void *func_15130374(s32, u8, s32, u8, s32);
void func_15152B38(void *, s32, s32);
s32 func_150ADA20();
f32 func_150ADA68();
extern f32 D_800A2634;
extern f32 D_800A2638;
extern f32 D_800A263C;
extern f32 D_800A2640;
extern f32 D_800A2644;
extern f32 D_800A2648;
extern f32 D_800A264C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109848 CURRENT (550) */
void func_15109848(Game1368C0EmitterOwner *arg0, Game1368C0EmitterVector *arg1,
                   s32 arg2, s32 arg3, s32 arg4, Game1368C0EmitterVector *arg5) {
    Game1368C0EmitterSpawn spawn;
    f32 speed;
    Game1368C0EmitterParticle descriptor;
    s32 flag80;
    s32 flag40;

    speed = (func_150ADA68() * D_800A2634 + D_800A2638) * D_800A263C;
    spawn.field1D = 0x2B;
    spawn.field8 = 0x4401;
    spawn.field0 = 0x200005;
    spawn.field4 = 0x20000;
    spawn.fieldA = (func_150ADA20() & 0xF) + 0xA;
    spawn.fieldC = 0;
    spawn.field10 = 0;
    spawn.colors14[0] = 0xFF;
    spawn.colors14[1] = 0xFF;
    spawn.colors14[2] = 0xFF;
    spawn.colors14[3] = 0xFF;
    spawn.colors14[4] = 0xFF;
    spawn.colors14[5] = 0xFF;
    spawn.colors14[6] = 0xFF;
    spawn.colors14[7] = 0xFF;
    spawn.colors14[8] = 0xFF;
    spawn.field28 = spawn.field2C = func_150ADA68() * 25.0f + 35.0f;
    spawn.position30 = *arg1;
    spawn.field3C = 0.0f;
    spawn.field40 = 0.0f;
    spawn.field44 = 0.0f;
    spawn.field48 = arg5->x * speed;
    spawn.field4C = arg5->y * speed;
    spawn.field50 = arg5->z * speed;
    spawn.field1E = 5;
    spawn.field20 = 0x33;
    spawn.field22 = 1;
    spawn.field54 = 0.0f;
    spawn.field24 = 1.0f;
    if (func_150ADA20() & 1) {
        flag40 = 0x40;
    } else {
        flag40 = 0;
    }
    if (func_150ADA20() & 1) {
        flag80 = 0x80;
    } else {
        flag80 = 0;
    }
    spawn.field58 = flag80 | 5 | flag40 | 0xC200;
    spawn.fields60[0] = 6;
    spawn.fields60[1] = 6;
    spawn.fields60[2] = -1;
    spawn.fields60[3] = -1;
    spawn.fields60[4] = -1;
    spawn.fields60[5] = 4;
    func_15130374((s32)&spawn, 1, 0, arg0->fieldC, arg0->field1);
    descriptor.field0 = 1;
    descriptor.field4 = 4;
    descriptor.position8 = *arg1;
    descriptor.field14 = D_800A2640;
    descriptor.field18 = D_800A2644;
    descriptor.field1C = D_800A2648;
    descriptor.field20 = D_800A264C;
    descriptor.field24 = 2.0f;
    descriptor.field28 = 6.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x40;
    descriptor.field32 = 0x2E;
    descriptor.field34 = 4;
    descriptor.field38 = 3;
    descriptor.field3C = 0x14;
    descriptor.field3E = 0xF;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 0xC;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xFF;
    descriptor.fields42[5] = 0xFF;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0;
    descriptor.fields42[9] = 0;
    descriptor.fields42[10] = 0;
    descriptor.fields42[11] = 0xFF;
    descriptor.fields42[12] = 0xFF;
    descriptor.fields42[13] = 0xFF;
    descriptor.fields42[14] = 0xFF;
    descriptor.fields42[15] = 0;
    descriptor.fields42[16] = 0;
    descriptor.fields42[17] = 0;
    descriptor.fields42[18] = 0;
    descriptor.fields42[19] = 0xFF;
    descriptor.fields42[20] = 0;
    descriptor.fields42[21] = 3;
    descriptor.fields42[22] = 0x24;
    descriptor.field5C = 0x200005;
    descriptor.field60 = 0x60600;
    descriptor.field64 = 0xA;
    descriptor.field66 = 0x19;
    descriptor.field68 = 1;
    descriptor.field6A = 0;
    descriptor.field6C = 1.0f;
    descriptor.fields70[0] = -1;
    descriptor.fields70[1] = 0;
    descriptor.fields70[2] = -1;
    descriptor.fields70[3] = -1;
    func_15152B38(&descriptor, arg0->fieldC, arg0->field1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109848 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109848.s")
typedef struct { u8 pad0[0x3B]; u8 kind; } Game1368C0BurstParent;
typedef struct {
    u8 pad0, color, pad2[0xA], flags, padD[6], kind;
    u8 pad14[0x14];
    Game1368C0BurstParent *parent;
} Game1368C0BurstOwner;
typedef struct {
    f32 first, second, width, height;
    Game1368C0EmitterVector angles, scale, position, velocity, acceleration;
    f32 scalar4C;
    s32 flags;
    s16 life, kind;
    u8 byte58, pad59[3];
    s32 word5C;
    u8 colors[9], pad69, variant, pad6B;
    Game1368C0BurstParent *parent;
    u8 parentKind, pad71;
    s16 value72, value74;
    u8 pad76[6];
} Game1368C0Burst;
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A2650, D_800A2654, D_800A2658, D_800A265C, D_800A2660, D_800A2664;
extern f32 D_800A2668, D_800A266C, D_800A2670, D_800A2674, D_800A2678, D_800A267C, D_800A2680;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109C20 CURRENT (1265) */
void func_15109C20(Game1368C0BurstOwner *arg0, Game1368C0EmitterVector *arg1,
                   s32 arg2, s32 arg3, s32 arg4, Game1368C0EmitterVector *arg5) {
    Game1368C0BurstParent *parent;
    f32 speed;
    Game1368C0Burst burst;

    parent = arg0->parent;
    speed = (func_150ADA68() * D_800A2650 + D_800A2654) * D_800A2658;
    burst.first = 1.0f;
    burst.second = 1.0f;
    burst.width = burst.height = (func_150ADA68() * D_800A265C + D_800A2660) * D_800A2664;
    burst.angles.x = func_150ADA68() * 360.0f;
    burst.angles.y = func_150ADA68() * 360.0f;
    burst.angles.z = func_150ADA68() * 360.0f;
    burst.scale.x = 1.0f;
    burst.scale.y = 1.0f;
    burst.scale.z = 1.0f;
    burst.position = *arg1;
    burst.velocity.x = arg5->x * speed;
    burst.velocity.y = arg5->y * speed;
    burst.velocity.z = arg5->z * speed;
    burst.acceleration.x = (func_150ADA68() * D_800A2668 + D_800A266C) * D_800A2670;
    burst.acceleration.y = 0.0f;
    burst.acceleration.z = (func_150ADA68() * D_800A2674 + D_800A2678) * D_800A267C;
    burst.scalar4C = (func_150ADA68() * 124.0f + -231.0f) * D_800A2680;
    burst.flags = 0x29E8;
    burst.life = ((u32)func_150ADA20() % 15U) + 20;
    if (func_150ADA20() & 1) burst.kind = 0x23;
    else burst.kind = 0x24;
    burst.byte58 = 0;
    burst.word5C = 0;
    burst.colors[0] = 0xFF;
    burst.colors[1] = 8;
    burst.colors[2] = 0;
    burst.colors[3] = 0;
    burst.colors[4] = 0;
    burst.colors[5] = 0;
    burst.colors[6] = 0;
    burst.colors[7] = 0;
    burst.colors[8] = 2;
    if (arg0->kind == 0x1A) burst.variant = 1;
    else burst.variant = 2;
    burst.parent = parent;
    burst.value72 = 10;
    burst.value74 = 25;
    burst.parentKind = parent->kind;
    func_15132A4C(&burst, 3, 0xFF, 0, arg0->flags, arg0->color);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109C20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109C20.s")
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1368C0Spawn {
    void *source;
    f32 zero;
    f32 value;
    s8 field_C;
    s8 field_D;
    u8 padE[2];
} Game1368C0Spawn;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109ED4 CURRENT (15) */
s32 func_15109ED4(s32 arg0, s16 arg1, s8 arg2, s8 arg3,
                   f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    s32 value;
    Game1368C0Spawn spawn;
    s16 var_a0;

    if (arg0 == 0) {
        return 0;
    }
    value = 0;
    if (arg1 < 0) {
        var_a0 = 0x12C;
    } else {
        value = 1;
        var_a0 = arg1;
    }
    spawn.zero = 0.0f;
    spawn.value = arg4;
    spawn.field_C = arg2;
    spawn.field_D = arg3;
    spawn.source = (void *)arg0;
    value = func_15149130(var_a0, -1, 0x1B, -1, value,
                             0x1B, arg5 + 0x10, arg6, arg7);
    if (value != 0) {
        func_10022EC0((u8 *)value + 0x28, &spawn, 0x10);
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109ED4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_15109FB8.s")
extern f32 D_800A2684;
extern f32 D_800A2688;

typedef struct Game1368C0Locals {
    void *source;
    u8 type;
    u8 pad5[3];
    f32 zero;
    f32 value_1;
    f32 value_2;
    s32 saved;
} Game1368C0Locals;

s32 func_1510A344(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    s32 value;
    struct {
        void *source;
        u8 type;
        u8 pad5[3];
        f32 zero;
        f32 value_1;
        f32 value_2;
    } locals;

    if (arg0 == 0) {
        return 0;
    }
    locals.source = arg0;
    locals.type = *(u8 *) ((u8 *) arg0 + 0x3B);
    locals.zero = 0.0f;
    locals.value_1 = D_800A2684;
    locals.value_2 = D_800A2688;
    value = func_15149130(arg1, -1, 0x1C, -1, 1, 0x1C, 0x14, arg2, arg3);
    if (value != 0) {
        func_10022EC0((u8 *) value + 0x28, &locals.source, 0x14);
    }
    return value;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1368C0/func_1510A40C.s")
