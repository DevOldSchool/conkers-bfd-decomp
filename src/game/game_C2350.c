#include "types.h"
#include <PR/gbi.h>

/*
 * Reviewed source unit: src/game/game_C2350.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_render_effect_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509563C
 * - func_15095B08
 * - func_15095D34
 * - func_1509629C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150A7A48(void *, void *, void *);
void func_151EFEB8(void *, s32);
extern u8 D_800BE9C0;
extern s32 D_800BE628;
extern u8 *D_800DC2A0[];
extern u8 D_800D2CA8[];

void func_15094EA0(s32 arg0) {
    u8 sp58[0x40];
    u8 sp18[0x40];

    func_151EFEB8(sp58, (s32)(D_800DC2A0[D_800BE9C0] + (arg0 << 6)));
    func_151EFEB8(sp18, (s32)((u8 *)D_800BE628 + (arg0 * 0x180) + (D_800BE9C0 << 6) + 0x100));
    func_150A7A48(sp58, sp18, D_800D2CA8 + arg0 * 0x40);
}
extern s32 D_800873D0;
extern u32 D_800D2CA0;

typedef struct GameC2350Command {
    u32 w0;
    u32 w1;
} GameC2350Command;

GameC2350Command *func_15094F40(GameC2350Command *arg0) {
    { GameC2350Command *command = arg0++; command->w0 = 0xDE000000; command->w1 = (u32)&D_800873D0; }
    D_800D2CA0 = 0;
    return arg0;
}
struct GameC2350Input;
struct GameC2350Output;
struct GameC2350Owner;

void func_15095060(struct GameC2350Input *, s32, struct GameC2350Owner *);
s32 func_150950D4(Gfx *, struct GameC2350Output *, s32, s32, s32, s32, s32, s32, s32, s32);
extern struct GameC2350Output D_800D2C90;

s32 func_15094F70(s32 arg0, struct GameC2350Input *arg1, s32 arg2, struct GameC2350Owner *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095060(arg1, arg2, arg3);
    return func_150950D4((Gfx *)arg0, &D_800D2C90, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}
s32 func_15094FE8(s32 arg0, struct GameC2350Input *arg1, s32 arg2, struct GameC2350Owner *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    func_15095060(arg1, arg2, arg3);
    return func_150950D4((Gfx *)arg0, &D_800D2C90, arg4, arg5, 0, arg6, arg7, arg8, arg9, arg10);
}

typedef struct GameC2350Input {
    u32 data;
    u8 field_4;
    u8 pad5;
    u16 field_6;
    u16 field_8;
    u8 field_A;
    u8 field_B;
} GameC2350Input;

typedef struct GameC2350Output {
    u32 data;
    u16 field_4;
    u16 field_6;
    u8 field_8;
    u8 field_9;
    u8 field_A;
} GameC2350Output;

typedef struct GameC2350Owner {
    u8 pad0[0x10];
    GameC2350Output *field_10;
} GameC2350Owner;

extern GameC2350Output D_800D2C90;

void func_15095060(GameC2350Input *arg0, s32 arg1, GameC2350Owner *arg2) {
    u32 data;

    if (arg2 != 0) {
        arg2->field_10 = &D_800D2C90;
    }
    data = arg0->data;
    if (data < 0x10000000U) {
        D_800D2C90.data = data;
    } else {
        D_800D2C90.data = ((u32 *)data)[arg1 >> 8];
    }
    D_800D2C90.field_4 = arg0->field_6;
    D_800D2C90.field_6 = arg0->field_8;
    D_800D2C90.field_8 = arg0->field_A;
    D_800D2C90.field_9 = arg0->field_B;
    D_800D2C90.field_A = arg0->field_4;
}
#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
/* Call context: func_1510D0EC: unique active project prototype */
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_8009DEB0[];
extern u8 D_8009DEB4[];
extern u8 D_8009DEB8[];
extern u8 D_8009DEBC[];
extern s32 D_800D2C9C;

