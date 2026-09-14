#include "types.h"

/*
 * Reviewed source unit: src/game/game_40490.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15013000
 * - func_150130B4
 * - func_15013778
 * - func_150139AC
 * - func_15013D38
 * - func_15013DE8
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
 * - func_15015354
 * - func_15015644
 * - func_150156F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;

typedef s32 (*Game40490SimpleCallback)(u8 *);

extern Game40490SimpleCallback D_80082EA0[];
extern Game40490SimpleCallback D_80082ECC[];
extern Game40490SimpleCallback D_80082F40[];
extern void *func_1515D088(u8 *);

void func_15012FE0(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013000.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")
s32 func_1501370C(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x17];
    callback = D_80082EA0[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
s32 func_1501374C(u8 *arg0) {
    arg0[0x16] |= 4;
    func_1515D088(arg0);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013778.s")
s32 func_1501396C(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x17];
    callback = D_80082ECC[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
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

s32 func_15013C38(Game40490CallbackState *state) {
    Game40490Callback callback;
    f32 callback_value;
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
        callback_value = D_80096650 * (f32)state->callback_value;
        callback(state, callback_value);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013D38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013DE8.s")
void func_151CD2C0(s32 arg0, s32 arg1, s32 arg2);

s32 func_15013F9C(s32 arg0) {
    func_151CD2C0(arg0, 0xFF, 1);
    return 1;
}
s32 func_15013FC4(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x1B];
    callback = D_80082F40[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
extern void *D_800E0900[];

s32 func_15014004(void *arg0) {
    s32 index;

    index = *(s32 *)((u8 *)arg0 + 0x1C);
    if (index < 0) {
        return 1;
    }
    if (index >= 6) {
        return 1;
    }
    D_800E0900[index] = arg0;
    return 1;
}
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
extern void *D_800D9AA0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150142AC CURRENT (245) */
s32 func_150142AC(void *arg0) {
    u8 temp_t6;
    u8 temp_v1;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x16);
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x1B);
    *(u8 *)((u8 *)arg0 + 0x16) = temp_t6 | 4;
    if (((s8) temp_v1 < 0) || (temp_v1 >= 3)) {
        return 1;
    }
    D_800D9AA0[temp_v1] = arg0;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150142AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150144B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501474C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014B60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014F6C.s")
void *func_1515F1B0(void);
void func_1515F25C(void **, void *);
extern f32 D_800DCD90;
extern void *D_800DCDC4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150150A4 CURRENT (133) */
s32 func_150150A4(void) {
    void *sp1C;
    void *temp_v0;

    temp_v0 = func_1515F1B0();
    if (temp_v0 == 0) {
        return 1;
    }
    sp1C = temp_v0;
    func_1515F25C(&D_800DCDC4, temp_v0);
    D_800DCD90 += *(f32 *)((u8 *)sp1C + 8);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150150A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150150A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015104.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150151D4.s")
typedef struct {
    u8 pad_0[0x1C];
    s32 field_1C;
} Game40490State;

extern void (*D_80082F70[])(void);

s32 func_15015300(Game40490State *arg0) {
    void (*temp_v1)(void);
    s32 temp_v0;

    temp_v0 = arg0->field_1C;
    if ((temp_v0 < 0) || (temp_v0 >= 2)) {
        return 1;
    }
    temp_v1 = D_80082F70[temp_v0];
    if (temp_v1 != 0) {
        temp_v1();
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015354.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150156F4.s")
