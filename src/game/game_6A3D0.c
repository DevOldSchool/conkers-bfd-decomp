#include "types.h"

/*
 * Reviewed source unit: src/game/game_6A3D0.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503CF20
 * - func_1503D368
 * - func_1503D45C
 * - func_1503D484
 * - func_1503D510
 * - func_1503D5F0
 * - func_1503D660
 * - func_1503D774
 * - func_1503D804
 * - func_1503D984
 * - func_1503DA3C
 * - func_1503DA9C
 * - func_1503DC3C
 * - func_1503DD1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503CF20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D368.s")
void func_1503D438(s32 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if ((temp_v0 != 0) && !(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D45C CURRENT (170) */
void func_1503D45C(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 temp_t6;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = *var_a0;
    if (var_v0 != 0) {
        do {
            temp_t6 = var_v0 + arg1;
            var_v0 = *(s32 *)((u8 *)var_a0 + 8);
            *(s32 *)((u8 *)var_a0 + 0) = temp_t6;
            var_a0 += 8;
        } while (var_v0 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D45C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D45C.s")
extern s16 D_800C5A90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D484 CURRENT (198) */
void func_1503D484(u8 *arg0, s32 arg1) {
    u16 *var_s0;
    u16 *temp_s1;
    u16 temp_t8;

    var_s0 = (u16 *)arg0;
    temp_s1 = var_s0;
    if (*(u16 *)var_s0 != 0x3E7) {
        do {
            if (*(s32 *)((u8 *)var_s0 + 4) != 0) {
                func_1503D438((s32 *)((u8 *)var_s0 + 4), (s32)temp_s1);
            }
            temp_t8 = *(u16 *)((u8 *)var_s0 + 8);
            var_s0 = (u16 *)((u8 *)var_s0 + 8);
        } while (temp_t8 != 0x3E7);
    }
    D_800C5A90[arg1] = (s16)(((s32)((u8 *)var_s0 - (u8 *)temp_s1)) >> 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D510.s")
extern u8 *D_80084410[];
extern u8 D_80098888[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D5F0 CURRENT (2240) */
s32 func_1503D5F0(s32 arg0) {
    s32 group_index;
    s32 entry_index;
    u8 *group;
    u8 *count;
    u8 *entry;
    u8 group_size;

    count = D_80098888;
    group_index = 0;
loop_groups:
    group_size = *count;
    entry_index = 0;
    if ((s32) group_size > 0) {
        group = D_80084410[group_index];
        entry = group;
loop_entries:
        entry_index++;
        if (arg0 == *entry) {
            return *group;
        }
        entry++;
        if (entry_index >= (s32) group_size) {
            goto next_group;
        }
        goto loop_entries;
    }
next_group:
    group_index++;
    count++;
    if (group_index == 5) {
        return arg0;
    }
    goto loop_groups;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D5F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D5F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D660.s")
s32 *func_1502B6BC(s32 *, s32, s32, s32, s32, s32);
extern s32 D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D774 CURRENT (417) */
s32 func_1503D774(s32 arg0, void *arg1) {
    s32 sp2C;
    s32 *sp24;
    s32 *temp_v1;
    s32 *temp_v0;

    temp_v1 = &D_800D1C90[arg0];
    if (*temp_v1 != 0) {
        return 0;
    }
    sp24 = temp_v1;
    temp_v0 = func_1502B6BC(&sp2C, 2, 0, 2, 0x11, arg0);
    if (temp_v0 == 0) {
        *sp24 = 0;
        return 2;
    }
    *sp24 = (s32)temp_v0;
    *sp24 = *temp_v0;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D774 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D774.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D804.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D984.s")
extern s32 D_800D19A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DA3C CURRENT (115) */
s32 func_1503DA3C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    u8 var_v1;
    u8 *temp_v1;

    temp_v0 = D_800D19A0[arg0];
    temp_v1 = (u8 *)temp_v0 - 0x38;
    if (temp_v0 == 0) {
        return 0xFF;
    }
    if (*(u32 *)(temp_v1 + 0x34) < (u32)(arg1 + 1)) {
        return 0xFF;
    }
    temp_v0_2 = *(s32 *)(temp_v1 + 0x30);
    var_v1 = 0xFF;
    if (temp_v0_2 != 0) {
        var_v1 = *((u8 *)temp_v0_2 + arg1);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DA3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DA3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DA9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DC3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DD1C.s")
