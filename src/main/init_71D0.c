#include "types.h"

/*
 * Reviewed source unit: src/main/init_71D0.c
 * Boundary evidence: docs/evidence/main_handwritten_family_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_800071D0
 * - func_8000777C
 * - func_800079D8
 * - func_80007A24
 * - func_80007A38
 * - func_80007C74
 * - func_80007DA0
 * - func_80007DAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct InitThreadQueueNode {
    struct InitThreadQueueNode *next;
    s32 priority;
    struct InitThreadQueueNode **queue;
} InitThreadQueueNode;

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_800071D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_8000777C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_800079D8 CURRENT (1275) */
void func_800079D8(InitThreadQueueNode **queue, InitThreadQueueNode *thread) {
    InitThreadQueueNode **link;
    InitThreadQueueNode *cursor;
    s32 priority;

    link = queue;
    cursor = *queue;
    priority = thread->priority;
    while (cursor->priority >= priority) {
        link = &cursor->next;
        cursor = cursor->next;
    }
    thread->next = *link;
    *link = thread;
    thread->queue = queue;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800079D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_800079D8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80007A24 CURRENT (10) */
InitThreadQueueNode *func_80007A24(InitThreadQueueNode **queue) {
    InitThreadQueueNode *thread;

    thread = *queue;
    *queue = thread->next;
    return thread;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80007A24 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_80007A24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_80007A38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_80007C74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_80007DA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_71D0/func_80007DAC.s")
