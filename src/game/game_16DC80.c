#include "types.h"

/*
 * Reviewed source unit: src/game/game_16DC80.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151408A4
 * - func_151412BC
 * - func_1514143C
 * - func_15141478
 * - func_151415D4
 * - func_151416E8
 * - func_151417C4
 * - func_1514182C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game16DC80Descriptor {
    u8 field0;
    u8 field1;
    u8 pad2[0x3E];
    u32 flags40;
} Game16DC80Descriptor;

typedef struct Game16DC80Inner {
    u8 pad0[0x44];
    void *field_44;
    u8 pad48[0x11];
    s8 field59;
} Game16DC80Inner;

typedef struct Game16DC80Object {
    u8 pad0[0x110];
    Game16DC80Inner inner;
} Game16DC80Object;

void *func_10022EC0(void *, const void *, u32);
s32 func_1513D524(Game16DC80Descriptor *, u8, u8, u8, s32, s32, u32, s32, s32);
extern s32 D_800DC9F0;

s32 func_151407D0(void *arg0, u32 arg1, Game16DC80Descriptor *arg2,
    u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9) {
    s32 result;
    s32 unused;
    Game16DC80Inner *inner;

    arg2->field1 = 3;
    arg2->flags40 |= 0x40400000;
    result = func_1513D524(arg2, arg3, arg4, arg5, 1, arg6, arg1, arg8, arg9);
    inner = (Game16DC80Inner *)(result + 0x110);
    if (result != 0) {
        func_10022EC0(inner, arg0, arg1);
        inner->field59 = arg7;
        inner->field_44 = 0;
copy_done:
        ;
    } else {
        return 0;
    }
    if (result) {
        D_800DC9F0 = D_800DC9F0 + 1;
    }
    return result;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151408A4.s")
void func_151411A4(void) {
    func_1513CA6C();
}
void func_151411C4(void) {
    func_1513CAA0();
}
typedef struct Game1411E4State {
    u8 pad_0[0x154];
    void *volatile field_154;
    u8 pad_158[0x10];
    u8 field_168;
} Game1411E4State;

void func_1517E134(void *);
extern u8 D_80089F9C[];
extern s32 D_800DC9F0;

void func_151411E4(Game1411E4State *arg0) {
    if (arg0->field_154 != 0) {
        func_1517E134(arg0->field_154);
    }
    D_800DC9F0 -= 1;
    (*(void (**)(Game1411E4State *))(D_80089F9C + (arg0->field_168 * 4)))(arg0);
}
extern u8 D_80089FE4[];

void func_15141250(Game1411E4State *arg0) {
    if (arg0->field_154 != 0) {
        func_1517E134(arg0->field_154);
    }
    D_800DC9F0 -= 1;
    (*(void (**)(Game1411E4State *))(D_80089FE4 + (arg0->field_168 * 4)))(arg0);
}
extern s32 D_80082FA0;
extern s32 D_800A5168[];
extern s32 D_800BE620;
extern s32 D_800BE624;
extern u16 *D_800BE9C4;
extern u8 D_800DCE50[];
extern u8 D_800DD190[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151412BC CURRENT (1460) */
void func_151412BC(void) {
    u8 *table = D_800DCE50;
    s32 object_index;

    do {
        object_index = 0;
        do {
            u8 *object = *(u8 **)(table + D_800A5168[object_index] * 4);
            object_index++;
            while (object != 0) {
                s32 flags = *(s32 *)(object + 0x58);
                if (flags & 0x2000) {
                    *(s16 *)(object + 0x162) = 0;
                    *(s16 *)(object + 0x160) = 0;
                    *(s16 *)(object + 0x15E) = 0;
                    *(s16 *)(object + 0x15C) = 0;
                    if (flags & 0x10) {
                        s32 index = 0;
                        u8 *data = object + 0x110;
                        if (D_80082FA0 >= 0) {
                            do {
                                s32 x = *(s32 *)(data + 0x24 + index * 4);
                                s32 y;
                                if (x >= 0 && x < D_800BE620 &&
                                    (y = *(s32 *)(data + 0x34 + index * 4), y >= 0) &&
                                    y < D_800BE624) {
                                    *(u16 *)(data + 0x4C + index * 2) = D_800BE9C4[y * D_800BE620 + x];
                                } else {
                                    *(s16 *)(data + 0x4C + index * 2) = 0x7FFF;
                                }
                                index = (index + 1) & 0xFF;
                            } while (index <= D_80082FA0);
                        }
                    }
                }
                object = *(u8 **)(object + 8);
            }
            object_index &= 0xFF;
        } while (object_index < 4);
        table += 0x1A0;
    } while (table != D_800DD190);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151412BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514143C CURRENT (260) */
void func_1514143C(Game16DC80Object *arg0) {
    Game16DC80Inner *temp_v0;
    void *temp_v1;

    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        temp_v0 = &arg0->inner;
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 0) = *(f32 *)((u8 *)arg0 + 0x34);
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 4) = *(f32 *)((u8 *)arg0 + 0x38);
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 8) = *(f32 *)((u8 *)arg0 + 0x3C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514143C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514143C.s")
s32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141478 CURRENT (2297) */
s32 func_15141478(u8 *arg0) {
    void *sp24;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    *(f32 *)((u8 *)arg0 + 0x180) = (f32) (*(f32 *)((u8 *)arg0 + 0x180) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x180) < 0.0f) {
        temp_v1 = (void *)(arg0 + 0x170);
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) (func_150ADA68() * *(f32 *)((u8 *)temp_v1 + 0x14));
        sp24 = temp_v1;
        if (func_150ADA20() & 3) {
            sp24 = temp_v1;
            temp_fv1 = *(f32 *)((u8 *)temp_v1 + 4);
            *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x170) - temp_fv1)) + temp_fv1);
        } else {
            sp24 = temp_v1;
            temp_fv1_2 = *(f32 *)((u8 *)arg0 + 0x170);
            *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_v1 + 8) - temp_fv1_2)) + temp_fv1_2);
        }
    }
    temp_a0 = (void *)(arg0 + 0x110);
    temp_v1_2 = (void *)(arg0 + 0x170);
    temp_fv0 = *(f32 *)((u8 *)temp_a0 + 0x48);
    *(f32 *)((u8 *)temp_a0 + 0x48) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_v1_2 + 0xC) - temp_fv0) * *(f32 *)((u8 *)temp_v1_2 + 0x18)));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141478 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141478.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

