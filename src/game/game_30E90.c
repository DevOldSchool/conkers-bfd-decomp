#include "types.h"

/*
 * Reviewed source unit: src/game/game_30E90.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150039E0
 * - func_15004574
 * - func_150045C4
 * - func_150049A4
 * - func_15004A4C
 * - func_15004AAC
 * - func_15004BF0
 * - func_15004CE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150039E0.s")
extern s32 D_800DBEF4;
extern u8 D_800DBF88;
extern s32 D_800DBF8C;
extern s32 D_800DBF90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004574 CURRENT (40) */
void func_15004574(void) {
    void *temp_v1;

    if (D_800DBF88 != 0xFF) {
        temp_v1 = D_800DBEF4 + (D_800DBF88 * 0xA0);
        D_800DBF8C = *(s32 *)((u8 *)temp_v1 + 0x1C);
        D_800DBF90 = *(s32 *)((u8 *)temp_v1 + 0x28);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004574 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150045C4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150049A4 CURRENT (2920) */
void func_150049A4(s8 *arg0, s32 arg1, s32 arg2) {
    s32 var_t8;
    s32 var_v0;
    s8 *var_a1;
    s8 var_a2;

    var_v0 = 0;
    var_a1 = arg0;
    if (*arg0 != -0x21) {
        var_a2 = *arg0;
        do {
            var_v0 += 1;
            if (var_a2 != -0x24) {
                if (var_a2 != 1) {
                    if (var_a2 == -0x22) {
                        var_t8 = *(s32 *)((u8 *)var_a1 + 4) + arg1;
                        goto block_9;
                    }
                } else {
                    *(s32 *)((u8 *)var_a1 + 4) = (s32) (*(s32 *)((u8 *)var_a1 + 4) + arg1);
                }
            } else if (*(u8 *)((u8 *)var_a1 + 3) == 0xE) {
                var_t8 = *(s32 *)((u8 *)var_a1 + 4) + arg2;
block_9:
                *(s32 *)((u8 *)var_a1 + 4) = var_t8;
            }
            var_a1 = (var_v0 * 8) + arg0;
            var_a2 = *var_a1;
        } while (var_a2 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150049A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150049A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004A4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004AAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004BF0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004CE0 CURRENT (1310) */
void func_15004CE0(s8 *arg0, s32 arg1) {
    s32 var_v0;
    s8 *var_v1;
    s8 var_a1;
    u32 temp_a1;

    var_v0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_a1 = *arg0;
        do {
            var_v0 += 1;
            if ((var_a1 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE)) {
                temp_a1 = *(u32 *)((u8 *)var_v1 + 4);
                if (temp_a1 < 0x80000000U) {
                    *(u32 *)((u8 *)var_v1 + 4) = (u32) (temp_a1 + arg1);
                }
            }
            var_v1 = (var_v0 * 8) + arg0;
            var_a1 = *var_v1;
        } while (var_a1 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004CE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004CE0.s")
