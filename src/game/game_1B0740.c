#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B0740.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15183290
 * - func_15183D28
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183290.s")
typedef struct {
    void *field0;
    u8 pad4[8];
    s32 fieldC;
    void *field10;
} Game1B0740Slot;

extern Game1B0740Slot D_800DDE80[];
void func_15183ACC(s32); /* extern */
void *func_1502B6BC(s32, s32, s32, s32, s32, s32);
extern u8 D_800DDF69[];

/* Keep slot reads inline: a named pointer local changes IDO stack layout. */
void func_151838B0(s32 arg0) {
    void *temp_v0;

    if (*(void **)((u8 *)&D_800DDE80[arg0]) == 0) {
        func_15183ACC(arg0);
    }
    if (*(void **)(((u8 *)&D_800DDE80[arg0]) + 0x14) == 0) {
        temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAE);
        if (temp_v0 != 0) {
            *(void **)(((u8 *)&D_800DDE80[arg0]) + 0x14) = temp_v0;
            *(s32 *)(((u8 *)&D_800DDE80[arg0]) + 0x18) = *(s32 *)temp_v0;
            *(s32 *)(((u8 *)&D_800DDE80[arg0]) + 0x1C) = *(s32 *)((u8 *)temp_v0 + 8);
            *(s32 *)(((u8 *)&D_800DDE80[arg0]) + 0x24) = 0;
            *(s32 *)(((u8 *)&D_800DDE80[arg0]) + 0x20) = *(s32 *)(((u8 *)&D_800DDE80[arg0]) + 0xC);
            D_800DDF69[arg0] = 1;
        }
    }
}

void func_15183974(s32 arg0) {
    if (D_800DDE80[arg0].field0 == 0) {
        func_15183ACC(arg0);
    }
    if ((&D_800DDE80[arg0])[1].field0 == 0) {
        func_15183ACC(arg0 + 1);
        (&D_800DDE80[arg0])[1].fieldC = D_800DDE80[arg0].fieldC;
    }
}
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

void func_15183ACC(s32 arg0) {
    u8 *allocated;

    if (D_800DDE80[arg0].field0 == 0) {
        allocated = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAD);
        if (allocated != 0) {
            D_800DDE80[arg0].field0 = allocated;
            *(s32 *)((u8 *)(&D_800DDE80[arg0]) + 4) = *(s32 *)allocated;
            *(s32 *)((u8 *)(&D_800DDE80[arg0]) + 8) = *(s32 *)(allocated + 8);
            D_800DDE80[arg0].fieldC = *(s32 *)(allocated + 0x18);
            D_800DDF78[arg0] = *(s32 *)(allocated + 0x10);
            func_1510CE60(D_800DDF78[arg0], 0, 1, 0x3E, (u8 *)(&D_800DDE80[arg0]) + 0x10);
            D_800DDF68[arg0] = 1;
        }
    }
}
extern u8 D_800A72D0[];

typedef struct Game1B0740Command {
    u32 w0;
    u32 w1;
} Game1B0740Command;

Game1B0740Command *func_15183BA4(Game1B0740Command *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 index = -1;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (arg1 == D_800A72D0[i]) {
            index = i;
            break;
        }
    }
    if (index != -1 && D_800DDF78[index] != 0) {
        { Game1B0740Command *command = arg0++; command->w0 = 0xDE000000; command->w1 = D_800DDF78[index]; }
    }
    return arg0;
}
void func_10004074(s32);
extern void *D_800DDF20;
extern s8 D_800DDF70;
extern s8 D_800DDF71;
extern s32 D_800DDF98;

void func_15183C28(s32 arg0) {
    if (D_800DDE80[arg0].field10 != 0) {
        func_1510D630(D_800DDE80[arg0].field10);
        D_800DDE80[arg0].field10 = 0;
    }
    if (arg0 == 8) {
        if (D_800DDF71 != -2) {
            return;
        }
        goto free_slot;
    }
    if ((arg0 == 9) && (D_800DDF70 == -2)) {
        if (D_800DDF20 != 0) {
            func_10004074((s32)D_800DDF20);
            D_800DDF20 = 0;
            D_800DDF98 = 0;
        }
    }
free_slot:
    if (D_800DDE80[arg0].field0 != 0) {
        func_10004074((s32)D_800DDE80[arg0].field0);
        D_800DDE80[arg0].field0 = 0;
        D_800DDF78[arg0] = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B0740/func_15183D28.s")
s32 func_15184118(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x57) != 0)) {
        return 1;
    }
    return 0;
}
