#include "types.h"

/*
 * Reviewed source unit: src/game/game_E3900.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B66DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516972C(u8 *);

void func_150B6450(s32 arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4A) {
        func_1516972C((u8 *)arg0);
    }
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} GameE3900Vector;

typedef struct {
    GameE3900Vector position;
    f32 fieldC;
    u8 field10;
    u8 pad11[3];
    f32 field14;
    f32 field18;
    u8 field1C;
    u8 pad1D[3];
    f32 field20;
    u8 field24;
    u8 pad25;
    s16 field26;
    f32 field28;
    f32 field2C;
    u8 field30;
    u8 field31;
    u8 field32;
    u8 field33;
    u8 field34;
    u8 field35;
    s16 field36;
    u8 field38;
    u8 pad39[3];
    f32 field3C;
} GameE3900Spawn;

f32 func_151423D8(u8);
void func_15143794(s16, s16, f32, void *);
void *func_150B3F5C(GameE3900Spawn *, GameE3900Vector *, s16);
extern GameE3900Vector D_8009FC3C[];
extern f32 D_8009FC60[], D_8009FC6C[], D_8009FC78[];
extern s16 D_8009FC84[];
extern s16 D_8009FC8E[][2];
extern f32 D_8009FCCC, D_8009FCD0, D_8009FCD4;
extern f32 D_8009FCD8, D_8009FCDC, D_8009FCE0, D_8009FCE4;

void func_150B648C(u8 arg0) {
    GameE3900Spawn spawn;
    GameE3900Vector position;
    if (arg0 == 0) {
        spawn.position.x = func_151423D8(0xAA) * 10.0f;
        spawn.position.y = 3.0f;
        spawn.position.z = func_151423D8(0xEA) * 10.0f;
        position.x = D_8009FCCC - func_151423D8(0xAA) * 150.0f;
        position.y = D_8009FCD0;
        position.z = D_8009FCD4 - func_151423D8(0xEA) * 150.0f;
    } else if (arg0 == 1) {
        func_15143794(-0x45, 0x1C, 9.349999f, &spawn.position);
        position = D_8009FC3C[arg0];
    } else {
        func_15143794(0x18, 0xF, 9.349999f, &spawn.position);
        position = D_8009FC3C[arg0];
    }
    spawn.field10 = 4;
    spawn.field1C = 6;
    spawn.fieldC = D_8009FC60[arg0];
    spawn.field24 = 0x80;
    spawn.field26 = 0xFF;
    spawn.field30 = 2;
    spawn.field31 = 5;
    spawn.field32 = 5;
    spawn.field33 = 0x33;
    spawn.field34 = 3;
    spawn.field35 = 0x55;
    spawn.field38 = 0;
    spawn.field14 = D_8009FCD8;
    spawn.field18 = D_8009FCDC;
    spawn.field20 = D_8009FCE0;
    spawn.field28 = D_8009FC6C[arg0];
    spawn.field2C = D_8009FC78[arg0];
    spawn.field36 = D_8009FC84[arg0];
    spawn.field3C = D_8009FCE4;
    func_150B3F5C(&spawn, &position, D_8009FC8E[arg0][0]);
}

typedef struct {
    u8 pad0[0x68];
    u8 mode;
} GameE3900Input;

typedef struct {
    u8 pad0[9];
    u8 enabled;
    u8 padA[0x25];
    u8 duration;
} GameE3900Output;

typedef struct {
    u8 pad0[0x14];
    GameE3900Output *output;
    GameE3900Input *input;
} GameE3900State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B66DC CURRENT (205) */
s32 func_150B66DC(GameE3900State *arg0) {
    s32 mode;

    mode = arg0->input->mode - 0xF;
    switch (mode) {
    case 0:
        arg0->output->enabled = 1;
        break;
    case 1:
        arg0->output->enabled = 0;
        arg0->output->duration = 0x14;
        break;
    default:
    case 2:
        arg0->output->enabled = 0;
        arg0->output->duration = 0x28;
        break;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B66DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3900/func_150B66DC.s")
u32 func_150ADA20(void);
void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);

void func_150B6754(u8 arg0, s32 arg1) {
    struct {
        u32 value;
        u32 padding;
    } sp28;

    sp28.value = func_150ADA20();
    func_15182670(0xCC, 0xCC, 0xFF, ((sp28.value % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 11U) + 0xF, 0, (s32) arg0, arg1);
}
