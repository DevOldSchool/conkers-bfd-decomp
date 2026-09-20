#include "types.h"

/*
 * Reviewed source unit: src/game/game_EC360.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BEEB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BEEB0 CURRENT (765) */
void func_150BEEB0(void *arg0) {
    s32 flags;

    if (func_1509BE40(1, 0x4063, 6, 0x2000) != 0 ||
        func_1509BE40(1, 0x4001, 6, 0x9000) != 0) {
        flags = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)((u8 *)arg0 + 0x84) = flags | 0x1010;
    } else {
        flags = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)((u8 *)arg0 + 0x84) = flags & ~0x1010;
    }
    flags = *(s32 *)((u8 *)arg0 + 0x84);
    if (func_1509BE40(1, 0x4069, 6, 0x2000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) = flags | 0x01000000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) = flags & 0xFEFFFFFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BEEB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC360/func_150BEEB0.s")
