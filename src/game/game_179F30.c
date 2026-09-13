#include "types.h"

/*
 * Reviewed source unit: src/game/game_179F30.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514CA80
 * - func_1514D15C
 * - func_1514D310
 * - func_1514D3B0
 * - func_1514D4B8
 * - func_1514D564
 * - func_1514D64C
 * - func_1514D978
 * - func_1514DA38
 * - func_1514DAA4
 * - func_1514DBB8
 * - func_1514DE94
 * - func_1514E00C
 * - func_1514E194
 * - func_1514E31C
 * - func_1514E508
 * - func_1514E5B8
 * - func_1514E668
 * - func_1514E718
 * - func_1514E89C
 * - func_1514E920
 * - func_1514EA1C
 * - func_1514EBA4
 * - func_1514EC1C
 * - func_1514ECE0
 * - func_1514ED3C
 * - func_1514EDF0
 * - func_1514EE70
 * - func_1514EECC
 * - func_1514F194
 * - func_1514F308
 * - func_1514F3CC
 * - func_1514F5CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514CA80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D15C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D4B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D564.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D64C.s")
void func_1514D96C(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D978.s")
extern void func_1514D978(s32 arg0);
extern s32 func_151ACA60(s32 arg0, s32 arg1, s32 arg2);
extern void func_1514EC1C(s32 arg0, s32 arg1, s32 arg2);

void func_1514D9F4(s32 arg0) {
    func_1514D978(arg0);
    func_1514EC1C(func_151ACA60(arg0, 0x41A00000, 0), arg0, 0x14);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DA38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DAA4.s")
extern s32 func_15158BD0(s32 arg0, s32 arg1, s32 arg2);

void func_1514DB18(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_15158BD0(arg0, 1, 0);
    if (temp_v0 != 0) {
        func_1514EC1C(temp_v0, arg0, 0x13);
    }
}
void func_1514DB58(s32 arg0) {

}
void func_151B2060(void);
extern s32 D_800BE9F0;

void func_1514DB64(void) {
    if (D_800BE9F0 == 0x14) {
        func_151B2060();
    }
}
void func_1514DB98(void) {
    func_1514F194();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DBB8.s")
/* Call context: func_1500EE18: raw o32 argument homes in asm/nonmatchings/game_3C230/func_1500EE18.s; pointer uses in entry block; caller discards result */
void func_1500EE18(void *, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514DC38(void *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}
void func_151D0F60(void *, s32, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514DC5C(void *arg0) {
    func_151D0F60(arg0, 0, 0xFF, 1);
}
void func_1514DC84(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 2;
}
void func_1514DC98(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 0x710;
}
void func_1514DCAC();

void func_15083568(void *, s32, s32, s32);

void func_1514DCAC(arg0)
void *arg0;
{
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 0x3F800000, 0);
    func_15083568(arg0, 0x44, 0x3F800000, 0);
}
void func_15083568(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1514DCF4(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x94) = 1;
    }
    func_15083568(arg0, 0x17, 0x3F800000, 0);
}
void func_1514DD2C(void) {
    func_1514DCAC();
}
void func_1514DD4C(void) {
    func_1514DCAC();
}
void func_1514DD6C(void) {
    func_1514DCAC();
}
void func_1514DD8C(void) {
    func_1514DCAC();
}
void func_1514DDAC(void) {
    func_1514DCAC();
}
void func_1514DDCC(void) {
    func_1514DCAC();
}
void func_1514DDEC(void) {
    func_1514DCAC();
}
void func_1514DE0C(void) {
    func_1514DCAC();
}
void func_1514DE2C(s32 arg0) {

}
void func_1514DE38(s32 arg0) {

}
void func_1514DE44(s32 arg0) {

}
extern void *D_800D2E4C;

void func_1514DE50(void) {
    if (*(u8 *)((u8 *)D_800D2E4C + 0x11) & 8) {
        func_1514DCAC();
    }
}
void func_1514DE88(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DE94.s")
/* Call context: func_15083FB0: unique active project prototype */
u8 func_15083FB0(u8);

void func_1514DFD0(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x65) = (s8) (func_15083FB0(9U) + 1);
    *(u8 *)((u8 *)arg0 + 0x101) = (u8) (*(u8 *)((u8 *)arg0 + 0x101) | 0x34);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E00C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E31C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E5B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E718.s")
void *func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);
extern u8 D_800A5920;

void func_1514E7C8(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, &D_800A5920);
    func_1514EC1C((s32)temp_v0, arg0, 0xF);
}
void func_1514E824(s32 arg0) {

}
void func_1516972C(void *arg0);

void func_1514E830(void *arg0) {
    func_1516972C(arg0);
}
void func_1518E308(void *arg0);

void func_1514E850(void *arg0) {
    func_1518E308(arg0);
    func_1516972C(arg0);
}
void func_1515F10C(void);

