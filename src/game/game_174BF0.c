#include "types.h"

/*
 * Reviewed source unit: src/game/game_174BF0.c
 * Boundary evidence: docs/evidence/game_raw_effect_dispatch_engine.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15147740
 * - func_1514795C
 * - func_15147A80
 * - func_15147C4C
 * - func_15147D1C
 * - func_15147D64
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147740.s")
void func_151478D0(s32 arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}
void func_1514795C(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151478F4(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169804(arg0);
}
void func_15147928(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169824(arg0);
}
void func_100043B4(void *, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514795C CURRENT (890) */
void func_1514795C(s32 arg0) {
    void *temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(void **)((u8 *)var_s0 + 0x3C);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x4C);
    if (temp_v0 != 0) {
        func_100043B4(temp_v0, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514795C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_1514795C.s")
typedef struct {
    u8 pad_0[0x20];
    s32 field_20;
} Game174BF0State;

extern void (*D_8008A2F0[])(void);

void func_151479E0(Game174BF0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_20;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x14) {
        temp_v0 = 0;
    }
    D_8008A2F0[temp_v0]();
}
extern void (*D_8008A340[])(void);

void func_15147A30(Game174BF0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field_20;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x14) {
        temp_v0 = 0;
    }
    D_8008A340[temp_v0]();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147C4C.s")
extern void (*D_8008A390[])(void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147D1C CURRENT (237) */
void func_15147D1C(void *arg0, s32 arg1, s32 arg2) {
    void (*temp_v0)(void *, s32, s32);

    arg2 = (u8) arg2;
    temp_v0 = D_8008A390[*(s32 *)((u8 *)arg0 + 0x20)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147D1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147D1C.s")
void func_15169260(void *, s32, s32, s32);
extern u8 D_800A5760;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147D64 CURRENT (260) */
void func_15147D64(s32 arg0, s32 arg1) {
    func_15169260(&D_800A5760, 2, arg0, (u8) arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147D64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147D64.s")
