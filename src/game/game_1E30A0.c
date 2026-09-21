#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E30A0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5BF0
 * - func_151B5E94
 * - func_151B5FCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5BF0.s")
void func_151B5E8C(void) {

}
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_15047D60(f32);
void func_15133894(void *);
extern f32 D_800AA434;
extern f32 D_800AA438;
extern f32 D_800AA43C;
extern f32 D_800AA440;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5E94 CURRENT (1385) */
void func_151B5E94(void *arg0) {
    f32 *values;
    f32 value;

    *(f32 *)((u8 *)arg0 + 0x170) += D_800AA434 * D_800BE9A4;
    if (D_800AA438 < *(f32 *)((u8 *)arg0 + 0x170)) {
        *(f32 *)((u8 *)arg0 + 0x170) = 0.0f;
        func_10010F88(0x502, 0x5DC0U, 0, 0, -1,
                      (s32)*(f32 *)((u8 *)arg0 + 0x38),
                      (s32)*(f32 *)((u8 *)arg0 + 0x3C),
                      (s32)*(f32 *)((u8 *)arg0 + 0x40), 0x64, 0x1F4);
    }
    values = (f32 *)((u8 *)arg0 + 0x170);
    if (values[0] < D_800AA43C) {
        value = values[1] +
                (func_15047D60(values[0]) * (D_800AA440 * values[1]));
    } else {
        value = values[1];
    }
    *(f32 *)((u8 *)arg0 + 0x1C) = value;
    *(f32 *)((u8 *)arg0 + 0x18) = value;
    func_15133894(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5E94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5E94.s")
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5FCC CURRENT (125) */
void func_151B5FCC(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0 & 0xFFFF, (u16) arg0);
        *(s32 *)((u8 *)arg0 + 0x88) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5FCC.s")
