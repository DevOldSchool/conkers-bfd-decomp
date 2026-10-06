#include "types.h"

/*
 * Reviewed source unit: src/game/game_123FB0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F6B00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x1CA];
    u8 enabled;
} Game123FB0Child;

typedef struct {
    u8 pad0[0x84];
    u32 flags;
    u8 pad88[0x21C];
    f32 position[3];
    u8 pad2B0[0xC4];
    f32 speed;
    u8 pad378[4];
    f32 angle;
    u8 pad380[0x1C];
    f32 scaledAngle;
    u8 pad3A0[0x30];
    Game123FB0Child *child;
    u8 pad3D4[0x3E0];
    f32 turnRate;
    u8 pad7B8[0x10];
    f32 turnState;
} Game123FB0Actor;

void func_15048F90(void *, void *, void *);
void func_1504917C(void *, void *);
void func_15049688(void *, f32, void *, f32, f32, f32);
f32 func_150AD900(f32 *, f32 *);
f32 func_150AD930(void *);
f32 func_15048FC8(f32 *);
s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, ...);
extern f32 D_800A1B80[3], D_800A1B8C[3], D_800D9A50[3];
extern f32 D_800A1B98, D_800A1B9C, D_800A1BA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F6B00 CURRENT (1672) */
void func_150F6B00(Game123FB0Actor *actor) {
    f32 normalized[3];
    f32 offset[3];
    f32 direction[3];
    f32 blend;
    f32 inverseLength;
    f32 lateral;
    f32 lower;
    f32 upper;
    f32 vertical;
    f32 projection;
    f32 clamped;

    if (func_1509BE40(1, 0x4003, 6, 0x2000) && actor->child->enabled) {
        actor->flags |= 0xC0001000;
        func_15048F90(D_800A1B80, actor->position, offset);
        func_15048F90(D_800A1B80, D_800A1B8C, direction);
        inverseLength = 1.0f / func_150AD930(direction);
        func_1504917C(direction, normalized);
        lower = 0.0f;
        projection = func_150AD900(normalized, offset) * inverseLength * 0.75f;
        if (projection < lower) {
            blend = lower;
        } else {
            upper = 1.0f;
            if (projection > upper) {
                clamped = upper;
            } else {
                clamped = projection;
            }
            blend = clamped;
        }
        if (func_1509BE40(4, 0x2000, 0xAC, 0x4040, 0x4041, 0x4042, 0x4043)) {
            lower = 0.0f;
            actor->speed = 220.0f;
            lateral = lower * blend + -900.0f;
        } else if (func_1509BE40(4, 0x2000, 0xAC, 0x4047, 0x4046, 0x4045, 0x4044)) {
            lower = 0.0f;
            actor->speed = 220.0f;
            lateral = lower * blend + 900.0f;
        } else {
            lower = 0.0f;
            lateral = lower * blend;
            actor->speed = 294.0f;
        }
        vertical = -20.0f;
        func_1509BFB0(3, 0x4003, 3, (s32) lateral, (s32) vertical,
                      (s32) (D_800A1B98 * blend + D_800A1B9C));
        func_15049688(&actor->angle, func_15048FC8(D_800D9A50) - 180.0f,
                      &actor->turnState, 8.0f, 10.0f, actor->turnRate);
        actor->scaledAngle = actor->angle * D_800A1BA0;
        return;
    }
    actor->flags &= 0x3FFFEFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F6B00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_123FB0/func_150F6B00.s")
