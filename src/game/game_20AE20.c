#include "types.h"

/*
 * Reviewed source unit: src/game/game_20AE20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DD970
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_8008FE54[23];
extern s8 D_8008FE6C[23];
extern s8 D_8008FE84[23];
extern s8 D_800E0BE0[23];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD970 CURRENT (1030) */
void func_151DD970(void) {
    u32 src;
    u32 end;
    u32 dst;
    s8 byte_1;
    s8 byte_2;
    s8 byte_3;
    s8 byte_0;

    src = (u32)&D_8008FE54[3];
    dst = (u32)&D_800E0BE0[3];
    byte_0 = D_8008FE54[0];
    byte_1 = D_8008FE54[1];
    byte_2 = D_8008FE54[2];
    D_800E0BE0[2] = byte_2;
    *(s8 *)((u32)&D_800E0BE0[2] - 1) = byte_1;
    *(s8 *)((u32)&D_800E0BE0[2] - 2) = byte_0;
    end = (u32)&D_8008FE54[23];
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

void func_151DD9E4(void) {
    s32 i;

    for (i = 0; i < 23; i++) {
        if (D_800E0BE0[i] < D_8008FE6C[i] || D_8008FE84[i] < D_800E0BE0[i]) {
            D_800E0BE0[i] = D_8008FE54[i];
        }
    }
}
s32 func_151DDB94(s32 arg0) {
    return ~arg0;
}
