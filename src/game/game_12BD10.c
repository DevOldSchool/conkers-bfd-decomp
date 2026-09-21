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
s32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
extern f32 D_800A203C;
extern f32 D_800A2040;
extern f32 D_800A2044;
extern f32 D_800A2048;
extern f32 D_800A204C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FEC28 CURRENT (216) */
void func_150FEC28(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4,
                   u8 arg5, s32 arg6) {
    volatile f32 sp54;
    f32 sp50;
    volatile s32 sp44;
    volatile s32 sp48;

    sp54 = (func_150ADA68() * D_800A203C) + D_800A2040;
    sp50 = (func_150ADA68() * D_800A2044) + D_800A2048;
    sp44 = func_150ADA20();
    sp48 = func_150ADA20();
    func_15102B38(arg0, arg1, arg2, arg3, &sp50, (sp44 & 3) + 6, 0xFF,
                  (func_150ADA68() * 270.0f) + D_800A204C, arg4, 0xFF, 0,
                  -1, (s32)arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FEC28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12BD10/func_150FEC28.s")
