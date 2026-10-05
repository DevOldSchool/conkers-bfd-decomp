#include "types.h"

/*
 * Reviewed source unit: src/game/game_18A8F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515D480
 * - func_1515D4D4
 * - func_1515D520
 * - func_1515D6D0
 * - func_1515D914
 * - func_1515E278
 * - func_1515E43C
 * - func_1515E544
 * - func_1515E888
 * - func_1515EB84
 * - func_1515EC78
 * - func_1515F008
 * - func_1515F040
 * - func_1515F0AC
 * - func_1515F338
 * - func_1515F5C4
 * - func_1515F850
 * - func_1515FB70
 * - func_1515FBC4
 * - func_1515FC60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game18A8F0Node {
    u8 pad0[0xC];
    struct Game18A8F0Node *next;
} Game18A8F0Node;

typedef struct Game18A8F0ListNode {
    struct Game18A8F0ListNode *next;
} Game18A8F0ListNode;

typedef struct Game18A8F0ValueNode {
    s32 value;
    f32 field_4;
    f32 field_8;
    s32 field_C;
} Game18A8F0ValueNode;

extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_100226F0(void *arg0, s32 arg1);
extern void *D_800DCD78;

void *func_1515D440(void) {
    void *temp_v0;

    temp_v0 = func_10003C40(0x10, 1, 2, 0);
    func_100226F0(temp_v0, 0x10);
    return temp_v0;
}
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D480 CURRENT (42) */
void *func_1515D480(s32 arg0) {
    s32 sp18;
    void *sp1C;

    sp18 = arg0 * 0x60;
    sp1C = func_10003C40(sp18, 1, 2, 0);
    func_100226F0(sp1C, sp18);
    return sp1C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D480 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D480.s")
extern s8 D_800DCD20[];
extern u8 D_800DCD27;
extern s32 D_800DCD7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D4D4 CURRENT (450) */
void func_1515D4D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg3 = arg3 & 0xFF;
    if (arg3 >= (s32)D_800DCD27) {
        D_800DCD20[0] = arg0;
        D_800DCD20[1] = arg1;
        D_800DCD20[2] = arg2;
        D_800DCD7C = 1;
        D_800DCD27 = (u8)arg3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D4D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D4D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D520 CURRENT (255) */
void *func_1515D520(void) {
    struct {
        s32 *cursor;
        s32 *allocated;
    } state;
    void *var_v1;

    state.allocated = (s32 *)func_10003C40(0x34, 1, 2, 2);
    if (state.allocated != 0) {
        func_100226F0(state.allocated, 0x34);
        if (D_800DCD78 != 0) {
            state.cursor = *(s32 **)D_800DCD78;
            var_v1 = D_800DCD78;
            if (state.cursor != 0) {
                do {
                    var_v1 = state.cursor;
                    state.cursor = *(s32 **)state.cursor;
                } while (state.cursor != 0);
            }
            *(s32 **)var_v1 = state.allocated;
        } else {
            D_800DCD78 = state.allocated;
        }
        *state.allocated = 0;
    }
    return state.allocated;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D520.s")
void *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

void func_1515D5AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, (u8) (s32) arg9);
}
void *func_1515D520();                              /* extern */

void *func_1515D5F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    void *temp_v0;

    temp_v0 = func_1515D520();
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 4) = 0;
        *(s8 *)((u8 *)temp_v0 + 5) = (s8) arg4;
        *(s8 *)((u8 *)temp_v0 + 6) = (s8) arg5;
        *(s8 *)((u8 *)temp_v0 + 7) = (s8) arg6;
        *(s8 *)((u8 *)temp_v0 + 8) = (s8) arg7;
        *(s8 *)((u8 *)temp_v0 + 9) = (s8) arg8;
        *(u8 *)((u8 *)temp_v0 + 0xB) = arg9;
        *(s8 *)((u8 *)temp_v0 + 0xA) = 0;
        *(s16 *)((u8 *)temp_v0 + 0xE) = (s16) arg0;
        *(s16 *)((u8 *)temp_v0 + 0x10) = (s16) arg1;
        *(s16 *)((u8 *)temp_v0 + 0x12) = (s16) arg2;
        *(s8 *)((u8 *)temp_v0 + 0x2F) = (s8) arg3;
        *(s8 *)((u8 *)temp_v0 + 0x2C) = 0x7F;
        *(s8 *)((u8 *)temp_v0 + 0x2D) = 0;
        *(s8 *)((u8 *)temp_v0 + 0x2E) = 0;
    }
    return temp_v0;
}
void func_1515D69C(void) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            *(s8 *)((u8 *)var_v0 + 0xC) = 0;
            *(s8 *)((u8 *)var_v0 + 0x30) = 0;
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
void func_1515D6C8(void) {

}
extern s32 D_800BE628;
extern u8 D_800BE9C0;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D6D0 CURRENT (11155) */
void *func_1515D6D0(u8 *arg0, s32 arg1) {
    u8 *temp_a2;
    u8 *temp_a2_10;

    u8 *temp_a2_12;
    u8 *temp_a2_2;
    u8 *temp_a2_3;
    u8 *temp_a2_4;
    u8 *temp_a2_5;
    u8 *temp_a2_6;
    u8 *temp_a2_7;
    u8 *temp_a2_8;
    u8 *temp_a2_9;

    *(s32 *)((u8 *)arg0 + 0) = 0xDB020000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    temp_a2_2 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)temp_a2_2 + 4) = 0x20000;
    *(s32 *)((u8 *)arg0 + 8) = 0xD9FFFFFF;
    arg0 = (void *)(temp_a2_2 + 8);
    func_1515EF74(D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 << 6) + 0x100);
    *(s32 *)((u8 *)arg0 + 0) = 0xDB100000;
    temp_a2_3 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 4) = (s32) ((((s32) *(s32 *)((u8 *)D_800DCD10 + 4) >> 0x10) & 0xFFFF) | (((s32) *(s32 *)((u8 *)D_800DCD10 + 0) >> 0x10) << 0x10));
    *(s32 *)((u8 *)arg0 + 8) = 0xDB100008;
    temp_a2_4 = (void *)(temp_a2_3 + 8);
    *(s32 *)((u8 *)temp_a2_3 + 4) = (s32) ((((s32) *(s32 *)((u8 *)D_800DCD10 + 4) >> 0x10) & 0xFFFF) | (((s32) *(s32 *)((u8 *)D_800DCD10 + 0) >> 0x10) << 0x10));
    *(s32 *)((u8 *)temp_a2_3 + 8) = 0xDB100004;
    temp_a2_5 = (void *)(temp_a2_4 + 8);
    *(s32 *)((u8 *)temp_a2_4 + 4) = (s32) (((s32) *(s32 *)((u8 *)D_800DCD10 + 8) >> 0x10) << 0x10);
    *(s32 *)((u8 *)temp_a2_4 + 8) = 0xDB10000C;
    temp_a2_6 = (void *)(temp_a2_5 + 8);
    *(s32 *)((u8 *)temp_a2_5 + 4) = (s32) (((s32) *(s32 *)((u8 *)D_800DCD10 + 8) >> 0x10) << 0x10);
    *(s32 *)((u8 *)temp_a2_5 + 8) = 0xDB100010;
    temp_a2_7 = (void *)(temp_a2_6 + 8);
    *(s32 *)((u8 *)temp_a2_6 + 4) = (s32) ((*(s32 *)((u8 *)D_800DCD10 + 4) & 0xFFFF) | (*(s32 *)((u8 *)D_800DCD10 + 0) << 0x10));
    *(s32 *)((u8 *)temp_a2_6 + 8) = 0xDB100018;
    temp_a2_8 = (void *)(temp_a2_7 + 8);
    *(s32 *)((u8 *)temp_a2_7 + 4) = (s32) ((*(s32 *)((u8 *)D_800DCD10 + 4) & 0xFFFF) | (*(s32 *)((u8 *)D_800DCD10 + 0) << 0x10));
    *(s32 *)((u8 *)temp_a2_7 + 8) = 0xDB100014;
    temp_a2_9 = (void *)(temp_a2_8 + 8);
    *(s32 *)((u8 *)temp_a2_8 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 8) << 0x10);
    *(s32 *)((u8 *)temp_a2_8 + 8) = 0xDB10001C;
    temp_a2_10 = (void *)(temp_a2_9 + 8);
    *(s32 *)((u8 *)temp_a2_9 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 8) << 0x10);
    *(s32 *)((u8 *)temp_a2_9 + 8) = 0xDB100020;
    {
    u8 *temp_a2_11;
    temp_a2_11 = (void *)(temp_a2_10 + 8);
    *(s32 *)((u8 *)temp_a2_10 + 4) = 0;
    *(s32 *)((u8 *)temp_a2_10 + 8) = 0xDB100024;
    temp_a2_12 = (void *)(temp_a2_11 + 8);
    *(s32 *)((u8 *)temp_a2_11 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 0xC) << 0x10);
    *(s32 *)((u8 *)temp_a2_11 + 8) = 0xDB100028;
    }
    temp_a2 = (void *)(temp_a2_12 + 8);
    *(s32 *)((u8 *)temp_a2_12 + 4) = 0;
    *(s32 *)((u8 *)temp_a2_12 + 8) = 0xDB10002C;
    *(s32 *)((u8 *)temp_a2 + 4) = (s32) (*(s32 *)((u8 *)D_800DCD10 + 0xC) << 0x10);
    return temp_a2 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D6D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D6D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D914.s")
