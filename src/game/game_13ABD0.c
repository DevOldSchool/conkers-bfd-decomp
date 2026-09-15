#include "types.h"

/*
 * Reviewed source unit: src/game/game_13ABD0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510D720
 * - func_1510D7AC
 * - func_1510D874
 * - func_1510D8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1510D608(s32, s32);
extern s8 D_800BC448[];
extern s32 D_800D9F58;
extern s32 D_800D9F5C;
extern u8 D_800D9F68[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D720 CURRENT (30) */
void func_1510D720(s32 arg0) {
    void *temp_v0;
    u8 temp_t8;
    u8 temp_v1;

    temp_v0 = &D_800D9F68[arg0];
    if (D_800BC448[arg0] != 0) {
        temp_v1 = *(u8 *)temp_v0;
        temp_t8 = temp_v1 - 1;
        if (temp_v1 != 0) {
            *(u8 *)temp_v0 = temp_t8;
            if ((temp_t8 & 0xFF) == 0) {
                if (arg0 < D_800D9F58) {
                    D_800D9F58 = arg0;
                }
                if (D_800D9F5C < arg0) {
                    D_800D9F5C = arg0;
                }
                func_1510D608(arg0, 2);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D720.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D7AC.s")
extern s8 D_800D9ED0;
extern u8 D_800D9ED8[];

void func_1510D864(void) {
    D_800D9ED0 = 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D874 CURRENT (505) */
void func_1510D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *temp_v1;

    if ((u8)D_800D9ED0 < 8) {
        temp_v1 = &D_800D9ED8[(u8)D_800D9ED0 * 0x10];
        *(s32 *)(temp_v1 + 0) = arg0;
        *(s32 *)(temp_v1 + 4) = arg1;
        *(s32 *)(temp_v1 + 8) = arg2;
        *(s8 *)(temp_v1 + 0xC) = arg3;
        D_800D9ED0 = (u8)D_800D9ED0 + 1;
        *(s8 *)(temp_v1 + 0xD) = (s8)arg4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D874 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D874.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D8C0 CURRENT (1995) */
void *func_1510D8C0(void *arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_a2;

    var_a2 = arg0;
    {
        u8 * var_a0 = D_800D9ED8;
    var_v0 = 0;
    if ((s32) (u8) D_800D9ED0 > 0) {
        do {
            var_v0 += 1;
            if (arg1 == *(s32 *)((u8 *)var_a0 + 0)) {
                temp_v1 = var_a2;
                var_a2 += 8;
                *(s32 *)((u8 *)temp_v1 + 0) = (s32) (((*(u8 *)((u8 *)var_a0 + 0xC) * 4) & 0xFFFF) | 0xDB060000);
                *(s32 *)((u8 *)temp_v1 + 4) = (s32) *(s32 *)((u8 *)var_a0 + 4);
                if (*(s32 *)((u8 *)var_a0 + 8) != 0) {
                    temp_v1_2 = var_a2;
                    var_a2 += 8;
                    *(s32 *)((u8 *)temp_v1_2 + 0) = (s32) (((*(u8 *)((u8 *)var_a0 + 0xD) * 4) & 0xFFFF) | 0xDB060000);
                    *(s32 *)((u8 *)temp_v1_2 + 4) = (s32) *(s32 *)((u8 *)var_a0 + 8);
                }
            }
            var_a0 += 0x10;
        } while (var_v0 < (s32) (u8) D_800D9ED0);
    }
    return var_a2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D8C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D8C0.s")
