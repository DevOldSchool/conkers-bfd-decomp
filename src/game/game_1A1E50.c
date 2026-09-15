#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A1E50.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151749A0
 * - func_151749F8
 * - func_15174AA4
 * - func_15174B48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;
extern u8 D_800DD405;
extern u8 D_800DD406;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151749A0 CURRENT (480) */
void func_151749A0(s32 arg0, s32 arg1) {
    u8 temp_t1;
    u8 temp_t8;

    temp_t8 = D_800DD406 + D_800BE9E4;
    D_800DD406 = temp_t8;
    if (arg0 < (temp_t8 & 0xFF)) {
        temp_t1 = D_800DD405 + 1;
        D_800DD405 = temp_t1;
        if ((temp_t1 & 0xFF) >= arg1) {
            D_800DD405 = 0;
        }
        D_800DD406 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151749A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_151749A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_151749F8.s")
typedef void *(*Game1A1E50Callback)(void *, s32, void *);

extern s32 D_80089470;
extern Game1A1E50Callback D_8008CD74[];
extern void *D_800B0DF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15174AA4 CURRENT (2894) */
void *func_15174AA4(void *arg0, s32 arg1, s32 arg2) {
    volatile s32 sp2C;
    void *sp18;
    u8 temp_t0;
    void *temp_a0;
    void *var_a0;

    sp2C = arg1;
    arg1 = arg2;
    *(u32 *)((u8 *)arg0 + 0) = 0xE7000000;
    *(u32 *)((u8 *)arg0 + 4) = 0;
    temp_a0 = (u8 *)arg0 + 8;
    *(u32 *)((u8 *)temp_a0 + 0) = 0xDA380003;
    *(u32 *)((u8 *)temp_a0 + 4) = (u32)&D_80089470;
    var_a0 = (u8 *)temp_a0 + 8;
    temp_t0 = *(u8 *)((u8 *)D_800B0DF0 + 0xC);
    if (temp_t0 != 0) {
        sp18 = &D_80089470;
        var_a0 = D_8008CD74[temp_t0](var_a0, arg1, sp18);
    }
    *(u32 *)((u8 *)var_a0 + 0) = 0xDA380003;
    *(u32 *)((u8 *)var_a0 + 4) = (u32)&D_80089470;
    return (u8 *)var_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15174AA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_15174AA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_15174B48.s")
