#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D3420.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5F70
 * - func_151A6068
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151A6068(void *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5F70 CURRENT (2422) */
void func_151A5F70(void *arg0, void *arg1, u8 arg2) {
    void *sp2C;
    s32 temp_a1;
    s32 var_a0;
    s32 var_v0;
    u8 *var_v1;
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    if (arg2 == 0x35) {
        temp_a1 = *(s32 *)arg1;
        var_v0 = 0;
        var_a0 = 0;
        if (temp_a1 > 0) {
            var_v1 = *(u8 **)((u8 *)arg1 + 4);
loop_3:
            if (*(u8 *)((u8 *)arg0 + 0x2C) == *var_v1) {
                var_a0 = 1;
            } else {
                var_v0 += 1;
                var_v1 += 1;
            }
            if ((var_v0 < temp_a1) && (var_a0 == 0)) {
                goto loop_3;
            }
        }
        if (var_a0 != 0) {
            temp_v0 = (u8 *)arg0 + 0x28;
            temp_a0 = *(void **)temp_v0;
            if (*(u8 *)((u8 *)temp_a0 + 0x14) == 1) {
                temp_v1 = *(u8 *)((u8 *)temp_v0 + 0xC);
                sp2C = temp_v0;
                func_151A6068(temp_a0, *(s32 *)((u8 *)temp_v0 + 8),
                              temp_v1 & 1, temp_v1 & 2,
                              *(u8 *)((u8 *)arg0 + 0xC),
                              *(u8 *)((u8 *)arg0 + 1));
                *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x14) = 0;
                *(s32 *)((u8 *)temp_v0 + 0x10) = *(s32 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5F70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3420/func_151A5F70.s")
typedef struct Game1D3420Spawn {
    u8 kind, subtype;
    s16 flags, life;
    u8 reserved6[2];
    s32 frame, rate;
    u8 colors[4];
    f32 radius, height;
    f32 position[3], angles[3], scale[3];
    s32 options;
    u8 alpha, color, mode46, mode47;
    s32 control;
    u8 unused50, inactive51[7];
} Game1D3420Spawn;

typedef struct Game1D3420Extension {
    void *owner;
    f32 angle, velocity, scale;
    s32 light;
    u8 phase, step, brightness, enabled;
    f32 elapsed;
} Game1D3420Extension;

typedef struct Game1D3420Light {
    u8 flags, callback;
    s16 life;
    u8 kind, reserved5;
} Game1D3420Light;

void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_1516284C(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u16 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern u8 D_800A4AA0[], D_1000EF40[];
extern f32 D_800A8D98, D_800A8D9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A6068 CURRENT (5395) */
void func_151A6068(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Game1D3420Spawn spawn;
    Game1D3420Extension extension;
    Game1D3420Light light;
    s32 position[3];
    Game1D3420Extension *payload;
    void *result;
    f32 speed;

    extension.owner = arg0;
    extension.angle = 0.0f;
    extension.velocity = func_150ADA68() * 80.0f + -380.0f;
    speed = func_150ADA68() * D_800A8D98;
    extension.light = 0;
    extension.scale = speed + D_800A8D9C;
    extension.phase = func_150ADA20();
    extension.step = (func_150ADA20() & 3) + 4;
    extension.brightness = 255;
    spawn.kind = 0x6B;
    spawn.subtype = 10;
    spawn.flags = 0x4C03;
    spawn.life = 240;
    spawn.frame = 0;
    spawn.rate = 0;
    spawn.colors[0] = 255;
    spawn.colors[1] = 255;
    spawn.colors[2] = 255;
    spawn.colors[3] = 255;
    extension.elapsed = 0.0f;
    extension.enabled = arg3;
    spawn.radius = ((s16 *)arg0)[3];
    spawn.height = ((s16 *)arg0)[4];
    spawn.position[0] = ((s16 *)arg0)[0];
    spawn.position[1] = ((s16 *)arg0)[1];
    spawn.options = 0x01EC0009;
    spawn.alpha = 255;
    spawn.color = 255;
    spawn.mode46 = 0;
    spawn.mode47 = 0;
    spawn.unused50 = 255;
    spawn.position[2] = ((s16 *)arg0)[2];
    spawn.angles[0] = 0.0f;
    spawn.angles[1] = 0.0f;
    spawn.angles[2] = 0.0f;
    spawn.scale[0] = 1.0f;
    spawn.scale[1] = 1.0f;
    spawn.scale[2] = 1.0f;
    spawn.control = arg1;
    result = func_1513D2F0((s32)&spawn, (s32)D_800A4AA0,
        0, 0x28, 0, 0x20, 0, 0, 0, 0x1C, (u8)arg4, arg5);
    if (result != 0) {
        payload = (Game1D3420Extension *)((u8 *)result + 0x110);
        func_10022EC0(payload, &extension, 0x1C);
        if ((u8)arg2 != 0) {
            position[0] = ((s16 *)arg0)[0];
            position[1] = ((s16 *)arg0)[1] + (((s16 *)arg0)[4] >> 1);
            light.flags = 2;
            light.callback = 2;
            light.life = 300;
            light.kind = 6;
            position[2] = ((s16 *)arg0)[2];
            payload->light = func_1516284C(&light.flags, position,
                255, 0x79, 0, 255, 0, 0, 14, (u8)arg4, arg5);
        }
    }
    if ((u8)arg2 != 0) {
        func_1000FA64(0x1AA, ((s16 *)arg0)[0], ((s16 *)arg0)[1],
            ((s16 *)arg0)[2], 0x4000, 1000, 750, D_1000EF40,
            (s32)arg0, 0, 8, func_150ADA20() & 0x300);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A6068 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3420/func_151A6068.s")
