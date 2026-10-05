#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFB70.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D275C
 * - func_151D2830
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, s32, s32);

void func_151D26C0(s16 arg0) {
    void *temp_v0;

    temp_v0 = func_15167A68(0x3C, 1, 0x18, 0, 0xFF, 1);
    *(s16 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x12) = 0;
    *(s16 *)((u8 *)temp_v0 + 0xE) = 0;
    *(s8 *)((u8 *)temp_v0 + 0x16) = 1;
    *(s16 *)((u8 *)temp_v0 + 0x10) = arg0;
}
extern void *D_800DD0E0;

void func_151D2718(s16 arg0) {
    void *var_v0;

    var_v0 = D_800DD0E0;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s16 *)((u8 *)var_v0 + 0x10)) {
                *(s8 *)((u8 *)var_v0 + 0x16) = -2;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 8);
        } while (var_v0 != 0);
    }
}
void func_1516972C(u8 *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D275C CURRENT (115) */
void func_151D275C(void *arg0) {
    s32 temp_v1;
    s8 temp_v0;

    *(s16 *)((u8 *)arg0 + 0xE) = (s16)(*(s16 *)((u8 *)arg0 + 0xE) +
        (D_800BE9E4 * (temp_v0 = *(s8 *)((u8 *)arg0 + 0x16))));
    if ((temp_v0 > 0) && (*(s16 *)((u8 *)arg0 + 0xE) >= 0xED)) {
        temp_v1 = 0x128 - *(s16 *)((u8 *)arg0 + 0xE);
        *(s16 *)((u8 *)arg0 + 0x14) = (s16)(temp_v1 * 4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            *(s16 *)((u8 *)arg0 + 0x14) = 0;
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16)(*(s16 *)((u8 *)arg0 + 0xE) * 2);
    }
    if (*(s16 *)((u8 *)arg0 + 0x14) >= 0x80) {
        *(s16 *)((u8 *)arg0 + 0x14) = 0x80;
    }
    *(s16 *)((u8 *)arg0 + 0x12) = (s16)(*(s16 *)((u8 *)arg0 + 0x12) + 1);
    if (*(s16 *)((u8 *)arg0 + 0x12) >= 0x100) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16)(*(s16 *)((u8 *)arg0 + 0x12) - 0x100);
    }
    if ((*(s16 *)((u8 *)arg0 + 0xE) >= 0x12D) || (*(s16 *)((u8 *)arg0 + 0xE) < 0)) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D275C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D275C.s")
typedef struct GameD2830Command { u32 word0, word1; } GameD2830Command;
typedef struct GameD2830State {
    u8 pad00[0x10];
    s16 id;
    s16 phase;
    s16 opacity;
} GameD2830State;
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_A48[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D2830 CURRENT (3025) */
void *func_151D2830(GameD2830Command *arg0, GameD2830State *arg1, s32 arg2) {
    s32 resource;

    arg2 = (s16)arg2;
    if (arg2 != arg1->id || arg1->opacity == 0) return arg0;
    {
        register GameD2830Command *command0 = arg0;
        command0->word1 = -1;
        arg0++;
        command0->word0 = 0xD7000002;
    }
    {
        register GameD2830Command *command1 = arg0++;
        command1->word0 = 0xE7000000;
        command1->word1 = 0;
    }
    {
        register GameD2830Command *command2 = arg0++;
        command2->word0 = 0xFC12D225;
        command2->word1 = 0xFFA7FFFF;
    }
    {
        register GameD2830Command *command3 = arg0++;
        command3->word0 = 0xEF002C3F;
        command3->word1 = 0x00504244;
    }
    resource = func_1510D0EC((s32)D_A48, 0, 3, 0);
    {
        register GameD2830Command *command4 = arg0++;
        command4->word0 = 0xFD700000;
        command4->word1 = resource;
    }
    {
        register GameD2830Command *command5 = arg0++;
        command5->word0 = 0xF5700000;
        command5->word1 = 0x07018060;
    }
    {
        register GameD2830Command *command6 = arg0++;
        command6->word0 = 0xE6000000;
        command6->word1 = 0;
    }
    {
        register GameD2830Command *command7 = arg0++;
        command7->word0 = 0xF3000000;
        command7->word1 = 0x077FF000;
    }
    {
        register GameD2830Command *command8 = arg0++;
        command8->word0 = 0xE7000000;
        command8->word1 = 0;
    }
    {
        register GameD2830Command *command9 = arg0++;
        command9->word0 = 0xF5681000;
        command9->word1 = 0x00018060;
    }
    {
        register GameD2830Command *command10 = arg0++;
        command10->word0 = 0xF2000000;
        command10->word1 = 0x000FC0FC;
    }
    {
        register GameD2830Command *command11 = arg0++;
        command11->word0 = 0xFB000000;
        command11->word1 = (arg1->opacity & 255) | 0x00FF0000;
    }
    {
        register GameD2830Command *command12 = arg0++;
        command12->word0 = 0xE45003C0;
        command12->word1 = 0;
    }
    {
        register GameD2830Command *command13 = arg0++;
        command13->word0 = 0xE1000000;
        command13->word1 = ((u32)arg1->phase << 19) | 0x400;
    }
    {
        register GameD2830Command *command14 = arg0++;
        command14->word1 = 0x04000400;
        command14->word0 = 0xF1000000;
    }
    {
        register GameD2830Command *command15 = arg0++;
        command15->word0 = 0xE7000000;
        command15->word1 = 0;
    }
    {
        register GameD2830Command *command16 = arg0++;
        command16->word0 = 0xFB000000;
        command16->word1 = ((arg1->opacity >> 1) & 255) | 0xFF000000;
    }
    {
        register GameD2830Command *command17 = arg0++;
        command17->word0 = 0xE45003C0;
        command17->word1 = 0;
    }
    {
        register GameD2830Command *command18 = arg0++;
        command18->word0 = 0xE1000000;
        command18->word1 = (u32)arg1->phase << 19;
    }
    {
        register GameD2830Command *command19 = arg0++;
        command19->word1 = 0x02000200;
        command19->word0 = 0xF1000000;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D2830 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D2830.s")
