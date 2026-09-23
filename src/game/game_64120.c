#include "types.h"

/*
 * Reviewed source unit: src/game/game_64120.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15036CE8
 * - func_15036F34
 * - func_15037698
 * - func_150379DC
 * - func_150380C0
 * - func_15038468
 * - func_15038620
 * - func_15039A78
 * - func_15039CC8
 * - func_15039ED0
 * - func_1503A08C
 * - func_1503A678
 * - func_1503A830
 * - func_1503B708
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game64120InitBlock {
    f32 first[3];
    f32 second[3];
    u8 pad18[0x30];
} Game64120InitBlock;

typedef struct Game64120InitState {
    u8 pad0[0x324];
    Game64120InitBlock *volatile block;
} Game64120InitState;

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
extern f32 D_80098250;

typedef struct Game64120OutputBlock {
    u8 pad0[0x30];
    f32 x;
    f32 y;
    f32 z;
} Game64120OutputBlock;

typedef struct Game64120Output {
    u8 pad0[0x40];
    Game64120OutputBlock block;
} Game64120Output;

typedef struct Game64120Record {
    u8 pad0[0x18];
    f32 y;
    u8 pad1C[0x158];
    f32 x;
    f32 z;
    u8 pad17C[0x58];
    Game64120Output *output;
    u8 pad1D8[0x154];
} Game64120Record;

extern Game64120Record D_800CC2D0[];

void func_15036C70(Game64120InitState *arg0) {
    f32 value;
    s32 offset;
    Game64120InitBlock *block;

    block = func_10003C40(sizeof(*block), 1, 0, 0);
    arg0->block = block;
    func_100226F0(block, sizeof(*block));
    value = D_80098250;
    offset = 0;
    do {
        *(f32 *)((u8 *)arg0->block + offset) = value;
        *(f32 *)((u8 *)arg0->block + offset + 0xC) = value;
        offset += 4;
    } while (offset != 0xC);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036CE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15036F34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15037698.s")
extern f32 D_8009862C;
extern s16 D_800C3FF4[];
extern void *D_800DBFF0;

s32 func_15037880(s32 arg0, f32 *arg1) {
    Game64120Record *temp_v0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t8;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = (*(u16 *)((u8 *)temp_v0 + 0x2F8)) & 7;
    if (temp_t8 == 1) {
        arg1[0] = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
        arg1[1] = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
        arg1[2] = *(f32 *)((u8 *)D_800DBFF0 + 0x300);
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->pad0[5] == 4) {
            temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0x14) - (f32)D_800C3FF4[0];
            temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x1C) - (f32)D_800C3FF4[2];
            if (D_8009862C < ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1))) {
                return 1;
            }
        }
        arg1[0] = (f32)D_800C3FF4[0];
        arg1[1] = (f32)D_800C3FF4[1];
        arg1[2] = (f32)D_800C3FF4[2];
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150379DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_150380C0.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_80098648;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15038468 CURRENT (3799) */
void func_15038468(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv0;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = func_150484A0(arg2, arg4);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
block_9:
        *arg1 = var_fv0;
        break;
    case 1:
        *arg0 = func_150484A0(-arg4, arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 2:
        *arg0 = func_150484A0(arg4, -arg2);
        var_fv0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 3:
        *arg0 = func_150484A0(arg4, -arg3);
        var_fv0 = func_150484A0(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        goto block_9;
    }
    *arg0 *= D_80098648;
    *arg1 *= D_80098648;
    temp_fv0 = *arg0;
    if (temp_fv0 > 180.0f) {
        *arg0 = temp_fv0 - 360.0f;
    }
    temp_fv0_2 = *arg1;
    if (temp_fv0_2 > 180.0f) {
        *arg1 = temp_fv0_2 - 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15038468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15038620.s")
typedef struct Game64120Entry {
    u8 data[0x18];
} Game64120Entry;

extern Game64120Entry D_80098068[];

Game64120Entry *func_15039A54(s32 arg0, s32 arg1) {
    return &D_80098068[arg1];
}
extern void * D_800CC5E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15039A78 CURRENT (1032) */
void func_15039A78(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, s32 arg6) {
    void *sp18;
    Game64120Entry *temp_v0;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    void *temp_v1;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa0_3;

    temp_v1 = *(&D_800CC5E8 + (arg6 * 0x32C));
    sp18 = temp_v1;
    temp_v0 = func_15039A54(arg6, 0);
    if ((temp_v1 != 0) && (*(s32 *)((u8 *)temp_v1 + 0x2C) != 0x100)) {
        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x10);
        temp_fv0 = *arg0;
        if (((*(f32 *)((u8 *)temp_v0 + 0) + temp_fa0) < temp_fv0) || (temp_fv0 < (*(f32 *)((u8 *)temp_v0 + 4) - temp_fa0))) {
            *arg0 = arg4;
            *arg1 = arg5;
            if (arg2 != 0) {
                *arg2 = *arg0;
                *arg3 = *arg1;
            }
        } else {
            if (arg2 != 0) {
                *arg2 = temp_fv0;
                *arg3 = *arg1;
            }
            if (*arg0 < *(f32 *)((u8 *)temp_v0 + 4)) {
                *arg0 = *(f32 *)((u8 *)temp_v0 + 4);
            } else {
                temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0);
                if (temp_fv1 < *arg0) {
                    var_fa0 = temp_fv1;
                } else {
                    var_fa0 = *arg0;
                }
                *arg0 = var_fa0;
            }
            temp_fa1 = *(f32 *)((u8 *)temp_v0 + 8);
            temp_fa0_2 = *(f32 *)((u8 *)temp_v0 + 0x14);
            temp_fv1_2 = *arg1;
            if (((temp_fa1 + temp_fa0_2) < temp_fv1_2) || (temp_fv0_2 = *(f32 *)((u8 *)temp_v0 + 0xC), (temp_fv1_2 < (temp_fv0_2 - temp_fa0_2)))) {
                *arg1 = arg5;
                return;
            }
            if (temp_fv1_2 < temp_fv0_2) {
                *arg1 = temp_fv0_2;
                return;
            }
            if (temp_fa1 < temp_fv1_2) {
                var_fa0_2 = temp_fa1;
            } else {
                var_fa0_2 = temp_fv1_2;
            }
            goto block_34;
        }
    } else {
        temp_fv0_3 = *arg0;
        temp_fv1_3 = *(f32 *)((u8 *)temp_v0 + 4);
        if (temp_fv0_3 < temp_fv1_3) {
            *arg0 = temp_fv1_3;
        } else {
            temp_fv1_4 = *(f32 *)((u8 *)temp_v0 + 0);
            if (temp_fv1_4 < temp_fv0_3) {
                var_fa0_3 = temp_fv1_4;
            } else {
                var_fa0_3 = temp_fv0_3;
            }
            *arg0 = var_fa0_3;
        }
        temp_fv1_5 = *arg1;
        temp_fv0_4 = *(f32 *)((u8 *)temp_v0 + 0xC);
        if (temp_fv1_5 < temp_fv0_4) {
            *arg1 = temp_fv0_4;
            return;
        }
        temp_fa1_2 = *(f32 *)((u8 *)temp_v0 + 8);
        if (temp_fa1_2 < temp_fv1_5) {
            var_fa0_2 = temp_fa1_2;
        } else {
            var_fa0_2 = temp_fv1_5;
        }
block_34:
        *arg1 = var_fa0_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15039A78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039A78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039CC8.s")
void func_15039A78(f32 *, f32 *, f32 *, f32 *, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15039ED0 CURRENT (1758) */
void func_15039ED0(s32 arg0, f32 *arg1, register f32 *arg2, f32 *arg3,
                   f32 *arg4, f32 arg5, f32 arg6, s32 arg7) {
    Game64120Entry *entry;
    f32 marginX;
    f32 marginY;
    f32 valueX;
    f32 valueY;
    f32 bound;

    if (arg0 == 0) {
        func_15039A78(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return;
    }
    entry = func_15039A54(arg7, arg0);
    marginX = *(f32 *)(entry->data + 0x10);
    valueX = *arg1;
    if ((*(f32 *)(entry->data + 0) + marginX < valueX) ||
        (valueX < *(f32 *)(entry->data + 4) - marginX)) {
        *arg1 = arg5;
        *arg2 = arg6;
        if (arg3 != 0) {
            *arg3 = *arg1;
            *arg4 = *arg2;
        }
    } else {
        if (arg3 != 0) {
            *arg3 = valueX;
            *arg4 = *arg2;
        }
        if (*arg1 < *(f32 *)(entry->data + 4)) {
            bound = *(f32 *)(entry->data + 4);
        } else if (*(f32 *)(entry->data + 0) < *arg1) {
            bound = *(f32 *)(entry->data + 0);
        } else {
            bound = *arg1;
        }
        *arg1 = bound;
        marginY = *(f32 *)(entry->data + 0x14);
        valueY = *arg2;
        if ((*(f32 *)(entry->data + 8) + marginY < valueY) ||
            (valueY < *(f32 *)(entry->data + 0xC) - marginY)) {
            *arg2 = arg6;
            return;
        }
        if (valueY < *(f32 *)(entry->data + 0xC)) {
            bound = *(f32 *)(entry->data + 0xC);
        } else if (*(f32 *)(entry->data + 8) < valueY) {
            bound = *(f32 *)(entry->data + 8);
        } else {
            bound = valueY;
        }
        *arg2 = bound;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15039ED0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_15039ED0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A08C.s")
extern u8 D_800C3E78;

void func_1503A60C(void) {
    Game64120OutputBlock *temp_v0;
    Game64120Record *temp_v1;

    temp_v0 = &D_800CC2D0[D_800C3E78].output->block;
    temp_v1 = &D_800CC2D0[D_800C3E78];
    temp_v0->x = temp_v1->x;
    temp_v0->y = D_800CC2D0[D_800C3E78].y;
    temp_v0->z = D_800CC2D0[D_800C3E78].z;
}
typedef struct Game64120Motion {
    u8 pad0[0xC];
    f32 zero0;
    u8 pad10[0xC];
    f32 zero1;
    u8 pad20[0xC];
    f32 zero2;
    f32 x;
    f32 y;
    f32 z;
    f32 one;
} Game64120Motion;

typedef union Game64120FloatBits {
    f32 value;
    u32 bits;
} Game64120FloatBits;

void func_150A7BC0(void *);
void func_150A7CB0(void *, u32, u32, u32);
void func_150A7A48(void *, void *, void *);
void func_10023A10(void *, void *, s32);
extern u8 D_80084404[];
extern u8 D_800C3FFA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503A678 CURRENT (667) */
void func_1503A678(void) {
    Game64120FloatBits scale[5];
    u8 transform[0x48];
    u8 transformed[0x40];
    f32 original[3];
    Game64120Record *record;
    Game64120Motion *motion;
    f32 factor;

    record = &D_800CC2D0[D_800C3E78];
    if (record->pad0[4] != 0x22) {
        return;
    }
    factor = (f32)(u32)record->pad1D8[0x32] * 0.015625f + 1.0f;
    if (D_800C3FFA == 0) {
        scale[0].value = factor;
        scale[1].value = 1.0f;
        scale[2].value = factor;
    } else {
        scale[0].value = 1.0f / factor;
        scale[1].value = 1.0f;
        scale[2].value = scale[0].value;
    }
    motion = ((Game64120Motion *)record->output) + D_80084404[D_800C3FFA];
    motion->one = 1.0f;
    motion->zero0 = 0.0f;
    motion->zero1 = 0.0f;
    motion->zero2 = 0.0f;
    original[0] = motion->x;
    original[1] = motion->y;
    original[2] = motion->z;
    func_150A7BC0(transform);
    func_150A7CB0(transform, scale[0].bits, scale[1].bits, scale[2].bits);
    func_150A7A48(motion, transform, transformed);
    func_10023A10(transformed, motion, 0x40);
    motion->x = original[0];
    motion->y = original[1];
    motion->z = original[2];
    D_800C3FFA++;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503A678 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A678.s")
void func_15036F34(void);
void func_1503A678(void);
extern u8 D_800C3FFA;

void func_1503A7F0(void) {
    s32 temp_t6;
    s32 sp1C;

    temp_t6 = D_800C3FFA;
    D_800C3FFA = 0;
    sp1C = temp_t6;
    func_15036F34();
    D_800C3FFA = sp1C;
    func_1503A678();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503A830.s")
s32 func_15037880(s32, f32 *);
void func_150380C0(void *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800986EC;
extern f32 D_800C3FD0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503B708 CURRENT (450) */
void func_1503B708(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    f32 *scratch;
    f32 value;

    scratch = D_800C3FD0;
    value = D_800986EC;
    *(f32 *)((u8 *)arg0 + 0) = value;
    *(f32 *)((u8 *)arg0 + 4) = value;
    *(f32 *)((u8 *)arg0 + 8) = value;
    scratch[0] = value;
    scratch[1] = value;
    scratch[2] = value;
    if (func_15037880(arg3, arg0) == 0) {
        func_150380C0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                      arg8, arg9, arg10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503B708 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_64120/func_1503B708.s")
