#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0E60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151739B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { u8 red, green, blue; } Game1A0E60Color;
typedef struct {
    u8 pad0[0xC];
    Game1A0E60Color color;
    u8 alpha;
} Game1A0E60Vertex;
typedef struct {
    Game1A0E60Color *colors;
    u16 *indices;
    s32 count;
} Game1A0E60Group;
typedef struct { u8 pad0[0x21]; u8 flags; } Game1A0E60State;
extern Game1A0E60State *D_800B0DF0;
extern Game1A0E60Vertex *D_800B0E10;
extern Game1A0E60Group **D_800B0E30;
extern u8 *D_800B0E34;
extern Game1A0E60Color *D_800BE510;
extern Game1A0E60Color ***D_800BE520;
extern u16 *D_800BE524;
extern u8 D_800BE9C0;
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151739B0 CURRENT (2332) */
void func_151739B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 limit;
    s32 count, flags, start, groupIndex, i, colorOffset;
    s32 red, green, blue;
    Game1A0E60Vertex *vertices, *vertex;
    Game1A0E60Group *group;
    Game1A0E60Color *color, *source;
    u16 *indices;
    Game1A0E60Group *groups;

    count = D_800B0E34[arg0];
    if (count != 0) {
        flags = D_800B0DF0->flags;
        if (!(flags & 4)) {
            if (arg1 == 0 && !(flags & 1)) return;
            if (arg1 == 1 && !(flags & 2)) return;
        }
        start = 0;
        if (arg3 == 0xFF) {
            limit = count;
        } else {
            start = arg3;
            if (arg3 >= count) return;
            limit = arg3 + 1;
        }
        if (arg1 == 0) {
            vertices = D_800B0E10;
        } else {
            vertices = *(Game1A0E60Vertex **)((u8 *)D_800DBEF4 + arg4 * 0xA0 + D_800BE9C0 * 4 + 0x20);
        }
        groups = D_800B0E30[arg0];
        groupIndex = start;
        if (start < limit) {
            group = &groups[start];
            do {
                count = group->count;
                indices = group->indices;
                source = group->colors;
                i = 0;
                if (count > 0) {
                    colorOffset = 0;
                    do {
                        count = *indices;
                        if (!(D_800B0DF0->flags & 4)) {
                            if (arg1 == 0) color = &D_800BE510[count];
                            else color = (Game1A0E60Color *)((u8 *)D_800BE510 + D_800BE524[arg4] * 3 + count * 3);
                        } else {
                            color = (Game1A0E60Color *)((u8 *)D_800BE520[arg0][groupIndex] + colorOffset);
                        }
                        red = color->red;
                        vertex = &vertices[count];
                        vertex->color.red = (((source->red - red) * arg2) >> 8) + red;
                        green = color->green;
                        vertex->color.green = (((source->green - green) * arg2) >> 8) + green;
                        blue = color->blue;
                        vertex->color.blue = (((source->blue - blue) * arg2) >> 8) + blue;
                        i++;
                        indices++;
                        colorOffset += 3;
                        source++;
                    } while (i < group->count);
                }
                groupIndex++;
                group++;
            } while (groupIndex != limit);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151739B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0E60/func_151739B0.s")
void func_151739B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15173C60(s32 arg0, s32 arg1) {
    func_151739B0(0, 0, arg0, arg1, 0);
}
/* Call context: func_151149AC: unique active project prototype */
/* Call context: func_151739B0: unique active project prototype */
s32 func_151149AC(u8);
extern s32 D_800DBEF4;

void func_15173C90(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_a0;

    temp_v0 = func_151149AC(arg2);
    if (temp_v0 != 0) {
        temp_a0 = *(u16 *)((u8 *)temp_v0 + 0x54) & 0xFFFF7FFF;
        func_151739B0(temp_a0, 1, arg0, arg1, (s32) (temp_v0 - D_800DBEF4) / 160);
    }
}
