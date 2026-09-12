#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A5C00.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15178750
 * - func_151787AC
 * - func_15178B98
 * - func_15178BE4
 * - func_15178C34
 * - func_15178C9C
 * - func_15178DA4
 * - func_15178E14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178750.s")
void func_151787A4(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_151787AC.s")
extern void *D_800DCF38;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15178B98 CURRENT (815) */
void *func_15178B98(s32 arg0) {
    void *var_v1;

    var_v1 = D_800DCF38;
    if (var_v1 != 0) {
loop_1:
        if ((arg0 & 0xFF) == *(u8 *)((u8 *)var_v1 + 0x34)) {
            return var_v1;
        }
        var_v1 = *(void **)((u8 *)var_v1 + 8);
        if (var_v1 == 0) {
            /* Duplicate return node #4. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15178B98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178B98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178C34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178C9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178DA4.s")
void *func_15178B98(s32);
void func_15178DA4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15178E14 CURRENT (269) */
void func_15178E14(s32 arg0) {
    arg0 = arg0 & 0xFF;
    func_15178DA4(func_15178B98(arg0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15178E14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5C00/func_15178E14.s")
