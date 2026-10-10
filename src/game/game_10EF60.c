#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10EF60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1AB0
 * - func_150E1D14
 * - func_150E28DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[6];
    s16 zero;
    s16 u;
    s16 v;
    u8 padC[4];
} Game10EF60Vertex;

typedef struct {
    u8 pad0[0x10];
    Game10EF60Vertex quads[8];
    s16 lifetime;
    u8 pad92[2];
    f32 x, y, z;
    f32 pitch, yaw;
    f32 scale, speed;
    f32 target_x, target_y, target_z;
    f32 range, rate;
    f32 dx, dy, dz;
    volatile s8 mode;
    u8 padD1;
    s16 fieldD2, fieldD4, fieldD6;
    volatile s16 material;
    u8 fieldDA, fieldDB;
    s32 owner;
    s16 timeout;
    u8 fieldE2, fieldE3;
    f32 fieldE4, fieldE8, fieldEC, fieldF0, fieldF4, fieldF8;
    u8 fieldFC, fieldFD, fieldFE, padFF;
} Game10EF60Effect;

typedef struct {
    u8 pad0[6];
    u16 width;
    u16 height;
} Game10EF60Texture;

extern Game10EF60Texture *D_8008CA4C[];
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_150484A0(f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E1AB0 CURRENT (5622) */
void func_150E1AB0(volatile s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21, f32 arg22, f32 arg23, f32 arg24, f32 arg25, f32 arg26, f32 arg27) {
    f32 dx;
    f32 dz;
    Game10EF60Effect *effect;
    Game10EF60Vertex *quad;
    Game10EF60Texture *texture;
    s16 right;
    s16 bottom;
    s32 i;

    effect = func_15167A68(0xB, 0, 0x100, 1, 0xFF, 1);
    if (effect != 0) {
        effect->x = arg1;
        effect->lifetime = (s16)arg11;
        effect->z = arg3;
        effect->y = arg2;
        dz = arg6 - arg3;
        dx = arg4 - arg1;
        effect->yaw = func_150484A0(-dx, -dz);
        effect->pitch = func_150484A0(arg5 - arg2, sqrtf(dx * dx + dz * dz));
        effect->dx = 0.0f;
        effect->dy = 0.0f;
        effect->dz = 0.0f;
        effect->target_x = arg4;
        i = 0;
        effect->target_y = arg5;
        effect->target_z = arg6;
        effect->speed = arg8;
        effect->scale = arg7;
        effect->range = arg9;
        effect->fieldE3 = 0;
        effect->rate = arg10;
        effect->fieldFD = 0;
        effect->fieldFC = (u8)arg20;
        effect->owner = arg16;
        effect->fieldFE = (u8)arg21;
        effect->material = (u16)arg12;
        effect->mode = (s8)arg13;
        if (effect->mode != 0) {
            if (arg16 == 0) {
                func_1516979C((u8 *)effect);
                return;
            }
            effect->fieldD2 = (s16)arg14;
            effect->fieldD6 = -(s16)arg15;
            effect->fieldD4 = (s16)arg15;
            effect->fieldDA = (u8)arg17;
            effect->fieldE2 = (u8)arg18;
            effect->timeout = arg19;
            effect->fieldE4 = arg22;
            effect->fieldE8 = arg23;
            effect->fieldEC = arg24;
            effect->fieldF0 = arg25;
            effect->fieldF4 = arg26;
            effect->fieldF8 = arg27;
        } else {
            effect->fieldD6 = 1;
            effect->timeout = -1;
        }
        quad = effect->quads;
        do {
            texture = D_8008CA4C[effect->material];
            quad[2].u = 0x2000;
            right = ((texture->width - 1) << 5) + 0x2000;
            bottom = ((texture->height - 1) << 5) + 0x2000;
            quad[2].v = 0x2000;
            quad[2].zero = 0;
            quad[0].u = right;
            quad[0].v = 0x2000;
            quad[0].zero = 0;
            quad[3].u = 0x2000;
            quad[3].v = bottom;
            quad[3].zero = 0;
            quad[1].u = right;
            quad[1].v = bottom;
            quad[1].zero = 0;
            i++;
            quad += 4;
        } while (i != 2);
        effect->fieldDB = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E1AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1AB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1D14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E28DC.s")
s32 func_150E2DA4(s32 arg0, s32 arg1) {
    return arg0;
}
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32,
                   f32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                   s32, s32, f32, f32, f32, f32, f32, f32);

void func_150E2DB4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12, u8 arg13) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                  40.0f, 400.0f, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg13, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E2EA4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12,
                   f32 arg13, f32 arg14, u8 arg15, f32 arg16) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg16, 0.0f,
                  arg13, arg14, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg15, arg4, arg5, arg6, arg7, arg8, arg9);
}
void func_150E2F90(s32 arg0, s32 arg1, s16 arg2) {
    func_150E2DA4(arg0, (s32) arg2);
}
void func_150E2FC0(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v0 == *(s32 *)((u8 *)arg0 + 0xDC)) {
            *(s32 *)((u8 *)arg0 + 0xDC) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)arg0 + 0xDC)) {
            *(s32 *)((u8 *)arg0 + 0xDC) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
