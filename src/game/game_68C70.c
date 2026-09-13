#include "types.h"

/*
 * Reviewed source unit: src/game/game_68C70.c
 * Boundary evidence: docs/evidence/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503B7C0
 * - func_1503B840
 * - func_1503B9BC
 * - func_1503CB98
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B7C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B840.s")
extern u8 D_800CC5CB;

s32 func_1503B95C(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)&D_800CC5CB + (arg0 * 0x32C));
    if (temp_v0 & 2) {
        *(s8 *)((u8 *)arg1 + 0x4E) = 0;
        return 0;
    }
    if (temp_v0 & 1) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B9BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503CB98.s")
