#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F3270.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5F94
 * - func_150C6460
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150C6460(void *);

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 pad1A[2];
    f32 unk1C;
} GameF3270Timer;

void func_150C5DC0(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x58) != 0) {
        GameF3270Timer *timer = (GameF3270Timer *)(*(u8 **)((u8 *)arg0 + 0x58) + 0xB0);

        timer->unk4 = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = func_150C6460(arg0);
    }
}
f32 func_150ADA68();                                /* extern */
extern s32 D_800BE9E4;

s8 func_150C5E0C(u8 *arg0) {
    s8 var_a2;
    GameF3270Timer *timer;

    var_a2 = 1;
    timer = (GameF3270Timer *)(arg0 + 0xB0);
    if (timer->unk4 == 0) {
        var_a2 = 0;
    }
    timer->unk4 = 0;
    timer->unk14 = timer->unk14 - D_800BE9E4;
    if (timer->unk14 < 0) {
        timer->unk14 = timer->unk16 + (func_150ADA20() % (u32) (timer->unk18 + 1));
        timer->unk10 = timer->unk8 + (timer->unkC * func_150ADA68());
    }
    *(s32 *)(arg0 + 0x24) += (s32) ((timer->unk10 - (f32) *(s32 *)(arg0 + 0x24)) * timer->unk1C);
    return var_a2;
}

s32 func_150C5EFC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *) arg0 + 0xB0);
    temp_v0 = (u8 *) temp_v0 + 0x58;
    *(s32 *) temp_v0 = 0;
    *(void **)((u8 *) arg0 + 0xB0) = 0;
    *(s32 *)((u8 *) arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}
typedef struct {
    u8 pad_0[0x5C];
    s8 field_5C;
} GameF3270Data;

typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    u8 pad_1C[0x40];
    GameF3270Data *field_5C;
} GameF3270State;

s32 func_150C5F94(void *, void *);

void func_150C5F40(GameF3270State *arg0) {
    s32 temp_a2;

    temp_a2 = arg0->field_18;
    if (*(GameF3270Data *volatile *)&arg0->field_5C != 0) {
        GameF3270Timer *timer = (GameF3270Timer *)((u8 *)arg0->field_5C + 0x58);

        timer->unk4 = 1;
    } else {
        arg0->field_5C = (GameF3270Data *)func_150C5F94((void *)temp_a2, arg0);
    }
}
extern f32 D_800A0410;
extern f32 D_800A0414;
extern f32 D_800A0418;
s32 func_15045800(f32 *, u16, f32, void *);
void *func_10022EC0(void *, const void *, u32);

typedef struct GameF3270SpawnPacket {
    s32 field_0;
    s32 field_4;
    u8 field_8;
    u8 pad_9[3];
    void *owner;
    u8 field_10;
    u8 pad_11[3];
    volatile f32 field_14;
    volatile f32 field_18;
    volatile f32 field_1C;
    f32 field_20;
    f32 field_24;
    s16 field_28;
    u8 field_2A;
    u8 field_2B;
    u8 field_2C;
    u8 field_2D;
} GameF3270SpawnPacket;

