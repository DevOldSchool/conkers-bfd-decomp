#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_68C70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503B840
 * - func_1503B9BC
 * - func_1503CB98
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game68C70Leaf {
    u8 pad0[0x44];
    f32 field_44;
    u8 pad48[4];
    s16 field_4C;
} Game68C70Leaf;

typedef struct Game68C70Nested {
    u8 pad0[0x11C];
    Game68C70Leaf *field_11C;
} Game68C70Nested;

typedef struct Game68C70Actor {
    u8 pad0[0x31C];
    Game68C70Nested *field_31C;
} Game68C70Actor;

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);

void func_1503B7C0(Game68C70Actor *arg0) {
    arg0->field_31C->field_11C = func_10003C40(0x50, 1, 0, 0);
    func_100226F0(arg0->field_31C->field_11C, 0x50);
    arg0->field_31C->field_11C->field_44 = 30.0f;
    arg0->field_31C->field_11C->field_4C = (s16)(func_150ADA20() % 30U);
}

typedef struct Game68C70Status {
    s32 field_0;
    u8 pad4[0x80];
    u16 field_84;
    u8 pad86[0x275];
    u8 field_2FB;
} Game68C70Status;

extern u16 D_8009877C;
extern u16 D_8009877E;
extern u8 D_80098780;
extern u16 D_80098830;
extern u16 D_80098836;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503B840 CURRENT (1785) */
void func_1503B840(Game68C70Status *arg0) {
    u8 *var_a1_2;
    u16 *var_a1;
    u16 temp_t5;
    u16 temp_t7;
    u16 temp_v1;

    var_a1 = &D_80098830;
    if (arg0->field_0 == 1) {
        temp_v1 = arg0->field_84;
loop_2:
        temp_t7 = *var_a1;
        var_a1++;
        if (temp_v1 == temp_t7) {
            arg0->field_2FB |= 2;
            return;
        }
        if (var_a1 >= &D_80098836) {
            if (temp_v1 == D_8009877C) {
                arg0->field_2FB |= 1;
                return;
            }
            var_a1_2 = &D_80098780;
            if (temp_v1 == D_8009877E) {
                arg0->field_2FB |= 1;
                return;
            }
loop_10:
            if (temp_v1 == *(u16 *)(var_a1_2 + 0)) {
                arg0->field_2FB |= 1;
                return;
            }
            if (temp_v1 == *(u16 *)(var_a1_2 + 2)) {
                arg0->field_2FB |= 1;
                return;
            }
            if (temp_v1 == *(u16 *)(var_a1_2 + 4)) {
                arg0->field_2FB |= 1;
                return;
            }
            temp_t5 = *(u16 *)(var_a1_2 + 6);
            var_a1_2 += 8;
            if (temp_v1 == temp_t5) {
                arg0->field_2FB |= 1;
                return;
            }
            if (var_a1_2 != (u8 *)&D_80098830) {
                goto loop_10;
            }
        } else {
            goto loop_2;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503B840 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B840.s")
extern u8 D_800CC5CB;

s32 func_1503B95C(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)&D_800CC5CB + (arg0 * 0x32C));
    if (temp_v0 & 2) {
        *(s8 *)((u8 *)arg1 + 0x4E) = 0;
        return 0;
    }
    if (temp_v0 & 1) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503B9BC.s")
void func_15043EC8(void *, f32, f32, f32, f32, f32, f32);
void func_150440A0(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_150A9B0C(f32 *, f32, f32, f32, f32, f32, f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503CB98 CURRENT (4654) */
void func_1503CB98(s32 arg0, s32 arg1, f32 arg2, u8 *arg3) {
    f32 length;
    f32 normalZSlot;
    f32 normalYSlot;
    f32 normalXSlot;
    f32 x, y, z, nextX, nextY, nextZ;
    u8 *actor;
    f32 inverse;
    f32 scale;
    u8 *matrixBase;
    f32 matrix[16];
    f32 positions[15];
    s32 offset;
    s32 index;
    s32 positionOffset;
    u8 *cursor;
    u8 *end;
    u8 *current;
    u8 *previous;
    f32 *sample;
    f32 savedX;
    f32 normalY;
    f32 normalZ;

    actor = (arg0 * 0x32C) + ((u8 *) D_800CC2D0);
    func_150A9B0C(matrix, *(f32 *)(actor + 0xB8), *(f32 *)(actor + 0x40), *(f32 *)(actor + 0xC4), 1.0f, 1.0f, 1.0f);
    cursor = arg3;
    offset = 0x600;
    index = 0;
    positionOffset = 0;
    end = (u8 *) cursor + 0x30;
    do {
        matrixBase = *(u8 **)(actor + 0x1D4);
        current = matrixBase + offset;
        if (index == 0) {
            previous = (u8 *)matrix;
        } else {
            previous = (matrixBase + offset) - 0x40;
        }
        normalXSlot = *(f32 *)(previous + 0x10);
        normalYSlot = *(f32 *)(previous + 0x14);
        savedX = *(volatile f32 *)&normalXSlot;
        normalZSlot = *(f32 *)(previous + 0x18);
        normalY = *(volatile f32 *)&normalYSlot;
        normalZ = *(volatile f32 *)&normalZSlot;
        length = sqrtf((normalZ * normalZ) + ((savedX * savedX) + (normalY * normalY)));
        if (length != 0.0f) {
            inverse = 1.0f / length;
            normalXSlot = savedX * inverse;
            normalYSlot = normalY * inverse;
            normalZSlot = normalZ * inverse;
        }
        x = *(f32 *)(cursor + 0);
        y = *(f32 *)(cursor + 4);
        z = *(f32 *)(cursor + 8);
        nextX = *(f32 *)(cursor + 0xC);
        nextY = *(f32 *)(cursor + 0x10);
        nextZ = *(f32 *)(cursor + 0x14);
        if (arg1 == 2) {
            sample = (f32 *)((u8 *)positions + positionOffset);
            if (index == 0) {
                previous = matrixBase + 0x600;
                positions[0] = *(f32 *)(previous + 0x30);
                positions[1] = *(f32 *)(previous + 0x34);
                positions[2] = *(f32 *)(previous + 0x38);
                previous = matrixBase + 0x640;
                positions[3] = *(f32 *)(previous + 0x30);
                positions[4] = *(f32 *)(previous + 0x34);
                positions[5] = *(f32 *)(previous + 0x38);
                previous = matrixBase + 0x680;
                positions[6] = *(f32 *)(previous + 0x30);
                positions[7] = *(f32 *)(previous + 0x34);
                positions[8] = *(f32 *)(previous + 0x38);
                previous = matrixBase + 0x6C0;
                positions[9] = *(f32 *)(previous + 0x30);
                positions[10] = *(f32 *)(previous + 0x34);
                positions[11] = *(f32 *)(previous + 0x38);
                savedX = positions[9];
                normalY = positions[10];
                normalZ = positions[11];
                positions[12] = savedX + (savedX - positions[6]);
                positions[13] = normalY + (normalY - positions[7]);
                positions[14] = normalZ + (normalZ - positions[8]);
            }
            x += (sample[0] - x) * arg2;
            y += (sample[1] - y) * arg2;
            z += (sample[2] - z) * arg2;
            nextX += (sample[3] - nextX) * arg2;
            nextY += (sample[4] - nextY) * arg2;
            nextZ += (sample[5] - nextZ) * arg2;
        }
        if ((x == nextX) && (z == nextZ)) {
            x += 1.0f;
        }
        func_150440A0(current, x, y, z, nextX, nextY, nextZ, normalXSlot, normalYSlot, normalZSlot);
        scale = *(f32 *)(actor + 0x14C);
        func_15043EC8(current, scale, *(f32 *)(actor + 0x150), scale, x, y, z);
        cursor = (u8 *) cursor + 0xC;
        offset += 0x40;
        index += 1;
        positionOffset += 0xC;
    } while ((u32)cursor < (u32)end);
    if (arg1 != 2) {
        *(s8 *)(arg3 + 0x4E) = 0x1E;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503CB98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_68C70/func_1503CB98.s")
