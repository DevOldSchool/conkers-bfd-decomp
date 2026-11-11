#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3F1F0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

void func_15103800(void);

void func_15011D40(void) {
    func_15103800();
}

typedef struct Game3F1F0State {
    void *owner;
    u8 index;
    s8 flag;
    s16 randomValue;
    s8 unk8;
    u8 pad9[3];
    s32 values[8];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    s16 unk3C;
    u8 pad3E[2];
    f32 positionX;
    f32 positionY;
    f32 positionZ;
} Game3F1F0State;

typedef struct Game3F1F0Descriptor {
    u8 pad0[0x15];
    s8 unk15;
    u8 pad16;
    s8 unk17;
    s32 index;
    u8 pad1C[0x24];
} Game3F1F0Descriptor;

typedef struct Game3F1F0Position {
    s16 x;
    s16 pad2;
    s16 y;
    s16 z;
} Game3F1F0Position;

void func_100226F0(void *arg0, s32 arg1);
void *func_10022EC0(void *, const void *, u32);
Game3F1F0Position *func_151438D8(s32 arg0, s32 arg1, s32 arg2, Game3F1F0Descriptor *arg3);

extern u8 D_800A1C00[][8];
extern s32 D_800D3094;

s32 func_15011D60(void *arg0) {
    Game3F1F0State state;
    Game3F1F0Descriptor descriptor;
    u8 *object;
    u8 i;
    s8 flag;

    func_100226F0(&state, sizeof(state));
    state.unk8 = 0;
    state.randomValue = (func_150ADA20() % 121U) + 0x12C;
    state.owner = arg0;
    state.index = ((s32 *)arg0)[7];
    if (state.index >= 4) {
        flag = 1;
    } else {
        flag = 0;
    }
    state.flag = flag;

    for (i = 0; i < 8; i++) {
        state.values[i] = (s32)func_151149AC(D_800A1C00[i][state.index]);
    }

    state.unk3C = 0;
    state.unk2C = 0.0f;
    state.unk30 = 0.0f;
    state.unk34 = 0.0f;
    state.unk38 = 0.0f;
    {
        Game3F1F0Position *position;

        descriptor.unk15 = 3;
        descriptor.unk17 = 0x15;
        descriptor.index = state.index;
        position = func_151438D8(0, D_800D3094, 0x11A0, &descriptor);
        if (position != 0) {
            state.positionX = position->x;
            state.positionY = position->y;
            state.positionZ = position->z;
        } else {
            state.positionZ = 10.0f;
        }
    }

    object = func_15149130(0x12C, -1, -1, -1, 0, 0x38, 0x4C, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &state, sizeof(state));
    }

    return 1;
}
