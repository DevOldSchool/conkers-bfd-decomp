#include "types.h"

/*
 * Reviewed source unit: src/game/game_147470.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15119FC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game147470Object {
    f32 x, y, z;
    u8 pad0C[4];
    s16 position[3];
    u8 pad16[0x26];
    s32 flags;
    u8 pad40[0xF];
    s8 state;
    u8 pad50[0x1E];
    s8 removed;
    u8 pad6F;
    u8 flags70;
    u8 pad71[0xB];
    f32 phase;
    s32 baseHeight;
    s32 timer;
    u8 pad88[2];
    u8 alpha;
} Game147470Object;

typedef struct Game147470Actor {
    s32 active;
    u8 pad04[0x10];
    f32 x, y, z;
    u8 pad20[0x107];
    u8 index;
    u8 pad128[0xA2];
    u8 enabled;
    u8 pad1CB[0x161];
} Game147470Actor;

f32 func_15047C00(f32);
f32 func_15047D60(f32);
s32 func_15060BA4(void *, s32);
s32 func_10010344(s32, void *, u32, s16, s32);
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
void func_1508EE0C(s32, s32);
void func_151D69B4(void *, void *);
extern s8 D_8008FD8C;
extern f32 D_800A3170, D_800A3174, D_800A3178, D_800A317C;
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern Game147470Actor D_800CC2D0[];
extern u8 *D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15119FC0 CURRENT (5142) */
void func_15119FC0(Game147470Object *arg0) {
    s16 height;
    s16 width;
    s16 depth;
    Game147470Actor *actor;
    f32 phase;
    f32 dx;
    f32 dz;
    f32 distance;
    f32 actorY;
    f32 objectY;
    s32 flags;
    s32 timer;

    timer = arg0->timer;
    if (timer < 0x20) {
        if (arg0->baseHeight == 0) {
            arg0->baseHeight = arg0->position[1];
        }
        arg0->x = func_15047D60(arg0->phase) * 15.0f;
        phase = arg0->phase;
        arg0->y = phase * D_800A3170;
        arg0->z = func_15047C00(phase) * 15.0f;
        arg0->phase += D_800A3178 * D_800BE9A4;
        if (D_800A3174 <= arg0->phase) {
            arg0->phase -= D_800A3174;
        }
        arg0->position[1] = (s32) (func_15047C00(arg0->phase + arg0->phase) * 10.0f) + arg0->baseHeight + 10;
        timer = arg0->timer;
        if (timer == 0) {
            actor = D_800CC2D0;
            if (D_8008FD8C > 0) {
                do {
                    if (actor->active != 0 && actor->index != 0xFF && arg0->flags >= 0) {
                        dz = (f32) arg0->position[2] - actor->z;
                        dx = (f32) arg0->position[0] - actor->x;
                        distance = dz * dz + dx * dx;
                        if (distance < 6400.0f) {
                            func_1507C3E0(actor, &height, &width, &depth);
                            arg0->state = 0x31;
                            actorY = actor->y;
                            objectY = (f32) arg0->position[1];
                            if (actorY < objectY + 80.0f && objectY - 80.0f < actorY + (f32) height && actor->enabled > 0) {
                                if (func_15060BA4(actor, 1) != 0) {
                                    flags = arg0->flags;
                                    if (flags != 0) {
                                        arg0->timer = ((flags >> 16) & 0xFFFF) * 60;
                                        arg0->flags70 |= 4;
                                    } else {
                                        arg0->removed = 1;
                                        func_1508EE0C(2, ((s32) ((u8 *) arg0 - D_800DBEF4) / 160) & 0xFFFF);
                                    }
                                    arg0->state = 0x20;
                                    func_10010344(0x1CF, actor, 0x7D00, 0xC8, 0x9C4);
                                    func_151D69B4(arg0, actor);
                                } else {
                                    arg0->state = 0x31;
                                    arg0->alpha = (u32) ((0.25f + distance * D_800A317C) * 255.0f);
                                }
                                break;
                            }
                        } else {
                            arg0->alpha = 0xFF;
                            arg0->state = 0x21;
                        }
                    }
                    actor++;
                } while ((u32) actor < (u32) (D_800CC2D0 + D_8008FD8C));
            }
            timer = arg0->timer;
        } else {
            arg0->state = 0x31;
            arg0->alpha = (0x20 - timer) * 8;
        }
    }
    if (timer > 0) {
        arg0->timer = timer - D_800BE9E4;
        if (arg0->timer <= 0) {
            arg0->timer = 0;
            arg0->alpha = 0xFF;
            arg0->state = 0x21;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15119FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_147470/func_15119FC0.s")
