#include "types.h"

/*
 * Reviewed source unit: src/game/game_126F60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

typedef struct Game126F60Command {
    u32 high;
    u32 low;
} Game126F60Command;

void func_15110360(s32, void *, f32, f32, f32);
Game126F60Command *func_15110544(Game126F60Command *, s32, s32, s32, s32, s32, s32, u8);
void func_150FB4C0(void *, f32 *);
extern s32 D_80082FA4;
extern s32 D_800BE628;

typedef struct {
    u8 pad[8];
    f32 matrix[16];
} Game126F60Matrix;

void func_150F9AB0(Game126F60Command *arg0, s32 arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6) {
    f32 matrix[16];
    u8 *record;

    func_15110360(D_80082FA4, matrix, arg4, arg5, arg6);
    record = ((u8 (*)[0x180])D_800BE628)[D_80082FA4];
    arg0 = func_15110544(
        arg0,
        (s32)*(f32 *)(record + 0x2C),
        (s32)*(f32 *)(record + 0x24),
        (s32)(*(f32 *)(record + 0x30) - 1.0f),
        (s32)*(f32 *)(record + 0x28), 0, 0, 0);
    { Game126F60Command *command = arg0++; command->high = 0xE7000000; command->low = 0; }
    { Game126F60Command *command = arg0++; command->high = 0xEF002C0F; command->low = 0x0F0A4004; }
    { Game126F60Command *command = arg0++; command->high = 0xFC357E6A; command->low = -1; }
    func_150FB4C0(arg0, matrix);
}
