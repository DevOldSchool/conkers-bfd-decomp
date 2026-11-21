#include "types.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_48B10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct Game48B10Actor {
    u8 pad00[4];
    u8 type;
    u8 pad05[0x1C3];
    u8 buffer;
    u8 pad1C9[0xC3];
    struct Game48B10Vertex *vertices[2][2];
} Game48B10Actor;
typedef struct Game48B10Vertex {
    s16 position[3];
    u16 flags;
    s16 uv[2];
    u8 r, g, b, a;
} Game48B10Vertex;
typedef struct Game48B10Color { u8 r, g, b; } Game48B10Color;
extern Game48B10Color *D_80084040[];
extern u16 D_800C57A0[];

void func_1501B660(Game48B10Actor *arg0, f32 *arg1, s32 arg2) {
    Game48B10Vertex *vertices;
    Game48B10Color *first;
    Game48B10Color *second;
    f32 value;
    f32 interval;
    f32 fraction;
    u8 sample;
    u32 r, g, b;
    u8 outR, outG, outB;
    s32 previous;
    s32 group;
    s32 i;
    u8 steps;

    vertices = arg0->vertices[arg0->buffer][D_800BE9C0];
    if (vertices == NULL) {
        return;
    }
    previous = -1;
    for (i = 0; i < D_800C57A0[arg0->type]; i++) {
        if (vertices[i].flags & 0x7F00) {
            group = (vertices[i].flags & 0x7F00) >> 8;
            if (group != previous) {
                if (group >= 6) {
                    continue;
                }
                previous = group;
                group--;
                steps = D_80096920[group];
                interval = 1.0f / (f32) (steps - 1);
                if (arg2 != 0) {
                    value = arg1[group];
                } else {
                    value = *arg1;
                }
                sample = value / interval;
                first = &D_80084040[group][sample];
                second = &D_80084040[group][sample + 1];
                fraction = (value - (f32) (u32) sample * interval) / interval;
                r = first->r;
                outR = (f32) (s32) (second->r - r) * fraction + (f32) r;
                g = first->g;
                outG = (f32) (s32) (second->g - g) * fraction + (f32) g;
                b = first->b;
                outB = (f32) (s32) (second->b - b) * fraction + (f32) b;
            }
            vertices[i].r = outR;
            vertices[i].g = outG;
            vertices[i].b = outB;
        }
    }
}
