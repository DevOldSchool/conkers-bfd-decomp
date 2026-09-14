#include "types.h"

/*
 * Reviewed source unit: src/game/game_35D20.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15008930
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DCE50[2][104];

void func_15008870(s32 arg0) {
    s32 start = 0;
    s32 end = 104;
    s32 row;
    s32 column;

    if (arg0 == 1) {
        end = 101;
    } else if (arg0 == 2) {
        start = 101;
    }

    for (row = 0; row < 2; row++) {
        for (column = start; column < end; column++) {
            D_800DCE50[row][column] = 0;
        }
    }
}

typedef void (*Game35D20Callback)(void);

extern Game35D20Callback D_80082BD0;
extern Game35D20Callback D_80082BD4;
extern s32 D_800DD1B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15008930 CURRENT (100) */
void func_15008930(s32 arg0) {
    Game35D20Callback *sp2C;
    Game35D20Callback *var_s1;
    s32 var_s0;
    s32 var_s2;

    if (arg0 == 1) {
        sp2C = &D_80082BD0;
        var_s2 = 1;
    } else {
        var_s2 = 0;
        if (arg0 == 2) {
            sp2C = &D_80082BD4;
            var_s2 = 1;
        }
    }
    var_s0 = 0;
    if (var_s2 > 0) {
        var_s1 = sp2C;
        do {
            (*var_s1)();
            var_s0 += 1;
            var_s1 += 1;
        } while (var_s0 != var_s2);
    }
    D_800DD1B0 = -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15008930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_35D20/func_15008930.s")
