#include "types.h"

/*
 * Reviewed source unit: src/game/game_13AE20.c
 * Boundary evidence: docs/evidence/game_raw_type4b_framebuffer_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510D970
 * - func_1510DA84
 * - func_1510E120
 * - func_1510E388
 * - func_1510E634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D970 CURRENT (890) */
void *func_1510D970(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 size;
    s32 enabled;
    s32 i;
    s32 j;
    u8 *result;
    u8 *entry;

    size = 0x128;
    enabled = arg3 & 1;
    if (enabled != 0) {
        size = 0x13A;
    }
    result = func_15167A68(0x4B, 0, size, 1, 0xFF, 1);
    if (result != 0) {
        i = 0;
        entry = result;
        do {
            i++;
            entry += 0x40;
            *(s16 *)(entry + 0x56) = 0;
            *(s16 *)(entry + 0x58) = 0x800;
            *(s16 *)(entry + 0x5A) = 0;
            *(s16 *)(entry + 0x66) = 0;
            *(s16 *)(entry + 0x68) = 0;
            *(s16 *)(entry + 0x6A) = 0;
            *(s16 *)(entry + 0x76) = 0;
            *(s16 *)(entry + 0x78) = 0;
            *(s16 *)(entry + 0x7A) = 0x800;
            *(s16 *)(entry + 0x86) = 0;
            *(s16 *)(entry + 0x88) = 0x800;
            *(s16 *)(entry + 0x8A) = 0x800;
        } while (i < 2);

        result[0x120] = arg0;
        *(s32 *)(result + 0x110) = arg1;
        result[0x121] = arg2;
        result[0x124] = arg4;
        if (enabled != 0) {
            *(s16 *)(result + 0x128) = 0x7FFF;
            j = 1;
            entry = result + 2;
            do {
                j += 4;
                *(s16 *)(entry + 0x12A) = 0x7FFF;
                *(s16 *)(entry + 0x12C) = 0x7FFF;
                *(s16 *)(entry + 0x12E) = 0x7FFF;
                entry += 8;
                *(s16 *)(entry + 0x120) = 0x7FFF;
            } while (j != 9);
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510D970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510DA84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E388.s")
extern s32 D_80089470;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510E634 CURRENT (485) */
void *func_1510E634(void *arg0, volatile s32 arg1, volatile s32 arg2) {
    void *temp_v1;

    temp_v1 = arg0;
    *(s32 *)temp_v1 = 0xDA380003;
    *(void **)((u8 *)temp_v1 + 4) = &D_80089470;
    arg0 = (u8 *)arg0 + 8;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510E634 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E634.s")
