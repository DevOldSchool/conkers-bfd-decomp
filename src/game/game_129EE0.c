#include "types.h"

/*
 * Reviewed source unit: src/game/game_129EE0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCA30
 * - func_150FCBC0
 * - func_150FCF1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCA30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCBC0.s")
f32 func_15165BB0(void *, f32 *, s32, s32, f32);
extern void *D_800D9AA0;
extern f32 D_800A1F2C;

typedef struct Game129EE0Values {
    f32 value0;
    f32 value1;
    f32 value2;
} Game129EE0Values;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FCF1C CURRENT (17) */
f32 func_150FCF1C(void *arg0) {
    Game129EE0Values sp20;

    if (D_800D9AA0 == 0) {
        return 1.0f;
    }
    sp20.value0 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 0);
    sp20.value1 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 2);
    sp20.value2 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 4);
    return func_15165BB0(arg0, &sp20.value0, 0x44FAE000, 0x460CB400, D_800A1F2C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FCF1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCF1C.s")
