#include "types.h"

/*
 * Reviewed source unit: src/game/game_20AE20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD970 CURRENT (650) */
void func_151DD970(void) {
    u32 src;
    u32 end;
    u32 dst;
    s8 byte_1;
    s8 byte_2;
    s8 byte_3;
    s8 byte_0;

    src = (u32)&D_8008FE57;
    dst = (u32)&D_800E0BE3;
    byte_0 = D_8008FE54;
    byte_1 = D_8008FE55;
    byte_2 = D_8008FE56;
    D_800E0BE2 = byte_2;
    *(s8 *)((u32)&D_800E0BE2 - 1) = byte_1;
    *(s8 *)((u32)&D_800E0BE2 - 2) = byte_0;
    end = (u32)&D_8008FE6B;
copy_bytes:
    {
        byte_1 = *(s8 *)(src + 1);
        byte_2 = *(s8 *)(src + 2);
        byte_3 = *(s8 *)(src + 3);
        byte_0 = *(s8 *)(src + 0);
        src += 4;
        dst += 4;
        *(s8 *)(dst - 3) = byte_1;
        *(s8 *)(dst - 2) = byte_2;
        *(s8 *)(dst - 1) = byte_3;
        *(s8 *)(dst - 4) = byte_0;
    }
    if (src != end) {
        goto copy_bytes;
    }
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD9E4 CURRENT (1645) */
void func_151DD9E4(void) {
    u32 min;
    u32 dst;
    u32 max;
    u32 defaults;
    s32 index;
    s8 current;

    index = D_800E0BE0;
    if (index < D_8008FE6C || D_8008FE84 < index) {
        index = D_8008FE54;
        D_800E0BE0 = index;
    }
    index = D_800E0BE1;
    if (index < D_8008FE6D || D_8008FE85 < index) {
        index = D_8008FE55;
        D_800E0BE1 = index;
    }
    index = D_800E0BE2;
    if (index < D_8008FE6E || D_8008FE86 < index) {
        index = D_8008FE56;
        D_800E0BE2 = index;
    }
    min = (u32)&D_8008FE6F;
    dst = (u32)&D_800E0BE3;
    max = (u32)&D_8008FE84;
    defaults = (u32)&D_8008FE54;
    index = 3;
clamp_bytes:
    {
        current = *(s8 *)(dst + 0);
        if (current < *(s8 *)(min + 0) || *(s8 *)(max + index) < current) {
            *(s8 *)(dst + 0) = *(s8 *)(defaults + index);
        }
        current = *(s8 *)(dst + 1);
        if (current < *(s8 *)(min + 1) || *(s8 *)(max + index + 1) < current) {
            *(s8 *)(dst + 1) = *(s8 *)(defaults + index + 1);
        }
        current = *(s8 *)(dst + 2);
        if (current < *(s8 *)(min + 2) || *(s8 *)(max + index + 2) < current) {
            *(s8 *)(dst + 2) = *(s8 *)(defaults + index + 2);
        }
        current = *(s8 *)(dst + 3);
        if (current < *(s8 *)(min + 3) || *(s8 *)(max + index + 3) < current) {
            *(s8 *)(dst + 3) = *(s8 *)(defaults + index + 3);
        }
        index += 4;
        min += 4;
        dst += 4;
    }
    if (index != 0x17) {
        goto clamp_bytes;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD9E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DD9E4.s")
s32 func_151DDB94(s32 arg0) {
    return ~arg0;
}
