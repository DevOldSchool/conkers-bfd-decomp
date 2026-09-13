#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B9DB0.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518C900
 * - func_1518CA04
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9DB0/func_1518C900.s")
void func_1510D630(s32); /* extern */
void func_100043B4(s32, s32); /* extern */
extern u8 D_800DF7D0;
extern s32 D_800DF9B8;
extern s32 D_800E0148;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518CA04 CURRENT (40) */
void func_1518CA04(s32 arg0) {
    s32 savedOffset;
    s32 offset;
    u8 *counter;
    u8 newValue;
    u8 value;

    if (arg0 != 0x1E4) {
        counter = arg0 + &D_800DF7D0;
        value = *counter;
        newValue = value - 1;
        if (value != 0) {
            *counter = newValue;
            if (!(newValue & 0xFF)) {
                offset = arg0 * 4;
                savedOffset = offset;
                func_1510D630(*(s32 *)((u8 *)&D_800DF9B8 + offset));
                func_100043B4(*(s32 *)((u8 *)&D_800E0148 + offset), 4);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518CA04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9DB0/func_1518CA04.s")
