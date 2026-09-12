#include "types.h"

/*
 * Reviewed source unit: src/game/game_7F710.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052260
 * - func_15052490
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052260.s")
typedef struct {
    u8 pad_0[0x95];
    s8 field_95;
} Game7F710Nested;

typedef struct {
    u8 pad_0[0x24];
    f32 field_24;
    u8 pad_28[0x14];
    f32 field_3C;
    u8 pad_40[0x41];
    s8 field_81;
    u8 pad_82[1];
    s8 field_83;
    u8 pad_84[5];
    s8 field_89;
    u8 pad_8A[0x23];
    s8 field_AD;
    u8 pad_AE[4];
    s16 field_B2;
    u8 pad_B4[4];
    f32 field_B8;
    u8 pad_BC[0x10E];
    u8 field_1CA;
    u8 pad_1CB[0x151];
    Game7F710Nested *field_31C;
} Game7F710State;

void func_15052408(Game7F710State *arg0) {
    arg0->field_B2 = 0;
    arg0->field_31C->field_95 = 0;
    if (arg0->field_1CA != 0) {
        arg0->field_81 = 0;
        arg0->field_83 = 0;
        arg0->field_89 = 6;
    }
    arg0->field_AD = 0;
    arg0->field_24 = 4.0f;
    arg0->field_B8 = 0.0f;
    arg0->field_3C = 15.0f;
}
void func_15052458(s32 arg0) {

}
void func_15060F28(u8 *arg0, s32 arg1);

void func_15052464(u8 *arg0) {
    if (arg0[0x1CA] == 0) {
        func_15060F28(arg0, 1);
    }
}
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15052490 CURRENT (420) */
void func_15052490(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fa0;
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg0 + 0x7A);
    temp_fa0 = arg3 * D_800D1550;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (temp_v0 + 0x4000) * 0.005493164f);
    if ((((arg1 & 0xFFFF) - temp_v0) + 0x4000) & 0x8000) {
        *(f32 *)((u8 *)arg0 + 0xB8) = (f32) (*(f32 *)((u8 *)arg0 + 0xB8) - (arg2 * temp_fa0));
        return;
    }
    *(f32 *)((u8 *)arg0 + 0xB8) = (f32) (*(f32 *)((u8 *)arg0 + 0xB8) + (arg2 * temp_fa0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15052490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052490.s")
void func_1505250C(void *arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xCE);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xCC);
    if (temp_v0 != temp_v1) {
        if (temp_v1 < temp_v0) {
            *(s16 *)((u8 *)arg0 + 0xCC) = (s16) (temp_v1 + ((s32) (temp_v0 - temp_v1) / 12) + 1);
            if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xCC)) {
                *(s16 *)((u8 *)arg0 + 0xCC) = temp_v0;
            }
        } else {
            *(s16 *)((u8 *)arg0 + 0xCC) = (s16) ((temp_v1 + ((s32) (temp_v0 - temp_v1) / 12)) - 1);
            if (*(s16 *)((u8 *)arg0 + 0xCC) < temp_v0) {
                *(s16 *)((u8 *)arg0 + 0xCC) = temp_v0;
            }
        }
    }
}
