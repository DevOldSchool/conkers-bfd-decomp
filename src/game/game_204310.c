#include "types.h"

/*
 * Reviewed source unit: src/game/game_204310.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D6E60
 * - func_151D7000
 * - func_151D710C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D6E60.s")
void func_15042D78(u8);
void func_150432CC(s32, s32);
void func_1504332C(u8, u8, u8, u8);
s32 func_15042E3C(s32 *, s32);
extern s32 D_800AB254;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D7000 CURRENT (610) */
s32 func_151D7000(u8 *arg0) {
    volatile s32 spacer;
    u8 *entry;
    u8 *object;
    s16 value;
    s16 limit;

    entry = *(u8 **)(arg0 + 0x48);
    object = *(u8 **)entry;
    if ((*(s32 *)object == 0) || (entry[4] != object[0x3B])) {
        return 0;
    }
    limit = *(s16 *)(arg0 + 0xE);
    value = 0xFF;
    if (limit < *(s16 *)(entry + 0xC)) {
        value = *(s16 *)(entry + 0xE) * limit;
        if (value < 0) {
            value = 0;
        }
    }
    func_150432CC((s32)object, 0x109);
    func_1504332C(0x32, 0x7D, 0x1C, (u8)value);
    func_15042D78(0x81);
    return func_15042E3C(&D_800AB254, *(s32 *)(entry + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D7000 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D7000.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151D70CC(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x48);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
s32 func_15133EEC(s32, u16, u8, s32);
extern u8 D_80083740[];
extern u8 D_800838C0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D710C CURRENT (550) */
void func_151D710C(void *arg0, void *arg1, s32 arg2, s32 arg3, s8 *arg4) {
    void *temp_v0;

    temp_v0 = arg0;
    if (*(u8 *)((u8 *)arg1 + 0x43) < 0xFF) {
        *(s32 *)temp_v0 = 0xDB060020;
        *(u8 **)((u8 *)temp_v0 + 4) = D_80083740;
        arg0 = (u8 *)arg0 + 8;
    } else {
        *(s32 *)temp_v0 = 0xDB060020;
        *(u8 **)((u8 *)temp_v0 + 4) = D_800838C0;
        arg0 = (u8 *)arg0 + 8;
    }
    func_15133EEC(func_15133EEC((s32)arg0, 0xC3, 6, 3), 0xC3, 7, 3);
    *arg4 = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D710C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D710C.s")
