#include "types.h"

/*
 * Reviewed source unit: src/game/game_1ED0F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BFC40
 * - func_151BFDA0
 * - func_151BFE84
 * - func_151C0098
 * - func_151C02E4
 * - func_151C0360
 * - func_151C04F8
 * - func_151C0698
 * - func_151C1180
 * - func_151C1570
 * - func_151C1814
 * - func_151C196C
 * - func_151C1D5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_80082FA0;
extern s8 D_8008FD8C;
extern f32 D_800AA97C;
extern f32 D_800AA980;
extern f32 D_800AA984;
extern f32 D_800AA988;
extern f32 D_800AA98C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFC40 CURRENT (1690) */
void func_151BFC40(void *arg0, f32 *arg1) {
    s32 var_v0;
    s32 var_v0_2;

    *(s32 *)((u8 *)arg0 + 0) = 3;
    if (D_80082FA0 >= 2) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    *(s32 *)((u8 *)arg0 + 4) = (s32) (4 >> var_v0);
    *arg1 = 494.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) D_800AA97C;
    *(s32 *)((u8 *)arg0 + 0x2C) = 7;
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) D_800AA980;
    *(f32 *)((u8 *)arg0 + 0x1C) = 45.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 53.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = 203.0f;
    *(f32 *)((u8 *)arg0 + 0x28) = 414.0f;
    if ((D_80082FA0 >= 2) || (var_v0_2 = 0, ((D_8008FD8C < 8) == 0))) {
        var_v0_2 = 1;
    }
    *(s32 *)((u8 *)arg0 + 0x30) = (s32) (3 >> var_v0_2);
    *(f32 *)((u8 *)arg0 + 0x34) = 15.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) D_800AA984;
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) D_800AA988;
    *(s16 *)((u8 *)arg0 + 0x44) = 0x19;
    *(s16 *)((u8 *)arg0 + 0x46) = 0xF;
    *(s16 *)((u8 *)arg0 + 0x48) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4A) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4C) = 0xC;
    *(s16 *)((u8 *)arg0 + 0x4E) = 0x14;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) D_800AA98C;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
        *(s8 *)((u8 *)arg0 + 0x50) = -1;
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x50) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFC40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFC40.s")
void func_151BFC40(void *, f32 *);
void func_151C0418(void *, u8, s32);
void func_151C04F8(s32, u8, s32);
void func_151C05A4(s32, u8, s32);
void func_151C05F0(s32, u8, s32);
void func_1514FB98(f32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFDA0 CURRENT (1415) */
void func_151BFDA0(void *arg0, f32 *arg1, u8 arg2, s32 arg3, s32 arg4) {
    u8 sp34[0x51];
    f32 sp30;
    f32 sp24[3];
    u8 temp_s1;

    temp_s1 = arg3;
    func_151C0418(arg0, temp_s1, arg4);
    func_151C04F8((s32)arg0, temp_s1, arg4);
    func_151C05A4((s32)arg0, temp_s1, arg4);
    func_151C05F0((s32)arg0, temp_s1, arg4);
    if (arg2 != 0) {
        sp24[0] = -arg1[0];
        sp24[1] = -arg1[1];
        sp24[2] = -arg1[2];
        func_151BFC40(sp34, &sp30);
        *(s32 *)(sp34 + 8) = *(s32 *)((u8 *)arg0 + 0);
        *(s32 *)(sp34 + 0xC) = *(s32 *)((u8 *)arg0 + 4);
        *(s32 *)(sp34 + 0x10) = *(s32 *)((u8 *)arg0 + 8);
        func_1514FB98(sp24, temp_s1, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFDA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0098.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C02E4 CURRENT (450) */
s32 func_151C02E4(void *arg0, void *arg1, s32 arg2, void **arg3) {
    s32 temp_t6;
    void **temp_t7;
    void *temp_t8;
    s32 temp_t9;
    s32 var_v0;

    var_v0 = 0;
    if (arg2 > 0) {
loop_1:
        temp_t6 = var_v0 << 2;
        temp_t7 = (void **)((u8 *)arg3 + temp_t6);
        temp_t8 = *temp_t7;
        if (arg0 == temp_t8) {
            return 0;
        }
        var_v0 += 1;
        temp_t9 = var_v0 & 0xFF;
        if (temp_t9 >= arg2) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C02E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C02E4.s")
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C0360 CURRENT (1098) */
void func_151C0360(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u32 random_value;
    f32 scale;

    scale = func_150ADA68();
    random_value = func_150ADA20((void *)0);
    func_150E7FEC((scale * 75.0f) + 75.0f,
                  ((random_value % 56U) + 0xC8) & 0xFF,
                  arg0, arg1,
                  (func_150ADA20((void *)0) % 205U) + 0x12B,
                  1, 1, 0, 0, 0, (s32)arg2, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C0360 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0360.s")
u32 func_150ADA20();
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct Game1ED0F0Position {
    s32 x;
    s32 y;
    s32 z;
} Game1ED0F0Position;

typedef struct Game1ED0F0Particle {
    u8 type;
    s8 subtype;
    s16 duration;
    s8 flags;
} Game1ED0F0Particle;

void func_151C0418(void *arg0, u8 arg1, s32 arg2) {
    Game1ED0F0Particle particle;
    Game1ED0F0Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 11U) + 0x14;
    particle.flags = 0;
    position.x = (s32)*(f32 *)((u8 *)arg0 + 0);
    position.y = (s32)*(f32 *)((u8 *)arg0 + 4);
    position.z = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20(arg0) % 121U) + 0x3C,
                   0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg1, arg2);
}
extern void func_151541B8(s32 arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4, u8 arg5, s32 arg6);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C04F8 CURRENT (2124) */
void func_151C04F8(s32 arg0, u8 arg1, s32 arg2) {
    f32 sp28;
    f32 var_ft5;
    s32 temp_t7;

    sp28 = func_150ADA68();
    temp_t7 = (func_150ADA20((void *)arg0) % 56U) + 0xC8;
    var_ft5 = (f32)temp_t7;
    if (temp_t7 < 0) {
        var_ft5 += 4294967296.0f;
    }
    func_151541B8(arg0, (sp28 * 4.0f) + 14.0f, 0x3F974EB9, var_ft5, 0.0f, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C04F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C04F8.s")
void func_151D5334(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_151C05A4(s32 arg0, u8 arg1, s32 arg2) {
    func_151D5334(arg0, 0x44480000, 0x44FA0000, 0x3A03126F, 5, arg1, arg2);
}
void func_151D5404(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_151C05F0(s32 arg0, u8 arg1, s32 arg2) {
    func_151D5404(arg0, 0x44480000, 0x44FA0000, 0x3A03126F, 0xF, 0x14, arg1, arg2);
}
void func_150E83AC(s32, s16, u8, s32);

void func_151C0644(s32 arg0, u8 arg1, s32 arg2) {
    func_150E83AC(arg0, (s16) ((func_150ADA20() % 62U) + 0x78), arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0698.s")
s32 func_151C110C(void *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x18);
    if ((temp_v1 != 0) && (*arg2 != 0)) {
        *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x38);
        *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x3C);
        *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x40);
        return 0;
    }
    *arg6 = 0;
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1180.s")
void func_1516972C(s32, ...);
void func_1000FD38(s32 (*)(void *, s32, s32 *, s32, s32, s32, s16 *), s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C1570 CURRENT (2291) */
void func_151C1570(s32 arg0) {
    void *sp1C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_t7;
    void *temp_a1;
    void *temp_v1;

    temp_t7 = *(s32 *)((u8 *)arg0 + 0x1F0);
    if (temp_t7 != 0) {
        func_1516972C(temp_t7);
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x1F4);
    temp_a1 = (u8 *)arg0 + 0x170;
    if (temp_a0 != 0) {
        sp1C = temp_a1;
        func_1516972C(temp_a0, temp_a1);
        temp_a1 = sp1C;
    }
    temp_v1 = *(void **)((u8 *)temp_a1 + 0x88);
    if (temp_v1 != 0) {
        *(s32 *)((u8 *)temp_v1 + 0x110) = 0;
    }
    temp_a0_2 = *(s32 *)((u8 *)temp_a1 + 0x8C);
    if (temp_a0_2 != 0) {
        func_1516972C(temp_a0_2, temp_a1);
    }
    func_1000FD38(func_151C110C, arg0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C1570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1570.s")
void func_151C1570(s32 arg0);
void func_1513259C(s32 arg0);

void func_151C15FC(s32 arg0) {
    func_151C1570(arg0);
    func_15132570(arg0);
}
void func_151C1628(s32 arg0) {
    func_151C1570(arg0);
    func_1513259C(arg0);
}
void func_151D40D4(void *, s32, s32, s32, s32, s32, s32, s32);
void func_151D42E8(void *, s32, s32, s32, s32);
extern void (*D_800E0934)(s32, s32, s32);

void func_151C1654(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    if (D_800E0934 != 0) {
        D_800E0934((s32)*(f32 *)((u8 *)arg0 + 0),
                   (s32)*(f32 *)((u8 *)arg0 + 4),
                   (s32)*(f32 *)((u8 *)arg0 + 8));
    }
    switch (arg3) {
    case 1:
        func_151D42E8(arg0, arg1, arg2, arg4, 0x24);
        return;
    case 2:
        func_151D42E8(arg0, arg1, arg2, arg4, 0x25);
        return;
    case 3:
        func_151D40D4(arg0, arg1, arg2, 0, arg4, 0x16, 0x26, 0);
        return;
    default:
    case 0:
        func_151D40D4(arg0, arg1, arg2, 0, arg4, 0x16, 0x15, 0);
        return;
    }
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1ED0F0Vector;

typedef struct {
    u8 pad0[4];
    u8 type;
    u8 pad5[0x1CF];
    s32 transform;
} Game1ED0F0Object;

void func_15143134(f32 *, f32 *, s32); /* extern */
extern u8 D_800AA954[];
extern Game1ED0F0Vector D_800AA958[];

void func_151C1798(Game1ED0F0Object *arg0, f32 *arg1) {
    s32 index;
    u8 type;

    type = arg0->type;
    if (type != 0x28) {
        if (type != 0x77) {
            index = 0;
        } else {
            index = 1;
        }
    } else {
        index = 2;
    }
    func_15143134(&D_800AA958[index].x, arg1,
                  (D_800AA954[index] << 6) + arg0->transform);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C1814 CURRENT (205) */
void func_151C1814(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x6C);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = temp_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C1814 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1814.s")
void func_151C1860(void *arg0, u8 arg1, s32 arg2) {
    Game1ED0F0Particle particle;
    Game1ED0F0Position position;

    particle.type = 3;
    particle.subtype = -1;
    particle.duration = (func_150ADA20() % 5U) + 5;
    particle.flags = 0;
    position.x = (s32)*(f32 *)((u8 *)arg0 + 0);
    position.y = (s32)*(f32 *)((u8 *)arg0 + 4);
    position.z = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&particle, &position.x,
                   (func_150ADA20(arg0) % 11U) + 5,
                   0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg1, arg2);
}
s32 func_151C02E4(void *arg0, void *arg1, s32 arg2, void **arg3);

void func_151C1940(void *arg0, void *arg1, s32 *arg2) {
    func_151C02E4(arg0, arg1, *arg2, (void **)((u8 *)arg2 + 4));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C196C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1D5C.s")
typedef struct {
    s8 field_0;
    s8 pad1;
    s16 field_2;
    s8 field_4;
    s8 field_5;
    s8 field_6;
} Game1ED0F0EventPacket;

void func_151D8868(s8 *, s32, s32, s32);

void func_151C1FB8(void *arg0) {
    Game1ED0F0EventPacket packet;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        packet.field_0 = 1;
        packet.field_2 = (func_150ADA20(arg0) & 7) + 0xD;
        packet.field_5 = 1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D);
        packet.field_4 = (func_150ADA20(arg0) % 3U) + 6;
        packet.field_6 = -1;
        func_151D8868(&packet.field_0, 0, 0xFF, 1);
    }
}
