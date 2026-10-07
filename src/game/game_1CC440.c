#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CC440.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_attachment_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519EF90
 * - func_1519F108
 * - func_1519F168
 * - func_1519F1C8
 * - func_1519F48C
 * - func_1519F4F0
 * - func_1519F7F0
 * - func_1519FE6C
 * - func_151A084C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1CC440NodeData {
    s32 field0;
    u8 pad4[4];
    s32 field8;
} Game1CC440NodeData;

typedef struct Game1CC440Node {
    u8 pad0[0x18];
    void *field18;
    u8 field1C;
    u8 pad1D[0x3B];
    Game1CC440NodeData data58;
} Game1CC440Node;

typedef struct Game1CC440State {
    u8 pad0[0x20];
    s32 mode;
    u8 pad24[0x74];
    Game1CC440Node **link98;
} Game1CC440State;

typedef struct Game1CC440Attachments {
    Game1CC440State *field0;
    Game1CC440State *field4;
    Game1CC440State *field8;
    Game1CC440State *fieldC;
} Game1CC440Attachments;

typedef struct Game1CC440AttachmentOwner {
    u8 pad0[0x58];
    Game1CC440Attachments attachments;
} Game1CC440AttachmentOwner;

void func_151478F4(s32);
void func_15147928(s32);

/* Call context: func_151423D8: unique active project prototype */
/* Call context: func_15143E08: unique active project prototype */
f32 func_151423D8(u8);
s32 func_15143E08(u16 *);
extern f32 D_800A8CE0;
extern f32 D_800A8CE4;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519EF90 CURRENT (2107) */
s32 func_1519EF90(u8 *arg0, u8 arg1, u8 *arg2) {
    u8 *sp38;
    f32 sp28;
    u8 sp1F;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft4;
    f32 var_ft5;
    u8 *temp_v0;
    f32 var_fv0;
    u16 *temp_a3;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0));
    sp38 = (void *)(temp_v0 + 0x58);
    temp_a3 = (void *)(*(u16 **)((u8 *)temp_v0 + 0x18));
    if (*(s32 *)((u8 *)temp_a3 + 0x1D4) == 0) {
        return 0;
    }
    var_ft4 = *(f32 *)((u8 *)temp_a3 + 0x14);
    temp_fa0 = var_ft4 - *(f32 *)((u8 *)arg0 + 0x20);
    temp_fa1 = *(f32 *)((u8 *)temp_a3 + 0x1C) - *(f32 *)((u8 *)arg0 + 0x24);
    if ((D_800A8CE0 < fabsf(temp_fa0)) || (D_800A8CE0 < fabsf(temp_fa1))) {
        temp_fv1 = 1.0f / sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
        var_ft5 = temp_fa1 * temp_fv1;
        sp28 = temp_fa0 * temp_fv1;
    } else {
        sp1F = func_15143E08(temp_a3);
        var_ft5 = func_151423D8(sp1F & 0xFF);
        sp28 = func_151423D8(sp1F - 0x40);
        var_ft4 = *(f32 *)((u8 *)temp_a3 + 0x14);
    }
    if (arg1 == 6) {
        var_fv0 = *(f32 *)((u8 *)sp38 + 0x10);
    } else {
        var_fv0 = -*(f32 *)((u8 *)sp38 + 0x10);
    }
    *(f32 *)((u8 *)arg2 + 0) = (f32) (var_ft4 + (var_fv0 * var_ft5));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)temp_a3 + 0x1C) - (var_fv0 * sp28));
    temp_fv1_2 = *(f32 *)((u8 *)temp_a3 + 0x118);
    if (temp_fv1_2 < D_800A8CE4) {
        *(f32 *)((u8 *)arg2 + 4) = (f32) *(f32 *)((u8 *)temp_a3 + 0x18);
        return 1;
    }
    *(f32 *)((u8 *)arg2 + 4) = temp_fv1_2;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519EF90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519EF90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F108 CURRENT (735) */
