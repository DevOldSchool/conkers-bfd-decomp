#include "types.h"

/*
 * Reviewed source unit: src/game/game_C9EC0.c
 * Boundary evidence: docs/evidence/game_raw_resource_dependency_core.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509CA98
 * - func_1509CB68
 * - func_1509CBD4
 * - func_1509CCF4
 * - func_1509CDDC
 * - func_1509CE64
 * - func_1509CF28
 * - func_1509D054
 * - func_1509D08C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* ROM-verified 0x14-byte records; names identify tasks/scenes when present. */
typedef struct ResourceDescriptor {
    const char *name;
    s32 packed_id;
    u16 field_8;
    u16 field_A;
    const u16 *dependencies;
    const u16 *related_dependencies;
} ResourceDescriptor;

/* Preserve the original interior-field address used by the ID accessor. */
typedef struct ResourceDescriptorIdField {
    s32 packed_id;
    u8 pad4[0x10];
} ResourceDescriptorIdField;

extern ResourceDescriptor D_80087430[];
extern ResourceDescriptorIdField D_80087434[];

typedef struct GameC9EC0HalfwordEntry {
    u16 field_0;
    u8 pad2[0x12];
} GameC9EC0HalfwordEntry;

extern GameC9EC0HalfwordEntry D_80087438[];
extern GameC9EC0HalfwordEntry D_8008743A[];

/* Resource descriptor name accessor; unnamed records return NULL. */
const char *func_1509CA10(s32 descriptor_index) {
    return D_80087430[descriptor_index].name;
}
u16 func_1509CA30(s32 arg0) {
    return D_80087438[arg0].field_0;
}
s32 func_1509CA50(s32 arg0) {
    return D_8008743A[arg0].field_0 & 0xFFF;
}
s32 func_1509CA78(s32 arg0) {
    return D_80087434[arg0].packed_id;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CA98 CURRENT (60) */
s32 func_1509CA98(s32 arg0) {
    ResourceDescriptor *var_v0;
    s32 var_v1;

    var_v1 = 0;
    var_v0 = D_80087430;
loop_1:
    if ((var_v0->name != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 4) & 0x1FFFFFFF) + 1))) {
        return var_v1;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x14) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x18) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 1;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x28) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x2C) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 2;
    }
    if ((*(s32 *)((u8 *)var_v0 + 0x3C) != 0) && (arg0 == ((*(s32 *)((u8 *)var_v0 + 0x40) & 0x1FFFFFFF) + 1))) {
        return var_v1 + 3;
    }
    var_v1 += 4;
    var_v0 = (ResourceDescriptor *)((u8 *)var_v0 + 0x50);
    if (var_v1 == 0xCC) {
        return 0xCC;
    }
    goto loop_1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CA98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CA98.s")
