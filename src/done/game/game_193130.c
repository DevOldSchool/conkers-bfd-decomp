#include "types.h"
#include <PR/gbi.h>

/*
 * Reviewed source unit: src/game/game_193130.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern s32 D_800BE9E4;

void func_15165C80(f32 *arg0, u8 *arg1, f32 arg2, f32 *arg3,
                   f32 arg4, f32 arg5, u8 *arg6, u8 arg7) {
    s32 i;
    f32 cosine;
    f32 sine;
    s32 x;
    s32 y;
    f32 velocity;
    f32 current;

    current = *arg0;
    velocity = *arg3;
    sine = func_150AD78C(current * 0.017453292f) * arg2;
    cosine = func_150AD780(current * 0.017453292f);
    arg7 = arg7 >> 1;
    x = (s16)(cosine * arg2);
    y = (s16)sine;
    for (i = 0; i < arg7; i++) {
        ((Vtx *)arg1)[arg6[i]].v.ob[0] = -x;
        ((Vtx *)arg1)[arg6[i]].v.ob[1] = y;
        ((Vtx *)arg1)[arg6[i + arg7]].v.ob[0] = x;
        ((Vtx *)arg1)[arg6[i + arg7]].v.ob[1] = y;
    }
    *arg0 += velocity * D_800BE9E4;
    if (arg4 <= *arg0) {
        *arg3 = -velocity;
        *arg0 = arg4;
    } else if (*arg0 <= arg5) {
        *arg3 = -velocity;
        *arg0 = arg5;
    }
}
