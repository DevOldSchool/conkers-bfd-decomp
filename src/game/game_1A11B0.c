#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A11B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151742EC
 * - func_151745F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TXL2WORDS(txls, b_txl) MAX(1, ((txls) * (b_txl) / 8))
#define CALC_DXT(width, b_txl) (((1 << 11) + TXL2WORDS(width, b_txl) - 1) / TXL2WORDS(width, b_txl))

typedef struct Game1A11B0Command {
    u32 w0;
    u32 w1;
} Game1A11B0Command;

typedef struct Game1A11B0View {
    u8 pad0[4];
    f32 width;
    u8 pad8[0x178];
} Game1A11B0View;

Game1A11B0Command *func_1501A490(Game1A11B0Command *, s16, s32, s32, s32, s32);
Game1A11B0Command *func_1501A680(Game1A11B0Command *);
extern s32 D_8002AAE8[];
extern s16 D_80082FA6;
extern s32 D_800BE620;
extern Game1A11B0View *D_800BE628;
extern u8 D_800BE9C0;
extern s32 D_800BE9C4;

Game1A11B0Command *func_15173D00(Game1A11B0Command *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6) {
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE200001C; command->w1 = 0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3000C00; command->w1 = 0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3000A01; command->w1 = 0x200000; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE2001E01; command->w1 = 0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3001001; command->w1 = 0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3001801; command->w1 = 0xC0; }
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3001A01; command->w1 = 0x30; }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(1 - 1, 0, 12); command->w1 = D_800BE9C4 + arg2 * D_800BE620 * 2; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(0, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE6, 24, 8); command->w1 = 0; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF3, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL(MIN((((s32)D_800BE628[arg6].width * 1) + 0 >> 0) - 1, 0x7FF), 12, 12) | _SHIFTL(CALC_DXT((s32)D_800BE628[arg6].width, 2), 0, 12); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE7, 24, 8); command->w1 = 0; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((s32)D_800BE628[arg6].width * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF2, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(((s32)D_800BE628[arg6].width - 1) << 2, 12, 12) | _SHIFTL((1 - 1) << 2, 0, 12); }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xFF, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(4 - 1, 0, 12); command->w1 = arg4; }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xED, 24, 8) | _SHIFTL((s32)((f32)(0) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(0) * 4.0f), 0, 12); command->w1 = _SHIFTL(0, 24, 2) | _SHIFTL((s32)((f32)((s32)D_800BE628[arg6].width) * 4.0f), 12, 12) | _SHIFTL((s32)((f32)(1) * 4.0f), 0, 12); }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL(3 << 2, 12, 12) | _SHIFTL(1 << 2, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0 << 2, 12, 12) | _SHIFTL(0 << 2, 0, 12); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE1, 24, 8); command->w1 = _SHIFTL(arg1 << 5, 16, 16) | _SHIFTL(0, 0, 16); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF1, 24, 8); command->w1 = _SHIFTL(4 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(1 - 1, 0, 12); command->w1 = D_8002AAE8[D_800BE9C0] + arg2 * D_800BE620 * 2; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(0, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE6, 24, 8); command->w1 = 0; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF3, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->w1 = _SHIFTL(7, 24, 3) | _SHIFTL(MIN((((s32)D_800BE628[arg6].width * 1) + 0 >> 0) - 1, 0x7FF), 12, 12) | _SHIFTL(CALC_DXT((s32)D_800BE628[arg6].width, 2), 0, 12); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE7, 24, 8); command->w1 = 0; } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((s32)D_800BE628[arg6].width * 2) + 7) >> 3, 9, 9) | _SHIFTL(0, 0, 9); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 20, 4) | _SHIFTL(0, 18, 2) | _SHIFTL(0, 14, 4) | _SHIFTL(0, 10, 4) | _SHIFTL(0, 8, 2) | _SHIFTL(0, 4, 4) | _SHIFTL(0, 0, 4); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF2, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(((s32)D_800BE628[arg6].width - 1) << 2, 12, 12) | _SHIFTL((1 - 1) << 2, 0, 12); }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xFF, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(4 - 1, 0, 12); command->w1 = arg5; }
    { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL(3 << 2, 12, 12) | _SHIFTL(1 << 2, 0, 12); command->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0 << 2, 12, 12) | _SHIFTL(0 << 2, 0, 12); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xE1, 24, 8); command->w1 = _SHIFTL(arg1 << 5, 16, 16) | _SHIFTL(0, 0, 16); } { Game1A11B0Command *command = arg0++; command->w0 = _SHIFTL(0xF1, 24, 8); command->w1 = _SHIFTL(4 << 10, 16, 16) | _SHIFTL(1 << 10, 0, 16); }
    arg0 = func_1501A490(func_1501A680(arg0), D_80082FA6, 0, 0, 0, 0);
    { Game1A11B0Command *command = arg0++; command->w0 = 0xE3000C00; command->w1 = 0x80000; }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_151742EC.s")
typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    u8 state;
    u8 pad_D[0x27];
    s8 field_34;
    u8 pad_35[3];
    s32 field_38;
} Game1A11B0Entry;

extern Game1A11B0Entry D_800DD348[];
extern Game1A11B0Entry D_800DD3FC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151745F0 CURRENT (1640) */
s32 func_151745F0(f32 arg0, f32 arg1, f32 arg2, void *arg3, s8 arg4,
                  s32 arg5) {
    typedef struct { u32 words[9]; } Copy9;
    Game1A11B0Entry *entry;
    Game1A11B0Entry *end;

    entry = D_800DD348;
    end = D_800DD3FC;
loop:
    if (entry->state == 0) {
        entry->field_0 = arg0;
        entry->field_4 = arg1;
        entry->state = 3;
        entry->field_8 = arg2;
        entry->field_34 = arg4;
        entry->field_38 = arg5;
        if (arg3 != 0) {
            *(Copy9 *)((u8 *)entry + 0x10) = *(Copy9 *)arg3;
        }
        return 0;
    }
    entry++;
    if (entry != end) {
        goto loop;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151745F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A11B0/func_151745F0.s")
