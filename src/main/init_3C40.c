#include "types.h"

/*
 * Reviewed source unit: src/main/init_3C40.c
 * Boundary evidence: docs/evidence/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80003C6C
 * - func_80004074
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
typedef struct {
    s16 values[5];
} AllocatorAlignmentTable;

extern AllocatorAlignmentTable D_8002AC34;
extern AllocatorAlignmentTable D_8002AC40;
extern AllocatorBlock *D_800380B4;
extern s32 D_800380C0;
extern s32 D_800380C4;
extern s32 D_800380C8;
extern s32 D_800380CC;
extern s32 D_800380D0;
extern s32 D_8003C8E0;
void func_850AD770(void);
void func_8000440C(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80003C6C CURRENT (1401) */
s32 func_80003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    AllocatorBlock *allocated;
    u8 *end;
    s32 aligned;
    u32 remainder;
    u32 blockSize;
    AllocatorBlock *previous;
    AllocatorBlock *following;
    AllocatorBlock *oldNext;
    AllocatorFreeBlock *nextFree;
    AllocatorFreeBlock *prevFree;
    s32 offset;
    s32 mask;
    AllocatorAlignmentTable offsets;
    AllocatorAlignmentTable masks;
    s32 interruptMask;
    AllocatorFreeBlock *block;

    offsets = D_8002AC34;
    masks = D_8002AC40;
    D_800380C0 = arg0;
    D_800380C4 = arg1;
    D_800380C8 = arg2;
    D_800380CC = arg3;
    D_800380D0 = arg4;
    if (arg2 == 2) {
        arg0 = (s32)(((u32)arg0 + 0xF) & ~0xFU);
    }
    if (arg0 < 8) {
        arg0 = 8;
    }
    arg0 = (s32)(((u32)arg0 + 3) & ~3U);
    offset = offsets.values[arg2];
    mask = masks.values[arg2];
    if (arg4 == 1 && D_8002AC30 < 0x7800) {
        return 0;
    }
    interruptMask = func_80024880(1);
    if (arg3 == 0) {
        block = D_800380B8;
    } else {
        block = D_800380BC;
    }
    for (;;) {
        if (block == 0) {
            func_80024880(interruptMask);
            if (arg4 == 0) {
                D_8003C8E0 = 0x0C000042;
                func_850AD770();
            }
            return 0;
        }
        blockSize = block->header.taggedSize;
        aligned = (s32)((u8 *)block + offset + 0xC) & mask;
        end = (u8 *)block + blockSize + 0xC;
        if ((u32)end >= aligned + (u32)arg0) {
            break;
        }
        if (arg3 == 0) {
            block = block->nextFree;
        } else {
            block = block->prevFree;
        }
    }
    if (arg3 == 0) {
        allocated = (AllocatorBlock *)((u32)aligned - 0xC);
        following = (AllocatorBlock *)((u32)allocated + (u32)arg0 + 0xC);
        remainder = (u32)block + blockSize -
                    ((u32)allocated + (u32)arg0);
    } else {
        allocated = (AllocatorBlock *)((((u32)block + blockSize -
                                        (u32)arg0 + 0xC) & mask) - 0xC);
        following = block->header.next;
        remainder = (u32)allocated - (u32)block;
    }
    previous = block->header.prev;
    nextFree = block->nextFree;
    prevFree = block->prevFree;
    if (arg3 == 0) {
        oldNext = block->header.next;
        if (remainder >= 0x14) {
            following->next = oldNext;
            following->taggedSize = remainder - 0xC;
            if (oldNext != 0) {
                oldNext->prev = following;
            }
            remainder = 0;
            ((AllocatorFreeBlock *)following)->nextFree = nextFree;
            ((AllocatorFreeBlock *)following)->prevFree = prevFree;
            if (nextFree != 0) {
                nextFree->prevFree = (AllocatorFreeBlock *)following;
            } else {
                D_800380BC = (AllocatorFreeBlock *)following;
            }
            if (prevFree != 0) {
                prevFree->nextFree = (AllocatorFreeBlock *)following;
            } else {
                D_800380B8 = (AllocatorFreeBlock *)following;
            }
        } else {
            following = oldNext;
            if (nextFree != 0) {
                nextFree->prevFree = prevFree;
            } else {
                D_800380BC = prevFree;
            }
            if (prevFree != 0) {
                prevFree->nextFree = nextFree;
            } else {
                D_800380B8 = nextFree;
            }
        }
        if (previous == 0) {
            D_800380B4 = allocated;
        } else {
            previous->next = allocated;
            previous->taggedSize = (previous->taggedSize & 0xFF000000) |
                                   ((u32)allocated - (u32)previous - 0xC);
        }
        allocated->next = following;
        allocated->prev = previous;
        allocated->taggedSize = ((u32)arg1 << 24) | (remainder + (u32)arg0);
        if (following != 0) {
            following->prev = allocated;
        }
    } else if (remainder >= 0x14) {
        allocated->next = block->header.next;
        allocated->prev = &block->header;
        allocated->taggedSize = ((u32)arg1 << 24) |
                               ((u32)end - (u32)allocated - 0xC);
        oldNext = allocated->next;
        if (oldNext != 0) {
            oldNext->prev = allocated;
        }
        block->header.next = allocated;
        block->header.taggedSize = remainder - 0xC;
    } else {
        aligned = ((u32)block + offset + 0xC) & mask;
        allocated = (AllocatorBlock *)aligned - 1;
        allocated->next = following;
        allocated->prev = previous;
        allocated->taggedSize = ((u32)arg1 << 24) |
                               ((u32)end - (u32)allocated - 0xC);
        if (nextFree != 0) {
            nextFree->prevFree = prevFree;
        } else {
            D_800380BC = prevFree;
        }
        if (prevFree != 0) {
            prevFree->nextFree = nextFree;
        } else {
            D_800380B8 = nextFree;
        }
        if (previous == 0) {
            D_800380B4 = allocated;
        } else {
            previous->next = allocated;
            previous->taggedSize = (previous->taggedSize & 0xFF000000) |
                                   ((u32)allocated - (u32)previous - 0xC);
        }
        oldNext = allocated->next;
        if (oldNext != 0) {
            oldNext->prev = allocated;
        }
        oldNext = allocated->prev;
        if (oldNext != 0) {
            oldNext->next = allocated;
        }
    }
    if (block == D_800380B0) {
        func_8000440C();
    }
    func_80024880(interruptMask);
    return (s32)((u32)allocated + 0xC);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80003C6C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3C40/func_80003C6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80004074 CURRENT (862) */
void func_80004074(s32 arg0) {
    AllocatorFreeBlock *block;
    AllocatorFreeBlock *neighbor;
    AllocatorFreeBlock *cursor;
    s32 merged;
    s32 mask;
    AllocatorFreeBlock *original;
    AllocatorFreeBlock *nextFree;

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
                    nextFree = cursor->nextFree;
                    if (nextFree == 0) {
                        block->nextFree = 0;
                        block->prevFree = cursor;
                        cursor->nextFree = block;
                        break;
                    }
                    if ((u32)block < (u32)nextFree) {
                        block->nextFree = nextFree;
                        block->prevFree = cursor;
                        nextFree->prevFree = block;
                        cursor->nextFree = block;
                        break;
                    }
                    cursor = nextFree;
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

void func_800043B4(void *arg0, s32 arg1) {
    s32 mask;
    AllocatorBlock *block;

    mask = func_80024880(1);
    block = (AllocatorBlock *)((u32)arg0 - sizeof(AllocatorBlock));
    block->taggedSize = (block->taggedSize & 0xFFFFFF) | ((u32)arg1 << 24);
    func_80024880(mask);
}
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
