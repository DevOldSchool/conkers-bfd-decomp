#include "types.h"

/*
 * Reviewed source unit: src/game/game_131F30.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104A80
 * - func_15104C44
 * - func_15104FF8
 * - func_151050B0
 * - func_1510550C
 * - func_15105548
 * - func_1510558C
 * - func_15105848
 * - func_151058B4
 * - func_15105C24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104C44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104FF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151050B0.s")
void func_1516972C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510550C CURRENT (577) */
void func_1510550C(s32 arg0, s32 arg1, s32 arg2) {
    arg2 = arg2 & 0xFF;
    if (arg2 == 0x4B) {
        func_1516972C(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510550C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_1510550C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105548 CURRENT (410) */
void func_15105548(void *arg0, s32 *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0x38) && (*(u8 *)((u8 *)(*(void **)temp_v0) + 0x14) == 1)) {
        *(s16 *)((u8 *)temp_v0 + 4) = 0x12C;
        *(s32 *)((u8 *)temp_v0 + 0x70) = *arg1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_1510558C.s")

void func_151058B4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105848 CURRENT (210) */
void func_15105848(void *arg0, s32 arg1, u8 arg2) {
    void *part;

    if (arg2 == 0x38) {
        func_151058B4(arg0);
        arg0 = (u8 *)arg0 + 0x28;
        *(u8 *)((u8 *)arg0 + 0xC) = *(u8 *)((u8 *)arg0 + 0xC) | 1;
        return;
    }
    part = (u8 *)arg0 + 0x28;
    if (arg2 == 0x39) {
        *(u8 *)((u8 *)part + 0xC) = *(u8 *)((u8 *)part + 0xC) & ~1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105848 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151058B4.s")
void func_1508B20C(f32, f32, f32, s32);

void func_15105BC8(void *arg0) {
    void *temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x34) & 1) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x28);
        func_1508B20C((f32)*(s16 *)temp_v0, (f32)*(s16 *)((u8 *)temp_v0 + 2),
                       (f32)*(s16 *)((u8 *)temp_v0 + 4), 0x43FA0000);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105C24.s")
