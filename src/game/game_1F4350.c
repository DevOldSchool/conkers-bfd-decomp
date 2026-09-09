#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F4350.c
 * Boundary evidence: docs/evidence/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C6EA0
 * - func_151C7038
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4350/func_151C6EA0.s")
s32 func_15142A5C(void *, void *, void *);          /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C7038 CURRENT (993) */
s32 func_151C7038(void *arg0) {
    void *sp1C;
    void *temp_a2;

    temp_a2 = *(void **)((u8 *)arg0 + 0x7C);
    if (*(u16 *)((u8 *)temp_a2 + 0x84) != 0xE9) {
        return 0;
    }
    sp1C = temp_a2;
    if (func_15142A5C(temp_a2, arg0, temp_a2) != 0) {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) | 0x20000);
    } else {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & 0xFFFDFFFF);
    }
    {
        f32 var_fv0 = *(f32 *)((u8 *)temp_a2 + 0x4C) * 35.0f;
    if (var_fv0 > 255.0f) {
        var_fv0 = 255.0f;
    } else if (var_fv0 < 0.0f) {
        var_fv0 = 0.0f;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) var_fv0;
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C7038 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4350/func_151C7038.s")
