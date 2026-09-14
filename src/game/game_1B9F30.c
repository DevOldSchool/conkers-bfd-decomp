#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B9F30.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518CA80
 * - func_1518CCA8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9F30/func_1518CA80.s")
typedef struct Game1B9F30State {
    u8 pad0[0x14];
    s32 packed_delta;
    u8 pad18[0x1C];
    s16 field_34;
    s16 field_36;
    s16 field_38;
    u8 pad3A;
    u8 callback_flags;
} Game1B9F30State;

extern void (*D_8008D5D0[])(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518CCA8 CURRENT (460) */
void func_1518CCA8(Game1B9F30State *arg0) {
    s32 packed_delta;
    s32 callback_index;

    packed_delta = arg0->packed_delta;
    arg0->field_34 += (u32)(packed_delta & 0xFFFF0000) >> 16;
    arg0->field_36 += packed_delta;
    if (arg0->field_38 == 0) {
        callback_index = arg0->callback_flags & 0xF;
        if (callback_index != 0) {
            D_8008D5D0[callback_index]();
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518CCA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9F30/func_1518CCA8.s")
