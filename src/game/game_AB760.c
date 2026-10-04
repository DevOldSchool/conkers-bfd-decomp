#include "types.h"

/*
 * Reviewed source unit: src/game/game_AB760.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507E2B0
 * - func_1507E3C0
 * - func_1507E73C
 * - func_1507E7E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define actor_set_expression func_1507E500
#define actor_apply_current_expression func_1507E5C8
#define actor_can_update_blink func_1507E6B8
#define actor_get_expression_record func_1507E908
#define actor_get_expression_count func_1507E968
#define actor_get_expression_action_table func_1507E9F8
#define actor_dispatch_expression_action func_1507EA44
#define actor_restore_default_expression func_1507EABC
#define actor_set_default_expression_zero func_1507EB2C

struct GameAB760State;
u32 func_150ADA20(void);
extern u8 D_800C35EA;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E2B0 CURRENT (230) */
void func_1507E2B0(struct GameAB760State *arg0) {
    u8 *state = (u8 *)arg0;
    u8 temp_t6;
    u8 temp_v0;
    s32 one;
    s32 timestep;

    if ((state[4] != 0x2B) && (D_800C35EA != 1)) {
        if ((state[0x127] != 0xFF) &&
            (*(u8 *)((u8 *)*(void **)(state + 0x31C) + 0x120) != 0)) {
            one = 1;
            state[0x6A] = one;
            state[0x6B] = one;
            return;
        }
        if ((s32)state[0x6A] >= 3) {
            state[0x6A] = 0;
        }
        if ((s32)state[0x6B] >= 3) {
            state[0x6B] = 0;
        }
        temp_v0 = state[0x6E];
        timestep = D_800BE9E4;
        one = 1;
        if ((s32)temp_v0 >= timestep) {
            state[0x6E] = temp_v0 - timestep;
            return;
        }
        state[0x6E] = 0;
        if (state[0x6C] != 1) {
            temp_t6 = state[0x6A] ^ 1;
            state[0x6A] = temp_t6;
            state[0x6B] ^= 1;
            if (!(temp_t6 & 0xFF)) {
                state[0x6E] = (func_150ADA20() % 140U) + 0xA;
                return;
            }
            state[0x6E] = one;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E2B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E2B0.s")
/* Descriptive role: actor_update_lady_cog_eye_parts.
 * Models 15/70/76 select paired eye parts from actor +0x6C/+0x6D; set bits
 * in actor +0x94 hide parts. Channel order does not establish left/right.
 * Evidence: docs/evidence/lady_cog_eye_part_semantics.md.
 * Naming only: the excluded candidate remains unmatched.
 */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E3C0 CURRENT (757) */
void func_1507E3C0(void *actor) {
    s32 eyePartStates[2];
    s32 *eyePartStateCursor;
    s32 partHideMask;
    u8 modelIndex;
    u8 *eyeCodeCursor;
    u8 *actorBytes;

    actorBytes = actor;
    modelIndex = actorBytes[4];
    eyePartStateCursor = eyePartStates;
    eyeCodeCursor = actorBytes;
    if ((modelIndex == 0xF) || (modelIndex == 0x46) || (modelIndex == 0x4C)) {
        do {
            *eyePartStateCursor = eyeCodeCursor[0x6C];
            if (*eyePartStateCursor >= 0xA) {
                *eyePartStateCursor -= 0xA;
                if (*eyePartStateCursor == 5) {
                    *eyePartStateCursor = 0;
                } else if (*eyePartStateCursor == 1) {
                    *eyePartStateCursor = 1;
                } else {
                    *eyePartStateCursor = 2;
                }
            } else if (*eyePartStateCursor < 2) {
                *eyePartStateCursor += 1;
            }
            eyePartStateCursor++;
            eyeCodeCursor++;
        } while (eyePartStateCursor != &eyePartStates[2]);
        partHideMask = *(s32 *)(actorBytes + 0x94) | 0x7E;
        *(s32 *)(actorBytes + 0x94) = partHideMask;
        if (eyePartStates[0] == 0) {
            *(s32 *)(actorBytes + 0x94) = partHideMask & ~8;
        } else if (eyePartStates[0] == 1) {
            *(s32 *)(actorBytes + 0x94) &= ~0x10;
        } else {
            *(s32 *)(actorBytes + 0x94) &= ~4;
        }
        if (eyePartStates[1] == 0) {
            *(s32 *)(actorBytes + 0x94) &= ~0x20;
        } else if (eyePartStates[1] == 1) {
            *(s32 *)(actorBytes + 0x94) &= ~0x40;
        } else {
            *(s32 *)(actorBytes + 0x94) &= ~2;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E3C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E3C0.s")
void func_150302F0(void *, s32);
void actor_apply_current_expression(u8 *, s32);
u8 *actor_get_expression_record(void *, s32);
void actor_dispatch_expression_action(void *, s32, s32);
s32 actor_get_expression_count(void *);
u8 *actor_get_expression_action_table(void *, s32 *);
extern void *D_800D1C90[];

/* Descriptive role: actor_set_expression.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
void actor_set_expression(u8 *actor, s32 expressionIndex, s32 morphDurationOverride) {
    u8 *previousExpression;
    u8 *actionIds;

    if (expressionIndex < actor_get_expression_count(actor)) {
        previousExpression = actor_get_expression_record(actor, actor[0x6F]);
        if (previousExpression[4] != 0) {
            actionIds = actor_get_expression_action_table(actor, 0);
            if (actionIds != 0) {
                func_150302F0(actor, actionIds[previousExpression[4] - 1]);
            }
        }
        actor[0x6F] = expressionIndex;
        actor_apply_current_expression(actor, morphDurationOverride);
        if (morphDurationOverride != 0) {
            actor[0x135] = morphDurationOverride;
            return;
        }
        actor[0x135] = actor_get_expression_record(actor, expressionIndex)[3];
    }
}
/* Semantic role: actor_apply_current_expression, including its action and selectors.
 * See docs/evidence/character_expression_semantics.md; keep the linked symbol stable.
 */
void actor_apply_current_expression(u8 *actor, s32 morphDurationOverride) {
    u8 *expressionRecord;
    u8 value;

    expressionRecord = actor_get_expression_record(actor, actor[0x6F]);
    if (expressionRecord != 0) {
        actor_dispatch_expression_action(actor, expressionRecord[4], *(u16 *)(expressionRecord + 6));
        value = expressionRecord[2];
        if (value != actor[0x134]) {
            actor[0x134] = value;
            if (morphDurationOverride == 0) {
                actor[0x135] = expressionRecord[3];
            } else {
                actor[0x135] = morphDurationOverride;
            }
        }
        actor[0x6C] = expressionRecord[0] + 0xA;
        actor[0x6D] = expressionRecord[1] + 0xA;
        value = expressionRecord[8];
        if (value != 0) {
            actor[0x68] = value;
        } else {
            actor[0x68] = *((u8 *)D_800D1C90[actor[4]] + 0x3B);
        }
        value = expressionRecord[9];
        if (value != 0) {
            actor[0x69] = value;
            return;
        }
        actor[0x69] = *((u8 *)D_800D1C90[actor[4]] + 0x3C);
    }
}
s32 func_150849A0();                                /* extern */

/* Descriptive role: actor_can_update_blink.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
s32 actor_can_update_blink(void *actor) {
    s32 representationModelIndex;
    u8 expressionIndex;

    if (*(u8 *)((u8 *)actor + 0x1CA) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)actor + 0x70) == *(u8 *)((u8 *)actor + 0x6F)) {
        return 1;
    }
    representationModelIndex = func_150849A0();
    expressionIndex = *(u8 *)((u8 *)actor + 0x6F);
    if (representationModelIndex == 0) {
        if (expressionIndex == 0x15) {
            return 1;
        }
        goto block_9;
    }
    if (representationModelIndex == 0x52) {
        return 1;
    }
block_9:
    return 0;
}

/* Source-local actor byte view; channel order is numeric, not left/right.
 * The expression timer retains its 0xFFFE/0xFFFF sentinel meanings.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
typedef struct GameAB760State {
    u8 pad0[0x6A];
    u8 blinkControl0;
    u8 blinkControl1;
    u8 blinkCode0;
    u8 blinkCode1;
    u8 pad6E[2];
    u8 field_70;
    u8 expressionPriority;
    u16 expressionTimer;
} GameAB760State;

void func_1507E2B0(GameAB760State *);
void actor_restore_default_expression(GameAB760State *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E73C CURRENT (220) */
void func_1507E73C(GameAB760State *arg0) {
    u32 temp_v0;
    u16 temp_v1;

    if (arg0->pad0[5] != 2) {
        temp_v1 = arg0->expressionTimer;
        if (temp_v1 != 0) {
            if (temp_v1 == 0xFFFE) {
                return;
            }
            temp_v0 = (u32)temp_v1;
            if (temp_v1 != 0xFFFF) {
                if (D_800BE9E4 < (s32)temp_v0) {
                    arg0->expressionTimer = temp_v0 - D_800BE9E4;
                } else {
                    arg0->expressionTimer = 0;
                }
            }
        }
        if (func_1507E6B8(arg0) != 0) {
            func_1507E2B0(arg0);
        }
        if ((arg0->expressionTimer == 0) && (arg0->field_70 != arg0->pad6E[1])) {
            func_1507EABC(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E73C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E73C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E7E4 CURRENT (132) */
void func_1507E7E4(GameAB760State *arg0, u8 arg1, u8 arg2, u16 arg3, s32 arg4) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 temp_v1;

    temp_v1 = arg0->pad6E[1];
    if (((arg1 != temp_v1) || (arg2 != arg0->expressionPriority) ||
         (arg0->expressionTimer != arg3)) &&
        ((arg2 == 3) || (temp_v1 == arg0->field_70) ||
         (temp_v1 == arg1) || (arg0->expressionTimer == 0) ||
         ((s32)arg0->expressionPriority < arg2))) {
        if ((s32)arg1 < func_1507E968(arg0)) {
            temp_v0 = func_1507E908(arg0, (s32)arg0->pad6E[1]);
            if (temp_v0[4] != 0) {
                temp_v0_2 = func_1507E9F8(arg0, 0);
                if (temp_v0_2 != 0) {
                    func_150302F0(arg0, (s32)temp_v0_2[temp_v0[4] - 1]);
                }
            }
            arg0->pad6E[1] = arg1;
            arg0->expressionTimer = arg3;
            arg0->expressionPriority = arg2;
            func_1507E5C8(arg0->pad0, arg4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E7E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E7E4.s")

/* Relocated eight-byte indexed-asset descriptor; field widths are unchanged. */
typedef struct GameAB760ValueRecord {
    s32 dataAddress;
    s32 sizeBytes;
} GameAB760ValueRecord;

/* Descriptive role: actor_get_expression_record.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
u8 *actor_get_expression_record(void *actor, s32 expressionIndex) {
    s32 expressionAddress;
    GameAB760ValueRecord *descriptor;

    descriptor = D_800D1C90[func_150849A0(actor)];
    if (descriptor != 0) {
        expressionAddress = (--descriptor)->dataAddress;
        if (expressionAddress != 0) {
            return (u8 *)((expressionIndex * 0xA) + expressionAddress);
        }
    }
    return 0;
}
/* Descriptive role: actor_get_expression_count.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
s32 actor_get_expression_count(void *actor) {
    GameAB760ValueRecord *descriptor;
    s32 modelIndex;
    s32 defaultsModelIndex;

    modelIndex = *(u8 *)((u8 *)actor + 4);
    if (modelIndex != 0x96) {
        defaultsModelIndex = func_150849A0(actor);
    } else {
        defaultsModelIndex = modelIndex;
    }
    if (defaultsModelIndex == 0xFF) {
        return 0;
    }
    descriptor = D_800D1C90[defaultsModelIndex];
    if (descriptor != 0) {
        return (u32)(--descriptor)->sizeBytes / 10U;
    }
    return 0;
}
void func_1507E9E8(s32 arg0, s32 arg1) {
}
extern u8 D_8009D910[];

/* Descriptive role: actor_get_expression_action_table.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
u8 *actor_get_expression_action_table(void *actor, s32 *countOut) {
    if (func_150849A0(actor) == 0) {
        if (countOut != 0) {
            *countOut = 5;
        }
        return D_8009D910;
    }
    if (countOut != 0) {
        *countOut = 0;
    }
    return 0;
}
u8 *actor_get_expression_action_table(void *, s32 *);
void func_15083568(void *, s32, f32, s32);
extern f32 D_8009B8A0;

/* Descriptive role: actor_dispatch_expression_action.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
void actor_dispatch_expression_action(void *actor, s32 actionSelector, s32 actionParameterRaw) {
    u8 *actionIds;

    if (actionSelector != 0) {
        actionIds = actor_get_expression_action_table(actor, 0);
        if (actionIds != 0) {
            func_15083568(actor, actionIds[actionSelector - 1], (f32)actionParameterRaw * D_8009B8A0, 0);
        }
    }
}
void func_1507E7E4(GameAB760State *, u8, u8, s32, s32);

/* Descriptive role: actor_restore_default_expression.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
void actor_restore_default_expression(GameAB760State *actor) {
    func_1507E7E4(actor, actor->field_70, 3, 0xFFFF, 0xA);
    actor->expressionPriority = 0;
    actor->expressionTimer = 0;
    if (actor->blinkCode0 >= 0xA) {
        actor->blinkCode0 = 0;
        actor->blinkControl0 = 0;
    }
    if (actor->blinkCode1 >= 0xA) {
        actor->blinkCode1 = 0;
        actor->blinkControl1 = 0;
    }
}
void func_1507EB4C(GameAB760State *arg0, s32 arg1);

/* Descriptive role: actor_set_default_expression_zero.
 * Evidence: docs/evidence/character_expression_semantics.md.
 */
void actor_set_default_expression_zero(GameAB760State *actor) {
    func_1507EB4C(actor, 0);
}

void func_1507EB4C(GameAB760State *arg0, s32 arg1) {
    if (arg1 != arg0->field_70) {
        arg0->field_70 = (u8)arg1;
        func_1507EABC(arg0);
    }
}
