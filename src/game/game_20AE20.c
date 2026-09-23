#include "types.h"

/*
 * Reviewed source unit: src/game/game_20AE20.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DD970
 * - func_151DD9E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_8008FE54;
extern s8 D_8008FE55;
extern s8 D_8008FE56;
extern s8 D_8008FE57;
extern s8 D_8008FE6B;
extern s8 D_800E0BE0;
extern s8 D_800E0BE1;
extern s8 D_800E0BE2;
extern s8 D_800E0BE3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD970 CURRENT (2400) */
void func_151DD970(void) {
    s8 *src;
    s8 *dst;
    s8 byte_1;
    s8 byte_2;
    s8 byte_3;
    s8 byte_0;

    src = &D_8008FE57;
    dst = &D_800E0BE3;
    D_800E0BE2 = D_8008FE56;
    D_800E0BE1 = D_8008FE55;
    D_800E0BE0 = D_8008FE54;
    do {
        byte_1 = src[1];
        byte_2 = src[2];
        byte_3 = src[3];
        byte_0 = src[0];
        src += 4;
        dst += 4;
        dst[-3] = byte_1;
        dst[-2] = byte_2;
        dst[-1] = byte_3;
        dst[-4] = byte_0;
    } while (src != &D_8008FE6B);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DD970.s")
extern s8 D_8008FE6C;
extern s8 D_8008FE6D;
extern s8 D_8008FE6E;
extern s8 D_8008FE6F;
extern s8 D_8008FE84;
extern s8 D_8008FE85;
extern s8 D_8008FE86;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD9E4 CURRENT (8290) */
void func_151DD9E4(void) {
    s8 *min;
    s8 *dst;
    s8 *max;
    s8 *defaults;
    s32 index;
    s8 current;

    current = D_800E0BE0;
    if (current < D_8008FE6C || D_8008FE84 < current) {
        D_800E0BE0 = D_8008FE54;
    }
    current = D_800E0BE1;
    if (current < D_8008FE6D || D_8008FE85 < current) {
        D_800E0BE1 = D_8008FE55;
    }
    current = D_800E0BE2;
    if (current < D_8008FE6E || D_8008FE86 < current) {
        D_800E0BE2 = D_8008FE56;
    }
    min = &D_8008FE6F;
    dst = &D_800E0BE3;
    max = &D_8008FE84;
    defaults = &D_8008FE54;
    index = 3;
    do {
        current = dst[0];
        if (current < min[0] || max[index] < current) {
            dst[0] = defaults[index];
        }
        current = dst[1];
        if (current < min[1] || max[index + 1] < current) {
            dst[1] = defaults[index + 1];
        }
        current = dst[2];
        if (current < min[2] || max[index + 2] < current) {
            dst[2] = defaults[index + 2];
        }
        current = dst[3];
        if (current < min[3] || max[index + 3] < current) {
            dst[3] = defaults[index + 3];
        }
        index += 4;
        min += 4;
        dst += 4;
    } while (index != 0x17);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD9E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DD9E4.s")
s32 func_151DDB94(s32 arg0) {
    return ~arg0;
}
