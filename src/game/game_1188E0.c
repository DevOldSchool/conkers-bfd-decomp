#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1188E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EB484
 * - func_150EB614
 * - func_150EB8C4
 * - func_150EBC80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1188E0Vector;

s32 func_150EB484(Game1188E0Vector *, f32 *, void *);

void func_150EB430(Game1188E0Vector *arg0, Game1188E0Vector *arg1, void *arg2) {
    f32 sp1C[3];
    Game1188E0Vector *temp_a3 = arg1;

    sp1C[0] = arg0->x + temp_a3->x;
    sp1C[1] = arg0->y + temp_a3->y;
    sp1C[2] = arg0->z + temp_a3->z;
    func_150EB484(arg0, sp1C, arg2);
}
void func_150A2864(s32, s32);
void *func_15083E90(s32);
s32 func_150A34B0(void *, Game1188E0Vector *, f32 *, void *);
void func_150EBC80(void *, u8, s32);
extern s32 D_80088AA0[];
extern s32 D_80088AB0[];
extern s32 D_80088AD0;
extern u8 *D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EB484 CURRENT (550) */
s32 func_150EB484(Game1188E0Vector *arg0, f32 *arg1, void *arg2) {
    u8 *spawned;
    s32 *index_ptr;
    s32 *alternate_ptr;
    s32 index;
    s32 id;
    s32 offset;

    spawned = func_15083E90(9);
    if (spawned != 0) {
        index_ptr = D_80088AA0;
        index = 0;
        do {
            id = *index_ptr;
            offset = id * 0x34;
            if (func_150A34B0(D_800D3098 + offset, arg0, arg1, arg2) != 0) {
                func_150A2864(id, 1);
                *(s32 *)(spawned + 0x2E8) = index + 1;
                func_150EBC80(D_800D3098 + offset, 0xFF, 1);
                return 1;
            }
            index++;
            index_ptr++;
        } while (index < 4);
        alternate_ptr = D_80088AB0;
        do {
            if (func_150A34B0(D_800D3098 + (*alternate_ptr * 0x34),
                               arg0, arg1, arg2) != 0) {
                return 1;
            }
            alternate_ptr++;
        } while (alternate_ptr != &D_80088AD0);
        return 0;
    }
    if (func_150A34B0(D_800D3098 + 0xF70, arg0, arg1, arg2) != 0) {
        *(s32 *)(D_800D3098 + 0xF88) = 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EB484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB484.s")
typedef struct Game1188E0ChildB614 {
    u8 pad0[0x57];
    u8 enabled;
} Game1188E0ChildB614;
typedef struct Game1188E0OwnerB614 {
    u8 pad0[0x14];
    Game1188E0Vector position;
    u8 pad20[0x2FC];
    Game1188E0ChildB614 *child;
} Game1188E0OwnerB614;
typedef struct Game1188E0StateB614 {
    f32 angle;
    u8 pad4[0xC];
    s16 x, y, z;
    u8 pad16[0x26];
    s32 packedTarget;
    u8 pad40[0xF];
    u8 flags;
    u8 pad50[0x23];
    volatile u8 mode;
    u8 pad74[8];
    f32 damping, acceleration, velocity;
} Game1188E0StateB614;

f32 func_15048A70(f32, f32);
void func_15117770(f32 *);
f32 sqrtf(f32);
f32 fabsf(f32);
#pragma intrinsic(sqrtf, fabsf)
extern Game1188E0OwnerB614 D_800CC2D0;
extern f32 D_800A14DC, D_800A14E0, D_800A14E4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EB614 CURRENT (466) */
void func_150EB614(f32 *arg0) {
    register Game1188E0StateB614 *state;
    f32 before;
    f32 angle;
    f32 acceleration, damping;
    f32 target, velocity;
    register f32 dx, dy, dz, distance, delta, magnitude;
    register s32 flags;
    u8 masked;

    state = (void *)arg0;
    flags = state->mode;
    if ((flags & 3) != 3) {
        if ((flags & 3) != 2) {
            if (state->flags & 4) {
                masked = flags & 0xFFFC;
                if (D_800CC2D0.child->enabled != 0) {
                    state->mode = masked;
                    state->mode = masked | 2;
                    state->packedTarget = 0;
                    state->damping = 0.5f;
                    state->acceleration = D_800A14DC;
                    state->velocity = 0.0f;
                }
                dz = (f32)state->z - D_800CC2D0.position.z;
                dx = (f32)state->x - D_800CC2D0.position.x;
                dy = (f32)state->y - D_800CC2D0.position.y;
                distance = sqrtf(dz * dz + (dx * dx + dy * dy));
                if (distance > 740.0f) {
                    distance = 740.0f;
                }
                target = distance * D_800A14E0 + -40.0f;
            } else {
                target = -40.0f;
            }
            angle = state->angle;
            damping = state->damping;
            acceleration = state->acceleration;
            velocity = state->velocity;
            if (angle != target || velocity != 0.0f) {
                angle += velocity * (f32)D_800BE9E4;
                delta = func_15048A70(angle, target);
                magnitude = fabsf(delta);
                if (delta > 0.0f) {
                    velocity += magnitude * acceleration;
                } else {
                    velocity -= magnitude * acceleration;
                }
                velocity *= damping;
                if (fabsf(delta) < D_800A14E4 && fabsf(velocity) < D_800A14E4) {
                    velocity = 0.0f;
                    angle = target;
                } else if (angle < 0.0f) {
                    angle += 360.0f;
                } else if (angle >= 360.0f) {
                    angle -= 360.0f;
                }
                state->velocity = velocity;
            }
            state->angle = angle;
            return;
        }
        before = state->angle;
        func_15117770(arg0);
        if (before == state->angle) {
            masked = state->mode & 0xFFFC;
            state->mode = masked;
            state->mode = masked | 3;
            state->angle = 0.0f;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EB614 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB614.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EB8C4.s")
typedef struct Game1188E0Event {
    u8 type;
    u8 pad1;
    s16 duration;
    u8 field4;
    u8 field5;
    s8 field6;
    u8 pad7;
} Game1188E0Event;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150E83AC(void *, s16, u8, s32);
void *func_151D8868(void *, s32, u8, s32);
void *func_15164F0C(u8, u8, void *, u8, s32);
void func_151D5514(void *, u8, s32);
void *func_151541B8(void *, f32, f32, f32, f32, u8, s32);
extern f32 D_800A14FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EBC80 CURRENT (130) */
void func_150EBC80(void *arg0, u8 arg1, s32 arg2) {
    Game1188E0Vector position;
    f32 random;
    f32 step;
    Game1188E0Event event;
    f32 scale;
    u8 index;

    position.x = ((s16 *)arg0)[0];
    position.y = ((s16 *)arg0)[1];
    position.z = ((s16 *)arg0)[2];
    step = ((s16 *)arg0)[4] * 0.5f;
    func_150E83AC(&position, (s16)((func_150ADA20() % 101U) + 0x12C),
                  arg1, arg2);
    event.type = 1;
    event.duration = (func_150ADA20() % 21U) + 0xF;
    event.field4 = 0;
    event.field6 = -1;
    event.field5 = 1;
    func_151D8868(&event, 0, arg1, arg2);
    func_15164F0C(0, 0, 0, arg1, arg2);
    scale = D_800A14FC;
    index = 0;
    do {
        func_151D3FF4(&position, arg1, arg2);
        func_151D5514(&position, arg1, arg2);
        random = func_150ADA68();
        func_151541B8(&position, random * 4.0f + 12.0f, scale,
                     (f32)((func_150ADA20() % 56U) + 0xC8), 0.0f, arg1, arg2);
        index++;
        position.y += step;
    } while (index < 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EBC80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1188E0/func_150EBC80.s")
