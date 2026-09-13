#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B7EC0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518AA10
 * - func_1518AADC
 * - func_1518AB60
 * - func_1518ABD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518AA10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518AADC.s")
typedef struct Game1B7EC0Effect {
    u8 pad0[0x10];
    s32 field_10;
    s32 field_14;
    s32 field_18;
    u8 field_1C;
    u8 pad1D[3];
} Game1B7EC0Effect;

void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518AB60 CURRENT (265) */
void *func_1518AB60(s32 arg0, u8 arg1) {
    volatile Game1B7EC0Effect *effect;

    effect = func_15167A68(0x1E, 0, sizeof(Game1B7EC0Effect), 1, 0xFF, 1);
    if (effect == 0) {
        return 0;
    }
    effect->field_10 = arg0;
    effect->field_14 = 0;
    effect->field_18 = 0;
    effect->field_1C = arg1;
    return (void *)effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518AB60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518AB60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518ABD0.s")
