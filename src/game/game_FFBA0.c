#include "types.h"

/*
 * Reviewed source unit: src/game/game_FFBA0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D26F0
 * - func_150D278C
 * - func_150D2924
 * - func_150D2D6C
 * - func_150D317C
 * - func_150D32FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_150D278C: unique active declaration in the allowed source */
void func_150D278C(s32, void *, u8, s32);
u32 func_150ADA20();                                /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D26F0 CURRENT (889) */
void func_150D26F0(u8 *arg0) {
    void *sp18;
    s32 temp_t1;
    u8 *temp_v1;

    temp_v1 = (void *)(arg0 + 0x28);
    if (*(u8 *)((u8 *)arg0 + 0x78) & 1) {
        temp_t1 = *(s32 *)((u8 *)temp_v1 + 0xC) - D_800BE9E4;
        *(s32 *)((u8 *)temp_v1 + 0xC) = temp_t1;
        if (temp_t1 < 0) {
            sp18 = temp_v1;
            func_150D278C(*(s32 *)((u8 *)arg0 + 0x28), temp_v1 + 0x10, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
            *(s32 *)((u8 *)temp_v1 + 0xC) = (s32) ((func_150ADA20() % (u32) (*(s32 *)((u8 *)temp_v1 + 8) + 1)) + *(s32 *)((u8 *)temp_v1 + 4));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D26F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D26F0.s")
void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
void *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800A0990[];
extern f32 D_800A099C;
extern f32 D_800A09A0;
extern f32 D_800A09A4;
extern f32 D_800A09A8;
extern f32 D_800A09AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D278C CURRENT (941) */
void func_150D278C(s32 arg0, void *arg1, u8 arg2, s32 arg3) {
    u8 packet[0x60];
    u8 choices[9];
    u8 *color;
    u8 *object;
    f32 temp;

    *(s32 *)(packet + 0) = arg0;
    *(f32 *)(packet + 4) = (2.0f * func_150ADA68()) * D_800A099C;
    temp = (func_150ADA68() * D_800A09A0) + D_800A09A4;
    *(f32 *)(packet + 8) = temp;
    *(f32 *)(packet + 0xC) = 1.0f / temp;
    *(f32 *)(packet + 0x10) = (func_150ADA68() * D_800A09A8) + D_800A09AC;
    if (func_150ADA20() & 1) {
        *(f32 *)(packet + 0x10) = -*(f32 *)(packet + 0x10);
    }
    *(f32 *)(packet + 0x14) = 0.0f;
    *(f32 *)(packet + 0x18) = 0.0f;
    func_10022EC0(packet + 0x1C, arg1, 0x40);
    *(u32 *)choices = *(u32 *)D_800A0990;
    *(u32 *)(choices + 4) = *(u32 *)(D_800A0990 + 4);
    choices[8] = D_800A0990[8];
    color = choices + (((func_150ADA20() % 3U) & 0xFF) * 3);
    packet[0x5C] = color[0];
    packet[0x5D] = color[1];
    packet[0x5E] = color[2];
    object = func_15149130((s16)((func_150ADA20() % 101U) + 0x64), -1,
                           0x32, -1, 1, 0, 0x60, arg2, arg3);
    if (object != 0) {
        func_10022EC0(object + 0x28, packet, 0x60);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D278C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D278C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2D6C.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D317C CURRENT (1600) */
s32 func_150D317C(u8 *arg0) {
    s32 var_v0;
    u8 *temp_s0;

    *(f32 *)((u8 *)arg0 + 0x128) = (f32) (*(f32 *)((u8 *)arg0 + 0x128) + (*(f32 *)((u8 *)arg0 + 0x130) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x12C) = (f32) (*(f32 *)((u8 *)arg0 + 0x12C) + (*(f32 *)((u8 *)arg0 + 0x134) * D_800BE9A4));
    temp_s0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x128));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    *(f32 *)((u8 *)arg0 + 0x110) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x18)) * *(f32 *)((u8 *)temp_s0 + 0x10)) + *(f32 *)((u8 *)temp_s0 + 8));
    var_v0 = 0;
    *(f32 *)((u8 *)temp_s0 + 4) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x1C)) * *(f32 *)((u8 *)temp_s0 + 0x14)) + *(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) - D_800BE9A4);
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) (*(f32 *)((u8 *)temp_s0 + 0x2C) * *(f32 *)((u8 *)temp_s0 + 0x28));
    if (*(f32 *)((u8 *)temp_s0 + 0x28) > 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D317C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D317C.s")
typedef struct {
    s32 field_0;
    u8 pad_4[0xC];
    u8 field_10[0x41];
    u8 field_51;
} GameFFBA0Child;

typedef struct {
    u8 pad_0;
    u8 field_1;
    u8 pad_2[0xA];
    u8 field_C;
    u8 pad_D[0x1B];
    GameFFBA0Child child;
} GameFFBA0State;

void func_150D278C(s32, void *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D32FC CURRENT (565) */
void func_150D32FC(GameFFBA0State *arg0, u8 *arg1, u8 arg2) {
    void *temp_v0;

    if (arg2 == 0x34) {
        temp_v0 = (void *)((u8 *)arg0 + 0x28);
        if (*arg1 == *(u8 *)((u8 *)temp_v0 + 0x51)) {
            func_150D278C(*(s32 *)temp_v0, (u8 *)temp_v0 + 0x10,
                          arg0->field_C, arg0->field_1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D32FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D32FC.s")
