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
 * - func_1514D9F4
 * - func_1514DA38
 * - func_1514DAA4
 * - func_1514DB18
 * - func_1514DB64
 * - func_1514DBB8
 * - func_1514DC5C
 * - func_1514DCAC
 * - func_1514DCF4
 * - func_1514DE94
 * - func_1514E00C
 * - func_1514E194
 * - func_1514E31C
 * - func_1514E508
 * - func_1514E5B8
 * - func_1514E668
 * - func_1514E718
 * - func_1514E7C8
 * - func_1514E850
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
 * - func_1514F130
 * - func_1514F194
 * - func_1514F308
 * - func_1514F3CC
 * - func_1514F44C
 * - func_1514F4A8
 * - func_1514F4D8
 * - func_1514F508
 * - func_1514F538
 * - func_1514F568
 * - func_1514F590
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514D9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DA38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DAA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DB18.s")
void func_1514DB58(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DB64.s")
void func_1514DB98(void) {
    func_1514F194();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DBB8.s")
/* Call context: func_1500EE18: raw o32 argument homes in asm/nonmatchings/game_3C230/func_1500EE18.s; pointer uses in entry block; caller discards result */
void func_1500EE18(void *, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_1514DC38(void *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DC5C.s")
void func_1514DC84(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 2;
}
void func_1514DC98(u8 *arg0) {
    *(u32 *)(arg0 + 0x94) |= 0x710;
}
s32 func_1514DCAC(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DCAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514DCF4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E7C8.s")
void func_1514E824(s32 arg0) {

}
void func_1516972C(void *arg0);

void func_1514E830(void *arg0) {
    func_1516972C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514E850.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EE70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514EECC.s")
void func_1514F110(void) {
    func_1514F194();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F130.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F194.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F308.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F3CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F44C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F4A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F4D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F508.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F538.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_179F30/func_1514F5CC.s")
