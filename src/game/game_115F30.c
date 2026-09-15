#include "types.h"

/*
 * Reviewed source unit: src/game/game_115F30.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E8A80
 * - func_150E8B1C
 * - func_150E8D5C
 * - func_150E90DC
 * - func_150E9178
 * - func_150E93DC
 * - func_150E971C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(s32, void *, s32);
u32 func_150ADA20(void);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A137C;
extern f32 D_800A1380;
extern f32 D_800A13B0;
extern f32 D_800A13B4;

typedef struct Game115F30Packet {
    f32 field_0;
    f32 field_4;
    f32 field_8;
} Game115F30Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E8A80 CURRENT (17) */
void func_150E8A80(void) {
    Game115F30Packet packet;
    s32 temp_v0;

    packet.field_0 = D_800A137C;
    packet.field_4 = D_800A1380;
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 41U) + 0x1E), -1, 0x33, -1, 1, 0, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E8A80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E8A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E8B1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E8D5C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E90DC CURRENT (17) */
void func_150E90DC(void) {
    Game115F30Packet packet;
    s32 temp_v0;

    packet.field_0 = D_800A13B0;
    packet.field_4 = D_800A13B4;
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130((s16) ((func_150ADA20() % 26U) + 5), -1, 0x36, -1, 1, 0, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E90DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E90DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E9178.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E93DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_115F30/func_150E971C.s")
