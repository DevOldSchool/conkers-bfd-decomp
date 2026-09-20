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
 * - func_15022398
 * - func_15022528
 * - func_15022640
 * - func_150227BC
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
extern s32 D_800C3960[];
extern u8 D_800C363A[];
extern s32 D_800C3640[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501C880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CC3C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501CDC0 CURRENT (1220) */
void func_1501CDC0(s32 arg0) {
    s32 *var_a1;
    s32 var_a0;
    s32 var_v0;
    u8 *temp_v1;

    temp_v1 = &D_800C363A[arg0];
    var_v0 = 0;
    if ((s32)*temp_v1 > 0) {
        var_a1 = (s32 *)((u8 *)D_800C3960 + (arg0 * 0x78));
        var_a0 = 0;
outer_loop:
        loop_3:
            *(u8 *)((u8 *)*var_a1 + var_a0) = 0xFF;
            *(u8 *)((u8 *)*var_a1 + var_a0 + 1) = 0xFF;
            *(u8 *)((u8 *)*var_a1 + var_a0 + 2) = 0xFF;
            *(u8 *)((u8 *)*var_a1 + var_a0 + 3) = 0xFF;
            var_a0 += 4;
            if (var_a0 != 0x10) {
                goto loop_3;
            }
            var_v0 += 1;
            var_a1 += 4;
            if (var_v0 < (s32)*temp_v1) {
                var_a0 = 0;
                goto outer_loop;
            }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501CDC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CDC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501CE54.s")
extern u16 *D_800C35D8[];

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
extern s32 D_800C3668[];
s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32, s32);

s32 func_1501D1D4(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0;

    temp_v0 = func_1502B6BC(&sp30, 0, &sp34, 3, 6, arg0, arg1);
    if (temp_v0 != 0) {
        D_800C3668[arg2] = temp_v0;
    } else {
        D_800C3668[arg2] = 0;
    }
    return temp_v0;
}
u64 func_100268A4(s32, s32, s32, s32);
extern u8 D_800C3670;
extern u64 D_800C3A60[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501D258 CURRENT (950) */
void func_1501D258(s32 arg0, s32 arg1) {
    u64 temp_ret;
    u64 *temp_a0;

    if (D_800C3670 == 0) {
        temp_ret = func_100268A4(0, 1, arg1 >> 31, arg1);
        temp_a0 = &D_800C3A60[arg0];
        *temp_a0 |= temp_ret;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501D258 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D258.s")
extern u8 D_800C3A64;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501D2C4 CURRENT (2260) */
s32 func_1501D2C4(s32 arg0, s32 arg1) {
    s32 var_v0;
    u64 temp_ret;

    if (D_800C3670 != 0) {
        return 1;
    }
    temp_ret = func_100268A4(0, 1, arg1 >> 0x1F, arg1);
    if ((temp_ret & D_800C3A60[arg0]) ||
        (var_v0 = 0, (((u32)temp_ret & *(u32 *)((u8 *)&D_800C3A64 + (arg0 * 8))) != 0))) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501D2C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501D348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DAAC.s")
void func_150242F8(s32, s32);
void func_1501EC38(s32);
void func_15020EC4(s32);
void func_1501E81C(s32, s32);
s32 func_150229E4(void *);
void func_1502178C(void *, s32, s32);
extern s32 D_800BEA08;
extern s32 D_800C35B0[];
extern s8 D_800C3E78;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501DE18 CURRENT (110) */
void func_1501DE18(s32 arg0) {
    u8 *actor;
    s32 index;

    D_800C35B0[arg0] = D_800C3640[arg0] + D_800BEA08;
    func_150242F8(1, 0);
    func_1501EC38(0);
    func_150242F8(0, 0);
    func_15020EC4(0);
    actor = &D_800CC2D0;
    index = 0;
    do {
        if (*(s32 *)actor != 0) {
            D_800C3E78 = index;
            if (func_150229E4(actor) != 0) {
                func_1502178C(actor, arg0, -1);
            }
        }
        index++;
        actor += 0x32C;
    } while (index != 0x19);
    func_1501E81C(1, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501DE18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DE18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501DF04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E05C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E1B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1501E540.s")
void *func_15083E90(u8);
void func_1507EABC(void *);
extern void *D_800C35F0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501E73C CURRENT (1825) */
void func_1501E73C(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;
    void *temp_v0;
    void *temp_v0_2;

    temp_s1 = &D_800C363A[arg0];
    if ((s32)*temp_s1 > 0) {
        var_s0 = 0;
        do {
            temp_v0 = (u8 *)D_800C35F0[arg0] + var_s0;
            if (*(u16 *)temp_v0 == 2) {
                temp_v0_2 = func_15083E90(*(u8 *)((u8 *)temp_v0 + 2));
                if (temp_v0_2 == 0) {
                } else {
                    if (*(u8 *)((u8 *)temp_v0_2 + 0x6C) >= 0xA) {
                        *(u8 *)((u8 *)temp_v0_2 + 0x6C) = 0;
                        *(u8 *)((u8 *)temp_v0_2 + 0x6A) = 0;
                    }
                    if (*(u8 *)((u8 *)temp_v0_2 + 0x6D) >= 0xA) {
                        *(u8 *)((u8 *)temp_v0_2 + 0x6D) = 0;
                        *(u8 *)((u8 *)temp_v0_2 + 0x6B) = 0;
                    }
                    func_1507EABC(temp_v0_2);
                }
            }
            var_s0 += 8;
        } while (var_s0 < (*temp_s1 * 8));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501E73C */
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
extern u8 D_800C3518[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502225C CURRENT (1215) */
void func_1502225C(s8 arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_v1;
    u8 *var_t0;
    u8 temp_a2;

    temp_v1 = &D_800C3510[arg1];
    temp_a2 = *temp_v1;
    var_v0 = 0;
    if ((s32)temp_a2 > 0) {
        var_t0 = (arg1 * 0x19) + D_800C3518;
loop_2:
        var_v0 += 1;
        if (arg0 != *var_t0) {
            var_t0 += 1;
            if (var_v0 < (s32)temp_a2) {
                goto loop_2;
            }
        } else {
            return;
        }
    }
    D_800C3518[(arg1 * 0x19) + temp_a2] = arg0;
    *temp_v1 = temp_a2 + 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502225C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502225C.s")
typedef struct Game49D30Entry {
    u16 field_0;
    u8 field_2;
} Game49D30Entry;

typedef struct Game49D30Object {
    u8 pad0[0x6A];
    u8 field_6A;
    u8 field_6B;
    u8 field_6C;
    u8 field_6D;
    u8 pad6E[2];
    u8 field_70;
    u8 field_71;
    u8 pad72[0x208];
    u16 field_27A;
    u16 field_27C;
    u16 field_27E;
    u16 field_280;
    u16 field_282;
} Game49D30Object;

void func_1507E7E4(void *, u8, u8, s32, s32);
void *func_15083E90(u8);
extern void *D_800C35C8[];
extern void *D_800C35F0[];

void func_150222E0(s32 arg0, s32 arg1) {
    Game49D30Object *temp_v0;
    Game49D30Object *sp24;
    Game49D30Entry *temp_v1;

    if (*(u16 *)((u8 *)D_800C35C8[arg1] + (arg0 * 2)) != 0) {
        temp_v1 = (Game49D30Entry *)((u8 *)D_800C35F0[arg1] + (arg0 * 8));
        if (temp_v1->field_0 == 2) {
            temp_v0 = (Game49D30Object *)func_15083E90(temp_v1->field_2);
            if (temp_v0 != 0) {
                temp_v0->field_6C = 0;
                temp_v0->field_6D = 0;
                temp_v0->field_6A = 0;
                temp_v0->field_6B = 0;
                temp_v0->field_282 = 0;
                temp_v0->field_27A = 0;
                temp_v0->field_27C = 0;
                temp_v0->field_27E = 0;
                temp_v0->field_280 = 0;
                sp24 = temp_v0;
                func_1507E7E4(temp_v0, 0, 3, 0xFFFF, 0xA);
                sp24->field_71 = 0;
            }
        }
    }
}
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
u8 *func_1505EEF4(s32);
void func_15082A44(void *, s32, s32, s32, s32);
s32 func_15083E0C(s32);
void func_1502225C(s32, s32);
extern u8 D_800CC2D0;
extern u8 *D_800D20FC;
extern u8 D_800D2100;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15022398 CURRENT (157) */
void func_15022398(s32 arg0, s32 arg1) {
    u8 *sp3C;
    s32 sp38;
    s32 sp34;
    void **sp2C;
    s32 temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 temp_v0;
    void **temp_a2;
    void *temp_v1;

    temp_a2 = &D_800C35F0[arg1];
    if ((*(u16 *)((u8 *)D_800C35C8[arg1] + (arg0 * 2)) != 0) &&
        (temp_v1 = (void *)((u8 *)*temp_a2 + (arg0 * 8)), (*(u16 *)((u8 *)temp_v1 + 0) == 2)) &&
        (temp_v0 = *(u8 *)((u8 *)temp_v1 + 2), sp2C = temp_a2, sp34 = (s32)temp_v0,
         temp_v0_2 = func_15083E0C(temp_v0), (temp_v0_2 != -1))) {
        sp38 = temp_v0_2;
        sp2C = temp_a2;
        temp_v0_3 = func_1505EEF4(temp_v0_2);
        if (temp_v0_3 != 0) {
            if (*(u8 *)((u8 *)temp_v0_3 + 5) == 3) {
                if (temp_a2 != D_800C35F0) {
                    *(u8 *)((u8 *)temp_v0_3 + 5) = 4;
                } else {
                    *(u8 *)((u8 *)temp_v0_3 + 5) = 0;
                }
            }
            if (sp34 == 1) {
                *(s32 *)((u8 *)temp_v0_3 + 0xF4) &= ~0x2A;
            }
        } else if (sp38 < (s32)D_800D2100) {
            func_15082A44(D_800D20FC + (sp38 * 0x30), sp38, 0, arg1, 0);
            temp_v0_4 = (u8 *)func_1505EEF4(sp38);
            if (temp_v0_4 != 0) {
                sp3C = temp_v0_4;
                func_1505E650(temp_v0_4, 0, 0, 0, 0.0f, 0.0f, 1);
                func_1502225C((s8)(((s32)(sp3C - &D_800CC2D0)) / 0x32C), arg1);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15022398 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022398.s")
void func_1502178C(void *, s32, s32);
void *func_15083E90(u8);
extern s32 D_800C35D0;
extern void *D_800C35C8[];
extern void *D_800C35F0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15022528 CURRENT (1757) */
void func_15022528(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    u8 *temp_s4;
    void *temp_v0;
    void *temp_v0_2;

    temp_s4 = &D_800C363A[arg0];
    var_s0 = 0;
    if ((s32)*temp_s4 > 0) {
        var_s1 = 0;
        do {
            if ((*(u16 *)((u8 *)*(void **)((u8 *)&D_800C35D0 + (arg0 * 4)) + var_s1) != 0) &&
                (*(u16 *)((u8 *)D_800C35C8[arg0] + var_s1) != 0)) {
                temp_v0 = (void *)((u8 *)D_800C35F0[arg0] + (var_s0 * 8));
                if (*(u16 *)((u8 *)temp_v0 + 0) == 2) {
                    temp_v0_2 = func_15083E90(*(u8 *)((u8 *)temp_v0 + 2));
                    if (temp_v0_2 != 0) {
                        func_1502178C(temp_v0_2, arg0, var_s0);
                    }
                }
            }
            var_s0 += 1;
            var_s1 += 2;
        } while (var_s0 < (s32)*temp_s4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15022528 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022528.s")

extern u8 D_800C3550[][0x1E];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15022640 CURRENT (2155) */
void func_15022640(s32 arg0, s32 arg1) {
    s32 i;
    u8 *count_ptr;
    u8 *entry;
    u8 count;

    count_ptr = &D_800C354A[arg1];
    count = *count_ptr;
    i = 0;
    if ((s32)count > 0) {
        entry = (arg1 * 0x1E) + &D_800C3550[0][0];
loop:
        i++;
        if (arg0 != *entry) {
            entry++;
            if (i >= (s32)count) {
                goto append;
            }
            goto loop;
        }
    } else {
append:
        *(&D_800C3550[0][0] + ((arg1 * 0x1E) + count)) = arg0;
        *count_ptr = count + 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15022640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022640.s")

void *func_151149AC(u8);
void func_15022640(s32, s32);

void func_150226BC(s32 arg0, s32 arg1) {
    void *temp_v0;
    void *sp1C;
    void *temp_v1;

    if (*(u16 *)((u8 *)D_800C35C8[arg1] + (arg0 * 2)) != 0) {
        temp_v1 = (void *)((u8 *)D_800C35F0[arg1] + (arg0 * 8));
        if (*(u16 *)((u8 *)temp_v1 + 0) == 3) {
            temp_v0 = func_151149AC(*(u8 *)((u8 *)temp_v1 + 2));
            if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x6E) == 1)) {
                sp1C = temp_v0;
                func_15022640(*(u8 *)((u8 *)temp_v0 + 0x72), arg1);
                *(s8 *)((u8 *)sp1C + 0x6E) = 0;
            }
        }
    }
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150227BC CURRENT (120) */
void func_150227BC(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;
    u8 *var_s1;

    temp_s2 = &D_800C354A[arg0];
    var_s0 = 0;
    if ((s32)*temp_s2 > 0) {
        var_s1 = D_800C3550[arg0];
        do {
            *(s8 *)((u8 *)func_151149AC(*var_s1) + 0x6E) = 1;
            var_s0 += 1;
            var_s1 += 1;
        } while (var_s0 < (s32)*temp_s2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150227BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150227BC.s")
void func_15022398(s32, s32);
extern u8 D_800C35EA[];
extern s8 D_800C3638;

void func_15022848(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;

    if (D_800C35EA[arg0] == 1) {
        D_800C3638 = 0;
        temp_s2 = &D_800C363A[arg0];
        var_s0 = 0;
        if ((s32)*temp_s2 > 0) {
            do {
                func_15022398(var_s0, arg0);
                func_150222E0(var_s0, arg0);
                var_s0 += 1;
            } while (var_s0 < (s32)*temp_s2);
        }
        D_800C3638 = 1;
    }
}
void func_15060F28(u8 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150228E4 CURRENT (1245) */
void func_150228E4(s32 arg0) {
    s32 var_s1;
    u8 *temp_a0;
    u8 *temp_s4;
    u8 *var_s0;

    temp_s4 = &D_800C3510[arg0];
    var_s1 = 0;
    if ((s32)*temp_s4 > 0) {
        var_s0 = (arg0 * 0x19) + D_800C3518;
        do {
            temp_a0 = (u8 *)&D_800CC2D0 + (*var_s0 * 0x32C);
            if (*(s32 *)temp_a0 != 0) {
                func_15060F28(temp_a0, 0);
            }
            var_s1 += 1;
            var_s0 += 1;
        } while (var_s1 < (s32)*temp_s4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150228E4 */
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
extern u8 D_800CBFDF;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150229E4 CURRENT (3455) */
s32 func_150229E4(void *arg0) {
    s32 var_a0;
    s32 var_v0;
    u8 temp_a1;
    u8 temp_a3;
    u8 var_a2;
    void *temp_v0;
    u8 *var_t0;

    var_v0 = 0;
    if (arg0 == 0) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (*D_800C35C8 == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 5) == 4) {
        var_v0 = 1;
    }
    temp_a1 = *(u8 *)((u8 *)arg0 + 0x65);
    if (temp_a1 != 0) {
        var_a2 = *(u8 *)((u8 *)&D_800CBFDF + (temp_a1 * 0x32C));
    } else {
        var_a2 = *(u8 *)((u8 *)arg0 + 0x3B);
    }
    temp_a3 = D_800C363A[var_v0];
    var_a0 = 0;
    if ((s32)temp_a3 > 0) {
        var_t0 = (u8 *)D_800C35C8[var_v0];
loop_13:
        if (*(u16 *)var_t0 != 0) {
            temp_v0 = (void *)((u8 *)D_800C35F0[var_v0] + (var_a0 * 8));
            if ((*(u16 *)((u8 *)temp_v0 + 0) == 2) &&
                (var_a2 == *(u8 *)((u8 *)temp_v0 + 2))) {
                if (temp_a1 == 0) {
                    return 1;
                }
                return 2;
            }
        }
        var_a0 += 1;
        var_t0 += 2;
        if (var_a0 < (s32)temp_a3) {
            goto loop_13;
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150229E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150229E4.s")
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15022B08 CURRENT (995) */
s32 func_15022B08(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 temp_v1;
    void *var_a2;

    temp_v1 = D_800C363A[arg1];
    var_v0 = 0;
    if ((s32)temp_v1 > 0) {
        var_a2 = D_800C35C8[arg1];
loop_2:
        if ((*(u16 *)var_a2 != 0) &&
            (*(u8 *)((u8 *)D_800C35F0[arg1] + (var_v0 * 8) + 2) ==
             *(u8 *)((u8 *)(D_800DBEF4 + (arg0 * 0xA0)) + 0x72))) {
            return 1;
        }
        var_v0 += 1;
        var_a2 = (void *)((u8 *)var_a2 + 2);
        if (var_v0 < (s32)temp_v1) {
            goto loop_2;
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15022B08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_15022BA4.s")
s32 func_15023BB0(u32, s32, s32, void **, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_800C3688[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15023264 CURRENT (1846) */
s16 func_15023264(s32 arg0, s32 arg1) {
    void *sp6C;
    s16 var_s6;
    void **var_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s2;
    u8 *temp_s3;
    u8 *var_v0;

    temp_s3 = &D_800C363A[arg0];
    var_s6 = -1;
    var_s2 = 0x1869F;
    var_s0 = 0;
    if ((s32)*temp_s3 > 0) {
        var_s1 = (void **)(D_800C3688 + (arg0 * 0x78));
        do {
            temp_v0 = (s32)*var_s1;
            if (temp_v0 != 0) {
                sp6C = 0;
                temp_v0_2 = func_15023BB0((u32)(temp_v0 + 0x18), 3, var_s0, &sp6C, 0, 0, 0, 0, 0, 0, arg0);
                if ((sp6C != 0) && (temp_v0_2 < var_s2)) {
                    var_s2 = temp_v0_2;
                    var_s6 = *(s16 *)((u8 *)sp6C + 2);
                }
            }
            var_s0 += 1;
            var_s1 += 1;
        } while (var_s0 < (s32)*temp_s3);
    }
    if (var_s6 == -1) {
        var_s6 = 0;
        var_s0 = 0;
        if ((s32)*temp_s3 > 0) {
            var_v0 = (u8 *)D_800C35F0[arg0];
            do {
                if (*(u16 *)var_v0 == 1) {
                    var_s6 = var_s0;
                } else {
                    var_s0 += 1;
                    var_v0 += 8;
                    if (var_s0 < (s32)*temp_s3) {
                        continue;
                    }
                }
                break;
            } while (1);
        }
    }
    return var_s6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15023264 */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150234A4 CURRENT (1770) */
Game49D30Record *func_150234A4(s32 arg0, s32 arg1) {
    u8 *var_a2;
    u8 *var_t0;
    u8 *var_t1;
    s16 temp_v0;
    s32 var_a3;

    var_a3 = arg0 + 1;
    var_t1 = 0;
    var_t0 = 0;
    var_a2 = &D_800C3CA0;
    do {
        temp_v0 = *(s16 *)var_a2;
        if (var_a3 == temp_v0) {
            if ((arg1 != 0) && (*(u8 *)(var_a2 + 0xC) != 0)) {
                arg0 = var_a3;
                func_15023440((Game49D30Record *)&D_800C3CA0, 1);
                var_a3 = arg0;
                var_t0 = &D_800C3CA0;
                var_t1 = 0;
            } else {
                var_t1 = var_a2;
            }
        } else if (temp_v0 == 0) {
            var_t0 = var_a2;
            if ((arg1 != 0) && (*(u8 *)(var_a2 + 0xC) != 0)) {
                arg0 = var_a3;
                func_15023440((Game49D30Record *)var_a2, 1);
                var_a3 = arg0;
                var_t1 = 0;
            }
        } else {
            var_a2 += 0x38;
            if (var_a2 != &D_800C3D48) {
                continue;
            }
        }
        break;
    } while (1);
    if (var_a2 == &D_800C3D48) {
        arg0 = var_a3;
        func_15023440((Game49D30Record *)&D_800C3CA0, 1);
        var_a3 = arg0;
        var_t0 = &D_800C3CA0;
    }
    if (var_t1 != 0) {
        return (Game49D30Record *)var_t1;
    }
    if (var_t0 != 0) {
        *(s16 *)var_t0 = (s16)var_a3;
    }
    return (Game49D30Record *)var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150234A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150234A4.s")
typedef struct Game49D30Inner235DC {
    f32 field0;
    u8 pad4[0x1C];
    u8 field20;
    u8 pad21[2];
    u8 field23;
} Game49D30Inner235DC;

typedef struct Game49D30Actor235DC {
    u8 pad0[0x18];
    f32 field18;
    u8 pad1C[4];
    f32 field20;
    f32 field24;
    f32 field28;
    u8 pad2C[0x10];
    f32 field3C;
    u8 pad40[0x14];
    f32 field54;
    u8 pad58[0x29];
    s8 field81;
    u8 pad82[1];
    s8 field83;
    u8 pad84[5];
    s8 field89;
    s8 field8A;
    u8 pad8B[0x22];
    s8 fieldAD;
    u8 padAE[4];
    s16 fieldB2;
    u8 padB4[0x18];
    s16 fieldCC;
    u8 padCE[2];
    s8 fieldD0;
    u8 padD1[0x33];
    s8 field104;
    u8 pad105[0x13];
    f32 field118;
    u8 pad11C[0x64];
    f32 field180;
    u8 pad184[0x22];
    s16 field1A6;
    u8 pad1A8[0x24];
    f32 field1CC;
    u8 pad1D0[0xA6];
    s8 field276;
    u8 pad277[1];
    s16 field278;
    u8 pad27A[8];
    s16 field282;
    s8 field284;
    s8 field285;
    s8 field286;
    s8 field287;
    u8 pad288[0x94];
    Game49D30Inner235DC *field31C;
} Game49D30Actor235DC;

void func_1507F640(void);
void *func_15083E90(u8);
void *func_1508F060(void *, u8 *);
extern f32 D_80096A1C;
extern u8 D_800C35AA;
extern s8 D_800C3E78;
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150235DC CURRENT (10) */
void func_150235DC(s32 arg0) {
    Game49D30Actor235DC *temp_v0;
    Game49D30Inner235DC *temp_a0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    s8 temp_v0_2;

    *(s32 *)((u8 *)&D_800CC2D0 + 0x25C) &= ~0x200;
    if (D_800C35AA == 0) {
        temp_v0 = (Game49D30Actor235DC *)func_15083E90(1);
        if (temp_v0 != 0) {
            D_800C3E78 = (s8)(((u8 *)temp_v0 - &D_800CC2D0) / 0x32C);
            temp_a0 = temp_v0->field31C;
            temp_v0->field3C = 0.0f;
            if (temp_a0 != 0) {
                temp_a0->field0 = 0.0f;
            }
            temp_v0->field54 = 0.0f;
            temp_v0->fieldCC = 0;
            temp_v0->fieldD0 = 0;
            if ((D_80096A1C != (temp_fv0 = temp_v0->field118)) && (temp_v0->field18 < temp_fv0)) {
                temp_v0->fieldAD = 1;
                temp_v0->field20 = 0.0f;
                temp_v0->field24 = 0.0f;
                if (((temp_fv0 - 50.0f) < (f32)temp_v0->field1A6) || (temp_v0->field31C->field20 & 1)) {
                    temp_v0->fieldB2 = 0;
                    func_1508F060(temp_a0, &D_800CC2D0);
                }
            } else {
                temp_fv0_2 = temp_v0->field180;
                temp_v0->fieldAD = 0;
                temp_v0->fieldB2 = 0;
                temp_v0->field20 = -4.0f;
                temp_v0->field18 = temp_fv0_2;
                temp_v0->field1CC = temp_fv0_2;
                temp_v0->field24 = 5.0f;
            }
            temp_v0->field81 = 0;
            temp_v0->field83 = 0;
            temp_v0->field89 = 0;
            temp_v0->field8A = 0;
            temp_v0->field104 = 0;
            temp_v0->field28 = temp_v0->field18 - temp_v0->field180;
            D_800D154C = temp_v0;
            func_1507F640();
            temp_v0->field31C->field23 = 0;
            temp_v0->field287 = 0;
            temp_v0_2 = temp_v0->field287;
            temp_v0->field276 = 0;
            temp_v0->field282 = 0;
            temp_v0->field278 = 0;
            temp_v0->field286 = temp_v0_2;
            temp_v0->field285 = temp_v0_2;
            temp_v0->field284 = temp_v0_2;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150235DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_150235DC.s")
void func_1504A730(void);
void func_15061B4C(void);
void func_1507E73C(s32 *);
void func_1507FEA0(s32 *);
void func_150627D4(void *);
s32 func_150229E4(void *);
extern u8 D_800C3654;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502378C CURRENT (460) */
void func_1502378C(void) {
    u8 *var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;

    var_s0 = &D_800CC2D0;
    var_s1 = 0;
    if (D_800C3654 != 0) {
        func_1504A730();
        return;
    }
    var_s4 = 1;
    var_s2 = 0x19;
    do {
        if (*(s32 *)var_s0 != 0) {
            D_800C3E78 = var_s1;
            func_15022998((s32 *)var_s0);
            func_1507E73C((s32 *)var_s0);
            if (func_150229E4(var_s0) != 0) {
                func_1502178C(var_s0, 0, -1);
                func_150627D4(var_s0);
                func_1507FEA0((s32 *)var_s0);
                *(s8 *)(var_s0 + 0x2FF) = var_s4;
            }
        }
        var_s1 += 1;
        var_s0 += 0x32C;
    } while (var_s1 != var_s2);
    func_15061B4C();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502378C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_49D30/func_1502378C.s")
