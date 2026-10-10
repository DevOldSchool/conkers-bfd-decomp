#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_DF930.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 */

s32 func_150B2480(s32 arg0, s32 arg1) {
    return 0xA;
}
u32 func_150ADA20(void);
void func_1514C678(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
void func_151D5404(f32 *, s32, s32, s32, s32, s32, s32, s32);
void func_151D3FF4(s32, u8, s32);

void func_150B2494(void *arg0, s32 arg1, s32 arg2) {
    f32 position[3];

    position[0] = *(f32 *)((u8 *)arg0 + 0x14);
    position[1] = *(f32 *)((u8 *)arg0 + 0x180);
    position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    func_1514C678(position[0], position[1], position[2], 135.0f,
                  0, 0xFF, (func_150ADA20() % 15U) + 0x1B,
                  7, 0, 0.0f, 0, 0xFF);
    func_151D5404(position, 0x44BBC000, 0x453B8000, 0x39AEC33E,
                  0xC, 0xF, 0xFF, 0);
    func_151D3FF4((s32)position, 0xFF, 0);
}
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_15156190(s32, u8, s32, u8, s32);
f32 func_150ADA68(void);
extern f32 D_8009F900;
extern f32 D_8009F904;
extern f32 D_8009F908;
extern f32 D_8009F90C;
extern f32 D_8009F910;
extern f32 D_8009F914;

typedef struct GameDF930Particle {
    f32 position[3];
    f32 velocity[3];
    f32 start, end;
    u8 color0[4], color1[4];
    u8 mode;
    u8 pad29;
    s16 count;
    s16 flags;
    u8 pad2E[2];
    f32 size;
    u8 alpha;
    u8 pad35;
    s16 kind, type;
} GameDF930Particle;

s32 func_150B2570(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    f32 scale;
    GameDF930Particle particle;
    s16 angle;
    f32 directionCos;
    f32 directionSin;
    f32 pitchCos;

    directionCos = func_151423D8((u8)(arg8 - 0x40));
    directionSin = func_151423D8((u8)arg8);
    angle = (func_150ADA20() % 21U) - 0x1E;
    pitchCos = func_151423D8((u8)(angle - 0x40));
    scale = func_151423D8((u8)angle);
    scale = 10.0f * scale;
    particle.position[0] = arg2;
    particle.position[1] = arg3;
    particle.position[2] = arg4;
    particle.velocity[0] = scale * directionCos;
    particle.velocity[1] = -10.0f * pitchCos;
    particle.velocity[2] = scale * directionSin;
    particle.start = func_150ADA68() * D_8009F900 + D_8009F904;
    particle.end = func_150ADA68() * D_8009F908 + D_8009F90C;
    func_151429E0(8, &particle.color0[0], &particle.color0[1], &particle.color0[2]);
    func_151429E0(8, &particle.color1[0], &particle.color1[1], &particle.color1[2]);
    particle.color0[3] = 0xFF;
    particle.color1[3] = 0xFF;
    particle.mode = 9;
    particle.count = func_150ADA20() % 7U + 0x12;
    particle.size = func_150ADA68() * D_8009F910 + D_8009F914;
    particle.flags = 0x1601;
    particle.alpha = 0xFF;
    particle.kind = 8;
    particle.type = 0x1F;
    func_15156190((s32)&particle, 1, 0, arg14, 1);
    return 1;
}
