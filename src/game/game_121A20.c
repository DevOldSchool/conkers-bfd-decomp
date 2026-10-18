#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_121A20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F4570
 * - func_150F48D0
 * - func_150F4A38
 * - func_150F4DEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game121A20NestedState {
    u8 pad0[0x24];
    u8 flags;
} Game121A20NestedState;

typedef struct Game121A20State {
    u8 pad0[0x71];
    u8 field71;
    u8 pad72[0xFE];
    Game121A20NestedState nested170;
} Game121A20State;

void *func_10022EC0(void *, const void *, u32);

typedef struct {
    f32 field00, field04, field08, field0C;
    Vec3f angles, scale, position, velocity;
    f32 field40, field44, field48, field4C;
    s32 flags;
    s16 lifetime, kind;
    u8 field58;
    u8 unknown59[3];
    s32 field5C;
    u8 field60, field61, field62, field63, field64, field65;
    u8 field66, field67, field68, field69, field6A, unknown6B;
    s32 field6C;
    u8 field70, unknown71;
    s16 field72, field74;
    u8 unknown76[2];
    s32 field78;
} Game121A20Descriptor;

typedef struct {
    f32 duration;
    Vec3f position;
    f32 angle, rate, cosine, sine, radius;
    u8 flags;
} Game121A20Motion;

f32 func_150ADA68(void);
f32 func_15047C00(f32);
f32 func_15047D60(f32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
extern f32 D_800A1A64, D_800A1A68, D_800A1A6C, D_800A1A70;
extern f32 D_800A1A74, D_800A1A78, D_800A1A7C, D_800A1A80;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4570 CURRENT (300) */
void func_150F4570(Vec3f *arg0, Vec3f *arg1, s32 arg2,
                   f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    Game121A20Descriptor descriptor;
    Vec3f direction;
    Vec3f delta;
    f32 length;
    f32 inverse;
    Game121A20Motion motion;
    s32 firstFlag;
    f32 angle;
    s32 secondFlag;
    u8 *result;

    delta.x = arg1->x - arg0->x;
    delta.y = arg1->y - arg0->y;
    delta.z = arg1->z - arg0->z;
    if (func_15145128(&delta.x, &direction.x, &length, &inverse) != 0) {
        firstFlag = ((u8 *)&arg6)[3] != 0 ? 1 : 0;
        secondFlag = arg7 != 0 ? 2 : 0;
        motion.flags = secondFlag | firstFlag;
        motion.duration = length * arg4;
        motion.position = *arg0;
        motion.angle = func_150ADA68() * D_800A1A64;
        motion.rate = func_150ADA68() * D_800A1A68 + D_800A1A6C;
        if (func_150ADA20() & 1) {
            motion.rate = -motion.rate;
        }
        motion.radius = func_150ADA68() * 21.0f + 13.0f;
        angle = func_150ADA68() * D_800A1A70;
        motion.cosine = func_15047C00(angle);
        motion.sine = func_15047D60(angle);
        descriptor.field00 = 1.0f;
        descriptor.field04 = 1.0f;
        descriptor.field0C = arg5;
        descriptor.field08 = arg5;
        descriptor.angles.x = func_150ADA68() * 360.0f;
        descriptor.angles.y = func_150ADA68() * 360.0f;
        descriptor.angles.z = func_150ADA68() * 360.0f;
        descriptor.scale.x = 1.0f;
        descriptor.scale.y = 1.0f;
        descriptor.scale.z = 1.0f;
        descriptor.position = *arg0;
        descriptor.velocity.x = direction.x * arg3;
        descriptor.velocity.y = direction.y * arg3;
        descriptor.velocity.z = direction.z * arg3;
        descriptor.field40 = func_150ADA68() * D_800A1A74 + D_800A1A78;
        descriptor.field44 = 0.0f;
        angle = func_150ADA68() * D_800A1A7C + D_800A1A80;
        descriptor.flags = 0x14900;
        descriptor.lifetime = 0x12C;
        descriptor.kind = ((u8 *)&arg2)[3];
        descriptor.field58 = 8;
        descriptor.field60 = 0xFF;
        descriptor.field61 = 0x16;
        descriptor.field48 = angle;
        descriptor.field5C = 0;
        descriptor.field62 = 7;
        descriptor.field63 = 0;
        descriptor.field64 = 0;
        descriptor.field65 = 0;
        descriptor.field66 = 0;
        descriptor.field67 = 0;
        descriptor.field68 = 2;
        *(s8 *)&descriptor.field69 = -1;
        descriptor.field6A = 2;
        descriptor.field6C = 0;
        descriptor.field70 = 0;
        descriptor.field72 = 1;
        descriptor.field74 = 0xFF;
        descriptor.field4C = 0.0f;
        descriptor.field78 = arg7;
        result = func_1513264C(&descriptor, 3, 0xFF, 0, 0x28, ((u8 *)&arg8)[3], arg9);
        if (result != NULL) {
            func_10022EC0(result + 0x170, &motion, 0x28U);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4570.s")
/* Call context: func_1514373C: unique active project prototype */
void func_1514373C(f32, f32, f32 *, f32 *);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F48D0 CURRENT (590) */
void *func_150F48D0(u8 *arg0) {
    u8 *temp_v0;
    f32 sp20;
    f32 sp1C;

    temp_v0 = (void *)(arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x170) <= 0.0f) {
        return 0;
    }
    func_1514373C(*(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0x20), &sp1C, &sp20);
    *(f32 *)((u8 *)temp_v0 + 0x10) += *(f32 *)((u8 *)temp_v0 + 0x14) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 4) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 8) += *(f32 *)((u8 *)arg0 + 0x48) * D_800BE9A4;
    *(f32 *)((u8 *)temp_v0 + 0xC) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x18) * sp1C) + *(f32 *)((u8 *)temp_v0 + 4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)temp_v0 + 8) + sp20);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC) - (*(f32 *)((u8 *)temp_v0 + 0x1C) * sp1C));
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F48D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F48D0.s")

