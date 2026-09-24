#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BD940.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151904BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15190454(s32 arg0);
void func_151617E4(s32 arg0);
void func_1000FD38(void *, void *, s32);
void func_1516972C(void *);
void func_151D2B4C(s32);
void func_1518E298(void);

void func_15190490(s32 arg0) {
    func_15190454(arg0);
    func_151617E4(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151904BC CURRENT (246) */
void func_151904BC(void *arg0) {
    volatile s32 *field84;
    void *sp18;

    field84 = (volatile s32 *)((u8 *)arg0 + 0x84);
    if (*field84 != 0) {
        func_1516972C((void *)*field84);
    }
    sp18 = (u8 *)arg0 + 0x30;
    func_1000FD38(&func_1518E298, arg0, *(s32 *)((u8 *)arg0 + 0x10));
    func_151D2B4C(*(s32 *)((u8 *)(void *)sp18 + 0x48));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151904BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BD940/func_151904BC.s")
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8);

void func_15190518(void *arg0) {
    struct {
        void *object;
        u8 kind;
    } descriptor;

    descriptor.object = arg0;
    descriptor.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    func_1516944C(0x3E, (s8 *)&descriptor, 0x2A);
}
