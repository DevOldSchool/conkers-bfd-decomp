#include "types.h"

/*
 * Reviewed source unit: src/game/game_15B200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512DD50
 * - func_1512DEA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150AD930(f32, f32, f32 *, void *);         /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512DD50 CURRENT (5856) */
void func_1512DD50(u8 *arg0) {
    f32 sp40;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft0;
    f32 var_ft1;
    s32 temp_t1;
    u8 *temp_v0;
    u8 *temp_v1;

    sp40 = (f32) *(s16 *)((u8 *)arg0 + 0x710);
    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0x712);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x720) * temp_fv1;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x724) * temp_fv1;
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x728) * temp_fv0;
    temp_fa1 = -temp_fv0 * *(f32 *)((u8 *)arg0 + 0x72C);
    *(f32 *)((u8 *)arg0 + 0x878) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0x70E) - temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x874) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0x70C) - temp_fv0_2);
    *(f32 *)((u8 *)arg0 + 0x87C) = (f32) (sp40 - temp_fa1);
    sp20 = 2.0f * temp_fv0_2;
    sp24 = 2.0f * temp_fa0;
    sp28 = 2.0f * temp_fa1;
    temp_fv1_2 = 1.0f / func_150AD930(temp_fa0, temp_fa1, &sp20, arg0);
    temp_v0 = (void *)(arg0 + 0x870);
    temp_v1 = (void *)(arg0 + 0x6FC);
    *(f32 *)((u8 *)temp_v0 + 0x1C) = temp_fv1_2;
    *(f32 *)((u8 *)temp_v0 + 0x10) = (f32) (temp_fv1_2 * sp20);
    *(f32 *)((u8 *)temp_v0 + 0x14) = (f32) (temp_fv1_2 * sp24);
    *(f32 *)((u8 *)temp_v0 + 0x18) = (f32) (temp_fv1_2 * sp28);
    {
        s32 temp_t0 = *(s32 *)((u8 *)temp_v1 + 0x20);
    var_ft1 = (f32) temp_t0;
    if (temp_t0 < 0) {
        var_ft1 += 4294967296.0f;
    }
    *(f32 *)((u8 *)temp_v0 + 0x20) = var_ft1;
    temp_t1 = *(s32 *)((u8 *)temp_v1 + 8);
    var_ft0 = (f32) temp_t1;
    if (temp_t1 < 0) {
        var_ft0 += 4294967296.0f;
    }
    *(f32 *)((u8 *)temp_v0 + 0x24) = var_ft0;
    *(f32 *)((u8 *)temp_v0 + 0x28) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x2C) = 0.0f;
    *(s8 *)((u8 *)arg0 + 0x870) = (s8) *(s32 *)((u8 *)temp_v1 + 0x1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512DD50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DD50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DEA4.s")
