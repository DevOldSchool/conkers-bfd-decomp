#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B74A0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15189FF0
 * - func_1518A094
 * - func_1518A214
 * - func_1518A2E8
 * - func_1518A324
 * - func_1518A360
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
s32 func_151407D0(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15189FF0 CURRENT (1264) */
s32 func_15189FF0(s32 arg0, void *arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    s32 temp_v0;

    *(u8 *)((u8 *)arg1 + 0x58) = 0xB;
    temp_v0 = func_151407D0(arg1, 0x80, arg0, arg3 & 0xFF, (s32)arg4, (s32)arg5, (s32)arg6, -1, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x170, (void *)arg2, 0x20);
        return temp_v0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15189FF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_15189FF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A094.s")
extern f32 D_800A73C0;
extern f32 D_800A73C4;
extern f32 D_800A73C8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A214 CURRENT (2190) */
s32 func_1518A214(void *arg0, s8 *arg1) {
    s32 mode;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;

    mode = *(u8 *)(*(u8 **)((u8 *)arg0 + 0x188) + 0x68) - 0xF;
    switch (mode) {
    default:
        temp_v0_2 = (u8 *)arg0 + 0x110;
        *(f32 *)((u8 *)temp_v0_2 + 0x18) = D_800A73C0;
        *(f32 *)((u8 *)temp_v0_2 + 0x1C) = D_800A73C0;
        *(u8 *)((u8 *)arg0 + 0x2A) = 0;
        *(u8 *)((u8 *)arg0 + 0x29) = 0;
        *(u8 *)((u8 *)arg0 + 0x28) = 0xFF;
        *arg1 = 1;
        break;
    case 0:
        *(s32 *)((u8 *)arg0 + 0x58) &= ~2;
        *arg1 = 0;
        break;
    case 1:
        temp_v0_3 = (u8 *)arg0 + 0x110;
        *(f32 *)((u8 *)temp_v0_3 + 0x18) = D_800A73C4;
        *(f32 *)((u8 *)temp_v0_3 + 0x1C) = D_800A73C4;
        *(u8 *)((u8 *)arg0 + 0x28) = 0x80;
        *(u8 *)((u8 *)arg0 + 0x29) = 0;
        *(u8 *)((u8 *)arg0 + 0x2A) = 0;
        *arg1 = 1;
        break;
    case 2:
        temp_v0_4 = (u8 *)arg0 + 0x110;
        *(f32 *)((u8 *)temp_v0_4 + 0x18) = D_800A73C8;
        *(f32 *)((u8 *)temp_v0_4 + 0x1C) = D_800A73C8;
        *(u8 *)((u8 *)arg0 + 0x28) = 0xFF;
        *(u8 *)((u8 *)arg0 + 0x29) = 0;
        *(u8 *)((u8 *)arg0 + 0x2A) = 0;
        *arg1 = 1;
        break;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A214.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A2E8 CURRENT (245) */
s32 func_1518A2E8(void *arg0, s8 *arg1) {
    s32 var_v0;
    u8 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x188);
    temp_t0 = 1;
    var_v0 = 1;
    if (*(u8 *)((u8 *)temp_v0 + 0x6A) != 0) {
        *(s32 *)((u8 *)arg0 + 0x58) = *(s32 *)((u8 *)arg0 + 0x58) & ~2;
        *arg1 = 0;
    } else {
        *arg1 = temp_t0;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A2E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A2E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A324 CURRENT (820) */
s32 func_1518A324(void *arg0, s8 *arg1) {
    s32 var_v0;
    s32 temp_t0;
    void *temp_v0;

    var_v0 = 1;
    temp_t0 = 1;
    temp_v0 = *(void **)((u8 *)arg0 + 0x188);
    if (*(u8 *)((u8 *)temp_v0 + 0x6F) != 0) {
        *arg1 = temp_t0;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = *(s32 *)((u8 *)arg0 + 0x58) & ~2;
        *arg1 = 0;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A324 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A324.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A360 CURRENT (205) */
void func_1518A360(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x18);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x18) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0x1D) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x18) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0x1D) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A360 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A360.s")
