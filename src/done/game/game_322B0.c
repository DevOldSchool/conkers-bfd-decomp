#include "types.h"

/*
 * Reviewed source unit: src/game/game_322B0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_small_multi_function_units.md
 */

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    u8 padC[3];
    s8 fieldF;
} Game322B0Record;

extern s32 D_800C6660;
extern s32 D_800C6664;
extern s32 D_800C6668;
extern s8 D_800C666F;
extern Game322B0Record D_800C6670;
extern Game322B0Record D_800C67F0;

void func_15004E00(void) {
    s32 i;

    for (i = 0; i < 25; i++) {
        ((Game322B0Record *)&D_800C6660)[i].field0 = 0;
        ((Game322B0Record *)&D_800C6660)[i].field4 = 0;
        ((Game322B0Record *)&D_800C6660)[i].field8 = 0;
        ((Game322B0Record *)&D_800C6660)[i].fieldF = 0;
    }
}
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
extern void *D_800B0DF0;
extern u16 D_800C3E7C;
extern void *D_800C3E80;
extern void *D_800C3E84;

void func_15004E80(void) {
    D_800C3E80 = func_10003C40((D_800C3E7C = *(u16 *)((u8 *)D_800B0DF0 + 0x1A)) << 6, 1, 3, 0);
    D_800C3E84 = func_10003C40(D_800C3E7C << 6, 1, 3, 0);
}
