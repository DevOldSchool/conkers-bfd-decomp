#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FC60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012C84 CURRENT (1025) */
void func_15012C84(u8 *arg0, s32 arg1) {
    u32 i;

    for (i = 0; i < (u32)arg1; i++) {
        ((u8 *)D_800BE510)[D_800BE528 * 3] = arg0[i * 0x10 + 0xC];
        ((u8 *)D_800BE510)[D_800BE528 * 3 + 1] = arg0[i * 0x10 + 0xD];
        ((u8 *)D_800BE510)[D_800BE528 * 3 + 2] = arg0[i * 0x10 + 0xE];
        D_800BE528++;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012C84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_15012C84.s")
extern u8 D_800BE530[];
extern s16 D_800BE550[];
extern u8 D_800BE564;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012ED8 CURRENT (375) */
void func_15012ED8(u32 *arg0) {
    u32 index;
    s32 tag;
    u32 *record;
    u8 value;
    u8 *output;

    index = 0;
    tag = *arg0;
    record = arg0;
    tag = (s8)((u32)tag >> 24);
    while (tag != -0x21) {
        if (tag == -5) {
            tag = D_800BE564;
            D_800BE550[tag] = index;
            output = D_800BE530 + (tag * 3);
            output[0] = (u8)(record[1] >> 24);
            output[1] = (u8)(record[1] >> 16);
            value = (u8)(record[1] >> 8);
            D_800BE564 = tag + 1;
            output[2] = value;
        }
        tag = record[2];
        index += 1;
        record += 2;
        tag = (s8)((u32)tag >> 24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012ED8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_15012ED8.s")
