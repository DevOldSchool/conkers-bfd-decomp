#include "types.h"

/*
 * Reviewed source unit: src/game/game_15BAA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct Game12E5F0Command { u32 first, second; } Game12E5F0Command;
void *func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A680(void *);
extern s16 D_80082FA6;
extern s32 D_800BE620;
extern s32 D_800BE9C4;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TXL2WORDS(txls, b_txl) MAX(1, ((txls) * (b_txl) / 8))
#define CALC_DXT(width, b_txl) (((1 << 11) + TXL2WORDS(width, b_txl) - 1) / TXL2WORDS(width, b_txl))
Game12E5F0Command *func_1512E5F0(Game12E5F0Command *arg0, u8 *arg1) {
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
    { Game12E5F0Command *command = arg0++; command->first = 0xEF202CFF; command->second = 0; }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(1 - 1, 0, 12); command->second = *(u16 *)(arg1 + 0x8BA) * D_800BE620 * 2 + D_800BE9C4; } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(0, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE6, 24, 8); command->second = 0; } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xF3, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->second = _SHIFTL(7, 24, 3) | _SHIFTL(MIN(D_800BE620 - 1, 0x7FF), 12, 12) | _SHIFTL(CALC_DXT(D_800BE620, 2), 0, 12); }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(((D_800BE620 * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xF2, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL((D_800BE620 - 1) << 2, 12, 12) | _SHIFTL((1 - 1) << 2, 0, 12); }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xFF, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(D_800BE620 - 1, 0, 12); command->second = *(u32 *)(arg1 + 0x8BC); }
    { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xED, 24, 8) | _SHIFTL((s32)((f32)(0) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(0) * 4.0f), 0, 12); command->second = _SHIFTL(0, 24, 2) | _SHIFTL((s32)((f32)(D_800BE620) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(1) * 4.0f), 0, 12); } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE4, 24, 8) | _SHIFTL(D_800BE620 << 2, 12, 12) | _SHIFTL(1 << 2, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE1, 24, 8); command->second = _SHIFTL(0, 16, 16) | _SHIFTL(0, 0, 16); } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xF1, 24, 8); command->second = _SHIFTL(4 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); } { Game12E5F0Command *command = arg0++; command->first = _SHIFTL(0xE7, 24, 8); command->second = 0; }
    arg0 = func_1501A490(func_1501A680(arg0), D_80082FA6, 0, 0, 0, 0);
    { Game12E5F0Command *command = arg0++; command->first = 0xEF082C3F; command->second = 0x552230; }
    return arg0;
}
