#include "types.h"

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_151875E0.s")
void func_10004074(s32);
void func_1516972C(u8 *);
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
    s16 timer;
} Game1B4A90Owner;
void func_150A7790(void *, s32);
void func_150A7A48(void *, void *, void *);
void func_150A7DA0(void *, f32, f32, f32);
void func_150A8050(void *, f32, f32, f32);
void func_15187D6C(void *, f32, f32, f32);
void func_151EFD00(f32 *, void *);
extern u32 D_8008D538[];
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187A98 CURRENT (2728) */
void *func_15187A98(register Game1B4A90Command *cursor, Game1B4A90Owner *arg1, s32 arg2) {
    f32 matrix[4][4];
    f32 rotation[4][4];
    s32 index, offset;

    if (arg1->timer >= 0) {
        func_150A7DA0(matrix, arg1->x, arg1->y, arg1->z);
        func_151EFD00(&matrix[0][0], arg1->fixed[D_800BE9C0]);
        index = 0;
        offset = 0;
        do {
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0xDA380003;
                command->value = (u32)arg1->fixed[D_800BE9C0];
                cursor++;
            }
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
                register s32 duration = child->duration;
                Game1B4A90Command *command = cursor;
                command->value = (((duration - child->elapsed) * 255 / duration) & 255) | 0xFFFFFF00;
                command->opcode = 0xFA000100;
                cursor++;
            }
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0xDA380001;
                command->value = (u32)arg1->children[index].fixed[D_800BE9C0];
                cursor++;
            }
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0x01004008;
                command->value = (u32)D_8008D538;
                cursor++;
            }
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0x05000204;
                command->value = 0;
                cursor++;
            }
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0x05000206;
                command->value = 0;
                cursor++;
            }
            {
                Game1B4A90Command *command = cursor;
                command->opcode = 0x05000406;
                command->value = 0;
                cursor++;
            }
            index++;
            offset += 0xA0;
        } while (index != 12);
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
