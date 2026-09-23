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
    s16 last_index;
} GameEDE60ResourceList;

void func_1516972C(void *);

void func_150C0A48(s32 arg0) {
    GameEDE60ResourceList *list;
    GameEDE60ResourceEntry *entries;
    s32 index;
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
/* SDK memcpy alias and the matched allocator declaration. */
void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C0AC0 CURRENT (815) */
void *func_150C0AC0(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *allocated;
    s32 size;
    s16 index;
    s16 next;

    size = (*(s16 *)(arg0 + 0x14) * 8) + 0x48;
    if (!(arg0[0x18] & 2)) {
        if (*(s32 **)(arg0 + 8) == 0) {
            return 0;
        }
        if (**(s32 **)(arg0 + 8) == 0) {
            return 0;
        }
    }
    allocated = func_15167A68(0x25, arg2, size, 1, arg1, 1);
    if (allocated == 0) {
        return 0;
    }
    func_10022EC0(allocated + 0x18, arg0, 0x1C);
    *(u8 **)(allocated + 0x40) = allocated + 0x48;
    if (arg0[0x18] & 2) {
        *(f32 *)(allocated + 0x34) = **(f32 **)(allocated + 0x18);
        *(f32 *)(allocated + 0x38) = *(f32 *)(*(u8 **)(allocated + 0x18) + 8);
    } else {
        *(f32 *)(allocated + 0x34) = *(f32 *)(*(u8 **)(allocated + 0x20) + 0x14);
        *(f32 *)(allocated + 0x38) = *(f32 *)(*(u8 **)(allocated + 0x20) + 0x1C);
    }
    *(f32 *)(allocated + 0x3C) = 0.0f;
    *(s16 *)(allocated + 0x44) = -1;
    *(s16 *)(allocated + 0x46) = 0;
    index = 0;
    if (*(s16 *)(arg0 + 0x14) - 1 > 0) {
        do {
            next = index + 1;
            *(s16 *)(*(u8 **)(allocated + 0x40) + (index * 8) + 4) = next;
            index = next;
        } while (next < *(s16 *)(arg0 + 0x14) - 1);
    }
    *(s16 *)(*(u8 **)(allocated + 0x40) + (*(s16 *)(arg0 + 0x14) * 8) - 4) = -1;
    *(s32 *)(allocated + 0x10) = 1;
    *(s32 *)(allocated + 0x14) = 0;
    return allocated;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C0AC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0AC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0C38.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1198 CURRENT (440) */
void func_150C1198(u8 *arg0) {
    GameEDE60ResourceEntry *entry;
    GameEDE60ResourceList *list;
    s16 index;
    s16 previous;
    s32 found;

    list = *(GameEDE60ResourceList **) (arg0 + 0xA8);
    index = list->first_index;
    found = 0;
    previous = -1;
    if (index != -1) {
        do {
            entry = &list->entries[index];
            if (arg0 == entry->resource) {
                found = 1;
            } else {
                previous = index;
                index = entry->next_index;
            }
        } while ((index != -1) && (found == 0));
    }
    if (found != 0) {
        entry = &list->entries[index];
        if (index == list->first_index) {
            list->first_index = entry->next_index;
        } else {
            list->entries[previous].next_index = entry->next_index;
            entry = &list->entries[index];
        }
        entry->next_index = list->last_index;
        list->last_index = index;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1198 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C1198.s")
