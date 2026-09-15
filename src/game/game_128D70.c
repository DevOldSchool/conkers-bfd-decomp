#include "types.h"

/*
 * Reviewed source unit: src/game/game_128D70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FB8C0
 * - func_150FC368
 * - func_150FC438
 * - func_150FC614
 * - func_150FC818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FB8C0.s")
/* Call context: func_151C3B0C: unique active project prototype */
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FC368 CURRENT (335) */
void func_150FC368(void *arg0) {
    s32 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x1A0);
    if ((temp_v0 == 0) || (*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) == 0xFF) || (*(u8 *)((u8 *)arg0 + 0x1A4) != *(u8 *)((u8 *)temp_v0 + 0x3B)) || (temp_v1 = *(void **)((u8 *)temp_v0 + 0x31C), (temp_v1 == 0)) || (*(u8 *)((u8 *)temp_v1 + 0x84) != 0) || (*(u8 *)((u8 *)temp_v0 + 0x127) == 0xFF) || (temp_v1_2 = *(void **)((u8 *)temp_v0 + 0x318), (temp_v1_2 == 0))) {
        var_v0 = 0xFF;
    } else {
        var_v0 = ~(1 << *(u8 *)((u8 *)temp_v1_2 + 0x23D)) & 0xFF;
    }
    func_151C3B0C(arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFF, 0xFF, var_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FC368 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC368.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC614.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC818.s")
