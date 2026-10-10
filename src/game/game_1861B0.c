#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1861B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15158D2C
 * - func_15158FA4
 * - func_15159084
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);
void func_15169824(s32 arg0);
void func_1519F400(void *arg0);

void func_15158D00(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169824((s32) arg0);
}
typedef struct Game58D2CState {
    u8 pad0[0x18];
    u8 *actor;
    u8 slot;
    u8 id;
    u8 pad1E[2];
    f32 position[3];
    u8 state[5];
    u8 flags;
} Game58D2CState;
typedef struct Game58D2CRule { u32 before; u32 after; } Game58D2CRule;
s32 func_15159084(void *, u8);
s32 func_15159120(void *, u8);
s32 func_15159184(void *, u8);
s32 func_15159230(void *, void *, u8);
s32 func_151592B8(void *, u8);
extern void (*D_8008AFD0[])(void *);
extern s8 *D_8008B02C[];
extern Game58D2CRule D_800A6200[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158D2C CURRENT (5871) */
void func_15158D2C(Game58D2CState *arg0) {
    u8 old0;
    volatile u8 old1;
    volatile u8 old2;
    volatile u8 old3;
    volatile u8 old4;
    u8 result;
    s32 result4;
    u8 *actor;
    u32 before;
    u32 after;
    s32 index;
    s8 callback;
    Game58D2CRule *rule;

    old0 = arg0->state[0];
    old1 = arg0->state[1];
    old2 = arg0->state[2];
    old3 = arg0->state[3];
    old4 = arg0->state[4];
    result = func_15159084(arg0->actor, arg0->id);
    arg0->state[0] = result;
    if (result == 0) arg0->state[1] = func_15159120(arg0->actor, arg0->id);
    else arg0->state[1] = 2;
    if (arg0->state[0] == 0) {
        if (arg0->state[1] == 0) arg0->state[2] = 1;
        else arg0->state[2] = func_15159184(arg0->actor, arg0->id);
    } else arg0->state[2] = 0;
    arg0->state[3] = func_15159230(arg0->actor, arg0->position, arg0->state[3]);
    actor = arg0->actor;
    arg0->position[0] = *(f32 *)(actor + 0x14);
    arg0->position[1] = *(f32 *)(actor + 0x18);
    arg0->position[2] = *(f32 *)(actor + 0x1C);
    result4 = func_151592B8(actor, arg0->id);
    arg0->state[4] = result4;
    if (arg0->flags & 1) {
        after = (1U << (arg0->state[0] & 31)) |
            (1U << ((arg0->state[1] + 3) & 31));
        after |= 1U << ((arg0->state[2] + 6) & 31);
        after |= 1U << ((arg0->state[3] + 9) & 31);
        after |= 1U << (((result4 & 0xFF) + 13) & 31);
        index = 0;
        do {
            before = 1U << (old0 & 31);
            result = old1;
            callback = D_8008B02C[arg0->id][index];
            rule = &D_800A6200[index];
            if (callback != -1) {
                before |= (1U << ((result + 3) & 31)) |
                    (1U << ((old2 + 6) & 31)) | (1U << ((old3 + 9) & 31)) |
                    (1U << ((old4 + 13) & 31));
                if ((rule->before | before) == rule->before &&
                    (rule->after | after) == rule->after) D_8008AFD0[callback](arg0);
            }
            index++;
        } while (index != 28);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158D2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15158D2C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158FA4 CURRENT (275) */
void func_15158FA4(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = arg2;
    if (temp_v0 == 0) {
        if ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
            (arg0[0x1C] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)(arg0 + 0x18);
        if (temp_v0 == temp_v1) {
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg1 + 4);
            arg0[0x1C] = arg1[9];
            return;
        }
        if (*(s32 *)(arg1 + 4) != temp_v1) {
            return;
        }
        *(s32 *)(arg0 + 0x18) = temp_v0;
        arg0[0x1C] = arg1[8];
    } else if ((temp_v0 == 4) &&
               ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
                (arg0[0x1C] == arg1[4]))) {
        func_1519F400(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158FA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15158FA4.s")
extern f32 D_800A63A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159084 CURRENT (900) */
s32 func_15159084(void *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 flags;
    s32 var_v1;

    flags = *(s32 *)((u8 *)arg0 + 0x184) & 0x1F;
    if ((arg1 == 2) || (arg1 == 3)) {
        var_v1 = 0;
    } else {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x118);
        if ((D_800A63A0 == temp_fv0) && !(flags & 0xA)) {
            var_v1 = 1;
        } else if ((temp_fv0 < *(f32 *)((u8 *)arg0 + 0x18)) || (var_v1 = 0, (*(u8 *)((u8 *)arg0 + 0x137) != 0))) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1861B0/func_15159084.s")
