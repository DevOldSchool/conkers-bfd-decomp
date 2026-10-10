#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_142560.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151152A8
 * - func_15115368
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151150B0(s32 arg0) {

}
extern s32 D_800BE9E4;

typedef struct Game142560Rotation {
    f32 angleX;
    f32 angleY;
    f32 angleZ;
    u8 pad0C[0x30];
    s32 packedSpeed;
    u8 pad40[0x20];
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
} Game142560Rotation;

void func_151150BC(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaZ = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleZ = arg0->angleZ + arg0->deltaZ;
    angle = arg0->angleZ;
    if (angle < 0.0f) {
        arg0->angleZ = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleZ = angle - full_turn;
    }
}

void func_1511515C(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaY = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleY = arg0->angleY + arg0->deltaY;
    angle = arg0->angleY;
    if (angle < 0.0f) {
        arg0->angleY = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleY = angle - full_turn;
    }
}

void func_151151FC(Game142560Rotation *arg0) {
    f32 angle;
    f32 full_turn = 360.0f;

    arg0->deltaX = ((arg0->packedSpeed >> 16) * D_800BE9E4) * 0.00390625f;
    arg0->angleX = arg0->angleX + arg0->deltaX;
    angle = arg0->angleX;
    if (angle < 0.0f) {
        arg0->angleX = angle + full_turn;
        return;
    }
    if (angle >= full_turn) {
        arg0->angleX = angle - full_turn;
    }
}

void func_1511529C(s32 arg0) {

}
extern f32 D_800A2F8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151152A8 CURRENT (170) */
void func_151152A8(void *arg0) {
    s16 temp_v1;
    s32 temp_a1;
    s32 var_v0;

    var_v0 = *(s32 *)((u8 *)arg0 + 0x7C);
    if (var_v0 == 0) {
        var_v0 = (s32) *(s16 *)((u8 *)arg0 + 0x12);
        *(s32 *)((u8 *)arg0 + 0x7C) = var_v0;
    }
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x12);
    if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
        temp_a1 = *(s32 *)((u8 *)arg0 + 0x3C);
        if ((var_v0 - temp_v1) < (s16) temp_a1) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_v1 - ((s16) (temp_a1 >> 0x10) * D_800BE9E4));
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) temp_v1 + ((f32) (var_v0 - temp_v1) * D_800A2F8C * (f32) D_800BE9E4));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151152A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151152A8.s")
f32 func_15047D60(f32);
extern f32 D_800A2F90;
extern f32 D_800A2F94;
extern u8 D_800CC2D0[];

typedef struct Game142560Motion {
    f32 angle_x;
    u8 pad04[4];
    f32 angle_z;
    u8 pad0C[4];
    s16 x, y, z;
    u8 pad16[0x26];
    s32 packed;
    u8 pad40[0xF];
    u8 flags;
    u8 pad50[0x2C];
    s32 saved_y;
    s32 timer;
    s32 returning;
} Game142560Motion;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15115368 CURRENT (5503) */
void func_15115368(Game142560Motion *actor) {
    f32 elapsed;
    f32 phase;
    f32 twice = 2.0f;
    s32 packed;
    s32 start;
    s32 delay;
    s32 end;
    s32 timer;
    s32 flags;
    s32 saved_y;
    u8 changed_flags;

    packed = actor->packed;
    delay = (s8)(packed >> 8);
    flags = actor->flags & 4;
    start = packed >> 24;
    if (flags != 0) {
        flags = actor->flags & 4;
        actor->timer += D_800BE9E4;
    }
    timer = actor->timer;
    end = start + delay;
    if (start >= timer) {
        if (flags == 0 && timer != 0) {
            actor->timer = start;
        }
    } else if (end >= timer) {
        if (flags == 0) {
            actor->timer = end;
        }
    } else {
        if (flags == 0) {
            timer += D_800BE9E4;
            actor->timer = timer;
        }
        elapsed = (f32)(timer - start - delay);
        if (actor->returning == 0) {
            phase = elapsed * D_800A2F90;
            actor->angle_x = -3.0f * func_15047D60(phase * twice);
            actor->angle_z = twice * func_15047D60(phase * 3.0f);
            if (elapsed > 10.0f) {
                saved_y = actor->saved_y;
                if (saved_y == 0) {
                    saved_y = actor->y;
                    actor->saved_y = saved_y;
                }
                packed = actor->packed;
                actor->y -= (s8)(packed >> 16) * D_800BE9E4;
                if ((packed & 0xFF) * 16 < saved_y - actor->y) {
                    actor->returning = 1;
                    changed_flags = actor->flags & 0xFF9E;
                    actor->flags = changed_flags;
                    actor->flags = changed_flags | 0x20;
                }
            }
        } else {
            elapsed = *(f32 *)(D_800CC2D0 + 0x14) - (f32)actor->x;
            phase = *(f32 *)(D_800CC2D0 + 0x1C) - (f32)actor->z;
            elapsed *= elapsed;
            phase *= phase;
            if (D_800A2F94 < elapsed + phase) {
                saved_y = actor->saved_y;
                actor->saved_y = 0;
                changed_flags = actor->flags & 0xFF9E;
                actor->flags = changed_flags;
                actor->flags = changed_flags | 1;
                actor->returning = 0;
                actor->timer = 0;
                actor->y = saved_y;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15115368 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15115368.s")
