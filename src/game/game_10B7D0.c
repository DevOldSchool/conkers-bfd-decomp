#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B7D0.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DE32C
 * - func_150DE458
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150DE320(s32 arg0) {

}
typedef struct {
    u8 bytes[8];
} Game10B7D0Lookup8;

void func_150A2864(s32, s32);
s32 func_150A32B4(s32, s32, s32, s32);
void *func_151149AC(u8, s32);
extern Game10B7D0Lookup8 D_80088950;
extern Game10B7D0Lookup8 D_80088958;
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DE32C CURRENT (1180) */
void func_150DE32C(s32 arg0, s32 arg1, s32 arg2) {
    Game10B7D0Lookup8 ids;
    Game10B7D0Lookup8 actions;
    s32 i;
    u8 *id;
    void *object;
    u8 action;

    ids = D_80088950;
    actions = D_80088958;
    i = 0;
    id = ids.bytes;
    do {
        if (func_150A32B4((*id * 0x34) + D_800D3098, arg0, arg1, arg2) != 0) {
            action = actions.bytes[i];
            if (action != 0) {
                object = func_151149AC(action, 1);
                *((u8 *) object + 0x73) = (*((u8 *) object + 0x73) & ~3) | 3;
            } else {
                func_150A2864(*id, 1);
            }
        }
        i++;
        id++;
    } while (i != 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DE32C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE32C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B7D0/func_150DE458.s")
f32 func_15048A40(s32);                             /* extern */
extern f32 D_800A0D48;
extern f32 D_800A0D4C;
extern f32 D_800A0D50;
extern f32 D_800A0D54;
extern s32 D_800BE9E4;

void func_150DE6D8(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x7C) >> 3) & 0xFF) * D_800A0D48) + D_800A0D4C);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x80) >> 3) & 0xFF) * D_800A0D50);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (func_15048A40(((s32) *(s32 *)((u8 *)arg0 + 0x84) >> 3) & 0xFF) * D_800A0D54);
    *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (*(s32 *)((u8 *)arg0 + 0x7C) + (D_800BE9E4 * 0xC));
    *(s32 *)((u8 *)arg0 + 0x80) = (s32) (*(s32 *)((u8 *)arg0 + 0x80) + (D_800BE9E4 * 0x10));
    *(s32 *)((u8 *)arg0 + 0x84) = (s32) (*(s32 *)((u8 *)arg0 + 0x84) + (D_800BE9E4 * 0x18));
}
