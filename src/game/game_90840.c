#include "types.h"

/*
 * Reviewed source unit: src/game/game_90840.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15063404
 * - func_150634E4
 * - func_15063570
 * - func_15063628
 * - func_150636A4
 * - func_150636F0
 * - func_15063B64
 * - func_15063C60
 * - func_15063E84
 * - func_15063FA0
 * - func_150641D8
 * - func_150642AC
 * - func_15064A14
 * - func_15064B94
 * - func_15065A5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game90840Inner {
    u8 pad0[0x12];
    s16 field_12;
    u8 pad14[0x11C];
    f32 field_130;
    f32 field_134;
    f32 field_138;
    s32 field_13C;
    s32 field_140;
    s32 field_144;
} Game90840Inner;

typedef struct Game90840Actor {
    u8 pad0[0x14];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[0x5A];
    u16 field_7A;
    u8 pad7C[0x1A6];
    u8 field_222;
    u8 pad223[0xAD];
    struct Game90840Value *field_2D0;
    u8 pad2D4[0x48];
    Game90840Inner *field_31C;
    u8 pad320[0xC];
} Game90840Actor;

typedef struct Game90840Value {
    u8 pad0[8];
    f32 field_8;
    u8 padC[0xC];
    f32 field_18;
} Game90840Value;

s32 func_1505A630(f32, f32, s32);
extern Game90840Actor D_800CC2D0[];

s16 func_15063390(Game90840Actor *arg0) {
    Game90840Actor *other = &D_800CC2D0[arg0->field_222];

    return func_1505A630(other->x - arg0->x, arg0->z - other->z, 0);
}
void func_15083568(void *, s32, s32, s32);
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063404 CURRENT (3324) */
void func_15063404(s32 arg0) {
    s32 index;
    Game90840Actor *sp28;
    Game90840Actor *temp_v0;

    index = (arg0 - (s32)D_800CC2D0) / 0x32C;
    temp_v0 = (Game90840Actor *)((u8 *)D_800CC2D0 + (index * 0x32C));
    temp_v0->field_31C->pad14[0x64] = 9;
    sp28 = temp_v0;
    func_15083568((void *)arg0, 0x1D, 0x3F800000, 0);
    func_15083568((void *)arg0, 0x1E, 0x3F800000, 0);
    *(s8 *)(arg0 + 0x8A) = 0x14;
    *(s8 *)(arg0 + 0x89) = 0;
    *(s8 *)(arg0 + 0x83) = 0;
    *(s16 *)((u8 *)temp_v0->field_31C + 0x24) = 0x3C;
    temp_v0->field_31C->pad14[0x106] = 2;
    func_1505E650((u8 *)arg0, 0x7F, 0x3F800000, 0, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063404 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063404.s")
void func_150836CC(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150634E4 CURRENT (2670) */
void func_150634E4(void *arg0) {
    Game90840Actor *temp_v0;

    temp_v0 = &D_800CC2D0[(s32)((u8 *)arg0 - (u8 *)D_800CC2D0) / 0x32C];
    temp_v0->field_31C->pad14[0x64] = 0;
    temp_v0->field_31C->pad14[0x106] = 0;
    func_150836CC(arg0, 0x1D);
    func_150836CC(arg0, 0x1E);
    *(u8 *)((u8 *)arg0 + 0x8A) = 0;
    *(u8 *)((u8 *)arg0 + 0x89) = 0;
    *(u8 *)((u8 *)arg0 + 0x83) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150634E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150634E4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063570 CURRENT (4221) */
void func_15063570(u8 *arg0) {
    Game90840Actor *actor = (Game90840Actor *)arg0;

    actor->field_31C->pad14[0x64] = 0x3B;
    actor->field_31C->pad14[0x106] = 2;
    func_15083568(0x89, 0x3F800000, 0);
    arg0[0x8A] = 0x14;
    arg0[0x89] = 0;
    arg0[0x83] = 0;
    func_1505E650(arg0, 0x221, 0x3F800000, 0, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063570.s")
void func_15081690(f32, s32, s32, s32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);
void func_150636A4(Game90840Actor *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063628 CURRENT (481) */
void func_15063628(Game90840Actor *arg0, f32 arg1) {
    Game90840Inner *inner;

    inner = arg0->field_31C;
    func_15081690(arg1, inner->field_13C, inner->field_140, inner->field_144,
                  inner->field_130, inner->field_134, inner->field_138,
                  (u8 *)inner + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
    func_150636A4(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063628 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063628.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150636A4 CURRENT (85) */
void func_150636A4(void *arg0) {
    void *temp_a1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    temp_v0 = *(void **)((u8 *)temp_v0 + 0xB0);
    if (temp_v0 != 0) {
        temp_a1 = *(void **)((u8 *)temp_v0 + 0x31C);
        if (temp_a1 != 0) {
            *(s8 *)((u8 *)temp_a1 + 0x195) = 0x1E;
            *(s8 *)((u8 *)*(void **)((u8 *)temp_v0 + 0x31C) + 0x196) =
                (s8)(((s32)arg0 - (s32)&D_800CC2D0) / 0x32C);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150636A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150636A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150636F0.s")
extern s16 D_800CC2B2;

s16 func_150639BC(Game90840Actor *arg0) {
    D_800CC2B2 = (arg0->field_7A - arg0->field_31C->field_12) - func_15063390(arg0);
    if (D_800CC2B2 >= 0x3E81) {
        D_800CC2B2 = 0x3E80;
    }
    if (D_800CC2B2 < -0x3E80) {
        D_800CC2B2 = -0x3E80;
    }
    return D_800CC2B2;
}

extern s16 D_800CC264;
extern void *D_800CC284;
extern f32 D_800CC2B4;

s32 func_15063A38(Game90840Actor *arg0, s32 arg1, s32 arg2) {
    s16 temp_v1;
    u16 temp_t0;
    u16 temp_t3;

    if (arg1 & arg2) {
        D_800CC2B2 = *(s8 *)((u8 *)D_800CC284 + 2) * 0xC8;
        if (arg0->field_31C->pad14[0x70] != 0) {
            D_800CC2B2 = func_150639BC(arg0);
        }
        D_800CC2B4 = 12.0f;
        D_800CC2B2 = arg0->field_31C->field_12 + ((s32) (D_800CC2B2 * D_800CC264) / 2000);
        temp_v1 = D_800CC2B2;
        if (temp_v1 < -0x2328) {
            temp_t0 = (arg0->field_7A - temp_v1) - 0x2328;
            arg0->field_7A = temp_t0;
            *(u16 *)((u8 *)arg0 + 0x76) = temp_t0;
            D_800CC2B2 = -0x2328;
            temp_v1 = D_800CC2B2;
        }
        if (temp_v1 >= 0x2329) {
            temp_t3 = (arg0->field_7A - temp_v1) + 0x2328;
            arg0->field_7A = temp_t3;
            *(u16 *)((u8 *)arg0 + 0x76) = temp_t3;
            D_800CC2B2 = 0x2328;
            temp_v1 = D_800CC2B2;
        }
        arg0->field_31C->field_12 = temp_v1;
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063B64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063C60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063E84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063FA0.s")
s32 func_1505DADC(void *, u16 *, s32, s32, s32);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150641D8 CURRENT (1340) */
u16 func_150641D8(void *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 selected;
    u16 output;
    u16 current;

    output = 0;
    selected = arg1;
    if (func_150ADA20() & 1) {
        selected = arg2;
    }
    current = *(u16 *)((u8 *)arg0 + 0x84);
    if ((arg1 == current) || (arg2 == current)) {
        selected = arg3;
        if (*(u8 *)((u8 *)arg0 + 0x107) < 0x28) {
            return 0x3E7;
        }
    }
    if (arg3 == current) {
        selected = 0x3E7;
    }
    if (func_1505DADC(arg0, &output, 0, 0xFE, 0x40) != 0xFF) {
        *(u16 *)((u8 *)arg0 + 0x76) = output;
    }
    *(u8 *)((u8 *)arg0 + 0x83) = 0xFF;
    return selected;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150641D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150641D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150642AC.s")

void func_150649A0(u32 arg0, u32 arg1) {
    Game90840Value *first = D_800CC2D0[arg1].field_2D0;
    Game90840Value *second = D_800CC2D0[arg0].field_2D0;

    if ((first != 0) && (second != 0)) {
        f32 limit = first->field_18;

        first->field_8 = second->field_8;
        if (limit <= first->field_8) {
            first->field_8 = limit - 1.0f;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064A14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064B94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15065A5C.s")
