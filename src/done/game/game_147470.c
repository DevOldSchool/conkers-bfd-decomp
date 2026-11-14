#include "types.h"

/*
 * Reviewed source unit: src/game/game_147470.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
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
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern Game147470Actor D_800CC2D0[];
extern u8 *D_800DBEF4;

void func_15119FC0(Game147470Object *arg0) {
    s32 i;
    f32 actorY;
    s16 height;
    s16 width;
    s16 depth;
    f32 distance;

    if (arg0->timer < 0x20) {
        if (arg0->baseHeight == 0) {
            arg0->baseHeight = arg0->position[1];
        }
        arg0->x = func_15047D60(arg0->phase) * 15.0f;
        arg0->y = arg0->phase * 19.098593f;
        arg0->z = func_15047C00(arg0->phase) * 15.0f;
        arg0->phase += 0.08726647f * D_800BE9A4;
        if (18.849556f <= arg0->phase) {
            arg0->phase -= 18.849556f;
        }
        arg0->position[1] = (s32)(func_15047C00(arg0->phase + arg0->phase) * 10.0f) + arg0->baseHeight + 10;
        if (arg0->timer == 0) {
            for (i = 0; i < D_8008FD8C; i++) {
                if (D_800CC2D0[i].active == 0 || D_800CC2D0[i].index == 0xFF || arg0->flags < 0) {
                    continue;
                }
                distance = ((f32)arg0->position[0] - D_800CC2D0[i].x) * ((f32)arg0->position[0] - D_800CC2D0[i].x) +
                           ((f32)arg0->position[2] - D_800CC2D0[i].z) * ((f32)arg0->position[2] - D_800CC2D0[i].z);
                if (distance < 6400.0f) {
                    func_1507C3E0(&D_800CC2D0[i], &height, &width, &depth);
                    arg0->state = 0x31;
                    actorY = D_800CC2D0[i].y;
                    if (actorY < (f32)arg0->position[1] + 80.0f && (f32)arg0->position[1] - 80.0f < actorY + (f32)height &&
                        D_800CC2D0[i].enabled > 0) {
                        if (func_15060BA4(&D_800CC2D0[i], 1) != 0) {
                            if (arg0->flags != 0) {
                                arg0->timer = ((arg0->flags >> 16) & 0xFFFF) * 60;
                                arg0->flags70 |= 4;
                            } else {
                                arg0->removed = 1;
                                func_1508EE0C(2, ((s32)((u8 *)arg0 - D_800DBEF4) / 160) & 0xFFFF);
                            }
                            arg0->state = 0x20;
                            func_10010344(0x1CF, &D_800CC2D0[i], 0x7D00, 0xC8, 0x9C4);
                            func_151D69B4(arg0, &D_800CC2D0[i]);
                        } else {
                            distance *= 0.0001171875f;
                            arg0->state = 0x31;
                            arg0->alpha = (0.25f + distance) * 255.0f;
                        }
                        break;
                    }
                } else {
                    arg0->alpha = 0xFF;
                    arg0->state = 0x21;
                }
            }
        } else {
            arg0->state = 0x31;
            arg0->alpha = (0x20 - arg0->timer) << 3;
        }
    }
    if (arg0->timer > 0) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer <= 0) {
            arg0->timer = 0;
            arg0->alpha = 0xFF;
            arg0->state = 0x21;
        }
    }
}
