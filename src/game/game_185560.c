#include "types.h"

/*
 * Reviewed source unit: src/game/game_185560.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_attachment_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151580B0
 * - func_15158224
 * - func_151582C8
 * - func_1515858C
 * - func_15158684
 * - func_15158920
 * - func_15158A20
 * - func_15158B3C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15158A20(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void *func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void *func_10022EC0(void *, const void *, u32);
void *func_1515D440(void);
s32 func_1515D480(s32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151580B0 CURRENT (1168) */
void *func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3,
                    s32 arg4, u8 arg5, s32 arg6) {
    s32 var_a0;
    s32 var_s1;
    s32 var_s1_2;
    void *temp_v0;
    volatile s32 *var_s0;
    void *var_s0_2;

    if (arg3) {
        var_a0 = 0x55;
    } else {
        var_a0 = 0x37;
    }
    temp_v0 = func_15167A68(var_a0, arg6, arg4 + 0xF8, 1, arg5, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x44);
    *(s32 *)((u8 *)temp_v0 + 0xD8) = arg1;
    *(s32 *)((u8 *)temp_v0 + 0xF4) = arg2;
    *(s8 *)((u8 *)temp_v0 + 0xDC) = 0;
    var_s1 = 0;
    var_s0 = (volatile s32 *)((u8 *)temp_v0 + 0xDC);
    do {
        var_s1++;
        var_s0++;
        *var_s0 = 0;
    } while (var_s1 < 4);
    *(void **)((u8 *)temp_v0 + 0xF0) = 0;
    if (arg1 != 0) {
        var_s1_2 = 0;
        var_s0_2 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)((u8 *)var_s0_2 + 0xE0) = func_1515D480(arg1);
                var_s1_2++;
                var_s0_2 = (u8 *)var_s0_2 + 4;
            } while (D_80082FA0 >= var_s1_2);
        }
        *(void **)((u8 *)temp_v0 + 0xF0) = func_1515D440();
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151580B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151580B0.s")
void func_151581D8(void *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_151580B0(arg0, 0, 0, arg1, arg2, arg3, arg4);
}
typedef s32 (*Game185560Callback)(void *);

