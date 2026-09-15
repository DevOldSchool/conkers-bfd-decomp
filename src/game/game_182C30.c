#include "types.h"

/*
 * Reviewed source unit: src/game/game_182C30.c
 * Boundary evidence: docs/evidence/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15155780
 * - func_151557FC
 * - func_1515589C
 * - func_15155CFC
 * - func_15155FD4
 * - func_15156028
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0xE];
    s16 fieldE;
    s8 field10;
    u8 field11;
    u8 pad12[2];
    s32 field14;
    u8 pad18[0x80];
    f32 field98;
} Game182C30Effect;

s32 func_1518C900(s32); /* extern */
Game182C30Effect *func_15167A68(s32, s32, s32, s32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155780 CURRENT (245) */
Game182C30Effect *func_15155780(s32 arg0, s32 arg1) {
    Game182C30Effect *effect;

    effect = func_15167A68(0x50, 0, 0xA0, 1, arg1, 1);
    if (effect == 0) {
        return effect;
    }
    effect->field11 = 0;
    effect->field14 = 0;
    effect->field10 = arg0;
    effect->field98 = 0.0f;
    func_1518C900(0xA6);
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155780.s")
Game182C30Effect *func_15155780(s32, s32);
void *func_15155FD4(s32);
extern u8 D_800CC37D[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151557FC CURRENT (100) */
void func_151557FC(s32 arg0, s32 arg1, f32 arg2) {
    Game182C30Effect *effect;

    effect = func_15155FD4(arg0);
    if (effect == 0) {
        effect = func_15155780(arg0, 0xFF);
    }
    if (effect != 0) {
        effect->field98 = arg2;
        if (D_800CC37D[arg0 * 0x32C] != 0) {
            effect->fieldE = 0;
            effect->field11 = 0;
            return;
        }
        effect->field11 = 3;
        effect->fieldE = (s16)arg1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151557FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_151557FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_1515589C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155CFC.s")
extern void func_1515F10C(void *arg0);
extern void func_15169804(s32 arg0);
extern void func_1518CA04(s32 arg0);

void func_15155EF8(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0;
    if (*(void **)((u8 *)temp_a1 + 0x14) != 0) {
        func_1515F10C(*(void **)((u8 *)temp_a1 + 0x14));
    }
    func_15169804((s32) temp_a1);
    func_1518CA04(0xA6);
}
/* Call context: func_15155FD4: unique active project prototype */
void * func_15155FD4(s32);
extern u8 D_800C3E78;

void func_15155F3C(void) {
    Game182C30Effect *effect;

    effect = func_15155FD4(D_800C3E78);
    if (effect != 0) {
        if (effect->field11 == 2) {
            effect->field11 = 0;
            return;
        }
        if (effect->field11 == 3) {
            effect->field11 = 2;
        }
    }
}
void *func_15155FD4(s32);                           /* extern */
extern u8 D_800C3E78;

void func_15155F90(void) {
    void *temp_v0;

    temp_v0 = func_15155FD4(D_800C3E78);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11) == 3)) {
        *(u8 *)((u8 *)temp_v0 + 0x11) = 1U;
    }
}
typedef struct Game182C30Node {
    u8 pad_0[8];
    struct Game182C30Node *next;
    u8 pad_C[4];
    u8 field_10;
} Game182C30Node;

typedef struct {
    u8 pad_0[0x140];
    Game182C30Node *field_140;
    u8 pad_144[0x5C];
} Game182C30Block;

extern Game182C30Block D_800DCE50;
extern Game182C30Block D_800DD190;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155FD4 CURRENT (50) */
void *func_15155FD4(s32 arg0) {
    Game182C30Node *var_v1;
    Game182C30Block *var_a1;

    var_a1 = &D_800DCE50;
    do {
        var_v1 = var_a1->field_140;
        var_a1++;
        while (var_v1 != 0) {
            if (arg0 == var_v1->field_10) {
                return var_v1;
            }
            var_v1 = var_v1->next;
        }
    } while (var_a1 != &D_800DD190);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15156028.s")
