#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E37D0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B6320
 * - func_151B6420
 * - func_151B65D4
 * - func_151B6928
 * - func_151B70B4
 * - func_151B7144
 * - func_151B7328
 * - func_151B7678
 * - func_151B76CC
 * - func_151B77F4
 * - func_151B7998
 * - func_151B7C38
 * - func_151B82CC
 * - func_151B8318
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6320.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6420.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B65D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6928.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B70B4 CURRENT (1255) */
void func_151B70B4(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (temp_t6 == 0) {
        if (temp_a3 == *(s32 *)((u8 *)arg1 + 0)) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B70B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B70B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B76CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B77F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B82CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B8318.s")
