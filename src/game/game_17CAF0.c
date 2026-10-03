#include "types.h"

/*
 * Reviewed source unit: src/game/game_17CAF0.c
 * Boundary evidence: docs/evidence/game_raw_emission_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514F808
 * - func_1514F8F8
 * - func_1514FCE8
 * - func_1514FF44
 * - func_15150178
 * - func_15150400
 * - func_1515080C
 * - func_15150D1C
 * - func_15150F90
 * - func_151511FC
 * - func_15151670
 * - func_15151A38
 * - func_15151D6C
 * - func_15152190
 * - func_15152520
 * - func_15152874
 * - func_15152B38
 * - func_15152F70
 * - func_15153298
 * - func_15153634
 * - func_151539B4
 * - func_15153CCC
 * - func_15153F18
 * - func_151541B8
 * - func_15154684
 * - func_15154884
 * - func_15154A88
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15144A74(void *, void *);                  /* extern */
s32 func_15144E80(void *, void *, void *, void *);  /* extern */
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);      /* extern */

void func_1514F640(s32 arg0, u8 *arg1) {

    *(s8 *)((u8 *)arg1 + 0) = 2;
    *(f32 *)((u8 *)arg1 + 0x28) = (f32) *(f32 *)(arg0 + 0x20);
    if ((func_15144E80((void *)(arg0 + 0xC), arg1 + 0x10, arg1 + 0x1C, (arg1 + 4)) != 0) && (func_15144A74((arg1 + 4), (void *)arg0) < 0.0f)) {
        *(f32 *)((u8 *)arg1 + 4) = (f32) -*(f32 *)((u8 *)arg1 + 4);
        *(f32 *)((u8 *)arg1 + 8) = (f32) -*(f32 *)((u8 *)arg1 + 8);
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -*(f32 *)((u8 *)arg1 + 0xC);
    }
}
s32 func_15146078(void *, void *, void *);

