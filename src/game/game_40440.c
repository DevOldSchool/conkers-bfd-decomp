#include "types.h"

/*
 * Reviewed source unit: src/game/game_40440.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012F90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_800DF7D0;
extern s8 D_800DF7D1;
extern s8 D_800DF7D2;
typedef struct Game40440Entry {
    s8 pad0[4];
} Game40440Entry;

extern Game40440Entry D_800DF7D3;
extern Game40440Entry D_800DF9B3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012F90 CURRENT (2915) */
void func_15012F90(void) {
    Game40440Entry *var_v1;

    D_800DF7D0 = 0;
    D_800DF7D1 = 0;
    var_v1 = &D_800DF7D3;
    D_800DF7D2 = 0;
    do {
        var_v1++;
        ((s8 *)var_v1)[-3] = 0;
        ((s8 *)var_v1)[-2] = 0;
        ((s8 *)var_v1)[-1] = 0;
        ((s8 *)var_v1)[-4] = 0;
    } while (var_v1 != &D_800DF9B3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012F90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40440/func_15012F90.s")
