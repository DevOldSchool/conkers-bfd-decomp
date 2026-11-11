#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_156160.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15128CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game156160State {
    u8 pad0[0x23D];
    u8 field_23D;
} Game156160State;

typedef struct Game156160Record {
    u8 pad0[2];
    s16 field_2;
    f32 field_4;
    f32 field_8;
    u8 padC[0x18];
} Game156160Record;

extern s16 D_80089550;
extern f32 D_800A3610;
extern Game156160Record D_800DC028[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_156160/func_15128CB0.s")

void func_151298C0(Game156160State *arg0, s32 arg1) {
    if (D_80089550 != 0) {
        D_800DC028[arg0->field_23D].field_2 = 0;
        D_800DC028[arg0->field_23D].field_4 = -1.0f;
        D_800DC028[arg0->field_23D].field_8 = D_800A3610;
    }
}
void func_15049148(void *, f32, void *);
void func_1504917C(void *, void *);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
s32 func_150A3FC4(f32, f32, s32, void *, f32 *);
void func_1510E7A4(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);
void func_151236D0(u8 *);
void func_1512C150(void *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_15129934(u8 *actor) {
    f32 x;
    f32 direction[3];
    f32 z;
    f32 y;
    f32 distance;
    f32 surface;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80089550 != 0 && *(s16 *)(actor + 0x73C) == 0) {
        *(f32 *)(actor + 0x27C) = *(f32 *)(actor + 0x288);
        *(f32 *)(actor + 0x280) = *(f32 *)(actor + 0x28C);
        *(f32 *)(actor + 0x284) = *(f32 *)(actor + 0x290);
        func_15048F90(actor + 0x27C, actor + 0x2BC, direction);
        func_1504917C(direction, direction);
        dx = *(f32 *)(actor + 0x2BC) - *(f32 *)(actor + 0x27C);
        dy = *(f32 *)(actor + 0x2C0) - *(f32 *)(actor + 0x280);
        dz = *(f32 *)(actor + 0x2C4) - *(f32 *)(actor + 0x284);
        distance = sqrtf(dx * dx + dy * dy + dz * dz);
        distance -= *(f32 *)(actor + 0x278);
        if (distance < 0.0f) distance = 0.0f;
        func_15049148(direction, distance, direction);
        x = direction[0] + *(f32 *)(actor + 0x27C);
        if (*(s32 *)(actor + 0x704) & 0xF) y = *(f32 *)(actor + 0x280);
        else y = direction[1] * 1.2f + *(f32 *)(actor + 0x280);
        z = direction[2] + *(f32 *)(actor + 0x284);
        if (actor[0x23C] != 0) {
            *(f32 *)(actor + 0x2F8) = x;
            *(f32 *)(actor + 0x304) = x;
            *(f32 *)(actor + 0x3C0) = 0;
        } else {
            func_150495B0((f32 *)(actor + 0x2F8), x, (f32 *)(actor + 0x3C0),
                         1.0f, 3.0f, *(f32 *)(actor + 0x7B4));
        }
        if (actor[0x23C] != 0) {
            *(f32 *)(actor + 0x2FC) = y;
            *(f32 *)(actor + 0x308) = y;
            *(f32 *)(actor + 0x3C4) = 0;
        } else {
            func_150495B0((f32 *)(actor + 0x2FC), y, (f32 *)(actor + 0x3C4),
                         1.0f, 2.0f, *(f32 *)(actor + 0x7B4));
        }
        if (actor[0x23C] != 0) {
            *(f32 *)(actor + 0x300) = z;
            *(f32 *)(actor + 0x30C) = z;
            *(f32 *)(actor + 0x3C8) = 0;
        } else {
            func_150495B0((f32 *)(actor + 0x300), z, (f32 *)(actor + 0x3C8),
                         1.0f, 3.0f, *(f32 *)(actor + 0x7B4));
        }
        func_1512C150(actor);
        if (actor[0x23C] != 0 || (*(u32 *)(actor + 0x84) & 0x400000U) != 0 ||
            func_150A3FC4(*(f32 *)(actor + 0x2F8), *(f32 *)(actor + 0x300),
                         *(s32 *)(actor + 0x644), actor + 0x648, (f32 *)(actor + 0x35C)) == 0) {
            func_1510E7A4(0, 0, (s32)&surface, (s32)(actor + 0x360), (s32)(actor + 0x640), 0,
                         *(f32 *)(actor + 0x2F8), *(f32 *)(actor + 0x2FC), *(f32 *)(actor + 0x300), *(f32 *)(actor + 0x2FC),
                         0, 0, -10000.0f, *(f32 *)(actor + 0x2FC));
            if (*(f32 *)(actor + 0x364) != -10000.0f) *(f32 *)(actor + 0x360) = *(f32 *)(actor + 0x364);
            func_151236D0(actor);
        }
        *(f32 *)(actor + 0x974) = 1.0f;
        *(f32 *)(actor + 0x964) = 1.0f;
        *(f32 *)(actor + 0x97C) = 1.0f;
        *(f32 *)(actor + 0x96C) = 1.0f;
        *(f32 *)(actor + 0x978) = 2.0f;
        *(f32 *)(actor + 0x968) = 2.0f;
        *(f32 *)(actor + 0x980) = 2.0f;
        *(f32 *)(actor + 0x970) = 2.0f;
    }
}