extern u8 D_80088420[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CB68 CURRENT (80) */
s32 func_1509CB68(void) {
    u8 *descriptor_block;
    s32 count;

    count = 0;
    descriptor_block = (u8 *)D_80087430;
loop:
        if (((ResourceDescriptor *)descriptor_block)[0].name != 0) {
            count++;
        }
        if (((ResourceDescriptor *)descriptor_block)[1].name != 0) {
            count++;
        }
        if (((ResourceDescriptor *)descriptor_block)[2].name != 0) {
            count++;
        }
        if (((ResourceDescriptor *)descriptor_block)[3].name != 0) {
            count++;
        }
        descriptor_block += 0x50;
    if (descriptor_block != D_80088420) {
        goto loop;
    }
    return count;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CB68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CB68.s")
extern s32 D_800D2E4C;
extern s32 D_8008743C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CBD4 CURRENT (450) */
s32 func_1509CBD4(s32 arg0) {
    s32 temp_v0_2;
    u16 *temp_v0;
    u16 *var_s1;
    u16 temp_t7;
    u16 var_s0;

    temp_v0 = (u16 *)((ResourceDescriptorIdField *)D_8008743C)[arg0].packed_id;
    temp_t7 = *temp_v0;
    var_s1 = temp_v0;
    var_s0 = temp_t7 & 0xFFFF;
    if (temp_t7 != 0xFFFF) {
loop_1:
        temp_v0_2 = func_1509CBD4(var_s0);
        var_s0 = *(u16 *)((u8 *)var_s1 + 0);
        if (!((1 << (var_s0 & 7)) & *(u8 *)(D_800D2E4C + ((s32) var_s0 >> 3))) || (temp_v0_2 == 0)) {
            return 0;
        }
        var_s0 = *(u16 *)((u8 *)var_s1 + 2);
        var_s1 += 1;
        if (var_s0 == 0xFFFF) {
            goto block_5;
        }
        goto loop_1;
    }
block_5:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CBD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CBD4.s")
extern s32 D_8008743C[];
extern void func_1509CE64(s32 arg0, void (*arg1)(s32), s32 arg2);
void func_1509CCB4();

void func_1509CC94(void) {
    func_1509CCB4();
}

void func_1509CCB4(s32 arg0) {
    func_1509CE64(((ResourceDescriptorIdField *)D_8008743C)[arg0].packed_id, func_1509CCB4, arg0);
}
extern s32 D_80087440;
extern u8 D_800D2E70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CCF4 CURRENT (35) */
s32 func_1509CCF4(s32 arg0) {
    s32 var_s1;
    u16 *var_s0;
    u8 *var_s4;
    s32 var_s3;
    u16 var_v1;
    u8 *temp_a1;
    u8 *temp_v0;

    var_s0 = *(u16 **)((u8 *)&D_80087440 + (arg0 * 0x14));
    var_s1 = 0;
    var_v1 = *var_s0;
    var_s4 = &D_800D2E70;
    var_s3 = 3;
    if (var_v1 != 0xFFFF) {
        do {
            temp_v0 = ((s32)var_v1 >> 3) + (u8 *)D_800D2E4C;
            *temp_v0 |= 1 << (var_v1 & 7);
            temp_a1 = var_s4 + *var_s0;
            if (*temp_a1 != var_s3) {
                *temp_a1 = 3;
                func_1509CCB4(*var_s0);
                var_s1 += 1;
            }
            var_v1 = var_s0[1];
            var_s0 += 1;
        } while (var_v1 != 0xFFFF);
    }
    return var_s1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CCF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CCF4.s")
s32 func_1509CCF4();
extern u8 D_800D2E70;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CDDC CURRENT (1255) */
void func_1509CDDC(void) {
    s32 var_s0;
    s32 var_s2;

    func_1509CCF4();
    do {
        u8 *var_s1;

        var_s2 = 0;
        var_s1 = &D_800D2E70;
        var_s0 = 0;
loop_2:
        if (*var_s1 == 3) {
            var_s2 += func_1509CCF4(var_s0);
        }
        var_s0 += 1;
        var_s1 += 1;
        if (var_s0 != 0xCC) {
            goto loop_2;
        }
    } while (var_s2 != 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CDDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CDDC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CE64 CURRENT (640) */
void func_1509CE64(s32 arg0, void (*arg1)(s32), s32 arg2) {
    s32 var_s0;
    u16 *var_s1;
    u16 temp_s0;
    u16 temp_t6;
    u16 temp_t7;
    u8 *temp_v0;

    temp_t6 = *(u16 *)arg0;
    var_s1 = (u16 *)arg0;
    var_s0 = temp_t6 & 0xFFFF;
    if (temp_t6 != 0xFFFF) {
        do {
            arg1(var_s0);
            temp_t7 = *var_s1;
            var_s1 += 1;
            *((u8 *)&D_800D2E70 + temp_t7) = 3;
            temp_s0 = var_s1[-1];
            temp_v0 = (u8 *)D_800D2E4C + ((s32)temp_s0 >> 3);
            *temp_v0 |= (u8)(1 << (temp_s0 & 7));
            var_s0 = *var_s1;
        } while (var_s0 != 0xFFFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CE64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CE64.s")
s32 func_1502B6BC(s32, s32, u32 *, s32, s32, s32, s32);
extern u8 *D_800D2FB0;

typedef struct GameC9EC0Reloc {
    s32 offset;
    u32 flags;
} GameC9EC0Reloc;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CF28 CURRENT (1005) */
s32 func_1509CF28(s32 arg0, s32 *arg1) {
    s32 base;
    s32 entryOffset;
    u32 index;
    u32 count;
    u8 *cursor;
    s32 done;
    GameC9EC0Reloc *reloc;
    void *resource;

    count = 0;
    base = func_1502B6BC(0, 0, &count, 3, 8, 0, arg0);
    D_800D2FB0 = (u8 *)base;
    if (base == 0) {
        *arg1 = 0;
        return 0;
    }
    *(s32 *)(base + 4) = count - 1;
    *arg1 = count - 1;
    index = 1;
    entryOffset = 8;
    cursor = (u8 *)base;
    if (count >= 2) {
        do {
            done = 0;
            reloc = *(GameC9EC0Reloc **)(D_800D2FB0 + entryOffset);
            do {
                reloc->offset += *(s32 *)(D_800D2FB0 + entryOffset);
                if (reloc->flags & 0x80000000) {
                    done = 1;
                }
                reloc->flags &= 0x0FFFFFFF;
                reloc++;
            } while (done == 0);
            resource = *(void **)(cursor + 8);
            index++;
            entryOffset += 8;
            cursor += 8;
            *(u32 *)((u8 *)resource + 0xC) =
                (*(u32 *)((u8 *)resource + 0xC) & 0x0FFFFFFF) >> 1;
        } while (index < count);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CF28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CF28.s")
void func_10004074(s32 arg0);
extern u8 *D_800D2FB0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509D054 CURRENT (220) */
void func_1509D054(void) {
    s32 temp_v0;

    if ((temp_v0 = D_800D2FB0) != 0) {
        func_10004074(temp_v0);
        D_800D2FB0 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509D054 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D054.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509D08C CURRENT (100) */
s32 func_1509D08C(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    u8 *base;
    u8 *entry;
    s16 **resource;
    s16 *dependencies;
    s16 dependency;
    u32 index;
    u32 count;

    base = (u8 *)D_800D2FB0;
    entry = (u8 *)((arg1 * 8) + (s32)base);
    if (base == 0) {
        if (arg2 != 0) {
            *arg2 = 0xBF;
        }
        if (arg3 != 0) {
            *arg3 = 0;
        }
        return 0;
    }
    resource = *(s16 ***)(entry + 8);
    if (resource == 0) {
        if (arg2 != 0) {
            *arg2 = 0xBF;
        }
        if (arg3 != 0) {
            *arg3 = 0;
        }
        return 0;
    }
    if (arg2 != 0) {
        *arg2 = resource[2][0];
        resource = *(s16 ***)(entry + 8);
    }
    if (arg3 != 0) {
        *arg3 = resource[0][0];
        resource = *(s16 ***)(entry + 8);
    }
    count = *(u32 *)((u8 *)resource + 0xC);
    index = 0;
    if (count != 0) {
        dependencies = resource[2];
        do {
            dependency = *dependencies;
            index++;
            if (!((1 << (dependency & 7)) &
                  *(u8 *)(D_800D2E4C + (dependency >> 3)))) {
                return 0;
            }
            dependencies++;
        } while (index < count);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509D08C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D08C.s")
