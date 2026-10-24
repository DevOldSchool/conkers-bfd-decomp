#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_11C2B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EEE00
 * - func_150EEF80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150EEF80(void *, u8, s32, s32);
extern u8 D_800A15F0[];
extern u8 D_800A1638[];
extern u8 D_800A163C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEE00 CURRENT (25) */
void func_150EEE00(void *arg0, u8 arg1) {
    typedef struct { u8 beforeFlags[0x94]; s32 flags; } ActorFlags;
    struct {
        s32 position[3];
        struct { u8 kind; s8 index; s16 life; u8 flags; } descriptor;
        f32 transformed[3];
    } work;
    u8 *state;

    state = arg0;
    if (!(D_800A163C[arg1] & ((ActorFlags *)state)->flags)) {
        func_150EEF80(arg0, arg1, 0xFF, 1);
        if (*(s32 *)(state + 0x1D4) != 0) {
            func_15143134((f32 *)&D_800A15F0[arg1 * 0xC], work.transformed,
                           (u32)*(s32 *)(state + 0x1D4) + (D_800A1638[arg1] << 6));
            work.descriptor.kind = 3;
            work.descriptor.index = -1;
            work.descriptor.life = (func_150ADA20() % 3U) + 4;
            work.descriptor.flags = 0;
            work.position[0] = (s32)work.transformed[0];
            work.position[1] = (s32)work.transformed[1];
            work.position[2] = (s32)work.transformed[2];
            func_151602C0((u8 *)&work.descriptor, work.position, 0xFF, 0xFF,
                           0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
            func_150F0A24(work.transformed);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEE00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEE00.s")
void func_151403A8(void *, u8);

void func_150EEF40(void *arg0, u8 arg1) {
    struct {
        void *field0;
        u8 field4;
        u8 field5;
    } sp18;

    sp18.field0 = arg0;
    sp18.field4 = *(u8 *)((u8 *)arg0 + 0x3B);
    sp18.field5 = arg1;
    func_151403A8(&sp18, 0x43);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF80.s")
typedef struct Game11C2B0Effect {
    u8 pad0[9];
    u8 hidden;
    u8 padA[4];
    s16 position[3];
} Game11C2B0Effect;

typedef struct Game11C2B0EffectOwner {
    u8 pad0[0x14];
    Game11C2B0Effect *sprite;
} Game11C2B0EffectOwner;

typedef struct Game11C2B0Link {
    u8 *actor;
    u8 group;
    u8 pad5[3];
    u8 *target;
    u8 targetGroup;
    u8 slot;
    u8 padE[2];
    f32 phase10;
    f32 phase14;
    u8 flags;
    u8 pad19[0x13];
    Game11C2B0EffectOwner *effect;
    Vec3f direction;
    f32 distance;
    f32 inverse;
} Game11C2B0Link;

typedef struct Game11C2B0Beam {
    u8 pad0[0x2C];
    f32 width;
    u8 pad30[4];
    Vec3f start;
    Vec3f end;
    u8 pad4C[0x10];
    u8 alpha;
    u8 pad5D[0xB3];
    Game11C2B0Link link;
} Game11C2B0Beam;

typedef struct Game11C2B0Hit {
    void *object;
    u8 pad4[0x55];
    u8 count;
    u8 pad5A[0xA];
} Game11C2B0Hit;

f32 func_15047D60(f32);
f32 func_15144B68(f32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
void func_15081690(void *, f32, f32, f32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);
s32 func_1505D024(void *, s32, s32, s32);
extern f32 D_800A181C;
extern f32 D_800A1820;
extern f32 D_800BE9A4;
extern u8 D_800CC2D0[];

s32 func_150EF38C(Game11C2B0Beam *arg0) {
    Game11C2B0Link *link;
    u8 *actor;
    u8 *target;
    s16 *position;
    Game11C2B0Hit hit;
    f32 angle;
    void *object;

    link = &arg0->link;
    actor = link->actor;
    target = link->target;
    if (link->group != actor[0x3B] || *(s32 *)actor == 0 || actor[4] == 0xFF) {
        return 0;
    }
    if (link->targetGroup != target[0x3B] || *(s32 *)target == 0) {
        return 0;
    }
    if (*(s32 *)(actor + 0x94) & D_800A163C[link->slot]) {
        return 0;
    }
    link->flags &= ~1;
    if (*(s32 *)(actor + 0x1D4) != 0) {
        func_15143134((f32 *)&D_800A15F0[link->slot * 0xC], &arg0->start.x,
                      *(s32 *)(actor + 0x1D4) + (D_800A1638[link->slot] << 6));
        arg0->end.x = ((Vec3f *)(target + 0x14))->x;
        arg0->end.y = ((Vec3f *)(target + 0x14))->y;
        arg0->end.z = ((Vec3f *)(target + 0x14))->z;
        link->direction.x = arg0->end.x - arg0->start.x;
        link->direction.y = arg0->end.y - arg0->start.y;
        link->direction.z = arg0->end.z - arg0->start.z;
        if (func_15145128(&link->direction.x, &link->direction.x, &link->distance, &link->inverse) != 0) {
            link->flags |= 1;
        }
    }
    link->phase10 += D_800A181C * D_800BE9A4;
    angle = func_15144B68(link->phase10);
    link->phase10 = angle;
    arg0->width = func_15047D60(angle) * 5.0f + 16.0f;
    link->phase14 += D_800A1820 * D_800BE9A4;
    angle = func_15144B68(link->phase14);
    link->phase14 = angle;
    arg0->alpha = func_15047D60(angle) * 25.0f + 230.0f;
    if (link->flags & 1) {
        if (link->effect != NULL) {
            link->effect->sprite->hidden = 0;
            position = link->effect->sprite->position;
            position[0] = arg0->start.x;
            position[1] = arg0->start.y;
            position[2] = arg0->start.z;
        }
        func_15081690(actor, arg0->start.x, arg0->start.y, arg0->start.z,
                      link->direction.x, link->direction.y, link->direction.z,
                      &hit, link->distance, 1, 0, 1, 4, 0, 0);
        if (hit.count >= 2) {
            object = hit.object;
            func_1502EA98(object, 0xFF, 0, 0, 0x90, 0, 1);
            func_1505D024(object, 0xA0038, 0, (actor - D_800CC2D0) / 0x32C);
        }
    } else if (link->effect != NULL) {
        link->effect->sprite->hidden = 1;
    }
    return 1;
}
s32 func_150EF784(void *arg0, s32 arg1, s32 arg2) {
    if (*(u8 *)((u8 *)arg0 + 4) == 0x28) {
        return 1;
    }
    return 0;
}
