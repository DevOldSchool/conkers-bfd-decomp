#include "types.h"

/*
 * Reviewed source unit: src/game/game_B21B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15084D70
 * - func_15085430
 * - func_15085710
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameB21B0Inner {
    u8 pad0[0x11B];
    u8 field_11B;
} GameB21B0Inner;

typedef struct GameB21B0Object {
    u8 pad0[4];
    u8 modelIndex;
    u8 pad5[0x317];
    GameB21B0Inner *inner;
} GameB21B0Object;

extern u8 *D_80087240[];
extern u8 D_8009D954[];

/* Semantic role: actor_get_animation_model_representative.
 * Scans seven model-sharing groups, returning the first member of the first
 * matching group or the current model byte unchanged. Model assignment stores
 * this bank-02 animation-resource model index separately at actor +6.
 * See docs/evidence/assets/naming/actor_animation_model_group_semantics.md.
 */
s32 func_15084D00(GameB21B0Object *arg0) {
    s32 i;
    s32 j;
    s32 value;

    value = arg0->modelIndex;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < D_8009D954[i]; j++) {
            if (value == D_80087240[i][j]) {
                return D_80087240[i][0];
            }
        }
    }
    return value;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15084D70.s")
void func_15085410(GameB21B0Object *arg0, s32 arg1) {
    arg0->inner->field_11B = arg1;
}
u8 func_15085420(GameB21B0Object *arg0) {
    return arg0->inner->field_11B;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B21B0/func_15085710.s")
/* Fields recovered from the shared 0x1C-byte player records. */
typedef struct GameB21B0PlayerRecord {
    s32 field_0;
    s32 field_4;
    s8 field_8;
    s8 field_9;
    u8 field_A;
    u8 padB;
    s32 field_C;
    u8 pad10[0xC];
} GameB21B0PlayerRecord;

extern GameB21B0PlayerRecord D_800D213C[];
extern u16 D_800D2340;

s32 func_150859AC(s16 arg0, s16 arg1) {
    if (arg0 >= 0xFF) {
        return 0;
    }
    switch (arg1) {
    case 0:
        return D_800D2340 & (1 << arg0);
    case 1:
        return D_800D213C[arg0].field_0;
    case 2:
        return D_800D213C[arg0].field_4;
    case 3:
        return D_800D213C[arg0].field_8;
    case 4:
        return D_800D213C[arg0].field_9;
    case 5:
        return D_800D213C[arg0].field_A;
    case 6:
        return D_800D213C[arg0].field_C;
    }
}

void func_15085710(s16, s32, u8);
extern u8 D_800CC2D0[];
extern u8 D_800D18A8;

void func_15085ABC(s16 arg0) {
    s32 i;

    if (D_800D18A8 != 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if ((1 << i) & arg0) {
            func_15085710(i, 5, ((u8 (*)[0x32C])&D_800CC2D0)[i][0x1CA]);
        }
    }
}
