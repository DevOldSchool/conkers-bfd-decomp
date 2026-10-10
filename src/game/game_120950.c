#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_120950.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F34F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800A1980;
extern f32 D_800A1984;

f32 func_150F34A0(s32 arg0, f32 arg1) {
    f32 var_fv1;

    if (arg1 < -5.0f) {
        var_fv1 = (arg1 * D_800A1980) + D_800A1984;
    } else {
        var_fv1 = 0.75f;
    }
    return var_fv1;
}
typedef struct Game120950Actor {
    s32 field_0;
    u8 field_4;
    u8 pad5[0x13];
    f32 field_18;
    u8 pad1C[0x4];
    f32 field_20;
    f32 field_24;
    f32 field_28;
    u8 pad2C[0x10];
    f32 field_3C;
    f32 field_40;
    f32 field_44;
    u8 pad48[0x2E];
    u16 field_76;
    u16 field_78;
    s16 field_7A;
    u8 pad7C[0x2];
    u8 field_7E;
    u8 pad7F[0x1];
    u8 field_80;
    u8 pad81[0x2];
    u8 field_83;
    u8 pad84[0x2];
    u8 field_86;
    u8 pad87[0x24];
    u8 field_AB;
    u8 padAC[0x1];
    u8 field_AD;
    u8 padAE[0xA];
    f32 field_B8;
    u8 padBC[0x4];
    f32 field_C0;
    f32 field_C4;
    u8 padC8[0x30];
    s32 field_F8;
    u8 padFC[0x6];
    u8 field_102;
    u8 field_103;
    u8 field_104;
    u8 pad105[0x13];
    f32 field_118;
    u8 pad11C[0x20];
    u8 field_13C;
    u8 field_13D;
    u8 pad13E[0x8C];
    u8 field_1CA;
    u8 pad1CB[0x1];
    f32 field_1CC;
    u8 pad1D0[0x48];
    s32 field_218;
    u8 pad21C[0x6];
    u8 field_222;
    u8 pad223[0xF];
    u8 field_232;
    u8 pad233[0x29];
    s32 field_25C;
    u8 pad260[0xCC];
} Game120950Actor;
typedef struct { u16 buttons; s8 stickX; s8 stickY; } Game120950Input;

void func_150585F0(u8 *, f32);
void func_15059140(u8 *);
/* Raw callee overwrites a2 at 15059628 before reading it. */
void func_1505959C(void *, s32);
void func_150599C8(u8 *, s32, u16);
void func_1505A3A8(f32, void *, f32, f32, u8);
f32 func_1505A5CC(void *);
s32 func_1505A630(f32, f32, s32);
void func_1506E5FC(void);
void func_1506E8D8(void);
f32 func_150F34A0(s32, f32);

