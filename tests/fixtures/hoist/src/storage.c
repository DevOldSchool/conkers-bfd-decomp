#include "types.h"

/*
 * Reviewed source unit: src/storage.c
 */

extern s32 D_80000010;
static s32 sCounter;

s32 Storage_Next(void) {
    sCounter += D_80000010;
    return sCounter;
}