s32 func_15141564(u8 *arg0) {
    typedef struct {
        f32 base;
        f32 scale;
        f32 value;
        f32 velocity;
    } Motion;
    void *sp18;
    Motion *temp_v1;
    f32 factor;

    temp_v1 = (Motion *)(arg0 + 0x170);
    factor = func_15047D60(temp_v1->value);
    *(f32 *)((u8 *)arg0 + 0x158) =
        temp_v1->base + temp_v1->scale * factor;
    temp_v1->value = temp_v1->value + temp_v1->velocity * D_800BE9A4;
    sp18 = temp_v1;
    temp_v1->value = func_15144B68(temp_v1->value);
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151415D4 CURRENT (685) */
s32 func_151415D4(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_ft2;
    u8 *var_v0;

    var_v0 = (void *)(arg0 + 0x170);
    if (*(f32 *)((u8 *)arg0 + 0x17C) < *(f32 *)((u8 *)arg0 + 0x180)) {
        var_v0 = (void *)(arg0 + 0x170);
        var_ft2 = *(f32 *)((u8 *)var_v0 + 4);
        goto block_7;
    }
    temp_fv1 = *(f32 *)((u8 *)var_v0 + 0xC);
    if (temp_fv1 < *(f32 *)((u8 *)var_v0 + 0x14)) {
        *(f32 *)((u8 *)arg0 + 0x158) = (f32) (*(f32 *)((u8 *)var_v0 + 4) + (*(f32 *)((u8 *)var_v0 + 8) * ((temp_fv1 - *(f32 *)((u8 *)var_v0 + 0x10)) * *(f32 *)((u8 *)var_v0 + 0x20))));
    } else {
        temp_fa0 = *(f32 *)((u8 *)var_v0 + 0x18);
        if (temp_fv1 < temp_fa0) {
            *(f32 *)((u8 *)arg0 + 0x158) = (f32) *(f32 *)((u8 *)arg0 + 0x170);
        } else {
            var_ft2 = *(f32 *)((u8 *)var_v0 + 4) + (*(f32 *)((u8 *)var_v0 + 8) * (1.0f - ((temp_fv1 - temp_fa0) * *(f32 *)((u8 *)var_v0 + 0x20))));
block_7:
            *(f32 *)((u8 *)arg0 + 0x158) = var_ft2;
        }
    }
    temp_fv0 = *(f32 *)((u8 *)var_v0 + 0x1C);
    *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) + D_800BE9A4);
    if (temp_fv0 < *(f32 *)((u8 *)var_v0 + 0xC)) {
        do {
            *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) - temp_fv0);
        } while (temp_fv0 < *(f32 *)((u8 *)var_v0 + 0xC));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151415D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151415D4.s")
