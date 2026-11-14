#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_191C30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15164F0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
extern s32 D_800DBFF0;

void *func_15164780(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *sp24;
    void *temp_v0;
    void *temp_v1;

    /* Reuse v0 for the owner base and linked object, matching their disjoint lifetimes. */
    temp_v0 = (void *)(D_800DBFF0 + (arg0[6] * 0x9A0));
    temp_v1 = *(void **)((u8 *)temp_v0 + 0x3D0);
    if (temp_v1 != 0) {
        temp_v0 = *(void **)((u8 *)temp_v1 + 0x31C);
        if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x198) != 0)) {
            return 0;
        }
    }
    sp24 = func_15167A68(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (sp24 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)sp24 + 0x10, arg0, 0x38);
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
void func_15164888(u8 *arg0) {
    arg0[0x10] |= 2;
}
f32 func_15047D60(f32);
f32 func_15144B68(f32);
void func_15164888(u8 *);
typedef struct { u8 v[3]; } Bytes3_1516489C;
extern s32 (*D_8008B390[])(u8 *);
extern f32 (*D_8008B394[])(u8 *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern u8 D_800DCDE0;

void func_1516489C(u8 *arg0) {
    s32 pad;
    u8 done;
    u8 kill;
    f32 scale;
    Bytes3_1516489C prevA;
    Bytes3_1516489C prevB;

    done = 0;
    kill = 0;
    if (arg0[0x10] & 1) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            kill = 1;
        }
    }
    if (!kill && *(s8 *)(arg0 + 0x11) != -1 && !D_8008B390[*(s8 *)(arg0 + 0x11)](arg0)) {
        kill = 1;
    }
    if (kill != 0) {
        func_15164888(arg0);
    }
    prevA = *(Bytes3_1516489C *)(arg0 + 0x60);
    prevB = *(Bytes3_1516489C *)(arg0 + 0x63);
    scale = 1.0f;
    if (arg0[0x10] & 4) {
        if (*(s8 *)(arg0 + 0x12) != -1) {
            scale = D_8008B394[*(s8 *)(arg0 + 0x12)](arg0);
        }
    }
    if (*(f32 *)(arg0 + 0x30) != 0.0f) {
        *(f32 *)(arg0 + 0x48) = func_15144B68(*(f32 *)(arg0 + 0x30) * D_800BE9A4 + *(f32 *)(arg0 + 0x48));
        arg0[0x60] = *(f32 *)(arg0 + 0x48) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevA.v[0] != arg0[0x60])) {
            *(f32 *)(arg0 + 0x30) = 0.0f;
            *(f32 *)(arg0 + 0x48) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[0] += func_15047D60(*(f32 *)(arg0 + 0x48)) * *(f32 *)(arg0 + 0x18) * scale;
    }
    if (*(f32 *)(arg0 + 0x34) != 0.0f) {
        *(f32 *)(arg0 + 0x4c) = func_15144B68(*(f32 *)(arg0 + 0x34) * D_800BE9A4 + *(f32 *)(arg0 + 0x4c));
        arg0[0x61] = *(f32 *)(arg0 + 0x4c) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevA.v[1] != arg0[0x61])) {
            *(f32 *)(arg0 + 0x34) = 0.0f;
            *(f32 *)(arg0 + 0x4c) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[1] += func_15047D60(*(f32 *)(arg0 + 0x4c)) * *(f32 *)(arg0 + 0x1c) * scale;
    }
    if (*(f32 *)(arg0 + 0x38) != 0.0f) {
        *(f32 *)(arg0 + 0x50) = func_15144B68(*(f32 *)(arg0 + 0x38) * D_800BE9A4 + *(f32 *)(arg0 + 0x50));
        arg0[0x62] = *(f32 *)(arg0 + 0x50) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevA.v[2] != arg0[0x62])) {
            *(f32 *)(arg0 + 0x38) = 0.0f;
            *(f32 *)(arg0 + 0x50) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[2] += func_15047D60(*(f32 *)(arg0 + 0x50)) * *(f32 *)(arg0 + 0x20) * scale;
    }
    if (*(f32 *)(arg0 + 0x3c) != 0.0f) {
        *(f32 *)(arg0 + 0x54) = func_15144B68(*(f32 *)(arg0 + 0x3c) * D_800BE9A4 + *(f32 *)(arg0 + 0x54));
        arg0[0x63] = *(f32 *)(arg0 + 0x54) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevB.v[0] != arg0[0x63])) {
            *(f32 *)(arg0 + 0x3c) = 0.0f;
            *(f32 *)(arg0 + 0x54) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[3] += func_15047D60(*(f32 *)(arg0 + 0x54)) * *(f32 *)(arg0 + 0x24) * scale;
    }
    if (*(f32 *)(arg0 + 0x40) != 0.0f) {
        *(f32 *)(arg0 + 0x58) = func_15144B68(*(f32 *)(arg0 + 0x40) * D_800BE9A4 + *(f32 *)(arg0 + 0x58));
        arg0[0x64] = *(f32 *)(arg0 + 0x58) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevB.v[1] != arg0[0x64])) {
            *(f32 *)(arg0 + 0x40) = 0.0f;
            *(f32 *)(arg0 + 0x58) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[4] += func_15047D60(*(f32 *)(arg0 + 0x58)) * *(f32 *)(arg0 + 0x28) * scale;
    }
    if (*(f32 *)(arg0 + 0x44) != 0.0f) {
        *(f32 *)(arg0 + 0x5c) = func_15144B68(*(f32 *)(arg0 + 0x44) * D_800BE9A4 + *(f32 *)(arg0 + 0x5c));
        arg0[0x65] = *(f32 *)(arg0 + 0x5c) < 3.1415927f;
        if ((arg0[0x10] & 2) && (prevB.v[2] != arg0[0x65])) {
            *(f32 *)(arg0 + 0x44) = 0.0f;
            *(f32 *)(arg0 + 0x5c) = 0.0f;
        }
        ((f32 *)(&D_800DCDE0 + arg0[0x16] * 0x18))[5] += func_15047D60(*(f32 *)(arg0 + 0x5c)) * *(f32 *)(arg0 + 0x2c) * scale;
    }
    if (*(f32 *)(arg0 + 0x30) == 0.0f && *(f32 *)(arg0 + 0x34) == 0.0f && *(f32 *)(arg0 + 0x38) == 0.0f &&
        *(f32 *)(arg0 + 0x3C) == 0.0f && *(f32 *)(arg0 + 0x40) == 0.0f && *(f32 *)(arg0 + 0x44) == 0.0f) {
        done = 1;
    }
    if (done != 0) {
        func_1516972C(arg0);
    }
}
void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800DCDE0;

