#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E240.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15040D9C
 * - func_15040FCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15040D90(s32 arg0) {

}
extern s32 D_8002AAE8[];
extern s32 D_800BE620;
extern u8 D_800BE9C0;
extern s32 D_800BE9C4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040D9C CURRENT (3740) */
void func_15040D9C(s32 arg0) {
    s32 x;
    s32 y;
    s32 buffer;

    x = D_800BE9C0;
    buffer = D_8002AAE8[x == 0];
    for (y = 0; y != 8; y++) {
        for (x = 0; x != 8; x++) {
            *(u16 *)(buffer + (arg0 + x) * 2 +
                     D_800BE620 * (y + 0xE1) * 2 + 0x190) = 0xF800;
            buffer = D_8002AAE8[D_800BE9C0];
            *(u16 *)(buffer + (arg0 + x) * 2 +
                     D_800BE620 * (y + 0xE1) * 2 + 0x190) = 0xF800;
            buffer = D_800BE9C4;
            *(u16 *)(buffer + (arg0 + x) * 2 +
                     D_800BE620 * (y + 0xE1) * 2 + 0x190) = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040D9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040D9C.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040FCC CURRENT (2465) */
void func_15040FCC(s32 arg0) {
    s32 x;
    s32 y;
    s32 index;
    s32 current;
    u16 *first;
    u16 *second;
    u16 *third;

    current = D_800BE9C0;
    first = (u16 *)D_8002AAE8[current == 0];
    second = (u16 *)D_8002AAE8[current];
    third = (u16 *)D_800BE9C4;
    for (x = 0; x != 8; x++) {
        index = arg0 + x + D_800BE620 * 0xE1 + 0xC8;
        first[index] = 0xF800;
        second[index] = 0xF800;
        third[index] = 0;
    }
    for (y = 1; y < 7; y++) {
        for (x = 0; x != 14; x += 7) {
            index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;
            first[index] = 0xF800;
            second[index] = 0xF800;
            third[index] = 0;
        }
    }
    for (y = 1; y < 7; y++) {
        for (x = 1; x < 7; x++) {
            index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;
            first[index] = 0;
            second[index] = 0;
            third[index] = 0;
        }
    }
    for (x = 0; x != 8; x++) {
        index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;
        first[index] = 0xF800;
        second[index] = 0xF800;
        third[index] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040FCC.s")
void func_1504129C(void) {
    s32 value = 0;

loop:
    value += 4;
    if (value != 0x18000000) {
        goto loop;
    }
}