typedef void (*Game16DC80Callback)(u8 *, u8 *, u8);
extern Game16DC80Callback D_8008A02C;
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151416E8 CURRENT (1995) */
void func_151416E8(u8 *arg0, u8 *arg1, u8 arg2) {
    if (*(&D_8008A02C + arg0[0x168]) != 0) {
        (*(&D_8008A02C + arg0[0x168]))(arg0, arg1, arg2);
    }
    if ((arg2 == 0x22) || (arg2 == 0x24) || (arg2 == 0x25)) {
        s8 *state;

        state = (s8 *)arg0 + 0x110;
        if (*arg1 == (u8)state[0x58]) {
            switch (arg2) {
                case 0x22:
                    func_1516972C(arg0);
                    return;
                case 0x24:
                    state[0x59] = -1;
                    return;
                case 0x25:
                    state[0x59] = 2;
                    break;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151416E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151416E8.s")
typedef struct {
    s32 field_0;
    s32 field_4;
} Game16DC80Pair;

void func_15169260(Game16DC80Pair *, s32, u8 *, s32);
extern Game16DC80Pair D_8008A074;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151417C4 CURRENT (209) */
void func_151417C4(u8 arg0, u8 arg1) {
    s32 sp24;
    Game16DC80Pair sp1C;

    sp1C = D_8008A074;
    *(u8 *)&sp24 = arg0;
    func_15169260(&sp1C, 2, (u8 *)&sp24, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151417C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151417C4.s")
s32 func_15141818(s32 arg0, s32 arg1) {
    return 0;
}
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514182C CURRENT (596) */
void func_1514182C(void *arg0, void *arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5) {
    struct {
        f32 matrix[16];
        f32 tail[3];
    } transform;
    f32 scaled_x;
    f32 scaled_y;
    f32 scaled_z;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    func_150A8050(transform.matrix, arg4, 0, arg5);
    transform.matrix[12] = *(f32 *)arg1;
    transform.matrix[13] = *(f32 *)((u8 *)arg1 + 4);
    transform.matrix[14] = *(f32 *)((u8 *)arg1 + 8);
    func_150A7960(transform.matrix, 0.0f, *(f32 *)&arg2, 0.0f,
                  (f32 *)((u8 *)arg0 + 0x34),
                  (f32 *)((u8 *)arg0 + 0x38),
                  (f32 *)((u8 *)arg0 + 0x3C));
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x34);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x38);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x3C);
    scaled_x = (temp_fv0 - *(f32 *)arg1) * *(f32 *)&arg3;
    scaled_y = (temp_fv1 - *(f32 *)((u8 *)arg1 + 4)) * *(f32 *)&arg3;
    scaled_z = (temp_fa0 - *(f32 *)((u8 *)arg1 + 8)) * *(f32 *)&arg3;
    *(f32 *)((u8 *)arg0 + 0x40) = temp_fv0 + (scaled_x * 500.0f);
    *(f32 *)((u8 *)arg0 + 0x44) = temp_fv1 + (scaled_y * 500.0f);
    *(f32 *)((u8 *)arg0 + 0x48) = temp_fa0 + (scaled_z * 500.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514182C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514182C.s")
void func_1514182C(void *, void *, s32, s32, f32, f32);

s32 func_15141928(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x178);
    func_1514182C(arg0,
                  (u8 *)arg0 + 0x17C,
                  *(s32 *)((u8 *)arg0 + 0x170),
                  *(s32 *)((u8 *)arg0 + 0x174),
                  *(f32 *)((u8 *)temp_v0 + 0),
                  *(f32 *)((u8 *)temp_v0 + 8));
    return 1;
}
