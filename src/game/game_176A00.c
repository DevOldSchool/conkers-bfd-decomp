#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_176A00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149550
 * - func_15149838
 * - func_15149A94
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149550.s")
typedef struct Game176A00Motion {
    f32 maxA, minA, targetA;
    volatile s16 timerA;
    s16 rangeA;
    f32 factorA;
    f32 maxB, minB, alternateB, targetB;
    volatile s16 timerB;
    s16 rangeB;
    f32 factorB;
    s32 maxC, minC, targetC;
    volatile s16 timerC;
    s16 rangeC;
    f32 factorC;
    u8 pad40[8];
    u8 effect;
} Game176A00Motion;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149838 CURRENT (660) */
s32 func_15149838(u8 *arg0) {
    Game176A00Motion *motion;
    u32 random;
    f32 fraction;
    f32 minimum;
    f32 current;
    s32 minimumC;
    s32 currentC;

    *(volatile s16 *)(arg0 + 0x11C) -= D_800BE9E4;
    if (*(volatile s16 *)(arg0 + 0x11C) < 0) {
        random = func_150ADA20();
        motion = (Game176A00Motion *)(arg0 + 0x110);
        motion->timerA = random % (u32)motion->rangeA;
        fraction = func_150ADA68();
        minimum = motion->minA;
        motion->targetA = fraction * (motion->maxA - minimum) + minimum;
    }
    motion = (Game176A00Motion *)(arg0 + 0x110);
    current = *(f32 *)(arg0 + 0x2C);
    *(f32 *)(arg0 + 0x2C) = current + (motion->targetA - current) * motion->factorA;
    motion->timerB -= D_800BE9E4;
    if (motion->timerB < 0) {
        motion->timerB = func_150ADA20() % (u32)motion->rangeB;
        if (func_150ADA20() & 3) {
            fraction = func_150ADA68();
            minimum = motion->minB;
            motion->targetB = fraction * (motion->maxB - minimum) + minimum;
        } else {
            fraction = func_150ADA68();
            minimum = motion->maxB;
            motion->targetB = fraction * (motion->alternateB - minimum) + minimum;
        }
    }
    current = *(f32 *)(arg0 + 0x30);
    *(f32 *)(arg0 + 0x30) = current + (motion->targetB - current) * motion->factorB;
    motion->timerC -= D_800BE9E4;
    if (motion->timerC < 0) {
        motion->timerC = func_150ADA20() % (u32)motion->rangeC;
        random = func_150ADA20();
        minimumC = motion->minC;
        motion->targetC = random % (u32)(motion->maxC - minimumC + 1) + minimumC;
    }
    currentC = *(s32 *)(arg0 + 0x24);
    *(s32 *)(arg0 + 0x24) = currentC + (s32)(((f32)motion->targetC - (f32)currentC) * motion->factorC);
    if (*(s16 *)(arg0 + 0x1C) < 5) {
        func_1513F680(arg0, arg0[0x70], motion->effect, arg0[0x72], arg0[0x73]);
        *(s16 *)(arg0 + 0x1C) = 0x12C;
        *(s32 *)(arg0 + 0x58) &= ~1;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149838 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149838.s")
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
    *(f32 *)((u8 *)arg0 + 0x2C) -= *(f32 *)((u8 *)arg0 + 0x2C) * *(f32 *)((u8 *)arg0 + 0x150);
    *(f32 *)((u8 *)arg0 + 0x30) -= *(f32 *)((u8 *)arg0 + 0x30) * *(f32 *)((u8 *)arg0 + 0x150);
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 2.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 2.0f)) {
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

typedef struct Game176A00QuadVertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game176A00QuadVertex;

typedef struct Game176A00QuadOwner {
    u8 pad0[0x2C];
    f32 scale;
    f32 height;
    f32 x, y, z;
    u8 pad40[0x80];
    u8 templateData[0x40];
    u8 *buffers[1];
} Game176A00QuadOwner;

void *func_15149D18(Game176A00QuadOwner *arg0, s16 arg1) {
    Game176A00QuadVertex *vertices;
    void *result;
    f32 offsetZ;
    f32 offsetX;
    u8 fresh;

    func_151D5D60(arg0->buffers, arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[arg1], arg0->templateData, 0x40);
            func_10022EC0(arg0->buffers[arg1] + 0x40, arg0->templateData, 0x40);
        }
    } else {
        return 0;
    }
    offsetZ = D_800DD1D8[arg1] * arg0->scale;
    offsetX = D_800DD1E8[arg1] * arg0->scale;
    vertices[0].x = vertices[3].x = (s32)(arg0->x + offsetX);
    vertices[0].y = vertices[1].y = (s32)arg0->y;
    vertices[0].z = vertices[3].z = (s32)(arg0->z - offsetZ);
    vertices[1].x = vertices[2].x = (s32)(arg0->x - offsetX);
    vertices[2].y = vertices[3].y = (s32)(arg0->y + arg0->height);
    vertices[1].z = vertices[2].z = (s32)(arg0->z + offsetZ);
    return result;
}
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
