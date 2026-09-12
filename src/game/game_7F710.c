#include "types.h"

/*
 * Reviewed source unit: src/game/game_7F710.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052260
 * - func_15052408
 * - func_15052490
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_7F710/func_15052408.s")
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
