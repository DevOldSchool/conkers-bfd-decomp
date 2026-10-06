#include "types.h"

/*
 * Reviewed source unit: src/game/game_1312F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15103E40
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1312F0Position { f32 x, y, z; } Game1312F0Position;
/* 0x24-byte result: func_1504715C initializes through the pointer at 0x20. */
typedef struct Game1312F0Hit {
    f32 height;
    s16 vertices[3][3];
    u8 pad16[2];
    s32 owner;
    u8 flags;
    u8 kind;
    u8 pad1E[2];
    void *record;
} Game1312F0Hit;
s32 func_15046C80(void *, u16, f32, void *);
void func_1504715C(void *, s32);
void func_15055A2C(s32, f32, f32, f32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
void func_151541B8(s32, f32, s32, f32, f32, u8, s32);
void func_151D3FF4(s32, u8, s32);
void func_151D40D4(void *, s32, s32, s32, s32, s32, s32, s32);
void func_151D5334(s32, s32, s32, s32, s32, s32, s32);
void func_151D5404(void *, f32, f32, f32, s16, s16);
void func_151D5514(s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103E40 CURRENT (2996) */
void func_15103E40(s32 arg0, s32 arg1, Game1312F0Position *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Game1312F0Position impact;
    u8 hit_valid;
    Game1312F0Position top;
    Game1312F0Hit hit;
    u32 random_value;
    f32 random_float;
    Game1312F0Position *position;
    s32 effect0;
    s32 effect1;

    if (arg0 != 0) {
        hit_valid = 0;
        func_151D3FF4((s32) arg2, (u8) arg5, arg6);
        top.x = arg2->x;
        top.y = arg2->y + 100.0f;
        top.z = arg2->z;
        func_1504715C(&hit, arg1);
        if ((func_15046C80(&top, 0, arg2->y - 100.0f, &hit) != 0) && (hit.flags & 1)) {
            impact.x = top.x;
            hit_valid = 1;
            impact.y = hit.height;
            impact.z = top.z;
            random_float = func_150ADA68();
            random_value = func_150ADA20();
            func_150E7FEC((random_float * 125.0f) + 204.0f, ((random_value % 101U) + 0x9B) & 0xFF, (s32) hit.vertices, (s32) &impact, (func_150ADA20() % 302U) + 0x1F4, 0, 1, 0, 0, 0, (u8) arg5, 0);
        }
        if (hit_valid != 0) {
            position = &impact;
        } else {
            position = arg2;
        }
        func_150E83AC(position, (s16) ((func_150ADA20() % 62U) + 0x78), (u8) arg5, arg6);
        /* Follow the accepted callee's six-argument contract. */
        func_151D5404(arg2, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14);
        func_151D5334((s32) arg2, 0x43FD0000, 0x447D4000, 0x3A8163D3, 5, (u8) arg5, arg6);
        func_151D5514((s32) arg2, (u8) arg5, arg6);
        if ((u8) arg3 != 0) {
            if ((u8) arg3 == 2) {
                effect0 = 0x42;
                effect1 = 0x41;
            } else {
                effect0 = 0x2B;
                effect1 = 0x2A;
            }
            func_151D40D4(arg2, 0, arg0, arg1, 0, effect0, effect1, arg4);
        }
        func_15055A2C(0, arg2->x, arg2->y, arg2->z, 1);
        random_float = func_150ADA68();
        random_value = (func_150ADA20() % 56U) + 0xC8;
        func_151541B8((s32) arg2, (random_float * 4.0f) + 12.0f, 0x3FD20C49, (f32) random_value, 0.0f, (u8) arg5, arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103E40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1312F0/func_15103E40.s")
