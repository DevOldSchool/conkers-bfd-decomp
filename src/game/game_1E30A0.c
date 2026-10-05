#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E30A0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5BF0
 * - func_151B5E94
 * - func_151B5FCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1E30A0Vector { f32 x, y, z; } Game1E30A0Vector;
typedef struct Game1E30A0Spawn {
    f32 field0, field4, field8, fieldC;
    Game1E30A0Vector rotation, scale, position, velocity, acceleration;
    f32 field4C;
    s32 flags;
    s16 lifetime, resource;
    u8 field58;
    u8 pad59[3];
    s32 field5C;
    u8 field60, field61, field62, field63, field64, field65, field66, field67, field68;
    u8 pad69;
    u8 field6A;
    u8 pad6B;
    s32 field6C;
    u8 field70;
    u8 pad71;
    s16 step, rate;
} Game1E30A0Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_15002FB4(s32);
void D_1500310C(void);
extern s8 D_8008FDA8;
extern f32 D_800AA430;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5BF0 CURRENT (3080) */
void *func_151B5BF0(Game1E30A0Vector *arg0, Game1E30A0Vector *arg1,
    f32 arg2, Game1E30A0Vector *arg3, Game1E30A0Vector *arg4,
    f32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9,
    s32 arg10, s32 arg11, s32 arg12, s32 arg13) {
    void *result;
    struct { f32 extra[2]; Game1E30A0Spawn spawn; } work;
    s32 step;
    s32 duration;
    u32 checksum;
    u32 *cursor;
    u32 word;

    work.extra[1] = arg2;
    work.extra[0] = 0.0f;
    work.spawn.fieldC = arg2;
    work.spawn.field8 = arg2;
    work.spawn.field4 = arg9;
    work.spawn.field0 = D_800AA430 * arg2;
    work.spawn.rotation = *arg3;
    checksum = 0;
    work.spawn.scale.x = 1.0f;
    work.spawn.scale.y = 1.0f;
    work.spawn.scale.z = 1.0f;
    work.spawn.position = *arg0;
    work.spawn.flags = 0xB908;
    work.spawn.field4C = arg5;
    duration = (s16)arg6;
    if (duration == -1) {
        work.spawn.lifetime = 300;
        step = 0x100 >> ((u8 *)&arg10)[3];
    } else {
        work.spawn.flags = 0xB988;
        step = 0x100 >> ((u8 *)&arg10)[3];
        work.spawn.lifetime = duration + step;
    }
    if (arg1 != 0) {
        work.spawn.velocity = *arg1;
        work.spawn.flags |= 0x20;
    } else {
        work.spawn.velocity.x = 0.0f;
        work.spawn.velocity.y = 0.0f;
        work.spawn.velocity.z = 0.0f;
    }
    cursor = (u32 *)func_15002FB4;
    if ((u32)cursor < (u32)D_1500310C) {
        do {
            word = *cursor;
            cursor++;
            checksum = (checksum + word) << 1;
        } while ((u32)cursor < (u32)D_1500310C);
    }
    if (checksum != 0x80D2D760U) {
        D_8008FDA8 = -1;
    }
    if (arg4 != 0) {
        work.spawn.acceleration = *arg4;
        work.spawn.flags |= 0x40;
    } else {
        work.spawn.acceleration.x = 0.0f;
        work.spawn.acceleration.y = 0.0f;
        work.spawn.acceleration.z = 0.0f;
    }
    if (((u8 *)&arg11)[3] != 0) {
        work.spawn.flags |= 1;
    }
    work.spawn.resource = 2;
    work.spawn.field60 = ((u8 *)&arg7)[3];
    work.spawn.field58 = 0;
    work.spawn.field5C = 0;
    work.spawn.field61 = 5;
    work.spawn.field62 = 0;
    work.spawn.field63 = 6;
    work.spawn.field64 = 0;
    work.spawn.field65 = 0;
    work.spawn.field66 = 2;
    work.spawn.field67 = 0;
    work.spawn.field68 = 2;
    work.spawn.field6A = 0;
    work.spawn.field6C = 0;
    work.spawn.field70 = 0;
    work.spawn.step = step;
    work.spawn.rate = 0xFF / step;
    result = func_15132A4C(&work.spawn, 3, 0xFF, 8, ((u8 *)&arg12)[3], arg13);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, work.extra, sizeof(work.extra));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5BF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5BF0.s")

void func_151B5E8C(void) {

}
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_15047D60(f32);
void func_15133894(void *);
extern f32 D_800AA434;
extern f32 D_800AA438;
extern f32 D_800AA43C;
extern f32 D_800AA440;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5E94 CURRENT (675) */
void func_151B5E94(void *arg0) {
    f32 *values;
    f32 value;

    *(f32 *)((u8 *)arg0 + 0x170) += D_800AA434 * D_800BE9A4;
    if (*(volatile f32 *)((u8 *)arg0 + 0x170) > D_800AA438) {
        *(f32 *)((u8 *)arg0 + 0x170) = 0.0f;
        func_10010F88(0x502, 0x5DC0U, 0, 0, -1,
                      (s32)*(f32 *)((u8 *)arg0 + 0x38),
                      (s32)*(f32 *)((u8 *)arg0 + 0x3C),
                      (s32)*(f32 *)((u8 *)arg0 + 0x40), 0x64, 0x1F4);
    }
    values = (f32 *)((u8 *)arg0 + 0x170);
    if (values[0] < D_800AA43C) {
        value = values[1] +
                (func_15047D60(values[0]) * (D_800AA440 * values[1]));
        *(f32 *)((u8 *)arg0 + 0x1C) = value;
        *(f32 *)((u8 *)arg0 + 0x18) = value;
    } else {
        value = values[1];
        *(f32 *)((u8 *)arg0 + 0x1C) = value;
        *(f32 *)((u8 *)arg0 + 0x18) = value;
    }
    func_15133894(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5E94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5E94.s")
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5FCC CURRENT (300) */
void func_151B5FCC(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0 & 0xFFFF, arg0);
        *(s32 *)((u8 *)arg0 + 0x88) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5FCC.s")
