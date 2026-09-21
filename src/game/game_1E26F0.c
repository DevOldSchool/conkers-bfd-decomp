#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E26F0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5240
 * - func_151B5328
 * - func_151B5A9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15083E90(u8);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800AA418;

typedef struct {
    u8 packet[0x5A8];
    u8 pad_5D8[4];
    s32 sp5DC;
} Game1E26F0Stack;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5240 CURRENT (582) */
s32 func_151B5240(s16 arg0, u8 arg1, s32 arg2) {
    Game1E26F0Stack stack;
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_v1;

    stack.packet[0x584] = 0x17;
    stack.packet[0x58C] = 0x16;
    *(s32 *)(stack.packet + 0x580) = func_15083E90(0x17);
    *(s32 *)(stack.packet + 0x588) = func_15083E90(stack.packet[0x58C]);
    temp_fv0 = 250.0f;
    *(f32 *)(stack.packet + 0x598) = temp_fv0;
    *(f32 *)(stack.packet + 0x590) = 18.0f;
    *(f32 *)(stack.packet + 0x5A0) = D_800AA418;
    *(f32 *)(stack.packet + 0x594) = 0.0f;
    *(f32 *)(stack.packet + 0x59C) = 1.0f / temp_fv0;
    temp_v0 = func_15149130(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        stack.sp5DC = temp_v0;
        func_10022EC0((void *)(temp_v0 + 0x28), stack.packet, 0x5A8);
        var_v1 = stack.sp5DC;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5240 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5240.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5328.s")
typedef struct {
    s32 first;
    s32 second;
    u8 firstFlag;
    u8 secondFlag;
} Game1E26F0Pair;

typedef struct {
    u8 pad0[0x580];
    s32 first;
    u8 firstFlag;
    u8 pad585[3];
    s32 second;
    u8 secondFlag;
} Game1E26F0State;

void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5A9C CURRENT (1940) */
void func_151B5A9C(u8 *arg0, void *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 temp_v1_3;
    void *temp_v0;
    void *temp_v0_2;

    if (arg2 == 0x2D) {
        temp_v0 = arg0 + 0x28;
        temp_a2 = *(s32 *)((u8 *) temp_v0 + 0x580);
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *) temp_v0 + 0x580) = *(s32 *)((u8 *) arg1 + 4);
            *(u8 *)((u8 *) temp_v0 + 0x584) = *(u8 *)((u8 *) arg1 + 9);
        } else if (*(s32 *)((u8 *) arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *) temp_v0 + 0x580) = temp_v1;
            *(u8 *)((u8 *) temp_v0 + 0x584) = *(u8 *)((u8 *) arg1 + 8);
        }
        temp_a2_2 = *(s32 *)((u8 *) temp_v0 + 0x588);
        if (*(s32 *)arg1 == temp_a2_2) {
            *(s32 *)((u8 *) temp_v0 + 0x588) = *(s32 *)((u8 *) arg1 + 4);
            *(u8 *)((u8 *) temp_v0 + 0x58C) = *(u8 *)((u8 *) arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *) arg1 + 4) == temp_a2_2) {
            *(s32 *)((u8 *) temp_v0 + 0x588) = *(s32 *)arg1;
            *(u8 *)((u8 *) temp_v0 + 0x58C) = *(u8 *)((u8 *) arg1 + 8);
        }
        return;
    }
    temp_v0_2 = arg0 + 0x28;
    if (arg2 == 0) {
        temp_v1_2 = *(s32 *)arg1;
        if ((temp_v1_2 == *(s32 *)((u8 *) temp_v0_2 + 0x580)) ||
            (temp_v1_2 == *(s32 *)((u8 *) temp_v0_2 + 0x588)) ||
            (temp_v1_3 = *(u8 *)((u8 *) arg1 + 4),
             *(u8 *)((u8 *) temp_v0_2 + 0x584) == temp_v1_3) ||
            (*(u8 *)((u8 *) temp_v0_2 + 0x58C) == temp_v1_3)) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5A9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5A9C.s")
