#include "types.h"

/*
 * Reviewed source unit: src/game/game_C98F0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509C440
 * - func_1509C7C8
 * - func_1509C8FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_1501D348: unique active project prototype */
/* Call context: func_15022190: unique active declaration in the allowed source */
/* Call context: func_150221E8: unique active declaration in the allowed source */
void func_1501D348(s32, s32, s32, u8, s32);
void func_15022190(s16, s16, s16, f32);
void func_150221E8(s16, s16, s16, f32);
extern s32 D_800BE9F0;
extern s8 D_800C35C2;
extern s8 D_800C35C3;
extern s8 D_800C3C99;
extern s8 D_800C3C9C;
extern s32 D_800D3840;
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509C440 CURRENT (5339) */
void func_1509C440(s32 arg0, s32 arg1, void *arg2) {
    s32 sp3C;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 temp_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;

    switch (arg1) {
    case 1:
        if (D_800C35EA == 0) {
            sp3C = D_800BE9F0;
            if (D_800D3840 == 6) {
                func_15022190(*(s16 *)((u8 *)arg2 + 0xA), *(s16 *)((u8 *)arg2 + 0xE), *(s16 *)((u8 *)arg2 + 0x12), (f32) *(s32 *)((u8 *)arg2 + 0x14) * 0.000015258789f);
            } else if (D_800D3840 == 3) {
                temp_a0 = *(s32 *)((u8 *)arg2 + 8);
                if ((temp_a0 & 0xF000) == 0x2000) {
                    func_1509C8FC(temp_a0, 0);
                } else {
                    sp3C = temp_a0;
                }
            }
            func_1501D348(sp3C, arg0, 0, 0U, 0);
            return;
        }
        return;
    case 4:
        if (D_800C35EA == 0) {
            if (D_800D3840 == 6) {
                func_15022190(*(s16 *)((u8 *)arg2 + 0xA), *(s16 *)((u8 *)arg2 + 0xE), *(s16 *)((u8 *)arg2 + 0x12), (f32) *(s32 *)((u8 *)arg2 + 0x14) * 0.000015258789f);
            }
            temp_s0 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            func_1501D348(0x25, arg0, 0, 0U, 0);
            D_800BE9F0 = temp_s0;
            return;
        }
        return;
    case 3:
        if (D_800C35EA == 0) {
            sp30 = *(s32 *)((u8 *)arg2 + 8);
            temp_v1 = *(s32 *)((u8 *)arg2 + 0xC);
            sp34 = D_800BE9F0;
            if (D_800D3840 == 8) {
                sp2C = temp_v1;
                func_15022190(*(s16 *)((u8 *)arg2 + 0x12), *(s16 *)((u8 *)arg2 + 0x16), *(s16 *)((u8 *)arg2 + 0x1A), (f32) *(s32 *)((u8 *)arg2 + 0x1C) * 0.000015258789f);
            } else if (D_800D3840 == 5) {
                sp34 = *(s32 *)((u8 *)arg2 + 0x10);
            }
            func_1501D348(sp34, arg0, 0, (u8) sp30, temp_v1);
            return;
        }
        return;
    case 2:
        D_800C35C2 = arg0 + 1;
        D_800C35C3 = (s8) D_800BE9F0;
        D_800C3C99 = 1;
        if (D_800D3840 == 6) {
            func_150221E8(*(s16 *)((u8 *)arg2 + 0xA), *(s16 *)((u8 *)arg2 + 0xE), *(s16 *)((u8 *)arg2 + 0x12), (f32) *(s32 *)((u8 *)arg2 + 0x14) * 0.000015258789f);
            return;
        }
        if (D_800D3840 == 3) {
            temp_a0_2 = *(s32 *)((u8 *)arg2 + 8);
            if ((temp_a0_2 & 0xF000) == 0x2000) {
                func_1509C8FC(temp_a0_2, 1);
                return;
            }
            D_800C35C3 = (s8) temp_a0_2;
            return;
        }
    default:
        return;
    case 5:
        D_800C35C2 = arg0 + 1;
        D_800C35C3 = 0x25;
        if (D_800D3840 == 6) {
            func_150221E8(*(s16 *)((u8 *)arg2 + 0xA), *(s16 *)((u8 *)arg2 + 0xE), *(s16 *)((u8 *)arg2 + 0x12), (f32) *(s32 *)((u8 *)arg2 + 0x14) * 0.000015258789f);
            return;
        }
        break;
    case 6:
        D_800C3C9C = 1;
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509C440 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C98F0/func_1509C440.s")
extern u8 D_800C35C4;
extern u8 D_800C35E8;
extern u8 D_800C35EA;
extern u8 D_800C3C98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509C7C8 CURRENT (5950) */
void func_1509C7C8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        if (D_800C35C4 != 0) {
            return;
        }
        if (D_800C35EA == 0) {
            return;
        }
        if (arg0 == D_800C3C98) {
            return;
        }
        return;
    case 2:
        if ((D_800C35EA == 1) && (arg0 == D_800C3C98)) {
            return;
        }
        return;
    case 3:
        if ((D_800C35EA == 1) && (arg0 == D_800C35E8)) {
            return;
        }
        return;
        return;
        return;
    case 6:
        if ((D_800C35EA == 1) && (arg0 == D_800C35E8)) {
            return;
        }
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509C7C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C98F0/func_1509C7C8.s")
/* Call context: func_15022190: unique active project prototype */
/* Call context: func_150221E8: unique active project prototype */
void func_15022190(s16, s16, s16, f32);
void func_150221E8(s16, s16, s16, f32);
void *func_1505EEF4(s32, s32);                      /* extern */
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509C8FC CURRENT (331) */
void func_1509C8FC(s32 arg0, s32 arg1) {
    f32 var_fv0;
    void *temp_v0;

    temp_v0 = func_1505EEF4(arg0 & 0xFFF, arg0);
    if (temp_v0 != 0) {
        if (*(s32 *)((u8 *)D_800DBFF0 + 0x2C) & 0x100) {
            var_fv0 = *(f32 *)((u8 *)D_800DBFF0 + 0x760);
        } else {
            var_fv0 = *(f32 *)((u8 *)D_800DBFF0 + 0x37C);
        }
        if (arg1 != 0) {
            func_150221E8((s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x14), (s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x18), (s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x1C), var_fv0 + 180.0f);
            return;
        }
        func_15022190((s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x14), (s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x18), (s16) (s32) *(f32 *)((u8 *)temp_v0 + 0x1C), var_fv0 + 180.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509C8FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C98F0/func_1509C8FC.s")
