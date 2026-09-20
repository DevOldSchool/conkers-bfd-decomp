#include "types.h"

/*
 * Reviewed source unit: src/game/game_196DB0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15169988
 * - func_15169A48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game196DB0Effect {
    u8 pad0[0x10];
    u8 payload[0x3C];
} Game196DB0Effect;

Game196DB0Effect *func_15167A68(s32, s32, s32, s32, s32, s32);
void func_10023A10(void *, void *, s32);

Game196DB0Effect *func_15169900(void *arg0, s32 arg1) {
    Game196DB0Effect *effect;

    effect = func_15167A68(0x5E, 0, 0x4C, 0, arg1, 1);
    if (effect != 0) {
        func_10023A10(arg0, effect->payload, sizeof(effect->payload));
    }
    return effect;
}

void func_15169968(void *arg0) {
    func_15169900(arg0, 0xFF);
}
void func_1516972C(u8 *);
extern void (*D_8008CA20[])(void);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169988 CURRENT (45) */
void func_15169988(void *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 temp_t1;
    s8 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x40);
    if (temp_v0 != 0) {
        D_8008CA20[(s32)temp_v0]();
    }
    var_v0 = *(s16 *)((u8 *)arg0 + 0x26) + (*(s16 *)((u8 *)arg0 + 0x28) * D_800BE9E4);
    temp_t1 = *(u8 *)((u8 *)arg0 + 0x41) << 8;
    if (var_v0 >= temp_t1) {
        var_v0 -= temp_t1;
    } else if (var_v0 < 0) {
        var_v0 += temp_t1;
    }
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x24);
    *(s16 *)((u8 *)arg0 + 0x26) = var_v0;
    if (temp_v1 != 0) {
        temp_v1 -= D_800BE9E4;
        if (temp_v1 <= 0) {
            func_1516972C(arg0);
            return;
        }
        *(s16 *)((u8 *)arg0 + 0x24) = temp_v1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169988 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_196DB0/func_15169988.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_196DB0/func_15169A48.s")
