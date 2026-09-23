#include "types.h"

/*
 * Reviewed source unit: src/game/game_138B40.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510B690
 * - func_1510B7B4
 * - func_1510B958
 * - func_1510B9D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x64];
    f32 base_x;
    f32 base_y;
    f32 scale_x;
    f32 scale_y;
    f32 value_x;
    f32 value_y;
    u8 pad7C[0x104];
} Game138B40Record;

typedef struct {
    u32 words[0x10];
} Game138B40Work;

extern Game138B40Record *D_800BE628;

void func_150A7A48(void *, void *, void *);
void func_151EFEB8(void *, s32);
void func_1501B22C(s32);

extern s32 D_80082FA0;
extern u8 D_800BE9C0;
extern u8 D_800D9C10[];
extern u8 D_800D9D10[];
extern u8 *D_800DC2A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510B690 CURRENT (255) */
void func_1510B690(void) {
    Game138B40Work sp4C;
    s16 var_s0;
    s32 temp_s1;
    void *temp_s2;

    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        do {
            func_151EFEB8(&sp4C,
                          (s32)((u8 *)D_800BE628 +
                                (((var_s0 << 2) - var_s0) << 7) +
                                (D_800BE9C0 << 6) + 0x100));
            temp_s1 = var_s0 << 6;
            temp_s2 = &D_800D9C10[temp_s1];
            func_151EFEB8(temp_s2,
                          (s32)(D_800DC2A0[D_800BE9C0] + (var_s0 * 0x40)));
            func_150A7A48(temp_s2, &sp4C, &D_800D9D10[temp_s1]);
            func_1501B22C(var_s0);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510B690 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B690.s")
extern u8 D_80089470[];

typedef struct Game138B40Command {
    u32 word0;
    u32 word1;
} Game138B40Command;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510B7B4 CURRENT (7175) */
void *func_1510B7B4(void *arg0, s32 arg1) {
    volatile Game138B40Command *command;
    Game138B40Command *cursor;

    cursor = arg0;
    command = cursor++;
    command->word0 = 0xE7000000;
    command->word1 = 0;
    command = cursor++;
    command->word1 = 1;
    command->word0 = 0xF9000000;
    command = cursor++;
    command->word0 = 0xDA380003;
    command->word1 = (s32)D_80089470;
    command = cursor++;
    command->word0 = 0xDB0E0000;
    command->word1 = *(u16 *)((u8 *)&D_800BE628[arg1] + 0xB8);
    command = cursor++;
    command->word1 = 3;
    command->word0 = 0xDB040004;
    command = cursor++;
    command->word0 = 0xDB04000C;
    command->word1 = 3;
    command = cursor++;
    command->word0 = 0xDB040014;
    command->word1 = 0xFFFD;
    command = cursor++;
    command->word0 = 0xDB04001C;
    command->word1 = 0xFFFD;
    command = cursor++;
    command->word0 = 0xD9EFFFFF;
    command->word1 = 0;
    command = cursor++;
    command->word0 = 0xDA380007;
    command->word1 = (s32)((u8 *)&D_800BE628[arg1] +
                          (D_800BE9C0 << 6) + 0x100);
    command = cursor++;
    command->word0 = 0xDA380005;
    command->word1 = (s32)(D_800DC2A0[D_800BE9C0] + (arg1 << 6));
    command = cursor++;
    command->word0 = 0xEF082C3F;
    command->word1 = 0x552230;
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510B7B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B7B4.s")
extern volatile f32 D_800D35E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510B958 CURRENT (460) */
void func_1510B958(s32 arg0) {
    Game138B40Record *record;

    record = &D_800BE628[arg0];
    D_800D35E0 = (((record->value_x / record->scale_x) - 1.0f) * -1.0f) + record->base_x;
    *(volatile f32 *)((u8 *)&D_800D35E0 + 4) = (((record->value_y / record->scale_y) - 1.0f) * -1.0f) + record->base_y;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510B958 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B9D0.s")
