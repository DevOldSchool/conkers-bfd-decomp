#include "types.h"

/*
 * Reviewed source unit: src/game/game_131A90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151045E0(s32 arg0, s32 arg1, s32 arg2) {
}
s32 func_151045F4(s32 arg0, s32 arg1) {
    return 1;
}
void func_15104608(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}
s32 func_15104620(s32 arg0, s32 arg1) {
    return 1;
}
typedef struct Game131A90Surface {
    s32 height;
    s32 *vertexOffsets;
    u8 *vertices;
    s32 owner;
} Game131A90Surface;

s32 func_150A3A70(s32, s32);
void func_1510F800(s32);
extern f32 D_800A2370;
extern Game131A90Surface D_800D3300[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15104634 CURRENT (5352) */
s32 func_15104634(f32 arg0, f32 arg1, f32 arg2, f32 *arg3) {
    s32 selected[40];
    f32 x[3];
    f32 z[3];
    Game131A90Surface *surface;
    s32 *offset;
    s16 *vertex;
    f32 dx;
    f32 dz;
    f32 distance;
    f32 nearest;
    s32 count;
    s32 selectedCount;
    s32 best;
    s32 i;
    s32 j;

    func_1510F800(0);
    count = func_150A3A70((s32) arg0, (s32) arg1);
    if (count == 0) {
        return 0;
    }
    selectedCount = 0;
    surface = D_800D3300;
    for (i = 0; i < count; i++, surface++) {
        offset = surface->vertexOffsets;
        for (j = 0; j < 3; j++, offset++) {
            vertex = (s16 *) (surface->vertices + *offset);
            x[j] = (f32) vertex[0];
            z[j] = (f32) vertex[2];
        }
        dx = x[0] - x[1];
        dz = z[1] - z[0];
        if ((z[2] * dx + dz * x[2] + -(z[0] * dx + dz * x[0])) > 0.0f) {
            selected[selectedCount++] = i;
        }
    }
    best = -1;
    if (selectedCount == 0) {
        return 0;
    }
    nearest = D_800A2370;
    for (i = 0; i < selectedCount; i++) {
        j = selected[i];
        distance = (f32) D_800D3300[j].height * 0.00390625f - arg2;
        if (distance < 0.0f) {
            distance = -((f32) D_800D3300[j].height * 0.00390625f - arg2);
        }
        if (distance < nearest || best == -1) {
            nearest = distance;
            best = j;
        }
    }
    *arg3 = (f32) D_800D3300[best].height * 0.00390625f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15104634 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131A90/func_15104634.s")
