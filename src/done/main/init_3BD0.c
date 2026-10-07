#include "types.h"

/*
 * Reviewed source unit: src/main/init_3BD0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
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

extern u32 D_80038098;
extern AllocatorFreeBlock *D_800380B0;
extern AllocatorBlock *D_800380B4;
extern AllocatorFreeBlock *D_800380B8;
extern AllocatorFreeBlock *D_800380BC;
extern AllocatorFreeBlock D_800E9D10;

void func_80003BD0(void) {
    D_800380B4 = &D_800E9D10.header;
    D_800380B4->next = 0;
    D_800380B4->prev = 0;
    D_800380B4->taggedSize = D_80038098 - (u32)&D_800E9D10 - 0x14;
    ((AllocatorFreeBlock *)D_800380B4)->nextFree = 0;
    ((AllocatorFreeBlock *)D_800380B4)->prevFree = 0;
    D_800380B8 = D_800380BC = (AllocatorFreeBlock *)D_800380B4;
    D_800380B0 = (AllocatorFreeBlock *)D_800380B4;
}
