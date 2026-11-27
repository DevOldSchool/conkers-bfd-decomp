#include "types.h"

/*
 * Reviewed source unit: src/second.c
 */

extern s32 D_80000010;
extern f32 D_80000020[];
extern s8 D_80000050;
extern Shared D_80000060[];
extern s32 (*D_80000070)(s32);
extern s32 D_80000080;
extern s32 D_80000090;

f32 Second_Read(void) {
    return D_80000020[0] + D_80000010 + D_80000050 + D_80000060[1].count + D_80000070(D_80000080) + D_80000090;
}
