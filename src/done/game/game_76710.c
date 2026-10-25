#include "types.h"

/*
 * Reviewed source unit: src/game/game_76710.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

typedef struct Game76710CallArgs {
    s32 words[9];
} Game76710CallArgs;

s32 func_150AAD98(Game76710CallArgs);

s32 func_15049260(Game76710CallArgs arg0) {
    return func_150AAD98(arg0);
}
extern f32 D_80099080;







extern f32 D_800CC220;
extern f32 D_800CC224;
extern f32 D_800CC228;
extern f32 D_800CC22C;
extern f32 D_800CC230;
extern f32 D_800CC234;
extern f32 D_800CC238;
extern f32 D_800CC23C;
void func_150492CC(f32 arg0, f32 arg1, f32 arg2) {
    D_800CC220 = arg0;
    D_800CC224 = arg1;
    D_800CC228 = arg2;
    D_800CC22C = arg0 / (1.0f + 1.0f);
    D_800CC230 = arg1 / (1.0f + 1.0f);
    D_800CC234 = arg2 / (1.0f + 1.0f);
    if (arg0 == 0.0f) {
        arg0 = D_80099080;
    }
    D_800CC238 = arg1 / arg0;
    D_800CC23C = arg2 / arg0;
}
extern f32 D_800CC210;
extern f32 D_800CC214;
extern f32 D_800CC218;
extern f32 D_800CC21C;

void func_15049350(Game76710CallArgs args) {
    f32 x;
    f32 y;
    f32 dx1;
    f32 dy1;
    f32 dz1;
    f32 dx2;
    f32 dy2;
    f32 dz2;
    f32 nx;

    dx1 = *(f32 *)&args.words[0] - *(f32 *)&args.words[3];
    x = *(f32 *)&args.words[0];
    dy1 = *(f32 *)&args.words[1] - *(f32 *)&args.words[4];
    y = *(f32 *)&args.words[1];
    dz1 = *(f32 *)&args.words[2] - *(f32 *)&args.words[5];
    dx2 = *(f32 *)&args.words[0] - *(f32 *)&args.words[6];
    dy2 = *(f32 *)&args.words[1] - *(f32 *)&args.words[7];
    dz2 = *(f32 *)&args.words[2] - *(f32 *)&args.words[8];
    nx = (dy1 * dz2) - (dz1 * dy2);
    D_800CC210 = nx;
    D_800CC214 = (-dx1 * dz2) + (dz1 * dx2);
    D_800CC218 = (dx1 * dy2) - (dy1 * dx2);
    D_800CC21C = (*(f32 *)&args.words[2] * ((dx1 * dy2) - (dy1 * dx2))) +
        ((nx * x) + (((-dx1 * dz2) + (dz1 * dx2)) * y));
}
