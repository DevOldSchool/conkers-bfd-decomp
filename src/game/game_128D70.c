#include "types.h"

/*
 * Reviewed source unit: src/game/game_128D70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FB8C0
 * - func_150FC368
 * - func_150FC438
 * - func_150FC614
 * - func_150FC818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FB8C0.s")
/* Call context: func_151C3B0C: unique active project prototype */
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FC368 CURRENT (335) */
void func_150FC368(void *arg0) {
    s32 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x1A0);
    if ((temp_v0 == 0) || (*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) == 0xFF) || (*(u8 *)((u8 *)arg0 + 0x1A4) != *(u8 *)((u8 *)temp_v0 + 0x3B)) || (temp_v1 = *(void **)((u8 *)temp_v0 + 0x31C), (temp_v1 == 0)) || (*(u8 *)((u8 *)temp_v1 + 0x84) != 0) || (*(u8 *)((u8 *)temp_v0 + 0x127) == 0xFF) || (temp_v1_2 = *(void **)((u8 *)temp_v0 + 0x318), (temp_v1_2 == 0))) {
        var_v0 = 0xFF;
    } else {
        var_v0 = ~(1 << *(u8 *)((u8 *)temp_v1_2 + 0x23D)) & 0xFF;
    }
    func_151C3B0C(arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFF, 0xFF, var_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FC368 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC368.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC614.s")
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FC818 CURRENT (1585) */
void func_150FC818(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 first;
    s32 second;
    s32 current;
    s32 alternate;
    u8 subtype;
    u8 *state;

    if (arg2 == 0) {
        state = arg0 + 0x28;
        first = *(s32 *)arg1;
        current = *(s32 *)state;
        if ((current == first) ||
            (subtype = arg1[4], subtype == state[4])) {
            func_1516972C(arg0);
            return;
        }
        alternate = *(s32 *)(state + 0x18);
        if ((alternate != 0) &&
            ((first == alternate) || (subtype == state[0x1C]))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        state = arg0 + 0x28;
        first = *(s32 *)arg1;
        current = *(s32 *)state;
        if (first == current) {
            *(s32 *)state = *(s32 *)(arg1 + 4);
            state[4] = arg1[9];
            return;
        }
        second = *(s32 *)(arg1 + 4);
        if (second == current) {
            *(s32 *)state = first;
            state[4] = arg1[8];
            return;
        }
        alternate = *(s32 *)(state + 0x18);
        if (alternate != 0) {
            if (first == alternate) {
                *(s32 *)(state + 0x18) = second;
                state[0x1C] = arg1[9];
                return;
            }
            if (second == alternate) {
                *(s32 *)(state + 0x18) = first;
                state[0x1C] = arg1[8];
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FC818 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC818.s")
