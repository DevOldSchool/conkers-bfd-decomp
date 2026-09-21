#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9D90.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507C8FC
 * - func_1507CD0C
 * - func_1507CD64
 * - func_1507D1D8
 * - func_1507D4F8
 * - func_1507D754
 * - func_1507DB6C
 * - func_1507DE4C
 * - func_1507DF10
 * - func_1507DFE4
 * - func_1507E1D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA9D90Inner {
    u8 pad0[0x120];
    u8 field_120;
    u8 pad121[3];
    s16 field_124;
} GameA9D90Inner;

typedef struct GameA9D90Object {
    u8 pad0[0x31C];
    GameA9D90Inner *field_31C;
} GameA9D90Object;

void func_1507C8E0(GameA9D90Object *arg0, s32 arg1) {
    arg0->field_31C->field_120 = 2;
    arg0->field_31C->field_124 = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")
void func_15181D70(s32, s32);
extern s32 D_80082FA0;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507CD0C CURRENT (35) */
void func_1507CD0C(void *arg0) {
    s32 temp_a1;
    s32 temp_lo;

    temp_a1 = (u8 *)arg0 - &D_800CC2D0;
    temp_lo = temp_a1 / 812;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x120) = 3;
    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo, temp_a1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507CD0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
typedef struct GameA9D90EntityIdRecord {
    u8 field_0;
    u8 pad_1[0x32B];
} GameA9D90EntityIdRecord;

extern GameA9D90EntityIdRecord D_800CC40F[];
void func_1509BFB0(s32, s32, s32, s32, s32, s32);

void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(3, temp_v0 | 0x2000, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")
void func_1503DE70(void *arg0, s32 arg1, s32 arg2);

void func_1507DB44(void *arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")
void func_150836CC(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DE4C CURRENT (35) */
void func_1507DE4C(void *arg0) {
    u8 temp_v0;

    if (*(s32 *)arg0 == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        *(s32 *)((u8 *)arg0 + 0x9C) |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }
    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 != 0x5A) && (temp_v0 != 0x74) && (temp_v0 != 0x7A)) {
        if ((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) {
            *(s32 *)((u8 *)arg0 + 0x9C) |= 0xF000;
        }
    } else {
        *(s32 *)((u8 *)arg0 + 0x9C) |= 0xFF8;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507DE4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DE4C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DF10 CURRENT (960) */
void func_1507DF10(void *arg0, s32 arg1) {
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t7;

    switch (arg1) {
    case 9:
        *(s32 *)((u8 *)arg0 + 0x94) = (s32) (*(s32 *)((u8 *)arg0 + 0x94) | 0x20);
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0x78);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 1;
        return;
    case 8:
        temp_t3 = *(s32 *)((u8 *)arg0 + 0x94) | 0x40;
        *(s32 *)((u8 *)arg0 + 0x94) = temp_t3;
        *(s32 *)((u8 *)arg0 + 0x94) = (s32) (temp_t3 & ~0x200);
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0xF00);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 2;
        return;
    case 6:
    case 7:
        temp_t0 = *(s32 *)((u8 *)arg0 + 0x94) | 0xE;
        *(s32 *)((u8 *)arg0 + 0x94) = temp_t0;
        *(s32 *)((u8 *)arg0 + 0x94) = (s32) (temp_t0 & ~0x410);
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0xEE0000);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 4;
        return;
    case 4:
    case 5:
        temp_t7 = *(s32 *)((u8 *)arg0 + 0x94) | 0x80;
        *(s32 *)((u8 *)arg0 + 0x94) = temp_t7;
        *(s32 *)((u8 *)arg0 + 0x94) = (s32) (temp_t7 & ~0x500);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 8;
        /* fallthrough */
    default:
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507DF10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DF10.s")
void func_1501D348(s32, s32, s32, u8, s32);
void func_15022190(s16, s16, s16, f32);
void func_15084D70(s32, u8, s32, void *, void *, void *, void *, void *, void *, s32, s32 *);
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
extern s8 D_800C3670;
extern s8 D_800C3671;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DFE4 CURRENT (487) */
void func_1507DFE4(u8 arg0, s32 arg1) {
    s32 sp64;
    s16 sp5C[3];
    u8 sp50[12];
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    s32 sp44;
    s32 sp3C;
    s32 sp38;
    f32 angle;

    if (D_800C35EA != 1) {
        func_15084D70(0, arg0, 1, sp5C, sp50, &sp4F, &sp4E,
                      &sp44, &sp48, 1, &sp38);
        angle = ((f32)(sp4E - 0x40) * 1.40625f) + 180.0f;
        if (sp38 == 0) {
            sp3C = 1;
            goto play;
        }
        if (sp38 == 1) {
            sp3C = 3;
play:
            func_15022190(sp5C[0], sp5C[1], sp5C[2], angle);
            sp64 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            D_800C3671 = 1;
            func_1501D348(0x25, sp3C, 0, 0, 0);
            D_800C3670 = 1;
            D_800BE9F0 = sp64;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507DFE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
extern s8 D_800BE3DF;
extern u8 D_800BE3E0;
extern s32 D_800BE9F4;
extern u8 D_800D18A8;

s32 func_1507E114(s32 arg0) {
    s32 sp5C;
    u8 sp54[8];
    u8 sp48[12];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    u8 sp3C[6];

    if (D_800D18A8 == 0) {
        return 0;
    }
    if ((D_800BE9F4 == 0x22) || (D_800BE9F4 == 0x18)) {
        return 0;
    }
    D_800BE9F4 = D_800BE3DF;
    func_15084D70(0, D_800BE3E0, 1, &sp54, &sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}
typedef struct GameA9D90Vec3 {
    f32 x;
    f32 y;
    f32 z;
} GameA9D90Vec3;

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 CURRENT (975) */
void func_1507E1D0(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    struct {
        GameA9D90Vec3 output;
        GameA9D90Vec3 input;
    } local;
    s32 temp_v0;
    s32 var_a2;

    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        local.input.x = 0.0f;
        local.input.z = 0.0f;
        local.input.y = *(f32 *)(arg0 + 0x150) * 30.0f;
        temp_v0 = *(s32 *)arg0;
        var_a2 = *(s32 *)(arg0 + 0x1D4);
        if (temp_v0 == 1) {
            var_a2 += 0x300;
        } else if (temp_v0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(&local.input.x, &local.output.x, var_a2);
        *arg1 = local.output.x;
        *arg2 = local.output.y;
        *arg3 = local.output.z;
        return;
    }
    *arg1 = *(f32 *)(arg0 + 0x14);
    *arg2 = *(f32 *)(arg0 + 0x18);
    *arg3 = *(f32 *)(arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
