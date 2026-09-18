#include "types.h"

/*
 * Reviewed source unit: src/game/game_EDE60.c
 * Boundary evidence: docs/evidence/game_raw_owner_chain_resource_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C0AC0
 * - func_150C0C38
 * - func_150C1198
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150C0A48(s32 arg0);
void func_15169824(s32 arg0);

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150C09B0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x20, arg0 + 0x24, arg0);
}
void func_150C09F0(s32 arg0) {
    func_150C0A48(arg0);
    func_15169804(arg0);
}
void func_150C0A1C(s32 arg0) {
    func_150C0A48(arg0);
    func_15169824(arg0);
}
typedef struct {
    void *resource;
    s16 next_index;
    u8 pad6[2];
} GameEDE60ResourceEntry;

typedef struct {
    u8 pad0[0x40];
    GameEDE60ResourceEntry *entries;
    s16 first_index;
} GameEDE60ResourceList;

void func_1516972C(void *);

void func_150C0A48(s32 arg0) {
    GameEDE60ResourceList *list;
    GameEDE60ResourceEntry *entries;
    s16 index;
    s32 offset;

    list = (GameEDE60ResourceList *)arg0;
    index = list->first_index;
    if (index != -1) {
        entries = list->entries;
        do {
            offset = index * sizeof(GameEDE60ResourceEntry);
            func_1516972C(((GameEDE60ResourceEntry *)((u8 *)entries + offset))->resource);
            entries = list->entries;
            index = ((GameEDE60ResourceEntry *)((u8 *)entries + offset))->next_index;
        } while (index != -1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0AC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C1198.s")
