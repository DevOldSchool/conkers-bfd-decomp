#include "types.h"

/*
 * Reviewed source unit: src/game/game_B21B0.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15084D00
 * - func_15084D70
 * - func_15085430
 * - func_15085710
 * - func_150859AC
 * - func_15085ABC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameB21B0Inner {
    u8 pad0[0x11B];
    u8 field_11B;
} GameB21B0Inner;

typedef struct GameB21B0Object {
    u8 pad0[4];
    u8 field_4;
    u8 pad5[0x317];
    GameB21B0Inner *inner;
} GameB21B0Object;

extern s32 D_80087240;
extern u8 D_8009D954;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084D00 CURRENT (1665) */
s32 func_15084D00(GameB21B0Object *arg0) {
    s32 entry_index;
    s32 group_index;
    u8 *count;
    u8 *entry;
    u8 *group;
    s32 group_size;
    s32 value;

    value = arg0->field_4;
    count = &D_8009D954;
    group_index = 0;
loop_groups:
    group_size = *count;
    entry_index = 0;
    if (group_size > 0) {
        group = *(u8 **)((u8 *)&D_80087240 + (group_index * 4));
        entry = group;
loop_entries:
        entry_index++;
        if (value == *entry) {
            return *group;
        }
        entry++;
        if (entry_index >= group_size) {
            goto next_group;
        }
        goto loop_entries;
    }
next_group:
    group_index++;
    count++;
    if (group_index == 7) {
        return value;
    }
    goto loop_groups;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084D00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D70.s")
void func_15085410(GameB21B0Object *arg0, s32 arg1) {
    arg0->inner->field_11B = arg1;
}
u8 func_15085420(GameB21B0Object *arg0) {
    return arg0->inner->field_11B;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085710.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_150859AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085ABC.s")