s32 func_1514F6E8(void *arg0) {
    f32 *temp_a0;
    f32 *temp_a0_2;
    f32 *temp_a0_3;
    s32 var_v0;

    var_v0 = *(u8 *)arg0;
    temp_a0 = (f32 *)((u8 *)arg0 + 4);
    if (!(var_v0 & 1)) {
        if ((var_v0 = func_15145128(temp_a0, temp_a0, 0, 0)) == 0) {
            return 0;
        }
        *(u8 *)arg0 |= 1;
        *(f32 *)((u8 *)arg0 + 4) *= 1000.0f;
        var_v0 = *(u8 *)arg0;
        *(f32 *)((u8 *)arg0 + 8) *= 1000.0f;
        *(f32 *)((u8 *)arg0 + 0xC) *= 1000.0f;
    }
    if (!(var_v0 & 2)) {
        if ((var_v0 = func_15146078((u8 *)arg0 + 4, (u8 *)arg0 + 0x10,
                          (u8 *)arg0 + 0x1C)) == 0) {
            return 0;
        }
        *(u8 *)arg0 |= 6;
        var_v0 = *(u8 *)arg0;
    }
    temp_a0_2 = (f32 *)((u8 *)arg0 + 0x10);
    if (!(var_v0 & 4)) {
        if ((var_v0 = func_15145128(temp_a0_2, temp_a0_2, 0, 0)) == 0) {
            return 0;
        }
        temp_a0_3 = (f32 *)((u8 *)arg0 + 0x1C);
        if ((var_v0 = func_15145128(temp_a0_3, temp_a0_3, 0, 0)) == 0) {
            return 0;
        }
        *(u8 *)arg0 |= 4;
    }
    return 1;
}
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143874(s16, f32, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514F808 CURRENT (143) */
void func_1514F808(u8 *arg0, f32 arg1, f32 *arg2) {
    f32 second;
    f32 first;
    u32 random;

    random = func_150ADA20();
    func_15143874(
        (s16)(random & 0xFF),
        func_150ADA68() * *(f32 *)(arg0 + 0x28),
        &first,
        &second);
    arg2[0] = ((*(f32 *)(arg0 + 0x10) * first) +
               (*(f32 *)(arg0 + 0x1C) * second) + *(f32 *)(arg0 + 4)) * arg1;
    arg2[1] = ((*(f32 *)(arg0 + 0x14) * first) +
               (*(f32 *)(arg0 + 0x20) * second) + *(f32 *)(arg0 + 8)) * arg1;
    arg2[2] = ((*(f32 *)(arg0 + 0x18) * first) +
               (*(f32 *)(arg0 + 0x24) * second) + *(f32 *)(arg0 + 0xC)) * arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514F808 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F808.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F8F8.s")
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game17CAF0Vec3f;

typedef struct {
    u8 pad_0[0xC];
    f32 field_C;
    u8 field_10;
} Game17CAF0Emitter;

void func_1514F8F8(void *, Game17CAF0Emitter *, Game17CAF0Vec3f *,
                   Game17CAF0Vec3f *, f32, s32, s32);

void func_1514FB98(void *arg0, u8 arg1, s32 arg2) {
    Game17CAF0Vec3f sp34;
    Game17CAF0Vec3f sp28;

    if (func_15146078(arg0, &sp34, &sp28) != 0) {
        func_1514F8F8(&((Game17CAF0Emitter *)arg0)->field_10, arg0, &sp34, &sp28,
                      ((Game17CAF0Emitter *)arg0)->field_C,
                      arg1, arg2);
    }
}
void func_1514FBFC(void *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 out_2C;
        f32 out_30;
        Game17CAF0Vec3f third;
        f32 out_40;
        f32 out_44;
        Game17CAF0Vec3f second;
        f32 out_54;
        f32 out_58;
        Game17CAF0Vec3f first;
    } locals;

    if (func_15144E80((u8 *) arg0 + 0xC, &locals.first, &locals.second, &locals.third)) {
        func_15145128(&locals.first.x, &locals.first.x, &locals.out_58, &locals.out_54);
        func_15145128(&locals.second.x, &locals.second.x, &locals.out_44, &locals.out_40);
        func_15145128(&locals.third.x, &locals.third.x, &locals.out_30, &locals.out_2C);
        if (func_15144A74(&locals.third, arg0) < 0.0f) {
            locals.third.x = -locals.third.x;
            locals.third.y = -locals.third.y;
            locals.third.z = -locals.third.z;
        }
        func_1514F8F8(
            (u8 *) arg0 + 0x24,
            (Game17CAF0Emitter *) &locals.third,
            &locals.first,
            &locals.second,
            *(f32 *) ((u8 *) arg0 + 0x20),
            arg1,
            arg2);
    }
}
typedef struct {
    s16 firstBase;
    s16 firstRange;
    s16 secondBase;
    s16 secondRange;
    s32 countBase;
    s32 countRange;
    Game17CAF0Vec3f position;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    s32 field34;
    s32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    s16 field4C;
    s16 field4E;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    s8 field58;
} Game17CAF0RangeConfig;

void func_151A2A14(s32, s16, s16, f32, f32, f32, s32, f32, f32, f32,
                    f32, s16, s16, s16, s16, s16, s16, s8, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514FCE8 CURRENT (492) */
void func_1514FCE8(s16 *arg0, s32 arg1, s32 arg2) {
    Game17CAF0RangeConfig *config;
    f32 randomX;
    f32 randomY;
    f32 randomZ;
    s32 count;
    u32 randomB;
    u32 randomA;
    u8 color;

    config = (Game17CAF0RangeConfig *)arg0;
    color = (u8)arg1;
    count = (func_150ADA20() % (u32)(config->countRange + 1)) + config->countBase;
    if (count != 0) {
        do {
            randomA = func_150ADA20();
            randomB = func_150ADA20();
            randomX = func_150ADA68();
            randomY = func_150ADA68();
            randomZ = func_150ADA68();
            func_151A2A14((s32)&config->position,
                (s16)((randomA % (u32)(config->firstRange + 1)) + config->firstBase),
                (s16)((randomB % (u32)(config->secondRange + 1)) + config->secondBase),
                (randomX * config->field20) + config->field1C,
                (randomY * config->field28) + config->field24,
                (randomZ * config->field30) + config->field2C,
                (func_150ADA20() % (u32)(config->field38 + 1)) + config->field34,
                config->field3C, config->field40, config->field44, config->field48,
                config->field4C, config->field4E, config->field50,
                config->field52, config->field54, config->field56,
                config->field58, color, arg2);
            count--;
        } while (count != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514FCE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514FCE8.s")
void func_1514F640(s32, u8 *);
void func_1514FF44(void *, s32, s32, u8, s32);

void func_1514FEFC(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x30];

    func_1514F640(arg0, sp24 + 4);
    func_1514FF44(sp24 + 4, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514FF44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150178.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1515080C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150D1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150F90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151511FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151670.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151A38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151D6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152190.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152874.s")
typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Game17CAF0Color;

u32 func_150ADA20(); /* extern */
extern u8 D_800A5FE0[];

void func_15152ABC(Game17CAF0Color *arg0) {
    struct {
        u8 *color;
        u8 *unused;
    } locals;

    locals.color = (((func_150ADA20() % 5U) & 0xFF) * 3) + D_800A5FE0;
    arg0->alpha = (func_150ADA20() % 101U) + 0x9B;
    arg0->red = locals.color[0];
    arg0->green = locals.color[1];
    arg0->blue = locals.color[2];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152B38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152F70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151539B4.s")
void func_1514F640(s32, u8 *);
void func_15153CCC(void *, s32, s32, u8, s32);

void func_15153C84(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x30];

    func_1514F640(arg0, sp24 + 4);
    func_15153CCC(sp24 + 4, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153CCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153F18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151541B8.s")
extern f32 D_800BE9A4;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

s32 func_1515452C(u8 *arg0) {
    f32 temp_fv1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x178) * sqrtf(*(f32 *)((u8 *)arg0 + 0x170));
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fv1;
    if (!(*(u8 *)((u8 *)arg0 + 0x184) & 1)) {
        *(f32 *)((u8 *)arg0 + 0x1C) = temp_fv1;
    }
    {
        f32 temp_fv0 = *(f32 *)temp_v0;
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) (*(f32 *)((u8 *)temp_v0 + 0xC) - (*(f32 *)((u8 *)temp_v0 + 0x10) * temp_fv0 * temp_fv0));
    *(f32 *)temp_v0 += D_800BE9A4;
    if (*(f32 *)((u8 *)temp_v0 + 4) < *(f32 *)temp_v0) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
    }
}
void func_15143794(s16, s16, f32, void *);
void func_151C5F44(s32, f32 *, f32, f32, s32, s32, f32, s32, s32, s32, s32);

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
} Game17CAF0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15154684 CURRENT (2250) */
void func_15154684(s16 *arg0, u8 arg1, s32 arg2) {
    s32 mode;
    f32 direction[3];
    f32 size_random;
    f32 speed_random;
    s32 count;
    u32 random_a;
    u32 random_b;
    Game17CAF0Packet *packet;

    packet = (Game17CAF0Packet *)arg0;
    count = (func_150ADA20() % (u32)(packet->field02 + 1)) + packet->field00;
    if (count > 0) {
        do {
            random_a = func_150ADA20();
            random_b = func_150ADA20();
            func_15143794((s16)(random_a & 0xFF),
                (s16)((random_b % (u32)(packet->field0E + 1)) + packet->field0A),
                (func_150ADA68() * packet->field14) + packet->field10, direction);
            size_random = func_150ADA68();
            random_a = func_150ADA20();
            random_b = func_150ADA20();
            speed_random = func_150ADA68();
            mode = func_150ADA68() < packet->field34 ? 1 : 0;
            func_151C5F44(packet->field04, direction,
                (size_random * packet->field1C) + packet->field18,
                packet->field20,
                (random_a % (u32)((u8)packet->field25 + 1)) + packet->field24,
                (random_b % (u32)(packet->field28 + 1)) + packet->field26,
                speed_random * packet->field30 + packet->field2C, mode, packet->field38, arg1, arg2);
            count--;
        } while (count > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15154684 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154684.s")
typedef struct Game154884Descriptor {
    f32 field00, field04, field08, field0C;
    Game17CAF0Vec3f angles;
    Game17CAF0Vec3f scale;
    Game17CAF0Vec3f position;
    Game17CAF0Vec3f velocity;
    f32 field40, field44, field48, field4C;
    s32 field50;
    s16 field54, field56;
    u8 field58;
    s32 field5C;
    u8 field60, field61, field62, field63;
    u8 field64, field65, field66, field67;
    u8 field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70;
    s16 field72, field74;
    u8 unknown76[6];
} Game154884Descriptor;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A601C, D_800A6020, D_800A6024, D_800A6028, D_800A602C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15154884 CURRENT (200) */
void *func_15154884(Game17CAF0Vec3f *arg0, f32 arg1, f32 arg2,
                    f32 arg3, s32 arg4, s32 arg5) {
    u8 *result;
    Game154884Descriptor descriptor;
    f32 payload[5];
    f32 random;

    if (arg1 <= 0.0f) {
        return 0;
    }
    payload[0] = arg1;
    payload[1] = arg2;
    payload[3] = 0.0f;
    descriptor.field08 = 0.0f;
    descriptor.field0C = 0.0f;
    descriptor.field00 = 1.0f;
    descriptor.field04 = 1.0f;
    payload[2] = arg3;
    payload[4] = D_800A601C / arg1;
    descriptor.angles.x = func_150ADA68() * 360.0f;
    descriptor.angles.y = func_150ADA68() * 360.0f;
    random = func_150ADA68();
    descriptor.scale.x = 1.0f;
    descriptor.scale.y = 1.0f;
    descriptor.scale.z = 1.0f;
    descriptor.angles.z = random * 360.0f;
    descriptor.position = *arg0;
    descriptor.velocity.x = 0.0f;
    descriptor.velocity.y = 0.0f;
    descriptor.velocity.z = 0.0f;
    random = func_150ADA68();
    descriptor.field44 = 0.0f;
    descriptor.field40 = (random * D_800A6020) + D_800A6024;
    descriptor.field48 = func_150ADA68() * D_800A6028 + D_800A602C;
    descriptor.field4C = 0.0f;
    descriptor.field50 = 0x140;
    descriptor.field56 = 0x55;
    descriptor.field58 = 0;
    descriptor.field5C = 0;
    descriptor.field60 = 0xFF;
    descriptor.field61 = 0x12;
    descriptor.field62 = 0;
    descriptor.field63 = 0;
    descriptor.field64 = 0;
    descriptor.field65 = 0;
    descriptor.field66 = 0;
    descriptor.field67 = 0;
    descriptor.field68 = 2;
    descriptor.field6A = 0;
    descriptor.field6C = 0;
    descriptor.field70 = 0;
    descriptor.field72 = 1;
    descriptor.field74 = 0xFF;
    descriptor.field54 = 0x12C;
    result = func_15132A4C(&descriptor, 0, 0, 0x14, (u8)arg4, arg5);
    if (result != 0) {
        func_10022EC0(result + 0x170, payload, 0x14);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15154884 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154884.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15154A88 CURRENT (1810) */
s32 func_15154A88(u8 *arg0) {
    f32 temp_fv0;
    f32 var_ft4;
    s32 temp_t8;
    u8 *temp_v1;

    temp_fv0 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x17C));
    temp_v1 = (void *)(arg0 + 0x170);
    {
        f32 temp_fv1 = *(f32 *)((u8 *)temp_v1 + 4) * temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x1C) = temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fv1;
    temp_t8 = (u32) *(f32 *)((u8 *)temp_v1 + 8) & 0xFF;
    var_ft4 = (f32) temp_t8;
    if (temp_t8 < 0) {
        var_ft4 += 4294967296.0f;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) (var_ft4 * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x170) <= 0.0f) {
        return 0;
    }
    *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC) + (*(f32 *)((u8 *)temp_v1 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15154A88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154A88.s")
