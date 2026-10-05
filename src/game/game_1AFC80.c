#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AFC80.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151827D0
 * - func_15182C5C
 * - func_15182FDC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game362B0Sample {
    f32 component0;
    f32 component1;
    f32 component2;
} Game362B0Sample;

typedef struct Game362B0Preset {
    f32 force00;
    f32 damping04;
    f32 scale08;
    u8 unknown0C[0x8];
    s16 initial14;
    u8 unknown16;
    u8 state17;
} Game362B0Preset;

typedef struct Game1AFC80Actor {
    s32 active00;
    u8 unknown04[0x10];
    f32 x14;
    f32 y18;
    f32 z1C;
    u8 unknown20[0x64];
    u16 kind84;
    u8 unknown86[0x2A6];
} Game1AFC80Actor;

extern s8 D_800DDE50;
extern u8 D_800DDE54[];
extern Game362B0Sample *D_800DDE60[];
extern Game362B0Preset D_8008D050[];
extern Game1AFC80Actor D_800CC2D0[];
extern s32 D_800BE9E4;
s32 func_15182FDC(void *, s32, s32);
u32 func_150ADA20(void);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151827D0 CURRENT (560) */
void func_151827D0(void) {
    s32 contributions[38];
    s32 bank;
    s32 sample;
    s32 actorIndex;
    s32 contribution;
    s32 lastActor;
    s32 moving;
    s32 pass;
    s32 left;
    s32 right;
    s32 sound;
    f32 x;
    f32 y;
    f32 z;
    f32 force;
    f32 damping;
    Game1AFC80Actor *actor;

    for (bank = 0; bank < (u8)D_800DDE50; bank++) {
        lastActor = 0;
        moving = 0;
        force = D_8008D050[D_800DDE54[bank]].force00;
        damping = D_8008D050[D_800DDE54[bank]].damping04;
        for (sample = 1; sample < 39; sample++) {
            contributions[sample - 1] = 0;
            for (actorIndex = 0; actorIndex < 4; actorIndex++) {
                actor = &D_800CC2D0[actorIndex];
                if (actor->active00 != 0) {
                    contribution = func_15182FDC(actor, sample, bank);
                    if (actor->kind84 == 75) {
                        contribution *= 2;
                    }
                    contributions[sample - 1] += contribution;
                    if (contribution != 0) {
                        lastActor = actorIndex + 1;
                    }
                }
            }
        }
        for (pass = 0; pass < 3; pass++) {
            for (sample = 1; sample < 39; sample++) {
                left = (s32)(D_800DDE60[bank][sample - 1].component2 -
                             D_800DDE60[bank][sample].component2);
                right = (s32)(D_800DDE60[bank][sample + 1].component2 -
                              D_800DDE60[bank][sample].component2);
                D_800DDE60[bank][sample].component0 = (f32)(left + right) + force;
                D_800DDE60[bank][sample].component0 += (f32)contributions[sample - 1];
                D_800DDE60[bank][sample].component1 += D_800DDE60[bank][sample].component0;
                D_800DDE60[bank][sample].component1 *= damping;
                if (fabsf(D_800DDE60[bank][sample].component1) < 1.0f) {
                    D_800DDE60[bank][sample].component1 = 0.0f;
                }
            }
            for (sample = 1; sample < 39; sample++) {
                D_800DDE60[bank][sample].component2 += D_800DDE60[bank][sample].component1;
                if (lastActor != 0 && D_800DDE60[bank][sample].component1 < -30.0f) {
                    moving = 1;
                }
            }
            if (lastActor == 0) {
                D_8008D050[D_800DDE54[bank]].state17 = 0;
            }
            if (moving != 0 && D_8008D050[D_800DDE54[bank]].state17 == 0) {
                actor = &D_800CC2D0[lastActor];
                D_8008D050[D_800DDE54[bank]].state17 = (func_150ADA20() & 0x3F) + 180;
                if (D_800DDE54[bank] == 2 || D_800DDE54[bank] == 3) {
                    sound = (func_150ADA20() & 8) + 0x507;
                    x = actor[-1].x14;
                    y = actor[-1].y18;
                    z = actor[-1].z1C;
                    func_10010F88(sound, 0x5DC0U, 0, 0, 0,
                                  (s32)x, (s32)y, (s32)z, 300, 800);
                } else {
                    x = actor[-1].x14;
                    y = actor[-1].y18;
                    z = actor[-1].z1C;
                    func_10010F88(15, 0x5DC0U, 0, 0, 0,
                                  (s32)x, (s32)y, (s32)z, 300, 800);
                }
            } else if (moving == 0) {
                if (D_8008D050[D_800DDE54[bank]].state17 != 0) {
                    if (D_8008D050[D_800DDE54[bank]].state17 != 0) {
                        D_8008D050[D_800DDE54[bank]].state17 -= D_800BE9E4;
                    }
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151827D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_151827D0.s")
void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
f32 func_15182F58(s32, s32);
extern u8 D_8008D060[];
extern u8 D_8008D062[];
extern u8 D_800BE9C0;
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15182C5C CURRENT (7594) */
void func_15182C5C(u8 *object) {
    f32 matrix[16];
    struct { f32 z, y, x; } output;
    struct { f32 left, right; } weighted;
    f32 position, fraction;
    s32 index, offset, count, sample, next;
    u8 *bank;
    u8 *destination;
    u8 *cursor;
    u8 *vertex;
    Game362B0Sample **samples;
    Game362B0Sample *table;

    index = *(s32 *)(object + 0x3C);
    bank = D_800DDE54 + index;
    destination = *(u8 **)(object + D_800BE9C0 * 4 + 0x20);
    func_150A8050(matrix, 0.0f,
                 (f32)-*(s16 *)(D_8008D060 + *bank * 0x18), 0.0f);
    count = 0;
    offset = 0;
    if (*(u16 *)((u32)D_800DBEF4 +
        *(s16 *)(D_8008D062 + *bank * 0x18) * 0xA0 + 0x16) > 0) {
        cursor = destination;
        samples = D_800DDE60 + index;
        do {
            position = func_15182F58(*(s16 *)(*(u8 **)(object + 0x28) + offset + 4), index);
            sample = (s32)position;
            next = sample + 1;
            if (next >= 40) next = 39;
            table = *samples;
            fraction = position - (f32)sample;
            weighted.left = table[sample].component2 * (1.0f - fraction);
            weighted.right = table[next].component2 * fraction;
            vertex = *(u8 **)(object + 0x28) + offset;
            func_150A7960(matrix, (f32)*(s16 *)vertex,
                         (f32)(*(s16 *)(vertex + 2) + ((s32)(weighted.right + weighted.left) >> 4)),
                         (f32)*(s16 *)(vertex + 4), &output.x, &output.y, &output.z);
            count++;
            offset += 0x10;
            cursor += 0x10;
            *(s16 *)(cursor - 0x10) = (s32)((f32)*(s16 *)(object + 0x10) + output.x);
            *(s16 *)(cursor - 0xE) = (s32)((f32)*(s16 *)(object + 0x12) + output.y);
            *(s16 *)(cursor - 0xC) = (s32)((f32)*(s16 *)(object + 0x14) + output.z);
        } while (count < *(u16 *)((u32)D_800DBEF4 +
                 *(s16 *)(D_8008D062 + *bank * 0x18) * 0xA0 + 0x16));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15182C5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182C5C.s")

f32 func_15182F58(s32 arg0, s32 arg1) {
    f32 var_fv1;

    var_fv1 = D_8008D050[D_800DDE54[arg1]].scale08 * (f32)(arg0 * 0x28);
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    } else if (var_fv1 > 39.0f) {
        var_fv1 = 39.0f;
    }
    return var_fv1;
}
typedef struct {
    u8 pad00[0x10];
    s16 x, y, z;
    u8 pad16[0x8A];
} Game1AFC80Placement;

typedef struct {
    s8 value;
    u8 pad01[0x17];
} Game1AFC80Contribution;

extern Game1AFC80Contribution D_8008D066[];
extern s32 D_800DBEF4;
void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15182FDC CURRENT (4870) */
s32 func_15182FDC(void *arg0, s32 arg1, s32 arg2) {
    f32 deltaX, deltaZ;
    f32 localX, localY, localZ;
    f32 matrix[4][4];
    f32 mappedZ, mappedX;
    u8 *bank;
    Game362B0Preset *preset;
    Game1AFC80Placement *placement;
    f32 originX, originY, originZ;
    f32 actorY;
    s32 sample;
    s32 contribution;

    bank = &D_800DDE54[arg2];
    if (*(f32 *)((u8 *)arg0 + 0x28) > 3.0f) {
        return 0;
    }
    preset = &D_8008D050[*bank];
    placement = (Game1AFC80Placement *)(D_800DBEF4 +
                 ((s16 *)preset->unknown0C)[3] * 0xA0);
    originX = (f32)placement->x;
    originY = D_800DDE60[arg2][arg1].component2 * 0.0625f + (f32)placement->y;
    originZ = (f32)placement->z;
    actorY = ((Game1AFC80Actor *)arg0)->y18;
    if (actorY < originY - 300.0f || originY + 300.0f < actorY) {
        return 0;
    }
    deltaX = ((Game1AFC80Actor *)arg0)->x14 - originX;
    deltaZ = ((Game1AFC80Actor *)arg0)->z1C - originZ;
    func_150A8050(matrix, 0.0f, (f32)((s16 *)preset->unknown0C)[2], 0.0f);
    func_150A7960(matrix, deltaX, 0.0f, deltaZ, &localX, &localY, &localZ);
    mappedZ = localZ;
    if (mappedZ > 0.0f ||
        (preset = &D_8008D050[*bank], mappedX = localX, mappedZ < (f32)((s16 *)preset->unknown0C)[0]) ||
        mappedX < 0.0f || (f32)((s16 *)preset->unknown0C)[1] < mappedX) {
        return 0;
    }
    sample = (s32)func_15182F58((s32)mappedZ, arg2);
    contribution = D_8008D066[*bank].value;
    if (arg1 == sample) {
        return contribution;
    }
    if (arg1 == sample + 1 || arg1 + 1 == sample) {
        return contribution * 4 / 7;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15182FDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182FDC.s")
