#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_122B60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F5A54
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F631C(u8 *arg0);
void *func_10022EC0(void *, const void *, u32);

typedef struct Game122B60TextureAttachment {
    u8 unknown00[0x18];
    s16 texture18;
} Game122B60TextureAttachment;

typedef struct Game122B60AnimationPrefix {
    u8 unknown00[8];
    f32 phase08;
} Game122B60AnimationPrefix;

typedef struct Game122B60ActorPrefix {
    u8 unknown00[0x84];
    u16 state84;
    u8 unknown86[0x24A];
    Game122B60AnimationPrefix *animation2D0;
} Game122B60ActorPrefix;

/* Existing ROM symbols only. No array capacity or new alias symbol is claimed. */
extern s32 D_80090274[];
extern f32 D_800A1B3C;
extern f32 D_800A1B40;
extern f32 D_800A1B44;
extern f32 D_800A1B48;
extern f32 D_800A1B4C;

s32 func_150F56B0(Game122B60TextureAttachment *attachment,
                  Game122B60ActorPrefix *actor) {
    Game122B60AnimationPrefix *animation;
    f32 weight;
    s32 frame;

    animation = actor->animation2D0;
    if (animation == 0) {
        return 0;
    }
    frame = 6;
    if (actor->state84 == 0xAE) {
        if ((36.0f <= animation->phase08) && (animation->phase08 <= 51.0f)) {
            weight = animation->phase08 - 36.0f;
            weight *= 0.0625f;
            weight = 1.0f - weight;
            frame = (s32)(6 * weight);
        } else if ((51.0f < animation->phase08) && (animation->phase08 <= 54.0f)) {
            frame = 0;
        } else if ((54.0f < animation->phase08) && (animation->phase08 <= 60.0f)) {
            weight = animation->phase08 - 54.0f;
            weight *= D_800A1B3C;
            frame = (s32)(6 * weight);
        } else if ((60.0f < animation->phase08) && (animation->phase08 <= 65.0f)) {
            weight = animation->phase08 - 60.0f;
            weight *= D_800A1B40;
            frame = (s32)(2 * weight) + 7;
        } else if ((65.0f < animation->phase08) && (animation->phase08 <= 67.0f)) {
            weight = animation->phase08 - 65.0f;
            weight *= D_800A1B44;
            weight = 1.0f - weight;
            frame = (s32)(2 * weight) + 7;
        } else if ((67.0f < animation->phase08) && (animation->phase08 <= 70.0f)) {
            weight = animation->phase08 - 67.0f;
            weight *= 0.25f;
            weight = 1.0f - weight;
            frame = (s32)(2 * weight) + 4;
        } else if ((70.0f < animation->phase08) && (animation->phase08 <= 74.0f)) {
            weight = animation->phase08 - 70.0f;
            weight *= D_800A1B48;
            frame = (s32)(2 * weight) + 4;
        } else if ((74.0f < animation->phase08) && (animation->phase08 <= 119.0f)) {
            weight = animation->phase08 - 74.0f;
            weight *= D_800A1B4C;
            frame = (s32)(2 * weight) + 7;
        } else if ((119.0f < animation->phase08) && (animation->phase08 <= 150.0f)) {
            weight = animation->phase08 - 119.0f;
            weight *= 0.03125f;
            weight = 1.0f - weight;
            frame = (s32)(2 * weight) + 7;
        }
    }
    attachment->texture18 = D_80090274[frame];
    return 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F5A54 CURRENT (3690) */
s32 func_150F5A54(u8 *arg0, u8 *arg1) {
    u8 *actor;
    s32 entries;
    s32 mode;
    s32 index;
    s32 remaining;
    s32 flag;
    s32 value;
    f32 weight;
    f32 savedWeight;
    f32 distance;

    actor = *(u8 **)(arg1 + 0x2D0);
    remaining = 1;
    if (actor == 0) {
        return 0;
    }
    mode = *(s32 *)(arg0 + 0x38);
    flag = 0;
    entries = *(s32 *)(*(u8 **)(arg0 + 0x24));
    if (mode != 0) {
        if (mode != 1) {
            weight = savedWeight;
            if (mode == 2) {
                weight = 0.0f;
            }
        } else {
            weight = 1.0f;
        }
    } else {
        if (*(u16 *)(arg1 + 0x84) == 5) {
            *(s32 *)(arg0 + 0x38) = 1;
            savedWeight = 1.0f;
        } else {
            flag = 1;
        }
        weight = savedWeight;
    }
    if (*(u16 *)(arg1 + 0x84) == 5) {
        distance = *(f32 *)(actor + 8);
        if (distance < 69.0f) {
            weight = 1.0f;
        } else if (distance > 84.0f) {
            weight = 0.0f;
            *(s32 *)(arg0 + 0x38) = 2;
        } else {
            weight = 1.0f - ((distance - 69.0f) / 15.0f);
        }
    }
    index = 0;
    do {
        remaining -= 1;
        if (*(s8 *)(entries + index * 8) != -14) {
            do {
                index += 1;
            } while (*(s8 *)(entries + index * 8) != -14);
        }
        if (remaining != 0) {
            index += 1;
        }
    } while (remaining != 0);
    if (flag != 0) {
        value = 2;
    } else {
        value = (s32)((58.0f * weight) + 44.0f);
    }
    *(s32 *)(entries + index * 8) = (value & 0xFFF) | 0xF2002000;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F5A54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5A54.s")
void func_150F5C08(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *field_0;
        u8 field_4;
        u8 pad5[3];
        f32 field_8;
    } packet;
    u8 *temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, 0xC, (s32) arg2, arg3);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, (void **)&packet, 0xC);
    }
}
typedef struct Game122B60SparkPacket {
    s32 config;
    s32 mode;
    s16 kind;
    s16 lifetime;
    s32 field_C;
    s32 field_10;
    u8 colors[10];
    s16 field_1E;
    s16 field_20;
    s16 field_22;
    f32 scale;
    f32 width;
    f32 height;
    Vec3f position;
    Vec3f vector1;
    Vec3f vector2;
    f32 field_54;
    s32 flags;
    s32 field_5C;
    s8 bytes[6];
    u8 byte66;
    u8 pad67;
    s16 field_68;
    u8 pad6A[2];
    f32 field_6C;
} Game122B60SparkPacket;

