#include "types.h"

/*
 * Reviewed source unit: src/game/game_205C90.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D87E0
 * - func_151D8868
 * - func_151D8A24
 * - func_151D8B24
 * - func_151D8C00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_80084060[4];
extern u8 D_800BE944[4];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D87E0 CURRENT (315) */
s32 func_151D87E0(u8 arg0) {
    s32 var_a1;
    s32 var_v1;
    s32 var_v0;
    u8 temp_a0;

    var_v0 = 0;
    var_v1 = arg0;
    var_a1 = 0;
loop_1:
    if (var_v1 & (1 << var_a1)) {
        temp_a0 = D_80084060[var_v0];
        if ((s32)temp_a0 >= 4) {
            return 0;
        }
        if (D_800BE944[temp_a0] != 0) {
            return 1;
        }
    }
    var_a1 = (var_v0 + 1) & 0xFF;
    var_v0 = var_a1;
    if (var_a1 < 4) {
        goto loop_1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D87E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D87E0.s")
s32 func_151D87E0(u8);
s32 func_15181CC8(s32);
s32 func_1517EF00(s32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void *func_10022EC0(void *, const void *, u32);
void func_1501C010(u8, u8);
extern s32 D_80082FA0;
extern u8 D_800BEAC0;
extern u8 D_800BEAC1;
extern u8 D_800BEAC2;
extern u8 D_800BEAC3;
extern u8 D_800E0B94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8868 CURRENT (620) */
void *func_151D8868(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 *maxIndex;
    s32 index;
    s32 nextIndex;
    s32 bit;
    u8 *result;

    if (D_800E0B94 != 0) {
        return 0;
    }
    if (func_151D87E0(arg0[5]) == 0) {
        return 0;
    }
    if (D_800BEAC0 != 0 || D_800BEAC1 != 0 || D_800BEAC2 != 0 || D_800BEAC3 != 0) {
        return 0;
    }
    maxIndex = &D_80082FA0;
    nextIndex = 0;
    index = 0;
    if (*maxIndex >= 0) {
        do {
            if (arg0[5] & (1 << index)) {
                if (func_15181CC8(index) == 0 || func_1517EF00(index) != 0) {
                    return 0;
                }
            }
            nextIndex += 1;
            index = nextIndex & 0xFF;
            nextIndex = index;
        } while (*maxIndex >= index);
    }
    result = func_15167A68(0x3F, arg3, arg1 + 0x18, 1, arg2, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0xE, arg0, 8);
    nextIndex = 0;
    bit = 0;
    do {
        if (result[0x13] & (1 << bit)) {
            func_1501C010(nextIndex, arg0[4]);
        }
        nextIndex += 1;
        bit = nextIndex & 0xFF;
        nextIndex = bit;
    } while (bit < 4);
    result[0x16] = arg0[4];
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8868 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8868.s")
void func_1501C17C(u8);
void func_1516972C(void *);
extern void (*D_8008FCC0[])(void *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8A24 CURRENT (1267) */
void func_151D8A24(void *arg0) {
    u8 sp23;
    s32 var_s0;
    s32 var_v0;
    s8 temp_v0;

    sp23 = 0;
    if (*(u8 *)((u8 *)arg0 + 0xE) & 1) {
        *(s16 *)((u8 *)arg0 + 0x10) =
            *(s16 *)((u8 *)arg0 + 0x10) - D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x10) < 0) {
            sp23 = 1;
        }
    }
    temp_v0 = *(s8 *)((u8 *)arg0 + 0x14);
    if (temp_v0 != -1) {
        D_8008FCC0[temp_v0](arg0);
    }
    var_s0 = 0;
    var_v0 = 0;
    if (*(u8 *)((u8 *)arg0 + 0x12) != *(u8 *)((u8 *)arg0 + 0x16)) {
        do {
            if (*(u8 *)((u8 *)arg0 + 0x13) & (1 << var_v0)) {
                func_1501C17C(var_s0 & 0xFF);
                func_1501C010(var_s0 & 0xFF,
                              *(u8 *)((u8 *)arg0 + 0x12));
            }
            var_v0 = (var_s0 + 1) & 0xFF;
            var_s0 = var_v0;
        } while (var_v0 < 4);
        *(u8 *)((u8 *)arg0 + 0x16) = *(u8 *)((u8 *)arg0 + 0x12);
    }
    if (sp23 != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8A24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8A24.s")
/* Call context: func_1501C17C: unique active project prototype */
void func_1501C17C(u8);
void func_151D8B24(s32);
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8B24 CURRENT (25) */
void func_151D8B24(s32 arg0) {
    s32 var_s0;
    s32 var_v0;

    var_s0 = 0;
    var_v0 = 0;
    do {
        if (*(u8 *)((u8 *)arg0 + 0x13) & (1 << var_v0)) {
            func_1501C17C(var_s0);
        }
        var_s0 += 1;
        var_v0 = var_s0 & 0xFF;
        var_s0 = var_v0;
    } while (var_v0 < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8B24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8B24.s")
void func_151D8B24(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151D8B88(s32 arg0) {
    func_151D8B24(arg0);
    func_15169804(arg0);
}
void func_151D8BB4(s32 arg0) {
    func_151D8B24(arg0);
    func_15169824(arg0);
}
void func_151D8C00(void *, u8 *);
void func_151D8BE0(s32 arg0) {
    func_151D8C00((void *)arg0, (u8 *)(arg0 + 0x18));
}
f32 func_15143E64(void *);
s32 func_15144B34(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8C00 CURRENT (25) */
void func_151D8C00(void *arg0, u8 *arg1) {
    struct {
        f32 values[3];
        u32 pad;
    } difference;
    f32 distance;
    f32 start;
    f32 alpha;
    f32 *origin;

    origin = (f32 *)func_15144B34(arg1[0x18]);
    difference.values[0] = *(f32 *)(arg1 + 0) - origin[0];
    difference.values[1] = *(f32 *)(arg1 + 4) - origin[1];
    difference.values[2] = *(f32 *)(arg1 + 8) - origin[2];
    distance = func_15143E64(difference.values);
    start = *(f32 *)(arg1 + 0xC);
    if (distance < start) {
        alpha = 1.0f;
    } else if ((*(f32 *)(arg1 + 0x10) + start) < distance) {
        alpha = 0.0f;
    } else {
        alpha = 1.0f - (*(f32 *)(arg1 + 0x14) * (distance - start));
    }
    *(s8 *)((u8 *)arg0 + 0x12) = (s8)(u32)(alpha * 8.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8C00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8C00.s")
void func_151D8D5C(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x58) {
        func_1516972C(arg0);
        return;
    }
    if (arg2 == 0x47) {
        func_1516972C(arg0);
    }
}
void func_15169260(void *arg0, s32 arg1, s32 arg2, u8 arg3);
extern u8 D_800AB300;

void func_151D8DB4(s32 arg0, u8 arg1) {
    func_15169260(&D_800AB300, 1, arg0, arg1);
}
void func_151D8DB4(s32 arg0, u8 arg1);
extern s8 D_800E0A00;

void func_151D8DE8(void) {
    D_800E0A00 = 1;
    func_151D8DB4(0, 0x58);
}
