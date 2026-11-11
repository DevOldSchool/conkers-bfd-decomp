#include "types.h"

/*
 * Reviewed source unit: src/game/game_43620.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

typedef struct Game43620State {
    u8 pad0[8];
    s32 field_8;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
    u8 pad18[0xC];
    s16 field_24;
    u8 pad26[0xA];
    s16 field_30;
    s16 field_32;
    u8 pad34[0x28];
    s32 field_5C;
    u8 pad60[0x14];
    s32 field_74;
    u8 pad78[0xC];
    s32 field_84;
    u32 field_88;
    u8 pad8C[8];
    s16 field_94;
    s16 field_96;
    u8 pad98[2];
    s8 field_9A;
} Game43620State;

void func_100226F0(void *, s32);
s32 func_10012844(s32, s32, s32, s32, s32);
void func_151F3C34(void *, s16, s32);
extern void func_151F3C4C(void);
extern s16 D_8002BC10[];
extern Game43620State D_800E0D80;

void func_15016170(s32 arg0) {
    func_100226F0(&D_800E0D80, 0xA0);
    D_800E0D80.field_8 = func_10012844(0, 0, arg0, 1, 0x50);
    D_800E0D80.field_74 = func_10012844(0, 0, arg0, 1, 0x440);
    D_800E0D80.field_5C = func_10012844(0, 0, arg0, 1, 8);
    D_800E0D80.field_C = 0x40;
    D_800E0D80.field_96 = 0x40;
    D_800E0D80.field_84 = 0;
    D_800E0D80.field_88 = 0x7FFF;
    D_800E0D80.field_9A = 0;
    D_800E0D80.field_32 = 0;
    D_800E0D80.field_30 = 0;
    D_800E0D80.field_94 = D_800E0D80.field_96;
    D_800E0D80.field_E = 0x7FFF;
    D_800E0D80.field_10 = (s16)((D_8002BC10[D_800E0D80.field_C] * D_800E0D80.field_E) >> 15);
    D_800E0D80.field_12 = (s16)((D_8002BC10[0x7F - D_800E0D80.field_C] * D_800E0D80.field_E) >> 15);
    D_800E0D80.field_24 = 1;
    D_800E0D80.field_14 = 0x7FFC;
    D_800E0D80.field_16 = 0;
    func_151F3C34(&func_151F3C4C, D_800E0D80.field_E, 0x40);
}
