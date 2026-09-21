#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BC650.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518F1A0
 * - func_1518F384
 * - func_1518F45C
 * - func_1518F49C
 * - func_1518F51C
 * - func_1518F5D0
 * - func_1518F7C4
 * - func_1518F8E0
 * - func_1518FC04
 * - func_1518FC44
 * - func_1518FC84
 * - func_1518FDC4
 * - func_1519003C
 * - func_1519021C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;
extern f32 D_800A7B68;
extern f32 D_800A7B6C;
extern f32 D_800A7B70;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 CURRENT (2240) */
s32 func_1518F1A0(u8 *arg0) {
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    s32 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    *(s16 *)((u8 *)arg0 + 0x12E) = (s16) (*(s16 *)((u8 *)arg0 + 0x12E) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x12E) < 0) {
        temp_s0 = (void *)(arg0 + 0x110);
        *(s16 *)((u8 *)temp_s0 + 0x1E) = (s16) (func_150ADA20() % 6U);
        if (func_150ADA20() & 3) {
            temp_fv1 = *(f32 *)((u8 *)temp_s0 + 0x10);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0xC) - temp_fv1)) + temp_fv1);
        } else {
            temp_fv1_2 = *(f32 *)((u8 *)temp_s0 + 0xC);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x14) - temp_fv1_2)) + temp_fv1_2);
        }
    }
    temp_s0_2 = (void *)(arg0 + 0x110);
    {
        f32 temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x18) - temp_fv0) * D_800A7B68));
    *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x1C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x1C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (func_150ADA20() % 17U);
        temp_fv1_3 = *(f32 *)((u8 *)temp_s0_2 + 4);
        *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x110) - temp_fv1_3)) + temp_fv1_3);
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_s0_2 + 8) - temp_fv0_2) * D_800A7B6C));
    *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x2C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x2C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (func_150ADA20() % 15U);
        temp_fv1_4 = *(f32 *)((u8 *)temp_s0_2 + 0x24);
        *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0_2 + 0x20) - temp_fv1_4)) + temp_fv1_4);
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_v1 + (s32) ((*(f32 *)((u8 *)temp_s0_2 + 0x28) - (f32) temp_v1) * D_800A7B70));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F1A0.s")
extern f32 D_800A7B74;
extern f32 D_800A7B78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F384 CURRENT (719) */
s32 func_1518F384(u8 *arg0) {
    void *sp18;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_v1;
    u8 *temp_v1_2;

    if (*(s16 *)((u8 *)arg0 + 0x12C) == 0) {
        temp_fv0 = func_150ADA68();
        temp_v1 = (void *)(arg0 + 0x110);
        temp_fv1 = *(f32 *)((u8 *)temp_v1 + 4);
        *(s16 *)((u8 *)temp_v1 + 0x1C) = 1;
        *(f32 *)((u8 *)temp_v1 + 8) = (f32) ((temp_fv0 * (*(f32 *)((u8 *)arg0 + 0x110) - temp_fv1)) + temp_fv1);
    }
    temp_v1_2 = (void *)(arg0 + 0x110);
    if (*(s16 *)((u8 *)temp_v1_2 + 0x1E) == 0) {
        sp18 = temp_v1_2;
        temp_fv0_2 = func_150ADA68(arg0);
        temp_fv1_2 = *(f32 *)((u8 *)temp_v1_2 + 0x10);
        *(s16 *)((u8 *)temp_v1_2 + 0x1E) = 1;
        *(f32 *)((u8 *)temp_v1_2 + 0x18) = (f32) ((temp_fv0_2 * (*(f32 *)((u8 *)temp_v1_2 + 0xC) - temp_fv1_2)) + temp_fv1_2);
    }
    temp_fv0_3 = *(f32 *)((u8 *)arg0 + 0x30);
    {
        f32 temp_fv1_3 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0_3 + ((*(f32 *)((u8 *)temp_v1_2 + 0x18) - temp_fv0_3) * D_800A7B74));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv1_3 + ((*(f32 *)((u8 *)temp_v1_2 + 8) - temp_fv1_3) * D_800A7B78));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F384 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F384.s")
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A74D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F45C CURRENT (720) */
void func_1518F45C(s32 arg0, s32 arg1) {
    s32 sp1C = D_800A74D4;

    func_15169260(&sp1C, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F45C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F45C.s")
void func_15169850(s32, s32, s32, s32, s32);
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F49C CURRENT (1306) */
void func_1518F49C(s32 arg0, s32 arg1, u8 arg2) {
    u8 temp_a1;

    func_15169850(arg1, (s32)arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
    if ((arg2 == 0x49) &&
        ((*(s32 *)((u8 *)arg0 + 0x18) == *(s32 *)((u8 *)arg1 + 0)) ||
         ((temp_a1 = *(u8 *)((u8 *)arg1 + 4)),
          (temp_a1 == *(u8 *)((u8 *)arg0 + 0x1C))))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F49C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F49C.s")
extern s32 D_8008D630;
s32 func_1518FDC4(void *, s8 *, s32);
s32 func_1518F5D0(void *, s32, s16, s8, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F51C CURRENT (533) */
 s32 func_1518F51C(void *arg0, u8 arg1, s16 arg2, s8 arg3,
                  s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s8 index[5];

    if (arg0 == 0) {
        return 0;
    }
    if (func_1518FDC4(arg0, &index[0], arg1) == 0) {
        return 0;
    }
    return func_1518F5D0(
        arg0,
        *(s32 *)((u8 *)&D_8008D630 + ((u8)index[0] * 4)) + (arg1 * 0x50),
        arg2, arg3, (s32)arg4, (s32)arg5, (s32)arg6, arg7, (s32)arg8, arg9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F51C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F5D0.s")
extern s32 (*D_8008D67C[])(void *);
extern void func_1518F8E0(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F7C4 CURRENT (89) */
s32 func_1518F7C4(void *arg0) {
    void *sp1C;
    s8 temp_v1;
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x30;
    *(f32 *)temp_v0 = (f32)(*(f32 *)temp_v0 + ((*(f32 *)((u8 *)temp_v0 + 4) +
        (func_150ADA68() * *(f32 *)((u8 *)temp_v0 + 8))) * D_800BE9A4));
    sp1C = temp_v0;
    func_1518F8E0(arg0);
    temp_v1 = *(s8 *)((u8 *)sp1C + 0x58);
    if (temp_v1 != -1) {
        return D_8008D67C[temp_v1](arg0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F7C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F7C4.s")
extern void (*D_8008D680[])(void);

void func_1518F858(void *arg0) {
    volatile s8 *field;

    field = (volatile s8 *)((u8 *)arg0 + 0x89);
    if (*field != -1) {
        D_8008D680[*field]();
    }
}
void func_1518F89C(void *arg0) {
    f32 *temp_v0;

    temp_v0 = (f32 *)((u8 *)arg0 + 0x30);
    *temp_v0 = temp_v0[3] + (temp_v0[4] * func_150ADA68());
    func_1518F8E0(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F8E0.s")
extern void func_1514BE20(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518FC04 CURRENT (130) */
s32 func_1518FC04(void *arg0, void *arg1) {
    struct {
        u8 pad0[0x2C];
        s32 *field2C;
    } *temp_a2;
    void *temp_a0;

    temp_a2 = arg0;
    temp_a0 = temp_a2->field2C;
    *(s32 *)((u8 *)temp_a0 + 0x34) = *(s32 *)((u8 *)arg1 + 0);
    *(s32 *)((u8 *)temp_a0 + 0x38) = *(s32 *)((u8 *)arg1 + 4);
    *(s32 *)((u8 *)temp_a0 + 0x3C) = *(s32 *)((u8 *)arg1 + 8);
    func_1514BE20((s32) temp_a0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518FC04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC04.s")
extern void func_1514BF50(void *arg0, void *arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518FC44 CURRENT (130) */
s32 func_1518FC44(void *arg0, void *arg1) {
    struct {
        u8 pad0[0x2C];
        s32 *field2C;
    } *temp_a2;
    void *temp_a0;

    temp_a2 = arg0;
    temp_a0 = temp_a2->field2C;
    *(s32 *)((u8 *)temp_a0 + 0x34) = *(s32 *)((u8 *)arg1 + 0);
    *(s32 *)((u8 *)temp_a0 + 0x38) = *(s32 *)((u8 *)arg1 + 4);
    *(s32 *)((u8 *)temp_a0 + 0x3C) = *(s32 *)((u8 *)arg1 + 8);
    func_1514BF50(temp_a0, arg1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518FC44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC44.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518FC84 CURRENT (501) */
void func_1518FC84(u8 *arg0, void *arg1) {
    u8 *object;
    u8 *settings;
    u8 *fields;
    u8 *transform;
    s32 range;
    u32 random;
    f32 *position;

    position = arg1;
    settings = *(u8 **)(arg0 + 0x30);
    object = *(u8 **)(arg0 + 0x2C);
    if (settings == 0) {
        func_1516972C((s32)object);
        return;
    }
    *(f32 *)(object + 0x148) = *(f32 *)(settings + 0x60) *
                              (position[0] - *(f32 *)(arg0 + 0x34));
    *(f32 *)(object + 0x14C) = *(f32 *)(settings + 0x60) *
                              (position[1] - *(f32 *)(arg0 + 0x38));
    *(f32 *)(object + 0x150) = *(f32 *)(settings + 0x60) *
                              (position[2] - *(f32 *)(arg0 + 0x3C));
    transform = object + 0x110;
    fields = settings + 0x30;
    *(f32 *)(transform + 0x44) = func_150ADA68() * *(f32 *)(fields + 0x38) +
                                  *(f32 *)(fields + 0x34);
    *(f32 *)(transform + 0x48) = *(f32 *)(fields + 0x3C);
    *(s16 *)(object + 0x6C) = *(s16 *)(fields + 0x40);
    *(s16 *)(object + 0x6E) = *(s16 *)(fields + 0x42);
    random = func_150ADA20();
    range = *(s16 *)(fields + 0x46) + 1;
    *(s16 *)(object + 0x1C) = random % (u32)range +
                              *(s16 *)(fields + 0x44);
    if (fields[0x4C] & 1) {
        object[0x70] = 0x21;
    } else {
        object[0x70] = 0x20;
    }
    object[0x71] = 0x24;
    *(s32 *)(object + 0x58) |= 0x8000001;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518FC84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518FDC4 CURRENT (6025) */
s32 func_1518FDC4(void *arg0, s8 *arg1, s32 arg2) {
    s32 temp_t6;
    u8 temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    switch ((s32) temp_v0) {                        /* irregular */
    case 0x87:
    case 0xB0:
        *arg1 = 0xD;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0xB1:
        *arg1 = 0xE;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0xB4:
        *arg1 = 0xF;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x70:
    case 0xB2:
        *arg1 = 0x10;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x53:
        *arg1 = 0x11;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x96:
        *arg1 = 0x12;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        *arg1 = 0;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x49:
        *arg1 = 1;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x58:
        *arg1 = 2;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x50:
        *arg1 = 3;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        *arg1 = 4;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x80:
        *arg1 = 5;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        *arg1 = 6;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x16:
        *arg1 = 7;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x88:
    case 0x90:
        *arg1 = 8;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x9C:
        *arg1 = 9;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x9D:
        *arg1 = 0xA;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0x9F:
        *arg1 = 0xB;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    case 0xA0:
        *arg1 = 0xC;
        if (temp_t6 > 0) {
            return 0;
        }
        return 1;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518FDC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FDC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1519003C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1519021C.s")
