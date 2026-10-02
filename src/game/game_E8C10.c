#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8C10.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BB760
 * - func_150BBB5C
 * - func_150BC488
 * - func_150BCBBC
 * - func_150BD070
 * - func_150BD740
 * - func_150BD954
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BB760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BBB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BC488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BCBBC.s")
extern f32 D_8009FEF8;

s32 func_150BCFB8(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10) * D_8009FEF8) + arg4);
    if (-2.0f < (temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48))) {
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & ~0x6F);
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    } else {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (-temp_fv0 * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv1);
        *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv1);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD070.s")
f32 func_150ADA68(void);
void func_15143134(f32 *, f32 *, s32);
void func_1514C470(f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
extern f32 D_8009FF40[12];
extern f32 D_8009FF70[12];
extern f32 D_8009FFA0[12];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BD740 CURRENT (2337) */
void func_150BD740(u8 *arg0, s32 arg1, s32 arg2) {
    f32 pointsA[12];
    f32 pointsB[12];
    f32 pointsC[12];
    f32 direction1[3];
    f32 direction0[3];
    f32 *endC;
    f32 *outC;
    f32 *inA;
    f32 *outA;
    f32 *inB;
    f32 *outB;
    f32 *inC;

    if (arg0 != 0) {
        inA = D_8009FF40;
        outA = pointsA;
        if (*(s32 *)(arg0 + 0x1D4) != 0) {
            inC = D_8009FFA0;
            inB = D_8009FF70;
            outB = pointsB;
            outC = pointsC;
            endC = pointsC + 12;
            do {
                func_15143134(inA, outA, *(s32 *)(arg0 + 0x1D4));
                func_15143134(inB, outB, *(s32 *)(arg0 + 0x1D4));
                func_15143134(inC, outC, *(s32 *)(arg0 + 0x1D4));
                outC += 3;
                inA += 3;
                outA += 3;
                inB += 3;
                outB += 3;
                inC += 3;
            } while (outC != endC);
            direction0[0] = pointsC[6] - pointsB[6];
            direction0[1] = pointsC[7] - pointsB[7];
            direction0[2] = pointsC[8] - pointsB[8];
            func_1514C470(pointsA[6], pointsA[7], pointsA[8],
                           pointsA[9], pointsA[10], pointsA[11],
                           (func_150ADA68() * 6.0f) + 14.0f,
                           0xD, 0, 0.0f, (s32)direction0, (u8)arg1);
            direction1[0] = pointsC[9] - pointsB[9];
            direction1[1] = pointsC[10] - pointsB[10];
            direction1[2] = pointsC[11] - pointsB[11];
            func_1514C470(pointsA[9], pointsA[10], pointsA[11],
                           pointsA[0], pointsA[1], pointsA[2],
                           (func_150ADA68() * 6.0f) + 14.0f,
                           0xD, 0, 0.0f, (s32)direction1, (u8)arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BD740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD740.s")
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, u8, s32);
extern f32 D_8009FFD0, D_8009FFD4, D_8009FFD8, D_8009FFDC, D_8009FFE0, D_8009FFE4;

typedef struct GameE8C10Emission {
    s32 zero, enabled, flags, kind, field10, field14, field18;
    u8 byte1C, byte1D;
    u8 pad1E[6];
    f32 angle, dx, dy, dz, speed, height;
    u8 mode, category, alpha, random;
    u8 pad40[4];
    f32 x, y, z;
    s16 count, one;
    s32 active;
    u8 pad58;
    u8 variant;
} GameE8C10Emission;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BD954 CURRENT (242) */
s32 func_150BD954(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, s32 arg11, f32 arg12, f32 *arg13, s32 arg14) {
    GameE8C10Emission emission;
    f32 scale;

    emission.enabled = 1;
    emission.flags = 0x160600;
    emission.zero = 0;
    emission.kind = 3;
    emission.field10 = 0x10;
    emission.field14 = 0x80;
    emission.field18 = 0x20;
    emission.byte1C = 0;
    emission.byte1D = 9;
    emission.active = 1;
    emission.one = 1;
    emission.x = arg2;
    emission.y = arg3;
    emission.height = arg3;
    emission.category = 9;
    emission.alpha = 0xFF;
    emission.mode = 8;
    emission.z = arg4;
    scale = ((func_150ADA68() * 127.0f) + 85.0f) * D_8009FFD0;
    emission.dx = arg13[0] * scale;
    emission.dy = arg13[1] * scale;
    emission.dz = arg13[2] * scale;
    emission.random = (func_150ADA20() % 86U) + 0xB4;
    emission.variant = (func_150ADA20() & 3) + 3;
    emission.count = (func_150ADA20() % 31U) + 0x27;
    emission.angle = ((func_150ADA68() * D_8009FFD4) + D_8009FFD8) * D_8009FFDC;
    emission.speed = ((func_150ADA68() * 356.0f) + D_8009FFE0) * D_8009FFE4;
    func_15147DA0(&emission.x, &emission.angle, 0, 1, 0xB, 0, 0, 0, 0, 0, 0, &emission.zero, 0, (u8)arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BD954 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8C10/func_150BD954.s")
s32 func_150BDB3C(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    if (temp_t6 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_t6;
    }
    return 1;
}
