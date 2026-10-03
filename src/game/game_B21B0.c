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
    u8 modelIndex;
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

    value = arg0->modelIndex;
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
/* Fields recovered from the shared 0x1C-byte player records. */
typedef struct GameB21B0PlayerRecord {
    s32 field_0;
    s32 field_4;
    s8 field_8;
    s8 field_9;
    u8 field_A;
    u8 padB;
    s32 field_C;
    u8 pad10[0xC];
} GameB21B0PlayerRecord;

extern GameB21B0PlayerRecord D_800D213C[];
extern u16 D_800D2340;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150859AC CURRENT (970) */
s32 func_150859AC(s32 arg0, s32 arg1) {
    arg0 = (s16)arg0;
    arg1 = (s16)arg1;
    if (arg0 >= 0xFF) {
        return 0;
    }
    switch (arg1) {
    case 0:
        return D_800D2340 & (1 << arg0);
    case 1:
        return D_800D213C[arg0].field_0;
    case 2:
        return D_800D213C[arg0].field_4;
    case 3:
        return D_800D213C[arg0].field_8;
    case 4:
        return D_800D213C[arg0].field_9;
    case 5:
        return D_800D213C[arg0].field_A;
    case 6:
        return D_800D213C[arg0].field_C;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150859AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_150859AC.s")

void func_15085710(s16, s32, u8);
extern u8 D_800CC2D0[];
extern u8 D_800D18A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15085ABC CURRENT (200) */
void func_15085ABC(s16 arg0) {
    s32 var_s0;

    var_s0 = 0;
    if (D_800D18A8 != 0) {
        return;
    }
    do {
        if ((1 << var_s0) & arg0) {
            func_15085710(var_s0, 5, *(u8 *)(D_800CC2D0 + (var_s0 * 0x32C) + 0x1CA));
        }
        var_s0 += 1;
    } while (var_s0 != 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15085ABC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085ABC.s")
