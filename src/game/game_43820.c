#include "types.h"

/*
 * Reviewed source unit: src/game/game_43820.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15016370
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_8008FD8C;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15016370 CURRENT (160) */
void func_15016370(void) {
    void *var_v1;
    s32 var_v0;
    void *temp_t7;

    var_v1 = &D_800CC2D0;
    var_v0 = 0;
    if (D_8008FD8C > 0) {
        do {
            temp_t7 = *(void **)((u8 *)var_v1 + 0x31C);
            var_v0 += 1;
            var_v1 = (u8 *)var_v1 + 0x32C;
            *(s16 *)((u8 *)temp_t7 + 0x114) = 0xB4;
            *(s16 *)(*(u8 **)((u8 *)var_v1 - 0x10) + 0x116) = 0x3C;
            *(s16 *)(*(u8 **)((u8 *)var_v1 - 0x10) + 0x118) = 0x3C;
        } while (var_v0 < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15016370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43820/func_15016370.s")