typedef struct GameF4A38Actor {
    u8 pad0[0x38];
    Vec3f position;
    u8 pad44[0x2C];
    u8 opacity;
    u8 pad71[0x17];
    u32 sound;
    u8 pad8C[0xE4];
    Game121A20NestedState nested;
} GameF4A38Actor;

s32 func_15144B34(s32);
void func_1000F9D4(s32, s32, s32, s32);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f64 D_800A1A88, D_800A1A90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4A38 CURRENT (1667) */
s32 func_150F4A38(GameF4A38Actor *arg0) {
    f32 distance;
    Vec3f delta;
    u8 *saved;
    u8 *nested;
    Vec3f *camera;
    u32 handle;
    s32 flags;

    nested = (u8 *) &arg0->nested;
    if ((arg0->nested.flags & 1) || ((flags = nested[0x24]) & 2)) {
        saved = (u8 *) &arg0->nested;
        camera = (Vec3f *) func_15144B34(0);
        delta.x = arg0->position.x - camera->x;
        delta.y = arg0->position.y - camera->y;
        delta.z = arg0->position.z - camera->z;
        distance = func_15143E64(&delta);
        nested = saved;
        flags = nested[0x24];
    }
    if (flags & 1) {
        if (distance < 500.0f) {
            arg0->opacity = 0;
        } else if (distance < 1200.0f) {
            arg0->opacity = (u32) ((f64) (distance - 500.0f) * D_800A1A88 * D_800A1A90);
        } else {
            arg0->opacity = 255;
        }
        flags = nested[0x24];
    }
    if ((flags & 2) && !(flags & 4)) {
        handle = arg0->sound >> 16;
        if (handle != 0) {
            func_1000F9D4(handle & 0xFFFF, (s16) (s32) arg0->position.x,
                         (s16) (s32) arg0->position.y, (s16) (s32) arg0->position.z);
        } else if (distance < 200.0f) {
            handle = func_10010F88(arg0->sound & 0xFFFF,
                (u16) ((func_150ADA20() & 0x3FFF) + 0x4000), 0, 0, -1,
                (s32) arg0->position.x, (s32) arg0->position.y, (s32) arg0->position.z,
                10000, 20000);
            arg0->sound |= handle << 16;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4A38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4A38.s")


void func_150F4CFC(Game121A20State *arg0, u8 arg1, u8 arg2) {
    Game121A20NestedState *nested = &arg0->nested170;

    if (arg2 == 0x4E) {
        arg0->field71 = 0;
        nested->flags |= 5;
    } else if (arg2 == 0x4F) {
        func_1516972C((u8 *)arg0);
    }
}

void func_150F4D5C(s32 arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        s32 field_0;
        f32 field_4;
        s8 field_8;
        u8 field_9;
        u8 padA[2];
    } packet;
    u8 *temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = 0.0f;
    packet.field_8 = arg1;
    packet.field_9 = arg2;
    temp_v0 = func_15149130(0x12C, -1, 0x56, -1, 0, 0, 0xC, (s32) arg3, arg4);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
typedef struct GameF4DECState {
    u8 *owner;
    f32 pending;
    s8 callback;
    u8 group;
    u8 padA[2];
} GameF4DECState;

typedef struct GameF4DECChoices {
    u8 count;
    u8 pad1[3];
    u8 *kinds;
    f32 *scales;
} GameF4DECChoices;

void func_150F4570(Vec3f *, Vec3f *, s32, f32, f32, f32, s32, s32, s32, s32);
extern GameF4DECChoices D_80088B20[];
extern s32 (*D_80088B38[])(void);
extern f32 D_800A1A98, D_800A1A9C, D_800A1AA0, D_800A1AA4, D_800A1AA8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4DEC CURRENT (961) */
void func_150F4DEC(u8 *arg0) {
    GameF4DECChoices *choices;
    register GameF4DECState *state;
    Vec3f *camera;
    Vec3f first;
    Vec3f second;
    f32 radiusRange;
    f32 duration;
    s32 index;
    Vec3f swap;
    s16 firstAngle;
    s32 secondAngle;

    if (*(volatile s8 *)(arg0 + 0x30) != -1 && D_80088B38[*(s8 *)(arg0 + 0x30)]() == 0) return;
    state = (GameF4DECState *)(arg0 + 0x28);
    state->pending += (D_800A1A98 + func_150ADA68() * D_800A1A9C) * D_800BE9A4;
    if (state->pending > 1.0f) {
        camera = (Vec3f *)func_15144B34(state->owner[0x23D]);
        index = (s32)((*(f32 *)(state->owner + 0x380) + 180.0f) * D_800A1AA0);
        radiusRange = D_800A1AA4;
        secondAngle = (s16)(index - 0x15);
        firstAngle = index + 0x15;
        do {
            func_15143874(firstAngle, func_150ADA68() * radiusRange + 254.0f, &first.x, &first.z);
            first.y = func_150ADA68() * 212.0f + -133.0f;
            first.x += camera->x;
            first.y += camera->y;
            first.z += camera->z;
            func_15143874(((s16 *)&secondAngle)[1], func_150ADA68() * radiusRange + 254.0f, &second.x, &second.z);
            second.y = func_150ADA68() * 212.0f + -133.0f;
            second.x += camera->x;
            second.y += camera->y;
            second.z += camera->z;
            if (func_150ADA20() & 1) {
                swap = first;
                first = second;
                second = swap;
            }
            choices = &D_80088B20[state->group];
            index = ((u32)func_150ADA20() % choices->count) & 0xFF;
            duration = func_150ADA68() * 10.0f + 5.0f;
            func_150F4570(&first, &second, choices->kinds[index * 2 + 1], duration, 1.0f / duration,
                         (func_150ADA68() * D_800A1AA8 + D_800A1AA8) * choices->scales[index],
                         0, 0, arg0[0xC], arg0[1]);
            state->pending -= 1.0f;
        } while (state->pending > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4DEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4DEC.s")
