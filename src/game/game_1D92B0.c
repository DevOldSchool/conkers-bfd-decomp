#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D92B0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 */

extern void func_1516944C(s32 arg0, s8 *arg1, u8 arg2, void *arg3);

void func_151ABE00(void *arg0) {
    struct {
        void *field0;
        u8 field8;
    } sp18;

    sp18.field0 = arg0;
    sp18.field8 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_1516944C(0x20, (s8 *) &sp18, 0xC, arg0);
}
