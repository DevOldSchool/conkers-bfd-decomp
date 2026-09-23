#include "types.h"

/*
 * Reviewed source unit: src/game/game_193430.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15166118
 * - func_15166268
 * - func_151668B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1517E05C(s32, s32, s32);
extern f32 D_800A6C94;

void func_15165F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    u8 *cursor;
    u8 *effect;
    f32 angle;
    s32 i;
    s32 j;

    effect = func_15167A68(4, arg8, 0xA8, 1, arg7, 1);
    if (effect == 0) {
        return;
    }
    if (arg0 == -1) {
        i = 0;
        cursor = effect;
        do {
            i += 0x40;
            cursor += 0x40;
            *(s16 *)(cursor - 0x2E) = arg2;
            *(s16 *)(cursor - 0x1E) = arg2;
            *(s16 *)(cursor - 0xE) = arg2;
            *(s16 *)(cursor + 2) = arg2;
            *(s16 *)(cursor - 0x2A) = 0;
            *(s16 *)(cursor - 0x1A) = 0;
            *(s16 *)(cursor - 0xA) = 0;
            *(s16 *)(cursor + 6) = 0;
        } while (i != 0x80);
        effect[0x95] = 0;
    } else {
        angle = (f32)arg0 * D_800A6C94;
        effect[0x91] = (s32)(func_15047D60(angle) * 127.0f);
        effect[0x90] = (s32)(-func_15047C00(angle) * 127.0f);
        effect[0x95] = 1;
    }
    j = 0;
    {
    u8 *cursor2 = effect;
    do {
        j++;
        cursor2 += 0x40;
        *(s16 *)(cursor2 - 0x28) = 0x2000;
        *(s16 *)(cursor2 - 0x26) = 0x2000;
        *(s16 *)(cursor2 - 0x18) = 0x2800;
        *(s16 *)(cursor2 - 0x16) = 0x2000;
        *(s16 *)(cursor2 - 8) = 0x2800;
        *(s16 *)(cursor2 - 6) = 0x2800;
        *(s16 *)(cursor2 + 8) = 0x2000;
        *(s16 *)(cursor2 + 0xA) = 0x2800;
    } while (j != 2);
    *(s16 *)(effect + 0x9A) = arg2;
    *(s16 *)(effect + 0x9E) = 1;
    effect[0x92] = arg5;
    effect[0x93] = arg5;
    *(s16 *)(effect + 0x98) = arg1;
    *(s16 *)(effect + 0x9C) = arg3;
    *(s16 *)(effect + 0x96) = arg4;
    effect[0x94] = arg6;
    func_1517E05C(arg1, arg2, arg3);
    }
}
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1517E05C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166118 CURRENT (200) */
void func_15166118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 i;
    u8 *effect;
    u8 *cursor;

    effect = func_15167A68(4, arg9, 0xA8, 1, arg8, 1);
    if (effect != 0) {
        effect[0x95] = 2;
        i = 0;
        cursor = effect;
        do {
            i++;
            cursor += 0x40;
            *(s16 *)(cursor - 0x28) = 0x2000;
            *(s16 *)(cursor - 0x26) = 0x2000;
            *(s16 *)(cursor - 0x18) = 0x2800;
            *(s16 *)(cursor - 0x16) = 0x2000;
            *(s16 *)(cursor - 8) = 0x2800;
            *(s16 *)(cursor - 6) = 0x2800;
            *(s16 *)(cursor + 8) = 0x2000;
            *(s16 *)(cursor + 0xA) = 0x2800;
        } while (i != 2);
        *(s16 *)(effect + 0x9E) = 1;
        effect[0x92] = arg6;
        effect[0x93] = arg6;
        *(s16 *)(effect + 0x98) = arg2;
        *(s16 *)(effect + 0x9A) = arg3;
        *(s16 *)(effect + 0x9C) = arg4;
        *(s16 *)(effect + 0x96) = arg5;
        effect[0x94] = arg7;
        effect[0xA0] = arg0;
        effect[0xA1] = arg1;
        func_1517E05C(arg2, arg3, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166118 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15166118.s")
typedef struct {
    u8 pad_0[0x92];
    u8 field_92;
    u8 pad_93[3];
    s16 field_96;
    u8 pad_98[6];
    s16 field_9E;
} Game193430State;

extern s32 D_800BE9E4;
void func_1516972C(void *);

void func_15166204(Game193430State *arg0) {
    s32 temp_v0;

    arg0->field_9E = arg0->field_9E + (arg0->field_96 * D_800BE9E4);
    temp_v0 = arg0->field_92;
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C(arg0);
        return;
    }
    arg0->field_92 = temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15166268.s")
void *func_15142FBC(void *, s32, s32, u8 *);
void *func_15094F70(void *, void *, s32, void *, s32, s32, s32, s32, s32);
extern s32 D_800903F4;
extern s32 D_800A4AC8;
extern s32 D_800D2C9C;
extern s16 D_800DCE40;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern void *D_800DD228;
extern s32 D_800DD230;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151668B8 CURRENT (584) */
void func_151668B8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp37;
    s16 temp_v0;

    temp_v0 = D_800DCE40;
    D_800DCE40 = temp_v0 + 0x80;
    D_800DD228 = &D_800903F4;
    sp37 = 1;
    D_800DD220 = temp_v0;
    if (D_800DCE40 >= 0x500) {
        D_800DCE40 = 0;
    }
    D_800DD224 = 1;
    func_15142FBC(
        func_15094F70(arg0, D_800DD228, D_800DD220, &D_800DD230, 0, 0, 0, 1, 3),
        D_800D2C9C | 0x80000 | 0x2CA0,
        *(s32 *)((u8 *)&D_800A4AC8 + 0x18) | *(s32 *)((u8 *)&D_800A4AC8 + 0x1C),
        &sp37);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151668B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_151668B8.s")
