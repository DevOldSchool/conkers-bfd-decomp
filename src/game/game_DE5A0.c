#include "types.h"

/*
 * Reviewed source unit: src/game/game_DE5A0.c
 * Boundary evidence: docs/evidence/game_raw_table_selected_collections.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B10F0
 * - func_150B12FC
 * - func_150B1484
 * - func_150B17DC
 * - func_150B19E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_1505A184: unique active project prototype */
/* Call context: func_1505A630: unique active project prototype */
/* Call context: func_1505E650: unique active project prototype */
void func_1505A184(u16, f32, s32, f32 *, f32 *, s32 *);
s32 func_1505A630(f32, f32, s32);
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
f32 func_1505A6F8(u8 *, u8 *);                      /* extern */
extern f32 D_8009F8A0;
extern f32 D_8009F8A4;
extern f32 D_8009F8A8;
extern f32 D_8009F8AC;
extern f32 D_8009F8B0;
extern f32 D_8009F8B4;
extern f32 D_8009F8B8;
extern u8 D_800CC2D0;
extern f32 D_800CC2E8;
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B10F0 CURRENT (1872) */
void func_150B10F0(u8 *arg0) {
    f32 sp50;
    f32 sp4C;
    s32 sp48;
    f32 sp40;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fv1;
    s32 temp_v1;

    *(f32 *)((u8 *)arg0 + 0x174) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x178) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
    *(s8 *)((u8 *)arg0 + 0x125) = 0x64;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) ((f32) (s16) (*(u16 *)((u8 *)arg0 + 0x7A) + 0x4000) * 0.005493164f);
    if (func_1505A6F8(&D_800CC2D0, arg0) < D_8009F8A0) {
        temp_fv0 = func_1505A6F8(arg0, &D_800CC2D0);
        temp_ft4 = temp_fv0;
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)&D_800CC2D0 + 0x18);
        if (temp_fv1 < 0.0f) {
            var_fv1 = 1000.0f;
        } else {
            var_fv1 = D_8009F8A4 - (temp_fv1 * D_8009F8A8);
        }
        if ((temp_fv0 < var_fv1) && (*(u8 *)((u8 *)&D_800CC2D0 + 0xAD) == 1)) {
            sp40 = temp_ft4;
            temp_fv0_2 = D_8009F8AC - temp_ft4;
            temp_v1 = func_1505A630(*(f32 *)((u8 *)arg0 + 0x174) - *(f32 *)((u8 *)&D_800CC2D0 + 0x14), *(f32 *)((u8 *)&D_800CC2D0 + 0x1C) - *(f32 *)((u8 *)arg0 + 0x178), 0) & 0xFFFF;
            if (D_8009F8B0 < temp_fv0_2) {
                D_800CC2E8 = *(f32 *)((u8 *)&D_800CC2D0 + 0x18) - ((temp_fv0_2 - 820.0f) * D_8009F8B4 * D_800D1550);
            }
            func_1505A184((temp_v1 - 0x3000) & 0xFFFF, (temp_fv0_2 * D_8009F8B8) + 5.0f, 0, &sp50, &sp4C, &sp48);
            *(f32 *)((u8 *)&D_800CC2D0 + 0x164) = sp50;
            *(f32 *)((u8 *)&D_800CC2D0 + 0x168) = sp4C;
        }
    }
    func_1505E650(arg0, 0, 0x3F800000, 0, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B10F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B10F0.s")
void func_1502178C(void *, s32, s32);
s32 func_150535F4(u8 *);
void func_15058EA4(void *, f32, f32, f32, f32, f32, f32);
void func_15056B08(u8 *);
void func_15059140(u8 *);
extern f32 D_8009F8BC;
extern f32 D_8009F8C0;
extern u8 **D_800D2104;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B12FC CURRENT (1805) */
void func_150B12FC(u8 *arg0) {
    s16 original[2];
    f32 height;
    f32 prior;
    f32 target;
    f32 current;

    original[0] = *(s16 *)(arg0 + 0x76);
    arg0[0x80] = 0xA;
    height = (f32)*(s16 *)(D_800D2104[arg0[0x13F]] + 2);
    func_15058EA4(arg0, height, 1.0f, height, D_8009F8BC, 12.0f, -16.0f);
    func_15056B08(arg0);
    prior = *(f32 *)(arg0 + 0xC4);
    target = ((f32)(s16)((original[0] - *(u16 *)(arg0 + 0x76)) * 6) * 0.00390625f) - prior;
    if (target > 6.0f) {
        target = 6.0f;
    } else if (target < -6.0f) {
        target = -6.0f;
    }
    current = *(f32 *)(arg0 + 0x148);
    *(volatile f32 *)(arg0 + 0x148) = current + ((target - current) * D_8009F8C0);
    *(volatile f32 *)(arg0 + 0xC4) = prior + *(volatile f32 *)(arg0 + 0x148);
    *(volatile f32 *)(arg0 + 0x40) = (f32)(s16)(*(u16 *)(arg0 + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    if (func_150535F4(arg0) == 0) {
        func_1502178C(arg0, 0, -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B12FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B12FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B1484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B17DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DE5A0/func_150B19E0.s")
