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
