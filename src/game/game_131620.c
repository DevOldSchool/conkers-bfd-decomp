#include "types.h"

/*
 * Reviewed source unit: src/game/game_131620.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104170
 * - func_151041E4
 * - func_1510448C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_15104170.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_151041E4.s")
typedef struct Game131620ScaleState {
    u8 pad0[0x1B];
    u8 scale;
} Game131620ScaleState;

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510448C CURRENT (275) */
s32 func_1510448C(s32 arg0, Game131620ScaleState * volatile arg1, s16 arg2) {
    u8 temp_v0;

    if ((arg2 != 0) || ((temp_v0 = arg1->scale) == 0)) {
        return arg0;
    }
    return func_1517F08C(arg0, (temp_v0 * 0x3F) >> 8, 0, 0, 0, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510448C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_1510448C.s")
extern void *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return *(u8 *)((u8 *)D_800CC5EC + 0x7D);
    }
    return 0U;
}
