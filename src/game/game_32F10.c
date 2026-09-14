#include "types.h"

/*
 * Reviewed source unit: src/game/game_32F10.c
 * Boundary evidence: docs/evidence/game_32F10_33080.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005A60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void (*D_80082B40[])(void);
extern void *D_800B0DF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005A60 CURRENT (109) */
void func_15005A60(void *arg0, s16 arg1) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)D_800B0DF0 + 0xE);
    if (temp_v0 != 0) {
        D_80082B40[temp_v0]();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32F10/func_15005A60.s")
