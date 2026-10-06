#include "types.h"

/*
 * Reviewed source unit: src/game/game_10E240.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0D90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10E240Camera {
    u8 pad0[0x2C];
    s32 mode;
    u8 pad30[0x54];
    u32 flags;
    u8 pad88[0x108];
    f32 distance;
    u8 pad194[0x20];
    s16 state;
    u8 pad1B6[0x2A];
    s16 transition;
    u8 pad1E2[0x5C];
    u8 kind;
    u8 pad23F[0x109];
    f32 range, previousRange;
    u8 pad350[0x24];
    f32 height;
    u8 pad378[0x350];
    s32 timer;
} Game10E240Camera;

s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, ...);
void func_15124B18(void *);
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E0D90 CURRENT (110) */
void func_150E0D90(void *arg0) {
    Game10E240Camera *camera = arg0;
    s32 result;
    s32 stage;

    if (camera->kind == 9) {
        if (D_800BE9F0 == 0x1E) {
            func_1509BFB0(0, 0x4044, 1);
        }
        if (camera->mode != 0x100 && camera->timer == 0) {
            if (func_15123934(camera, 8, 0, 0, 0) != 0) {
                camera->flags |= 0x300000;
                camera->flags &= ~4U;
                camera->state = 1;
                camera->transition = 3;
                func_15124B18(camera);
            }
            camera->range = 125.0f;
            camera->previousRange = 125.0f;
            camera->height = 220.0f;
            camera->distance = 30.0f;
        } else {
            camera->distance = 0.0f;
        }
        stage = D_800BE9F0;
    } else {
        if (camera->mode == 8 && camera->timer == 0 &&
            func_151239CC(camera, 0) != 0) {
            camera->previousRange = 110.0f;
            camera->range = 110.0f;
            camera->height = 300.0f;
        }
        stage = D_800BE9F0;
        if (stage == 0x1E) {
            func_1509BFB0(0, 0x4044, 0);
            stage = D_800BE9F0;
        }
    }
    if (stage == 0x2F) {
        camera->flags &= 0x7FFFFFFF;
        stage = D_800BE9F0;
    } else if (stage == 0x1E) {
        result = func_1509BE40(1, 0x4042, 6, 0x9000);
        if (result != 0) {
            camera->flags &= 0x7FFFFFFF;
        } else {
            camera->flags |= 0x80000000;
        }
        result = func_1509BE40(1, 0x4044, 6, 0x2000);
        if (result != 0) {
            camera->flags |= 0x20001010;
            camera->flags &= ~8U;
            stage = D_800BE9F0;
        } else {
            camera->flags &= 0xDFFFEFEF;
            camera->flags |= 8;
            stage = D_800BE9F0;
        }
    }
    if (stage == 0x1B) {
        result = func_1509BE40(1, 0x406E, 6, 0x9000);
        if (result != 0) {
            camera->flags |= 0x200;
        } else {
            camera->flags &= ~0x200U;
        }
        result = func_1509BE40(1, 0x406F, 6, 0x9000);
        if (result != 0) {
            camera->flags |= 0x80000000;
        } else {
            camera->flags &= 0x7FFFFFFF;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E0D90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10E240/func_150E0D90.s")
