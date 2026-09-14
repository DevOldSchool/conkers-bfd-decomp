#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D4140.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6C90
 * - func_151A6F00
 * - func_151A743C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A6C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A6F00.s")
typedef struct {
    s32 field_0;
    s32 field_4;
} Game1D4140Entry;

typedef struct {
    u8 pad_0[0x64];
    s16 field_64;
    u8 pad_66[0x10A];
    Game1D4140Entry field_170;
} Game1D4140State;

void func_1516972C(s32, void *);

s32 func_151A73EC(Game1D4140State *arg0) {
    Game1D4140Entry *temp_v0;

    temp_v0 = &arg0->field_170;
    if (arg0->field_64 < 0x20) {
        if (temp_v0->field_4 != 0) {
            func_1516972C(temp_v0->field_4, arg0);
            temp_v0->field_4 = 0;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4140/func_151A743C.s")
