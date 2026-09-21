#include "types.h"

/*
 * Reviewed source unit: src/game/game_43880.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150163D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 offset;
    s32 other;
} Game43880Record;

s32 func_1502B7F0(s32 **, s32, s32, s32, s32);
extern s32 *D_800D18B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150163D0 CURRENT (640) */
void func_150163D0(s32 arg0) {
    Game43880Record *base;
    Game43880Record *scan;
    s32 count;
    s32 total;
    s32 i;

    if (func_1502B7F0(&D_800D18B0, 3, 0xC, arg0, 9) > 0) {
        count = 1;
        i = 0;
        base = (Game43880Record *) D_800D18B0;
        if (base->offset != 0) {
            scan = (Game43880Record *) D_800D18B0;
            do {
                count++;
                scan++;
            } while (scan->offset != 0);
            i = 0;
        }
        total = count - 1;
        if (total > 0) {
            do {
                ((Game43880Record *) D_800D18B0)[i].offset += (s32) D_800D18B0;
                i++;
            } while (i != total);
        }
    } else {
        D_800D18B0 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150163D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43880/func_150163D0.s")
