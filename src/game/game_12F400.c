#include "types.h"

/*
 * Reviewed source unit: src/game/game_12F400.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151022AC
 * - func_151025F4
 * - func_151026BC
 * - func_151028AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15144E80(void *, void *, void *, void *);
void func_151D5D60(void *, s16, s32, void **, u8 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);

void *func_15101F50(u8 *arg0, s32 arg1) {
    u8 *source;
    void *vertices;
    void *result;
    f32 first[3];
    f32 second[3];
    u8 fresh;
    u8 *slot;

    func_151D5D60(arg0 + 0x100, ((s16 *)&arg1)[1], 0x40, &vertices, &fresh);
    result = vertices;
    if (vertices != NULL) {
        if (fresh != 0) {
            slot = arg0;
            slot += ((s16 *)&arg1)[1] * 4;
            source = arg0 + 0xC0;
            func_10022EC0(*(void **)(slot + 0x100), source, 0x40U);
            func_10022EC0(*(u8 **)(slot + 0x100) + 0x40, source, 0x40U);
        }
    } else {
        return NULL;
    }
    {
        if (!(arg0[0x110] & 1)) {
            return NULL;
        }
        if (func_15144E80(arg0 + 0x112, first, second, NULL) == 0) {
            return NULL;
        }
        func_15145128(first, first, NULL, NULL);
        func_15145128(second, second, NULL, NULL);
        first[0] *= *(f32 *)(arg0 + 0x2C);
        first[1] *= *(f32 *)(arg0 + 0x2C);
        first[2] *= *(f32 *)(arg0 + 0x2C);
        second[0] *= *(f32 *)(arg0 + 0x30);
        second[1] *= *(f32 *)(arg0 + 0x30);
        second[2] *= *(f32 *)(arg0 + 0x30);
        ((s16 *)vertices)[0] = (s32)(second[0] + (*(f32 *)(arg0 + 0x34) - first[0]));
        ((s16 *)vertices)[1] = (s32)(second[1] + (*(f32 *)(arg0 + 0x38) - first[1]));
        ((s16 *)vertices)[2] = (s32)(second[2] + (*(f32 *)(arg0 + 0x3C) - first[2]));
        ((s16 *)vertices)[3] = 0;
        ((s16 *)vertices)[8] = (s32)(second[0] + (first[0] + *(f32 *)(arg0 + 0x34)));
        ((s16 *)vertices)[9] = (s32)(second[1] + (first[1] + *(f32 *)(arg0 + 0x38)));
        ((s16 *)vertices)[10] = (s32)(second[2] + (first[2] + *(f32 *)(arg0 + 0x3C)));
        ((s16 *)vertices)[11] = 0;
        ((s16 *)vertices)[16] = (s32)((*(f32 *)(arg0 + 0x34) + first[0]) - second[0]);
        ((s16 *)vertices)[17] = (s32)((*(f32 *)(arg0 + 0x38) + first[1]) - second[1]);
        ((s16 *)vertices)[18] = (s32)((*(f32 *)(arg0 + 0x3C) + first[2]) - second[2]);
        ((s16 *)vertices)[19] = 0;
        ((s16 *)vertices)[24] = (s32)((*(f32 *)(arg0 + 0x34) - first[0]) - second[0]);
        ((s16 *)vertices)[25] = (s32)((*(f32 *)(arg0 + 0x38) - first[1]) - second[1]);
        ((s16 *)vertices)[26] = (s32)((*(f32 *)(arg0 + 0x3C) - first[2]) - second[2]);
        ((s16 *)vertices)[27] = 0;
        return result;
    }
}
typedef struct Game12F400Animation {
    u8 pad0[0x24];
    u8 *linked24, *linked28, *linked2C;
    u8 pad30[4];
    u8 *linked34;
    f32 field38, field3C, field40;
    u8 pad44[0xC];
    f32 angle, rate, rotation, velocity, targetVelocity, velocityRange;
    f32 timer, timerRange, velocityBlend;
    f32 alpha, targetAlpha, alphaBase, alphaRange, alphaTimer, alphaTimerRange, alphaBlend;
} Game12F400Animation;

f32 func_15144B68(f32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800BE9A4, D_800A228C, D_800A2290, D_800A2294;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151022AC CURRENT (1982) */
s32 func_151022AC(u8 *arg0) {
    u8 *scaleLink;
    u8 *particleLink;
    Game12F400Animation *state;
    u8 *link;
    u32 alpha;
    f32 upperBound;

    state = (Game12F400Animation *)(arg0 + 0x110);
    *(f32 *)(arg0 + 0x160) += *(f32 *)(arg0 + 0x164) * D_800BE9A4;
    state->angle = func_15144B68(*(f32 *)(arg0 + 0x160));
    upperBound = D_800A228C;
    state->rotation += state->velocity * D_800BE9A4;
    while (upperBound < state->rotation) {
        state->rotation -= 65536.0f;
    }
    while (state->rotation < -32768.0f) {
        state->rotation += 65536.0f;
    }
    state->timer -= D_800BE9A4;
    if (state->timer < 0.0f) {
        state->timer = func_150ADA68() * state->timerRange;
        state->targetVelocity = func_150ADA68() * (2.0f * state->velocityRange) - state->velocityRange;
    }
    state->velocity += (state->targetVelocity - state->velocity) * state->velocityBlend;
    state->field38 += (state->field3C - state->field38) * state->field40;
    link = state->linked28;
    if (link != NULL) {
        scaleLink = link;
        *(f32 *)(scaleLink + 0x2C) = *(f32 *)(scaleLink + 0x30) =
            (func_150ADA68() * D_800A2290 + D_800A2294) * state->field38;
    }
    state->alphaTimer -= D_800BE9A4;
    if (state->alphaTimer < 0.0f) {
        state->alphaTimer = func_150ADA68() * state->alphaTimerRange;
        state->targetAlpha = func_150ADA68() * state->alphaRange + state->alphaBase;
    }
    state->alpha += (state->targetAlpha - state->alpha) * state->alphaBlend;
    alpha = (u32)state->alpha;
    arg0[0x5C] = alpha;
    link = state->linked28;
    if (link != NULL) {
        link[0x5C] = alpha;
    }
    link = state->linked24;
    if (link != NULL) {
        link[0x2B] = arg0[0x5C];
    }
    link = state->linked2C;
    if (link != NULL) {
        particleLink = link;
        (*(u8 **)(particleLink + 0x14))[0x2F] = (func_150ADA20() & 3) + 2;
    }
    link = state->linked34;
    if (link != NULL) {
        state = (Game12F400Animation *)link;
        state->field38 = state->field3C = func_150ADA68() * 10.0f + 120.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151022AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151022AC.s")

/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151025F4 CURRENT (2008) */
s32 func_151025F4(u8 *arg0, s32 arg1) {
    f32 first;
    f32 second;
    f32 *state;

    first = func_15047D60(*(f32 *)(arg0 + 0xC0));
    state = (f32 *)(arg0 + 0xA8);
    second = func_15047D60(state[7]);
    state[0] = state[2] + state[4] * first;
    state[1] = state[3] + state[5] * second;
    state[6] += state[8] * D_800BE9A4;
    state[7] += state[9] * D_800BE9A4;
    state[6] = func_15144B68(state[6]);
    state[7] = func_15144B68(state[7]);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151025F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151025F4.s")
typedef struct {
    u8 pad0[0x78];
    u8 field78;
} Game12F400Inner;

typedef struct {
    u8 pad0[4];
    u8 type;
    u8 pad5[0x317];
    Game12F400Inner *inner;
} Game12F400Object;

s32 func_15100600(void *, void *, void *, u8, s32, s32, s32, s32, f32, f32, f32, f32, s32, s32, s32);
extern u8 D_800A21A0[];
extern u8 D_800A21F4[];
extern u8 D_800A2248[];
extern f32 D_800A233C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151026BC CURRENT (600) */
s32 func_151026BC(Game12F400Object *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    s32 offset;
    s32 var_t0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg0->type) {
    case 0x58:
    case 0x5B:
    case 0x80:
        var_v1 = 0x32;
        var_t0 = 0xFF;
        break;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        var_v1 = 0xFF;
        var_t0 = 0;
        break;
    default:
        var_v1 = 0x32;
        var_t0 = 0xFF;
        if (arg0->inner->field78 != 0x3B) {
            break;
        }
        var_v1 = 0xFF;
        var_t0 = 0;
        break;
    }
    offset = arg2 * 0xC;
    return func_15100600(arg0, D_800A21A0 + offset, D_800A21F4 + offset, D_800A2248[arg2],
                         arg1, var_v1, var_t0, 0, 20.0f, (f32) 20, 4.0f, D_800A233C,
                         arg3, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151026BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151026BC.s")
void func_151403A8();

void func_151027E8(void *arg0) {
    struct {
        void *sp18;
        u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151403A8(&sp.sp18, 0x1A, arg0);
}
typedef struct Game12F400DeepState {
    u8 pad0[0x197];
    u8 active;
} Game12F400DeepState;

typedef struct Game12F400LinkedState {
    u8 pad0[0x31C];
    Game12F400DeepState *deep;
} Game12F400LinkedState;

typedef struct Game12F400ControlState {
    u8 pad0[0x110];
    Game12F400LinkedState *linked;
    u8 pad114[0x1E];
    u8 selector;
} Game12F400ControlState;

typedef struct Game12F400State {
    u8 pad0[0xD0];
    Game12F400ControlState *control;
    u8 flags;
} Game12F400State;

s32 func_1510281C(Game12F400State *arg0, s16 arg1) {
    Game12F400LinkedState **temp_v0;
    Game12F400LinkedState *temp_v1;

    temp_v0 = (Game12F400LinkedState **)((u8 (*)[1])arg0->control)[0x110];
    if (arg1 == *(u8 *)((u8 *)temp_v0 + 0x22)) {
        temp_v1 = *temp_v0;
        if ((temp_v1 == 0) || (temp_v1->deep->active != 0)) {
            return 0;
        }
    }
    if (!(arg0->flags & 1)) {
        return 0;
    }
    return 1;
}
s32 func_15102884(void *arg0, s32 arg1) {
    if (!(*(u8 *)((u8 *)arg0 + 0xAC) & 1)) {
        return 0;
    }
    return 1;
}

typedef struct Game12F400WideState {
    u8 pad0[0x170];
    Game12F400ControlState *control;
    u8 flags;
} Game12F400WideState;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151028AC CURRENT (460) */
s32 func_151028AC(Game12F400WideState *arg0, s16 arg1) {
    Game12F400ControlState *control = arg0->control;
    Game12F400LinkedState *linked;
    u8 selector = control->selector;

    control = (Game12F400ControlState *)((u8 *)control + 0x110);
    if (arg1 == selector) {
        linked = *(Game12F400LinkedState **)control;
        if ((linked == 0) || (linked->deep->active != 0)) {
            return 0;
        }
    }
    if (!(arg0->flags & 1)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151028AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151028AC.s")
