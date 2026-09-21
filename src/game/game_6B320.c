#include "types.h"

/*
 * Reviewed source unit: src/game/game_6B320.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503DE70
 * - func_1503DF0C
 * - func_1503DF48
 * - func_1503E260
 * - func_1503E3C4
 * - func_1503E5F8
 * - func_1503E82C
 * - func_1503EA54
 * - func_1503EB78
 * - func_1503ECA0
 * - func_1503EF4C
 * - func_1503EFC4
 * - func_1503F16C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game6B320MaskPair {
    u32 first;
    u32 second;
} Game6B320MaskPair;

extern u8 D_800CC2D0[];
extern Game6B320MaskPair *D_8008446C[];
void func_1503DF0C(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DE70 CURRENT (80) */
void func_1503DE70(s32 arg0, s32 arg1, s32 arg2) {
    Game6B320MaskPair *temp_v0;
    s32 temp_a0;

    temp_a0 = ((u8 *)arg0 - D_800CC2D0) / 812;
    if (arg2 != -1) {
        temp_v0 = &D_8008446C[arg1][arg2];
        func_1503DF0C(temp_a0, arg1, temp_v0->first, temp_v0->second);
        return;
    }
    func_1503DF0C(temp_a0, arg1, -1, -1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DE70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DE70.s")
typedef struct {
    u8 pad_0[0x1EC];
    f32 field_1EC;
} Game6B320Entity;

typedef struct {
    Game6B320Entity *entity;
    u8 pad_4[8];
    s16 field_C;
    u8 pad_E[2];
} Game6B320Slot;

extern Game6B320Slot D_800C6660[];
extern u8 D_80098914[];
extern s32 D_800BE9E4;
extern s8 *D_80084454[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DF0C CURRENT (380) */
void func_1503DF0C(s32 arg0, s8 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = (void *)((u8 *)&D_800C6660 + (arg0 * 0x10));
    *(s32 *)((u8 *)temp_v0 + 4) |= arg2;
    *(s32 *)((u8 *)temp_v0 + 8) |= arg3;
    *(s8 *)((u8 *)temp_v0 + 0xE) = arg1;
    *(s8 *)((u8 *)temp_v0 + 0xF) = 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DF0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DF0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503DF48.s")
typedef struct Game6B320MaskColumn {
    u32 bits;
    u8 pad4[0xC];
} Game6B320MaskColumn;

extern Game6B320MaskColumn D_800C6664[];
extern Game6B320MaskColumn D_800C6668[];

s32 func_1503E1F4(s32 arg0, s32 arg1) {
    if (arg0 < 0x20) {
        if (D_800C6664[arg1].bits & (1U << arg0)) {
            return 1;
        }
    } else {
        if (D_800C6668[arg1].bits & (1U << arg0)) {
            return 1;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E3C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E5F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E82C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EA54 CURRENT (3165) */
void func_1503EA54(s32 arg0) {
    Game6B320Entity *temp_a0;
    Game6B320Slot *temp_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    s32 temp_v0;

    temp_v1 = &D_800C6660[arg0];
    temp_v0 = D_80098914[temp_v1->pad_E[0]];
    var_a1 = 0;
    temp_fv0 = (f32) D_800BE9E4;
    if ((s32) temp_v0 > 0) {
        var_a2 = 0;
        do {
            temp_a0 = temp_v1->entity;
            temp_a3 = (u8 *) temp_a0 + var_a2;
            if (temp_a3[0x64] != 0) {
                if (D_80084454[temp_v1->pad_E[0]][var_a1] == -1) {
                    temp_fv1 = *(f32 *) (temp_a3 + 0x4C);
                    *(f32 *) (temp_a3 + 0x24) += *(f32 *) (temp_a3 + 0x48) * temp_fv0;
                    *(f32 *) (temp_a3 + 0x28) += temp_fv1 * temp_fv0;
                    *(f32 *) (temp_a3 + 0x2C) += *(f32 *) (temp_a3 + 0x50) * temp_fv0;
                    *(f32 *) (temp_a3 + 0x30) += *(f32 *) (temp_a3 + 0x54) * temp_fv0;
                    *(f32 *) (temp_a3 + 0x34) += *(f32 *) (temp_a3 + 0x58) * temp_fv0;
                    *(f32 *) (temp_a3 + 0x38) += *(f32 *) (temp_a3 + 0x5C) * temp_fv0;
                    *(f32 *) (temp_a3 + 0x4C) = temp_fv1 + *(f32 *) (temp_a3 + 0x60) * temp_fv0;
                }
            }
            var_a1++;
            var_a2 += 0x68;
        } while (var_a1 != temp_v0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503EA54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EA54.s")
extern f32 D_80098920;
extern f32 D_80098924;
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EB78 CURRENT (395) */
void func_1503EB78(void *arg0, f32 arg1, f32 arg2, s32 arg3) {
    f32 sp50[3];
    f32 *var_s1;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 temp_random;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *var_s0;
    u8 *var_s0_2;

    if (arg3 != 0) {
        var_s3 = 0x80;
        var_s4 = 0x7F;
    } else {
        var_s3 = 0xFF;
        var_s4 = 0;
    }
    temp_fv0 = arg1 * D_80098920;
    var_s0 = arg0;
    var_s1 = sp50;
    sp50[0] = temp_fv0;
    sp50[2] = temp_fv0;
    sp50[1] = arg2 * D_80098920;
    do {
        temp_random = func_150ADA20();
        temp_ft2 = *var_s1;
        temp_ft5 = *(f32 *)(var_s0 + 0x48);
        var_s1++;
        var_s0 += 4;
        *(f32 *)(var_s0 + 0x44) =
            temp_ft5 * (((f32)((temp_random & var_s3) + var_s4) *
                         temp_ft2) + 2.0f);
    } while ((u32)var_s1 < (u32)&sp50[3]);
    var_s2 = 0;
    var_s0_2 = arg0;
    do {
        temp_random = func_150ADA20();
        var_s2 += 1;
        var_s0_2 += 4;
        *(f32 *)(var_s0_2 + 0x50) =
            (f32)((temp_random & 0xFF) - 0x80) * 0.03125f;
    } while (var_s2 != 3);
    *(f32 *)((u8 *)arg0 + 0x60) = D_80098924;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503EB78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EB78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503ECA0.s")
void func_1503EEB8(void) {

}
void func_15060F28(u8 *, s32);
void func_1503ECA0(s32, s32);
extern s32 D_800BE9E4;
extern u8 D_800CC2D0[];

void func_1503EEC0(s32 arg0, s32 arg1) {
    Game6B320Slot *temp_v1;
    s32 temp_v0;

    func_1503ECA0(arg0, arg1);
    temp_v1 = &D_800C6660[arg0];
    temp_v0 = temp_v1->field_C;
    temp_v0 -= D_800BE9E4;
    temp_v1->field_C = temp_v0;
    if (temp_v0 <= 0) {
        func_15060F28(D_800CC2D0 + (arg0 * 0x32C), 1);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EF4C CURRENT (20) */
s32 func_1503EF4C(s32 arg0, s32 arg1, s32 arg2) {
    Game6B320MaskPair *base;
    Game6B320MaskPair *pair;
    u32 first;
    u32 second;

    base = D_8008446C[arg0];
    pair = (Game6B320MaskPair *)((u8 *)base + (arg1 * sizeof(*pair)));
    first = pair->first;
    if (((first == 0) ||
         (D_800C6664[arg2].bits & first)) &&
        ((second = pair->second, (second == 0)) ||
         (D_800C6668[arg2].bits & second))) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503EF4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EF4C.s")
extern u8 D_80098914[];
extern u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EFC4 CURRENT (1867) */
void func_1503EFC4(s32 arg0) {
    Game6B320Slot *temp_s2;
    s32 var_s0;
    s32 var_s1;
    u8 temp_s3;

    temp_s2 = &D_800C6660[arg0];
    temp_s2->field_C = 0x78;
    temp_s3 = D_80098914[temp_s2->pad_E[0]];
    var_s0 = 0;
    var_s1 = 0;
    if (temp_s3 > 0) {
        do {
            *(f32 *)((u8 *)temp_s2->entity + var_s1 + 0x4C) =
                (f32)((func_150ADA20() % 20U) - 5);
            var_s0 += 1;
            var_s1 += 0x68;
        } while (var_s0 != temp_s3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503EFC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EFC4.s")
/* Call context: func_1503EB78: unique active project prototype */
void func_1503EB78(void *, f32, f32, s32);

void func_1503F078(void *arg0, s32 arg1) {
    func_1503EB78(arg0, 2.0f, 2.0f, 0);
}
void func_1503EB78(void *arg0, f32 arg1, f32 arg2, s32 arg3);

void func_1503F0AC(void *arg0, u8 arg1) {
    func_1503EB78(arg0, 1.0f, 2.0f, 1);
}
/* Call context: func_1503EB78: unique active project prototype */

void func_1503F0D8(void *arg0, s32 arg1) {
    func_1503EB78(arg0, 2.06f, 3.0f, 1);
}
typedef struct {
    s32 field_0;
    u8 pad_4[0x328];
} Game6B320EntityRecordField94;

extern Game6B320EntityRecordField94 D_800CC364[];

void func_1503F108(s32 arg0) {
    D_800C6660[arg0].field_C = 0x8C;
    D_800CC364[arg0].field_0 = 6;
    D_800C6660[arg0].entity->field_1EC = 10.0f;
}
s32 func_1503EF4C(s32, s32, s32);
extern s16 D_800C666C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503F16C CURRENT (310) */
void func_1503F16C(s32 arg0) {
    u8 *entity;
    s32 first_flags;
    s32 second_flags;

    *(s16 *)((u8 *)&D_800C666C + arg0 * 0x10) = 0x12C;
    if (func_1503EF4C(2, 0, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        first_flags = *(s32 *)(entity + 0x94) | 0x40;
        *(volatile s32 *)(entity + 0x94) = first_flags;
        *(s32 *)(entity + 0x94) = first_flags & ~0x200;
    }
    if (func_1503EF4C(2, 1, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        second_flags = *(s32 *)(entity + 0x94) | 0x80;
        *(volatile s32 *)(entity + 0x94) = second_flags;
        *(s32 *)(entity + 0x94) = second_flags & ~0x100;
    }
    if (func_1503EF4C(2, 2, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) &= ~0x400;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503F16C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503F16C.s")
void func_1503E260(s32);

void func_1503F2B0(s32 arg0, s32 arg1) {
    Game6B320Slot *slot;
    u8 *entity;

    func_1503ECA0(arg0, arg1);
    slot = &D_800C6660[arg0];
    slot->field_C -= D_800BE9E4;
    if (slot->field_C > 0) {
        return;
    }
    func_1503E260(arg0);
    if (func_1503EF4C(2, 0, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) |= 8;
    }
    if (func_1503EF4C(2, 1, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) |= 4;
    }
    if (func_1503EF4C(2, 2, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) |= 2;
    }
}
void *func_10022EC0(void *, const void *, u32);
void func_151EFEB8(void *, s32);
s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C3E90;

void func_1503F404(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    u8 sp30[0x40];

    if (D_800C3E90 != 0) {
        func_151EFEB8(sp30, arg0);
    } else {
        func_10022EC0(sp30, (void *)arg0, 0x40U);
    }
    func_1503E5F8(sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
