#include "types.h"

/*
 * Reviewed source unit: src/game/game_175250.c
 * Boundary evidence: docs/evidence/game_raw_parametric_elements.md
 *
 * TODO: Implement these source-unit functions:
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

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    s32 values[8];
} Struct15147DA0;

void *func_15147DA0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4,
                    s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                    s32 arg10, void *arg11, s32 arg12, u8 arg13, s32 arg14) {
    void *temp_v0;
    void *temp_a0;

    *(s32 *)((u8 *)arg0 + 0x10) = 1;
    temp_v0 = func_15147A80(arg0, (u8 *)arg2 + 0x48, 0x14, 1, 0, 1,
                           arg9, arg10, arg12, arg13, arg14);
    if (temp_v0 == 0) {
        return 0;
    }
    temp_a0 = *(void **)((u8 *)temp_v0 + 0x98);
    func_10022EC0(temp_a0, arg1, 0x20);
    *(s8 *)((u8 *)temp_a0 + 0x20) = arg3;
    *(s8 *)((u8 *)temp_a0 + 0x21) = arg4;
    *(s8 *)((u8 *)temp_a0 + 0x22) = arg5;
    *(s8 *)((u8 *)temp_a0 + 0x23) = arg6;
    *(s8 *)((u8 *)temp_a0 + 0x24) = arg7;
    *(s8 *)((u8 *)temp_a0 + 0x25) = arg8;
    *(Struct15147DA0 *)((u8 *)temp_a0 + 0x28) = *(Struct15147DA0 *)arg11;
    return temp_v0;
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15148DE0 CURRENT (1050) */
s32 func_15148DE0(void *arg0) {
    s32 var_v0;
    s32 temp_t9;
    s8 temp_v0;
    s32 var_a2;
    u8 *temp_a1;
    u8 *temp_v1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 >= 3) {
        *(s8 *)((u8 *)arg0 + 0x2C) = temp_v0 - 1;
        temp_a1 = *(u8 **)((u8 *)arg0 + 0x98);
        temp_v1 = *(u8 **)((u8 *)arg0 + 0x94);
        temp_t9 = (0x1000 / *(s8 *)((u8 *)arg0 + 0x2C)) & 0xFFFF;
        var_a2 = *(s8 *)((u8 *)arg0 + 0x2D);
        var_v0 = 0;
        if (temp_a1[0x18] & 0x20) {
            var_v0 = 0x1000;
        }
        *(s8 *)((u8 *)arg0 + 0x2E) = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (*(s8 *)((u8 *)arg0 + 0x2E) < 0) {
            *(s8 *)((u8 *)arg0 + 0x2E) = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        if (var_a2 != *(s8 *)((u8 *)arg0 + 0x2E)) {
            do {
                *(s16 *)(temp_v1 + (var_a2 * 0x14) + 0x10) = var_v0;
                if (temp_a1[0x18] & 0x20) {
                    var_v0 = (var_v0 - temp_t9) & 0xFFFF;
                } else {
                    var_v0 = (var_v0 + temp_t9) & 0xFFFF;
                }
                var_a2 += 1;
                if (var_a2 == *(u8 *)((u8 *)arg0 + 0x25)) {
                    var_a2 = 0;
                }
            } while (var_a2 != *(s8 *)((u8 *)arg0 + 0x2E));
        }
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15148DE0 */
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
