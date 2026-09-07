#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A89B0.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517B500
 * - func_1517B6E8
 * - func_1517B7F8
 * - func_1517B89C
 * - func_1517BBAC
 * - func_1517CFC4
 * - func_1517D074
 * - func_1517D578
 * - func_1517D5FC
 * - func_1517D690
 * - func_1517D7B0
 * - func_1517DE5C
 * - func_1517E05C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B500.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517B6E8 CURRENT (700) */
s32 func_1517B6E8(void *arg0, void *arg1, s32 *arg2, u8 *arg3) {
    s32 temp_t1;
    s32 temp_v0;
    u8 temp_t0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0x600) {
        *(s16 *)((u8 *)arg1 + 2) = (s16) (((temp_v0 >> 6) + *(s16 *)((u8 *)arg0 + 2)) - 0x18);
        *(s16 *)((u8 *)arg1 + 0) = (s16) ((((s32) *arg2 >> 8) + *(s16 *)((u8 *)arg0 + 0)) - 6);
        temp_t0 = *arg3;
        temp_t1 = (s32) ((s32) (temp_t0 << 7) / (s32) (((s32) *arg2 >> 6) - 0x17)) >> 4;
        if (temp_t1 < (s32) temp_t0) {
            *arg3 = (u8) temp_t1;
        }
        *arg2 = 0x600;
    } else {
        *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
        *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    }
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517B6E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B6E8.s")
s32 func_1517B7A8(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 >= 0x300) {
        if (temp_v0 >= 0x501) {
            *arg2 = temp_v0 - 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
    *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517B7F8 */
s32 func_1517B7F8(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;

    temp_v0 = *arg2;
    if (temp_v0 >= 0xD00) {
        return 1;
    }
    temp_v1 = temp_v0 - 0x600;
    if (temp_v0 >= 0x100) {
        *(s16 *)((u8 *)arg1 + 2) = (s16) (*(s16 *)((u8 *)arg0 + 2) + ((s32) (0x190000 - (temp_v1 * temp_v1)) / 7680));
        temp_v0_2 = *arg2;
        if (temp_v0_2 >= 0x200) {
            if (temp_v0_2 >= 0xA01) {
                *arg2 = temp_v0_2 - 0x800;
            } else {
                *arg2 = 0x200;
            }
        }
    } else {
        *(s16 *)((u8 *)arg1 + 2) = (s16) *(s16 *)((u8 *)arg0 + 2);
    }
    *(s16 *)((u8 *)arg1 + 0) = (s16) *(s16 *)((u8 *)arg0 + 0);
    *(s16 *)((u8 *)arg1 + 4) = (s16) *(s16 *)((u8 *)arg0 + 4);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517B7F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B7F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B89C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517BBAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517CFC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D074.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D5FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D7B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517DE5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517E05C.s")
