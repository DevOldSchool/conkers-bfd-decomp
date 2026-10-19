#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F5800.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_narrow_effect_record_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C8350
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE4E0;
extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C8350 CURRENT (450) */
void func_150C8350(void) {
    s32 temp_a1;
    s32 temp_a1_3;
    s32 var_a0;
    s32 var_a2;
    s32 temp_a1_2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_t0;
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    do {
        var_v0 = (u8 *)D_800BE4E0 + var_v1;
        var_a0 = *(s16 *)((u8 *)var_v0 + 6);
        temp_a1 = *(s16 *)((u8 *)var_v0 + 8);
        if (var_a0 != temp_a1) {
            var_a2 = temp_a1;
            if (var_a0 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = var_a2 - var_a0;
            temp_t7 = D_800BE9E4 * 0x10;
            var_t0 = temp_a1_2 < 0 ? -temp_a1_2 : temp_a1_2;
            if (var_t0 < temp_t7) {
                *(s16 *)((u8 *)var_v0 + 6) = var_a2;
                var_v0 = (u8 *)D_800BE4E0 + var_v1;
                var_a0 = *(s16 *)((u8 *)var_v0 + 6);
            } else {
                if (temp_a1_2 < 0) {
                    var_a1 = -1;
                } else {
                    var_a1 = 1;
                }
                *(s16 *)((u8 *)var_v0 + 6) = (s16) (var_a0 + (temp_t7 * var_a1));
                var_v0 = (u8 *)D_800BE4E0 + var_v1;
                var_a0 = *(s16 *)((u8 *)var_v0 + 6);
            }
        }
        *(s16 *)((u8 *)var_v0 + 4) += var_a0 * *(s8 *)((u8 *)var_v0 + 2) * D_800BE9A0;
        var_v0 = (u8 *)D_800BE4E0 + var_v1;
        temp_a1_3 = *(s16 *)((u8 *)var_v0 + 4);
        if (temp_a1_3 >= 0x500) {
            *(s16 *)((u8 *)var_v0 + 4) = (s16) (temp_a1_3 - 0x500);
            var_v0 = (u8 *)D_800BE4E0 + var_v1;
            *(s16 *)((u8 *)var_v0 + 4) = (s16) (0x500 - *(s16 *)((u8 *)var_v0 + 4));
            var_v0 = (u8 *)D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)var_v0 + 2) = (s8) -*(s8 *)((u8 *)var_v0 + 2);
            var_v0 = (u8 *)D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)var_v0 + 4) >= 0x500) {
                *(s16 *)((u8 *)var_v0 + 4) = 0x4FF;
            }
        } else if (temp_a1_3 < 0) {
            *(s16 *)((u8 *)var_v0 + 4) = (s16) -temp_a1_3;
            var_v0 = (u8 *)D_800BE4E0 + var_v1;
            *(s8 *)((u8 *)var_v0 + 2) = (s8) -*(s8 *)((u8 *)var_v0 + 2);
            var_v0 = (u8 *)D_800BE4E0 + var_v1;
            if (*(s16 *)((u8 *)var_v0 + 4) < 0) {
                *(s16 *)((u8 *)var_v0 + 4) = 0;
            }
        }
        var_v1 += 0xA;
    } while (var_v1 != 0x64);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C8350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F5800/func_150C8350.s")
void func_150C84F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8350();
    }
}
void func_150CDB6C(s32);

void func_150C851C(s32 arg0) {
    s32 base;
    s32 range;
    s32 i;

    if (D_800BE4E0 != 0) {
        func_150CDB6C(arg0);
        range = ((s32)(arg0 * 0x32) >> 8) + 0x32; base = (s32)(arg0 * 0x12C) >> 8;
        for (i = 0; i < 10; i++) {
            arg0 = base;
            arg0 += func_150ADA20() % (u32)range;
            *(s16 *)((u8 *)D_800BE4E0 + i * 10 + 8) = arg0;
        }
    }
}
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 *D_80088810[2];

typedef struct GameF5800Command {
    u32 w0;
    u32 w1;
} GameF5800Command;

GameF5800Command *func_150C8600(GameF5800Command *arg0) {
    typedef struct { s32 *entries[2]; } PointerPair;
    s32 record_offset;
    s32 command_offset;
    s32 workspace[2];
    s32 variant;
    PointerPair tables;
    s32 result;

    tables = *(PointerPair *)D_80088810;
    for (record_offset = 0, command_offset = 4; command_offset != 0x2C; command_offset += 4, record_offset += 0xA) {
        variant = *(s16 *)((u8 *)D_800BE4E0 + record_offset + 4) >> 8;
        if (variant < 0) {
            variant = 0;
        } else if (variant >= 5) {
            variant = 4;
        }
        if (*((u8 *)D_800BE4E0 + record_offset) >= 2) {
            *((u8 *)D_800BE4E0 + record_offset) = 0;
        }
        result = func_1510D0EC(tables.entries[*((u8 *)D_800BE4E0 + record_offset)][variant], workspace, 3, 0);
        { GameF5800Command *command = arg0++; command->w0 = (command_offset & 0xFFFF) | 0xDB060000; command->w1 = result; }
    }
    return arg0;
}
