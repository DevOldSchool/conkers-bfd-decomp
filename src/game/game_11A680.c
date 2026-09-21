#include "types.h"

/*
 * Reviewed source unit: src/game/game_11A680.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150ED298
 * - func_150ED578
 * - func_150ED638
 * - func_150ED748
 * - func_150EEC84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_15144BC8: unique active project prototype */
f32 func_15144BC8(f32);

f32 func_150ED1D0(f32 arg0, f32 arg1) {
    f32 temp_fv0;
    f32 var_fv1;

    arg0 = func_15144BC8(arg0);
    temp_fv0 = func_15144BC8(func_15144BC8(arg1) - arg0);
    var_fv1 = temp_fv0;
    if (temp_fv0 > 180.0f) {
        var_fv1 = -360.0f + temp_fv0;
    }
    return var_fv1;
}
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    u8 pad_18[4];
    f32 field_1C;
    u8 pad_20[0x20];
    f32 field_40;
} Game11A680Position;

s32 func_1505A630(f32, f32, s32);

void func_150ED234(Game11A680Position *arg0, Game11A680Position *arg1) {
    func_150ED1D0((f32)(func_1505A630(arg1->field_14 - arg0->field_14,
                                     arg0->field_1C - arg1->field_1C, 0) + 0x4000) * 0.005493164f,
                  arg0->field_40);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED298.s")
extern u8 D_800BE616;
extern u32 *D_800BE728;
extern u8 *D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ED578 CURRENT (220) */
void func_150ED578(void *arg0) {
    u8 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)(temp_v0 + 0x84) == 0)) {
        if (D_800BE616 != 0) {
            var_v0 = *(u8 *)((u8 *)arg0 + 0x127);
        } else {
            var_v0 = *(u8 *)((u8 *)arg0 + 0x124);
        }
        if ((*(u16 *)D_800BE728[var_v0] & 0x10) != 0) {
            temp_v1 = D_800CC2D0 + (var_v0 * 0x32C);
            if (*(u8 *)(*(u8 **)(temp_v1 + 0x31C) + 0x197) != 0) {
                temp_v0_2 = *(u8 **)(temp_v1 + 0x318);
                if (temp_v0_2 != 0) {
                    *(u8 *)((u8 *)arg0 + 0x2FC) |= (u8)(1 << *(u8 *)(temp_v0_2 + 0x23D));
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ED578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED578.s")
void func_15062FC0(void *, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150ED638 CURRENT (570) */
void func_150ED638(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 < -0x2D) {
        arg1 = -0x2D;
    } else {
        var_v0 = arg1;
        if (arg1 >= 0x2E) {
            var_v0 = 0x2D;
        }
        arg1 = var_v0;
    }
    if (arg2 < -0x2D) {
        arg2 = -0x2D;
    } else {
        var_v0_2 = arg2;
        if (arg2 >= 0x2E) {
            var_v0_2 = 0x2D;
        }
        arg2 = var_v0_2;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0x28) {
        var_s0 = 0x7C;
    } else {
        temp_v0 = arg1;
        arg1 = arg2;
        var_s0 = 0x1C;
        arg2 = temp_v0;
    }
    func_15062FC0(arg0, 0, 0, 0x800, 0x800, var_s0, arg2 * -7, 0);
    func_15062FC0(arg0, 1, var_s0, 0x800, 0x800, var_s0,
                  arg1 * -7, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150ED638 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150ED748.s")
void func_151254F4(void *, s32);
void func_1517F488(s32, s32, s32, s32, s32, s32);
extern u8 D_800BE748[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EEC84 CURRENT (356) */
void func_150EEC84(u8 *arg0) {
    s32 var_a1;
    u8 *temp_s0;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v0 = *(s32 *)(arg0 + 0x318);
    arg0[5] = 3;
    *(s16 *)(arg0 + 0xE4) = 0;
    arg0[0x125] = 0xFF;
    arg0[0x328] = 0;
    if (temp_v0 != 0) {
        var_a1 = 0;
        temp_s0 = (u8 *)temp_v0;
        if (*(u8 *)(temp_v0 + 0x23D) == 3) {
            var_a1 = 1;
        }
        func_151254F4(temp_s0, var_a1);
        (*(u8 **)(arg0 + 0x31C))[0x78] = 0x29;
        *(u16 *)(D_800BE748 + (var_a1 * 6)) &= 0xFFEF;
        temp_v1 = (u8 *)&D_800CC2D0 + (var_a1 * 0x32C);
        temp_v1[0x2FC] |= (u8)(1 << temp_s0[0x23D]);
        if (temp_v1[0x10A] != 0) {
            func_1517F488(0xFF, 0, 0, 0xB4, 0x14, (s32)temp_s0[0x23D]);
            temp_v1[0x10A] = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EEC84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11A680/func_150EEC84.s")
void func_151045E0(s32, s32, s32);
void func_15052590(void *);

void func_150EEDA8(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 5) != 3) {
        func_151045E0((s32)arg0, 0xF, 0x437A0000);
        *(u8 *)((u8 *)arg0 + 5) = 3;
        *(s16 *)((u8 *)arg0 + 0xE4) = 0;
        *(u8 *)((u8 *)arg0 + 0x125) = 0xFF;
    }
    func_15052590(arg0);
}
