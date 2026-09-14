#include "types.h"

/*
 * Reviewed source unit: src/game/game_C9EC0.c
 * Boundary evidence: docs/evidence/game_raw_resource_dependency_core.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509CA98
 * - func_1509CB68
 * - func_1509CBD4
 * - func_1509CCB4
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
    var_v0 += 0x50;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CBD4 CURRENT (1491) */
s32 func_1509CBD4(u16 arg0) {
    s32 temp_v0_2;
    u16 *temp_v0;
    u16 *var_s1;
    u16 temp_s0;
    u16 temp_t7;
    u16 var_s0;

    temp_v0 = (void *)(*(u8 *)(D_8008743C + (arg0 * 0x14)));
    temp_t7 = *temp_v0;
    var_s1 = temp_v0;
    var_s0 = temp_t7 & 0xFFFF;
    if (temp_t7 != 0xFFFF) {
loop_1:
        temp_v0_2 = func_1509CBD4(var_s0);
        temp_s0 = *(u16 *)((u8 *)var_s1 + 0);
        if (!((1 << (temp_s0 & 7)) & *(u8 *)(D_800D2E4C + ((s32) temp_s0 >> 3))) || (temp_v0_2 == 0)) {
            return 0;
        }
        var_s0 = *(u16 *)((u8 *)var_s1 + 2);
        var_s1 += 2;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509CCB4 CURRENT (110) */
void func_1509CCB4(s32 arg0) {
    func_1509CE64(D_8008743C[arg0 * 5], func_1509CCB4, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509CCB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CCB4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CE64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CF28.s")
void func_10004074(s32 arg0);
extern s32 D_800D2FB0;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D08C.s")
