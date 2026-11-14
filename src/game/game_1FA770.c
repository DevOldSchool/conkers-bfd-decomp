#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1FA770.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CD4C0
 * - func_151CD7BC
 * - func_151CDE20
 * - func_151CE51C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);

typedef struct Game1FA770Packet {
    void *field_0;
    s32 field_4;
    s32 field_8;
    s8 field_C;
    u8 padD[3];
} Game1FA770Packet;

s32 func_151CD2C0(void *arg0, u8 arg1, s32 arg2) {
    s32 result;
    Game1FA770Packet packet;

    packet.field_0 = arg0;
    packet.field_4 = *(s32 *)((u8 *)arg0 + 0x18);
    packet.field_8 = 0;
    packet.field_C = (s8) *(s32 *)((u8 *)arg0 + 0x1C);
    result = (s32)func_15149130(0x12C, -1, -1, -1, 0, 0x1E, 0x10, (s32) arg1, arg2);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &packet, 0x10);
    }
    return result;
}
void func_151CD35C(s32 arg0) {
    s32 sp1C;

    if ((arg0 >= 0) && (arg0 < 4)) {
        sp1C = arg0;
        func_151494E0(&sp1C, 0x17);
    }
}
void func_151CD394(s32 arg0) {
    s32 sp1C;

    if ((arg0 >= 0) && (arg0 < 4)) {
        sp1C = arg0;
        func_151494E0(&sp1C, 0x18);
    }
}
typedef struct Game1FA770DispatchState {
    void *object;
    s32 id;
    void *handle;
    u8 field_C;
} Game1FA770DispatchState;

typedef struct Game1FA770DispatchOwner {
    u8 pad0;
    u8 field_1;
    u8 pad2[0xA];
    u8 field_C;
    u8 padD[0x1B];
    Game1FA770DispatchState state;
} Game1FA770DispatchOwner;

s32 func_151CD4C0(void *, u8, s32, u8, s32);
typedef struct Game1FA770Object Game1FA770Object;
void func_151CE47C(Game1FA770Object *);

void func_151CD3CC(Game1FA770DispatchOwner *arg0, s32 *arg1, u8 arg2) {
    s32 event = arg2;
    Game1FA770DispatchState *state = &arg0->state;
    if (event == 0x17) {
        s32 id = state->id;

        if ((id == *arg1) && (state->handle == 0)) {
            state->handle = (void *)func_151CD4C0(state->object, state->field_C, id, arg0->field_C, arg0->field_1);
            *(s8 *)((u8 *)state->object + 0x14) = 0;
        }
    } else if (event == 0x18) {
        if (state->id == *arg1) {
            void *handle = state->handle;

            if (handle != 0) {
                func_151CE47C(handle);
            }
        }
    } else if ((event == 0x23) && (state->id == *arg1)) {
        state->handle = 0;
        *(s8 *)((u8 *)state->object + 0x14) = 1;
    }
}
typedef struct Game1CD4C0Source {
    s16 x;
    s16 y;
    s16 z;
    s16 vertical;
    s16 delta;
} Game1CD4C0Source;

typedef struct Game1CD4C0Locals {
    f32 values[18];
    s32 id;
    u8 shade;
    u8 pad4D[3];
    f32 position[3];
    s16 duration;
    s16 count;
    s32 mode;
    u8 layer;
    s8 kind;
    u8 pad66[2];
    s32 zero;
} Game1CD4C0Locals;

void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32,
                    s32, s32, s32);
extern f32 D_800AAFB4;
extern f32 D_800AAFB8;
extern f32 D_800AAFBC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD4C0 CURRENT (7714) */
s32 func_151CD4C0(void *arg0, u8 arg1, s32 arg2, u8 arg3,
                   s32 arg4) {
    Game1CD4C0Source *source;
    Game1CD4C0Locals locals;
    f32 vertical;
    void *result;

    source = arg0;
    locals.kind = 0x23;
    vertical = (f32)source->vertical;
    locals.position[0] = (f32)source->x;
    locals.position[1] = (f32)(source->y + source->delta);
    locals.duration = 0x12C;
    locals.count = 0x34;
    locals.mode = 0xB;
    locals.position[2] = (f32)source->z;
    locals.values[9] = vertical * 0.875f;
    locals.values[4] = D_800AAFB4;
    locals.values[0] = vertical * 0.125f;
    locals.values[1] = locals.values[0];
    locals.values[5] = D_800AAFB8;
    locals.values[2] = 0.0f;
    locals.values[17] = (f32)source->y;
    locals.values[3] = 0.0f;
    locals.values[6] = locals.position[0];
    locals.values[7] = locals.position[2];
    locals.values[13] = locals.values[9];
    locals.values[10] = vertical * 0.0625f;
    locals.values[11] = 0.0f;
    locals.values[12] = D_800AAFBC;
    locals.values[16] = 0.0f;
    locals.id = arg2;
    locals.values[14] = -16384.0f;
    locals.values[15] = -16384.0f;
    locals.values[8] = 0.0f;
    locals.shade = arg1;
    locals.zero = 0;
    locals.layer = 7;
    result = func_15147A80(locals.position, (void *)0x50, 0x1C,
                           9, 9, 9, 0, 0, 0, arg3, arg4);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x98), locals.values, 0x50);
    }
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD4C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD4C0.s")
typedef struct Game1FA770Particle {
    f32 x;
    f32 y;
    u8 pad08[4];
    f32 velocity;
    u8 pad10[0xC];
} Game1FA770Particle;

