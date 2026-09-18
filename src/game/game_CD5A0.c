#include "types.h"

/*
 * Reviewed source unit: src/game/game_CD5A0.c
 * Boundary evidence: docs/evidence/game_raw_record_transform_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A00F0
 * - func_150A019C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameCD5A0Record {
    u32 active : 1;
    u32 enabled : 1;
    u32 kind : 4;
    u32 reserved : 26;
    u32 field_4;
    u32 field_8;
} GameCD5A0Record;

extern GameCD5A0Record D_800D3010[];
extern s32 D_800D3014[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A00F0 CURRENT (70) */
void func_150A00F0(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_800D3010[i].active = 0;
        D_800D3010[i].field_4 = 0;
        D_800D3010[i].field_8 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A00F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A00F0.s")

extern u16 D_80088510[];
extern u16 D_8008851C[];
extern s32 D_800BE9E4;
extern GameCD5A0Record D_800D3088;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A019C CURRENT (10) */
void func_150A019C(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_800D3010[i].active && D_800D3010[i].enabled == 1) {
            D_800D3010[i].field_8 += D_800BE9E4;
            if (D_800D3010[i].field_8 >= D_80088510[D_800D3010[i].kind]) {
                D_800D3010[i].field_8 -= D_80088510[D_800D3010[i].kind];
                D_800D3010[i].field_4++;
                if (D_8008851C[D_800D3010[i].kind] != 0) {
                    D_800D3010[i].field_4 %= D_8008851C[D_800D3010[i].kind];
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A019C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A019C.s")

s32 func_150A0264(s32 arg0, s32 *arg1) {
    GameCD5A0Record *record;

    record = &D_800D3010[arg0];
    if (record->active) {
        return 0;
    }
    record->active = 1;
    record->enabled = 0;
    record->kind = arg1[1];
    record->field_4 = 0;
    return 1;
}

s32 func_150A02D0(s32 arg0, s32 arg1, s32 *arg2) {
    switch (arg1) {
    case 0:
        D_800D3010[arg0].enabled = 1;
        return 1;
    case 1:
        D_800D3010[arg0].enabled = 0;
        return 1;
    case 2:
        *(s32 *)((u8 *)D_800D3014 + arg0 * 0xC) = arg2[2];
        return 1;
    default:
        return 0;
    }
}
extern s32 D_800D3014[];

s32 func_150A0374(s32 arg0, s32 arg1, volatile s32 arg2) {
    if (arg1 == 3) {
        return *(s32 *)((u8 *)D_800D3014 + (arg0 * 0xC));
    }
    return 0;
}

#if 0 /* Candidate definition awaits verified BSS placement; retain the ROM address via extern above. */
GameCD5A0Record D_800D3010[10];
#endif
