#include "types.h"

/*
 * Reviewed source unit: src/game/game_6B320.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503DE70
 * - func_1503DF48
 * - func_1503E260
 * - func_1503E5F8
 * - func_1503E82C
 * - func_1503EA54
 * - func_1503EB78
 * - func_1503ECA0
 * - func_1503EFC4
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

void func_1503DF0C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = (void *)((u8 *)&D_800C6660 + (arg0 * 0x10));
    *(s32 *)((u8 *)temp_v0 + 4) |= arg2;
    *(s32 *)((u8 *)temp_v0 + 8) |= arg3;
    *(s8 *)((u8 *)temp_v0 + 0xE) = arg1;
    *(s8 *)((u8 *)temp_v0 + 0xF) = 2;
}
typedef struct Game6B320Particle {
    u8 fields[0x64];
    u8 active;
    u8 reserved_65[3];
} Game6B320Particle;

void *func_10003C40(s32, s32, s32, s32);
s32 func_1503E1F4(s32, s32);
void func_1503E3C4(s32, s32, s32, s32, s32);
void func_1503EA54(s32);
void func_1503E82C(s32);
extern void (*D_80084430[])(void *, s32);
extern void (*D_8008443C[])(s32);
extern void (*D_80084448[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DF48 CURRENT (2426) */
void func_1503DF48(s32 arg0) {
    Game6B320Slot *slot;
    Game6B320Particle *allocated;
    Game6B320Particle *particle;
    u8 *actor;
    s8 *parent;
    s8 *list;
    s32 state;
    s32 count;
    s32 i;

    slot = &D_800C6660[arg0];
    state = slot->pad_E[1];
    if (state == 2) {
        actor = D_800CC2D0 + arg0 * 0x32C;
        actor[0x74] |= 0x80;
        state = 3;
        if (*(s32 *)(actor + 0x1D4) == 0) {
            return;
        }
    }
    if (state == 3) {
        count = D_80098914[slot->pad_E[0]];
        if (slot->entity == 0) {
            allocated = func_10003C40(count * 0x68, 1, 0, 0);
            if (allocated == 0) {
                return;
            }
            slot->entity = (Game6B320Entity *)allocated;
            for (i = 0; i < count; i++) {
                allocated[i].active = 0;
            }
        }
        list = D_80084454[slot->pad_E[0]];
        i = 0;
        if (count > 0) {
            parent = list;
            do {
            if (*parent != -2) {
                particle = (Game6B320Particle *)slot->entity + i;
                if (func_1503E1F4(i, arg0) != 0 && particle->active == 0) {
                    func_1503E3C4(arg0, i, 0, (s32)particle, 0);
                    D_80084430[slot->pad_E[0]](particle, arg0);
                    particle->active = 1;
                }
            }
                i++;
                parent++;
            } while (i != count);
        }
        D_8008443C[slot->pad_E[0]](arg0);
        state = 1;
        slot->pad_E[1] = 1;
    }
    if (state == 1) {
        D_80084448[slot->pad_E[0]](arg0);
        if (slot->pad_E[1] != 0) {
            func_1503EA54(arg0);
            func_1503E82C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DF48 */
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
extern u8 *D_80084460[];
void func_10004074(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503E260 CURRENT (93) */
void func_1503E260(s32 arg0) {
    Game6B320Slot *slot = &D_800C6660[arg0];
    s32 i;
    u8 *list;
    u8 *mask;
    u8 *actor;
    u8 count;
    u8 selector;

    if (slot->pad_E[1] != 0) {
        selector = slot->pad_E[0];
        list = D_80084460[selector];
        if (list != 0) {
            count = D_80098914[selector];
            i = 0;
            mask = list;
            if ((s32)count > 0) {
                do {
                    if (*mask != 0xFF && func_1503E1F4(i, arg0) != 0) {
                        actor = D_800CC2D0 + arg0 * 0x32C;
                        *(s32 *)(actor + 0x94) |= 1 << *mask;
                    }
                    i++;
                    mask++;
                } while (i != count);
            }
        }
        actor = D_800CC2D0 + arg0 * 0x32C;
        slot->pad_E[1] = 0;
        if (slot->entity != 0) {
            func_10004074((s32)slot->entity);
        }
        {
            u8 flags = actor[0x74];
            slot->entity = 0;
            actor[0x74] = flags & 0xFF7F;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503E260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E260.s")
/* Call context: func_10023A10: unique active project prototype */
/* Call context: func_1503E5F8: unique active declaration in the allowed source */
/* Call context: func_150A7A48: unique active declaration in the allowed source */
void func_10023A10(void *, void *, s32);
void func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150A7A48(void *, void *, void *);

void func_150499A0(void *, void *);
f32 sqrtf(f32);
#pragma intrinsic (sqrtf)

void func_1503E3C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s8 var_v0;
    f32 matrix[4][4];
    f32 inverse[4][4];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 var_fv1;
    u8 *temp_s1;

    temp_s1 = (arg0 * 0x32C) + D_800CC2D0;
    func_10023A10(*(u8 **)(temp_s1 + 0x1D4) + ((arg1 + arg2) << 6), (u8 *)matrix, 0x40);
    if (arg4 != 0) {
        var_v0 = -1;
    } else {
        var_v0 = D_80084454[D_800C6660[arg0].pad_E[0]][arg1];
    }
    if (var_v0 != -1) {
        func_150499A0(*(u8 **)(temp_s1 + 0x1D4) + (var_v0 << 6), inverse);
        matrix[1][3] = 0.0f;
        matrix[0][3] = 0.0f;
        matrix[2][3] = 0.0f;
        matrix[3][3] = 1.0f;
        func_150A7A48((u8 *)matrix, inverse, (u8 *)matrix);
    }
    func_1503E5F8((u8 *)matrix, arg3, arg3 + 4, arg3 + 8, arg3 + 0xC, arg3 + 0x10, arg3 + 0x14, arg3 + 0x18, arg3 + 0x1C, arg3 + 0x20);
    *(f32 *)((u8 *)arg3 + 0x28) = (f32) *(f32 *)((u8 *)arg3 + 4);
    *(f32 *)((u8 *)arg3 + 0x2C) = (f32) *(f32 *)((u8 *)arg3 + 8);
    *(f32 *)((u8 *)arg3 + 0x30) = (f32) *(f32 *)((u8 *)arg3 + 0xC);
    temp_fv0 = *(f32 *)((u8 *)arg3 + 0);
    *(f32 *)((u8 *)arg3 + 0x34) = (f32) *(f32 *)((u8 *)arg3 + 0x10);
    *(f32 *)((u8 *)arg3 + 0x24) = temp_fv0;
    *(f32 *)((u8 *)arg3 + 0x38) = (f32) *(f32 *)((u8 *)arg3 + 0x14);
    *(f32 *)((u8 *)arg3 + 0x3C) = (f32) *(f32 *)((u8 *)arg3 + 0x18);
    *(f32 *)((u8 *)arg3 + 0x40) = (f32) *(f32 *)((u8 *)arg3 + 0x1C);
    *(f32 *)((u8 *)arg3 + 0x44) = (f32) *(f32 *)((u8 *)arg3 + 0x20);
    temp_fa0 = temp_fv0 - *(f32 *)((u8 *)temp_s1 + 0x14);
    temp_fa1 = (*(f32 *)((u8 *)arg3 + 0x28) - *(f32 *)((u8 *)temp_s1 + 0x18)) - 30.0f;
    temp_ft4 = *(f32 *)((u8 *)arg3 + 0x2C) - *(f32 *)((u8 *)temp_s1 + 0x1C);
    var_fv1 = sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1) + (temp_ft4 * temp_ft4));
    if (var_fv1 == 0.0f) {
        var_fv1 = 1.0f;
    }
    var_fv1 = 1.0f / var_fv1;
    *(f32 *)((u8 *)arg3 + 0x48) = (f32) (temp_fa0 * var_fv1);
    *(f32 *)((u8 *)arg3 + 0x4C) = (f32) (temp_fa1 * var_fv1);
    *(f32 *)((u8 *)arg3 + 0x50) = (f32) (temp_ft4 * var_fv1);
}
f32 func_150484A0(f32, f32);
/* Used-input contract: raw callers set only f12; the matched callee
 * overwrites its other reconstructed parameter before every read. */
f32 func_150487E0(f32);
void func_15049148(void *, f32, void *);
f32 func_150AD780(f32);
void func_150AD8B0(f32 *, f32 *, f32 *);
f32 func_150AD900(f32 *, f32 *);
f32 func_150AD930(f32 *);
extern f32 D_80098918;
extern f32 D_8009891C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503E5F8 CURRENT (3575) */
void func_1503E5F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9) {
    f32 matrix[16];
    f32 cross[3];
    f32 *row;
    f32 *negative_row;
    f32 epsilon;
    f32 length;
    f32 angle_x;
    f32 angle_y;
    f32 angle_z;
    f32 scale;

    func_10023A10(arg0, &matrix, 0x40);
    *(f32 *)arg1 = matrix[12];
    *(f32 *)arg2 = matrix[13];
    *(f32 *)arg3 = matrix[14];
    epsilon = D_80098918;
    row = (matrix + 0);
    do {
        length = func_150AD930(row);
        if (length == 0.0f) {
            length = epsilon;
        }
        if (row == (matrix + 0)) {
            *(f32 *)arg7 = length;
        } else if (row == (matrix + 4)) {
            *(f32 *)arg8 = length;
        } else {
            *(f32 *)arg9 = length;
        }
        func_15049148(row, 1.0f / length, row);
        row += 4;
    } while ((u32)row < (u32)(matrix + 12));
    func_150AD8B0((matrix + 4), (matrix + 8), cross);
    if (func_150AD900((matrix + 0), cross) < 0.0f) {
        negative_row = (matrix + 0);
        *(f32 *)arg7 = -*(f32 *)arg7;
        *(f32 *)arg8 = -*(f32 *)arg8;
        *(f32 *)arg9 = -*(f32 *)arg9;
        do {
            negative_row[0] = -negative_row[0];
            negative_row[1] = -negative_row[1];
            negative_row[2] = -negative_row[2];
            negative_row += 4;
        } while (negative_row != (matrix + 12));
    }
    angle_y = func_150487E0(-matrix[2]);
    if (func_150AD780(angle_y) != 0.0f) {
        angle_x = func_150484A0(matrix[6], matrix[10]);
        angle_z = func_150484A0(matrix[1], matrix[0]);
    } else {
        angle_x = func_150484A0(matrix[4], matrix[5]);
        angle_z = 0.0f;
    }
    scale = D_8009891C;
    *(f32 *)arg4 = angle_x * scale;
    *(f32 *)arg5 = angle_y * scale;
    *(f32 *)arg6 = angle_z * scale;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503E5F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503E5F8.s")
/* Call context: func_15043EC8: matched US definition in src/done/game/game_71240.c */
/* Call context: func_150A7A48: unique active project prototype */
void func_15043EC8(void *, f32, f32, f32, f32, f32, f32);
void func_150A7A48(void *, void *, void *);

void func_150A7CB0(void *, s32, s32, s32);
void func_150A7DA0(void *, s32, s32, s32);
void func_150A8050(void *, f32, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503E82C CURRENT (432) */
void func_1503E82C(s32 arg0) {
    s32 count;
    Game6B320Slot *temp_s6;
    s32 var_s5;
    s8 *var_s7;
    s8 temp_s3;
    f32 matrix[4][4];
    u8 *temp_fp;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_fp = (arg0 * 0x32C) + D_800CC2D0;
    if (*(s32 *)(temp_fp + 0x1D4) != 0) {
        temp_s6 = &D_800C6660[arg0];
        count = D_80098914[temp_s6->pad_E[0]];
        var_s7 = D_80084454[temp_s6->pad_E[0]];
        var_s5 = 0;
        if (count > 0) {
            do {
                if (*var_s7 != -2) {
                    temp_s0 = (u8 *)temp_s6->entity + (var_s5 * 0x68);
                    if (*(u8 *)(temp_s0 + 0x64) != 0) {
                        temp_s3 = D_80084454[temp_s6->pad_E[0]][var_s5];
                        temp_s1 = *(u8 **)(temp_fp + 0x1D4) + (var_s5 << 6);
                        if (temp_s3 != -1) {
                            func_150A7DA0(matrix, *(s32 *)(temp_s0 + 0x24), *(s32 *)(temp_s0 + 0x28), *(s32 *)(temp_s0 + 0x2C));
                            func_150A7A48(matrix, *(u8 **)(temp_fp + 0x1D4) + (temp_s3 << 6), matrix);
                            temp_s0 = (u8 *)temp_s6->entity + (var_s5 * 0x68);
                            func_150A8050(temp_s1, *(f32 *)(temp_s0 + 0x30), *(f32 *)(temp_s0 + 0x34), *(f32 *)(temp_s0 + 0x38));
                            func_150A7A48(temp_s1, matrix, temp_s1);
                            temp_s0 = (u8 *)temp_s6->entity + (var_s5 * 0x68);
                            func_150A7CB0(matrix, *(s32 *)(temp_s0 + 0x3C), *(s32 *)(temp_s0 + 0x40), *(s32 *)(temp_s0 + 0x44));
                            func_150A7A48(matrix, temp_s1, temp_s1);
                        } else {
                            func_150A8050(temp_s1, *(f32 *)(temp_s0 + 0x30), *(f32 *)(temp_s0 + 0x34), *(f32 *)(temp_s0 + 0x38));
                            temp_s0 = (u8 *)temp_s6->entity + (var_s5 * 0x68);
                            func_15043EC8(temp_s1, *(f32 *)(temp_s0 + 0x3C), *(f32 *)(temp_s0 + 0x40), *(f32 *)(temp_s0 + 0x44), *(f32 *)(temp_s0 + 0x24), *(f32 *)(temp_s0 + 0x28), *(f32 *)(temp_s0 + 0x2C));
                        }
                    }
                }
                var_s5 += 1;
                var_s7 += 1;
            } while (var_s5 != count);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503E82C */
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EB78 CURRENT (227) */
void func_1503EB78(void *arg0, f32 arg1, f32 arg2, s32 arg3) {
    f32 sp50[3];
    f32 *var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *var_s0;

    if (arg3 != 0) {
        var_s3 = 0x80;
        var_s4 = 0x7F;
    } else {
        var_s3 = 0xFF;
        var_s4 = 0;
    }
    arg1 *= D_80098920;
    var_s0 = arg0;
    var_s1 = sp50;
    sp50[0] = arg1;
    sp50[2] = arg1;
    sp50[1] = arg2 * D_80098920;
    do {
        arg3 = func_150ADA20();
        arg1 = *var_s1;
        arg2 = *(f32 *)(var_s0 + 0x48);
        var_s1++;
        var_s0 += 4;
        *(f32 *)(var_s0 + 0x44) =
            arg2 * (((f32)((arg3 & var_s3) + var_s4) *
                         arg1) + 2.0f);
    } while ((u32)var_s1 < (u32)&sp50[3]);
    var_s2 = 0;
    var_s0 = arg0;
    do {
        arg3 = func_150ADA20();
        var_s2 += 1;
        var_s0 += 4;
        *(f32 *)(var_s0 + 0x50) =
            (f32)((arg3 & 0xFF) - 0x80) * 0.03125f;
    } while (var_s2 != 3);
    *(f32 *)((u8 *)arg0 + 0x60) = D_80098924;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503EB78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503EB78.s")
void func_1510F800(s32);
s32 func_1510F8D8(s32, s32, s32, s32);
extern f32 D_80098928;
extern f32 D_8009892C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503ECA0 CURRENT (290) */
void func_1503ECA0(s32 arg0) {
    Game6B320Entity *temp_v0;
    Game6B320Slot *temp_s3;
    f32 temp_fs1;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_s1;
    s32 var_s2;
    u8 *temp_s0;
    s32 temp_s6;

    func_1510F800(0);
    temp_s3 = &D_800C6660[arg0];
    var_s1 = 0;
    temp_s6 = D_80098914[temp_s3->pad_E[0]];
    var_s2 = 0;
    if ((s32) temp_s6 > 0) {
        temp_fs5 = 0.4f;
        temp_fs1 = 0.8f;
        do {
            temp_v0 = temp_s3->entity;
            if (*((u8 *)temp_v0 + var_s2 + 0x64) != 0) {
                temp_s0 = (u8 *)temp_v0 + var_s2;
                if ((D_80084454[temp_s3->pad_E[0]][var_s1] == -1) && (*(f32 *)(temp_s0 + 0x60) != 0.0f)) {
                    temp_fv0 = (f32) (func_1510F8D8((s32) *(f32 *)(temp_s0 + 0x24), (s32) *(f32 *)(temp_s0 + 0x28), (s32) *(f32 *)(temp_s0 + 0x2C), 0) + 5);
                    if (*(f32 *)(temp_s0 + 0x28) < temp_fv0) {
                        temp_fv1 = *(f32 *)(temp_s0 + 0x4C);
                        *(f32 *)(temp_s0 + 0x28) = temp_fv0;
                        if (temp_fv1 < -4.0f) {
                            *(f32 *)(temp_s0 + 0x48) = (f32) (*(f32 *)(temp_s0 + 0x48) * temp_fs1);
                            *(f32 *)(temp_s0 + 0x4C) = (f32) (temp_fv1 * -0.5f);
                            *(f32 *)(temp_s0 + 0x50) = (f32) (*(f32 *)(temp_s0 + 0x50) * temp_fs1);
                            *(f32 *)(temp_s0 + 0x54) = (f32) (*(f32 *)(temp_s0 + 0x54) * -1.0f);
                            *(f32 *)(temp_s0 + 0x58) = (f32) (*(f32 *)(temp_s0 + 0x58) * temp_fs5);
                            *(f32 *)(temp_s0 + 0x5C) = (f32) (*(f32 *)(temp_s0 + 0x5C) * -1.0f);
                        } else {
                            *(f32 *)(temp_s0 + 0x5C) = 0.0f;
                            *(f32 *)(temp_s0 + 0x58) = 0.0f;
                            *(f32 *)(temp_s0 + 0x54) = 0.0f;
                            *(f32 *)(temp_s0 + 0x60) = 0.0f;
                            *(f32 *)(temp_s0 + 0x50) = 0.0f;
                            *(f32 *)(temp_s0 + 0x4C) = 0.0f;
                            *(f32 *)(temp_s0 + 0x48) = 0.0f;
                        }
                    }
                }
            }
            var_s1 += 1;
            var_s2 += 0x68;
        } while (var_s1 != temp_s6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503ECA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6B320/func_1503ECA0.s")
void func_1503EEB8(void) {

}
void func_15060F28(u8 *, s32);
void func_1503ECA0(s32);
extern s32 D_800BE9E4;
extern u8 D_800CC2D0[];

void func_1503EEC0(s32 arg0) {
    Game6B320Slot *temp_v1;
    s32 temp_v0;

    func_1503ECA0(arg0);
    temp_v1 = &D_800C6660[arg0];
    temp_v0 = temp_v1->field_C;
    temp_v0 -= D_800BE9E4;
    temp_v1->field_C = temp_v0;
    if (temp_v0 <= 0) {
        func_15060F28(D_800CC2D0 + (arg0 * 0x32C), 1);
    }
}
s32 func_1503EF4C(s32 arg0, s32 arg1, s32 arg2) {
    Game6B320MaskPair *base;
    u32 tmp1;
    u32 *tmp2;
    Game6B320MaskPair *pair;
    u32 first;

    base = D_8008446C[arg0];
    pair = (Game6B320MaskPair *)((u8 *)base + (arg1 * sizeof(*pair)));
    first = pair->first;
    tmp2 = &D_800C6668[arg2].bits;
    if ((first == 0 || D_800C6664[arg2].bits & (tmp1 = first)) && (((*pair).second == 0) || *tmp2 & (*pair).second)) {
        return 1;
    }
    return 0;
}
extern u8 D_80098914[];
extern u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503EFC4 CURRENT (145) */
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
                (f32)((s32)(func_150ADA20() % 20U) - 5);
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

void func_1503F16C(s32 arg0) {
    u8 *entity;

    *(s16 *)((u8 *)&D_800C666C + arg0 * 0x10) = 0x12C;
    if (func_1503EF4C(2, 0, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) |= 0x40;
        *(volatile s32 *)(entity + 0x94) = *(s32 *)(entity + 0x94) & ~0x200;
    }
    if (func_1503EF4C(2, 1, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) |= 0x80;
        *(volatile s32 *)(entity + 0x94) = *(s32 *)(entity + 0x94) & ~0x100;
    }
    if (func_1503EF4C(2, 2, arg0) != 0) {
        entity = D_800CC2D0 + arg0 * 0x32C;
        *(s32 *)(entity + 0x94) &= ~0x400;
    }
}
void func_1503E260(s32);

void func_1503F2B0(s32 arg0) {
    Game6B320Slot *slot;
    u8 *entity;

    func_1503ECA0(arg0);
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
void func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
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
