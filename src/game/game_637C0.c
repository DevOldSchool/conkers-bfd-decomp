#include "types.h"

/*
 * Reviewed source unit: src/game/game_637C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15036310
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { f32 x, y, z; } Game637C0Vector;
typedef struct { f32 values[16]; } Game637C0Matrix;
typedef struct {
    u8 pad00[0x14C];
    f32 scaleXZ, scaleY;
    u8 pad154[0x80];
    Game637C0Matrix *matrices;
    u8 pad1D8[0x154];
} Game637C0Actor;
typedef struct {
    u8 pad00[0x2F8];
    Game637C0Vector position;
} Game637C0Target;

void func_150440A0(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern Game637C0Actor D_800CC2D0[];
extern Game637C0Target *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15036310 CURRENT (5406) */
void func_15036310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game637C0Matrix *matrix;
    f32 up[3];
    f32 position[3];
    f32 direction[3];
    f32 side[3];
    Game637C0Actor *actor;
    f32 saved_side_x;
    f32 swap;
    f32 factor;
    register f32 unit_y;
    register f32 zero_x;
    register f32 zero_z;

    actor = &D_800CC2D0[arg1];
    matrix = (Game637C0Matrix *)((u32)actor->matrices + ((u32)arg2 << 6));
    if (actor->matrices != 0) {
        zero_x = 0.0f;
        unit_y = 1.0f;
        zero_z = 0.0f;
        position[0] = matrix->values[12];
        position[1] = matrix->values[13];
        position[2] = matrix->values[14];
        direction[0] = D_800DBFF0->position.x - position[0];
        direction[1] = D_800DBFF0->position.y - position[1];
        direction[2] = D_800DBFF0->position.z - position[2];
        if (arg3 != 0) {
            swap = direction[2];
            direction[2] = -direction[0];
            direction[0] = swap;
        }
        side[0] = direction[1] * zero_z - unit_y * direction[2];
        saved_side_x = side[0];
        side[1] = direction[2] * zero_x - zero_z * direction[0];
        side[2] = direction[0] * unit_y - zero_x * direction[1];
        up[0] = direction[1] * side[2] - side[1] * direction[2];
        up[1] = direction[2] * saved_side_x - side[2] * direction[0];
        up[2] = direction[0] * side[1] - saved_side_x * direction[1];
        func_150440A0(matrix, position[0], position[1], position[2],
                       position[0] - direction[0], position[1] - direction[1],
                       position[2] - direction[2], up[0], up[1], up[2]);
        factor = actor->scaleXZ;
        if (1.0f != factor) {
            matrix->values[0] *= factor;
            matrix->values[4] *= actor->scaleXZ;
            matrix->values[8] *= actor->scaleXZ;
            matrix->values[2] *= actor->scaleXZ;
            matrix->values[6] *= actor->scaleXZ;
            matrix->values[10] *= actor->scaleXZ;
        }
        factor = actor->scaleY;
        if (1.0f != factor) {
            matrix->values[1] *= factor;
            matrix->values[5] *= actor->scaleY;
            matrix->values[9] *= actor->scaleY;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15036310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_637C0/func_15036310.s")
