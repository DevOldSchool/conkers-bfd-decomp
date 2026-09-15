#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC550.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF0A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15117798(u8 *);
void *func_151149AC(u8);
extern void *D_800CC5EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF0A0 CURRENT (70) */
void func_150CF0A0(u8 *arg0) {
    s32 temp_t4;
    s32 temp_t8;
    void *temp_v0;
    void *temp_v0_2;

    if ((arg0[0x73] & 3) != 2) {
        if ((arg0[0x4F] & 4) && (*(u8 *)((u8 *)D_800CC5EC + 0x57) != 0)) {
            temp_v0 = func_151149AC(0xFE);
            temp_t4 = *(u8 *)((u8 *)temp_v0 + 0x73) & 0xFFFC;
            *(volatile u8 *)((u8 *)temp_v0 + 0x73) = temp_t4;
            *(volatile u8 *)((u8 *)temp_v0 + 0x73) = temp_t4 | 2;
            temp_v0_2 = func_151149AC(0xFD);
            temp_t8 = *(u8 *)((u8 *)temp_v0_2 + 0x73) & 0xFFFC;
            *(volatile u8 *)((u8 *)temp_v0_2 + 0x73) = temp_t8;
            *(volatile u8 *)((u8 *)temp_v0_2 + 0x73) = temp_t8 | 2;
        }
    } else {
        func_15117798(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF0A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC550/func_150CF0A0.s")
