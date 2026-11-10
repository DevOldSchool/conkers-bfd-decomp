#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B1600.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15184150
 * - func_15184368
 * - func_15184DF0
 * - func_15185F24
 * - func_1518652C
 * - func_15186794
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game184150Matrix {
    f32 values[16];
} Game184150Matrix;

typedef struct Game184DF0Actor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x103];
    u8 field_123;
    u8 pad124[3];
    u8 field_127;
    u8 pad128[0x24];
    f32 scaleXZ;
    f32 scaleY;
    u8 pad154[0x74];
    u8 field_1C8;
    u8 pad1C9[0xB];
    Game184150Matrix *matrices;
    u8 pad1D8[0x154];
} Game184DF0Actor;

extern Game184DF0Actor D_800CC2D0[];
extern u8 D_800C3E90;
extern u8 *D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15184150 CURRENT (1794) */
void func_15184150(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 kind;
    Game184DF0Actor *actor;
    Game184150Matrix *matrix;
    u8 *model;
    s32 count;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 radius;

    actor = &D_800CC2D0[arg0];
    kind = actor->pad0[4];
    *arg3 = 0.0f;
    *arg2 = 0.0f;
    *arg1 = 0.0f;
    if (actor->matrices == 0 || D_800C3E90 != 0) {
        return;
    }
    count = func_1502DB20(kind);
    for (i = 0; i < count * 0x40; i += 0x40) {
        matrix = (Game184150Matrix *) ((u8 *) actor->matrices + i);
        x = matrix->values[12] - actor->x;
        y = matrix->values[13] - actor->y;
        z = matrix->values[14] - actor->z;
        if (x < 0.0f) {
            x = -x;
        }
        if (*arg1 < x) {
            *arg1 = x;
        }
        if (y < 0.0f) {
            y = -y;
        }
        if (*arg2 < y) {
            *arg2 = y;
        }
        if (z < 0.0f) {
            z = -z;
        }
        if (*arg3 < z) {
            *arg3 = z;
        }
    }
    if (*arg1 == 0.0f || *arg2 == 0.0f || *arg3 == 0.0f) {
        radius = actor->scaleXZ * (f32) *(s16 *)(D_800D1C90[actor->pad0[4]] + 0x1A);
        *arg3 = radius;
        *arg1 = radius;
        model = D_800D1C90[actor->pad0[4]];
        *arg2 = actor->scaleY * (f32) (*(s16 *)(model + 0x1E) + *(s16 *)(model + 0x1C));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15184150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184150.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184368.s")

typedef struct Game184DF0Camera {
    u8 pad0[0x2F8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad304[0x69C];
} Game184DF0Camera;

s32 func_150AD9A0(s32, s32, s32);
void func_15184150(s32, f32 *, f32 *, f32 *);
extern Game184DF0Camera *D_800DBFF0;
extern f32 D_800A7378;
extern f32 D_800D3688;
extern f32 D_800D368C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15184DF0 CURRENT (1458) */
s32 func_15184DF0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    Game184DF0Actor *actor;
    Game184DF0Camera *camera;
    s32 distance;
    s32 dx;
    s32 dy;
    s32 dz;
    f32 scale;

    actor = &D_800CC2D0[arg0];
    camera = &D_800DBFF0[arg1];
    dx = (s32)(actor->x - camera->x);
    dy = (s32)(actor->y - camera->y);
    dz = (s32)(actor->z - camera->z);
    distance = func_150AD9A0(dx, dy, dz);
    if (distance >= 0x7D1) {
        D_800D3688 = 0.0f;
        D_800D368C = D_800D3688;
        return 0;
    }
    func_15184150(arg0, arg2, arg3, arg4);
    scale = D_800A7378;
    *arg2 *= scale;
    *arg3 *= scale;
    *arg4 *= scale;
    if ((*arg2 == 0.0f) || (*arg3 == 0.0f) || (*arg4 == 0.0f)) {
        D_800D3688 = 0.0f;
        D_800D368C = D_800D3688;
        return 0;
    }
    return distance;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15184DF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184DF0.s")
typedef struct Game1B1600Command {
    u32 w0;
    u32 w1;
} Game1B1600Command;

void *func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A680(void *);
void *func_1502CCFC(void *, s32, s32, Game184150Matrix *, s32, s32 *, s32, s32);
void func_1510B7B4(void *, s32);
extern s16 D_80082FA6;
extern u8 D_8008D3E8[];
extern u8 D_8008D448[];
extern u8 D_800BE9C0;
extern s32 D_800DF088;
extern u16 D_800DF0D0[];
extern u8 D_800DF2F8[];
extern u8 D_89470[];

void func_15184FA4(Game1B1600Command *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 count;
    s32 bounds[3];

    if (D_800CC2D0[arg1].field_127 == 0xFF) {
        count = D_800CC2D0[arg1].field_1C8 + 1;
    } else {
        count = D_800CC2D0[arg1].field_1C8;
    }
    { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xFF48003F; command->w1 = D_800DF088; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xDE000000; command->w1 = (u32)D_8008D448; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xDB0E0000; command->w1 = D_800DF0D0[arg2]; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xDC080008; command->w1 = (u32)D_8008D3E8; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xDA380007; command->w1 = (u32)(D_800DF2F8 + (arg2 << 7) + (D_800BE9C0 << 6)); }
    { Game1B1600Command *command = arg0++; command->w0 = 0xDA380003; command->w1 = (u32)D_89470; }
    bounds[0] = bounds[1] = bounds[2] = 0;
    arg0 = func_1502CCFC(arg0, arg1, arg3, D_800CC2D0[arg1].matrices, func_1506196C((u8 *)&D_800CC2D0[arg1], arg3), bounds, 3, 1);
    { Game1B1600Command *command = arg0++; command->w0 = 0xD7000002; command->w1 = 0xFFFFFFFF; }
    { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    if (count < 2) {
        { Game1B1600Command *command = arg0++; command->w0 = 0xFCFFFFFF; command->w1 = 0xFFFCF87C; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xFA000000; command->w1 = 0xFFFFFFFF; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xEF003C3F; command->w1 = 0x0F0A4000; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xFD900000; command->w1 = D_800DF088; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xF5900000; command->w1 = 0x07018060; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xE6000000; command->w1 = 0; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xF3000000; command->w1 = 0x077FF100; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xF5881000; command->w1 = 0x00018060; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xF2000000; command->w1 = 0x000FC0FC; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xE40FC0FC; command->w1 = 0; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xE1000000; command->w1 = 0x00100010; }
        { Game1B1600Command *command = arg0++; command->w0 = 0xF1000000; command->w1 = 0x04000400; }
        if (count == 0) {
            { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xFD900000; command->w1 = D_800DF088; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xF5900000; command->w1 = 0x07018060; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xE6000000; command->w1 = 0; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xF3000000; command->w1 = 0x077FF100; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xF5881000; command->w1 = 0x00018060; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xF2000000; command->w1 = 0x000FC0FC; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xE40FC0FC; command->w1 = 0; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xE1000000; command->w1 = 0x00100010; }
            { Game1B1600Command *command = arg0++; command->w0 = 0xF1000000; command->w1 = 0x04000400; }
        }
        { Game1B1600Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    }
    { Game1B1600Command *command = arg0++; command->w0 = 0xD9FFFFFF; command->w1 = 0x00200001; }
    arg0 = func_1501A680(arg0);
    arg0 = func_1501A490(arg0, D_80082FA6, 0, 0, 0, 0);
    func_1510B7B4(arg0, arg3);
    D_800CC2D0[arg1].field_123 = 1;
}
void *func_15185454(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 4)) /
        ((*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185554(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 4);
}
void *func_1518557C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) + *(f32 *)arg0) /
        ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)arg0 - *(f32 *)arg1));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)arg2;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_1518567C(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 0) < -*(f32 *)((u8 *)arg0 + 8);
}
void *func_151856A8(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 4)) /
        ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 4);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_151857B0(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) < -*(f32 *)((u8 *)arg0 + 8);
}
void *func_151857DC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (*(f32 *)(arg0 + 8) - *(f32 *)arg0) /
        ((*(f32 *)arg1 - *(f32 *)arg0) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = *(f32 *)arg2;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_151858D4(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 0);
}
extern f32 D_800D3688;

