#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D5C0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15010110
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game3D5C0PositionBlock {
    f32 values[6];
} Game3D5C0PositionBlock;

typedef struct Game3D5C0Request {
    s8 enabled;
    u8 pad1[3];
    Game3D5C0PositionBlock position;
    f32 distance;
    s8 unused;
} Game3D5C0Request;

void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
void func_151ACBD4(Game3D5C0Request *, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern s32 D_80090298[];
extern s32 D_800963A0[];
extern s32 D_800B0E00[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010110 CURRENT (1750) */
void func_15010110(void) {
    Game3D5C0Request request;
    s8 var_s0;
    s8 temp_s2;
    struct Game3D5C0PositionBlock *var_s1;

    func_15195AA8(D_800B0E00[0], D_80090298[0x50 / 4], 0, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E00[1], D_80090298[0x50 / 4], 0, -1, 0, 1, 0, -8);
    request.unused = 0;
    var_s1 = (struct Game3D5C0PositionBlock *)D_800963A0;
    var_s0 = 0;
    do {
        temp_s2 = var_s0 + 1;
        request.position = *var_s1;
        request.enabled = temp_s2;
        request.distance = fabsf(request.position.values[1] - request.position.values[4]);
        func_151ACBD4(&request, 0);
        var_s0 = temp_s2;
        var_s1 += 1;
    } while (temp_s2 != 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010110 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D5C0/func_15010110.s")
