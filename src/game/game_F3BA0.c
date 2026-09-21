#include "types.h"

/*
 * Reviewed source unit: src/game/game_F3BA0.c
 * Boundary evidence: docs/evidence/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C66F0
 * - func_150C673C
 * - func_150C682C
 * - func_150C6870
 * - func_150C68C4
 * - func_150C6A08
 * - func_150C6D90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150C6D90();                                  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C66F0 CURRENT (165) */
void func_150C66F0(void *arg0) {
    void *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x6C) != 0) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x6C);
        temp_v0 = (void *)((u8 *)temp_v0 + 0xB0);
        *(s8 *)((u8 *)temp_v0 + 4) = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x6C) = func_150C6D90();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C66F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C66F0.s")

u32 func_150ADA20(void *, s8);                      /* extern */
f32 func_150ADA68();                                /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C673C CURRENT (1097) */
s8 func_150C673C(u8 *arg0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150C673C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C673C.s")
extern void func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C682C CURRENT (100) */
s32 func_150C682C(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *) arg0 + 0xB0);
    *(s32 *)((u8 *) temp_v0 + 0x6C) = 0;
    *(void **)((u8 *) arg0 + 0xB0) = 0;
    temp_v0 = (u8 *) temp_v0 + 0x58;
    *(s32 *)((u8 *) arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C682C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C682C.s")
s32 func_150C68C4(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C6870 CURRENT (835) */
void func_150C6870(void *arg0) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x18);
    if (*(s32 *)((u8 *)arg0 + 0x70) != 0) {
        *(s8 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x70) + 0x58) + 4) = 1;
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x70) = func_150C68C4(temp_a2, arg0, temp_a2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C6870 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6870.s")
extern f32 D_800A0450;
extern f32 D_800A0454;
extern f32 D_800A0458;
s32 func_15045800(f32 *, s32, f32, void *);
u32 func_1513418C(void *, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);

typedef struct GameF3BA0SpawnPacket {
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
} GameF3BA0SpawnPacket;

typedef struct GameF3BA0RayPacket {
    f32 coordinates[3];
    u8 pad_C[4];
    void *source;
    u8 flag;
    u8 pad_15[3];
    f32 result;
} GameF3BA0RayPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C68C4 CURRENT (390) */
s32 func_150C68C4(void *arg0, void *arg1) {
    GameF3BA0SpawnPacket packet;
    GameF3BA0RayPacket ray;
    u32 spawned;

    ray.source = arg1;
    ray.flag = 1;
    ray.coordinates[0] = *(f32 *)((u8 *)arg0 + 0x14);
    ray.coordinates[1] = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0450;
    ray.coordinates[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    if (func_15045800(ray.coordinates, 0, *(f32 *)((u8 *)arg0 + 0x18) - 100.0f,
                      (u8 *)arg1 + 0x34) != 0) {
        ray.result = *(f32 *)((u8 *)arg1 + 0x34);
    } else {
        ray.result = *(f32 *)((u8 *)arg0 + 0x18) + D_800A0454;
    }
    packet.field_0 = 0;
    packet.field_4 = 0;
    packet.field_8 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.owner = arg0;
    packet.field_10 = 0;
    packet.field_14 = 0.0f;
    packet.field_18 = 0.0f;
    packet.field_1C = 0.0f;
    packet.field_20 = 80.0f;
    packet.field_24 = D_800A0458;
    packet.field_28 = 0x12C;
    packet.field_2A = 0xA;
    packet.field_2B = 5;
    packet.field_2C = 2;
    packet.field_2D = 3;
    spawned = func_1513418C(&packet, 0xC, 0xFF, 0);
    if (spawned != 0) {
        func_10022EC0((void *)(spawned + 0x58), &ray.source, 0xC);
    }
    return spawned;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C68C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C68C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6A08.s")
s32 func_150C6D1C(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}
void func_151346EC(void);

void func_150C6D40(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_151346EC();
}
void func_1513470C(void);

void func_150C6D68(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_1513470C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6D90.s")
