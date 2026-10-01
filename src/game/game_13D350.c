#include "types.h"

/*
 * Reviewed source unit: src/game/game_13D350.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510FEA0
 * - func_151103C8
 * - func_15110544
 * - func_151106A8
 * - func_151108C4
 * - func_15110CFC
 * - func_15111858
 * - func_15111AF4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_1510FEA0.s")
void func_150A8050(void *, f32, f32, f32);
void func_151102CC(void *, f32, f32, f32);
void func_150A7A48(void *, void *, void *);
void func_151102CC(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[16];

    func_150A8050(arg0, 0.0f, arg2, 0.0f);
    func_150A8050(sp28, arg1, 0.0f, 0.0f);
    func_150A7A48(arg0, sp28, arg0);
    func_150A8050(sp28, 0.0f, 0.0f, arg3);
    func_150A7A48(arg0, sp28, arg0);
}
typedef struct Game13D350Record {
    u8 pad0[0xBC];
    u8 payload[0xC4];
} Game13D350Record;

extern Game13D350Record *D_800BE628;

void func_15110360(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_151102CC(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, D_800BE628[arg0].payload, arg1);
}
void *func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A6CC(void *, s32, s32, s32, s32);
void *func_15110544(void *, s32, s32, s32, s32, s32, s32, u8);
extern s32 D_80082FA0;
extern s32 D_80082FA4;
extern s32 D_800BE620;
extern s32 D_800BE624;
extern u8 D_800DBEA8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151103C8 CURRENT (1553) */
void *func_151103C8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game13D350Record *record = &D_800BE628[D_80082FA4];
    void *temp_v0;
    void *temp_v0_2;
    void *var_a0;
    s32 half;

    temp_v0 = func_15110544(arg0,
                           (s32)*(f32 *)((u8 *)record + 0x2C),
                           (s32)*(f32 *)((u8 *)record + 0x24),
                           (s32)(*(f32 *)((u8 *)record + 0x30) - 1.0f),
                           (s32)*(f32 *)((u8 *)record + 0x28),
                           D_800DBEA8[0], D_800DBEA8[1], D_800DBEA8[2]);
    var_a0 = temp_v0;
    if ((D_80082FA0 != 0) && (D_80082FA4 == 0)) {
        *(s32 *)temp_v0 = 0xE7000000;
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
        temp_v0_2 = func_1501A490((u8 *)var_a0 + 8, 0xFF, 0, 0, 0, 0);
        *(s32 *)temp_v0_2 = 0xF7000000;
        *(s32 *)((u8 *)temp_v0_2 + 4) = 0x10001;
        half = D_800BE624 >> 1;
        var_a0 = func_1501A6CC((u8 *)temp_v0_2 + 8, 0, half - 6,
                                D_800BE620, half + 6);
        if (D_80082FA0 != 1) {
            half = D_800BE620 >> 1;
            var_a0 = func_1501A6CC(var_a0, half - 1, 0, half + 1,
                                    D_800BE624);
        }
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151103C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151103C8.s")

void *func_1501A680(void *);
void *func_1501A6CC(void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15110544 CURRENT (1980) */
void *func_15110544(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, s32 arg5, s32 arg6, u8 arg7) {
    void *temp_a0;
    void *temp_v0;
    s32 packed;

    *(s32 *)arg0 = 0xE7000000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    temp_a0 = (u8 *)arg0 + 8;
    *(s32 *)((u8 *)temp_a0 + 4) = 4;
    *(s32 *)temp_a0 = 0xEF302C0F;
    temp_v0 = func_1501A680((u8 *)temp_a0 + 8);
    *(s32 *)temp_v0 = 0xF7000000;
    packed = (((u8)arg5 << 8) & 0xF800) |
             (((u8)arg6 * 8) & 0x7C0) |
             ((((s32)arg7 >> 2) & 0x3E) | 1);
    *(s32 *)((u8 *)temp_v0 + 4) = (packed << 16) | packed;
    return func_1501A6CC((u8 *)temp_v0 + 8, arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15110544 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110544.s")
extern s32 D_800BE9F0;
extern u8 D_800DBEA8[];
extern void *D_800DBFF0;
extern s32 D_800BE620;
extern s32 D_800BE624;

s32 func_15110600(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;

    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E) ||
        ((D_800BE9F0 == 0x31) &&
         (*(u8 *)((u8 *)*(void **)((u8 *)D_800DBFF0 + 0x3D4) + 0x78) == 3))) {
        temp_v0 = D_800DBEA8;
        arg0 = (s32)func_15110544((void *)arg0, 2, 0, D_800BE620 - 2,
                                   D_800BE624, temp_v0[0], temp_v0[1], temp_v0[2]);
    }
    return arg0;
}
/* Call context: func_1501A490: unique active project prototype */
void * func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A680(void *);                        /* extern */
void *func_1501A6CC(void *, s32, s32, s32, s32);    /* extern */
extern s32 D_80082FA0;
extern s32 D_80082FA4;
extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE9C4;
extern u8 D_800BEAC2;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151106A8 CURRENT (5653) */
void *func_151106A8(void *arg0) {
    s32 temp_t5;
    s32 temp_t7;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_80082FA4 == 0) {
        temp_a0 = (void *)(var_a0 + 8);
        *(s32 *)((u8 *)var_a0 + 0) = 0xE7000000;
        *(s32 *)((u8 *)var_a0 + 4) = 0;
        *(s32 *)((u8 *)temp_a0 + 4) = 4;
        *(s32 *)((u8 *)var_a0 + 8) = 0xEF302C0F;
        temp_a0_2 = (void *)(temp_a0 + 8);
        *(s32 *)((u8 *)temp_a0 + 8) = 0xFCFFFFFF;
        *(s32 *)((u8 *)temp_a0_2 + 4) = 0xFFFE793C;
        temp_a0_3 = (void *)(temp_a0_2 + 8);
        *(s32 *)((u8 *)temp_a0_2 + 8) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFF100000);
        temp_a0_4 = (void *)(temp_a0_3 + 8);
        *(s32 *)((u8 *)temp_a0_3 + 4) = (s32) D_800BE9C4;
        *(s32 *)((u8 *)temp_a0_3 + 8) = 0xF7000000;
        *(s32 *)((u8 *)temp_a0_4 + 4) = 0xFFFCFFFC;
        temp_v0 = (void *)(func_1501A490(temp_a0_4 + 8, 0xFF, 0, 0, 0, 0));
        *(s32 *)((u8 *)temp_v0 + 4) = 0x8000;
        *(s32 *)((u8 *)temp_v0 + 0) = (s32) ((((D_800BE620 - 2) & 0x3FF) << 0xE) | 0xF6000000 | ((D_800BE624 & 0x3FF) * 4));
        *(s32 *)((u8 *)temp_v0 + 8) = 0xE7000000;
        *(s32 *)((u8 *)temp_v0 + 0xC) = 0;
        temp_v0_2 = (void *)(func_1501A680(temp_v0 + 0x10));
        var_a0 = temp_v0_2;
        if (D_80082FA0 != 0) {
            *(s32 *)((u8 *)temp_v0_2 + 0) = 0xE7000000;
            *(s32 *)((u8 *)temp_v0_2 + 4) = 0;
            temp_v0_3 = (void *)(func_1501A490(var_a0 + 8, 0xFF, 0, 0, 0, 0));
            *(s32 *)((u8 *)temp_v0_3 + 0) = 0xF7000000;
            *(s32 *)((u8 *)temp_v0_3 + 4) = 0x10001;
            temp_t5 = (s32) D_800BE624 >> 1;
            var_a0 = (void *)(func_1501A6CC(temp_v0_3 + 8, 0, temp_t5 - 6, D_800BE620, temp_t5 + 6));
            if (D_80082FA0 != 1) {
                temp_t7 = (s32) D_800BE620 >> 1;
                var_a0 = (void *)(func_1501A6CC(var_a0, temp_t7 - 1, 0, temp_t7 + 1, D_800BE624));
            }
            if (D_800BEAC2 != 0) {
                var_a0 = func_1501A6CC(var_a0, 0, 0, D_800BE620, D_800BE624);
            }
        }
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151106A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151106A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151108C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110CFC.s")
typedef struct {
    u8 pad0[8];
    u8 mode;
    u8 selection;
} Game13D350State;

void func_10004074(s32);
void func_1510D694(s32);
void func_15111858(void);
void func_1502B7F0(void **, s32, s32, u8);
extern u8 D_80038080;
extern s32 *D_800891BC[];
extern Game13D350State *D_800B0DF0;
extern void *D_800DBE80;

void func_1511172C(s32 arg0) {
    s32 i;

    if (arg0 == 1) {
        D_800B0DF0->mode = 1;
        if (D_800DBE80 != 0) {
            func_10004074((s32) D_800DBE80);
        }
        func_15111858();
        return;
    }
    if ((arg0 != D_800B0DF0->selection) && (D_800B0DF0->mode == 4)) {
        i = 0;
        if (D_80038080 != 0) {
            do {
                func_1510D694(*D_800891BC[D_800B0DF0->selection] + i);
                i++;
            } while (i != 0x168);
        }
        func_10004074((s32) D_800DBE80);
        D_800B0DF0->selection = (u8) arg0;
        func_1502B7F0(&D_800DBE80, 2, 0xD, D_800B0DF0->selection);
    }
}
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
u32 func_150ADA20();                                /* extern */
extern f32 D_800A2F24;
extern f32 D_800A2F28;
extern f32 D_800A2F2C;
extern void *D_800DBE80;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15111858 CURRENT (320) */
void func_15111858(void) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv1;
    f32 var_fa0;
    s32 temp_ft3;
    s32 var_s1;
    struct { u16 x, y, z; u8 kind, alpha; } *var_s0;
    union { f32 value; u16 half[2]; } sp78;

    D_800DBE80 = func_10003C40(0xFA00, 1, 0, 0);
    var_s1 = 0;
    var_s0 = D_800DBE80;
    do {
        temp_fs1 = (f32) (func_150ADA20() % 36000U) * 0.000174532920937053859f;
        temp_fv1 = (f32) (s32) ((func_150ADA20() % 1584400U) - 0xC1624) * 0.01f;
        if (temp_fv1 >= 0.0f) {
            var_fa0 = 89.0f - sqrtf(temp_fv1);
        } else {
            var_fa0 = sqrtf(-temp_fv1) + -89.0f;
        }
        var_fa0 *= 0.0174532923847436905f;
        temp_ft3 = (s32) (func_150AD78C(var_fa0) * 256.0f);
        sp78.value = (f32) temp_ft3;
        var_s0->y = sp78.half[0];
        temp_fs0 = sqrtf((f32) (0x10000 - (temp_ft3 * temp_ft3)));
        sp78.value = (f32) (s32) (func_150AD78C(temp_fs1) * temp_fs0);
        var_s0->x = sp78.half[0];
        sp78.value = (f32) (s32) (func_150AD780(temp_fs1) * temp_fs0);
        var_s0->z = sp78.half[0];
        var_s0->alpha = (s8) ((func_150ADA20() % 191U) + 0x40);
        var_s0->kind = (s8) (func_150ADA20() % 5U);
        var_s1 += 1;
        var_s0++;
    } while (var_s1 != 0x1F40);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15111858 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111858.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111AF4.s")
