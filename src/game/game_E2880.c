#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E2880.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B54A8
 * - func_150B5840
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_151D2AB0(s32);

void *func_150B53D0(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *owner;
        u8 selector;
        u8 pad[3];
        f32 x;
        f32 y;
        void *result;
    } locals;
    s32 duration;
    s32 var_v0;

    var_v0 = -1;
    if (arg0 == 0) {
        return 0;
    }
    locals.owner = arg0;
    locals.selector = *(u8 *)((u8 *)arg0 + 0x3B);
    locals.x = 0.0f;
    locals.y = 0.0f;
    if (arg1 == var_v0) {
        duration = 0x12C;
    } else {
        duration = arg1;
    }
    if (arg1 == var_v0) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    locals.result = func_15149130((s16)duration, -1, 0x24, -1, var_v0,
                                  0x23, 0x10, arg2, arg3);
    if (locals.result != 0) {
        func_10022EC0((u8 *)locals.result + 0x28, &locals.owner, 0x10);
        func_151D2AB0(6);
    }
    return locals.result;
}
typedef struct {
    u8 *owner;
    u8 selector;
    u8 pad[3];
    f32 first;
    f32 second;
} GameE2880Emitter;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15107700(void *, s16, s16, s16, s32, f32, f32, s32, s32, u8 *, s32, s32);
void func_15107B78(void *, s16, s16, u8, s32);
extern f32 D_8009FC20, D_8009FC24, D_8009FC28, D_8009FC2C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B54A8 CURRENT (47) */
void func_150B54A8(u8 *arg0) {
    u32 first;
    u32 second;
    u8 color[4];
    u32 third;
    GameE2880Emitter *state;
    u8 *owner;

    owner = *(u8 **)(arg0 + 0x28);
    state = (GameE2880Emitter *)(arg0 + 0x28);
    if (*(s32 *)owner == 0 || state->selector != owner[0x3B] || owner[4] == 0xFF) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    func_1502EA98(owner, 0xFF, 0xFF, 0xFF, 0x1E, 0, 0xA);
    state->first += (D_8009FC20 + func_150ADA68() * D_8009FC24) * D_800BE9A4;
    while (state->first > 1.0f) {
        color[0] = 0xBA;
        color[1] = 0xD2;
        color[2] = 0xFF;
        color[3] = func_150ADA20() % 126U + 0x82;
        first = func_150ADA20();
        second = func_150ADA20();
        third = func_150ADA20();
        func_15107700(owner, (s16)(first & 0xFF), (s16)(second % 101U - 0x3F),
                      (s16)((third & 0xF) + 0xF), 4, 129.0f,
                      func_150ADA68() * 75.0f + 35.0f, 0, 1, color, arg0[0xC], arg0[1]);
        state->first -= 1.0f;
    }
    state->second += (D_8009FC28 + func_150ADA68() * D_8009FC2C) * D_800BE9A4;
    while (state->second > 1.0f) {
        second = func_150ADA20();
        func_15107B78(owner, (s16)(second & 0xFF), (s16)(func_150ADA20() % 101U - 0x3F), arg0[0xC], arg0[1]);
        state->second -= 1.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B54A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2880/func_150B54A8.s")
void func_150B57C4(u8 *arg0) {
    func_151D2B4C(6);
}

void func_150B57E8(void *arg0) {
    func_150B57C4(arg0);
    func_1514933C(arg0);
}
void func_150B5814(void *arg0) {
    func_150B57C4(arg0);
    func_15149368(arg0);
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5840 CURRENT (110) */
void func_150B5840(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2;
    temp_v0 = arg0 + 0x28;
    if (temp_t6 == 0) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) || (temp_v0[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)temp_v0;
            temp_v1 = *(s32 *)((u8 *)arg1 + 0);
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)(arg1 + 4) == temp_a0) {
                *(s32 *)temp_v0 = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5840 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2880/func_150B5840.s")
