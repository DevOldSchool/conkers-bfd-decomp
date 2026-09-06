#include "types.h"

/*
 * Reviewed source unit: src/game/game_105FC0.c
 * Boundary evidence: docs/evidence/game_raw_particle_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D8B3C
 * - func_150D8B88
 * - func_150D8D84
 * - func_150D8E1C
 * - func_150D8E4C
 * - func_150D8FAC
 * - func_150D942C
 * - func_150D9C7C
 * - func_150DA484
 * - func_150DA4E0
 * - func_150DA50C
 * - func_150DA5EC
 * - func_150DA628
 * - func_150DA67C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D8B10(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 20.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8B3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8B88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8D84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8E1C CURRENT (345) */
void func_150D8E1C(void *arg0) {
    u16 temp_t0;
    u16 temp_t8;

    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    temp_t8 = *(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD;
    temp_t0 = temp_t8 | 8;
    *(u16 *)((u8 *)arg0 + 0x1E) = temp_t8;
    *(u16 *)((u8 *)arg0 + 0x1E) = temp_t0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (temp_t0 | 1);
    *(s16 *)((u8 *)arg0 + 0x1C) = 0x28;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8E1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8E1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8E4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D942C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D9C7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA484.s")
void func_150DA4B4(s32 arg0) {
    func_150DA484(arg0);
    func_151478F4(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA4E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA50C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA5EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA67C.s")
