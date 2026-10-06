#include "types.h"

/*
 * Reviewed source unit: src/game/game_193130.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15165C80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_800A6C70;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15165C80 CURRENT (349) */
void func_15165C80(f32 *arg0, u8 *arg1, f32 arg2, f32 *arg3,
                   f32 arg4, f32 arg5, u8 *arg6, s32 arg7) {
    f32 angle, velocity, vertical, cosine, current;
    s32 index, count;
    f32 savedAngle, savedVelocity, savedVertical;
    s32 x, y;

    angle = *arg0 * D_800A6C70;
    velocity = *arg3;
    savedVelocity = velocity;
    savedAngle = angle;
    vertical = func_150AD78C(angle) * arg2;
    savedVertical = vertical;
    cosine = func_150AD780(savedAngle);
    vertical = savedVertical;
    velocity = savedVelocity;
    count = (u8)((u8)arg7 >> 1);
    index = 0;
    if (count > 0) {
        do {
            y = (s16)(s32)vertical;
            x = (s16)(s32)(cosine * arg2);
            *(s16 *)(arg1 + arg6[index] * 16) = -x;
            *(s16 *)(arg1 + arg6[index] * 16 + 2) = y;
            *(s16 *)(arg1 + arg6[index + count] * 16) = x;
            *(s16 *)(arg1 + arg6[index + count] * 16 + 2) = y;
            index++;
        } while (index != count);
    }
    *arg0 += velocity * (f32)D_800BE9E4;
    current = *arg0;
    angle = arg4;
    if (angle <= current) {
        *arg3 = -velocity;
        *arg0 = angle;
    } else {
        angle = arg5;
        if (current <= angle) {
            *arg3 = -velocity;
            *arg0 = angle;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15165C80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193130/func_15165C80.s")
