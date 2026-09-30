#include "types.h"

/*
 * Reviewed source unit: src/game/game_143DE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151169B4
 * - func_15116BAC
 * - func_15116D7C
 * - func_15116EA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15116930(void *arg0, void *arg1) {
    u8 flags;

    if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
        flags = *(u8 *)((u8 *)arg0 + 0x73);
        if (!(flags & 3) && !(flags & 4)) {
            if (*(u8 *)((u8 *)*(void **)((u8 *)arg1 + 0x31C) + 0x57) == 1) {
                *(u8 *)((u8 *)arg0 + 0x73) = flags & 0xFFFC;
                *(volatile u8 *)((u8 *)arg0 + 0x73) = *(u8 *)((u8 *)arg0 + 0x73) | 2;
            }
        }
    }
}

void func_151169B4(void);

void func_15116984(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x73) & 2) {
        func_151169B4();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_151169B4.s")
typedef struct Game143DE0Sound {
    s16 sound;
    u8 pad2[6];
    s16 endSound;
    s16 threshold;
} Game143DE0Sound;

extern s32 D_800BE9E4;
extern Game143DE0Sound D_80089260[];
void func_15114D24(s32, s32, s32, s16, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116BAC CURRENT (5909) */
void func_15116BAC(u8 *arg0) {
    s32 packed;
    s32 soundIndex;
    s32 rate;
    s32 maximum;
    s32 played;
    s32 step;
    s32 offset;
    s16 *current;
    s16 *previous;
    s32 *target;
    s32 desired;
    s32 distance;
    s16 value;
    s16 soundId;
    Game143DE0Sound *sound;

    packed = *(s32 *)(arg0 + 0x3C);
    soundIndex = packed >> 10;
    played = 0;
    maximum = 0;
    rate = packed & 0xFFFF03FF;
    if (soundIndex != 0 && *(u16 *)(arg0 + 0x74) == 0) {
        soundId = D_80089260[soundIndex].sound;
        if (soundId != 0) {
            func_15114D24((s32)arg0, soundId, 0x5DC0, 0x7D0, 0xFA0, 0);
            played = 1;
        }
    }
    offset = 0;
    current = (s16 *)(arg0 + 0x10);
    target = (s32 *)(arg0 + 0x7C);
    previous = (s16 *)(arg0 + 0x5A);
    step = (rate * D_800BE9E4) >> 1;
    do {
        offset += 4;
        *previous = *current;
        desired = *target;
        value = *current;
        if (value != desired) {
            if (desired < value) {
                *current = value - step;
                desired = *target;
                distance = *current - desired;
                if (distance < 0) {
                    *current = desired;
                }
            } else {
                *current = value + step;
                desired = *target;
                distance = desired - *current;
                if (distance < 0) {
                    *current = desired;
                }
            }
            if (maximum < distance) {
                maximum = distance;
            }
        }
        *previous = *current - *previous;
        current++;
        target++;
        previous++;
    } while (offset != 0xC);
    if (soundIndex != 0) {
        sound = &D_80089260[soundIndex];
        soundId = sound->endSound;
        if (soundId != 0) {
            maximum -= (sound->threshold * rate) >> 1;
            if (maximum <= 0 && (-step < maximum || played != 0)) {
                func_15114D24((s32)arg0, soundId, 0x5DC0, 0x7D0, 0xFA0, 0);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116BAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116BAC.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116D7C CURRENT (285) */
void func_15116D7C(f32 *arg0) {
    volatile f32 *var_a1;
    f32 *var_a2;
    volatile f32 *var_a3;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 rate;
    s32 var_v1;

    temp_fa1 = (f32) *(s32 *)((u8 *)arg0 + 0x3C);
    temp_fa0 = (f32) D_800BE9E4;
    rate = temp_fa0;
    temp_fv0 = temp_fa1 * 0.00390625f;
    var_a1 = (f32 *)((u8 *)arg0 + 0x60);
    var_a2 = (f32 *)((u8 *)arg0 + 0x7C);
    var_a3 = arg0;
    for (var_v1 = 0; var_v1 < 3; var_v1++) {
        temp_fa1 = var_a1[var_v1];
        temp_fa0 = var_a2[var_v1];
        if (temp_fa1 != temp_fa0) {
            if (temp_fa0 < temp_fa1) {
                var_a1[var_v1] = temp_fa1 - temp_fv0;
                temp_fa0 = var_a2[var_v1];
                temp_fa1 = var_a1[var_v1];
                if (temp_fa1 < temp_fa0) {
                    var_a1[var_v1] = temp_fa0;
                    temp_fa1 = var_a1[var_v1];
                }
            } else {
                var_a1[var_v1] = temp_fa1 + temp_fv0;
                temp_fa1 = var_a1[var_v1];
                temp_fa0 = var_a2[var_v1];
                if (temp_fa0 < temp_fa1) {
                    var_a1[var_v1] = temp_fa0;
                    temp_fa1 = var_a1[var_v1];
                }
            }
        }
        var_a3[var_v1] += temp_fa1 * rate;
        temp_fa0 = var_a3[var_v1];
        if (temp_fa0 < 0.0f) {
            var_a3[var_v1] = temp_fa0 + 360.0f;
        } else if (temp_fa0 >= 360.0f) {
            var_a3[var_v1] = temp_fa0 - 360.0f;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116D7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116D7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_15116EA4.s")
typedef struct Game143DE0Motion {
    u8 pad0[0x3C];
    s32 packedTarget;
    u8 pad40[0x3C];
    f32 damping;
    f32 acceleration;
    f32 velocity;
} Game143DE0Motion;



extern Game143DE0Sound D_80089260[];
extern f32 D_800A2FD8;
f32 func_15048A70(f32, f32);
void func_15114D24(s32, s32, s32, s16, s32, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

f32 func_151172D8(Game143DE0Motion *arg0, f32 angle) {
    f32 velocity;
    f32 delta;
    f32 target;
    f32 magnitude;
    f32 damping;
    f32 acceleration;

    damping = arg0->damping;
    acceleration = arg0->acceleration;
    velocity = arg0->velocity;
    target = (f32)((arg0->packedTarget << 22) >> 22);
    if (angle != target || velocity != 0.0f) {
        if (velocity == 0.0f && (arg0->packedTarget >> 10) != 0) {
            if (D_80089260[arg0->packedTarget >> 10].sound != 0) {
                func_15114D24((s32)arg0, D_80089260[arg0->packedTarget >> 10].sound, 0x5DC0, 0xC8, 0x9C4, 0);
            }
        }
        angle += velocity * (f32)D_800BE9E4;
        delta = func_15048A70(angle, target);
        magnitude = fabsf(delta);
        if (delta > 0.0f) {
            velocity += magnitude * acceleration;
        } else {
            velocity -= magnitude * acceleration;
        }
        velocity *= damping;
        if (fabsf(delta) < D_800A2FD8 && fabsf(velocity) < D_800A2FD8) {
            angle = target;
            velocity = 0.0f;
        } else if (angle < 0.0f) {
            angle += 360.0f;
        } else if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        arg0->velocity = velocity;
    }
    return angle;
}
