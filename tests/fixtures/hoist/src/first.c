#include "types.h"

/*
 * Reviewed source unit: src/first.c
 */

typedef struct Local {
    s32 value;
} Local;

#define gAlias D_800000A0

extern s32 D_80000010;
extern f32 D_80000020[], D_80000090;
extern Local D_80000040;
extern u8 D_80000050;
extern Shared D_80000060[4];
extern u8 gAlias;
extern s32 (*D_80000070)(s32);

s32 First_Read(void) {
    extern s32 D_80000080;

    return D_80000010 + D_80000080 + D_80000040.value + D_80000050 + D_80000060[0].count + gAlias + D_80000090;
}
