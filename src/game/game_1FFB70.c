#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFB70.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D26C0
 * - func_151D275C
 * - func_151D2830
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D26C0.s")
extern void *D_800DD0E0;

void func_151D2718(s16 arg0) {
    void *var_v0;

    var_v0 = D_800DD0E0;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s16 *)((u8 *)var_v0 + 0x10)) {
                *(s8 *)((u8 *)var_v0 + 0x16) = -2;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 8);
        } while (var_v0 != 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D275C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D2830.s")
