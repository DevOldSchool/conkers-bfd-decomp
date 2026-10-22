#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/effects_sight.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_beta_sight.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C71A0
 * - func_151C756C
 * - func_151C7E98
 * - func_151C82D0
 * - func_151C86AC
 * - func_151C87E0
 * - func_151C899C
 * - func_151C8FCC
 * - func_151C9198
 * - func_151C9740
 * - func_151C9BA0
 * - func_151C9DE8
 * - func_151C9ED4
 * - func_151C9F38
 * - func_151CA6A0
 * - func_151CAB78
 * - func_151CAD28
 * - func_151CB110
 * - func_151CB5FC
 * - func_151CBC60
 * - func_151CC1D4
 * - func_151CC524
 * - func_151CC840
 * - func_151CCD1C
 * - func_151CCF08
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Sight71Parameters {
    s16 position[3];
    u8 pad06[2];
    s16 length;
    u8 pad0A[2];
    f32 rotationX, rotationY;
    u8 disabled;
    u8 pad15[3];
    u32 flags, colors, widths;
} Sight71Parameters;

void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *,
                  f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
s32 func_151C756C(f32 *, s16 *, f32 *, s16 *, void *, void *,
                  s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                  s32, s32, s32, f32, f32, s32, s32, s32);
extern f32 D_800AAC38, D_800AAC3C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C71A0 CURRENT (15665) */
s32 func_151C71A0(Sight71Parameters *arg0) {
    f32 origin[3];
    f32 end[3];
    f32 direction[3];
    f32 middle[3];
    f32 matrix[16];
    s32 hit;
    s16 triangle1[9], triangle2[9];
    f32 point1[3], point2[3];
    f32 distance1, distance2;
    s32 object1, object2;
    u32 flags, colors, widths;
    s32 secondHit;

    if (arg0->disabled == 1) {
        return 1;
    }
    origin[0] = arg0->position[0];
    origin[1] = arg0->position[1];
    origin[2] = arg0->position[2];
    func_150A8050(matrix, arg0->rotationX, arg0->rotationY, 0.0f);
    func_150A7960(matrix, 0.0f, (f32)arg0->length, 0.0f,
                  &end[0], &end[1], &end[2]);
    end[0] += origin[0];
    end[1] += origin[1];
    end[2] += origin[2];
    direction[0] = end[0] - origin[0];
    direction[1] = end[1] - origin[1];
    direction[2] = end[2] - origin[2];
    middle[0] = direction[0] * 0.5f + origin[0];
    middle[1] = direction[1] * 0.5f + origin[1];
    middle[2] = direction[2] * 0.5f + origin[2];
    hit = func_150AC9C0(middle[0], middle[1], middle[2],
                         -direction[0], -direction[1], -direction[2], 0,
                         triangle1, &point1[0], &point1[1], &point1[2],
                         &distance1, &object1, 0, 0.0f);
    secondHit = func_150AC9C0(middle[0], middle[1], middle[2],
                       direction[0], direction[1], direction[2], 0,
                       triangle2, &point2[0], &point2[1], &point2[2],
                       &distance2, &object2, 0, 0.0f);
    if ((hit == 0) || (secondHit == 0)) {
        return 1;
    }
    flags = arg0->flags;
    colors = arg0->colors;
    widths = arg0->widths;
    func_151C756C(point1, triangle1, point2, triangle2, arg0, arg0,
                  colors & 0xFF, (colors & 0xFF00) >> 8, (colors & 0xFF0000) >> 16,
                  (flags & 0x01000000) >> 24,
                  flags & 0xFF, (flags & 0xFF00) >> 8, (flags & 0xFF0000) >> 16,
                  (flags & 0x02000000) >> 25, (flags & 0x04000000) >> 26,
                  ((flags & 0x08000000) >> 27) == 0,
                  ((flags & 0x20000000) >> 29) == 0,
                  ((flags & 0x40000000) >> 30) ? 1 : 0,
                  (flags & 0x10000000) >> 28,
                  (f32)(widths & 0xFF) * D_800AAC38,
                  (f32)((widths & 0xFF00) >> 8) * D_800AAC3C,
                  ((flags & 0x80000000) >> 31) == 0, 255, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C71A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C71A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C756C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C7E98.s")
typedef struct SightOscillation {
    f32 x, y, centerX, centerY, radiusX, radiusY;
    f32 angleX, angleY, speedX, speedY;
    u8 pad28[4];
    void *animation;
    u8 pad30[0x10];
    void *objects[5];
    f32 phase;
    u8 alternate;
    u8 pad59[0x25];
    s16 activeTime;
    u8 pad80[2];
    s16 timer, period;
    u8 flags;
    u8 pad87;
    void *secondary;
    u8 pad8C[0xC];
    f32 brightnessAngle, brightnessSpeed;
} SightOscillation;

f32 func_150AD78C(f32);
f32 func_15144B68(f32);
extern f32 D_800BE9A4, D_800AAC50, D_800AAC54;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C82D0 CURRENT (970) */
s32 func_151C82D0(void *volatile arg0) {
    register SightOscillation *state;
    register s16 period;
    register void *object;
    register void *object1;
    register void *object2;
    register void *object3;

    state = (SightOscillation *)((u8 *)arg0 + 0x110);
    if (state->flags & 1) {
        period = state->period;
        state->timer += D_800BE9E4;
        while (state->timer >= period) {
            state->timer -= period;
        }
        if (state->timer < state->activeTime) {
            state->flags |= 2;
        } else {
            state->flags &= 0xFFFD;
        }
    }
    state = (SightOscillation *)((u8 *)arg0 + 0x110);
    if (state->flags & 2) {
        state->angleX += state->speedX * D_800BE9A4;
        state->angleY += state->speedY * D_800BE9A4;
        state->angleX = func_15144B68(state->angleX);
        state->angleY = func_15144B68(state->angleY);
        state->x = func_150AD78C(state->angleX) * state->radiusX + state->centerX;
        state->y = func_150AD78C(state->angleY) * state->radiusY + state->centerY;
        object = state->animation;
        if (object != NULL) {
            *((u8 *)*(void **)((u8 *)object + 0x14) + 9) = 0;
        }
        object = state->secondary;
        if (object != NULL && (state->flags & 0x10)) {
            *((u8 *)object + 0x14) = 0;
        }
    } else {
        object = state->animation;
        if (object != NULL) {
            *((u8 *)*(void **)((u8 *)object + 0x14) + 9) = 1;
        }
        object = state->secondary;
        if (object != NULL) {
            *((u8 *)object + 0x14) = 1;
        }
    }
    state->phase += D_800AAC50 * D_800BE9A4;
    while (state->phase > 1.0f) {
        if (state->flags & 2) {
            state->alternate ^= 1;
        }
        state->phase -= 1.0f;
    }
    if (state->alternate != 0) {
        object = state->objects[0];
        *(u32 *)((u8 *)object + 0x60) &= 0xFFFDFFFF;
        object1 = state->objects[1];
        *(u32 *)((u8 *)object1 + 0x60) |= 0x20000;
        object2 = state->objects[3];
        *(u32 *)((u8 *)object2 + 0x60) &= 0xFFFDFFFF;
        object3 = state->objects[4];
        *(u32 *)((u8 *)object3 + 0x60) |= 0x20000;
    } else {
        object = state->objects[0];
        *(u32 *)((u8 *)object + 0x60) |= 0x20000;
        object1 = state->objects[1];
        *(u32 *)((u8 *)object1 + 0x60) &= 0xFFFDFFFF;
        object2 = state->objects[3];
        *(u32 *)((u8 *)object2 + 0x60) |= 0x20000;
        object3 = state->objects[4];
        *(u32 *)((u8 *)object3 + 0x60) &= 0xFFFDFFFF;
    }
    if (state->flags & 8) {
        *((u8 *)arg0 + 0x5C) = (u32)(func_150AD78C(state->brightnessAngle) * 112.5f + D_800AAC54);
        state->brightnessAngle = func_15144B68(state->brightnessAngle + state->brightnessSpeed * D_800BE9A4);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C82D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C82D0.s")
void func_151403A8();

void func_151C8674(void *arg0, s32 arg1) {
    struct {
        void *owner;
        s32 value;
    } message;

    if (arg0 != 0) {
        message.owner = arg0;
        message.value = arg1;
        func_151403A8(&message.owner, 0x20, arg0);
    }
}
s32 func_151C87E0(s32, void *);
void func_151C899C();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C86AC CURRENT (935) */
void func_151C86AC(void *volatile arg0, void *arg1, u8 arg2) {
    void *owner;
    s32 owner_id;
    u8 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    switch (arg2) {
    case 0x20:
        owner = arg0;
        temp_v0 = (u8 *)owner + 0x110;
        if ((temp_v0[0x86] & 0x10) &&
            (*(s32 *)(temp_v0 + 0x28) == *(s32 *)((u8 *)arg1 + 4)) &&
            (func_151C87E0(*(s32 *)arg1, owner) != 0)) {
            func_151C899C(*(s32 *)arg1, arg0);
        }
        return;
    case 0x3A:
        temp_v0_2 = arg0;
        owner_id = *(s32 *)(temp_v0_2 + 0x138);
        temp_v0_2 += 0x110;
        if (owner_id == *(s32 *)arg1) {
            temp_v1 = *((u8 *)arg1 + 4);
            switch (temp_v1) {
            case 0:
                temp_v0_2[0x86] |= 2;
                return;
            case 1:
                temp_v0_2[0x86] &= 0xFFFD;
                return;
            case 2:
                func_151C899C(0, arg0);
                break;
            }
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C86AC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C86AC.s")
s32 func_151C87AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x18);
    if (!(*(u8 *)((u8 *)temp_v0 + 0x86) & 2)) {
        *arg6 = 0;
    }
    return 0;
}
extern u8 *D_800D1C90[];
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_151451F0(void *, void *, s32, f32, f32, s32, s32, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C87E0 CURRENT (3348) */
s32 func_151C87E0(s32 arg0, void *arg1) {
    u8 *actor;
    u8 *sight;
    f32 ratio;
    f32 sample;
    f32 half;
    struct {
        f32 inverse;
        u8 pad44[2];
        s16 sample3;
        s16 sample2;
        s16 sample;
        f32 output1;
        f32 output0;
        u8 pad54[0xC];
        u8 result60[0xC];
        f32 length;
        f32 direction[3];
        u8 pad7C[0xC];
        f32 clipped[3];
        u8 pad94[4];
        f32 start[3];
        u8 padA4[4];
        f32 radius;
    } local;

    actor = (u8 *)arg0;
    sight = arg1;
    if ((actor[4] < 0xBB) && (actor[4] != 0xFF)) {
        local.radius = (f32)*(s16 *)(D_800D1C90[actor[4]] + 0x1A) * *(f32 *)(actor + 0x14C);
    } else {
        local.radius = 50.0f;
    }
    func_1507C3E0(actor, &local.sample, &local.sample2, &local.sample3);
    sample = (f32)local.sample;
    if (sample == 0.0f) {
        return 0;
    }
    half = sample * 0.5f;
    ratio = local.radius / half;
    local.start[0] = *(f32 *)(actor + 0x14);
    local.start[1] = *(f32 *)(actor + 0x18) + half;
    local.start[2] = *(f32 *)(actor + 0x1C);
    local.clipped[0] = *(f32 *)(sight + 0x34);
    local.clipped[1] = ((*(f32 *)(sight + 0x38) - local.start[1]) * ratio) + local.start[1];
    local.clipped[2] = *(f32 *)(sight + 0x3C);
    local.direction[0] = *(f32 *)(sight + 0x40) - local.clipped[0];
    local.direction[1] = (((*(f32 *)(sight + 0x44) - local.start[1]) * ratio) + local.start[1]) - local.clipped[1];
    local.direction[2] = *(f32 *)(sight + 0x48) - local.clipped[2];
    if (func_15145128(local.direction, local.direction, &local.length, &local.inverse) == 0) {
        return 0;
    }
    if (func_151451F0(local.clipped, local.direction, (s32)local.start, local.radius, local.length,
                      (s32)local.result60, (s32)local.pad54, &local.output0, &local.output1) != 0) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C87E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C899C.s")
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800AAC70;
extern f32 D_800AAC74;
extern f32 D_800AAC78;
s32 func_151407D0();

typedef struct Sight8FCCVector { s32 words[3]; } Sight8FCCVector;
typedef struct Sight8FCCDescriptor {
    u8 kind, mode;
    u16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 callback0, callback1;
    u8 colors[4];
    f32 field14, field18;
    Sight8FCCVector position, direction;
    f32 scales[3];
    u32 options;
    u8 channels[4];
    s32 parameter;
    u8 pad4C[0xC];
} Sight8FCCDescriptor;

typedef struct Sight8FCCParameters {
    f32 values[9];
    u8 pad24[0x24];
    f32 multiplier;
    u8 pad4C[8];
    u8 states[5];
} Sight8FCCParameters;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C8FCC CURRENT (1783) */
s32 func_151C8FCC(s32 arg0, Sight8FCCVector *arg1, Sight8FCCVector *arg2,
                  u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7,
                  u8 arg8, s32 arg9) {
    s32 saved;
    Sight8FCCParameters parameters;
    Sight8FCCDescriptor descriptor;
    s32 owner;
    u32 options;
    s32 result;

    descriptor.position = *arg1;
    descriptor.direction = *arg2;
    owner = arg0;
    parameters.values[0] = D_800AAC70;
    parameters.values[1] = D_800AAC70;
    parameters.values[2] = 40.0f;
    parameters.values[3] = 40.0f;
    parameters.values[6] = 1.0f;
    parameters.values[4] = 0.0f;
    parameters.values[5] = 0.0f;
    descriptor.kind = 0x15;
    descriptor.flags = 0x3403;
    descriptor.lifetime = 0x12C;
    descriptor.callback0 = 0;
    descriptor.callback1 = 0;
    descriptor.colors[0] = arg3;
    descriptor.colors[3] = 0xFF;
    descriptor.field14 = 0.0f;
    descriptor.field18 = 0.0f;
    descriptor.scales[0] = 1.0f;
    descriptor.scales[1] = 1.0f;
    descriptor.scales[2] = 1.0f;
    parameters.values[7] = D_800AAC74;
    descriptor.colors[1] = arg4;
    descriptor.colors[2] = arg5;
    options = 0;
    if (arg7 != 0) {
        options = 0x01000000;
    }
    descriptor.options = options | 0x024D2006 | 0x40000000;
    descriptor.channels[1] = 0xFF;
    descriptor.channels[0] = 0xFF;
    descriptor.channels[2] = 0;
    descriptor.channels[3] = 6;
    descriptor.mode = 3;
    parameters.states[0] = 0;
    parameters.states[1] = 0;
    parameters.states[2] = 0;
    parameters.states[3] = 0;
    parameters.multiplier = 1.0f;
    parameters.states[4] = 0;
    descriptor.parameter = arg6;
    parameters.values[8] = D_800AAC78;
    result = func_151407D0(&parameters, 100, &descriptor, 0, 0, 0, 0, 1, arg8, arg9);
    if (result != 0) {
        saved = result;
        func_10022EC0((void *)(result + 0x170), &owner, 4);
        result = saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C8FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C8FCC.s")
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
s32 func_15144E80(void *, void *, void *, void *);
void func_15145974(void *, f32 *, f32 *);
extern f32 D_800AAC7C;

/* func_1513264C copies all 0x7C bytes into the spawned effect. */
typedef struct SightSpawnDescriptor {
    f32 scale0, scale1, field08, field0C;
    f32 pitch, yaw, roll;
    f32 scale[3];
    Sight8FCCVector position;
    f32 motion[7];
    s32 flags;
    s16 lifetime, kind;
    s8 field58;
    u8 pad59[3];
    s32 owner;
    u8 channels[8];
    s8 field68, field69, field6A;
    u8 pad6B;
    s32 field6C;
    s8 field70;
    u8 pad71;
    s16 field72, field74;
    u8 pad76[6];
} SightSpawnDescriptor;

typedef struct SightSpawnCommand {
    s16 id;
    s8 mode;
    u8 pad3;
    s32 value;
} SightSpawnCommand;

typedef struct SightSpawnCommands {
    s8 count;
    u8 pad1[3];
    SightSpawnCommand entries[2];
} SightSpawnCommands;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9198 CURRENT (1147) */
void func_151C9198(struct Game15F680TransformState **arg0, Sight8FCCVector *arg1,
                   void *arg2, s32 arg3, s32 arg4, volatile u8 arg5, u8 arg6, u8 arg7, s32 arg8) {
    Sight8FCCVector vector0, vector1, vector2;
    SightSpawnDescriptor descriptor;
    struct Game15F680TransformState *result;
    SightSpawnCommands commands;
    s32 offset;
    s32 flags;
    struct Game15F680TransformState *effect;

    if (func_15144E80(arg2, &vector0, &vector1, &vector2) != 0) {
        func_15145974(&vector2, &descriptor.yaw, &descriptor.pitch);
        descriptor.scale0 = 1.0f;
        descriptor.scale1 = 1.0f;
        descriptor.scale[0] = 1.0f;
        descriptor.scale[1] = 1.0f;
        descriptor.pitch += 90.0f;
        descriptor.scale[2] = 1.0f;
        descriptor.field0C = D_800AAC7C;
        descriptor.field08 = D_800AAC7C;
        descriptor.roll = 0.0f;
        descriptor.position = *arg1;
        descriptor.motion[0] = 0.0f;
        descriptor.motion[1] = 0.0f;
        descriptor.motion[2] = 0.0f;
        descriptor.motion[3] = 0.0f;
        descriptor.motion[4] = 0.0f;
        descriptor.motion[5] = 0.0f;
        descriptor.motion[6] = 0.0f;
        if (arg6 != 0) {
            flags = 0x400;
        } else {
            flags = 0;
        }
        descriptor.flags = flags | 0x900 | 0x10000 | 0x4000 | 0x40000 | 0x80000;
        descriptor.lifetime = 0x12C;
        descriptor.kind = 0x36;
        descriptor.field58 = 0;
        descriptor.channels[0] = 0xFF;
        descriptor.channels[1] = 0;
        descriptor.channels[2] = 0;
        descriptor.channels[3] = 0;
        descriptor.channels[4] = 0;
        descriptor.channels[5] = 0;
        descriptor.channels[6] = 0;
        descriptor.channels[7] = 0;
        descriptor.field68 = 2;
        descriptor.field6A = 0;
        descriptor.field6C = 0;
        descriptor.field70 = 0;
        descriptor.field72 = 1;
        descriptor.field74 = 0xFF;
        descriptor.field69 = -1;
        descriptor.owner = arg4;
        result = func_15132A4C(&descriptor, 3, 0xFF, 0, arg7, arg8);
        arg0[0] = result;
        if (result != 0) {
            offset = 0;
            do {
                effect = arg0[0];
                func_15133760((s32)((u8 *)effect + offset + 0x90), effect);
                offset += 0x40;
            } while (offset != 0x80);
        }
        descriptor.field69 = 2;
        commands.count = 2;
        commands.entries[0].mode = 4;
        commands.entries[1].mode = 6;
        commands.entries[0].value = 0x3E;
        commands.entries[1].value = 0x3E;
        if (arg5 != 0) {
            commands.entries[0].id = 0x87;
            commands.entries[1].id = 0x88;
        } else {
            commands.entries[0].id = 0x8B;
            commands.entries[1].id = 0x8C;
        }
        descriptor.kind = 0x37;
        descriptor.field68 = 0;
        result = func_15132A4C(&descriptor, 3, 0xFF, 0x14, arg7, arg8);
        arg0[1] = result;
        if (result != 0) {
            offset = 0;
            do {
                effect = arg0[1];
                func_15133760((s32)((u8 *)effect + offset + 0x90), effect);
                offset += 0x40;
            } while (offset != 0x80);
            func_10022EC0((u8 *)arg0[1] + 0x170, &commands, 0x14);
        }
        descriptor.kind = 0x38;
        if (arg5 != 0) {
            commands.entries[0].id = 0x89;
            commands.entries[1].id = 0x8A;
        } else {
            commands.entries[0].id = 0x8D;
            commands.entries[1].id = 0x8E;
        }
        result = func_15132A4C(&descriptor, 3, 0xFF, 0x14, arg7, arg8);
        arg0[2] = result;
        if (result != 0) {
            offset = 0;
            do {
                effect = arg0[2];
                func_15133760((s32)((u8 *)effect + offset + 0x90), effect);
                offset += 0x40;
            } while (offset != 0x80);
            func_10022EC0((u8 *)arg0[2] + 0x170, &commands, 0x14);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9198 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9198.s")
void func_1000FD38(void *, void *, s32);

void func_151C94D4(void *arg0) {
    u8 *state = (u8 *)arg0 + 0x110;

    if (*(s32 *)(state + 0x2C) != 0) {
        func_1516972C(*(void **)(state + 0x2C));
        func_1000FD38((void *)func_151C87AC, state, 0);
    }
    if (*(void **)(state + 0x34) != 0) {
        func_1516972C(*(void **)(state + 0x34));
    }
    if (*(void **)(state + 0x38) != 0) {
        func_1516972C(*(void **)(state + 0x38));
    }
    if (*(void **)(state + 0x3C) != 0) {
        func_1516972C(*(void **)(state + 0x3C));
    }
    if (*(void **)(state + 0x40) != 0) {
        func_1516972C(*(void **)(state + 0x40));
    }
    if (*(void **)(state + 0x44) != 0) {
        func_1516972C(*(void **)(state + 0x44));
    }
    if (*(void **)(state + 0x48) != 0) {
        func_1516972C(*(void **)(state + 0x48));
    }
    if (*(void **)(state + 0x4C) != 0) {
        func_1516972C(*(void **)(state + 0x4C));
    }
    if (*(void **)(state + 0x50) != 0) {
        func_1516972C(*(void **)(state + 0x50));
    }
    func_1513CA6C((s32)arg0);
}

void func_151C95D8(void *arg0) {
    u8 *state = (u8 *)arg0 + 0x110;

    if (*(s32 *)(state + 0x2C) != 0) {
        func_1516972C(*(void **)(state + 0x2C));
        func_1000FD38((void *)func_151C87AC, state, 0);
    }
    if (*(void **)(state + 0x34) != 0) {
        func_1516972C(*(void **)(state + 0x34));
    }
    if (*(void **)(state + 0x38) != 0) {
        func_1516972C(*(void **)(state + 0x38));
    }
    if (*(void **)(state + 0x3C) != 0) {
        func_1516972C(*(void **)(state + 0x3C));
    }
    if (*(void **)(state + 0x40) != 0) {
        func_1516972C(*(void **)(state + 0x40));
    }
    if (*(void **)(state + 0x44) != 0) {
        func_1516972C(*(void **)(state + 0x44));
    }
    if (*(void **)(state + 0x48) != 0) {
        func_1516972C(*(void **)(state + 0x48));
    }
    if (*(void **)(state + 0x4C) != 0) {
        func_1516972C(*(void **)(state + 0x4C));
    }
    if (*(void **)(state + 0x50) != 0) {
        func_1516972C(*(void **)(state + 0x50));
    }
    func_1513CAA0((s32)arg0);
}
s32 func_151C96DC(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x170);
    temp_v0 += 0x110;
    if (*(u8 *)(temp_v0 + 0x86) & 2) {
        return 1;
    }
    return 0;
}
void func_151C970C(s32 arg0, void *arg1) {
    struct {
        void *sp18;
        s8 sp1C;
    } sp;

    sp.sp18 = arg1;
    sp.sp1C = (s8)arg0;
    func_151403A8(&sp.sp18, 0x3A, arg1);
}

typedef struct EffectsSightTransform {
    u8 bytes[0x24];
} EffectsSightTransform;

typedef struct EffectsSightActor {
    u8 pad0[0x14];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[0x160];
    f32 y;
} EffectsSightActor;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(EffectsSightTransform *, EffectsSightActor *);
void func_150E83AC(void *, s16, u8, s32);
void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void *func_151541B8(void *, f32, f32, f32, f32, s32, s32);
void func_151D5334(void *, f32, f32, f32, u8, u8, s32);
void func_151D5514(void *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9740 CURRENT (3809) */
void func_151C9740(EffectsSightActor *arg0, u8 arg1, s32 arg2) {
    Vec3f origin;
    Vec3f impact;
    u8 hit;
    u8 airborne;
    Vec3f query;
    union {
        EffectsSightTransform transform;
        f32 values[9];
    } collision;
    f32 *point;
    u32 randomWord;
    f32 randomFloat;
    register s32 priority;

    priority = arg1;
    if (arg0 != NULL) {
        origin.x = arg0->x;
        origin.y = *(f32 *)((u8 *)arg0 + 0x18) + 135.0f;
        origin.z = arg0->z;
        hit = 0;
        airborne = *(f32 *)((u8 *)arg0 + 0x2D8) != 0.0f;
        if (!airborne) {
            query.x = origin.x;
            query.y = origin.y;
            query.z = origin.z;
            func_1504715C(&collision.transform, arg0);
            if (func_15046C80(&query.x, 0, origin.y - 200.0f, &collision.transform) != 0 &&
                (collision.transform.bytes[0x1C] & 1)) {
                impact.x = query.x;
                hit = 1;
                impact.y = collision.values[0];
                impact.z = query.z;
                randomFloat = func_150ADA68();
                randomWord = func_150ADA20();
                func_150E7FEC(randomFloat * 125.0f + 204.0f,
                    (randomWord % 101U + 0x9B) & 0xFF,
                    (s32)&collision.values[1], (s32)&impact,
                    func_150ADA20() % 302U + 0x1F4, 0, 1, 0, 0, 0, priority, 0);
            }
        }
        func_151D5404(&origin, 506.0f, 1013.0f, 0.000987166888f, 0xF, 0x14, priority, arg2);
        func_151D5334(&origin, 506.0f, 1013.0f, 0.000987166888f, 5, priority, arg2);
        func_151D5514(&origin, priority, arg2);
        func_151D3FF4(&origin.x, priority, arg2);
        point = hit ? &impact.x : &origin.x;
        func_150E83AC(point, (s16)(func_150ADA20() % 62U + 0x78), priority, arg2);
        randomFloat = func_150ADA68();
        func_151541B8(&origin, 2.0f * randomFloat + 8.0f, 2.4641099f,
            (f32)(func_150ADA20() % 56U + 0xC8), 0.0f, priority, arg2);
        if (!airborne) {
            func_15136C3C(arg0, 0, 0, 1, 0, 0, priority, arg2);
        }
        func_10010F88(0x60D, 0x7D00, 0, 0, 0, (s32)origin.x,
            (s32)origin.y, (s32)origin.z, 0x1F4, 0x3E8);
        if (airborne) {
            func_151C9AC0(arg0, priority, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9740 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9740.s")


void func_1504715C(EffectsSightTransform *, EffectsSightActor *);
void func_151ABE40(Vec3f *, EffectsSightTransform *, s32, u8, s32);

void func_151C9AC0(EffectsSightActor *arg0, u8 arg1, s32 arg2) {
    Vec3f position;
    EffectsSightTransform transform;

    position.x = arg0->x;
    position.y = arg0->y + 2.0f;
    position.z = arg0->z;
    func_1504715C(&transform, arg0);
    func_151ABE40(&position, &transform, 2, arg1, arg2);
}
s32 func_151C9B30(void *arg0) {
    void *temp_v0 = *(void **)((u8 *)arg0 + 0x18);

    if (*(u8 *)((u8 *)temp_v0 + 0x6F) == 0) {
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 9) = 0;
    } else {
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x14) + 9) = 1;
    }
    return 1;
}
s32 func_151C9B64(void *arg0, s8 *arg1) {
    s32 var_v0;
    s32 temp_t7;
    void *temp_v0;

    var_v0 = 1;
    temp_t7 = 1;
    temp_v0 = *(void **)((u8 *)arg0 + 0x188);
    if (*(u8 *)((u8 *)temp_v0 + 0x6F) == 0) {
        *arg1 = temp_t7;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = *(s32 *)((u8 *)arg0 + 0x58) & ~2;
        *arg1 = 0;
    }
    return var_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9BA0.s")
void func_150BDE90(s32, u8, s32);
s32 func_151C9F38(s32, s32, s32, s8, s32);
void func_151CB5FC(s32, u8, u8, s8, u8);
void func_151CC524(s32, s32, s32, s32, s32, s32);
s32 func_151CC840(s32, s32, s32, s32, s32, s32);
void func_151CCF08(s32, u8, s8, u8);
extern s32 D_800BE9F0;
extern s8 D_8008CD00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9DE8 CURRENT (2019) */
void func_151C9DE8(s32 arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    func_151C9F38(arg0, 4, arg1, arg2, arg3);
    func_151CC524(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CC840(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CCF08(arg0, arg1, arg2, arg3);
    func_150BDE90(arg0, arg3, arg4);
    func_151CB5FC(arg0, 2, arg1, arg2, arg3);
    if (D_800BE9F0 == 0x27) {
        D_8008CD00 = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9DE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9DE8.s")
void func_15160274(void *, u8);
void func_1515572C();
extern s8 D_8008CD00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C9ED4 CURRENT (1434) */
void func_151C9ED4(void *arg0) {
    void *sp24;

    sp24 = arg0;
    func_15160274(&sp24, 0x21);
    func_1515572C(&sp24, 0x21);
    func_151A561C(&sp24, 0x21);
    func_151494E0(&sp24, 0x21);
    D_8008CD00 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C9ED4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9F38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CA6A0.s")
extern void (*D_8008FC10[])(void *, void **, u8);

void func_151CAACC(void *arg0, void **arg1, volatile u8 arg2) {
    s32 type;
    void *other;
    void (*callback)(void *, void **, u8);

    type = arg2;
    if (type == 0x21) {
        if (*(void **)((u8 *)arg0 + 0x70) == *arg1) {
            void *owner = arg0;

            func_1516972C(owner);
        }
    } else if (type == 0) {
        other = *arg1;
        if (*(void **)((u8 *)arg0 + 0x70) == *(void **)((u8 *)other + 0x318)) {
            func_1516972C(arg0);
        }
    }
    callback = D_8008FC10[*(u8 *)((u8 *)arg0 + 0x7D)];
    if (callback != 0) {
        callback(arg0, arg1, arg2);
    }
}
extern s32 D_80082FA0;
void *func_1515548C(void *, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CAB78 CURRENT (1557) */
void func_151CAB78(u8 *arg0, u8 arg1) {
    struct {
        f32 x;
        f32 y;
        f32 width;
        f32 height;
        u8 type;
        u8 pad11;
        s16 angle;
        s16 flags;
        s16 count;
        s16 color;
        u8 mode;
        u8 arg1;
        u8 arg2;
        u8 arg3;
        u8 time;
        u8 color0;
        u8 color1;
        u8 color2;
        u8 color3;
        u8 color4;
        s32 field24;
        s32 field28;
        s32 field2C;
        s32 field30;
        s32 field34;
        s32 field38;
        s32 field3C;
        u8 field40;
        u8 field41;
        u8 pad42[2];
        u8 field44;
        u8 pad45[0x13];
    } spawn;
    struct {
        u8 *owner;
        f32 zero;
        f32 scale;
        u8 bytes[2];
        u8 pad[0x4E];
    } payload;
    f32 multiplier;
    s32 mode;
    void *object;

    payload.owner = arg0;
    payload.zero = 0.0f;
    payload.bytes[1] = 0;
    payload.bytes[0] = 0;
    payload.scale = 130.0f;
    if (D_80082FA0 > 0) {
        multiplier = 2.0f;
    } else {
        multiplier = 1.0f;
    }
    spawn.type = 100;
    spawn.angle = 300;
    spawn.height = multiplier * 12.0f;
    spawn.width = spawn.height;
    spawn.color = 255;
    spawn.mode = 7;
    spawn.flags = (1 << (arg0[0x23D] + 11)) | 0x50;
    spawn.count = 1;
    spawn.arg1 = 255;
    spawn.arg2 = 200;
    spawn.time = 130;
    spawn.color0 = 255;
    spawn.color1 = 255;
    spawn.arg3 = 0;
    spawn.color2 = 255;
    spawn.color3 = 255;
    spawn.color4 = 255;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 8;
    spawn.field34 = 0x44;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 10;
    spawn.x = 0.0f;
    spawn.y = 0.0f;
    spawn.field44 = arg0[0x23D];
    mode = arg1 ? 4 : 0;
    object = func_1515548C(&spawn, mode & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CAB78 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAB78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAD28.s")
typedef struct SightWarpState {
    s32 field0;
    u8 *center;
    u16 *pixels;
    s32 rowOffset;
    s32 columnOffset;
} SightWarpState;

f32 func_15145A0C(f32, f32, f32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern f32 D_800AAE9C, D_800AAEA0, D_800AAEA4;
extern s32 D_800BE620;
extern u8 D_800BEAC0, D_800BEAC1, D_800BEAC2;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CB110 CURRENT (8774) */
void func_151CB110(u8 *arg0, u16 *arg1) {
    SightWarpState *state;
    u8 *center;
    s32 copyRow;
    s32 copyDestination;
    s32 copySource;
    volatile f32 savedY;
    register f32 radius;
    f32 scale;
    f32 offset;
    volatile s32 savedBottom;
    volatile s32 savedRight;
    volatile s32 savedTop;
    volatile s32 savedLeft;
    f32 blend;
    volatile s32 savedSourceBottom;
    volatile s32 savedSourceRight;
    volatile s32 savedSourceTop;
    volatile s32 savedSourceLeft;
    f32 y;
    f32 x;
    f32 sampleX;
    f32 sampleY;
    s32 bottom;
    s32 right;
    s32 top;
    s32 left;
    s32 sourceBottom;
    s32 sourceRight;
    s32 sourceTop;
    s32 sourceLeft;

    if ((D_800BEAC0 == 0) && (D_800BEAC1 == 0)) {
        copyRow = 0;
        copyDestination = 0;
        state = (SightWarpState *)(arg0 + 0x18);
        if (D_800BEAC2 == 0) {
            center = state->center;
            copySource = state->rowOffset + state->columnOffset;
            do {
                func_10022EC0(state->pixels + copyDestination, arg1 + copySource, 0x30U);
                copyRow++;
                copyDestination += 0x18;
                copySource += D_800BE620;
            } while (copyRow != 0x18);
            for (y = -1.0f; y < 0.0f; y += D_800AAEA4) {
                savedY = y;
                radius = func_15145A0C(fabsf(y), 1.0f, 1.0f);
                y = savedY;
                if (radius != 0.0f) {
                    offset = y * 12.0f;
                    x = -radius;
                    savedTop = top = (s32)(*(f32 *)(center + 0x38) + offset) * D_800BE620;
                    savedBottom = bottom = (s32)(*(f32 *)(center + 0x38) - offset) * D_800BE620;
                    if (x < 0.0f) {
                        scale = 1.0f - (1.0f - radius * D_800AAE9C);
                        do {
                            savedY = y;
                            blend = func_15145A0C(fabsf(x), radius, 1.0f / radius) * scale;
                            y = savedY;
                            offset = x * 12.0f;
                            savedLeft = left = (s32)(*(f32 *)(center + 0x34) + offset);
                            savedRight = right = (s32)(*(f32 *)(center + 0x34) - offset);
                            blend = 1.0f - blend;
                            sampleX = x * blend * 12.0f;
                            sampleY = y * blend * 12.0f;
                            savedSourceLeft = sourceLeft = (s32)(sampleX + 12.0f);
                            savedSourceRight = sourceRight = (s32)(12.0f - sampleX);
                            savedSourceTop = sourceTop = (s32)(sampleY + 12.0f) * 0x18;
                            savedSourceBottom = sourceBottom = (s32)(12.0f - sampleY) * 0x18;
                            top = savedTop;
                            bottom = savedBottom;
                            *(arg1 + top + left) = *(state->pixels + sourceLeft + sourceTop);
                            *(arg1 + top + right) = *(state->pixels + sourceRight + sourceTop);
                            *(arg1 + bottom + right) = *(state->pixels + sourceRight + sourceBottom);
                            *(arg1 + bottom + left) = *(state->pixels + sourceLeft + sourceBottom);
                            x += D_800AAEA0;
                        } while (x < 0.0f);
                    }
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CB110 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB110.s")

typedef struct SightActor {
    u8 pad0[0x318];
    void *field_318;
} SightActor;

typedef struct SightEffect {
    u8 pad0[0x18];
    SightActor *owner;
} SightEffect;

typedef struct SightMessage {
    SightActor *actor;
} SightMessage;

void func_151CB49C(SightEffect *arg0, SightMessage *arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (arg1->actor == arg0->owner) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        SightActor *actor = arg1->actor;

        if (actor->field_318 == arg0->owner) {
            func_1516972C(arg0);
        }
    }
}
extern f32 D_800AAEA8;

void func_151CB510(void *arg0) {
    f32 temp_fv1;
    f32 var_fv0;
    void *temp_v0;
    u8 *var_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x70);
    if ((**(u16 **)((u8 *)temp_v0 + 0x36C) & 0x2000) &&
        (var_v0 = (u8 *)arg0 + 0x70,
         (*(u16 *)(*(u8 **)((u8 *)temp_v0 + 0x3D4) + 0x19E) == 0))) {
        var_fv0 = *(f32 *)(var_v0 + 8);
    } else {
        var_fv0 = 0.0f;
        var_v0 = (u8 *)arg0 + 0x70;
    }
    temp_fv1 = *(f32 *)(var_v0 + 4);
    *(f32 *)(var_v0 + 4) += (var_fv0 - temp_fv1) * D_800AAEA8;
    *(s8 *)((u8 *)arg0 + 0x2E) = (s8)(u32)*(f32 *)(var_v0 + 4);
}
typedef struct SightCrosshairPayload {
    u8 *owner;
    f32 unk4;
    f32 unk8;
    u8 mode;
    u8 arg1;
    u8 side;
    u8 padF;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8 pad24[0x30];
    s8 unk54;
    u8 pad55[3];
} SightCrosshairPayload;

typedef struct SightCrosshairSpawn {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 type;
    u8 pad11;
    s16 angle;
    u16 flags;
    s16 count;
    s16 color;
    u8 mode;
    u8 arg1;
    u8 arg2;
    u8 arg3;
    u8 time;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3C;
    u8 field40;
    u8 field41;
    u8 pad42[2];
    u8 field44;
    u8 pad45[3];
} SightCrosshairSpawn;

extern f32 D_800AAD84[];
extern f32 D_800AADAC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CB5FC CURRENT (6057) */
void func_151CB5FC(s32 arg0, u8 arg1, u8 arg2, s8 arg3, u8 arg4) {
    f32 alpha;
    s32 mode;
    s32 bits;
    s32 index;
    SightCrosshairSpawn spawn;
    void *object;
    SightCrosshairPayload payload;

    alpha = 255.0f;
    payload.unk4 = alpha;
    payload.unk8 = alpha;
    payload.arg1 = arg1;
    payload.owner = (u8 *)arg0;
    if (arg3 == -1) {
        mode = 0;
    } else {
        mode = 4;
    }
    payload.mode = mode;
    payload.unk54 = arg3;
    payload.unk14 = alpha;
    spawn.angle = 300;
    spawn.width = 49.0f;
    payload.unk10 = 0.0f;
    spawn.height = 18.0f;
    if (arg2) {
        bits = 0x40;
    } else {
        bits = 0;
    }
    spawn.flags = bits | 0x32 | (1 << (((u8 *)arg0)[0x23D] + 11));
    spawn.mode = 7;
    spawn.arg1 = 255;
    spawn.count = 1;
    spawn.arg2 = 255;
    spawn.arg3 = 255;
    spawn.color0 = 255;
    spawn.color1 = 255;
    spawn.color2 = 255;
    spawn.color = 255;
    spawn.color3 = 255;
    spawn.color4 = 255;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 7;
    spawn.field34 = 0x22;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 7;
    payload.side = 0;
    spawn.time = 255;
    spawn.type = 0x7B;
    payload.unk1C = 0.0f;
    spawn.field44 = ((u8 *)arg0)[0x23D];
    spawn.x = 88.0f;
    spawn.y = 91.0f;
    payload.unk18 = D_800AAD84[D_80082FA0 == 1];
    payload.unk20 = D_800AADAC[D_80082FA0 == 1];
    object = func_1515548C(&spawn, 5, 0, 0, 0x58, arg4, 0);
    if (object != NULL) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
    spawn.time = 0;
    spawn.type = 0x7C;
    object = func_1515548C(&spawn, 5, 0, 0, 0x58, arg4, 0);
    if (object != NULL) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
    spawn.flags &= 0xFFFD;
    spawn.time = 255;
    spawn.type = 0x7B;
    payload.side = 1;
    spawn.x = -88.0f;
    spawn.y = 91.0f;
    object = func_1515548C(&spawn, 5, 0, 0, 0x58, arg4, 0);
    if (object != NULL) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
    spawn.time = 0;
    spawn.type = 0x7C;
    object = func_1515548C(&spawn, 5, 0, 0, 0x58, arg4, 0);
    if (object != NULL) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CB5FC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB5FC.s")
void func_151CB918(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if ((arg2 == 0x37) && (*(u8 *)((u8 *)arg1 + 0) == *(u8 *)((u8 *)temp_v0 + 0xE)) && (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)((u8 *)temp_v0 + 0x10) = 0.0f;
        *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v0 + 0xC) | 1);
        *(f32 *)((u8 *)temp_v0 + 0x14) = 0.0f;
    }
}
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
extern f32 D_800AAEAC;
extern f32 D_800AAEB0;
extern f32 D_800AAEB4;
extern f32 D_800BE9A4;
f32 func_151CC1D4(void *);

s32 func_151CB970(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    s32 temp_t2;
    f32 temp_fv1;
    u8 *temp_v1;

    temp_v1 = (void *)(arg0 + 0x70);
    temp_fv1 = (1.0f - (*(f32 *)((u8 *)temp_v1 + 0x20) * (func_151CC1D4(arg0) - *(f32 *)((u8 *)temp_v1 + 0x18)))) * 75.0f;
    if (*(u8 *)((u8 *)temp_v1 + 0xC) & 1) {
        temp_fa0 = 91.0f + temp_fv1;
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_v1 + 0x10)) * ((112.0f + temp_fv1) - temp_fa0)) + temp_fa0);
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10) + (D_800AAEAC * D_800BE9A4));
        if (D_800AAEB0 <= *(f32 *)((u8 *)temp_v1 + 0x10)) {
            *(f32 *)((u8 *)arg0 + 0x14) = temp_fa0;
            *(u8 *)((u8 *)temp_v1 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v1 + 0xC) & 0xFFFE);
        }
    } else {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (91.0f + temp_fv1);
    }
    if (*(u8 *)((u8 *)temp_v1 + 0xD) == 2) {
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) - 20.0f);
    }
    temp_t2 = (u32) *(f32 *)((u8 *)temp_v1 + 0x14) & 0xFF;
    if (*(u8 *)((u8 *)arg0 + 0x20) == 0x7C) {
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (0xFF - temp_t2);
    } else {
        *(s8 *)((u8 *)arg0 + 0x2E) = temp_t2;
    }
    temp_fv0 = *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)temp_v1 + 0x14) += (255.0f - temp_fv0) * D_800AAEB4;
    return 1;
}
typedef struct SightEffect20 {
    u8 pad0[0x20];
    SightActor *owner;
} SightEffect20;

void func_151CBB6C(SightEffect20 *arg0, SightMessage *arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (arg1->actor == arg0->owner) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        SightActor *actor = arg1->actor;

        if (actor->field_318 == arg0->owner) {
            func_1516972C(arg0);
        }
    }
}
void func_1514373C(f32, f32, f32 *, f32 *);
extern f32 D_800AAEB8;

f32 func_151CC1D4(void *);

s32 func_151CBBE0(u8 *arg0) {
    u8 *state = arg0 + 0x70;
    f32 value;
    f32 offset;

    value = func_151CC1D4(arg0);
    if (value != *(f32 *)(state + 0x28)) {
        *(f32 *)(state + 0x28) = value;
        offset = *(f32 *)(state + 0x20) * (value - *(f32 *)(state + 0x18)) * D_800AAEB8;
        func_1514373C(*(f32 *)(state + 0x24) + offset,
                      55.0f, (f32 *)(arg0 + 0x10), (f32 *)(arg0 + 0x14));
    }
    return 1;
}
extern f32 D_800AAEBC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CBC60 CURRENT (1330) */
s32 func_151CBC60(u8 *arg0) {
    f32 scale;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_v0;

    temp_fv0 = func_151CC1D4(arg0);
    temp_v0 = ((u8 (*)[0x70])arg0)[1];
    if (temp_fv0 != *(f32 *)((u8 *)temp_v0 + 0x28)) {
        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x4C);
        *(f32 *)((u8 *)temp_v0 + 0x28) = temp_fv0;
        *(f32 *)((u8 *)arg0 + 0x1C) = (f32) ((temp_fv1 - ((temp_fv0 - *(f32 *)((u8 *)temp_v0 + 0x18)) * *(f32 *)((u8 *)temp_v0 + 0x20) * temp_fv1)) + 1.0f);
    }
    if (*(u8 *)((u8 *)temp_v0 + 0xC) & 2) {
        *(f32 *)((u8 *)temp_v0 + 0x50) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x50) - D_800BE9A4);
        temp_ft5 = *(f32 *)((u8 *)temp_v0 + 0x50);
        if (temp_ft5 <= 0.0f) {
            *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x3C);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x40);
            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x44);
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (u32) *(f32 *)((u8 *)temp_v0 + 0x48);
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) (*(u8 *)((u8 *)temp_v0 + 0xC) & 0xFFFD);
        } else {
            scale = D_800AAEBC;
            temp_fv0_2 = *(f32 *)((u8 *)temp_v0 + 0x3C);
            *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_v0 + 0x2C) - temp_fv0_2) * (temp_ft5 * scale)));
            temp_fv1_2 = *(f32 *)((u8 *)temp_v0 + 0x40);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (u32) (temp_fv1_2 + ((*(f32 *)((u8 *)temp_v0 + 0x30) - temp_fv1_2) * (*(f32 *)((u8 *)temp_v0 + 0x50) * scale)));
            temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x44);
            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (u32) (temp_fa0 + ((*(f32 *)((u8 *)temp_v0 + 0x34) - temp_fa0) * (*(f32 *)((u8 *)temp_v0 + 0x50) * scale)));
            temp_fa1 = *(f32 *)((u8 *)temp_v0 + 0x48);
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (u32) (temp_fa1 + ((*(f32 *)((u8 *)temp_v0 + 0x38) - temp_fa1) * (*(f32 *)((u8 *)temp_v0 + 0x50) * scale)));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CBC60 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBC60.s")

extern f32 D_800AAEC0;
extern s32 D_800C3958;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CC1D4 CURRENT (715) */
f32 func_151CC1D4(void *arg0) {
    struct State {
        void *object;
        u8 pad4[0x14];
        f32 lower;
        f32 upper;
        u8 pad20[0x34];
        s8 index;
    };
    struct State *state;
    f32 upper;
    f32 value;
    f32 lower;
    void *object;

    state = (struct State *)((u8 *)arg0 + 0x70);
    if (*(u8 *)((u8 *)arg0 + 0x7C) & 4) {
        state = (struct State *)((u8 *)arg0 + 0x70);
        upper = *(f32 *)((u8 *)D_800C3958 +
                          (state->index * 0x44) + 0x28) * D_800AAEC0;
        lower = state->lower;
        value = lower + ((state->upper - lower) * upper);
    } else {
        object = state->object;
        value = (*(f32 *)((u8 *)object + 0x1A0) +
                 *(f32 *)((u8 *)object + 0x19C)) * 0.5f;
        lower = state->lower;
    }
    if (value < lower) {
        value = lower;
    } else {
        upper = state->upper;
        if (upper < value) {
            value = upper;
        }
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CC1D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC1D4.s")
void func_151CC290(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x46, arg0);
}
typedef struct SightFlashPayload {
    s32 owner_word;
    u8 pad04[8];
    u8 flags;
    u8 selector;
    u8 pad0E[0x1E];
    f32 red;
    f32 green;
    f32 blue;
    f32 alpha;
    u8 pad3C[0x14];
    f32 timer;
} SightFlashPayload;

void func_151CC2BC(void *arg0, void **arg1, u8 arg2) {
    SightFlashPayload *state;

    state = (SightFlashPayload *)((u8 *)arg0 + 0x70);
    if (arg2 == 0x46) {
        if (*(s32 *)arg1 == (*state).owner_word) {
            state->flags |= 2;
            state->timer = 35.0f;
            ((u8 *)arg0)[0x2B] = (u8)(u32)state->red;
            ((u8 *)arg0)[0x2C] = (u8)(u32)state->green;
            ((u8 *)arg0)[0x2D] = (u8)(u32)state->blue;
            ((u8 *)arg0)[0x2E] = (u8)(u32)state->alpha;
        }
    }
}
typedef struct SightTwinPayload {
    u8 *owner;
    f32 value_04;
    f32 value_08;
    u8 flags;
    u8 selector;
    u8 reserved_0E[0x4A];
} SightTwinPayload;

typedef struct SightTwinSpawn {
    f32 x, y, z, value_0C;
    u8 kind;
    u8 reserved_11;
    s16 lifetime;
    u16 flags;
    s16 value_16;
    s16 value_18;
    u8 value_1A, red, green, blue;
    u8 value_1E, value_1F, value_20, value_21, value_22, value_23;
    s32 value_24;
    u32 value_28;
    s32 value_2C, value_30, value_34, value_38, value_3C;
    u8 value_40, value_41;
    u8 reserved_42[2];
    u8 value_44;
    u8 reserved_45[3];
    f32 value_48, value_4C, value_50, value_54;
} SightTwinSpawn;

extern f32 D_800AAEC4;
extern f32 D_800AAEC8;
extern f32 D_800AAECC;
extern f32 D_800AAED0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CC524 CURRENT (5208) */
void func_151CC524(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5) {
    SightTwinSpawn spawn;
    SightTwinPayload payload;
    u32 flags;
    void *object;

    payload.value_04 = 0.0f;
    payload.selector = 0;
    payload.flags = 0;
    spawn.value_50 = 0.0f;
    spawn.value_54 = 0.0f;
    spawn.lifetime = 300;
    payload.owner = (u8 *)arg0;
    payload.value_08 = 130.0f;
    if ((u8)arg4 != 0) {
        flags = 0x40;
    } else {
        flags = 0;
    }
    spawn.value_16 = 1;
    spawn.flags = flags | 0x390U |
                  (1U << ((((u8 *)arg0)[0x23D] + 11) & 31));
    spawn.red = (u8)arg1;
    spawn.green = (u8)arg2;
    spawn.value_1A = 7;
    spawn.value_1E = 0x82;
    spawn.value_1F = 255;
    spawn.value_20 = 255;
    spawn.value_21 = 255;
    spawn.blue = (u8)arg3;
    spawn.value_18 = 255;
    spawn.value_22 = 255;
    spawn.value_23 = 255;
    spawn.value_24 = 0;
    spawn.value_28 = 0x200004;
    spawn.value_2C = 0x1F0601;
    spawn.value_30 = 8;
    spawn.value_34 = 0x44;
    spawn.value_38 = 0x80;
    spawn.value_3C = 0x20;
    spawn.value_40 = 0;
    spawn.value_41 = 10;
    spawn.kind = 0x9A;
    spawn.x = 0.0f;
    spawn.value_48 = D_800AAEC4;
    spawn.value_44 = ((u8 *)arg0)[0x23D];
    spawn.value_4C = 1.0f;
    spawn.z = 28.0f;
    spawn.value_0C = D_800AAEC8;
    spawn.y = -37.0f;
    object = func_1515548C(&spawn, 9, 0, 0, 0x58, (u8)arg5, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
    spawn.kind = 0x9B;
    spawn.y = 0.0f;
    spawn.value_48 = 1.0f;
    spawn.value_4C = D_800AAECC;
    spawn.z = D_800AAED0;
    spawn.value_0C = 28.0f;
    spawn.x = -37.0f;
    object = func_1515548C(&spawn, 9, 0, 0, 0x58, (u8)arg5, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CC524 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC524.s")
void func_15145974(void *, f32 *, f32 *);
extern f32 D_800AAED4;
extern f32 D_800AAED8;

s32 func_151CC77C(void *arg0) {
    u8 *temp_a3;
    u8 *temp_v0;
    u8 *temp_v1;
    void *saved_arg0;
    f32 sp24;
    f32 sp20;
    f32 scaled;

    saved_arg0 = arg0;
    temp_a3 = *(u8 **)((u8 *)arg0 + 0x70);
    temp_v1 = *(u8 **)(temp_a3 + 0x3D0);
    if (temp_v1 == 0) {
        return 0;
    }
    temp_v0 = *(u8 **)(temp_v1 + 0x31C);
    if (temp_v0 == 0) {
        return 0;
    }
    func_15145974(temp_v0 + 0x130, &sp24, &sp20);
    if (*(u8 *)((u8 *)saved_arg0 + 0x20) == 0x9A) {
        scaled = -(sp24 * D_800AAED4 * 2560.0f);
        *(f32 *)((u8 *)saved_arg0 + 0x60) = 2.0f * scaled;
    } else {
        scaled = sp20 * D_800AAED8 * 2560.0f;
        *(f32 *)((u8 *)saved_arg0 + 0x64) = 2.0f * scaled;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC840.s")
typedef struct SightEffectPayload {
    void *owner;
    f32 zero;
    f32 scale;
    u8 bytes[2];
    u8 pad[0x4E];
} SightEffectPayload;

typedef struct SightEffectSpawn {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 type;
    u8 pad11;
    s16 angle;
    s16 flags;
    s16 count;
    s16 color;
    u8 mode;
    u8 arg1;
    u8 arg2;
    u8 arg3;
    u8 time;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3C;
    u8 field40;
    u8 field41;
    u8 pad42[2];
    u8 field44;
    u8 pad45[3];
} SightEffectSpawn;

void *func_1515548C(void *, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CCD1C CURRENT (2834) */
void func_151CCD1C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    SightEffectSpawn spawn;
    SightEffectPayload payload;
    void *object;

    payload.zero = 0.0f;
    payload.bytes[1] = 0;
    payload.bytes[0] = 0;
    spawn.angle = 0x12C;
    payload.owner = arg0;
    payload.scale = 130.0f;
    spawn.flags = (1 << (*(u8 *)((u8 *)arg0 + 0x23D) + 0xB)) | 0x50;
    spawn.count = 1;
    spawn.arg1 = arg1;
    spawn.arg2 = arg2;
    spawn.mode = 7;
    spawn.time = 0xB4;
    spawn.color0 = 0xFF;
    spawn.color1 = 0xFF;
    spawn.color2 = 0xFF;
    spawn.arg3 = arg3;
    spawn.color = 0xFF;
    spawn.color3 = 0xFF;
    spawn.color4 = 0xFF;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 8;
    spawn.field34 = 0x44;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 0xA;
    spawn.x = 0.0f;
    spawn.y = 0.0f;
    spawn.type = 0xB4;
    spawn.width = 65.0f;
    spawn.height = 65.0f;
    spawn.field44 = *(u8 *)((u8 *)arg0 + 0x23D);
    object = func_1515548C(&spawn, 0, 0, 0, 0x58, 0xFF, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CCD1C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCD1C.s")
typedef struct SightSpawnOwner {
    u8 pad0[0x23D];
    u8 type;
} SightSpawnOwner;

extern u8 D_800BE616;
void *func_10022EC0(void *, const void *, u32);

void func_151CCE94(SightSpawnOwner *arg0) {
    void *object;
    SightSpawnOwner *owner;

    if (D_800BE616 != 0) {
        owner = arg0;
        object = func_151A4FD0(0, 0, 0, 0xFF, 0, arg0->type, 1, 4);
        if (object != 0) {
            func_10022EC0((u8 *)object + 0x20, &owner, sizeof(owner));
        }
    }
}
typedef struct SightPanelColors {
    u8 values[4];
} SightPanelColors;

typedef struct SightPanelPayload {
    u8 *owner;
    f32 unk4;
    f32 unk8;
    u8 mode;
    u8 side;
    u8 padE[0xA];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8 pad24[0x30];
    s8 unk54;
    u8 pad55[3];
} SightPanelPayload;

typedef struct SightPanelSpawn {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    u8 type;
    u8 pad11;
    s16 angle;
    u16 flags;
    s16 count;
    s16 color;
    u8 mode;
    u8 arg1;
    u8 arg2;
    u8 arg3;
    u8 time;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3C;
    u8 field40;
    u8 field41;
    u8 pad42[2];
    u8 field44;
    u8 pad45[3];
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
} SightPanelSpawn;

extern SightPanelColors D_8008FC28;
extern f32 D_800AAD8C[];
extern f32 D_800AADB4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CCF08 CURRENT (3493) */
void func_151CCF08(s32 arg0, u8 arg1, s8 arg2, u8 arg3) {
    SightPanelSpawn spawn;
    SightPanelPayload payload;
    SightPanelColors colors;
    s32 select;
    u8 side;
    u8 slot;
    void *object;

    payload.unk1C = 0.0f;
    payload.owner = (u8 *)arg0;
    payload.unk4 = 0.0f;
    payload.unk18 = D_800AAD8C[D_80082FA0 == 1];
    payload.unk20 = D_800AADB4[D_80082FA0 == 1];
    payload.unk8 = 130.0f;
    if (arg2 == -1) {
        select = 0;
    } else {
        select = 4;
    }
    payload.mode = select;
    payload.unk54 = arg2;
    spawn.angle = 300;
    if (arg1) {
        select = 0x40;
    } else {
        select = 0;
    }
    spawn.mode = 7;
    spawn.arg1 = 255;
    spawn.flags = select | 0x30;
    spawn.count = 1;
    spawn.arg2 = 255;
    spawn.arg3 = 255;
    spawn.time = 255;
    spawn.color0 = 255;
    spawn.color = 255;
    spawn.color1 = 255;
    spawn.color2 = 255;
    spawn.color3 = 255;
    spawn.color4 = 255;
    spawn.field24 = 0;
    spawn.field28 = 0x200004;
    spawn.field2C = 0x1F0601;
    spawn.field30 = 8;
    spawn.field34 = 0x13;
    spawn.field38 = 0x80;
    spawn.field3C = 0x20;
    spawn.field40 = 0;
    spawn.field41 = 0;
    spawn.field50 = 0.0f;
    spawn.field54 = 0.0f;
    spawn.field48 = 1.0f;
    spawn.field4C = 1.0f;
    spawn.width = 35.75f;
    spawn.height = 16.0f;
    spawn.field44 = ((u8 *)arg0)[0x23D];
    for (side = 0; side < 2; side++) {
        colors = D_8008FC28;
        if (side) {
            spawn.y = 92.0f;
        } else {
            spawn.y = -90.0f;
        }
        if (side) {
            select = 4;
        } else {
            select = 0;
        }
        spawn.flags |= select;
        if (side) {
            payload.side = 5;
        } else {
            payload.side = 4;
        }
        for (slot = 0; slot < 4; slot++) {
            spawn.x = slot * 71.5f + 35.75f - 143.0f;
            spawn.type = colors.values[slot];
            object = func_1515548C(&spawn, 0xB, 0, 0, 0x58, arg3, 1);
            if (object != NULL) {
                func_10022EC0((u8 *)object + 0x70, &payload, 0x58);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CCF08 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCF08.s")
f32 func_151CC1D4(void *);                          /* extern */

typedef struct SightUpdateFields {
    u8 pad0[0xD];
    u8 mode;
    u8 padE[0xA];
    f32 start;
    u8 pad1C[4];
    f32 scale;
} SightUpdateFields;

void func_151CD224(u8 *arg0) {
    SightUpdateFields *state = (SightUpdateFields *)(arg0 + 0x70);
    f32 current;
    f32 offset;

    current = func_151CC1D4(arg0);
    offset = (1.0f - (current - state->start) * state->scale) * 75.0f;
    if (state->mode == 5) {
        *(f32 *)(arg0 + 0x14) = 92.0f + offset;
    } else if (state->mode == 4) {
        *(f32 *)(arg0 + 0x14) = -92.0f - offset;
    }
}
