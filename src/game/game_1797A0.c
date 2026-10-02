#include "types.h"

/*
 * Reviewed source unit: src/game/game_1797A0.c
 * Boundary evidence: docs/evidence/game_raw_particle_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514C2F0
 * - func_1514C470
 * - func_1514C678
 * - func_1514C858
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef s32 (*Game1797A0Callback)(s32, s16, f32, f32, f32, f32,
                                  f32, f32, s32, s32, f32, s32, f32, s32, s32);
f32 func_151423D8(u8);
extern Game1797A0Callback D_8008AA00[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C2F0 CURRENT (2223) */
void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   u8 arg4, volatile s8 arg5, s16 arg6, u8 arg7, s32 arg8,
                   f32 arg9, s32 arg10, u8 arg11) {
    s32 angle = arg4 & 0xFF;
    s16 index = 0;

    if (arg6 > 0) {
        do {
            s32 old_angle = angle;
            f32 start = func_151423D8((angle - 0x40) & 0xFF);
            f32 end_value = (arg3 * func_151423D8(angle & 0xFF)) + arg2;
            Game1797A0Callback callback = D_8008AA00[arg7];

            if (callback != 0 &&
                callback(1, index, (arg3 * start) + arg0, arg1,
                         end_value, arg0, arg1, arg2,
                         old_angle, arg4, arg3, arg8, arg9, arg10, arg11) == 0) {
                return;
            }
            index++;
            angle = (old_angle + arg5) & 0xFF;
        } while (index < arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C2F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C2F0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C470 CURRENT (2403) */
void func_1514C470(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8,
                   f32 arg9, s32 arg10, s32 arg11) {
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 x;
    f32 y;
    f32 z;
    s16 index;
    Game1797A0Callback callback;

    index = 0;
    if (!(arg6 < 2.0f)) {
        y = arg1;
        if ((s32)arg6 & 1) {
            f32 inverse = 1.0f / (arg6 - 1.0f);
            stepX = (arg3 - arg0) * inverse;
            stepY = (arg4 - arg1) * inverse;
            stepZ = (arg5 - arg2) * inverse;
        } else {
            f32 inverse = 1.0f / (arg6 - 1.0f);
            stepX = (arg3 - arg0) * inverse;
            stepY = (arg4 - arg1) * inverse;
            stepZ = (arg5 - arg2) * inverse;
        }
        x = arg0;
        z = arg2;
        do {
            callback = D_8008AA00[(u8)arg7];
            if (callback != 0 &&
                callback(0, index, x, y, z, arg0, arg1, arg2,
                         0, 0, 0.0f, arg8, arg9, arg10, (u8)arg11) == 0) {
                return;
            }
            arg6 -= 1.0f;
            x += stepX;
            index++;
            y += stepY;
            z += stepZ;
        } while (arg6 > 0.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C470 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C470.s")
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C678 CURRENT (4012) */
void func_1514C678(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   f32 arg9, s32 arg10, s32 arg11) {
    f32 sine;
    f32 endValue;
    s16 index;
    s16 range;
    s16 low;
    Game1797A0Callback callback;
    s32 randomAngle;
    s32 angle;

    if ((s16)arg5 < (s16)arg4) {
        range = ((s16)arg4 - (s16)arg5) + 1;
        low = (s16)arg5;
    } else {
        range = ((s16)arg5 - (s16)arg4) + 1;
        low = (s16)arg4;
    }
    index = 0;
    if ((s16)arg6 > 0) {
        do {
            randomAngle = (func_150ADA20() % (u32)range) + low;
            angle = randomAngle & 0xFF;
            sine = func_151423D8((randomAngle - 0x40) & 0xFF);
            endValue = arg3 * func_151423D8(angle & 0xFF) + arg2;
            callback = D_8008AA00[(u8)arg7];
            if (callback != 0) {
                if (callback(2, index, arg3 * sine + arg0, arg1,
                             endValue, arg0, arg1, arg2, angle, (s16)arg4,
                             arg3, arg8, arg9, arg10, (u8)arg11) == 0) {
                    return;
                }
            }
            index++;
        } while (index < (s16)arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C678 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C678.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C858 CURRENT (4809) */
void func_1514C858(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9, f32 arg10, s32 arg11, s32 arg12) {
    f32 cosine;
    f32 sine;
    f32 productX;
    f32 productZ;
    f32 x;
    f32 z;
    s16 range;
    s16 low;
    s16 index;
    Game1797A0Callback callback;
    s32 randomAngle;
    s32 angle;

    cosine = func_151423D8(((s16)arg4 - 0x40) & 0xFF);
    sine = func_151423D8((u8)arg4);
    if ((s16)arg6 < (s16)arg5) {
        range = ((s16)arg5 - (s16)arg6) + 1;
        low = (s16)arg6;
    } else {
        range = ((s16)arg6 - (s16)arg5) + 1;
        low = (s16)arg5;
    }
    index = 0;
    if ((s16)arg7 > 0) {
        productX = arg3 * cosine;
        productZ = arg3 * sine;
        do {
            randomAngle = (func_150ADA20() % (u32)range) + low;
            angle = randomAngle & 0xFF;
            cosine = func_151423D8((randomAngle - 0x40) & 0xFF);
            sine = func_151423D8(angle & 0xFF);
            callback = D_8008AA00[(u8)arg8];
            x = (productX * sine) + arg0;
            z = (productZ * sine) + arg2;
            if (callback != 0 &&
                callback(3, index, x, arg1 - (arg3 * cosine), z,
                         arg0, arg1, arg2, angle, (s16)arg4,
                         arg3, arg9, arg10, arg11, (u8)arg12) == 0) {
                return;
            }
            index++;
        } while (index < (s16)arg7);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C858 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1797A0/func_1514C858.s")
