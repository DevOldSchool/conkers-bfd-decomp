#include "types.h"

/*
 * Reviewed source unit: src/game/game_13F9D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_code_selected_segments.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15112520
 * - func_15112A80
 * - func_15113180
 * - func_15113218
 * - func_151135C4
 * - func_151137D4
 * - func_15113C88
 * - func_15113E54
 * - func_15114188
 * - func_15114348
 * - func_1511473C
 * - func_15114A1C
 * - func_15114B94
 * - func_15114D24
 * - func_15114F44
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define placed_object_test_actor_mask func_15114050
#define placed_object_first_actor_mask_index func_151140C4
#define placed_object_build_orientation func_151148A8
#define placed_object_build_transform func_1511490C
#define placed_object_find_by_id func_151149AC

#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15112A80.s")
extern s32 D_800DBEF0;
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113180 CURRENT (185) */
void func_15113180(void) {
    s32 var_v0;
    s32 var_v1;
    u8 temp_a1;
    u8 *temp_a0;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DBEF0 > 0) {
        do {
            temp_a0 = (u8 *)D_800DBEF4 + var_v1;
            temp_a0[0x6F] = (u8) (temp_a0[0x6F] & ~0x40);
            temp_a0 = (u8 *)D_800DBEF4 + var_v1;
            temp_a1 = temp_a0[0x6F];
            if (((temp_a1 & 0xF) || ((temp_a0[0x70] & 4) == 4)) && (*(s32 *)(temp_a0 + 0x38) != 0)) {
                temp_a0[0x6F] = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DBEF0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113180 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113180.s")
typedef struct {
    u8 transform[0x30];
    f32 position_x;
    f32 position_y;
    f32 position_z;
    u8 pad_3C[4];
} Game13F9D0Transform;

typedef struct {
    f32 rotationXDegrees;
    f32 rotationYDegrees;
    f32 rotationZDegrees;
} Game13F9D0TransformArgs;

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2C;
    s32 field_30;
    s32 field_34;
    u32 field_38;
    f32 field_3C;
} Game13F9D0Matrix;

typedef struct {
    u8 pad_0[0x10];
    s16 positionX;
    s16 positionY;
    s16 positionZ;
    u8 pad_16[2];
    f32 verticalOffset;
    u8 pad_1C[0x10];
    s32 scaleXBits;
    s32 scaleYBits;
    s32 scaleZBits;
    u8 pad_38[0x16];
    u8 kind4E;
    u8 pad_4F[0x21];
    u8 flags70;
} Game13F9D0MotionArgs;

typedef struct Game13F9D0DrawEntry {
    u16 index;
    u16 value;
} Game13F9D0DrawEntry;

void *func_151733D8(void *, s32);
s32 func_151137D4(s32, void *, s32, s32, s32, s32);
s32 func_1515E544(s32, s32, s32, s32, void *);
extern u8 **D_80089240;
extern u8 **D_80089250[];
extern u8 D_80089470;
extern u8 D_800BE9C0;
extern u8 D_800D9BD0[];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9E21;
extern u16 D_800DBEE8[];

typedef struct Game13F9D0AttachedActor {
    u8 pad0[0x14];
    f32 xyz[3];
    u8 pad20[0x70];
    s16 field90;
    u8 pad92[0x142];
    Game13F9D0Transform *transform1D4;
    u8 pad1D8[0x154];
} Game13F9D0AttachedActor;

s32 func_150859AC(s32, s32);
void func_150A7790(void *, s32);
void func_150A7B80(void *);
void func_150A7CB0(Game13F9D0Matrix *, s32, s32, s32);
void func_150442C0(f32 [4][4], f32, f32, f32);
void placed_object_build_transform(Game13F9D0Transform *, Game13F9D0MotionArgs *);
extern s32 D_80082FA0;
extern u8 D_800CC2D0;
extern u8 D_800DBF08[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113218 CURRENT (4727) */
void func_15113218(void) {
    Game13F9D0Transform matrix;
    s32 view;
    f32 translation[3];
    s32 offset;
    u16 *count;
    u8 ***table;
    Game13F9D0MotionArgs *motion;
    Game13F9D0AttachedActor *actor;
    Game13F9D0Transform *parent;
    u16 index;
    u16 countValue;
    u8 kind;

    if (D_80082FA0 >= 0) {
        view = 0;
        do {
            if (func_150859AC((s16)view, 0) != 0) {
                count = &D_800DBEE8[view];
                countValue = *count;
                if (countValue > 0) {
                    table = &D_80089240 + view;
                    offset = 0;
                    do {
                        index = ((Game13F9D0DrawEntry *)(**table + offset))->index;
                        motion = (Game13F9D0MotionArgs *)(index * 0xA0 + D_800DBEF4);
                        if ((motion->flags70 & 1) == 1) {
                            func_150A7B80(*D_80089250[D_800BE9C0] + (index << 6));
                            countValue = *count;
                        } else {
                            kind = motion->kind4E;
                            if (kind == 3) {
                            } else if (kind < 3) {
                                func_1511490C(&matrix, motion);
                                func_150A7790(&matrix,
                                    (s32)(*D_80089250[D_800BE9C0] +
                                    (((Game13F9D0DrawEntry *)(**table + offset))->index << 6)));
                                countValue = *count;
                            } else if (kind >= 0x65 && kind < 0x7D) {
                                actor = &((Game13F9D0AttachedActor *)&D_800CC2D0)[kind - 100];
                                if (actor->transform1D4 == 0) {
                                    func_150A7CB0((Game13F9D0Matrix *)&matrix,
                                        motion->scaleXBits, motion->scaleYBits, motion->scaleZBits);
                                    matrix.position_x = actor->xyz[0];
                                    matrix.position_y = actor->xyz[1];
                                    matrix.position_z = actor->xyz[2];
                                    func_150A7790(&matrix,
                                        (s32)(*D_80089250[D_800BE9C0] +
                                        (((Game13F9D0DrawEntry *)(**table + offset))->index << 6)));
                                    countValue = *count;
                                } else {
                                    translation[2] = 0.0f;
                                    translation[0] = translation[2];
                                    translation[1] = (f32)actor->field90;
                                    parent = actor->transform1D4;
                                    func_150A7CB0((Game13F9D0Matrix *)&matrix,
                                        motion->scaleXBits, motion->scaleYBits, motion->scaleZBits);
                                    matrix.position_x = parent->position_x;
                                    matrix.position_y = parent->position_y;
                                    matrix.position_z = parent->position_z;
                                    func_150442C0((f32 (*)[4])&matrix,
                                        translation[0], translation[1], translation[2]);
                                    motion->positionX = (s32)matrix.position_x;
                                    motion->positionY = (s32)matrix.position_y;
                                    motion->positionZ = (s32)matrix.position_z;
                                    func_150A7790(&matrix,
                                        (s32)(*D_80089250[D_800BE9C0] +
                                        (((Game13F9D0DrawEntry *)(**table + offset))->index << 6)));
                                    countValue = *count;
                                }
                            } else {
                                func_150A7790(D_800DBF08 + (D_800BE9C0 << 6),
                                    (s32)(*D_80089250[D_800BE9C0] + (index << 6)));
                                countValue = *count;
                            }
                        }
                        offset += 4;
                    } while (offset < countValue * 4);
                }
            }
            view++;
        } while (D_80082FA0 >= view);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113218 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113218.s")


typedef struct Game13F9D0Command {
    u32 word0;
    u32 word1;
} Game13F9D0Command;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151135C4 CURRENT (4056) */
void *func_151135C4(Game13F9D0Command *arg0, s32 arg1, s32 arg2) {
    s32 viewOffset;
    s32 flags;
    s32 index;
    s32 offset;
    u16 *count;
    u8 ***table;
    Game13F9D0DrawEntry *entry;
    Game13F9D0Command *command;

    if (arg1 == 0) {
        flags = 0;
    } else {
        flags = 0x10;
    }
    command = func_151733D8(arg0, 0);
    command[0].word0 = 0xD9A3FFFF;
    command[0].word1 = 0;
    command[1].word1 = 0x20000;
    command[1].word0 = 0xD9FFFFFF;
    viewOffset = (s16)arg2 * 4;
    arg0 = (Game13F9D0Command *)func_1515E544((s32)(command + 2),
                          *(s32 *)((u8 *)D_800D9E10 + viewOffset),
                          D_800D9E20, D_800D9E21,
                          D_800D9BD0 + (s16)arg2 * 0x10 + D_800BE9C0 * 8);
    count = &D_800DBEE8[(s16)arg2];
    index = 0;
    if (*count > 0) {
        table = (u8 ***)((u8 *)&D_80089240 + viewOffset);
        offset = 0;
        do {
            entry = (Game13F9D0DrawEntry *)(**table + offset);
            arg0 = (Game13F9D0Command *)func_151137D4((s32)arg0, (void *)(entry->index * 0xA0 + D_800DBEF4),
                                  (s32)(*D_80089250[D_800BE9C0] + (entry->index << 6)),
                                  (s16)arg2, entry->value, flags);
            index++;
            offset += 4;
        } while (index < *count);
    }
    command = arg0++;
    command->word0 = 0xDA380003;
    command->word1 = (u32)&D_80089470;
    command = arg0++;
    command->word0 = 0xD9AFFDFF;
    command->word1 = 0;
    command = arg0++;
    command->word1 = 0x20000;
    command->word0 = 0xD9FFFFFF;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151135C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151135C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_151137D4.s")
s32 func_15022B08(s32, s32);
s32 func_150859AC(s32, s32);
void func_1516972C(u8 *);
void *func_1510D970(s32, s32, s32, s32, s32);
extern s32 D_80082FA0;
extern u8 D_800C35EA;
extern u8 D_800C3658;

typedef struct Game13F9D0ActiveEntry {
    u8 pad0[0x4C];
    u8 enabled;
    u8 pad4D[2];
    u8 flags;
    u8 pad50[0x20];
    u8 state;
    u8 pad71[0x1A];
    u8 players[9];
    u8 *callback;
} Game13F9D0ActiveEntry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113C88 CURRENT (2105) */
void func_15113C88(void) {
    s32 player;
    s32 blocked;
    s32 index;
    s32 offset;
    s32 active;
    u8 *callback;
    Game13F9D0ActiveEntry *entry;

    index = 0;
    offset = 0;
    if (D_800DBEF0 > 0) {
        do {
            blocked = 0;
            player = 0;
            entry = (Game13F9D0ActiveEntry *)(offset + D_800DBEF4);
            if (D_80082FA0 > 0) {
                do {
                    if ((func_150859AC((s16)player, 0) != 0) &&
                        (entry->players[player] == 0)) {
                        blocked = 1;
                        break;
                    }
                    player++;
                } while (player < D_80082FA0);
            }
            if (!(entry->state & 8) && (entry->enabled != 0) &&
                ((entry->flags & 0x10) != 0x10) && (blocked == 0)) {
                if ((D_800C3658 == 0) && (D_800C35EA == 1)) {
                    if (func_15022B08(index, 0) != 0) {
                        goto check_flags;
                    }
                    goto inactive;
                }
check_flags:
                active = 1;
                if (!(entry->flags & 1)) {
                    goto inactive;
                }
            } else {
inactive:
                active = 0;
            }
            if (active != 0) {
                if (entry->callback == 0) {
                    entry->callback = func_1510D970(1, (s32)entry, 0, 1, 0);
                }
            } else {
                callback = entry->callback;
                if (callback != 0) {
                    func_1516972C(callback);
                    entry->callback = 0;
                }
            }
            index++;
            offset += 0xA0;
        } while (index < D_800DBEF0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113C88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113C88.s")
extern s32 D_80087380;
extern s32 D_800DBF98;
extern void *D_800D23C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15113E54 CURRENT (3071) */
void func_15113E54(s32 arg0) {
    s16 var_s3;
    s16 var_s4;
    s16 var_s5;
    s32 temp_s2;
    s32 var_fp;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s6;
    s32 var_s7;
    u16 temp_v0;
    u16 var_a0;
    void *temp_s0;
    void *temp_s0_2;
    void *var_a1;

    var_s3 = 0;
    var_s4 = 0;
    temp_s2 = D_800DBEF0 - D_800DBF98;
    var_s5 = 0;
    var_s6 = 0;
    var_fp = 0;
    if (temp_s2 > 0) {
        var_s1 = 0;
        do {
            temp_s0 = (void *)(var_s1 + D_800DBEF4);
            if (((*(u8 *)((u8 *)temp_s0 + 0x6F) & 0x40) == 0x40) && (*(u8 *)((u8 *)temp_s0 + 0x6E) == 0)) {
                (*(void (**)(void *))((u8 *)temp_s0 + 0x38))(temp_s0);
            }
            var_fp += 1;
            var_s1 += 0xA0;
        } while (var_fp != temp_s2);
        var_fp = 0;
    }
    if (D_80087380 > 0) {
        var_s7 = 0;
        var_a1 = D_800D23C0;
        do {
            if (((s32) *(u16 *)((u8 *)var_a1 + 8) >> 0xC) == 2) {
                var_a0 = *(u16 *)((u8 *)var_a1 + 2);
                var_s1_2 = 0;
                var_s2 = 0;
                if ((s32) var_a0 > 0) {
                    do {
                        temp_v0 = *(u16 *)((u8 *)D_800D23C0 + (var_fp * 0x18) + var_s2 + 8);
                        if (((s32) temp_v0 >> 0xC) == 2) {
                            temp_s0_2 = (void *)(((temp_v0 & 0xFFF) * 0xA0) + D_800DBEF4);
                            if (((*(u8 *)((u8 *)temp_s0_2 + 0x6F) & 0x40) == 0x40) && (*(u8 *)((u8 *)temp_s0_2 + 0x6E) == 0)) {
                                if (var_s1_2 != 0) {
                                    *(s16 *)((u8 *)temp_s0_2 + 0x5A) = var_s3;
                                    *(s16 *)((u8 *)temp_s0_2 + 0x5C) = var_s4;
                                    *(s16 *)((u8 *)temp_s0_2 + 0x5E) = var_s5;
                                    *(s32 *)((u8 *)temp_s0_2 + 0x80) = var_s6;
                                }
                                (*(void (**)(void *))((u8 *)temp_s0_2 + 0x38))(temp_s0_2);
                                var_a1 = (u8 *)D_800D23C0 + var_s7;
                                var_a0 = *(u16 *)((u8 *)var_a1 + 2);
                            }
                            if (var_s1_2 == 0) {
                                var_s3 = *(s16 *)((u8 *)temp_s0_2 + 0x5A);
                                var_s4 = *(s16 *)((u8 *)temp_s0_2 + 0x5C);
                                var_s5 = *(s16 *)((u8 *)temp_s0_2 + 0x5E);
                                var_s6 = *(s32 *)((u8 *)temp_s0_2 + 0x80);
                            }
                        }
                        var_s1_2 += 1;
                        var_s2 += 2;
                    } while (var_s1_2 < (s32) var_a0);
                }
            }
            var_fp += 1;
            var_s7 += 0x18;
            var_a1 = (u8 *)var_a1 + 0x18;
        } while (var_fp < D_80087380);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15113E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15113E54.s")

typedef struct Game13F9D0Entry {
    u8 pad0[0x4F];
    u8 flags;
    u8 pad50[0x50];
} Game13F9D0Entry;

extern u32 *D_800DBF94;

/* Semantic role: placed_object_test_actor_mask.
 * Require flag 0x80; -1 accepts that flag without consulting the actor mask.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
s32 placed_object_test_actor_mask(Game13F9D0Entry *placedObject, s32 actorIndexOrAny) {
    if (placedObject->flags & 0x80) {
        if (actorIndexOrAny == -1) {
            return 1;
        }
        if (D_800DBF94[placedObject - (Game13F9D0Entry *)D_800DBEF4] &
            (1 << actorIndexOrAny)) {
            return 1;
        }
    }
    return 0;
}
/* Semantic role: placed_object_first_actor_mask_index.
 * Require flag 0x80 and scan bits 0..31; zero also represents no set bit.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
s32 placed_object_first_actor_mask_index(u8 *placedObject) {
    s32 actorIndex;
    u32 actorMask;
    u32 actorBit;

    actorIndex = 0;
    if (*(u8 *)((u8 *)placedObject + 0x4F) & 0x80) {
        actorMask = D_800DBF94[(s32) (placedObject - D_800DBEF4) / 160];
        for (; actorIndex < 32; actorIndex++) {
            actorBit = actorMask;
            actorBit &= 1U << actorIndex;
            if (actorBit) {
                return actorIndex;
            }
        }
    }
    return 0;
}
extern u8 D_800CC2D0;
void func_1511473C(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114188 CURRENT (700) */
void func_15114188(void) {
    struct ActorSlot {
        u8 pad[0x127];
        u8 flag;
        u8 rest[0x204];
    };
    s32 index;
    s32 offset;
    s32 actorOffset;
    s32 bit;
    u32 mask;
    u32 *maskPointer;
    u32 bitMask;
    u8 *entry;
    u8 *actor;
    void (*callback)(void *);

    index = 0;
    offset = 0;
    if (D_800DBEF0 > 0) {
        do {
            maskPointer = (u32 *)((u8 *)D_800DBF94 + offset);
            mask = *maskPointer;
            bit = 0;
            if (mask != 0) {
                actorOffset = index * 0xA0;
                if (mask != 0) {
                    do {
                        bitMask = 1U << bit;
                        if (mask & bitMask) {
                            *maskPointer = mask ^ bitMask;
                            entry = (u8 *)D_800DBEF4 + actorOffset;
                            callback = *(void (**)(void *))(entry + 0x78);
                            if (callback != 0) {
                                actor = (u8 *)&((struct ActorSlot *)&D_800CC2D0)[bit];
                                if (entry[0x92] != 0 || actor[0x127] != 0xFF) {
                                    ((void (*)(void *, void *, void *, void *))callback)(
                                        (void *)(actorOffset + D_800DBEF4), actor,
                                        (void *)D_800DBEF4, (void *)callback);
                                    entry = (u8 *)D_800DBEF4 + actorOffset;
                                }
                            }
                            if ((entry[0x4F] & 4) == 4) {
                                if (!(entry[0x4F] & 8)) {
                                    func_1511473C(&((struct ActorSlot *)&D_800CC2D0)[bit], index);
                                }
                            }
                        }
                        bit++;
                        if (bit >= 0x19) {
                            break;
                        }
                        maskPointer = (u32 *)((u8 *)D_800DBF94 + offset);
                        mask = *maskPointer;
                    } while (mask != 0);
                }
                entry = (u8 *)D_800DBEF4 + actorOffset;
                entry[0x4F] &= 0xFF73;
            }
            index++;
            offset += 4;
        } while (index < D_800DBEF0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114188 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114348.s")
typedef struct Game13F9D0MovingActor {
    u8 pad0[0x14];
    f32 xyz[3];
    u8 pad20[0x56];
    u16 angle;
    u8 pad78[2];
    s16 angleCopy;
    u8 pad7C[0xBB];
    u8 active;
} Game13F9D0MovingActor;

void func_15114348(s32, f32 *, f32 *, f32 *);
extern f32 D_800A2F60;
extern u16 D_800CBDA0[];
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511473C CURRENT (225) */
void func_1511473C(Game13F9D0MovingActor *arg0, s32 arg1) {
    u32 angle;

    if ((arg0 != 0) && (arg1 < D_800DBEF0)) {
        func_15114348(arg1, &arg0->xyz[0], &arg0->xyz[1], &arg0->xyz[2]);
        angle = (u32)((f32)arg0->angle + (*(f32 *)((u8 *)D_800DBEF4 + (arg1 * 0xA0) + 0x64) * D_800A2F60));
        arg0->angle = (u16)angle;
        if ((arg0->active != 0) && ((arg1 + 1) == D_800CBDA0[((s32)((u8 *)arg0 - &D_800CC2D0) / 0x32C)])) {
            arg0->angleCopy = (s16)angle;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511473C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_1511473C.s")


void func_150A7A48(void *, void *, void *);
void func_150A8050(void *, f32, f32, f32);

/* Semantic role: placed_object_build_orientation.
 * Compose placement-derived X/Y/Z rotations, expressed in degrees.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
void placed_object_build_orientation(Game13F9D0Transform *orientation, Game13F9D0TransformArgs *rotation) {
    Game13F9D0Transform xzRotation;

    func_150A8050(orientation, 0.0f, rotation->rotationYDegrees, 0.0f);
    func_150A8050(&xzRotation, rotation->rotationXDegrees, 0.0f, rotation->rotationZDegrees);
    func_150A7A48(&xzRotation, orientation, orientation);
}
void func_150A7CB0(Game13F9D0Matrix *, s32, s32, s32);

/* Semantic role: placed_object_build_transform.
 * Add the vertical offset to Y; pass scale bit patterns through unchanged.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
void placed_object_build_transform(Game13F9D0Transform *transform,
                                   Game13F9D0MotionArgs *placedObject) {
    Game13F9D0Matrix scaleMatrix;

    placed_object_build_orientation(transform, (Game13F9D0TransformArgs *)placedObject);
    transform->position_x = (f32)placedObject->positionX;
    transform->position_y = (f32)placedObject->positionY + placedObject->verticalOffset;
    transform->position_z = (f32)placedObject->positionZ;
    func_150A7CB0(&scaleMatrix, placedObject->scaleXBits, placedObject->scaleYBits, placedObject->scaleZBits);
    func_150A7A48(&scaleMatrix, transform, transform);
}
/* Semantic role: placed_object_find_by_id.
 * Return the first matching object address; zero ID or no match returns zero.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
s32 placed_object_find_by_id(u8 objectId) {
    s32 requestedObjectId;
    s32 objectOffset;
    s32 objectAddress;
    s32 objectIndex;
    s32 objectPoolBase;

    requestedObjectId = objectId;
    if (requestedObjectId == 0) {
        return 0;
    }
    objectIndex = 0;
    if (D_800DBEF0 > 0) {
        objectPoolBase = D_800DBEF4;
        objectOffset = 0;
        objectAddress = objectPoolBase;
        do {
            objectIndex += 1;
            if (requestedObjectId == *(u8 *)((u8 *)objectAddress + 0x72)) {
                return objectOffset + objectPoolBase;
            }
            objectOffset += 0xA0;
            objectAddress += 0xA0;
        } while (objectIndex < D_800DBEF0);
    }
    return 0;
}
/* Call context: func_10004074: unique active project prototype */
void func_10004074(s32);
extern s32 D_800DBEF8;
extern s32 D_800DBEFC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114A1C CURRENT (1361) */
void func_15114A1C(void) {
    s32 temp_a1;
    s32 temp_s1;
    s32 var_a0;
    s32 var_s0;
    s32 var_s4;
    u8 *temp_v0_2;
    u8 temp_v1;
    u8 *temp_v0;

    var_a0 = D_800DBEF0;
    var_s0 = 0;
    var_s4 = 0;
    if (var_a0 > 0) {
        do {
            temp_v0 = (void *)(D_800DBEF4 + var_s4);
            if ((*(u8 *)((u8 *)temp_v0 + 0x70) & 1) != 1) {
                temp_s1 = var_s0 * 4;
                temp_a1 = *(s32 *)(D_800DBEF8 + temp_s1);
                if (temp_a1 != 0) {
                    if ((*(u8 *)((u8 *)temp_v0 + 0x4E) != 3) && !(*(u8 *)((u8 *)temp_v0 + 0x6F) & 0x80)) {
                        func_10004074(temp_a1);
                        *(s32 *)(D_800DBEF8 + temp_s1) = 0;
                        var_a0 = D_800DBEF0;
                    } else {
                        temp_v0_2 = (void *)(D_800DBEFC + var_s0);
                        temp_v1 = *temp_v0_2;
                        if (temp_v1 != 0) {
                            *temp_v0_2 = temp_v1 - 1;
                            var_a0 = D_800DBEF0;
                        } else {
                            func_10004074(temp_a1);
                            *(s32 *)(D_800DBEF8 + temp_s1) = 0;
                            var_a0 = D_800DBEF0;
                        }
                    }
                }
            } else if (!(*(u8 *)((u8 *)temp_v0 + 0x6F) & 0x80)) {
                *(s32 *)(D_800DBEF8 + (var_s0 * 4)) = 0;
                var_a0 = D_800DBEF0;
            }
            var_s0 += 1;
            var_s4 += 0xA0;
        } while (var_s0 < var_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114A1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114A1C.s")
void func_1516972C(u8 *);
extern s32 D_800DBF98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114B94 CURRENT (503) */
void func_15114B94(u32 arg0) {
    s32 offset;
    s32 count;
    s32 next_count;
    u32 index;
    u32 threshold;
    u8 *entry;
    u8 *callback;

    count = D_800DBEF0;
    if (arg0 < (u32)count) {
        offset = arg0 * 0xA0;
        entry = (u8 *)(D_800DBEF4 + offset);
        callback = *(u8 **)(entry + 0x94);
        if (callback != 0) {
            func_1516972C(callback);
            *(s32 *)(D_800DBEF4 + offset + 0x94) = 0;
            entry = (u8 *)(D_800DBEF4 + offset);
        }
        entry[0x70] |= 8;
        *(u8 *)(D_800DBEF4 + offset + 0x6E) = 1;
        count = D_800DBEF0;
    }

    index = count - 1;
    threshold = count - D_800DBF98;
    if (count != 0) {
        entry = (u8 *)(D_800DBEF4 + (index * 0xA0));
        if (entry[0x70] & 8) {
            do {
                next_count = count - 1;
                if ((index >= threshold) && (D_800DBF98 != 0)) {
                    D_800DBF98--;
                } else {
                    threshold--;
                }
                D_800DBEF0 = next_count;
                index--;
                entry -= 0xA0;
                count = next_count;
            } while ((next_count != 0) && (entry[0x70] & 8));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114B94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114B94.s")
s32 func_15114CC4(void *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x18);
    if ((temp_v1 != 0) && ((*arg2 != 0) || (*(s32 *)((u8 *)arg0 + 0x1C) == 0))) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 1;
        *(s16 *)((u8 *)arg0 + 2) = (s16) *(s16 *)((u8 *)temp_v1 + 0x10);
        *(s16 *)((u8 *)arg0 + 4) = (s16) *(s16 *)((u8 *)temp_v1 + 0x12);
        *(s16 *)((u8 *)arg0 + 6) = (s16) *(s16 *)((u8 *)temp_v1 + 0x14);
        return 0;
    }
    return 1;
}
typedef struct Game13F9D0SoundEntry {
    u8 pad0[0x10];
    s16 x;
    s16 y;
    s16 z;
    u8 pad16[0x5E];
    u16 sound;
} Game13F9D0SoundEntry;

u16 func_1000FA64(u16, s16, s16, s16, s32, s32, s32,
                 s32 (*)(void *, s32, s32 *, s32), void *, s32, s32, s32);
u16 func_10010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void func_100111C8(u16);
void func_1001123C(s32);
s32 func_1001147C(u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114D24 CURRENT (1180) */
void func_15114D24(Game13F9D0SoundEntry *arg0, s32 arg1, s32 arg2,
                   s16 arg3, s32 arg4, s32 arg5) {
    s32 independent;
    s32 sound;
    u16 result;

    if (!(arg5 & 1) || (arg0->sound == 0) ||
        (func_1001147C(arg0->sound) != arg1)) {
        independent = arg5 & 8;
        if (arg1 == -1) {
            if (arg0->sound != 0) {
                func_100111C8(arg0->sound);
                arg0->sound = 0;
            }
        } else {
            if (independent != 0) {
                sound = 0;
            } else {
                sound = arg0->sound;
            }
            if (arg5 & 4) {
                func_10010E78(sound & 0xFFFF, arg1, (u16)arg2, 0, 0, -1,
                             arg0->x, arg0->y, arg0->z, arg3, (s16)arg4);
                if (independent == 0) {
                    arg0->sound = 0;
                }
            } else {
                if (arg5 & 2) {
                    if (sound != 0) {
                        func_1001123C(sound & 0xFFFF);
                        sound = 0;
                    }
                    result = func_10010E78(sound & 0xFFFF, arg1, (u16)arg2,
                                          0, 0, -1, arg0->x, arg0->y, arg0->z,
                                          arg3, (s16)arg4);
                } else {
                    if (sound != 0) {
                        func_1001123C(sound & 0xFFFF);
                    }
                    result = func_1000FA64((u16)arg1, arg0->x, arg0->y,
                                          arg0->z, arg2, (s16)arg4, arg3,
                                          func_15114CC4, arg0, 0, 0, 0);
                }
                arg0->sound = result;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114D24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114D24.s")
extern s32 func_1001001C(s32 (*arg0)(void *, s32, s32 *, s32), s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15114F04(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15114CC4, arg0, 0, arg1, arg2);
}
/* Call context: func_150AD770: unique active project prototype */
void func_150AD770(void);
extern s32 D_8003C8E0;
extern s32 D_800BE9F0;
extern void *D_800DBDD8;
extern s32 D_800DBE18;
extern s32 D_800DBE20;
extern s32 D_800DBF9C;
extern s32 D_800DBFA0;
extern s32 D_800DBFA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15114F44 CURRENT (880) */
void func_15114F44(s32 arg0, s32 arg1, s32 arg2) {
    s32 *var_s4;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s1;
    void **var_s7;
    u8 *var_s0;

    var_s7 = &D_800DBDD8;
    if ((D_800BE9F0 == 0x12) || (D_800BE9F0 == 0x36) || (D_800BE9F0 == 0x13)) {
        var_s4 = &D_800DBE18;
        do {
            var_s0 = *var_s7;
            for (var_s1 = 0; var_s1 < *var_s4; var_s1++, var_s0 += 0xC) {
                    temp_v0 = *(s32 *)((u8 *)var_s0 + 0);
                    if (((temp_v0 & 0xF0000000) != 0x80000000) || (temp_v1 = *(s32 *)((u8 *)var_s0 + 4), ((temp_v1 & 0xF0000000) != 0x80000000)) || (temp_a0 = *(s32 *)((u8 *)var_s0 + 8), ((temp_a0 & 0xF0000000) != 0x80000000)) || (temp_v0 & 3) || (temp_v1 & 3) || (temp_a0 & 3)) {
                        D_8003C8E0 = 0x0C00005A;
                        func_150AD770();
                    }
            }
            var_s4++;
            var_s7++;
        } while (var_s4 != &D_800DBE20);
        D_800DBF9C = arg0;
        D_800DBFA0 = arg1;
        D_800DBFA4 = arg2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15114F44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13F9D0/func_15114F44.s")
