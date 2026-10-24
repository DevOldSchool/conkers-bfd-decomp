#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12BD10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FE860
 * - func_150FEBC8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12BD10State {
    u8 pad0[0x1D4];
    s32 field1D4;
} Game12BD10State;

void func_15145EA4(s32 *, s32 *, s32, s32);

extern u8 D_80088BA0;
extern s32 D_800A2000;

f32 func_150ADA68(void);
void func_150FEC28(void *, s32, void *, void *, void *, s32, s32);
void func_15145740(void *, void *, void *, void *, f32);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_151D5148(void *);
void *func_151C229C(void *, void *, void *, void *, s32, s32, f32, f32,
                   f32, f32, f32, s32, void *, s32, s32, s32, s32, s32,
                   s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern u8 D_800A200C[];
extern u8 D_800A2018[];
extern u8 D_800A2024[];
extern f32 D_800A2030;
extern f32 D_800A2034;
extern f32 D_800A2038;
f32 fabsf(f32);
f32 sqrtf(f32);
#pragma intrinsic(fabsf)
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FE860 CURRENT (775) */
void func_150FE860(Game12BD10State *arg0, s32 arg1, s32 arg2) {
    Vec3f position;
    Vec3f direction;
    Vec3f right;
    Vec3f up;
    Vec3f origin;
    Vec3f delta;
    f32 sideX;
    f32 sideZ;
    s32 matrix;
    s32 sources[3];
    s32 destinations[3];
    s32 matrixBase;
    f32 threshold;
    f32 inverse;
    f32 absoluteX;
    f32 absoluteZ;
    f32 randomB;
    f32 randomA;

    func_151D5148(arg0);
    func_15145740(arg0, &direction, &right, &up, D_800A2030);
    matrixBase = arg0->field1D4;
    if (matrixBase != 0) {
        matrix = matrixBase + (D_80088BA0 << 6);
        sources[0] = (s32)&D_800A2000;
        sources[1] = (s32)D_800A2018;
        sources[2] = (s32)D_800A2024;
        destinations[0] = (s32)&position;
        destinations[1] = (s32)&origin;
        destinations[2] = (s32)&delta;
        func_15145EA4(sources, destinations, matrix, 3);
        delta.x -= origin.x;
        delta.y -= origin.y;
        delta.z -= origin.z;
    } else {
        threshold = D_800A2034;
        absoluteX = fabsf(direction.x);
        matrix = 0;
        if (threshold < absoluteX || threshold < (absoluteZ = fabsf(direction.z))) {
            inverse = 1.0f / sqrtf(direction.x * direction.x + direction.z * direction.z);
            sideZ = direction.z * inverse;
            sideX = -direction.x * inverse;
        } else {
            sideZ = 1.0f;
            sideX = 0.0f;
        }
        position.x = *(f32 *)((u8 *)arg0 + 0x14) + 34.0f * sideX;
        position.y = *(f32 *)((u8 *)arg0 + 0x18) + 49.0f;
        position.z = *(f32 *)((u8 *)arg0 + 0x1C) + 34.0f * sideZ;
    }
    randomA = func_150ADA68();
    randomB = func_150ADA68();
    func_151C229C(&position, &direction, 0, 0, 0, 0, 300.0f, D_800A2038,
                   randomA * 10.0f + 25.0f, randomB * 200.0f + 400.0f, 50.0f,
                   (u32)func_150ADA20() % 156U + 0x64, arg0, 1, 1, 0, 0, 1, 1,
                   0, 0x35, 0.0f, 0xFF, -1, 0, ((u8 *)&arg1)[3], arg2);
    if (arg0->field1D4 != 0 && (*((u8 *)arg0 + 0x74) & 0xF) != 0xF) {
        func_151D3F14(&position, ((u8 *)&arg1)[3], arg2);
        func_151D4408(&origin, &delta, matrix, arg0, 1.0f, ((u8 *)&arg1)[3], arg2);
        if (func_150ADA20() & 1) {
            func_150FEC28(arg0, D_80088BA0, &D_800A2000, D_800A200C, &position,
                          ((u8 *)&arg1)[3], arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FE860 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FE860.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FEBC8 CURRENT (1253) */
void func_150FEBC8(Game12BD10State *arg0, s32 arg1, s32 arg2) {
    s32 sp20[2];
    s32 sp1C;

    sp20[0] = (s32) &D_800A2000;
    sp1C = arg2;
    func_15145EA4(sp20, &sp1C,
                  arg0->field1D4 + (D_80088BA0 << 6), 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FEBC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FEBC8.s")
f32 func_150ADA68(void);
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
extern f32 D_800A203C;
extern f32 D_800A2040;
extern f32 D_800A2044;
extern f32 D_800A2048;
extern f32 D_800A204C;

void func_150FEC28(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4,
                   s32 arg5, s32 arg6) {
    f32 speed[2];
    s32 unused;
    s32 random[2];

    speed[1] = (func_150ADA68() * D_800A203C) + D_800A2040;
    speed[0] = (func_150ADA68() * D_800A2044) + D_800A2048;
    random[0] = func_150ADA20();
    random[1] = func_150ADA20();
    func_15102B38((s32)arg0, (u8)arg1, (s32)arg2, (s32)arg3, speed,
                  (random[0] & 3) + 6, 0xFF,
                  (func_150ADA68() * 270.0f) + D_800A204C, (s32)arg4, 0xFF, 0,
                  -1, (u8)arg5, arg6);
}
