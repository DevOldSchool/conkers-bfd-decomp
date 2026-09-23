#include "types.h"

/*
 * Reviewed source unit: src/game/game_129EE0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCBC0
 * - func_150FCF1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15164F0C(u8, s32, void *, u8, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_150FCBC0(s32);
void func_151D8868(s8 *, s32, s32, s32);
extern u8 D_1000EC24[];
extern s32 D_80082FA0;

void func_150FCA30(void) {
    s8 spawn[11];
    s32 index;

    func_150FCBC0(0);
    func_150FCBC0(1);
    func_150FCBC0(2);
    func_1000FA64(0x2B8, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0x2D, 0, 0, 0);
    func_1000FA64(0x2B7, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0, 0, 0, 0);
    func_1000FA64(0x2B6, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0x5A, 0, 0, 0);
    index = 0;
    if (D_80082FA0 + 1 > 0) {
        do {
            func_15164F0C(4, (u8)index, 0, 0xFF, 1);
            index++;
        } while (D_80082FA0 >= index);
    }
    spawn[0] = 1;
    *(s16 *)&spawn[2] = 0x64;
    spawn[5] = 0xF;
    spawn[4] = 8;
    spawn[6] = -1;
    func_151D8868((s8 *)spawn, 0, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCBC0.s")
f32 func_15165BB0(void *, f32 *, s32, s32, f32);
extern void *D_800D9AA0;
extern f32 D_800A1F2C;

typedef struct Game129EE0Values {
    f32 value0;
    f32 value1;
    f32 value2;
} Game129EE0Values;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FCF1C CURRENT (17) */
f32 func_150FCF1C(void *arg0) {
    Game129EE0Values sp20;

    if (D_800D9AA0 == 0) {
        return 1.0f;
    }
    sp20.value0 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 0);
    sp20.value1 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 2);
    sp20.value2 = (f32)*(s16 *)((u8 *)D_800D9AA0 + 4);
    return func_15165BB0(arg0, &sp20.value0, 0x44FAE000, 0x460CB400, D_800A1F2C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FCF1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCF1C.s")
