#include "types.h"

/*
 * Reviewed source unit: src/game/game_203340.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_type4b_framebuffer_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D5E90
 * - func_151D61B0
 * - func_151D6418
 * - func_151D6778
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE620;
extern s32 D_800BE624;

typedef struct Game203340Command { u32 first, second; } Game203340Command;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TXL2WORDS(txls, b_txl) MAX(1, ((txls) * (b_txl) / 8))
#define CALC_DXT(width, b_txl) (((1 << 11) + TXL2WORDS(width, b_txl) - 1) / TXL2WORDS(width, b_txl))
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E90 CURRENT (92) */
Game203340Command *func_151D5E90(Game203340Command *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 width;
    u32 height;
    u32 y;
    u32 x;
    u32 rows;
    u32 cols;

    width = D_800BE620;
    height = D_800BE624;
    { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
    { Game203340Command *command = arg0++; command->first = 0xFCFFFFFF; command->second = 0xFFFCF279; }
    { Game203340Command *command = arg0++; command->first = 0xEF000CFF; command->second = 0x0F0A4000; }
    { Game203340Command *command = arg0++; command->first = 0xD9000000; command->second = 0; }
    { Game203340Command *command = arg0++; command->first = 0xD7000002; command->second = 0xFFFFFFFF; }
    rows = 16;
    for (y = 0; y < height; y += rows) {
        if (y + rows > height) rows = height - y;
        for (x = 0, cols = 128; x < width; x += cols) {
            if (x + cols > width) cols = width - x;
            { Game203340Command *command = arg0++; command->first = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(width - 1, 0, 12); command->second = arg1; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((((x + cols - 1) - x + 1) * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE6, 24, 8); command->second = 0; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF4, 24, 8) | _SHIFTL(x << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); command->second = _SHIFTL(7, 24, 3) | _SHIFTL((x + cols - 1) << 2, 12, 12) | _SHIFTL((y + rows - 1) << 2, 0, 12); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((((x + cols - 1) - x + 1) * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF2, 24, 8) | _SHIFTL(x << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL((x + cols - 1) << 2, 12, 12) | _SHIFTL((y + rows - 1) << 2, 0, 12); }
            { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE4, 24, 8) | _SHIFTL((x + cols) << 2, 12, 12) | _SHIFTL((y + rows) << 2, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(x << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE1, 24, 8); command->second = _SHIFTL(x << 5, 16, 16) | _SHIFTL(y << 5, 0, 16); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF1, 24, 8); command->second = _SHIFTL(1 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
            { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
        }
    }
    { Game203340Command *command = arg0++; command->first = 0xEF080C3F; command->second = 0x0F0A4000; }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5E90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D5E90.s")

extern s32 D_800BE620;
extern s32 D_800BE624;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D61B0 CURRENT (90) */
void func_151D61B0(void *arg0) {
    s32 height;
    s32 width;
    s32 y;
    s32 x;
    u16 red;
    u16 green;
    u16 blue;
    u16 previous;
    u16 current;
    u16 next;
    u16 *row;
    u16 *cursor;

    width = D_800BE620;
    height = D_800BE624;
    row = arg0;
    for (y = 0; y < height; y++) {
        cursor = row + 1;
        current = row[1];
        next = row[2];
        for (x = 1; x < width - 1; x++) {
            previous = current;
            current = next;
            next = cursor[2];
            red = (current >> 11) & 31;
            red += (previous >> 12) & 15;
            red += (next >> 12) & 15;
            green = (current >> 6) & 31;
            green += (previous >> 7) & 15;
            green += (next >> 7) & 15;
            blue = (current >> 1) & 31;
            blue += (previous >> 2) & 15;
            blue = (blue + ((next >> 2) & 15)) & 0x3E;
            cursor[1] = ((red & 0x3E) << 10) | ((green & 0x3E) << 5) | blue | 1;
            cursor++;
        }
        row += width;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D61B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D61B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6418 CURRENT (70) */
Game203340Command *func_151D6418(Game203340Command *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 width;
    u32 y;
    u32 height;
    s32 address;

    width = D_800BE620;
    height = D_800BE624;
    address = arg1;
    { Game203340Command *command = arg0++; command->first = _SHIFTL(0xFA, 24, 8) | _SHIFTL(0, 8, 8) | _SHIFTL(0, 0, 8); command->second = _SHIFTL(255, 24, 8) | _SHIFTL(255, 16, 8) | _SHIFTL(255, 8, 8) | _SHIFTL(arg3, 0, 8); }
    { Game203340Command *command = arg0++; command->first = 0xFC11FE23; command->second = 0xFFFFF7FB; }
    { Game203340Command *command = arg0++; command->first = 0xEF000CFF; command->second = 0x00504340; }
    { Game203340Command *command = arg0++; command->first = 0xD9000000; command->second = 0; }
    { Game203340Command *command = arg0++; command->first = 0xD7000002; command->second = 0xFFFFFFFF; }
    for (y = 0; y < height; y += 4) {
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(1 - 1, 0, 12); command->second = address + 0x80000000; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(0, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE6, 24, 8); command->second = 0; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF3, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->second = _SHIFTL(7, 24, 3) | _SHIFTL(MIN(((width * 4) + 0 >> 0) - 1, 0x7FF), 12, 12) | _SHIFTL(CALC_DXT(width, 2), 0, 12); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((width * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF2, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL((width - 1) << 2, 12, 12) | _SHIFTL((4 - 1) << 2, 0, 12); }
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE4, 24, 8) | _SHIFTL((width - arg2) << 2, 12, 12) | _SHIFTL((y + 4) << 2, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(0 << 2, 12, 12) | _SHIFTL(y << 2, 0, 12); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE1, 24, 8); command->second = _SHIFTL(0, 16, 16) | _SHIFTL(0, 0, 16); } { Game203340Command *command = arg0++; command->first = _SHIFTL(0xF1, 24, 8); command->second = _SHIFTL(1 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
        address += width * 8;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6418 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6418.s")
void func_100043B4(void *, s32);
extern u8 D_80038080;
extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;
extern s32 D_800BE9F0;

void func_151D66F0(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 != 6) || (D_80038080 != 0)) {
        if (arg1 == 0) {
            arg0 = 0;
        }
        D_800BE574 = arg0;
        if (arg0 != 0) {
            D_800BE575 = arg1;
        } else {
            D_800BE575 = 0;
        }
        if ((arg0 == 0) && (D_800BE570 != 0)) {
            func_100043B4((void *)D_800BE570, 3);
            D_800BE570 = 0;
        }
    }
}
void *func_1501A680(void *);
s32 func_10003C40(s32, s32, s32, s32);
Game203340Command *func_151D6418(Game203340Command *, s32, s32, s32);
Game203340Command *func_151D5E90(Game203340Command *, s32, s32, s32);
extern s32 D_8002AAE8[];
extern u8 D_800BE9C0;
extern u8 D_800BEAC0;


#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6778 CURRENT (225) */
Game203340Command *func_151D6778(Game203340Command *arg0) {
    u32 flags;

    flags = (u8)D_800BE574;
    if ((flags == 0 && D_800BE9F0 != 0x32 && D_800BE9F0 != 0x33) || D_800BEAC0 != 0) {
        return arg0;
    }
    if (flags != 0) {
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
        if (D_800BE570 != 0) {
            arg0 = func_151D6418(arg0, D_800BE570, 0, flags);
        } else {
            D_800BE570 = func_10003C40(D_800BE620 * D_800BE624 * 2, 1, 3, 1);
            if (D_800BE570 == 0) {
                return arg0;
            }
        }
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xFF, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(D_800BE620 - 1, 0, 12); command->second = D_800BE570; }
        { Game203340Command *command = arg0++; command->first = _SHIFTL(0xED, 24, 8) | _SHIFTL((s32)((f32)(0) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(0) * 4.0f), 0, 12); command->second = _SHIFTL(0, 24, 2) | _SHIFTL((s32)((f32)(D_800BE620) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(D_800BE624) * 4.0f), 0, 12); }
        arg0 = func_151D5E90(arg0, D_8002AAE8[D_800BE9C0], 0, 4);
        { Game203340Command *command = arg0++; command->first = 0xEF082C3F; command->second = 0x552230; }
        { Game203340Command *command = arg0++; command->first = 0xD9FFFFFF; command->second = 0x220405; }
        arg0 = func_1501A680(arg0);
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6778 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6778.s")
