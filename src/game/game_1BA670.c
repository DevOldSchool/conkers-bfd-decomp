#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BA670.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518D6E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BA670Owner {
    u8 pad0[0x3B];
    u8 group;
    u8 pad3C[0x18E];
    u8 flag1CA;
} Game1BA670Owner;

typedef struct Game1BA670Node {
    u8 pad0[8];
    struct Game1BA670Node *next;
    u8 padC[0xC];
    Game1BA670Owner *owner;
    u8 group;
} Game1BA670Node;

typedef struct Game1BA670Spawn {
    Game1BA670Owner *owner;
    u8 group;
    s16 duration;
    u8 enabled;
    s8 direction;
    u8 mode;
} Game1BA670Spawn;

extern Game1BA670Node *D_800DCE50[][104];
extern s8 D_800DD190;
extern Game1BA670Node *D_800DD198[];
void *func_1518E3C4(void **arg0, u8 arg1);

void *func_1518D1C0(Game1BA670Owner *arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, s32 arg5, void *arg6) {
    Game1BA670Spawn spawn;
    s32 row;

    if (arg0 == NULL) {
        return NULL;
    }
    if (arg3) {
        for (row = 0; row < 2; row++) {
            Game1BA670Node *node = D_800DCE50[row][0x21];
            D_800DD190++;
            while (node != NULL) {
                D_800DD198[D_800DD190] = node->next;
                if (node->owner == arg0 || node->group == arg0->group) {
                    func_1516972C(node);
                }
                node = D_800DD198[D_800DD190];
            }
            D_800DD190--;
        }
    }
    spawn.owner = arg0;
    spawn.group = arg0->group;
    switch (arg1) {
    case 10:
        spawn.duration = 0x4B;
        spawn.enabled = arg0->flag1CA ? 1 : 0;
        spawn.direction = 1;
        spawn.mode = 7;
        return func_1518E3C4((void **)&spawn, arg4);
    case 11:
        spawn.duration = 0x4B;
        spawn.enabled = arg0->flag1CA ? 1 : 0;
        spawn.direction = 0;
        spawn.mode = 1;
        return func_1518E3C4((void **)&spawn, arg4);
    case 12:
        spawn.duration = 0x4B;
        spawn.enabled = arg0->flag1CA ? 1 : 0;
        spawn.direction = 1;
        spawn.mode = 7;
        return func_1518E3C4((void **)&spawn, arg4);
    case 1:
        spawn.duration = 0x1F4;
        spawn.enabled = 1;
        spawn.direction = 0;
        spawn.mode = 1;
        return func_1518E3C4((void **)&spawn, arg4);
    case 2:
        spawn.duration = 0xBB8;
        spawn.enabled = 1;
        spawn.direction = 1;
        spawn.mode = 7;
        return func_1518E3C4((void **)&spawn, arg4);
    case 3:
        spawn.duration = 0xC8;
        spawn.enabled = 1;
        spawn.direction = -1;
        spawn.mode = 8;
        return func_1518E3C4((void **)&spawn, arg4);
    case 4:
        spawn.duration = 0xC8;
        spawn.enabled = 1;
        spawn.direction = -1;
        spawn.mode = 9;
        return func_1518E3C4((void **)&spawn, arg4);
    case 5:
        spawn.duration = 0xBB8;
        spawn.enabled = 0;
        spawn.direction = -1;
        spawn.mode = 2;
        return func_1518E3C4((void **)&spawn, arg4);
    case 6:
        spawn.duration = 0xBB8;
        spawn.enabled = 0;
        spawn.direction = -1;
        spawn.mode = 3;
        return func_1518E3C4((void **)&spawn, arg4);
    case 7:
        spawn.duration = 0xBB8;
        spawn.enabled = 0;
        spawn.direction = -1;
        spawn.mode = 4;
        return func_1518E3C4((void **)&spawn, arg4);
    case 8:
        spawn.duration = 0xBB8;
        spawn.enabled = 0;
        spawn.direction = -1;
        spawn.mode = 5;
        return func_1518E3C4((void **)&spawn, arg4);
    case 9:
        spawn.duration = 0xBB8;
        spawn.enabled = 0;
        spawn.direction = -1;
        spawn.mode = 6;
        return func_1518E3C4((void **)&spawn, arg4);
    case 13:
        spawn.duration = arg2;
        spawn.enabled = (arg2 == 999) ? 0 : 1;
        spawn.direction = -1;
        spawn.mode = 10;
        return func_1518E3C4((void **)&spawn, arg4);
    case 14:
        spawn.duration = arg2;
        spawn.enabled = 1;
        spawn.direction = -1;
        spawn.mode = 11;
        return func_1518E3C4((void **)&spawn, arg4);
    case 15:
        spawn.duration = arg2;
        spawn.enabled = (arg2 == 999) ? 0 : 1;
        spawn.direction = -1;
        spawn.mode = 12;
        return func_1518E3C4((void **)&spawn, arg4);
    case 16:
        spawn.duration = arg2;
        spawn.enabled = (arg2 == 999) ? 0 : 1;
        spawn.direction = -1;
        spawn.mode = 13;
        return func_1518E3C4((void **)&spawn, arg4);
    case 17:
        spawn.duration = 0x12C;
        spawn.enabled = 1;
        spawn.direction = -1;
        spawn.mode = 14;
        return func_1518E3C4((void **)&spawn, arg4);
    case 18:
        spawn.duration = arg2;
        spawn.enabled = 1;
        spawn.direction = -1;
        spawn.mode = 15;
        return func_1518E3C4((void **)&spawn, arg4);
    }
    return NULL;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BA670/func_1518D6E0.s")
s32 func_1518E298(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x1C);
    if ((temp_v1 != 0) && (*(s32 *)((u8 *)temp_v1 + 0) != 0)) {
        *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x14);
        *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x18);
        *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x1C);
        return 0;
    }
    return 1;
}
typedef struct Game1BA670Slot {
    void *effect;
    u8 pad4[0x14];
} Game1BA670Slot;

