#include "types.h"

/*
 * Reviewed source unit: src/game/game_48FD0.c
 * Boundary evidence: docs/evidence/game_raw_controller_io_group.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501BB20
 * - func_1501BBB8
 * - func_1501C010
 * - func_1501C17C
 * - func_1501C1B0
 * - func_1501C57C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u64 func_10026968(s32, s32, s32, s32);
u64 func_10026868(u64, s32, s32);
void func_10024A40(void *, u64, s32, s32, void *, s32);
extern s32 D_8002BD10;
extern s32 D_8002BD14;
extern u8 D_80084064;
extern u8 D_8003B218[];
extern u8 D_800BE6E0[];
extern f32 D_80096960;
void func_1501C0F0(u8, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501BB20 CURRENT (1307) */
void func_1501BB20(void) {
    u64 temp_ret;

    if (D_80084064 != 0) {
        temp_ret = func_10026968(0, 0x19, D_8002BD10, D_8002BD14);
        temp_ret = func_10026868(temp_ret, 0, 0xF4240);
        func_10024A40(D_800BE6E0, temp_ret, 0, 0, D_8003B218, 6);
        D_80084064 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501BB20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BB20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BBB8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C010 CURRENT (1149) */
void func_1501C010(s32 arg0, s32 arg1) {
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_ft1;
    f32 var_fv1;
    s32 var_a1;
    s32 var_v0;

    arg0 &= 0xFF;
    arg1 &= 0xFF;
    var_a1 = arg1;
    var_v0 = var_a1;
    if (var_a1 >= 9) {
        var_a1 = 8;
        var_v0 = 8;
    }
    if (var_v0 == 8) {
        var_fv1 = 20.0f;
        var_fa0 = 0.0f;
    } else if (var_v0 == 0) {
        var_fv1 = 0.0f;
        var_fa0 = 99.0f;
    } else {
        var_ft1 = (f32)var_a1;
        if (var_a1 < 0) {
            var_ft1 += 4294967296.0f;
        }
        temp_fv0 = (var_ft1 - 1.0f) * D_80096960 * 5.0f;
        var_fv1 = temp_fv0 + 2.0f;
        var_fa0 = 7.0f - temp_fv0;
    }
    func_1501C0F0(arg0, var_fv1, var_fa0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C010.s")
extern u8 D_80084060[4];
extern u8 D_800BE93C[4];
extern u8 D_800BE944[4];
extern f32 D_800BE950[4];
extern f32 D_800BE960[4];
extern f32 D_800BE970[4];
extern f32 D_800BE980[4];

void func_1501C0F0(u8 arg0, f32 arg1, f32 arg2) {
    u8 temp_v0;

    temp_v0 = D_80084060[arg0];
    if ((temp_v0 < 4) && (D_800BE944[temp_v0] != 0)) {
        D_800BE93C[temp_v0] = 1;
        D_800BE950[temp_v0] = 0.0f;
        D_800BE960[temp_v0] = arg1;
        D_800BE970[temp_v0] = arg2;
        D_800BE980[temp_v0] = arg1 + arg2;
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C17C CURRENT (200) */
void func_1501C17C(s32 arg0) {

    arg0 = arg0 & 0xFF;
    {
        u8 temp_v0 = D_80084060[arg0];
    if ((s32)temp_v0 < 4) {
        D_800BE93C[temp_v0] = 0;
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C17C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C1B0.s")
void func_1501C17C(s32);

void func_1501C53C(void) {
    s32 temp_t6;
    s32 var_s0;

    var_s0 = 0;
    do {
        func_1501C17C(var_s0 & 0xFF);
        var_s0 += 1;
        temp_t6 = var_s0 & 0xFF;
    } while ((var_s0 = temp_t6) < 4);
}
void func_10004074(s32);
void func_150064E0(void);
void func_15007168(void);
s32 func_151DCFD8(s32);
void func_15006590(s8);
void func_15006BEC(s8);
void func_1500707C(s8);
void func_1500727C(void);
void func_15007360(void);
void func_15007440(void);
void func_15007558(void);
u8 func_151DD460(void *);
extern s8 D_80082BB4;
extern u8 D_80084068;
extern s8 D_800BE3EC;
extern s32 D_800BE3F0;
extern u8 D_800BE900;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C57C CURRENT (2320) */
void func_1501C57C(void) {
    s32 count;
    s8 action;
    u8 status;

    func_151DCFD8(0);
    action = D_80082BB4;
    if (action != 0) {
        status = D_80084068;
        if (status != 2) {
            D_80084068 = func_151DD460(&D_800BE900);
            status = *(volatile u8 *)&D_80084068;
            action = D_80082BB4;
        }
        if (status != 2) {
            switch (action) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                break;
            }
            count = 19;
            if (count > 0) {
                for (; count > 0; count--) {
                }
            }
            if (action == 1) {
                func_150064E0();
            } else if (action == 4) {
                func_15007168();
            }
            D_80082BB4 = 0;
            return;
        }
        switch (action) {
        case 1:
            func_15006590(D_800BE3EC);
            break;
        case 2:
            func_15006BEC(D_800BE3EC);
            break;
        case 3:
            func_1500707C(D_800BE3EC);
            break;
        case 4:
            func_1500727C();
            break;
        case 5:
            func_15007360();
            break;
        case 6:
            func_15007440();
            break;
        case 7:
            func_15007558();
            break;
        }
        D_80082BB4 = 0;
        if (D_800BE3F0 != 0) {
            func_10004074(D_800BE3F0 - 8);
            D_800BE3F0 = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C57C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C57C.s")
