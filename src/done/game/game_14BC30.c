#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_14BC30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_callback_table_runs.md
 */

typedef struct Mover {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 pad0C[0x30];
    /* 0x3C */ s32 kind; /* movement type in the high half, sound set in the low half */
    /* 0x40 */ u8 pad40[0x33];
    /* 0x73 */ u8 flags; /* bits 0-1: travel state */
    /* 0x74 */ u8 pad74[0x8];
    /* 0x7C */ s32 started;
    /* 0x80 */ s32 mode;
    /* 0x84 */ f32 base;
} Mover;

extern s16 D_80089260[][6];
extern s32 D_800BE9E4;
void func_15114D24(void *, s32, s32, s16, s32, s32);
f32 func_15047D60(f32);

void func_1511E780(Mover *arg0) {
    f32 speed;
    s32 cue;
    s32 sfx;
    s32 state;
    f32 range;
    f32 rate;

    state = arg0->flags & 3;
    cue = -1;
    if (arg0->mode == 1) {
        if (state == 0 || state == 1) {
            state = 2;
            cue = 0;
        }
        speed = 1.0f;
    } else if (arg0->mode == 0) {
        if (state == 3 || state == 2) {
            state = 1;
            cue = 1;
        }
        speed = -1.0f;
    } else {
        speed = 90.0f;
    }
    if (cue != -1) {
        sfx = arg0->kind & 0xFFFF;
        sfx = D_80089260[sfx][cue];
        if (sfx > 0) {
            func_15114D24(arg0, sfx, 0x5DC0, 0xC8, 0x9C4, 0);
        }
    }
    speed *= (f32) D_800BE9E4;
    range = 70.0f;
    rate = 6.0f;
    switch (arg0->kind >> 16) {
    case 6:
        rate = 3.0f;
        range = 82.0f;
        break;
    case 2:
    case 4:
        range = 80.0f;
        break;
    }
    switch (arg0->kind >> 16) {
    case 0:
        if (arg0->started == 0) {
            arg0->base = arg0->z;
        }
        arg0->z -= speed * rate;
        if (arg0->base < arg0->z) {
            arg0->z = arg0->base;
            state = 0;
        }
        if (arg0->z < -110.0f) {
            arg0->z = -110.0f;
            state = 3;
        }
        break;
    case 3:
        if (arg0->started == 0) {
            arg0->base = arg0->y;
        }
        arg0->y -= speed * 3.0f;
        if (arg0->y < 260.0f) {
            arg0->y = 260.0f;
            state = 3;
        }
        if (arg0->base < arg0->y) {
            arg0->y = arg0->base;
            state = 0;
        }
        break;
    case 2:
    case 8:
        if (arg0->started == 0) {
            arg0->base = arg0->y;
        }
        arg0->y += speed * rate;
        if (arg0->base + range < arg0->y) {
            arg0->y = arg0->base + range;
            state = 3;
        }
        if (arg0->y < arg0->base) {
            arg0->y = arg0->base;
            state = 0;
        }
        break;
    case 4:
    case 6:
    case 7:
        if (arg0->started == 0) {
            arg0->base = arg0->y;
        }
        arg0->y -= speed * rate;
        if (arg0->base < arg0->y) {
            arg0->y = arg0->base;
            state = 0;
        }
        if (arg0->y < arg0->base - range) {
            arg0->y = arg0->base - range;
            state = 3;
        }
        break;
    case 10:
        arg0->base += 0.01f;
        /* fallthrough */
    case 11:
        arg0->base += 0.04f * (f32) D_800BE9E4;
        arg0->z = func_15047D60(arg0->base) * 10.0f;
        if (arg0->base > 12.566371f) {
            arg0->base -= 12.566371f * ((func_150ADA20() & 4) + 1);
            func_15114D24(arg0, 0x503, 0x1F40, 0x96, 0x258, 0);
        }
        break;
    case 12:
        arg0->base += 0.01f;
        /* fallthrough */
    case 13:
        arg0->base += 0.04f * (f32) D_800BE9E4;
        arg0->z = 180.0 - func_15047D60(arg0->base) * 10.0f;
        break;
    }
    arg0->started = 1;
    arg0->flags &= ~3;
    arg0->flags |= state;
}

void func_1511EC50(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 var_fv1;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(f32 *)((u8 *)arg0 + 0x84) = (f32) *(s16 *)((u8 *)arg0 + 0x12);
    }
    var_fv1 = (f32) D_800BE9E4 * 4.0f;
    if (*(s32 *)((u8 *)arg0 + 0x3C) != 0) {
        var_fv1 *= 0.25f;
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) + var_fv1 * 5.0f);
        temp_fa0 = *(f32 *)((u8 *)arg0 + 0x84) + 500.0f;
        if (temp_fa0 < (f32) *(s16 *)((u8 *)arg0 + 0x12)) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) temp_fa0;
            *(s8 *)((u8 *)arg0 + 0x6E) = 1;
        }
    } else {
        temp_fa0_2 = *(f32 *)((u8 *)arg0 + 0x84);
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) - var_fv1);
        if ((f32) *(s16 *)((u8 *)arg0 + 0x12) < temp_fa0_2) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) temp_fa0_2;
        }
    }
    *(s32 *)((u8 *)arg0 + 0x7C) = 1;
}
void func_1511ED84(void *arg0) {
    f32 step;
    s32 direction;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(f32 *)((u8 *)arg0 + 0x84) = (f32) *(s16 *)((u8 *)arg0 + 0x14);
    }
    step = (f32) D_800BE9E4 * 4.0f;
    direction = 1 - (*(u8 *)((u8 *)arg0 + 0x72) & 1);
    if (*(s32 *)((u8 *)arg0 + 0x80) != 0) {
        if (direction & 1) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) + step);
            if (*(f32 *)((u8 *)arg0 + 0x84) < (f32) *(s16 *)((u8 *)arg0 + 0x14)) {
                *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x84);
            }
        } else {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) - step);
            if ((f32) *(s16 *)((u8 *)arg0 + 0x14) < *(f32 *)((u8 *)arg0 + 0x84)) {
                *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x84);
            }
        }
    } else if (direction & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) - step);
        if ((f32) *(s16 *)((u8 *)arg0 + 0x14) < (*(f32 *)((u8 *)arg0 + 0x84) - 350.0f)) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x84) - 350.0f);
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x14) + step);
        if ((*(f32 *)((u8 *)arg0 + 0x84) + 350.0f) < (f32) *(s16 *)((u8 *)arg0 + 0x14)) {
            *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x84) + 350.0f);
        }
    }
    *(s32 *)((u8 *)arg0 + 0x7C) = 1;
}
