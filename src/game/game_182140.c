#include "types.h"

/*
 * Reviewed source unit: src/game/game_182140.c
 * Boundary evidence: docs/evidence/game_raw_emission_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15154C90
 * - func_15154D80
 * - func_1515548C
 * - func_151555AC
 * - func_1515572C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_15154C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_15154D80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_1515548C.s")
extern void (*D_8008AD04[])(void *, s32, u8);

void func_15155564(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008AD04[*(u8 *)((u8 *)arg0 + 0x2A)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_151555AC.s")
typedef struct {
    s32 field_0;
    s32 field_4;
} Game182140Pair;

void func_15169260(Game182140Pair *, s32, s32, s32);
extern Game182140Pair D_800A6038;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515572C CURRENT (260) */
void func_1515572C(s32 arg0, u8 arg1) {
    Game182140Pair sp18;

    sp18 = D_800A6038;
    func_15169260(&sp18, 2, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515572C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_1515572C.s")
