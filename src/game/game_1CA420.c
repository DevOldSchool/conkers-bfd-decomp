#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CA420.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519CF70
 * - func_1519CFA0
 * - func_1519CFD0
 * - func_1519D000
 * - func_1519D030
 * - func_1519D240
 * - func_1519D454
 * - func_1519D9F4
 * - func_1519E1F4
 * - func_1519E304
 * - func_1519E3BC
 * - func_1519E464
 * - func_1519E570
 * - func_1519E61C
 * - func_1519E688
 * - func_1519E6BC
 * - func_1519E754
 * - func_1519E818
 * - func_1519E8CC
 * - func_1519E8F8
 * - func_1519E924
 * - func_1519E948
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519CF70.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519CFA0 CURRENT (220) */
void func_1519CFA0(void *arg0) {
    u8 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    temp_t0 = *(u8 *)((u8 *)temp_v0 + 6) | 1;
    *(u8 *)((u8 *)temp_v0 + 6) = temp_t0;
    *(u8 *)((u8 *)temp_v0 + 6) = (u8) (temp_t0 | 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519CFA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519CFA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519CFD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D000.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D030.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D240.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D454.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D9F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519E1F4 CURRENT (1287) */
void func_1519E1F4(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1519CFA0(arg0);
        }
    } else if (temp_t6 == 6) {
        if ((u8) *(s32 *)((u8 *)arg1 + 0) == *(u8 *)((u8 *)temp_v0 + 0x4C)) {
            func_1519CFA0(arg0);
        }
    } else if (temp_t6 == 7) {
        if ((*(s32 *)((u8 *)temp_v0 + 0) == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1519CFA0(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)temp_v0 + 0);
        if (temp_a0 == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519E1F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E304.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E3BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E464.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E61C.s")
void func_1519E65C(s32 arg0) {
    func_1519CF70(3);
    func_1519CF70(4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E688.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E6BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E754.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E818.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E8CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E8F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E948.s")
