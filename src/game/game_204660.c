#include "types.h"

/*
 * Reviewed source unit: src/game/game_204660.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D71B0
 * - func_151D7264
 * - func_151D7424
 * - func_151D7538
 * - func_151D75C4
 * - func_151D7724
 * - func_151D77C8
 * - func_151D7830
 * - func_151D792C
 * - func_151D7A38
 * - func_151D7CD0
 * - func_151D80C4
 * - func_151D8718
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D71B0 CURRENT (2001) */
s32 func_151D71B0(s16 arg0, u8 arg1, u8 arg2, s32 arg3,
                  s32 arg4, u8 arg5, s32 arg6) {
    s32 sp4C;
    s32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s8 sp39;
    u8 sp38;
    s32 sp34;
    s32 temp_v0;
    s32 var_v1;

    sp34 = 0;
    sp39 = 0;
    sp3C = 0.0f;
    sp40 = 0.0f;
    sp44 = 0.0f;
    sp48 = *(f32 *)&arg3;
    sp38 = arg2;
    temp_v0 = func_15149130((s16)arg0, -1, 0x42, -1,
                            (s32)arg1, 0x36, arg4 + 0x18,
                            (s32)arg5, arg6);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp4C = temp_v0;
        func_10022EC0((void *)(temp_v0 + 0x28), &sp34, 0x18);
        var_v1 = sp4C;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D71B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D71B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7264.s")
extern void (*volatile D_8008FCA4[])(void *, s32, u8);

void func_151D73A8(void *arg0, s32 arg1, u8 arg2) {
    volatile u8 *selector;

    selector = (volatile u8 *)((u8 *)arg0 + 0x2C);
    if (D_8008FCA4[*selector] != 0) {
        D_8008FCA4[*selector](arg0, arg1, arg2);
    }
}
void func_151D77C8();

void func_151D7404() {
    func_151D77C8();
}
void func_1514933C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D7424 CURRENT (200) */
void func_151D7424(s32 arg0) {
    func_151D7404();
    func_1514933C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D7424 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7424.s")
void func_15149368(s32 arg0);

void func_151D7450(s32 arg0) {
    func_151D7404(arg0);
    func_15149368(arg0);
}
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151D747C(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3D, (s32)arg0);
}
void func_10022EC0(void *, void *, s32);
s32 func_151D71B0(s16, u8, u8, s32, s32, u8, s32);

typedef struct Game204660D74B0Packet {
    void *owner;
    u8 field34;
    u8 field35;
    s8 field36;
    u8 pad37;
} Game204660D74B0Packet;

void func_151D74B0(void *arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    Game204660D74B0Packet packet;
    s32 temp_v0;

    packet.owner = arg0;
    packet.field34 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field35 = arg1;
    packet.field36 = arg2;
    temp_v0 = func_151D71B0(0x12C, 0, 0, 0x41400000, 8, (s32)arg3, arg4);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x40), &packet, 8);
    }
}
void func_1516972C(s32, ...);
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D7538 CURRENT (1142) */
void func_151D7538(void *arg0, void *arg1, s32 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x40;
    if ((u8)arg2 == 0x3D) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) ||
            (*(u8 *)(temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((s32)arg0);
        }
    } else {
        func_15149514((s32)arg1, (u8)arg2, (s32)temp_a2,
                      (s32)(temp_a2 + 4), (s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D7538 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7538.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D75C4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D7724 CURRENT (635) */
s32 func_151D7724(u8 *arg0) {
    u16 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x40));
    if ((*(s32 *)((u8 *)temp_v0 + 0x94) & 2) || (temp_v1 = *(u16 *)((u8 *)temp_v0 + 0x84), (temp_v1 == 4)) || (temp_v1 == 0xA) || (temp_v1 == 0xC)) {
        temp_v0_2 = (void *)(arg0 + 0x28);
        *(u8 *)((u8 *)temp_v0_2 + 5) = (u8) (*(u8 *)((u8 *)temp_v0_2 + 5) & 0xFFFE);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D7724 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7724.s")
s32 func_151D7770(void *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x40));
    temp_v0_2 = (void *)((u8 *)arg0 + 0x28);
    if (*(u16 *)((u8 *)temp_v0 + 0x84) == 0) {
        *(u8 *)((u8 *)temp_v0_2 + 5) = (u8)(*(u8 *)((u8 *)temp_v0_2 + 5) & 0xFFFE);
    }
    return 1;
}
s32 func_151D779C(void *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 temp_t7;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x40));
    temp_v0_2 = (void *)((u8 *)arg0 + 0x28);
    if (*(u8 *)((u8 *)temp_v0 + 0xAD) != 0) {
        *(u8 *)((u8 *)temp_v0_2 + 5) = (u8)(*(u8 *)((u8 *)temp_v0_2 + 5) & 0xFFFE);
    }
    return 1;
}
typedef struct Game204660ActorState {
    s32 active;
} Game204660ActorState;

typedef struct Game204660Actor {
    u8 pad0[0x1C];
    s16 timer;
    u16 flags;
    u8 pad20[0x10];
    s8 mode;
    u8 pad31[0x67];
    Game204660ActorState * volatile state;
} Game204660Actor;

typedef struct Game204660ActorContext {
    u8 pad0[0x28];
    Game204660Actor *actor;
} Game204660ActorContext;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D77C8 CURRENT (70) */
void func_151D77C8(Game204660ActorContext *arg0) {
    Game204660ActorState *temp_v1;
    Game204660Actor *temp_a1;
    Game204660Actor **temp_v0;
    s32 temp_t3;

    temp_v0 = &arg0->actor;
    if (*temp_v0 != 0) {
        temp_a1 = *temp_v0;
        temp_t3 = 0x14;
        temp_v1 = temp_a1->state;
        temp_a1->mode = 0;
        temp_a1 = *temp_v0;
        temp_a1->flags &= 0xFFFD;
        temp_a1 = *temp_v0;
        temp_a1->flags |= 8;
        temp_a1 = *temp_v0;
        temp_a1->flags |= 1;
        (*temp_v0)->timer = temp_t3;
        temp_v1->active = 0;
        *temp_v0 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D77C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D77C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D792C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7A38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7CD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D80C4.s")
extern f32 D_800AB2EC;
extern f32 D_800AB2F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8718 CURRENT (20) */
void func_151D8718(void *arg0, f32 *arg1, f32 arg2) {
    f32 temp_fv1;

    temp_fv1 = *arg1;
    *arg1 = temp_fv1 + (D_800AB2EC * arg2);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + ((temp_fv1 * arg2) + (D_800AB2F0 * (arg2 * arg2))));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8718 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D8718.s")
void func_151D8764(void *arg0) {
    register void **link = *(void ***)((u8 *)arg0 + 0x98);
    register void *leaf = *link;

    if (leaf) {
        *(s32 *)((u8 *)leaf + 0x28) = 0;
    }
}
/* Call context: func_151478F4: unique active project prototype */
/* Call context: func_151D8764: unique active project prototype */
void func_151478F4(s32);

void func_151D8780(void *arg0) {
    func_151D8764(arg0);
    func_151478F4((s32) arg0);
}
/* Call context: func_15147928: unique active project prototype */
/* Call context: func_151D8764: unique active project prototype */
void func_15147928(s32);

void func_151D87AC(void *arg0) {
    func_151D8764(arg0);
    func_15147928((s32) arg0);
}
