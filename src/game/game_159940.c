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
    u8 field_84E;
    u8 pad84F;
    s32 field_850;
} Game159940Object;

extern s32 D_800BE9E4;
extern s32 D_800DC290[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512C490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D238.s")
void func_1512D2E4(Game159940Object *arg0, s32 arg1) {
    arg0->field_850 = arg1;
    arg0->field_84D = 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D2F8 CURRENT (175) */
void func_1512D2F8(Game159940Object *arg0) {
    u8 state;
    s32 value;

    state = arg0->field_84D;
    switch (state) {
    case 1:
        arg0->field_84E = 0;
        arg0->field_84D = 2;
        return;
    case 2:
        value = arg0->field_84E + D_800BE9E4;
        arg0->field_84E = value;
        if ((value & 0xFF) >= D_800DC290[arg0->field_850]) {
            arg0->field_84D = 0;
        }
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D2F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D2F8.s")
void func_1512D368(s32 arg0) {

}
