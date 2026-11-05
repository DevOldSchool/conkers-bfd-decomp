#include "types.h"

/*
 * Reviewed source unit: src/game/game_35EC0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

void *func_15083E90(u8);
extern void *D_80088720;
extern f32 D_80088724[];
extern void *D_80088730;

void func_15008A10(void) {
    D_80088720 = func_15083E90(1);
    D_80088724[0] = 0.0f;
    D_80088724[1] = 0.0f;
    D_80088724[2] = 0.0f;
    D_80088730 = func_15083E90(1);
}
extern s8 D_800DDDAC[4];
extern s32 D_800DDDB0[4];
extern f32 D_800DDDC8[4];
extern f32 D_800DDDD8[4];
extern s16 D_800DDE08;
extern s32 D_800DDE18;
extern s8 D_800DDE1C[4];
extern s8 D_800DDE20[4];
extern s32 D_800DDE28[4];
extern s8 D_800DDE38;
extern s8 D_800DDE3C[4];
extern s8 D_800DDE40;

void func_15008A60(void) {
    s32 i;

    D_800DDE08 = 0;
    D_800DDE40 = 0;
    for (i = 0; i < 4; i++) {
        D_800DDDAC[i] = 0;
        D_800DDE28[i] = 0;
        D_800DDDB0[i] = 0;
        D_800DDE1C[i] = 0;
        D_800DDE20[i] = 0;
        D_800DDDC8[i] = 0.0f;
        D_800DDDD8[i] = 0.0f;
        D_800DDE3C[i] = 0;
    }
    D_800DDE18 = 0;
    D_800DDE38 = 0;
}