extern f32 D_800BE9A4;

s32 func_151CD674(u8 *actor) {
    u8 *owner;
    Game1FA770Particle *particles;
    Game1FA770Particle *particle;
    s32 cursor;
    f32 velocity;
    f32 gravity;
    f32 acceleration;
    f32 step;
    f32 travel;
    f32 squared;

    owner = *(u8 **)(actor + 0x98);
    particles = *(Game1FA770Particle **)(actor + 0x94);
    if ((*(s8 *)(actor + 0x2C) < 2) && (*(u16 *)(actor + 0x1E) & 8)) {
        return 0;
    }
    cursor = *(s8 *)(actor + 0x2E);
    if (cursor != *(s8 *)(actor + 0x2D)) {
        gravity = -0.25500003f;
        acceleration = -0.12750001f;
        do {
            cursor--;
            if (cursor < 0) {
                cursor = actor[0x25] - 1;
            }
            particle = &particles[cursor];
            velocity = particle->velocity;
            step = D_800BE9A4;
            travel = velocity * step;
            squared = step * step;
            particle->y = particle->y + (travel + acceleration * squared);
            particle->velocity = (f32)velocity + gravity * D_800BE9A4;
            if (particle->y < *(f32 *)(owner + 0x44)) {
                if (cursor != *(s8 *)(actor + 0x2D)) {
                    do {
                        *(s8 *)(actor + 0x2D) += 1;
                        if (actor[0x25] == *(s8 *)(actor + 0x2D)) {
                            *(s8 *)(actor + 0x2D) = 0;
                        }
                        *(s8 *)(actor + 0x2C) -= 1;
                    } while (cursor != *(s8 *)(actor + 0x2D));
                }
                particles[*(s8 *)(actor + 0x2D)].y = *(f32 *)(owner + 0x44);
            }
        } while (cursor != *(s8 *)(actor + 0x2D));
    }
    *(Vec3i *)(actor + 0x54) = *(Vec3i *)(actor + 0x10);
    return 1;
}
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_150ADA68();                                /* extern */
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800AAFC8;
extern f32 D_800AAFCC;
extern f32 D_800AAFD0;
extern f32 D_800AAFD4;
extern f32 D_800AAFD8;
extern f32 D_800AAFDC;
extern f32 D_800AAFE0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CD7BC CURRENT (5037) */
s32 func_151CD7BC(u8 *arg0) {
    typedef struct { f32 x, z; } Position;
    Position position;
    volatile f32 spB0;
    volatile f32 spAC;
    volatile f32 spA8;
    volatile f32 sp90;
    volatile f32 sp84;
    u8 *sp6C;
    f32 stepX;
    f32 stepZ;
    f32 stepPhase;
    f32 stepAngle;
    f32 gravity;
    f32 acceleration;
    f32 baseVelocity;
    f32 step;
    f32 result;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    u8 *temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_s3 = *(u8 **)((u8 *)arg0 + 0x94);
    *(f32 *)((u8 *)temp_s1 + 8) = (f32) (*(f32 *)((u8 *)temp_s1 + 8) + (*(f32 *)((u8 *)temp_s1 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s1 + 0xC) + (*(f32 *)((u8 *)temp_s1 + 0x14) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 8));
    *(f32 *)((u8 *)temp_s1 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 0xC));
    *(f32 *)((u8 *)temp_s1 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x2C) + (*(f32 *)((u8 *)temp_s1 + 0x30) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0x2C) = func_15144B68(*(f32 *)((u8 *)temp_s1 + 0x2C));
    *(f32 *)((u8 *)temp_s1 + 0x40) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x40) + (D_800AAFC8 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s1 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x3C) + ((D_800AAFCC + (func_150ADA68() * D_800AAFD0)) * D_800AAFD4 * D_800BE9A4));
    if (*(f32 *)((u8 *)temp_s1 + 0x3C) >= 16384.0f) {
        do {
            *(f32 *)((u8 *)temp_s1 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x3C) - 16384.0f);
        } while (*(f32 *)((u8 *)temp_s1 + 0x3C) >= 16384.0f);
    }
    temp_fv0 = *(f32 *)((u8 *)temp_s1 + 0x40);
    if (temp_fv0 > 1.0f) {
        temp_fs4 = 1.0f / temp_fv0;
        temp_v0 = (void *)(temp_s1 + 0x18);
        temp_ft4 = *(f32 *)((u8 *)temp_s1 + 0x20) + D_800BE9A4;
        spAC = -(temp_ft4 * temp_fs4);
        position = *(Position *)(temp_s1 + 0x18);
        spB0 = temp_ft4;
        sp6C = temp_v0;
        temp_fs5 = ((func_15047D60(*(f32 *)((u8 *)temp_s1 + 8)) * *(f32 *)((u8 *)temp_s1 + 0)) + *(f32 *)((u8 *)arg0 + 0x10)) - *(f32 *)((u8 *)temp_s1 + 0x18);
        spA8 = ((func_15047D60(*(f32 *)((u8 *)temp_s1 + 0xC)) * *(f32 *)((u8 *)temp_s1 + 4)) + *(f32 *)((u8 *)arg0 + 0x18)) - *(f32 *)((u8 *)temp_s1 + 0x1C);
        result = func_15047D60(*(f32 *)(temp_s1 + 0x2C));
        var_fa0 = *(f32 *)(temp_s1 + 0x34);
        var_ft4 = spB0;
        temp_ft2 = ((result * *(f32 *)(temp_s1 + 0x28)) + *(f32 *)(temp_s1 + 0x24)) - var_fa0;
        sp90 = temp_ft2;
        var_fa1 = *(f32 *)((u8 *)temp_s1 + 0x3C);
        sp84 = var_fa1 - *(f32 *)((u8 *)temp_s1 + 0x38);
        if (*(f32 *)((u8 *)temp_s1 + 0x40) > 1.0f) {
            stepX = temp_fs5 * temp_fs4;
            stepZ = spA8 * temp_fs4;
            stepPhase = sp90 * temp_fs4;
            stepAngle = sp84 * temp_fs4;
            gravity = D_800AAFD8;
            acceleration = D_800AAFDC;
            baseVelocity = D_800AAFE0;
            do {
                temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x1C) + temp_s3);
                *(f32 *)((u8 *)temp_v0_2 + 0) = position.x;
                *(f32 *)((u8 *)temp_v0_2 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
                *(f32 *)((u8 *)temp_v0_2 + 0xC) = baseVelocity;
                *(f32 *)((u8 *)temp_v0_2 + 0x10) = var_fa0;
                *(s16 *)((u8 *)temp_v0_2 + 0x14) = 0xFF;
                *(f32 *)((u8 *)temp_v0_2 + 0x18) = var_fa1;
                *(f32 *)((u8 *)temp_v0_2 + 8) = position.z;
                var_fa0 += stepPhase;
                var_fa1 += stepAngle;
                step = D_800BE9A4;
                *(f32 *)(temp_v0_2 + 4) = *(f32 *)(temp_v0_2 + 4) + ((baseVelocity * step) + (acceleration * (step * step)));
                *(f32 *)(temp_v0_2 + 0xC) = baseVelocity + (gravity * D_800BE9A4);
                *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                    *(s8 *)((u8 *)arg0 + 0x2E) = 0;
                }
                temp_v1 = *(s8 *)((u8 *)arg0 + 0x2D);
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
                if (temp_v1 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v1 + 1);
                    if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                        *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                    }
                    *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
                }
                position.x += stepX;
                var_ft4 += spAC;
                position.z += stepZ;
                *(f32 *)((u8 *)temp_s1 + 0x40) = (f32) (*(f32 *)((u8 *)temp_s1 + 0x40) - 1.0f);
            } while (*(f32 *)((u8 *)temp_s1 + 0x40) > 1.0f);
        }
        *(Position *)sp6C = position;
        *(f32 *)((u8 *)temp_s1 + 0x34) = var_fa0;
        *(f32 *)((u8 *)temp_s1 + 0x38) = var_fa1;
        *(f32 *)((u8 *)temp_s1 + 0x20) = var_ft4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CD7BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD7BC.s")

