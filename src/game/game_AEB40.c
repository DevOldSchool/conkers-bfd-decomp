#include "types.h"

/*
 * Reviewed source unit: src/game/game_AEB40.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15081690
 * - func_15081C20
 * - func_15081E0C
 * - func_15081E78
 * - func_150825C0
 * - func_15082A44
 * - func_150832AC
 * - func_15083384
 * - func_15083568
 * - func_150836CC
 * - func_150837D4
 * - func_15083AC8
 * - func_15083E0C
 * - func_15083E90
 * - func_15083FB0
 * - func_15084044
 * - func_150843AC
 * - func_15084558
 * - func_150849CC
 * - func_15084A18
 * - func_15084C30
 * - func_15084CB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameAEB40NestedState {
    u8 pad0[0x56];
    u8 field_56;
} GameAEB40NestedState;

typedef struct GameAEB40State {
    u8 pad0[0xF8];
    u32 flags_F8;
    u8 padFC[0xCD];
    u8 field_1C9;
    u8 field_1CA;
    u8 pad1CB[0xF9];
    u8 *field_2C4;
    u8 field_2C8;
    u8 field_2C9;
    u8 pad2CA[0x52];
    GameAEB40NestedState *nested_31C;
} GameAEB40State;

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081C20.s")
void func_1507DF10(GameAEB40State *, u16, u8);
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15081E0C CURRENT (742) */
void func_15081E0C(GameAEB40State *arg0, u16 arg1, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0->field_1CA != 0) {
            arg0->field_1CA = 7;
        }
        if ((arg2 == 0) || (arg1 != 0xA)) {
            func_1507DF10(arg0, arg1, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15081E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150825C0.s")
void func_150825C0(s32, s32);
extern u8 D_800D2100;
extern u8 D_800D2101;

void func_1508295C(s32 arg0, s32 arg1, s32 arg2) {
    s32 current;
    s32 end;
    s32 start;

    if (arg2 != 0) {
        start = 0;
        end = D_800D2101;
    } else {
        start = D_800D2101;
        end = D_800D2100;
    }
    current = start;
    if (start < end) {
        do {
            func_150825C0(current, arg1);
            current++;
        } while (current != end);
    }
}

extern s32 D_800BE9F0;

void func_150829D8(GameAEB40State *arg0) {
    arg0->flags_F8 &= 0xF7FFFFFD;
    arg0->flags_F8 |= 4;
    if ((arg0->nested_31C != 0) && (arg0->nested_31C->field_56 == 0)) {
        switch (D_800BE9F0) {
            case 0:
            case 10:
            case 14:
            case 18:
            case 19:
            case 25:
            case 27:
            case 44:
            case 60:
            case 61:
            case 66:
            case 67:
            case 68:
                break;
            default:
                arg0->flags_F8 |= 2;
                break;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15082A44.s")
s32 func_1515D440();                                /* extern */
s32 func_1515D480(u8);                              /* extern */
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150832AC CURRENT (830) */
void func_150832AC(u8 *arg0) {
    s32 var_s1;
    u8 temp_a0;
    u8 var_s3;
    u8 *var_s0;

    temp_v1 = (void *)(*(void **)((u8 *)arg0 + 0x144));
    if (temp_v1 != 0) {
        temp_a0 = *(u8 *)((u8 *)temp_v1 + 0x2F);
        var_s0 = arg0;
        var_s3 = temp_a0;
        if (temp_a0 == 0) {
            if (*(u8 *)((u8 *)arg0 + 0x127) == 0) {
                var_s3 = 5;
            } else {
                var_s3 = 3;
            }
        }
        var_s1 = 0;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)((u8 *)var_s0 + 0x304) = func_1515D480(var_s3);
                var_s1 += 1;
                var_s0 += 4;
            } while (D_80082FA0 >= var_s1);
        }
        if (*(s32 *)((u8 *)(arg0 + (var_s1 * 4)) + 0x300) != 0) {
            *(u8 *)((u8 *)arg0 + 0x301) = var_s3;
        }
        *(s32 *)((u8 *)arg0 + 0x314) = func_1515D440();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150832AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150832AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083384.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083568.s")
typedef struct {
    u8 *entries;
    u8 count;
    u8 pad5[3];
} GameAEB40EntryList;

void func_150302F0(void *, s32);
u8 *func_1505F0AC(u8);
void func_15060F28(u8 *, s32);
extern GameAEB40EntryList D_80086CC4[];
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150836CC CURRENT (330) */
void func_150836CC(void *arg0, s32 arg1) {
    s32 var_s1;
    u8 *temp_v0;
    GameAEB40EntryList *temp_s2;

    func_150302F0(arg0, arg1);
    arg1 -= 1;
    temp_s2 = &D_80086CC4[arg1];
    var_s1 = 0;
    arg1 = (s32)temp_s2->entries;
    if ((s32)temp_s2->count > 0) {
        do {
            if (((u8 *)arg1)[3] == 0) {
                temp_v0 = func_1505F0AC(((u8 *)arg1)[0]);
                if ((temp_v0 != 0) &&
                    ((((s32)((u8 *)arg0 - (u8 *)&D_800CC2D0) / 812) + 1) ==
                     temp_v0[0x65])) {
                    func_15060F28(temp_v0, 0);
                }
            }
            var_s1 += 1;
            arg1 += 0x10;
        } while (var_s1 < (s32)temp_s2->count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150836CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150836CC.s")
extern u8 *D_800D1C90[];
extern u16 D_800C5A90[];
s32 func_1502B020(s32, s32, s32, s32);
void func_15062BDC(void *, s32, s32, s32);
s8 func_15084D00(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150837D4 CURRENT (568) */
void func_150837D4(s32 arg0, s32 arg1, s32 arg2) {
    u8 **sp20;
    s32 index;
    s8 result;
    u8 *state;

    state = (u8 *)&D_800CC2D0 + (arg0 * 0x32C);
    state[4] = arg1;
    if (arg1 == 0xFF) {
        *(s16 *)(state + 0xE4) = 0;
        *(s16 *)(state + 0xE6) = 0;
        *(s16 *)(state + 0xE8) = 0;
        *(s16 *)(state + 0xD2) = 0x46;
        *(s16 *)(state + 0xD4) = 0x46;
        *(s16 *)(state + 0xD6) = 0;
        *(s16 *)(state + 0x160) = 0;
        *(f32 *)(state + 0xC8) = 0.0f;
    } else {
        sp20 = &D_800D1C90[arg1];
        *(f32 *)(state + 0xC8) = (f32)*(s16 *)(*sp20 + 6);
        func_15062BDC(state, *(s32 *)(state + 0x14C),
                      *(s32 *)(state + 0x150), arg1);
        state[5] = (*sp20)[0x12];
    }
    result = func_15084D00(state);
    index = result & 0xFF;
    state[6] = result;
    if (D_800C5A90[index] != 0) {
        *(s32 *)(state + 0x58) = func_1502B020(0, 2, 2, index);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150837D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150837D4.s")
void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
void func_1505E650(u8 *, s32, s32, f32, f32, f32, s32);
extern u16 D_800C5A90[];
extern void *D_800D1588[];

s32 func_150838EC(u8 *arg0, u16 arg1, s32 arg2, s32 arg3) {
    u8 index;

    index = arg0[4];
    if (D_800D1588[index] == 0) {
        return 0;
    }
    if (D_800C5A90[index] == 0) {
        return 0;
    }
    *(void **)(arg0 + 0x2D0) = func_10003C40(0x3E0, 1, 2, 0);
    if (*(void **)(arg0 + 0x2D0) == 0) {
        return 1;
    }
    func_100226F0(*(void **)(arg0 + 0x2D0), 0x40);
    func_1505E650(arg0, arg1, arg3, 0.0f, 0.0f, 0.0f, arg2);
    return 0;
}
extern u8 *D_80086CAC[];
extern u8 *D_800D1C90[];
void func_15036C70(void *);

void func_150839B8(void *arg0, s32 arg1, void *arg2) {
    u16 temp_v1;
    s32 var_a1;
    u8 *temp_v0;

    var_a1 = arg1;
    if (var_a1 != 0xFF) {
        temp_v0 = D_800D1C90[var_a1];
        if (arg2 != 0) {
            temp_v1 = *(u16 *)((u8 *)arg2 + 0x2C);
            var_a1 = temp_v1;
            if (temp_v1 == 0) {
                *(u16 *)((u8 *)arg0 + 0x10) = *(u16 *)(temp_v0 + 0x2A);
            } else if (var_a1 == 1) {
                *(u16 *)((u8 *)arg0 + 0x10) = 0;
            } else {
                *(u16 *)((u8 *)arg0 + 0x10) = temp_v1;
            }
            if (D_800BE9F0 == 0x1D) {
                *(u16 *)((u8 *)arg0 + 0x10) = 0x3E8;
            }
        } else {
            *(u16 *)((u8 *)arg0 + 0x10) = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x13B) = temp_v0[0x39];
        *(s8 *)((u8 *)arg0 + 0x2CB) = *(s8 *)(temp_v0 + 0x33);
        *(s32 *)((u8 *)arg0 + 0x2CC) = *(s32 *)(temp_v0 + 0x34);
        *(u8 *)((u8 *)arg0 + 5) = temp_v0[0x12];
        *(u8 *)((u8 *)arg0 + 0x68) = temp_v0[0x3B];
        *(u8 *)((u8 *)arg0 + 0x69) = temp_v0[0x3C];
        *(s16 *)((u8 *)arg0 + 0x160) = *(s16 *)(temp_v0 + 2);
        if (temp_v0[4] != 0) {
            *(u8 **)((u8 *)arg0 + 0x2C4) = D_80086CAC[temp_v0[5]];
            *(u8 *)((u8 *)arg0 + 0x2C8) = temp_v0[4];
        }
        *(u8 *)((u8 *)arg0 + 0x2C9) =
            temp_v0[0x38] + *(u8 *)((u8 *)arg0 + 0x2C8);
        if (temp_v0[0x29] != 0) {
            func_15036C70(arg0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083AC8.s")
extern u8 *D_800D20FC;
extern u8 D_800D2100;

s32 func_15083DA0(void) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_v1;

    var_v1 = 1;
    var_v0 = 0;
    if ((s32) D_800D2100 > 0) {
        do {
            if (var_v1 == *(u8 *)((s32)D_800D20FC + (var_v0 * 0x30) + 0x28)) {
                var_v1 += 1;
                var_v0 = 0;
            }
            var_v0 += 1;
        } while (var_v0 < (s32) D_800D2100);
    }
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    return var_v1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083E0C CURRENT (410) */
s32 func_15083E0C(s32 arg0) {
    s32 temp_t6;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return -1;
    }
    var_v1 = 0;
    if ((s32) D_800D2100 > 0) {
        var_a2 = 0;
        var_a3 = D_800D20FC;
loop_4:
        var_v1 += 1;
        var_a3 += 0x30;
        if (temp_t6 == *(u8 *)((u8 *)var_a3 + 0x28)) {
            return (s32) ((var_a2 + D_800D20FC) - D_800D20FC) / 48;
        }
        var_a2 += 0x30;
        if (var_v1 >= (s32) D_800D2100) {
            /* Duplicate return node #7. Try simplifying control flow for better match */
            return -1;
        }
        goto loop_4;
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E0C.s")
extern s32 D_800CC2D0;
extern u8 D_800CC30B;
extern s32 D_800CC5FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083E90 CURRENT (410) */
s32 *func_15083E90(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 temp_t6;
    s32 var_a0;

    temp_t6 = arg0 & 0xFF;
    if (temp_t6 == 0) {
        return 0;
    }
    if ((D_800CC2D0 != 0) && (temp_t6 == D_800CC30B)) {
        return &D_800CC2D0;
    }
    var_a0 = 2;
    if ((*(s32 *)((u8 *)&D_800CC5FC + 0) != 0) && (temp_t6 == *(u8 *)((u8 *)&D_800CC5FC + 0x3B))) {
        return &D_800CC5FC;
    }
    var_v1 = &D_800CC5FC + 0x32C;
loop_9:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (temp_t6 == *(u8 *)((u8 *)var_v1 + 0x3B))) {
        return var_v1;
    }
    temp_v1_3 = var_v1 + 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1_3 + 0x3B))) {
        return temp_v1_3;
    }
    temp_v1_2 = temp_v1_3 + 0x32C;
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1_2 + 0x3B))) {
        return temp_v1_2;
    }
    temp_v1 = temp_v1_2 + 0x32C;
    var_a0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (temp_t6 == *(u8 *)((u8 *)temp_v1 + 0x3B))) {
        return temp_v1;
    }
    var_v1 = temp_v1 + 0x32C;
    if (var_a0 == 0x1A) {
        return 0;
    }
    goto loop_9;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083E90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E90.s")
/* Call context: func_15083E90: unique active project prototype */
void *func_15083E90(u8 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15083FB0 CURRENT (474) */
s32 func_15083FB0(s32 arg0) {
    s32 temp_a0;
    void *temp_v0;

    temp_a0 = arg0;
    temp_a0 &= 0xFF;
    temp_v0 = func_15083E90(temp_a0);
    if (temp_v0 != 0) {
        return (s32) ((u8 *)temp_v0 - (u8 *)&D_800CC2D0) / 0x32C;
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15083FB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083FB0.s")
extern s32 *func_1505EEF4(s32 arg0);

s32 func_15084000(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = func_1505EEF4(arg0);
    if (temp_v0 != 0) {
        return (s32) ((u8 *) temp_v0 - (u8 *) &D_800CC2D0) / 0x32C;
    }
    return -1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084044.s")
void func_150843AC(GameAEB40State *, s32);

void func_1508434C(GameAEB40State *arg0) {
    s32 index;
    s32 count;

    count = arg0->field_2C9;
    if (count == 0) {
        count = 1;
    }
    index = 0;
    if (count > 0) {
        do {
            func_150843AC(arg0, index);
            index += 1;
        } while (index != count);
    }
}
void func_100043B4(s32, s32);
extern void *D_800D19A0[];
extern u8 D_800D1F80[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150843AC CURRENT (840) */
void func_150843AC(GameAEB40State *arg0, s32 arg1) {
    s32 resource;
    s32 offset;
    u8 *count;
    u8 resource_index;
    u8 *entry;
    u8 *current;

    entry = (u8 *)arg0 + arg1 * 8;
    current = (u8 *)arg0 + arg1 * 8;
    offset = 0;
    if ((*(s32 *)(entry + 0x28C) != 0) ||
        (*(s32 *)(entry + 0x290) != 0)) {
        resource_index = arg0->field_2C4[arg1];
        do {
            resource = *(s32 *)(current + 0x28C);
            if (resource != 0) {
                count = &D_800D1F80[resource_index];
                if (resource != (s32)D_800D19A0[resource_index]) {
                    func_100043B4(resource, 3);
                } else {
                    *count -= 1;
                }
                *(s32 *)(current + 0x28C) = 0;
            }
            offset += 4;
            current += 4;
        } while (offset != 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150843AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150843AC.s")
void func_1503D660(s32, s32);
void func_1503D774(s32, s32);
extern u8 *D_80086CAC[];
extern u8 *D_800D1C90[];

void func_15084488(u8 *arg0, s32 arg1, s32 arg2) {
    s32 count;
    s32 i;
    u8 *record;
    u8 *entry;
    u8 *entries;
    u8 index;

    index = arg0[4];
    if (index != 0xFF) {
        func_1503D774(index, arg2);
        record = D_800D1C90[index];
        entries = arg0 + 4;
        count = record[4];
        if (count == 0) {
            count = 1;
        } else {
            entries = D_80086CAC[record[5]];
        }
        i = 0;
        entry = entries;
        count += record[0x38];
        if (count > 0) {
            do {
                func_1503D774(*entry, arg2);
                func_1503D660(*entry, arg2);
                i++;
                entry++;
            } while (i != count);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084558.s")
u8 func_150849A0(void *arg0) {
    u8 temp_v1;

    temp_v1 = *(u8 *)((u8 *)arg0 + 0x1C9);
    if (temp_v1 != 0) {
        return *(*(u8 **)((u8 *)arg0 + 0x2C4) + temp_v1 - 1);
    }
    return **(u8 **)((u8 *)arg0 + 0x2C4);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150849CC CURRENT (235) */
u8 func_150849CC(void *arg0, s32 *arg1) {
    s32 var_v1;
    s32 temp_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1C9);
    if (temp_v0 != 0) {
        var_v1 = temp_v0 - 1;
    } else {
        temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x2C8);
        var_v1 = 0;
        if (temp_v0_2 != 0) {
            var_v1 = temp_v0_2 - 1;
        }
    }
    if (arg1 != 0) {
        temp_v1 = var_v1;
        *arg1 = temp_v1;
    } else {
        temp_v1 = var_v1;
    }
    return *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x2C4) + temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150849CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150849CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084A18.s")
u32 func_150ADA20();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084C30 CURRENT (1080) */
void func_15084C30(void *arg0) {
    void *sp1C;
    u32 temp_hi;
    void *temp_v1;

    if (*(u8 *)((u8 *)arg0 + 4) == 0x94) {
        temp_v1 = *(void **)((u8 *)arg0 + 0x2D0);
        sp1C = temp_v1;
        temp_hi = func_150ADA20() % (u32) (s32) *(f32 *)((u8 *)temp_v1 + 0x18);
        {
            f32 var_fv0 = (f32) temp_hi;
        if ((s32) temp_hi < 0) {
            var_fv0 += 4294967296.0f;
        }
        *(f32 *)((u8 *)temp_v1 + 8) = var_fv0;
    }
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084C30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084C30.s")
extern u8 D_800BE590;
extern u16 D_800BE598;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15084CB0 CURRENT (140) */
s32 func_15084CB0(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u16 *var_a2;

    var_v1 = 0;
    var_v0 = 0;
    if ((s32) D_800BE590 > 0) {
        var_a2 = &D_800BE598;
loop_2:
        if (arg0 == *var_a2) {
            var_v1 = var_v0;
        } else {
            var_v0 += 1;
            var_a2 += 2;
            if (var_v0 < (s32) D_800BE590) {
                goto loop_2;
            }
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15084CB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084CB0.s")
