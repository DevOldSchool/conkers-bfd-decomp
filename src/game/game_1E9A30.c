#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E9A30.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BC580
 * - func_151BC5A4
 * - func_151BC64C
 * - func_151BC794
 * - func_151BCA90
 * - func_151BD21C
 * - func_151BD2F8
 * - func_151BD43C
 * - func_151BD750
 * - func_151BD828
 * - func_151BDD8C
 * - func_151BE0AC
 * - func_151BE138
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC580 CURRENT (80) */
s32 func_151BC580(void *arg0) {
    if (**(s32 **)((u8 *)arg0 + 0x40) == 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC580 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC580.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC5A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC64C.s")
f32 func_15143E64(f32 *, void *, void *);           /* extern */
extern f32 D_800AA848;
extern f32 D_800AA84C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC794 CURRENT (5435) */
s32 func_151BC794(u8 *arg0) {
    u8 *sp9C;
    s32 sp98;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp4C;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa1;
    f32 var_ft4;
    s8 temp_v1;
    u8 *temp_a2;
    u8 *temp_t3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_v0 = (void *)(*(void **)((u8 *)temp_a2 + 0));
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_a2 + 4) != *(u8 *)((u8 *)temp_v0 + 0x3B))) {
        *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        return 1;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    sp88 = *(f32 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)temp_a2 + 8);
    sp8C = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)temp_a2 + 0xC);
    sp98 = *(s32 *)((u8 *)arg0 + 0x94);
    sp9C = temp_a2;
    sp90 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_a2 + 0x10);
    temp_fv0 = func_15143E64(&sp88, arg0, temp_a2);
    *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) + (temp_fv0 * D_800AA848 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)sp9C + 0x14);
    *(f32 *)((u8 *)sp9C + 0x1C) = (f32) (*(f32 *)((u8 *)sp9C + 0x1C) + (temp_fv0 * D_800AA84C));
    sp4C = temp_fv1;
    if (temp_fv1 > 1.0f) {
        temp_t3 = (void *)(sp9C + 8);
        temp_fv0_2 = 1.0f / sp4C;
        *(f32 *)((u8 *)&sp6C + 0) = *(f32 *)((u8 *)sp9C + 8);
        *(s32 *)((u8 *)&sp6C + 4) = (s32) *(s32 *)((u8 *)temp_t3 + 4);
        var_ft4 = *(f32 *)((u8 *)sp9C + 0x18) + D_800BE9A4;
        *(s32 *)((u8 *)&sp6C + 8) = (s32) *(s32 *)((u8 *)temp_t3 + 8);
        temp_fv1_2 = *(f32 *)((u8 *)sp9C + 0x20);
        var_fa1 = temp_fv1_2;
        temp_fs0 = -(var_ft4 * temp_fv0_2);
        do {
            temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x14) + sp98);
            *(f32 *)((u8 *)temp_v0_2 + 0) = (f32) *(f32 *)((u8 *)&sp6C + 0);
            *(s32 *)((u8 *)temp_v0_2 + 4) = (s32) *(s32 *)((u8 *)&sp6C + 4);
            *(s16 *)((u8 *)temp_v0_2 + 0xC) = 0xC;
            *(s8 *)((u8 *)temp_v0_2 + 0xE) = 0x64;
            *(f32 *)((u8 *)temp_v0_2 + 0x10) = var_fa1;
            *(s32 *)((u8 *)temp_v0_2 + 8) = (s32) *(s32 *)((u8 *)&sp6C + 8);
            if (var_fa1 > 16384.0f) {
                do {
                    *(f32 *)((u8 *)temp_v0_2 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x10) - 32768.0f);
                } while (*(f32 *)((u8 *)temp_v0_2 + 0x10) > 16384.0f);
            }
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2E) = 0;
            }
            temp_v1 = *(s8 *)((u8 *)arg0 + 0x2D);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
            if (temp_v1 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v1 + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                }
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
            }
            var_fa1 += (*(f32 *)((u8 *)sp9C + 0x1C) - temp_fv1_2) * temp_fv0_2;
            sp6C += sp88 * temp_fv0_2;
            sp70 += sp8C * temp_fv0_2;
            var_ft4 += temp_fs0;
            sp74 += sp90 * temp_fv0_2;
            *(f32 *)((u8 *)sp9C + 0x14) = (f32) (*(f32 *)((u8 *)sp9C + 0x14) - 1.0f);
        } while (*(f32 *)((u8 *)sp9C + 0x14) > 1.0f);
        *(f32 *)((u8 *)sp9C + 8) = (f32) *(f32 *)((u8 *)&sp6C + 0);
        *(s32 *)((u8 *)temp_t3 + 4) = (s32) *(s32 *)((u8 *)&sp6C + 4);
        *(s32 *)((u8 *)temp_t3 + 8) = (s32) *(s32 *)((u8 *)&sp6C + 8);
        *(f32 *)((u8 *)sp9C + 0x20) = var_fa1;
        *(f32 *)((u8 *)sp9C + 0x18) = var_ft4;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC794 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BCA90.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD21C CURRENT (1285) */
void func_151BD21C(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (temp_t6 == 0) {
        if ((temp_a3 == *(s32 *)((u8 *)arg1 + 0)) || (*(u8 *)((u8 *)temp_v0 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(u8 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg1 + 4) == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD21C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD21C.s")
s32 func_151BD2BC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x28);
    if (*(s32 *)((u8 *)temp_v0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x2C) != *(u8 *)((u8 *)temp_v0 + 0x3B)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD2F8.s")
s32 func_151BD42C(u8 *arg0) {
    *(s16 *)(arg0 + 0x80) = 0;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD43C.s")
extern f32 D_800AA860;
extern f32 D_800AA864;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD750 CURRENT (945) */
f32 func_151BD750(void *arg0) {
    s16 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x80);
    *(s16 *)((u8 *)arg0 + 0x80) = (s16) (temp_v0 + D_800BE9E4);
    return ((f32) temp_v0 * 2.0f * D_800AA860) + D_800AA864;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD750 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD750.s")
/* Call context: func_1513170C: unique active project prototype */
s32 func_1513170C(u8 *, s32);

void func_151BD79C(u8 *arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0xB0);
    if ((*(s32 *)((u8 *)temp_v0 + 0) != 0) && (*(u8 *)((u8 *)temp_v0 + 4) != 0xFF)) {
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    }
    func_1513170C(arg0, arg1);
}
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151BD7F4(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3B, (s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BDD8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE0AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE138.s")
void func_151BE138(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

void func_151BE1B8(s32 arg0) {
    func_151BE138(arg0);
    func_1514933C(arg0);
}
void func_151BE1E4(s32 arg0) {
    func_151BE138(arg0);
    func_15149368(arg0);
}