f32 func_150ADA68(void);
extern u8 D_800A1B00[];
extern u8 D_800A1B0C[];
extern f32 D_800A1B50;
extern f32 D_800A1B54;
extern f32 D_800A1B58;
extern f32 D_800A1B5C;
extern Vec3f D_800A5480;
extern f32 D_800BE9A4;
void func_15145EA4(s32 *, s32 *, s32, s32);

void func_150F5C98(u8 *arg0) {
    u8 *state;
    u8 *actor;
    Game122B60SparkPacket packet;
    f32 tail;
    Vec3f start;
    Vec3f end;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 *sources[2];
    Vec3f *targets[2];
    f32 scale;
    f32 t;
    s32 n;
    s32 flags2;
    s32 flags1;
    void *result;

    state = arg0 + 0x28;
    actor = *(u8 **)state;
    if (*(s32 *)actor == 0 || state[4] != actor[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(actor + 0x1D4) != 0) {
        *(f32 *)(state + 8) += (D_800A1B50 + func_150ADA68() * D_800A1B54) * D_800BE9A4;
        if (*(f32 *)(state + 8) > 1.0f) {
            packet.colors[0] = 0xFF;
            packet.colors[1] = 0xFF;
            packet.colors[2] = 0xFF;
            packet.colors[4] = 0xB4;
            packet.colors[5] = 0xB4;
            packet.colors[6] = 0xB4;
            sources[0] = D_800A1B00;
            sources[1] = D_800A1B0C;
            targets[0] = &start;
            targets[1] = &end;
            func_15145EA4((s32 *)sources, (s32 *)targets, *(s32 *)(actor + 0x1D4) + 0x140, 2);
            packet.colors[9] = 0x6C;
            packet.kind = 0x5103;
            packet.config = 0x200005;
            packet.mode = 0x9F0600;
            packet.field_C = 0;
            packet.field_10 = 0;
            packet.colors[3] = 0xFF;
            packet.colors[8] = 0xFF;
            dx = end.x - start.x;
            dy = end.y - start.y;
            dz = end.z - start.z;
            packet.vector1 = D_800A5480;
            packet.flags = 0x84CE07;
            packet.bytes[0] = 8;
            packet.bytes[1] = 6;
            packet.bytes[2] = 0x10;
            packet.bytes[3] = -1;
            packet.bytes[4] = -1;
            packet.bytes[5] = 0;
            packet.field_5C = 0;
            packet.byte66 = 0xFF;
            packet.field_68 = 1000;
            packet.field_6C = 1000.0f;
            tail = D_800A1B58;
            packet.scale = D_800A1B5C;
            do {
                n = (s16)(func_150ADA20() % 21U + 20);
                packet.field_22 = n;
                packet.field_1E = n;
                packet.field_20 = 255 / n;
                packet.lifetime = n;
                packet.colors[7] = func_150ADA20() % 26U + 8;
                packet.width = packet.height = func_150ADA68() * 70.0f + 148.0f;
                packet.field_54 = func_150ADA68() * 0.21900001f + 0.086f;
                scale = func_150ADA68() * 0.041f + 0.078f;
                packet.vector2.x = dx * scale;
                packet.vector2.y = dy * scale;
                packet.vector2.z = dz * scale;
                t = func_150ADA68() * D_800BE9A4;
                packet.flags &= ~0xC0;
                packet.position.x = packet.vector2.x * t + start.x;
                packet.position.y = packet.vector2.y * t + start.y;
                packet.position.z = packet.vector2.z * t + start.z;
                if (func_150ADA20() & 1) {
                    flags2 = 0x80;
                } else {
                    flags2 = 0;
                }
                if (func_150ADA20() & 1) {
                    flags1 = 0x40;
                } else {
                    flags1 = 0;
                }
                packet.flags |= (u32)(flags1 | flags2);
                result = func_15130280(&packet, 1, NULL, 4, arg0[0xC], arg0[1]);
                if (result != NULL) {
                    func_10022EC0((u8 *)result + 0xA8, &tail, 4);
                }
                *(f32 *)(state + 8) -= 1.0f;
            } while (*(f32 *)(state + 8) > 1.0f);
        }
    }
}
extern void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_15145EA4(s32 *, s32 *, s32, s32);
extern u8 D_800A1B18[];
extern u8 D_800A1B24[];

typedef struct Game122B60Vec3Bits {
    u32 words[3];
} Game122B60Vec3Bits;

void func_150F6178(u8 *arg0) {
    u8 *actor;
    u8 *entry;
    f32 vector0[3];
    f32 vector1[3];
    u8 *source[2];
    f32 *target[2];
    u8 *link;
    u8 *sub;
    u8 *link2;
    u8 *object2;
    u8 *sub2;

    entry = arg0 + 0x28;
    actor = *(u8 **)entry;
    if (*(s32 *)actor == 0 || entry[4] != actor[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(actor + 0x1D4) != 0 && !(*(s32 *)(actor + 0x94) & 2)) {
        source[0] = D_800A1B18;
        source[1] = D_800A1B24;
        target[0] = vector0;
        target[1] = vector1;
        func_15145EA4((s32 *)source, (s32 *)target, *(s32 *)(actor + 0x1D4), 2);
        link = *(u8 **)(entry + 8);
        if (link != 0) {
            link[0x168] |= 1;
            *(Game122B60Vec3Bits *)(link + 0x34) = *(Game122B60Vec3Bits *)vector0;
            *(Game122B60Vec3Bits *)(link + 0x40) = *(Game122B60Vec3Bits *)vector1;
        }
        link = *(u8 **)(entry + 0xC);
        if (link != 0) {
            u8 *object = *(u8 **)(link + 0x14);
            object[9] = 0;
            *(s16 *)(object + 0xE) = (s32)vector0[0];
            *(s16 *)(object + 0x10) = (s32)vector0[1];
            *(s16 *)(object + 0x12) = (s32)vector0[2];
        }
    } else {
        if (*(u8 **)(entry + 8) != 0) {
            sub = *(u8 **)(entry + 8) + 0x110;
            sub[0x58] &= ~1;
        }
        link2 = *(u8 **)(entry + 0xC);
        if (link2 != 0) {
            object2 = *(u8 **)(link2 + 0x14);
            object2[9] = 1;
        }
    }
    if (*(u8 **)(entry + 8) != 0) {
        sub2 = *(u8 **)(entry + 8) + 0x110;
        *(f32 *)(sub2 + 0x48) = 4.0f;
        *(f32 *)(sub2 + 0x4C) = 8.0f;
    }
}
void func_150F631C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x30) != 0) {
        func_1516972C(*(void **)(arg0 + 0x30));
    }
    if (*(void **)(arg0 + 0x34) != 0) {
        func_1516972C(*(void **)(arg0 + 0x34));
    }
}
void func_150F6368(void *arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}
void func_150F6394(void *arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}