struct Game18A8F0SearchNode;
typedef struct {
    u8 pad0[0x18];
    u32 field_18;
    u32 field_1C;
} Game18A8F0ColorResult;

Game18A8F0ColorResult *func_1515EB84(s32, s32, s32, s32,
                                     struct Game18A8F0SearchNode *);
void func_1515E43C(s32, s32, s32, s32, u8 *, u8 *, u8 *, u8 *);
extern u8 D_800DCD23;
extern struct Game18A8F0SearchNode *D_800DCD80;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515E278 CURRENT (2974) */
void func_1515E278(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *volatile arg4, u32 arg5, s32 arg6) {
    u8 sp50[3];
    u8 sp4C[3];
    u8 sp48[3];
    u8 sp47;
    u8 sp46;
    u8 *var_a1;
    s32 temp_t8_2;
    s32 var_a3;
    u8 *var_v0;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 *var_a2;
    u8 *var_t0;
    u8 temp_t4;
    u8 temp_t8;
    u8 temp_v0_2;
    Game18A8F0ColorResult *temp_v0;

    temp_v0 = func_1515EB84(arg0, arg1, arg2, arg3, D_800DCD80);
    var_a0 = arg4;
    if (temp_v0 != 0) {
        var_a0_2 = arg4;
        var_a0_2[0] = temp_v0->field_18;
        var_a0_2[1] = temp_v0->field_18 >> 8;
        var_a0_2[2] = temp_v0->field_18 >> 16;
    } else {
        var_v0 = (u8 *)D_800DCD20;
fallback_loop:
        {
            temp_t8 = *var_v0;
            var_v0++;
            var_a0++;
            var_a0[-1] = (s32)(temp_t8 * (0x100 - (((arg5 >> 5) & 3) << 6))) >> 8;
        }
        if (var_v0 != &D_800DCD23) {
            goto fallback_loop;
        }
    }
    if (arg6 & 0x10) {
        func_1515E43C(arg0, arg1, arg2, arg3, sp4C, sp48, &sp47, &sp46);
        var_a0_2 = arg4;
        var_a1 = sp50;
        var_t0 = sp4C;
        var_a2 = sp48;
        do {
            temp_v0_2 = *var_a0_2;
            temp_t4 = *var_t0;
            var_a1++;
            var_t0++;
            var_a2++;
            var_a1[-1] = (s32)(temp_t4 * ((temp_v0_2 + ((s32)((0xFF - temp_v0_2) * sp47) >> 8)) & 0xFF)) >> 8;
            temp_v0_2 = *var_a0_2;
            temp_t8_2 = (s32)(var_a2[-1] * ((temp_v0_2 + ((s32)((0xFF - temp_v0_2) * sp46) >> 8)) & 0xFF)) >> 8;
            *var_a0_2 = temp_t8_2;
            var_a3 = ((s32)(var_a1[-1] * 7) >> 3) + (temp_t8_2 & 0xFF);
            if (var_a3 >= 0x100) {
                var_a3 = 0xFF;
            }
            *var_a0_2 = var_a3;
            var_a0_2++;
        } while (var_a2 != sp48 + 3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515E278 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E278.s")
extern u8 D_800DCD24[];
extern u8 D_800DCD28[];
extern u8 D_800DCD3C;
extern u8 D_800DCD3D;
extern struct Game18A8F0SearchNode *D_800DCD84;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515E43C CURRENT (280) */
void func_1515E43C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4,
                   u8 *arg5, u8 *arg6, u8 *arg7) {
    Game18A8F0ColorResult *temp_v0;

    temp_v0 = func_1515EB84(arg0, arg1, arg2, 0, D_800DCD84);
    if (temp_v0 != 0) {
        arg4[0] = temp_v0->field_18;
        arg4[1] = temp_v0->field_18 >> 8;
        arg4[2] = temp_v0->field_18 >> 16;
        arg5[0] = temp_v0->field_1C;
        arg5[1] = temp_v0->field_1C >> 8;
        arg5[2] = temp_v0->field_1C >> 16;
        *arg6 = temp_v0->field_1C >> 24;
        *arg7 = temp_v0->field_18 >> 24;
    } else {
        arg4[0] = D_800DCD24[0];
        arg4[1] = D_800DCD24[1];
        arg4[2] = D_800DCD24[2];
        arg5[0] = D_800DCD28[0];
        arg5[1] = D_800DCD28[1];
        arg5[2] = D_800DCD28[2];
        *arg6 = D_800DCD3C;
        *arg7 = D_800DCD3D;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515E43C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E43C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E544.s")
void func_1515E278(s32, s32, s32, s32, u8 *, u32, s32);
extern u8 D_800D9E21;
extern u8 *D_800D9E28[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515E888 CURRENT (12477) */
void func_1515E888(s32 arg0, s32 x, s32 y, s32 z, s32 mode,
                   u8 *color, u32 flags, s32 options) {
    f32 channels[3];
    f32 position[3];
    f32 dx, dy, dz, amount;
    s32 count, index, value;
    u8 **slot;
    u8 *light;

    func_1515E278(x, y, z, mode, color, flags, options);
    channels[0] = (f32)(u32)color[0];
    channels[1] = (f32)(u32)color[1];
    channels[2] = (f32)(u32)color[2];
    index = 0;
    count = (D_800D9E21 & 0x7F) - 1;
    if (count > 0) {
        slot = D_800D9E28;
        do {
            light = *slot;
            index++;
            if (light != 0) {
                position[0] = *(s16 *)(light + 0xE);
                position[1] = *(s16 *)(light + 0x10);
                position[2] = *(s16 *)(light + 0x12);
                dz = position[2] - (f32)z;
                dx = position[0] - (f32)x;
                dy = position[1] - (f32)y;
                amount = ((f32)(u32)light[0x2F] * 2048.0f) /
                         (dz * dz + (dx * dx + dy * dy));
                if (amount > 1.0f) amount = 1.0f;
                channels[0] += amount * (f32)(u32)light[5];
                channels[1] += amount * (f32)(u32)light[6];
                channels[2] += amount * (f32)(u32)light[7];
            }
            slot++;
        } while (index != count);
    }
    value = (s32)channels[0];
    if (value >= 256) value = 255;
    color[0] = value;
    value = (s32)channels[1];
    if (value >= 256) value = 255;
    color[1] = value;
    value = (s32)channels[2];
    if (value >= 256) value = 255;
    color[2] = value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515E888 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E888.s")

typedef struct Game18A8F0SearchActor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xC];
    f32 field_2C;
    f32 field_30;
    f32 field_34;
    u8 pad38[0x148];
    f32 field_180;
    u8 pad184[0x1A8];
} Game18A8F0SearchActor;

typedef struct Game18A8F0SearchEntry {
    u8 pad0[0x14];
    u8 field_14;
    u8 field_15;
    u8 pad16[2];
    u32 flags_18;
} Game18A8F0SearchEntry;

typedef struct Game18A8F0SearchNode {
    struct Game18A8F0SearchNode *next;
    Game18A8F0SearchEntry *entry;
} Game18A8F0SearchNode;

s32 func_150A1DA0(Game18A8F0SearchActor *, Game18A8F0SearchEntry *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515EB84 CURRENT (20) */
void *func_1515EB84(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    Game18A8F0SearchNode *arg4) {
    Game18A8F0SearchActor actor;
    Game18A8F0SearchEntry *entry;

    actor.y = (f32)arg1;
    actor.field_180 = (f32)arg1;
    actor.field_30 = (f32)arg1;
    actor.x = (f32)arg0;
    actor.field_2C = (f32)arg0;
    actor.z = (f32)arg2;
    actor.field_34 = (f32)arg2;
    if (arg4 != 0) {
        do {
            entry = arg4->entry;
            if ((entry->field_14 == 0) &&
                ((arg3 == 0) || (((entry->flags_18 >> 24) & arg3) != 0)) &&
                (((entry->field_15 >> 2) == 0x18) ||
                 ((entry->flags_18 >> 31) == 0)) &&
                (func_150A1DA0(&actor, entry, 0) == 0)) {
                return arg4->entry;
            }
            arg4 = arg4->next;
        } while (arg4 != 0);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515EB84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EB84.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
f32 sqrtf(f32);
#pragma intrinsic (sqrtf)
extern u8 D_800D9C10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515EC78 CURRENT (6744) */
void func_1515EC78(u8 *light, s32 slot, u8 *output, s32 x, s32 y,
                   s32 z, s32 flags) {
    f32 transformed[3];
    s32 position[3];
    s32 normal[3];
    u32 mask;

    position[0] = *(s16 *)(light + 0xE);
    if (position[0] != -0x8000) {
        position[1] = *(s16 *)(light + 0x10);
        position[2] = *(s16 *)(light + 0x12);
    } else {
        f32 *source;
        source = (f32 *)(((u32)*(s16 *)(light + 0x12) & 0xFFFFU) |
                         ((u32)*(s16 *)(light + 0x10) << 16));
        position[0] = (s32)source[0];
        position[1] = (s32)source[1];
        position[2] = (s32)source[2];
    }
    if (flags & 2) {
        f32 dx, dy, dz, distance, scale;
        dx = (f32)(s32)((u32)position[0] - (u32)x);
        dy = (f32)(s32)((u32)position[1] - (u32)y);
        dz = (f32)(s32)((u32)position[2] - (u32)z);
        distance = sqrtf((dx * dx + dy * dy) + dz * dz);
        if (distance != 0.0f) {
            scale = 127.0f / distance;
            dx *= scale;
            dy *= scale;
            dz *= scale;
        } else {
            dz = 0.0f;
            dx = 127.0f;
            dy = 0.0f;
        }
        normal[0] = (s32)dx;
        normal[1] = (s32)dy;
        normal[2] = (s32)dz;
    } else {
        normal[0] = 0;
        normal[1] = 0;
        normal[2] = 127;
    }
    mask = 1U << slot;
    if (light[0x30] & mask) {
        u8 *cache;
        cache = (u8 *)((u32)light + (u32)(slot * 6));
        position[0] = *(s16 *)(cache + 0x14);
        position[1] = *(s16 *)(cache + 0x16);
        position[2] = *(s16 *)(cache + 0x18);
    } else {
        u8 *cache;
        func_150A7960(D_800D9C10 + (slot << 6),
                     (f32)position[0], (f32)position[1], (f32)position[2],
                     transformed, transformed + 1, transformed + 2);
        position[0] = (s32)transformed[0];
        position[1] = (s32)transformed[1];
        position[2] = (s32)transformed[2];
        cache = (u8 *)((u32)light + (u32)(slot * 6));
        *(s16 *)(cache + 0x14) = position[0];
        *(s16 *)(cache + 0x16) = position[1];
        *(s16 *)(cache + 0x18) = position[2];
        light[0x30] |= mask;
    }
    {
        u8 *half_output, *color, *byte_output;
        s32 *direction, *point;
        half_output = output;
        color = light;
        direction = normal;
        point = position;
        byte_output = output;
        do {
            point++;
            byte_output++;
            byte_output[-1] = color[5];
            byte_output[3] = color[5];
            color++;
            direction++;
            half_output += 2;
            byte_output[7] = direction[-1];
            *(s16 *)(half_output + 0x1E) = point[-1];
            *(s16 *)(half_output + 0x26) = point[-1];
        } while (point != position + 3);
    }
    output[0xC] = light[0x2F];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515EC78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EC78.s")

f32 func_1515F008(s32, s32);
void func_1515F040(f32, s32);
void func_1515F0AC(f32, s32);
void func_1515EF74(s32 arg0) {
    func_1515F040(1.0f / func_1515F008(arg0, 0), 0);
    func_1515F040(1.0f / func_1515F008(arg0, 5), 1);
    func_1515F040(1.0f / func_1515F008(arg0, 0xA), 2);
    func_1515F0AC(-func_1515F008(arg0, 0xE), 3);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F008 CURRENT (35) */
f32 func_1515F008(s32 arg0, s32 arg1) {
    s32 value;
    s16 *temp_v1;

    temp_v1 = (s16 *)arg0 + arg1;
    value = *temp_v1;
    value = *(u16 *)((u8 *)temp_v1 + 0x20) | (value << 0x10);
    return (f32)value * 0.000015258789f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F008.s")
extern f32 D_800A6520;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F040 CURRENT (120) */
void func_1515F040(f32 arg0, s32 arg1) {
    f32 var_fv0;

    var_fv0 = D_800A6520;
    if (var_fv0 <= arg0) {
        arg0 = var_fv0;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    arg0 *= 65536.0f;
    D_800DCD10[arg1] = (s32) arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F040 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F040.s")
extern f32 D_800A6524;
extern s32 D_800DCD10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F0AC CURRENT (220) */
void func_1515F0AC(f32 arg0, s32 arg1) {
    f32 var_fv0;

    var_fv0 = D_800A6524;
    if (arg0 >= var_fv0) {
        arg0 = var_fv0;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    D_800DCD10[arg1] = (s32) arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F0AC.s")
void func_10004074(s32);

void func_1515F10C(Game18A8F0ListNode *arg0) {
    Game18A8F0ListNode *var_a1;
    Game18A8F0ListNode *var_v0;

    var_a1 = D_800DCD78;
    var_v0 = 0;
    if (var_a1 != arg0) {
        do {
            var_v0 = var_a1;
            var_a1 = var_a1->next;
        } while (var_a1 != arg0);
    }
    if (var_v0 != 0) {
        var_v0->next = var_a1->next;
    } else {
        D_800DCD78 = var_a1->next;
    }
    func_10004074((s32)var_a1);
}
void func_1515F170(s32 arg0, u8 arg1) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(u8 *)((u8 *)var_v0 + 0xB)) {
                *(s8 *)((u8 *)var_v0 + 9) = (s8) (arg1 & 0xFF);
            }
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
extern Game18A8F0ValueNode *func_10003C6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern f32 func_15144598(s32 arg0);
extern f32 func_1514462C(s32 arg0);

Game18A8F0ValueNode *func_1515F1B0(s32 arg0) {
    Game18A8F0ValueNode *var_v1;

    var_v1 = func_10003C6C(0x10, 1, 2, 0, 1);
    if (var_v1 == 0) {
        return 0;
    }
    var_v1->value = arg0;
    if (arg0 != 0) {
        var_v1->field_4 = func_1514462C(arg0);
    } else {
        var_v1->field_4 = 0.0f;
    }
    if (arg0 != 0) {
        var_v1->field_8 = func_15144598(arg0);
    } else {
        var_v1->field_8 = 0.0f;
    }
    var_v1->field_C = 0;
    return var_v1;
}
void func_1515F25C(Game18A8F0Node **arg0, Game18A8F0Node *arg1) {
    arg1->next = *arg0;
    *arg0 = arg1;
}
extern void (*D_8008B090[])(void *, void *);

void func_1515F270(void *arg0, void *arg1) {
    void (*temp_v1)(void *, void *);
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg1 + 0x18);
    if ((temp_v0 >= 0) && (temp_v0 < 0xC)) {
        temp_v1 = D_8008B090[temp_v0];
        if (temp_v1 != 0) {
            temp_v1(arg0, arg1);
        }
    }
}
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515F2B8(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6001D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
typedef struct {
    u8 pad_0[0x3B];
    u8 field_3B;
} Game18A8F0State;

typedef struct {
    u8 pad_0[0x1C];
    s32 field_1C;
} Game18A8F0Selection;

extern void (*D_8008B0C0[])(void);

void func_1515F2E8(Game18A8F0State *arg0, Game18A8F0Selection *arg1) {
    s32 temp_v0;

    if (arg0->field_3B == 1) {
        temp_v0 = arg1->field_1C;
        if ((temp_v0 >= 0) && (temp_v0 < 3)) {
            D_8008B0C0[temp_v0]();
        }
    }
}
extern f32 D_800DCD94;
extern f32 D_800DCD98;
extern f32 D_800DCD9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F338 */
void func_1515F338(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    var_t0 = *(u8 *)((u8 *)D_800DCD20 + 1);
    var_t1 = *(u8 *)((u8 *)D_800DCD20 + 2);
    if (D_800DCD94 != 97.0f) {
        D_800DCD94 += (97.0f - D_800DCD94) * 0.5f;
        var_v1 = (u32) D_800DCD94 & 0xFF;
    }
    if (D_800DCD98 != 96.0f) {
        D_800DCD98 += (96.0f - D_800DCD98) * 0.5f;
        var_t0 = (u32) D_800DCD98 & 0xFF;
    }
    if (D_800DCD9C != 98.0f) {
        D_800DCD9C += (98.0f - D_800DCD9C) * 0.5f;
        var_t1 = (u32) D_800DCD9C & 0xFF;
    }
    func_1515D4D4((s32) var_v1, (s32) var_t0, (s32) var_t1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F338 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F338.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F5C4 */
void func_1515F5C4(s32 arg0, s32 arg1) {
    u8 var_t0;
    u8 var_t1;
    u8 var_v1;

    var_v1 = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    var_t0 = *(u8 *)((u8 *)D_800DCD20 + 1);
    var_t1 = *(u8 *)((u8 *)D_800DCD20 + 2);
    if (D_800DCD94 != 229.0f) {
        D_800DCD94 += (229.0f - D_800DCD94) * 0.5f;
        var_v1 = (u32) D_800DCD94 & 0xFF;
    }
    if (D_800DCD98 != 253.0f) {
        D_800DCD98 += (253.0f - D_800DCD98) * 0.5f;
        var_t0 = (u32) D_800DCD98 & 0xFF;
    }
    if (D_800DCD9C != 160.0f) {
        D_800DCD9C += (160.0f - D_800DCD9C) * 0.5f;
        var_t1 = (u32) D_800DCD9C & 0xFF;
    }
    func_1515D4D4((s32) var_v1, (s32) var_t0, (s32) var_t1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F5C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F5C4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32, f32);                        /* extern */
extern f32 D_800A6530;
extern f32 D_800BE9A4;
extern f32 D_800DCDA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F850 CURRENT (1647) */
void func_1515F850(s32 arg0, s32 arg1) {
    f32 sp28;
    f32 sp24;
    u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;

    sp1C = (u8) *(s8 *)((u8 *)D_800DCD20 + 0);
    sp1D = *(u8 *)((u8 *)D_800DCD20 + 1);
    sp1E = *(u8 *)((u8 *)D_800DCD20 + 2);
    temp_fv0 = func_15047D60(D_800DCDA0);
    temp_fa1 = (temp_fv0 * 29.5f) + 127.5f;
    temp_ft4 = (temp_fv0 * 71.0f) + 109.0f;
    sp28 = temp_fa1;
    sp24 = temp_ft4;
    temp_ft5 = (temp_fv0 * 26.0f) + 26.0f;
    {
        f32 sp20 = temp_ft5;
    D_800DCDA0 += D_800A6530 * D_800BE9A4;
    D_800DCDA0 = func_15144B68(D_800DCDA0, temp_fa1);
    if (temp_fa1 != D_800DCD94) {
        D_800DCD94 += (temp_fa1 - D_800DCD94) * 0.5f;
        sp1C = (u8) (u32) D_800DCD94;
    }
    if (temp_ft4 != D_800DCD98) {
        D_800DCD98 += (temp_ft4 - D_800DCD98) * 0.5f;
        sp1D = (u8) (u32) D_800DCD98;
    }
    if (temp_ft5 != D_800DCD9C) {
        D_800DCD9C += (temp_ft5 - D_800DCD9C) * 0.5f;
        sp1E = (u8) (u32) D_800DCD9C;
    }
    func_1515D4D4((s32) sp1C, (s32) sp1D, (s32) sp1E, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F850.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FB70 CURRENT (725) */
void func_1515FB70(void *arg0, void *arg1) {
    if ((*(u8 *)((u8 *)arg0 + 0x3B) == 1) && (*(s32 *)((u8 *)arg1 + 0x1C) >= 0)) {

    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FB70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FB70.s")
void func_1515FB94(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6002D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
typedef struct Game18A8F0Actor {
    u8 pad0[0x7A];
    u16 field_7A;
    u8 pad7C[0x2B0];
} Game18A8F0Actor;

typedef struct Game18A8F0LookupResult {
    u8 pad0[0x98];
    Game18A8F0Actor *actor_98;
} Game18A8F0LookupResult;

Game18A8F0LookupResult *func_15105C24(s32);
extern Game18A8F0Actor D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FBC4 CURRENT (382) */
void func_1515FBC4(Game18A8F0Actor *arg0, s32 arg1) {
    Game18A8F0Actor * volatile sp18;
    Game18A8F0Actor *actor;
    Game18A8F0LookupResult *result;
    s32 actor_index;

    sp18 = 0;
    result = func_15105C24(arg1);
    actor = sp18;
    if (result != 0) {
        actor = result->actor_98;
    }
    if (actor != 0) {
        actor_index = actor - D_800CC2D0;
    } else {
        actor_index = -1;
    }
    func_1505D024((s32)arg0, 0x6002E, arg0->field_7A, actor_index);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FBC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FBC4.s")
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515FC34(s32 arg0, s32 arg1) {
    func_1505D024(arg0, 0x33, 0xC000, -1);
}
void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void func_15145A50(u8 *);
void func_1507CD64(u8 *, s32);
s32 func_150AD960(s16, s16, s32, s32);
extern f32 D_800A6534;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FC60 CURRENT (484) */
void func_1515FC60(u8 *arg0, u8 *arg1) {
    f32 scaled;
    f32 amount;
    s32 count;
    u8 *object;

    object = *(u8 **)(arg0 + 0x31C);
    if (object != 0 && object[0x120] == 0) {
        count = *(u32 *)(arg1 + 0x1C);
        if (count != 0) {
            amount = (f32)(u32)count;
            scaled = amount * D_800A6534;
            if ((f32)func_150AD960(*(s16 *)arg1, *(s16 *)(arg1 + 4),
                                     (s32)*(f32 *)(arg0 + 0x14),
                                     (s32)*(f32 *)(arg0 + 0x1C)) <
                ((f32)*(s16 *)(arg1 + 6) * scaled -
                 (f32)*(s16 *)(arg0 + 0xE4))) {
                return;
            }
        }
        func_1505D024((s32)arg0, 0x2F, 0, -1);
        func_15136C3C(arg0, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg0);
        func_1507CD64(arg0, 6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FC60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FC60.s")