void func_15164EE4(void) {
    func_100226F0(&D_800DCDE0, 0x60);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_191C30/func_15164F0C.s")

typedef struct {
    Vec3f points[4];
    f32 firstDuration, holdDuration, secondDuration;
} Game191C30Motion;

typedef struct {
    u8 kind, flags;
    s8 mode;
    u8 pad03;
    s16 duration;
    u8 owner, pad07;
    Vec3f vectors[4];
} Game191C30Header;

typedef struct {
    Vec3f firstVelocity[4], secondVelocity[4], points[4];
    f32 firstDuration, holdDuration, secondDuration, elapsed;
} Game191C30Payload;

void *func_15164780(u8 *, s32, u8, s32);

void *func_15165628(Game191C30Motion *arg0, u8 arg1, s8 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Game191C30Header header;
    Game191C30Payload payload;
    f32 firstInverse;
    f32 secondInverse;
    void *result;

    if (!arg0->firstDuration || !arg0->secondDuration) {
        return 0;
    }
    firstInverse = 1.0f / arg0->firstDuration;
    secondInverse = 1.0f / arg0->secondDuration;
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
    payload.secondDuration = arg0->secondDuration;
    payload.elapsed = 0.0f;
    result = func_15164780((u8 *)&header, arg3 + 0xA0, (u8)arg4, arg5);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x68, &payload, 0xA0);
    }
    return result;
}
extern f32 D_800BE9A4;

