#include "types.h"

/*
 * Reviewed source unit: src/game/game_CB1C0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509DDC4
 * - func_1509DDFC
 * - func_1509DEC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509DD10(s32 arg0) {
    return 1;
}
s32 func_1509DD20(s32 arg0) {
    return 1;
}
s32 func_1509DD30(s32 arg0) {
    return 1;
}
s32 func_1509DD40(s32 arg0) {
    return 1;
}

typedef struct GameCB1C0Record {
    u8 pad0[7];
    u8 field_7;
    u8 pad8[3];
    u8 field_B;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} GameCB1C0Record;

void func_15177F90(u8, s32, u8, s32, s32, s32, s32, s32, s32, s32,
                   s32);

s32 func_1509DD50(s32 arg0, GameCB1C0Record *arg1) {
    func_15177F90(arg1->field_7, 0, arg1->field_B, arg1->field_C,
                  arg1->field_10, arg1->field_14, arg1->field_18, 0x7FFF,
                  0xFF, arg1->field_1C, 0);
    return 1;
}
void func_15178E14(s32 arg0, s32 arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509DDC4 CURRENT (270) */
s32 func_1509DDC4(s32 arg0, s32 arg1) {
    arg1 = arg0;
    func_15178E14(arg1 & 0xFF, arg1);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509DDC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB1C0/func_1509DDC4.s")
void func_15178BE4(u8, void *, s16);
void func_15178C34(u8, s32, s32, s32, s32);
s32 func_15084000(s32);
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509DDFC CURRENT (990) */
s32 func_1509DDFC(s32 arg0, s32 arg1, u8 *arg2) {
    switch (arg1) {
        case 0:
            func_15178BE4(arg0,
                          (u8 *) &D_800CC2D0 + (func_15084000(*(s32 *) (arg2 + 8) & ~0x2000) * 0x32C) + 0x14,
                          *(s16 *) (arg2 + 0xE));
            return 1;
        case 1:
            func_15178C34(arg0,
                          *(s32 *) (arg2 + 8),
                          *(s32 *) (arg2 + 0xC),
                          *(s32 *) (arg2 + 0x10),
                          *(s32 *) (arg2 + 0x14));
            return 1;
        default:
            return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509DDFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB1C0/func_1509DDFC.s")
s32 func_15178C9C(s32, s32);                        /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509DEC4 CURRENT (605) */
s32 func_1509DEC4(s32 arg0, s32 arg1, void *arg2) {
    if (arg1 == 0) {
        return func_15178C9C(arg0 & 0xFF, func_15084000(*(s32 *)((u8 *)arg2 + 8) & ~0x2000));
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509DEC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB1C0/func_1509DEC4.s")