f32 fabsf(f32);
#pragma intrinsic (fabsf)

s32 func_151CDB94(void *arg0) {
    u8 *base;
    s32 prev;
    s32 i;
    u8 *first;
    u8 *entry;
    f32 span;
    f32 inv;
    f32 diff;
    f32 scale;
    f32 ratio;

    base = *(u8 **)((u8 *)arg0 + 0x94);
    if (*(s8 *)((u8 *)arg0 + 0x2C) <= 0) {
        return 1;
    }
    prev = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
    if (prev < 0) {
        prev = *(u8 *)((u8 *)arg0 + 0x25) - 1;
    }
    first = *(s8 *)((u8 *)arg0 + 0x2D) * 0x1C + base;
    span = fabsf(*(f32 *)(prev * 0x1C + base + 4) - *(f32 *)(first + 4));
    if (span == 0.0f) {
        return 1;
    }
    inv = 1.0f / span;
    scale = inv * 10.0f;
    i = *(s8 *)((u8 *)arg0 + 0x2D);
    do {
        entry = i * 0x1C + base;
        diff = *(f32 *)(entry + 4) - *(f32 *)(first + 4);
        *(s16 *)(entry + 0x14) = 0xFF;
        if (diff < span * 0.19700001f) {
            ratio = inv * 5.076142f;
            *(s16 *)(entry + 0x14) = (u32)(diff * ratio * 255.0f) & 0xFF;
        } else if (span - span * 0.1f < diff) {
            *(s16 *)(entry + 0x14) = (u32)((span - diff) * scale * 255.0f) & 0xFF;
        }
        i++;
        if (i >= *(u8 *)((u8 *)arg0 + 0x25)) {
            i = 0;
        }
    } while (i != *(s8 *)((u8 *)arg0 + 0x2E));
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDE20.s")
struct Game1FA770Object {
    u8 pad0[0x1E];
    volatile u16 flags;
    u8 pad20[0x10];
    s8 field_30;
};

void func_151CE47C(Game1FA770Object *arg0) {
    arg0->field_30 = 0;
    *(u16 *)&arg0->flags &= 0xFFFD;
    arg0->flags = *(u16 *)&arg0->flags | 8;
}
void func_151CE49C(void *arg0) {
    s32 sp1C;
    u8 *state;

    state = *(u8 **)((u8 *)arg0 + 0x98);
    sp1C = *(s32 *)(state + 0x48);
    func_151494E0(&sp1C, 0x23);
    func_151478F4(arg0);
}
void func_151CE4DC(void *arg0) {
    s32 sp1C;
    u8 *state;

    state = *(u8 **)((u8 *)arg0 + 0x98);
    sp1C = *(s32 *)(state + 0x48);
    func_151494E0(&sp1C, 0x23);
    func_15147928(arg0);
}
typedef struct {
    f32 x;
    f32 y;
} Game1FA770Vec2;

void *func_151CE634(s32);
void func_1515C1A0(void *, void *, f32 *, f32 *);
s32 func_1505D024(void *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE51C CURRENT (1718) */
void func_151CE51C(void *arg0, void *arg1) {
    Game1FA770Vec2 sp44;
    f32 sp40;
    f32 sp3C;
    void *sp38;
    s32 var_v0;
    u8 *temp_v0;

    temp_v0 = func_151CE634(*(s32 *)((u8 *)arg1 + 0x18));
    if (temp_v0 != 0) {
        sp38 = temp_v0;
        func_1515C1A0(arg0, &sp44, &sp40, &sp3C);
        if (*(u16 *)(temp_v0 + 0x1E) & 8) {
            if (*(s8 *)(temp_v0 + 0x2C) > 0) {
                var_v0 = *(s8 *)(temp_v0 + 0x2E) - 1;
                if (var_v0 < 0) {
                    var_v0 = temp_v0[0x25] - 1;
                }
                if ((sp44.y - sp3C) <=
                    *(f32 *)(*(u8 **)(temp_v0 + 0x94) + (var_v0 * 0x1C) + 4)) {
                    func_1505D024(arg0, 0x60019, 0, -1);
                }
            }
        } else if ((*(s8 *)(temp_v0 + 0x2C) > 0) &&
                   (*(f32 *)(*(u8 **)(temp_v0 + 0x94) +
                              (*(s8 *)(temp_v0 + 0x2D) * 0x1C) + 4) <=
                    (sp44.y + sp3C))) {
            func_1505D024(arg0, 0x60019, 0, -1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE51C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE51C.s")
extern s32 D_800A5760[];
extern u8 D_800DCE50[];
extern u8 D_800DD190[];

void *func_151CE634(s32 arg0) {
    u8 i;
    s32 j;
    u8 *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (node = ((u8 **)&D_800DCE50[j * 0x1A0])[D_800A5760[i]]; node != 0; node = *(u8 **)(node + 8)) {
                if (*(s32 *)(node + 0x20) == 0xB) {
                    u8 *owner = *(u8 **)(node + 0x98);

                    if (arg0 == *(s32 *)(owner + 0x48)) {
                        return node;
                    }
                }
            }
        }
    }
    return 0;
}
