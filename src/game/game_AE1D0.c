#include "types.h"

/*
 * Reviewed source unit: src/game/game_AE1D0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080D20
 * - func_1508108C
 * - func_1508114C
 * - func_15081574
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15080D20.s")
extern u16 D_8009BD30;
extern u16 D_8009BD34;
extern u16 D_8009BD38;
extern u16 D_8009BD3C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508108C CURRENT (3770) */
s32 func_1508108C(void *arg0) {
    u8 value;
    s32 index;
    u16 *entry;

    value = *(u8 *)((u8 *)arg0 + 4);
    if (value == D_8009BD30) {
        return 0;
    }
    if (value == D_8009BD34) {
        return 1;
    }
    index = 3;
    if (value == D_8009BD38) {
        return 2;
    }
    entry = D_8009BD3C;
    do {
        if (value == entry[0]) {
            return index;
        }
        if (value == entry[2]) {
            return index + 1;
        }
        if (value == entry[4]) {
            return index + 2;
        }
        if (value == entry[6]) {
            return index + 3;
        }
        index += 4;
        entry += 8;
    } while (index != 0x17);
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508108C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_1508108C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_1508114C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15081574.s")
