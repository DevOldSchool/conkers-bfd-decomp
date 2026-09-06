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
 * - func_15142914
 * - func_151429E0
 * - func_15142A5C
 * - func_15142B7C
 * - func_15142C10
 * - func_15142CF0
 * - func_15142E24
 * - func_15142FBC
 * - func_15143044
 * - func_1514306C
 * - func_15143134
 * - func_151432BC
 * - func_151436B4
 * - func_1514373C
 * - func_15143794
 * - func_15143834
 * - func_15143874
 * - func_151438D8
 * - func_15143D18
 * - func_15143DA8
 * - func_15143E24
 * - func_15143E64
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
 * - func_15144AA8
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
 * - func_15145974
 * - func_15145A0C
 * - func_15145A50
 * - func_15145AD8
 * - func_15145C90
 * - func_15145CD0
 * - func_15145DB4
 * - func_15145EA4
 * - func_15146078
 * - func_151462C8
 * - func_151464B8
 * - func_15146508
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142314.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151423D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151424F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142914.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151429E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142A5C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142C10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142CF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142E24.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143834.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E24.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143E64 CURRENT (1035) */
f32 func_15143E64(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143E64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E64.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144598.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514462C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144A74 CURRENT (20) */
f32 func_15144A74(void *arg0, void *arg1) {
    return (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144A74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144A74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144AA8.s")
extern s32 D_800DBFF0;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151454BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514563C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145A0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146508.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151467A4.s")
