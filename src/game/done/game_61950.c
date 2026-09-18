#include "types.h"

/*
 * Reviewed source unit: src/game/game_61950.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 */

typedef struct Game61950Matrix {
    f32 values[16];
} Game61950Matrix;

typedef struct Game61950Actor {
    s32 field_0;
    u8 kind;
    u8 mode;
    u8 pad6[0x96];
    s32 field_9C;
    u8 padA0[0x134];
    Game61950Matrix *matrices;
    u8 pad1D8[0x10C];
    s16 field_2E4;
    s16 field_2E6;
    u8 pad2E8[0x44];
} Game61950Actor;

extern Game61950Actor D_800CC2D0[];
extern u8 D_800CC2D4[];
void func_1503B9BC(void);

s16 *func_150344A0(s16 *arg0, s32 arg1) {
    s32 value;

    arg0[0] = 0x12;
    value = D_800CC2D0[arg1].field_2E6;
    arg0[1] = value * 3.640889f;
    arg0[2] = 0xE;
    value = -D_800CC2D0[arg1].field_2E4;
    arg0[3] = value * 3.640889f;
    return arg0 + 4;
}
void func_1503453C(s32 arg0) {
    if ((s32) D_800CC2D4[arg0 * 0x32C] >= 0x81) {
        if (D_800CC2D4[arg0 * 0x32C] != 0xB0) {
            return;
        }
        goto block_8;
    }
    if ((s32) D_800CC2D4[arg0 * 0x32C] >= 5) {
        if (D_800CC2D4[arg0 * 0x32C] != 0x80) {
            return;
        }
        goto block_8;
    }
    switch (D_800CC2D4[arg0 * 0x32C]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
block_8:
        func_1503B9BC();
    }
}
void func_15034EB4(void *, s32, s32);
void func_150DFDA4(void *);
void func_150F1A00(void *);
void func_15036310(s32, s32, s32, s32);
extern u8 D_800BE616;

void func_150345E4(s32 arg0) {
    if (D_800CC2D0[arg0].matrices != 0) {
        if (D_800CC2D0[arg0].field_0 == 1 || D_800CC2D0[arg0].mode == 7) {
            func_1503453C(arg0);
        }
        if (D_800CC2D0[arg0].field_0 == 0x22) {
            func_1503453C(arg0);
        }
        switch (D_800CC2D0[arg0].kind) {
        case 4:
            if (D_800BE616 == 0) {
                func_15036310(0, arg0, 9, 0);
                func_15036310(0, arg0, 4, 0);
                return;
            }
            break;
        case 0x70:
            func_15034EB4(&D_800CC2D0[arg0], 10, 11);
            return;
        case 0x7B:
            func_150F1A00(&D_800CC2D0[arg0]);
            return;
        case 0x60:
            func_150DFDA4(&D_800CC2D0[arg0]);
            break;
        }
    }
}
s32 func_1502DB20(u8);                              /* extern */

void func_15034728(Game61950Actor *arg0) {
    s32 count;
    s32 i;
    s32 row;
    s32 column;
    Game61950Matrix *matrices;
    u8 *matrix;

    if (arg0->matrices != 0 && arg0->field_9C != 0) {
        count = func_1502DB20(arg0->kind) - 1;
        matrices = arg0->matrices;
        i = 31;
        if (count < 31) {
            i = count;
        }
        for (; i >= 0; i--) {
            if (arg0->field_9C & (1U << i)) {
                matrix = (i << 6) + (u8 *)matrices;
                for (row = 0; row < 3; row++) {
                    for (column = 0; column < 3; column++) {
                        *(f32 *)(matrix + (row << 4) + column * 4) = 0.0f;
                    }
                }
            }
        }
    }
}
extern u8 D_800BEAC0;
extern Game61950Actor D_800D121C;

void func_150347E8(void) {
    Game61950Actor *actor;
    Game61950Actor *end;

    if (D_800BEAC0 == 0) {
        actor = D_800CC2D0;
        end = &D_800D121C;
        do {
            if ((actor->field_0 != 0) && (actor->field_9C != 0)) {
                func_15034728(actor);
            }
            actor++;
        } while (actor != end);
    }
}
