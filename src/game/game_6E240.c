#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E240.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 */

void func_15040D90(s32 arg0) {

}
extern s32 D_8002AAE8[];
extern s32 D_800BE620;
extern u8 D_800BE9C0;
extern s32 D_800BE9C4;

void func_15040D9C(s32 arg0) {
    s32 current;
    s32 x;
    s32 y;
    u16 *buffer;

    current = D_800BE9C0;
    buffer = (u16 *)D_8002AAE8[current == 0];
    for (y = 0; y != 8; y++) {
        for (x = 0; x != 8; x++) {
            buffer[arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8] = 0xF800;
            buffer = (u16 *)D_8002AAE8[D_800BE9C0];
            buffer[arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8] = 0xF800;
            buffer = (u16 *)D_800BE9C4;
            buffer[arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8] = 0;
        }
    }
}

void func_15040FCC(s32 arg0) {
    s32 x;
    s32 y;
    u16 *first;
    u16 *second;
    u16 *third;

    first = (u16 *)D_8002AAE8[!D_800BE9C0];
    second = (u16 *)D_8002AAE8[D_800BE9C0];
    third = (u16 *)D_800BE9C4;
    y = 0;
    for (x = 0; x < 8; x++) {
        s32 index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;

        first[index] = 0xF800;
        second[index] = 0xF800;
        third[index] = 0;
    }
    for (y = 1; y < 7; y++) {
        for (x = 0; x < 14; x += 7) {
            s32 index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;

            first[index] = 0xF800;
            second[index] = 0xF800;
            third[index] = 0;
        }
    }
    for (y = 1; y < 7; y++) {
        for (x = 1; x < 7; x++) {
            s32 index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;

            first[index] = 0;
            second[index] = 0;
            third[index] = 0;
        }
    }
    for (x = 0; x < 8; x++) {
        s32 index = arg0 + x + D_800BE620 * (y + 0xE1) + 0xC8;

        first[index] = 0xF800;
        second[index] = 0xF800;
        third[index] = 0;
    }
}
void func_1504129C(void) {
    s32 value = 0;
    s32 step = 4;

    do {
        value += step;
    } while (value != 0x18000000);
}
