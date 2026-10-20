#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1FFB70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 */

void func_151D26C0(s16 arg0) {
    void *temp_v0;

    temp_v0 = func_15167A68(0x3C, 1, 0x18, 0, 0xFF, 1);
    *(s16 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x12) = 0;
    *(s16 *)((u8 *)temp_v0 + 0xE) = 0;
    *(s8 *)((u8 *)temp_v0 + 0x16) = 1;
    *(s16 *)((u8 *)temp_v0 + 0x10) = arg0;
}
extern void *D_800DD0E0;

void func_151D2718(s16 arg0) {
    void *var_v0;

    var_v0 = D_800DD0E0;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s16 *)((u8 *)var_v0 + 0x10)) {
                *(s8 *)((u8 *)var_v0 + 0x16) = -2;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 8);
        } while (var_v0 != 0);
    }
}
extern s32 D_800BE9E4;

void func_151D275C(void *arg0) {
    u8 *p = arg0;
    s8 temp_v0;
    u16 temp_v1; // stored as s16 either way, but s32 here changes register allocation

    // the target loads the step (lb 0x16) before the position (lh 0xE)
    *(s16 *)(p + 0xE) = (s16)(D_800BE9E4 * (temp_v0 = *(s8 *)(p + 0x16)) + *(s16 *)(p + 0xE));
    if (temp_v0 > 0 && *(s16 *)(p + 0xE) >= 0xED) {
        temp_v1 = 0x128 - *(s16 *)(p + 0xE);
        *(s16 *)(p + 0x14) = (s16)(temp_v1 * 4);
        if (*(s16 *)(p + 0x14) < 0) {
            *(s16 *)(p + 0x14) = 0;
        }
    } else {
        *(s16 *)(p + 0x14) = (s16)(*(s16 *)(p + 0xE) * 2);
    }
    if (*(s16 *)(p + 0x14) >= 0x80) {
        *(s16 *)(p + 0x14) = 0x80;
    }
    *(s16 *)(p + 0x12) = (s16)(*(s16 *)(p + 0x12) + 1);
    if (*(s16 *)(p + 0x12) >= 0x100) {
        *(s16 *)(p + 0x12) = (s16)(*(s16 *)(p + 0x12) - 0x100);
    }
    if (*(s16 *)(p + 0xE) >= 0x12D || *(s16 *)(p + 0xE) < 0) {
        func_1516972C(arg0);
    }
}
typedef struct GameD2830Command { u32 word0, word1; } GameD2830Command;
typedef struct GameD2830State {
    u8 pad00[0x10];
    s16 id;
    s16 phase;
    s16 opacity;
} GameD2830State;
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_A48[];

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
void *func_151D2830(GameD2830Command *arg0, GameD2830State *arg1, s16 arg2) {
    s32 resource;

    if (arg2 != arg1->id || arg1->opacity == 0) return arg0;
    { GameD2830Command *command = arg0++; command->word0 = 0xD7000002; command->word1 = -1; }
    { GameD2830Command *command = arg0++; command->word0 = 0xE7000000; command->word1 = 0; }
    { GameD2830Command *command = arg0++; command->word0 = 0xFC12D225; command->word1 = 0xFFA7FFFF; }
    { GameD2830Command *command = arg0++; command->word0 = 0xEF002C3F; command->word1 = 0x00504244; }
    resource = func_1510D0EC((s32)D_A48, 0, 3, 0);
    { GameD2830Command *command = arg0++; command->word0 = 0xFD700000; command->word1 = resource; }
    { GameD2830Command *command = arg0++; command->word0 = 0xF5700000; command->word1 = 0x07018060; }
    { GameD2830Command *command = arg0++; command->word0 = 0xE6000000; command->word1 = 0; }
    { GameD2830Command *command = arg0++; command->word0 = 0xF3000000; command->word1 = 0x077FF000; }
    { GameD2830Command *command = arg0++; command->word0 = 0xE7000000; command->word1 = 0; }
    { GameD2830Command *command = arg0++; command->word0 = 0xF5681000; command->word1 = 0x00018060; }
    { GameD2830Command *command = arg0++; command->word0 = 0xF2000000; command->word1 = 0x000FC0FC; }
    { GameD2830Command *command = arg0++; command->word0 = 0xFB000000; command->word1 = (arg1->opacity & 255) | 0x00FF0000; }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL(0x500, 12, 12) | _SHIFTL(0x3C0, 0, 12); command->word1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xE1, 24, 8); command->word1 = _SHIFTL(arg1->phase << 3, 16, 16) | _SHIFTL(0x400, 0, 16); }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xF1, 24, 8); command->word1 = _SHIFTL(0x400, 16, 16) | _SHIFTL(0x400, 0, 16); }
    { GameD2830Command *command = arg0++; command->word0 = 0xE7000000; command->word1 = 0; }
    { GameD2830Command *command = arg0++; command->word0 = 0xFB000000; command->word1 = ((arg1->opacity >> 1) & 255) | 0xFF000000; }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL(0x500, 12, 12) | _SHIFTL(0x3C0, 0, 12); command->word1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12); }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xE1, 24, 8); command->word1 = _SHIFTL(arg1->phase << 3, 16, 16) | _SHIFTL(0, 0, 16); }
    { GameD2830Command *command = arg0++; command->word0 = _SHIFTL(0xF1, 24, 8); command->word1 = _SHIFTL(0x200, 16, 16) | _SHIFTL(0x200, 0, 16); }
    return arg0;
}
