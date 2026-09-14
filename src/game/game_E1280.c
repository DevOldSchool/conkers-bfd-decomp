#include "types.h"

/*
 * Reviewed source unit: src/game/game_E1280.c
 * Boundary evidence: docs/evidence/game_raw_audio_owner_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B3DD0
 * - func_150B3F5C
 * - func_150B40E8
 * - func_150B4294
 * - func_150B4710
 * - func_150B5088
 * - func_150B538C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE1280State {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
} GameE1280State;

void func_1000FC18(s32, s16, s16, s16, s32);
void func_151478F4(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3DD0.s")

void func_150B3E74(GameE1280State *arg0) {
    func_1000FC18(0x221, (s16)(s32)arg0->x, (s16)(s32)arg0->y,
                  (s16)(s32)arg0->z, 0xFA0);
    func_151478F4((s32)arg0);
}
void func_15147928(s32);

void func_150B3EE8(GameE1280State *arg0) {
    func_1000FC18(0x221, (s16)(s32)arg0->x, (s16)(s32)arg0->y,
                  (s16)(s32)arg0->z, 0xFA0);
    func_15147928((s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B3F5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B40E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B4710.s")
void func_150B5060(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 0x1C) = (u8) (*(u8 *)((u8 *)temp_v0 + 0x1C) | 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B5088.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B538C CURRENT (295) */
void func_150B538C(void *arg0, s32 arg1, s32 arg2) {
    if ((arg2 & 0xFF) == 5) {
        func_150B5060(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B538C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E1280/func_150B538C.s")
