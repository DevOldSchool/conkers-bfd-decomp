#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EF410.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1F60
 * - func_150C2290
 * - func_150C2558
 * - func_150C2700
 * - func_150C2898
 * - func_150C29F0
 * - func_150C2C00
 * - func_150C3230
 * - func_150C3574
 * - func_150C3D5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 w0;
    s32 w1;
} Gwords;
typedef union {
    Gwords words;
    s64 force_structure_alignment;
} Gfx;

typedef struct GameC2290Packet {
    f32 floats[9];
    s16 shorts[10];
    u8 bytes50[4];
    s32 words54[6];
    u8 bytes6C[4];
    s32 words70[9];
    u8 bytes94[4];
    s16 shorts98[2];
    s32 field84;
} GameC2290Packet;

typedef struct {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    f32 position[3];
    s16 field14;
    s16 field16;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    s8 field2C;
    s8 field2D;
    u8 pad2E[2];
    f32 field30;
    f32 field34;
    s8 field38;
    s8 field39;
    u8 pad3A[2];
    f32 field3C;
    s8 field40;
    u8 pad41[3];
    f32 field44;
} GameEF410Spawn;

typedef struct GameEF410Vector {
    f32 x;
    f32 y;
    f32 z;
} GameEF410Vector;

void func_15150178(s16 *, f32 *, s32, u8, s32);
void func_15151A38(f32 *, s32, s32);
extern f32 D_800A0230;
extern f32 D_800A0234;
extern f32 D_800A0238;
extern f32 D_800A023C;
extern f32 D_800A0240;
extern f32 D_800A0244;
extern f32 D_800A0248;
extern f32 D_800A024C;
extern f32 D_800A0250;
extern f32 D_800A0254;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1F60 CURRENT (5019) */
void func_150C1F60(s32 arg0) {
    GameC2290Packet packet;
    GameEF410Spawn spawn;

    packet.floats[0] = D_800A0230;
    packet.shorts[0] = 0xC;
    packet.floats[1] = 40.0f;
    packet.shorts[2] = -0xA0;
    packet.shorts[4] = -0x3C;
    packet.shorts[3] = 0x45;
    packet.shorts[5] = 0x43;
    packet.shorts[6] = 3;
    packet.shorts[7] = 5;
    packet.shorts[9] = 0x1F;
    packet.bytes50[0] = 0xB;
    packet.floats[2] = D_800A0234;
    packet.shorts[1] = 0xD;
    packet.shorts[8] = 0x32;
    packet.bytes50[2] = 0x28;
    packet.words54[0] = 1;
    packet.words54[1] = 4;
    packet.bytes6C[0] = 0xFF;
    packet.bytes6C[1] = 0xFF;
    packet.words70[0] = 3;
    packet.bytes50[1] = 1;
    packet.words54[2] = 0;
    packet.words54[3] = 0;
    packet.words54[4] = 0;
    packet.words54[5] = 0;
    packet.bytes6C[2] = 0;
    packet.words70[1] = 0xFF;
    packet.words70[2] = 0;
    packet.words70[3] = 0x220005;
    packet.words70[4] = 0x1D0600;
    packet.words70[5] = 1;
    packet.words70[6] = 0x3B;
    packet.words70[7] = 0x80;
    packet.words70[8] = 0x20;
    packet.bytes94[0] = 0;
    packet.bytes94[1] = 7;
    packet.shorts98[0] = 0xC;
    packet.shorts98[1] = 0x15;
    packet.floats[7] = D_800A0238;
    packet.floats[8] = D_800A023C;
    packet.floats[3] = 9.0f;
    packet.floats[4] = D_800A0240;
    packet.floats[5] = D_800A0244;
    packet.floats[6] = 0.5f;
    /* The raw caller leaves the consumed word at packet+0x84 uninitialized. */
    func_15151A38(packet.floats, (u8)arg0, 1);
    packet.shorts[0] = 2;
    packet.shorts[1] = 3;
    packet.shorts[2] = -0x6C;
    packet.shorts[4] = -0x16;
    packet.shorts[3] = 0x15;
    packet.shorts[5] = 0x16;
    packet.shorts[6] = 7;
    packet.shorts[7] = 0;
    packet.shorts[8] = 0x30;
    packet.shorts[9] = 0x15;
    packet.floats[7] = 100.0f;
    packet.floats[8] = 57.5f;
    packet.floats[3] = D_800A0248;
    packet.floats[4] = 39.0f;
    packet.floats[5] = D_800A024C;
    packet.floats[6] = 1.0f;
    func_15151A38(packet.floats, (u8)arg0, 1);
    *(GameEF410Vector *)spawn.position = *(GameEF410Vector *)packet.floats;
    spawn.field14 = 0x19;
    spawn.field16 = 0x12;
    spawn.field00 = -0x9F;
    spawn.field02 = 0x44;
    spawn.field04 = -0x34;
    spawn.field06 = 0x26;
    spawn.field20 = 0x19;
    spawn.field22 = 0x19;
    spawn.field2C = 0x9B;
    spawn.field2D = 0x64;
    spawn.field38 = 1;
    spawn.field39 = 6;
    spawn.field3C = 0.0f;
    spawn.field40 = 1;
    spawn.field44 = 0.0f;
    spawn.field18 = 40.0f;
    spawn.field1C = 35.0f;
    spawn.field24 = D_800A0250;
    spawn.field28 = D_800A0254;
    spawn.field30 = 1152.0f;
    spawn.field34 = 848.0f;
    func_15150178(&spawn.field00, spawn.position, 0, arg0, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1F60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C1F60.s")


void func_15151A38(f32 *, s32, s32);
extern f32 D_800A0258;
extern f32 D_800A025C;
extern f32 D_800A0260;
extern f32 D_800A0264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2290 CURRENT (1893) */
void func_150C2290(u8 arg0) {
    GameC2290Packet packet;

    packet.floats[0] = D_800A0258;
    packet.floats[1] = 40.0f;
    packet.shorts[1] = 3;
    packet.shorts[2] = -0x29;
    packet.shorts[4] = -0x16;
    packet.shorts[3] = 0x15;
    packet.shorts[5] = 0x16;
    packet.shorts[6] = 7;
    packet.shorts[9] = 0x15;
    packet.bytes50[0] = 0xB;
    packet.floats[2] = D_800A025C;
    packet.shorts[0] = 2;
    packet.shorts[8] = 0x30;
    packet.bytes50[2] = 0x28;
    packet.words54[0] = 1;
    packet.words54[1] = 4;
    packet.bytes6C[0] = 0xFF;
    packet.bytes6C[1] = 0xFF;
    packet.words70[0] = 3;
    packet.shorts[7] = 0;
    packet.bytes50[1] = 1;
    packet.words54[2] = 0;
    packet.words54[3] = 0;
    packet.words54[4] = 0;
    packet.words54[5] = 0;
    packet.bytes6C[2] = 0;
    packet.words70[1] = 0xFF;
    packet.words70[2] = 0;
    packet.words70[3] = 0x220005;
    packet.words70[4] = 0x1D0600;
    packet.words70[5] = 1;
    packet.words70[6] = 0x3B;
    packet.words70[7] = 0x80;
    packet.words70[8] = 0x20;
    packet.bytes94[0] = 0;
    packet.bytes94[1] = 7;
    packet.shorts98[0] = 0xC;
    packet.shorts98[1] = 0x15;
    packet.floats[7] = 100.0f;
    packet.floats[8] = 57.5f;
    packet.floats[3] = D_800A0260;
    packet.floats[4] = 39.0f;
    packet.floats[5] = D_800A0264;
    packet.floats[6] = 1.0f;
    func_15151A38(packet.floats, arg0, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2290 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2290.s")
f32 func_150ADA68(void);
void func_1514C470(f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, u8);
extern f32 D_800A0268;
extern f32 D_800A026C;

void func_150C2424(u8 arg0) {
    f32 *p = &D_800A0268;

    func_1514C470(
        *p,
        -490.0f,
        -328.0f,
        *p,
        -490.0f,
        328.0f,
        (func_150ADA68() * 8.0f) + 8.0f,
        1,
        0,
        0.0f,
        0,
        arg0
    );
    func_1514C470(
        D_800A026C,
        -560.0f,
        -580.0f,
        8117.0f,
        -560.0f,
        -580.0f,
        (func_150ADA68() * 3.0f) + 4.0f,
        3,
        0,
        0.0f,
        0,
        arg0
    );
}

s32 func_150C251C(void *arg0) {
    typedef struct {
        u8 pad0[0x1C];
        s16 unk1C;
        u8 pad1E[0x7A];
        void *unk98;
    } Local;
    typedef struct {
        u8 pad[0x1B];
        u8 unk1B;
    } Inner;
    Local *a = arg0;
    Inner *p = a->unk98;
    s32 v = a->unk1C * 8;

    if (v >= 0x100) {
        v = 0xFF;
    }
    p->unk1B = v;
    if ((u8)v < 0) {
        return 0;
    }
    return 1;
}
extern f32 D_800A0270;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2558 CURRENT (3119) */
s32 func_150C2558(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    GameC2290Packet packet;
    f32 value;

    packet.floats[0] = arg2;
    packet.floats[1] = arg3;
    value = (arg4 + 15.0f) - func_150ADA68() * 30.0f;
    packet.shorts[3] = 9;
    packet.shorts[6] = 3;
    packet.shorts[9] = 0x15;
    packet.bytes50[0] = 0xB;
    packet.shorts[2] = (s32)(value * D_800A0270) - 0x40;
    packet.shorts[7] = 3;
    packet.shorts[8] = 0x28;
    packet.bytes50[2] = 0x28;
    packet.words54[0] = 1;
    packet.words54[1] = 4;
    packet.bytes6C[0] = 0xFF;
    packet.bytes6C[1] = 0xFF;
    packet.words70[0] = 3;
    packet.shorts[0] = 1;
    packet.shorts[1] = 0;
    packet.shorts[4] = 0;
    packet.shorts[5] = 0;
    packet.bytes50[1] = 1;
    packet.words54[2] = 0;
    packet.words54[3] = 0;
    packet.words54[4] = 0;
    packet.words54[5] = 0;
    packet.bytes6C[2] = 0;
    packet.words70[1] = 0xFF;
    packet.words70[2] = 0;
    packet.words70[3] = 0x220005;
    packet.words70[4] = 0x1D0600;
    packet.words70[5] = 1;
    packet.words70[6] = 0x3B;
    packet.words70[7] = 0x80;
    packet.words70[8] = 0x20;
    packet.bytes94[0] = 0;
    packet.bytes94[1] = 7;
    packet.shorts98[0] = 0xC;
    packet.shorts98[1] = 0x15;
    packet.floats[2] = value;
    packet.floats[7] = 200.0f;
    packet.floats[8] = 150.0f;
    packet.floats[3] = 22.0f;
    packet.floats[5] = 0.0f;
    packet.floats[6] = 0.0f;
    packet.floats[4] = 44.0f;
    func_15151A38(packet.floats, arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2558 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2558.s")


void func_15150178(s16 *, f32 *, s32, u8, s32);
extern f32 D_800A0274;
extern f32 D_800A0278;
extern f32 D_800A027C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2700 CURRENT (625) */
s32 func_150C2700(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    GameEF410Spawn spawn;

    spawn.field16 = 5;
    spawn.field00 = 0x6B;
    spawn.position[0] = arg2;
    spawn.position[1] = arg3;
    spawn.field14 = 6;
    spawn.field02 = 0x46;
    spawn.field04 = -0x1F;
    spawn.field06 = 0x2E;
    spawn.field20 = 0x64;
    spawn.field22 = 0;
    *(u8 *)&spawn.field2C = 0x9B;
    spawn.field2D = 0x64;
    spawn.field34 = 0.0f;
    spawn.field38 = 1;
    spawn.field39 = 6;
    spawn.field3C = 0.0f;
    spawn.field40 = 1;
    spawn.field44 = 0.0f;
    spawn.field18 = 30.0f;
    spawn.field1C = 35.0f;
    spawn.field24 = D_800A0274;
    spawn.field28 = D_800A0278;
    spawn.position[2] = arg4;
    spawn.field30 = D_800A027C;
    func_15150178(&spawn.field00, spawn.position, 0, arg14, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2700 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2700.s")
extern f32 D_800A0280;
extern f32 D_800A0284;

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    f32 field_C;
    f32 field_10;
    s16 field_14;
    s8 field_16;
    s8 field_17;
    s8 field_18;
    s8 field_19;
} GameEF410Params;

void func_150C2804(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    GameEF410Params sp1C;

    sp1C.field_C = D_800A0280;
    sp1C.field_0 = arg0;
    sp1C.field_4 = arg1;
    sp1C.field_8 = arg2;
    sp1C.field_10 = D_800A0284;
    sp1C.field_14 = arg3;
    sp1C.field_16 = 5;
    sp1C.field_17 = 6;
    sp1C.field_18 = 3;
    sp1C.field_19 = -1;
    func_15134908(&sp1C, 0, arg4, arg5);
}
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32, f32,
                   s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
extern f32 D_800A0288;
extern f32 D_800A028C;
extern f32 D_800A0290;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2898 CURRENT (48) */
void func_150C2898(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, void *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    u32 sp54;
    u32 sp50;
    f32 sp4C;
    f32 temp_fv1;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_fv1 = ((func_150ADA68() * 112.0f) + 247.0f) * D_800A0288;
    sp60[0] = -arg3 * temp_fv1;
    sp60[1] = -arg4 * temp_fv1;
    sp60[2] = -arg5 * temp_fv1;
    sp4C = func_150ADA68();
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    func_151D9014(sp6C, sp60, 6, (sp4C * D_800A028C) + D_800A0290,
                   (sp50 & 0xF) + 0x19, (sp54 % 101U) + 0x9B,
                   (func_150ADA68() * 119.0f) + 129.0f, 0, 1.0f, 1.0f,
                   1, 0, 1, 0, *(u8 *)((u8 *)arg6 + 0xC),
                   *(u8 *)((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2898 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2898.s")
typedef struct GameEF410Particle {
    f32 position[3];
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 color26[4];
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 field2F;
    s32 field30;
    u8 field34;
    u8 pad35[3];
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
} GameEF410Particle;

typedef struct GameEF410Emitter {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD;
    s16 timerE;
    u8 pad10[0x18];
    f32 field28[4];
} GameEF410Emitter;

void func_15149550(f32 *, s32, s32, s32, s32, s32);
extern f32 D_800A02A0;
extern f32 D_800A02A4;
extern f32 D_800A02A8;
extern f32 D_800A02AC;
extern f32 D_800A02B0;
extern f32 D_800A02B4;
extern f32 D_800A02B8;
extern f32 D_800A02BC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C29F0 CURRENT (3947) */
void func_150C29F0(GameEF410Emitter *arg0) {
    GameEF410Particle packet;
    f32 firstScale;
    u8 angle;
    f32 waveX;
    f32 waveZ;
    f32 radius;
    f32 *position;
    f32 secondScale;

    angle = func_150ADA20();
    waveX = func_151423D8(angle - 0x40);
    waveZ = func_151423D8(angle);
    radius = func_150ADA68() * arg0->field28[2];
    position = arg0->field28;
    packet.field22 = 0x1A4D;
    packet.field20 = 0x6231;
    packet.color26[0] = 0;
    packet.color26[1] = 0;
    packet.color26[2] = 0;
    packet.color26[3] = 0xFF;
    packet.field2C = 0xFF;
    packet.field2D = 0xFF;
    packet.field30 = 0;
    packet.field2A = 1;
    packet.field2E = 0;
    packet.field2F = 1;
    packet.field24 = (func_150ADA20() % 201U) + 100;
    packet.field34 = 0xF;
    packet.field40 = D_800A02A0;
    packet.field38 = 0.0f;
    packet.field44 = D_800A02A4;
    packet.position[0] = position[0] + radius * waveX;
    packet.position[1] = position[3];
    packet.field3C = D_800A02A8;
    packet.position[2] = position[1] + radius * waveZ;
    firstScale = func_150ADA68() * 0.5f + 1.0f;
    secondScale = func_150ADA68() * 0.5f + 1.0f;
    packet.field0C = D_800A02AC * firstScale;
    packet.field14 = D_800A02B0 * firstScale;
    packet.field10 = D_800A02B4 * secondScale;
    packet.field18 = D_800A02B8 * secondScale;
    packet.field1C = D_800A02BC * secondScale;
    func_15149550(packet.position, 0xA, 1, 0, arg0->fieldC, arg0->field1);
    arg0->timerE = (func_150ADA20() % 51U) + 25;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C29F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C29F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2C00.s")
extern f32 D_800BE9A4;

typedef struct T150C { u8 pad0[0x2C]; f32 unk2C, unk30, unk34, unk38; u8 pad3C[0x10]; f32 unk4C, unk50; u8 pad54[0xFC]; f32 unk150; } T150C;

s32 func_150C2FCC(T150C *arg0) {
    f32 *dt = &D_800BE9A4;

    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk150);
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk150);
    arg0->unk38 += (arg0->unk50 * *dt) + (((0.5f * arg0->unk4C) * *dt) * *dt);
    arg0->unk50 += arg0->unk4C * *dt;
    if ((arg0->unk2C < 10.0f) || (arg0->unk30 < 10.0f)) {
        return 0;
    }
    return 1;
}
f32 func_150484A0(f32, f32);
s32 func_15144B34(s32);
f32 func_15144C8C(f32, f32);
extern s32 D_80082FA4;
extern f32 D_800A0310;
extern f32 D_800A0314;

s32 func_150C308C(void *arg0) {
    u8 flag;
    f32 tmp1;
    u8 sp1F;
    f32 x;
    f32 z;
    f32 magnitude;
    u8 *vector;

    flag = 0;
    if (*(s16 *)((u8 *)arg0 + 0x1C) >= 6) {
        sp1F = 0;
        vector = (u8 *)func_15144B34(D_80082FA4);
        x = *(f32 *)vector;
        tmp1 = *(f32 *)(vector + 8);
        z = (magnitude = tmp1);
        tmp1 = x;
        magnitude = tmp1 * tmp1 + magnitude * z;
        if (magnitude < D_800A0310) {
            flag = 1;
        } else {
            flag = sp1F;
            magnitude = *(f32 *)vector;
            if (D_800A0314 <
                func_15144C8C(func_150484A0(magnitude,
                                           *(f32 *)(vector + 8)),
                              *(f32 *)((u8 *)arg0 + 0x160))) {
                flag = 1;
            }
        }
    }
    if (flag != 0) {
        *(s16 *)((u8 *)arg0 + 0x1C) = 5;
    }
    return 1;
}
Gfx *func_150C3160(Gfx *gdl, s8 *arg1)
{
  s32 new_var2;
  f32 t;
  s32 v1;
  s32 new_var;
  s32 a0;
  s32 d;
  d = *((s32 *) (arg1 + 0x2E8));
  if (d != 0)
  {
    t = ((f32) (*((s32 *) (arg1 + 0x2E4)))) / ((f32) d);
  }
  else
  {
    t = 1.0f;
  }
  t = 1.0f - t;
  new_var = (s32) ((500.0f * t) + 2.0f);
  a0 = 2 - (*((s32 *) (arg1 + 0x2EC)));
  v1 = new_var;
  *((s32 *) (arg1 + 0x2EC)) = v1 / 3;
  while (a0 < 0)
  {
    a0 += 0x40;
  }

 { Gfx *_g = (Gfx *) (gdl++); _g->words.w0 = ((0xF2 << 24) | ((v1 & 0xFFF) << 12)) | (a0 & 0xFFF);
    new_var2 = 0x1FE;
    _g->words.w1 = ((4 << 24) | (new_var2 << 12)) | 0x3E;
  }
  return gdl;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3574.s")
void func_15059140(u8 *);
void func_15060F28(u8 *, s32);
void func_1506AC8C(void *, s32, void *);
void func_150C1660(f32, f32, f32, u8);
void func_150C3D5C(u8 *);
void func_15188810(u8 *, s32, s32);
void func_151B9BF0(s32, s32, s16, s16, s16, s16, s16, s16, s16, s16, s16, s16, s16, s32, u8, s32);
s32 func_10010344(s32, void *, u32, s16, s32);
void func_10010630(u16, void *, s32, s32, s32);
extern f32 D_800A0334;

void func_150C3994(u8 *arg0) {
    if (*(s32 *)arg0 == 0x14) {
        if (*(s32 *)(arg0 + 0x2E4) == 0) {
            func_151B9BF0(0x2F, 1, *(f32 *)(arg0 + 0x14), *(f32 *)(arg0 + 0x18) + 30.0f,
                          *(f32 *)(arg0 + 0x1C), 0x7D0, 0x3E8, 0x190, 0xC8, 0xC00, 0xC00, 1, 1, 0,
                          0xFF, 0);
        } else {
            func_15188810(arg0, 0x64, 0);
        }
    }
    if (*(f32 *)(arg0 + 0x20) < 0.0f && *(f32 *)(arg0 + 0x28) > 20.0f && arg0[0x136] == 0 &&
        -20.0f * *(f32 *)(arg0 + 0x20) > *(f32 *)(arg0 + 0x28)) {
        func_10010630(0x92, arg0, 0x7D00, 0xC8, 0x9C4);
        arg0[0x136] = 1;
    }
    if (arg0[0x83] == 0) {
        *(f32 *)(arg0 + 0x148) = 70.0f;
        if (*(s32 *)(arg0 + 0x2E4) == 0) {
            func_151B9BF0(0x2F, 1, *(f32 *)(arg0 + 0x14), *(f32 *)(arg0 + 0x18) + 30.0f,
                          *(f32 *)(arg0 + 0x1C), 0x898, 0x500, 0x320, 0x2BC, 0xC00, 0xC00, 0x14, 1,
                          0, 0xFF, 0);
            func_150C1660(*(f32 *)(arg0 + 0x14), *(f32 *)(arg0 + 0x18) + 30.0f,
                          *(f32 *)(arg0 + 0x1C), 0xFF);
            func_1506AC8C(arg0, 6, NULL);
        } else {
            func_15188810(arg0, 0x64, 0);
        }
        func_10010344(0x1A9, arg0, 0x7FFF, 0x3E8, 0x7D0);
        arg0[0xD0] = 1;
        *(f32 *)(arg0 + 0x114) = 500.0f;
        *(s32 *)(arg0 + 0xF8) |= 0x01008000;
    }
    arg0[0x125] = 0xFF;
    if (++arg0[0x83] >= 11) {
        *(s32 *)(arg0 + 0xF8) &= ~0x8000;
    }
    *(f32 *)(arg0 + 0x40) = (*(u16 *)(arg0 + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    *(f32 *)(arg0 + 0xB8) += *(f32 *)(arg0 + 0x148);
    *(f32 *)(arg0 + 0x148) *= D_800A0334;
    if ((*(f32 *)(arg0 + 0x28) == 0.0f && arg0[0x83] >= 21 && *(s16 *)(arg0 + 0xCC) == 0) ||
        arg0[0x107] != 0 || arg0[0x1CA] == 0) {
        func_150C3D5C(arg0);
        func_10010630(0x93, arg0, 0x7D00, 0xC8, 0x9C4);
        func_15060F28(arg0, 1);
    }
}
s32 func_150C3D48(s32 arg0) {
    return arg0 + 0xEDCBA988;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3D5C.s")
