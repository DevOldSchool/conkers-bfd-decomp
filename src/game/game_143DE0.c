#include "types.h"

/*
 * Reviewed source unit: src/game/game_143DE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151169B4
 * - func_15116BAC
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
                *(u8 *)((u8 *)arg0 + 0x73) |= 2;
            }
        }
    }
}

void func_151169B4(void *);

void func_15116984(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x73) & 2) {
        func_151169B4(arg0);
    }
}
typedef struct Game143DE0Sound {
    s16 sound;
    u8 pad2[6];
    s16 endSound;
    s16 threshold;
} Game143DE0Sound;

extern s32 D_800BE9E4;
extern Game143DE0Sound D_80089260[];
void func_15114D24(s32, s32, s32, s16, s32, s32);

void func_15116BAC(u8 *);
extern s16 D_80089264[][6];
extern s16 D_80089268[][6];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151169B4 CURRENT (5325) */
void func_151169B4(void *arg0) {
    s32 packed;
    s32 index;
    s32 rate;
    s32 step;
    s32 offset;
    s16 *current;
    s16 *previous;
    s32 *target;
    s32 desired;
    s32 value;
    s16 sound;

    packed = *(s32 *)((u8 *)arg0 + 0x3C);
    index = packed >> 10;
    if (*(s32 *)((u8 *)arg0 + 0x7C) != *(s16 *)((u8 *)arg0 + 0x10) ||
        *(s32 *)((u8 *)arg0 + 0x80) != *(s16 *)((u8 *)arg0 + 0x12) ||
        *(s32 *)((u8 *)arg0 + 0x84) != *(s16 *)((u8 *)arg0 + 0x14)) {
        if (index != 0 && D_80089268[index][0] != 0) {
            func_15116BAC(arg0);
            return;
        }
        rate = packed & 0xFFFF03FF;
        if (index != 0 && *(u16 *)((u8 *)arg0 + 0x74) == 0) {
            sound = D_80089260[index].sound;
            if (sound != 0) {
                func_15114D24((s32)arg0, sound, 0x5DC0, 0x7D0, 0xFA0, 0);
            }
        }
        offset = 0;
        current = (s16 *)((u8 *)arg0 + 0x10);
        target = (s32 *)((u8 *)arg0 + 0x7C);
        previous = (s16 *)((u8 *)arg0 + 0x5A);
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
                    if (*current < desired) {
                        *current = desired;
                    }
                } else {
                    *current = value + step;
                    desired = *target;
                    if (desired < *current) {
                        *current = desired;
                    }
                }
            }
            *previous = *current - *previous;
            current++;
            target++;
            previous++;
        } while (offset != 0xC);
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x5E) = 0;
    value = *(s16 *)((u8 *)arg0 + 0x5E);
    *(s16 *)((u8 *)arg0 + 0x5C) = value;
    *(s16 *)((u8 *)arg0 + 0x5A) = value;
    if (*(u16 *)((u8 *)arg0 + 0x74) != 0) {
        if (index != 0) {
            sound = D_80089264[index][0];
            if (sound != 0) {
                func_15114D24((s32)arg0, sound, 0x5DC0, 0x7D0, 0xFA0, 4);
            }
        }
        *(u16 *)((u8 *)arg0 + 0x74) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151169B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143DE0/func_151169B4.s")

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

void func_15116D7C(f32 *arg0) {
    f32 step = *(s32 *)((u8 *)arg0 + 0x3C) * 0.00390625f;
    f32 rate = D_800BE9E4;
    f32 *vel = (f32 *)((u8 *)arg0 + 0x60);
    f32 *target = (f32 *)((u8 *)arg0 + 0x7C);
    f32 *rot = arg0;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (vel[i] != target[i]) {
            if (target[i] < vel[i]) {
                vel[i] -= step;
                if (vel[i] < target[i]) {
                    vel[i] = target[i];
                }
            } else {
                vel[i] += step;
                if (target[i] < vel[i]) {
                    vel[i] = target[i];
                }
            }
        }
        rot[i] += vel[i] * rate;
        if (rot[i] < 0.0f) {
            rot[i] += 360.0f;
        } else if (rot[i] >= 360.0f) {
            rot[i] -= 360.0f;
        }
    }
}
s32 func_10003C40(s32, s32, s32, s32);
void func_10004514(s32, s32, s32, s32);
extern u8 D_8002AAD0[];
extern u8 D_80089320[];
extern f32 D_800A2FD4;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116EA4 CURRENT (3253) */
void func_15116EA4(u8 *arg0) {
    s32 size;
    u8 *anim;
    s32 *rom;
    s32 current;
    s32 frames;
    s32 step;
    f32 position;
    s32 frame;
    f32 fraction;
    u32 frameSize;
    s32 count;
    s16 *from;
    s16 *to;
    s32 offset;
    s32 i;
    s32 target;

    anim = &D_80089320[(*(s32 *)(arg0 + 0x3C) & 0xFFFF) * 2];
    rom = (s32 *)&D_8002AAD0[anim[0] * 8];
    current = *(s32 *)(arg0 + 0x84);
    frames = anim[1];
    size = rom[1] - rom[0];
    step = *(s32 *)(arg0 + 0x3C) >> 16;
    if (*(s32 *)(arg0 + 0x80) == 0) {
        *(s32 *)(arg0 + 0x80) = func_10003C40(size, 1, 2, 0);
        func_10004514(rom[0], *(s32 *)(arg0 + 0x80), size, 1);
    }
    position = frames * (current * D_800A2FD4);
    frame = position;
    fraction = position - frame;
    if (frames == frame) {
        fraction = 1.0f;
        frame--;
    }
    frameSize = (size / frames) & ~1;
    count = frameSize / 6;
    from = (s16 *)(*(s32 *)(arg0 + 0x80) + frame * frameSize);
    to = from;
    if (frames != frame + 1) {
        to = (s16 *)(*(s32 *)(arg0 + 0x80) + (frame + 1) * frameSize);
    }
    offset = 0;
    for (i = 0; i < count; i++) {
        *(s16 *)(*(s32 *)(arg0 + 0x20 + D_800BE9C0 * 4) + offset + 0) = ((f32)to[0] - (f32)from[0]) * fraction + (f32)from[0] + *(s16 *)(arg0 + 0x10);
        *(s16 *)(*(s32 *)(arg0 + 0x20 + D_800BE9C0 * 4) + offset + 4) = ((f32)to[2] - (f32)from[2]) * fraction + (f32)from[2] + *(s16 *)(arg0 + 0x12);
        *(s16 *)(*(s32 *)(arg0 + 0x20 + D_800BE9C0 * 4) + offset + 2) = ((f32)to[1] - (f32)from[1]) * fraction + (f32)from[1] + *(s16 *)(arg0 + 0x14);
        offset += 0x10;
        from += 3;
        to += 3;
    }
    target = *(s32 *)(arg0 + 0x7C);
    if (target < current) {
        current -= step;
        if (current < target) {
            current = target;
        }
    } else if (current < target) {
        current += step;
        if (target < current) {
            current = target;
        }
    }
    *(s32 *)(arg0 + 0x84) = current;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116EA4 */
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
