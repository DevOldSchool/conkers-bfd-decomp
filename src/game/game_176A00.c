#include "types.h"

/*
 * Reviewed source unit: src/game/game_176A00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149550
 * - func_15149838
 * - func_15149A94
 * - func_15149D18
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149838.s")
void func_1513F680(void *, s32, s32, s32, u8);
extern f32 D_800A578C;
extern f32 D_800A5790;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149A94 CURRENT (475) */
s32 func_15149A94(void *arg0) {
    u8 *actor = arg0;
    s32 flags = actor[0x74];
    s32 ready = 1;
    u8 *target;
    f32 current;
    f32 target_value;
    f32 factor;

    if (!(flags & 2)) {
        target = actor + 0x110;
        target_value = *(volatile f32 *)(target + 8);
        current = *(volatile f32 *)(actor + 0x2C);
        factor = *(volatile f32 *)(target + 0x44);
        *(volatile f32 *)(actor + 0x2C) = current +
            ((target_value - current) * factor);
        if ((*(volatile f32 *)(target + 8) * D_800A578C) < *(volatile f32 *)(actor + 0x2C)) {
            flags = actor[0x74] | 2;
            actor[0x74] = (u8)flags;
            flags &= 0xFF;
        } else {
            ready = 0;
            flags = actor[0x74];
        }
    }
    target = actor + 0x110;
    if (!(flags & 8)) {
        current = *(volatile f32 *)(actor + 0x30);
        target_value = *(volatile f32 *)(target + 0x20);
        factor = *(volatile f32 *)(target + 0x44);
        *(volatile f32 *)(actor + 0x30) = current +
            ((target_value - current) * factor);
        if ((*(volatile f32 *)(target + 0x20) * D_800A5790) < *(volatile f32 *)(actor + 0x30)) {
            actor[0x74] |= 8;
        } else {
            ready = 0;
        }
    }
    if (ready != 0) {
        func_1513F680(arg0, actor[0x70], 0xD, actor[0x72], actor[0x73]);
    }
    if (*(s16 *)(actor + 0x1C) < 5) {
        func_1513F680(arg0, actor[0x70], actor[0x158], actor[0x72], actor[0x73]);
        *(s16 *)(actor + 0x1C) = 0x64;
        *(s32 *)(actor + 0x58) &= ~1;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149A94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149A94.s")
s32 func_15149BF4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if ((*(volatile f32 *)((u8 *)arg0 + 0x2C) < 2.0f) || (*(volatile f32 *)((u8 *)arg0 + 0x30) < 2.0f)) {
        return 0;
    }
    return 1;
}
extern f32 D_800BE9A4;

s32 func_15149C58(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x50) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    if (*(f32 *)((u8 *)arg0 + 0x15C) < *(f32 *)((u8 *)arg0 + 0x38)) {
        return 0;
    }
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 4.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 4.0f)) {
        return 0;
    }
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149D18 CURRENT (208) */
void *func_15149D18(void *arg0, s16 arg1) {
    void *segment;
    void *result;
    u8 copy;
    u8 *object = arg0;
    f32 offset_x;
    f32 offset_z;

    func_151D5D60(object + 0x100, arg1, 0x40, &segment, &copy);
    result = segment;
    if (segment != 0) {
        if (copy != 0) {
            func_10022EC0(*(u8 **)(object + 0x100 + (arg1 * 4)), object + 0xC0, 0x40);
            func_10022EC0(*(u8 **)(object + 0x100 + (arg1 * 4)) + 0x40, object + 0xC0, 0x40);
        }
    } else {
        return 0;
    }

    offset_z = D_800DD1D8[arg1] * *(f32 *)(object + 0x2C);
    offset_x = D_800DD1E8[arg1] * *(f32 *)(object + 0x2C);
    *(s16 *)segment = *(s16 *)((u8 *)segment + 0x30) =
        (s32)(*(f32 *)(object + 0x34) + offset_x);
    *(s16 *)((u8 *)segment + 2) = *(s16 *)((u8 *)segment + 0x12) =
        (s32)*(f32 *)(object + 0x38);
    *(s16 *)((u8 *)segment + 4) = *(s16 *)((u8 *)segment + 0x34) =
        (s32)(*(f32 *)(object + 0x3C) - offset_z);
    *(s16 *)((u8 *)segment + 0x10) = *(s16 *)((u8 *)segment + 0x20) =
        (s32)(*(f32 *)(object + 0x34) - offset_x);
    *(s16 *)((u8 *)segment + 0x22) = *(s16 *)((u8 *)segment + 0x32) =
        (s32)(*(f32 *)(object + 0x30) + *(f32 *)(object + 0x38));
    *(s16 *)((u8 *)segment + 0x14) = *(s16 *)((u8 *)segment + 0x24) =
        (s32)(*(f32 *)(object + 0x3C) + offset_z);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149D18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149D18.s")
typedef struct {
    s32 values[3];
} Game176A00Position;

typedef struct {
    Game176A00Position position;
    u8 pad0C[0xA];
    s16 field16;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
    s16 field20;
    s16 field22;
    s16 field24;
    s16 field26;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    s8 field2F;
    s8 field30;
    s8 field31;
} Game176A00Effect;

void func_151429E0(u8, u8 *, u8 *, u8 *);
u32 func_150ADA20(void);
void func_1518CA80(void *, s32);

s32 func_15149EC4(void *arg0) {
    u8 effect_storage[sizeof(Game176A00Effect)];
    Game176A00Effect *effect = (Game176A00Effect *)effect_storage;

    effect->position = *(Game176A00Position *)((u8 *)arg0 + 0x34);
    effect->field16 = 0;
    effect->field18 = 0;
    effect->field1C = (func_150ADA20() % 6U) + 8;
    effect->field1A = effect->field1C;
    effect->field1E = 0;
    effect->field20 = 0;
    effect->field22 = (func_150ADA20() % 201U) + 0x64;
    effect->field24 = (func_150ADA20() % 5U) + 3;
    effect->field26 = 0x258;
    func_151429E0(3, &effect->field28, &effect->field29, &effect->field2A);
    func_151429E0(4, &effect->field2B, &effect->field2C, &effect->field2D);
    effect->field2E = 0xFF;
    effect->field2F = (func_150ADA20() % 65U) + 0x5C;
    effect->field30 = (func_150ADA20() % 3U) + 1;
    effect->field31 = 0;
    func_1518CA80(effect, 1);
    return 0;
}
