#include "types.h"
#include "game_functions.h"
#include "game_render_view.h"

/*
 * Reviewed source unit: src/game/game_138B40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510B9D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */


typedef struct {
    u32 words[0x10];
} Game138B40Work;

void func_150A7A48(void *, void *, void *);
void func_151EFEB8(void *, s32);
void func_1501B22C(s32);

extern s32 D_80082FA0;
extern u8 D_800BE9C0;
extern u8 D_800D9C10[];
extern u8 D_800D9D10[];
extern u8 *D_800DC2A0[];

void func_1510B690(void) {
    s16 i;
    Game138B40Work sp4C;

    for (i = 0; i <= D_80082FA0; i++) {
        func_151EFEB8(&sp4C, (s32)&D_800BE628[i].matrices[D_800BE9C0]);
        func_151EFEB8(D_800D9C10 + (i << 6), (s32)(D_800DC2A0[D_800BE9C0] + i * 64));
        func_150A7A48(D_800D9C10 + (i << 6), &sp4C, D_800D9D10 + (i << 6));
        func_1501B22C(i);
    }
}
extern u8 D_80089470[];

typedef struct Game138B40Command {
    u32 word0;
    u32 word1;
} Game138B40Command;

Game138B40Command *func_1510B7B4(Game138B40Command *arg0, s32 arg1) {
    { Game138B40Command *command = arg0++; command->word0 = 0xE7000000; command->word1 = 0; }
    { Game138B40Command *command = arg0++; command->word0 = 0xF9000000; command->word1 = 1; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380003; command->word1 = (s32)D_80089470; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB0E0000; command->word1 = D_800BE628[arg1].normalization; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB040004; command->word1 = 3; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB04000C; command->word1 = 3; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB040014; command->word1 = 0xFFFD; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB04001C; command->word1 = 0xFFFD; }
    { Game138B40Command *command = arg0++; command->word0 = 0xD9EFFFFF; command->word1 = 0; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380007; command->word1 = (s32)&D_800BE628[arg1].matrices[D_800BE9C0]; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380005; command->word1 = (s32)(D_800DC2A0[D_800BE9C0] + (arg1 << 6)); }
    { Game138B40Command *command = arg0++; command->word0 = 0xEF082C3F; command->word1 = 0x552230; }
    return arg0;
}
extern f32 D_800D35E0, D_800D35E4;

void func_1510B958(s32 arg0) {
    GameRenderView *record;

    record = (GameRenderView *)((u8 *)D_800BE628 + arg0 * 0x180);
    D_800D35E0 = (((record->value_x / record->scale_x) - 1.0f) * -1.0f) + record->base_x;
    D_800D35E4 = (((record->value_y / record->scale_y) - 1.0f) * -1.0f) + record->base_y;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B9D0.s")
