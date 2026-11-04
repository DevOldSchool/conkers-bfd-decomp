#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_197120.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 */

typedef struct Game197120Debris {
    u8 pad0;
    u8 field_1;
    u8 pad2[0xA];
    u8 field_C;
    u8 padD[0x83];
    f32 x;      /* 0x90 */
    f32 y;      /* 0x94 */
    f32 z;      /* 0x98 */
    f32 rotX;   /* 0x9C */
    f32 rotY;   /* 0xA0 */
    f32 rotZ;   /* 0xA4 */
    f32 velX;   /* 0xA8 */
    f32 velY;   /* 0xAC */
    f32 velZ;   /* 0xB0 */
    f32 spinX;  /* 0xB4 */
    f32 spinY;  /* 0xB8 */
    f32 spinZ;  /* 0xBC */
    u8 padC0[4];
    f32 scale;  /* 0xC4 */
    u8 padC8[4];
    s32 timer;  /* 0xCC */
    u8 padD0[4];
    f32 baseScale; /* 0xD4 */
    f32 friction;  /* 0xD8 */
    f32 bounce;    /* 0xDC */
    f32 spinDamp;  /* 0xE0 */
    u8 padE4;
    u8 alpha;      /* 0xE5 */
    u8 padE6;
    u8 phase;      /* 0xE7 */
    u8 flags;      /* 0xE8 */
    u8 floorOffset; /* 0xE9 */
    u8 sound;      /* 0xEA */
    u8 kind;       /* 0xEB */
    s8 state;      /* 0xEC */
} Game197120Debris;

