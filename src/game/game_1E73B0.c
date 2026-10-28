#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1E73B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B9F00
 * - func_151BA084
 * - func_151BA468
 * - func_151BA518
 * - func_151BB0E0
 * - func_151BB61C
 * - func_151BC104
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15160CDC(
    s32 arg0,
    s32 arg1,
    void *arg2,
    void *arg3,
    f32 arg4,
    s32 arg5,
    s32 arg6,
    s32 arg7,
    s32 arg8,
    s32 arg9,
    s32 arg10,
    s32 arg11,
    s32 arg12,
    s32 arg13,
    s32 arg14,
    s32 arg15
);
extern u8 D_800AA760;
extern u8 D_800AA76C;
extern f32 D_800AA82C;

typedef struct Game1E73B0Request {
    void *source;
    u8 code;
    u8 pad05[3];
    s8 kind;
    s8 negative;
    s8 count;
    u8 pad0B;
    s16 duration;
    u8 pad0E[2];
    s32 one;
    s32 mask;
    s32 flags;
    s32 another_one;
    s32 value36;
    s32 value80;
    s32 value20;
    u8 zero1;
    u8 zero2;
    u8 pad2E[0xA];
    s32 value9;
    s32 value1AD;
    s8 extra;
    u8 variant;
    u8 pad42[2];
    u8 pad44[4];
} Game1E73B0Request;

