#include "types.h"

/*
 * Reviewed source unit: src/game/game_447B0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_next_compact_units.md
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2138[];

/* Call context: func_100226F0: unique active declaration in the allowed source */
/* Call context: func_1501748C: unique active declaration in the allowed source */
/* Call context: func_15085710: unique active project prototype */
void func_1501748C(s16);
void func_15085710(s16, s32, s32);
extern s8 D_80087260;
extern s8 D_80087264;
extern s8 D_8008726C;
extern s8 D_80087270[];
extern u8 D_800BE616;
extern s16 D_800D2132;
extern s16 D_800D2340;
extern u8 D_800D2456;
extern u8 D_800D2457;

void func_15017300(s16 arg0, s16 arg1) {
    s32 i;
    s32 *state = (s32 *)D_800D2138;

    func_100226F0(state, 0x20C);
    *state = arg0;
    for (i = 0; i < 16; i++) {
        if ((1 << i) & arg1) {
            func_15085710(i, 0, D_80087270[i]);
            D_800D2457 = D_800D2456 = 6;
            func_15085710(i, 5, D_8008726C);
            func_15085710(i, 2, D_80087260);
            if (D_800BE616 != 0) {
                func_15085710(i, 9, D_80087264);
            }
        }
        func_1501748C(arg1);
    }
    D_800D2340 = arg1;
    D_800D2132 = 0;
}
void func_1501748C(s16 arg0) {

}
void func_15017498(void) {
    func_100226F0(D_800D2138, 0x20C);
}
extern u32 D_80087380;
extern void *D_800D23C0;

typedef struct Game447B0Record {
    u16 unk0;
    u16 count;
    s32 unk4;
    u16 entries[8];
} Game447B0Record;

void func_150174C0(s32 arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < (s32)D_80087380; i++) {
        for (j = 0; j < ((Game447B0Record *)D_800D23C0)[i].count; j++) {
            if ((((Game447B0Record *)D_800D23C0)[i].entries[j] >> 12) == 2) {
                ((Game447B0Record *)D_800D23C0)[i].entries[j] += arg0;
            }
        }
    }
}
void *func_1502B5C8(u32 *, s32, ...);
void func_150174C0(s32);
extern u32 D_80087380;
extern void *D_800D23C0;
extern u8 D_800DBF00;

void func_15017578(s32 arg0) {
    u32 sp24;

    sp24 = 0;
    D_800D23C0 = func_1502B5C8(&sp24, 3, 0xC, arg0, 4);
    D_80087380 = sp24 / 24U;
    func_150174C0(D_800DBF00);
}
