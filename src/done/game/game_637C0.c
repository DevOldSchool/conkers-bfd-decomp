#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_637C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

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
    Vec3f position;
} Game637C0Target;

void func_150440A0(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern Game637C0Actor D_800CC2D0[];
extern Game637C0Target *D_800DBFF0;

void func_15036310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game637C0Matrix *matrix;
    f32 up[3];
    f32 position[3];
    f32 direction[3];
    f32 side[3];
    Game637C0Actor *actor;
    f32 swap;

    actor = &D_800CC2D0[arg1];
    if (actor->matrices != 0) {
        matrix = &actor->matrices[arg2];
        position[0] = matrix->values[12];
        position[1] = matrix->values[13];
        position[2] = matrix->values[14];
        direction[0] = D_800DBFF0->position.x - position[0];
        direction[1] = D_800DBFF0->position.y - position[1];
        direction[2] = D_800DBFF0->position.z - position[2];
        if (arg3 != 0) {
            swap = direction[0];
            direction[0] = direction[2];
            direction[2] = -swap;
        }
        up[0] = 0.0f;
        up[1] = 1.0f;
        up[2] = 0.0f;
        side[0] = direction[1] * up[2] - direction[2] * up[1];
        side[1] = direction[2] * up[0] - direction[0] * up[2];
        side[2] = direction[0] * up[1] - direction[1] * up[0];
        up[0] = direction[1] * side[2] - direction[2] * side[1];
        up[1] = direction[2] * side[0] - direction[0] * side[2];
        up[2] = direction[0] * side[1] - direction[1] * side[0];
        func_150440A0(matrix, position[0], position[1], position[2],
                       position[0] - direction[0], position[1] - direction[1],
                       position[2] - direction[2], up[0], up[1], up[2]);
        if (actor->scaleXZ != 1.0f) {
            matrix->values[0] *= actor->scaleXZ;
            matrix->values[4] *= actor->scaleXZ;
            matrix->values[8] *= actor->scaleXZ;
            matrix->values[2] *= actor->scaleXZ;
            matrix->values[6] *= actor->scaleXZ;
            matrix->values[10] *= actor->scaleXZ;
        }
        if (actor->scaleY != 1.0f) {
            matrix->values[1] *= actor->scaleY;
            matrix->values[5] *= actor->scaleY;
            matrix->values[9] *= actor->scaleY;
        }
    }
}
