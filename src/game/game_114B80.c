#include "types.h"

/*
 * Reviewed source unit: src/game/game_114B80.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E76D0
 * - func_150E7994
 * - func_150E7C9C
 * - func_150E7FEC
 * - func_150E81A8
 * - func_150E83AC
 * - func_150E8470
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E76D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7994.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7C9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E81A8.s")
void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E83AC CURRENT (2259) */
void func_150E83AC(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 first;
        s32 second;
        s32 third;
        f32 value;
    } packet;
    s32 var_v1;
    s32 var_v0;
    u8 *temp_v0;

    packet.first = *(s32 *)arg0;
    packet.second = *(s32 *)((u8 *)arg0 + 4);
    var_v1 = arg1;
    packet.third = *(s32 *)((u8 *)arg0 + 8);
    packet.value = 0.0f;
    if (arg1 == -1) {
        var_v1 = 0x12C;
    }
    if (arg1 == -1) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    temp_v0 = func_15149130((s32)var_v1, -1, 0x28, -1, var_v0, 0, 0x10,
        (s32)arg2, arg3);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E83AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E83AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E8470.s")
void func_15131828(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_150E8824(s32 arg0, s32 arg1) {
    func_15131828(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150E8854(void) {
    u8 *object;
    f32 value;

    value = 10.0f;
    object = func_15149130(0x12C, -1, 0x35, -1, 0, 0, 4, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &value, 4);
    }
}
