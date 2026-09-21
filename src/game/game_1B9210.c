#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B9210.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518BD60
 * - func_1518C0B8
 * - func_1518C540
 * - func_1518C57C
 * - func_1518C69C
 * - func_1518C850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518BD60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C0B8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C540 CURRENT (615) */
s32 func_1518C540(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    if (temp_t6 < 0x100) {
        var_v1 = temp_t6;
    } else {
        var_v1 = -1;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C540 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C540.s")
typedef struct Game1B9210EffectPacket {
    u8 pad0[0x80];
    s32 field80;
    u8 pad84[6];
    s16 field8A;
    s16 field8C;
    s16 field8E;
    s16 field90;
    s16 field92;
    s16 field94;
    s16 field96;
    s16 field98;
    u8 pad9A[6];
    s8 fieldA0;
    s8 fieldA1;
    s8 fieldA2;
    u8 padA3;
} Game1B9210EffectPacket;

u32 func_150ADA20(void);
void func_1516865C(void *, s32, s32, s32, s32);
void *func_15168800(void *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C57C CURRENT (2414) */
s32 func_1518C57C(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 packet[0xA4];
    void *sp34;
    s32 sp2C;
    s16 temp_t2;
    s32 temp_ft3;
    s32 temp_v0;

    arg1 = 0x14;
    sp34 = *(void **)((u8 *)arg0 + 0x98);
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x94);
    *(s32 *)(packet + 0x80) = 0;
    *(s16 *)(packet + 0x8A) = 0x100;
    temp_ft3 = (s32)arg4;
    *(s16 *)(packet + 0x8E) = temp_ft3;
    *(s16 *)(packet + 0x8C) =
        (s32)*(f32 *)(temp_v0 + (*(s8 *)((u8 *)arg0 + 0x2D) * arg1));
    sp2C = temp_ft3;
    *(s16 *)(packet + 0x90) =
        (s32)*(f32 *)(temp_v0 +
                      (*(s8 *)((u8 *)arg0 + 0x2D) * arg1) + 8);
    temp_t2 = (func_150ADA20() % 21U) + 0x23;
    *(s16 *)(packet + 0x92) = temp_t2;
    *(s8 *)(packet + 0xA2) = -1;
    *(s8 *)(packet + 0xA0) = 0x12;
    *(s16 *)(packet + 0x98) = 0xC;
    *(s8 *)(packet + 0xA1) = 0;
    *(s16 *)(packet + 0x94) = temp_t2;
    *(s16 *)(packet + 0x96) = sp2C;
    func_1516865C(packet, 0xFF, 0xFF, 0xFF, 0xFF);
    func_15168800(packet, *(u8 *)((u8 *)arg0 + 0xC),
                   *(u8 *)((u8 *)arg0 + 1));
    *(s8 *)((u8 *)sp34 + 0x20) = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C57C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C57C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C69C.s")
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518C850 CURRENT (515) */
void func_1518C850(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x24);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x24) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x28) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x24) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0x28) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((arg2 == 0) &&
               ((*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0x24)) ||
                (*(u8 *)((u8 *)arg0 + 0x28) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518C850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B9210/func_1518C850.s")
