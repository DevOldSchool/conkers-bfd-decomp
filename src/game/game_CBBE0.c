#include "types.h"

/*
 * Reviewed source unit: src/game/game_CBBE0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509E730
 * - func_1509E8A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameCBBE0Args {
    s32 pad0;
    s32 pad4;
    s32 value0;
    s32 value1;
    s32 value2;
} GameCBBE0Args;

void func_1000D96C(s32, s32, s32);
void func_1000DF68(s32, s32, s32);
void func_1000DE1C(s32, s32);
s32 func_1000E46C(s32, s32, s32, s32);
s32 func_1000E654(s32, s32, s32, s32);
void func_1000E054(s32, s32);
extern s32 D_800D3840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509E730 */
s32 func_1509E730(s32 arg0, u32 kind, GameCBBE0Args *args) {
    s32 value;
    s32 mode;

    switch (kind) {
    case 0:
        func_1000D96C(arg0 & 0xFFF, args->value0, args->value1);
        return 1;
    case 2:
        func_1000DF68(arg0 & 0xFFF, args->value0, 0);
        return 1;
    case 5:
        func_1000DF68(arg0 & 0xFFF, args->value0, 1);
        return 1;
    case 1:
        func_1000DE1C(arg0 & 0xFFF, args->value0);
        return 1;
    case 3:
        if (D_800D3840 == 5) {
            return func_1000E46C(arg0 & 0xFFF, args->value0, args->value1, args->value2);
        }
        return func_1000E46C(arg0 & 0xFFF, args->value0, args->value1, 0x3C);
    case 4:
        value = arg0 & 0xFFF;
        if (D_800D3840 == 5) {
            return func_1000E654(arg0 & 0xFFF, args->value0, args->value1, args->value2 & 0xFFF);
        }
        return func_1000E654(value, args->value0, args->value1, value);
    case 6:
        mode = 1;
        if (D_800D3840 == 3) {
            mode = args->value0;
        }
        func_1000E054(arg0 & 0xFFF, mode);
        return 1;
    default:
        goto block_default;
    }
block_default:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509E730 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CBBE0/func_1509E730.s")
s32 func_1000E0F8();                                /* extern */
s32 func_1000E8F0();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509E8A0 CURRENT (113) */
s32 func_1509E8A0(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {                                 /* irregular */
    case 7:
        return func_1000E0F8();
    case 8:
        return func_1000E8F0();
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509E8A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CBBE0/func_1509E8A0.s")
