#include "types.h"

/*
 * Reviewed source unit: src/game/game_49BE0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 */

void func_1501C53C(void);
void func_15016680(void);
extern s16 D_800D2132;
extern s32 D_800BEA00;
extern s32 D_800BEA04;
extern s32 D_800BE9F4;
extern u16 D_800CC382;
extern u8 D_800DD2C0;
extern u8 D_800BE615;
extern u8 D_800BE616;

void func_1501C730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_1501C53C();
    D_800D2132 = 0;

    switch (arg0) {
        case 4:
        case 6:
            D_800BEA00 = arg4;
            D_800BEA04 = arg3;
            D_800BE9F4 = arg1;
            D_800DD2C0 = arg2;
            D_800BE615 = 2;
            break;
        case 1:
            D_800BE615 = 3;
            D_800BE9F4 = arg1;
            D_800D2132 = D_800CC382;
            break;
        case 2:
            D_800BE615 = 3;
            D_800BE9F4 = arg1;
            D_800DD2C0 = arg2;
            D_800D2132 = D_800CC382;
            break;
        case 3:
            if (D_800BE616 == 0) {
                D_800BE615 = 4;
                func_15016680();
            }
            break;
        case 5:
            D_800BE9F4 = 5;
            D_800BE615 = 1;
            break;
        case 0:
            break;
    }
}
