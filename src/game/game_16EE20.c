#include "types.h"

/*
 * Reviewed source unit: src/game/game_16EE20.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151419D0
 * - func_15141A7C
 * - func_15141C0C
 * - func_15141CC0
 * - func_15141DA4
 * - func_15141E38
 * - func_15141F78
 * - func_151420F8
 * - func_15142180
 * - func_15142314
 * - func_151423D8
 * - func_15142444
 * - func_151424F4
 * - func_15142600
 * - func_15142838
 * - func_15142B7C
 * - func_15142C10
 * - func_15142CF0
 * - func_15142FBC
 * - func_15143044
 * - func_1514306C
 * - func_15143134
 * - func_151432BC
 * - func_151436B4
 * - func_1514373C
 * - func_15143794
 * - func_15143874
 * - func_151438D8
 * - func_15143D18
 * - func_15143DA8
 * - func_15143E94
 * - func_1514401C
 * - func_151441A4
 * - func_151442FC
 * - func_151444DC
 * - func_15144528
 * - func_15144598
 * - func_1514462C
 * - func_1514470C
 * - func_15144A74
 * - func_15144B68
 * - func_15144C8C
 * - func_15144CEC
 * - func_15144E80
 * - func_151450B4
 * - func_15145128
 * - func_151451F0
 * - func_151452C4
 * - func_151454BC
 * - func_15145548
 * - func_1514563C
 * - func_15145740
 * - func_15145AD8
 * - func_15145C90
 * - func_15145CD0
 * - func_15145DB4
 * - func_15145EA4
 * - func_15146078
 * - func_151462C8
 * - func_151464B8
 * - func_1514654C
 * - func_1514672C
 * - func_151467A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);

void func_15141970(s32 *arg0) {
    func_1514EDF0((s32)arg0, arg0[0xB]);
}
void func_15141990(s32 *arg0) {
    func_15141970(arg0);
}
void func_151419B0(s32 *arg0) {
    func_15141970(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151419D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141C0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141CC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141DA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141E38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141F78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151420F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142180.s")
s32 func_151422C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return (arg3 + arg2) >> 1;
}
s32 func_151422DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
s32 func_151422F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
extern u8 D_800C3E90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142314 CURRENT (970) */
void func_15142314(s32 arg0, s32 arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = arg0 + (arg1 << 6);
    if (D_800C3E90 != 0) {
        temp_v0_2 = arg0 + (arg1 << 6);
        *(f32 *)((u8 *)arg2 + 0) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x38) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x18) << 0x10)) * 0.000015258789f);
        *(f32 *)((u8 *)arg2 + 4) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x3A) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x1A) << 0x10)) * 0.000015258789f);
        *(f32 *)((u8 *)arg2 + 8) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x3C) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x1C) << 0x10)) * 0.000015258789f);
        return;
    }
    *(f32 *)((u8 *)arg2 + 0) = (f32) *(f32 *)((u8 *)temp_v0 + 0x30);
    *(f32 *)((u8 *)arg2 + 4) = (f32) *(f32 *)((u8 *)temp_v0 + 0x34);
    *(f32 *)((u8 *)arg2 + 8) = (f32) *(f32 *)((u8 *)temp_v0 + 0x38);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142314 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142314.s")
extern f32 D_8009A220[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151423D8 CURRENT (35) */
f32 func_151423D8(u8 arg0) {
    s32 temp_t0;
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = arg0;
    if (temp_v0 & 0x40) {
        var_v1 = 0x40 - (temp_v0 & 0x3F);
    } else {
        var_v1 = temp_v0 & 0x3F;
    }
    temp_t0 = temp_v0 & 0xC0;
    if ((temp_t0 == 0) || (temp_t0 == 0xC0)) {
        return D_8009A220[var_v1];
    }
    return -D_8009A220[var_v1];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151423D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151423D8.s")
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142444 CURRENT (1354) */
void *func_15142444(s32 arg0, void *arg1) {
    u8 temp_t6;
    void *temp_v0;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0xFF) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        goto block_13;
    }
    if ((arg1 != 0) && (*(s32 *)((u8 *)arg1 + 0) != 0) && (temp_t6 == *(u8 *)((u8 *)arg1 + 0x3B))) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        goto block_13;
    }
    temp_v0 = func_15083E90(temp_t6);
    if ((temp_v0 != 0) && (*(s32 *)((u8 *)temp_v0 + 0x1D4) != 0)) {
        return temp_v0;
    }