extern Game185560Callback D_8008AE00[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158224 CURRENT (120) */
void func_15158224(void *arg0) {
    s32 result;
    u8 sp1B;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0x10) & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0x12);
        if (callback_index != -1) {
            sp1B = callback_pending;
            result = D_8008AE00[(s32) callback_index](arg0);
            callback_pending = sp1B;
            if (result == 0) {
                callback_pending = 1;
            }
        }
    }
    if (callback_pending != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158224 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158224.s")
typedef struct Game185560RenderActor {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11[2];
    s8 drawCallback;
    u8 pad14[2];
    u8 listIndex, pad17;
    s32 state, geometry0, geometry1, presetIndex;
    u8 pad28[3];
    u8 combine;
    s32 flags2C, flags30;
    s8 colorMode0, colorMode1;
    u8 pad36[2];
    u8 color0[4], color1[4];
    void *owner;
    u8 generation, attachmentMode;
    u8 pad46[2];
    f32 position[3];
    u8 pad54[4];
    u8 matrices[0x80];
    u8 attachments[0x20];
} Game185560RenderActor;

typedef struct Game185560RenderColor {
    s16 alpha, blue, green, red;
} Game185560RenderColor;

typedef struct Game185560RenderPreset {
    s32 first, second;
} Game185560RenderPreset;

typedef struct Game185560Command {
    u32 opcode, data;
} Game185560Command;

typedef s32 (*Game185560DrawCallback)(void *, Game185560RenderActor *);
extern Game185560DrawCallback D_8008AE0C[];
extern u32 D_8008AFB8[];
extern Game185560RenderPreset D_800A4AC8[];
extern u8 D_800BE9C0;
s32 *func_15142B7C(s32 *, s32, s32);
void *func_15142C10(void *, s32, s32, s32, s32, u8 *);
void *func_15142CF0(void *, s32, s32, s32, s32, s32, s32, u8 *);
void *func_1513F4E4(void *, u8, u8 *);
void *func_15142FBC(void *, s32, s32, u8 *);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, s32, u8, u8, u8, u8, u8, u8);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 func_151462C8(s32, void *, s32, s32, s32, s32, void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151582C8 CURRENT (1235) */
Game185560Command *func_151582C8(Game185560Command *arg0, Game185560RenderActor *arg1, s32 arg2) {
    Game185560Command *commands;
    Game185560RenderColor first;
    Game185560RenderColor second;
    u8 sync;
    s32 callback;
    s32 flags;
    s32 attached;
    Game185560RenderPreset *preset;

    sync = 1;
    callback = arg1->drawCallback;
    if (callback != -1 && D_8008AE0C[callback]((u8 *) arg1 + (D_800BE9C0 << 6) + 0x58, arg1) == 0) {
        return arg0;
    }
    arg0 = (Game185560Command *) func_15142B7C((s32 *) arg0, arg1->geometry0, arg1->geometry1);
    func_151441A4(&first.red, &first.green, &first.blue, &first.alpha,
        arg1->color1[0], arg1->color1[1], arg1->color1[2], arg1->color1[3],
        arg1->color0[0], arg1->color0[1], arg1->color0[2], arg1->color0[3],
        255, (u8) arg1->colorMode0);
    func_151442FC(&second.red, &second.green, &second.blue, &second.alpha,
        arg1->color1[0], arg1->color1[1], arg1->color1[2], arg1->color1[3],
        arg1->color0[0], arg1->color0[1], arg1->color0[2], arg1->color0[3],
        255, (u8) arg1->colorMode1);
    arg0 = func_15142C10(arg0, second.red, second.green, second.blue, second.alpha, &sync);
    arg0 = func_15142CF0(arg0, 0, 0, first.red, first.green, first.blue, first.alpha, &sync);
    arg0 = func_1513F4E4(arg0, arg1->combine, &sync);
    preset = &D_800A4AC8[arg1->presetIndex];
    arg0 = func_15142FBC(arg0, arg1->state | 0x80000 | 0x2C00 | arg1->flags2C | arg1->flags30,
                        preset->second | preset->first, &sync);
    flags = arg1->flags;
    if (flags & 2) {
        if (flags & 4) {
            attached = 1;
        } else {
            attached = 0;
        }
        arg0 = (Game185560Command *) func_151462C8((s32) arg0, arg1->attachments, arg1->attachmentMode,
            (s32) arg1->owner, arg1->generation, *((s16 *) &arg2 + 1), arg1->position, attached, 0);
    }
    commands = (Game185560Command *) arg0;
    commands->opcode = 0xDA380003;
    arg0++;
    commands->data = (u32) ((u8 *) arg1 + (D_800BE9C0 << 6) + 0x58);
    commands = (Game185560Command *) arg0;
    commands->opcode = 0xDE000000;
    arg0++;
    commands->data = D_8008AFB8[arg1->listIndex];
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151582C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151582C8.s")

typedef struct Game185560TransformArgs {
    u8 pad0[0x48];
    f32 field48;
    f32 field4C;
    f32 field50;
    u8 pad54[0xA4];
    f32 fieldF8;
    s32 fieldFC;
    f32 field100;
    f32 field104;
} Game185560TransformArgs;

void func_150A7790(void *, s32);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515858C CURRENT (583) */
s32 func_1515858C(s32 arg0, Game185560TransformArgs *arg1) {
    f32 matrix[15];
    void *temp_v0;

    func_150A8050(matrix, arg1->fieldF8, arg1->fieldFC, arg1->field100);
    temp_v0 = (u8 *)arg1 + 0xF8;
    matrix[12] = arg1->field48;
    matrix[13] = arg1->field4C;
    matrix[14] = arg1->field50;
    matrix[0] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[1] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[2] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[4] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[5] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[6] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[8] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[9] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[10] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    func_150A7790(matrix, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515858C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515858C.s")

typedef struct Game185560Vec3f {
    f32 x, y, z;
} Game185560Vec3f;

typedef struct Game185560Motion {
    Game185560Vec3f angle;
    f32 scale;
    Game185560Vec3f velocity;
    Game185560Vec3f angularVelocity;
    f32 acceleration;
    f32 damping;
} Game185560Motion;

typedef struct Game185560MovingActor {
    u8 unknown0[0x48];
    Game185560Vec3f position;
    u8 unknown54[0xA4];
    Game185560Motion motion;
} Game185560MovingActor;

extern f32 D_800BE9A4;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158684 CURRENT (2965) */
s32 func_15158684(void *actor) {
    f32 acceleration;
    Game185560Vec3f previous;
    s32 remaining;
    Game185560Motion *motion;
    f32 deltaX;
    f32 deltaZ;

    previous = ((Game185560MovingActor *)actor)->motion.velocity;
    remaining = D_800BE9E4;
    while (remaining != 0) {
        motion = (Game185560Motion *)((u32)actor + 0xF8U);
        motion->velocity.x *= motion->damping;
        remaining--;
        motion->velocity.z *= motion->damping;
    }
    motion = (Game185560Motion *)((u32)actor + 0xF8U);
    acceleration = motion->acceleration;
    motion->velocity.y += acceleration * D_800BE9A4;
    deltaX = (motion->velocity.x - previous.x) * D_800BE9A8;
    deltaZ = (motion->velocity.z - previous.z) * D_800BE9A8;
    ((Game185560MovingActor *)actor)->position.x += (previous.x + (0.5f * deltaX * D_800BE9A4)) * D_800BE9A4;
    ((Game185560MovingActor *)actor)->position.y += (previous.y + (0.5f * acceleration * D_800BE9A4)) * D_800BE9A4;
    ((Game185560MovingActor *)actor)->position.z += (previous.z + (0.5f * deltaZ * D_800BE9A4)) * D_800BE9A4;
    ((Game185560MovingActor *)actor)->motion.angle.x += motion->angularVelocity.x * D_800BE9A4;
    motion->angle.y += motion->angularVelocity.y * D_800BE9A4;
    motion->angle.z += motion->angularVelocity.z * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158684 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158684.s")
typedef struct {
    f32 values[16];
} Game185560Matrix;

extern Game185560Matrix D_8008AE18;
extern f32 D_800A6070;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158920 CURRENT (89) */
s32 func_15158920(s32 arg0, Game185560TransformArgs *arg1) {
    register f32 scale;
    Game185560Matrix matrix;

    matrix = D_8008AE18;
    scale = arg1->fieldF8 * D_800A6070;
    matrix.values[12] = arg1->field48;
    matrix.values[13] = arg1->field4C;
    matrix.values[14] = arg1->field50;
    matrix.values[0] *= scale;
    matrix.values[1] *= scale;
    matrix.values[2] *= scale;
    matrix.values[4] *= scale;
    matrix.values[5] *= scale;
    matrix.values[6] *= scale;
    matrix.values[8] *= scale;
    matrix.values[9] *= scale;
    matrix.values[10] *= scale;
    func_150A7790(&matrix, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158920.s")
void func_100043B4(s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158A20 CURRENT (890) */
void func_15158A20(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(s32 *)((u8 *)var_s0 + 0xE0);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0_2 = *(s32 *)((u8 *)arg0 + 0xF0);
    if (temp_v0_2 != 0) {
        func_100043B4(temp_v0_2, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158A20.s")
void func_15158AA4(s32 arg0) {
    func_15158A20(arg0);
    func_15169804(arg0);
}
void func_15158AD0(s32 arg0) {
    func_15158A20(arg0);
    func_15169824(arg0);
}
s32 func_15158AFC(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x14);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xF8)) {
        temp_lo = temp_v0;
        temp_lo *= *(s32 *)((u8 *)arg0 + 0xFC);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x3B)) {
            *(u8 *)((u8 *)arg0 + 0x3B) = (u8) temp_lo;
        }
    }
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158B3C CURRENT (170) */
void func_15158B3C(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x40);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x40) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x44) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x40) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0x44) = (u8) *(u8 *)((u8 *)arg1 + 8);
            return;
        }
    } else if ((arg2 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x40)) || (*(u8 *)((u8 *)arg0 + 0x44) == *(u8 *)((u8 *)arg1 + 4)))) {
        *(s32 *)((u8 *)arg0 + 0x40) = 0;
        *(u8 *)((u8 *)arg0 + 0x44) = 0U;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158B3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158B3C.s")
