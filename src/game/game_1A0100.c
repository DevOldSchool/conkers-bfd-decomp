#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0100.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15172C50
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_800DD2B0[16];
extern u8 D_800DD2C0[16];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15172C50 CURRENT (10) */
void func_15172C50(s32 arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_800DD2B0[i] = -1;
        D_800DD2C0[i] = 0;
    }
    D_800DD2C0[0] = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15172C50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0100/func_15172C50.s")

void func_1517EE40(s32, s32, s32, s32, s32, s32);

void func_15172CA8(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = &D_800DD2B0[arg0];
    if (*temp_v0 != -1) {
        *temp_v0 = -1;
        func_1517EE40(0, 0, 0, 0, 1, arg0);
        func_1517EE40(0, 0, 0, 0x32, 0, arg0);
    }
}
void func_15085430(void *, s32, s32);
extern u8 D_800BE9B4;

void func_15172D28(void *arg0, s32 arg1) {
    void *temp_v0;

    func_15085430(arg0, arg1, 1);
    *(u16 *)((u8 *)arg0 + 0x2F8) &= 0xFFEF;
    if (D_800BE9B4 == 0) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
        if (temp_v0 != 0) {
            *(s8 *)((u8 *)temp_v0 + 0x56) = 3;
        }
    }
}
void func_1501C730(s32, s32, s32, s32, s32);
s32 func_1517F40C(s32);
extern s32 D_800BE9F0;
typedef struct Game1A0100Attachment {
    u8 pad0[0x23];
    s8 state;
} Game1A0100Attachment;

typedef struct Game1A0100Actor {
    u8 pad0[0x127];
    u8 slot;
    u8 pad128[0xA2];
    u8 active;
    u8 pad1CB[0x12D];
    u16 flags;
    u8 pad2FA[0x1E];
    void *field318;
    Game1A0100Attachment *attachment;
    u8 pad320[0xC];
} Game1A0100Actor;

extern Game1A0100Actor D_800CC2D0[];

void func_15172D80(s32 arg0) {
    if (D_800DD2B0[arg0] != -1) {
        if (D_800CC2D0[arg0].active == 0) {
            D_800DD2B0[arg0] = -1;
            func_1517EE40(0, 0, 0, 0x32, 0, arg0);
        }
        if (func_1517F40C(arg0) != 0) {
            if (D_800BE9F0 != D_800DD2B0[arg0]) {
                func_1501C730(1, D_800DD2B0[arg0], 0, 0, 0);
                return;
            }
            func_15172CA8(arg0);
            func_15172D28(&D_800CC2D0[arg0], D_800DD2C0[arg0]);
        }
    }
}
void func_15172E7C(Game1A0100Actor *arg0, s32 arg1, s32 arg2) {
    s32 slot;

    slot = arg0->slot;
    if (arg0->active != 0 &&
        (arg0->attachment == 0 || arg0->attachment->state <= 0)) {
        if (arg0->field318 != 0) {
            if (D_800DD2B0[slot] == -1) {
                func_1517EE40(0, 0, 0, 0xA, 1, slot);
                arg0->flags |= 0x10;
                D_800DD2B0[slot] = arg1;
                D_800DD2C0[slot] = arg2;
            }
        } else if (arg1 == D_800BE9F0) {
            func_15172D28(arg0, arg2);
        }
    }
}
