#ifndef CONKER_TYPES_H
#define CONKER_TYPES_H

/* Base types come from the pinned SDK (lib/ultralib), so SDK headers can be included. */
#include "../lib/ultralib/include/PR/ultratypes.h"

/*
 * Shared structure layouts used by matched game C.
 * Keep private/partial structures in their owning source file; promote here
 * when cross-source use requires a common declaration (see
 * docs/decompilation-workflow.md).
 */

typedef struct struct108 struct108;
typedef struct struct124 struct124;
typedef struct struct127 struct127;
typedef struct struct216 struct216;
typedef struct struct255 struct255;

struct FLOAT {
    f32 unk0;
};

struct UBYTES4 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

typedef struct {
    u8  unk0;
    u8  unk1;   // used
    u8  unk2;
    u8  unk3;
    u8  unk4;
    u8  unk5;
    u8  unk6;
    u8  unk7;
    s32 unk8;
    s16 unkC;
    u8  unkE;
    u8  unkF;
    s16 unk10;
    u8  unk12;  // used
    u8  unk13;
    u8  unk14;
    u8  pad15[0x3];
    u8  unk18;  // used
    u8  unk19;  // used
    u8  pad1A[0x2];
    s16 unk1C;
    u8  pad1E[0xA];
    u8  unk28;
    u8  unk29[0x3];
    s32 unk2C;
    s32 unk30;
    u8  pad34[0x6];
    u8  unk3A;
    u8  pad3B[0x2];
    u8  unk3D;
} struct102;

struct struct124 {
    struct124* unk0;
    u8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8  pad14[0x3];
    u8  unk17;
    s16 unk18;
    s16 unk1A;  // used
    s16 unk1C;  // used
    s16 unk1E;  // used
    s16 unk20;
    s16 unk22;  // used
    s16 unk24;  // used
    s16 unk26;  // used
    union {
        struct UBYTES4 i;
        struct FLOAT f;
    } data;
};

typedef struct {
    u8  pad0[0x8];
    u16 unk8;
    u8  padA[0x2];
    u8  unkC;
    u8  padD;
    u16 unkE;
    u8  pad10[0x2];
    s16 unk12;
    u8  unk14;
    u8  pad15;
    u8  unk16;
    u8  pad17[0xD];
    s16 unk24;
    s8  unk26;
    u8  unk27;
    s32 unk28;
    s32 unk2C;
    u8  unk30;
    u8  unk31;
    u8  pad32[0x4];
    u8  unk36;
    u8  pad37;
    s32 unk38;
    u8  pad3C[0x8];
    s8  unk44;
    u8  pad45[0x5];
    /* 0x4A */ s8  chased; //unk4A;
    /* 0x4B */ s8  chasing; //unk4B;
    u16 unk4C;
    u8  unk4E;
    u8  pad4F[0x3];
    u8  unk52;
    u8  pad53;
    s8  unk54;
    s8  unk55;
    u8  pad56;
    u8  unk57;
    u8  unk58;   // used
    u8  unk59;   // used
    u8  pad5A[0xC];
    u16 unk66;
    u8  pad68[0x3];
    u8  unk6B;
    u8  pad6C[0x9];
    u8  unk75;
    u8  pad76[0x2];
    u8  unk78;
    u8  pad79[0x4];
    /* 0x7D */  u8  matrix_physics; //unk7D;
    u8  pad7E[0x2];
    s16 unk80;
    s16 unk82;
    u8  unk84;
    u8  pad85[0x3];
    s16 unk88;
    s16 unk8A;  // used
    u16 unk8C;  // used
    s8  unk8E;  // used
    s8  unk8F;  // used
    s8  unk90;
    s8  unk91;
    s8  unk92;
    s8  unk93;
    s8  unk94;
    s8  unk95;  // used
    u8  pad96;
    u8  unk97;
    u8  pad98[0x10];
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ u8  unkAC;
    /* 0xAD */ u8  unkAD;
    u8  padAE[0x66];
    u16 unk114;
    u16 unk116;
    u16 unk118;
    u8  unk11A;
    u8  pad11B[0x5];
    u8  unk120;
    u8  unk121;
    u8  unk122;
    u8  unk123;
    s16 unk124;
    u16 pad126;
    u8  unk128;
    u8  pad129[0x6C];
    u8  unk195;
    u8  pad196;
    u8  unk197;
    u8  unk198;
    u8  pad199;
    /* 0x19a */ u8  grenade_count;
    u8  unk19B;
    u8  pad19C[0x2];
    u16 unk19E;
    u16 unk1A0;
    u8  pad1A2[0x7];
    u8  unk1A9;
    s16 unk1AA;
} struct126;

