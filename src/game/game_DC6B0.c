#include "types.h"

/*
 * Reviewed source unit: src/game/game_DC6B0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AF200
 * - func_150AF2E0
 * - func_150AF328
 * - func_150AF6E4
 * - func_150AF7C4
 * - func_150AFBF4
 * - func_150AFDB0
 * - func_150AFE64
 * - func_150B0094
 * - func_150B0348
 * - func_150B060C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_151149AC(u8);
void func_1505D024(s32, s32, s32, s32);
typedef struct GameCollisionHeightActor {
    u8 pad00[0x18];
    f32 y;
    u8 pad1C[0x2FC];
    void *entity;
    u8 pad31C[0x10];
} GameCollisionHeightActor;

extern GameCollisionHeightActor D_800CC2D0[];
extern u8 D_800CC3D4;
extern s32 D_800DBEF4;
extern s32 D_800DBF94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF200 CURRENT (80) */
void func_150AF200(s32 arg0, s32 arg1) {
    s32 delta;
    s32 index;

    if (D_800CC3D4 == 0) {
        delta = func_151149AC((u8)arg0) - D_800DBEF4;
        index = delta / 160;
        if (*(s32 *)(((u8 (*)[4])D_800DBF94)[index]) & 1) {
            func_1505D024((s32)&D_800CC2D0, 0x3F, 0x6E00, -1);
            return;
        }
        delta = func_151149AC((u8)arg1) - D_800DBEF4;
        index = delta / 160;
        if (*(s32 *)(((u8 (*)[4])D_800DBF94)[index]) & 1) {
            func_1505D024((s32)&D_800CC2D0, 0x3F, 0xEE00, -1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF200 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF200.s")
extern void func_151CF898(void *arg0, f32 arg1, f32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 CURRENT (10) */
void func_150AF2E0(void *arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg1 + 2);
    func_151CF898(arg0, (f32)(temp_v0 + *(s16 *)((u8 *)arg1 + 8)), (f32)temp_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF2E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF2E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF328.s")
/* Call context: func_15131828: unique active project prototype */
/* Call context: func_15131958: unique active project prototype */
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF6E4 CURRENT (10) */
s32 func_150AF6E4(s32 arg0, s32 arg1) {
    s32 sp20;
    s32 temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)((u8 *)temp_a2 + 0xC));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF6E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF6E4.s")
void func_1515FF74(s8 *, s32, u8, void *);

void func_150AF738(s16 arg0, u8 arg1, void *arg2) {
    struct {
        s8 sp18;
        s8 sp19;
        s8 sp1A;
        u8 pad1B;
        s16 sp1C;
        s8 sp1E;
    } locals;

    locals.sp18 = 1;
    locals.sp19 = -1;
    locals.sp1A = 2;
    locals.sp1E = 0;
    locals.sp1C = arg0;
    func_1515FF74(&locals.sp18, 0, arg1, arg2);
}
void func_150B1DB0(s32 arg0, s32 arg1, s32 arg2);

void func_150AF790(s32 arg0, s32 arg1) {
    func_150B1DB0(arg1, arg1 + 0x1ECC0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AF7C4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 CURRENT (220) */
s32 func_150AFBF4(u8 *arg0) {
    volatile struct {
        u8 *ptr;
        u8 pad[4];
    } saved;
    register f32 temp_fv0;
    volatile f32 *temp_v1;

    *(f32 *)((u8 *)arg0 + 0x78) += *(f32 *)((u8 *)arg0 + 0x7C) * D_800BE9A4;
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)arg0 + 0x78));
    temp_v1 = (volatile f32 *)((s32)arg0 + 0x70);
    temp_v1[2] = temp_fv0;
    saved.ptr = (u8 *)temp_v1;
    temp_fv0 = func_15047D60(temp_fv0);
    temp_v1 = (volatile f32 *)saved.ptr;
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (temp_v1[0] + (temp_v1[1] * temp_fv0));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFBF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFBF4.s")
void func_1516D99C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_150AFC68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516D99C(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (u8) (s32) arg4, arg5);
}
void func_1516972C(void *);
extern u8 D_800C3E78;
extern void *D_800DCE94;
extern s8 D_800DD190;
extern s32 D_800DD198;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFDB0 CURRENT (3002) */
void func_150AFDB0(void) {
    s32 temp_t7;
    void **var_v0;
    void *var_a0;
    u8 *var_s0;

    var_a0 = D_800DCE94;
    temp_t7 = D_800DD190 + 1;
    D_800DD190 = temp_t7;
    if (var_a0 != 0) {
        var_v0 = (void **)((u8 *)&D_800DD198 + ((s8)temp_t7 * 4));
        var_s0 = &D_800C3E78;
        do {
            *var_v0 = *(void **)((u8 *)var_a0 + 8);
            if (*var_s0 == *(u8 *)((u8 *)var_a0 + 0x3F)) {
                func_1516972C(var_a0);
                var_v0 = (void **)((u8 *)&D_800DD198 + (D_800DD190 * 4));
            }
            var_a0 = *var_v0;
        } while (var_a0 != 0);
    }
    D_800DD190 -= 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFDB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFDB0.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
void func_150E2DB4(s32, u8, s16, s32, f32, f32, f32, f32, f32, f32, s16, s16, u16, u8);
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AFE64 CURRENT (16) */
void func_150AFE64(s32 arg0) {
    f32 near_x;
    f32 near_y;
    f32 near_z;
    f32 far_x;
    f32 far_y;
    f32 far_z;
    s32 index;
    void *matrix;
    u8 *matrices;

    matrices = *(u8 **)((u8 *)D_800D154C + 0x1D4);
    if (matrices != 0) {
        if (arg0 == 0) {
            index = 3;
        } else {
            index = 2;
        }
        matrix = (void *)((u32)matrices + ((u32)index << 6));
        near_x = 0.0f;
        near_y = 0.0f;
        near_z = -20.0f;
        func_150A7960(matrix, 0.0f, 0.0f, -20.0f, &near_x, &near_y, &near_z);
        far_x = 0.0f;
        far_y = 0.0f;
        far_z = -150.0f;
        func_150A7960(matrix, 0.0f, 0.0f, -150.0f, &far_x, &far_y, &far_z);
        func_150E1AB0(0, near_x, near_y, near_z, far_x, far_y, far_z,
                     40.0f, 0.0f, 2.0f, 120.0f, 60, 35,
                     0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        arg0 = (s32)D_800D154C;
        func_150E2DB4(arg0, *((u8 *)arg0 + 0x3B),
                     (s16)index, -1, 0.0f, 0.0f, -39.0f,
                     0.0f, 0.0f, -150.0f, 3, 255, 4, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AFE64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150AFE64.s")
void func_15179008(s32);
void func_150AF200(s32, s32);
extern s32 D_800BE9F0;

void func_150B003C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF200(0xE2, 0xE1);
        return;
    }
    func_150AF200(0xDF, 0xDE);
}
typedef struct GameDC6B0Vector {
    f32 x, y, z;
} GameDC6B0Vector;

typedef struct GameDC6B0Packet {
    f32 field0, field4, field8, fieldC;
    f32 angle0, angle1, angle2;
    GameDC6B0Vector scale;
    GameDC6B0Vector position;
    GameDC6B0Vector velocity;
    GameDC6B0Vector field40;
    f32 field4C;
    s32 field50;
    s16 field54, field56;
    u8 field58;
    u8 pad59[3];
    s32 field5C;
    u8 field60, field61, field62, field63;
    u8 field64, field65, field66, field67;
    u8 field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 field72, field74;
    u8 pad76[2];
    s32 field78;
} GameDC6B0Packet;

typedef struct GameDC6B0Link {
    void *object;
    s32 zero;
} GameDC6B0Link;

void *func_10022EC0(void *, const void *, u32);
void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
void func_15145974(void *, f32 *, f32 *);
void *func_151B7328(void *, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
extern f32 D_8009F7D8;
extern GameDC6B0Vector D_800A5480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B0094 CURRENT (75) */
void func_150B0094(GameDC6B0Vector *arg0, GameDC6B0Vector *arg1, u8 arg2, s32 arg3) {
    GameDC6B0Packet packet;
    GameDC6B0Vector delta;
    f32 length;
    f32 inverse_length;
    u8 *created;
    GameDC6B0Link link;
    void **slot;

    link.zero = 0;
    delta.x = arg1->x - arg0->x;
    delta.y = arg1->y - arg0->y;
    delta.z = arg1->z - arg0->z;
    if (func_15145128(&delta.x, &delta.x, &length, &inverse_length) != 0) {
        packet.field4 = packet.field0 = 1.0f;
        packet.field8 = packet.fieldC = D_8009F7D8;
        packet.position = *arg0;
        packet.velocity.x = delta.x * 80.0f;
        packet.velocity.y = delta.y * 80.0f;
        packet.velocity.z = delta.z * 80.0f;
        func_15145974(&packet.velocity, &packet.angle1, &packet.angle0);
        packet.scale.z = packet.scale.y = packet.scale.x = 1.0f;
        packet.angle2 = 0.0f;
        packet.field40 = D_800A5480;
        packet.field50 = 0x19A0;
        packet.field54 = 0x12C;
        packet.field56 = 0xD2;
        packet.field58 = 7;
        packet.field5C = 0;
        packet.field60 = 0xFF;
        packet.field61 = 8;
        packet.field62 = 0;
        packet.field63 = 0;
        packet.field64 = 0;
        packet.field65 = 0;
        packet.field66 = 0;
        packet.field67 = 0;
        packet.field68 = 2;
        packet.field6A = 0;
        packet.field6C = 0;
        packet.field70 = 0;
        packet.field72 = 1;
        packet.field74 = 0xFF;
        packet.field78 = 0;
        packet.field4C = 0.0f;
        created = func_1513264C(&packet, 3, 0xFF, 0, 4, arg2, arg3);
        if (created != 0) {
            slot = (void **)(created + 0x170);
            func_10022EC0(slot, &link.zero, 4);
            link.object = created;
            *slot = func_151B7328(&link, 1, 8, arg2, arg3);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B0094 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0094.s")
void func_1516972C(void *arg0);
void func_150B02C0(void *arg0);
void func_15132570(s32 arg0);
void func_1513259C(s32 arg0);

void func_150B02C0(void *arg0) {
    volatile void **field_170 = (volatile void **)((u8 *)arg0 + 0x170);

    if (*field_170 != 0) {
        func_1516972C((void *)*field_170);
    }
}

void func_150B02F0(s32 arg0) {
    func_150B02C0((void *)arg0);
    func_15132570(arg0);
}
void func_150B031C(s32 arg0) {
    func_150B02C0((void *)arg0);
    func_1513259C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B0348.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B060C CURRENT (200) */
s32 func_150B060C(u8 arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = func_151149AC(arg0);
    *(s32 *)((u8 *)arg1 + 8) = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    temp_v1 = *(s32 *)((u8 *)arg1 + 8);
    *(f32 *)((u8 *)arg1 + 0) = -150.0f;
    *(f32 *)((u8 *)arg1 + 4) = 4.5f;
    *(f32 *)((u8 *)arg1 + 0xC) = (f32) *(s16 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg1 + 0x10) = (f32) *(s16 *)((u8 *)temp_v1 + 0x12);
    *(f32 *)((u8 *)arg1 + 0x14) = (f32) *(s16 *)((u8 *)temp_v1 + 0x14);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B060C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC6B0/func_150B060C.s")
