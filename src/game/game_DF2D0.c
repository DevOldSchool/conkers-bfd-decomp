#include "types.h"

/*
 * Reviewed source unit: src/game/game_DF2D0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B1EE0
 * - func_150B1F90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40();

void func_150B1E20(void *arg0) {
    void *state;

    if (func_1509BE40(1, 0x4054, 6, 0x9000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x10000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= 0xFFFEFFFF;
    }
    if (func_1509BE40(1, 0x405C, 6, 0x9000) == 0 &&
        func_1509BE40(1, 0x405B, 6, 0x2000) != 0 &&
        *(s32 *)((u8 *)arg0 + 0x2C) != 0x40) {
        state = *(void **)((u8 *)arg0 + 0x3D0);
        *(f32 *)((u8 *)state + 0x17C) = *(f32 *)((u8 *)state + 0x180) + 10.0f;
    }
}
typedef struct GameDF2D0Packet {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    f32 field_C;
} GameDF2D0Packet;

extern void *func_10022EC0(void *arg0, const void *arg1, u32 arg2);
extern u32 func_150ADA20(void);
extern s32 func_15149130(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B1EE0 CURRENT (555) */
void func_150B1EE0(void *arg0, GameDF2D0Packet *arg1, s32 arg2, s32 arg3) {
    GameDF2D0Packet packet;
    s16 temp_a0;
    s32 temp_v0;

    packet.field_0 = arg1->field_0;
    packet.field_4 = arg1->field_4;
    packet.field_8 = arg1->field_8;
    packet.field_C = 0.0f;
    temp_a0 = (func_150ADA20() % 133U) + 0x45;
    temp_v0 = func_15149130(temp_a0, -1, 0x49, -1, 1, 0, 0x10,
        *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B1EE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DF2D0/func_150B1EE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DF2D0/func_150B1F90.s")
void func_150B2340(void *arg0) {
    s32 sp24;
    s32 sp20;
    s32 first;
    u8 *state;

    state = arg0;
    first = func_1509BE40(0, 0x2007, 0xB7);
    sp24 = func_1509BE40(0, first | 0x2000, 0xBC);
    sp20 = func_1509BE40(0, 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5043, 0x1A) != 0) {
        if (func_1509BE40(0, 0x5045, 0x1A) != 0) {
            *(s32 *)(state + 0x84) |= 0x4000;
        }
        *(s32 *)(state + 0x84) |= 0x400000;
        *(f32 *)(state + 0x190) = 0.0f;
    } else if (func_1509BE40(1, 0x4030, 6, 0x2000) != 0) {
        *(f32 *)(state + 0x190) = 235.0f;
    } else {
        *(f32 *)(state + 0x348) = 114.0f;
        *(f32 *)(state + 0x34C) = 114.0f;
        *(f32 *)(state + 0x374) = 384.0f;
        *(f32 *)(state + 0x190) = 60.0f;
    }
    if ((sp24 != 0) && (sp20 != -1)) {
        *(s32 *)(state + 0x5F0) |= 0x100;
    } else {
        *(s32 *)(state + 0x5F0) &= ~0x100;
    }
}
