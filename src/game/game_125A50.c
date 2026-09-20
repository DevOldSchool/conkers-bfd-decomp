#include "types.h"

/*
 * Reviewed source unit: src/game/game_125A50.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F85A0
 * - func_150F887C
 * - func_150F892C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F85A0.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_150F884C(s32 arg0, s32 arg1) {
    s32 sp18[2];

    sp18[0] = arg1;
    func_151494E0(&sp18[0], 0x3F, arg1);
}
extern void func_150F892C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F887C CURRENT (2038) */
void func_150F887C(void *arg0, u8 *arg1, s32 arg2) {
    u8 *temp_a0;
    void *temp_t1;
    s32 var_v0;
    s32 temp_t2;

    arg2 &= 0xFF;
    temp_a0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x42) {
        var_v0 = 0;
        if (arg1[4] == temp_a0[4]) {
            do {
                temp_t1 = *(void **)(temp_a0 + (var_v0 * 4) + 0xC);
                temp_t2 = (var_v0 + 1) & 0xFF;
                var_v0 = temp_t2;
                *(u8 *)((u8 *)temp_t1 + 0x6E) = 1;
            } while (temp_t2 < 7);
            *(u8 *)((u8 *)*(void **)(temp_a0 + 0x28) + 0x6E) = 0;
            temp_a0[8] = 7;
        }
    } else if ((arg2 == 0x3F) && (*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x28))) {
        func_150F892C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F887C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F887C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F892C.s")
