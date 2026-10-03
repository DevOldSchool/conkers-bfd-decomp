#include "types.h"

/*
 * Reviewed source unit: src/game/entrypoint.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 */

void func_10023790(void *, void *, s32);
void func_100050A0(void *);
void func_100051E8(void);
void func_10008180(void);
void func_15000000(void);
void func_15003570(void);
void func_150061B0(void);
void func_15006234(void);
void func_15007A20(void);
void func_15007A70(s16, s16, s16);
void func_15007B3C(void);
void func_15008A60(void);
void func_15015920(s16);
void func_15016588(void);
void func_15017498(void);
void func_150186D0(void);
void func_15042D50(void);
void func_1509C120(void);
void func_150ADACC(s32);
void func_151DD970(void);
void func_151E50C8(void);
void func_151EEFF0(void);

extern u8 D_800BE615;
extern s8 D_800BE617;
extern s32 D_800BE9E8;
extern s32 D_800BE9F4;
extern s32 D_800BEA00;
extern s32 D_800BEA04;
extern u8 D_800BEA10[];
extern u8 D_800BEA28[];
extern s16 D_800BEA68[];
extern s16 D_800BEAA8;
extern u8 D_800BEAAA;
extern s8 D_800BEAAB;
extern s32 D_800D2C28;
extern u8 D_800E0B94;

void func_15007830(void) {
    func_15007A20();
    D_800D2C28 = 0;
    func_10023790(D_800BEA10, D_800BEA28, 0x10);
    D_800BEA68[0] = 2;
    D_800BEA68[16] = 2;
    D_800BE617 = 0;
    func_100050A0(D_800BEA10);
    func_15003570();
    D_800BEAAB = 0;
    func_10008180();
    func_15000000();
    func_15016588();
    func_151EEFF0();
    D_800BEAA8 = 0;
    func_150061B0();
    func_15006234();
    func_151DD970();
    func_15015920(0);
    func_15008A60();
    func_15042D50();
    D_800BE615 = 5;
    D_800BEA04 = 0;
    D_800BEA00 = 1;
    D_800BEAAA = 1;
    func_1509C120();
    while (1) {
        switch (D_800BE615) {
        case 1:
        case 5:
            func_151E50C8();
            /* fallthrough */
        case 2:
            func_15017498();
            if (D_800E0B94 == 2) {
                func_150ADACC(0x81280783);
            }
            func_15007A70(((s16 *)&D_800BEA04)[1], ((s16 *)&D_800BEA00)[1], ((s16 *)&D_800BE9F4)[1]);
            /* fallthrough */
        case 3:
            func_15007B3C();
            D_800BE615 = 0;
            break;
        case 4:
            break;
        }
        func_100051E8();
        D_800BE9E8 = 0;
        func_150186D0();
    }
}
