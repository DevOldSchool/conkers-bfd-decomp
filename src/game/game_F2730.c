#include "types.h"

/*
 * Reviewed source unit: src/game/game_F2730.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 */

extern u8 D_800C35E8;
extern u8 D_800C35EA;

s32 func_150C5280(void) {
    if ((D_800C35EA == 1) && ((D_800C35E8 == 0xB) || (D_800C35E8 == 0xC) || (D_800C35E8 == 0xD))) {
        return 1;
    }
    return 0;
}
s32 func_150C5280();                                /* extern */
extern s32 (*D_8008ADA8)(s32);

s32 func_150C52CC(s32 arg0) {
    if (func_150C5280() != 0) {
        return 0;
    }
    return D_8008ADA8(arg0);
}
s32 func_150C5310(void *arg0) {
    if (func_150C5280() != 0) {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) | 0x20000);
    } else {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & 0xFFFDFFFF);
    }
    return 1;
}
