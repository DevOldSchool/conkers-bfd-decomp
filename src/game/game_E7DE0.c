#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E7DE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BAA14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern f32 D_8009FE60;

s32 func_150BA930(f32 *arg0, u8 *arg1, void *arg2, s32 arg3) {
    f32 position[3];
    f32 value;

    arg0[0] = *(f32 *)(arg1 + 0x14);
    if (D_8009FE60 < (value = *(f32 *)(arg1 + 0x180))) {
        arg0[1] = value;
    } else {
        arg0[1] = *(f32 *)(arg1 + 0x18);
    }
    arg0[2] = *(f32 *)(arg1 + 0x1C);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 100.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 100.0f, arg2);
}
s32 func_150BAA00(s32 arg0, s32 arg1) {
    return 9;
}
typedef struct GameE7DE0Hit {
    f32 height;
    s16 points[9];
    s32 object;
    u8 flags;
    u8 active;
    u8 pad1E[2];
    s32 field20;
} GameE7DE0Hit;

s32 func_150BA930(f32 *, u8 *, void *, s32);
u8 func_15143E94(s32, s32);
void func_1514C678(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
/* The raw caller supplies two additional words beyond the consumed prefix. */
u32 func_150ADA20();
f32 func_150ADA68();
extern s32 D_80082FA4;
extern f32 D_8009FE64;
extern u8 *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BAA14 CURRENT (188) */
void func_150BAA14(u8 *volatile arg0, u8 arg1, s32 arg2) {
    f32 position[3];
    GameE7DE0Hit hit;
    s32 angle;
    u8 found;
    f32 random;

    if (*(void **)(arg0 + 0x1D4) != 0) {
        found = func_150BA930(position, arg0, &hit, arg1);
        func_151D5404(position, 1307.0f, 2000.0f, 0.0005f, 0xC, 0xF, 0xFF, 0);
        func_15143E94(5, 0x4022);
        if (found != 0) {
            angle = (s32)(*(f32 *)((u32)D_800DBFF0 + (u32)D_80082FA4 * 0x9A0U + 0x380) * D_8009FE64);
            func_15165F80(-1, (s32)position[0], (s32)(position[1] + 6.0f),
                         (s32)position[2], 0x19, 0x12, 0, 0xFF, 1);
            random = func_150ADA68();
            func_1514C678(position[0], position[1], position[2], random * 50.0f + 40.0f,
                         (s32)((u32)angle + 0x3CU), (s32)((u32)angle - 0x3CU), (func_150ADA20() % 11U) + 0x1E,
                         5, 0, 0.0f, 0, 0xFF);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BAA14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7DE0/func_150BAA14.s")
