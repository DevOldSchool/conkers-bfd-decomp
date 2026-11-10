#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A7260.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct {
    s16 x;
    u8 pad2[0xE];
} Game179DB0Vertex;

typedef struct {
    u8 pad0[0x18];
    f32 velocity[2];
    f32 phase[2];
    f32 magnitude;
    u8 pad2C[0xC];
} Game179DB0State;

typedef struct {
    u8 pad0[4];
    Game179DB0Vertex *first;
    Game179DB0Vertex *second;
    u8 padC[8];
} Game179DB0Entry;

extern Game179DB0State D_8008D0B0[];
extern Game179DB0Entry D_800DDE80[];
f32 func_15047D60(f32);

void func_15179DB0(u8 arg0) {
    static const u8 sIndices[] = { 4, 9, 13, 14, 15, 17, 19 };
    s16 height;
    s32 i;
    s32 j;
    Game179DB0Vertex *buffers[2];
    f32 *phases[2];
    f32 *velocities[2];

    buffers[1] = D_800DDE80[arg0].first;
    buffers[0] = D_800DDE80[arg0].second;
    phases[0] = &D_8008D0B0[arg0].phase[0];
    phases[1] = &D_8008D0B0[arg0].phase[1];
    velocities[0] = &D_8008D0B0[arg0].velocity[0];
    velocities[1] = &D_8008D0B0[arg0].velocity[1];
    for (i = 0; i < 2; i++) {
        height = D_8008D0B0[arg0].magnitude * func_15047D60(*phases[i] * 0.017453292f);
        buffers[i][2].x = height;
        buffers[i][3].x = height;
        height = -(height >> 1);
        for (j = 0; j < 7; j++) {
            buffers[i][sIndices[j]].x = height;
        }
        buffers[i][6].x = height + 0x12;
        buffers[i][8].x = height - 0x12;
        *phases[i] += *velocities[i];
        if (*phases[i] >= 360.0f) {
            *phases[i] -= 360.0f;
        }
    }
}
