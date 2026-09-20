#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FC60.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150127B0
 * - func_15012C84
 * - func_15012ED8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_150127B0.s")
extern s32 D_800BE510;
extern u16 D_800BE528;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012C84 CURRENT (13205) */
void func_15012C84(u8 *arg0, s32 arg1) {
    s32 temp_a3;
    s32 var_v0;
    u16 temp_t2;
    u16 temp_t4;
    u16 temp_t8;
    u8 temp_t7;
    u8 temp_t7_2;
    u8 *var_v1;
    u8 *var_v1_2;

    var_v0 = 0;
    if (arg1 != 0) {
        temp_a3 = arg1 & 3;
        if (temp_a3 != 0) {
            var_v1 = (void *)(arg0 + (0 * 0x10));
            do {
                temp_t7 = *(u8 *)((u8 *)var_v1 + 0xC);
                var_v0 += 1;
                var_v1 += 0x10;
                *(u8 *)(D_800BE510 + (D_800BE528 * 3)) = temp_t7;
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 1) = (u8) *(u8 *)((u8 *)var_v1 + -3);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 2) = (u8) *(u8 *)((u8 *)var_v1 + -2);
                D_800BE528 += 1;
            } while (temp_a3 != var_v0);
            if (var_v0 != arg1) {
                goto block_5;
            }
        } else {
block_5:
            var_v1_2 = (void *)(arg0 + (var_v0 * 0x10));
            do {
                temp_t7_2 = *(u8 *)((u8 *)var_v1_2 + 0xC);
                var_v1_2 += 0x40;
                *(u8 *)(D_800BE510 + (D_800BE528 * 3)) = temp_t7_2;
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 1) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x33);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 2) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x32);
                temp_t4 = D_800BE528 + 1;
                D_800BE528 = temp_t4;
                *(u8 *)(D_800BE510 + ((temp_t4 & 0xFFFF) * 3)) = *(u8 *)((u8 *)var_v1_2 + -0x24);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 1) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x23);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 2) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x22);
                temp_t8 = D_800BE528 + 1;
                D_800BE528 = temp_t8;
                *(u8 *)(D_800BE510 + ((temp_t8 & 0xFFFF) * 3)) = *(u8 *)((u8 *)var_v1_2 + -0x14);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 1) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x13);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 2) = (u8) *(u8 *)((u8 *)var_v1_2 + -0x12);
                temp_t2 = D_800BE528 + 1;
                D_800BE528 = temp_t2;
                *(u8 *)(D_800BE510 + ((temp_t2 & 0xFFFF) * 3)) = *(u8 *)((u8 *)var_v1_2 + -4);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 1) = (u8) *(u8 *)((u8 *)var_v1_2 + -3);
                *(u8 *)((u8 *)(D_800BE510 + (D_800BE528 * 3)) + 2) = (u8) *(u8 *)((u8 *)var_v1_2 + -2);
                D_800BE528 += 1;
            } while (var_v1_2 != ((arg1 * 0x10) + arg0));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012C84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_15012C84.s")
extern u8 D_800BE530[];
extern s16 D_800BE550[];
extern u8 D_800BE564;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012ED8 CURRENT (2085) */
void func_15012ED8(u32 *arg0) {
    s16 index;
    s8 tag;
    u32 *record;
    u32 value;
    u8 *output;

    index = 0;
    record = arg0;
    tag = (s8)(*record >> 24);
    while (tag != -0x21) {
        if (tag == -5) {
            D_800BE550[D_800BE564] = index;
            output = D_800BE530 + (D_800BE564 * 3);
            value = record[1];
            output[0] = (u8)(value >> 24);
            output[1] = (u8)(value >> 16);
            D_800BE564 += 1;
            output[2] = (u8)(value >> 8);
        }
        value = record[2];
        index += 1;
        record += 2;
        tag = (s8)(value >> 24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012ED8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_15012ED8.s")
