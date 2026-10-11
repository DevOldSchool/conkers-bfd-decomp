#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1F2730.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C5280
 * - func_151C5588
 * - func_151C577C
 * - func_151C5F44
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { f32 x, y, z; } Game1F2730Vector;

typedef struct Game1F2730PointPair {
    void *points[2];
} Game1F2730PointPair;

void func_15145740(void *, void *, void *, void *, f32);
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
void *func_1503195C(void *, s32, s32);
void func_151C56A4(void *, u8, s32);
void func_151C5588(s32, s32, s16, u8, s32);
s32 func_151C229C(f32 *, f32 *, s32, s32, s32, s32,
                  f32, f32, f32, f32, f32, s32, void *, s32, s32, s32,
                  s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
u32 func_150ADA20();
f32 func_150ADA68(void);
extern s32 D_800AAA90;
extern u8 D_800AAAA8[];
extern f32 D_800AAAB4;
extern f32 D_800AAAB8;
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C5280 CURRENT (441) */
void func_151C5280(void *arg0, u8 arg1, s32 arg2) {
    Game1F2730Vector position;
    Game1F2730Vector endpoint;
    Game1F2730Vector direction;
    Game1F2730Vector side;
    Game1F2730PointPair inputs;
    Game1F2730PointPair outputs;
    f32 random2;
    f32 random1;
    f32 direction_x;
    void *model;
    s32 mode;
    s32 alpha;
    u32 random;

    if (arg0 != 0) {
        func_15145740(arg0, &direction, &side, 0, 0.0f);
        direction.x *= D_800AAAB4;
        direction.y *= D_800AAAB4;
        direction.z *= D_800AAAB4;
        if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
            inputs.points[0] = &D_800AAA90;
            inputs.points[1] = D_800AAAA8;
            outputs.points[0] = &position;
            outputs.points[1] = &endpoint;
            model = func_1503195C(arg0, 0x46, 0);
            if (model == 0) {
                return;
            }
            if (func_1514654C(arg0, (s32)model, 0, inputs.points, outputs.points, 2) == 0) {
                return;
            }
            func_151C56A4(&position, arg1, arg2);
            if (func_150ADA20() & 1) {
                func_151C5588((s32)arg0, (s32)&position, 0x46, arg1, arg2);
            }
        } else {
            position.x = *(f32 *)((u8 *)arg0 + 0x14);
            position.y = *(f32 *)((u8 *)arg0 + 0x18) + 106.0f;
            direction_x = direction.x;
            position.z = *(f32 *)((u8 *)arg0 + 0x1C);
            endpoint.x = direction.x * -82.0f + position.x;
            endpoint.y = direction.y * -82.0f + position.y;
            endpoint.z = direction.z * -82.0f + position.z;
            position.x -= direction_x * -120.0f;
            position.y -= direction.y * -120.0f;
            position.z -= direction.z * -120.0f;
        }
        random1 = func_150ADA68();
        random2 = func_150ADA68();
        random = func_150ADA20();
        if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
            alpha = 0xFF;
        } else {
            alpha = 0x80;
        }
        if (D_800BE616 != 0) {
            mode = -1;
        } else {
            mode = 2;
        }
        func_151C229C((f32 *)&position, 0, (s32)&endpoint, (s32)&direction, 1, 0,
                      300.0f, D_800AAAB8, random1 * 10.0f + 25.0f,
                      random2 * 150.0f + 400.0f, 80.0f, random % 56U + 0xC8,
                      arg0, 1, 1, 0, alpha, 0, 1, 0, 0x1A, 0.0f,
                      0xFF, mode, 0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C5280 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5280.s")
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
u32 func_150ADA20();
f32 func_150ADA68(void);
extern s32 D_800AAA90;
extern s32 D_800AAA9C;
extern f32 D_800AAABC;
extern f32 D_800AAAC0;
extern f32 D_800AAAC4;
extern f32 D_800AAAC8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C5588 CURRENT (12) */
void func_151C5588(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    struct {
        u32 sp44;
        u32 sp48;
        f32 sp50;
        f32 sp54;
    } locals;

    locals.sp54 = ((func_150ADA68() * D_800AAABC) + 604.0f) * D_800AAAC0;
    locals.sp50 = ((func_150ADA68() * 59.0f) + 141.0f) * D_800AAAC4;
    locals.sp44 = func_150ADA20();
    locals.sp48 = func_150ADA20();
    func_15102B38(arg0, 0, (s32)&D_800AAA90, (s32)&D_800AAA9C,
                  &locals.sp50, (locals.sp44 & 3) + 6, 0xFF,
                  (func_150ADA68() * 270.0f) + D_800AAAC8,
                  arg1, 0xFF, 0, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C5588 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5588.s")
typedef struct {
    u8 type;
    s8 neg_one;
    s16 lifetime;
    s8 zero;
} Game1F2730Descriptor;

s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20();

void func_151C56A4(void *arg0, u8 arg1, s32 arg2) {
    Game1F2730Descriptor descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.neg_one = -1;
    descriptor.lifetime = (func_150ADA20() % 3U) + 3;
    descriptor.zero = 0;
    position[0] = (s32)*(f32 *)arg0;
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position,
                  (func_150ADA20(arg0) & 1) + 6,
                  0xFF, 0xE8, 0xAB, 0xFF, 0, 0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C577C.s")
void func_15137F30(void *, void *, void *, void *, f32, void *, void *, void *,
                   void *, f32 *, s16 *, s8 *, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);

void func_151C5E74(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4,
                   u8 *arg5) {
    f32 position[3];
    f32 direction[3];
    f32 vector[3];
    f32 value;
    s16 count;
    s8 alpha;
    f32 scale;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, position, direction,
                  vector, &value, &count, &alpha, &scale);
    func_151D9014(position, vector, 1, value, count, (u8)alpha, scale, 0,
                  1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}

typedef struct {
    s32 field00, field04;
    s16 field08, lifetime;
    s32 field0C, field10;
    u8 colors[8];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, field28, field2C;
    Game1F2730Vector position, velocity, direction;
    f32 field54;
    s32 flags, field5C;
    s8 controls[6];
    u8 pad66[0xA];
} Game1F2730SpawnInit;

typedef struct {
    u8 enabled, field01;
    u8 pad02[2];
    f32 scale;
} Game1F2730SpawnExtra;

void *func_10022EC0(void *, const void *, u32);
extern f32 D_800AAAF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C5F44 CURRENT (1597) */
s32 func_151C5F44(Game1F2730Vector *arg0, Game1F2730Vector *arg1,
                   f32 arg2, f32 arg3, s32 arg4, s32 arg5,
                   f32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    Game1F2730SpawnInit packet;
    f32 value;
    s32 result;
    Game1F2730SpawnExtra extra;
    s32 first_flag;
    s32 has_lifetime;
    s32 second_flag;

    value = arg3;
    packet.field1D = 0x6C;
    packet.field08 = 0x5103;
    packet.field00 = 0x200005;
    packet.field04 = 0;
    packet.field0C = 0;
    packet.field10 = 0;
    packet.field1E = 0x14;
    packet.field20 = 0xC;
    if (func_150ADA20() & 1) {
        first_flag = 0x40;
    } else {
        first_flag = 0;
    }
    has_lifetime = 1;
    if ((s16)arg5 == -1) {
        has_lifetime = 0;
    }
    if (func_150ADA20() & 1) {
        second_flag = 0x80;
    } else {
        second_flag = 0;
    }
    packet.flags = second_flag | has_lifetime | 6 | first_flag | 0xC200 | 0x800000;
    packet.controls[0] = 8;
    packet.controls[1] = 6;
    if ((u8)arg7 != 0) {
        packet.controls[2] = 0x1D;
    } else {
        packet.controls[2] = 0xA;
    }
    packet.field22 = 1;
    packet.controls[3] = -1;
    packet.controls[4] = -1;
    packet.controls[5] = 0;
    extra.enabled = 1;
    extra.field01 = 0;
    packet.colors[0] = 0xE2;
    packet.colors[1] = 0xB2;
    packet.colors[2] = 0x60;
    packet.colors[3] = 0xFF;
    packet.colors[4] = 0x39;
    packet.colors[5] = 0xF;
    packet.colors[6] = 0;
    packet.field1C = 0xFF;
    packet.field24 = 1.0f;
    extra.scale = D_800AAAF0;
    packet.position = *arg0;
    packet.velocity.x = 0.0f;
    packet.velocity.y = 0.0f;
    packet.velocity.z = 0.0f;
    packet.direction = *arg1;
    packet.field54 = arg2;
    packet.colors[7] = arg4;
    if ((s16)arg5 == -1) {
        packet.lifetime = 0x12C;
    } else {
        packet.lifetime = arg5;
    }
    packet.field2C = arg6;
    packet.field28 = arg6;
    result = func_15130280(&packet, 1, arg8, 0x10, (u8)arg9, arg10);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0xA8, &value, 4U);
        func_10022EC0((u8 *)result + 0xB0, &extra, 8U);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C5F44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F2730/func_151C5F44.s")

typedef struct {
    s16 field00;
    s16 field02;
    s32 field04;
    s16 field08;
    s16 field0A;
    s16 field0C;
    s16 field0E;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    u8 field24;
    s8 field25;
    s16 field26;
    s16 field28;
    u8 pad2A[2];
    f32 field2C;
    f32 field30;
    f32 field34;
    s32 field38;
} Game1F2730Packet;

void func_15154684(s16 *, u8, s32);
extern f32 D_800AAAF4;
extern f32 D_800AAAF8;
extern f32 D_800AAAFC;

void func_151C61A0(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    Game1F2730Packet packet;

    packet.field10 = 5.0f;
    packet.field00 = 0xA;
    packet.field14 = 7.0f;
    packet.field02 = 4;
    packet.field04 = arg0;
    packet.field08 = 0;
    packet.field0C = 0xFF;
    packet.field0A = -0x18;
    packet.field0E = 0x19;
    packet.field24 = 0xBE;
    packet.field25 = 0x41;
    packet.field26 = 0xC8;
    packet.field28 = 0x96;
    packet.field18 = D_800AAAF4;
    packet.field1C = D_800AAAF8;
    packet.field20 = D_800AAAFC;
    packet.field2C = 96.0f;
    packet.field30 = 109.0f;
    packet.field34 = 1.0f;
    packet.field38 = arg1;
    func_15154684(&packet.field00, arg2, arg3);
}