typedef struct {
    u16 unk0;
    u8  unk2;
    u8  unk3;
    u8  unk4;
    u8  pad5[0x9];
    u8  unkE;
    u8  unkF;
    u8  pad10[0x8];
    s32 unk18;
    u8  unk1C[0x4];
    f32 unk20;
    f32 unk24;
} struct129;

typedef struct {
    u8 pad[0xEC];
} struct150;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} struct17;

typedef struct {
    u8  pad0[0x4];
    u16 unk4;
    u8  pad6[0x2];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8  pad14[0x4];
    f32 unk18;
} struct197;

struct struct216 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
};

typedef struct {
    u8  pad0[0x5];
    u8  unk5;
    u8  unk6;
    u8  unk7;
    u8  pad8;
    u8  unk9;
    u8  padA[0x4];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8  unk16[0x19];
    u8  unk2F;
} struct226;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    u8  pad12[0x12];
    u8  unk24;
} struct227;

typedef struct {
    u8 pad0[0x1A];
    s16 unk1A;
} struct254;

struct struct255 {
    u8 pad0[0x240];
    struct254 *unk240;
};

struct struct127 {
    /* 0x00 */  s32 interaction_state;
    /* 0x04 */  u8  id;
    u8  unk5;
    u8  unk6;
    u8  unk7;
    u8  unk8;
    u8  unk9;
    u8  unkA;
    u8  unkB;
    u8  unkC;
    u8  unkD;
    union {
      s16 h;
      u8  ub[2];
    } unkE;
    s8  unk10;
    s8  unk11;
    u8  unk12;
    u8  unk13;
    /* 0x14 */  f32 x_position;
    /* 0x18 */  f32 y_position;
    /* 0x1C */  f32 z_position;
    /* 0x20 */  f32 y_velocity;
    /* 0x24 */  f32 gravity;
    f32 unk28;
    /* 0x2C */  f32 old_x_position;
    /* 0x30 */  f32 old_y_position;
    /* 0x34 */  f32 old_z_position;
    u8  unk38;
    u8  pad39;
    s8  unk3A;
    /* 0x3B */  u8  unique_id;
    /* 0x3C */  f32 xz_velocity;
    f32 unk40;  // used
    f32 unk44;
    f32 unk48;
    /* 0x4C */  f32 animation_speed;
    u32 pad50;
    u32 pad54;
    u32 pad58;
    s32 unk5C;  // used
    s32 unk60;
    s8  unk64;
    u8  unk65;  // used
    u8  pad66;
    u8  pad67;
    u32 pad68;
    s16 pad6C;
    s8  unk6E;
    s8  pad6F;
    u32 pad70;
    u8  unk74;
    s8  pad75;
    u16 unk76;  // moving_angle
    u16 unk78;
    u16 unk7A;  // facing angle
    u16 unk7C;
    u8  unk7E;
    u8  unk7F;  // counter
    u8  unk80;  // counter
    u8  unk81;  // counter
    u8  unk82;  // counter
    u8  unk83;  // used
    union {
        u16 uh;
        u8  ub[2];
    }   unk84;
    u8  unk86;
    u8  unk87;
    u8  unk88;
    /* 0x89 */  u8  disable_run;   // slowdown?
    /* 0x8A */  u8  disable_jump; // unk8A;
    u16 unk8C;  // used
    u16 unk8E;  // used
    u16 unk90;
    u16 unk92;
    s32 unk94;
    u32 pad98;
    u32 unk9C;
    u32 padA0;
    u32 padA4;
    u8  unkA8;
    u8  unkA9;
    u8  unkAA;
    u8  unkAB;
    u8  padAC;
    /* 0xAD */  u8  in_water;
    u8  unkAE;
    u8  padAF;
    s8  unkB0;
    u8  padB1;
    u16 unkB2;  // (oxygen?)
    s32 padB4;
    f32 unkB8;  // used
    u32 padBC;
    /* 0xC0 */  f32 target_speed;
    f32 unkC4;
    u32 padC8;
    s16 unkCC;
    s16 unkCE;
    u8  unkD0;
    s8  padD1;
    s16 unkD2;    // used
    s16 unkD4;    // used
    s16 unkD6;    // used
    s16 unkD8;
    s16 unkDA;
    f32 unkDC;    // used
    f32 unkE0;    // used
    s16 unkE4;    // used
    s16 unkE6;    // used
    u16 unkE8;    // used
    u16 unkEA;
    f32 unkEC;
    f32 unkF0;
    s32 unkF4;
    s32 unkF8;
    s32 unkFC;
    u8  unk100;   // used
    u8  unk101;
    u8  unk102;
    u8  unk103;
    /* 0x104 */ u8  stunned; //unk104;
    u8  unk105;
    u8  unk106;
    u8  unk107;
    u8  pad108;
    u8  unk109;
    u8  pad10A;
    u8  unk10B;
    s16 unk10C;
    u8  unk10E;
    u8  unk10F;
    u32 pad110;
    f32 unk114;
    f32 unk118;
    f32 unk11C;
    u8  unk120;
    u8  unk121;
    u8  unk122;
    u8  unk123;
    u8  unk124;
    /* 0x125 */ u8  immune; // used
    u8  pad126;
    u8  unk127;
    u32 pad128;
    u32 pad12C;
    u32 pad130;
    u8  pad134[3];
    u8  unk137;
    u8  unk138;
    u8  pad139[0x3];
    u8  unk13C; // used
    u8  unk13D;
    u8  unk13E;
    u8  unk13F; // used
    s32 unk140;
    struct129 *unk144; // used
    f32 unk148;
    /* 0x14C */ f32 xz_scale;
    /* 0x150 */ f32 y_scale;
    f32 unk154;
    f32 unk158;
    f32 unk15C;
    u32 pad160;
    f32 unk164;
    f32 unk168;
    f32 unk16C;
    f32 unk170;
    u32 pad174;
    u32 pad178;
    u32 pad17C;
    f32 unk180;
    s32 unk184;
    u32 pad188;
    f32 unk18C; // used
    u32 pad190;
    u8  pad194;
    u8  unk195;
    u8  pad196;
    u8  unk197;
    u8  unk198;
    u8  pad199;
    u8  pad19A;
    u8  pad19B;
    u32 pad19C;
    u32 pad1A0;
    u16 pad1A4;
    s16 unk1A6;
    u32 pad1A8;
    u32 pad1AC;
    u32 pad1B0;
    u32 pad1B4;
    u32 pad1B8;
    u32 pad1BC;
    u32 pad1C0;
    u32 pad1C4;
    u8  pad1C8;
    u8  unk1C9;
    /* 0x1CA */ u8  health;
    u8  unk1CB;
    f32 unk1CC;
    s8  unk1D0;
    s8  unk1D1;
    u16 pad1D2;
    struct255 *unk1D4;
    u32 pad1D8;
    u32 pad1DC;
    u32 pad1E0;
    u8  unk1E4;
    u8  unk1E5;
    u8  unk1E6;
    u8  unk1E7;
    u8  unk1E8;
    u8  pad1E9;
    u16 unk1EA;
    u16 unk1EC;
    u8  pad1EE[0x2];
    u32 pad1F0;
    s32 unk1F4;
    u32 pad1F8;
    u8  unk1FC;
    u8  unk1FD;
    u8  pad1FE;
    u8  unk1FF;
    s8  unk200;
    u8  pad201[0x3];
    s32 unk204;
    u32 pad208;
    u8  pad20C[0x3];
    u8  unk20F;
    u8  pad210;
    u8  unk211;
    u8  unk212[0x2];
    s32 unk214;
    struct216 *unk218; // struct216 is 5 bytes long
    u16 unk21C;
    u8  unk21E;
    u8  unk21F;
    u8  unk220;
    s8  unk221;
    u8  unk222;
    u8  unk223;
    u16 unk224;
    u8  unk226;
    u8  pad227;
    u8  unk228;
    u8  unk229;
    u8  pad22A;
    u8  unk22B;
    u16 unk22C;
    s16 unk22E;
    u8  pad230;
    u8  unk231;
    u8  unk232; // used
    u8  unk233;
    u8  unk234;
    u8  unk235;
    u8  unk236;
    u8  unk237;
    u8  unk238;
    s8  unk239; // used
    u8  unk23A;
    u8  unk23B;
    u8  pad23C;
    u8  unk23D;
    u8  unk23E;
    u8  unk23F;
    u8  unk240;
    u8  unk241;
    u8  unk242;
    u8  pad243;
    s16 unk244;
    u8  unk246;
    u8  unk247;
    u8  unk248;
    u8  unk249;
    u8  unk24A;
    u8  pad24B;
    u8  unk24C;
    u8  unk24D;
    u8  unk24E;
    s8  unk24F;
    u8  unk250;
    u8  unk251;
    u8  unk252;
    u8  unk253;
    u8  unk254;
    u8  unk255;
    u8  unk256;
    u8  unk257;
    u8  unk258;
    u8  pad259[0x3];
    s32 unk25C;
    u8  pad260[0x14];
    u8  unk274;
    u8  pad275;
    s8  unk276;
    u8  pad277;
    s16 unk278;
    u8  unk27A[0x8];
    s16 unk282;
    u8  unk284;
    u8  unk285;
    u8  unk286;
    u8  unk287;
    /* 0x288 */ u8  unk288;
    u8  pad289[0x40];
    u8  unk2C9;
    s8  unk2CA;
    s8  unk2CB;
    s32 unk2CC;
    struct197 *unk2D0;
    u8  pad2D4[0x10];
    s32 unk2E4;
    s32 unk2E8;
    s32 unk2EC;
    u8  pad2F0[0x8];
    u16 unk2F8; // wait animation?
    u8  unk2FA;
    u8  unk2FB;
    u8  pad2FC[0x3];
    u8  unk2FF;
    u8  unk300;
    u8  unk301[0x17];
    /* 0x318 */ struct108 *camera;
    struct126 *unk31C; // used (is this actually 127?)
    u8  pad320[0xC];
};

