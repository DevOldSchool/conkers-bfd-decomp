#include "types.h"

/*
 * Reviewed source unit: src/game/game_DBA60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AE5B0
 * - func_150AE790
 * - func_150AEB9C
 * - func_150AECCC
 * - func_150AED4C
 * - func_150AED9C
 * - func_150AEDF8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AE5B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AE790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEB9C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AECCC CURRENT (30) */
void func_150AECCC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x96) = (s16) (*(s16 *)((u8 *)arg0 + 0x96) + (*(s16 *)((u8 *)arg0 + 0x94) * D_800BE9E4));
    if (*(s16 *)((u8 *)arg0 + 0x96) >= 0x1401) {
        *(s16 *)((u8 *)arg0 + 0x96) = 0x1400;
    }
    *(s16 *)((u8 *)arg0 + 0x9E) = (s16) (*(s16 *)((u8 *)arg0 + 0x9E) - (*(s16 *)((u8 *)arg0 + 0x96) >> 8));
    *(s16 *)((u8 *)arg0 + 0xA4) = (s16) (*(s16 *)((u8 *)arg0 + 0xA4) + D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0xA4) >= 0x1A) {
        *(s16 *)((u8 *)arg0 + 0xA4) = 0x19;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AECCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AECCC.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AED4C CURRENT (245) */
void func_150AED4C(void *arg0) {
    s16 temp_v1;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x2A);
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + (*(s32 *)((u8 *)arg0 + 0x14) * D_800BE9E4));
    if (temp_v1 < *(s16 *)((u8 *)arg0 + 0x34)) {
        *(s16 *)((u8 *)arg0 + 0x34) = temp_v1;
        *(s8 *)((u8 *)arg0 + 0x3A) = 0x46;
    }
    *(s16 *)((u8 *)arg0 + 0x36) = *(s16 *)((u8 *)arg0 + 0x34);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AED4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AED4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AED9C.s")
typedef struct GameDBA60Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameDBA60Object;

s32 func_150AEDD8(GameDBA60Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEDF8.s")
