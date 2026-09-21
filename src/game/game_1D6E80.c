#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6E80.c
 * Boundary evidence: docs/evidence/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A99D0
 * - func_151A9AA4
 * - func_151A9BA0
 * - func_151A9CA0
 * - func_151A9DC0
 * - func_151A9EC0
 * - func_151A9FC8
 * - func_151AA09C
 * - func_151AA17C
 * - func_151AA210
 * - func_151AA264
 * - func_151AA30C
 * - func_151AA48C
 * - func_151AA5A4
 * - func_151AA6D8
 * - func_151AAA4C
 * - func_151AAABC
 * - func_151AABC4
 * - func_151AADBC
 * - func_151AADF8
 * - func_151AB090
 * - func_151AB180
 * - func_151AB1C4
 * - func_151AB2C4
 * - func_151AB3A4
 * - func_151AB788
 * - func_151AB7D8
 * - func_151AB854
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game1D6E80Vec3;

s32 func_15045800(Game1D6E80Vec3 *, u16, f32, void *);
void func_151ABE40(Game1D6E80Vec3 *, void *, s32, u8, s32);
extern f32 D_800A8F74;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A99D0 CURRENT (520) */
void func_151A99D0(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp2C;
    f32 height;
    void *target;
    register u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F74 < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp2C = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp2C, 3, *(u8 *)((u8 *)arg0 + 0xC),
                       *(u8 *)((u8 *)arg0 + 1));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A99D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A99D0.s")
void func_10010FFC(s32, s32, s32, s32, s32, void *);
void func_151ABE00(void *);
extern f32 D_800A8F78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9AA4 CURRENT (512) */
void func_151A9AA4(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp28;
    f32 height;
    void *target;
    u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F78 < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp28 = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp28, 3,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
    }
    func_151ABE00(object);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9AA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9AA4.s")
