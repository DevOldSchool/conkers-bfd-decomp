#include "types.h"

/*
 * Reviewed source unit: src/game/game_EEB70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C16C0
 * - func_150C1978
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x, y, z;
    s16 life, flags;
    s32 active;
    u8 pad14, count, pad16[6];
} GameEEB70Position;

typedef struct {
    f32 first, x, y, z, second;
    u8 pad14[4], color[4], pad1C[4];
} GameEEB70Motion;

typedef struct {
    s32 zero, one, flags, kind, first, second, third;
    u8 mode, count, pad1E[2];
} GameEEB70Descriptor;

f32 func_151423D8(u8);
void *func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A01F0, D_800A01F4, D_800A01F8, D_800A01FC, D_800A0200;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C16C0 CURRENT (3154) */
s32 func_150C16C0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    GameEEB70Position position;
    GameEEB70Motion motion;
    GameEEB70Descriptor descriptor;
    f32 speed, angleSin, angleCos, directionSin, directionCos, speedRange, horizontal;
    s16 angle;
    s32 count;

    descriptor.one = 1;
    descriptor.flags = 0x160600;
    descriptor.kind = 3;
    descriptor.first = 0x10;
    count = 1;
    descriptor.zero = 0;
    descriptor.second = 0x80;
    descriptor.third = 0x20;
    descriptor.mode = 0;
    descriptor.count = 9;
    position.active = 1;
    position.flags = 1;
    motion.color[1] = 10;
    motion.color[2] = 0xFF;
    motion.color[0] = 40;
    motion.color[3] = 0xFF;
    position.x = arg2;
    position.y = arg3;
    speedRange = D_800A01F0;
    position.z = arg4;
    do {
        angle = (func_150ADA20() % 13U) - 63;
        angleSin = func_151423D8(angle & 0xFF);
        angleCos = func_151423D8((angle - 64) & 0xFF);
        directionSin = func_151423D8(arg8 & 0xFF);
        directionCos = func_151423D8((arg8 - 64) & 0xFF);
        speed = func_150ADA68() * speedRange + 25.5f;
        position.count = func_150ADA20() % 9U + 5;
        position.life = (func_150ADA20() & 0x3F) + 90;
        motion.first = func_150ADA68() * D_800A01F4 + D_800A01F8;
        motion.second = func_150ADA68() * D_800A01FC + D_800A0200;
        horizontal = speed * angleSin;
        motion.x = horizontal * directionCos;
        motion.y = -speed * angleCos;
        motion.z = horizontal * directionSin;
        func_15147DA0(&position, &motion, 0, 1, 5, 0, 0, 0, 0, 0, 0,
                      &descriptor, 0, (u8)arg14, 0);
        count--;
    } while (count != 0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C16C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEB70/func_150C16C0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1978 CURRENT (200) */
s32 func_150C1978(void *arg0) {
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    var_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v1 *= 8;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1978 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEB70/func_150C1978.s")