void func_1514E87C(void) {
    func_1515F10C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E89C.s")
void func_1514E920(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E920.s")
void func_1514E9DC(void) {
    func_1514E920();
}
void func_1514E9FC(void) {
    func_1514E89C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EA1C.s")
void func_1514EB6C(void) {
    func_1514E89C();
}
s32 func_1514EB8C(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EBA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EC1C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514ECE0 CURRENT (920) */
s32 func_1514ECE0(void *arg0, s16 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    var_v0 = arg0;
    if (arg0 != 0) {
loop_1:
        if (arg1 == *(s16 *)((u8 *)var_v0 + 0x1C)) {
            var_v1 = 1;
        } else {
            var_v0 = *(void **)((u8 *)var_v0 + 0x14);
        }
        if ((var_v0 != 0) && (var_v1 == 0)) {
            goto loop_1;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514ECE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514ECE0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514ED3C CURRENT (920) */
s32 func_1514ED3C(void *arg0, s32 arg1, void **arg2) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    var_v0 = arg0;
    if (arg0 != 0) {
loop_1:
        if (arg1 == *(s32 *)((u8 *)var_v0 + 0x10)) {
            var_v1 = 1;
        } else {
            var_v0 = *(void **)((u8 *)var_v0 + 0x14);
        }
        if ((var_v0 != 0) && (var_v1 == 0)) {
            goto loop_1;
        }
    }
    if (arg2 != 0) {
        *arg2 = var_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514ED3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514ED3C.s")
s32 func_1514ED8C(void *arg0, void *arg1) {
    s32 sp1C;
    void *temp_v0;
    void *temp_v0_2;

    if (arg0 == *(void **)((u8 *)arg1 + 0x2F4)) {
        *(void **)((u8 *)arg1 + 0x2F4) = (void *) *(void **)((u8 *)arg0 + 0x14);
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x14);
    if (temp_v0 != 0) {
        *(void **)((u8 *)temp_v0 + 0x18) = (void *) *(void **)((u8 *)arg0 + 0x18);
    }
    temp_v0_2 = *(void **)((u8 *)arg0 + 0x18);
    if (temp_v0_2 != 0) {
        *(void **)((u8 *)temp_v0_2 + 0x14) = (void *) *(void **)((u8 *)arg0 + 0x14);
    }
    sp1C = *(s32 *)((u8 *)arg0 + 0x10);
    func_1516972C(arg0);
    return sp1C;
}
/* Call context: func_1514ED8C: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514EDF0 CURRENT (310) */
void func_1514EDF0(s32 arg0, void *arg1) {
    s32 temp_v0;
    void *var_s1;

    var_s1 = *(void **)((u8 *)arg1 + 0x2F4);
    {
        void * sp34 = 0;
    do {
        temp_v0 = func_1514ED3C(var_s1, arg0, &sp34);
        if (temp_v0 != 0) {
            var_s1 = *(void **)((u8 *)sp34 + 0x14);
            func_1514ED8C(sp34, arg1);
        }
    } while (temp_v0 & 0xFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514EDF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EDF0.s")
void *func_1515BE50(void *, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514EE70 CURRENT (185) */
void func_1514EE70(s32 arg0) {
    struct {
        void *field_0;
        u8 field_4;
        u8 field_5;
        s16 field_6;
    } sp20;
    void *temp_v0;

    sp20.field_0 = (void *)arg0;
    sp20.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    sp20.field_5 = 0;
    sp20.field_6 = 0x12C;
    temp_v0 = func_1515BE50(&sp20, 0, 0xFF, 1);
    func_1514EC1C((s32)temp_v0, arg0, 0x16);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514EE70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EE70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EECC.s")
void func_1514F110(void) {
    func_1514F194();
}
typedef struct {
    u8 pad_0[9];
    u8 field_9;
} Game179F30Mode;

typedef struct {
    u8 pad_0[0x14];
    Game179F30Mode *field_14;
} Game179F30ModeState;

s32 func_1514E89C(Game179F30ModeState *, s32, s32);

s32 func_1514F130(Game179F30ModeState *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
        case 0xD:
            arg0->field_14->field_9 = 0;
            break;
        case 0xE:
            arg0->field_14->field_9 = 1;
            break;
        default:
            return func_1514E89C(arg0, arg1, arg2);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F308.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F3CC.s")
extern u8 D_800A5988;

void func_1514F44C(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, &D_800A5988);
    func_1514EC1C((s32)temp_v0, arg0, 0xD);
}
void func_151D74B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1514F4A8(s32 arg0) {
    func_151D74B0(arg0, 1, -1, 0xFF, 1);
}
void func_1514F4D8(s32 arg0) {
    func_151D74B0(arg0, 2, 1, 0xFF, 1);
}
void func_1514F508(s32 arg0) {
    func_151D74B0(arg0, 3, 0, 0xFF, 1);
}
void func_1514F538(s32 arg0) {
    func_151D74B0(arg0, 4, -1, 0xFF, 1);
}
void func_150C4120(void *, s32, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514F568(void *arg0) {
    func_150C4120(arg0, -1, 0xFF, 1);
}
void func_1501175C(s32, s32, s32);
void func_15011A78(s32, s32, s32);

void func_1514F590(s32 arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F5CC.s")
