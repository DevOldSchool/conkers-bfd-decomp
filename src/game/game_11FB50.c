#include "types.h"

/*
 * Reviewed source unit: src/game/game_11FB50.c
 * Boundary evidence: docs/evidence/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F26A0
 * - func_150F2994
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11FB50/func_150F26A0.s")
void func_1509BFB0(s32, s32, s32);
extern void *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2994 CURRENT (300) */
void func_150F2994(s32 arg0, s32 arg1) {
    register s32 index;
    register s32 limit;
    register s32 saved_arg1;

    saved_arg1 = arg1;
    index = 0;
    limit = 0xE;
    do {
        func_1509BFB0(0, index + 0x4016, saved_arg1);
        index += 1;
    } while (index != limit);
    func_1509BFB0(0, 0x405D, saved_arg1);
    func_1509BFB0(0, 0x405F, saved_arg1);
    if (*(u8 *)((u8 *)D_800D2E4C + 0x15) & 8) {
        func_1509BFB0(0, 0x4063, saved_arg1);
        func_1509BFB0(0, 0x4064, saved_arg1);
        func_1509BFB0(0, 0x4065, saved_arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2994 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FB50/func_150F2994.s")
