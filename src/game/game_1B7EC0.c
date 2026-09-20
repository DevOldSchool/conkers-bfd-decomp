#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B7EC0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518AADC
 * - func_1518AB60
 * - func_1518ABD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1B7EC0Node {
    u8 pad0[0x10];
    s32 field10;
    struct Game1B7EC0Node *field14;
    struct Game1B7EC0Node *field18;
    u8 field1C;
} Game1B7EC0Node;

void func_1516972C(void *);
extern void (*D_8008D5C0[])(s32);
extern s32 D_800BE9E4;

void func_1518AA10(u8 *arg0) {
    Game1B7EC0Node *next;
    Game1B7EC0Node *node;
    s16 timer;

    if (*(s32 *)(arg0 + 0x1C) == 0) {
        return;
    }
    timer = *(s16 *)(arg0 + 0x22);
    if (timer < 0) {
        node = *(Game1B7EC0Node **)(arg0 + 0x14);
        next = node->field18;
        if (next == 0) {
            *(s32 *)(arg0 + 0x10) = 0;
            *(void **)(arg0 + 0x14) = 0;
        } else {
            next->field14 = 0;
            *(Game1B7EC0Node **)(arg0 + 0x14) = node->field18;
        }
        if (node->field1C != 0) {
            D_8008D5C0[node->field1C](node->field10);
        }
        func_1516972C(node);
        *(s32 *)(arg0 + 0x1C) -= 1;
        return;
    }
    if (*(u8 *)(arg0 + 0x24) & 1) {
        *(s16 *)(arg0 + 0x22) = timer - D_800BE9E4;
    }
}
typedef struct Game1B7EC0Effect {
    u8 pad0[0x10];
    s32 field_10;
    s32 field_14;
    s32 field_18;
    u8 field_1C;
    u8 pad1D[3];
} Game1B7EC0Effect;

typedef struct Game1B7EC0RadialEffect {
    u8 pad0[0x10];
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s16 field_20;
    s16 field_22;
    u8 field_24;
    u8 pad25[3];
} Game1B7EC0RadialEffect;

void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518AADC CURRENT (120) */
void *func_1518AADC(s32 arg0, s16 arg1, u8 arg2) {
    s32 temp_t8;
    void *temp_v0;

    temp_v0 = func_15167A68(0x1D, 0, 0x28, 1, 0xFF, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x1C) = 0;
    temp_t8 = arg0;
    *(s16 *)((u8 *)temp_v0 + 0x22) = arg1;
    *(s16 *)((u8 *)temp_v0 + 0x20) = arg1;
    *(s32 *)((u8 *)temp_v0 + 0x10) = 0;
    *(s32 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s32 *)((u8 *)temp_v0 + 0x18) = temp_t8;
    *(u8 *)((u8 *)temp_v0 + 0x24) = arg2;
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518AADC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518AADC.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518AB60 CURRENT (265) */
void *func_1518AB60(s32 arg0, u8 arg1) {
    volatile Game1B7EC0Effect *effect;

    effect = func_15167A68(0x1E, 0, sizeof(Game1B7EC0Effect), 1, 0xFF, 1);
    if (effect == 0) {
        return 0;
    }
    effect->field_10 = arg0;
    effect->field_14 = 0;
    effect->field_18 = 0;
    effect->field_1C = arg1;
    return (void *)effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518AB60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518AB60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7EC0/func_1518ABD0.s")