block_13:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142444 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151424F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142838.s")
/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);

void func_15142914(void *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_150A8050(arg0, arg3, arg4, arg5);
    *(f32 *)((u8 *)arg0 + 0x30) = arg6;
    *(f32 *)((u8 *)arg0 + 0x34) = arg7;
    *(f32 *)((u8 *)arg0 + 0x38) = arg8;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg1);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg1);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg1);
}
s32 func_150ADA20(); /* extern */
extern u8 D_8008A160[];

void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *entry;

    entry = ((func_150ADA20() & 3) * 3) + (arg0 * 0xC) + D_8008A160;
    *arg1 = entry[0];
    *arg2 = entry[1];
    *arg3 = entry[2];
}
s32 func_15142A5C(void *arg0) {
    s16 *state = *(s16 **)((u8 *)arg0 + 0x2D0);

    if (state[0x1E] > 0) {
        return 1;
    }
    return 0;
}
extern f32 D_800A5624;

f32 func_15142A80(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * D_800A5624;
}
f32 func_15142AC0(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
extern f32 D_800A5628;

f32 func_15142B44(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * D_800A5628;
}
extern s32 D_800DD1FC;
extern s32 D_800DD200;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142B7C CURRENT (740) */
s32 *func_15142B7C(s32 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;
    s32 *temp_v0_2;
    s32 *var_a0;

    var_a0 = arg0;
    temp_v0 = var_a0;
    if (~D_800DD200 & arg2) {
        *(s32 *)((u8 *)temp_v0 + 0) = (~arg2 & 0xFFFFFF) | 0xD9000000;
        var_a0 += 8;
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
        D_800DD200 |= arg2;
    }
    temp_v0_2 = var_a0;
    if (~D_800DD1FC & arg1) {
        var_a0 += 8;
        *(s32 *)((u8 *)temp_v0_2 + 0) = 0xD9FFFFFF;
        *(s32 *)((u8 *)temp_v0_2 + 4) = arg1;
        D_800DD1FC |= arg1;
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142B7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B7C.s")
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;
extern s16 D_800DD1CE;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142C10 CURRENT (2870) */
void *func_15142C10(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u8 *arg5) {
    u8 *var_s0;

    var_s0 = arg0;
    if ((arg1 != D_800DD1C8) || (arg2 != D_800DD1CA) || (arg3 != D_800DD1CC) || (arg4 != D_800DD1CE)) {
        if (*arg5 == 1) {
            *(s32 *)((u8 *)var_s0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)var_s0 + 4) = 0;
            var_s0 += 8;
            *arg5 = 0;
        }
        *(s32 *)((u8 *)var_s0 + 0) = 0xFB000000;
        *(s32 *)((u8 *)var_s0 + 4) = (s32) ((arg1 << 0x18) | ((arg2 & 0xFF) << 0x10) | ((arg3 & 0xFF) << 8) | (arg4 & 0xFF));
        var_s0 += 8;
        D_800DD1C8 = arg1;
        D_800DD1CA = arg2;
        D_800DD1CC = arg3;
        D_800DD1CE = (s16) arg4;
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142C10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142C10.s")
extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;
extern s16 D_800DD204;
extern s16 D_800DD206;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142CF0 CURRENT (3067) */
void *func_15142CF0(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7) {
    u8 *var_s0;

    var_s0 = arg0;
    if ((arg1 != D_800DD204) || (arg2 != D_800DD206) || (arg3 != D_800DD1C0) || (arg4 != D_800DD1C2) || (arg5 != D_800DD1C4) || (arg6 != D_800DD1C6)) {
        if (*arg7 == 1) {
            *(s32 *)((u8 *)var_s0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)var_s0 + 4) = 0;
            var_s0 += 8;
            *arg7 = 0;
        }
        *(s32 *)((u8 *)var_s0 + 0) = (s32) (((arg1 & 0xFF) << 8) | 0xFA000000 | (arg2 & 0xFF));
        *(s32 *)((u8 *)var_s0 + 4) = (s32) ((arg3 << 0x18) | ((arg4 & 0xFF) << 0x10) | ((arg5 & 0xFF) << 8) | (arg6 & 0xFF));
        var_s0 += 8;
        D_800DD204 = arg1;
        D_800DD206 = arg2;
        D_800DD1C0 = arg3;
        D_800DD1C2 = (s16) arg4;
        D_800DD1C4 = (s16) arg5;
        D_800DD1C6 = (s16) arg6;
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142CF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142CF0.s")
s32 func_15094FE8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_1514306C(s32, s32, s32, u8);               /* extern */
extern u8 D_800BE616;
extern s32 D_800BE9F0;
extern s32 D_800DD1B0;
extern s32 D_800DD208;
extern s32 D_800DD20C;
extern s32 D_800DD210;
extern s32 D_800DD214;

s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 arg10) {
    s32 temp_v0;
    s32 sp3C;
    s32 temp_v0_2;

    temp_v0 = func_1514306C(arg1, arg6, arg2 >> 0x10, arg7);
    if ((temp_v0 != D_800DD1B0) || (arg3 != D_800DD208) || (arg4 != D_800DD20C) || (arg5 != D_800DD210) || (arg8 != D_800DD214)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x13) || (D_800BE9F0 == 6) || (D_800BE9F0 == 0x3B) || (D_800BE9F0 == 2) || (D_800BE616 != 0)) {
            arg10 = 3;
        }
        sp3C = temp_v0;
        temp_v0_2 = func_15094FE8(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, arg10);
        D_800DD1B0 = temp_v0;
        D_800DD208 = arg3;
        D_800DD20C = arg4;
        D_800DD210 = arg5;
        arg0 = temp_v0_2;
        D_800DD214 = D_800DD214;
    }
    return arg0;
}
extern s32 D_800DD218;
extern s32 D_800DD21C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142FBC CURRENT (1600) */
void *func_15142FBC(void *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 *temp_v0;
    u8 *var_a0;

    var_a0 = arg0;
    if ((arg1 != D_800DD218) || (arg2 != D_800DD21C)) {
        temp_v0 = var_a0;
        if (*arg3 == 1) {
            var_a0 += 8;
            *(s32 *)((u8 *)temp_v0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)temp_v0 + 4) = 0;
            *arg3 = 0;
        }
        *(s32 *)((u8 *)var_a0 + 0) = (s32) (((arg1 | 0xF) & 0xFFFFFF) | 0xEF000000);
        *(s32 *)((u8 *)var_a0 + 4) = arg2;
        var_a0 += 8;
        D_800DD218 = arg1;
        D_800DD21C = arg2;
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142FBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142FBC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143044 CURRENT (214) */
s16 func_15143044(s32 arg0, s32 arg1) {
    return (s16) (0x7FFF - (arg0 & 0xFF));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143044 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143044.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514306C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151432BC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15047C00(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151436B4 CURRENT (1233) */
void func_151436B4(f32 arg0, f32 arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv1;

    sp24 = func_15047C00(arg0);
    sp20 = func_15047D60(arg0);
    sp1C = func_15047C00(arg1);
    temp_fv1 = arg2 * sp1C;
    {
        f32 temp_ft4 = -arg2 * func_15047D60(arg1);
    *(f32 *)((u8 *)arg3 + 0) = (f32) (temp_fv1 * sp20);
    *(f32 *)((u8 *)arg3 + 4) = temp_ft4;
    *(f32 *)((u8 *)arg3 + 8) = (f32) (temp_fv1 * sp24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151436B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151436B4.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514373C CURRENT (10) */
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;

    sp1C = func_15047C00(arg0);
    *arg2 = arg1 * func_15047D60(arg0);
    *arg3 = arg1 * sp1C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514373C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514373C.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143794 CURRENT (2025) */
void func_15143794(u8 arg0, u8 arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 temp_fv1;
    f32 sp20;
    f32 sp1C;
    f32 temp_ft4;

    sp24 = func_151423D8(arg0);
    sp20 = func_151423D8(((s16) arg0 - 0x40) & 0xFF);
    sp1C = func_151423D8(arg1);
    temp_fv1 = arg2 * sp1C;
    temp_ft4 = -arg2 * func_151423D8(((s16) arg1 - 0x40) & 0xFF);
    *(f32 *)((u8 *)arg3 + 0) = (f32) (temp_fv1 * sp20);
    *(f32 *)((u8 *)arg3 + 4) = temp_ft4;
    *(f32 *)((u8 *)arg3 + 8) = (f32) (temp_fv1 * sp24);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143794 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143794.s")
extern void func_15143794(s16 arg0, s16 arg1, f32 arg2, void *arg3);

void func_15143834(s16 arg0, s16 arg1, f32 arg2, void *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
f32 func_151423D8(u8);                              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143874 CURRENT (535) */
void func_15143874(u8 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;

    sp1C = func_151423D8(arg0);
    *arg2 = arg1 * func_151423D8(((s16) arg0 - 0x40) & 0xFF);
    *arg3 = arg1 * sp1C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143874 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143874.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151438D8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143D18 CURRENT (390) */
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;

    var_a2 = arg2;
    var_a3 = arg3;
    temp_v1 = var_a2 ^ var_a3;
    if (var_a3 < var_a2) {
        temp_a1 = var_a3 ^ temp_v1;
        var_a3 = temp_a1;
        var_a2 = temp_a1 ^ temp_v1;
    }
    temp_v1_2 = *arg1;
    var_a1 = *arg0;
    temp_v0 = var_a1 ^ temp_v1_2;
    if (temp_v1_2 < var_a1) {
        *arg0 = temp_v0;
        temp_a0 = *arg1 ^ temp_v0;
        *arg1 = temp_a0;
        var_a1 = *arg0 ^ temp_a0;
        *arg0 = var_a1;
    }
    if (var_a1 < var_a2) {
        *arg0 = var_a2;
    }
    if (var_a3 < *arg1) {
        *arg1 = var_a3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143D18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143D18.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143DA8 CURRENT (530) */
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a2;

    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a2 < var_a1) {
        {
            s32 temp_v1 = var_a1 ^ var_a2;
        temp_a3 = var_a2 ^ temp_v1;
        var_a2 = temp_a3;
        var_a1 = temp_v1 ^ temp_a3;
    }
    temp_v0 = *arg0;
    if (temp_v0 < var_a1) {
        *arg0 = var_a1;
        return 1;
    }
    if (var_a2 < temp_v0) {
        *arg0 = var_a2;
        return 2;
    }
    return 0;
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143DA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143DA8.s")
s32 func_15143E08(u16 *arg0) {
    return (((s32)arg0[0x3D] >> 8) + 0x40) & 0xFF;
}
s16 func_15143E24(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v1 != 0) {
        return (s16) ((s32) (*(u16 *)((u8 *)arg0 + 0x7A) - *(s16 *)((u8 *)temp_v1 + 0x12)) >> 8);
    }
    return (s16) ((s32) *(u16 *)((u8 *)arg0 + 0x7A) >> 8);
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15143E64(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514401C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151441A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151442FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151444DC CURRENT (610) */
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;

    var_a0 = arg0;
    if (arg1 < var_a0) {
        do {
            var_a0 -= (arg1 - arg2) + 1;
        } while (arg1 < var_a0);
    }
    if (var_a0 < arg2) {
        do {
            var_a0 += (arg1 - arg2) + 1;
        } while (var_a0 < arg2);
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151444DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151444DC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144528 CURRENT (270) */
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_fa0;

    var_fa0 = arg0;
    if (arg1 < var_fa0) {
        do {
            var_fa0 -= arg1 - arg2;
        } while (arg1 < var_fa0);
    }
    if (var_fa0 < arg2) {
        do {
            var_fa0 += arg1 - arg2;
        } while (var_fa0 < arg2);
    }
    return var_fa0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144528 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144528.s")
extern f32 D_800A5694;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144598 CURRENT (10) */
f32 func_15144598(void *arg0) {
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {                              /* irregular */
    default:
        var_fv1 = 1.0f;
        break;
    case 2:
        var_fv1 = (f32) (*(s16 *)((u8 *)arg0 + 6) * *(s16 *)((u8 *)arg0 + 0xA)) * 4.0f;
        break;
    case 0:
    case 1:
        temp_v0 = *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = (f32) (temp_v0 * temp_v0) * D_800A5694;
        break;
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144598 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144598.s")
extern f32 D_800A5698;
extern f32 D_800A569C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514462C CURRENT (25) */
f32 func_1514462C(void *arg0) {
    f32 temp_fv0;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {                              /* irregular */
    default:
        var_fv1 = 1.0f;
        break;
    case 2:
        var_fv1 = (f32) (*(s16 *)((u8 *)arg0 + 6) * *(s16 *)((u8 *)arg0 + 8) * *(s16 *)((u8 *)arg0 + 0xA));
        break;
    case 0:
        temp_v0 = *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = (f32) (temp_v0 * temp_v0) * D_800A5698 * (f32) *(s16 *)((u8 *)arg0 + 8);
        break;
    case 1:
        temp_fv0 = (f32) *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = temp_fv0 * D_800A569C * temp_fv0 * temp_fv0;
        break;
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514462C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514462C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144A74 CURRENT (20) */
f32 func_15144A74(void *arg0, void *arg1) {
    return (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144A74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144A74.s")
extern s32 D_800DBFF0;

f32 func_15144AA8(s32 arg0) {
    f32 var_fv1;

    var_fv1 = *(f32 *)((u8 *)D_800DBFF0 + (arg0 * 0x9A0) + 0x380);
    if (var_fv1 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}

s32 func_15144B34(s32 arg0) {
    return (arg0 * 0x9A0) + D_800DBFF0 + 0x2F8;
}
extern f32 D_800A56A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144B68 CURRENT (60) */
f32 func_15144B68(f32 arg0) {
    f32 var_fv1;

    var_fv1 = arg0;
    if (D_800A56A4 < arg0) {
        do {
            var_fv1 -= D_800A56A4;
        } while (D_800A56A4 < var_fv1);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += D_800A56A4;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144B68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144B68.s")
f32 func_15144BC8(f32 arg0) {
    f32 var_fv1;

    var_fv1 = arg0;
    if (arg0 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}
s16 func_15144C2C(s16 arg0) {
    s16 var_v1;

    var_v1 = arg0;
    if (arg0 >= 0x100) {
        do {
            var_v1 -= 0xFF;
        } while (var_v1 >= 0x100);
    }
    if (var_v1 < 0) {
        do {
            var_v1 += 0xFF;
        } while (var_v1 < 0);
    }
    return var_v1;
}
extern f32 D_800A56A8;
extern f32 D_800A56AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144C8C CURRENT (1703) */
f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 var_fv1;

    arg0 = func_15144B68(arg0);
    {
        f32 temp_fv0 = fabsf(arg0 - func_15144B68(arg1));
    var_fv1 = temp_fv0;
    if (D_800A56A8 < temp_fv0) {
        var_fv1 = D_800A56AC - temp_fv0;
    }
    return var_fv1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144C8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144C8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144E80.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151450B4 CURRENT (50) */
void func_151450B4(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) ((*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 4)));
    *(f32 *)((u8 *)arg2 + 4) = (f32) ((*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 8)));
    *(f32 *)((u8 *)arg2 + 8) = (f32) ((*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 0)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151450B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151450B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145128.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151451F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151452C4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151454BC CURRENT (610) */
s32 func_151454BC(u8 arg0, f32 arg1, void *arg2) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v0;
    void *temp_v0;

    temp_v0 = func_15144B34((s32) arg0);
    temp_fv0 = *(f32 *)((u8 *)arg2 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg2 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    var_v0 = 1;
    temp_fa0 = *(f32 *)((u8 *)arg2 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    if ((arg1 * arg1) < ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0))) {
        var_v0 = 0;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151454BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151454BC.s")
s32 func_1514563C(f32 *);                           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145548 CURRENT (3785) */
void func_15145548(void *arg0, void *arg1, void *arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_fv0;

    if (arg4 == 0) {
        arg4 = &sp24;
    }
    if (func_1514563C(arg4) != 0) {
        temp_fv0 = *arg4;
        if (temp_fv0 < 0.0f) {
            *(f32 *)((u8 *)arg3 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0);
            *(f32 *)((u8 *)arg3 + 4) = (f32) *(f32 *)((u8 *)arg0 + 4);
            goto block_8;
        }
        if (temp_fv0 > 1.0f) {
            *(f32 *)((u8 *)arg3 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + *(f32 *)((u8 *)arg1 + 0));
            *(f32 *)((u8 *)arg3 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + *(f32 *)((u8 *)arg1 + 4));
            *(f32 *)((u8 *)arg3 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)arg1 + 8));
        }
    } else {
        *(f32 *)((u8 *)arg3 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0);
        *(f32 *)((u8 *)arg3 + 4) = (f32) *(f32 *)((u8 *)arg0 + 4);
block_8:
        *(f32 *)((u8 *)arg3 + 8) = *(f32 *)((u8 *)arg0 + 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514563C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_800A56BC;
extern f32 D_800A56C0;

void func_15145974(void *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_ft4;
    f32 temp_fv1;

    *arg1 = func_150484A0(*(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 8)) * D_800A56BC;
    if (arg2 != 0) {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
        temp_ft4 = *(f32 *)((u8 *)arg0 + 8);
        *arg2 = (func_150484A0(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), *(f32 *)((u8 *)arg0 + 4)) * D_800A56C0) - 90.0f;
    }
}
extern f32 D_800A548C[];

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32) (arg0 * arg2 * 100.0f)] * arg1;
}
/* Call context: func_15053694: unique active project prototype */
void func_15053694(u8 *);

void func_15145A50(u8 *arg0) {
    s32 temp_v0;
    void *temp_v0_2;

    *(s8 *)((u8 *)arg0 + 5) = 3;
    if (D_800BE9F0 != 0x33) {
        if ((D_800BE616 != 0) || (temp_v0 = *(s32 *)((u8 *)arg0 + 0), (temp_v0 == 5)) || (temp_v0 == 1) || (temp_v0 == 0x15)) {
            temp_v0_2 = *(void **)((u8 *)arg0 + 0x31C);
            *(s32 *)((u8 *)arg0 + 0) = 5;
            if (temp_v0_2 != 0) {
                *(s8 *)((u8 *)temp_v0_2 + 0x78) = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145C90 CURRENT (200) */
s32 func_15145C90(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    }
    return ((*(u8 *)((u8 *)(D_800DBEF4 + (arg0 * 0xA0)) + 0x6F) & 0x80) == 0x80) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145CD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145DB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151462C8.s")
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151464B8 CURRENT (245) */
s32 func_151464B8(void *arg0) {
    s16 var_v1;
    s32 temp_t7;
    s32 var_v0;

    var_v0 = 0;
    var_v1 = 0;
    if (D_80082FA0 >= 0) {
        do {
            temp_t7 = 1 << var_v0;
            var_v0 += 1;
            var_v1 |= temp_t7;
        } while (D_80082FA0 >= var_v0);
    }
    return ((*(s16 *)((u8 *)arg0 + 2) & var_v1) == 0) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151464B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151464B8.s")
extern void func_15169040(s32 arg0, u8 arg1);

void func_15146508(void *arg0, void *arg1) {
    struct {
        void *field0;
        void *field4;
        u8 field8;
        u8 field9;
    } sp1C;

    sp1C.field0 = arg0;
    sp1C.field4 = arg1;
    sp1C.field8 = *(u8 *)((u8 *) arg0 + 0x3B);
    sp1C.field9 = *(u8 *)((u8 *) arg1 + 0x3B);
    func_15169040((s32) &sp1C, 0x2D);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514654C.s")
extern f32 D_800A56C4;
extern f32 D_800A56C8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514672C CURRENT (2550) */
s32 func_1514672C(void *arg0) {
    f32 temp_fv0;

    if ((D_800A56C4 < fabsf(*(f32 *)((u8 *)arg0 + 0))) || (D_800A56C4 < fabsf(*(f32 *)((u8 *)arg0 + 8))) || (temp_fv0 = *(f32 *)((u8 *)arg0 + 4), (D_800A56C4 < temp_fv0)) || (temp_fv0 < D_800A56C8)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514672C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514672C.s")
s32 func_150ADA20(f32 *);                           /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151467A4 CURRENT (10) */
void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    f32 temp_fv0;

    *arg0 -= D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if (func_150ADA20(arg0) & 3) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    temp_fv0 = *arg7;
    *arg7 = temp_fv0 + ((*arg2 - temp_fv0) * arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151467A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151467A4.s")
