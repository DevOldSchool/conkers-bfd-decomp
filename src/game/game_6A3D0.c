#include "types.h"

/*
 * Reviewed source unit: src/game/game_6A3D0.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503CF20
 * - func_1503D368
 * - func_1503D45C
 * - func_1503D484
 * - func_1503D510
 * - func_1503D5F0
 * - func_1503D660
 * - func_1503D774
 * - func_1503D804
 * - func_1503D984
 * - func_1503DA3C
 * - func_1503DA9C
 * - func_1503DC3C
 * - func_1503DD1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503CF20.s")
void func_1503D438(s32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D368 CURRENT (1525) */
void func_1503D368(s8 *arg0, s32 arg1) {
    register s8 *base;
    s32 index;
    s8 *entry;
    s8 opcode;

    base = arg0;
    if (base != 0) {
        index = 0;
        entry = base;
        if (*base != -0x21) {
            opcode = *base;
            do {
                if (opcode != -0x24) {
                    if (opcode == 1) {
                        func_1503D438((s32 *)(entry + 4), arg1);
                    }
                } else if (*(u8 *)(entry + 3) == 0xE) {
                    func_1503D438((s32 *)(entry + 4), arg1);
                }
                index++;
                entry = base + (index * 8);
                opcode = *entry;
            } while (opcode != -0x21);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D368 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D368.s")
void func_1503D438(s32 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if ((temp_v0 != 0) && !(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D45C CURRENT (15) */
void func_1503D45C(s32 *arg0, s32 arg1) {
    s32 temp_t6;
    s32 var_v0;

    var_v0 = *arg0;
    if (var_v0 != 0) {
        do {
            temp_t6 = var_v0 + arg1;
            var_v0 = *(s32 *)((u8 *)arg0 + 8);
            *(s32 *)((u8 *)arg0 + 0) = temp_t6;
            arg0 = (s32 *)((u8 *)arg0 + 8);
        } while (var_v0 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D45C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D45C.s")
extern s16 D_800C5A90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D484 CURRENT (198) */
void func_1503D484(u8 *arg0, s32 arg1) {
    u16 *var_s0;
    u16 *temp_s1;
    u16 temp_t8;

    var_s0 = (u16 *)arg0;
    temp_s1 = var_s0;
    if (*(u16 *)var_s0 != 0x3E7) {
        do {
            if (*(s32 *)((u8 *)var_s0 + 4) != 0) {
                func_1503D438((s32 *)((u8 *)var_s0 + 4), (s32)temp_s1);
            }
            temp_t8 = *(u16 *)((u8 *)var_s0 + 8);
            var_s0 = (u16 *)((u8 *)var_s0 + 8);
        } while (temp_t8 != 0x3E7);
    }
    D_800C5A90[arg1] = (s16)(((s32)((u8 *)var_s0 - (u8 *)temp_s1)) >> 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D484.s")
extern u8 *D_80084410[];
extern u8 D_80098888[];
extern s32 D_800D1588[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D510 CURRENT (4355) */
void func_1503D510(s32 arg0) {
    s16 *temp_t3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 *temp_a1;
    u16 *temp_t0;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 *var_v1_2;
    u8 temp_a0;

    var_a1 = D_80098888;
    var_v0 = 0;
loop_1:
    temp_a0 = *var_a1;
    var_v1 = 0;
    if ((s32)temp_a0 > 0) {
        temp_a3 = D_80084410[var_v0];
        var_t0 = temp_a3;
loop_3:
        var_v1 += 1;
        if (arg0 == *var_t0) {
            var_v0_2 = 0;
            if ((s32)temp_a0 > 0) {
                var_v1_2 = temp_a3;
                temp_a1 = &D_800D1588[arg0];
                temp_t0 = (u16 *)&D_800C5A90[arg0];
#pragma loop unroll 0
                do {
                    var_v0_2 += 1;
                    D_800D1588[*var_v1_2] = *temp_a1;
                    temp_t3 = &D_800C5A90[*var_v1_2];
                    var_v1_2 += 1;
                    *temp_t3 = *temp_t0;
                } while (var_v0_2 < (s32)temp_a0);
            }
        } else {
            var_t0 += 1;
            if (var_v1 >= (s32)temp_a0) {
                goto block_9;
            }
            goto loop_3;
        }
    } else {
block_9:
        var_v0 += 1;
        var_a1 += 1;
        if (var_v0 == 5) {
            return;
        }
        goto loop_1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D510 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D510.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D5F0 CURRENT (2240) */
s32 func_1503D5F0(s32 arg0) {
    s32 group_index;
    s32 entry_index;
    u8 *group;
    u8 *count;
    u8 *entry;
    u8 group_size;

    count = D_80098888;
    group_index = 0;
loop_groups:
    group_size = *count;
    entry_index = 0;
    if ((s32) group_size > 0) {
        group = D_80084410[group_index];
        entry = group;
loop_entries:
        entry_index++;
        if (arg0 == *entry) {
            return *group;
        }
        entry++;
        if (entry_index >= (s32) group_size) {
            goto next_group;
        }
        goto loop_entries;
    }
next_group:
    group_index++;
    count++;
    if (group_index == 5) {
        return arg0;
    }
    goto loop_groups;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D5F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D5F0.s")
typedef struct Game6A3D0Resource {
    u8 *field0;
    u8 *field4;
    u8 *field8;
    u8 padC[4];
} Game6A3D0Resource;

Game6A3D0Resource *func_1502B5C8(s32 *, s32, ...);
void func_1503D45C(s32 *, s32);
void func_1503D484(u8 *, s32);
void func_1503D510(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D660 CURRENT (861) */
s32 func_1503D660(s32 arg0, s32 arg1, s32 arg2, u32 arg3) {
    s32 sp34;
    void ***sp28;
    void ***temp_v1;
    void **temp_v0;
    void **temp_v0_2;
    void **temp_v0_3;
    void *temp_a0;
    void *temp_a0_2;
    void **temp_a0_3;

    temp_v1 = (void ***)&D_800D1588[arg0];
    if (*temp_v1 != 0) {
        return 0;
    }
    sp28 = temp_v1;
    temp_v0 = (void **)func_1502B5C8(&sp34, 2, 0xF,
                                     func_1503D5F0(arg0));
    if (temp_v0 == 0) {
        *sp28 = 0;
        D_800C5A90[arg0] = 0;
        func_1503D510(arg0);
        return 4;
    }
    *sp28 = temp_v0;
    if (*temp_v0 != 0) {
        *temp_v0 = (u8 *)*temp_v0 + (s32)temp_v0;
        temp_v0_2 = *sp28;
        func_1503D45C(*temp_v0_2, (u8 *)temp_v0_2 + 0x10);
    }
    temp_v0_3 = *sp28;
    temp_a0 = temp_v0_3[1];
    if (temp_a0 != 0) {
        temp_v0_3[1] = (u8 *)temp_a0 + (s32)temp_v0_3;
        temp_v0_3 = *sp28;
    }
    temp_a0_2 = temp_v0_3[2];
    if (temp_a0_2 != 0) {
        temp_v0_3[2] = (u8 *)temp_a0_2 + (s32)temp_v0_3;
        temp_v0_3 = *sp28;
    }
    temp_a0_3 = (void **)((u8 *)temp_v0_3 + 0x10);
    *sp28 = temp_a0_3;
    func_1503D484((u8 *)temp_a0_3, arg0);
    func_1503D510(arg0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D660 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D660.s")
s32 *func_1502B6BC(s32 *, s32, s32, s32, s32, s32);
extern s32 D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D774 CURRENT (417) */
s32 func_1503D774(s32 arg0, void *arg1) {
    s32 sp2C;
    s32 *sp24;
    s32 *temp_v1;
    s32 *temp_v0;

    temp_v1 = &D_800D1C90[arg0];
    if (*temp_v1 != 0) {
        return 0;
    }
    sp24 = temp_v1;
    temp_v0 = func_1502B6BC(&sp2C, 2, 0, 2, 0x11, arg0);
    if (temp_v0 == 0) {
        *sp24 = 0;
        return 2;
    }
    *sp24 = (s32)temp_v0;
    *sp24 = *temp_v0;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D774 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D774.s")
void *func_10003C40(s32, s32, s32, s32);
extern void *D_800C4020[];
extern void *D_800C6360[];
extern s32 D_800D19A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D804 CURRENT (46) */
s32 func_1503D804(s32 arg0) {
    s32 selected = -1;
    s32 count;
    void **slot;
    u8 *source;
    u8 *destination;
    s32 i;

    if (arg0 == 0x24) {
        count = 0x5E;
        selected = 0;
    } else {
        count = 0;
    }
    if (count == 0) {
        return 0;
    }
    slot = &D_800C6360[arg0];
    if (*slot != 0) {
        return 0;
    }
    source = (u8 *)D_800D19A0[arg0];
    if (selected != -1) {
        source += *(s32 *)((u8 *)D_800C4020[arg0] + selected * 4) * 0x10;
    }
    if ((*slot = func_10003C40(count * 4, 1, 0, 2)) == 0) {
        return 1;
    }
    destination = *slot;
    for (i = 0; i < count; i++) {
        *(s16 *)(destination + i * 4) = *(s16 *)(source + i * 0x10 + 8);
        *(s16 *)(destination + i * 4 + 2) = *(s16 *)(source + i * 0x10 + 0xA);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D804 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D804.s")
extern s32 D_800C4488;
extern s16 D_800C5918;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D984 CURRENT (2195) */
void func_1503D984(s32 arg0) {
    s16 count;
    s32 stream;
    u32 **list;
    u32 *record;
    s8 tag;

    count = 0;
    list = (u32 **)((u8 *)&D_800C4488 + (arg0 * 4));
    for (stream = 0; stream < 4; stream++, list++) {
        record = *list;
        tag = (s8)(record[0] >> 24);
        while (tag != -0x21) {
            if (tag == 5) {
                count += 1;
            } else if (tag == 6) {
                count += 2;
            } else if ((tag >> 4) == 1) {
                count += 4;
            }
            record += 2;
            tag = (s8)(record[0] >> 24);
        }
    }
    *(s16 *)((u8 *)&D_800C5918 + (arg0 * 2)) = count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D984.s")
extern s32 D_800D19A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DA3C CURRENT (115) */
s32 func_1503DA3C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    u8 var_v1;
    u8 *temp_v1;

    temp_v0 = D_800D19A0[arg0];
    temp_v1 = (u8 *)temp_v0 - 0x38;
    if (temp_v0 == 0) {
        return 0xFF;
    }
    if (*(u32 *)(temp_v1 + 0x34) < (u32)(arg1 + 1)) {
        return 0xFF;
    }
    temp_v0_2 = *(s32 *)(temp_v1 + 0x30);
    var_v1 = 0xFF;
    if (temp_v0_2 != 0) {
        var_v1 = *((u8 *)temp_v0_2 + arg1);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DA3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DA3C.s")
s32 func_1503CF20(s32, s32, void *, s32, s32);
void func_150028BC(s32);
s32 func_1503DC3C(s32);
s32 func_15084044(void *, s32);
void func_1510CE60(s32, s32, s32, s32, void *);
extern s32 D_800C5C08[];
extern u16 D_800C4778[];
extern s32 D_800C4488;
extern u8 *D_800C5338[];
extern u16 D_800C5628[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DA9C CURRENT (1099) */
s32 func_1503DA9C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *node;
    s32 result;
    s32 index;
    s32 offset;
    u16 *countPtr;
    s32 *entries;

    node = *(u8 **)(arg0 + 0x144);
    if (D_800D19A0[arg1] == 0) {
        result = func_1503CF20(arg1, 0, node, arg3, arg0[0xAC]);
    } else {
        result = 0;
        if (((node != 0 && (*(s32 *)(node + 0x18) & 0x4000)) ||
             (arg0[0xAC] & 1)) && D_800C5C08[arg1] == 0) {
            func_150028BC(arg1);
        }
        if (arg3 != 0) {
            if (D_800C5628[arg1] != 0 &&
                *(u32 *)D_800C5338[arg1] < 0x10000000U) {
                result = func_1503DC3C(arg1);
                countPtr = &D_800C4778[arg1];
                index = 0;
                offset = 0;
                if (*countPtr > 0) {
                    do {
                        entries = *(s32 **)((u8 *)&D_800C4488 + arg1 * 4);
                        func_1510CE60(*(s32 *)((u8 *)entries + offset),
                                       0, 0, 0x3E, 0);
                        index++;
                        offset += 4;
                    } while (index < *countPtr);
                }
            }
        }
    }
    if (result == 0) {
        result = func_15084044(arg0, arg2);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DA9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DA9C.s")
extern s32 func_1510D0EC(s32, s32 *, s32, s32);
extern void func_1510D7AC(s32 arg0, s32 arg1, u16 arg2);
extern u8 *D_800C5338[];
extern u16 D_800C5628[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DC3C CURRENT (573) */
s32 func_1503DC3C(s32 arg0) {
    s32 *temp_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    u16 *temp_s6;
    void **temp_s2;
    register void *var_s0;

    temp_s6 = &D_800C5628[arg0];
    var_s4 = 0;
    var_s3 = 0;
    if ((s32)*temp_s6 > 0) {
        temp_s2 = (void **)&D_800C5338[arg0];
        var_s0 = *temp_s2;
        var_s1 = 0;
        do {
            *(s32 *)((u8 *)*temp_s2 + var_s1) = func_1510D0EC(*(s32 *)((u8 *)var_s0 + 4), 0, 0x3E, 1);
            temp_s0 = (s32 *)((u8 *)*temp_s2 + var_s1);
            if (*temp_s0 == (s32)0x80000000) {
                var_s4 |= 0x10;
            }
            var_s3 += 1;
            var_s1 += 0xC;
            var_s0 = (u8 *)temp_s0 + 0xC;
        } while (var_s3 < (s32)*temp_s6);
    }
    return var_s4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DC3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DC3C.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DD1C CURRENT (2265) */
void func_1503DD1C(s32 arg0) {
    u16 *temp_s3;
    u8 *temp_v0;
    s32 temp_a1;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;

    temp_s3 = &D_800C5628[arg0];
    var_s0 = 0;
    if (*temp_s3 > 0) {
        var_s1 = 0;
        do {
            temp_v0 = D_800C5338[arg0] + var_s1;
            temp_v1 = *(s32 *)temp_v0;
            if (temp_v1 != (s32)0x80000000) {
                temp_a1 = *(s32 *)(temp_v0 + 4);
                if (temp_v1 != temp_a1) {
                    func_1510D7AC(temp_a1, temp_a1, *temp_s3);
                }
            }
            var_s0 += 1;
            var_s1 += 0xC;
        } while (var_s0 < (s32)*temp_s3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DD1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DD1C.s")
