#include "types.h"

/*
 * Reviewed source unit: src/game/game_10CCD0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DF820
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15124B18(void *arg0);
extern f32 D_800A0F60;
extern f32 D_800A0F64;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF820 CURRENT (85) */
void func_150DF820(void *arg0) {
    s32 flags;

    *(s32 *)((u8 *)arg0 + 0x84) &= ~0x4000;
    flags = (*(volatile s32 *)((u8 *)arg0 + 0x84) = *(s32 *)((u8 *)arg0 + 0x84) | 4);
    *(s32 *)((u8 *)arg0 + 0x84) = flags & ~0x1010;
    if (*(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x3D0) + 0xAD) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x1010;
        *(volatile s32 *)((u8 *)arg0 + 0x84) = *(s32 *)((u8 *)arg0 + 0x84) & ~4;
        *(f32 *)((u8 *)arg0 + 0x374) = D_800A0F60;
        return;
    }
    if (D_800A0F64 == *(f32 *)((u8 *)arg0 + 0x374)) {
        *(s16 *)((u8 *)arg0 + 0x1B4) = 3;
        func_15124B18(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF820 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10CCD0/func_150DF820.s")