f32 func_150484A0(f32, f32);
void func_151709B4(s32, s32, s32, s32, f32, u8, s32);
void func_15171200(s32, s32, f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, u8, s32);
void func_151718F0(f32, f32, f32, f32, s32, f32, s32, s32, u8, s32);
void func_1518CA04(s32);
extern s32 D_800BE9E4;
void func_1510F800(s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_15169C70(Game197120Debris *arg0) {
    f32 dt;
    f32 floor;
    f32 vx;
    f32 vz;
    s32 timer;
    s32 alpha;
    s32 height;

    dt = (f32)D_800BE9E4;
    arg0->x += arg0->velX * dt;
    arg0->z += arg0->velZ * dt;
    arg0->rotX += arg0->spinX * dt;
    arg0->rotY += arg0->spinY * dt;
    arg0->rotZ += arg0->spinZ * dt;
    arg0->velY += -0.5f * dt;
    arg0->y += arg0->velY * dt;
    if (arg0->flags & 1) {
        arg0->phase += D_800BE9E4 * 8;
        arg0->scale = ((func_15048A40(arg0->phase) * 0.4f) + 1.0f) * arg0->baseScale;
    }
    if (arg0->flags & 2) {
        arg0->rotY = func_150484A0(arg0->velX, arg0->velZ) * 57.295776f;
        vx = arg0->velX;
        vz = arg0->velZ;
        arg0->rotX = func_150484A0(-arg0->velY, sqrtf((vx * vx) + (vz * vz))) * 57.295776f;
    }
    func_1510F800(0);
    height = func_1510F8D8((s32)arg0->x, (s32)arg0->y, (s32)arg0->z, 0) + arg0->floorOffset;
    floor = height;
    if ((arg0->y < floor) && (arg0->velY < 0.0f)) {
        arg0->y = floor;
        if (arg0->kind == 1) {
            func_15171200(4, 0xB, arg0->x, arg0->y, arg0->z, arg0->velY * arg0->bounce,
                          0.5f, 1.0f, 60.0f, 2, 0xFF, -0.4f, arg0->field_C, arg0->field_1);
            func_151718F0(arg0->x, (arg0->y - (f32)(u32)arg0->floorOffset) + 30.0f, arg0->z,
                          50.0f, 0x28, 0.0030517578f, 0, 0x14, arg0->field_C, arg0->field_1);
            func_151718F0(arg0->x, (arg0->y - (f32)(u32)arg0->floorOffset) + 15.0f, arg0->z,
                          30.0f, 0x28, 0.0030517578f, 0, 0xA, arg0->field_C, arg0->field_1);
            func_1518CA04(arg0->sound);
            func_1516972C(arg0);
            return;
        }
        if (arg0->kind == 4) {
            func_15171200(3, 0xB, arg0->x, arg0->y, arg0->z, arg0->velY * arg0->bounce,
                          0.5f, 0.7f, 40.0f, 2, 0x3C, -0.5f, arg0->field_C, arg0->field_1);
            func_1518CA04(arg0->sound);
            func_1516972C(arg0);
            return;
        }
        if (arg0->kind == 3) {
            func_15171200(2, 0xCB, arg0->x, arg0->y, arg0->z, 6.0f,
                          0.5f, 1.0f, 60.0f, 5, 0x3C, -0.7f, arg0->field_C, arg0->field_1);
            func_151709B4(arg0->x, arg0->y + 10.0f, arg0->z, 4, arg0->velY * 200.0f,
                          arg0->field_C, arg0->field_1);
            func_1518CA04(arg0->sound);
            func_1516972C(arg0);
            return;
        }
        if (arg0->kind == 6) {
            arg0->velZ = 0.0f;
            arg0->velY = 0.0f;
            arg0->velX = 0.0f;
            arg0->spinZ = 0.0f;
            arg0->spinY = 0.0f;
            arg0->spinX = 0.0f;
            arg0->bounce = 0.0f;
            arg0->kind = 0;
            arg0->timer = 0x3C;
            return;
        }
        if (arg0->kind == 8) {
            func_1518CA04(arg0->sound);
            func_1516972C(arg0);
            return;
        }
        arg0->velX *= arg0->friction;
        arg0->velZ *= arg0->friction;
        arg0->velY *= arg0->bounce;
        if (arg0->velY < 2.0f) {
            arg0->velX = 0;
            arg0->velY = 0;
            arg0->velZ = 0;
            arg0->spinX = 0;
            arg0->spinY = 0;
            arg0->spinZ = 0;
        } else {
            func_151718F0(arg0->x, (arg0->y - (f32)(u32)arg0->floorOffset) + 15.0f, arg0->z,
                          20.0f, 0x32, 0.00045776367f, 0, 4, arg0->field_C, arg0->field_1);
            if (arg0->kind == 2) {
                if (func_150ADA20() & 0x8000) {
                    arg0->spinX = ((f32)((s32)func_150ADA20() >> 16) * 0.00015258789f) + 40.0f;
                }
            } else if (arg0->kind == 5) {
                func_151709B4(arg0->x, arg0->y + 10.0f, arg0->z, 4, arg0->velY * 200.0f,
                              arg0->field_C, arg0->field_1);
            }
        }
        arg0->spinX *= arg0->spinDamp;
        arg0->spinZ *= arg0->spinDamp;
    }
    timer = arg0->timer;
    if (timer != 0) {
        timer -= D_800BE9E4;
        if (timer <= 0) {
            arg0->state = 2;
            timer = 1;
            alpha = arg0->alpha;
            alpha -= D_800BE9E4 * 4;
            if (alpha <= 0) {
                func_1518CA04(arg0->sound);
                func_1516972C(arg0);
                return;
            }
            arg0->alpha = alpha;
        }
        arg0->timer = timer;
    }
}
typedef struct Game197120SpawnPacket {
    s32 resource;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s8 field_12;
    u8 pad_13;
    s8 field_14;
    u8 field_15;
} Game197120SpawnPacket;

void func_1510F800(s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);
void func_15167AD8(void *, u8, s32);
extern s32 D_8008CADC;

void func_1516A3F4(void *arg0) {
    s32 current;
    s32 limit;
    s32 shade;
    Game197120SpawnPacket packet;
    u8 color;

    current = *(s32 *)((u8 *)arg0 + 0x14);
    limit = *(s16 *)((u8 *)arg0 + 0x2A) + *(s16 *)((u8 *)arg0 + 0x22);
    if (current >= limit) {
        func_1510F800(0);
        *(s32 *)((u8 *)arg0 + 0x14) = func_1510F8D8(*(s16 *)((u8 *)arg0 + 0x20),
                                *(s16 *)((u8 *)arg0 + 0x22),
                                *(s16 *)((u8 *)arg0 + 0x24), 0);
        current = *(s32 *)((u8 *)arg0 + 0x14);
    }
    if (current >= limit) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
        if ((limit - current) < 0x32) {
            packet.resource = D_8008CADC;
            packet.field_4 = 0;
            packet.field_6 = 0x100;
            packet.field_8 = *(s16 *)((u8 *)arg0 + 0x20);
            packet.field_A = *(s32 *)((u8 *)arg0 + 0x14) + 0xA;
            packet.field_C = *(s16 *)((u8 *)arg0 + 0x24);
            color = *(u8 *)((u8 *)arg0 + 0x3B);
            shade = ((s32)(color << 12) / 5100) + 0xCC;
            packet.field_12 = 0;
            packet.field_E = shade;
            packet.field_10 = shade;
            packet.field_15 = color;
            packet.field_14 = 3;
            func_15167AD8(&packet, *(u8 *)((u8 *)arg0 + 0xC),
                           *(u8 *)((u8 *)arg0 + 1));
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x26) = (s32)((f32)*(s16 *)((u8 *)arg0 + 0x26) * 0.98f);
        *(s16 *)((u8 *)arg0 + 0x28) = (s32)((f32)*(s16 *)((u8 *)arg0 + 0x28) * 0.98f);
    }
}
void func_15171D4C(f32, f32, f32, s32, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32, s32);

