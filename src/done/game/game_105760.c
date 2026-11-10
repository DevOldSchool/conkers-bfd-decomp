#include "types.h"

/*
 * Reviewed source unit: src/game/game_105760.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 */

void func_150D82B0(s32 arg0) {

}
extern s32 D_80090298[];
extern f32 D_800A0B10;

s32 func_150D82BC(u8 *arg0, u8 *arg1) {
    s32 index;
    s8 *display;
    f32 scaled;
    s32 value;
    s32 *cmd;
    s32 temp;

    temp = *(s32 *)(arg1 + 0x2D0);
    if (temp == 0) {
        return 0;
    }
    *(s16 *)(arg0 + 0x18) = D_80090298[6];
    if (*(u16 *)(arg1 + 0x84) == 0xD && *(f32 *)(temp + 8) >= 23.0f &&
        *(f32 *)(temp + 8) <= 40.0f) {
        *(s16 *)(arg0 + 0x18) = D_80090298[7];
        display = **(s8 ***)(arg0 + 0x24);
        scaled = *(f32 *)(temp + 8) - 23.0f;
        scaled *= D_800A0B10;
        index = 0;
        while (*(s8 *)((index << 3) + (s32)display) != -0xE) {
            index++;
        }
        cmd = (s32 *)((s32)display + (index << 3));
        temp = *cmd;
        value = (s32)(70.0f * scaled + 2.0f);
        if (value < 0) {
            value += (temp >> 12) & 0xFFF;
        }
        *cmd = ((value & 0xFFF) << 12) | 0xF2000000 | 2;
    }
    return 0;
}
typedef struct GameD83D8State {
    u8 pad0[0x18];
    s16 field18;
    u8 pad1A[0xA];
    s8 **display;
    u8 pad28[0x10];
    s32 phase;
    s32 progress;
} GameD83D8State;

typedef struct GameD83D8Owner {
    u8 pad0[0x84];
    u16 action;
    u8 pad86[0x24A];
    u8 *position;
} GameD83D8Owner;

extern f32 D_800A0B14;
extern s32 D_800BE9E4;

s32 func_150D83D8(GameD83D8State *arg0, GameD83D8Owner *arg1) {
    s32 index;
    s8 *display;
    f32 scaled;

    switch (arg0->phase) {
    case 0:
        arg0->progress = 0x32;
        arg0->field18 = D_80090298[0x6C / 4];
        if (arg1->action == 0x18D && *(f32 *)(arg1->position + 8) >= 46.0f) {
            arg0->phase = 1;
            arg0->field18 = D_80090298[0x70 / 4];
        }
        break;
    case 1:
        arg0->progress += D_800BE9E4;
        if (arg0->progress >= 0x64) {
            arg0->progress = 0x64;
            arg0->phase = 2;
        }
        break;
    case 2:
        if (arg1->action == 0x18E && *(f32 *)(arg1->position + 8) >= 34.0f) {
            arg0->phase = 3;
        }
        break;
    case 3:
        arg0->progress -= D_800BE9E4 * 4;
        if (arg0->progress <= 0) {
            arg0->progress = 0;
            arg0->phase = 4;
        }
        break;
    }
    scaled = (f32)arg0->progress * D_800A0B14;
    display = *arg0->display;
    index = 0;
    while (*(s8 *)((index << 3) + (s32)display) != -0xE) {
        index++;
    }
    *(s32 *)((s32)display + (index << 3)) =
        ((s32)(120.0f * scaled + 2.0f) & 0xFFF) |
        0xF2002000;
    return 0;
}
