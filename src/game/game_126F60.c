#include "types.h"

/*
 * Reviewed source unit: src/game/game_126F60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9AB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15110360(s32, void *, f32, f32, f32);
u32 *func_15110544(void *, s32, s32, s32, s32, s32, s32, u8);
void func_150FB4C0(void *, f32 *);
extern s32 D_80082FA4;
extern s32 D_800BE628;

typedef struct {
    u8 pad[8];
    f32 matrix[16];
} Game126F60Matrix;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9AB0 CURRENT (980) */
void func_150F9AB0(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6) {
    Game126F60Matrix local;
    u8 *record;
    volatile u8 *display_list;

    func_15110360(D_80082FA4, local.matrix, arg4, arg5, arg6);
    record = (u8 *)(D_800BE628 + (D_80082FA4 * 0x180));
    display_list = (volatile u8 *)func_15110544(
        arg0,
        (s32)*(f32 *)(record + 0x2C),
        (s32)*(f32 *)(record + 0x24),
        (s32)(*(f32 *)(record + 0x30) - 1.0f),
        (s32)*(f32 *)(record + 0x28), 0, 0, 0);
    *(volatile u32 *)(display_list + 0x0) = 0xE7000000;
    *(volatile u32 *)(display_list + 0x4) = 0;
    *(volatile u32 *)(display_list + 0x8) = 0xEF002C0F;
    *(volatile u32 *)(display_list + 0xC) = 0x0F0A4004;
    *(volatile u32 *)(display_list + 0x14) = -1;
    *(volatile u32 *)(display_list + 0x10) = 0xFC357E6A;
    func_150FB4C0((void *)(display_list + 0x18), local.matrix);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150F9AB0.s")
