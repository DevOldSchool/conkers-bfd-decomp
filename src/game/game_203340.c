#include "types.h"

/*
 * Reviewed source unit: src/game/game_203340.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_type4b_framebuffer_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D5E90
 * - func_151D61B0
 * - func_151D6418
 * - func_151D66F0
 * - func_151D6778
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE620;
extern s32 D_800BE624;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E90 CURRENT (6213) */
void *func_151D5E90(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    typedef struct { u32 first, second; } Packet;
    volatile u32 sp8C;
    volatile s32 sp84;
    volatile u32 sp34;
    s32 width;
    s32 height;
    s32 rows;
    s32 columns;
    u32 y;
    u32 nextY;
    u32 x;
    u32 nextX;
    u32 lastX;
    u32 tile;
    u32 startX;
    u32 endX;
    u32 startY;
    u32 endY;

    width = D_800BE620;
    height = D_800BE624;
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xE7000000;
        command->second = 0;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xFCFFFFFF;
        command->second = 0xFFFCF279;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xEF000CFF;
        command->second = 0x0F0A4000;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xD9000000;
        command->second = 0;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->second = 0xFFFFFFFF;
        command->first = 0xD7000002;
    }
    rows = 16;
    y = 0;
    if (height != 0) {
        do {
            nextY = y + rows;
            x = 0;
            columns = 128;
            if ((u32)height < nextY) {
                rows = height - y;
                nextY = y + rows;
            }
            if (width != 0) {
                startY = (y * 4) & 0xFFF;
                endY = ((nextY - 1) * 4) & 0xFFF;
                sp84 = rows;
                sp8C = height;
                sp34 = nextY;
                do {
                    nextX = x + columns;
                    if ((u32)width < nextX) {
                        columns = width - x;
                        nextX = x + columns;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = ((width - 1) & 0xFFF) | 0xFD100000;
                        command->second = arg1;
                    }
                    lastX = nextX - 1;
                    tile = ((((u32)(((lastX - x) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = tile;
                        command->second = 0x07000000;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = 0xE6000000;
                        command->second = 0;
                    }
                    startX = ((x * 4) & 0xFFF) << 12;
                    endX = ((lastX * 4) & 0xFFF) << 12;
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = startX | 0xF4000000 | startY;
                        command->second = endX | 0x07000000 | endY;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = 0xE7000000;
                        command->second = 0;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = tile;
                        command->second = 0;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->second = endX | endY;
                        command->first = startX | 0xF2000000 | startY;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->second = startX | startY;
                        command->first = (((nextX * 4) & 0xFFF) << 12) | 0xE4000000 | ((nextY * 4) & 0xFFF);
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = 0xE1000000;
                        command->second = (x << 21) | ((y << 5) & 0xFFFF);
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = 0xF1000000;
                        command->second = 0x04000400;
                    }
                    {
                        Packet *command = (Packet *)arg0;
                        arg0 += sizeof(Packet);
                        command->first = 0xE7000000;
                        command->second = 0;
                    }
                    x = nextX;
                } while (nextX < (u32)width);
                nextY = sp34;
                rows = sp84;
                height = sp8C;
            }
            y = nextY;
        } while (nextY < (u32)height);
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xEF080C3F;
        command->second = 0x0F0A4000;
    }
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6418 CURRENT (4830) */
void *func_151D6418(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    typedef struct { u32 first, second; } Packet;
    s32 width;
    s32 height;
    volatile s32 sp34;
    s32 address;
    u32 doubleWidth;
    u32 loadSize;
    u32 stride;
    u32 y;
    u32 nextY;
    u32 size;
    u32 numerator;
    u32 denominator;

    width = D_800BE620;
    height = D_800BE624;
    address = arg1;
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xFA000000;
        command->second = (arg3 & 0xFF) | ~0xFF;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->second = -0x805;
        command->first = 0xFC11FE23;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xEF000CFF;
        command->second = 0x00504340;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->first = 0xD9000000;
        command->second = 0;
    }
    {
        Packet *command = (Packet *)arg0;
        arg0 += sizeof(Packet);
        command->second = -1;
        command->first = 0xD7000002;
    }
    y = 0;
    sp34 = height;
    if (height != 0) {
        doubleWidth = width * 2;
        loadSize = (width * 4) - 1;
        stride = doubleWidth >> 3;
        do {
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->second = address + 0x80000000;
                command->first = 0xFD100000;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xF5100000;
                command->second = 0x07000000;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xE6000000;
                command->second = 0;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xF3000000;
                if (loadSize < 0x7FFU) {
                    size = loadSize;
                } else {
                    size = 0x7FF;
                }
                if (stride == 0) {
                    numerator = 1;
                } else {
                    numerator = stride;
                }
                if (stride == 0) {
                    denominator = 1;
                } else {
                    denominator = stride;
                }
                command->second = (((numerator + 0x7FF) / denominator) & 0xFFF) |
                                  0x07000000 | ((size & 0xFFF) << 12);
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xE7000000;
                command->second = 0;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = (((((u32)(doubleWidth + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
                command->second = 0;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xF2000000;
                command->second = ((((width - 1) * 4) & 0xFFF) << 12) | 0xC;
            }
            nextY = y + 4;
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = ((((width - arg2) * 4) & 0xFFF) << 12) | 0xE4000000 | ((nextY * 4) & 0xFFF);
                command->second = (y * 4) & 0xFFF;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xE1000000;
                command->second = 0;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xF1000000;
                command->second = 0x04000400;
            }
            {
                Packet *command = (Packet *)arg0;
                arg0 += sizeof(Packet);
                command->first = 0xE7000000;
                command->second = 0;
            }
            y = nextY;
            address += width * 8;
        } while (nextY < (u32)sp34);
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6418 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6418.s")
void func_100043B4(s32, s32);
extern u8 D_80038080;
extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D66F0 CURRENT (415) */
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
            func_100043B4(D_800BE570, 3);
            D_800BE570 = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D66F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D66F0.s")
void *func_1501A680(void *);
s32 func_10003C40(s32, s32, s32, s32);
void *func_151D6418(u8 *, s32, s32, s32);
void *func_151D5E90(u8 *, s32, s32, s32);
extern s32 D_8002AAE8[];
extern u8 D_800BE9C0;
extern u8 D_800BEAC0;

typedef struct Game203340Command { u32 first, second; } Game203340Command;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6778 CURRENT (4473) */
u8 *func_151D6778(u8 *arg0) {
    Game203340Command *cursor = (Game203340Command *)arg0;
    Game203340Command *command;
    s32 allocated;
    s32 *buffer;
    u32 flags;

    flags = (u8)D_800BE574;
    if ((flags == 0 && D_800BE9F0 != 0x32 && D_800BE9F0 != 0x33) || D_800BEAC0 != 0) {
        return (u8 *)cursor;
    }
    if (flags != 0) {
        buffer = &D_800BE570;
        command = cursor++;
        command->first = 0xE7000000;
        command->second = 0;
        if (*buffer != 0) {
            cursor = func_151D6418((u8 *)cursor, *buffer, 0, flags);
        } else {
            allocated = func_10003C40(D_800BE620 * D_800BE624 * 2, 1, 3, 1);
            *buffer = allocated;
            if (allocated == 0) {
                return (u8 *)cursor;
            }
        }
        command = cursor++;
        command->first = ((D_800BE620 - 1) & 0xFFF) | 0xFF100000;
        command->second = *buffer;
        command = cursor++;
        command->first = 0xED000000;
        command->second = (((s32)((f32)D_800BE620 * 4.0f) & 0xFFF) << 12) |
                           ((s32)((f32)D_800BE624 * 4.0f) & 0xFFF);
        cursor = func_151D5E90((u8 *)cursor, D_8002AAE8[D_800BE9C0], 0, 4);
        command = cursor++;
        command->first = 0xEF082C3F;
        command->second = 0x552230;
        command = cursor++;
        command->first = 0xD9FFFFFF;
        command->second = 0x220405;
        cursor = func_1501A680(cursor);
    }
    return (u8 *)cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6778 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6778.s")
