#include "types.h"

/*
 * Reviewed source unit: src/game/game_1104D0.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E3020
 * - func_150E3208
 * - func_150E33CC
 * - func_150E3414
 * - func_150E35DC
 * - func_150E3738
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3020.s")
/* Call context: func_150AD9A0: unique active project prototype */
s32 func_150AD9A0(s32, s32, s32, s16);
void *func_150E3020(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E3208 CURRENT (100) */
s32 func_150E3208(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;

    temp_v0 = func_150E3020(arg0, arg1, arg2, arg3, arg4, arg5, arg6, (f32) func_150AD9A0(arg0 - arg3, arg1 - arg4, arg2 - arg5, (s16) arg3) / (f32) arg7, 0, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return *(u8 *)((u8 *)temp_v0 + 0x48) + 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E3208 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3208.s")
/* Call context: func_150E3020: unique active project prototype */
void * func_150E3020(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s32);

s32 func_150E32D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    void *temp_v0;

    temp_v0 = func_150E3020(arg0, arg1, arg2, 0, 0, 0, arg4, arg5, arg3, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return *(u8 *)((u8 *)temp_v0 + 0x48) + 1;
    }
    return 0;
}
/* Call context: func_150E3020: unique active project prototype */

void func_150E3340(void *arg0, void *arg1, s32 arg2, s16 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    temp_a0 = *(s32 *)((u8 *)arg1 + 0);
    temp_a1 = *(s32 *)((u8 *)arg1 + 4);
    temp_a2 = *(s32 *)((u8 *)arg1 + 8);
    func_150E3020(temp_a0, temp_a1, temp_a2, temp_a0, temp_a1, temp_a2, 0x1A, 10.0f, 0, *(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 4), *(f32 *)((u8 *)arg0 + 8), arg2, (s32) arg3);
}
void func_1000E7A0(s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E33CC CURRENT (170) */
s32 func_150E33CC(s32 arg0, s32 arg1, void **arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = *arg2;
    if (temp_v0 == 0) {
        return 1;
    }
    func_1000E7A0(2, temp_v0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E33CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E33CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3414.s")
typedef struct {
    u8 type;
    u8 pad1[0xF];
    f32 x;
    f32 y;
    f32 z;
} Game1104D0Slot;

extern Game1104D0Slot *D_800D99D0[8];

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void func_100111C8(u16);
void func_1516972C(u8 *);

void func_150E3514(u8 *arg0) {
    Game1104D0Slot **slot;
    u16 handle;
    u8 index;

    index = arg0[0x48];
    if ((s32) index >= 0) {
        slot = &D_800D99D0[index];
        if (arg0 == (u8 *) *slot) {
            *slot = 0;
        }
    }
    handle = *(u16 *) (arg0 + 0x4A);
    if (handle != 0) {
        func_100111C8(handle);
        *(u16 *) (arg0 + 0x4A) = 0;
        func_10010F88(0x2D7, 0x5DC0, 0, 0, 0,
                      (s32) *(f32 *) (arg0 + 0x28),
                      (s32) *(f32 *) (arg0 + 0x2C),
                      (s32) *(f32 *) (arg0 + 0x30),
                      0x3E8, 0x1770);
    }
    func_1516972C(arg0);
}
extern u8 D_800DCE50[];
extern s8 D_800DD190;
extern s32 D_800DD198;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E35DC CURRENT (1635) */
void func_150E35DC(s32 arg0) {
    s32 temp_s0;
    u8 *block;
    u8 *end;

    temp_s0 = arg0 - 1;
    block = D_800DCE50;
    end = (u8 *)&D_800DD190;
    do {
        u8 *node;
        u8 *volatile *link;

        node = *(u8 **)(block + 0x9C);
        D_800DD190 += 1;
        if (node != 0) {
            link = (u8 *volatile *)((u8 *)&D_800DD198 + (D_800DD190 * 4));
            do {
                *link = *(u8 **)(node + 8);
                if ((temp_s0 == -1) || (temp_s0 == node[0x48])) {
                    func_150E3514(node);
                    link = (u8 *volatile *)((u8 *)&D_800DD198 + (D_800DD190 * 4));
                }
                node = *link;
            } while (node != 0);
        }
        block += 0x1A0;
        D_800DD190 -= 1;
    } while (block != end);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E35DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E35DC.s")

void func_150E36BC(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    Game1104D0Slot *slot;

    arg0--;
    if ((arg0 >= 0) && (arg0 < 8)) {
        slot = D_800D99D0[arg0];
        if ((slot != 0) && (slot->type == 0x27)) {
            *arg1 = (s32) slot->x;
            *arg2 = (s32) slot->y;
            *arg3 = (s32) slot->z;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1104D0/func_150E3738.s")
