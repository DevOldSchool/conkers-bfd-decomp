#include "types.h"

/*
 * Reviewed source unit: src/game/game_10EA20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1570
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10EA20Actor {
    s32 present;
    u8 pad4[0x10];
    f32 x;
    f32 y;
    union { f32 value; s32 bits; } z;
    u8 pad20[0x56];
    u16 owner;
    u8 pad78[0x5A];
    s16 xExtent;
    s16 yExtent;
    s16 yOffset;
    u8 padD8[0x4C];
    u8 index;
    u8 excluded;
    u8 pad126[0xA4];
    u8 active;
    u8 pad1CB[0x161];
} Game10EA20Actor;

void func_15047390(f32 *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15049440(f32 *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_1505D1C4(f32, f32, s32, s32, s32, s32, s32, s32);
f32 sqrtf(f32);
__pragma(1, sqrtf);
extern u8 D_800C3E78;
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E1570 CURRENT (775) */
s32 func_150E1570(Game10EA20Actor *arg0, f32 arg1, f32 arg2, f32 arg3,
                  f32 arg4, f32 arg5, f32 arg6, register s32 arg7, s32 arg8) {
    f32 matrix[16];
    Game10EA20Actor *actor;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 length;
    s32 result;
    s32 distance;
    s32 index;
    s32 best;
    s32 bestDistance;
    s32 ownerIndex;

    bestDistance = 0;
    result = 0;
    func_15047390(matrix, arg1, arg2, arg3, arg4, arg5, arg6, 0.0f, 1.0f, 0.0f);
    dx = arg1 - arg4;
    dy = arg2 - arg5;
    dz = arg3 - arg6;
    best = -1;
    actor = (Game10EA20Actor *)D_800CC2D0;
    index = 0;
    length = sqrtf(dx * dx + dy * dy + dz * dz);
    ownerIndex = arg0 != 0 ? arg0->index - 1 : -1;
    do {
        if (actor->present != 0 && index != arg7 && actor->active != 0 &&
            actor->excluded == 0 && index != ownerIndex) {
            distance = func_15049440(matrix, actor->x, actor->y + (f32)actor->yOffset,
                                    actor->z.value, (f32)actor->xExtent,
                                    (f32)actor->yExtent, 0.0f, length, 10.0f, 10.0f);
            if (distance != 0 && (best == -1 || distance < bestDistance)) {
                best = index;
                bestDistance = distance;
            }
        }
        index++;
        actor++;
    } while (index != 25);
    if (best != -1) {
        actor = (Game10EA20Actor *)(D_800CC2D0 + best * 0x32C);
        result = func_1505D1C4(actor->x, (f32)actor->yOffset + actor->y,
                              actor->z.bits, arg8, D_800C3E78, 0, 0, 0);
        actor->owner = arg0->owner;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E1570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EA20/func_150E1570.s")