void *func_151858FC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (D_800D3688 - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * ratio + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3688;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
extern f32 D_800D3688;

s32 func_151859FC(void *arg0) {
    return D_800D3688 < *(f32 *)((u8 *)arg0 + 8);
}
extern f32 D_800D368C;

void *func_15185A28(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = (D_800D368C - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * ratio + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D368C;
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
extern f32 D_800D368C;

s32 func_15185B28(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 8) < D_800D368C;
}
void *func_15185B54(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = *(f32 *)arg0 / (*(f32 *)arg0 - *(f32 *)arg1);
    *(f32 *)arg2 = 0.0f;
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * ratio + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)) * ratio + *(f32 *)(arg0 + 8);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185C44(f32 *arg0) {
    return *arg0 <= 0.0f;
}
void *func_15185C6C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 ratio;

    ratio = *(f32 *)(arg0 + 4) / (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4));
    *(f32 *)(arg2 + 4) = 0.0f;
    *(f32 *)arg2 = (*(f32 *)arg1 - *(f32 *)arg0) * ratio + *(f32 *)arg0;
    *(f32 *)(arg2 + 8) = (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)) * ratio + *(f32 *)(arg0 + 8);
    *(s16 *)(arg2 + 0xC) = (s32)((f32)(*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * ratio + (f32)*(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s32)((f32)(*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * ratio + (f32)*(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s32)((f32)(*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * ratio + (f32)*(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}
s32 func_15185D5C(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) <= 0.0f;
}
s32 func_15185D84(f32 *arg0) {
    return *arg0 > 0.0f;
}
s32 func_15185DAC(void *arg0) {
    return *(f32 *)((u8 *)arg0 + 4) > 0.0f;
}
typedef struct {
    s32 words[5];
} Game1B1600Record;

extern Game1B1600Record *(*D_8008D498[])(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
extern s32 (*D_8008D4C0[])(Game1B1600Record *);

Game1B1600Record *func_15185DD4(Game1B1600Record *arg0, s32 arg1, s32 arg2,
                                  Game1B1600Record *arg3) {
    s32 (*predicate)(Game1B1600Record *);
    Game1B1600Record *(*combine)(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
    Game1B1600Record *previous;
    Game1B1600Record *current;
    s32 index;

    previous = arg0 + arg1 - 1;
    combine = D_8008D498[arg2];
    predicate = D_8008D4C0[arg2];
    current = arg0;
    index = 0;
    if (arg1 > 0) {
        do {
            if (predicate(current) != 0) {
                if (predicate(previous) != 0) {
                    arg3++;
                    arg3[-1] = *current;
                } else {
                    arg3 = combine(previous, current, arg3);
                    *arg3++ = *current;
                }
            } else if (predicate(previous) != 0) {
                arg3 = combine(previous, current, arg3);
            }
            index++;
            previous = current;
            current++;
        } while (index != arg1);
    }
    return arg3;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185F24.s")
void func_1510F800(s32);
void func_100226F0(void *, s32);
s32 func_1510F720(s32, s32, s32, void **);
s32 func_150A5B90(u32 *, s32, s32, s32);
extern u8 *D_800D3668;
extern u32 *D_800D3694;
extern u8 D_800DE041;
extern s32 D_800D3690, D_800DBE3C;
extern s32 D_800DF0E8, D_800DF0EC, D_800DF0F0, D_800DF0F4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518652C CURRENT (5197) */
s32 func_1518652C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        u32 bits[187];
        s32 count;
        void *items[16];
    } work;
    volatile u32 savedMaximum;
    u32 maximum;
    void **cursor;
    u8 *data;
    u32 index;
    u32 *word;
    u8 code;
    u8 filter;
    s32 end;

    savedMaximum = 0;
    func_1510F800(0);
    work.count = func_1510F720(arg0, arg1, arg2, work.items);
    maximum = savedMaximum;
    if (work.count != 0) {
        savedMaximum = maximum;
        func_100226F0(work.bits, 0x2EC);
        maximum = savedMaximum;
        if (work.count != 0) {
            cursor = work.items + work.count;
            filter = (u8)D_800DE041;
            do {
                data = (u8 *)cursor[-1];
                index = 0;
                cursor--;
                data += 0xE;
                if (filter != 0) {
                    code = *data;
                    if (code != 0) {
                        do {
                            if (code & 0x80) {
                                index = ((code << 8) | data[1]) & 0x7FFF;
                                data += 2;
                            } else {
                                index += code;
                                data++;
                            }
                            if (index < 0x1760U) {
                                word = &work.bits[index >> 5];
                                if (D_800D3668[index] == 1) {
                                    *word |= 1U << (index & 0x1F);
                                    if (maximum < index) {
                                        maximum = index;
                                    }
                                }
                            }
                            code = *data;
                        } while (code != 0);
                    }
                } else {
                    code = *data;
                    if (code != 0) {
                        do {
                            if (code & 0x80) {
                                index = ((code << 8) | data[1]) & 0x7FFF;
                                data += 2;
                            } else {
                                index += code;
                                data++;
                            }
                            if (index < 0x1760U) {
                                word = &work.bits[index >> 5];
                                *word |= 1U << (index & 0x1F);
                                if (maximum < index) {
                                    maximum = index;
                                }
                            }
                            code = *data;
                        } while (code != 0);
                    }
                }
            } while (cursor != work.items);
        }
        D_800D3690 = D_800DBE3C;
        D_800D3694 = &work.bits[maximum >> 5] + 1;
        D_800DF0E8 = (s32)((u32)arg0 - (u32)arg2);
        D_800DF0EC = (s32)((u32)arg0 + (u32)arg2);
        D_800DF0F0 = (s32)((u32)arg1 - (u32)arg2);
        D_800DF0F4 = (s32)((u32)arg1 + (u32)arg2);
        end = func_150A5B90(work.bits, arg3, arg4, arg5);
        return (s32)((u32)end - (u32)arg3) / 20;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518652C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518652C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15186794.s")
extern s32 D_800DE01C;
extern s32 D_800DE020;
extern s32 D_800DE024;
extern s32 D_800DE030;
extern s32 D_800DE034;
extern s32 D_800DE038;
extern f32 D_800DE03C;
extern u8 D_800DE040;

void func_151872B0(s32 arg0) {
    D_800DE01C = 0x258;
    D_800DE020 = 0xB4;
    D_800DE024 = 0x5A;
    D_800DE030 = 0x3F8;
    D_800DE034 = 0;
    D_800DE038 = 1;
    D_800DE03C = 1.0f;
    D_800DE040 = 1;
    D_800DE041 = 1;
    switch (arg0) {
    case 33:
        D_800DE01C = 0x12C0;
        D_800DE020 = D_800DE01C - 1;
        D_800DE024 = D_800DE01C - 2;
        D_800DE030 = 0x3F2;
        D_800DE034 = 1;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 34:
        D_800DE01C = 0x960;
        D_800DE020 = D_800DE01C - 1;
        D_800DE024 = D_800DE01C - 2;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 20:
        D_800DE041 = 0;
        return;
    case 41:
        D_800DE01C = 0x4B0;
        D_800DE020 = 0x258;
        D_800DE024 = 0x12C;
        return;
    }
}
/* Call context: func_150A44F0: unique active project prototype */
void func_150A44F0(s32, void *, s32);

s32 func_150A5E44(void *, s32, s32, s32);
void func_1510F800(s32);
extern s32 D_800D3690;
extern u8 D_800D37E0[];
extern s32 D_800DBE3C;
extern s32 D_800DBEF0;
extern void *D_800DBEF4;
extern s32 D_800DF0E4;
extern s32 D_800DF0E8;
extern s32 D_800DF0EC;
extern s32 D_800DF0F0;
extern s32 D_800DF0F4;

typedef struct {
    u8 pad0[0x10];
    s16 x;
    u8 pad12[2];
    s16 z;
    u8 pad16[0x39];
    u8 flags;
    u16 width;
    u16 depth;
    u8 pad54[0x1A];
    u8 hidden;
    u8 pad6F[0x31];
} Game1873E4Entry;

s32 func_151873E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Game1873E4Entry *entry;
    s32 count;
    s32 i;
    s32 radius;

    if (D_800DBEF0 == 0) {
        return arg6;
    }
    func_1510F800(2);
    arg3 += arg6 * 0x14;
    D_800DF0E8 = arg0 - arg2;
    D_800DF0EC = arg0 + arg2;
    D_800DF0F0 = arg1 - arg2;
    D_800DF0F4 = arg1 + arg2;
    count = 0;
    for (i = 0; i < D_800DBEF0; i++) {
        entry = &((Game1873E4Entry *)D_800DBEF4)[i];
        if (entry->hidden != 0) {
            continue;
        }
        if (entry->flags & 0x60) {
            continue;
        }
        radius = (entry->depth < entry->width) ? entry->width : entry->depth;
        if (D_800DF0EC < entry->x - radius) {
            continue;
        }
        if (entry->x + radius < D_800DF0E8) {
            continue;
        }
        if (D_800DF0F4 < entry->z - radius) {
            continue;
        }
        if (entry->z + radius < D_800DF0F0) {
            continue;
        }
        ((s16 *)D_800D37E0)[count] = i;
        count++;
    }
    if (count != 0) {
        func_150A44F0(count, D_800D37E0, 0);
        D_800D3690 = D_800DBE3C;
        D_800DF0E4 = count;
        arg6 += (func_150A5E44(D_800D37E0, arg3, arg4, arg5) - arg3) / 20;
    }
    return arg6;
}
