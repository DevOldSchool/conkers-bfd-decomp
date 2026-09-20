#include "types.h"

/*
 * Reviewed source unit: src/game/game_981E0.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AD30
 * - func_1506B100
 * - func_1506B3B8
 * - func_1506B520
 * - func_1506B634
 * - func_1506B740
 * - func_1506BC24
 * - func_1506BCC8
 * - func_1506BF5C
 * - func_1506C32C
 * - func_1506C460
 * - func_1506CE6C
 * - func_1506D2E8
 * - func_1506D4F4
 * - func_1506D584
 * - func_1506D6B4
 * - func_1506D74C
 * - func_1506D898
 * - func_1506D958
 * - func_1506DBA0
 * - func_1506DC10
 * - func_1506DE04
 * - func_1506DE84
 * - func_1506E0EC
 * - func_1506E2CC
 * - func_1506E46C
 * - func_1506EA98
 * - func_1506EBC0
 * - func_1506EEF4
 * - func_1506EF5C
 * - func_1506F1A8
 * - func_1506F54C
 * - func_1506FD30
 * - func_15070084
 * - func_150700B4
 * - func_150700E4
 * - func_15070114
 * - func_15070144
 * - func_150701C4
 * - func_150701F4
 * - func_15070300
 * - func_150707C8
 * - func_15070830
 * - func_15070898
 * - func_15070C40
 * - func_15070D24
 * - func_15070F60
 * - func_150717E0
 * - func_15071830
 * - func_150718E4
 * - func_15071A34
 * - func_15071B18
 * - func_15071D08
 * - func_15071D78
 * - func_15071FDC
 * - func_150721A4
 * - func_15072208
 * - func_150722F0
 * - func_15072420
 * - func_1507266C
 * - func_15072740
 * - func_150727F0
 * - func_15072B44
 * - func_15072F10
 * - func_15073118
 * - func_1507342C
 * - func_150738E8
 * - func_15073A50
 * - func_15073B38
 * - func_15073FA0
 * - func_150746F0
 * - func_150747E4
 * - func_1507488C
 * - func_1507490C
 * - func_15074980
 * - func_15074A94
 * - func_15074C80
 * - func_1507515C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")
/* Call context: func_1505E650: unique active project prototype */
void func_1505E650(u8 *, s32, s32, s32, f32, f32, s32);
extern u8 * D_800D154C;
void func_15060A9C(s32, u8 *);
s32 func_150ADA20();
extern f32 D_80099D50;
extern f32 D_80099C3C;
void func_1506B634(s32 arg0);

