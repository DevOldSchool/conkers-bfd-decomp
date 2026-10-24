#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_11D030.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EFB80
 * - func_150EFEC8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D030Emission {
    Vec3f position;
    s16 life, fieldE;
    s32 field10;
    u8 field14, mode;
    u8 pad16[6];
} Game11D030Emission;
typedef struct Game11D030Motion {
    f32 speed;
    Vec3f direction;
    f32 size;
    u8 kind, mode, flags, red, green, blue, alpha, field1B;
    u8 field1C, field1D, field1E, field1F, field20, field21;
    u8 pad22[2];
    s32 field24, field28;
    s16 field2C, field2E, field30;
    u8 field32, pad33;
    f32 field34;
    s8 field38, field39;
    u8 pad3A[2];
} Game11D030Motion;
typedef struct Game11D030EmitterState {
    u8 *actor;
    f32 accumulator;
} Game11D030EmitterState;

f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void *func_1515C2F0(void *, void *, s32, s32, u8, s32);
extern f32 D_800A1824, D_800A1828, D_800A182C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EFB80 CURRENT (1288) */
void func_150EFB80(u8 *arg0) {
    Game11D030Emission spawn;
    Game11D030Motion motion;
    u32 randomA;
    u32 randomB;
    Game11D030EmitterState *state;
    u8 *actor;

    state = (Game11D030EmitterState *)(arg0 + 0x28);
    state->accumulator += (364.0f + func_150ADA68() * 300.0f) * D_800A1824;
    if (state->accumulator > 1.0f) {
        actor = state->actor;
        if (actor[0x128] & 1) {
            spawn.position = *(Vec3f *)(actor + 0x40);
            spawn.fieldE = 5;
            spawn.field10 = 10;
            motion.kind = 4;
            motion.mode = 2;
            motion.flags = 3;
            motion.red = 0x9D;
            motion.green = 0x72;
            motion.blue = 0x2E;
            motion.field1B = 0;
            motion.field1C = 0;
            motion.field1D = 0;
            motion.field1E = 0;
            motion.field1F = 0xFF;
            motion.field20 = 3;
            motion.field21 = 0x24;
            motion.field24 = 0x200005;
            motion.field28 = 0x60600;
            motion.field2C = 12;
            motion.field2E = 21;
            motion.field30 = 1;
            motion.field32 = 0;
            motion.field34 = 1.0f;
            motion.field38 = -1;
            motion.field39 = 0;
            do {
                spawn.mode = func_150ADA20() % 3U + 3;
                spawn.life = (func_150ADA20() & 0xF) + 0x28;
                motion.speed = func_150ADA68() * 10.0f + 22.0f;
                randomA = func_150ADA20();
                randomB = func_150ADA20();
                func_15143794((s16)(randomA & 0xFF), (s16)(randomB % 31U - 0x37),
                              func_150ADA68() * 15.0f + 25.0f, &motion.direction);
                motion.size = (func_150ADA68() * 740.0f + D_800A1828) * D_800A182C;
                motion.alpha = func_150ADA20() % 101U + 0x9B;
                func_1515C2F0(&spawn, NULL, (s32)&motion.speed, 0, arg0[0xC], arg0[1]);
                state->accumulator -= 1.0f;
            } while (state->accumulator > 1.0f);
            return;
        }
        do {
            state->accumulator -= 1.0f;
        } while (state->accumulator > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EFB80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFB80.s")

typedef struct Game11D030SpawnDescriptor {
    u8 kind, mode;
    u16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 callback0, callback1;
    u8 colors[4];
    f32 field14, field18;
    f32 position[3], direction[3], scales[3];
    u32 options;
    u8 channels[4];
    s32 parameter;
    u8 pad4C[0xC];
} Game11D030SpawnDescriptor;

typedef struct Game11D030SpawnParameters {
    f32 values[9];
    s32 handles[8];
    s32 count;
    f32 multiplier;
    s16 angles[4];
    u8 colors[4];
    u8 state;
    s8 mode;
    u8 pad5A[0x12];
} Game11D030SpawnParameters;

typedef struct Game11D030SpawnOwner {
    u8 *actor;
    u8 kind, mode;
    u8 pad6[2];
    s32 data;
} Game11D030SpawnOwner;

void *func_10022EC0(void *, const void *, u32);
s32 func_151407D0();
extern s32 (*D_8008FD00)(void *, u8);
extern f32 D_800A1830, D_800A1834;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EFEC8 CURRENT (3643) */
s32 func_150EFEC8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4,
                   s32 arg5, u8 arg6, s32 arg7) {
    s32 saved;
    Game11D030SpawnParameters parameters;
    Game11D030SpawnDescriptor descriptor;
    Game11D030SpawnOwner owner;
    register s32 value;

    owner.actor = arg0;
    owner.mode = arg1;
    owner.kind = arg0[0x3B];
    owner.data = arg5;
    descriptor.kind = D_8008FD00(arg0, arg1);
    descriptor.colors[3] = 0xFF;
    descriptor.options = 0xCD2002;
    descriptor.mode = 3;
    descriptor.flags = 0x2203;
    descriptor.lifetime = 0x12C;
    descriptor.colors[0] = arg2;
    parameters.handles[6] = -1;
    parameters.handles[3] = -1;
    descriptor.channels[0] = 0xFF;
    descriptor.channels[3] = 6;
    parameters.handles[0] = -1;
    parameters.handles[4] = -1;
    parameters.handles[1] = -1;
    descriptor.colors[1] = arg3;
    descriptor.colors[2] = arg4;
    descriptor.callback0 = 0;
    descriptor.callback1 = 0;
    descriptor.channels[1] = 0xFF;
    descriptor.channels[2] = 0;
    descriptor.parameter = 0;
    parameters.handles[5] = -1;
    parameters.handles[2] = -1;
    parameters.handles[7] = -1;
    parameters.count = 0;
    parameters.angles[0] = 0;
    parameters.angles[1] = 0;
    parameters.angles[2] = 0;
    parameters.angles[3] = 0;
    parameters.colors[0] = 0xFF;
    parameters.colors[1] = 0xFF;
    parameters.colors[2] = 0xFF;
    parameters.colors[3] = 0xFF;
    parameters.state = 0xA;
    parameters.mode = -1;
    descriptor.scales[0] = 1.0f;
    descriptor.scales[1] = 1.0f;
    descriptor.scales[2] = 1.0f;
    parameters.values[6] = 1.0f;
    parameters.multiplier = 1.0f;
    descriptor.field18 = 100.0f;
    descriptor.field14 = 100.0f;
    parameters.values[1] = 160.0f;
    parameters.values[0] = 160.0f;
    parameters.values[3] = 80.0f;
    parameters.values[2] = 80.0f;
    descriptor.position[0] = 0.0f;
    descriptor.position[1] = 0.0f;
    descriptor.position[2] = 0.0f;
    descriptor.direction[0] = 0.0f;
    descriptor.direction[1] = 0.0f;
    descriptor.direction[2] = 0.0f;
    parameters.values[4] = 0.5f;
    parameters.values[5] = 0.5f;
    parameters.values[7] = D_800A1830;
    parameters.values[8] = D_800A1834;
    value = func_151407D0(&parameters, 0x6C, &descriptor, 0x1E,
                         0, 0, 0, -1, arg6, arg7);
    if (value != 0) {
        saved = value;
        func_10022EC0((void *)(value + 0x170), &owner, 0xCU);
        value = saved;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EFEC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFEC8.s")
s32 func_150F00EC(u8 *arg0) {
    typedef struct { f32 words[3]; } Copy3;
    u8 *object;
    u8 *motion;

    object = *(u8 **)(arg0 + 0x178);
    motion = object + 0x110;
    if (object[0x128] & 1) {
        *(Copy3 *)(arg0 + 0x34) = *(Copy3 *)(object + 0x34);
        *(f32 *)(arg0 + 0x40) = (*(f32 *)(motion + 0x30) * 500.0f) + *(f32 *)(object + 0x34);
        *(f32 *)(arg0 + 0x44) = (*(f32 *)(motion + 0x34) * 500.0f) + *(f32 *)(object + 0x38);
        *(f32 *)(arg0 + 0x48) = (*(f32 *)(motion + 0x38) * 500.0f) + *(f32 *)(object + 0x3C);
        *(s32 *)(arg0 + 0x58) |= 6;
    } else {
        *(s32 *)(arg0 + 0x58) &= ~4;
        *(s32 *)(arg0 + 0x58) &= ~2;
    }
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game11D030Locals {
    s32 payload;
    s32 position[3];
    u8 descriptor_0;
    s8 descriptor_1;
    s16 descriptor_2;
    s8 descriptor_4;
    u8 pad15[3];
    s32 saved;
} Game11D030Locals;

s32 func_150F0198(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    s32 value;
    struct {
        s32 payload;
        s32 position[3];
        u8 descriptor_0;
        s8 descriptor_1;
        s16 descriptor_2;
        s8 descriptor_4;
        u8 pad15[3];
    } locals;

    locals.payload = arg4;
    locals.descriptor_0 = 2;
    locals.descriptor_1 = -1;
    locals.descriptor_2 = 0x12C;
    locals.descriptor_4 = 0x21;
    locals.position[0] = 0;
    locals.position[1] = 0;
    locals.position[2] = 0;
    value = func_151602C0(&locals.descriptor_0, &locals.position[0], arg0, arg1, arg2,
                          arg3, 0xFF, 0, 4, arg5, arg6);
    if (value != 0) {
        func_10022EC0((u8 *) value + 0x18, &locals.payload, 4);
    }
    return value;
}
