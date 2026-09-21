#include "types.h"

/*
 * Reviewed source unit: src/game/game_F3270.c
 * Boundary evidence: docs/evidence/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5DC0
 * - func_150C5E0C
 * - func_150C5F40
 * - func_150C5F94
 * - func_150C60D8
 * - func_150C6460
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150C6460();                                  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5DC0 CURRENT (165) */
void func_150C5DC0(void *arg0) {
    void *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) != 0) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x58);
        temp_v0 = (void *)((u8 *)temp_v0 + 0xB0);
        *(volatile s8 *)((u8 *)temp_v0 + 4) = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = func_150C6460();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5DC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5DC0.s")
u32 func_150ADA20(void *, s8);                      /* extern */
f32 func_150ADA68();                                /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5E0C CURRENT (1097) */
s8 func_150C5E0C(u8 *arg0) {
    s8 sp27;
    s8 var_a2;
    void *sp1C;
    s32 temp_a0;
    u8 *temp_v1;

    var_a2 = 1;
    temp_v1 = (void *)(arg0 + 0xB0);
    if (*(u8 *)((u8 *)arg0 + 0xB4) == 0) {
        var_a2 = 0;
    }
    *(s8 *)((u8 *)temp_v1 + 4) = 0;
    *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_v1 + 0x14) < 0) {
        sp1C = temp_v1;
        sp27 = var_a2;
        *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) ((func_150ADA20(arg0, var_a2) % (u32) (*(s16 *)((u8 *)temp_v1 + 0x18) + 1)) + *(s16 *)((u8 *)temp_v1 + 0x16));
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_v1 + 0xC)) + *(f32 *)((u8 *)temp_v1 + 8));
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_a0 + (s32) ((*(f32 *)((u8 *)temp_v1 + 0x10) - (f32) temp_a0) * *(f32 *)((u8 *)temp_v1 + 0x1C)));
    return var_a2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5E0C.s")
extern void func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

s32 func_150C5EFC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *) arg0 + 0xB0);
    temp_v0 = (u8 *) temp_v0 + 0x58;
    *(s32 *) temp_v0 = 0;
    *(void **)((u8 *) arg0 + 0xB0) = 0;
    *(s32 *)((u8 *) arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}
typedef struct {
    u8 pad_0[0x5C];
    s8 field_5C;
} GameF3270Data;

typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    u8 pad_1C[0x40];
    GameF3270Data *field_5C;
} GameF3270State;

s32 func_150C5F94(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5F40 CURRENT (835) */
void func_150C5F40(GameF3270State *arg0) {
    s32 temp_a2;

    temp_a2 = arg0->field_18;
    if (arg0->field_5C != 0) {
        arg0->field_5C->field_5C = 1;
        return;
    }
    arg0->field_5C = (GameF3270Data *)func_150C5F94(temp_a2, arg0, temp_a2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5F40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F40.s")
extern f32 D_800A0410;
extern f32 D_800A0414;
extern f32 D_800A0418;
s32 func_15045800(f32 *, s32, f32, void *);
u32 func_1513418C(void *, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);

typedef struct GameF3270SpawnPacket {
    s32 field_0;
    s32 field_4;
    u8 field_8;
    u8 pad_9[3];
    void *owner;
    u8 field_10;
    u8 pad_11[3];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    s16 field_28;
    u8 field_2A;
    u8 field_2B;
    u8 field_2C;
    u8 field_2D;
} GameF3270SpawnPacket;

typedef struct GameF3270RayPacket {
    f32 coordinates[3];
    u8 pad_C[4];
    void *source;
    u8 flag;
    u8 pad_15[3];
    f32 result;
} GameF3270RayPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5F94 CURRENT (390) */
s32 func_150C5F94(void *arg0, void *arg1) {
    GameF3270SpawnPacket packet;
    GameF3270RayPacket ray;
    u32 spawned;

    ray.source = arg1;
    ray.flag = 1;
    ray.coordinates[0] = *(f32 *)((u8 *)arg0 + 0x14);
    ray.coordinates[1] = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0410;
    ray.coordinates[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    if (func_15045800(ray.coordinates, 0, *(f32 *)((u8 *)arg0 + 0x18) - 100.0f,
                      (u8 *)arg1 + 0x34) != 0) {
        ray.result = *(f32 *)((u8 *)arg1 + 0x34);
    } else {
        ray.result = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0414;
    }
    packet.field_0 = 0;
    packet.field_4 = 0;
    packet.field_8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.owner = arg0;
    packet.field_10 = 0;
    packet.field_14 = packet.field_18 = packet.field_1C = 0.0f;
    packet.field_20 = 25.0f;
    packet.field_24 = D_800A0418;
    packet.field_28 = 0x12C;
    packet.field_2A = 0xA;
    packet.field_2B = 4;
    packet.field_2C = 1;
    packet.field_2D = 2;
    spawned = func_1513418C(&packet, 0xC, 0xFF, 0);
    if (spawned != 0) {
        func_10022EC0((void *)(spawned + 0x58), &ray.source, 0xC);
    }
    return spawned;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5F94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C60D8.s")
s32 func_150C63EC(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}
void func_151346EC(void);

void func_150C6410(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_151346EC();
}
void func_1513470C(void);

void func_150C6438(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_1513470C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
