#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AB530.c
 * Boundary evidence: docs/evidence/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517E28C
 * - func_1517E4A8
 * - func_1517EAAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10003C40(s32, s32, s32, s32);
extern void *D_800DDD64;

void *func_1517E080(s32 arg0, s32 arg1) {
    void *node;
    void **link;
    void *result;

    node = D_800DDD64;
    if (node != 0) {
        while (*(void **)((u8 *)node + 0x24) != 0) {
            node = *(void **)((u8 *)node + 0x24);
        }
        link = (void **)((u8 *)node + 0x24);
    } else {
        link = &D_800DDD64;
    }
    result = func_10003C40(0x34, 1, 0, 1);
    if (result == 0) {
        return 0;
    }
    *link = result;
    *(s32 *)((u8 *)result + 0x24) = 0;
    *(s16 *)((u8 *)result + 0x28) = 0;
    *(s8 *)((u8 *)result + 0x2E) = 0;
    *(f32 *)((u8 *)result + 0x10) = 0.0f;
    *(f32 *)((u8 *)result + 0xC) = 0.0f;
    *(s8 *)((u8 *)result + 0x2F) = (s8)arg0;
    *(s8 *)((u8 *)result + 0x30) = (s8)arg1;
    return result;
}
/* Call context: func_10004074: unique active project prototype */
void func_10004074(s32);

void func_1517E134(void *arg0) {
    void *var_v0;
    void *var_v1;

    var_v0 = D_800DDD64;
    if (arg0 == var_v0) {
        D_800DDD64 = *(void **)((u8 *)arg0 + 0x24);
        goto block_8;
    }
    var_v1 = var_v0;
    if (var_v0 != 0) {
        var_v0 = *(void **)((u8 *)var_v0 + 0x24);
        if (arg0 != var_v0) {
loop_4:
            var_v1 = var_v0;
            if (var_v0 != 0) {
                var_v0 = *(void **)((u8 *)var_v0 + 0x24);
                if (arg0 != var_v0) {
                    goto loop_4;
                }
            }
        }
    }
    if (var_v1 != 0) {
        *(void **)((u8 *)var_v1 + 0x24) = (void *) *(void **)((u8 *)arg0 + 0x24);
block_8:
        func_10004074((s32) arg0);
    }
}
typedef struct Game1AB530Node {
    u8 pad0[0xC];
    f32 field_C;
    f32 field_10;
    u8 pad14[0x10];
    struct Game1AB530Node *next;
    u8 pad28[2];
    u16 field_2A;
} Game1AB530Node;

extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE9C4;

void func_1517E1AC(void) {
    f32 temp_fv0;
    f32 temp_fv1;
    Game1AB530Node *var_v0;

    var_v0 = D_800DDD64;
    if (var_v0 != 0) {
        do {
            temp_fv0 = var_v0->field_C;
            if ((temp_fv0 >= 0.0f) && (temp_fv0 < (f32)D_800BE620)) {
                temp_fv1 = var_v0->field_10;
                if ((temp_fv1 >= 0.0f) && (temp_fv1 < (f32)D_800BE624)) {
                    var_v0->field_2A = ((u16 *)D_800BE9C4)[
                        (s32)temp_fv0 + ((s32)temp_fv1 * D_800BE620)];
                }
            }
            var_v0 = var_v0->next;
        } while (var_v0 != 0);
    }
}
typedef union Game1AB530BytePair {
    u16 word;
    u8 bytes[2];
} Game1AB530BytePair;

