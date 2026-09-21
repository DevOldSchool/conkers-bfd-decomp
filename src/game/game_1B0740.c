#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B0740.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15183290
 * - func_151838B0
 * - func_15183974
 * - func_15183ACC
 * - func_15183BA4
 * - func_15183C28
 * - func_15183D28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183290.s")
typedef struct {
    void *field0;
    u8 pad4[8];
    s32 fieldC;
    u8 pad10[4];
} Game1B0740Slot;

extern Game1B0740Slot D_800DDE80[];
void func_15183ACC(s32); /* extern */
void *func_1502B6BC(s32, s32, s32, s32, s32, s32);
extern u8 D_800DDF69[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151838B0 CURRENT (525) */
void func_151838B0(s32 arg0) {
    u8 *temp_v1;
    void *temp_v0;

    temp_v1 = (u8 *)&D_800DDE80[arg0];
    if (*(void **)temp_v1 == 0) {
        func_15183ACC(arg0);
    }
    if (*(void **)(temp_v1 + 0x14) == 0) {
        temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAE);
        if (temp_v0 != 0) {
            *(void **)(temp_v1 + 0x14) = temp_v0;
            *(s32 *)(temp_v1 + 0x18) = *(s32 *)temp_v0;
            *(s32 *)(temp_v1 + 0x24) = 0;
            *(s32 *)(temp_v1 + 0x20) = *(s32 *)(temp_v1 + 0xC);
            *(s32 *)(temp_v1 + 0x1C) = *(s32 *)((u8 *)temp_v0 + 8);
            D_800DDF69[arg0] = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151838B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_151838B0.s")

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
extern u8 D_800DDF68[];
void func_151839F0(s32 arg0, s32 arg1) {
    Game1B0740Slot *second;

    second = &D_800DDE80[arg0];
    if (second->field0 == 0) {
        func_15183ACC(arg0);
    }
    if (second->field0 != 0) {
        second = &D_800DDE80[arg1];
        if (second->field0 == 0) {
            arg0 = (s32)func_1502B6BC(0, 0, 0, 2, 9, arg1 + 0xAD);
            if (arg0 != 0) {
                second->field0 = (void *)arg0;
                *(s32 *)((u8 *)second + 4) = *(s32 *)arg0;
                *(s32 *)((u8 *)second + 8) = *(s32 *)((u8 *)arg0 + 8);
                second->fieldC = *(s32 *)((u8 *)arg0 + 0x18);
                *(s32 *)((u8 *)second + 0x10) = 0;
                D_800DDF68[arg1] = 1;
            }
        }
    }
}
void func_1510CE60(s32, s32, s32, s32, void *);
extern s32 D_800DDF78[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15183ACC CURRENT (42) */
void func_15183ACC(s32 arg0) {
    register Game1B0740Slot *slot;
    u8 *allocated;
    s32 *handle_slot;

    slot = &D_800DDE80[arg0];
    if (slot->field0 == 0) {
        allocated = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAD);
        if (allocated != 0) {
            slot->field0 = allocated;
            *(s32 *)((u8 *)slot + 4) = *(s32 *)allocated;
            *(s32 *)((u8 *)slot + 8) = *(s32 *)(allocated + 8);
            slot->fieldC = *(s32 *)(allocated + 0x18);
            handle_slot = &D_800DDF78[arg0];
            *handle_slot = *(s32 *)(allocated + 0x10);
            func_1510CE60(*handle_slot, 0, 1, 0x3E, (u8 *)slot + 0x10);
            D_800DDF68[arg0] = 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15183ACC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183ACC.s")
extern u8 D_800A72D0[];

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
void func_1510D630(void *);
void func_10004074(s32);
extern s32 D_800DDF20;
extern s8 D_800DDF70;
extern s8 D_800DDF71;
extern s32 D_800DDF98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15183C28 CURRENT (183) */
void func_15183C28(s32 arg0) {
    register Game1B0740Slot *slot;
    register void *resource;

    slot = &D_800DDE80[arg0];
    resource = *(void **)((u8 *)slot + 0x10);
    if (resource != 0) {
        func_1510D630(resource);
        *(void **)((u8 *)slot + 0x10) = 0;
    }
    if (arg0 == 8) {
        if (D_800DDF71 != -2) {
            return;
        }
        goto free_slot;
    }
    if ((arg0 == 9) && (D_800DDF70 == -2)) {
        resource = (void *)D_800DDF20;
        if (resource != 0) {
            func_10004074((s32)resource);
            D_800DDF20 = 0;
            D_800DDF98 = 0;
        }
    }
free_slot:
    resource = slot->field0;
    if (resource != 0) {
        func_10004074((s32)resource);
        slot->field0 = 0;
        D_800DDF78[arg0] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15183C28 */
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
