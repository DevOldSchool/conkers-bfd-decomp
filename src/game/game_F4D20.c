#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F4D20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C7968
 * - func_150C79BC
 * - func_150C7C90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameF4D20GlobalState {
    u8 pad0[0xA];
    u8 field_A;
} GameF4D20GlobalState;

typedef struct GameF4D20Flags {
    u8 pad0[0x73];
    u8 field_73;
} GameF4D20Flags;

void func_1511650C(void *, s32, s32, f32);
extern GameF4D20GlobalState *D_800D2E4C;
extern void *D_800DBEF4;

void func_150C7870(void *arg0) {
    if (!(D_800D2E4C->field_A & 8)) {
        if (!(((GameF4D20Flags *)D_800DBEF4)->field_73 & 4)) {
            func_1511650C(arg0, 1, 0x353, 1000.0f);
            return;
        }
        func_1511650C(arg0, 1, 0x43, 400.0f);
    }
}
/* Call context: func_151150BC: unique active project prototype */
void func_151150BC(void);
extern void * D_800DBEF4;

void func_150C78E0(void *arg0) {
    u8 *state;

    if (!(*(u8 *)((u8 *)arg0 + 0x73) & 4)) {
        state = D_800DBEF4;
        state += 0x1E0;
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) (-(*(s32 *)(state + 0x3C) & 0xFFFF0000) & 0xFFFF0000);
        func_151150BC();
    }
}
void func_151150BC(void);
extern void *D_800DBEF4;

void func_150C7930(void *arg0) {
    u8 *temp_v0;

    temp_v0 = D_800DBEF4;
    temp_v0 += 0x1E0;
    *(s32 *)((u8 *)arg0 + 0x3C) = *(s32 *)(temp_v0 + 0x3C) & 0xFFFF0000;
    func_151150BC();
}
typedef struct {
    u8 pad_0[0x73];
    u8 field_73;
    u8 pad_74[8];
    void *field_7C;
} GameF4D20State;

extern void *D_800DBEF4;
void func_15116110(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7968 CURRENT (200) */
void func_150C7968(GameF4D20State *arg0) {
    u8 *var_v0;
    void *temp_v1;
    s32 value;

    func_15116110(arg0);
    if (!(arg0->field_73 & 4)) {
        var_v0 = D_800DBEF4;
        var_v0 += 0x1E0;
        temp_v1 = arg0->field_7C;
        value = *(s16 *)(var_v0 + 0x3C);
        if (temp_v1 != 0) {
            *(s8 *)((u8 *)temp_v1 + 0x13) = value >> 4;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7968 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7968.s")
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
u32 func_150ADA20(void);
void func_15179FE0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800887F4;
extern f32 D_800A04D0, D_800A04D4;
extern u8 *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C79BC CURRENT (983) */
void func_150C79BC(s32 arg0) {
    s32 offset;
    u8 angle;
    f32 radius;
    u8 *view;
    s32 height, x, z;
    register f32 sine;

    offset = arg0 * 0x9A0;
    view = D_800DBFF0 + offset;
    x = (s32)*(f32 *)(view + 0x2F8) + 0x972;
    height = (s32)*(f32 *)(view + 0x2FC);
    z = (s32)*(f32 *)(view + 0x300) - 0x6EF;
    if (height - 0x9C4 >= -0xC7 && x * x + z * z < 0x15F900) {
        if (D_800887F4 == 0) {
            func_1000D96C(0x5F, 0xF, 6);
            func_1000DE1C(0x10, 4);
            D_800887F4 = 1;
            height = (s32)*(f32 *)(D_800DBFF0 + offset + 0x2FC);
        }
    } else if (D_800887F4 != 0) {
        func_1000D96C(0xF, 0x5F, 4);
        func_1000D96C(0x10, 0, 3);
        D_800887F4 = 0;
        height = (s32)*(f32 *)(D_800DBFF0 + offset + 0x2FC);
    }
    if (height - 0x62F < 0 && x * x + z * z < 0xC5C10 &&
        (func_150ADA20() & 0xFFFF) < 0x2000U) {
        z = func_150ADA20() % 900U;
        angle = func_150ADA20();
        sine = func_150489B0(angle);
        radius = (f32)z;
        x = (s32)(sine * radius + D_800A04D0);
        z = (s32)(func_15048A40(angle) * radius + D_800A04D4);
        func_15179FE0((s32)((f32)((func_150ADA20() & 0xFFFF) * 2) *
                      0.0000152587890625f) & 0xFF,
                      (s16)x, 0x62F, (s16)z, 7, 0x4B0, 0x25, 0xA, 0x1E, 3, 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C79BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C79BC.s")
typedef struct GameF4D20Entry7C90 {
    s8 marker;
    u8 pad1[7];
} GameF4D20Entry7C90;

typedef struct GameF4D20State7C90 {
    u8 pad0[0x1C];
    GameF4D20Entry7C90 *entries;
    u8 pad20[0x1C];
    s32 flags;
    u8 pad40[0x3C];
    s32 index;
} GameF4D20State7C90;

typedef struct GameF4D20Object7C90 {
    u8 pad0[0x12];
    s16 angle;
} GameF4D20Object7C90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7C90 CURRENT (1603) */
void func_150C7C90(void *arg0) {
    s32 *entry;
    s8 *entries;
    s32 index;
    s32 current;
    s32 angle;
    s32 value;
    void *object;

    current = *(s32 *)((u8 *)arg0 + 0x7C);
    if (current == 0) {
        entries = *(s8 **)((u8 *)arg0 + 0x1C);
        index = 0;
        if (*entries != -0xE) {
            do {
                index++;
            } while (*(s8 *)(entries + (index * 8)) != -0xE);
        }
        *(s32 *)((u8 *)arg0 + 0x7C) = index;
        current = index;
    }
    entry = (s32 *)(*(s8 **)((u8 *)arg0 + 0x1C) + (current * 8));
    object = func_151149AC(*(s32 *)((u8 *)arg0 + 0x3C) & 0xFF, entry, arg0);
    angle = -0x29D - *(s16 *)((u8 *)object + 0x12);
    if (*(s32 *)((u8 *)arg0 + 0x3C) & 0x8000) {
        angle = 0x344 - angle;
    }
    if (angle < 0) {
        do {
            angle += 0x400;
        } while (angle < 0);
    }
    if (angle >= 0x400) {
        do {
            angle -= 0x400;
        } while (angle >= 0x400);
    }
    value = *entry & ~0xFFF;
    *entry = value;
    *entry = value | angle;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4D20/func_150C7C90.s")
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);

void func_150C7D7C(void *arg0) {
    void *temp_v0;

    temp_v0 = func_15083E90(0xCU);
    *(s16 *)((u8 *)arg0 + 0x10) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x14) - 30.0f);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x18) + 50.0f);
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (s32) (*(f32 *)((u8 *)temp_v0 + 0x1C) + 30.0f);
}
