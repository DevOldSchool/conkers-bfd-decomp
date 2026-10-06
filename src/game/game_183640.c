#include "types.h"

/*
 * Reviewed source unit: src/game/game_183640.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15156190
 * - func_151563B8
 * - func_151564F8
 * - func_151568F8
 * - func_15156B54
 * - func_15156D24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game183640Copy3 { s32 words[3]; } Game183640Copy3;
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_100226F0(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156190 CURRENT (933) */
void *func_15156190(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 var_a0;
    u8 *temp_v0;
    void *sp44;
    Game183640Copy3 sp30;

    switch (arg1) {
        case 0:
            var_a0 = 0x2C;
            break;
        case 1:
            var_a0 = 0x53;
            break;
        default:
            var_a0 = 0x2C;
            break;
    }
    temp_v0 = func_15167A68(var_a0, arg4, arg2 + 0x98, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s16 *)((u8 *)temp_v0 + 0x5E) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x64) = (u8) *(u8 *)((u8 *)arg0 + 0x24);
    *(u8 *)((u8 *)temp_v0 + 0x65) = (u8) *(u8 *)((u8 *)arg0 + 0x25);
    *(u8 *)((u8 *)temp_v0 + 0x66) = (u8) *(u8 *)((u8 *)arg0 + 0x26);
    *(s16 *)((u8 *)temp_v0 + 0x60) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x62) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x6E) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x67) = (u8) *(u8 *)((u8 *)arg0 + 0x27);
    *(u8 *)((u8 *)temp_v0 + 0x74) = (u8) *(u8 *)((u8 *)arg0 + 0x20);
    *(u8 *)((u8 *)temp_v0 + 0x75) = (u8) *(u8 *)((u8 *)arg0 + 0x21);
    *(u8 *)((u8 *)temp_v0 + 0x76) = (u8) *(u8 *)((u8 *)arg0 + 0x22);
    *(s16 *)((u8 *)temp_v0 + 0x7E) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x77) = (u8) *(u8 *)((u8 *)arg0 + 0x23);
    *(u8 *)((u8 *)temp_v0 + 0x84) = (u8) *(u8 *)((u8 *)arg0 + 0x20);
    *(u8 *)((u8 *)temp_v0 + 0x85) = (u8) *(u8 *)((u8 *)arg0 + 0x21);
    *(u8 *)((u8 *)temp_v0 + 0x86) = (u8) *(u8 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)temp_v0 + 0x87) = (u8) *(u8 *)((u8 *)arg0 + 0x23);
    sp30 = *(Game183640Copy3 *)arg0;
    *(Game183640Copy3 *)(temp_v0 + 0x28) = sp30;
    *(Game183640Copy3 *)(temp_v0 + 0x10) = sp30;
    *(f32 *)((u8 *)temp_v0 + 0x1C) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * *(f32 *)((u8 *)arg0 + 0xC));
    *(f32 *)((u8 *)temp_v0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * *(f32 *)((u8 *)arg0 + 0x10));
    *(f32 *)((u8 *)temp_v0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * *(f32 *)((u8 *)arg0 + 0x14));
    *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) * *(f32 *)((u8 *)arg0 + 0xC));
    *(f32 *)((u8 *)temp_v0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) * *(f32 *)((u8 *)arg0 + 0x10));
    *(f32 *)((u8 *)temp_v0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) * *(f32 *)((u8 *)arg0 + 0x14));
    *(u8 *)((u8 *)temp_v0 + 0x40) = (u8) *(u8 *)((u8 *)arg0 + 0x28);
    *(s16 *)((u8 *)temp_v0 + 0x42) = (s16) *(s16 *)((u8 *)arg0 + 0x2A);
    *(u16 *)((u8 *)temp_v0 + 0x44) = (u16) *(u16 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)temp_v0 + 0x48) = (f32) *(f32 *)((u8 *)arg0 + 0x30);
    *(u8 *)((u8 *)temp_v0 + 0x4C) = (u8) *(u8 *)((u8 *)arg0 + 0x34);
    *(s16 *)((u8 *)temp_v0 + 0x4E) = (s16) *(s16 *)((u8 *)arg0 + 0x36);
    *(s16 *)((u8 *)temp_v0 + 0x50) = (s16) *(s16 *)((u8 *)arg0 + 0x38);
    sp44 = temp_v0;
    func_100226F0(temp_v0 + 0x88, 0x10);
    return sp44;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156190 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156190.s")