void func_1519F108(Game1CC440State *arg0) {
    register Game1CC440Node **link = arg0->link98;
    register Game1CC440Node *node = *link;

    if (node != 0) {
        Game1CC440NodeData *data = &node->data58;

        if (arg0->mode == 6) {
            data->field0 = 0;
        }
        if (arg0->mode == 7) {
            data->field8 = 0;
        }
    }
    func_151478F4((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F108 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F108.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F168 CURRENT (465) */
void func_1519F168(Game1CC440State *arg0) {
    Game1CC440State *owner = arg0;
    Game1CC440Node *node = *owner->link98;

    if (node != 0) {
        arg0 = (Game1CC440State *)&node->data58;
        if (owner->mode == 6) {
            ((Game1CC440NodeData *)arg0)->field0 = 0;
        }
        if (owner->mode == 7) {
            ((Game1CC440NodeData *)arg0)->field8 = 0;
        }
    }
    func_15147928((s32) owner);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F168 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F168.s")
typedef struct Game1CC440Vector {
    f32 x, y, z;
} Game1CC440Vector;

typedef struct Game1CC440Spawn {
    Game1CC440Vector position;
    s16 duration;
    u16 flags;
    s32 mode;
    u8 pad14;
    u8 field15;
    u8 pad16[2];
} Game1CC440Spawn;

typedef struct Game1CC440Config {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 field8;
    f32 fieldC;
    Game1CC440Vector position;
    f32 field1C;
    f32 field20;
    f32 field24;
    s16 field28;
    u8 color[3];
    u8 pad2D;
    s16 field2E;
    s16 field30;
    s16 field32;
    s16 field34;
    u8 pad36[2];
    f32 field38;
    f32 field3C;
    u8 field40;
    u8 field41;
    u8 field42;
    u8 field43;
    u8 field44;
    u8 field45;
    s16 field46;
    s16 field48;
    s16 field4A;
    f32 field4C;
} Game1CC440Config;

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_151D8E20(void);
s32 func_1519EF90(u8 *, u8, u8 *);
extern f32 D_800A8CE8;
extern f32 D_800A8CEC;
extern u8 D_800AB414[][3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F1C8 CURRENT (2508) */
s32 func_1519F1C8(void *arg0, u8 arg1, ...) {
    u8 *actor;
    Game1CC440Spawn spawn;
    Game1CC440Config config;
    void *saved;
    u8 color_id;
    u8 *color;
    void *result;

    actor = *(u8 **)((u8 *)arg0 + 0x18);
    color_id = func_151D8E20();
    spawn.flags = 0x42;
    spawn.duration = 0x12C;
    spawn.field15 = 0xA;
    config.field2E = 0xC8;
    config.field40 = 3;
    config.owner = arg0;
    config.type = 6;
    config.field41 = 0x55;
    config.field42 = 3;
    config.field43 = 0x55;
    config.field44 = 0x88;
    config.field45 = 0xC4;
    config.field28 = 0;
    config.field46 = 0;
    config.field30 = 0xFF;
    config.field32 = 0x28;
    config.field34 = 0x19;
    config.field48 = 6;
    config.field4A = 0x325;
    config.field8 = D_800A8CE8;
    config.field38 = D_800A8CEC;
    config.field3C = 1.0f;
    config.fieldC = 0.0f;
    config.field1C = 0.0f;
    spawn.mode = arg1;
    config.field4C = 1.5f;
    config.field20 = *(f32 *)(actor + 0x14);
    config.field24 = *(f32 *)(actor + 0x1C);
    if (func_1519EF90((u8 *)&config, arg1 & 0xFF, (u8 *)&spawn.position) != 0) {
        config.position = spawn.position;
        spawn.flags |= 4;
    }
    color = D_800AB414[color_id];
    config.color[0] = color[0];
    config.color[1] = color[1];
    config.color[2] = color[2];
    result = func_15147A80(&spawn, (void *)0x50, 0x24, 5, 5, 5, 0, 0,
                           (s32)((u8 *)arg0 + 0x34), 0xFF, 1);
    if (result != 0) {
        saved = result;
        func_10022EC0(*(void **)((u8 *)result + 0x98), &config, 0x50U);
        result = saved;
    }
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F1C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F1C8.s")
s32 func_1519F1C8(void *, u8, ...);

void func_1519F3B8(void *arg0) {
    void *temp_v1;

    temp_v1 = (u8 *)arg0 + 0x58;
    *(s32 *)temp_v1 = func_1519F1C8(arg0, 6);
    *(s32 *)((u8 *)temp_v1 + 4) = 0;
    *(s32 *)((u8 *)temp_v1 + 8) = func_1519F1C8(arg0, 7);
    *(s32 *)((u8 *)temp_v1 + 0xC) = 0;
}
void func_1519F48C(Game1CC440State *);
void func_151A0928(void *);
void func_1516972C(void *);

void func_1519F400(void *arg0) {
    Game1CC440State *temp_a0;
    register void *temp_s0;

    temp_s0 = (u8 *)arg0 + 0x58;
    if (*(Game1CC440State **)temp_s0 != 0) {
        func_1519F48C(*(Game1CC440State **)temp_s0);
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 8);
    if (temp_a0 != 0) {
        func_1519F48C(temp_a0);
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 4);
    if (temp_a0 != 0) {
        func_151A0928(temp_a0);
        func_1516972C(*(void **)((u8 *)temp_s0 + 4));
    }
    temp_a0 = *(Game1CC440State **)((u8 *)temp_s0 + 0xC);
    if (temp_a0 != 0) {
        func_151A0928(temp_a0);
        func_1516972C(*(void **)((u8 *)temp_s0 + 0xC));
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F48C CURRENT (35) */
void func_1519F48C(Game1CC440State *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_v1 = (void *)(*(void **)((u8 *)temp_v0 + 0));
    if (temp_v1 != 0) {
        temp_v1 += 0x58;
        if (*(s32 *)((u8 *)arg0 + 0x20) == 6) {
            *(s32 *)temp_v1 = 0;
        }
        if (*(s32 *)((u8 *)arg0 + 0x20) == 7) {
            *(s32 *)(temp_v1 + 8) = 0;
        }
        *(void **)((u8 *)temp_v0 + 0) = 0;
    }
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) & 0xFFFD);
    *(u8 *)((u8 *)temp_v0 + 4) = (u8) (*(u8 *)((u8 *)temp_v0 + 4) | 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F48C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F48C.s")
typedef struct Game1CC440TrailPoint {
    f32 x, z, y, fieldC;
    s16 size, delay, alpha;
    u8 pad16[2];
    s16 life;
    u8 pad1A[2];
    f32 velocityX, velocityZ;
} Game1CC440TrailPoint;

s32 func_15045800(Game1CC440Vector *, u16, f32, void *);
extern f32 D_800A8CF0, D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519F4F0 CURRENT (135) */
s32 func_1519F4F0(u8 *arg0) {
    Game1CC440TrailPoint *base;
    Game1CC440TrailPoint *point;
    Game1CC440Config *config;
    s32 index, expired, delay;
    register f32 offset, bound;
    f32 probe[3];

    config = *(Game1CC440Config **)(arg0 + 0x98);
    base = *(Game1CC440TrailPoint **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) < 2 && (config->type & 1)) return 0;
    index = *(s8 *)(arg0 + 0x2E);
    if (index != *(s8 *)(arg0 + 0x2D)) {
        offset = 30.0f;
        bound = D_800A8CF0;
        do {
            index--;
            expired = 0;
            if (index < 0) index = arg0[0x25] - 1;
            point = base + index;
            point->life = (u32)point->life - (u32)D_800BE9E4;
            if (point->life < 0) expired = 1;
            delay = point->delay;
            point->alpha = 255;
            if (delay > 0) point->delay = (u32)delay - (u32)D_800BE9E4;
            else point->size = (u32)point->size - (u32)config->field34 * (u32)D_800BE9E4;
            point->fieldC += config->field3C * D_800BE9A4;
            point->x += point->velocityX * D_800BE9A4;
            point->z += point->velocityZ * D_800BE9A4;
            probe[0] = point->x;
            probe[1] = point->y + offset;
            probe[2] = point->z;
            if (bound < fabsf(probe[0]) || bound < fabsf(probe[2])) expired = 1;
            else if (func_15045800((Game1CC440Vector *)probe, 0, point->y - offset, arg0 + 0x60) != 0) {
                point->y = *(f32 *)(arg0 + 0x60);
            } else expired = 1;
            if (point->size < 0) expired = 1;
            if (expired != 0) {
                if (index != *(s8 *)(arg0 + 0x2D)) {
                    do {
                        *(s8 *)(arg0 + 0x2D) += 1;
                        if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) *(s8 *)(arg0 + 0x2D) = 0;
                        *(s8 *)(arg0 + 0x2C) -= 1;
                    } while (index != *(s8 *)(arg0 + 0x2D));
                }
                base[*(s8 *)(arg0 + 0x2D)].size = 0;
            }
        } while (index != *(s8 *)(arg0 + 0x2D));
    }
    config->field46 = (u32)config->field46 + (u32)config->field48 * (u32)D_800BE9E4;
    if (*(s8 *)(arg0 + 0x2C) > 0) {
        point = (Game1CC440TrailPoint *)((u8 *)base + *(s8 *)(arg0 + 0x2D) * 0x24);
        *(f32 *)(arg0 + 0x54) = point->x;
        *(f32 *)(arg0 + 0x58) = point->y;
        *(f32 *)(arg0 + 0x5C) = point->z;
    } else {
        *(f32 *)(arg0 + 0x54) = 0.0f;
        *(f32 *)(arg0 + 0x58) = 0.0f;
        *(f32 *)(arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519F4F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F4F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F7F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519FE6C.s")
/* Call context: func_151A0928: unique active project prototype */
void func_151A0928(void *);
s32 func_1519F1C8(void *, u8, ...);                 /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A084C CURRENT (1355) */
void func_151A084C(u8 *arg0) {
    struct Lookup { Game1CC440Node *node; u8 mode; };
    s32 temp_v0_2;
    u8 var_v1;
    Game1CC440Node *temp_a0;
    u8 *temp_a1;
    u8 *temp_v0;
    struct Lookup *temp_a2;
    Game1CC440NodeData *temp_t0;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x28));
    var_v1 = 0;
    temp_a2 = (void *)(arg0 + 0x28);
    temp_a1 = (void *)(*(void **)((u8 *)temp_v0 + 0x18));
    temp_t0 = (Game1CC440NodeData *)(temp_v0 + 0x58);
    if (*(s32 *)((u8 *)temp_a1 + 0) == 0) {
        var_v1 = 1;
    }
    temp_a0 = temp_a2->node;
    if (temp_a0->field1C != *(u8 *)((u8 *)temp_a1 + 0x3B)) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && (*(s32 *)((u8 *)temp_a1 + 0x1D4) != 0)) {
        temp_v0_2 = func_1519F1C8(temp_a0, *(u8 *)((u8 *)temp_a2 + 4), temp_a2, arg0);
        var_v1 = 1;
        if (*(u8 *)((u8 *)temp_a2 + 4) == 6) {
            temp_t0->field0 = temp_v0_2;
        } else {
            temp_t0->field8 = temp_v0_2;
        }
    }
    if (var_v1 != 0) {
        func_151A0928(arg0);
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        *(u8 *)((u8 *)arg0 + 0xD) = (u8) (*(u8 *)((u8 *)arg0 + 0xD) | 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A084C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A084C.s")
void func_151A0928(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x28) + 0x58);
    if (*(u8 *)((u8 *)arg0 + 0x2C) == 6) {
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
        return;
    }
    *(s32 *)((u8 *)temp_v0 + 0xC) = 0;
}
typedef struct {
    void *field0;
    u8 field4;
} Game1CC440Lookup;

void func_1519F48C(Game1CC440State *);

void func_151A0950(Game1CC440State *arg0, Game1CC440Lookup *arg1, u8 arg2) {
    Game1CC440Node **temp_v1;
    Game1CC440Node *temp_v0;

    temp_v1 = arg0->link98;
    if (arg2 == 0xA) {
        temp_v0 = *temp_v1;
        if (temp_v0 != 0) {
            void *key = temp_v0->field18;
            if ((arg1->field0 == key) ||
                (arg1->field4 == temp_v0->field1C)) {
                func_1519F48C(arg0);
            }
        }
    }
}
void func_1516972C(void *);

void func_151A09B4(void *arg0, void *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = *(void **)(*(u8 **)((u8 *)arg0 + 0x28) + 0x18);
    if ((arg2 == 0) && ((temp_v0 == *(void **)arg1) ||
        (*(u8 *)((u8 *)temp_v0 + 0x3B) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_151A0928(arg0);
        func_1516972C(arg0);
    }
}
