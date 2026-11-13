#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include "PR/mbi.h"
#include "game_functions.h"
#include "game_render_view.h"

/*
 * Reviewed source unit: src/game/game_138B40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 */


typedef struct {
    u32 words[0x10];
} Game138B40Work;

void func_150A7A48(void *, void *, void *);
void func_151EFEB8(void *, s32);
void func_1501B22C(s32);

extern s32 D_80082FA0;
extern u8 D_800BE9C0;
extern u8 D_800D9C10[];
extern u8 D_800D9D10[];
extern u8 *D_800DC2A0[];

void func_1510B690(void) {
    s16 i;
    Game138B40Work sp4C;

    for (i = 0; i <= D_80082FA0; i++) {
        func_151EFEB8(&sp4C, (s32)&D_800BE628[i].matrices[D_800BE9C0]);
        func_151EFEB8(D_800D9C10 + (i << 6), (s32)(D_800DC2A0[D_800BE9C0] + i * 64));
        func_150A7A48(D_800D9C10 + (i << 6), &sp4C, D_800D9D10 + (i << 6));
        func_1501B22C(i);
    }
}
extern u8 D_80089470[];

typedef struct Game138B40Command {
    u32 word0;
    u32 word1;
} Game138B40Command;

Game138B40Command *func_1510B7B4(Game138B40Command *arg0, s32 arg1) {
    { Game138B40Command *command = arg0++; command->word0 = 0xE7000000; command->word1 = 0; }
    { Game138B40Command *command = arg0++; command->word0 = 0xF9000000; command->word1 = 1; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380003; command->word1 = (s32)D_80089470; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB0E0000; command->word1 = D_800BE628[arg1].normalization; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB040004; command->word1 = 3; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB04000C; command->word1 = 3; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB040014; command->word1 = 0xFFFD; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDB04001C; command->word1 = 0xFFFD; }
    { Game138B40Command *command = arg0++; command->word0 = 0xD9EFFFFF; command->word1 = 0; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380007; command->word1 = (s32)&D_800BE628[arg1].matrices[D_800BE9C0]; }
    { Game138B40Command *command = arg0++; command->word0 = 0xDA380005; command->word1 = (s32)(D_800DC2A0[D_800BE9C0] + (arg1 << 6)); }
    { Game138B40Command *command = arg0++; command->word0 = 0xEF082C3F; command->word1 = 0x552230; }
    return arg0;
}
extern f32 D_800D35E0, D_800D35E4;

void func_1510B958(s32 arg0) {
    GameRenderView *record;

    record = (GameRenderView *)((u8 *)D_800BE628 + arg0 * 0x180);
    D_800D35E0 = (((record->value_x / record->scale_x) - 1.0f) * -1.0f) + record->base_x;
    D_800D35E4 = (((record->value_y / record->scale_y) - 1.0f) * -1.0f) + record->base_y;
}
extern u8 *D_800DBFF0;
extern u8 D_800BEBA0;
extern u8 D_800C35EA;
extern u8 D_800C3662;
extern u16 D_800D18A0;
extern LookAt D_800D9B90[];
extern s32 D_800BE9F0;
extern s32 D_800DCD7C;
extern u8 D_800D9BD0[][2][8];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9E21;
extern u8 D_800D9E28[];
extern u8 D_800BEAAA;
extern u8 D_800DBE62;
extern Gfx *D_800B0E00;
extern Gfx *D_800B0E04;
extern Gfx *D_800B0E08;

