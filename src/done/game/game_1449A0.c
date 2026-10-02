#include "types.h"

/*
 * Reviewed source unit: src/game/game_1449A0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 */

f32 func_151172D8(void *, f32);                     /* extern */

void func_151174F0(f32 *arg0) {
    *arg0 = func_151172D8(arg0, *arg0);
}
typedef struct {
    s16 sound;
    u8 pad2[10];
} Game1449A0Sound;

extern Game1449A0Sound D_80089260[];
extern s32 D_800BE9E4;
f32 func_15048A70(f32, f32);
void func_15114D24(s32, s32, s32, s16, s32, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

f32 func_15117518(void *arg0, f32 current) {
    f32 velocity;
    s32 sound_index;
    f32 target;
    f32 after;
    f32 before;
    f32 rebound;
    f32 acceleration;

    rebound = *(f32 *)((u8 *)arg0 + 0x7C);
    acceleration = *(f32 *)((u8 *)arg0 + 0x80) * (f32)D_800BE9E4;
    velocity = *(f32 *)((u8 *)arg0 + 0x84);
    target = (f32)((*(s32 *)((u8 *)arg0 + 0x3C) << 22) >> 22);
    if (current == target && velocity == 0.0f) {
        goto done;
    }
    sound_index = *(s32 *)((u8 *)arg0 + 0x3C) >> 10;
    if (velocity == 0.0f && sound_index != 0 && D_80089260[sound_index].sound != 0) {
        func_15114D24((s32)arg0, D_80089260[sound_index].sound, 24000, 200, 2500, 0);
    }
    before = func_15048A70(current, target);
    current += velocity * (f32)D_800BE9E4;
    after = func_15048A70(current, target);
    if ((after <= 0.0f && before > 0.0f) || (after >= 0.0f && before < 0.0f)) {
        current = target;
        velocity = -rebound * velocity;
        after = 0;
    } else if (after > 0.0f) {
        velocity += acceleration;
    } else {
        velocity -= acceleration;
    }
    if (fabsf(after) < 2.0f && fabsf(velocity) < 1.0f) {
        current = target;
        velocity = 0.0f;
    } else if (current < 0.0f) {
        current += 360.0f;
    } else if (current >= 360.0f) {
        current -= 360.0f;
    }
    *(f32 *)((u8 *)arg0 + 0x84) = velocity;
done:
    return current;
}
f32 func_15117518(void *, f32);

void func_15117770(f32 *arg0) {
    *arg0 = func_15117518(arg0, *arg0);
}
void func_15117798(u8 *arg0) {
    *(f32 *)(arg0 + 8) = func_15117518(arg0, *(f32 *)(arg0 + 8));
}
