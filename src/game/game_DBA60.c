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
void func_1516972C(void *arg0);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AECCC CURRENT (100) */
void func_150AECCC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x96) = (s16) ((*(s16 *)((u8 *)arg0 + 0x94) * D_800BE9E4) + *(s16 *)((u8 *)arg0 + 0x96));
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AED9C CURRENT (480) */
s32 func_150AED9C(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AED9C */
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
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AEDF8 CURRENT (1597) */
void func_150AEDF8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v0 = (void *)(arg0 + 0x28);
        temp_a0 = *(s32 *)((u8 *)arg0 + 0x28);
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)((u8 *)arg0 + 0x28) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((temp_t6 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x28)) || (*(u8 *)((u8 *)(arg0 + 0x28) + 4) == (u8) *(s32 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AEDF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEDF8.s")
