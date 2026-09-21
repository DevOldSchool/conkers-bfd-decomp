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

s32 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
void func_1510CE60(s32, s32, s32, s32, void *);
void func_15168E54(s32, s32 *);
extern u8 D_800DF7D0[];
extern s32 D_800DF9B8[];
extern s32 *D_800E0148[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C900 CURRENT (722) */
s32 func_1518C900(s32 arg0) {
    s32 offset;
    s32 *temp_v0;
    s32 *var_s0;
    u8 *temp_t0;
    u8 var_v0;
    u8 var_v1;

    temp_t0 = &D_800DF7D0[arg0];
    var_v0 = *temp_t0;
    var_v1 = var_v0;
    if (var_v0 == 0) {
        temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg0);
        var_s0 = temp_v0;
        if (temp_v0 == 0) {
            return 0;
        }
        offset = arg0 * 4;
        func_1510CE60(*var_s0, 0, 1, 0x3E, &D_800DF9B8[arg0]);
        func_15168E54(*var_s0, var_s0);
        *(s32 **)((u8 *) D_800E0148 + offset) = var_s0;
        var_v0 = *temp_t0;
        var_v1 = var_v0;
        goto block_5;
    }
    var_s0 = D_800E0148[arg0];
block_5:
    if (var_v1 != 0xFF) {
        *temp_t0 = var_v0 + 1;
    }
    return *var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9DB0/func_1518C900.s")
void func_1510D630(s32); /* extern */
void func_100043B4(s32, s32); /* extern */

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
