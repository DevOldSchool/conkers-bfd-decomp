#include "types.h"

/*
 * Reviewed source unit: src/game/game_7FC10.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052760
 * - func_150528C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_80099348;
extern f32 D_8009934C;
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15052760 CURRENT (1420) */
void func_15052760(void *arg0, s16 arg1) {
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_a1;
    s32 var_a1;
    s32 var_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = *(u8 *)((u8 *)arg0 + 4);
    var_v0 = (s32) ((s16) ((arg1 & 0xFFFF) - *(u16 *)((u8 *)arg0 + 0x76)) * 0x64) / (s16) D_800CC264;
    if (((temp_v1 == 0x29) || (temp_v1 != 8)) && !(*(u16 *)((u8 *)arg0 + 0x22C) & 8)) {
        var_fv0 = D_80099348;
        var_a1 = 7;
        if (temp_v1 == 0xA) {
            var_a1 = 0x28;
        }
        if (*(u8 *)((u8 *)arg0 + 0x226) == 0xFF) {
            temp_a1 = var_v0 >> 8;
            if ((*(u8 *)((u8 *)arg0 + 0x87) ^ (s8) temp_a1) & 0x80) {
                var_v0 = 0;
            }
            var_fv0 = D_8009934C;
            var_a1 = 4;
            *(u8 *)((u8 *)arg0 + 0x87) = (u8) (s8) temp_a1;
        }
        temp_v1_2 = *(u8 *)((u8 *)arg0 + 0x1E5);
        if (temp_v1_2 != 0) {
            temp_fv1 = *(f32 *)((u8 *)arg0 + 0xC4);
            *(f32 *)((u8 *)arg0 + 0xC4) = (f32) (temp_fv1 + (((f32) (var_v0 / (s32) (temp_v1_2 * var_a1)) - temp_fv1) * var_fv0));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15052760 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_7FC10/func_15052760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_7FC10/func_150528C8.s")
