#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_182140.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_emission_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15154D80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef s32 (*Game182140Callback)(u8 *, s8);

extern Game182140Callback D_8008ACC8[];
extern s32 D_800BE9E4;

void func_15154C90(u8 *arg0) {
    s32 index;
    s8 should_free;

    should_free = 0;
    if (*(u16 *)(arg0 + 0x24) & 1) {
        *(s16 *)(arg0 + 0x22) = *(s16 *)(arg0 + 0x22) - D_800BE9E4;
        if (*(s16 *)(arg0 + 0x22) < 0) {
            should_free = 1;
        }
    }

    index = arg0[0x68] & 0xF;
    if ((index != 0) && (should_free == 0)) {
        if (D_8008ACC8[index](arg0, should_free) == 0) {
            should_free = 1;
        }
    }

    if (*(u16 *)(arg0 + 0x24) & 8) {
        s32 a;

        a = *(s16 *)(arg0 + 0x22);
        if (a < *(s16 *)(arg0 + 0x26)) {
            if ((s16)(*(s16 *)(arg0 + 0x22) * *(s16 *)(arg0 + 0x28)) < arg0[0x2E]) {
                arg0[0x2E] = (s16)(*(s16 *)(arg0 + 0x22) * *(s16 *)(arg0 + 0x28));
            }
        }
    }

    if (should_free != 0) {
        func_1516972C(arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_15154D80.s")
typedef struct Game182140Extent {
    f32 x;
    f32 y;
} Game182140Extent;

void *func_10022EC0(void *, const void *, u32);
s32 func_151555AC(f32 *, Game182140Extent *, s32 *, s32);

void *func_1515548C(void *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4,
                    u8 arg5, s32 arg6) {
    struct { Game182140Extent extent; void *result; } locals;
    s32 kind;

    if ((arg2 != 0) && (arg3 > 0)) {
        locals.extent.x = *(f32 *)((u8 *)arg0 + 8);
        locals.extent.y = *(f32 *)((u8 *)arg0 + 0xC);
        if (func_151555AC(arg0, &locals.extent, (s32 *)arg2, arg3) != 0) {
            return 0;
        }
    }
    if (*(u16 *)((u8 *)arg0 + 0x14) & 0x20) {
        kind = 0x57;
    } else {
        kind = 0x5D;
    }
    locals.result = func_15167A68(kind, arg6, arg4 + 0x70, 1, arg5, 1);
    if (locals.result == 0) {
        return 0;
    }
    func_10022EC0((u8 *)locals.result + 0x10, arg0, 0x58);
    arg0 = locals.result;
    if (1) {
    }
    *(u8 *)((u8 *)arg0 + 0x68) = 0;
    *(u8 *)((u8 *)arg0 + 0x68) |= arg1;
    return arg0;
}
extern void (*D_8008AD04[])(void *, s32, u8);

void func_15155564(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008AD04[*(u8 *)((u8 *)arg0 + 0x2A)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
typedef struct Game1555Pair {
    s32 entries[2];
} Game1555Pair;

extern Game1555Pair D_800A6030;
typedef struct Game182140Object {
    u8 unk_00[0x8];
    struct Game182140Object *next;
    u8 unk_0C[0x10 - 0xC];
    f32 x;
    f32 y;
    f32 halfWidth;
    f32 halfHeight;
    u8 unk_20[0x2A - 0x20];
    u8 group;
} Game182140Object;

typedef struct Game182140Grid {
    Game182140Object *lists[104];
} Game182140Grid;

extern Game182140Grid D_800DCE50[2];

s32 func_151555AC(f32 *arg0, Game182140Extent *arg1, s32 *arg2, s32 arg3) {
    s32 j;

    for (j = 0; j < 2; j++) {
        Game1555Pair pair = D_800A6030;
        Game182140Object *object;
        Game182140Object *next;
        u8 index;
        s32 i;
        s32 found;

        for (index = 0; index < 2; index++) {
            for (object = D_800DCE50[j].lists[pair.entries[index]]; object != 0; object = next) {
                next = object->next;
                i = arg3;
                found = 0;
                while (i > 0 && found == 0) {
                    if (object->group == arg2[i - 1]) {
                        found = 1;
                    } else {
                        i--;
                    }
                }
                if (found != 0) {
                    f32 x_extent = object->halfWidth + arg1->x;
                    f32 y_extent = object->halfHeight + arg1->y;

                    if (arg0[0] - x_extent <= object->x && object->x <= arg0[0] + x_extent &&
                        arg0[1] - y_extent <= object->y && object->y <= arg0[1] + y_extent) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
typedef struct {
    s32 field_0;
    s32 field_4;
} Game182140Pair;

void func_15169260(Game182140Pair *, s32, s32, u8);
extern Game182140Pair D_800A6038;

void func_1515572C(s32 arg0, u8 arg1) {
    Game182140Pair sp18;

    sp18 = D_800A6038;
    func_15169260(&sp18, 2, arg0, arg1);
}