void func_1506AF74(void) {
    s32 var_v1;

    var_v1 = *(u8 *)((u8 *)D_800D154C + 0x100);
    if (var_v1 & 8) {
        *(u8 *)((u8 *)D_800D154C + 0x100) = (u8) (var_v1 | 4);
        var_v1 = *(u8 *)((u8 *)D_800D154C + 0x100);
    }
    *(u8 *)((u8 *)D_800D154C + 0x100) = (u8) (var_v1 & 0xF7);
    func_1505E650(D_800D154C, 0x38, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
extern u8 *D_800D154C;
extern s32 D_800CC2D0;
void func_1507D4F8(s32 arg0);
extern void func_1505E650(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

void func_1506AFE0(void) {
    func_1505E650(D_800D154C, 0x48, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B020(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1CB) = 1;
    func_1505E650(D_800D154C, 0x39, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
void func_1506B070(void) {

}
/* Call context: func_1506B100: unique active project prototype */
void func_1506B100(s32, f32, f32);
extern f32 D_80099C34;

void func_1506B078(void) {
    f32 temp_fv0;
    f32 var_fv0;

    temp_fv0 = (*(f32 *)((u8 *)D_800D154C + 0x18) - (*(f32 *)((u8 *)D_800D154C + 0x118) - 150.0f)) * D_80099C34;
    if (temp_fv0 < 0.0f) {
        temp_fv0 = 1.0f;
    } else {
        temp_fv0 += 1.0f;
    }
    func_1506B100(0xD1, temp_fv0, 4.0f);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B100 CURRENT (911) */
void func_1506B100(s32 arg0, f32 arg1, f32 arg2) {
    func_1505E650(D_800D154C, (s32)(u16)arg0, *(s32 *)&arg1, *(s32 *)&arg2, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B100 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B100.s")
/* Call context: func_1505E650: unique active project prototype */

void func_1506B14C(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, *(s32 *)((u8 *)D_800D154C + 0x4C), 0x40400000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B198(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, *(s32 *)((u8 *)D_800D154C + 0x4C), 0x40400000, 0.0f, 0.0f, 1);
}
void func_1506B1E8(void) {
    func_1505E650(D_800D154C, 0x3C, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_1506B228(void) {
    func_1505E650(D_800D154C, 0x54, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
/* Call context: func_1505E650: unique active project prototype */

void func_1506B268(void) {
    *(s8 *)((u8 *)D_800D154C + 0x83) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0;
    func_1505E650(D_800D154C, 0xF, 0x3F800000, 0x40C00000, 0.0f, 0.0f, 0);
}
typedef struct Game981E0ActorRecord {
    u8 pad0[0x218];
    s32 field_218;
    u8 pad21C[0x16];
    u8 field_232;
    u8 pad233[0x41];
    u8 field_274;
    u8 pad275[0xB7];
} Game981E0ActorRecord;

void *func_150721E8(void *);

void func_1506B2BC(void) {
    Game981E0ActorRecord *temp_v0;
    Game981E0ActorRecord *base;
    s32 index;

    temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        base = (Game981E0ActorRecord *)&D_800CC2D0;
        index = (temp_v0 - base) + 1;
        if (index == base->field_274) {
            ((Game981E0ActorRecord *)D_800D154C)->field_218 = 0;
            ((Game981E0ActorRecord *)D_800D154C)->field_232 = 4;
        }
    }
}
void func_1506B328(void) {
    func_1505E650(D_800D154C, 0x3E, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
}
void func_1506B368(void) {

}
void func_1506B370(void) {
    func_1507D4F8((D_800D154C - (u8 *)&D_800CC2D0) / 0x32C);
    return;
}
void func_1506B3B0(void) {
}
/* Call context: func_1505A630: unique active declaration in the allowed source */
s32 func_1505A630(f32, f32, s32);
extern u8 D_80099A3C;
extern u8 D_80099A3E;
extern u8 D_80099A43;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B3B8 CURRENT (1259) */
void func_1506B3B8(void) {
    u8 sp19;
    s16 temp_t0;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a0_2;
    u8 var_a0;

    sp19 = 0;
    var_a0 = sp19;
    temp_t0 = (*(u16 *)((u8 *)D_800D154C + 0x7A) + (*(u8 *)((u8 *)D_800D154C + 0x1FD) << 8)) - func_1505A630(*(f32 *)((u8 *)&D_800CC2D0 + 0x14) - *(f32 *)((u8 *)D_800D154C + 0x14), *(f32 *)((u8 *)D_800D154C + 0x1C) - *(f32 *)((u8 *)&D_800CC2D0 + 0x1C), 0);
    temp_v1 = temp_t0 >> 8;
    temp_a3 = temp_v1 & 0xFF;
    var_a2 = temp_v1 & 0xFF;
    if (temp_a3 & 0x80) {
        var_a2 = -temp_a3 & 0xFF;
    }
    if (var_a2 < (s32) D_80099A3C) {
        var_a0_2 = 1;
    } else {
        if ((s32) D_80099A43 < var_a2) {
            var_a0 = 5;
        } else if ((s32) D_80099A3E < var_a2) {
            var_a0 = 2;
        }
        if (temp_t0 < 0) {
            var_a0_2 = (var_a0 + 4) & 0xFF;
        } else {
            var_a0_2 = (var_a0 + 3) & 0xFF;
        }
    }
    *(s8 *)((u8 *)D_800D154C + 0x138) = 0;
    *(s16 *)((u8 *)D_800D154C + 0x244) = (s16) (&D_80099A3C)[var_a0_2];
    *(s16 *)((u8 *)D_800D154C + 0x21C) = 0x4E20;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B3B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
void func_1506B4EC(void) {
    func_1506B3B8();
}
extern s32 D_800D1580;
void func_15141A7C(u8 *arg0, s32 arg1);
void func_15192800(u8 *arg0, s32 arg1);
void func_1507C8E0(u8 *arg0, s32 arg1);
void func_1507F640(void);
void func_1512D748(void *arg0, s32 arg1, s32 arg2);

void func_1506B50C(void) {
    *(s16 *)(D_800D154C + 0x21C) = 0;
}
void func_1507CD64();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B520 CURRENT (530) */
void func_1506B520(void) {
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    void *temp_v0;

    var_a2 = 0x3FC00000;
    var_a3 = 0x40400000;
    if (*(u8 *)((u8 *)D_800D154C + 0x1CA) != 0) {
        temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
        if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x78) == 0x25)) {
            var_v0 = 0x1AB;
        } else {
            var_v0 = 0xF0;
        }
        func_1505E650(D_800D154C, var_v0 & 0xFFFF, var_a2, var_a3, 0.0f, 0.0f, 0);
        return;
    }
    func_1507CD64(D_800D154C, 1, var_a2, var_a3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B520.s")
void func_1506B5A4(void) {
}
void func_1506B5AC(void) {
}
void func_1506B5B4(void) {
    D_800D154C[0x1CB] = 1;
}
void func_1506B5CC(void) {
    D_800D154C[0x1CB] = 1;
}
void func_1506160C(u8 *, s32, s32, s32, u8);

void func_1506B5E4(void) {
    func_1506160C(D_800D154C, 2, 7, 8, 0U);
    *(f32 *)(D_800D154C + 0x4C) = 0.0f;
    *(f32 *)(*(u8 **)(D_800D154C + 0x2D0) + 0x10) = 0.0f;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B634.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506B740 CURRENT (520) */
void func_1506B740(void) {
    f32 temp_fv0;
    s32 var_a1;
    u8 temp_a0;
    u8 *temp_v0;

    var_a1 = func_150ADA20() & 0xFF;
    temp_fv0 = *(f32 *)((u8 *)D_800D154C + 0x118);
    if ((D_80099C3C != temp_fv0) &&
        (*(f32 *)((u8 *)D_800D154C + 0x18) < temp_fv0)) {
        *(s16 *)(*(u8 **)((u8 *)D_800D154C + 0x31C) + 0xE) = 0x2D0;
        return;
    }
    if (*(u16 *)((u8 *)D_800D154C + 0x84) == 0xA7) {
        temp_v0 = *(u8 **)((u8 *)D_800D154C + 0x31C);
        var_a1 = 0xFF;
        temp_a0 = temp_v0[0xC];
        if (temp_a0 == 0) {
            var_a1 = 0;
        } else {
            temp_v0[0xC] = temp_a0 - 1;
        }
    }
    if (var_a1 < 0x80) {
        func_1506B634(8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506B740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B740.s")
void func_1506B634(s32 arg0);

void func_1506B7F4(void) {
    D_800D154C[0x89] = 0;
    D_800D154C[0x83] = 0;
    func_1506B634(2);
}
void func_1506B82C(void) {
    *(u8 *)(D_800D154C + 0x89) = 0;
    *(u8 *)(D_800D154C + 0x83) = 0;
    func_1507F640();
}
void func_1506B100(s32 arg0, f32 arg1, f32 arg2);

void func_1506B860(void) {
    func_1506B100(0xB5, 0.63f, 5.0f);
}
void func_1506B88C(void) {
    func_1506B100(0xB6, 1.0f, 4.0f);
}
void func_1506B8B4(void) {
    *(u8 *)(*(u8 **)(D_800D154C + 0x31C) + 0x78) = 0;
    *(u8 *)(D_800D154C + 0x89) = 0;
    *(u8 *)(D_800D154C + 0x83) = 0;
    func_1507F640();
}
void func_1506B8F4(void) {
    func_1506B100(0xDE, 0.75f, 4.0f);
}
void func_1506B91C(void) {
    func_1506B100(0xBF, 1.0f, 4.0f);
}
/* Call context: func_1506B100: unique active project prototype */

void func_1506B944(void) {
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x83) = 0;
    func_1506B100(0xC5, 1.0f, 4.0f);
}
void func_1506B984(void) {
    func_1506B100(0xAF, 1.0f, 4.0f);
}
void func_1506B9AC(void) {
    *(s16 *)(D_800D154C + 0x244) = 0;
}
extern u16 D_800BE720[];
extern u8 D_800C3E78;
extern u8 D_800D1940;
extern u8 D_800D2E60[];

void func_1506B9C0(void) {
    u16 *temp_v0;
    u8 *temp_v1;
    u8 *temp_a0;
    s32 temp_d1940;

    temp_v0 = &D_800BE720[D_800C3E78];
    *temp_v0 |= 0x4000;
    temp_a0 = *(u8 **)((u8 *)D_800D154C + 0x31C);
    if (temp_a0 != 0) {
        *(s8 *)((u8 *)temp_a0 + 0x78) = 0;
        temp_v1 = D_800D2E60;
        temp_d1940 = D_800D1940;
        temp_v1 += temp_d1940 >> 3;
        *temp_v1 |= 1 << (temp_d1940 & 7);
    }
    func_1507F640();
}
void func_10010154(s32, u8 *, s32, s32, s32);
void func_100109D0(s32);

void func_1506BA4C(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_100109D0((s32) D_800D154C);
        return;
    }
    if (*(s32 *)((u8 *)D_800D154C + 0x318) == 0) {
        func_10010154(D_800D1580 & 0xFFFF, D_800D154C, 0x6D60, (s32) (s16) arg0, arg1);
        return;
    }
    func_10010154(D_800D1580 & 0xFFFF, D_800D154C, 0x5DC0, 0x1F4, 0x9C4);
}
void func_10010A3C(s32);
s32 func_10010344(s32, u8 *, u32, s16, s32);

void func_1506BAD8(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_10010A3C((s32) D_800D154C);
        return;
    }
    if (*(s32 *)((u8 *)D_800D154C + 0x318) == 0) {
        func_10010344(D_800D1580 & 0xFFFF, D_800D154C, 0x6D60U, (s16) arg0, arg1);
        return;
    }
    func_10010344(D_800D1580 & 0xFFFF, D_800D154C, 0x5DC0U, 0x1F4, 0x9C4);
}
extern u16 D_800D1582;
extern void func_10012718(u16 arg0, u8 *arg1, s32 arg2, s16 arg3, s32 arg4);
void func_1506BB64(s32 arg0, s32 arg1) {
    func_10012718(D_800D1582, D_800D154C, 0x6D60, (s16) arg0, arg1);
}
/* Call context: func_10010154: unique active project prototype */
void func_10010154(s32, u8 *, s32, s32, s32);
void func_1506BBA8(s32, s32);

void func_1506BBA8(s32 arg0, s32 arg1) {
    u8 *sp24;

    sp24 = D_800D154C;
    if (*(s32 *)(sp24 + 0x318) == 0) {
        func_10010154((s32) D_800D1582, sp24, 0x36B0, (s32) (s16) arg0, arg1);
        return;
    }
    func_10010154((s32) D_800D1582, sp24, 0x2EE0, 0x1F4, 0x9C4);
}
/* Call context: func_10010344: unique active project prototype */
s32 func_10010344(s32, u8 *, u32, s16, s32);
extern u16 D_800D1582;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506BC24 CURRENT (1270) */
void func_1506BC24(s16 arg0, s32 arg1) {
    u8 *sp24;

    sp24 = D_800D154C;
    if (*(s32 *)((u8 *)D_800D154C + 0x318) == 0) {
        func_10010344((s32) D_800D1582, D_800D154C, 0x36B0U, arg0, arg1);
        return;
    }
    func_10010344((s32) D_800D1582, sp24, 0x2EE0U, 0x1F4, 0x9C4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506BC24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BC24.s")
void func_1506BCA0(void) {
    *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) D_800D1580;
}
s32 func_151EF610(u8 **);                           /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506BCC8 CURRENT (570) */
void func_1506BCC8(void) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft1;
    u8 *temp_v1;

    temp_v1 = D_800D154C;
    if (*(s32 *)((u8 *)temp_v1 + 0) == 0x16) {
        if (*(f32 *)((u8 *)temp_v1 + 0x180) == *(f32 *)((u8 *)temp_v1 + 0x18)) {
            *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) ((func_151EF610(&D_800D154C) % 8) + D_800D1580);
            temp_fv0 = *(f32 *)((u8 *)D_800D154C + 0x3C);
            if (temp_fv0 != 0.0f) {
                var_ft1 = *(f32 *)((u8 *)D_800D154C + 0x20) * (temp_fv0 / 40.0f);
                goto block_8;
            }
            *(f32 *)((u8 *)D_800D154C + 0x20) = 0.0f;
        }
    } else {
        temp_fv0_2 = *(f32 *)((u8 *)temp_v1 + 0x18) - *(f32 *)((u8 *)temp_v1 + 0x180);
        if ((temp_fv0_2 > -5.0f) && (temp_fv0_2 < 5.0f)) {
            var_ft1 = (f32) D_800D1580;
block_8:
            *(f32 *)((u8 *)temp_v1 + 0x20) = var_ft1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506BCC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BCC8.s")
extern f32 D_80099C40;

void func_1506BDE8(void) {
    if (*(f32 *)((u8 *)D_800D154C + 0x18) < D_80099C40) {
        *(f32 *)((u8 *)D_800D154C + 0x20) = (f32) D_800D1580;
    }
}
void func_1506BE2C(void) {
    *(f32 *)((u8 *)D_800D154C + 0x24) = (f32) D_800D1580;
}
extern f32 D_80099C44;

void func_1506BE54(void) {
    *(f32 *)((u8 *)D_800D154C + 0x24) = (f32) ((f32) D_800D1580 * D_80099C44);
}
void func_1506BE84(void) {
    D_800D154C[0x89] = 0;
}
void func_1506BE98(void) {
    *(f32 *)((u8 *)D_800D154C + 0xC0) = (f32) D_800D1580;
}
void func_1506BEC0(void) {
    D_800D154C[0x89] = (s8)D_800D1580;
}
void func_1506BEDC(void) {
    *(s8 *)((u8 *)D_800D154C + 0xD0) = (s8) D_800D1580;
    *(f32 *)((u8 *)D_800D154C + 0x114) = (f32) ((s32) D_800D1580 >> 8);
}
extern void func_1506BF5C(void);

void func_1506BF1C(void) {
    if (*(f32 *)(D_800D154C + 0x118) <= *(f32 *)(D_800D154C + 0x18)) {
        func_1506BF5C();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF5C.s")
s32 func_1000F568(s32, s32);
extern s32 D_800D187C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506C32C CURRENT (645) */
void func_1506C32C(void) {
    s32 values[4];
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_a1;

    temp_t6 = D_800D187C - 1;
    if (D_800D187C != 0) {
        D_800D187C = temp_t6;
        values[0] = temp_t6 & 0x7FF;
        temp_t2 = ((s32) D_800D1580 >> 0x16) & 0x7FF;
        values[1] = D_800D1580 & 0x7FF;
        values[2] = ((s32) D_800D1580 >> 0xB) & 0x7FF;
        values[3] = temp_t2;
        if (temp_t2 != 0) {
            var_a1 = 4;
        } else if (values[2] != 0) {
            var_a1 = 3;
        } else {
            var_a1 = 0;
            if (values[1] != 0) {
                var_a1 = 2;
            }
        }
        if (var_a1 != 0) {
            var_a1 = func_1000F568(values[0], var_a1) - values[0];
        }
        temp_v0 = values[var_a1];
        if (temp_v0 != 0) {
            temp_t8 = D_800D187C & 0xFFFEF800;
            D_800D187C = temp_t8;
            D_800D1580 = temp_v0 | temp_t8;
            func_1506BF5C();
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506C32C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C32C.s")
void func_1506C418(void) {
    func_10010A3C((s32) D_800D154C);
}
void func_1506C43C(void) {
    func_100109D0((s32) D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506CE6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D2E8.s")
void func_1506D4EC(void) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506D4F4 CURRENT (370) */
void func_1506D4F4(void) {
    union {
        f32 f;
        s32 i;
    } temp;

    temp.f = 0.0f;
    func_1505E650(D_800D154C, *(u16 *)(D_800D154C + 0x84), 0x3C23D70A, temp.i, 0.0f, 0.0f, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506D4F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D4F4.s")
extern u8 D_800C35EA;
extern u8 D_800C3E78;

void func_1506D538(void) {
    if (D_800C35EA != 1) {
        func_1507D4F8(D_800C3E78);
    }
}
void func_1506D570(void) {
    D_800D154C[0x6E] = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D584.s")
extern f32 D_80099D4C;
void func_1506D584(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506D6B4 CURRENT (510) */
void func_1506D6B4(void) {
    f32 temp_fv0;
    s16 temp_v0;
    u8 temp_v0_2;
    s32 *temp_v1;
    s32 var_v0;

    temp_fv0 = *(f32 *)(D_800D154C + 0x118);
    if (temp_fv0 != D_80099D4C) {
        temp_v0 = *(s16 *)(D_800D154C + 0x1A6);
        temp_v1 = &D_800D1580;
        if (!(temp_fv0 < (f32)temp_v0)) {
            temp_v0_2 = *(u8 *)(D_800D154C + 0x1CA);
            var_v0 = 0x29;
            if ((s32)temp_v0_2 >= 2) {
                var_v0 = 0x2C;
            }
            *temp_v1 = (var_v0 << 24) | (*temp_v1 & 0xFFFF);
            func_1506D584();
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506D6B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D6B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D74C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506D898 CURRENT (320) */
void func_1506D898(void) {
    *(f32 *)(D_800D154C + 0x18) = (f32) (*(f32 *)(D_800D154C + 0x18) - 80.0f);
    func_1505E650(D_800D154C, 0x297, 0x3F800000, 0, 0.0f, 0.0f, 0);
    *(u8 *)(D_800D154C + 0x100) = (u8) (*(u8 *)(D_800D154C + 0x100) & 0xFFDF);
    *(u8 *)(D_800D154C + 0x83) = 0;
    *(u8 *)(D_800D154C + 0x89) = 0;
    *(u8 *)(*(u8 **)(D_800D154C + 0x31C) + 0x97) = 0;
    *(u8 *)(*(u8 **)(D_800D154C + 0x31C) + 0x44) = 0xC;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506D898 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D898.s")
void func_1506D934(void) {
    D_800D154C[0x103] = (s8)D_800D1580;
}
void func_1506D950(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D958.s")
void func_1506DA78(void) {
    D_800D154C[0x125] = (s8)D_800D1580;
}
/* Call context: func_15174690: unique active project prototype */
void func_15174690(u8, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1506DA94(void) {
    if ((D_800D1580 != 0) && (*(f32 *)((u8 *)D_800D154C + 0x44) > 20.0f) && (*(f32 *)((u8 *)D_800D154C + 0x3C) > 20.0f)) {
        *(s8 *)((u8 *)D_800D154C + 0x83) = 0;
    }
    func_15174690(D_800C3E78, 0, 0x18, 0, 0x199, 4, 0xAA, 0xFF, 0);
}
void func_15076760(void);
extern s8 D_800D1890;

void func_1506DB30(void) {
    D_800D1890 = (s8) D_800D1580;
    func_15076760();
}
void func_1506DB5C(void) {
    *(f32 *)((u8 *)D_800D154C + 0x3C) = (f32) D_800D1580;
}
void func_1506DB84(void) {
    D_800D154C[0x239] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506DBA0 CURRENT (50) */
void func_1506DBA0(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1E5) = (s8) D_800D1580;
    *(s8 *)((u8 *)D_800D154C + 0x1E6) = (s8) ((s32) D_800D1580 >> 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506DBA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DBA0.s")
void func_15054A5C(u8 *, void *);
void *func_15072208(void *, s32);

void func_1506DBD4(void) {
    void *temp_v0;

    temp_v0 = func_15072208(D_800D154C, 0);
    if (temp_v0 != 0) {
        func_15054A5C(temp_v0, D_800D154C);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506DC10 CURRENT (1700) */
void func_1506DC10(s32 arg0) {
    f32 temp_fv0;
    s32 temp_v1;
    s32 var_a0;
    u8 *temp_a1;

    var_a0 = arg0;
    temp_a1 = D_800D154C;
    temp_fv0 = *(f32 *)((u8 *)temp_a1 + 0x118);
    if (((temp_fv0 - 60.0f) < *(f32 *)((u8 *)temp_a1 + 0x18)) ||
        (var_a0 = 9, (D_80099D50 == temp_fv0))) {
        temp_v1 = func_150ADA20(var_a0, temp_a1) & 3;
        if (temp_v1 >= 2) {
            var_a0 = temp_v1 + 0x612;
        } else {
            var_a0 = temp_v1 + 0x8F;
        }
    }
    func_15060A9C(var_a0, temp_a1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506DC10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DC10.s")
void func_1506DCA4(void) {
    *(s32 *)(D_800D154C + 0x2E8) = D_800D1580;
}
void func_1506DCC0(void) {
    *(s32 *)(D_800D154C + 0x2EC) = D_800D1580;
}
void func_1506DCDC(void) {
    D_800D154C[0x1CA] = (s8)D_800D1580;
}
void func_1506DCF8(void) {
}
void func_1506DD00(void) {
    if (D_800D1580 == 0) {
        *(s32 *)(D_800D154C + 0xF8) = *(s32 *)(*(u8 **)(D_800D154C + 0x144) + 0x18);
        return;
    }
    *(s32 *)(D_800D154C + 0xF8) |= D_800D1580;
}
void func_1506DD44(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF8) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF8) & ~D_800D1580);
}
void func_1506DD6C(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x7D) = (s8) (D_800D1580 & 0x7F);
    }
    if (D_800D1580 == 0) {
        *(u16 *)((u8 *)D_800D154C + 0x76) = (u16) *(u16 *)((u8 *)D_800D154C + 0x7A);
    }
}
void func_1506DDB8(void) {
}
extern s32 D_800BE9F0;
extern u8 D_800C3E78;
extern s32 func_15178E50(s32 arg0);
extern void func_1516EED4(u8 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506DDC0(void) {
    if (func_15178E50(D_800BE9F0) != 0) {
        func_1516EED4(D_800C3E78, D_800D1580, 0xFF, 0);
    }
}
void func_15174690(u8, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506DE04 CURRENT (160) */
void func_1506DE04(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_15174690(D_800C3E78, 0xA, 0x12, 0xC, 0x199, 4, 0xAA, 0xFF, 0);
        var_s0 += 1;
    } while (var_s0 != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506DE04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")
extern void func_1506BA4C(s32 arg0, s32 arg1);
extern s32 func_1506E46C(u8 *arg0, s32 *arg1, s32 arg2);

void func_1506E5FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0x708);
    }
}
void func_1506E63C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x64, 0x320);
    }
}
void func_1506E67C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBE, 0x514);
    }
}
void func_1506E6BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x12C, 0xBB8);
    }
}
void func_1506E6FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0x2BC, 0xFA0);
    }
}
void func_1506E73C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(0xBB8, 0x1F40);
    }
}
extern void func_1506BBA8(s32 arg0, s32 arg1);

void func_1506E77C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(0x12C, 0x708);
    }
}
void func_1506E7BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(0x12C, 0xBB8);
    }
}
/* Call context: func_1506E5FC: unique active project prototype */

void func_1506E7FC(void) {
    if ((*(f32 *)((u8 *)D_800D154C + 0x28) == 0.0f) && (*(u8 *)((u8 *)D_800D154C + 0x107) == 0)) {
        func_1506E5FC();
    }
}
/* Call context: func_1506BA4C: unique active project prototype */
/* Call context: func_1506E46C: unique active project prototype */
s32 func_1000F4D8(u16);                             /* extern */

void func_1506E848(void) {
    if ((func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) && (func_1000F4D8(D_800D1582) == 0)) {
        func_1506BA4C(0x50, 0x320);
    }
}
extern void func_1506BB64(s32 arg0, s32 arg1);

void func_1506E898(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 2) != 0) {
        func_1506BB64(0x12C, 0x708);
    }
}
extern void func_1506BAD8(s32 arg0, s32 arg1);

void func_1506E8D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0x708);
    }
}
void func_1506E918(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x64, 0x320);
    }
}
void func_1506E958(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBE, 0x514);
    }
}
void func_1506E998(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x12C, 0xBB8);
    }
}
void func_1506E9D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0x2BC, 0xFA0);
    }
}
void func_1506EA18(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(0xBB8, 0x1F40);
    }
}
extern void func_1506BC24(s16 arg0, s32 arg1);

void func_1506EA58(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BC24(0x12C, 0xBB8);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EA98.s")
extern f32 D_80099DA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EBC0 CURRENT (615) */
void func_1506EBC0(void) {
    u8 temp_a0;
    void *temp_a0_2;

    temp_a0 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_a0 != 0) {
        temp_a0_2 = (((temp_a0 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        if ((s32) *(u8 *)((u8 *)temp_a0_2 + 0x13D) >= 0x64) {
            *(s8 *)((u8 *)temp_a0_2 + 0x65) = 0;
            *(u8 *)((u8 *)temp_a0_2 + 0x13D) = 0U;
            *(f32 *)((u8 *)temp_a0_2 + 0x3C) = 0.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x20) = 0.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x24) = 6.0f;
            *(f32 *)((u8 *)temp_a0_2 + 0x1CC) = (f32) D_80099DA4;
        }
        *(u8 *)((u8 *)D_800D154C + 0x13C) = 0U;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EBC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EBC0.s")
extern f32 D_80099DA8;
extern f32 D_800CC2E8;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_1506EC50(void) {
    if ((D_80099DA8 < *(f32 *)((u8 *)D_800D154C + 0x28)) && (!(D_800D1580 & 0x8000) || (D_800CC2E8 < *(f32 *)((u8 *)D_800D154C + 0x18)))) {
        D_800D1878 = (f32) (D_800D1580 & 0xFF);
        D_800D1880 = 0;
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) - 1);
    }
}
typedef struct Game981E0Flags {
    u8 pad0[4];
    u16 flags;
} Game981E0Flags;

void func_1506ECD0(void) {
    Game981E0Flags *entry = *(Game981E0Flags **)(D_800D154C + 0x2D0);

    entry->flags |= 0x8000;
}
void func_1506ECF0(void) {
    D_800D154C[0x3A] = (s8)D_800D1580;
}
void func_1506ED0C(void) {
    D_800D154C[0x83] = (s8) D_800D1580;
    D_800D154C[0x100] = (s8) (D_800D154C[0x100] | 0x10);
    (*(u8 **)(D_800D154C + 0x31C))[0x31] = 1;
}
void func_1506ED4C(void) {
    D_800D154C[0x100] = (s8)D_800D1580;
}
void func_1506ED68(void) {
    D_800D154C[0xA9] = 5;
    (*(u8 **)(D_800D154C + 0x31C))[0x31] = 0;
}
void func_1506ED90(void) {
    *(s16 *)(D_800D154C + 0x21C) = (s16)D_800D1580;
}
void func_1506EDAC(void) {
    *(s32 *)(D_800D154C + 0xF4) = D_800D1580;
}
void func_1506EDC8(void) {
    *(s32 *)((u8 *)D_800D154C + 0xF4) = (s32) (*(s32 *)((u8 *)D_800D154C + 0xF4) & ~D_800D1580);
}
void func_1506EDF0(void) {
    *(s32 *)(D_800D154C + 0xF4) |= D_800D1580;
}
void func_1506EE14(void) {
    *(s32 *)(D_800D154C + 0x25C) |= D_800D1580;
}
void func_1506EE38(void) {
    *(s32 *)((u8 *)D_800D154C + 0x25C) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x25C) & ~D_800D1580);
}
void func_15188810(u8 *arg0, s32 arg1, s32 arg2);
void func_15188A9C(s32 arg0);

