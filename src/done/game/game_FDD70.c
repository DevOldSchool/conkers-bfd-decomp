#include "types.h"

/*
 * Reviewed source unit: src/game/game_FDD70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons.md
 */

typedef struct {
    u8 pad00[0x84];
    s32 flags;
    u8 pad88[0x72C];
    f32 delta;
} GameFDD70Camera;

/* Call context: func_150495B0: unique active project prototype */
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);

s32 func_1509BE40(s32, s32, s32, ...);
void func_1509BFB0(s32, s32, s32, ...);
extern f32 D_800888C0;
extern f32 D_800888C4;
extern f32 D_800888C8;
extern f32 D_800888CC;
extern f32 D_800888D0;
extern f32 D_800888D4;
extern f32 D_800888D8;
extern f32 D_800888DC;
extern f32 D_800888E0;

void func_150D08C0(GameFDD70Camera *arg0) {

    if (func_1509BE40(1, 0x403D, 6, 0x9000) != 0) {
        arg0->flags = (s32) (arg0->flags | 0x80021000);
        if (func_1509BE40(1, 0x4043, 6, 0x9000) != 0) {
            D_800888CC = 64.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 255.0f;
        } else if (func_1509BE40(1, 0x4044, 6, 0x9000) != 0) {
            D_800888CC = 255.0f;
            D_800888D0 = 64.0f;
            D_800888D4 = 255.0f;
        } else if (func_1509BE40(1, 0x4045, 6, 0x9000) != 0) {
            D_800888CC = 255.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 64.0f;
        } else {
            D_800888CC = 255.0f;
            D_800888D0 = 255.0f;
            D_800888D4 = 255.0f;
        }
    } else {
        D_800888CC = 255.0f;
        D_800888D0 = 255.0f;
        D_800888D4 = 255.0f;
        arg0->flags &= 0x7FFDEFFF;
        arg0->flags |= 8;
    }
    func_150495B0(&D_800888C0, D_800888CC, &D_800888D8, 4.0f, 6.0f, arg0->delta);
    func_150495B0(&D_800888C4, D_800888D0, &D_800888DC, 4.0f, 6.0f, arg0->delta);
    func_150495B0(&D_800888C8, D_800888D4, &D_800888E0, 4.0f, 6.0f, arg0->delta);
    func_1509BFB0(1, 0x30F5, 0x12, (u32) D_800888C0 & 0xFF);
    func_1509BFB0(1, 0x30F4, 0x12, (u32) D_800888C4 & 0xFF);
    func_1509BFB0(1, 0x30F3, 0x12, (u32) D_800888C8 & 0xFF);
    func_1509BFB0(1, 0x30FA, 0x12, (u32) D_800888C0 & 0xFF);
    func_1509BFB0(1, 0x30F9, 0x12, (u32) D_800888C4 & 0xFF);
    func_1509BFB0(1, 0x30F8, 0x12, (u32) D_800888C8 & 0xFF);
}
