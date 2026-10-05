#include "types.h"

/*
 * Reviewed source unit: src/game/game_42DD0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15015920
 * - func_15015A38
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015920 CURRENT (1714) */
void func_15015920(s16 arg0) {
    u8 *buffer;
    u8 *cursor;
    s32 index;
    register u8 *range;

    buffer = func_10003C6C(0x2800, 1, 2, 1, 0);
    range = (u8 *)&D_80082F80[arg0];
    func_10004514(*(s32 *)range, (s32)buffer,
                  (s32)(*(u32 *)(range + 4) - *(u32 *)range), 1);
    cursor = buffer;
    index = 0;
    if (((u32)buffer + 0xF) <
        ((u32)buffer + *(u32 *)(range + 4) - *(u32 *)range)) {
        do {
            func_15015A38(cursor, index, arg0);
            cursor = (u8 *)((u32)cursor + ((u32)cursor[4] << 24) +
                            ((u32)cursor[5] << 16) +
                            ((u32)cursor[6] << 8) + cursor[7]);
            index++;
        } while (((u32)cursor + 0xF) <
                 ((u32)buffer + *(u32 *)(range + 4) - *(u32 *)range));
    }
    func_10004074((s32)buffer);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_42DD0/func_15015920.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015A38 CURRENT (8173) */
void func_15015A38(void *arg0, s32 glyph, s32 bank) {
    u8 *source = arg0;
    s32 x;
    s32 y;
    s32 input_offset;
    s32 row_stride;
    s32 swizzle;
    s32 packed;
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
        swizzle = (y & 1) ? 4 : 0;
        for (x = 0; x < D_80085994[bank][glyph * 4]; x++) {
            if (x == 0) {
                D_80085990[bank][glyph][(x ^ swizzle) + y * row_stride] = 0;
            } else {
                packed = source[input_offset++];
                run = (packed & 0xF) + 1;
                for (i = 0; i < run; i++) {
                    D_80085990[bank][glyph][((x + i) ^ swizzle) + y * row_stride] = packed & 0xF0;
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
#endif /* CONKER_DEFERRED_CANDIDATE func_15015A38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_42DD0/func_15015A38.s")