extern s8 D_8008FD90;
extern s8 D_800E0BCE[];
extern u8 D_800CC2D0[];
extern void *func_1513B5E0(s8 *, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9F00 CURRENT (1427) */
void *func_151B9F00(void *arg0, u8 arg1, s32 arg2) {
    Game1E73B0Request request;
    s32 actor_index;
    void *result;

    if (arg0 == 0) {
        return 0;
    }
    request.source = arg0;
    request.kind = 2;
    request.negative = -1;
    request.count = 3;
    request.duration = 0x12C;
    request.value9 = 9;
    request.value1AD = 0x1AD;
    request.variant = 0xFF;
    request.code = *(u8 *)((u8 *)arg0 + 0x3B);
    actor_index = ((u8 *)arg0 - D_800CC2D0) / 0x32C;
    if (actor_index < 2 && D_800E0BCE[actor_index] != 0) {
        if (D_8008FD90 == 2) {
            request.variant = 0xFD;
        } else if (D_8008FD90 == 4) {
            if (actor_index == 0) {
                request.variant = 0xFB;
            } else {
                request.variant = 0xF7;
            }
        }
    }
    request.one = 1;
    request.mask = 0x200205;
    request.flags = 0x60600;
    request.zero1 = 0;
    request.zero2 = 0;
    request.another_one = 1;
    request.value36 = 0x36;
    request.value80 = 0x80;
    request.value20 = 0x20;
    request.extra = 2;
    result = func_1513B5E0(&request.kind, 1, 8, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + *(s32 *)((u8 *)result + 0x50) + 0xF8,
                      &request.source, 8);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9F00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151B9F00.s")
void func_150A7790(void *, s32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_151EFEB8(void *, s32);
extern f32 D_800AA7B8;
extern u8 D_800BE616, D_800BE9C0, D_800C3E90;
extern void *D_800CC5E8, *D_800CC5EC;
extern u8 D_800D9D10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BA084 CURRENT (5050) */
s32 func_151BA084(void *arg0, s16 arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    f32 matrix[16];
    s32 temp_a3;
    f32 camera[16];
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s16 *temp_s0_2;
    s32 *temp_s0;
    s32 var_s1;

    temp_v0 = (u8 *) arg0 + *(s32 *)((u8 *)(arg0) + 0x50);
    temp_s0 = *(s32 * *)((u8 *)(temp_v0) + 0xF8);
    temp_v0 = (u8 *)temp_v0 + 0xF8;
    if ((*(s32 *)((u8 *)(temp_s0) + 0) == 0) || (*(u8 *)((u8 *)(temp_v0) + 4) != *(u8 *)((u8 *)(temp_s0) + 0x3B))) {
        func_1516972C(arg0);
    }
    temp_a3 = *(s32 *)((u8 *)(temp_s0) + 0x1D4);
    if (temp_a3 == 0) {
        return 0;
    }
    if ((*(u8 *)((u8 *)(temp_s0) + 0x74) & 0xF) == 0xF) {
        return 0;
    }
    if (D_800BE616 != 0) {
        temp_v0_2 = *(void * *)((u8 *)(temp_s0) + 0x318);
        if (temp_v0_2 != NULL) {
            temp_v1 = *(void * *)((u8 *)(temp_s0) + 0x31C);
            if ((temp_v1 != NULL) && (*(u8 *)((u8 *)(temp_v1) + 0x197) != 0) && (arg1 == *(u8 *)((u8 *)(temp_v0_2) + 0x23D))) {
                return 0;
            }
        }
        goto block_18;
    }
    if ((D_800CC5E8 != NULL) && (D_800CC5EC != NULL) && (*(u8 *)((u8 *)(D_800CC5EC) + 0x197) != 0) && (arg1 == *(u8 *)((u8 *)(D_800CC5E8) + 0x23D))) {
        return 0;
    }
block_18:
    if (D_800C3E90 != 0) {
        func_151EFEB8(&matrix, temp_a3 + 0x40);
    } else {
        func_10022EC0(&matrix, (void *)(temp_a3 + 0x40), 0x40U);
    }
    matrix[3] = 0.0f;
    matrix[7] = 0.0f;
    matrix[11] = 0.0f;
    matrix[15] = 1.0f;
    func_150A7790(&matrix, (s32) ((u8 *) ((u8 *) arg0 + (D_800BE9C0 << 6)) + 0x78));
    func_10022EC0(&camera, (arg1 << 6) + ((u8 *) D_800D9D10), 0x40U);
    camera[3] = 0.0f;
    camera[7] = 0.0f;
    camera[11] = 0.0f;
    camera[15] = 1.0f;
    func_150A7960(&matrix, 0.0f, 67.0f, 159.0f, &spA0, &spA4, &spA8);
    func_150A7960(&camera, spA0, spA4, spA8, &spAC, &spB0, &spB4);
    temp_fs0 = D_800AA7B8;
    temp_fv0 = spAC * temp_fs0;
    var_s1 = 0;
    temp_fv1 = spB0 * temp_fs0;
    spAC = temp_fv0;
    spB0 = temp_fv1;
    do {
        temp_s0_2 = (s16 *) (*(s32 *)((u8 *)(((u8 *) ((u8 *) arg0 + (D_800BE9C0 * 0x10)) + (arg1 * 4))) + 0x58) + (var_s1 * 0x10));
        func_150A7960(&matrix, (f32) *(s16 *)((u8 *)(temp_s0_2) + 0), (f32) *(s16 *)((u8 *)(temp_s0_2) + 2), (f32) *(s16 *)((u8 *)(temp_s0_2) + 4), &sp84, &sp88, &sp8C);
        func_150A7960(&camera, sp84, sp88, sp8C, &sp78, &sp7C, &sp80);
        var_s1 += 1;
        sp78 *= temp_fs0;
        sp7C *= temp_fs0;
        *(s16 *)((u8 *)(temp_s0_2) + 8) = (s16) (s32) (sp78 - ((f32) (s32) (temp_fv0 * 0.0009765625f) * 1024.0f));
        *(s16 *)((u8 *)(temp_s0_2) + 0xA) = (s16) (s32) (sp7C - ((f32) (s32) (temp_fv1 * 0.0009765625f) * 1024.0f));
    } while (var_s1 != 0x14);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BA084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA084.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BA468 CURRENT (350) */
void func_151BA468(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    void *temp_v1;

    temp_v0 = (u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x50);
    temp_v1 = *(void **)(temp_v0 + 0xF8);
    temp_v0 += 0xF8;
    if (arg2 == 0) {
        if ((temp_v1 == *(void **)arg1) ||
            (*(u8 *)((u8 *)temp_v1 + 0x3B) == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        void *temp_a0 = *(void **)arg1;

        if (temp_a0 == temp_v1) {
            *(void **)temp_v0 = *(void **)(arg1 + 4);
            temp_v0[4] = arg1[9];
            return;
        }
        if (*(void **)(arg1 + 4) == temp_v1) {
            *(void **)temp_v0 = temp_a0;
            temp_v0[4] = arg1[8];
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BA468 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA468.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BA518.s")
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern void func_151BB0E0(void);

void func_151BB044(void *arg0) {
    func_1000FA64(0x4A7,
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x14),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x18),
                  (s32) (s16) (s32) *(f32 *)((u8 *)arg0 + 0x1C),
                  0x2000, 0x320, 0xC8, (void *)&func_151BB0E0,
                  (s32) arg0, 0, 8, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB0E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BB61C.s")
typedef struct Game1E73B0Effect {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    s32 field08;
    s32 field0C;
    Vec3i position;
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
    u8 pad59[3];
} Game1E73B0Effect;

typedef struct Game1E73B0Config {
    s32 countBase, countRange;
    Vec3f position;
    s16 yawBase, yawRange, pitchBase, pitchRange;
    f32 speedBase, speedRange, durationBase, durationRange;
    s16 lifeBase, lifeRange;
    f32 sizeBase, sizeRange, jitter;
} Game1E73B0Config;

void func_15055A2C(s32, f32, f32, f32, s32);
s32 func_15144E80(void *, void *, void *, void *);
void func_1514FCE8(s16 *, u8, s32);
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
void func_151BBEE4(void *, u8, s32);
void func_151BBFBC(s32, s32, u8, s32);
void func_151C0644(void *, u8, s32);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern s32 D_80082FA0;
extern Vec3f D_8008FBA0;
extern Vec3f D_8008FBAC;
extern s8 D_8008FD8C;
extern f32 D_800AA80C;
extern f32 D_800AA810;
extern f32 D_800AA814;
extern f32 D_800AA818;
extern f32 D_800AA81C;
extern f32 D_800AA820;
extern f32 D_800AA824;
extern f32 D_800AA828;

void func_151BBA9C(s32 arg0, f32 *arg1, f32 *arg2, u8 arg3, s32 arg4) {
    Vec3f center;
    Game1E73B0Effect effect;
    f32 contact[8];
    f32 ground;
    Vec3f probe;
    Vec3f hit;
    Vec3f normal;
    Vec3f tangent;
    Vec3f facing;

    if (arg0 != 0) {
        center.x = (arg2[0] + arg1[0]) * 0.5f;
        center.y = (arg2[1] + arg1[1]) * 0.5f;
        center.z = (arg2[2] + arg1[2]) * 0.5f;
        func_151C04F8(&center.x, arg3, arg4);
        func_151C05A4(&center.x, arg3, arg4);
        func_151C05F0(&center.x, arg3, arg4);
        func_15055A2C(1, center.x, center.y, center.z, 0);
        func_151BBEE4(&center, arg3, arg4);
        effect.field00 = 0;
        effect.field02 = 0xFF;
        effect.field04 = -0x40;
        effect.field06 = 0x47;
        effect.field08 = 6;
        effect.field0C = 4 >> ((D_80082FA0 >= 2) ? 1 : 0);
        effect.position = *(Vec3i *)&center;
        effect.field34 = 7;
        effect.field1C = 23.0f;
        effect.field20 = 30.0f;
        effect.field24 = 45.0f;
        effect.field28 = 53.0f;
        effect.field2C = 203.0f;
        effect.field30 = 414.0f;
        effect.field38 = 3 >> ((D_80082FA0 >= 2 || D_8008FD8C >= 8) ? 1 : 0);
        effect.field4C = 0x19;
        effect.field4E = 0xF;
        effect.field50 = 0x64;
        effect.field52 = 0x64;
        effect.field54 = 0xC;
        effect.field56 = 0x14;
        effect.field3C = 15.0f;
        effect.field40 = D_800AA80C;
        effect.field44 = D_800AA810;
        effect.field48 = D_800AA814;
        if (D_80082FA0 >= 2 || D_8008FD8C >= 8) {
            effect.field58 = -1;
        } else {
            effect.field58 = 0;
        }
        func_1514FCE8(&effect.field00, arg3, arg4);
        func_1504715C(&ground, (void *)arg0);
        probe.x = center.x;
        probe.y = center.y + 100.0f;
        probe.z = center.z;
        if (func_15046C80(&probe.x, 0, center.y - 1000.0f, &ground) != 0) {
            hit.x = probe.x;
            hit.y = ground;
            hit.z = probe.z;
            func_151BBFBC((s32)contact, (s32)&hit, arg3, arg4);
            if (func_15144E80(contact, &normal, &tangent, &facing) != 0 && facing.y < 0.0f) {
                func_151C0644(&hit, arg3, arg4);
            }
        }
        {
            Game1E73B0Config config;
            Vec3f first = D_8008FBA0;
            Vec3f second = D_8008FBAC;

            config.countBase = 4;
            config.countRange = 8;
            config.position = center;
            config.speedBase = 12.0f;
            config.speedRange = 6.0f;
            config.yawBase = 0;
            config.yawRange = 0xFF;
            config.pitchBase = -0x3F;
            config.pitchRange = 0x57;
            config.lifeBase = 0x32;
            config.lifeRange = 0xA;
            config.durationBase = D_800AA818;
            config.durationRange = D_800AA81C;
            config.sizeBase = D_800AA820;
            config.sizeRange = D_800AA824;
            config.jitter = D_800AA828;
            func_15152190(&config, &first, &second, 3, 0.0f, 1, arg3, arg4);
        }
    }
}
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    u8 type;
    s8 neg_one;
    s16 lifetime;
    s8 zero;
} Game1E73B0Descriptor;

void func_151BBEE4(void *arg0, u8 arg1, s32 arg2) {
    Game1E73B0Descriptor descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.neg_one = -1;
    descriptor.lifetime = (func_150ADA20() & 0xF) + 5;
    descriptor.zero = 0;
    position[0] = (s32)*(f32 *)arg0;
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position,
                  (func_150ADA20() % 21U) + 0x1E,
                  0xFF, 0x61, 0x36, 0xFF, 0, 0, arg1, arg2);
}

f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BBFBC(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 pad0;
        f32 scale;
        u32 random_value;
        s32 pad1;
    } locals;

    locals.scale = func_150ADA68();
    locals.random_value = func_150ADA20();
    func_150E7FEC((locals.scale * 75.0f) + 75.0f,
                  ((locals.random_value % 56U) + 0xC8) & 0xFF,
                  arg0, arg1,
                  (func_150ADA20() % 205U) + 0x12B,
                  1, 1, 0, 0, 0, (s32)arg2, 0);
}
void func_151BC074(s32 arg0) {
    if (arg0 != 0) {
        func_15160CDC(arg0, 1, &D_800AA760, &D_800AA76C, D_800AA82C, 2, 0x12C, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E73B0/func_151BC104.s")
