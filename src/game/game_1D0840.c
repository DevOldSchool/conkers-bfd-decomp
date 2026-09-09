#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D0840.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A3390
 * - func_151A3504
 * - func_151A361C
 * - func_151A37C0
 * - func_151A3BE4
 * - func_151A4590
 * - func_151A4638
 * - func_151A483C
 * - func_151A4900
 * - func_151A499C
 * - func_151A4A38
 * - func_151A4CE0
 * - func_151A4D88
 * - func_151A4E34
 * - func_151A4E9C
 * - func_151A4ECC
 * - func_151A4F7C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3504.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A361C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A37C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A483C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4900.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A499C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4A38.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 CURRENT (1222) */
void func_151A4CE0(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_151A4E9C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0);
        if (temp_a0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4CE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4CE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4D88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4E34.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A4E9C CURRENT (220) */
void func_151A4E9C(void *arg0) {
    u8 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    temp_t0 = *(u8 *)((u8 *)temp_v0 + 0x30) | 1;
    *(u8 *)((u8 *)temp_v0 + 0x30) = temp_t0;
    *(u8 *)((u8 *)temp_v0 + 0x30) = (u8) (temp_t0 | 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A4E9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4E9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4ECC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4F7C.s")
