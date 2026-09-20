#include "types.h"

/*
 * Reviewed source unit: src/game/game_E2880.c
 * Boundary evidence: docs/evidence/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B54A8
 * - func_150B5840
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516972C(void *arg0);

void *func_10022EC0(void *, const void *, u32);
void *func_15149130();
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2880/func_150B54A8.s")
void func_150B57C4(s32 arg0) {
    func_151D2B4C(6);
}
void func_15149368(s32 arg0);
void func_1514933C(s32);

void func_150B57E8(s32 arg0) {
    func_150B57C4(arg0);
    func_1514933C(arg0);
}
void func_150B5814(s32 arg0) {
    func_150B57C4(arg0);
    func_15149368(arg0);
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5840 CURRENT (1887) */
void func_150B5840(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x28)) || (*(u8 *)((u8 *)(arg0 + 0x28) + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (void *)(arg0 + 0x28);
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x28);
            temp_v1 = *(s32 *)((u8 *)arg1 + 0);
            if (temp_v1 == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(u8 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x28) = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5840 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2880/func_150B5840.s")
