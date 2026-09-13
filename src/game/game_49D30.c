#include "types.h"

/*
 * Reviewed source unit: src/game/game_49D30.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501C880
 * - func_1501CC3C
 * - func_1501CDC0
 * - func_1501CE54
 * - func_1501CFF8
 * - func_1501D044
 * - func_1501D1D4
 * - func_1501D258
 * - func_1501D2C4
 * - func_1501D348
 * - func_1501DAAC
 * - func_1501DE18
 * - func_1501DF04
 * - func_1501E05C
 * - func_1501E1B4
 * - func_1501E2F8
 * - func_1501E400
 * - func_1501E540
 * - func_1501E73C
 * - func_1501E81C
 * - func_1501EA18
 * - func_1501EC38
 * - func_1501F72C
 * - func_1501FC8C
 * - func_1501FE68
 * - func_1501FFE8
 * - func_15020388
 * - func_15020878
 * - func_15020EC4
 * - func_1502178C
 * - func_15021DB8
 * - func_15022024
 * - func_1502225C
 * - func_150222E0
 * - func_15022398
 * - func_15022528
 * - func_15022640
 * - func_150226BC
 * - func_150227BC
 * - func_15022848
 * - func_150228E4
 * - func_150229E4
 * - func_15022B08
 * - func_15022BA4
 * - func_15023264
 * - func_150233E4
 * - func_150234A4
 * - func_150235DC
 * - func_1502378C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game49D30Resource Game49D30Resource;

typedef struct Game49D30Record {
    s16 active;
    u8 pad2[0xA];
    u8 flagC;
    u8 padD[0x27];
    Game49D30Resource *resource34;
} Game49D30Record;

void func_1516D328(Game49D30Resource *);

#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501C880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CC3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CDC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CE54.s")
extern u16 *D_800C35D8[];
extern u8 D_800C363A[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501CFF8 CURRENT (2000) */
s32 func_1501CFF8(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u16 *var_a2;
    u16 temp_t7;
    u8 temp_a1;

    temp_a1 = D_800C363A[arg0];
    var_v1 = 0;
    var_v0 = 0;
    if ((s32)temp_a1 > 0) {
        var_a2 = D_800C35D8[arg0];
        do {
            temp_t7 = *var_a2;
            var_v0 += 1;
            var_a2 += 1;
            var_v1 += temp_t7;
        } while (var_v0 < (s32)temp_a1);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501CFF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CFF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D044.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D1D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DAAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DE18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DF04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E05C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E1B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E540.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E81C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501EA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501EC38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501F72C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FC8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FE68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501FFE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15020EC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502178C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15021DB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022024.s")
typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
} Game49D30Position;

extern Game49D30Position D_800C358C;
extern f32 D_800C3594;
extern s8 D_800C3663;

void func_15022190(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C3594 = arg3;
    D_800C358C.field_0 = arg0;
    D_800C358C.field_2 = arg1;
    D_800C358C.field_4 = arg2;
    D_800C3663 = 1;
}
extern s16 D_800C3598[];
extern f32 D_800C35A0;

void func_150221E8(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C35A0 = arg3;
    D_800C3598[0] = arg0;
    D_800C3598[1] = arg1;
    D_800C3598[2] = arg2;
}
extern u8 D_800C3510[];

void func_15022234(s32 arg0) {
    D_800C3510[arg0] = 0;
}
extern u8 D_800C354A[];

void func_15022248(s32 arg0) {
    D_800C354A[arg0] = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502225C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150222E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022398.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022528.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150226BC.s")
void func_150226BC(s32, s32);

void func_15022754(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;

    temp_s1 = &D_800C363A[arg0];
    var_s0 = 0;
    if (*temp_s1 > 0) {
        do {
            func_150226BC(var_s0, arg0);
            var_s0++;
        } while (var_s0 < *temp_s1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150227BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150228E4.s")
extern void (*D_80086014[])(void);

void func_15022998(s32 *arg0) {
    void (*temp_v1)(void);
    s32 temp_v0;

    temp_v0 = *arg0;
    if ((temp_v0 == 0x1B) || (temp_v0 == 4)) {
        temp_v1 = *(void (**)(void))((u8 *)D_80086014 + (temp_v0 * 4));
        if (temp_v1 != 0) {
            temp_v1();
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150229E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15023264.s")
void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800C3CA0;

void func_150233BC(void) {
    func_100226F0(&D_800C3CA0, 0xA8);
}
void func_1516D2E0(Game49D30Resource *);
extern u8 D_800C3D48;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150233E4 CURRENT (20) */
void func_150233E4(void) {
    u8 *var_s0;
    u8 *var_s1;

    var_s1 = &D_800C3D48;
    var_s0 = &D_800C3CA0;
    do {
        if (*(s16 *)var_s0 != 0) {
            func_1516D2E0(*(void **)(var_s0 + 0x34));
            *(void **)(var_s0 + 0x34) = 0;
            *(s16 *)var_s0 = 0;
        }
        var_s0 += 0x38;
    } while (var_s0 != var_s1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150233E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150233E4.s")
void func_15023440(Game49D30Record *arg0, s32 arg1) {
    if (arg1 != 0) {
        func_1516D2E0(arg0->resource34);
        arg0->resource34 = 0;
    } else if (arg0->flagC != 0) {
        func_1516D328(arg0->resource34);
    } else {
        arg0->resource34 = 0;
    }
    arg0->active = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150234A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150235DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502378C.s")
