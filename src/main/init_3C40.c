#include "types.h"

/*
 * Reviewed source unit: src/main/init_3C40.c
 * Boundary evidence: docs/evidence/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80003C6C
 * - func_80004074
 * - func_800043B4
 * - func_8000440C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct AllocatorBlock {
    struct AllocatorBlock *next;
    struct AllocatorBlock *prev;
    u32 taggedSize;
} AllocatorBlock;

typedef struct AllocatorFreeBlock {
    AllocatorBlock header;
    struct AllocatorFreeBlock *nextFree;
    struct AllocatorFreeBlock *prevFree;
} AllocatorFreeBlock;

extern s32 D_8002AC30;
extern AllocatorFreeBlock *D_800380B0;
extern AllocatorFreeBlock *D_800380B8;

extern AllocatorFreeBlock *D_800380BC;
s32 func_80024880(s32);

s32 func_80003C6C(s32, s32, s32, s32, s32);

s32 func_80003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_80003C6C(arg0, arg1, arg2, 0, arg3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3C40/func_80003C6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80004074 CURRENT (1026) */
void func_80004074(s32 arg0) {
    AllocatorFreeBlock *block;
    AllocatorFreeBlock *neighbor;
    s32 merged;
    s32 mask;
    AllocatorFreeBlock *original;
    AllocatorFreeBlock *cursor;

    original = (AllocatorFreeBlock *)(arg0 - 0xC);
    if (arg0 != 0) {
        block = original;
        merged = 0;
        mask = func_80024880(1);
        neighbor = (AllocatorFreeBlock *)original->header.prev;
        ((u8 *)&original->header.taggedSize)[0] = 0;
        if ((neighbor != 0) && ((neighbor->header.taggedSize >> 24) == 0)) {
            neighbor->header.next = original->header.next;
            neighbor->header.taggedSize += original->header.taggedSize + 0xC;
            if (neighbor->header.next != 0) {
                neighbor->header.next->prev = &neighbor->header;
            }
            block = neighbor;
            merged = 1;
        }
        neighbor = (AllocatorFreeBlock *)block->header.next;
        if ((neighbor != 0) && ((neighbor->header.taggedSize >> 24) == 0)) {
            block->header.next = neighbor->header.next;
            block->header.taggedSize += neighbor->header.taggedSize + 0xC;
            if (block->header.next != 0) {
                block->header.next->prev = &block->header;
            }
            block->nextFree = neighbor->nextFree;
            if (block->nextFree != 0) {
                block->nextFree->prevFree = block;
            }
            cursor = neighbor->prevFree;
            if (cursor == 0) {
                D_800380B8 = block;
                block->prevFree = 0;
            } else if (cursor != block) {
                block->prevFree = cursor;
                if (cursor != 0) {
                    cursor->nextFree = block;
                }
            }
            merged = 1;
        }
        if (merged == 0) {
            cursor = D_800380B8;
            if (cursor == 0) {
                block->nextFree = 0;
                block->prevFree = 0;
                D_800380B8 = block;
            } else if ((u32)block < (u32)cursor) {
                block->nextFree = cursor;
                block->prevFree = 0;
                cursor->prevFree = block;
                D_800380B8 = block;
            } else {
                for (;;) {
                    neighbor = cursor->nextFree;
                    if (neighbor == 0) {
                        block->nextFree = 0;
                        block->prevFree = cursor;
                        cursor->nextFree = block;
                        break;
                    }
                    if ((u32)block < (u32)neighbor) {
                        block->nextFree = neighbor;
                        block->prevFree = cursor;
                        neighbor->prevFree = block;
                        cursor->nextFree = block;
                        break;
                    }
                    cursor = neighbor;
                }
            }
        }
        if (block->nextFree == 0) {
            D_800380BC = block;
        }
        if ((u32)D_8002AC30 < block->header.taggedSize) {
            D_8002AC30 = block->header.taggedSize;
            D_800380B0 = block;
        }
        func_80024880(mask);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80004074 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3C40/func_80004074.s")
void func_80004074(s32);
s32 func_80024880(s32);
void func_85042D50(void);
extern AllocatorBlock *D_800380B4;

void func_80004250(void) {
    u32 tag;
    AllocatorBlock *block;
    s32 mask;

    mask = func_80024880(1);
    block = D_800380B4;
    if (block != 0) {
        do {
            tag = block->taggedSize >> 24;
            if (tag == 2) {
                func_80004074((s32)(block + 1));
            } else if ((tag == 3) || (tag == 4)) {
                block->taggedSize = ((tag - 1) << 24) |
                    (block->taggedSize & 0xFFFFFF);
            }
            block = block->next;
        } while (block != 0);
    }
    func_80024880(mask);
}
void func_80004308(void) {
    u32 tag;
    AllocatorBlock *block;
    s32 mask;

    mask = func_80024880(1);
    block = D_800380B4;
    func_85042D50();
    if (block != 0) {
        do {
            tag = block->taggedSize >> 24;
            if ((tag == 1) || (tag == 2) || (tag == 3) || (tag == 4)) {
                func_80004074((s32)(block + 1));
            }
            block = block->next;
        } while (block != 0);
    }
    func_80024880(mask);
}
s32 func_80024880(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800043B4 CURRENT (160) */
void func_800043B4(void *arg0, s32 arg1) {
    s32 mask;
    AllocatorBlock *block;

    mask = func_80024880(1);
    block = (AllocatorBlock *)arg0 - 1;
    block->taggedSize = (block->taggedSize & 0xFFFFFF) | ((u32)arg1 << 24);
    func_80024880(mask);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800043B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3C40/func_800043B4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000440C */
void func_8000440C(void) {
    s32 maximum;
    AllocatorFreeBlock *largest;
    s32 size;
    AllocatorFreeBlock *block;

    block = D_800380B8;
    maximum = 0;
    if (block != 0) {
        do {
            size = block->header.taggedSize;
            if (maximum < size) {
                maximum = size;
                largest = block;
            }
            block = block->nextFree;
        } while (block != 0);
    }
    D_800380B0 = largest;
    D_8002AC30 = maximum;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000440C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3C40/func_8000440C.s")
