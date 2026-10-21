#include "types.h"

/*
 * Reviewed source unit: src/game/game_6A3D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503CF20
 * - func_1503D368
 * - func_1503D510
 * - func_1503D5F0
 * - func_1503D660
 * - func_1503D774
 * - func_1503D984
 * - func_1503DA9C
 * - func_1503DD1C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Semantic role: model_load_bank01_resources.
 * Install model-indexed geometry/draw/texture tables; this is a shared loader.
 * See docs/evidence/assets/naming/actor_representation_asset_semantics.md.
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
/* Semantic role: asset_relocate_untagged_offset (shared with display lists).
 * Only nonzero values with (value & 0x0F000000) == 0 receive the base address.
 * See docs/evidence/assets/naming/actor_representation_asset_semantics.md.
 */
void func_1503D438(s32 *offsetSlot, s32 baseAddress) {
    s32 offset;

    offset = *offsetSlot;
    if ((offset != 0) && !(offset & 0x0F000000)) {
        *offsetSlot = offset + baseAddress;
    }
}
void func_1503D45C(s32 *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = *arg0;
    if (var_v0 != 0) {
        do {
            *arg0 = var_v0 + arg1;
            var_v0 = *(s32 *)((u8 *)arg0 + 8);
            arg0 = (s32 *)((u8 *)arg0 + 8);
        } while (var_v0 != 0);
    }
}
extern s16 D_800C5A90[];

/* Semantic role: animation_routes_relocate_event_offsets.
 * Eight-byte routes end at descriptor 999; optional event offsets at +4 are
 * relative to the route-record base. Store the route count by model index.
 * See docs/evidence/assets/naming/actor_representation_asset_semantics.md.
 */
void func_1503D484(u8 *routeRecord, s32 modelIndex) {
    u16 *routeBase;

    routeBase = (u16 *)routeRecord;
    if (*(u16 *)routeRecord != 0x3E7) {
        do {
            if (*(s32 *)((u8 *)routeRecord + 4) != 0) {
                func_1503D438((s32 *)((u8 *)routeRecord + 4), (s32)routeBase);
            }
            routeRecord += 8;
        } while (*(u16 *)routeRecord != 0x3E7);
    }
    D_800C5A90[modelIndex] = (s16)(((s32)((u8 *)routeRecord - (u8 *)routeBase)) >> 3);
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D660 CURRENT (466) */
s32 func_1503D660(s32 arg0, s32 arg1) {
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

/* Semantic role: model_load_bank11_defaults.
 * The first relocated descriptor pointer becomes D_800D1C90[modelIndex].
 * See docs/evidence/assets/naming/actor_representation_asset_semantics.md.
 */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D774 CURRENT (317) */
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

s32 func_1503D804(s32 arg0) {
    s32 count;
    s32 selected = -1;
    u8 *source;
    u8 *destination;

    if (arg0 == 0x24) {
        count = 0x5E;
        selected = 0;
    } else {
        count = 0;
    }
    if (count == 0) {
        return 0;
    }
    if (D_800C6360[arg0] != 0) {
        return 0;
    }
    source = (u8 *)D_800D19A0[arg0];
    if (selected != -1) {
        source += *(s32 *)((u8 *)D_800C4020[arg0] + selected * 4) * 0x10;
    }
    if ((D_800C6360[arg0] = func_10003C40(count * 4, 1, 0, 2)) == 0) {
        return 1;
    }
    destination = D_800C6360[arg0];
    for (arg0 = 0; arg0 < count; arg0++) {
        *(s16 *)(destination + arg0 * 4) = *(s16 *)(((u8 (*)[0x10])source)[arg0] + 8);
        *(s16 *)(destination + arg0 * 4 + 2) = *(s16 *)(((u8 (*)[0x10])source)[arg0] + 0xA);
    }
    return 0;
}
extern s32 D_800C4488;
extern s16 D_800C5918;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503D984 CURRENT (330) */
void func_1503D984(s32 arg0) {
    u32 count;
    s32 stream;
    u32 *start;
    u32 list;
    u32 record;
    s8 tag;

    count = 0;
    list = *(u32 *)((u32)&D_800C4488 + (u32)arg0 * 4U);
    stream = 0;
next_stream:
    {
        start = *(u32 **)list;
        stream += 4;
        tag = (s8)(start[0] >> 24);
        record = (u32)start;
        while (tag != -0x21) {
            if (tag == 5) {
                count += 1;
            } else if (tag == 6) {
                count += 2;
            } else if ((tag >> 4) == 1) {
                count += 4;
            }
            record += 8;
            tag = (s8)(*(u32 *)record >> 24);
        }
    }
    list += 4;
    if (stream != 4) {
        goto next_stream;
    }
    *(s16 *)((u32)&D_800C5918 + (u32)arg0 * 2U) = count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503D984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503D984.s")
extern s32 D_800D19A0[];

/* Partial header at stream address - 0x38; the preceding bytes are opaque. */
typedef struct Game6A3D0StreamHeader {
    u8 pad0[0x30];
    s32 data_address;
    u32 length;
} Game6A3D0StreamHeader;

s32 func_1503DA3C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    u8 var_v1;
    u32 temp_v1;

    temp_v0 = D_800D19A0[arg0];
    temp_v1 = (u32)temp_v0 - 0x38U;
    if (temp_v0 == 0) {
        return 0xFF;
    }
    if (((Game6A3D0StreamHeader *)temp_v1)->length < ((u32)arg1 + 1U)) {
        return 0xFF;
    }
    temp_v0_2 = ((Game6A3D0StreamHeader *)temp_v1)->data_address;
    if (temp_v0_2 != 0) {
        var_v1 = *((u8 *)temp_v0_2 + arg1);
    } else {
        var_v1 = 0xFF;
    }
    return var_v1;
}
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
extern void func_1510D7AC(s32 arg0);
extern u8 *D_800C5338[];
extern u16 D_800C5628[];

/* Semantic role: model_load_descriptor_flat_textures.
 * Twelve-byte descriptors supply flat IDs at +4 and receive loaded bases at +0.
 * See docs/evidence/assets/naming/actor_representation_asset_semantics.md.
 */
typedef struct Game6A3D0Entry {
    s32 value;
    s32 key;
    s32 extra;
} Game6A3D0Entry;

s32 func_1503DC3C(s32 arg0) {
    Game6A3D0Entry *entry;
    u16 *count;
    u8 **table;
    s32 flags;
    s32 i;

    count = &D_800C5628[arg0];
    flags = 0;
    i = 0;
    if (*count > 0) {
        table = &D_800C5338[arg0];
        entry = (Game6A3D0Entry *)*table;
        do {
            ((Game6A3D0Entry *)*table)[i].value = func_1510D0EC(entry->key, 0, 0x3E, 1);
            entry = &((Game6A3D0Entry *)*table)[i];
            if (entry->value == (s32)0x80000000) {
                flags |= 0x10;
            }
            i++;
            entry++;
        } while (i < *count);
    }
    return flags;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503DD1C CURRENT (35) */
void func_1503DD1C(s32 arg0) {
    Game6A3D0Entry *entry;
    u16 *countp;
    s32 count;
    s32 key;
    s32 i;

    countp = &D_800C5628[arg0];
    count = *countp;
    for (i = 0; i < count; i++) {
        entry = &((Game6A3D0Entry *)D_800C5338[arg0])[i];
        if (entry->value != (s32)0x80000000) {
            key = entry->key;
            if (entry->value != key) {
                func_1510D7AC((entry->key));
                count = *countp;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503DD1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6A3D0/func_1503DD1C.s")
