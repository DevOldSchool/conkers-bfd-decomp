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
typedef s32 (*Game18A094Callback)(void *, u8 *);
extern Game18A094Callback D_8008D5A0[];
s32 func_15083E90(u8);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A094 CURRENT (2483) */
s32 func_1518A094(void *arg0) {
    u8 *inner = (u8 *)arg0 + 0x170;
    u8 *target;
    struct {
        u8 padding[4];
        u8 value;
    } callback_result;
    s8 callback_index;
    void *frame;
    s32 flags;

    if (*(void **)((u8 *)arg0 + 0x188) == 0) {
        target = (u8 *)func_15083E90(inner[0x1D]);
        *(u8 **)(inner + 0x18) = target;
        if (target == 0) {
            return 0;
        }
    }
    inner = (u8 *)arg0 + 0x170;
    target = *(u8 **)(inner + 0x18);
    if (*(s32 *)target == 0 || inner[0x1D] != target[0x3B]) {
        return 0;
    }
    callback_index = *(s8 *)(inner + 0x1E);
    if (callback_index != -1) {
        if (D_8008D5A0[callback_index](arg0, &callback_result.value) == 0) {
            return 0;
        }
        if (callback_result.value == 0) {
            return 1;
        }
        target = *(u8 **)(inner + 0x18);
    }
    frame = *(void **)(target + 0x1D4);
    if (frame != 0) {
        frame = (u8 *)frame + (inner[0x1C] << 6);
        func_150A7960(frame, *(f32 *)(inner + 0), *(f32 *)(inner + 4),
                       *(f32 *)(inner + 8), (f32 *)((u8 *)arg0 + 0x34),
                       (f32 *)((u8 *)arg0 + 0x38), (f32 *)((u8 *)arg0 + 0x3C));
        func_150A7960(frame, *(f32 *)(inner + 0xC), *(f32 *)(inner + 0x10),
                       *(f32 *)(inner + 0x14), (f32 *)((u8 *)arg0 + 0x40),
                       (f32 *)((u8 *)arg0 + 0x44), (f32 *)((u8 *)arg0 + 0x48));
        flags = *(s32 *)((u8 *)arg0 + 0x58) | 2;
        *(s32 *)((u8 *)arg0 + 0x58) = flags;
        *(s32 *)((u8 *)arg0 + 0x58) = flags & ~4;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) &= ~2;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A094 */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A360 CURRENT (10) */
void func_1518A360(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if (arg2 == 0x2D) {
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
