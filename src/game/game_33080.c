#include "types.h"

/*
 * Reviewed source unit: src/game/game_33080.c
 * Boundary evidence: docs/evidence/game_32F10_33080.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005BD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15124B18(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005BD0 CURRENT (65) */
void func_15005BD0(void *arg0) {
    volatile s32 *field84;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t8;

    field84 = (volatile s32 *)((u8 *)arg0 + 0x84);
    temp_t6 = 8;
    temp_t8 = *field84 | 0x300000;
    *field84 = temp_t8;
    temp_t0 = temp_t8 & ~4;
    temp_t1 = 1;
    temp_t2 = 3;
    *(s32 *)((u8 *)arg0 + 0x2C) = temp_t6;
    *field84 = temp_t0;
    *(s16 *)((u8 *)arg0 + 0x1B4) = temp_t1;
    *(s16 *)((u8 *)arg0 + 0x1E0) = temp_t2;
    func_15124B18();
    *(s32 *)((u8 *)arg0 + 0x134) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005BD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33080/func_15005BD0.s")
