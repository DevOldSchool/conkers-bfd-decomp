#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FEA80.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D15D0
 * - func_151D197C
 * - func_151D1C98
 * - func_151D2258
 * - func_151D2284
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D15D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D197C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D1C98.s")
typedef struct Game1FEA80Leaf {
    u8 pad0[0x30];
    s32 field_30;
} Game1FEA80Leaf;

typedef struct Game1FEA80Object {
    u8 pad0[0x98];
    Game1FEA80Leaf **field_98;
} Game1FEA80Object;

void func_151D223C(Game1FEA80Object *arg0) {
    register Game1FEA80Leaf **link = arg0->field_98;
    register Game1FEA80Leaf *leaf = *link;

    if (leaf) {
        leaf->field_30 = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D2258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FEA80/func_151D2284.s")