s32 func_1517E4A8(s32, void *, s32, s32, s32, s32, s8 *);
s32 func_1517EAAC(f32, f32, f32, f32 *, f32 *);
s32 func_1517EC1C(void *, s32 *);
extern f32 *D_8008CFFC[];
extern Game1AB530BytePair D_8008D004, D_8008D008, D_8008D00C;
extern void *D_800B0DF0;
extern u8 D_800DCDD0;
extern s8 D_800DD2D0, D_800DDD60;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517E28C CURRENT (4232) */
s32 func_1517E28C(s32 arg0, s32 arg1) {
    s32 depth;
    s32 distance;
    Game1AB530BytePair first;
    Game1AB530BytePair second;
    Game1AB530BytePair third;
    s32 skip;
    s32 display;
    s8 *flag;
    u8 index;
    f32 *position;
    Game1AB530Node *node;

    display = arg0;
    first = D_8008D004;
    second = D_8008D008;
    third = D_8008D00C;
    node = D_800DDD64;
    D_800DDD60 = 0;
    if (node != 0) {
        do {
            if (*((u8 *)node + 0x30) != 0) {
                skip = 0;
                if (*((u8 *)node + 0x2E) & 1) {
                    if (D_800DCDD0 == 0) {
                        skip = 1;
                    } else {
                        position = D_8008CFFC[*((u8 *)D_800B0DF0 + 0x10)];
                        depth = 0xFF;
                        if (func_1517EAAC(position[0], position[1], position[2], &node->field_C, &node->field_10) != 1) {
                            skip = 1;
                        }
                        if (node->field_2A != 0xFFFC) {
                            depth = -1;
                        }
                    }
                } else {
                    if (func_1517EC1C(node, &distance) != 1) {
                        skip = 1;
                    }
                    depth = -1;
                    if ((*(u16 *)((u8 *)node + 0x2C) - distance) < 0x1E) {
                        depth = 0x100;
                    }
                }
                flag = 0;
                if (*((u8 *)node + 0x2E) & 2) {
                    flag = &D_800DD2D0;
                }
                if (skip == 0) {
                    index = *((u8 *)node + 0x2F);
                    display = func_1517E4A8(display, node, first.bytes[index], second.bytes[index], third.bytes[index], depth, flag);
                } else if (flag != 0) {
                    *flag = 0;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return display;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517E28C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517E28C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517E4A8.s")
typedef union Game1AB530DisplayCommand {
    struct {
        u32 word0;
        u32 word1;
    } words;
    u64 alignment;
} Game1AB530DisplayCommand;

#define GAME1AB530_COMMAND(pkt, first, second)                  \
{                                                              \
    Game1AB530DisplayCommand *command = (pkt);                  \
    command->words.word0 = (u32)(first);                        \
    command->words.word1 = (u32)(second);                       \
}

Game1AB530DisplayCommand *func_1517EA4C(Game1AB530DisplayCommand *arg0) {
    GAME1AB530_COMMAND(arg0++, 0xE7000000, 0);
    GAME1AB530_COMMAND(arg0++, 0xFCFFB3FF, 0xFF65FEFF);
    GAME1AB530_COMMAND(arg0++, 0xEF002C0F, 0x00504344);
    return arg0;
}

#undef GAME1AB530_COMMAND
typedef struct Game1AB530TransformRef {
    u8 pad0[0x380];
    f32 field380;
    u8 pad384[4];
    f32 field388;
    u8 pad38C[0x260];
    f32 field5EC;
} Game1AB530TransformRef;

typedef struct Game1AB530CameraInfo {
    u8 pad0[0xC];
    f32 fieldC;
    f32 field10;
} Game1AB530CameraInfo;

void func_15110360(s32, void *, f32, f32, f32);
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern s32 D_80082FA4;
extern u8 *D_800DBFF0;
extern u8 *D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517EAAC CURRENT (743) */
s32 func_1517EAAC(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    f32 output[4];
    u8 transform[0x40];
    f32 camera_x;
    f32 camera_y;
    f32 ratio;
    f32 x_component;
    f32 y_component;
    Game1AB530TransformRef *transform_ref;
    Game1AB530CameraInfo *camera_info;

    transform_ref = (Game1AB530TransformRef *)(D_800DBFF0 + (D_80082FA4 * 0x9A0));
    func_15110360(D_80082FA4, transform, -transform_ref->field388, -transform_ref->field380, transform_ref->field5EC);
    camera_info = (Game1AB530CameraInfo *)(D_800BE628 + (D_80082FA4 * 0x180));
    camera_x = camera_info->fieldC;
    camera_y = camera_info->field10;
    func_150A7A00(transform, arg0, arg1, arg2, &output[3], &output[2], &output[1], &output[0]);
    if (output[0] > 10.0f) {
        ratio = 1.0f / output[0];
        x_component = output[3] * camera_x * ratio;
        output[3] = x_component;
        y_component = output[2] * camera_y * ratio;
        output[2] = y_component;
        *arg3 = camera_x + x_component;
        *arg4 = camera_y - y_component;
        return 1;
    }
    *arg3 = 0.0f;
    *arg4 = 0.0f;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517EAAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517EAAC.s")
typedef struct Game1AB530ProjectionNode {
    f32 position[3];
    f32 screen[2];
    f32 direction[3];
    f32 threshold;
    void *next;
    u16 field28;
    u16 encoded;
    u16 depth;
    u8 flags;
} Game1AB530ProjectionNode;

typedef struct Game1AB530DepthEncoding {
    s32 shift;
    s32 base;
} Game1AB530DepthEncoding;

typedef struct Game1AB530ViewPosition {
    u8 pad0[0x2F8];
    f32 position[3];
} Game1AB530ViewPosition;

typedef struct Game1AB530DepthRange {
    u8 pad0[0x44];
    s16 scale;
    u8 pad46[6];
    s16 offset;
} Game1AB530DepthRange;

s32 func_1509563C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);
f32 sqrtf(f32);
__pragma(1, sqrtf);
extern Game1AB530DepthEncoding D_80089630[];
extern u8 D_800BE9C0;

s32 func_1517EC1C(void *arg0, s32 *arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    u16 encoded;
    Game1AB530DepthEncoding *encoding;
    Game1AB530DepthRange *range;
    f32 projected;
    f32 distance;
    if (func_1509563C(((Game1AB530ProjectionNode *)arg0)->position[0], ((Game1AB530ProjectionNode *)arg0)->position[1], ((Game1AB530ProjectionNode *)arg0)->position[2],
                      &((Game1AB530ProjectionNode *)arg0)->screen[0], &((Game1AB530ProjectionNode *)arg0)->screen[1], &projected, &distance, 4000.0f) == 1) {
        if (((Game1AB530ProjectionNode *)arg0)->flags & 4) {
            dx = ((Game1AB530ProjectionNode *)arg0)->position[0] - ((Game1AB530ViewPosition *)D_800DBFF0)->position[0];
            dy = ((Game1AB530ProjectionNode *)arg0)->position[1] - ((Game1AB530ViewPosition *)D_800DBFF0)->position[1];
            dz = ((Game1AB530ProjectionNode *)arg0)->position[2] - ((Game1AB530ViewPosition *)D_800DBFF0)->position[2];
            dx = ((dx * ((Game1AB530ProjectionNode *)arg0)->direction[0] + dy * ((Game1AB530ProjectionNode *)arg0)->direction[1] + dz * ((Game1AB530ProjectionNode *)arg0)->direction[2]) /
                 sqrtf(dx * dx + dy * dy + dz * dz));
            if (dx < ((Game1AB530ProjectionNode *)arg0)->threshold) {
                return 1;
            }
        }
        encoded = ((Game1AB530ProjectionNode *)arg0)->encoded;
        encoding = &D_80089630[(s32)encoded >> 13];
        *arg1 = (u32)(encoding->base + ((((s32)encoded >> 2) & 0x7FF) << encoding->shift)) >> 3;
        range = (Game1AB530DepthRange *)((u32)D_800BE628 + D_800BE9C0 * 0x10);
        ((Game1AB530ProjectionNode *)arg0)->depth = (u32)(((f32)range->offset + (projected / distance) * (f32)range->scale) * 32.0f);
        return 1;
    }
    return 0;
}
