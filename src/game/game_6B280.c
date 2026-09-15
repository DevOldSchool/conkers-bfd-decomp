#include "types.h"

/*
 * Reviewed source unit: src/game/game_6B280.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503DDD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800C6650;
extern u32 D_800C6654;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DDD0 CURRENT (645) */
void func_1503DDD0(s32 arg0) {
    s32 temp_a3;
    u32 temp_t5;
    u32 var_v0;
    void *var_v1;

    temp_a3 = 0x14;
    if ((arg0 >= 0) && ((u32)arg0 < D_800C6654)) {
        *(s16 *)((u8 *)(s32)D_800C6650 + (arg0 * temp_a3) + 6) = 2;
        var_v0 = D_800C6654;
        if (var_v0 != 0) {
            var_v1 = (void *)((u8 *)(s32)D_800C6650 + ((var_v0 - 1) * temp_a3));
            if ((*(u16 *)((u8 *)var_v1 + 6) & 2) != 0) {
loop_4:
                temp_t5 = var_v0 - 1;
                D_800C6654 = temp_t5;
                var_v0 = temp_t5;
                var_v1 = (void *)((u8 *)var_v1 - 0x14);
                if (temp_t5 != 0) {
                    if ((*(u16 *)((u8 *)var_v1 + 6) & 2) != 0) {
                        goto loop_4;
                    }
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DDD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B280/func_1503DDD0.s")
