#include "types.h"

/*
 * Reviewed source unit: src/game/game_175250.c
 * Boundary evidence: docs/evidence/game_raw_parametric_elements.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15147EB8
 * - func_1514803C
 * - func_151488C4
 * - func_15148AF4
 * - func_15148BA4
 * - func_15148DE0
 * - func_15148F1C
 * - func_151490C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    s32 values[8];
} Struct15147DA0;

void *func_15147DA0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4,
                    s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                    s32 arg10, void *arg11, s32 arg12, u8 arg13, s32 arg14) {
    void *temp_v0;
    void *temp_a0;

    *(s32 *)((u8 *)arg0 + 0x10) = 1;
    temp_v0 = func_15147A80(arg0, (u8 *)arg2 + 0x48, 0x14, 1, 0, 1,
                           arg9, arg10, arg12, arg13, arg14);
    if (temp_v0 == 0) {
        return 0;
    }
    temp_a0 = *(void **)((u8 *)temp_v0 + 0x98);
    func_10022EC0(temp_a0, arg1, 0x20);
    *(s8 *)((u8 *)temp_a0 + 0x20) = arg3;
    *(s8 *)((u8 *)temp_a0 + 0x21) = arg4;
    *(s8 *)((u8 *)temp_a0 + 0x22) = arg5;
    *(s8 *)((u8 *)temp_a0 + 0x23) = arg6;
    *(s8 *)((u8 *)temp_a0 + 0x24) = arg7;
    *(s8 *)((u8 *)temp_a0 + 0x25) = arg8;
    *(Struct15147DA0 *)((u8 *)temp_a0 + 0x28) = *(Struct15147DA0 *)arg11;
    return temp_v0;
}
typedef s32 (*Game175250Callback)();
typedef struct Game175250Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Game175250Vec3;

extern Game175250Callback D_8008A3E0[];
extern Game175250Callback D_8008A3F8[];
extern Game175250Callback D_8008A42C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147EB8 CURRENT (885) */
s8 func_15147EB8(void *arg0) {
    u8 *entry = *(u8 **)((u8 *)arg0 + 0x98);
    s8 state = 0;
    u8 index;
    s16 count;
    s32 product;
    u8 *list;
    Game175250Vec3 *position;

    index = entry[0x20];
    if (index != 0) {
        if (D_8008A3E0[index]() == 0) {
            state = 1;
        }
    }
    index = entry[0x21];
    if (index != 0 && state == 0) {
        if (D_8008A3F8[index]() == 0) {
            state = 1;
        }
    }
    if ((entry[0x18] & 0x40) && state == 0) {
        count = *(s16 *)((u8 *)arg0 + 0x1C);
        if (count < *(s16 *)(entry + 0x1C)) {
            product = *(s16 *)(entry + 0x1E) * count;
            if (product < entry[0x1B]) {
                entry[0x1B] = product;
            }
        }
    }
    if (state != 0) {
        index = entry[0x22];
        if (index != 0) {
            D_8008A42C[index]();
        }
    }
    list = *(u8 **)((u8 *)arg0 + 0x94);
    if (*(s8 *)((u8 *)arg0 + 0x2C) > 0) {
        position = (Game175250Vec3 *)(list + (*(s8 *)((u8 *)arg0 + 0x2D) * 0x14));
        *(Game175250Vec3 *)((u8 *)arg0 + 0x54) = *position;
    } else {
        *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
    }
    return (s8)(state == 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147EB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15147EB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_1514803C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_151488C4.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15148AF4 CURRENT (860) */
s32 func_15148AF4(void *arg0) {
    s8 var_a1;
    void *temp_a2;
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x98);
    var_a1 = *(s8 *)((u8 *)arg0 + 0x2E);
    do {
        var_a1 -= 1;
        if (var_a1 < 0) {
            var_a1 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        temp_a2 = *(s32 *)((u8 *)arg0 + 0x94) + (var_a1 * 0x14);
        *(f32 *)((u8 *)temp_a2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_a2 + 0xC) - (*(f32 *)((u8 *)temp_v1 + 0x10) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 0) = (f32) (*(f32 *)((u8 *)temp_a2 + 0) + (*(f32 *)((u8 *)temp_v1 + 4) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 4) = (f32) (*(f32 *)((u8 *)temp_a2 + 4) + (*(f32 *)((u8 *)temp_a2 + 0xC) * D_800BE9A4));
        *(f32 *)((u8 *)temp_a2 + 8) = (f32) (*(f32 *)((u8 *)temp_a2 + 8) + (*(f32 *)((u8 *)temp_v1 + 0xC) * D_800BE9A4));
    } while (var_a1 != *(s8 *)((u8 *)arg0 + 0x2D));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15148AF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148AF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148BA4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15148DE0 CURRENT (1050) */
s32 func_15148DE0(void *arg0) {
    s32 var_v0;
    s32 temp_t9;
    s8 temp_v0;
    s32 var_a2;
    u8 *temp_a1;
    u8 *temp_v1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 >= 3) {
        *(s8 *)((u8 *)arg0 + 0x2C) = temp_v0 - 1;
        temp_a1 = *(u8 **)((u8 *)arg0 + 0x98);
        temp_v1 = *(u8 **)((u8 *)arg0 + 0x94);
        temp_t9 = (0x1000 / *(s8 *)((u8 *)arg0 + 0x2C)) & 0xFFFF;
        var_a2 = *(s8 *)((u8 *)arg0 + 0x2D);
        var_v0 = 0;
        if (temp_a1[0x18] & 0x20) {
            var_v0 = 0x1000;
        }
        *(s8 *)((u8 *)arg0 + 0x2E) = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (*(s8 *)((u8 *)arg0 + 0x2E) < 0) {
            *(s8 *)((u8 *)arg0 + 0x2E) = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        if (var_a2 != *(s8 *)((u8 *)arg0 + 0x2E)) {
            do {
                *(s16 *)(temp_v1 + (var_a2 * 0x14) + 0x10) = var_v0;
                if (temp_a1[0x18] & 0x20) {
                    var_v0 = (var_v0 - temp_t9) & 0xFFFF;
                } else {
                    var_v0 = (var_v0 + temp_t9) & 0xFFFF;
                }
                var_a2 += 1;
                if (var_a2 == *(u8 *)((u8 *)arg0 + 0x25)) {
                    var_a2 = 0;
                }
            } while (var_a2 != *(s8 *)((u8 *)arg0 + 0x2E));
        }
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15148DE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148DE0.s")
s32 func_15148EF8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x98);
    *(u8 *)((u8 *)temp_v1 + 0x20) = 4;
    return 1;
}
f32 func_151423D8(u8);

typedef struct Game175250PrimaryPacket {
    f32 x;
    f32 y;
    f32 z;
    s16 angle;
    s16 enabled;
    s32 active;
    u8 pad14;
    s8 kind;
    u8 pad16[2];
} Game175250PrimaryPacket;

typedef struct Game175250SecondaryPacket {
    f32 value0;
    f32 value1;
    f32 value2;
    f32 value3;
    f32 value4;
    u8 pad14[4];
    u8 size;
    u8 type;
    u8 color0;
    u8 color1;
    u8 pad1C[4];
} Game175250SecondaryPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15148F1C CURRENT (443) */
void func_15148F1C(u8 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4,
                    s32 arg5, s32 arg6, f32 arg7, s16 arg8, f32 arg9,
                    f32 arg10, u8 arg11) {
    Game175250PrimaryPacket primary;
    Game175250SecondaryPacket secondary;
    f32 channel0;
    f32 channel1;
    f32 channel2;
    Struct15147DA0 colors;
    f32 channel3;
    f32 amount;

    channel0 = func_151423D8((u8)arg6);
    channel1 = func_151423D8((u8)(arg6 - 0x40));
    channel2 = func_151423D8((u8)arg5);
    channel3 = func_151423D8((u8)(arg5 - 0x40));

    primary.active = 1;
    primary.enabled = 1;
    secondary.color0 = 0xFF;
    secondary.size = 8;
    secondary.type = arg0;
    if (arg0 == 0xA) {
        secondary.size = 0x28;
    }

    primary.x = arg1;
    primary.y = arg2;
    primary.z = arg3;
    secondary.value0 = arg9;
    secondary.value4 = arg10;
    amount = arg7 * channel0;
    secondary.value1 = amount * channel3;
    secondary.value2 = -arg7 * channel1;
    secondary.value3 = amount * channel2;
    primary.kind = arg4 + 3;
    secondary.color1 = 0xFF;
    primary.angle = arg8;

    colors.values[0] = 0;
    colors.values[1] = 1;
    colors.values[2] = 0x160600;
    colors.values[3] = 3;
    colors.values[4] = 0x10;
    colors.values[5] = 0x80;
    colors.values[6] = 0x20;
    ((u8 *)&colors)[0x1C] = 0;
    ((u8 *)&colors)[0x1D] = 9;
    func_15147DA0(&primary, &secondary, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                  &colors, 0, arg11, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15148F1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_15148F1C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151490C8 CURRENT (425) */
s32 func_151490C8(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151490C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_175250/func_151490C8.s")
void func_15149104(void) {
    func_151478F4();
}
