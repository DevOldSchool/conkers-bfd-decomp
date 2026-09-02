#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BFC70.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151927C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BFC70State {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x20];
    s16 unk38;
    s8 unk3A;
    s8 unk3B;
} Game1BFC70State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151927C0 */
s32 func_151927C0(Game1BFC70State *arg0) {
    s32 value = arg0->unk14;
    s32 packed = (s16)((value & 0xFF) >> 1) * 0x10001;

    arg0->unk38 = 0x12C;
    arg0->unk3A = 0xA;
    arg0->unk14 = packed;
    arg0->unk3B = 0;
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151927C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFC70/func_151927C0.s")
