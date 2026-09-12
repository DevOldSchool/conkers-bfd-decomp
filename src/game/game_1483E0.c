#include "types.h"

/*
 * Reviewed source unit: src/game/game_1483E0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511AF30
 * - func_1511B07C
 * - func_1511B51C
 * - func_1511B7D4
 * - func_1511BA24
 * - func_1511BB04
 * - func_1511BDF4
 * - func_1511BEBC
 * - func_1511C548
 * - func_1511C638
 * - func_1511CB44
 * - func_1511D394
 * - func_1511D7BC
 * - func_1511D9E4
 * - func_1511DBC4
 * - func_1511DD98
 * - func_1511DF6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(f32, f32);                        /* extern */
extern f32 D_800A3188;
extern f32 D_800A318C;
extern f32 D_800A3190;
extern f32 D_800A3194;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511AF30 CURRENT (3240) */
void func_1511AF30(void *arg0) {
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s32 var_v0;
    u32 temp_hi;
    f32 temp_fv0;

    temp_fv0 = (f32) *(s32 *)((u8 *)arg0 + 0x3C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x7C);
    temp_fa0 = 75.0f * temp_fv0 * D_800A3188;
    if (temp_fa0 != temp_fa1) {
        temp_fv1 = temp_fa0 - temp_fa1;
        if (fabsf(temp_fv1) < 1.0f) {
            *(f32 *)((u8 *)arg0 + 0x7C) = temp_fa0;
        } else {
            var_v0 = 1;
            if (temp_fv1 < 0.0f) {
                var_v0 = -1;
            }
            *(f32 *)((u8 *)arg0 + 0x7C) = (f32) (temp_fa1 + (f32) var_v0);
        }
        *(f32 *)((u8 *)arg0 + 0x80) = 0.0f;
    } else {
        sp1C = temp_fv0;
        temp_hi = func_150ADA20(temp_fa0, temp_fa1) % 1000U;
        if ((s32) temp_hi < 0x1F4) {
            *(f32 *)((u8 *)arg0 + 0x84) = (f32) ((f32) temp_hi * 5.0f * temp_fv0 * D_800A318C * D_800A3190);
        }
        temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x80);
        *(f32 *)((u8 *)arg0 + 0x80) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)arg0 + 0x84) - temp_fv0_2) * D_800A3194));
    }
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0x7C) + *(f32 *)((u8 *)arg0 + 0x80));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511AF30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511AF30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B07C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B7D4.s")
/* Call context: func_15188010: unique active project prototype */
void func_15188010(s32, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511BA24 CURRENT (125) */
void func_1511BA24(void *arg0) {
    f32 sp1C;
    u32 temp_t7;

    sp1C = 0.0f;
    func_15188010(*(s32 *)((u8 *)arg0 + 0x3C), &sp1C);
    temp_t7 = (u32) (sp1C * 255.0f);
    *(s8 *)((u8 *)arg0 + 0x8A) = (s8) temp_t7;
    if (!(temp_t7 & 0xFF)) {
        *(s8 *)((u8 *)arg0 + 0x8A) = 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511BA24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BA24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BB04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BDF4.s")
f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A31E0;
extern void *D_800DBFF0;

void func_1511BE5C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 4) = (f32) (func_150484A0((f32) *(s16 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8), (f32) *(s16 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) * D_800A31E0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BEBC.s")
void func_1511C540(void) {

}
f32 func_15047D60(f32);                             /* extern */
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A31EC;
extern f32 D_800A31F0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511C548 CURRENT (60) */
void func_1511C548(void *arg0) {
    f32 temp_ft2;
    f32 sp20;

    sp20 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x80));
    temp_ft2 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x84)) * 16.0f;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (sp20 * 16.0f);
    *(f32 *)((u8 *)arg0 + 8) = temp_ft2;
    *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) + (D_800A31EC * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x84) = (f32) (*(f32 *)((u8 *)arg0 + 0x84) + (D_800A31F0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x80) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x80));
    *(f32 *)((u8 *)arg0 + 0x84) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x84));
    if ((*(f32 *)((u8 *)arg0 + 8) == 0.0f) && (*(f32 *)((u8 *)arg0 + 0x84) == 0.0f)) {
        *(f32 *)((u8 *)arg0 + 0) = 7.5f;
        *(f32 *)((u8 *)arg0 + 8) = 8.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511C548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511C548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511C638.s")
extern f32 D_800A31F4;

void func_1511CB2C(s32 arg0, f32 *arg1) {
    *arg1 = D_800A31F4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511CB44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D394.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D7BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D9E4.s")
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_800A3210;
extern f32 D_800A3214;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511DBC4 CURRENT (308) */
void func_1511DBC4(void *arg0) {
    s32 sp24;
    void *sp20;
    f32 temp_fa0;
    f32 temp_fv1;
    s32 temp_t6;
    u8 temp_t1;
    s32 var_v0;
    void *var_v1;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x7C);
    if (temp_v0 == 0) {
        temp_v0_2 = func_10003C40(0x10, 1, 0, 0);
        *(void **)((u8 *)arg0 + 0x7C) = temp_v0_2;
        *(f32 *)((u8 *)temp_v0_2 + 0) = 0.0f;
        *(f32 *)((u8 *)temp_v0_2 + 4) = 0.0f;
        *(f32 *)((u8 *)temp_v0_2 + 8) = 0.0f;
        var_v1 = temp_v0_2;
        *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) D_800A3210;
    } else {
        var_v1 = temp_v0;
    }
    temp_t6 = *(u8 *)((u8 *)arg0 + 0x73) & 3;
    var_v0 = temp_t6;
    if (temp_t6 == 0) {
        *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    } else if (var_v0 == 3) {
        *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        sp20 = var_v1;
        sp24 = var_v0;
        *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (func_15047C00(*(f32 *)((u8 *)var_v1 + 0) * D_800A3214) * 0.5f));
        *(f32 *)((u8 *)var_v1 + 0) = (f32) (*(f32 *)((u8 *)var_v1 + 0) + (3.0f * (f32) D_800BE9E4));
    } else if (var_v0 == 2) {
        if (*(f32 *)((u8 *)arg0 + 8) == 0.0f) {
            *(f32 *)((u8 *)var_v1 + 4) = 0.0f;
            *(f32 *)((u8 *)var_v1 + 8) = 0.0f;
        }
        *(f32 *)((u8 *)var_v1 + 8) = (f32) (*(f32 *)((u8 *)var_v1 + 8) + *(f32 *)((u8 *)var_v1 + 0xC));
        *(f32 *)((u8 *)var_v1 + 4) = (f32) (*(f32 *)((u8 *)var_v1 + 4) + *(f32 *)((u8 *)var_v1 + 8));
        *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)var_v1 + 4));
        if (*(f32 *)((u8 *)arg0 + 8) >= 90.0f) {
            var_v0 = 3;
            *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        }
    } else {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
        temp_fa0 = (f32) D_800BE9E4;
        if (temp_fa0 < temp_fv1) {
            *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv1 - temp_fa0);
        } else {
            *(f32 *)((u8 *)arg0 + 8) = 0.0f;
            var_v0 = 0;
        }
    }
    temp_t1 = *(u8 *)((u8 *)arg0 + 0x73) & 0xFFFC;
    *(u8 *)((u8 *)arg0 + 0x73) = temp_t1;
    *(u8 *)((u8 *)arg0 + 0x73) = (u8) (temp_t1 | var_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511DBC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511DBC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511DD98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511DF6C.s")
