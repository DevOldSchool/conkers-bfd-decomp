#include "types.h"

/*
 * Reviewed source unit: src/game/game_159940.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512C490
 * - func_1512D070
 * - func_1512D238
 * - func_1512D2F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game159940Object {
    u8 pad0[0x84D];
    u8 field_84D;
    u8 pad84E[2];
    s32 field_850;
} Game159940Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512C490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D238.s")
void func_1512D2E4(Game159940Object *arg0, s32 arg1) {
    arg0->field_850 = arg1;
    arg0->field_84D = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D2F8.s")
void func_1512D368(s32 arg0) {

}
