#include "types.h"

/*
 * Reviewed source unit: src/game/game_12C1E0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FED30
 * - func_150FF084
 * - func_150FF2D4
 * - func_150FF474
 * - func_150FF6E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FED30.s")
extern s32 func_1503195C(void *arg0, s32 arg1, s32 arg2);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A2050;

void func_150FEFD0(void *arg0, s16 arg1, void *arg2) {
    u8 *sp34;
    void *sp30;
    s32 result;

    if (arg1 == -1) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    result = func_1503195C(arg0, arg1, 0);
    if (result == 0) {
        *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
        *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x1C);
        return;
    }
    sp34 = &D_800A2050;
    sp30 = arg2;
    func_1514654C(arg0, result, 0, (void **)&sp34, &sp30, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF084.s")

void func_150FF288(void *arg0) {
    func_1503195C(arg0, 0x82, 0);
}
void func_15145740(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4);
extern f32 D_800A211C;

void func_150FF2AC(void *arg0, void *arg1, void *arg2, void *arg3) {
    func_15145740(arg0, arg1, arg2, arg3, D_800A211C);
}
s32 func_150FF6E0(void *, void *, void *, void *, void *, void *, s32);
void func_151D5174(void *, void *, void *, s32, s32, s32, s32, s32, s32, void *);
f32 fabsf(f32);
f32 sqrtf(f32);
#pragma intrinsic(fabsf)
#pragma intrinsic(sqrtf)
extern f32 D_800A2120;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF2D4 CURRENT (1702) */
void func_150FF2D4(u8 *arg0, void *arg1, f32 *arg2, void *arg3,
                    void *arg4, f32 *arg5, s32 arg6, s32 arg7, s32 arg8,
                    s32 arg9, s32 arg10, s32 arg11, f32 *arg12,
                    f32 *arg13, s32 arg14) {
    f32 directionX;
    f32 directionZ;
    f32 x;
    f32 z;
    f32 length;
    u8 result;

    result = *arg0;
    if (result != 0) {
        result = func_150FF6E0(arg1, arg2, arg3, arg4, arg12, arg13, arg14);
        *arg0 = result;
    }
    if (result == 0) {
        x = arg5[0];
        if (D_800A2120 < fabsf(x) || D_800A2120 < fabsf(arg5[2])) {
            z = arg5[2];
            length = 1.0f / sqrtf((x * x) + (z * z));
            directionX = z * length;
            directionZ = -x * length;
        } else {
            directionX = 1.0f;
            directionZ = 0.0f;
        }
        arg2[0] = arg13[5] + (34.0f * directionZ);
        arg2[1] = arg13[6] + 49.0f;
        arg2[2] = arg13[7] + (34.0f * directionX);
        ((u32 *)arg12)[0] = ((u32 *)arg2)[0];
        ((u32 *)arg12)[1] = ((u32 *)arg2)[1];
        ((u32 *)arg12)[2] = ((u32 *)arg2)[2];
    }
    func_151D5174(arg13, arg2, arg5, arg6, arg7, arg8, arg9,
                   arg10, arg11, arg12);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF2D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF2D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF474.s")
s32 func_150FF6B4(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x98) {
        return 0;
    }
    return 1;
}
s32 func_150ADA20(void);
extern u8 D_800A205C;
extern u8 D_800A2068;
extern u8 D_800A2074;
extern u8 D_800A2080;

typedef struct Game12C1E0Pointers {
    void *head[4];
    void *elements[6];
} Game12C1E0Pointers;

typedef struct Game12C1E0InputPointers {
    void *head[4];
    void *elements[6];
    u32 pad;
} Game12C1E0InputPointers;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FF6E0 CURRENT (1880) */
s32 func_150FF6E0(s32 arg0, void *arg1, void *arg2, f32 *arg3,
                  s32 arg4, void *arg5, s32 arg6) {
    Game12C1E0InputPointers input;
    Game12C1E0Pointers output;
    s32 index;
    s32 variant;

    variant = (func_150ADA20() & 1) * 0x48;
    input.head[0] = &D_800A2050;
    input.head[1] = &D_800A2068;
    input.head[2] = &D_800A2074;
    input.head[3] = &D_800A205C;
    index = 0;
    do {
        input.elements[index] = (u8 *)&D_800A2080 + variant + index * 0xC;
        output.elements[index] = (void *)(arg0 + index * 0xC);
        index = (u8)(index + 1);
    } while (index < 6);
    output.head[0] = arg1;
    output.head[1] = arg2;
    output.head[2] = arg3;
    output.head[3] = (void *)arg4;
    if (func_1514654C(arg5, arg6, 0, input.head, output.head, 0xA) != 0) {
        arg3[0] -= ((f32 *)arg2)[0];
        arg3[1] -= ((f32 *)arg2)[1];
        arg3[2] -= ((f32 *)arg2)[2];
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FF6E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12C1E0/func_150FF6E0.s")
