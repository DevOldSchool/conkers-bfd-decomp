#include "types.h"

/*
 * Reviewed source unit: src/game/game_15D730.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15130280
 * - func_15130374
 * - func_151303BC
 * - func_151303EC
 * - func_15130A9C
 * - func_1513137C
 * - func_15131514
 * - func_15131828
 * - func_151319C4
 * - func_15131B7C
 * - func_15131C2C
 * - func_15131C84
 * - func_15131D4C
 * - func_15131EE4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game15D730ColorState {
    u8 pad0[0x24];
    u8 field24;
    u8 field25;
    u8 field26;
    u8 field27;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    u8 field2C;
    u8 pad2D[0x43];
    u8 mode70;
    u8 mode71;
} Game15D730ColorState;

void func_1513137C(s16 *, s16 *, s16 *, s16 *, Game15D730ColorState *);
void func_15131514(s16 *, s16 *, s16 *, s16 *, Game15D730ColorState *);

typedef struct Game15D730CopyBlock {
    s32 words[9];
} Game15D730CopyBlock;

void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15130280 CURRENT (1455) */
void func_15130280(void *arg0, u8 arg1, Game15D730CopyBlock *arg2,
                   s32 arg3, u8 arg4, s32 arg5) {
    void *sp24;
    s32 var_a0;

    if (arg1 != 0) {
        if (arg1 != 1) {
            var_a0 = 0x47;
            if (arg1 != 2) {
                var_a0 = 0x2B;
            }
        } else {
            var_a0 = 0x52;
        }
    } else {
        var_a0 = 0x2B;
    }
    sp24 = func_15167A68(var_a0, arg5, arg3 + 0xA8, 1, arg4, 1);
    if (sp24 == 0) {
        return;
    }
    func_10022EC0((u8 *)sp24 + 0x10, arg0, 0x70);
    if (arg2 != 0) {
        *(Game15D730CopyBlock *)((u8 *)sp24 + 0x80) = *arg2;
        return;
    }
    *(s8 *)((u8 *)sp24 + 0x9C) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15130280 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130280.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15130374 CURRENT (832) */
void func_15130374(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15130280(arg1 & 0xFF, 0, arg2, arg3, arg3 & 0xFF, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15130374 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130374.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151303BC CURRENT (510) */
void func_151303BC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;

    temp_a1 = arg1;
    func_15130374(arg0, temp_a1 & 0xFF, arg2, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151303BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151303BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151303EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130A9C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513137C CURRENT (1330) */
void func_1513137C(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, Game15D730ColorState *arg4) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    u8 temp_t6;

    temp_t6 = arg4->mode70;
    switch (temp_t6) {
    case 1:
        *arg2 = 0;
        temp_v0 = *arg2;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 2:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 3:
        *arg0 = (s16) arg4->field28;
        *arg1 = (s16) arg4->field29;
        *arg2 = (s16) arg4->field2A;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 4:
    case 6:
        *arg3 = 0;
        temp_v0_2 = *arg3;
        *arg2 = temp_v0_2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        return;
    case 5:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg4->field2B;
        return;
    case 7:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) arg4->field2B;
        return;
    case 8:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
block_10:
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4->field24 * arg4->field2C) >> 8);
        *arg1 = (s16) ((s32) (arg4->field25 * arg4->field2C) >> 8);
        *arg2 = (s16) ((s32) (arg4->field26 * arg4->field2C) >> 8);
        goto block_10;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513137C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_1513137C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131514 CURRENT (915) */
void func_15131514(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, Game15D730ColorState *arg4) {
    s16 temp_v0;
    s16 temp_v0_3;
    u8 temp_t6;
    u8 temp_v0_2;
    u8 temp_v0_4;
    u8 temp_v0_5;

    temp_t6 = arg4->mode71;
    switch (temp_t6) {
    case 1:
    case 5:
        *arg2 = 0;
        temp_v0 = *arg2;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        *arg3 = 0;
        return;
    case 2:
        temp_v0_2 = arg4->field2C;
        *arg2 = (s16) temp_v0_2;
        *arg1 = (s16) temp_v0_2;
        *arg0 = (s16) temp_v0_2;
        *arg3 = 0;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg4->field2B;
        return;
    case 3:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = 0;
        return;
    case 4:
    case 6:
        *arg0 = (s16) arg4->field28;
        *arg1 = (s16) arg4->field29;
        *arg2 = (s16) arg4->field2A;
        *arg3 = (s16) arg4->field2B;
        return;
    case 7:
        temp_v0_4 = arg4->field2C;
        *arg2 = (s16) temp_v0_4;
        *arg1 = (s16) temp_v0_4;
        *arg0 = (s16) temp_v0_4;
        *arg3 = (s16) arg4->field2B;
        return;
    case 9:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) arg4->field2B;
        return;
    default:
        temp_v0_5 = arg4->field2C;
        *arg2 = (s16) temp_v0_5;
        *arg1 = (s16) temp_v0_5;
        *arg0 = (s16) temp_v0_5;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131514 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131514.s")
void func_1513164C(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3,
                   s16 *arg4, s16 *arg5, s16 *arg6, s16 *arg7,
                   Game15D730ColorState *arg8) {
    func_15131514(arg4, arg5, arg6, arg7, arg8);
    func_1513137C(arg0, arg1, arg2, arg3, arg8);
}
void func_151318E8(void *, f32);

s32 func_151316AC(u8 *arg0, s32 arg1) {
    func_151318E8(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131918(void *, f32);

s32 func_151316DC(u8 *arg0, s32 arg1) {
    func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131958(void *, f32);

s32 func_1513170C(u8 *arg0, s32 arg1) {
    func_15131958(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_1513173C(void) {
    func_15169804();
}
void func_1513175C(void) {
    func_15169824();
}
extern void (*D_80089814[])(void);

void func_1513177C(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x75);
    } else {
        var_v0 = 0;
    }
    D_80089814[var_v0]();
}
extern void (*D_80089844[])(void);

void func_151317C8(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x75);
    } else {
        var_v0 = 0;
    }
    D_80089844[var_v0]();
}
s32 func_15131814(s32 arg0, s32 arg1) {
    return 0;
}
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131828 CURRENT (770) */
void func_15131828(void *arg0, void *arg1, void *arg2, void *arg3) {
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (func_151423D8((*(u8 *)((u8 *)arg2 + 0) - 0x40) & 0xFF) * *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (func_151423D8((*(u8 *)((u8 *)arg2 + 1) - 0x40) & 0xFF) * *(f32 *)((u8 *)arg1 + 4));
    *(u8 *)((u8 *)arg2 + 0) = (u8) (*(u8 *)((u8 *)arg2 + 0) + (*(u8 *)((u8 *)arg3 + 0) * D_800BE9E4));
    *(u8 *)((u8 *)arg2 + 1) = (u8) (*(u8 *)((u8 *)arg2 + 1) + (*(u8 *)((u8 *)arg3 + 1) * D_800BE9E4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131828.s")
extern s32 D_800BE9E4;

void func_151318E8(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131918(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131958(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
void func_151319C4(void *arg0, s32 arg1, void *arg2);

void func_151319A4(void *arg0, s32 arg1) {
    func_151319C4(arg0, arg1, (u8 *)arg0 + 0xA8);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_151319C4.s")
/* Call context: func_15131958: unique active project prototype */
/* Call context: func_151319C4: unique active project prototype */

void func_15131AFC(u8 *arg0, s32 arg1) {
    func_15131958(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    func_151319C4(arg0, arg1, arg0 + 0xB0);
}
/* Call context: func_15131918: unique active project prototype */
/* Call context: func_151319C4: unique active project prototype */

void func_15131B3C(u8 *arg0, s32 arg1) {
    func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    func_151319C4(arg0, arg1, arg0 + 0xB0);
}
extern f32 D_800A3848;
extern f32 D_800A384C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131B7C CURRENT (2126) */
s32 func_15131B7C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg2 + 4) + (*(f32 *)((u8 *)arg0 + 0x3C) * D_800A3848));
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg3 + 4));
    *(f32 *)((u8 *)arg0 + 0x5C) = (f32) (*(f32 *)((u8 *)arg0 + 0x5C) * -*(f32 *)((u8 *)arg3 + 4));
    temp_fv0 = fabsf(*(f32 *)((u8 *)arg0 + 0x5C));
    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg3 + 4));
    if (temp_fv0 < D_800A384C) {
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x60) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
        *(u8 *)((u8 *)arg3 + 0) = (u8) (*(u8 *)((u8 *)arg3 + 0) & 0xFFFE);
        *(s32 *)((u8 *)arg0 + 0x68) = (s32) (*(s32 *)((u8 *)arg0 + 0x68) & ~6);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131B7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131B7C.s")
typedef void (*Game15D730Callback)(void *, s32, s32);

extern Game15D730Callback D_80089878[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131C2C CURRENT (467) */
void func_15131C2C(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    Game15D730Callback temp_v0;

    temp_a2 = arg2 & 0xFF;
    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        temp_v0 = D_80089878[*(u8 *)((u8 *)arg0 + 0x75)];
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1, temp_a2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131C2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131C2C.s")
/* Call context: func_151423D8: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131C84 CURRENT (530) */
void func_15131C84(void *arg0, void *arg1, f32 arg2, void *arg3, f32 *arg4, f32 *arg5) {
    u8 temp_a0;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0) + (*(s8 *)((u8 *)arg1 + 0) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0) = temp_a0;
    *(u8 *)((u8 *)arg0 + 1) = (u8) (*(u8 *)((u8 *)arg0 + 1) + (*(s8 *)((u8 *)arg1 + 1) * D_800BE9E4));
    *arg4 = (func_151423D8((temp_a0 - 0x40) & 0xFF) * *(f32 *)((u8 *)arg3 + 0)) + arg2;
    *arg5 = (func_151423D8((*(u8 *)((u8 *)arg0 + 1) - 0x40) & 0xFF) * *(f32 *)((u8 *)arg3 + 4)) + arg2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131C84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131C84.s")
typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
} Game15D730Args;

extern Game15D730Args D_800A37F0;
void func_15169260(Game15D730Args *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15131D4C CURRENT (260) */
void func_15131D4C(s32 arg0, s32 arg1) {
    Game15D730Args sp1C;
    u8 temp_a3;

    temp_a3 = arg1;
    sp1C = D_800A37F0;
    func_15169260(&sp1C, 3, arg0, temp_a3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15131D4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131D4C.s")
typedef struct {
    u8 pad_0[0x38];
    s32 field_38;
    s32 field_3C;
    u8 pad_40[0x68];
    s16 field_A8;
    s16 field_AA;
    s32 field_AC;
    s32 field_B0;
} Game15D730State;

void func_15131C84(s16 *, s16 *, s32, s32 *, s32 *, s32 *);

s32 func_15131D9C(Game15D730State *arg0, s32 arg1) {
    func_15131C84(&arg0->field_A8, &arg0->field_AA, arg0->field_AC, &arg0->field_B0,
                  &arg0->field_38, &arg0->field_3C);
    return 1;
}
extern f32 D_800BE9A4;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
s32 func_15131DEC(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0xA8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0xB0) * sqrtf(temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x3C) = temp_fa0;
    *(f32 *)((u8 *)arg0 + 0x38) = temp_fa0;
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (*(f32 *)((u8 *)arg0 + 0xB4) - (*(f32 *)((u8 *)arg0 + 0xB8) * temp_fv1 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) (temp_fv1 + D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0xAC) < *(f32 *)((u8 *)arg0 + 0xA8)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15131EE4.s")
