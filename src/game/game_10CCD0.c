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

void func_15124B18(void);
extern f32 D_800A0F60;
extern f32 D_800A0F64;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF820 CURRENT (110) */
void func_150DF820(void *arg0) {
    s32 temp_t6 = *(s32 *)((u8 *)arg0 + 0x84);
    void *temp_t2 = *(void **)((u8 *)arg0 + 0x3D0);
    s32 temp_t1;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t9;
    u8 temp_t3;

    temp_t7 = temp_t6 & ~0x4000;
    temp_t9 = temp_t7 | 4;
    *(volatile s32 *)((u8 *)arg0 + 0x84) = temp_t7;
    *(volatile s32 *)((u8 *)arg0 + 0x84) = temp_t9;
    temp_t1 = temp_t9 & ~0x1010;
    *(volatile s32 *)((u8 *)arg0 + 0x84) = temp_t1;
    temp_t5 = temp_t1 | 0x1010;
    temp_t3 = *(u8 *)((u8 *)temp_t2 + 0xAD);
    if (temp_t3 != 0) {
        *(volatile s32 *)((u8 *)arg0 + 0x84) = temp_t5;
        *(volatile s32 *)((u8 *)arg0 + 0x84) = temp_t5 & ~4;
        *(f32 *)((u8 *)arg0 + 0x374) = D_800A0F60;
        return;
    }
    if (D_800A0F64 == *(f32 *)((u8 *)arg0 + 0x374)) {
        *(s16 *)((u8 *)arg0 + 0x1B4) = 3;
        func_15124B18();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF820 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10CCD0/func_150DF820.s")
