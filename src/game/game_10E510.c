#include "types.h"

/*
 * Reviewed source unit: src/game/game_10E510.c
 * Boundary evidence: docs/evidence/game_raw_timed_actor_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1060
 * - func_150E114C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10E510Object1060 {
    u8 pad0[0x10];
    s16 field_10;
    u8 pad12[2];
    s16 field_14;
} Game10E510Object1060;

typedef struct Game10E510Payload1060 {
    s8 index;
    u8 pad1[3];
    Game10E510Object1060 *object;
    s32 value;
    f32 zero;
} Game10E510Payload1060;

void *func_10022EC0(void *, const void *, u32);
Game10E510Object1060 *func_151149AC(u8);
void func_1510F800(s32);
s32 func_1510FD20(s16, s16);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800A0FE0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E1060 CURRENT (626) */
s32 func_150E1060(s32 arg0, u8 arg1, s32 arg2) {
    Game10E510Payload1060 payload;
    s32 result;
    s32 index;

    index = arg0 & 0xFF;
    if (index < 0) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }
    payload.index = index;
    payload.object = func_151149AC(D_800A0FE0[index]);
    if (payload.object == 0) {
        return 0;
    }
    func_1510F800(0);
    payload.value = func_1510FD20(payload.object->field_10, payload.object->field_14);
    payload.zero = 0.0f;
    result = func_15149130(0x12C, -1, 0x1F, -1, 0, 0x1F, 0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &payload, 0x10U);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E1060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10E510/func_150E1060.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10E510/func_150E114C.s")
