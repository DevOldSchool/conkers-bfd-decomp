#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DF510.c
 * Boundary evidence: docs/evidence/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B2060
 * - func_151B2100
 * - func_151B222C
 * - func_151B229C
 * - func_151B22F4
 * - func_151B2348
 * - func_151B2690
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2060.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2100.s")
void func_151B220C() {
    func_151B222C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B222C.s")
void func_1514933C(s32);
void func_15149368(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B229C CURRENT (200) */
void func_151B229C(s32 arg0) {
    func_151B220C();
    func_1514933C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B229C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B229C.s")
void func_151B22C8(s32 arg0) {
    func_151B220C(arg0);
    func_15149368(arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    s32 field_5C;
    u8 pad_60[5];
    u8 field_65;
} Game1DF510Entry;

typedef struct {
    u8 pad_0[0x28];
    u8 *field_28;
    u8 pad_2C[4];
    Game1DF510Entry *field_30;
} Game1DF510State;

extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B22F4 CURRENT (780) */
s32 func_151B22F4(Game1DF510State *arg0) {
    Game1DF510Entry *temp_v1;

    temp_v1 = arg0->field_30;
    if (((((arg0->field_28 - &D_800CC2D0) / 0x32C) + 1) == temp_v1->field_65) && (temp_v1->field_5C == 1)) {
        return 1;
    }
    return 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B22F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B22F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DF510/func_151B2690.s")
