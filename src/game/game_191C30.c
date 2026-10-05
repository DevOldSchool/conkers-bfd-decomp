#include "types.h"

/*
 * Reviewed source unit: src/game/game_191C30.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15164780
 * - func_1516489C
 * - func_15164F0C
 * - func_15165628
 * - func_151658DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15164780 CURRENT (88) */
void *func_15164780(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *sp24;
    void *temp_v0;
    void *temp_v1;

    temp_v1 = *(void **)(D_800DBFF0 + (arg0[6] * 0x9A0) + 0x3D0);
    if (temp_v1 != 0) {
        temp_v0 = *(void **)((u8 *)temp_v1 + 0x31C);
        if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x198) != 0)) {
            return 0;
        }
    }
    temp_v0 = func_15167A68(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x38);
    *(s8 *)((u8 *)sp24 + 0x60) = 1;
    *(s8 *)((u8 *)sp24 + 0x61) = 1;
    *(s8 *)((u8 *)sp24 + 0x62) = 1;
    *(s8 *)((u8 *)sp24 + 0x63) = 1;
    *(s8 *)((u8 *)sp24 + 0x64) = 1;
    *(s8 *)((u8 *)sp24 + 0x65) = 1;
    *(f32 *)((u8 *)sp24 + 0x48) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x50) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x54) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x58) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x5C) = 0.0f;
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15164780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164780.s")
void func_15164888(u8 *arg0) {
    arg0[0x10] |= 2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_1516489C.s")
void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800DCDE0;

void func_15164EE4(void) {
    func_100226F0(&D_800DCDE0, 0x60);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164F0C.s")
typedef struct {
    f32 x, y, z;
} Game191C30Vector;

typedef struct {
    Game191C30Vector points[4];
    f32 firstDuration, holdDuration, secondDuration;
} Game191C30Motion;

typedef struct {
    u8 kind, flags;
    s8 mode;
    u8 pad03;
    s16 duration;
    u8 owner, pad07;
    Game191C30Vector vectors[4];
} Game191C30Header;

typedef struct {
    Game191C30Vector firstVelocity[4], secondVelocity[4], points[4];
    f32 firstDuration, holdDuration, secondDuration, elapsed;
} Game191C30Payload;

void *func_15164780(u8 *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15165628 CURRENT (2709) */
void *func_15165628(Game191C30Motion *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Game191C30Header header;
    Game191C30Payload payload;
    f32 firstInverse, secondInverse;
    void *result;

    arg1 = (u8)arg1;
    arg2 = (s8)arg2;
    if (arg0->firstDuration == 0.0f || arg0->secondDuration == 0.0f) {
        return 0;
    }
    firstInverse = 1.0f / arg0->firstDuration;
    header.kind = 4;
    header.flags = 0;
    header.duration = 300;
    header.owner = arg1;
    header.mode = arg2;
    header.vectors[0].x = 0.0f;
    header.vectors[0].y = 0.0f;
    header.vectors[0].z = 0.0f;
    header.vectors[1].x = 0.0f;
    header.vectors[1].y = 0.0f;
    header.vectors[1].z = 0.0f;
    header.vectors[2].x = 0.0f;
    header.vectors[2].y = 0.0f;
    header.vectors[2].z = 0.0f;
    header.vectors[3].x = 0.0f;
    header.vectors[3].y = 0.0f;
    header.vectors[3].z = 0.0f;
    secondInverse = 1.0f / arg0->secondDuration;
    payload.firstVelocity[0].x = arg0->points[0].x * firstInverse;
    payload.firstVelocity[0].y = arg0->points[0].y * firstInverse;
    payload.firstVelocity[0].z = arg0->points[0].z * firstInverse;
    payload.firstVelocity[1].x = arg0->points[1].x * firstInverse;
    payload.firstVelocity[1].y = arg0->points[1].y * firstInverse;
    payload.firstVelocity[1].z = arg0->points[1].z * firstInverse;
    payload.firstVelocity[2].x = arg0->points[2].x * firstInverse;
    payload.firstVelocity[2].y = arg0->points[2].y * firstInverse;
    payload.firstVelocity[2].z = arg0->points[2].z * firstInverse;
    payload.firstVelocity[3].x = arg0->points[3].x * firstInverse;
    payload.firstVelocity[3].y = arg0->points[3].y * firstInverse;
    payload.firstVelocity[3].z = arg0->points[3].z * firstInverse;
    payload.secondVelocity[1].x = arg0->points[0].x * secondInverse;
    payload.secondVelocity[1].y = arg0->points[0].y * secondInverse;
    payload.secondVelocity[1].z = arg0->points[0].z * secondInverse;
    payload.secondVelocity[0].x = arg0->points[1].x * secondInverse;
    payload.secondVelocity[0].y = arg0->points[1].y * secondInverse;
    payload.secondVelocity[0].z = arg0->points[1].z * secondInverse;
    payload.secondVelocity[3].x = arg0->points[2].x * secondInverse;
    payload.secondVelocity[3].y = arg0->points[2].y * secondInverse;
    payload.secondVelocity[3].z = arg0->points[2].z * secondInverse;
    payload.secondVelocity[2].x = arg0->points[3].x * secondInverse;
    payload.secondVelocity[2].y = arg0->points[3].y * secondInverse;
    payload.secondVelocity[2].z = arg0->points[3].z * secondInverse;
    payload.points[0] = arg0->points[0];
    payload.points[1] = arg0->points[1];
    payload.points[2] = arg0->points[2];
    payload.points[3] = arg0->points[3];
    payload.firstDuration = arg0->firstDuration;
    payload.holdDuration = arg0->holdDuration;
    payload.elapsed = 0.0f;
    payload.secondDuration = arg0->secondDuration;
    result = func_15164780((u8 *)&header, arg3 + 0xA0, (u8)arg4, arg5);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x68, &payload, 0xA0);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15165628 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15165628.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151658DC CURRENT (4020) */
s32 func_151658DC(u8 *arg0) {
    typedef struct { f32 x, y, z; } Point;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    temp_v0 = (void *)(arg0 + 0x68);
    *(f32 *)((u8 *)arg0 + 0x104) = (f32) (*(f32 *)((u8 *)arg0 + 0x104) + D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x104) < *(f32 *)((u8 *)arg0 + 0xF8)) {
        temp_v0_2 = (void *)(arg0 + 0x68);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x68) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 8) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x10) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x14) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x18) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x1C) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x20) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x24) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x28) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x2C) * *(volatile f32 *)((u8 *)temp_v0_2 + 0x9C));
    } else {
        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x9C);
        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x90) + *(f32 *)((u8 *)temp_v0 + 0x94);
        if (temp_fv1 < temp_fa0) {
            *(Point *)(arg0 + 0x18) = *(Point *)(temp_v0 + 0x60);
            *(Point *)(arg0 + 0x24) = *(Point *)(temp_v0 + 0x6C);
            *(Point *)(arg0 + 0x30) = *(Point *)(temp_v0 + 0x78);
            *(Point *)(arg0 + 0x3C) = *(Point *)(temp_v0 + 0x84);
        } else if (temp_fv1 < (temp_fa0 + *(f32 *)((u8 *)temp_v0 + 0x98))) {
            temp_fv0 = temp_fv1 - temp_fa0;
            *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x60) - (*(f32 *)((u8 *)temp_v0 + 0x3C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x64) - (*(f32 *)((u8 *)temp_v0 + 0x40) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x68) - (*(f32 *)((u8 *)temp_v0 + 0x44) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x6C) - (*(f32 *)((u8 *)temp_v0 + 0x30) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x70) - (*(f32 *)((u8 *)temp_v0 + 0x34) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x74) - (*(f32 *)((u8 *)temp_v0 + 0x38) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x78) - (*(f32 *)((u8 *)temp_v0 + 0x54) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x7C) - (*(f32 *)((u8 *)temp_v0 + 0x58) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x80) - (*(f32 *)((u8 *)temp_v0 + 0x5C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x84) - (*(f32 *)((u8 *)temp_v0 + 0x48) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x88) - (*(f32 *)((u8 *)temp_v0 + 0x4C) * temp_fv0));
            *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x8C) - (*(f32 *)((u8 *)temp_v0 + 0x50) * temp_fv0));
        } else {
            var_v1 = 0;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151658DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_151658DC.s")
f32 func_15165BB0(void *, void *, f32, f32, f32);

void func_15165B80(u8 *arg0) {
    func_15165BB0(arg0, arg0 + 0x108, *(f32 *)((u8 *)arg0 + 0x114), *(f32 *)((u8 *)arg0 + 0x118), *(f32 *)((u8 *)arg0 + 0x11C));
}
f32 func_15143E64(void *);                   /* extern */
s32 func_15144B34(s32);                    /* extern */

f32 func_15165BB0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    struct { f32 x; f32 y; f32 z; f32 length; } position;
    f32 var_fv1;
    void *temp_v0;

    temp_v0 = (void *)func_15144B34(*(u8 *)((u8 *)arg0 + 0x16));
    position.x = *(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    position.y = *(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    position.z = *(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    position.length = func_15143E64(&position);
    if (position.length < arg2) {
        var_fv1 = 1.0f;
    } else if ((arg2 + arg3) < position.length) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 1.0f - ((position.length - arg2) * arg4);
    }
    return var_fv1;
}
