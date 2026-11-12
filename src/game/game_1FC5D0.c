#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FC5D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CF120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x, y, z, distance;
    u8 pad10[4];
    f32 wave;
    u8 pad18[0x10];
} Game1FC5D0Point;

typedef struct {
    u8 pad00[0x20];
    f32 limit, phase;
} Game1FC5D0Config;

typedef struct {
    u8 pad00[0x25];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 head;
    s8 tail;
    u8 pad2F[0x65];
    Game1FC5D0Point *points;
    Game1FC5D0Config *config;
} Game1FC5D0Actor;

f32 func_15047D60(f32);
extern f32 D_800AB014, D_800AB018, D_800AB01C, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CF120 */
s32 func_151CF120(Game1FC5D0Actor *arg0) {
    Game1FC5D0Config *config;
    Game1FC5D0Point *points;
    s32 count;
    f32 total;
    f32 limit;

    count = arg0->count;
    config = arg0->config;
    points = arg0->points;
    if (count >= 2) {
        s32 index;
        s32 current;
        Game1FC5D0Point *point;

        total = 0.0f;
        index = arg0->tail - 1;
        if (index < 0) index = arg0->capacity - 1;
        if (index != arg0->head) {
            limit = config->limit;
            do {
                current = index;
                index--;
                if (index < 0) index = arg0->capacity - 1;
                point = &points[current];
                total += point->distance;
                if (limit < total) {
                    if (point->distance != 0) {
                        Game1FC5D0Point *previous;
                        f32 ratio;
                        f32 px, py, pz;
                        f32 dx, dy, dz;

                        ratio = (total - limit) / point->distance;
                        previous = &points[index];
                        px = previous->x; py = previous->y; pz = previous->z;
                        dx = px - point->x; dy = py - point->y; dz = pz - point->z;
                        previous->x = px - dx * ratio;
                        previous->y = py - dy * ratio;
                        previous->z = pz - dz * ratio;
                        point->distance *= 1.0f - ratio;
                    }
                    if (index != arg0->head) {
                        do {
                            arg0->head++;
                            if (arg0->head == arg0->capacity) {
                                arg0->head = 0;
                            }
                            arg0->count--;
                        } while (index != arg0->head);
                    }
                    limit = config->limit;
                    total = limit;
                }
            } while (index != arg0->head);
            count = arg0->count;
        }
    }
    if (count >= 2) {
        f32 amplitude;
        f32 phase;
        s32 index;

        total = D_800AB014;
        amplitude = 0.0f;
        index = arg0->tail;
        phase = config->phase;
        limit = D_800AB018;
        do {
            Game1FC5D0Point *point;
            f32 result;
            f32 distance;

            index--;
            if (index < 0) index = arg0->capacity - 1;
            point = &points[index];
            result = func_15047D60(phase);
            point->wave = result * amplitude;
            distance = point->distance;
            amplitude += distance * limit;
            phase += distance * total;
        } while (index != arg0->head);
    }
    config->phase += D_800AB01C * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CF120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC5D0/func_151CF120.s")
