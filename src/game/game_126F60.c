#include "types.h"

/*
 * Reviewed source unit: src/game/game_126F60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9AB0 CURRENT (134) */
void func_150F9AB0(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6) {
    f32 matrix[16];
    u8 *record;
    struct Command { u32 high; u32 low; } *display_list;

    func_15110360(D_80082FA4, matrix, arg4, arg5, arg6);
    record = ((u8 (*)[0x180])D_800BE628)[D_80082FA4];
    display_list = (struct Command *)func_15110544(
        arg0,
        (s32)*(f32 *)(record + 0x2C),
        (s32)*(f32 *)(record + 0x24),
        (s32)(*(f32 *)(record + 0x30) - 1.0f),
        (s32)*(f32 *)(record + 0x28), 0, 0, 0);
    {
        struct Command *command = display_list++;
        command->high = 0xE7000000;
        command->low = 0;
    }
    {
        struct Command *command = display_list++;
        command->high = 0xEF002C0F;
        command->low = 0x0F0A4004;
    }
    {
        struct Command *command = display_list++;
        command->high = 0xFC357E6A;
        command->low = -1;
    }
    func_150FB4C0((void *)display_list, matrix);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150F9AB0.s")
