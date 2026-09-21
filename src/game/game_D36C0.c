#include "types.h"

/*
 * Reviewed source unit: src/game/game_D36C0.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A6210
 * - func_150A6354
 * - func_150A6360
 * - func_150A6500
 * - func_150A6760
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_8009F6A0;
extern f32 D_800D35E0[2];
extern f32 D_800D9B20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A6210 CURRENT (10295) */
s32 func_150A6210(u8 *arg0, f32 arg1, f32 arg2, f32 arg3,
                  f32 arg4, f32 arg5, f32 arg6) {
    f32 z;
    f32 x;
    f32 y;
    f32 scale;
    f32 bound;
    f32 opposite;

    z = (*(f32 *)(arg0 + 8) * arg1) + (*(f32 *)(arg0 + 0x18) * arg2) +
        ((*(f32 *)(arg0 + 0x28) * arg3) + *(f32 *)(arg0 + 0x38));
    if ((z - arg4) > -D_800D9B20 || (z + arg4) < -arg6) {
        return 0;
    }
    x = (*(f32 *)(arg0 + 0) * arg1) + (*(f32 *)(arg0 + 0x10) * arg2) +
        ((*(f32 *)(arg0 + 0x20) * arg3) + *(f32 *)(arg0 + 0x30));
    scale = arg4 * D_8009F6A0;
    bound = -z + scale;
    if ((x - scale) * D_800D35E0[0] > bound) {
        return 0;
    }
    opposite = -bound;
    if ((x + scale) * D_800D35E0[0] < opposite) {
        return 0;
    }
    y = (*(f32 *)(arg0 + 4) * arg1) + (*(f32 *)(arg0 + 0x14) * arg2) +
        ((*(f32 *)(arg0 + 0x24) * arg3) + *(f32 *)(arg0 + 0x34));
    scale = arg5 * D_8009F6A0;
    if (((y - scale) * D_800D35E0[1] > bound) ||
        ((y + scale) * D_800D35E0[1] < opposite)) {
        return 0;
    }
    return (s32)z;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A6210 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6210.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A6354 CURRENT (300) */
void func_150A6354(void) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A6354 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6354.s")
extern f32 D_800D9B20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A6360 CURRENT (9040) */
s32 func_150A6360(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_fa1f;
    f32 temp_ft2f;
    f32 temp_ft2f_2;
    f32 temp_ft4;
    f32 temp_ft5;
    s32 var_v0;

    temp_ft5 = (*(f32 *)((u8 *)arg1 + 8) * arg2) + (*(f32 *)((u8 *)arg1 + 0x18) * arg3) + ((*(f32 *)((u8 *)arg1 + 0x28) * arg4) + *(f32 *)((u8 *)arg1 + 0x38));
    if (!((temp_ft5 - arg5) > -D_800D9B20) && !((temp_ft5 + arg5) < -arg7)) {
        temp_ft2f = (*(f32 *)((u8 *)arg1 + 0) * arg2) + (*(f32 *)((u8 *)arg1 + 0x10) * arg3) + ((*(f32 *)((u8 *)arg1 + 0x20) * arg4) + *(f32 *)((u8 *)arg1 + 0x30));
        temp_fa1f = -arg5;
        if ((((temp_ft2f * *(f32 *)((u8 *)arg0 + 0x88)) + (temp_ft5 * *(f32 *)((u8 *)arg0 + 0x90))) >= temp_fa1f) && (((temp_ft2f * *(f32 *)((u8 *)arg0 + 0x94)) + (temp_ft5 * *(f32 *)((u8 *)arg0 + 0x9C))) >= temp_fa1f)) {
            temp_ft2f_2 = (*(f32 *)((u8 *)arg1 + 4) * arg2) + (*(f32 *)((u8 *)arg1 + 0x14) * arg3) + ((*(f32 *)((u8 *)arg1 + 0x24) * arg4) + *(f32 *)((u8 *)arg1 + 0x34));
            temp_ft4 = -arg6;
            if ((((temp_ft2f_2 * *(f32 *)((u8 *)arg0 + 0xA4)) + (temp_ft5 * *(f32 *)((u8 *)arg0 + 0xA8))) >= temp_ft4) && (((temp_ft2f_2 * *(f32 *)((u8 *)arg0 + 0xB0)) + (temp_ft5 * *(f32 *)((u8 *)arg0 + 0xB4))) >= temp_ft4)) {
                var_v0 = (s32) temp_ft5;
                if (var_v0 == 0) {
                    return 1;
                }
                /* Duplicate return node #9. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
    var_v0 = 0;
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A6360 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6500.s")
typedef struct GameD36C0CodeEntry {
    u16 byte_offset;
    s16 bit_index;
} GameD36C0CodeEntry;

typedef struct GameD36C0TreeNode {
    s16 value;
    s16 zero_offset;
    s16 one_offset;
} GameD36C0TreeNode;

typedef struct GameD36C0TargetNode {
    s16 flags;
    u8 pad2[2];
    s16 alternate_offset;
    u8 pad6[6];
    s16 next_offset;
} GameD36C0TargetNode;

extern u8 *D_800BE5D0;
extern u8 *D_800BE5D4;
extern u8 *D_800BE5D8;
extern s16 D_800DBE30[];
extern u8 *D_800DBE48;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A6760 CURRENT (6675) */
void func_150A6760(s32 arg0) {
    s16 alternate_offset;
    s16 next_offset;
    s32 bit_index;
    s32 decoded;
    s32 bit_number;
    u8 *byte;
    u8 bits;
    u8 *entry;
    u8 *target;
    u8 *tree;
    u8 *tree_base;
    s32 mask;

    if (D_800BE5D0 != 0) {
        mask = ~(1 << arg0);
        target = D_800DBE48;
        bit_number = 0;
        entry = D_800BE5D4 + (D_800DBE30[arg0] * 4);
        bit_index = *(s16 *)(entry + 2);
        byte = D_800BE5D0 + *(u16 *)entry;
        bits = *byte;
        tree_base = D_800BE5D8;
        if (target != 0) {
loop_target:
            tree = tree_base;
            if (bit_number == 0) {
loop_tree:
                decoded = *(s16 *)tree;
                if (decoded < 0) {
                    if (bit_index-- == 0) {
                        byte++;
                        bits = *byte;
                        bit_index = 7;
                    }
                    if ((bits >> bit_index) & 1) {
                        tree = tree_base + *(s16 *)(tree + 4);
                    } else {
                        tree = tree_base + *(s16 *)(tree + 2);
                    }
                    goto loop_tree;
                }
            }
            *(s16 *)target = (*(s16 *)target & mask) | (((decoded >> bit_number) & 1) << arg0);
            if (bit_number < 7) {
                bit_number++;
            } else {
                bit_number = 0;
            }
            next_offset = *(s16 *)(target + 0xC);
            alternate_offset = *(s16 *)(target + 4);
            if (next_offset != 0) {
                target += next_offset;
                goto loop_target;
            }
            if (alternate_offset != 0) {
                target += alternate_offset;
                goto loop_target;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A6760 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6760.s")
