#include "types.h"

/*
 * Reviewed source unit: src/game/game_DAC30.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AD780
 * - func_150AD78C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD780 CURRENT (7200) */
void func_150AD780(f32 arg0) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAC30/func_150AD780.s")
extern f32 D_8009F714;
extern f32 D_8009F718;
extern f32 D_8009F71C;
extern f32 D_8009F720;
extern f32 D_8009F724;
extern f32 D_8009F728;
extern f32 D_8009F72C;
extern f32 D_8009F730;
extern f32 D_8009F734;
extern f32 D_8009F738;
extern f32 D_8009F73C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD78C CURRENT (5185) */
f32 func_150AD78C(f32 x) {
    f32 dx;
    f32 xsq;
    f32 poly;
    f32 dn;
    s32 n;
    f32 result;
    s32 ix;
    s32 xpt;

    ix = *(s32 *)&x;
    xpt = (ix >> 22);
    xpt &= 0x1FF;

    if (xpt < 0xFF) {
        dx = x;
        if (xpt >= 0xE6) {
            xsq = dx * dx;
            poly = ((D_8009F714 * xsq + D_8009F718) * xsq + D_8009F71C) * xsq + D_8009F720;
            result = dx + (dx * xsq) * poly;
            return result;
        }
        return x;
    }

    if (xpt < 0x136) {
        dx = x;
        dn = dx * D_8009F724;
        n = (s32)dn;
        dn = n;
        dx = dx - dn * D_8009F728;
        dx = dx - dn * D_8009F72C;
        xsq = dx * dx;
        poly = ((D_8009F730 * xsq + D_8009F734) * xsq + D_8009F738) * xsq + D_8009F73C;
        result = dx + (dx * xsq) * poly;
        if ((n & 1) == 0) {
            return result;
        }
        return -result;
    }

    return 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD78C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAC30/func_150AD78C.s")
