#include "types.h"

/*
 * Reviewed source unit: src/game/game_122B60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F56B0
 * - func_150F5A54
 * - func_150F5C08
 * - func_150F5C98
 * - func_150F6178
 * - func_150F631C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F631C(s32 arg0);
void func_1516972C(void *arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);
void func_10022EC0(s32, void **, s32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F56B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5A54.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F5C08 CURRENT (100) */
void func_150F5C08(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *field_0;
        u8 field_4;
        u8 pad5[3];
        f32 field_8;
    } packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, 0xC, (s32) arg2, arg3);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, (void **)&packet, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F5C08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5C08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5C98.s")
extern void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F6178.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F631C CURRENT (505) */
void func_150F631C(s32 arg0) {
    s32 temp_a1;
    void *temp_a0;

    temp_a1 = arg0;
    if (*(void **)((u8 *)temp_a1 + 0x30) != 0) {
        func_1516972C(*(void **)((u8 *)temp_a1 + 0x30));
    }
    temp_a0 = *(void **)((u8 *)temp_a1 + 0x34);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F631C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F631C.s")
void func_150F6368(s32 arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}
void func_150F6394(s32 arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}
