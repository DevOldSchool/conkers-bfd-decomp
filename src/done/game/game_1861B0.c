#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1861B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 */

void func_1519F400(void *arg0);

void func_15158D00(void *arg0) {
    func_1514EDF0(arg0, *(void **)((u8 *)arg0 + 0x18));
    func_15169824(arg0);
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

void func_15158D2C(Game58D2CState *arg0) {
    s32 index;
    u8 result4;
    u8 old0;
    u8 old1;
    u8 old2;
    u8 old3;
    u8 old4;
    u32 after;
    s8 callback;
    Game58D2CRule *rule;

    old0 = arg0->state[0];
    old1 = arg0->state[1];
    old2 = arg0->state[2];
    old3 = arg0->state[3];
    old4 = arg0->state[4];
    if ((arg0->state[0] = func_15159084(arg0->actor, arg0->id)) == 0) {
        arg0->state[1] = func_15159120(arg0->actor, arg0->id);
    } else {
        arg0->state[1] = 2;
    }
    if (arg0->state[0] == 0) {
        if (arg0->state[1] == 0) {
            arg0->state[2] = 1;
        } else {
            arg0->state[2] = func_15159184(arg0->actor, arg0->id);
        }
    } else {
        arg0->state[2] = 0;
    }
    arg0->state[3] = func_15159230(arg0->actor, arg0->position, arg0->state[3]);
    arg0->position[0] = *(f32 *)(arg0->actor + 0x14);
    arg0->position[1] = *(f32 *)(arg0->actor + 0x18);
    arg0->position[2] = *(f32 *)(arg0->actor + 0x1C);
    arg0->state[4] = result4 = func_151592B8(arg0->actor, arg0->id);
    if (arg0->flags & 1) {
        after = (1 << (arg0->state[1] + 3)) | (1 << (arg0->state[2] + 6)) | (1 << (arg0->state[3] + 9)) | (1 << arg0->state[0]) | (1 << (result4 + 13));
        for (index = 0; index != 28; index++) {
            callback = D_8008B02C[arg0->id][index];
            rule = &D_800A6200[index];
            if (callback != -1) {
                u32 before = (1 << old0) | (1 << (old1 + 3)) | (1 << (old2 + 6)) | (1 << (old3 + 9)) |
                             (1 << (old4 + 13));
                if (rule->before == (rule->before | before) && rule->after == (rule->after | after)) {
                    D_8008AFD0[callback](arg0);
                }
            }
        }
    }
}
void func_15158FA4(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;

    temp_v0 = arg2;
    if (temp_v0 == 0) {
        if ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
            (arg0[0x1C] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x2D) {
        temp_v0 = *(s32 *)arg1;
        if (temp_v0 == *(s32 *)(arg0 + 0x18)) {
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg1 + 4);
            arg0[0x1C] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)(arg0 + 0x18)) {
            u8 *dst = arg0;

            *(s32 *)(dst + 0x18) = temp_v0;
            dst[0x1C] = arg1[8];
        }
    } else if (temp_v0 == 4) {
        if ((*(s32 *)(arg0 + 0x18) == *(s32 *)arg1) ||
            (arg0[0x1C] == arg1[4])) {
            func_1519F400(arg0);
        }
    }
}
extern f32 D_800A63A0;

s32 func_15159084(void *arg0, u8 arg1) {
    s32 flags;
    s32 result;

    flags = *(s32 *)((u8 *)arg0 + 0x184) & 0x1F;
    if ((arg1 == 2) || (arg1 == 3)) {
        result = 0;
    } else {
        if ((D_800A63A0 == *(f32 *)((u8 *)arg0 + 0x118)) && !(flags & 0xA)) {
            result = 1;
        } else if ((*(f32 *)((u8 *)arg0 + 0x118) < *(f32 *)((u8 *)arg0 + 0x18)) || (*(u8 *)((u8 *)arg0 + 0x137) != 0)) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}
