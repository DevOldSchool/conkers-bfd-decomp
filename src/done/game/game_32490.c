#include "types.h"

/*
 * Reviewed source unit: src/game/game_32490.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

void func_10004074(s32);
void *func_10003C40(s32, s32, s32, s32);
u32 func_1502B7F0(s32 *, s32, ...);
extern s32 D_800C6650;
extern u32 D_800C6654;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 r;
    f32 unk10;
    f32 unk14;
} Game32490In;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
    u32 rsq;
    s16 unkC;
    s16 xmax;
    s16 xmin;
    s16 unk12;
} Game32490Out;

s32 func_15004FE0(s32 arg0) {
    Game32490In *source;
    s32 count;
    s32 i;

    source = NULL;
    i = 0;
    count = func_1502B7F0((s32 *)&source, 3, 0xC, arg0, 3) / 24U;
    D_800C6650 = (s32)func_10003C40(count * 20, 1, 1, 0);
    D_800C6654 = count;
    while (count > 0) {
        ((Game32490Out *)D_800C6650)[i].x = source[i].x;
        ((Game32490Out *)D_800C6650)[i].y = source[i].y;
        ((Game32490Out *)D_800C6650)[i].z = source[i].z;
        ((Game32490Out *)D_800C6650)[i].unk6 = 0;
        ((Game32490Out *)D_800C6650)[i].rsq = source[i].r * source[i].r;
        ((Game32490Out *)D_800C6650)[i].unkC = source[i].unk10;
        ((Game32490Out *)D_800C6650)[i].xmax = source[i].x + source[i].r;
        ((Game32490Out *)D_800C6650)[i].xmin = source[i].x - source[i].r;
        ((Game32490Out *)D_800C6650)[i].unk12 = source[i].unk14;
        count--;
        i++;
    }
    if (source != NULL) {
        func_10004074((s32)source);
    }
    return i;
}