s32 func_150950D4(Gfx *arg0, GameC2350Output *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 width;
    s32 size;
    s32 masks;
    s32 maskt;
    s32 i;
    s32 fmt;

    if (arg1->field_A == 0) {
        arg4 = 0;
    }
    size = D_8009DEB0[arg1->field_9] + arg1->field_4 * arg1->field_6;
    if (arg1->field_8 == 5) {
        size += (arg1->field_4 * arg1->field_6) / 4;
    }
    size >>= D_8009DEB4[arg1->field_9];
    D_800D2CA0 = arg1->data;
    if (D_800D2CA0 < 0x10000000U) {
        D_800D2CA0 = func_1510D0EC(D_800D2CA0, NULL, arg9, 0);
    }
    if (D_800D2CA0 != 0x80000000) {
        D_800D2CA0 += (size + size) * arg4;
    }
    if (arg1->field_9 == 0) {
        width = arg1->field_4 >> 1;
    } else {
        width = arg1->field_4;
    }
    masks = 1;
    for (i = 2; i < arg1->field_4; i *= 2) {
        masks++;
    }
    maskt = 1;
    for (i = 2; i < arg1->field_6; i *= 2) {
        maskt++;
    }
    if (arg1->field_8 != 5) {
        fmt = arg1->field_8;
    } else {
        fmt = 0;
    }
    gDPPipeSync(arg0++);
    gDPSetTextureImage(arg0++, fmt, D_8009DEBC[arg1->field_9], 1, D_800D2CA0);
    gDPSetTile(arg0++, fmt, D_8009DEBC[arg1->field_9], 0, arg2, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadBlock(arg0++, G_TX_LOADTILE, 0, 0, size - 1, 0);
    gDPSetTile(arg0++, fmt, arg1->field_9, ((D_8009DEB8[arg1->field_9] * width) + 7) >> 3, arg2, arg3, 0, arg6, maskt, 0, arg6, masks, 0);
    gDPSetTileSize(arg0++, arg3, (arg7 << 2) + arg5, arg8 << 2, ((arg1->field_4 + arg7 - 1) << 2) + arg5, (arg1->field_6 + arg8 - 1) << 2);
    if (arg1->field_8 == 5) {
        gDPSetTile(arg0++, G_IM_FMT_I, G_IM_SIZ_4b, ((D_8009DEB8[G_IM_SIZ_4b] * (width >> 1)) + 7) >> 3, arg2 + (width * arg1->field_6) / 4, arg3 + 1, 0, arg6, maskt, 0, arg6, masks, 0);
        gDPSetTileSize(arg0++, arg3 + 1, (arg7 << 2) + arg5, arg8, ((arg1->field_4 + arg7 - 1) << 2) + arg5, (arg1->field_6 + arg8 - 1) << 2);
    }
    if (arg1->field_8 == 2) {
        s32 bits;
        s32 count;

        if (arg1->field_9 == 0) {
            bits = 4;
            count = 0xF;
        } else {
            bits = 8;
            count = 0xFF;
        }
        gDPSetTextureImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_800D2CA0 + (arg1->field_4 * arg1->field_6 * bits) / 8);
        gDPLoadSync(arg0++);
        gDPLoadTLUTCmd(arg0++, G_TX_LOADTILE - 1, count);
        D_800D2C9C = 0x8000;
    } else {
        D_800D2C9C = 0;
    }
    return (s32)arg0;
}
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern s32 D_80082FA4;
extern f32 D_800D9B20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509563C CURRENT (800) */
s32 func_1509563C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4,
                  f32 *arg5, f32 *arg6, f32 arg7) {
    u8 *temp_v1;

    func_150A7A00((void *)((u32)D_800D2CA8 + ((u32)D_80082FA4 << 6)), arg0, arg1, arg2,
                  arg3, arg4, arg5, arg6);
    arg1 = *arg6;
    if ((arg7 <= arg1) || (arg1 <= D_800D9B20)) {
        return 0;
    }
    arg0 = 1.0f / arg1;
    temp_v1 = (u8 *)((u32)D_800BE628 + (u32)D_80082FA4 * 0x180U);
    arg2 = ((*(f32 *)(temp_v1 + 0xC) + 5.0f) * *arg3 * arg0) +
            *(f32 *)(temp_v1 + 0x34);
    arg1 = *(f32 *)(temp_v1 + 0x38) -
            ((*(f32 *)(temp_v1 + 0x10) + 5.0f) * *arg4 * arg0);
    *arg3 = arg2;
    *arg4 = arg1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509563C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C2350/func_1509563C.s")
s32 func_1509563C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);
s32 func_15095A90(s32, void *, f32, f32, f32, s32, s32, s32, s32);

typedef struct GameC2350Viewport {
    s16 scale[4];
    s16 translate[4];
} GameC2350Viewport;

typedef struct GameC2350Record {
    u8 pad0[0x40];
    GameC2350Viewport viewports[12];
    u8 matrices[2][0x40];
} GameC2350Record;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
GameC2350Command *func_15095760(GameC2350Command *arg0, s16 *input) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (func_1509563C((f32)input[0], (f32)input[1], (f32)input[2],
                      &sp44, &sp40, &sp3C, &sp38, 4000.0f) == 0) {
        return arg0;
    }
    { GameC2350Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    { GameC2350Command *command = arg0++; command->w0 = _SHIFTL(0xEE, 24, 8); command->w1 = _SHIFTL((s32)((sp3C / sp38 * ((GameC2350Record *)D_800BE628)[D_80082FA4].viewports[D_800BE9C0].scale[2] + ((GameC2350Record *)D_800BE628)[D_80082FA4].viewports[D_800BE9C0].translate[2]) * 32.0f), 16, 16) | _SHIFTL(0, 0, 16); }
    return (GameC2350Command *)func_15095A90((s32)arg0, input, sp44, sp40, sp38, 1, 0, 0, 0);
}
s32 func_1509563C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32); /* extern */
void func_15095B08(void *, f32, f32, f32, s32, s32 *);

