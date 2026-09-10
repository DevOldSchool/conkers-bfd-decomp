#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B050.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FDBA0
 * - func_150FDC2C
 * - func_150FDCAC
 * - func_150FDCD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513EDE4(s16);                           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDBA0 CURRENT (470) */
void *func_150FDBA0(void *arg0, s16 arg1) {
    void *temp_v0;

    temp_v0 = func_1513EDE4(arg1);
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)temp_v0 + 8) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
        *(s16 *)((u8 *)temp_v0 + 0x18) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x28) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x38) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDBA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDBA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDC2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDCAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDCD8.s")
