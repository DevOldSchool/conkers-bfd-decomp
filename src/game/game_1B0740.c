#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B0740.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15183290
 * - func_151838B0
 * - func_15183974
 * - func_151839F0
 * - func_15183ACC
 * - func_15183BA4
 * - func_15183C28
 * - func_15183D28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183290.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_151838B0.s")
typedef struct {
    void *field0;
    u8 pad4[8];
    s32 fieldC;
    u8 pad10[4];
} Game1B0740Slot;

extern Game1B0740Slot D_800DDE80[];
void func_15183ACC(s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15183974 CURRENT (16) */
void func_15183974(s32 arg0) {
    Game1B0740Slot *slot;

    slot = &D_800DDE80[arg0];
    if (slot->field0 == 0) {
        func_15183ACC(arg0);
    }
    if (slot[1].field0 == 0) {
        func_15183ACC(arg0 + 1);
        slot[1].fieldC = slot->fieldC;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15183974 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_151839F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183ACC.s")
extern u8 D_800A72D0[];
extern s32 D_800DDF78[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15183BA4 CURRENT (305) */
s32 *func_15183BA4(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *temp_v0;
    s32 *temp_v1;
    s32 *var_a0;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a2;

    var_a0 = arg0;
    var_v0 = -1;
    var_a2 = D_800A72D0;
    var_v1 = 0;
loop_1:
    if (arg1 == *var_a2) {
        var_v0 = var_v1;
    } else {
        var_v1 += 1;
        var_a2 += 1;
        if (var_v1 != 0xB) {
            goto loop_1;
        }
    }
    if (var_v0 != -1) {
        temp_v1 = &D_800DDF78[var_v0];
        temp_v0 = var_a0;
        if (*temp_v1 != 0) {
            temp_v0[0] = 0xDE000000;
            var_a0 += 2;
            temp_v0[1] = *temp_v1;
        }
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15183BA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183C28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183D28.s")
s32 func_15184118(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x57) != 0)) {
        return 1;
    }
    return 0;
}
