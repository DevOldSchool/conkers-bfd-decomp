#include "types.h"

/*
 * Reviewed source unit: src/game/game_D4450.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A6FA0
 * - func_150A70C0
 * - func_150A71C8
 * - func_150A7360
 * - func_150A751C
 * - func_150A76F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_8009A220[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A6FA0 CURRENT (10910) */
void func_150A6FA0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3,
                   f32 *arg4, u8 *arg5) {
    f32 var_ft2;
    f32 scale;
    s32 temp_a1;
    s32 temp_t4;
    s32 var_t6;
    u16 temp_t5;

    temp_t5 = *(u16 *)(arg2 + 0x10);
    temp_a1 = (arg1 * 0x10) + (s32)arg0;
    do {
        scale = *arg4;
        temp_t4 = (*arg3 - ((s32)temp_t5 >> 4)) & 0xFF;
        if (scale > 0.0f) {
            if (temp_t4 >= 0x41) {
                if (temp_t4 >= 0x81) {
                    if (temp_t4 >= 0xC1) {
                        var_ft2 = D_8009A220[0x100 - temp_t4];
                    } else {
                        var_ft2 = -D_8009A220[temp_t4 - 0x80];
                    }
                } else {
                    var_ft2 = -D_8009A220[0x80 - temp_t4];
                }
            } else {
                var_ft2 = D_8009A220[temp_t4];
            }
            var_t6 = (s32)(var_ft2 * scale);
        } else {
            var_t6 = 0;
        }
        *(s16 *)(arg0 + 2) = *(s16 *)(arg5 + 2) + var_t6;
        arg4++;
        arg3++;
        arg0 += 0x10;
        arg5 += 0x10;
    } while (temp_a1 != (s32)arg0);
    *(u16 *)(arg2 + 0x10) =
        (*(s8 *)(arg2 + 0x12) + temp_t5) & 0xFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A6FA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A6FA0.s")
extern f32 D_8009A220[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A70C0 CURRENT (9000) */
void func_150A70C0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3, u8 *arg4) {
    f32 var_ft2;
    f32 scale;
    s32 temp_a1;
    s32 temp_t4;
    u16 temp_t5;

    scale = *(f32 *)(arg2 + 4);
    temp_t5 = *(u16 *)(arg2 + 0x10);
    temp_a1 = (arg1 * 0x10) + (s32)arg0;
    do {
        temp_t4 = (*arg3 - ((s32)temp_t5 >> 4)) & 0xFF;
        if (temp_t4 >= 0x41) {
            if (temp_t4 >= 0x81) {
                if (temp_t4 >= 0xC1) {
                    var_ft2 = D_8009A220[0x100 - temp_t4];
                } else {
                    var_ft2 = -D_8009A220[temp_t4 - 0x80];
                }
            } else {
                var_ft2 = -D_8009A220[0x80 - temp_t4];
            }
        } else {
            var_ft2 = D_8009A220[temp_t4];
        }
        arg3++;
        *(s16 *)(arg0 + 2) =
            *(s16 *)(arg4 + 2) + (s32)(var_ft2 * scale);
        arg0 += 0x10;
        arg4 += 0x10;
    } while (temp_a1 != (s32)arg0);
    *(u16 *)(arg2 + 0x10) =
        (*(s8 *)(arg2 + 0x12) + temp_t5) & 0xFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A70C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A70C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A71C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A7360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A751C.s")
/* Semantic candidate only; the raw entry consumes live registers and tail-jumps. */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A76F0 CURRENT (3410) */
f32 func_150A76F0(u32 index, u32 lower_bound, u32 *table, u32 upper_bound) {
    index &= 0xFF;
    if (index < 0x41) {
        return *(f32 *)&table[lower_bound - index];
    }
    if (index < 0x81) {
        return -*(f32 *)&table[index - 0x80];
    }
    if (index < 0xC1) {
        return -*(f32 *)&table[upper_bound - index];
    }
    return *(f32 *)&table[index];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A76F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A76F0.s")
