#include "types.h"

/*
 * Reviewed source unit: src/game/game_42DD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
 */

typedef struct Game42DD0Range {
    u8 *start;
    u8 *end;
} Game42DD0Range;

extern Game42DD0Range D_80082F80[];
extern u8 (*D_80085990[])[224];
extern u8 *D_80085994[];
u8 *func_10003C6C(s32, s32, s32, s32, s32);
void func_10004514(s32, s32, s32, s32);
void func_10004074(s32);
void func_15015A38(void *, s32, s32);

void func_15015920(s16 arg0) {
    u8 *buffer;
    u8 *cursor;
    s32 index;

    buffer = func_10003C6C(0x2800, 1, 2, 1, 0);
    func_10004514((s32)D_80082F80[arg0].start, (s32)buffer, (s32)D_80082F80[arg0].end - (s32)D_80082F80[arg0].start, 1);
    cursor = buffer;
    index = 0;
    while ((u32)(cursor + 0xF) < (u32)buffer + (u32)D_80082F80[arg0].end - (u32)D_80082F80[arg0].start) {
        func_15015A38(cursor, index, arg0);
        cursor += (cursor[4] << 24) + (cursor[5] << 16) + (cursor[6] << 8) + cursor[7];
        index++;
    }
    func_10004074((s32)buffer);
}
void func_15015A38(void *arg0, s32 glyph, s32 bank) {
    u8 *source = arg0;
    s32 x;
    s32 y;
    s32 input_offset;
    s32 row_stride;
    s32 swizzle;
    s32 shade;
    s32 run;
    s32 i;

    D_80085994[bank][glyph * 4] = source[0] + 1;
    D_80085994[bank][glyph * 4 + 1] = source[1] + 1;
    D_80085994[bank][glyph * 4 + 2] = source[2];
    D_80085994[bank][glyph * 4 + 3] = source[3];
    input_offset = 8;
    row_stride = (D_80085994[bank][glyph * 4] + 7) & 0xFFF8;

    for (x = 0; x < D_80085994[bank][glyph * 4]; x++) {
        D_80085990[bank][glyph][x] = 0;
    }
    for (y = 1; y < D_80085994[bank][glyph * 4 + 1] + 1; y++) {
        if ((y & 1) == 0) {
            swizzle = 0;
        } else {
            swizzle = 4;
        }
        for (x = 0; x < D_80085994[bank][glyph * 4]; x++) {
            if (x == 0) {
                D_80085990[bank][glyph][(x ^ swizzle) + y * row_stride] = 0;
            } else {
                run = (source[input_offset] & 0xF) + 1;
                shade = source[input_offset] & 0xF0;
                input_offset++;
                for (i = 0; i < run; i++) {
                    D_80085990[bank][glyph][((x + i) ^ swizzle) + y * row_stride] = shade;
                }
                x += run - 1;
            }
        }
        for (; x < row_stride; x++) {
            D_80085990[bank][glyph][(x ^ swizzle) + y * row_stride] = 0;
        }
    }
    for (x = 0; x < row_stride; x++) {
        D_80085990[bank][glyph][x + y * row_stride] = 0;
    }
}
