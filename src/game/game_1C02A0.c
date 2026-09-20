#include "types.h"

/*
 * Reviewed source unit: src/game/game_1C02A0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15192DF0
 * - func_15193234
 * - func_151932E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C02A0/func_15192DF0.s")
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15193234 CURRENT (1817) */
void func_15193234(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    u8 *temp_v0;

    arg2 &= 0xFF;
    if (arg2 == 0x2D) {
        temp_v0 = (u8 *)arg0 + 0x28;
        temp_a0 = *(s32 *)temp_v0;
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((arg2 == 0) &&
               ((*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x28)) ||
                (*(u8 *)((u8 *)arg0 + 0x2C) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15193234 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C02A0/func_15193234.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151932E0 CURRENT (1540) */
void func_151932E0(u8 *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v0 = arg0 + 0x28;
        temp_a0 = *(s32 *)(arg0 + 0x28);
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a0) {
            *(s32 *)(arg0 + 0x28) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)(arg0 + 0x28) = temp_v1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (temp_t6 == 0) {
        if ((*(s32 *)arg1 == *(s32 *)(arg0 + 0x28)) ||
            (*(u8 *)(arg0 + 0x2C) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151932E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C02A0/func_151932E0.s")
