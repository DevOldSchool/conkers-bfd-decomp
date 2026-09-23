#include "types.h"

/*
 * Reviewed source unit: src/game/game_C3E20.c
 * Boundary evidence: docs/evidence/game_raw_record_command_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150969A0
 * - func_15096A68
 * - func_15096D78
 * - func_1509759C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2DC0;
extern s32 D_800D2DB4;

void func_15096970(void) {
    func_100226F0(&D_800D2DC0, 0x6C);
    D_800D2DB4 = 0;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150969A0 CURRENT (345) */
s32 func_150969A0(s32 arg0) {
    s32 temp_a2;
    s32 var_v0;
    u8 *var_v1;
    u8 *var_v1_2;

    var_v0 = 0;
    if (arg0 > 0) {
        temp_a2 = arg0 & 3;
        if (temp_a2 != 0) {
            var_v1 = (void *)((0 << 5) + &D_800D2DC0);
loop_3:
            var_v0 += 1;
            if (*var_v1 != 0) {
                return 1;
            }
            var_v1 += 0x24;
            if (temp_a2 == var_v0) {
                if (var_v0 != arg0) {
                    goto block_7;
                }
                /* Duplicate return node #17. Try simplifying control flow for better match */
                return 0;
            }
            goto loop_3;
        }
block_7:
        var_v1_2 = (void *)((var_v0 * 0x24) + &D_800D2DC0);
loop_8:
        var_v0 += 4;
        if (*(u8 *)((u8 *)var_v1_2 + 0) != 0) {
            return 1;
        }
        if (*(u8 *)((u8 *)var_v1_2 + 0x24) != 0) {
            return 1;
        }
        if (*(u8 *)((u8 *)var_v1_2 + 0x48) != 0) {
            return 1;
        }
        if (*(u8 *)((u8 *)var_v1_2 + 0x6C) != 0) {
            return 1;
        }
        var_v1_2 += 0x90;
        if (var_v0 == arg0) {
            /* Duplicate return node #17. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_8;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150969A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_150969A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096A68.s")
s32 func_15096A68(s32);                             /* extern */
extern u8 D_800C35EA;
extern u8 D_800D2DC0;

void func_15096D08(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = &D_800D2DC0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096A68(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096D78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_1509759C.s")
typedef struct GameC3E20View {
    u8 pad0[0x2A4];
    f32 firstX;
    f32 firstY;
    f32 firstZ;
    u8 pad2B0[0x48];
    f32 secondX;
    f32 secondY;
    f32 secondZ;
} GameC3E20View;

void func_15048F90(void *, void *, void *);
void func_1504917C(void *, void *);
extern u8 *D_800DBFF0;
extern s32 D_800D2E30[];

void func_15097798(s32 arg0) {
    GameC3E20View *view;
    f32 direction[5];

    view = (GameC3E20View *)(D_800DBFF0 + arg0 * 0x9A0);
    if (D_800D2DB4 != 0) {
        func_15048F90(&view->firstX, &view->secondX, direction + 2);
        func_1504917C(direction + 2, direction + 2);
        view->firstX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->firstY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->firstZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->secondZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
    }
}
