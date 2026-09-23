#include "types.h"

/*
 * Reviewed source unit: src/game/game_182140.c
 * Boundary evidence: docs/evidence/game_raw_emission_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15154C90
 * - func_15154D80
 * - func_1515548C
 * - func_151555AC
 * - func_1515572C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef s32 (*Game182140Callback)(u8 *, s8);

void func_1516972C(u8 *);
extern Game182140Callback D_8008ACC8[];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15154C90 CURRENT (30) */
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
        s16 temp_lo;
        s16 temp_v1;

        temp_v1 = *(s16 *)(arg0 + 0x22);
        if (temp_v1 < *(s16 *)(arg0 + 0x26)) {
            temp_lo = temp_v1 * *(s16 *)(arg0 + 0x28);
            if (temp_lo < arg0[0x2E]) {
                arg0[0x2E] = temp_lo;
            }
        }
    }

    if (should_free != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15154C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_15154C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_15154D80.s")
void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
s32 func_151555AC(f32 *, f32 *, s32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515548C CURRENT (239) */
void *func_1515548C(void *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4,
                    u8 arg5, s32 arg6) {
    f32 position[2];
    void *result;
    s32 kind;

    if ((arg2 != 0) && (arg3 > 0)) {
        position[0] = *(f32 *)((u8 *)arg0 + 8);
        position[1] = *(f32 *)((u8 *)arg0 + 0xC);
        if (func_151555AC(arg0, position) != 0) {
            return 0;
        }
    }
    if (*(u16 *)((u8 *)arg0 + 0x14) & 0x20) {
        kind = 0x57;
    } else {
        kind = 0x5D;
    }
    result = func_15167A68(kind, arg6, arg4 + 0x70, 1, arg5, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0((u8 *)result + 0x10, arg0, 0x58);
    *(volatile u8 *)((u8 *)result + 0x68) = 0;
    *(volatile u8 *)((u8 *)result + 0x68) = arg1;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515548C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_1515548C.s")
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
extern u8 D_800DCE50[];
extern u8 D_800DD190[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151555AC CURRENT (5659) */
s32 func_151555AC(f32 *arg0, f32 *arg1, s32 *arg2, s32 arg3) {
    Game1555Pair pair = D_800A6030;
    u8 *table = D_800DCE50;
    s32 index;

    do {
        index = 0;
        do {
            u8 *object = *(u8 **)(table + pair.entries[index] * 4);
            while (object != 0) {
                u8 *next = *(u8 **)(object + 8);
                s32 found = 0;
                if (arg3 > 0) {
                    s32 remaining = arg3 * 4;
                    s32 *scan = arg2 + arg3;
                    do {
                        if (object[0x2A] == scan[-1]) {
                            found = 1;
                        } else {
                            remaining -= 4;
                            scan--;
                        }
                        if (remaining < 4 || found != 0) {
                            break;
                        }
                    } while (1);
                }
                if (found != 0) {
                    f32 x_extent = *(f32 *)(object + 0x18) + arg1[0];
                    f32 y_extent = *(f32 *)(object + 0x1C) + arg1[1];
                    f32 x = arg0[0];
                    f32 x_center = *(f32 *)(object + 0x10);
                    if (x - x_extent <= x_center && x_center <= x + x_extent) {
                        f32 y = arg0[1];
                        f32 y_center = *(f32 *)(object + 0x14);
                        if (y - y_extent <= y_center && y_center <= y + y_extent) {
                            return 1;
                        }
                    }
                }
                object = next;
            }
            index = (index + 1) & 0xFF;
        } while (index < 2);
        table += 0x1A0;
    } while (table != D_800DD190);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151555AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_151555AC.s")
typedef struct {
    s32 field_0;
    s32 field_4;
} Game182140Pair;

void func_15169260(Game182140Pair *, s32, s32, u8);
extern Game182140Pair D_800A6038;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515572C CURRENT (300) */
void func_1515572C(s32 arg0, u8 arg1) {
    Game182140Pair sp18;

    sp18 = D_800A6038;
    func_15169260(&sp18, 2, arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515572C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182140/func_1515572C.s")
