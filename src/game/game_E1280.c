#include "types.h"

/*
 * Reviewed source unit: src/game/game_E1280.c
 * Boundary evidence: docs/evidence/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B3DD0
 * - func_150B3E74
 * - func_150B3EE8
 * - func_150B3F5C
 * - func_150B40E8
 * - func_150B4294
 * - func_150B4710
 * - func_150B5088
 * - func_150B538C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3DD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3E74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3EE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3F5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B40E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4710.s")
void func_150B5060(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 0x1C) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x1C) | 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B5088.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B538C CURRENT (295) */
void func_150B538C(void *arg0, s32 arg1, s32 arg2) {
    if ((arg2 & 0xFF) == 5) {
        func_150B5060(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B538C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B538C.s")
