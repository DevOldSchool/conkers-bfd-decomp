#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_19EDA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151718F0
 * - func_15171BF4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(void);
void func_1516D4E8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

typedef struct Game19EDA0Color {
    u8 red, green, blue;
} Game19EDA0Color;

extern Game19EDA0Color D_8008CC20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151718F0 CURRENT (2784) */
void func_151718F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4,
                   f32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    f32 sine, z, randomScale;
    f32 cosine;
    s32 packedX, packedZ, highZ, lowZ;
    s32 size;
    s32 angle, index;
    s32 step;
    u8 *color;
    s16 height;
    Game19EDA0Color colors;

    colors = D_8008CC20;
    if (arg7 != 0) {
        angle = 0;
        index = 0;
        if (arg7 > 0) {
            step = 0xFFFF / arg7;
            height = (s16)(s32)arg1;
            color = (u8 *)&colors + arg6 * 3;
            do {
                highZ = angle >> 8;
                highZ &= 0xFF;
                sine = func_15048A40(highZ & 0xFF);
                cosine = func_150489B0(highZ & 0xFF);
                z = arg3 * cosine + arg2;
                packedZ = (s32)(200.0f * cosine);
                highZ = (packedZ >> 8) & 0xFF;
                lowZ = packedZ & 0xFF;
                randomScale = (f32)(func_150ADA20() & 0xFFFF) * 0.000015258789f + 100.0f;
                size = (s32)((f32)(func_150ADA20() & 0xFFFF) * arg5 + (f32)arg4);
                packedX = (s32)(200.0f * sine);
                func_1516D4E8((s16)(s32)(arg3 * sine + arg0), (s16)height,
                    (s16)(s32)z, 0xD, 0, color[0], color[1], color[2],
                    0, 0, 0, 0, 2, (packedX >> 8) & 0xFF, packedX & 0xFF,
                    highZ, lowZ, 0, 0, 5, 0, 0, 0, (s16)size, (s16)size,
                    (func_150ADA20() & 0xF) + 0xA, (s32)randomScale,
                    0, 0, arg8, arg9);
                index++;
                angle += step;
            } while (index != arg7);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151718F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19EDA0/func_151718F0.s")
extern void func_150AEEB0(u8 *arg0, s32 arg1);
extern void func_10010154(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_150BD740(u8 *arg0, s32 arg1, s32 arg2);
extern void func_150CDBB0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15171BF4 CURRENT (495) */
void func_15171BF4(u8 *arg0, s32 arg1) {
    u8 type;

    arg1 &= 0xFF;
    type = arg0[4];
    switch (type) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BD740(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CDBB0(arg0, arg1, 1);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15171BF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19EDA0/func_15171BF4.s")
