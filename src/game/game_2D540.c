#include "types.h"

/*
 * Reviewed source unit: src/game/game_2D540.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150000B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15000090(void) {
    func_1000DEC4();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D540/func_150000B0.s")
void func_15000940(s32);
void *func_1515D480(s32);
extern s32 D_80082FA0;
extern void *D_800B0DF0;
extern f32 D_800D3670, D_800D9B1C, D_800D9B20;
extern f32 D_800D9AC0[], D_800D9AF8[];
extern u8 D_800D9B68[4][3], D_800D9B78[4][3];
extern u8 D_800D9B84[], D_800D9B88[];
extern u8 D_800D9BD0[];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9AF0, D_800D9B18, D_800D9B8B, D_800D9B8C;

void func_150006E0(s32 arg0) {
    s32 i;
    s32 j;
    u8 *first;
    u8 *second;

    D_800D9B20 = (f32)(u32)*(u16 *)((u8 *)D_800B0DF0 + 2);
    D_800D9B1C = (f32)(u32)*(u16 *)D_800B0DF0;
    D_800D3670 = 100.0f - D_800D9B1C;
    func_15000940(arg0);
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 3; i++) {
            D_800D9B68[j][i] = 0;
            D_800D9B78[j][i] = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        D_800D9B84[i] = 0;
        D_800D9B88[i] = 0;
    }
    D_800D9B8B = 0xFF;
    D_800D9B8C = 0xFF;
    D_800D9E20 = 0xB;
    for (i = 0; i <= D_80082FA0; i++) {
        D_800D9E10[i] = (s32)func_1515D480(D_800D9E20);
    }
    for (j = 0; j <= D_80082FA0; j++) {
        for (i = 0; i < 2; i++) {
            D_800D9BD0[j * 16 + i * 8 + 0] = D_800D9BD0[j * 16 + i * 8 + 4] = 0xFF;
            D_800D9BD0[j * 16 + i * 8 + 1] = D_800D9BD0[j * 16 + i * 8 + 5] = 0xFF;
            D_800D9BD0[j * 16 + i * 8 + 2] = D_800D9BD0[j * 16 + i * 8 + 6] = 0xFF;
        }
    }
    for (j = 0; j <= D_80082FA0; j++) {
        D_800D9AC0[j * 3] = -1.0f;
    }
    D_800D9AF0 = 0;
    for (j = 0; j <= D_80082FA0; j++) {
        D_800D9AF8[j * 2] = -1.0f;
    }
    D_800D9B18 = 0;
}