void *func_15156190(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4);

void func_15156388(s32 arg0, u8 arg1, s32 arg2) {
    func_15156190(arg0, arg1, arg2, 0xFF, 0);
}
void func_1516972C(u8 *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151563B8 CURRENT (30) */
void func_151563B8(u8 *arg0) {
    s32 value;
    s16 product;
    s32 expired;

    expired = 0;
    if (arg0[0x40] & 1) {
        *(s16 *)(arg0 + 0x42) = *(s16 *)(arg0 + 0x42) - D_800BE9E4;
        if (*(s16 *)(arg0 + 0x42) < 0) {
            expired = 1;
        }
    }
    if (expired == 0) {
        *(f32 *)(arg0 + 0x10) += *(f32 *)(arg0 + 0x1C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x14) += *(f32 *)(arg0 + 0x20) * D_800BE9A4;
        *(f32 *)(arg0 + 0x18) += *(f32 *)(arg0 + 0x24) * D_800BE9A4;
        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x34) * D_800BE9A4;
        *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg0 + 0x38) * D_800BE9A4;
        *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x3C) * D_800BE9A4;
        if (arg0[0x40] & 8) {
            value = *(s16 *)(arg0 + 0x42);
            if (value < *(s16 *)(arg0 + 0x4E)) {
                product = value * *(s16 *)(arg0 + 0x50);
                if (product < arg0[0x4C]) {
                    arg0[0x4C] = product;
                }
            }
        }
    }
    if (expired != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151563B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151563B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151564F8.s")
typedef struct { f32 x, y, z; } Game183640Vector;
typedef struct { f32 first, second; } Game183640Pair;

typedef struct {
    Game183640Vector position;
    s16 field_0C, field_0E, field_10, field_12, field_14, field_16;
    f32 field_18, field_1C, field_20, field_24;
    u8 field_28, field_29, field_2A, field_2B, field_2C;
    u8 field_2D, field_2E, field_2F, field_30;
    u8 pad31;
    s16 field_32, field_34;
    u16 field_36;
    f32 field_38, field_3C;
    u8 field_40, field_41;
    s16 field_42, field_44;
    u8 field_46, field_47;
    u16 field_48;
    u8 pad4A[2];
    s32 field_4C, field_50;
    s16 field_54;
    u8 pad56[2];
    s32 field_58, field_5C;
    u8 field_60, field_61, field_62, field_63, field_64;
    u8 field_65, field_66, field_67, field_68;
    u8 pad69[3];
    Game183640Pair pair_6C;
    s16 field_74, field_76, field_78;
    u8 pad7A[2];
    f32 field_7C;
    s32 field_80;
    u8 field_84, field_85;
    s8 field_86, field_87;
    u8 field_88, field_89, field_8A, field_8B, field_8C;
} Game183640CombinedRecord;

typedef struct {
    s16 field_00, field_02;
    Game183640Vector position;
    s16 field_10, field_12, field_14, field_16;
    f32 field_18, field_1C, field_20, field_24;
    u8 field_28, field_29, field_2A, field_2B, field_2C;
    u8 field_2D, field_2E, field_2F, field_30;
    u8 pad31;
    s16 field_32, field_34;
    u16 field_36;
    f32 field_38, field_3C;
    u8 field_40, field_41;
    s16 field_42, field_44;
    u8 field_46;
} Game183640BurstDescriptor;

typedef struct {
    s32 field_00, field_04;
    u16 field_08;
    s16 field_0A;
    s32 field_0C, field_10;
    u8 field_14, field_15, field_16, field_17, field_18;
    u8 field_19, field_1A, field_1B, field_1C, field_1D;
    s16 field_1E, field_20, field_22;
    f32 field_24;
    Game183640Pair pair_28;
    Game183640Vector position;
    u8 unused_3C[0xC];
    f32 field_48, field_4C, field_50, field_54;
    s32 field_58;
    u8 unused_5C[4];
    u8 field_60, field_61;
    s8 field_62, field_63;
    u8 unused_64[0xC];
} Game183640SpriteDescriptor;

void func_151539B4(void *, s32);
void *func_15130374(s32, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151568F8 CURRENT (1075) */
void func_151568F8(Game183640CombinedRecord *arg0, s32 arg1) {
    Game183640BurstDescriptor burst;
    Game183640SpriteDescriptor sprite;

    arg1 = (u8)arg1;
    burst.field_00 = arg0->field_0C;
    burst.field_02 = arg0->field_0E;
    burst.position = arg0->position;
    burst.field_10 = arg0->field_10;
    burst.field_14 = arg0->field_14;
    burst.field_12 = arg0->field_12;
    burst.field_16 = arg0->field_16;
    burst.field_18 = arg0->field_18;
    burst.field_1C = arg0->field_1C;
    burst.field_20 = arg0->field_20;
    burst.field_24 = arg0->field_24;
    burst.field_28 = arg0->field_28;
    burst.field_29 = arg0->field_29;
    burst.field_2A = arg0->field_2A;
    burst.field_2B = arg0->field_2B;
    burst.field_2C = arg0->field_2C;
    burst.field_2D = arg0->field_2D;
    burst.field_2E = arg0->field_2E;
    burst.field_2F = arg0->field_2F;
    burst.field_30 = arg0->field_30;
    burst.field_32 = arg0->field_32;
    burst.field_34 = arg0->field_34;
    burst.field_36 = arg0->field_36;
    burst.field_38 = arg0->field_38;
    burst.field_3C = arg0->field_3C;
    burst.field_40 = arg0->field_40;
    burst.field_41 = arg0->field_41;
    burst.field_42 = arg0->field_42;
    burst.field_44 = arg0->field_44;
    burst.field_46 = arg0->field_46;
    func_151539B4(&burst, arg1);
    sprite.field_1D = arg0->field_47;
    sprite.field_08 = arg0->field_48;
    sprite.field_04 = arg0->field_50;
    sprite.field_00 = arg0->field_4C;
    sprite.field_0C = arg0->field_58;
    sprite.field_10 = arg0->field_5C;
    sprite.field_14 = arg0->field_60;
    sprite.field_15 = arg0->field_61;
    sprite.field_16 = arg0->field_62;
    sprite.field_17 = arg0->field_63;
    sprite.field_18 = arg0->field_64;
    sprite.field_19 = arg0->field_65;
    sprite.field_1A = arg0->field_66;
    sprite.position = arg0->position;
    sprite.field_58 = arg0->field_80;
    sprite.field_1B = arg0->field_67;
    sprite.field_1C = arg0->field_68;
    sprite.field_62 = arg0->field_86;
    sprite.field_63 = arg0->field_87;
    sprite.field_1E = arg0->field_74;
    sprite.field_20 = arg0->field_76;
    sprite.field_60 = arg0->field_84;
    sprite.field_61 = arg0->field_85;
    sprite.field_22 = arg0->field_78;
    sprite.field_24 = arg0->field_7C;
    sprite.field_0A = arg0->field_54;
    sprite.pair_28 = arg0->pair_6C;
    sprite.field_48 = 0.0f;
    sprite.field_4C = 0.0f;
    sprite.field_50 = 0.0f;
    sprite.field_54 = 0.0f;
    func_15130374((s32)&sprite, arg0->field_88, 0, (u8)arg1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151568F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151568F8.s")
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
void func_15156D24(void *, u8);

typedef struct Game183640Point {
    f32 x, y, z;
    s32 value;
} Game183640Point;
extern Game183640Point D_800DCA30[3][10];

typedef struct Game183640Light {
    u8 kind;
    s8 mode;
    s16 lifetime;
    u8 state;
} Game183640Light;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156B54 CURRENT (2047) */
void func_15156B54(u8 *arg0) {
    u32 row;
    Game183640Light light;
    s32 position[3];
    Game183640Point *point;
    Game183640Point *group;
    u32 index;
    s16 *timers;

    *(s16 *)(arg0 + 0x2C) -= D_800BE9E4;
    if (*(s16 *)(arg0 + 0x2C) < 0) {
        row = func_150ADA20() % 3U;
        index = func_150ADA20() % 10U;
        group = D_800DCA30[row];
        point = &group[index];
        if (point->x != 0.0f && point->y != 0.0f && point->z != 0.0f) {
            point = &group[index];
            func_15156D24(point, arg0[0xC]);
            light.kind = 3;
            light.mode = -1;
            light.lifetime = func_150ADA20() % 11U + 5;
            light.state = 0;
            position[0] = point->x;
            position[1] = point->y;
            position[2] = point->z;
            func_151602C0((u8 *)&light, position, func_150ADA20() % 156U + 0x64,
                         0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
        }
        timers = (s16 *)(arg0 + 0x28);
        timers[2] = func_150ADA20() % (u32)(timers[1] + 1) + timers[0];
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156B54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156B54.s")
void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);
void func_151568F8(Game183640CombinedRecord *, s32);
extern f32 D_800A6040;
extern f32 D_800A6044;
extern f32 D_800A6048;
extern f32 D_800A604C;
extern f32 D_800A6050;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156D24 CURRENT (2335) */
void func_15156D24(void *arg0, u8 arg1) {
    Game183640CombinedRecord record;
    f32 scale;

    func_10022EC0(&record.position, arg0, 0xC);
    record.field_29 = 0xFF;
    record.field_0C = 10;
    record.field_0E = 30;
    record.field_12 = -63;
    record.field_16 = 128;
    record.field_30 = 9;
    record.field_14 = 255;
    record.field_8A = 255;
    record.field_28 = 255;
    record.field_64 = 255;
    record.field_8B = 255;
    record.field_65 = 255;
    record.field_66 = 255;
    record.field_2A = 255;
    record.field_8C = 255;
    record.field_2B = 255;
    record.field_2C = 255;
    record.field_2D = 255;
    record.field_2E = 255;
    record.field_2F = 255;
    record.field_10 = 0;
    record.field_32 = 5;
    record.field_34 = 10;
    record.field_36 = 0x1601;
    record.field_40 = 100;
    record.field_41 = 155;
    record.field_42 = 4;
    record.field_44 = 63;
    record.field_46 = 0;
    record.field_47 = 43;
    record.field_48 = 0x1A01;
    record.field_4C = 0x200005;
    record.field_50 = 0;
    record.field_20 = D_800A6040;
    record.field_24 = D_800A6040;
    record.field_18 = D_800A6044;
    record.field_1C = D_800A6048;
    record.field_38 = D_800A604C;
    record.field_3C = D_800A6050;
    record.field_54 = (func_150ADA20() % 3U) + 7;
    record.field_58 = 0;
    record.field_5C = 0;
    record.field_60 = 255;
    record.field_61 = 255;
    record.field_62 = 255;
    record.field_63 = 255;
    func_150ADA20();
    record.field_67 = 255;
    record.field_68 = 255;
    scale = (func_150ADA68() * 150.0f) + 196.0f;
    record.field_74 = 4;
    record.field_76 = 63;
    record.field_78 = 22;
    record.pair_6C.first = scale;
    record.field_80 = 0xE01;
    record.pair_6C.second = scale;
    record.field_7C = 1.25f;
    if (func_150ADA20() & 1) {
        record.field_80 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        record.field_80 |= 0x80;
    }
    record.field_84 = 4;
    record.field_85 = 4;
    record.field_86 = -1;
    record.field_87 = -1;
    record.field_88 = 1;
    record.field_89 = 1;
    func_151568F8(&record, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156D24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156D24.s")
void func_15156F94(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}
void func_15169804(s32);

void func_15156FB8(s32 arg0) {
    func_15156F94(arg0);
    func_15169804(arg0);
}
void func_15169824(s32 arg0);

void func_15156FE4(s32 arg0) {
    func_15156F94(arg0);
    func_15169824(arg0);
}