void func_1505E650(void *, s32, f32, f32, f32, f32, s32);
/* Raw callee consumes global D_800D1580, not incoming arguments. */
void func_15073FA0(void);
f32 fabsf(f32);
#pragma intrinsic (fabsf)
extern s32 D_80082FA0;
extern f32 D_800A1988;
extern f32 D_800A198C;
extern f32 D_800A1990;
extern f32 D_800A1994;
extern f32 D_800A1998;
extern f32 D_800A199C;
extern f32 D_800A19A0;
extern f32 D_800A19A4;
extern f32 D_800A19A8;
extern f32 D_800A19AC;
extern f32 D_800A19B0;
extern f32 D_800A19B4;
extern f32 D_800A19B8;
extern f32 D_800A19BC;
extern f32 D_800A19C0;
extern f32 D_800A19C4;
extern f32 D_800A19C8;
extern f32 D_800A19CC;
extern f32 D_800A19D0;
extern f32 D_800A19D4;
extern u16 D_800BE710;
extern void **D_800BE728;
extern s32 D_800BE9F0;
extern u8 D_800C3E78;
extern s8 D_800CBDD3;
extern u8 D_800CC26D;
extern s32 D_800CC280;
extern void *D_800CC284;
extern s32 D_800CC288;
extern u8 D_800CC2D0[];                             /* unknown layout; byte-addressed storage */
extern u8 D_800CC5FC[];                             /* unknown layout; byte-addressed storage */
extern u8 D_800D121C[];                             /* unknown layout; byte-addressed storage */
extern void *D_800D154C;
extern f32 D_800D1550;
extern s32 D_800D1580;
extern f32 D_800DDDC8[];                             /* unknown layout; byte-addressed storage */
extern u8 D_800DDE3C[];                             /* unknown layout; byte-addressed storage */
extern u8 D_800E0B94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F34F4 CURRENT (17895) */
void func_150F34F4(u8 *arg0) {
    u16 sp7E;
    f32 sp6C;
    f32 sp68;
    f32 sp58;
    s32 sp50;
    f32 sp48;
    u8 *sp34;
    u8 *var_a1;
    u8 *var_v0_2;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 temp_a1;
    s32 temp_cond;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_t9;
    u16 var_v0;
    void *temp_a2;
    void *temp_t2;
    void *temp_v0_3;
    void *temp_v0_6;

    sp58 = 0.0f;
    ((Game120950Actor *) arg0)->field_AB = 1;
    ((Game120950Actor *) arg0)->field_80 = 1;
    ((Game120950Actor *) arg0)->field_222 = 0;
    D_800CC288 = (s32) D_800BE710;
    temp_t2 = *D_800BE728;
    temp_v0 = D_800C3E78;
    D_800CC284 = temp_t2;
    if ((D_80082FA0 >= (s32) temp_v0) && (*(((u8 *) D_800DDE3C) + temp_v0) != 0) && (D_800DDDC8[temp_v0] > 0.75f) && (D_800E0B94 != 2)) {
        ((Game120950Input *) temp_t2)->stickX = 0;
        ((Game120950Input *) D_800CC284)->stickY = 0;
        ((Game120950Input *) D_800CC284)->buttons = 0U;
        D_800CC288 = 0;
    }
    temp_v0_2 = ((Game120950Actor *) arg0)->field_103;
    ((Game120950Actor *) arg0)->field_F8 = (s32) (((Game120950Actor *) arg0)->field_F8 | 0x40);
    ((Game120950Actor *) arg0)->field_1CC = (f32) ((Game120950Actor *) arg0)->field_18;
    if (temp_v0_2 != 0) {
        ((Game120950Actor *) arg0)->field_103 = (u8) (temp_v0_2 - 1);
    }
    if (((Game120950Actor *) arg0)->field_104 != 0) {
        func_150585F0(arg0, 0.25f);
        func_15059140(arg0);
        temp_v1 = ((Game120950Actor *) arg0)->field_13C;
        ((Game120950Actor *) arg0)->field_40 = (f32) ((f32) (((Game120950Actor *) arg0)->field_7A + 0x4000) * 0.005493164f);
        if (temp_v1 != 0) {
            temp_v0_3 = ((temp_v1 - 0x64) * 0x32C) + ((u8 *) D_800CC2D0);
            ((Game120950Actor *) temp_v0_3)->field_13D = 0;
            temp_t4 = ((Game120950Actor *) temp_v0_3)->field_F8 & ~0x400;
            ((Game120950Actor *) temp_v0_3)->field_232 = 0x21;
            ((Game120950Actor *) temp_v0_3)->field_218 = 0;
            ((Game120950Actor *) temp_v0_3)->field_104 = 0;
            ((Game120950Actor *) temp_v0_3)->field_F8 = temp_t4;
            ((Game120950Actor *) temp_v0_3)->field_3C = (f32) ((Game120950Actor *) arg0)->field_3C;
            ((Game120950Actor *) arg0)->field_13C = 0U;
        }
    } else if (((Game120950Actor *) arg0)->field_102 == 0) {
        ((Game120950Actor *) arg0)->field_AD = 0;
        sp7E = func_1505A630((f32) ((Game120950Input *) D_800CC284)->stickX, (f32) ((Game120950Input *) D_800CC284)->stickY, 0);
        var_fv1 = func_1505A5CC(D_800CC284);
        if (((Game120950Input *) D_800CC284)->buttons & 0x10) {
            var_fv1 = 0.0f;
        }
        ((Game120950Actor *) arg0)->field_78 = (u16) ((Game120950Actor *) arg0)->field_7A;
        if (var_fv1 > 1.0f) {
            ((Game120950Actor *) arg0)->field_78 = (u16) ((sp7E + D_800CC280) & 0xFFFF);
        }
        ((Game120950Actor *) arg0)->field_232 = 7;
        ((Game120950Actor *) arg0)->field_218 = 0;
        ((Game120950Actor *) arg0)->field_44 = (f32) (var_fv1 * D_800A1988);
        if ((D_800CC288 & 0xC000) || (((Game120950Actor *) arg0)->field_28 > 100.0f)) {
            ((Game120950Actor *) arg0)->field_232 = 8;
            ((Game120950Actor *) arg0)->field_102 = 1U;
        }
        func_15052590(arg0);
        if (D_800CC26D != 0) {
            if (((Game120950Actor *) arg0)->field_28 > 30.0f) {
                D_800D1580 = 0xFF010074;
                func_1506E8D8();
                func_1505959C(D_800CC2D0 + ((D_800CC26D - 100) * 0x32C), (s32) D_800C3E78);
                ((Game120950Actor *) arg0)->field_102 = 1U;
                ((Game120950Actor *) arg0)->field_13C = (u8) D_800CC26D;
            }
            ((Game120950Actor *) arg0)->field_20 = 23.0f;
        }
        if (((Game120950Actor *) arg0)->field_18 < ((Game120950Actor *) arg0)->field_118) {
            ((Game120950Actor *) arg0)->field_102 = 1U;
            ((Game120950Actor *) arg0)->field_86 = 1U;
            ((Game120950Actor *) arg0)->field_20 = -6.0f;
        }
    } else {
        sp68 = ((Game120950Actor *) arg0)->field_3C;
        if (sp68 > 60.0f) {
            sp68 = 60.0f;
        }
        sp6C = (f32) ((Game120950Input *) D_800CC284)->stickY * 1.25f;
        temp_t6 = ((Game120950Input *) D_800CC284)->buttons & 0x10;
        if (temp_t6 != 0) {
            sp6C = 0.0f;
        }
        if (((Game120950Actor *) arg0)->field_13C != 0) {
            if (temp_t6 == 0) {
                ((Game120950Actor *) arg0)->field_18 = (f32) (((Game120950Actor *) arg0)->field_18 - (16.0f * D_800D1550));
            }
        } else {
            var_fv1_2 = 1000.0f;
            var_a1 = (u8 *) D_800CC2D0;
            var_v1 = 0;
            do {
                if ((((Game120950Actor *) var_a1)->field_0 != 0) && (((Game120950Actor *) var_a1)->field_1CA != 0) && (((Game120950Actor *) var_a1)->field_28 == 0.0f) && (((Game120950Actor *) var_a1)->field_232 != 0x21) && ((temp_v0_4 = ((Game120950Actor *) var_a1)->field_4, (temp_v0_4 == 0x9C)) || (temp_v0_4 == 0x9D))) {
                    sp50 = var_v1;
                    sp34 = var_a1;
                    sp48 = var_fv1_2;
                    temp_fv0 = func_1505A6F8(D_800D154C, var_a1);
                    temp_cond = temp_fv0 < var_fv1_2;
                    if (temp_cond) {
                        ((Game120950Actor *) arg0)->field_222 = (s8) var_v1;
                        var_fv1_2 = temp_fv0;
                    }
                }
                var_v1 += 1;
                var_a1 += 0x32C;
            } while (var_v1 != 0x19);
        }
        if (sp6C < -90.0f) {
            sp6C = -90.0f;
        }
        if (sp6C > 90.0f) {
            sp6C = 90.0f;
        }
        if (D_800A198C < ((Game120950Actor *) arg0)->field_18) {
            temp_fv1 = ((Game120950Actor *) arg0)->field_20;
            if (temp_fv1 > -30.0f) {
                ((Game120950Actor *) arg0)->field_20 = (f32) (temp_fv1 - 1.5f);
            }
            sp6C = 40.0f;
        }
        temp_fv0_2 = ((Game120950Actor *) arg0)->field_C4;
        ((Game120950Actor *) arg0)->field_C4 = (f32) (temp_fv0_2 + (((f32) ((Game120950Input *) D_800CC284)->stickX - temp_fv0_2) * (D_800A1990 * D_800D1550)));
        temp_ft0 = ((Game120950Actor *) arg0)->field_C4 * D_800D1550 * D_800A1994;
        ((Game120950Actor *) arg0)->field_7E = 0x19;
        temp_t9 = ((Game120950Actor *) arg0)->field_76 - (s32) (temp_ft0 * ((100.0f - sp68) * D_800A1998) * 220.0f);
        ((Game120950Actor *) arg0)->field_76 = temp_t9;
        func_150599C8(arg0, 8, temp_t9 & 0xFFFF);
        ((Game120950Actor *) arg0)->field_C0 = 0.0f;
        sp68 = 0.0f;
        var_fv0 = D_800A199C;
        if (((Game120950Actor *) arg0)->field_18 < ((Game120950Actor *) arg0)->field_118) {
            if (((Game120950Actor *) arg0)->field_86 == 0) {
                ((Game120950Actor *) arg0)->field_86 = 1U;
                ((Game120950Actor *) arg0)->field_3C = 0.0f;
                ((Game120950Actor *) arg0)->field_20 = -6.0f;
            }
        } else if (((Game120950Actor *) arg0)->field_86 != 0) {
            ((Game120950Actor *) arg0)->field_86 = 0U;
            ((Game120950Actor *) arg0)->field_20 = 9.0f;
        }
        var_v0 = ((Game120950Input *) D_800CC284)->buttons;
        if (!(var_v0 & 0x10)) {
            if (var_v0 & 0x8000) {
                ((Game120950Actor *) arg0)->field_C0 = -22.0f;
                sp68 = 1.0f;
                var_fv0 = D_800A19A0;
                var_v0 = ((Game120950Input *) D_800CC284)->buttons;
            }
            if (var_v0 & 0x4000) {
                temp_fv1_2 = ((Game120950Actor *) arg0)->field_20;
                ((Game120950Actor *) arg0)->field_C0 = 30.0f;
                if (temp_fv1_2 < 0.0f) {
                    ((Game120950Actor *) arg0)->field_C0 = (f32) (((Game120950Actor *) arg0)->field_C0 - (temp_fv1_2 * D_800A19A4));
                }
                sp68 = 1.5f;
                var_fv0 = D_800A19A8;
            }
        }
        func_1505A3A8(((Game120950Actor *) arg0)->field_C0, arg0, sp68, var_fv0, 1U);
        ((Game120950Actor *) arg0)->field_40 = (f32) ((f32) (((Game120950Actor *) arg0)->field_7A + 0x4000) * 0.005493164f);
        ((Game120950Actor *) arg0)->field_24 = (f32) (sp6C * D_800A19AC * (200.0f - ((Game120950Actor *) arg0)->field_3C));
        if (((Game120950Actor *) arg0)->field_13C == 0) {
            if (((Game120950Actor *) arg0)->field_20 > 26.0f) {
                ((Game120950Actor *) arg0)->field_20 = 26.0f;
            }
            if (((Game120950Actor *) arg0)->field_20 < -34.0f) {
                ((Game120950Actor *) arg0)->field_20 = -34.0f;
            }
        }
        temp_fv0_3 = fabsf(sp6C * 0.5f);
        var_fa0 = temp_fv0_3;
        if (((Game120950Actor *) arg0)->field_86 != 0) {
            var_fa0 = temp_fv0_3 * D_800A19B0;
            ((Game120950Actor *) arg0)->field_24 = (f32) (((Game120950Actor *) arg0)->field_24 * D_800A19B4);
        }
        temp_fv0_4 = ((Game120950Actor *) arg0)->field_24;
        temp_fv1_3 = ((Game120950Actor *) arg0)->field_20;
        if (temp_fv0_4 == 0.0f) {
            if (fabsf(temp_fv1_3) < 1.5f) {
                ((Game120950Actor *) arg0)->field_20 = 0.0f;
            } else if (temp_fv1_3 > 0.0f) {
                ((Game120950Actor *) arg0)->field_24 = (f32) D_800A19B8;
            } else {
                ((Game120950Actor *) arg0)->field_24 = (f32) D_800A19BC;
            }
        } else {
            if (((var_fa0 * D_800A19C0) < temp_fv1_3) && (temp_fv0_4 < 0.0f)) {
                goto block_80;
            }
            if ((temp_fv1_3 < (-var_fa0 * 1.5f)) && (temp_fv0_4 > 0.0f)) {
block_80:
                ((Game120950Actor *) arg0)->field_24 = 0.0f;
            }
        }
        ((Game120950Actor *) arg0)->field_AD = 0xA;
        if (((Game120950Input *) D_800CC284)->buttons & 0x10) {
            temp_fv0_5 = ((Game120950Actor *) arg0)->field_B8;
            ((Game120950Actor *) arg0)->field_20 = 0.0f;
            ((Game120950Actor *) arg0)->field_24 = 0.0f;
            ((Game120950Actor *) arg0)->field_B8 = (f32) (temp_fv0_5 + (((f32) ((Game120950Input *) D_800CC284)->stickY - temp_fv0_5) * D_800A19C4));
        } else {
            temp_fv0_6 = (((Game120950Actor *) arg0)->field_20 - 0.0f) * -2.0f;
            ((Game120950Actor *) arg0)->field_B8 = temp_fv0_6;
            if (temp_fv0_6 > 40.0f) {
                ((Game120950Actor *) arg0)->field_B8 = 40.0f;
            } else if (((Game120950Actor *) arg0)->field_B8 < -55.0f) {
                ((Game120950Actor *) arg0)->field_B8 = -55.0f;
            }
        }
        sp68 = ((Game120950Actor *) arg0)->field_20;
        D_800CBDD3 = 1;
        func_15059140(arg0);
        D_800CBDD3 = 0;
        temp_v1_2 = ((Game120950Actor *) arg0)->field_13C;
        if ((temp_v1_2 != 0) && (((Game120950Actor *) arg0)->field_28 < 50.0f)) {
            sp58 = 50.0f;
        }
        if (!(((Game120950Input *) D_800CC284)->buttons & 0x10)) {
            temp_v0_5 = D_800CC26D;
            if ((temp_v0_5 != 0) && (temp_v1_2 == 0)) {
                temp_a2 = D_800CC2D0 + ((temp_v0_5 - 100) * 0x32C);
                if (((Game120950Actor *) temp_a2)->field_28 == 0.0f) {
                    ((Game120950Actor *) arg0)->field_20 = 20.0f;
                    ((Game120950Actor *) arg0)->field_18 = (f32) (((Game120950Actor *) temp_a2)->field_18 + 70.0f);
                    func_1505959C(D_800CC2D0 + ((D_800CC26D - 100) * 0x32C), (s32) D_800C3E78);
                    ((Game120950Actor *) arg0)->field_13C = (u8) D_800CC26D;
                    D_800D1580 = 0xFF010074;
                    func_1506E8D8();
                }
            }
            if (((Game120950Actor *) arg0)->field_13C != 0) {
                temp_a1 = ((Game120950Actor *) arg0)->field_25C;
                if (temp_a1 & 2) {
                    ((Game120950Actor *) arg0)->field_25C = (s32) (temp_a1 & ~2);
                    temp_v0_6 = ((u8 *) D_800CC2D0) + ((((Game120950Actor *) arg0)->field_13C - 0x64) * 0x32C);
                    ((Game120950Actor *) temp_v0_6)->field_13D = 0;
                    temp_t9_2 = ((Game120950Actor *) temp_v0_6)->field_F8;
                    ((Game120950Actor *) temp_v0_6)->field_232 = 0x21;
                    ((Game120950Actor *) temp_v0_6)->field_218 = 0;
                    ((Game120950Actor *) temp_v0_6)->field_104 = 0;
                    ((Game120950Actor *) temp_v0_6)->field_F8 = (s32) (temp_t9_2 & ~0x400);
                    ((Game120950Actor *) temp_v0_6)->field_3C = (f32) ((Game120950Actor *) arg0)->field_3C;
                    ((Game120950Actor *) arg0)->field_13C = 0U;
                    ((Game120950Actor *) arg0)->field_20 = 0.0f;
                    D_800D1580 = 0x76;
                    func_1506E8D8();
                }
            } else if ((D_800CC288 & 0x2000) && (((Game120950Actor *) arg0)->field_103 == 0)) {
                var_v1_2 = 0;
                if (D_800BE9F0 == 0x3C) {
                    var_v0_2 = (u8 *) D_800CC5FC;
                    do {
                        if ((((Game120950Actor *) var_v0_2)->field_0 != 0) && (((Game120950Actor *) var_v0_2)->field_4 == 0x25)) {
                            var_v1_2 += 1;
                        }
                        var_v0_2 += 0x32C;
                    } while (var_v0_2 != ((u8 *) D_800D121C));
                    if (var_v1_2 < 5) {
                        D_800D1580 = 6;
                        ((Game120950Actor *) arg0)->field_103 = 4U;
                        func_15073FA0();
                    }
                }
            }
        }
        if (((Game120950Actor *) arg0)->field_28 <= sp58) {
            ((Game120950Actor *) arg0)->field_3C = (f32) (((Game120950Actor *) arg0)->field_3C * D_800A19C8);
            if ((((Game120950Input *) D_800CC284)->buttons & 0x4000) || (((Game120950Actor *) arg0)->field_86 != 0) || (((Game120950Actor *) arg0)->field_13C != 0)) {
                if (((Game120950Actor *) arg0)->field_13C != 0) {
                    if (((Game120950Actor *) arg0)->field_20 < -10.0f) {
                        D_800D1580 = 0xFF0100A7;
                        func_1506E5FC();
                        D_800D1580 = 0xFF060372;
                        func_1506E8D8();
                    }
                } else if (((Game120950Actor *) arg0)->field_18 < 0.0f) {
                    D_800D1580 = 0xFF010072;
                    func_1506E8D8();
                }
                if (((Game120950Actor *) arg0)->field_13C == 0) {
                    ((Game120950Actor *) arg0)->field_20 = 20.0f;
                } else if (((Game120950Actor *) arg0)->field_86 == 0) {
                    ((Game120950Actor *) arg0)->field_20 = 38.0f;
                }
                sp6C = -80.0f;
            } else {
                ((Game120950Actor *) arg0)->field_102 = 0U;
                ((Game120950Actor *) arg0)->field_20 = (f32) (sp68 * -1.0f);
                ((Game120950Actor *) arg0)->field_B8 = 0.0f;
                ((Game120950Actor *) arg0)->field_28 = (f32) D_800A19CC;
            }
        }
        if (!(((Game120950Input *) D_800CC284)->buttons & 0x10)) {
            ((Game120950Actor *) arg0)->field_B8 = (f32) (((Game120950Actor *) arg0)->field_B8 + 20.0f);
        } else {
            ((Game120950Actor *) arg0)->field_20 = (f32) (((Game120950Actor *) arg0)->field_B8 * D_800A19D0);
        }
        if (((Game120950Actor *) arg0)->field_86 != 0) {
            ((Game120950Actor *) arg0)->field_83 = 0;
            if ((fabsf(sp6C) > 8.0f) || (((Game120950Actor *) arg0)->field_C0 > 7.0f)) {
                var_fv1_3 = 1.0f;
            } else {
                var_fv1_3 = 0.5f;
            }
        } else {
            var_fv1_3 = func_150F34A0((s32) arg0, sp6C);
        }
        var_v0_3 = 0xF;
        if ((((Game120950Actor *) arg0)->field_B8 > 40.0f) && (sp6C > 20.0f)) {
            var_v0_3 = 0x11;
        }
        temp_fv0_7 = ((Game120950Actor *) arg0)->field_3C;
        if ((temp_fv0_7 < 20.0f) && (((Game120950Actor *) arg0)->field_C0 <= 0.0f) && (sp6C == 0.0f)) {
            var_v0_3 = 0x18;
        }
        if (temp_fv0_7 < 0.0f) {
            var_v0_3 = 0x1F;
        }
        if (((Game120950Actor *) arg0)->field_13C != 0) {
            var_v0_3 = 0x17;
            var_fv1_3 += D_800A19D4;
        }
        func_1505E650(arg0, var_v0_3 & 0xFFFF, var_fv1_3, 9.0f, 0.0f, 0.0f, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F34F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_120950/func_150F34F4.s")
