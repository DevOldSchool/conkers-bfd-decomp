#include "types.h"

/*
 * Reviewed source unit: src/game/game_AEB40.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15081690
 * - func_15081C20
 * - func_15081E0C
 * - func_15081E78
 * - func_150825C0
 * - func_1508295C
 * - func_150829D8
 * - func_15082A44
 * - func_150832AC
 * - func_15083384
 * - func_15083568
 * - func_150836CC
 * - func_150837D4
 * - func_150838EC
 * - func_150839B8
 * - func_15083AC8
 * - func_15083DA0
 * - func_15083E0C
 * - func_15083E90
 * - func_15083FB0
 * - func_15084000
 * - func_15084044
 * - func_1508434C
 * - func_150843AC
 * - func_15084488
 * - func_15084558
 * - func_150849A0
 * - func_150849CC
 * - func_15084A18
 * - func_15084C30
 * - func_15084CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081C20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150825C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_1508295C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150829D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15082A44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150832AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083384.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150836CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150837D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150838EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150839B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083AC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083DA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083FB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084000.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084044.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_1508434C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150843AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150849A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150849CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084A18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084C30.s")
extern u8 D_800BE590;
extern u16 D_800BE598;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084CB0 CURRENT (140) */
s32 func_15084CB0(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u16 *var_a2;

    var_v1 = 0;
    var_v0 = 0;
    if ((s32) D_800BE590 > 0) {
        var_a2 = &D_800BE598;
loop_2:
        if (arg0 == *var_a2) {
            var_v1 = var_v0;
        } else {
            var_v0 += 1;
            var_a2 += 2;
            if (var_v0 < (s32) D_800BE590) {
                goto loop_2;
            }
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084CB0.s")
