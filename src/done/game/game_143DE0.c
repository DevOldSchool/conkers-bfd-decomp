#include "types.h"

/*
 * Reviewed source unit: src/game/game_143DE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
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

void func_151169B4(void *arg0) {
    s32 step;
    s32 index;
    s32 i;
    s16 *current;
    s16 *previous;
    s32 *target;
    s16 sound;

    index = *(s32 *)((u8 *)arg0 + 0x3C) >> 10;
    if (*(s32 *)((u8 *)arg0 + 0x7C) != *(s16 *)((u8 *)arg0 + 0x10) ||
        *(s32 *)((u8 *)arg0 + 0x80) != *(s16 *)((u8 *)arg0 + 0x12) ||
        *(s32 *)((u8 *)arg0 + 0x84) != *(s16 *)((u8 *)arg0 + 0x14)) {
        if (index != 0 && D_80089268[index][0] != 0) {
            func_15116BAC(arg0);
            return;
        }
        step = *(s32 *)((u8 *)arg0 + 0x3C) & 0xFFFF03FF;
        if (index != 0 && *(u16 *)((u8 *)arg0 + 0x74) == 0) {
            sound = D_80089260[index].sound;
            if (sound != 0) {
                func_15114D24((s32)arg0, sound, 0x5DC0, 0x7D0, 0xFA0, 0);
            }
        }
        current = (s16 *)((u8 *)arg0 + 0x10);
        target = (s32 *)((u8 *)arg0 + 0x7C);
        previous = (s16 *)((u8 *)arg0 + 0x5A);
        step = (step * D_800BE9E4) >> 1;
        for (i = 0; i < 3; i++) {
            previous[i] = current[i];
            if (current[i] != target[i]) {
                if (target[i] < current[i]) {
                    current[i] -= step;
                    if (current[i] < target[i]) {
                        current[i] = target[i];
                    }
                } else {
                    current[i] += step;
                    if (target[i] < current[i]) {
                        current[i] = target[i];
                    }
                }
            }
            previous[i] = current[i] - previous[i];
        }
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x5A) = *(s16 *)((u8 *)arg0 + 0x5C) = *(s16 *)((u8 *)arg0 + 0x5E) = 0;
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

void func_15116BAC(u8 *arg0) {
    s32 rate;
    s32 step;
    s32 soundIndex;
    s16 *current;
    s32 *target;
    s16 *delta;
    s32 i;
    s32 played;
    s32 distance;
    s32 maximum;

    soundIndex = *(s32 *)(arg0 + 0x3C) >> 10;
    played = 0;
    maximum = 0;
    rate = *(s32 *)(arg0 + 0x3C) & 0xFFFF03FF;
    if (soundIndex != 0 && *(u16 *)(arg0 + 0x74) == 0 && D_80089260[soundIndex].sound != 0) {
        func_15114D24((s32)arg0, D_80089260[soundIndex].sound, 0x5DC0, 0x7D0, 0xFA0, 0);
        played = 1;
    }
    current = (s16 *)(arg0 + 0x10);
    target = (s32 *)(arg0 + 0x7C);
    delta = (s16 *)(arg0 + 0x5A);
    step = (rate * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        delta[i] = current[i];
        if (current[i] != target[i]) {
            if (target[i] < current[i]) {
                current[i] -= step;
                distance = current[i] - target[i];
                if (distance < 0) {
                    current[i] = target[i];
                }
            } else {
                current[i] += step;
                distance = target[i] - current[i];
                if (distance < 0) {
                    current[i] = target[i];
                }
            }
            if (maximum < distance) {
                maximum = distance;
            }
        }
        delta[i] = current[i] - delta[i];
    }
    if (soundIndex != 0 && D_80089260[soundIndex].endSound != 0) {
        maximum -= (D_80089260[soundIndex].threshold * rate) >> 1;
        if (maximum <= 0 && (-step < maximum || played != 0)) {
            func_15114D24((s32)arg0, D_80089260[soundIndex].endSound, 0x5DC0, 0x7D0, 0xFA0, 0);
        }
    }
}
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
typedef struct Game143DE0MorphVertex {
    s16 x;
    s16 y;
    s16 z;
    u8 unk_06[0xA];
} Game143DE0MorphVertex;

typedef struct Game143DE0Morph {
    u8 unk_00[0x10];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 unk_16[0xA];
    Game143DE0MorphVertex *vertices[2];
    u8 unk_28[0x14];
    s32 animation;
    u8 unk_40[0x3C];
    s32 target;
    s32 buffer;
    s32 current;
} Game143DE0Morph;

typedef struct Game143DE0MorphAnim {
    u8 bank;
    u8 frames;
} Game143DE0MorphAnim;

typedef struct Game143DE0RomRange {
    s32 start;
    s32 end;
} Game143DE0RomRange;

s32 func_10003C40(s32, s32, s32, s32);
void func_10004514(s32, s32, s32, s32);
extern Game143DE0RomRange D_8002AAD0[];
extern Game143DE0MorphAnim D_80089320[];
extern f32 D_800A2FD4;
extern u8 D_800BE9C0;

void func_15116EA4(Game143DE0Morph *arg0) {
    s32 size;
    u16 id;
    u8 bank;
    f32 position;
    s32 frame;
    f32 fraction;
    s32 frameSize;
    s32 count;
    s16 *from;
    s32 current;
    s16 *to;
    int frames;
    s32 step;
    s32 i;

    id = arg0->animation;
    bank = D_80089320[id].bank;
    current = arg0->current;
    frames = D_80089320[id].frames;
    size = D_8002AAD0[bank].end - D_8002AAD0[bank].start;
    step = arg0->animation >> 16;
    if (arg0->buffer == 0) {
        arg0->buffer = func_10003C40(size, 1, 2, 0);
        func_10004514(D_8002AAD0[bank].start, arg0->buffer, size, 1);
    }
    position = frames * (current * D_800A2FD4);
    frame = position;
    fraction = position - frame;
    if (frames == frame) {
        fraction = 1.0f;
        frame--;
    }
    frameSize = (size / frames) & ~1;
    count = (u32)frameSize / 6;
    from = (s16 *)(arg0->buffer + frame * frameSize);
    if (frames != frame + 1) {
        to = (s16 *)(arg0->buffer + (frame + 1) * frameSize);
    } else {
        to = from;
    }
    for (i = 0; i < count; i++) {
        arg0->vertices[D_800BE9C0][i].x = arg0->unk_10 + ((f32)from[i * 3] + ((f32)to[i * 3] - (f32)from[i * 3]) * fraction);
        arg0->vertices[D_800BE9C0][i].z = arg0->unk_12 + ((f32)from[i * 3 + 2] + ((f32)to[i * 3 + 2] - (f32)from[i * 3 + 2]) * fraction);
        arg0->vertices[D_800BE9C0][i].y = arg0->unk_14 + ((f32)from[i * 3 + 1] + ((f32)to[i * 3 + 1] - (f32)from[i * 3 + 1]) * fraction);
    }
    if (arg0->target < current) {
        current -= step;
        if (current < arg0->target) {
            current = arg0->target;
        }
    } else if (current < arg0->target) {
        current += step;
        if (arg0->target < current) {
            current = arg0->target;
        }
    }
    arg0->current = current;
}
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
