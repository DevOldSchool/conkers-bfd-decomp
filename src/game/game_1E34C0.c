#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E34C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B6010
 * - func_151B6254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 x, y, z;
} Game1B6010Vector;

typedef struct {
    f32 field0, field4, field8, fieldC;
    Game1B6010Vector rotation, scale, position, velocity, acceleration;
    f32 field4C;
    u32 flags;
    s16 lifetime;
    u16 resource;
    u8 field58, pad59[3];
    s32 field5C;
    u8 field60, field61, field62, field63, field64, field65, field66, field67;
    u8 field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 step;
    u16 rate;
    u8 tail76[6];
} Game1B6010Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800AA450;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B6010 CURRENT (490) */
void *func_151B6010(Game1B6010Vector *arg0, Game1B6010Vector *arg1,
                   f32 arg2, Game1B6010Vector *arg3, Game1B6010Vector *arg4,
                   f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                   u8 arg10, u8 arg11, u8 arg12, s32 arg13) {
    void *result;
    Game1B6010Spawn spawn;
    f32 extra[2];
    s32 step;

    extra[1] = arg2;
    extra[0] = 0.0f;
    spawn.fieldC = arg2;
    spawn.field8 = arg2;
    spawn.field0 = D_800AA450 * arg2;
    spawn.field4 = arg9;
    spawn.rotation = *arg3;
    spawn.scale.x = 1.0f;
    spawn.scale.y = 1.0f;
    spawn.scale.z = 1.0f;
    spawn.position = *arg0;
    spawn.flags = 0x3900;
    spawn.field4C = arg5;
    if (arg6 == -1) {
        spawn.lifetime = 300;
        step = 0x100 >> arg10;
    } else {
        spawn.lifetime = (step = 0x100 >> arg10) + arg6;
        spawn.flags = 0x3980;
    }
    if (arg1 != 0) {
        spawn.velocity = *arg1;
        spawn.flags |= 0x20;
    } else {
        spawn.velocity.x = 0.0f;
        spawn.velocity.y = 0.0f;
        spawn.velocity.z = 0.0f;
    }
    if (arg4 != 0) {
        spawn.acceleration = *arg4;
        spawn.flags |= 0x40;
    } else {
        spawn.acceleration.x = 0.0f;
        spawn.acceleration.y = 0.0f;
        spawn.acceleration.z = 0.0f;
    }
    if (arg11 != 0) {
        spawn.flags |= 1;
    }
    spawn.resource = 3;
    spawn.field58 = 0;
    spawn.field5C = 0;
    spawn.field61 = 6;
    spawn.field62 = 0;
    spawn.field63 = 6;
    spawn.field64 = 0;
    spawn.field65 = 0;
    spawn.field66 = 0;
    spawn.field67 = 0;
    spawn.field68 = 2;
    spawn.field6A = 0;
    spawn.field6C = 0;
    spawn.field70 = 0;
    spawn.step = step;
    spawn.rate = 0xFF / step;
    spawn.field60 = arg7;
    result = func_15132A4C(&spawn, 3, 0xFF, 8, arg12, arg13);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, extra, sizeof(extra));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B6010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E34C0/func_151B6010.s")
f32 func_15047D60(f32);
void func_15133894(void *);
extern f32 D_800AA454;
extern f32 D_800AA458;
extern f32 D_800AA45C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B6254 CURRENT (469) */
void func_151B6254(u8 *arg0) {
    f32 *angle;
    f32 value;
    f32 wave;
    f32 wrap;

    wrap = D_800AA454;
    angle = (f32 *)(arg0 + 0x170);
    *angle += D_800AA458 * D_800BE9A4;
    while (wrap < *angle) {
        *angle -= wrap;
    }
    wave = func_15047D60(*angle);
    value = angle[1];
    value += wave * (D_800AA45C * value);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = value;
    func_15133894(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B6254 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E34C0/func_151B6254.s")
