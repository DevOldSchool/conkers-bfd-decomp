#include "types.h"

/*
 * Reviewed source unit: src/game/game_14F130.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15121C80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game14F130Vector { s32 x, y, z; } Game14F130Vector;
typedef struct Game14F130Actor {
    u8 pad00[0x40];
    f32 yaw;
    u8 pad44[0x38];
    u16 angle;
    u8 pad7E[0x266];
    s32 rotation;
} Game14F130Actor;
typedef struct Game14F130Target {
    u8 pad00[0x12];
    s16 angle;
    u8 pad14[0x14C];
    Game14F130Vector position;
    u8 pad16C[0x20];
    f32 yaw;
    u8 pad190[0x23];
    u8 enabled;
} Game14F130Target;
typedef struct Game14F130Camera {
    u8 pad00[0x84];
    s32 flags84;
    u8 pad88[0x1B4];
    u8 instant;
    u8 pad23D;
    u8 mode;
    u8 pad23F[0xB9];
    Game14F130Vector position, previousPosition;
    u8 pad310[0x5C];
    u16 *controls;
    u8 pad370[0xC];
    f32 yaw;
    u8 pad380[0x1C];
    f32 yawRadians;
    u8 pad3A0[0x30];
    Game14F130Actor *actor;
    Game14F130Target *target;
    u8 pad3D8[0x218];
    s32 flags5F0;
    u8 pad5F4[0xC];
    u8 fast;
    u8 pad601[0x97];
    s32 locked;
    u8 pad69C[0x118];
    f32 delta;
    u8 pad7B8[0x10];
    f32 yawVelocity;
    u8 pad7CC[0x1A0];
    f32 speed, limit;
    u8 pad974[8];
    f32 targetSpeed, targetLimit;
    u8 pad984[8];
    f32 speedVelocity, limitVelocity;
} Game14F130Camera;

void func_15048758(f32 *);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_15049688(void *, f32, void *, f32, f32, f32);
void func_1512E140(void *);
void func_15123A54(void *);
void func_1512A390(void *);
extern f32 D_800A3440, D_800A3444, D_800A3448;
extern f32 D_800A344C, D_800A3450, D_800A3454;
extern u8 D_800BE616, D_800BEA0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15121C80 CURRENT (8) */
void func_15121C80(Game14F130Camera *arg0, f32 arg1) {
    f32 angle;
    f32 speed;
    f32 limit;
    s32 active;
    s32 mode;
    Game14F130Vector position;

    active = (arg0->flags5F0 & 0x10) != 0;
    if (active != 0) {
        active = (*arg0->controls & 0x10) != 0;
    }
    if (active == 0 && (D_800BE616 != 0 || (mode = arg0->mode) == 9 || mode == 0x3B) && arg0->target->enabled != 0) {
        if (D_800BE616 != 0) {
            arg0->targetSpeed = 5.0f;
            arg0->targetLimit = 8.0f;
            func_150495B0(&arg0->speed, 5.0f, &arg0->speedVelocity, 1.0f, 2.0f, arg0->delta);
            func_150495B0(&arg0->limit, arg0->targetLimit, &arg0->limitVelocity, 1.0f, 2.0f, arg0->delta);
            func_15049688(&arg0->yaw, arg0->actor->yaw - 180.0f, &arg0->yawVelocity, arg0->speed, arg0->limit, arg0->delta);
        } else {
            func_15049688(&arg0->yaw, arg0->actor->yaw - 180.0f, &arg0->yawVelocity, 5.0f, 8.0f, arg0->delta);
        }
        arg0->yawRadians = arg0->yaw * D_800A3440;
    } else if (arg0->locked == 0) {
        angle = ((arg0->actor->yaw + (f32) (u32) arg0->actor->angle * 0.0054931640625f) - 180.0f) - arg1;
        if (active != 0 && arg0->mode != 0x1C) {
            angle -= (f32) (arg0->actor->rotation >> 16) * D_800A3444;
        }
        mode = arg0->mode;
        if (mode == 9 || mode == 0x38 || mode == 0x39 || mode == 0x37 || mode == 0x3B || mode == 0x12) {
            angle -= (f32) arg0->target->angle * 0.0054931640625f;
        }
        func_15048758(&angle);
        if (arg0->instant != 0) {
            speed = arg0->target->yaw;
            limit = D_800A3448;
            if (limit != speed) {
                arg0->yaw = speed;
                position = arg0->target->position;
                arg0->position = position;
                arg0->previousPosition = position;
                arg0->target->yaw = limit;
            } else {
                arg0->yaw = angle;
            }
            arg0->yawVelocity = 0.0f;
        } else {
            if (active != 0 || arg0->fast != 0) {
                speed = 4.0f;
                limit = 6.0f;
            } else {
                mode = arg0->mode;
                if ((mode == 9 && D_800BE616 != 0) || mode == 0x38 || mode == 0x39 || mode == 0x37 || mode == 0x3B || mode == 0x12) {
                    speed = 2.0f;
                    limit = 6.0f;
                } else if (arg0->flags84 & 0x200000) {
                    speed = 1.0f;
                    limit = D_800A344C;
                } else {
                    speed = 0.75f;
                    limit = D_800A3450;
                }
            }
            if (D_800BEA0C == 0) {
                func_15049688(&arg0->yaw, angle, &arg0->yawVelocity, speed, limit, arg0->delta);
            }
        }
        arg0->yawRadians = arg0->yaw * D_800A3454;
    }
    func_1512A390(arg0);
    func_15123A54(arg0);
    func_1512E140(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15121C80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14F130/func_15121C80.s")