void func_1506EE60(void) {
    if (D_800D1580 != 0) {
        func_15188810(D_800D154C, D_800D1580 & 0xFFFF, (s32)D_800D1580 >> 0x10);
        return;
    }
    func_15188A9C((s32)D_800D154C);
}
/* Call context: func_151898C0: unique active project prototype */
void func_151898C0(s32, s32);

void func_1506EEAC(void) {
    func_151898C0((s32) D_800D154C, D_800D1580);
}
void func_1506EED8(void) {
    D_800D154C[0x24E] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EEF4 CURRENT (120) */
void func_1506EEF4(void) {
    *(s8 *)((u8 *)D_800D154C + 0x276) = (s8) ((s32) D_800D1580 >> 0x10);
    *(s16 *)((u8 *)D_800D154C + 0x278) = (s16) (((s32) D_800D1580 >> 0x18) & 0xFF);
    *(s16 *)((u8 *)D_800D154C + 0x282) = (s16) D_800D1580;
    *(s8 *)((u8 *)D_800D154C + 0x284) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x285) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x286) = 0;
    *(s8 *)((u8 *)D_800D154C + 0x287) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EEF4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506EF5C CURRENT (1545) */
void func_1506EF5C(void) {
    s32 temp_t6;

    *(s16 *)((u8 *)D_800D154C + 0x282) = 0xFFFF;
    *(s8 *)((u8 *)D_800D154C + 0x276) = 5;
    temp_t6 = (((s32) D_800D1580 >> 0x10) & 0xFF) * 2;
    *(s8 *)((u8 *)(D_800D154C + temp_t6) + 0x284) = (s8) ((s32) D_800D1580 >> 8);
    *(s8 *)((u8 *)(temp_t6 + D_800D154C) + 0x285) = (s8) D_800D1580;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506EF5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")
void func_1506EFB4(void) {
    *(s16 *)(D_800D154C + 0x282) = 0;
}
void func_150BB760(u8 *);

void func_1506EFC8(s32 arg0) {
    if (D_800D154C[4] != 0x8C) {
        func_150BB760(D_800D154C);
    }
}
void func_150BCBBC(u8 *arg0);

void func_1506F004(s32 arg0) {
    func_150BCBBC(D_800D154C);
}
void func_150BA4C0(u8 *arg0, s32 arg1, s32 arg2);

void func_1506F02C(s32 arg0) {
    func_150BA4C0(D_800D154C, 0xFF, 0);
}
void func_151925C4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506F05C(s32 arg0) {
    func_151925C4(D_800D154C, 0x32, 0xFF, 1);
}
void func_1506F090(s32 arg0) {
    func_151925C4(D_800D154C, -1, 0xFF, 1);
}
void func_150C1260(u8 *arg0, s32 arg1);

void func_1506F0C4(s32 arg0) {
    func_150C1260(D_800D154C, 0);
}
void func_1506F0F0(s32 arg0) {
    func_150C1260(D_800D154C, 1);
}
void func_150BABE0(u8 *arg0, s32 arg1, s32 arg2);

void func_1506F11C(s32 arg0) {
    func_150BABE0(D_800D154C, 0, 0xFF);
}
void func_1506F14C(s32 arg0) {
    func_150BABE0(D_800D154C, 1, 0xFF);
}
void func_150AEEB0(u8 *arg0, s32 arg1);

void func_1506F17C(s32 arg0) {
    func_150AEEB0(D_800D154C, 0xFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F1A8.s")
void func_15197A7C(void *arg0);

void func_1506F524(s32 arg0) {
    func_15197A7C(D_800D154C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")
/* Call context: func_1519EF70: unique active project prototype */
void func_1519EF70(s32, s32, s32);

void func_1506F8C0(s32 arg0) {
    func_1519EF70((s32) D_800D154C, 0, 0);
}
f32 func_150ADA68(void);
void func_150E2EA4(s32, u8, u8, s32, f32, f32, f32, f32, f32, f32,
                   s32, s32, s32, f32, f32, s32, f32);
extern f32 D_80099E98;

void func_1506F8F0(s32 arg0) {
    register f32 random;

    random = func_150ADA68();
    arg0 = (s32)D_800D154C;
    func_150E2EA4(arg0, *(u8 *)(arg0 + 0x3B), 0x14, -1, 482.0f,
                  -127.0f, -45.0f, D_80099E98, -211.0f, -114.0f,
                  3, 3, 5, 20.0f, (random * 10.0f) + 40.0f,
                  0, 0.0f);
}
void func_1506F9C0(s32 arg0) {
    register f32 random;

    random = func_150ADA68();
    arg0 = (s32)D_800D154C;
    func_150E2EA4(arg0, *(u8 *)(arg0 + 0x3B), 0x14, -1, 241.0f,
                  -127.0f, -45.0f, 418.0f, -211.0f, -114.0f,
                  3, 3, 5, 20.0f, (random * 10.0f) + 40.0f,
                  0, 0.0f);
}
extern f32 D_80099E9C;

void func_1506FA90(s32 arg0) {
    register f32 random;

    random = func_150ADA68();
    arg0 = (s32)D_800D154C;
    func_150E2EA4(arg0, *(u8 *)(arg0 + 0x3B), 0x1A, -1, -181.0f,
                  -218.0f, -1.0f, D_80099E9C, -584.0f, -2.0f,
                  3, 3, 5, 20.0f, (random * 10.0f) + 40.0f,
                  0, 0.0f);
}
u8 func_151044F4(void);
void func_151C6A28(u8 *, s32, s32, s32);
void func_151C62D0(u8 *, s32, s32, s32, s32, s32, s32);

void func_1506FB60(s32 arg0) {
    if (func_151044F4() != 0) {
        func_151C6A28(D_800D154C, (arg0 - 0x13) & 0xFF, 0xFF, 0);
        return;
    }
    func_151C62D0(D_800D154C, (arg0 - 0x13) & 0xFF, 0, 0, -1, 0xFF, 0);
}
void func_151A0A10(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FBE8(s32 arg0) {
    func_151A0A10(D_800D154C, 0x46, 0xFF, 0);
}
void func_1506FC1C(s32 arg0) {
    func_151A0A10(D_800D154C, 0x28, 0xFF, 0);
}
void func_1506FC50(s32 arg0) {
    func_1519E688();
}
void func_1519E6BC(u8 *arg0);

void func_1506FC74(s32 arg0) {
    func_1519E6BC(D_800D154C);
}
void func_150B3AB0(u8 *arg0, s32 arg1);

void func_1506FC9C(s32 arg0) {
    func_150B3AB0(D_800D154C, 0xFF);
}
void func_15196438(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FCC8(s32 arg0) {
    func_15196438(D_800D154C, 6, 0xFF, 0);
}
void func_1506FCFC(s32 arg0) {
    func_15196438(D_800D154C, 5, 0xFF, 0);
}
void func_150E2EA4(s32, u8, u8, s32, f32, f32, f32, f32, f32, f32,
                   s32, s32, s32, f32, f32, s32, f32);
f32 func_150ADA68(void);
extern f32 D_80099EA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506FD30 CURRENT (1201) */
void func_1506FD30(s32 arg0) {
    func_150E2EA4(0, D_800D154C, *(u8 *)(D_800D154C + 0x3B), 1, -1,
                  0.0f, 0.0f, D_80099EA0, 0.0f, 0.0f, 414.0f,
                  3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f,
                  1, 50.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506FD30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506FD30.s")
void func_151AABC4(u8 *arg0, s32 arg1);

void func_1506FDF0(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}
void func_1506FE1C(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FE48(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FE74(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FEA0(s32 arg0) {
    func_151AABC4(D_800D154C, 2);
}
/* Call context: func_151AABC4: unique active project prototype */

void func_1506FECC(s32 arg0) {
    func_151AABC4(D_800D154C, 3);
}
/* Call context: func_151AB920: unique active project prototype */
void func_151AB920(s32, s32);

void func_1506FEF8(s32 arg0) {
    func_151AB920((s32) D_800D154C, 0);
}
/* Call context: func_151AB920: unique active project prototype */

void func_1506FF24(s32 arg0) {
    func_151AB920((s32) D_800D154C, 1);
}
void func_151AB930(u8 *arg0);

void func_1506FF50(s32 arg0) {
    func_151AB930(D_800D154C);
}
void func_150CBF80(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1506FF78(s32 arg0) {
    func_150CBF80(D_800D154C, 0, 1, 0xFF);
}
void func_1506FFAC(s32 arg0) {
    func_150CBF80(D_800D154C, 1, 1, 0xFF);
}
void func_1506FFE0(s32 arg0) {
    func_150CBF80(D_800D154C, 2, 1, 0xFF);
}
void func_150CA150(u8 *arg0);

void func_15070014(s32 arg0) {
    func_150CA150(D_800D154C);
}
extern void func_151B01B8(u8 *arg0, s32 arg1);
extern void func_151B09BC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1507003C(s32 arg0) {
    func_151B01B8(D_800D154C, 0);
    func_151B09BC(D_800D154C, 0, 0x3E8, 0xFF, 0);
}
void func_151AECA0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070084 CURRENT (100) */
void func_15070084(void) {
    func_151AECA0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070084.s")
void func_151B03B8(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150700B4 CURRENT (100) */
void func_150700B4(void) {
    func_151B03B8(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150700B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700B4.s")
void func_15193660(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150700E4 CURRENT (100) */
void func_150700E4(void) {
    func_15193660(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150700E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150700E4.s")
void func_151937F4(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070114 CURRENT (100) */
void func_15070114(void) {
    func_151937F4(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070114 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070114.s")
extern s32 D_800BE9F0;
void func_151C0698(u8 *, s32, s32 *, s32, s32, s32);
void func_151C1FB8(u8 *);
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070144 CURRENT (769) */
void func_15070144(s32 arg0) {
    s32 sp34;
    s32 sp30;
    u8 *sp2C;
    s32 sp28;
    s32 var_v0;

    sp2C = D_800D154C;
    sp28 = 1;
    sp30 = 0;
    sp34 = 0;
    if (D_800BE9F0 == 0x2B) {
        var_v0 = 3;
    } else {
        var_v0 = 0;
    }
    func_151C0698(sp2C, 0, &sp28, var_v0 & 0xFF, 0xFF, 1);
    func_151C1FB8(D_800D154C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070144 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070144.s")
void func_151C5280(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150701C4 CURRENT (100) */
void func_150701C4(void) {
    func_151C5280(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150701C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701C4.s")
void func_151C9740(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150701F4 CURRENT (100) */
void func_150701F4(void) {
    func_151C9740(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150701F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150701F4.s")
typedef struct {
    u8 type;
    s8 neg_one;
    s16 lifetime;
    s8 zero;
} Game981E0Descriptor;

s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15070224(s32 arg0) {
    Game981E0Descriptor descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.neg_one = -1;
    descriptor.lifetime = (func_150ADA20() % 5U) + 4;
    descriptor.zero = 0;
    position[0] = (s32)*(f32 *)(D_800D154C + 0x14);
    position[1] = (s32)*(f32 *)(D_800D154C + 0x18);
    position[2] = (s32)*(f32 *)(D_800D154C + 0x1C);
    func_151602C0((u8 *)&descriptor, position,
                  (func_150ADA20() % 3U) + 4,
                  0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")
void func_150EEE00(u8 *arg0, s32 arg1, s32 arg2);

void func_15070690(s32 arg0) {
    func_150EEE00(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}
void func_150EEF40(u8 *arg0, s32 arg1, s32 arg2);

void func_150706C4(s32 arg0) {
    func_150EEF40(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}
typedef struct {
    u8 pad_0[0x94];
    s32 flags_94;
} Game981E0ActionState;

void *func_150F03F8(Game981E0ActionState *, s32, s32, s32);

void func_150706F8(s32 arg0) {
    s32 var_v0;
    Game981E0ActionState *temp_a0;

    temp_a0 = (Game981E0ActionState *)D_800D154C;
    var_v0 = temp_a0->flags_94;
    if (!(var_v0 & 0x10)) {
        func_150F03F8(temp_a0, 0, 0xFF, 1);
        temp_a0 = (Game981E0ActionState *)D_800D154C;
        var_v0 = temp_a0->flags_94;
    }
    if (!(var_v0 & 8)) {
        func_150F03F8(temp_a0, 1, 0xFF, 1);
    }
}
void func_150EBEC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15070760(s32 arg0) {
    func_150EBEC0(D_800D154C, 0, 0xFF, 1);
}
void func_15070794(s32 arg0) {
    func_150EBEC0(D_800D154C, 1, 0xFF, 1);
}
void func_150FDDA0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150707C8 CURRENT (100) */
void func_150707C8(void) {
    func_150FDDA0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150707C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150707C8.s")
void func_150FDF38(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150707F8(s32 arg0) {
    func_150FDF38(D_800D154C, 0xFF, 1, 0, 0);
}
void func_150FE320(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070830 CURRENT (100) */
void func_15070830(void) {
    func_150FE320(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070830 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070830.s")
void func_150FE49C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15070860(s32 arg0) {
    func_150FE49C(D_800D154C, 0xFF, 1, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")
void func_15199834(void *arg0);

void func_15070C18(s32 arg0) {
    func_15199834(D_800D154C);
}
void func_15070C40(s32 arg0);

void func_15103E40(u8 *, u8 *, f32 *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15070C40 CURRENT (1500) */
void func_15070C40(s32 arg0) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    u8 *var_a0 = D_800D154C;
    u8 temp_v0;

    sp34 = *(f32 *)(D_800D154C + 0x14);
    sp38 = *(f32 *)(D_800D154C + 0x18);
    sp3C = *(f32 *)(D_800D154C + 0x1C);
    temp_v0 = *(u8 *)(D_800D154C + 0x124);
    if (temp_v0 != 0) {
        var_a0 = (u8 *)&D_800CC2D0 + (temp_v0 * 0x32C) - 0x32C;
    }
    func_15103E40(var_a0, D_800D154C, &sp34, arg0 & 0xFF, 0, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15070C40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070C40.s")
void func_15070CDC(s32 arg0) {
    func_15070C40(1);
}
void func_15070D00(s32 arg0) {
    func_15070C40(0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070D24.s")
void func_15070F60(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070F60.s")
void func_15071230(s32 arg0) {
    func_15070F60(0);
}
void func_15071254(s32 arg0) {
    func_15070F60(1);
}
void func_150FC438(u8 *arg0, s32 arg1, s32 arg2, u8 arg3);

void func_15071278(s32 arg0) {
    func_150FC438(D_800D154C, 0, 1, D_800D154C[0x85]);
}
void func_150FE860(u8 *, s32, s32);
void func_151D8868(s8 *, s32, s32, s32);

void func_150712AC(s32 arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } packet;

    func_150FE860(D_800D154C, 0xFF, 1);
    if (*(void **)((u8 *)D_800D154C + 0x318) != 0) {
        packet.field_0 = 1;
        packet.field_2 = (s16) ((func_150ADA20() % 7U) + 0xA);
        packet.field_5 = (s8) (1 << *(u8 *)((u8 *)*(void **)((u8 *)D_800D154C + 0x318) + 0x23D));
        packet.field_4 = (s8) ((func_150ADA20() % 7U) + 2);
        packet.field_6 = -1;
        func_151D8868(&packet.field_0, 0, 0xFF, 1);
    }
}
u8 func_151044F4(void);
void func_150FED30(u8 *, s32, s32);
void func_150FF084(u8 *, s32, s32);

void func_15071360(s32 arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } packet;

    if (func_151044F4() != 0) {
        func_150FF084(D_800D154C, 0xFF, 1);
    } else {
        func_150FED30(D_800D154C, 0xFF, 1);
    }
    if (*(void **)((u8 *)D_800D154C + 0x318) != 0) {
        packet.field_0 = 1;
        packet.field_2 = (s16)((func_150ADA20() % 5U) + 0xF);
        packet.field_5 = (s8)(1 << *(u8 *)((u8 *)*(void **)((u8 *)D_800D154C + 0x318) + 0x23D));
        packet.field_4 = (s8)((func_150ADA20() & 3) + 3);
        packet.field_6 = -1;
        func_151D8868(&packet.field_0, 0, 0xFF, 1);
    }
}
void func_150FF840(u8 *, s32, s32, s32, s32);

void func_15071434(s32 arg0) {
    func_150FF840(D_800D154C, 1, 0, 0xFF, 1);
}
void func_15071470(s32 arg0) {
    func_150FF840(D_800D154C, 0, 0, 0xFF, 1);
}
void func_150714AC(s32 arg0) {
    func_150FF840(D_800D154C, 0, 1, 0xFF, 1);
}
void func_151D5714(u8 *, void *, void *, u8, f32, s32, s32);
extern u8 D_80088BB0;
extern u8 D_800A2148;
extern u8 D_800A2154;

void func_150714E8(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A2148, &D_800A2154, D_80088BB0, 1.0f, 0xFF, 1);
}
extern void func_151D4668(void *arg0);
extern void func_151D469C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15071544(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 4, 0x78, 0xFF, 1);
}
void func_1507158C(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 2, 0x78, 0xFF, 1);
}
void func_150715D4(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 3, 0x78, 0xFF, 1);
}
void func_1507161C(s32 arg0) {

}
extern void func_151D0058(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15071628(s32 arg0) {
    func_151D0058(D_800D154C, (arg0 - 0x55) & 0xFF, 0xFF, 1);
}
void func_151D0024(u8 *arg0);

void func_15071668(s32 arg0) {
    func_151D0024(D_800D154C);
}
void func_150B60E0(void *, f32 *);
void func_150B5C38(f32 *, s32, s32);

void func_15071690(s32 arg0) {
    f32 sp1C[3];

    if ((*(s32 *)((u8 *)D_800D154C + 0x1D4) != 0) && ((*(u8 *)((u8 *)D_800D154C + 0x74) & 0xF) != 0xF)) {
        func_150B60E0(D_800D154C, &sp1C[0]);
        func_150B5C38(&sp1C[0], 0xFF, 1);
    }
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game981E0Position;

typedef struct {
    u8 pad0[0x14];
    Game981E0Position position;
} Game981E0PositionSource;

void func_151D5404(Game981E0Position *, s32, s32, s32, s32, s32, s32, s32);

void func_150716EC(s32 arg0) {
    Game981E0Position position;
    Game981E0PositionSource *source;

    source = (Game981E0PositionSource *)D_800D154C;
    position.x = source->position.x;
    position.y = source->position.y;
    position.z = source->position.z;
    func_151D5404(&position, 0x44BBC000, 0x453B8000, 0x39AEC33E, 0xC, 0xF, 0xFF, 0);
}
void *func_15083E90(u8);
void func_150F0BEC(void *);
void func_150F10D4(void *);
void func_15161E24(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15071764(s32 arg0) {
    void *object;

    object = func_15083E90(0x12);
    if (object != 0) {
        func_150F0BEC(object);
        func_150F10D4(object);
        func_15161E24(object, 1, 2, 0x12C, 0x46, 0xFF, 0x82, 0, 0xFF, 1);
    }
}

typedef struct {
    void *field_0;
    u8 field_4;
} Game981E0MenuInput;

void func_15131D4C(Game981E0MenuInput *, s32);
void func_151494E0(Game981E0MenuInput *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150717E0 CURRENT (300) */
void func_150717E0(s32 arg0) {
    Game981E0MenuInput sp20;
    Game981E0MenuInput *sp18;
    void *temp_v0;

    temp_v0 = func_15083E90(0x12U);
    if (temp_v0 != 0) {
        sp20.field_0 = temp_v0;
        sp18 = &sp20;
        sp20.field_4 = ((u8 *)temp_v0)[0x3B];
        func_15131D4C(sp18, 0x43);
        func_151494E0(sp18, 0x43);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150717E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150717E0.s")
void func_150F9BB0(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071830 CURRENT (100) */
void func_15071830(void) {
    func_150F9BB0(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071830 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071830.s")
void func_1519072C(u8 *arg0);

void func_15071860(s32 arg0) {
    func_1519072C(D_800D154C);
}
extern u8 D_80088B90;
extern f32 D_80099F30;
extern u8 D_800A1FB0;
extern u8 D_800A1FBC;

void func_15071888(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A1FB0, &D_800A1FBC, D_80088B90, D_80099F30, 0xFF, 1);
}
void func_15143134(f32 *, f32 *, s32);
void func_151C329C(f32 *, u8, s32);
extern s32 D_80099BB8;
extern f32 D_800A5480[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150718E4 CURRENT (738) */
void func_150718E4(s32 arg0) {
    struct {
        s32 seed;
        f32 vector;
        f32 value;
    } packet;
    u8 *base;

    packet.seed = D_80099BB8;
    base = D_800D154C;
    if ((*(s32 *)(base + 0x1D4) != 0) ||
        ((*(u8 *)(base + 0x74) & 0xF) == 0xF)) {
        func_15143134(&D_800A5480[0], &packet.vector,
                      (((u8 *)&packet.seed)[func_150ADA20() & 3] << 6) +
                      *(s32 *)(base + 0x1D4));
        packet.value = *(f32 *)(base + 0x180) + 20.0f;
        func_151C329C(&packet.vector, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150718E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150718E4.s")
void func_150FA520(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15071998(s32 arg0) {
    func_150FA520(D_800D154C, 0, 0xFF, 1);
}
void func_150719CC(s32 arg0) {
    func_150FA520(D_800D154C, 1, 0xFF, 1);
}
void func_15071A00(s32 arg0) {
    func_150FA520(D_800D154C, 2, 0xFF, 1);
}
void func_151D09A8(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071A34 CURRENT (100) */
void func_15071A34(void) {
    func_151D09A8(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071A34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071A34.s")
void func_1504715C(void *, void *);
void func_15143134(f32 *, f32 *, s32);
void func_151DC484(f32 *, void *, s32, s32, s32);
extern f32 D_80099BBC;

void func_15071A64(s32 arg0) {
    struct {
        u8 packet[0x24];
        f32 result;
        u8 pad[8];
    } locals;

    if (!(func_150ADA20() & 1) &&
        (*(s32 *)((u8 *)D_800D154C + 0x1D4) != 0) &&
        ((*(u8 *)((u8 *)D_800D154C + 0x74) & 0xF) != 0xF) &&
        (*(u8 *)((u8 *)&D_800CC2D0 + 0x104) != 0) &&
        (*(u8 *)((u8 *)&D_800CC2D0 + 0x1CA) > 0)) {
        func_1504715C(locals.packet, D_800D154C);
        func_15143134(&D_80099BBC, &locals.result,
                      *(s32 *)((u8 *)D_800D154C + 0x1D4) + 0x3C0);
        func_151DC484(&locals.result, locals.packet, 0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071B18.s")
void func_150F2230(u8 *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071D08 CURRENT (100) */
void func_15071D08(void) {
    func_150F2230(D_800D154C, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071D08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D08.s")
extern void (*D_80086150[])(s32);

void func_15071D38(void) {
    void (*temp_v0)(s32);

    temp_v0 = D_80086150[D_800D1580];
    if (temp_v0 != 0) {
        temp_v0(D_800D1580);
    }
}
/* Call context: func_15071D38: unique active project prototype */
/* Call context: func_150721E8: unique active project prototype */
void * func_150721E8(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071D78 CURRENT (325) */
void func_15071D78(void) {
    u8 *sp18;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        temp_t6 = D_800D154C;
        D_800D154C = temp_v0;
        sp18 = temp_t6;
        func_15071D38();
        D_800D154C = sp18;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071D78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071D78.s")
void func_15071DC8(void) {
    func_15141A7C(D_800D154C, D_800D1580);
}
void func_15071DF4(void) {
    func_15192800(D_800D154C, D_800D1580);
}
void func_15071E20(void) {
    D_800D154C[0x247] = (s8)D_800D1580;
}
void func_15071E3C(void) {
    D_800D154C[0x248] = (s8)D_800D1580;
}
/* Call context: func_1505E650: unique active project prototype */

void func_15071E58(void) {
    D_800D1878 = (f32) (D_800D1580 & 0xFF);
    *(u16 *)((u8 *)D_800D154C + 0x244) = (u16) (((s32) D_800D1580 >> 8) & 0xFF);
    func_1505E650(D_800D154C, (s32) *(u16 *)((u8 *)D_800D154C + 0x244), 0x3F99999A, 0x40400000, D_800D1878, 0.0f, 0);
}
void func_15071ED4(void) {
    func_1505E650(D_800D154C, 0x59, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_15071F14(void) {
    func_1505E650(D_800D154C, 0x24, 0x3F800000, 0x40400000, 0.0f, 0.0f, 0);
}
void func_15071F54(void) {
    func_1507C8E0(D_800D154C, D_800D1580);
}
extern u8 D_800C35EA;

void func_15071F80(void) {
    if (D_800C35EA == 1) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + 1);
    }
}
void func_15071FB0(void) {
    if (*(f32 *)((u8 *)D_800D154C + 0x28) == 0.0f) {
        *(s16 *)((u8 *)D_800D154C + 0x10C) = 0;
    }
}
/* Call context: func_1505E650: unique active project prototype */
extern f32 D_80099F48;
extern f32 D_800CC2F0;
extern f32 D_800CC2F4;
extern f32 D_800CC30C;
extern u16 D_800CC346;
extern s8 D_800CC351;
extern f32 D_800CC49C;
extern u8 D_800CC544;
extern void *D_800CC5E8;
extern void *D_800CC5EC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15071FDC CURRENT (3665) */
void func_15071FDC(void) {
    s32 sp2C;
    s32 *var_v1;
    s32 var_a2;
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t1 = 1;
    var_t0 = 0x194;
    if (D_800D1580 == 0) {
        var_a2 = -1;
        var_v1 = &D_800CC2D0;
        var_v0 = 0;
loop_2:
        if ((D_800C3E78 + 1) == *(u8 *)((u8 *)var_v1 + 0x65)) {
            var_a2 = var_v0;
        } else {
            var_v0 += 1;
            var_v1 += 0x32C;
            if (var_v0 != 0x19) {
                goto loop_2;
            }
        }
        if ((var_a2 + 1) == D_800CC544) {
            D_800CC346 = *(u16 *)((u8 *)D_800D154C + 0x76) + 0x8000;
            D_800CC49C = D_80099F48;
            goto block_13;
        }
    } else {
        if (*(s32 *)((u8 *)D_800D154C + 0x2E8) >= 0x71) {
            var_t0 = 0x2E5;
            *(f32 *)((u8 *)D_800D154C + 0x2E0) = 0.0f;
        } else {
            var_t0 = 0x32;
            D_800CC346 = *(u16 *)((u8 *)D_800D154C + 0x76);
            var_t1 = 0;
            if (*(u8 *)((u8 *)D_800D154C + 0x251) != 0) {
                D_800CC49C = D_800CC2E8 + 800.0f;
            }
        }
        *(s32 *)((u8 *)D_800D154C + 0x2E4) = 0x32;
block_13:
        D_800CC2F0 = *(f32 *)((u8 *)D_800D154C + 0x2D8);
        D_800CC2F4 = *(f32 *)((u8 *)D_800D154C + 0x2DC);
        sp2C = var_t1;
        D_800CC30C = *(f32 *)((u8 *)D_800D154C + 0x2E0);
        D_800CC351 = 1;
        func_1505E650((u8 *) &D_800CC2D0, var_t0 & 0xFFFF, 0x3F800000, 0x40000000, 6.0f, 0.0f, 0);
        *(s8 *)((u8 *)D_800CC5EC + 0x31) = (s8) var_t1;
        if (D_800CC5E8 != 0) {
            *(s32 *)((u8 *)D_800CC5E8 + 0x5F0) = (s32) (*(s32 *)((u8 *)D_800CC5E8 + 0x5F0) | 0x400);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15071FDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
extern void func_1506160C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150721A4 CURRENT (260) */
void func_150721A4(void) {
    s32 *temp_v0;
    s32 temp_v1;
    s32 temp_t6;
    s32 temp_t7;

    temp_v0 = &D_800D1580;
    temp_v1 = *temp_v0;
    temp_t6 = temp_v1 >> 8;
    temp_t7 = temp_v1 >> 0x10;
    func_1506160C(D_800D154C, temp_t7 & 0xFF, temp_v1 & 0xFF, temp_t6 & 0xFF, 0U);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150721A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150721A4.s")
void *func_15072208(void *arg0, s32 arg1);

void *func_150721E8(void *arg0) {
    return func_15072208(arg0, 0);
}
extern u8 D_800CC335;
extern s32 D_800CC5FC;
extern s32 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15072208 CURRENT (370) */
void *func_15072208(void *arg0, s32 arg1) {
    u8 *temp_a1;
    u8 *var_a1;
    s32 temp_v0;
    s32 var_v1;

    temp_a1 = (u8 *)&D_800CC2D0;
    temp_v0 = (((u8 *)arg0 - temp_a1) / 812) + 1;
    var_v1 = 0;
    if (temp_v0 == D_800CC335) {
        var_v1 = 1;
        if (arg1 == 0) {
            return temp_a1;
        }
    }
    var_a1 = (u8 *)&D_800CC5FC;
loop_4:
    if (temp_v0 == var_a1[0x65]) {
        if (var_v1 == arg1) {
            return var_a1;
        }
        var_v1 += 1;
        goto block_8;
    }
block_8:
    if (temp_v0 == var_a1[0x391]) {
        if (var_v1 == arg1) {
            return var_a1 + 0x32C;
        }
        var_v1 += 1;
        goto block_12;
    }
block_12:
    if (temp_v0 == var_a1[0x6BD]) {
        if (var_v1 == arg1) {
            return var_a1 + 0x658;
        }
        var_v1 += 1;
        goto block_16;
    }
block_16:
    if (temp_v0 == var_a1[0x9E9]) {
        if (var_v1 == arg1) {
            return var_a1 + 0x984;
        }
        var_v1 += 1;
        goto block_20;
    }
block_20:
    var_a1 += 0xCB0;
    if (var_a1 == (u8 *)&D_800D121C) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15072208 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072208.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150722F0 CURRENT (130) */
void func_150722F0(void) {
    u8 *temp_v0;

    temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        func_1506160C(temp_v0, 2, (D_800D1580 >> 8) & 0xFF, D_800D1580 & 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150722F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150722F0.s")
void func_1507233C(void) {
    *(s32 *)(D_800D154C + 0x94) = ~(D_800D1580 | 1);
}
void func_15072360(void) {
    *(s32 *)((u8 *)D_800D154C + 0x94) = (s32) (*(s32 *)((u8 *)D_800D154C + 0x94) & ~D_800D1580);
}
void func_15072388(void) {
    *(s32 *)(D_800D154C + 0x94) |= D_800D1580;
}
/* Call context: func_15060F28: unique active project prototype */
/* Call context: func_15083E90: unique active project prototype */
void func_15060F28(u8 *, s32);
void * func_15083E90(u8);
extern u8 D_800D1583;

void func_150723AC(void) {
    u8 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        func_15060F28(temp_v0, 0);
    }
}
/* Call context: func_15060F28: unique active project prototype */
/* Call context: func_15083E90: unique active project prototype */

void func_150723E0(void) {
    u8 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x65) != 0)) {
        func_15060F28(temp_v0, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
void func_151B5BA0(void *, void *, s32, s32 *);
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507266C CURRENT (775) */
void func_1507266C(void) {
    typedef struct {
        u8 bytes[0x32C];
    } ActorSlot;
    s32 high_value;
    s32 value;
    u8 *actor;
    ActorSlot *slots;

    slots = (ActorSlot *)&D_800CC2D0;
    if ((D_800BE616 == 0) && (*(u8 *)((u8 *)D_800D154C + 0x222) == 0)) {
        return;
    }
    value = D_800D1580;
    high_value = value >> 16;
    actor = slots[*(u8 *)((u8 *)D_800D154C + 0x222)].bytes;
    actor[0x65] = D_800C3E78 + 1;
    *(s32 *)(actor + 0x5C) = high_value;
    actor[0x101] = 4;
    actor[0x104] = 0;
    actor[0x125] = 0xFF;
    *(s32 *)(actor + 0x218) = 0;
    *(s16 *)(actor + 0xE4) = 0;
    *(s16 *)(actor + 0xE6) = 0;
    actor[0x232] = value;
    *(f32 *)(actor + 0xEC) = 1.0f;
    *(f32 *)(actor + 0xF0) = 1.0f;
    *(f32 *)(actor + 0xDC) = 1.0f;
    *(f32 *)(actor + 0xE0) = 1.0f;
    func_151B5BA0(slots[D_800C3E78].bytes, actor, high_value, &D_800CC2D0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507266C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507266C.s")
void func_15072740(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15072740 CURRENT (1845) */
void func_15072740(void) {
    void *temp_v1;

    temp_v1 = (*(u8 *)((u8 *)D_800D154C + 0x222) * 0x32C) + &D_800CC2D0;
    *(s8 *)((u8 *)temp_v1 + 0x65) = (s8) (D_800C3E78 + 1);
    *(s32 *)((u8 *)temp_v1 + 0x5C) = (s32) ((s32) D_800D1580 >> 0x10);
    *(s8 *)((u8 *)temp_v1 + 0x101) = 4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15072740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072740.s")
extern f32 D_80099F4C;

void func_150727AC(void) {
    *(f32 *)(D_800D154C + 0x4C) = (f32) D_800D1580 * D_80099F4C;
    *(f32 *)(*(u8 **)(D_800D154C + 0x2D0) + 0x10) = *(f32 *)(D_800D154C + 0x4C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727F0.s")
void func_15060F28(u8 *arg0, s32 arg1);

void func_15072918(void) {
    func_15060F28(D_800D154C, 0);
}
void func_15072940(void) {
    func_15060F28(D_800D154C, 1);
}
/* Call context: func_1505E650: unique active project prototype */

void func_15072968(void) {
    func_1505E650(D_800D154C, 0x2C, 0x3FC00000, 0x41400000, 0.0f, 0.0f, 0);
    *(s8 *)((u8 *)D_800D154C + 0x89) = 0x19;
}
void func_150729B4(void) {
    *(s32 *)(D_800D154C + 0x2E4) = D_800D1580;
}
extern void func_1507EB4C(void *arg0, s32 arg1);

void func_150729D0(void) {
    *(s16 *)(*(u8 **)(D_800D154C + 0x31C) + 8) = 1;
    func_1507EB4C(D_800D154C, 0x15);
    func_1506B82C();
}
void func_15072A14(void) {
    *(s16 *)(*(u8 **)(D_800D154C + 0x31C) + 0x66) = 0;
    func_1507F640();
}
void func_15072A40(void) {
    *(s8 *)((u8 *)(*(void **)(D_800D154C + 0x31C)) + 0x19B) = 0;
    *(s8 *)((u8 *)(*(void **)(D_800D154C + 0x31C)) + 0x78) = 0;
    func_1507F640();
}
typedef struct {
    u8 pad0[0x1A9];
    u8 counter;
} Game981E0CounterState;

typedef struct {
    u8 pad0[0x31C];
    Game981E0CounterState *counter_state;
} Game981E0CounterOwner;

void func_15072A7C(void) {
    Game981E0CounterState *counter_state;

    counter_state = ((Game981E0CounterOwner *)D_800D154C)->counter_state;
    if (counter_state != 0) {
        counter_state->counter++;
        if ((u32)(func_150ADA20() & 7) <
            ((Game981E0CounterOwner *)D_800D154C)->counter_state->counter) {
            func_1505E650(D_800D154C, 0x18A, 0x3F800000, 0x40800000, 0.0f, 0.0f, 0);
        }
    }
}

/* Call context: func_1505E650: unique active project prototype */

void func_15072AF8(void) {
    func_1505E650(D_800D154C, (*(u16 *)((u8 *)D_800D154C + 0x84) + 1) & 0xFFFF, 0x3F800000, 0x40C00000, 0.0f, 0.0f, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
void func_15072DA0(void) {
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFFF8);
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | D_800D1580);
}
/* Call context: func_15083568: unique active project prototype */
void func_15083568(void *, s32, s32, s32);

void func_15072DD8(void) {
    void *temp_v0;

    func_15083568(D_800D154C, D_800D1580, 0x3F800000, 0);
    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11A) == 1)) {
        *(u8 *)((u8 *)temp_v0 + 0x11A) = 2U;
    }
}
extern void func_150836CC(u8 *arg0, s32 arg1);

void func_15072E38(void) {
    u8 *temp_v0;

    func_150836CC(D_800D154C, D_800D1580);
    temp_v0 = *(u8 **)(D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        temp_v0[0x11A] = 0;
    }
}
void func_15072E7C(void) {
    *(s16 *)(D_800D154C + 0x10C) = (s16)D_800D1580;
}
extern f32 D_800D1874;

void func_15072E98(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x2D0);
    *(f32 *)((u8 *)temp_v0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x10) * D_800D1874);
}
void func_15072EC0(void) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)((u8 *)D_800D154C + 0x2D0);
    if (*(f32 *)(temp_v0 + 0x10) < D_800D1874) {
        *(s16 *)((u8 *)D_800D154C + 0x10C) = 0;
    }
}
void func_15072EF4(void) {
    D_800D154C[0x104] = (s8)D_800D1580;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072F10.s")
void func_1507304C(void) {
}
void func_15073054(void) {
    *(s16 *)(D_800D154C + 0x22E) = (s16)D_800D1580;
}

void func_15073070(void) {
}
void func_15073078(void) {
    func_1512D748(0, D_800D1580, 1);
}
void func_150730A4(void) {
    *(s8 *)((u8 *)D_800D154C + 0x1FF) = 3;
    *(s8 *)((u8 *)D_800D154C + 0x200) = (s8) D_800D1580;
}
void func_150730D0(void) {
    if (D_800D1580 == 1) {
        *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) | 0x100);
        return;
    }
    *(u16 *)((u8 *)D_800D154C + 0x2F8) = (u16) (*(u16 *)((u8 *)D_800D154C + 0x2F8) & 0xFEFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507342C.s")
/* Call context: func_1505E650: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150738E8 CURRENT (1043) */
void func_150738E8(void) {
    u8 temp_v0;
    void *temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_v0 != 0) {
        *(u8 *)((u8 *)D_800D154C + 0x13C) = 0U;
        temp_v0_2 = (((temp_v0 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_v0_2 + 0xF8) = 0x8200;
        *(s8 *)((u8 *)temp_v0_2 + 0x13D) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x65) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x232) = 6;
        *(s32 *)((u8 *)temp_v0_2 + 0x218) = 0;
        *(s8 *)((u8 *)temp_v0_2 + 0x104) = 0;
        *(s16 *)((u8 *)temp_v0_2 + 0x7A) = 0xE000;
        *(u16 *)((u8 *)temp_v0_2 + 0x76) = (u16) *(u16 *)((u8 *)D_800D154C + 0x7A);
        func_1505E650(D_800D154C, 0x97, 0x3F800000, 0x40A00000, 0.0f, 0.0f, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150738E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150738E8.s")
void func_150739A4(void) {
    D_800D154C[0x64] = (s8)D_800D1580;
}
extern u8 D_800BE9A0;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_150739C0(void) {
    *(s8 *)((u8 *)D_800D154C + 0x64) = (s8) (*(s8 *)((u8 *)D_800D154C + 0x64) - D_800BE9A0);
    if (*(s8 *)((u8 *)D_800D154C + 0x64) >= 0) {
        D_800D1880 = 0;
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) - 1);
        D_800D1878 = (f32) D_800D1580;
    }
}
void func_15073A28(void) {
    *(f32 *)((u8 *)D_800D154C + 0x44) = (f32) D_800D1580;
}
/* Call context: func_1505D024: unique active project prototype */
void func_1505D024(s32, s32, s32, s32);
extern f32 D_8009A0D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15073A50 CURRENT (645) */
void func_15073A50(void) {
    s32 sp20;
    s32 temp_v0;
    void *sp18;
    void *temp_a0;

    temp_a0 = (*(u8 *)((u8 *)D_800D154C + 0x124) * 0x32C) + &D_800CC2D0;
    if (*(u8 *)((u8 *)temp_a0 + 0x65) != 0) {
        temp_v0 = D_800D1580;
        *(s8 *)((u8 *)D_800D154C + 0x13C) = 0;
        *(s8 *)((u8 *)temp_a0 + 0x125) = 0;
        sp18 = temp_a0;
        sp20 = temp_v0;
        func_1505D024((s32) temp_a0, D_800D1580 & 0xFF00FF, 0, (s32) D_800C3E78);
        *(f32 *)((u8 *)temp_a0 + 0x1CC) = (f32) D_8009A0D8;
        if (temp_v0 & 0x40000000) {
            *(f32 *)((u8 *)temp_a0 + 0x1CC) = (f32) *(f32 *)((u8 *)D_800D154C + 0x18);
        }
        *(s8 *)((u8 *)temp_a0 + 0x125) = 0x14;
        *(s16 *)((u8 *)temp_a0 + 0x76) = (s16) (*(u16 *)((u8 *)D_800D154C + 0x7A) + temp_v0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15073A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15073B38 CURRENT (160) */
void func_15073B38(void) {
    *(f32 *)(*(u8 **)(D_800D154C + 0x31C) + 0xA8) = (f32)(D_800D1580 & 0xFFFF);
    *(s8 *)(*(u8 **)(D_800D154C + 0x31C) + 0xAC) =
        (s8)(u32)(f32)(((s32)D_800D1580 >> 16) & 0xFF);
    *(s8 *)(*(u8 **)(D_800D154C + 0x31C) + 0xAD) =
        (s8)((s32)D_800D1580 >> 24);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15073B38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073B38.s")
void func_15073C28(void) {
    func_1507F640();
}
void func_15073C48(void) {
}
void func_15073C50(void) {
    *(s16 *)((u8 *)D_800D154C + 0x224) = (s16) (s32) (*(f32 *)((u8 *) &D_800CC2E8 + (*(u8 *)((u8 *)D_800D154C + 0x222) * 0x32C)) + (f32) D_800D1580);
}
/* Call context: func_1505F0AC: unique active project prototype */
void * func_1505F0AC(u8);

void func_15073CB8(void) {
    void *temp_v0;

    temp_v0 = func_1505F0AC(0x53U);
    if ((temp_v0 != 0) && (*(u16 *)((u8 *)temp_v0 + 0x244) == 0x1F)) {
        *(s16 *)((u8 *)temp_v0 + 0x21C) = 0;
    }
}
/* Call context: func_15062B1C: unique active project prototype */
void func_15062B1C(void *, f32);

void func_15073CF4(void) {
    func_15062B1C(D_800D154C, (f32) D_800D1580);
}
/* Call context: func_15062B50: unique active project prototype */
void func_15062B50(void *, f32);

void func_15073D34(void) {
    func_15062B50(D_800D154C, (f32) D_800D1580);
}
void *func_15083E90(u8);                            /* extern */
extern u8 D_800D1583;

void func_15073D74(void) {
    void *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x65) = 0;
    }
}
/* Call context: func_1506C460: unique active project prototype */
void func_1506C460(f32, f32, f32, f32, s32, s32, f32, f32, s32, s32, s32);

void func_15073DA4(void) {
    s32 var_v0;

    if (D_800D1580 != 0) {
        var_v0 = 0x12;
    } else {
        var_v0 = 2;
    }
    func_1506C460(*(f32 *)((u8 *)D_800D154C + 0x40), 150.0f, 0.0f, 0.0f, 0x64, var_v0, 60.0f, 0.5f, 0, 0, 1);
}
typedef struct {
    u8 pad0[0x40];
    f32 field_40;
} Game981E0Field40Source;

void func_1506C460(f32, f32, f32, f32, s32, s32, f32, f32, s32, s32, s32);

void func_15073E2C(void) {
    func_1506C460(((Game981E0Field40Source *)D_800D154C)->field_40, 80.0f, 0.0f, 0.0f, 0x64, 0xB, 40.0f, 0.5f, 0, 0xE, 1);
}
void func_15073EA4(void) {
    func_1506C460(((Game981E0Field40Source *)D_800D154C)->field_40, 60.0f, 0.0f, 0.0f, 0x64, 0xC, 40.0f, 0.5f, 0, 0xE, 1);
}
void *func_1503195C(u8 *arg0, s32 arg1, s32 arg2);

void func_15073F1C(void) {
    void *temp_v0;

    temp_v0 = func_1503195C(D_800D154C, 0x3C, 0);
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)temp_v0 + 0x38) = 0x960;
    }
}
void func_15073F54(void) {
}
void func_15073F5C(void) {
    D_800D154C[0x2CB] = (s8)D_800D1580;
}
void func_15073F78(void) {
    *(u8 *)((u8 *)D_800D154C + 0x10B) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x10B) & ~D_800D1580);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073FA0.s")
typedef struct Game981E0NestedState {
    u8 pad0[0x11A];
    s8 field_11A;
} Game981E0NestedState;

void func_15074644(void) {
    (*(Game981E0NestedState **)(D_800D154C + 0x31C))->field_11A = (s8)D_800D1580;
}
typedef struct Game981E0FlagState {
    u8 pad0[0x94];
    u8 field_94;
} Game981E0FlagState;

void func_10011FDC(s32);

void func_15074664(void) {
    Game981E0FlagState *state;

    state = *(Game981E0FlagState **)((u8 *)D_800D154C + 0x31C);
    if (state != 0) {
        if (D_800D1580 == 1) {
            func_10011FDC(5);
            state = *(Game981E0FlagState **)((u8 *)D_800D154C + 0x31C);
        } else if (state->field_94 == 1) {
            func_10011FDC(0);
            state = *(Game981E0FlagState **)((u8 *)D_800D154C + 0x31C);
        }
        state->field_94 = (u8) D_800D1580;
    }
}
void func_1517F488(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150746F0 CURRENT (235) */
void func_150746F0(void) {
    u8 *var_a0;
    s32 temp_v1;
    void *temp_a1;
    void *temp_v0;

    var_a0 = 0;
    if (D_800BE616 != 0) {
        var_a0 = D_800D154C;
    } else if (*(u8 *)(D_800D154C + 0x13C) != 0) {
        var_a0 = (u8 *)&D_800CC2D0;
    }
    if (var_a0 != 0) {
        if (D_800D1580 >= (temp_v1 = *(u8 *)(var_a0 + 0x1CA))) {
            *(u8 *)(var_a0 + 0x1CA) = 0;
            *(u8 *)(D_800D154C + 0x1CA) = 0;
            if (*(s32 *)var_a0 == 1) {
                *(u8 *)(var_a0 + 0x125) = 0xFF;
                func_1507CD64(var_a0, 6);
            }
        } else {
            temp_a1 = *(u8 **)(var_a0 + 0x31C);
            *(u8 *)(var_a0 + 0x1CA) = temp_v1 - D_800D1580;
            if (temp_a1 != 0) {
                temp_v0 = *(u8 **)(var_a0 + 0x318);
                if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_a1 + 0x197) != 0)) {
                    func_1517F488(0xFF, 0, 0, 0xB4, 0x14,
                                  *(u8 *)((u8 *)temp_v0 + 0x23D));
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150746F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150746F0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150747E4 CURRENT (585) */
void func_150747E4(void) {
    u8 temp_v0;
    void *temp_a0;

    temp_v0 = *(u8 *)((u8 *)D_800D154C + 0x65);
    if (temp_v0 != 0) {
        temp_a0 = ((temp_v0 - 1) * 0x32C) + &D_800CC2D0;
        *(s32 *)((u8 *)temp_a0 + 0x218) = 0;
        *(s8 *)((u8 *)temp_a0 + 0x232) = (s8) D_800D1580;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150747E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150747E4.s")
void func_15074840(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)temp_v0 + 0x1AA) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x1AA) + D_800D1580);
    }
}
void func_15074870(void) {
    D_800D154C[0x24F] = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507488C CURRENT (570) */
void func_1507488C(void) {
    s32 temp_t8;
    s32 var_a1;

    temp_t8 = D_800D1580 & 1;
    var_a1 = temp_t8;
    if (*(s32 *)((u8 *)(D_800D154C + ((((s32) D_800D1580 >> 0x10) & 0xFF) * 4)) + 0x2E4) & (((s32) D_800D1580 >> 8) & 0xFF)) {
        var_a1 = (temp_t8 ^ 1) & 0xFF;
    }
    if (var_a1 != 0) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + ((s32) D_800D1580 >> 0x18));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507488C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")
extern s8 D_800CC3D7;

void func_150748F4(void) {
    D_800CC3D7 = (s8)D_800D1580;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507490C CURRENT (610) */
void func_1507490C(void) {
    u8 temp_v1;
    void *temp_v1_2;

    temp_v1 = *(u8 *)((u8 *)D_800D154C + 0x13C);
    if (temp_v1 != 0) {
        temp_v1_2 = (((temp_v1 - 0x64) & 0xFF) * 0x32C) + &D_800CC2D0;
        if ((s32) *(u8 *)((u8 *)temp_v1_2 + 0x13D) >= 0x64) {
            *(s32 *)((u8 *)temp_v1_2 + 0x218) = 0;
            *(s8 *)((u8 *)temp_v1_2 + 0x104) = 0;
            *(s8 *)((u8 *)temp_v1_2 + 0x232) = (s8) D_800D1580;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507490C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507490C.s")
f32 func_1505A72C(u8 *, u8 *);                      /* extern */
extern s8 D_8008FD8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074980 CURRENT (30) */
void func_15074980(void) {
    f32 temp_fs0;
    u8 *var_s0;
    s32 var_s1;
    void *temp_v0;

    var_s1 = 0;
    temp_fs0 = (f32) (D_800D1580 * 8);
    if (D_8008FD8C > 0) {
        var_s0 = (u8 *) &D_800CC2D0;
        do {
            if (func_1505A72C(D_800D154C, var_s0) < temp_fs0) {
                temp_v0 = *(void **)((u8 *)var_s0 + 0x31C);
                if (temp_v0 != 0) {
                    *(s8 *)((u8 *)temp_v0 + 0x4B) = 0x14;
                }
            }
            var_s1 += 1;
            var_s0 += 0x32C;
        } while (var_s1 < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074980.s")
void func_15074A44(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x26) = (s8) D_800D1580;
    }
}
void func_15074A6C(void) {
    if (*(u8 *)((u8 *)D_800D154C + 0x13C) == 0) {
        *(u8 *)((u8 *)D_800D154C + 0x138) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x138) + 1);
    }
}
extern f32 D_8009A0E8;
extern f32 D_8009A0EC;
extern f32 D_8009A0F0;
extern f32 D_8009A0F4;
extern f32 D_8009A0F8;
extern f32 D_8009A0FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15074A94 CURRENT (80) */
void func_15074A94(void) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv1;
    f32 delta;

    temp_fv0 = func_1505A72C((u8 *) &D_800CC2D0, D_800D154C);
    if (*(f32 *)((u8 *)D_800D154C + 0x148) < D_8009A0E8) {
        *(f32 *)((u8 *)D_800D154C + 0x148) = (f32) *(f32 *)((u8 *)D_800D154C + 0x154);
    }
    if (temp_fv0 < 200.0f) {
        var_fv1 = D_8009A0EC;
    } else {
        temp_fa1 = *(f32 *)((u8 *)D_800D154C + 0x148);
        if (D_8009A0F0 < temp_fv0) {
            var_fv1 = temp_fa1;
        } else {
            delta = temp_fa1 - D_8009A0F4;
            var_fv1 = (((temp_fv0 - 200.0f) / D_8009A0F8) * delta) + D_8009A0F4;
        }
    }
    *(f32 *)((u8 *)D_800D154C + 0x158) = var_fv1;
    *(f32 *)((u8 *)D_800D154C + 0x154) = (f32) *(f32 *)((u8 *)D_800D154C + 0x158);
    *(f32 *)((u8 *)D_800D154C + 0x15C) = (f32) D_8009A0FC;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15074A94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A94.s")
extern f32 D_8009A100;
extern f32 D_800D1878;
extern s32 D_800D1880;

void func_15074B7C(void) {
    D_800D1880 = 0;
    D_800D1878 = (f32) D_800D1580;
    if (D_800D1580 == 0) {
        D_800D1878 = D_8009A100;
        *(u8 *)((u8 *)D_800D154C + 0x1FC) = (u8) (*(u8 *)((u8 *)D_800D154C + 0x1FC) | 4);
        *(s8 *)((u8 *)D_800D154C + 0x138) = 0;
    }
}
void func_15074BD8(s32 arg0, s32 arg1, s32 arg2) {
}
void func_15074BEC(s32 arg0, s32 arg1, s32 arg2) {
}
typedef struct Game981E0SightActor {
    u8 pad0[0x239];
    u8 field_239;
} Game981E0SightActor;

void func_1504715C(void *, void *);
void func_150C04C0(f32 *, void *, s32, s32, s32, s32);
extern f32 D_800CC2C0;
extern f32 D_800CC2C4;
extern f32 D_800CC2C8;

void func_15074C00(s32 arg0, Game981E0SightActor *arg1, s32 arg2) {
    f32 sp44[3];
    u8 sp20[0x24];

    if ((arg1->field_239 & 0x7F) == 5) {
        func_1504715C(sp20, arg1);
        sp44[0] = D_800CC2C0;
        sp44[1] = D_800CC2C4;
        sp44[2] = D_800CC2C8;
        func_150C04C0(sp44, sp20, 0x16, 1, 0xFF, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074C80.s")
void func_15074DEC(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x2E8) = 1;
}
void func_1516FE1C(s32, s32, s32, s32);
void *func_1518D1C0(void *, s32, s32, s32, s32, s32, void *);
extern u8 D_80099C1C;

void func_15074E04(s32 arg0, void *arg1, s32 arg2) {
    func_1516FE1C(((u8 *)arg1 - (u8 *)&D_800CC2D0) / 0x32C, 0xB4, 0xFF, 0);
    func_1518D1C0(arg1, 0xB, 0, 1, 0xFF, 0, &D_80099C1C);
}

typedef struct Game981E0EventObject {
    s32 kind;
    u8 pad4[0x121];
    u8 field125;
} Game981E0EventObject;

void func_15194794(Game981E0EventObject *, Game981E0EventObject *, s8 *);

void func_15074E80(Game981E0EventObject *arg0, Game981E0EventObject *arg1, s32 arg2) {
    s8 sp1F = 0;

    func_15194794(arg0, arg1, &sp1F);
    if (arg1->kind == 1) {
        arg0->field125 = 0xFF;
        arg1->field125 = 0xC8;
        D_800D1580 = 0x60000;
        func_15072740();
    }
}

void func_15074EE8(u8 *arg0, u8 *arg1, s32 arg2) {
    if (*(s32 *)arg1 == 1) {
        arg0[0x125] = 0xFF;
        arg1[0x125] = 0xC8;
        D_800D1580 = 0x70000;
        func_15072740();
    }
}
void func_15074F30(u8 *arg0, u8 *arg1, s32 arg2) {
    arg0[0x232] = arg1[0x109];
    *(s32 *)(arg0 + 0x218) = 0;
}
/* Call context: func_1505A630: unique active project prototype */
/* Call context: func_15194408: unique active project prototype */
s32 func_1505A630(f32, f32, s32);
void func_15194408(s32, s32);
extern f32 D_8009A108;
extern f32 D_8009A10C;
extern f32 D_8009A110;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_15074F48(void *arg0, void *arg1, s32 arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 sp1C;
    f32 sp18;

    temp_fa0 = D_8009A108 - *(f32 *)((u8 *)arg0 + 0x14);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x1C) - D_8009A10C;
    sp1C = temp_fa0;
    sp18 = temp_fa1;
    *(s16 *)((u8 *)arg1 + 0x76) = func_1505A630(temp_fa0, temp_fa1, 0);
    *(f32 *)((u8 *)arg1 + 0x3C) = (f32) (sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1)) * D_8009A110);
    func_15194408((s32) arg0, (s32) arg1);
}
/* Call context: func_15072740: unique active project prototype */
/* Call context: func_151942B0: unique active project prototype */
void func_151942B0(s32, s32, s32);

void func_15074FD4(void *arg0, void *arg1, s32 arg2) {
    if (*(s32 *)((u8 *)arg1 + 0) == 1) {
        *(u8 *)((u8 *)arg0 + 0x125) = 0xFF;
        *(u8 *)((u8 *)arg1 + 0x125) = 0xC8;
        D_800D1580 = 0x60000;
        if (*(u8 *)((u8 *)arg0 + 4) == 0x8E) {
            D_800D1580 = 0x140000;
        }
        func_15072740();
    }
    func_151942B0((s32) arg0, (s32) arg1, arg2);
}
void func_15075050(void *arg0, s32 arg1, s32 arg2) {
    *(f32 *)((u8 *)arg0 + 0xB8) = 5.0f;
    if (*(f32 *)((u8 *)arg0 + 0x3C) > 0.0f) {
        *(f32 *)((u8 *)arg0 + 0xB8) = -5.0f;
    }
    *(f32 *)((u8 *)arg0 + 0x24) = 5.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 12.0f;
}
void func_150750A4(f32 *arg0, s32 arg1, s32 arg2) {
    arg0[9] = 5.0f;
}
/* Call context: func_15145A50: unique active project prototype */
void func_15145A50(u8 *);

void func_150750C4(Game981E0EventObject *arg0, Game981E0EventObject *arg1, s8 *arg2) {
    if ((arg1->pad4[0] == 0x88) && ((s32) arg0->pad4[0x103] < 0x37)) {
        *(u8 *)((u8 *)arg0 + 0x138) = (u8) (*(u8 *)((u8 *)arg0 + 0x138) + 3);
    }
    func_15194794(arg0, arg1, arg2);
    if (arg1->pad4[0] != 0x53) {
        func_15145A50((u8 *) arg1);
        *(s8 *)((u8 *)arg1 + 0x1CA) = 0;
        func_1507CD64(arg1, 8);
        *arg2 = 0x27;
    }
}
extern u8 D_800CC2D4;
extern u8 D_800CC335;
extern s32 D_800CC5FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507515C CURRENT (3120) */
s32 *func_1507515C(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 var_v0;

    if ((D_800CC2D0 != 0) && (D_800CC2D4 != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == D_800CC335)) {
        return &D_800CC2D0;
    }
    var_v0 = 2;
    if ((*(s32 *)((u8 *)&D_800CC5FC + 0) != 0) && (*(u8 *)((u8 *)&D_800CC5FC + 4) != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == *(u8 *)((u8 *)&D_800CC5FC + 0x65))) {
        return &D_800CC5FC;
    }
    var_v1 = (void *)((u8 *) &D_800CC5FC + 0x32C);
loop_9:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (*(u8 *)((u8 *)var_v1 + 4) != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == *(u8 *)((u8 *)var_v1 + 0x65))) {
        return var_v1;
    }
    temp_v1_3 = (void *)((u8 *) var_v1 + 0x32C);
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (*(u8 *)((u8 *)temp_v1_3 + 4) != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == *(u8 *)((u8 *)temp_v1_3 + 0x65))) {
        return temp_v1_3;
    }
    temp_v1_2 = (void *)((u8 *) temp_v1_3 + 0x32C);
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (*(u8 *)((u8 *)temp_v1_2 + 4) != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == *(u8 *)((u8 *)temp_v1_2 + 0x65))) {
        return temp_v1_2;
    }
    temp_v1 = (void *)((u8 *) temp_v1_2 + 0x32C);
    var_v0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (*(u8 *)((u8 *)temp_v1 + 4) != 0xFF) && ((((s32) (arg0 - (s32) &D_800CC2D0) / 812) + 1) == *(u8 *)((u8 *)temp_v1 + 0x65))) {
        return temp_v1;
    }
    var_v1 = (void *)((u8 *) temp_v1 + 0x32C);
    if (var_v0 == 0x1A) {
        return 0;
    }
    goto loop_9;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507515C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507515C.s")
