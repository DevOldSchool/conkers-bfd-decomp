#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_14C3F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_complete_11ef40.md
 */

typedef struct {
    f32 x, y, z, radius, angle, dx, dz;
    s16 timer;
    u8 pad1E[6];
} Game11EF40Motion;

s32 func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
f32 func_15047C00(f32);
f32 func_15047D60(f32);
s32 func_15086CBC(s32, f32 *, f32 *, f32 *);
s32 func_15086D48(s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_800CC2D0[];
extern s32 D_800DBFF0;

void func_1511EF40(u8 *arg0) {
    u8 *player;
    f32 x, y, z, angle;
    Game11EF40Motion *motion;
    u8 *actor;
    f32 dx;

    if (*(Game11EF40Motion **)(arg0 + 0x7C) == NULL) {
        motion = *(Game11EF40Motion **)(arg0 + 0x7C) = (Game11EF40Motion *)func_10003C40(0x24, 1, 0, 0);
        func_100226F0(motion, 0x24);
    } else {
        motion = *(Game11EF40Motion **)(arg0 + 0x7C);
    }
    if (motion->timer > 0) {
        motion->timer -= D_800BE9E4;
        if (motion->timer <= 0) {
            actor = (u8 *)D_800DBFF0 + *(s32 *)(arg0 + 0x84) * 0x9A0;
            func_151239CC(actor, 0xA);
        }
    }
    if (*(s32 *)(arg0 + 0x80) == 1) {
        player = D_800CC2D0 + *(s32 *)(arg0 + 0x84) * 0x32C;
        *(s16 *)(arg0 + 0x10) = (s32)*(f32 *)(player + 0x14);
        *(s16 *)(arg0 + 0x12) = (s16)*(f32 *)(player + 0x18) + 100;
        *(s16 *)(arg0 + 0x14) = (s32)*(f32 *)(player + 0x1C);
        func_15086CBC(func_15086D48(0x28), &x, &y, &z);
        motion->dx = (x - *(f32 *)(player + 0x14)) * 0.5f;
        dx = motion->dx;
        motion->dz = (z - *(f32 *)(player + 0x1C)) * 0.5f;
        angle = motion->dz;
        motion->x = *(f32 *)(player + 0x14) + dx;
        motion->y = *(f32 *)(player + 0x18) + 100.0f;
        motion->z = *(f32 *)(player + 0x1C) + angle;
        motion->radius = sqrtf(dx * dx + angle * angle);
        motion->angle = -90.0f;
        *(s32 *)(arg0 + 0x80) = 2;
        return;
    }
    if (*(s32 *)(arg0 + 0x80) == 2) {
        if (D_80082FA0 >= *(s32 *)(arg0 + 0x84)) {
            actor = (u8 *)D_800DBFF0 + *(s32 *)(arg0 + 0x84) * 0x9A0;
            if (*(s32 *)(actor + 0x2C) != 0x400000) {
                func_15123934(actor, 0x400000, 0, *(s32 *)(actor + 0x134), 0xA);
            }
            *(f32 *)(actor + 0x2BC) = *(s16 *)(arg0 + 0x10);
            *(f32 *)(actor + 0x2C0) = *(s16 *)(arg0 + 0x12);
            *(f32 *)(actor + 0x2C4) = *(s16 *)(arg0 + 0x14);
            *(Vec3f *)(actor + 0x2A4) = *(Vec3f *)(actor + 0x2BC);
            *(f32 *)(actor + 0x2F8) = 0.0f;
            *(f32 *)(actor + 0x300) = 0.0f;
            *(f32 *)(actor + 0x2FC) = 300.0f;
            motion->timer = 60;
        }
        angle = (motion->angle * D_800A3378) / 180.0f;
        *(s16 *)(arg0 + 0x12) = (s32)(func_15047C00(angle) * motion->radius + motion->y);
        dx = func_15047D60(angle);
        *(s16 *)(arg0 + 0x10) = (s32)(motion->x + motion->dx * dx);
        *(s16 *)(arg0 + 0x14) = (s32)(motion->z + motion->dz * dx);
        motion->angle += (f32)D_800BE9E4;
        if (motion->angle > 90.0f) {
            motion->angle = 90.0f;
            *(s32 *)(arg0 + 0x80) = 0;
            *(s8 *)(arg0 + 0x6E) = 1;
            if (D_80082FA0 >= *(s32 *)(arg0 + 0x84)) func_151239CC(actor, 0xA);
        }
    }
}

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_1511490C();

void func_1511F31C(u8 *arg0) {
    u8 transform[0x48];
    f32 x;
    f32 y;
    f32 z;
    void *object;
    u16 type;

    type = *(u16 *)(arg0 + 0x3E);
    if ((*(u16 *)(arg0 + 0x54) == 0x8005) && (D_800BE9F0 == 0x35)) {
        object = func_151149AC(type);
        if (object != 0) {
            func_1511490C(transform, object);
            func_150A7960(transform, -3.0f, 223.0f, 549.0f, &x, &y, &z);
            *(s16 *)(arg0 + 0x10) = (s16)(s32)x;
            *(s16 *)(arg0 + 0x12) = (s16)(s32)y;
            *(s16 *)(arg0 + 0x14) = (s16)(s32)z;
        }
    }
}

void func_1511F3E8(void *arg0) {
    s32 temp_t2;
    s32 temp_v1;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        temp_t2 = *(s32 *)((u8 *)arg0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x80) = (s32) (((temp_t2 >> 0x10) & 0xFFFF) * 0x3C);
        *(s32 *)((u8 *)arg0 + 0x7C) = 1;
    }
    temp_t2 = *(s32 *)((u8 *)arg0 + 0x3C);
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x80);
    temp_t2 = (temp_t2 & 0xFFFF) * 0x3C;
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x80) = (s32) (temp_v1 - D_800BE9E4);
            return;
        }
        *(s32 *)((u8 *)arg0 + 0x80) = 0;
        *(s32 *)((u8 *)arg0 + 0x84) = temp_t2;
        return;
    }
    if (D_800BE9E4 < *(s32 *)((u8 *)arg0 + 0x84)) {
        *(s32 *)((u8 *)arg0 + 0x84) -= D_800BE9E4;
        *(s8 *)((u8 *)arg0 + 0x8A) = (s8) ((s32) (*(s32 *)((u8 *)arg0 + 0x84) * 0xFF) / temp_t2);
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x6E) = 1;
}
typedef struct Game14C3F0Entry {
    u8 unk_00[0x10];
    s16 unk_10;
    s16 unk_12;
    u8 unk_14[0x1C];
    f32 unk_30;
    u8 unk_34[8];
    s32 unk_3C;
    u8 unk_40[0x33];
    u8 unk_73;
    u8 unk_74[8];
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    u8 unk_88[0x18];
} Game14C3F0Entry;

