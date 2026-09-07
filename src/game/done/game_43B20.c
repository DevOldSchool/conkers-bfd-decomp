#include "types.h"

/*
 * Reviewed source unit: src/game/game_43B20.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 */

extern s8 D_800D18C0;

typedef struct Game43B20Target {
    s16 x;
    s16 y;
    s16 z;
    s8 unk6;
    u8 type;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    u8 pad14;
    s8 unk15;
} Game43B20Target;

typedef struct Game43B20Source {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 z;
    u8 type;
} Game43B20Source;

extern Game43B20Source *volatile D_800D20FC;
extern s32 D_800D2120;
extern s32 D_800D2124;
extern u32 D_800D2128;
extern s32 D_800D212C;

#define D_800D212C_PTR (*(Game43B20Target *volatile *)&D_800D212C)

void func_15016670(void) {
    D_800D18C0 = 0;
}
void func_15016680(void) {
    D_800D212C = 0;
}

void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u32 func_1502B7F0(Game43B20Target **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15016690(s32 arg0) {
    u32 count;
    f32 value;
    Game43B20Source *source;
    Game43B20Target *target;

    D_800D2120 = -1;
    D_800D2124 = -1;
    count = func_1502B7F0((Game43B20Target **)&D_800D212C, 3, 0xC, arg0, 6) / 24U;
    D_800D2128 = count;

    if (count == 0) {
        D_800D212C_PTR = func_10003C40(0x18, 1, 0, 0);
        D_800D2128 = 1;
        source = D_800D20FC;
        if (source != 0) {
            D_800D212C_PTR->x = source->x;
            D_800D212C_PTR->y = D_800D20FC->y;
            D_800D212C_PTR->z = D_800D20FC->z;
            D_800D212C_PTR->offsetX = D_800D20FC->x + 100;
            D_800D212C_PTR->offsetY = D_800D20FC->y + 100;
            D_800D212C_PTR->offsetZ = D_800D20FC->z;
            D_800D212C_PTR->unk6 = 0;
            D_800D212C_PTR->type = D_800D20FC->type;
            D_800D212C_PTR->unk15 = 0;
            return;
        }

        D_800D212C_PTR->x = 0xE10;
        D_800D212C_PTR->y = -0xC80;
        D_800D212C_PTR->z = -0x898;
        D_800D212C_PTR->offsetZ = 1000.0f;
        target = D_800D212C_PTR;
        value = target->offsetZ;
        target->offsetY = value;
        D_800D212C_PTR->offsetX = value;
        D_800D212C_PTR->unk6 = 0;
        D_800D212C_PTR->type = 0;
        D_800D212C_PTR->unk15 = 0;
    }
}
