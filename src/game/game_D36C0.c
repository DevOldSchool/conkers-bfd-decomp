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

#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D36C0/func_150A6354.s")
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
