#include "types.h"

/*
 * Reviewed source unit: src/game/game_331B0.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005D00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15124B18(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005D00 CURRENT (65) */
void func_15005D00(void *arg0) {
    volatile s32 *field84;
    s32 temp_t8;

    field84 = (volatile s32 *)((u8 *)arg0 + 0x84);
    temp_t8 = *field84 | 0x300000;
    *field84 = temp_t8;
    *(s32 *)((u8 *)arg0 + 0x2C) = 8;
    *field84 = temp_t8 & ~4;
    *(s16 *)((u8 *)arg0 + 0x1B4) = 1;
    *(s16 *)((u8 *)arg0 + 0x1E0) = 3;
    func_15124B18();
    *(s32 *)((u8 *)arg0 + 0x134) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005D00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_331B0/func_15005D00.s")
