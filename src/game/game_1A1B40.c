#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A1B40.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15174690
 * - func_15174920
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1B40/func_15174690.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15174920 CURRENT (445) */
void func_15174920(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x3F);
    if ((s32) var_v0 >= 0xC9) {
        var_v0 = 0xC8;
    }
    temp_v0 = var_v0 - (D_800BE9E4 * *(s32 *)((u8 *)arg0 + 0x18));
    if (temp_v0 < 0) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
        return;
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    *(u8 *)((u8 *)arg0 + 0x3F) = (u8) temp_v0;
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_v1);
    *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + ((s32) (temp_v1 * 8) / 7));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15174920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1B40/func_15174920.s")
