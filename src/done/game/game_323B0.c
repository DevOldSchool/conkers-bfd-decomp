#include "types.h"

/*
 * Reviewed source unit: src/game/game_323B0.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define actor_attachments_clear_list_head func_15004F00

extern s32 D_800C3EE0;
extern s8 D_800C4000;

void actor_attachments_clear_list_head(void) {
    D_800C3EE0 = 0;
}
void func_15004F10(void) {
    D_800C4000 = 0xF;
}