struct struct108 {
                u16 unk0;
                u16 unk2[0x15];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ struct150 *unk30;
    /* 0x034 */ u8  pad34[0x50];
    /* 0x084 */ s32 unk84;
                s32 unk88;
    /* 0x088 */ u8  pad8C[0x50];
    /* 0x0DC */ s32 unkDC;
                s32 unkE0;
    /* 0x0E0 */ u8  padE4[0x50];
    /* 0x134 */ s32 unk134;
                s32 unk138;
    /* 0x138 */ u8  pad13C[0x50];
    /* 0x18C */ f32 unk18C;      // used
    /* 0x190 */ f32 unk190;      // used
    /* 0x194 */ f32 unk194;
                f32 unk198;
    /* 0x19C */ f32 unk19C;
    /* 0x1A0 */ f32 unk1A0;
    /* 0x1A4 */ f32 unk1A4;
    /* 0x1A8 */ f32 unk1A8;
    /* 0x1AC */ u8  pad1AC[0x8];
    /* 0x1B4 */ s16 unk1B4;      // used
    /* 0x1B6 */ u16 unk1B6[0x15]; // 0x15 * 2 => 0x1E0
    /* 0x1E0 */ s16 unk1E0;
    /* 0x1E2 */ s16 unk1E2;
    /* 0x1E4 */ u8  pad1E4[0x28];
    /* 0x20C */ s16 unk20C[0x15];
    /* 0x236 */ u8  pad236[0x2];
    /* 0x238 */ s32 unk238;
    /* 0x23C */ u8  unk23C;
    /* 0x23D */ u8  unk23D;
    /* 0x23E */ u8  unk23E; // used
    /* 0x23F */ u8  unk23F;
    /* 0x240 */ s32 unk240;
    /* 0x244 */ s16 unk244;
    /* 0x246 */ s16 pad246;
    /* 0x248 */ s32 unk248;
    /* 0x24C */ f32 unk24C;
    /* 0x250 */ f32 unk250;
    /* 0x254 */ u8  pad254[0x18];
    /* 0x26C */ f32 unk26C;
    /* 0x270 */ s16 pad270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ u8  pad274[0x24];
    /* 0x298 */ u16 unk298;
    /* 0x29A */ u8  pad29A[0xA];
    /* 0x2A4 */ f32 unk2A4;
    /* 0x2A8 */ f32 unk2A8;
    /* 0x2AC */ s32 unk2AC; // is this really s32?
    /* 0x2B0 */ f32 unk2B0;
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ f32 unk2B8;
    /* 0x2BC */ f32 unk2BC;
    /* 0x2C0 */ f32 unk2C0;
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ s32 unk2C8;
    /* 0x2CC */ s32 unk2CC;
    /* 0x2D0 */ s32 unk2D0;
    /* 0x2D4 */ u8  pad2D4[0xC];
    /* 0x2E0 */ s32 unk2E0;
    /* 0x2E4 */ s32 unk2E4;
    /* 0x2E8 */ s32 unk2E8;
    /* 0x2EC */ s32 unk2EC;
    /* 0x2F0 */ s32 unk2F0;
    /* 0x2F4 */ s32 unk2F4;
    /* 0x2F8 */ f32 unk2F8; // struct ptr?
    /* 0x2FC */ f32 unk2FC;
    /* 0x300 */ f32 unk300;
    /* 0x304 */ f32 unk304;
    /* 0x308 */ f32 unk308;
    /* 0x30C */ f32 unk30C;
    /* 0x310 */ u8  pad310[0x38];
    /* 0x348 */ f32 unk348;      // used
    /* 0x34C */ f32 unk34C;      // used
    /* 0x350 */ u8  pad350[0x4];
    /* 0x354 */ f32 unk354;
    /* 0x358 */ f32 unk358;
    /* 0x35C */ f32 unk35C;
    /* 0x360 */ u32 pad360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ s16 unk368;
    /* 0x36A */ u16 unk36A;
    /* 0x36C */ u16 *unk36C;
    /* 0x370 */ u8  pad370[0x4];
    /* 0x374 */ f32 unk374;      // used
    /* 0x378 */ u32 pad378;
    /* 0x37C */ f32 unk37C;
    /* 0x380 */ f32 unk380;
    /* 0x384 */ f32 unk384;
    /* 0x388 */ f32 unk388;
    /* 0x38C */ f32 unk38C;
    /* 0x390 */ f32 unk390;
    /* 0x394 */ s32 pad394;
    /* 0x398 */ f32 unk398;
    /* 0x39C */ f32 unk39C;
    /* 0x3A0 */ f32 unk3A0;
    /* 0x3A4 */ f32 pad3A4;
    /* 0x3A8 */ f32 unk3A8;
    /* 0x3AC */ u8  pad3AC[0x20];
    /* 0x3CC */ s16 unk3CC;
    /* 0x3CE */ u16 pad3CE;
    /* 0x3D0 */ struct127 *unk3D0;
    /* 0x3D4 */ struct127 *unk3D4;
    /* 0x3D8 */ u8  pad3D8[0x8];
    /* 0x3E0 */ f32 unk3E0;
    /* 0x3E4 */ u32 pad3E4;
    /* 0x3E8 */ u8  unk3E8;
    /* 0x3E9 */ u8  pad3E9[0xb];
    /* 0x3F4 */ f32 unk3F4;
    /* 0x3F8 */ f32 unk3F8;
    /* 0x3FC */ u8  pad3FC[0x1d0];
    /* 0x5CC */ f32 unk5CC;
    /* 0x5D0 */ u32 pad5D0;
    /* 0x5D4 */ s32 unk5D4;
    /* 0x5D8 */ f32 unk5D8;
    /* 0x5DC */ u8  pad5DC[0xC];
    /* 0x5E8 */ f32 unk5E8;
    /* 0x5EC */ s32 pad5EC;
    /* 0x5F0 */ s32 unk5F0;
    /* 0x5F4 */ u8  pad5F4[0x6];
    /* 0x5FA */ s16 unk5FA;
    /* 0x5FC */ u16 unk5FC;
    /* 0x5FE */ u16 unk5FE;
    /* 0x600 */ u8  pad600[0x18];
    /* 0x618 */ s32 unk618; // struct ptr
    /* 0x61C */ u8  pad61C[0x48];
    /* 0x664 */ f32 unk664;
    /* 0x668 */ f32 unk668;
    /* 0x66C */ f32 unk66C;
    /* 0x670 */ f32 unk670;
    /* 0x674 */ f32 unk674;
    /* 0x678 */ u8  pad678[0x4];
    /* 0x67C */ f32 unk67C;
    /* 0x680 */ u8  pad680[0x18];
    /* 0x698 */ s32 unk698;
    /* 0x69C */ u8  pad69C[0x14];
    /* 0x6B0 */ s32 unk6B0;
    /* 0x6B4 */ u8  pad6B4[0x14];
    /* 0x6C8 */ s32 unk6C8;
    /* 0x6CC */ u8  pad6CC[0x30];
    /* 0x6FC */ s32 unk6FC; // struct pointer
    /* 0x700 */ u8  pad700[0xC];
                s16 unk70C;
                s16 unk70E;
                s16 unk710;
                s16 unk712;
                u8  pad714[0xC];
                f32 unk720;
                f32 unk724;
                f32 unk728;
                f32 unk72C;
                u8  pad730[0xC];
    /* 0x73C */ s16 unk73C;
    /* 0x73E */ u8  pad73E[0x42];
                f32 unk780;
                u8  pad784[0x30];
    /* 0x7B4 */ f32 unk7B4; // used
    /* 0x7B8 */ f32 unk7B8;
    /* 0x7BC */ f32 unk7BC;
    /* 0x7C0 */ u8  pad7C0[0x8];
                s32 unk7C8;
    /* 0x7CC */ s32 unk7CC;
    /* 0x7D0 */ u8  pad7D0[0x14];
                u8  unk7E4;
                u8  pad7E5;
                u16 unk7E6;
    /* 0x7E8 */ f32 unk7E8;
    /* 0x7EC */ u32 pad7EC;
    /* 0x7F0 */ u32 pad7F0;
    /* 0x7F4 */ u16 unk7F4;
    /* 0x7F6 */ u16 unk7F6;
                f32 unk7F8;
                f32 unk7FC;
                f32 unk800;
    /* 0x7F8 */ u8  pad814[0x68];
    /* 0x86C */ f32 unk86C;
    /* 0x870 */ s32 unk870; // struct pointer
                f32 unk874;
                f32 unk878;
                f32 unk87C;
    /* 0x874 */ u8  pad880[0x3C];
    /* 0x8BC */ s32 unk8BC;
    /* 0x8C0 */ u8  pad8C0[0x2D];
                u8  unk8ED;
                u8  pad8EE[0xB1];
};

