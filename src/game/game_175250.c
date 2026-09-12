#include "types.h"

/*
 * Reviewed source unit: src/game/game_175250.c
 * Boundary evidence: docs/evidence/game_raw_parametric_elements.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15147DA0
 * - func_15147EB8
 * - func_1514803C
 * - func_151488C4
 * - func_15148AF4
 * - func_15148BA4
 * - func_15148DE0
 * - func_15148F1C
 * - func_151490C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15147DA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15147EB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_1514803C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_151488C4.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15148AF4 CURRENT (860) */
s32 func_15148AF4(void *arg0) {
    s8 var_a1;
    void *temp_a2;
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x98);
    var_a1 = *(s8 *)((u8 *)arg0 + 0x2E);
    do {
        var_a1 -= 1;
        if (var_a1 < 0) {
            var_a1 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        temp_a2 = *(s32 *)((u8 *)arg0 + 0x94) + (var_a1 * 0x14);
        *(f32 *)((u8 *)temp_a2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_a2 + 0xC) - (*(f32 *)((u8 *)temp_v1 + 0x10) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 0) = (f32) (*(f32 *)((u8 *)temp_a2 + 0) + (*(f32 *)((u8 *)temp_v1 + 4) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 4) = (f32) (*(f32 *)((u8 *)temp_a2 + 4) + (*(f32 *)((u8 *)temp_a2 + 0xC) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 8) = (f32) (*(f32 *)((u8 *)temp_a2 + 8) + (*(f32 *)((u8 *)temp_v1 + 0xC) * D_800BE9A4));
    } while (var_a1 != *(s8 *)((u8 *)arg0 + 0x2D));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15148AF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148AF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148DE0.s")
s32 func_15148EF8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x98);
    *(u8 *)((u8 *)temp_v1 + 0x20) = 4;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148F1C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151490C8 CURRENT (425) */
s32 func_151490C8(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151490C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_151490C8.s")
void func_15149104(void) {
    func_151478F4();
}