GameC2350Command *func_150958B0(GameC2350Command *arg0, s16 *arg1, s32 *arg2) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    if (func_1509563C((f32)arg1[0], (f32)arg1[1], (f32)arg1[2], &sp44, &sp40, &sp3C, &sp38, 4000.0f) == 0) {
        *arg2 = 0;
        return arg0;
    }
    func_15095B08(arg1, sp44, sp40, sp38, 1, arg2);
    if (*arg2 != 0) {
        { GameC2350Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
        { GameC2350Command *command = arg0++; command->w0 = _SHIFTL(0xEE, 24, 8); command->w1 = _SHIFTL(sp3C / sp38 * 16352.0f + 16352.0f, 16, 16) | _SHIFTL(0, 0, 16); }
    }
    return arg0;
}
s32 func_15095A48(s32 arg0, void *arg1, f32 arg2, f32 arg3) {
    return func_15095A90(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}
s32 func_15095D34(s32, void *, s32, s32, s32);      /* extern */

s32 func_15095A90(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;

    func_15095B08(arg1, arg2, arg3, arg4, arg5, &sp24);
    if (sp24 != 0) {
        arg0 = func_15095D34(arg0, arg1, arg6, arg7, arg8);
    }
    return arg0;
}
extern f32 D_800380A0;
extern f32 D_800380A4;
extern s32 D_80082FA4;
extern s32 D_800BE628;
extern f32 D_800D2C70;
extern f32 D_800D2C74;
extern f32 D_800D2C78;
extern f32 D_800D2C7C;
extern f32 D_800D2C80;
extern f32 D_800D2C84;
extern f32 D_800D2C88;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15095B08 CURRENT (2690) */
void func_15095B08(void *arg0, register f32 arg1, register f32 arg2, register f32 arg3, s32 arg4, s32 *arg5) {
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;
    u32 temp_t3;
    u32 temp_t4;
    void *temp_v1_2;
    void *var_v0;

    *arg5 = 0;
    temp_v0 = *(s16 *)((u8 *)arg0 + 6);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 8);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v0 * D_800380A0;
            temp_fv1 = (f32) temp_v1 * D_800380A4;
            if (arg4 != 0) {
                var_v0 = (u8 *)D_800BE628 + (D_80082FA4 * 0x180);
                temp_fv0 = temp_fv0 * *(f32 *)((u8 *)var_v0 + 0x1C);
                temp_fv1 = temp_fv1 * *(f32 *)((u8 *)var_v0 + 0x20);
            } else {
                var_v0 = (u8 *)D_800BE628 + (D_80082FA4 * 0x180);
                temp_fv0 = temp_fv0 * *(f32 *)((u8 *)var_v0 + 0x14);
                temp_fv1 = temp_fv1 * *(f32 *)((u8 *)var_v0 + 0x18);
            }
            temp_v1_2 = *(void **)((u8 *)arg0 + 0x10);
            temp_t3 = *(u16 *)((u8 *)temp_v1_2 + 4);
            temp_fa1 = 1.0f / arg3;
            temp_t4 = *(u16 *)((u8 *)temp_v1_2 + 6);
            temp_ft4 = temp_fv0 * ((f32)temp_t3) * temp_fa1;
            temp_ft5 = ((f32)temp_t4) * temp_fv1 * temp_fa1;
            arg1 = arg1 - (temp_ft4 * 0.5f);
            arg2 = arg2 - (temp_ft5 * 0.5f);
            if ((*(f32 *)((u8 *)var_v0 + 0x2C) <= (arg1 + temp_ft4)) && (arg1 < *(f32 *)((u8 *)var_v0 + 0x30)) && (*(f32 *)((u8 *)var_v0 + 0x24) <= (arg2 + temp_ft5)) && (arg2 < *(f32 *)((u8 *)var_v0 + 0x28))) {
                *arg5 = 1;
            }
            D_800D2C70 = temp_fv0;
            D_800D2C74 = temp_fv1;
            D_800D2C78 = arg1;
            D_800D2C7C = arg2;
            D_800D2C80 = arg3;
            D_800D2C84 = temp_ft4;
            D_800D2C88 = temp_ft5;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15095B08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C2350/func_15095B08.s")
void func_15095D0C(s32 arg0, void *arg1) {
    func_15095D34(arg0, arg1, 0, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C2350/func_15095D34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C2350/func_1509629C.s")
extern s32 D_80087408;
extern s8 D_800D2DAB;

GameC2350Command *func_15096934(GameC2350Command *arg0) {
    { GameC2350Command *command = arg0++; command->w0 = 0xDE000000; command->w1 = (u32)&D_80087408; }
    D_800D2DAB = 0;
    return arg0;
}