typedef struct {
    struct127 *unk0; // struct127 pointer?
    u8  unk4;
    u8  pad5[0x9];
    u8  unkE; // 6 bytes?
    s8  unkF;
    s16 unk10;
    u8  unk12;
    u8  pad13;
    struct226 *unk14;
    struct227 *unk18; // struct227 pointer?
    f32 unk1C;
    s32 unk20; // struct17 pointer?
    s8  unk24;
    u8  unk25;
    u8  pad26[0x2];
    s16 unk28;
    u8  unk2A;
    u8  pad2B[0x2];
    u8  unk2D;
    u8  pad2E[0x2];
    s32 unk30;
} struct225;

typedef struct {
    s32 unk0;
} struct36;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
} struct37;


typedef s32 OSIntMask;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char pad[0x174];
} Cam180;

typedef struct struct54 {
    struct struct54 *unk0; /* used */
    struct struct54 *unk4;
    u32 unk8; /* used */
    s32 unkC; /* used */
    s32 unk10;
    s8 unk14; /* used */
    u8 unk15; /* used */
    u8 unk16; /* used */
} struct54;
typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    u8  unkC[0x8];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8  pad2C[0x30];
    f32 unk5C;
} struct168;
typedef struct {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    u8  unk6[0x2E];
} struct178;
typedef struct {
    u8  pad0[0x48];
    u8  unk48;  // used
    u8  pad49;
    u8  pad4A;
    u8  pad4B;
    s32 unk4C; // used
} struct132;

#endif
