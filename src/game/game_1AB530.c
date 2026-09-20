#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AB530.c
 * Boundary evidence: docs/evidence/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517E28C
 * - func_1517E4A8
 * - func_1517EAAC
 * - func_1517EC1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10003C40(s32, s32, s32, s32);
extern void *D_800DDD64;

void *func_1517E080(s32 arg0, s32 arg1) {
    void *node;
    void **link;
    void *result;

    node = D_800DDD64;
    if (node != 0) {
        while (*(void **)((u8 *)node + 0x24) != 0) {
            node = *(void **)((u8 *)node + 0x24);
        }
        link = (void **)((u8 *)node + 0x24);
    } else {
        link = &D_800DDD64;
    }
    result = func_10003C40(0x34, 1, 0, 1);
    if (result == 0) {
        return 0;
    }
    *link = result;
    *(s32 *)((u8 *)result + 0x24) = 0;
    *(s16 *)((u8 *)result + 0x28) = 0;
    *(s8 *)((u8 *)result + 0x2E) = 0;
    *(f32 *)((u8 *)result + 0x10) = 0.0f;
    *(f32 *)((u8 *)result + 0xC) = 0.0f;
    *(s8 *)((u8 *)result + 0x2F) = (s8)arg0;
    *(s8 *)((u8 *)result + 0x30) = (s8)arg1;
    return result;
}
/* Call context: func_10004074: unique active project prototype */
void func_10004074(s32);

void func_1517E134(void *arg0) {
    void *var_v0;
    void *var_v1;

    var_v0 = D_800DDD64;
    if (arg0 == var_v0) {
        D_800DDD64 = *(void **)((u8 *)arg0 + 0x24);
        goto block_8;
    }
    var_v1 = var_v0;
    if (var_v0 != 0) {
        var_v0 = *(void **)((u8 *)var_v0 + 0x24);
        if (arg0 != var_v0) {
loop_4:
            var_v1 = var_v0;
            if (var_v0 != 0) {
                var_v0 = *(void **)((u8 *)var_v0 + 0x24);
                if (arg0 != var_v0) {
                    goto loop_4;
                }
            }
        }
    }
    if (var_v1 != 0) {
        *(void **)((u8 *)var_v1 + 0x24) = (void *) *(void **)((u8 *)arg0 + 0x24);
block_8:
        func_10004074((s32) arg0);
    }
}
typedef struct Game1AB530Node {
    u8 pad0[0xC];
    f32 field_C;
    f32 field_10;
    u8 pad14[0x10];
    struct Game1AB530Node *next;
    u8 pad28[2];
    u16 field_2A;
} Game1AB530Node;

extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE9C4;

void func_1517E1AC(void) {
    f32 temp_fv0;
    f32 temp_fv1;
    Game1AB530Node *var_v0;

    var_v0 = D_800DDD64;
    if (var_v0 != 0) {
        do {
            temp_fv0 = var_v0->field_C;
            if ((temp_fv0 >= 0.0f) && (temp_fv0 < (f32)D_800BE620)) {
                temp_fv1 = var_v0->field_10;
                if ((temp_fv1 >= 0.0f) && (temp_fv1 < (f32)D_800BE624)) {
                    var_v0->field_2A = ((u16 *)D_800BE9C4)[
                        (s32)temp_fv0 + ((s32)temp_fv1 * D_800BE620)];
                }
            }
            var_v0 = var_v0->next;
        } while (var_v0 != 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517E28C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517E4A8.s")
typedef union Game1AB530DisplayCommand {
    struct {
        u32 word0;
        u32 word1;
    } words;
    u64 alignment;
} Game1AB530DisplayCommand;

#define GAME1AB530_COMMAND(pkt, first, second)                  \
{                                                              \
    Game1AB530DisplayCommand *command = (pkt);                  \
    command->words.word0 = (u32)(first);                        \
    command->words.word1 = (u32)(second);                       \
}

Game1AB530DisplayCommand *func_1517EA4C(Game1AB530DisplayCommand *arg0) {
    GAME1AB530_COMMAND(arg0++, 0xE7000000, 0);
    GAME1AB530_COMMAND(arg0++, 0xFCFFB3FF, 0xFF65FEFF);
    GAME1AB530_COMMAND(arg0++, 0xEF002C0F, 0x00504344);
    return arg0;
}

#undef GAME1AB530_COMMAND
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517EAAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517EC1C.s")
