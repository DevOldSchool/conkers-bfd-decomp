#include "types.h"

/*
 * Reviewed source unit: src/game/game_F9430.c
 * Boundary evidence: docs/evidence/game_raw_radial_particle_composite.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CBF80
 * - func_150CC638
 * - func_150CC6B8
 * - func_150CC8D4
 * - func_150CCA7C
 * - func_150CCCB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CBF80.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CC638 CURRENT (420) */
s32 func_150CC638(u8 *arg0) {
    f32 temp_fv0;
    s32 temp_v1;
    u8 *subrecord;
    s32 temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
        subrecord = arg0 + 0x128;
        if (temp_v1 < 0x20) {
            temp_v0 = temp_v1 * 8;
            if (temp_v0 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v0;
            }
        }
        if (*(s16 *)subrecord < *(s16 *)((u8 *)arg0 + 0x1C)) {
            temp_fv0 = *(f32 *)(subrecord + 4) * D_800BE9A4;
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CC638 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CC638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CC6B8.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CC8D4 CURRENT (13905) */
s32 func_150CC8D4(void *arg0, s32 arg1) {
    f32 var_ft5;
    f32 var_ft5_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;

    var_v1 = D_800BE9E4;
    if (var_v1 != 0) {
        temp_a2 = -(var_v1 & 3);
        temp_a1 = var_v1 + temp_a2;
        if (temp_a2 != 0) {
            var_v1 -= 1;
            var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (temp_a1 != var_v1) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
                    var_v1 -= 1;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (temp_a1 != var_v1);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            if (var_v1 != 0) {
                goto block_5;
            }
        } else {
block_5:
            var_v1_2 = var_v1 - 4;
            var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (var_v1_2 != 0) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
                    var_v1_2 -= 4;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (var_v1_2 != 0);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CC8D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CC8D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CCA7C.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CCCB4 CURRENT (325) */
s32 func_150CCCB4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * D_800BE9A4) + (D_800BE9A4 * temp_fa0 * D_800BE9A4 * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CCCB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F9430/func_150CCCB4.s")
