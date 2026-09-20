#include "types.h"

/*
 * Reviewed source unit: src/game/game_159940.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512C490
 * - func_1512D070
 * - func_1512D238
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

typedef struct Game159940Resource Game159940Resource;

extern s32 D_800BE9E4;
extern Game159940Resource *D_800DC280[];
extern u32 D_800DC290[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512C490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D070.s")
Game159940Resource *func_1502B5C8(u32 *arg0, s32 arg1, s32 arg2, s32 arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D238 CURRENT (240) */
void func_1512D238(void) {
    Game159940Resource **var_s1;
    u32 *var_s2;
    u32 sp3C;
    Game159940Resource *temp_v0;
    s32 var_s0;

    var_s1 = D_800DC280;
    var_s2 = D_800DC290;
    var_s0 = 0;
    do {
        temp_v0 = func_1502B5C8(&sp3C, 2, 0x1B, var_s0);
        var_s0 += 1;
        var_s1 += 1;
        var_s2 += 1;
        var_s1[-1] = temp_v0;
        var_s2[-1] = sp3C / 24U;
    } while (var_s0 != 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D238 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D238.s")
void func_1512D2E4(Game159940Object *arg0, s32 arg1) {
    arg0->field_850 = arg1;
    arg0->field_84D = 1;
}
void func_1512D2F8(Game159940Object *arg0) {
    u8 state;
    u8 value;

    state = arg0->field_84D;
    switch (state) {
    case 1:
        arg0->field_84E = 0;
        arg0->field_84D = 2;
        return;
    case 2:
        value = arg0->field_84E + D_800BE9E4;
        arg0->field_84E = value;
        if ((value & 0xFF) >= (s32)D_800DC290[arg0->field_850]) {
            arg0->field_84D = 0;
        }
        return;
    }
}
void func_1512D368(s32 arg0) {

}
