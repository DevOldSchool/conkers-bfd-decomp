#include "types.h"

/*
 * Reviewed source unit: src/game/game_12BD10.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FE860
 * - func_150FEBC8
 * - func_150FEC28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12BD10State {
    u8 pad0[0x1D4];
    s32 field1D4;
} Game12BD10State;

void func_15145EA4(s32 *, s32 *, s32, s32);

extern u8 D_80088BA0;
extern s32 D_800A2000;

#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FE860.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FEBC8 CURRENT (1253) */
void func_150FEBC8(Game12BD10State *arg0, s32 arg1, s32 arg2) {
    s32 sp20[2];
    s32 sp1C;

    sp20[0] = (s32) &D_800A2000;
    sp1C = arg2;
    func_15145EA4(sp20, &sp1C,
                  arg0->field1D4 + (D_80088BA0 << 6), 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FEBC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FEBC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FEC28.s")
