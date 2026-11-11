#include "types.h"

/*
 * Reviewed source unit: src/game/game_6CCB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 */

typedef struct {
    s16 field0;
    s16 flags;
    s16 nextOffset;
    u16 radius;
    s16 x;
    s16 z;
    s16 value;
} Game6CCB0Node;

void func_1510F800(s32);
extern Game6CCB0Node *D_800DBE48;

s32 func_1503F800(void *arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    Game6CCB0Node *node;
    s32 offset;
    s32 value;

    func_1510F800(0);
    node = D_800DBE48;
    while (node != NULL) {
        if ((node->x + node->radius) >= arg1 && arg1 >= (node->x - node->radius) &&
            (node->z + node->radius) >= arg2 && arg2 >= (node->z - node->radius)) {
            if (!(node->flags & (1 << arg3))) {
                return 1;
            }
            value = node->value;
            if (value != 0) {
                offset = value;
            } else {
                return 0;
            }
        } else {
            offset = node->nextOffset;
        }
        if (offset != 0) {
            node = (Game6CCB0Node *)((u8 *)node + offset);
        } else {
            node = NULL;
        }
    }
    return 1;
}
extern s32 func_1503F800(void *, s16, s16, s32, s32);

void func_1503F904(void *arg0, s32 arg1, s32 arg2) {
    func_1503F800((u8 *)arg0 + 0x320, (s16)*(f32 *)((u8 *)arg0 + 0x14),
                  (s16)*(f32 *)((u8 *)arg0 + 0x1C), arg1, 1);
}
extern u8 D_800C67F0;
extern u8 D_800C67F1;
extern u8 D_800CC2D0[];

void func_1503F964(void) {
    s32 var_a0;
    s32 temp_v0;

    if (D_800C67F0 != 0) {
        temp_v0 = D_800C67F1;
        var_a0 = D_800C67F1 + 1;
        if (var_a0 >= 0x19) {
            var_a0 = 0;
        }
        if (var_a0 != temp_v0) {
            do {
                if ((*(s32 *)(D_800CC2D0 + (var_a0 * 0x32C) + 0xF8) & 0x800000) != 0) {
                    D_800C67F1 = (u8)var_a0;
                    return;
                }
                var_a0 += 1;
                if (var_a0 >= 0x19) {
                    var_a0 = 0;
                }
            } while (var_a0 != temp_v0);
        }
    }
}
