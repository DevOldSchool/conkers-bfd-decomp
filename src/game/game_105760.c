#include "types.h"

/*
 * Reviewed source unit: src/game/game_105760.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D82BC
 * - func_150D83D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D82B0(s32 arg0) {

}
extern s32 D_80090298[];
extern f32 D_800A0B10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D82BC CURRENT (1250) */
s32 func_150D82BC(u8 *arg0, u8 *arg1) {
    f32 temp_fv0;
    s32 *temp_a0;
    s32 temp_ft1;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_a2;
    s8 **temp_t9;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg1 + 0x2D0);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s16 *)(arg0 + 0x18) = D_80090298[6];
    if (*(u16 *)(arg1 + 0x84) == 0xD) {
        temp_fv0 = *(f32 *)(temp_v0 + 8);
        if ((temp_fv0 >= 23.0f) && (temp_fv0 <= 40.0f)) {
            *(s16 *)(arg0 + 0x18) = D_80090298[7];
            temp_t9 = *(s8 ***)(arg0 + 0x24);
            temp_fv0 = *(f32 *)(temp_v0 + 8);
            temp_v1 = (s32)*temp_t9;
            temp_fv0 = (temp_fv0 - 23.0f) * D_800A0B10;
            var_a1 = 0;
            if (*(s8 *)temp_v1 != -0xE) {
                do {
                    var_a1++;
                } while (*(s8 *)((var_a1 * 8) + temp_v1) != -0xE);
            }
            temp_a0 = (s32 *)(temp_v1 + (var_a1 * 8));
            temp_v0_2 = *temp_a0;
            temp_ft1 = (s32)((70.0f * temp_fv0) + 2.0f);
            var_a2 = temp_ft1;
            if (temp_ft1 < 0) {
                var_a2 = temp_ft1 + ((temp_v0_2 >> 12) & 0xFFF);
            }
            *temp_a0 = ((var_a2 & 0xFFF) << 12) | 0xF2000000 | 2;
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D82BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D82BC.s")
typedef struct GameD83D8State {
    u8 pad0[0x18];
    s16 field18;
    u8 pad1A[0xA];
    s8 **display;
    u8 pad28[0x10];
    s32 phase;
    s32 progress;
} GameD83D8State;

typedef struct GameD83D8Owner {
    u8 pad0[0x84];
    u16 action;
    u8 pad86[0x24A];
    u8 *position;
} GameD83D8Owner;

extern f32 D_800A0B14;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D83D8 CURRENT (395) */
s32 func_150D83D8(GameD83D8State *arg0, GameD83D8Owner *arg1) {
    s32 progress;
    s32 index;
    s8 *display;
    f32 scaled;

    switch (arg0->phase) {
    case 0:
        arg0->progress = 0x32;
        arg0->field18 = D_80090298[0x6C / 4];
        if (arg1->action == 0x18D && *(f32 *)(arg1->position + 8) >= 46.0f) {
            arg0->phase = 1;
            arg0->field18 = D_80090298[0x70 / 4];
        }
        progress = arg0->progress;
        break;
    case 1:
        progress = arg0->progress + D_800BE9E4;
        arg0->progress = progress;
        if (progress >= 0x64) {
            arg0->progress = (progress = 0x64);
            arg0->phase = 2;
        }
        break;
    case 2:
        if (arg1->action == 0x18E && *(f32 *)(arg1->position + 8) >= 34.0f) {
            arg0->phase = 3;
        }
        progress = arg0->progress;
        break;
    case 3:
        progress = arg0->progress - D_800BE9E4 * 4;
        arg0->progress = progress;
        if (progress <= 0) {
            arg0->progress = 0;
            arg0->phase = 4;
            progress = 0;
        }
        break;
    default:
        progress = arg0->progress;
        break;
    }
    scaled = (f32)progress * D_800A0B14;
    display = *arg0->display;
    index = 0;
    if (*display != -0xE) {
        do {
            index++;
        } while (*(s8 *)((s32)display + (index << 3)) != -0xE);
    }
    *(s32 *)((s32)display + (index << 3)) =
        ((s32)(120.0f * scaled + 2.0f) & 0xFFF) |
        0xF2002000;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D83D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105760/func_150D83D8.s")
