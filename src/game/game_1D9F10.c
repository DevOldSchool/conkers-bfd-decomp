#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D9F10.c
 * Boundary evidence: docs/evidence/game_raw_owner_point_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ACA60
 * - func_151ACB38
 * - func_151ACB60
 * - func_151ACBD4
 * - func_151AD174
 * - func_151AD92C
 * - func_151AE06C
 * - func_151AE0E4
 * - func_151AE2BC
 * - func_151AE3A8
 * - func_151AE590
 * - func_151AE640
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x10];
    s32 field10;
    s32 field14;
    u8 pad18[4];
    void *field1C;
    u8 field20;
    u8 pad21[3];
    s32 field24;
    f32 field28;
} Game1D9F10Record;

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1516979C(u8 *);
s32 func_151ACB38(void *, s8 *);
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACA60 CURRENT (510) */
Game1D9F10Record *func_151ACA60(void *arg0, f32 arg1, s32 arg2) {
    Game1D9F10Record *record;
    s32 difference;
    s32 actor_index;
    u8 type;

    if (arg0 == 0) {
        return 0;
    }
    record = func_15167A68(0x30, 0, arg2 + 0x30, 1, 0xFF, 1);
    if (record == 0) {
        return 0;
    }
    if (func_151ACB38(arg0, (s8 *)record + 0x18) == 0) {
        func_1516979C((u8 *)record);
        return 0;
    }
    difference = (s32)arg0 - (s32)&D_800CC2D0;
    actor_index = difference / 0x32C;
    *(void **)((u8 *)record + 0x1C) = arg0;
    type = *(u8 *)((u8 *)arg0 + 0x3B);
    *(s32 *)((u8 *)record + 0x24) = actor_index;
    *(u8 *)((u8 *)record + 0x20) = type;
    *(s32 *)((u8 *)record + 0x10) = 1;
    *(s32 *)((u8 *)record + 0x14) = 0;
    *(f32 *)((u8 *)record + 0x28) = arg1;
    return record;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACA60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACA60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACB38 CURRENT (805) */
s32 func_151ACB38(void *arg0, s8 *arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (*(u8 *)((u8 *)arg0 + 0x3B) == 1) {
        *arg1 = 1;
        var_v1 = 1;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACB38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACB38.s")
void func_151AE3A8(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACB60 CURRENT (200) */
void func_151ACB60(void *arg0) {
    s32 temp_v0 = *(s32 *)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)arg0 + 0x1C)) + 0x31C)) + 0x9C);

    if (temp_v0 != 0) {
        func_151AE3A8((s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACB60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACB60.s")
void func_151ACB94(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x1C, arg0 + 0x20, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACBD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD174.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD92C.s")
typedef struct {
    u8 pad0[0x98];
    u8 active_type;
} Game1D9F10NestedState;

typedef struct {
    u8 pad0[0x31C];
    Game1D9F10NestedState *nested;
} Game1D9F10Actor;

typedef struct {
    u8 pad0[0x1B];
    u8 type;
} Game1D9F10Event;

s32 func_151ACB38(void *, s8 *);
void func_151AE0E4(void *, u8);
void func_151AE264(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE06C CURRENT (10) */
void func_151AE06C(Game1D9F10Actor *arg0, Game1D9F10Event *arg1) {
    s8 matched;
    u8 type;
    s32 active_type;

    if (func_151ACB38(arg0, &matched) != 0) {
        type = arg1->type;
        active_type = arg0->nested->active_type;
        if (active_type == 0) {
            func_151AE0E4(arg0, type);
            return;
        }
        if (type == active_type) {
            return;
        }
        func_151AE264(arg0);
        func_151AE0E4(arg0, type);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE06C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE06C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE0E4.s")
extern f32 D_800A9294;

void func_151AE264(void *arg0) {
    f32 temp_fv0;
    void *temp_v0;

    temp_v0 = *(void **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x9C);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x3C) * D_800A9294;
    *(f32 *)((u8 *)temp_v0 + 0x4C) = temp_fv0;
    *(s8 *)((u8 *)temp_v0 + 0x50) = *(u16 *)((u8 *)arg0 + 0x76) >> 8;
    *(u8 *)((u8 *)temp_v0 + 0x51) = *(u8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xAE);
    *(s16 *)((u8 *)temp_v0 + 0x52) = 0x14;
    *(s32 *)((u8 *)temp_v0 + 0x44) = 0;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x98) = 0;
    *(void **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x9C) = 0;
}
typedef struct {
    f32 field_0;
    f32 field_4;
    u8 pad_8[0x10];
} Game1D9F10CurvePoint;

typedef struct {
    u8 pad_0[0x38];
    Game1D9F10CurvePoint *points;
    u8 pad_3C[6];
    u8 count;
} Game1D9F10Curve;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE2BC CURRENT (2778) */
void func_151AE2BC(s32 arg0, void *arg1, s32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_a2;
    s32 upper;
    s32 var_v1;
    u8 temp_v0;
    u8 *temp_a0;
    u8 *var_a0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 0x42);
    var_v1 = 0;
    temp_a2 = temp_v0 - 1;
    upper = temp_v0 - 2;
    if (temp_a2 > 0) {
        var_a0 = *(u8 **)((u8 *)arg1 + 0x38);
loop_2:
        if (!(arg3 <= *(f32 *)(var_a0 + 4))) {
            var_v1 += 1;
            var_a0 += 0x18;
            if (var_v1 != temp_a2) {
                goto loop_2;
            }
        }
    }
    if (var_v1 >= upper) {
        *(f32 *)arg0 = 1.0f;
        return;
    }
    if (var_v1 == 0) {
        *(f32 *)arg0 = 0.0f;
        return;
    }
    temp_a0 = *(u8 **)((u8 *)arg1 + 0x38) + (var_v1 * 0x18);
    temp_fv1 = *(f32 *)(temp_a0 - 0x14);
    temp_fv0 = *(f32 *)(temp_a0 + 4) - temp_fv1;
    if (temp_fv0 != 0.0f) {
        var_fv0 = (arg3 - temp_fv1) / temp_fv0;
    } else {
        var_fv0 = 0.0f;
    }
    *(f32 *)arg0 = ((f32)(var_v1 - 1) / (f32)(temp_v0 - 3)) + (var_fv0 / (f32)temp_a2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE2BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE3A8.s")
extern s32 D_800A9270[];
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE590 CURRENT (4360) */
void *func_151AE590(s32 arg0) {
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    do {
        var_v1 = 0;
        do {
            void *var_a0;
            s32 temp_t4;

            var_a0 = *(void **)(D_800DCE50 + (var_v1 * 0x1A0) + (D_800A9270[var_v0] * 4));
            temp_t4 = (var_v1 + 1) & 0xFF;
            if (var_a0 != 0) {
                do {
                    void *temp_a2;

                    temp_a2 = *(void **)((u8 *)var_a0 + 8);
                    if ((arg0 & 0xFF) == *(u8 *)((u8 *)var_a0 + 0x10)) {
                        return var_a0;
                    }
                    var_a0 = temp_a2;
                    if (temp_a2 == 0) {
                        break;
                    }
                } while (1);
            }
            var_v1 = temp_t4;
        } while (var_v1 < 2);
        var_v0 = (var_v0 + 1) & 0xFF;
    } while (var_v0 < 2);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE590 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE590.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE640 CURRENT (590) */
void func_151AE640(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x44)) {
            *(s32 *)((u8 *)arg0 + 0x44) = 0;
        }
    } else if (temp_t6 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x44);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x44) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x44) = temp_v0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE640.s")