void func_1516A538(u8 *arg0) {
    u32 angle;
    u32 type;
    s32 alpha;

    if (*(s16 *)(arg0 + 0x14) >= 0x300) {
        type = func_150ADA20(arg0) % 3U;
        alpha = arg0[0x25];
        angle = func_150ADA20(arg0) % 360U;
        func_15171D4C((f32)*(s16 *)(arg0 + 0x18),
                      (f32)(*(s16 *)(arg0 + 0x1A) - 0xA),
                      (f32)*(s16 *)(arg0 + 0x1C), 0x64, 0,
                      type + 0x20, (f32)angle, 0,
                      ((alpha * 0x19) / 0xFF) + 0x19, 0, 0x100, 0,
                      arg0[0xC], arg0[1]);
    }
}
void func_1516F94C(s32, s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);
extern s32 D_800BE9E4;

s32 func_1516A648(u8 *arg0) {
    s32 value;
    s32 height;

    value = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (value != 0xFF) {
            value = (s32)((u32)value + (u32)D_800BE9E4 * 0x10U);
            if (value >= 0x100) {
                value = 0xFF;
            }
            arg0[0x1F] = value;
        }
    } else if (value != 0) {
        value = (s32)((u32)value - (u32)D_800BE9E4 * 4U);
        if (value < 0) {
            value = 0;
        }
        arg0[0x1F] = value;
    }
    if ((arg0[0x24] == 0) && (value == 0)) {
        return 1;
    }
    *(s16 *)(arg0 + 0x18) -= 0x12C;
    func_1516F864((struct Game19A8B0Motion *)arg0);
    height = (s32)((u32)func_1510F8D8(*(s16 *)(arg0 + 0xE), *(s16 *)(arg0 + 0x10),
                           *(s16 *)(arg0 + 0x12), 0) + 0xAU);
    arg0[0x2C] = height >> 8;
    /* Redundant for u8 storage; omitting it shifts IDO's later scratch registers. */
    arg0[0x2D] = height & 0xFFFF;
    if (*(s16 *)(arg0 + 0x10) < height) {
        *(s16 *)(arg0 + 0x10) = height;
        *(s16 *)(arg0 + 0x18) = (s32)((f32)*(s16 *)(arg0 + 0x18) * -0.5f);
        func_1516F94C((s32)arg0, 0xE6);
    }
    return 0;
}
