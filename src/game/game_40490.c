#include "types.h"

/*
 * Reviewed source unit: src/game/game_40490.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15013000
 * - func_150130B4
 * - func_1501370C
 * - func_1501374C
 * - func_15013778
 * - func_1501396C
 * - func_150139AC
 * - func_15013C38
 * - func_15013D38
 * - func_15013DE8
 * - func_15013F9C
 * - func_15013FC4
 * - func_15014004
 * - func_15014094
 * - func_15014144
 * - func_15014220
 * - func_150142AC
 * - func_150142EC
 * - func_150144B8
 * - func_1501474C
 * - func_15014B60
 * - func_15014F6C
 * - func_150150A4
 * - func_15015104
 * - func_150151D4
 * - func_15015300
 * - func_15015354
 * - func_15015644
 * - func_150156F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;

void func_15012FE0(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013000.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501370C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501374C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013778.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501396C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150139AC.s")
typedef struct Game40490CallbackState {
    u8 pad0[0x16];
    u8 flags;
    u8 pad17;
    s32 callback_index;
    u32 callback_value;
} Game40490CallbackState;

typedef void (*Game40490Callback)(Game40490CallbackState *, f32);

extern Game40490Callback D_80082F28[];
extern f32 D_80096650;
extern s32 D_800BE9F0;
extern u8 D_800C35E8;
extern u8 D_800C35EA;
extern u8 *D_800D2E4C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013C38 CURRENT (10) */
s32 func_15013C38(Game40490CallbackState *state) {
    Game40490Callback callback;
    s32 index;

    index = state->callback_index;
    state->flags |= 4;
    if ((D_800D2E4C[0x11] & 4) && (D_800BE9F0 == 0x13)) {
        return 1;
    }
    if ((D_800C35EA == 1) &&
        ((D_800C35E8 == 0xF) || (D_800C35E8 == 0x10) || (D_800C35E8 == 0x11))) {
        return 1;
    }
    if (index >= 6) {
        return 1;
    }
    callback = D_80082F28[index];
    if (callback != 0) {
        callback(state, (f32)state->callback_value * D_80096650);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15013C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013D38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013DE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013FC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014004.s")
extern void *D_800D9A20;
extern void *D_800D9A24;

s32 func_15014040(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x18);
    *(u8 *)((u8 *)arg0 + 0x16) = (u8) (*(u8 *)((u8 *)arg0 + 0x16) | 4);
    if (temp_v0 == 0) {
        D_800D9A20 = arg0;
    } else if (temp_v0 == 1) {
        D_800D9A24 = arg0;
    }
    return 1;
}
extern s8 D_800D987C;

s32 func_1501407C(s32 arg0) {
    D_800D987C = 0;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014094.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014220.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150144B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501474C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014B60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014F6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150150A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015104.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150151D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015300.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015354.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150156F4.s")
