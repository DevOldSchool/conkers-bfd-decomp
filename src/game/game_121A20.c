#include "types.h"

/*
 * Reviewed source unit: src/game/game_121A20.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F4570
 * - func_150F48D0
 * - func_150F4A38
 * - func_150F4CFC
 * - func_150F4DEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game121A20NestedState {
    u8 pad0[0x24];
    u8 flags;
} Game121A20NestedState;

typedef struct Game121A20State {
    u8 pad0[0x71];
    u8 field71;
    u8 pad72[0xFE];
    Game121A20NestedState nested170;
} Game121A20State;

void func_1516972C(s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_10022EC0(s32, s32 *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4570.s")
/* Call context: func_1514373C: unique active project prototype */
void func_1514373C(f32, f32, f32 *, f32 *);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F48D0 CURRENT (970) */
void *func_150F48D0(u8 *arg0) {
    u8 *sp18;
    u8 *temp_v0;
    f32 sp1C;
    f32 sp20;

    temp_v0 = (void *)(arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x170) <= 0.0f) {
        return 0;
    }
    sp18 = temp_v0;
    func_1514373C(*(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0x20), &sp1C, &sp20);
    *(f32 *)((u8 *)sp18 + 0x10) = (f32) (*(f32 *)((u8 *)sp18 + 0x10) + (*(f32 *)((u8 *)sp18 + 0x14) * D_800BE9A4));
    *(f32 *)((u8 *)sp18 + 4) = (f32) (*(f32 *)((u8 *)sp18 + 4) + (*(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4));
    *(f32 *)((u8 *)sp18 + 8) = (f32) (*(f32 *)((u8 *)sp18 + 8) + (*(f32 *)((u8 *)arg0 + 0x48) * D_800BE9A4));
    *(f32 *)((u8 *)sp18 + 0xC) = (f32) (*(f32 *)((u8 *)sp18 + 0xC) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)sp18 + 4) + (sp1C * *(f32 *)((u8 *)sp18 + 0x18)));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)sp18 + 8) + sp20);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)sp18 + 0xC) - (sp1C * *(f32 *)((u8 *)sp18 + 0x1C)));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return sp18;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F48D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F48D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4A38.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4CFC CURRENT (520) */
void func_150F4CFC(Game121A20State *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4E) {
        arg0->field71 = 0;
        arg0->nested170.flags |= 5;
        return;
    }
    if (arg2 == 0x4F) {
        func_1516972C(arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4CFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4CFC.s")

void func_150F4D5C(s32 arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        s32 field_0;
        f32 field_4;
        s8 field_8;
        u8 field_9;
        u8 padA[2];
    } packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = 0.0f;
    packet.field_8 = arg1;
    packet.field_9 = arg2;
    temp_v0 = func_15149130(0x12C, -1, 0x56, -1, 0, 0, 0xC, (s32) arg3, arg4);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4DEC.s")
