#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D5C0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
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

void func_15010110(void) {
    Game3D5C0Request request;
    s32 i;
    func_15195AA8(D_800B0E00[0], D_80090298[0x50 / 4], 0, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E00[1], D_80090298[0x50 / 4], 0, -1, 0, 1, 0, -8);
    request.unused = 0;
    for (i = 0; i < 6; i++) {
        request.position = ((Game3D5C0PositionBlock *)D_800963A0)[i];
        request.enabled = i + 1;
        request.distance = fabsf(request.position.values[1] - request.position.values[4]);
        func_151ACBD4(&request, 0);
    }
}
