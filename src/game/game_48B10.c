#include "types.h"

/*
 * Reviewed source unit: src/game/game_48B10.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501B660
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game48B10Actor {
    u8 pad00[4];
    u8 type;
    u8 pad05[0x1C3];
    u8 buffer;
} Game48B10Actor;
typedef struct Game48B10Vertex {
    s16 position[3];
    u16 flags;
    s16 uv[2];
    u8 r, g, b, a;
} Game48B10Vertex;
typedef struct Game48B10Color { u8 r, g, b; } Game48B10Color;
extern Game48B10Color *D_80084040[];
extern u8 D_80096920[];
extern u8 D_800BE9C0;
extern u16 D_800C57A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501B660 CURRENT (4726) */
void func_1501B660(Game48B10Actor *arg0, f32 *arg1, s32 arg2) {
    Game48B10Vertex *vertex;
    Game48B10Color *colors;
    Game48B10Color *first;
    Game48B10Color *second;
    f32 value;
    f32 interval;
    f32 fraction;
    u32 sample;
    u32 r, g, b;
    u8 outR, outG, outB;
    s32 previous;
    s32 group;
    s32 offset;
    u16 count;

    vertex = *(Game48B10Vertex **) ((u8 *) arg0 + 0x28C + arg0->buffer * 8 + D_800BE9C0 * 4);
    if (vertex != 0) {
        previous = -1;
        count = D_800C57A0[arg0->type];
        offset = 0;
        if (count > 0) {
            do {
                offset += 0x10;
                group = (vertex->flags & 0x7F00) >> 8;
                if (group != 0) {
                    if (group != previous) {
                        if (group >= 6) {
                            goto next_vertex;
                        }
                        previous = group;
                        group--;
                        if (arg2 != 0) {
                            value = arg1[group];
                        } else {
                            value = *arg1;
                        }
                        colors = D_80084040[group];
                        interval = 1.0f / (f32) (D_80096920[group] - 1);
                        sample = (u32) (value / interval) & 0xFF;
                        first = &colors[sample];
                        second = &colors[sample] + 1;
                        fraction = (value - (f32) sample * interval) / interval;
                        r = first->r;
                        outR = (u32) ((f32) ((s32) second->r - (s32) r) * fraction + (f32) r) & 0xFF;
                        g = first->g;
                        outG = (u32) ((f32) ((s32) second->g - (s32) g) * fraction + (f32) g) & 0xFF;
                        b = first->b;
                        outB = (u32) ((f32) ((s32) second->b - (s32) b) * fraction + (f32) b) & 0xFF;
                    }
                    vertex->r = outR;
                    vertex->g = outG;
                    vertex->b = outB;
                    count = D_800C57A0[arg0->type];
                }
next_vertex:
                vertex++;
            } while (offset < count * 0x10);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501B660 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48B10/func_1501B660.s")
