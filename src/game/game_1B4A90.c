#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B4A90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151875E0
 * - func_15187978
 * - func_15187A98
 * - func_15187D6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1B4A90Child {
    u32 fixed[2][16];
    f32 rotationX, rotationY, rotationZ, speed;
    f32 translation;
    s16 elapsed, duration;
    u8 mode;
    u8 pad99[7];
} Game1B4A90Child;
typedef struct Game1B4A90Owner {
    u8 pad0[0x10];
    u32 fixed[2][16];
    f32 x, y, z;
    f32 scaleYZ, scaleX;
    Game1B4A90Child *children;
    s16 timer, duration;
} Game1B4A90Owner;

void *func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151875E0 CURRENT (1980) */
void func_151875E0(f32 arg0, f32 arg1, f32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, f32 arg6, f32 arg7) {
    Game1B4A90Owner *owner;
    s32 offset;
    s32 angle;

    owner = func_15167A68(6, 0, 0xB0, 1, 0xFF, 1);
    if (owner != NULL) {
        owner->children = func_10003C40(0x780, 1, 2, 1);
        if (owner->children == NULL) {
            func_1516972C(owner);
            return;
        }
        owner->x = arg0;
        owner->y = arg1;
        owner->z = arg2;
        owner->timer = 0;
        owner->duration = arg4;
        owner->scaleYZ = arg6;
        owner->scaleX = arg7;
        arg0 = 0.0f;
        offset = 0;
        angle = 0;
        do {
            if (angle < 360) {
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationX = 7U - (func_150ADA20() & 15U);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationY = arg0;
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationZ = (func_150ADA20() & 63U) + (angle - 30);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->mode = 0;
            } else if (angle < 720) {
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationX = arg0;
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationY = (func_150ADA20() & 63U) + (angle - 570);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationZ = 7U - (func_150ADA20() & 15U);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->mode = 0;
            } else {
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationX = (func_150ADA20() & 63U) + (angle - 30);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationY = 97U - (func_150ADA20() & 15U);
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->rotationZ = arg0;
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->mode = 1;
            }
            if (arg3 >= 4) {
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->speed = func_150ADA20() % (u32)(arg3 >> 2) + arg3;
            } else {
                ((Game1B4A90Child *)((u8 *)owner->children + offset))->speed = (f32)arg3;
            }
            ((Game1B4A90Child *)((u8 *)owner->children + offset))->translation = func_150ADA20() & 15U;
            ((Game1B4A90Child *)((u8 *)owner->children + offset))->elapsed = 0;
            ((Game1B4A90Child *)((u8 *)owner->children + offset))->duration = arg4 - (func_150ADA20() & arg5);
            angle += 90;
            offset += 0xA0;
        } while (angle != 1080);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151875E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_151875E0.s")

void func_10004074(s32);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187978 CURRENT (1907) */
void func_15187978(s32 arg0) {
    f32 temp_fv0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a0;
    s16 var_v1;
    s32 var_a2;
    s32 var_a1;
    s32 temp_v0_3;
    s32 var_v0;

    var_a2 = arg0;
    temp_v0 = *(s16 *)(var_a2 + 0xA8);
    if (temp_v0 < 0) {
        func_10004074(*(s32 *)(var_a2 + 0xA4));
        func_1516972C((u8 *)var_a2);
        return;
    }
    *(s16 *)(var_a2 + 0xA8) = temp_v0 + D_800BE9E4;
    temp_v0_2 = *(s16 *)(var_a2 + 0xA8);
    if (*(s16 *)(var_a2 + 0xAA) < temp_v0_2) {
        *(s16 *)(var_a2 + 0xA8) = -0xA;
        return;
    }
    var_a1 = 0;
    if (temp_v0_2 >= 0) {
        do {
            temp_v0_3 = *(s32 *)(var_a2 + 0xA4) + var_a1;
            temp_v1 = *(s16 *)(temp_v0_3 + 0x94);
            if (temp_v1 < *(s16 *)(temp_v0_3 + 0x96)) {
                *(s16 *)(temp_v0_3 + 0x94) = temp_v1 + D_800BE9E4;
                var_v0 = *(s32 *)(var_a2 + 0xA4) + var_a1;
                var_a0 = *(s16 *)(var_v0 + 0x96);
                var_v1 = *(s16 *)(var_v0 + 0x94);
                if (var_a0 < var_v1) {
                    *(s16 *)(var_v0 + 0x94) = var_a0;
                    var_v0 = *(s32 *)(var_a2 + 0xA4) + var_a1;
                    var_v1 = *(s16 *)(var_v0 + 0x94);
                    var_a0 = *(s16 *)(var_v0 + 0x96);
                }
                temp_fv0 = *(f32 *)(var_v0 + 0x8C);
                *(f32 *)(var_v0 + 0x90) +=
                    temp_fv0 - (((temp_fv0 / 3.0f) * (f32)var_v1) /
                                (f32)var_a0);
            }
            var_a1 += 0xA0;
        } while (var_a1 != 0x780);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15187978 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187978.s")
typedef struct Game1B4A90Command { u32 opcode, value; } Game1B4A90Command;
void func_150A7790(void *, s32);
void func_150A7A48(void *, void *, void *);
void func_150A7DA0(void *, f32, f32, f32);
void func_150A8050(void *, f32, f32, f32);
void func_15187D6C(void *, f32, f32, f32);
void func_151EFD00(f32 *, void *);
extern u32 D_8008D538[];
extern u8 D_800BE9C0;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187A98 CURRENT (55) */
Game1B4A90Command *func_15187A98(Game1B4A90Command *cursor, Game1B4A90Owner *arg1, s32 arg2) {
    s32 index, offset;
    f32 matrix[4][4];
    f32 rotation[4][4];

    if (arg1->timer >= 0) {
        func_150A7DA0(matrix, arg1->x, arg1->y, arg1->z);
        func_151EFD00(&matrix[0][0], arg1->fixed[D_800BE9C0]);
        for (index = 0, offset = 0; index != 12; index++, offset += 0xA0) {
            { Game1B4A90Command *command = cursor++; command->opcode = 0xDA380003; command->value = (u32)arg1->fixed[D_800BE9C0]; }
            func_150A7DA0(matrix,
                ((Game1B4A90Child *)((u8 *)arg1->children + offset))->translation, 0.0f, 0.0f);
            matrix[0][0] *= arg1->scaleX;
            matrix[1][1] *= arg1->scaleYZ;
            matrix[2][2] *= arg1->scaleYZ;
            {
                Game1B4A90Child *child = (Game1B4A90Child *)((u8 *)arg1->children + offset);
                if (child->mode == 0) {
                    func_150A8050(rotation, child->rotationX, child->rotationY, child->rotationZ);
                } else {
                    func_15187D6C(rotation, child->rotationX, child->rotationY, child->rotationZ);
                }
            }
            func_150A7A48(matrix, rotation, matrix);
            func_150A7790(matrix, (s32)arg1->children[index].fixed[D_800BE9C0]);
            {
                Game1B4A90Child *child = (Game1B4A90Child *)((u8 *)arg1->children + offset);
                s32 duration = child->duration;
                s32 alpha = (duration - child->elapsed) * 255 / duration;
                { Game1B4A90Command *command = cursor++; command->opcode = _SHIFTL(0xFA, 24, 8) | _SHIFTL(1, 8, 8) | _SHIFTL(0, 0, 8); command->value = _SHIFTL(255, 24, 8) | _SHIFTL(255, 16, 8) | _SHIFTL(255, 8, 8) | _SHIFTL(alpha, 0, 8); }
            }
            { Game1B4A90Command *command = cursor++; command->opcode = 0xDA380001; command->value = (u32)arg1->children[index].fixed[D_800BE9C0]; }
            { Game1B4A90Command *command = cursor++; command->opcode = 0x01004008; command->value = (u32)D_8008D538; }
            { Game1B4A90Command *command = cursor++; command->opcode = 0x05000204; command->value = 0; }
            { Game1B4A90Command *command = cursor++; command->opcode = 0x05000206; command->value = 0; }
            { Game1B4A90Command *command = cursor++; command->opcode = 0x05000406; command->value = 0; }
        }
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15187A98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187A98.s")

f32 func_15047D60(f32);
f32 func_15047C00(f32);
void func_151EFE00(void *);
extern f32 D_8008D578;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187D6C CURRENT (2074) */
void func_15187D6C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp44;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fa0 = arg1 * D_8008D578;
    arg1 = temp_fa0;
    arg2 *= D_8008D578;
    arg3 *= D_8008D578;
    sp44 = func_15047D60(temp_fa0);
    temp_fs0 = func_15047C00(arg1);
    temp_fs1 = func_15047D60(arg2);
    sp34 = func_15047C00(arg2);
    sp3C = func_15047D60(arg3);
    sp30 = func_15047C00(arg3);
    func_151EFE00(arg0);
    temp_fv0 = sp44 * temp_fs1;
    *(f32 *)((u8 *)arg0 + 0x18) = sp44;
    *(f32 *)((u8 *)arg0 + 0) = (sp34 * sp30) - (temp_fv0 * sp3C);
    *(f32 *)((u8 *)arg0 + 4) = (sp34 * sp3C) + (temp_fv0 * sp30);
    *(f32 *)((u8 *)arg0 + 8) = -temp_fs1 * temp_fs0;
    temp_fv0_2 = sp44 * sp34;
    *(f32 *)((u8 *)arg0 + 0x10) = -temp_fs0 * sp3C;
    *(f32 *)((u8 *)arg0 + 0x14) = temp_fs0 * sp30;
    *(f32 *)((u8 *)arg0 + 0x20) = (temp_fs1 * sp30) + (temp_fv0_2 * sp3C);
    *(f32 *)((u8 *)arg0 + 0x28) = temp_fs0 * sp34;
    *(f32 *)((u8 *)arg0 + 0x24) = (temp_fs1 * sp3C) - (temp_fv0_2 * sp30);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15187D6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187D6C.s")