typedef struct {
    u8 pad00[0x10];
    Game191C30Header header;
    u8 pad48[0x20];
    Game191C30Payload payload;
} Game191C30Object;

s32 func_151658DC(Game191C30Object *arg0) {
    s32 result = 1;
    Game191C30Payload *p = &arg0->payload;

    p->elapsed += D_800BE9A4;
    if (p->elapsed < p->firstDuration) {
        arg0->header.vectors[0].x = p->firstVelocity[0].x * p->elapsed;
        arg0->header.vectors[0].y = p->firstVelocity[0].y * p->elapsed;
        arg0->header.vectors[0].z = p->firstVelocity[0].z * p->elapsed;
        arg0->header.vectors[1].x = p->firstVelocity[1].x * p->elapsed;
        arg0->header.vectors[1].y = p->firstVelocity[1].y * p->elapsed;
        arg0->header.vectors[1].z = p->firstVelocity[1].z * p->elapsed;
        arg0->header.vectors[2].x = p->firstVelocity[2].x * p->elapsed;
        arg0->header.vectors[2].y = p->firstVelocity[2].y * p->elapsed;
        arg0->header.vectors[2].z = p->firstVelocity[2].z * p->elapsed;
        arg0->header.vectors[3].x = p->firstVelocity[3].x * p->elapsed;
        arg0->header.vectors[3].y = p->firstVelocity[3].y * p->elapsed;
        arg0->header.vectors[3].z = p->firstVelocity[3].z * p->elapsed;
    } else if (p->elapsed < p->firstDuration + p->holdDuration) {
        arg0->header.vectors[0] = p->points[0];
        arg0->header.vectors[1] = p->points[1];
        arg0->header.vectors[2] = p->points[2];
        arg0->header.vectors[3] = p->points[3];
    } else if (p->elapsed < p->firstDuration + p->holdDuration + p->secondDuration) {
        f32 t = p->elapsed - (p->firstDuration + p->holdDuration);
        arg0->header.vectors[0].x = p->points[0].x - p->secondVelocity[1].x * t;
        arg0->header.vectors[0].y = p->points[0].y - p->secondVelocity[1].y * t;
        arg0->header.vectors[0].z = p->points[0].z - p->secondVelocity[1].z * t;
        arg0->header.vectors[1].x = p->points[1].x - p->secondVelocity[0].x * t;
        arg0->header.vectors[1].y = p->points[1].y - p->secondVelocity[0].y * t;
        arg0->header.vectors[1].z = p->points[1].z - p->secondVelocity[0].z * t;
        arg0->header.vectors[2].x = p->points[2].x - p->secondVelocity[3].x * t;
        arg0->header.vectors[2].y = p->points[2].y - p->secondVelocity[3].y * t;
        arg0->header.vectors[2].z = p->points[2].z - p->secondVelocity[3].z * t;
        arg0->header.vectors[3].x = p->points[3].x - p->secondVelocity[2].x * t;
        arg0->header.vectors[3].y = p->points[3].y - p->secondVelocity[2].y * t;
        arg0->header.vectors[3].z = p->points[3].z - p->secondVelocity[2].z * t;
    } else {
        result = 0;
    }
    return result;
}
f32 func_15165BB0(void *, void *, f32, f32, f32);

void func_15165B80(u8 *arg0) {
    func_15165BB0(arg0, arg0 + 0x108, *(f32 *)((u8 *)arg0 + 0x114), *(f32 *)((u8 *)arg0 + 0x118), *(f32 *)((u8 *)arg0 + 0x11C));
}
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
