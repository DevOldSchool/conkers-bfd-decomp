#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EC390.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BEEE0
 * - func_151BF0C8
 * - func_151BF340
 * - func_151BF81C
 * - func_151BFB2C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BEEE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF0C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF340.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BF81C.s")

typedef struct {
    u8 pad0[0x28];
    void *primary;
    void *secondary[2];
} Game1EC390ResourceOwner;

void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFB2C CURRENT (1078) */
void func_151BFB2C(Game1EC390ResourceOwner *arg0) {
    u8 i;

    if (arg0->primary != 0) {
        func_1516972C(arg0->primary);
    }

    for (i = 0; i < 2; i++) {
        if (arg0->secondary[i] != 0) {
            func_1516972C(arg0->secondary[i]);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFB2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EC390/func_151BFB2C.s")

void func_1514933C(s32 arg0);

void func_151BFBA4(s32 arg0) {
    func_151BFB2C(arg0);
    func_1514933C(arg0);
}