void func_1510CB10(s32);
Gfx *func_1510CDB8(Gfx *, s32, s32, s32);
Gfx *func_151733D8(Gfx *, s32);
Gfx *func_150C8600(Gfx *);
Gfx *func_15100464(Gfx *);
Gfx *func_150DFBD0(Gfx *);
Gfx *func_150CF5E8(Gfx *);
Gfx *func_150D765C(Gfx *);
void func_1510F800(s32);
s32 func_1515D914(s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
Gfx *func_150A5378(Gfx *, Gfx *, u8 *, s32, s32, s32);
Gfx *func_150A50C0(Gfx *, Gfx *, u8 *, s32, s32, s32);
Gfx *func_1512E5F0(Gfx *, u8 *);
u32 *func_1515E544(u32 *, s32, u8, u8, s32);
Gfx *func_151742EC(Gfx *, s16);

Gfx *func_1510B9D0(Gfx *gdl, s16 arg1) {
    u8 *player;
    s32 skip;

    player = D_800DBFF0 + arg1 * 0x9A0;
    D_800BEBA0 = 1;
    skip = 0;
    if (D_800C35EA == 1 && D_800C3662 != 0) {
        skip = 1;
    }
    if (D_800D18A0 & (1 << arg1)) {
        skip = 1;
    }
    gdl = (Gfx *)func_1510B7B4((Game138B40Command *)gdl, arg1);
    gSPLookAtX(gdl++, &D_800D9B90[D_800BE9C0].l[0]);
    gSPLight(gdl++, &D_800D9B90[D_800BE9C0].l[1], 1);
    func_1510CB10(arg1);
    gdl = func_1510CDB8(gdl, 0xFF, 0xFF, arg1);
    gdl = func_151733D8(gdl, 1);
    gSPMatrix(gdl++, D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    if (skip == 0) {
        switch (D_800BE9F0) {
        case 0x14:
            gdl = func_150C8600(gdl);
            break;
        case 0x1A:
            gdl = func_15100464(gdl);
            break;
        case 0x13:
            gdl = func_150DFBD0(gdl);
            break;
        case 0x35:
            gdl = func_150CF5E8(gdl);
            break;
        case 0x33:
            gdl = func_150D765C(gdl);
            break;
        }
    }
    func_1510F800(0);
    if (D_800DCD7C == 0) {
        gDma2p(gdl++, G_MOVEMEM, D_800D9BD0[arg1][D_800BE9C0], 48, G_MV_LIGHT, G_MVO_L2);
    }
    gdl = (Gfx *)func_1515D914((s32)gdl, arg1, (s32)*(f32 *)(D_800DBFF0 + 0x2F8 + arg1 * 0x9A0),
                               (s32)*(f32 *)(D_800DBFF0 + 0x2FC + arg1 * 0x9A0),
                               (s32)*(f32 *)(D_800DBFF0 + 0x300 + arg1 * 0x9A0), 0, D_800D9E10[arg1], D_800D9E20,
                               (s32)D_800D9BD0[arg1][D_800BE9C0], &D_800D9E21, 1, 0, 0x25, (s32)D_800D9E28);
    if (skip == 0) {
        if (D_800BE9F0 != 5) {
            if (D_800BEAAA != 0) {
                gDPPipeSync(gdl++);
                if (D_800DBE62 != 0) {
                    if (D_800BE9F0 != 0x14 && D_800BE9F0 != 0x33 && D_800BE9F0 != 0x32) {
                        gdl = func_150A5378(D_800B0E00, gdl, D_800D9C10 + arg1 * 64, 0, 0, 1 << arg1);
                    } else {
                        gSPDisplayList(gdl++, D_800B0E00);
                    }
                    if (D_800B0E04 != NULL) {
                        gDPPipeSync(gdl++);
                        gdl = func_1510CDB8(gdl, 0xFF, 0xFF, arg1);
                        gdl = func_151733D8(gdl, 1);
                        if (D_800BE9F0 == 0x35) {
                            gdl = func_150CF5E8(gdl);
                        }
                        gSPDisplayList(gdl++, D_800B0E04);
                    }
                    D_800BEBA0 = 0;
                    if (player[0x8B8] != 0 && (*(s32 *)(player + 0x84) & 8)) {
                        gdl = func_1512E5F0(gdl, player);
                        gDPPipeSync(gdl++);
                    }
                } else {
                    gSPDisplayList(gdl++, D_800B0E00);
                }
            } else if (D_800BEAAA != 0) {
                gdl = func_150A50C0(D_800B0E00, gdl, D_800D9C10 + arg1 * 64, 0, 0, 0);
            } else {
                gSPDisplayList(gdl++, D_800B0E00);
            }
        }
        gdl = (Gfx *)func_1515E544((u32 *)gdl, D_800D9E10[arg1], D_800D9E20, D_800D9E21, (s32)D_800D9BD0[arg1][D_800BE9C0]);
        if (D_800B0E08 != NULL) {
            gDPPipeSync(gdl++);
            gdl = func_1510CDB8(gdl, 0xFF, 0xFF, arg1);
            gSPDisplayList(gdl++, D_800B0E08);
        }
    }
    gdl = func_151742EC(gdl, arg1);
    gDPPipeSync(gdl++);
    return gdl;
}
