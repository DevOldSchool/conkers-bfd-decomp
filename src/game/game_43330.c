#include "types.h"

/*
 * Reviewed source unit: src/game/game_43330.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

void *func_10003C40(s32, s32, s32, s32);
extern void *D_800B0DF0;
extern u8 *D_800BE9C8[2];
extern s32 D_800BEBA4;

void func_15015E80(void) {
    if (*(u16 *)((u8 *)D_800B0DF0 + 0x1C) == 0) {
        *(u16 *)((u8 *)D_800B0DF0 + 0x1C) = 0x1F40;
    }
    *(u16 *)((u8 *)D_800B0DF0 + 0x1C) += 0x190;
    D_800BE9C8[0] = func_10003C40(*(u16 *)((u8 *)D_800B0DF0 + 0x1C) * 8, 0xFF, 2, 0);
    D_800BE9C8[1] = func_10003C40(*(u16 *)((u8 *)D_800B0DF0 + 0x1C) * 8, 0xFF, 2, 0);
    D_800BEBA4 = ((D_800BE9C8[1] - D_800BE9C8[0]) >> 3) - 0x190;
}
