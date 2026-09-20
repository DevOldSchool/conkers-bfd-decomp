#include "types.h"

/*
 * Reviewed source unit: src/game/game_77BE0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1504A730
 * - func_1504ADD0
 * - func_1504AF10
 * - func_1504B0FC
 * - func_1504BA38
 * - func_1504BB88
 * - func_1504BC38
 * - func_1504BE2C
 * - func_1504C0E8
 * - func_1504C8BC
 * - func_1504C9E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504A730.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504ADD0.s")
s32 func_1504AEF4(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504AF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504B0FC.s")
extern s8 D_80099140[];
extern f32 D_800991D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504BA38 CURRENT (1435) */
void func_1504BA38(void *arg0) {
    s8 temp_a1;
    s8 temp_v0;
    s8 *entry;

    if (*(f32 *)((u8 *)arg0 + 0x28) > 10.0f) {
        *(s16 *)((u8 *)arg0 + 0xCE) = 0;
        return;
    }
    entry = D_80099140 + ((*(s32 *)((u8 *)arg0 + 0x184) & 0x1F) * 3);
    temp_a1 = entry[2];
    if ((temp_a1 != 0) && (*(u8 *)((u8 *)arg0 + 0xAA) == 0)) {
        *(u8 *)((u8 *)arg0 + 0xAA) = temp_a1;
    }
    temp_v0 = entry[1];
    if (temp_v0 == 0) {
        *(s16 *)((u8 *)arg0 + 0xCE) = entry[0];
        return;
    }
    *(s16 *)((u8 *)arg0 + 0xCE) = (s16)(s32)((f32)temp_v0 * D_800991D4 *
        ((f32)entry[0] - *(f32 *)((u8 *)arg0 + 0x3C)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504BA38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BA38.s")
void func_1506EBC0(void);
void func_1507490C(void);
extern u8 D_800CC2D0[];
extern s32 D_800D1580;

void func_1504BAF0(void *arg0) {
    s16 temp_v0;
    u8 temp_v0_2;
    u8 *temp_v1;

    temp_v0 = (s16)(*(u8 *)((u8 *)arg0 + 0x13C) - 0x64);
    if (temp_v0 >= 0) {
        temp_v1 = D_800CC2D0 + (temp_v0 * 0x32C);
        if ((*(u8 *)(temp_v1 + 0x13D) >= 0x64) &&
            ((temp_v0_2 = *(u8 *)(temp_v1 + 4), temp_v0_2 == 0xA8) || (temp_v0_2 == 0xA9))) {
            D_800D1580 = 3;
            func_1507490C();
        }
    }
    func_1506EBC0();
}
extern void func_1504BAF0(void *arg0);
extern void func_1505E650(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504BB88 CURRENT (255) */
void func_1504BB88(u8 *arg0) {
    s32 var_v0;

    var_v0 = *(s32 *)(arg0 + 0x25C);
    if (var_v0 & 0x10) {
        arg0[0x83] = 0xFF;
        arg0[0x89] = 0xFF;
        if (*(s32 *)arg0 == 1) {
            func_1505E650(arg0, 0xD6, 0x3F933333, 0x40400000, 0.0f, 0.0f, 0);
        }
        var_v0 = *(s32 *)(arg0 + 0x25C) & ~0x10;
        *(s32 *)(arg0 + 0x25C) = var_v0;
    }
    if (var_v0 & 2) {
        if (arg0[0x13C] != 0) {
            func_1504BAF0(arg0);
            var_v0 = *(s32 *)(arg0 + 0x25C);
        }
        *(s32 *)(arg0 + 0x25C) = var_v0 & ~2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504BB88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BB88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BC38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BE2C.s")
void func_1507F640(void);
extern void *D_800D154C;

s32 func_1504C078(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (*(u8 *)((u8 *)temp_v0 + 0x58) != 1) {
        *(s8 *)((u8 *)temp_v0 + 0x59) = 0;
        func_1507F640();
    }
    return 0x3E7;
}
extern s32 D_800BE9F0;

s32 func_1504C0B8(void) {
    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E)) {
        return 0x18B;
    }
    return 0x1B;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C0E8.s")
typedef struct {
    u8 pad_0[0x8A];
    s16 field_8A;
    u16 field_8C;
    s8 field_8E;
    s8 field_8F;
} Game77BE0TimerState;

typedef struct {
    u8 pad_0[0x31C];
    Game77BE0TimerState *field_31C;
} Game77BE0State;

extern u8 D_800BE9A0;
extern s32 D_800CC288;

void func_1504C854(Game77BE0State *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;
    Game77BE0TimerState *temp_v0;
    Game77BE0TimerState *temp_v0_2;

    D_800CC288 = arg0->field_31C->field_8C;
    temp_v0 = arg0->field_31C;
    temp_v1 = temp_v0->field_8E;
    if (temp_v1 > 0) {
        temp_v0->field_8E = temp_v1 - D_800BE9A0;
    } else {
        temp_v0->field_8A = 0;
    }
    temp_v0_2 = arg0->field_31C;
    temp_v1_2 = temp_v0_2->field_8F;
    if (temp_v1_2 > 0) {
        temp_v0_2->field_8F = temp_v1_2 - D_800BE9A0;
        return;
    }
    temp_v0_2->field_8C = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C8BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504C9E4 CURRENT (810) */
void func_1504C9E4(void *arg0, s8 arg1, s32 arg2) {
    s32 temp_t8;
    s32 var_a2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)arg0 + 0x1D1);
    temp_t8 = (temp_v1 - arg1) & 0xFF;
    if (temp_t8 != 0) {
        var_a2 = 3;
        if ((arg2 & 0xFF) == 0x10) {
            var_a2 = 6;
        }
        if (temp_t8 >= 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) = (s8) (temp_v1 + var_a2);
        } else {
            *(s8 *)((u8 *)arg0 + 0x1D1) = (s8) (temp_v1 - var_a2);
        }
        if ((temp_t8 ^ (*(s8 *)((u8 *)arg0 + 0x1D1) - arg1)) & 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) = arg1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504C9E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C9E4.s")