typedef struct GameF3270RayPacket {
    f32 coordinates[3];
    void *source;
    u8 flag;
    u8 pad_11[3];
    f32 result;
} GameF3270RayPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5F94 CURRENT (257) */
s32 func_150C5F94(void *arg0, void *arg1) {
    GameF3270SpawnPacket packet;
    GameF3270RayPacket ray;
    void *spawned;

    ray.source = arg1;
    ray.flag = 1;
    ray.coordinates[0] = *(f32 *)((u8 *)arg0 + 0x14);
    ray.coordinates[1] = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0410;
    ray.coordinates[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    if (func_15045800(ray.coordinates, 0, *(f32 *)((u8 *)arg0 + 0x18) - 100.0f,
                      (u8 *)arg1 + 0x34) != 0) {
        ray.result = *(f32 *)((u8 *)arg1 + 0x34);
    } else {
        ray.result = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0414;
    }
    packet.field_0 = 0;
    packet.field_4 = 0;
    packet.field_8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.owner = arg0;
    packet.field_10 = 0;
    packet.field_14 = 0.0f;
    packet.field_18 = 0.0f;
    packet.field_1C = 0.0f;
    packet.field_20 = 25.0f;
    packet.field_24 = D_800A0418;
    packet.field_28 = 0x12C;
    packet.field_2A = 0xA;
    packet.field_2B = 4;
    packet.field_2C = 1;
    packet.field_2D = 2;
    spawned = func_1513418C((s32)&packet, 0xC, 0xFF, 0);
    if (spawned != 0) {
        func_10022EC0((u8 *)spawned + 0x58, &ray.source, 0xC);
    }
    return (s32)spawned;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5F94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F94.s")
typedef struct GameF3270Burst {
    s32 flags, zero4;
    s16 texture, lifetime;
    s32 zeroC, zero10;
    u8 zero14, zero15, zero16, zero17, zero18, zero19, zero1A;
    u8 alpha, maximum, kind;
    s16 duration, period, zero22;
    f32 zero24, width, height;
    f32 x, y, z;
    f32 zero3C, zero40, zero44;
    f32 vx, vy, vz, rotation;
    s32 mode, unused5C;
    s8 field60, field61, field62, field63;
    u8 pad64[0xC];
} GameF3270Burst;

typedef struct GameF3270BurstMotion {
    f32 size;
    u8 mode0, mode1, count0, count1;
    f32 amount0, amount1, speed, damping;
    u8 mode2, mode3, count2, count3;
    f32 amount2, amount3, sourceScale;
} GameF3270BurstMotion;

void *func_151303BC(s32, u8, s32);
extern f32 D_800A041C, D_800A0420, D_800A0424, D_800A0428;
extern f32 D_800A042C, D_800A0430, D_800A0434, D_800A0438;

void func_150C60D8(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                  f32 arg4, f32 arg5, void *arg6) {
    GameF3270Burst burst;
    void *spawned;
    GameF3270BurstMotion motion;
    burst.kind = 0x2F;
    burst.texture = 0xC01;
    burst.flags = 0x200005;
    burst.zero4 = 0;
    burst.zero1A = 0;
    burst.zero19 = 0;
    burst.zero18 = 0;
    burst.zero17 = 0;
    burst.zero16 = 0;
    burst.zero15 = 0;
    burst.zero14 = 0;
    burst.zero10 = 0;
    burst.zeroC = 0;
    burst.maximum = 0xFF;
    burst.zero22 = 0;
    burst.zero24 = 0.0f;
    burst.mode = 0x3207;
    burst.field60 = 5;
    burst.field61 = 5;
    burst.field62 = 4;
    burst.field63 = -1;
    burst.x = arg0;
    burst.y = arg1;
    burst.zero3C = 0.0f;
    burst.zero40 = 0.0f;
    burst.zero44 = 0.0f;
    burst.duration = 30;
    burst.period = 8;
    burst.z = arg2;
    motion.sourceScale = *(f32 *)((u8 *)arg6 + 0x60);
    motion.speed = 4.0f;
    motion.damping = 0.25f;
    motion.mode0 = 0;
    motion.mode1 = 0;
    motion.mode2 = 0;
    motion.mode3 = 0;
    burst.vx = -arg3 * 0.2f;
    burst.vy = 0.0f;
    burst.vz = -arg5 * 0.2f;
    if (func_150ADA20() & 1) burst.mode |= 0x40;
    if (func_150ADA20() & 1) burst.mode |= 0x80;
    burst.lifetime = func_150ADA20() % 51U + 106;
    burst.alpha = func_150ADA20() % 101U + 100;
    motion.size = burst.width = burst.height = func_150ADA68() * 62.0f + 41.0f;
    motion.count0 = func_150ADA20() % 5U + 4;
    motion.count1 = func_150ADA20() % 5U + 4;
    motion.amount0 = (func_150ADA68() * 0.25f + D_800A0420) * motion.size;
    motion.amount1 = (func_150ADA68() * 0.25f + D_800A0424) * motion.size;
    motion.count2 = func_150ADA20() % 5U + 4;
    motion.count3 = func_150ADA20() % 5U + 4;
    motion.amount2 = (func_150ADA68() * D_800A0428 + D_800A042C) * motion.size;
    motion.amount3 = (func_150ADA68() * D_800A0430 + D_800A0434) * motion.size;
    burst.rotation = (func_150ADA68() * 60.0f + 21.0f) * D_800A0438;
    spawned = func_151303BC((s32)&burst, 2, 0x28);
    if (spawned != NULL) func_10022EC0((u8 *)spawned + 0xA8, &motion, 0x28);
}
s32 func_150C63EC(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}

void func_150C6410(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_151346EC(arg0);
}

void func_150C6438(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_1513470C(arg0);
}
typedef struct GameF3270Vector {
    f32 coordinates[3];
} GameF3270Vector;

typedef struct GameF3270ParticleDescriptor {
    s32 field0;
    s16 field4;
    u8 field6;
    u8 field7;
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
} GameF3270ParticleDescriptor;

typedef struct GameF3270ParticleState {
    void *owner;
    u8 request;
    f32 base;
    f32 range;
    f32 current;
    s16 timer;
    s16 basePeriod;
    s16 periodRange;
    f32 interpolation;
} GameF3270ParticleState;

void *func_1513C73C(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);
void func_15143134(f32 *, f32 *, s32);
u8 func_151D8E20(void);
extern GameF3270Vector D_800887D0;
extern f32 D_800A043C;
extern f32 D_800A0440;
extern u8 D_800AB414[][3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C6460 CURRENT (5102) */
s32 func_150C6460(void *arg0) {
    void *result;
    GameF3270Vector position;
    GameF3270Vector anchor;
    GameF3270Vector query;
    GameF3270ParticleDescriptor descriptor;
    GameF3270ParticleState state;
    f32 scale;
    u8 color;
    u32 firstRandom;
    u32 secondRandom;
    void *actor;
    void *particle;
    u8 *rgb;

    result = 0;
    actor = *(void **)((u8 *)arg0 + 0x18);
    if (*(s32 *)((u8 *)actor + 0x1D4) != 0) {
        anchor = D_800887D0;
        func_15143134(anchor.coordinates, position.coordinates,
                      *(s32 *)((u8 *)actor + 0x1D4));
    } else {
        position.coordinates[0] = *(f32 *)((u8 *)actor + 0x14);
        position.coordinates[1] = *(f32 *)((u8 *)actor + 0x18);
        position.coordinates[2] = *(f32 *)((u8 *)actor + 0x1C);
    }
    query.coordinates[1] = position.coordinates[1] + 200.0f;
    query.coordinates[0] = position.coordinates[0];
    query.coordinates[2] = position.coordinates[2];
    if (func_15045800(query.coordinates, 0, position.coordinates[1] - 200.0f,
                      (u8 *)arg0 + 0x34) != 0) {
        color = func_151D8E20();
        query.coordinates[1] = *(f32 *)((u8 *)arg0 + 0x34);
        scale = func_150ADA68() * 50.0f + 100.0f;
        state.owner = arg0;
        state.request = 1;
        state.base = D_800A043C;
        state.range = 32768.0f;
        state.current = 0.0f;
        state.timer = 0;
        state.basePeriod = 10;
        state.periodRange = 10;
        state.interpolation = D_800A0440;
        descriptor.field0 = 0x20300;
        descriptor.field4 = 0x12C;
        descriptor.field6 = 0x38;
        descriptor.field8 = 0;
        descriptor.fieldC = (s32)(state.base + state.range * 0.5f);
        descriptor.field10 = 0x96;
        descriptor.field11 = 0xFF;
        rgb = D_800AB414[color];
        descriptor.field12 = rgb[0];
        descriptor.field13 = rgb[1];
        descriptor.field14 = rgb[2];
        descriptor.field15 = 0xFF;
        descriptor.field16 = 0;
        descriptor.field17 = 6;
        descriptor.field18 = 0x440001;
        firstRandom = func_150ADA20();
        secondRandom = func_150ADA20();
        particle = func_1513C73C((s32)&descriptor, 8, 2, (s32)((u8 *)arg0 + 0x38),
                                 query.coordinates[0], query.coordinates[1], query.coordinates[2],
                                 scale, scale, (u8)(firstRandom & 0xFF),
                                 (u8)(((func_150ADA20() & 1) * 2) + (secondRandom & 1)),
                                 0x20, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
        result = particle;
        if (particle != 0) {
            func_10022EC0((u8 *)particle + 0xB0, &state, 0x20);
        }
    }
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C6460 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