void func_1511F4D0(Game14C3F0Entry *arg0) {
    s32 state;
    s32 scale;
    s32 low;
    s32 high;
    s32 temp;
    s32 reversed;
    s32 offset;
    s32 base[2];

    state = arg0->unk_73 & 3;
    reversed = arg0->unk_73 & 4;
    if (reversed == 4) {
        if (state == 2) {
            state = 0;
        } else if (state == 1) {
            state = 3;
        }
    }
    scale = arg0->unk_3C;
    scale *= arg0->unk_30;
    low = arg0->unk_84 & 0xFFFF;
    high = (arg0->unk_84 >> 16) & 0xFFFF;
    if (arg0->unk_7C == 0) {
        arg0->unk_7C = (arg0->unk_10 & 0xFFFF) | ((arg0->unk_12 & 0xFFFF) << 16);
        if (state == 3) {
            low = 13;
            high = 13;
        } else {
            high = 0;
            low = 0;
        }
    }
    base[0] = (s16)(arg0->unk_7C & 0xFFFF);
    base[1] = (s16)((arg0->unk_7C >> 16) & 0xFFFF);
    if (state == 2) {
        temp = low + D_800BE9E4;
        if (temp < 13) {
            low = temp;
        } else {
            low = 13;
        }
        if (low >= 9) {
            temp = high + D_800BE9E4;
            if (temp < 13) {
                high = temp;
            } else {
                high = 13;
                state = 3;
            }
        }
    } else if (state == 1) {
        temp = high - D_800BE9E4;
        if (temp > 0) {
            high = temp;
        } else {
            high = 0;
        }
        if (high < 4) {
            temp = low - D_800BE9E4;
            if (temp > 0) {
                low = temp;
            } else {
                low = 0;
                state = 0;
            }
        }
    }
    arg0[0].unk_12 = base[1] + low * scale / 13;
    arg0[1].unk_12 = base[1] - (scale + 1) * low / 13;
    offset = high * scale / 13;
    arg0[2].unk_10 = base[0] - offset;
    arg0[3].unk_10 = base[0] + offset;
    arg0->unk_84 = (low & 0xFFFF) | ((high & 0xFFFF) << 16);
    arg0->unk_73 &= ~3;
    arg0->unk_73 |= state;
}

void func_1511F768(s32 *arg0, s32 arg1) {
    if (arg0[0x20] == 0) {
        arg0[0x20] = 1;
    }
}
f32 func_15047C00(f32);

void func_1511F788(void *arg0) {
    s32 state;
    f32 bob;
    s32 limit;
    f32 angle;
    s16 base;

    base = (s16)(s32)(*(f32 *)((u8 *)arg0 + 0x18) + (f32)*(s16 *)((u8 *)arg0 + 0x12));
    limit = *(s32 *)((u8 *)arg0 + 0x3C);
    limit = limit * 60 / 60;
    if (D_800BE9B4 != 0) {
        *(s32 *)((u8 *)arg0 + 0x7C) = func_150ADA20() & 0xFFFF;
    }
    angle = (f32)*(s32 *)((u8 *)arg0 + 0x7C) * 0.005493164f;
    bob = func_15047C00(angle) * 25.0f;
    *(f32 *)((u8 *)arg0 + 0x18) = bob;
    *(s32 *)((u8 *)arg0 + 0x7C) += D_800BE9E4 * 10;
    state = *(s32 *)((u8 *)arg0 + 0x80);
    if (state == 1) {
        *(s32 *)((u8 *)arg0 + 0x84) += D_800BE9E4;
        if (limit < *(s32 *)((u8 *)arg0 + 0x84)) {
            *(s32 *)((u8 *)arg0 + 0x80) = 2;
        }
    } else if (state == 2) {
        *(s16 *)((u8 *)arg0 + 0x12) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x12) < -10000) {
            *(u8 *)((u8 *)arg0 + 0x6E) = 1;
        }
    }
    *(s16 *)((u8 *)arg0 + 0x5C) = (s32)((*(f32 *)((u8 *)arg0 + 0x18) + (f32)*(s16 *)((u8 *)arg0 + 0x12)) - (f32)base);
}
/* Call context: func_151149AC: unique active project prototype */

void func_1511F92C(void *arg0) {
    u8 *temp_v0;

    temp_v0 = func_151149AC(*(u8 *)((u8 *)arg0 + 0x3F));
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) *(s16 *)((u8 *)temp_v0 + 0x10);
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) *(s16 *)((u8 *)temp_v0 + 0x12);
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)temp_v0 + 0x14);
    }
}
