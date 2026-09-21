#include "types.h"

/*
 * Reviewed source unit: src/game/game_45880.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150183D0
 * - func_15018500
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10003C40(s32, s32, s32, s32);
void func_15018500(void);
extern u8 *D_800BE5D0;
extern u8 *D_800BE5D4;
extern u8 *D_800BE5D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150183D0 CURRENT (7062) */
void func_150183D0(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    s32 column;
    s32 row;
    s32 byte_index;
    s32 bit_index;
    s16 offset;
    u8 bits;
    u8 *source;
    u8 *output;
    u8 *node;
    u8 *tree;

    func_15018500();
    source = arg2;
    D_800BE5D0 = arg2;
    output = func_10003C40(arg1 * 4, 1, 0, 0);
    D_800BE5D4 = output;
    byte_index = -1;
    bit_index = 0;
    row = 0;
    tree = D_800BE5D8;
    do {
        column = 0;
        *(s16 *) output = byte_index;
        *(s16 *) (output + 2) = bit_index;
        output += 4;
loop_2:
        node = tree;
loop_3:
        if (*(s16 *) node < 0) {
            if (bit_index-- == 0) {
                bits = *source++;
                byte_index++;
                bit_index = 7;
            }
            if (((u32) bits >> bit_index) & 1) {
                offset = *(s16 *) (node + 4);
            } else {
                offset = *(s16 *) (node + 2);
            }
            node = tree + offset;
            goto loop_3;
        }
        column++;
        if (column != arg0) {
            goto loop_2;
        }
        row++;
    } while (row != arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150183D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_45880/func_150183D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_45880/func_15018500.s")
