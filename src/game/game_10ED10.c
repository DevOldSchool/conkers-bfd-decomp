#include "types.h"

/*
 * Reviewed source unit: src/game/game_10ED10.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1860
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x84];
    u32 flags;
    u8 pad88[0x72C];
    f32 delta;
} Game10ED10Actor;

void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, ...);
extern f32 D_80088990[], D_800889A0[], D_800889B0[];
extern s32 D_800889C0[], D_800889D0[], D_800889E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E1860 CURRENT (10) */
void func_150E1860(Game10ED10Actor *arg0) {
    s32 index;
    s32 active;

    active = 0;
    arg0->flags |= 0x10;
    for (index = 0; index < 4; index++) {
        if (func_1509BE40(1, D_800889C0[index], 6, 0x9000)) {
            D_800889A0[index] = 192.0f;
            active = 1;
            arg0->flags |= 0x80021010;
        } else {
            D_800889A0[index] = 255.0f;
        }
        func_150495B0(&D_80088990[index], D_800889A0[index], &D_800889B0[index], 4.0f, 6.0f, arg0->delta);
        func_1509BFB0(1, D_800889D0[index], 0x12, (u32)D_80088990[index] & 0xFF);
    }
    if (active == 0) {
        arg0->flags &= 0x7FFDEFFF;
    }
    if (func_1509BE40(1, 0x403D, 6, 0x2000)) {
        arg0->flags &= 0x7FFFFFFF;
        return;
    }
    arg0->flags |= 0x80000000;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E1860 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10ED10/func_150E1860.s")
