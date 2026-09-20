#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9260.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507BDB0
 * - func_1507C22C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9260/func_1507BDB0.s")
s32 func_150229E4(void *);
void func_1507BDB0(s32, s32, void *, s32);
extern u8 D_800C3638;
extern u8 D_800C3654;
extern u8 D_800CC2D0;
extern u8 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507C22C CURRENT (100) */
void func_1507C22C(s32 arg0) {
    u8 *var_s0;
    s32 temp_a0;

    var_s0 = &D_800CC2D0;
    do {
        if ((*(s32 *)(var_s0 + 0) != 0) &&
            !(*(s32 *)(var_s0 + 0x25C) & 0x200) &&
            ((arg0 == 0) || (var_s0[5] == 4)) &&
            ((D_800C3638 == 0) || (D_800C3654 != 0) ||
             (func_150229E4(var_s0) != 0))) {
            temp_a0 = *(s32 *)(var_s0 + 0x2D0);
            if ((temp_a0 != 0) && (var_s0[0x2FA] != 0)) {
                func_1507BDB0(temp_a0, *(s32 *)(var_s0 + 0x48), var_s0,
                              arg0);
            }
        }
        var_s0 += 0x32C;
    } while (var_s0 != &D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507C22C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9260/func_1507C22C.s")
void func_1507C324(void *arg0, void *arg1) {
    f32 temp_fv0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x2D0);
    temp_v1 = *(void **)((u8 *)arg1 + 0x2D0);
    if ((temp_v0 != 0) && (temp_v1 != 0)) {
        *(f32 *)((u8 *)temp_v0 + 8) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0x18) - 1.0f;
        if (temp_fv0 <= *(f32 *)((u8 *)temp_v0 + 8)) {
            *(f32 *)((u8 *)temp_v0 + 8) = temp_fv0;
        }
    }
}