typedef struct Game1BA670State {
    u8 pad0[0x24];
    f32 field_24;
    s32 field_28;
    u8 pad2C[0x1C];
    Game1BA670Slot slots[100];
} Game1BA670State;

void func_100226F0(void *, s32);

void func_1518E308(Game1BA670State *arg0) {
    Game1BA670Slot *slot;
    s32 i;

    slot = arg0->slots;
    arg0->field_28 = 0;
    arg0->field_24 = 0.0f;
    for (i = 0; i < 100; i++, slot++) {
        if (slot->effect != 0) {
            func_1516972C(slot->effect);
        }
    }
    func_100226F0(arg0->slots, sizeof(arg0->slots));
}

void func_1518E37C(void *arg0, u8 arg1) {
    if (arg1 != *(u8 *)((u8 *)arg0 + 0x22)) {
        func_1518E308(arg0);
        *(u8 *)((u8 *)arg0 + 0x22) = arg1;
    }
}
void *func_10022EC0(void *, const void *, u32);

void *func_1518E3C4(void **arg0, u8 arg1) {
    u8 *result;

    if (*(u8 *)((u8 *)*arg0 + 4) == 0x96) {
        return 0;
    }
    result = func_15167A68(0x21, 1, 0x9EC, 1, arg1, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0x18, arg0, 0xC);
    *(s32 *)(result + 0x28) = 0;
    *(s8 *)(result + 0x2C) = 8;
    *(s8 *)(result + 0x2D) = 4;
    *(s32 *)(result + 0x30) = 0;
    *(s32 *)(result + 0x10) = 1;
    *(s32 *)(result + 0x14) = 0;
    *(f32 *)(result + 0x24) = 0.0f;
    *(f32 *)(result + 0x38) = 0.0f;
    *(f32 *)(result + 0x3C) = 0.0f;
    *(f32 *)(result + 0x40) = 0.0f;
    *(f32 *)(result + 0x34) = 1.0f;
    func_100226F0(result + 0x48, 0x960);
    return result;
}