extern f32 D_800A8F7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9BA0 CURRENT (502) */
void func_151A9BA0(void *arg0) {
    u8 *object;
    Game1D6E80Vec3 position;
    void *sp28;
    f32 height;
    void *target;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F7C < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp28 = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp28, 1,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9BA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9BA0.s")
void func_151AA264(void *, void *);
extern f32 D_800A8F80;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9CA0 CURRENT (10) */
void func_151A9CA0(void *arg0) {
    void *sp2C;
    register f32 temp_fv0;
    register void *temp_a3;
    register u8 *object;
    register u8 *temp_v0;
    Game1D6E80Vec3 position;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    temp_v0 = *(u8 **)(object + 0x31C);
    if ((temp_v0 == 0) || (*(u8 *)(temp_v0 + 0x95) == 0)) {
        position.x = *(f32 *)(object + 0x14);
        temp_fv0 = *(f32 *)(object + 0x118);
        if (D_800A8F80 < temp_fv0) {
            position.y = temp_fv0 + 100.0f;
        } else {
            position.y = *(f32 *)(object + 0x18) + 150.0f;
        }
        temp_a3 = (u8 *)arg0 + 0x34;
        sp2C = temp_a3;
        position.z = *(f32 *)(object + 0x1C);
        if (func_15045800(&position, 0, position.y - 300.0f,
                          temp_a3) != 0) {
            position.y = *(f32 *)((u8 *)arg0 + 0x34);
            func_151ABE40(&position, sp2C, 1,
                          *(u8 *)((u8 *)arg0 + 0xC),
                          *(u8 *)((u8 *)arg0 + 1));
            func_10010FFC(0, 8, 0x6978, 0, 0, object);
        }
        func_151AA264(object, sp2C);
        func_151ABE00(object);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9CA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9CA0.s")
extern f32 D_800A8F84;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9DC0 CURRENT (502) */
void func_151A9DC0(void *arg0) {
    u8 *object;
    Game1D6E80Vec3 position;
    void *sp28;
    f32 height;
    void *target;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F84 < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp28 = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp28, 2,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9DC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9DC0.s")
void func_151AA264(void *, void *);
extern f32 D_800A8F88;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9EC0 CURRENT (454) */
void func_151A9EC0(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp28;
    register u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    if (D_800A8F88 < *(f32 *)(object + 0x118)) {
        position.y = *(f32 *)(object + 0x118) + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    sp28 = (u8 *)arg0 + 0x34;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, sp28) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp28, 2,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 8, 0x6978, 0, 0, object);
    }
    func_151AA264(object, sp28);
    func_151ABE00(object);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9EC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9EC0.s")
extern f32 D_800A8F8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9FC8 CURRENT (520) */
void func_151A9FC8(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp2C;
    f32 height;
    void *target;
    u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F8C < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp2C = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp2C, 4, *(u8 *)((u8 *)arg0 + 0xC),
                       *(u8 *)((u8 *)arg0 + 1));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9FC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9FC8.s")
extern f32 D_800A8F90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA09C CURRENT (520) */
void func_151AA09C(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp2C;
    f32 height;
    void *target;
    u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8F90 < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp2C = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp2C, 4, *(u8 *)((u8 *)arg0 + 0xC),
                       *(u8 *)((u8 *)arg0 + 1));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA09C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA09C.s")
void func_151AA170(s32 arg0) {

}
typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    u8 field_1C;
} Game1D6E80State;

void func_15147D64(s32 *, s32, void *);
void func_151494E0(s32 *, s32);
void func_1519F3B8(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA17C CURRENT (516) */
void func_151AA17C(Game1D6E80State *arg0) {
    volatile u8 sp20;
    s32 sp1C;
    s32 *volatile sp18;

    sp1C = arg0->field_18;
    sp18 = &sp1C;
    sp20 = arg0->field_1C;
    func_15147D64(&sp1C, 0xA, arg0);
    func_151494E0(sp18, 0xA);
    func_1519F3B8(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA17C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA17C.s")
void func_151AA1D0(void) {
    func_1519F400();
}
void func_151AA1F0(void) {
    func_1519F400();
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA210 CURRENT (516) */
void func_151AA210(Game1D6E80State *arg0) {
    volatile u8 sp20;
    s32 sp1C;
    s32 *volatile sp18;

    sp1C = arg0->field_18;
    sp18 = &sp1C;
    sp20 = arg0->field_1C;
    func_15147D64(&sp1C, 0xA, arg0);
    func_151494E0(sp18, 0xA);
    func_1519F3B8(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA210 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA210.s")
u32 func_1513418C(void *, s32, u8, s32);
extern f32 D_800A8F94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA264 CURRENT (5171) */
void func_151AA264(void *arg0, void *arg1) {
    s8 sp45;
    s8 sp44;
    s8 sp43;
    s8 sp42;
    s16 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s8 sp28;
    void *sp24;
    u8 sp20;
    s32 sp1C;
    s32 sp18;

    if (*(u8 *)((u8 *)arg1 + 0x1C) & 1) {
        sp18 = 0;
        sp1C = 0;
        sp28 = 1;
        sp40 = 0x1E;
        sp42 = 0xE;
        sp43 = 2;
        sp44 = -1;
        sp45 = 0;
        sp24 = arg0;
        sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
        sp2C = 0.0f;
        sp30 = 0.0f;
        sp34 = 0.0f;
        sp38 = 25.0f;
        sp3C = D_800A8F94;
        func_1513418C(&sp18, 0, 0xFFU, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA264 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA30C.s")
typedef struct {
    void *link;
    s8 active;
    u8 pad05[3];
    s32 field08;
    s32 field0C;
    f32 field10;
    f32 field14;
    void *saved;
    u8 id;
    u8 pad1D[3];
    void *object;
    s8 field24;
    u8 pad25[3];
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    s8 field40;
    u8 pad41;
    s16 field42;
    s16 field44;
    s16 field46;
    u8 pad48[2];
    s8 field4A;
    s8 field4B;
    s8 field4C;
    u8 pad4D[3];
    f32 field50;
    s8 field54;
    s8 field55;
} Game1D6E80SpawnLocals;

void *func_10022EC0(void *, const void *, u32);
void *func_15134DAC(u8 *, s32, void *, void *);
extern f32 D_800A8FA4;
extern f32 D_800A8FA8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA48C CURRENT (2190) */
void *func_151AA48C(u8 *arg0, void *arg1) {
    Game1D6E80SpawnLocals locals;
    void *result;

    locals.link = arg1;
    locals.active = 1;
    locals.object = arg0;
    locals.field24 = 0xF;
    locals.field28 = -11.0f;
    locals.field2C = -2.0f;
    locals.field34 = -11.0f;
    locals.field38 = -2.0f;
    locals.field40 = 0;
    locals.field42 = 0x3C;
    locals.field44 = 0x3C;
    locals.field46 = 0x12C;
    locals.field4A = 1;
    locals.field4B = 0;
    locals.field4C = 1;
    locals.field54 = 1;
    locals.field55 = 0;
    locals.field08 = 0;
    locals.field0C = 0x11111;
    locals.id = arg0[0x3B];
    locals.field30 = 8.0f;
    locals.field3C = 20.0f;
    locals.field50 = 0.5f;
    locals.field10 = D_800A8FA4;
    locals.field14 = D_800A8FA8;
    result = func_15134DAC(&locals.id, 0x18, arg0, arg1);
    if (result != 0) {
        locals.saved = result;
        func_10022EC0((u8 *)result + 0x80, &locals.link, 0x18);
        result = locals.saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA48C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA48C.s")
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void *, s32);
s32 func_151EF610(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AA5A4 CURRENT (260) */
s32 func_151AA5A4(void *arg0, s32 arg1) {
    register u8 *object;

    object = arg0;
    *(s32 *)(object + 0x88) = 0;
    if (func_150ADA20(arg0, arg1) & 1) {
        func_10010F88(0xA, 0x55F0,
                      (s16)((func_151EF610() % 1200) - 0x258), 0, 0,
                      (s32)*(f32 *)(object + 0x58),
                      (s32)*(f32 *)(object + 0x5C),
                      (s32)*(f32 *)(object + 0x60), 0x1F4, 0x9C4);
    } else {
        func_10010F88(0xB, 0x55F0,
                      (s16)((func_151EF610() % 1200) - 0x258), 0, 0,
                      (s32)*(f32 *)(object + 0x58),
                      (s32)*(f32 *)(object + 0x5C),
                      (s32)*(f32 *)(object + 0x60), 0x1F4, 0x9C4);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AA5A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA5A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA6D8.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AAA4C CURRENT (900) */
f32 func_151AAA4C(u8 *arg0) {
    f32 temp_fv1;

    temp_fv1 = (func_151423D8((((u32) *(u32 *)((u8 *)arg0 + 0x88) >> 0x10) - 0x40) & 0xFF) * *(f32 *)((u8 *)arg0 + 0x94)) + *(f32 *)((u8 *)arg0 + 0x90);
    *(s32 *)((u8 *)(arg0 + 0x80) + 8) = (s32) (*(u32 *)((u8 *)arg0 + 0x88) + (*(s32 *)((u8 *)arg0 + 0x8C) * D_800BE9E4));
    return temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AAA4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAA4C.s")
void *func_151AA48C(u8 *, void *);
 s32 func_151AB2C4();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AAABC CURRENT (1489) */
void func_151AAABC(void *arg0) {
    s32 sp2C;
    void *sp1C;
    s32 temp_a2;
    s32 temp_a0;
    void *var_v1;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x18);
    var_v1 = (u8 *)arg0 + 0x58;
    if (*(s32 *)((u8 *)arg0 + 0x6C) != 0) {
        *(s8 *)((u8 *)*(s32 **)((u8 *)var_v1 + 0x14) + 0x84) = 1;
    } else {
        sp2C = temp_a2;
        var_v1 = (u8 *)arg0 + 0x58;
        *(s32 *)((u8 *)var_v1 + 0x14) = func_151AA48C(sp2C, arg0, sp2C);
    }
    temp_a0 = *(s32 *)((u8 *)var_v1 + 0x1C);
    if (temp_a0 != 0) {
        *(s8 *)((u8 *)temp_a0 + 0x5C) = 1;
        return;
    }
    sp1C = var_v1;
    *(s32 *)((u8 *)sp1C + 0x1C) = func_151AB2C4(temp_a2, arg0, temp_a2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AAABC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAABC.s")
void func_151352EC(void);

void func_151AAB50(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_151352EC();
}
void func_1513530C(void);

void func_151AAB78(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_1513530C();
}
s32 func_151AABA0(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x84) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x84) = 0U;
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AABC4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AADBC CURRENT (130) */
s32 func_151AADBC(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 0x10;
    {
        s32 var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AADBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADF8.s")
u32 func_150ADA20(void *, s32);                     /* extern */
f32 func_150ADA68();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB090 CURRENT (1097) */
s8 func_151AB090(u8 *arg0) {
    s8 sp27;
    s8 var_a2;
    void *sp1C;
    s32 temp_a0;
    u8 *temp_v1;

    var_a2 = 1;
    temp_v1 = (void *)(arg0 + 0xB0);
    if (*(u8 *)((u8 *)arg0 + 0xB4) == 0) {
        var_a2 = 0;
    }
    *(s8 *)((u8 *)temp_v1 + 4) = 0;
    *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_v1 + 0x14) < 0) {
        sp1C = temp_v1;
        sp27 = var_a2;
        *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) ((func_150ADA20(arg0, var_a2) % (u32) (*(s16 *)((u8 *)temp_v1 + 0x18) + 1)) + *(s16 *)((u8 *)temp_v1 + 0x16));
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_v1 + 0xC)) + *(f32 *)((u8 *)temp_v1 + 8));
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_a0 + (s32) ((*(f32 *)((u8 *)temp_v1 + 0x10) - (f32) temp_a0) * *(f32 *)((u8 *)temp_v1 + 0x1C)));
    return var_a2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB090 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB090.s")
extern void func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB180 CURRENT (100) */
s32 func_151AB180(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0xB0);
    *(s32 *)((u8 *)temp_v0 + 0x70) = 0;
    *(void **)((u8 *)arg0 + 0xB0) = 0;
    temp_v0 = (u8 *)temp_v0 + 0x58;
    *(s32 *)((u8 *)arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB180 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB180.s")
extern f32 D_800A8FEC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB1C4 CURRENT (512) */
void func_151AB1C4(void *arg0) {
    Game1D6E80Vec3 position;
    void *sp28;
    f32 height;
    void *target;
    u8 *object;

    object = *(u8 **)((u8 *)arg0 + 0x18);
    position.x = *(f32 *)(object + 0x14);
    height = *(f32 *)(object + 0x118);
    if (D_800A8FEC < height) {
        position.y = height + 100.0f;
    } else {
        position.y = *(f32 *)(object + 0x18) + 150.0f;
    }
    target = (u8 *)arg0 + 0x34;
    sp28 = target;
    position.z = *(f32 *)(object + 0x1C);
    if (func_15045800(&position, 0, position.y - 300.0f, target) != 0) {
        position.y = *(f32 *)((u8 *)arg0 + 0x34);
        func_151ABE40(&position, sp28, 3,
                      *(u8 *)((u8 *)arg0 + 0xC),
                      *(u8 *)((u8 *)arg0 + 1));
        func_10010FFC(0, 0x11, 0x5208, 0, 0, object);
    }
    func_151AA264(object, sp28);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB1C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB1C4.s")
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800A8FF0;

typedef struct Game1D6E80SpawnPacket {
    void *field_00;
    s8 field_04;
    u8 pad05;
    s16 field_06;
    f32 field_08;
    s32 field_0C;
    s32 field_10;
    u8 field_14;
    u8 pad15[3];
    s32 field_18;
    s8 field_1C;
    u8 pad1D[3];
    f32 field_20;
    f32 field_24;
    f32 field_28;
    f32 field_2C;
    f32 field_30;
    s16 field_34;
    s8 field_36;
    s8 field_37;
    s8 field_38;
    s8 field_39;
} Game1D6E80SpawnPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB2C4 CURRENT (1475) */
s32 func_151AB2C4(s32 arg0, void *arg1) {
    Game1D6E80SpawnPacket packet;
    u32 sp18;
    u32 temp_v0;
    u32 var_v1;

    packet.field_06 = 0;
    packet.field_04 = 1;
    packet.field_00 = arg1;
    packet.field_0C = 0;
    packet.field_10 = 0;
    packet.field_08 = *(f32 *)(arg0 + 0x118);
    packet.field_1C = 1;
    packet.field_20 = 0.0f;
    packet.field_24 = 0.0f;
    packet.field_28 = 0.0f;
    packet.field_34 = 0x12C;
    packet.field_36 = 0xA;
    packet.field_37 = 3;
    packet.field_38 = 0;
    packet.field_39 = 1;
    packet.field_18 = arg0;
    packet.field_14 = *(u8 *)(arg0 + 0x3B);
    packet.field_2C = 25.0f;
    packet.field_30 = D_800A8FF0;
    temp_v0 = func_1513418C(&packet.field_0C, 0xC, 0xFFU, 0);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp18 = temp_v0;
        func_10022EC0((u8 *)temp_v0 + 0x58, &packet, 0xC);
        var_v1 = sp18;
    }
    return (s32)var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB2C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB3A4.s")
s32 func_10010F30(s32, s32, s32, s32, s32);
void func_100111C8(s32, void *);
extern void *D_800DBFF0;

u8 func_151AB6B8(void *arg0) {
    u8 result;
    u8 *state;

    result = 1;
    state = (u8 *)arg0 + 0x58;
    if ((*(u16 *)((u8 *)arg0 + 0x5E) != 0) &&
        ((*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 1) == 0)) {
        func_100111C8(*(u16 *)(state + 6), arg0);
        *(u16 *)(state + 6) = 0;
    } else if ((*(u16 *)(state + 6) == 0) &&
               (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 1)) {
        *(s16 *)(state + 6) = (s16)func_10010F30(0x355, 0x7D00, 0x40, 0, 0);
    }
    if (state[4] == 0) {
        result = 0;
    }
    state[4] = 0;
    return result;
}
/* Call context: func_100111C8: unique active project prototype */
/* Call context: func_151346EC: unique active project prototype */
void func_100111C8(s32, void *);
void func_151346EC(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB788 CURRENT (690) */
void func_151AB788(void *arg0) {
    void *sp18;
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x58) + 0x58);
    if (*(u16 *)((u8 *)arg0 + 0x5E) != 0) {
        sp18 = temp_v0;
        func_100111C8((s32) *(u16 *)((u8 *)arg0 + 0x5E), (u16) arg0);
    }
    *(s32 *)((u8 *)temp_v0 + 0x1C) = 0;
    func_151346EC();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB788 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB788.s")
/* Call context: func_100111C8: unique active project prototype */
/* Call context: func_1513470C: unique active project prototype */
void func_1513470C(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB7D8 CURRENT (690) */
void func_151AB7D8(void *arg0) {
    void *sp18;
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x58) + 0x58);
    if (*(u16 *)((u8 *)arg0 + 0x5E) != 0) {
        sp18 = temp_v0;
        func_100111C8((s32) *(u16 *)((u8 *)arg0 + 0x5E), (u16) arg0);
    }
    *(s32 *)((u8 *)temp_v0 + 0x1C) = 0;
    func_1513470C();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB7D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB7D8.s")
void func_15141DA4(s32 arg0, s32 arg1, s32 arg2, void *arg3);

void func_151AB828(void *arg0) {
    func_15141DA4(*(s32 *)((u8 *)arg0 + 0x18), 0, 4, arg0);
}
typedef struct Game1D6E80Event {
    void *object;
    u8 value4;
    u8 pad5;
    s16 value6;
    s8 value8;
    s8 value9;
    s8 valueA;
} Game1D6E80Event;

void func_15190770(Game1D6E80Event *, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB854 CURRENT (532) */
void func_151AB854(u8 *arg0) {
    Game1D6E80Event event;
    u8 *object;
    u8 type;

    object = *(u8 **)(arg0 + 0x18);
    type = object[4];
    if ((type == 0) || (type == 1) || (type == 2) || (type == 3) ||
        (type == 4) || (type == 0x96)) {
        event.object = object;
        event.value6 = 0x12C;
        event.value8 = 0;
        event.value9 = 0;
        event.value4 = object[0x3B];
        if (object[4] == 0x96) {
            event.valueA = 3;
        } else {
            event.valueA = 0;
        }
        if (object[0x127] != 0xFF) {
            *(s16 *)(*(u8 **)(object + 0x31C) + 0x66) = 0x1F4;
        }
        func_15190770(&event, 0, arg0[0xC], arg0[1]);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB854 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB854.s")
void func_151AB920(s32 arg0, s32 arg1) {
}
