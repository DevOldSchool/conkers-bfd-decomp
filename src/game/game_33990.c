#include "types.h"

/*
 * Reviewed source unit: src/game/game_33990.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150064E0
 * - func_15006590
 * - func_15006BEC
 * - func_1500707C
 * - func_15007168
 * - func_1500727C
 * - func_15007360
 * - func_15007440
 * - func_15007558
 * - func_15007778
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_15017790(void);
extern s8 D_800BE3DF;
extern s32 D_800BE3E8;
extern s32 D_800C3A60;
extern s32 D_800C3A64;
extern s32 D_800C3A68[];
extern s32 D_800C3C88[];
extern s8 D_800D2E45;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150064E0 CURRENT (4915) */
void func_150064E0(void) {
    s32 *var_v0;

    func_15017790();
    D_800C3A60 = 0;
    D_800C3A64 = 0;
    var_v0 = D_800C3A68;
    do {
        var_v0 += 8;
        var_v0[-1] = 0;
        var_v0[-2] = 0;
        var_v0[-3] = 0;
        var_v0[-4] = 0;
        var_v0[-5] = 0;
        var_v0[-6] = 0;
        var_v0[-7] = 0;
        var_v0[-8] = 0;
    } while (var_v0 != D_800C3C88);
    D_800BE3DF = 0x18;
    D_800BE3E8 = 0;
    D_800D2E45 = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150064E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_150064E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006590.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006BEC.s")
void func_10024F10(void);
s32 func_151DD4E0(u8 *, s32, u8 *);
extern u8 D_8002AC5C;
extern u16 D_800BE358;
extern u8 D_800BE3D8[];
extern u8 D_800BE900[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500707C CURRENT (1833) */
void func_1500707C(s32 arg0) {
    s32 i;
    s32 index;
    s32 next_index;
    s32 unused;
    u8 *flags;

    i = 0;
    do {
        ((u8 *)&D_800BE358)[i] = 0xFF;
        i++;
    } while (i < 8);
    func_10024F10();
    flags = D_800BE3D8;
    index = 0;
    if (D_8002AC5C == 0) {
        do {
            i = (index * 0x10) + 4;
            if (arg0 == *(s8 *)flags) {
                next_index = i + 1;
                unused = func_151DD4E0(D_800BE900, i & 0xFF, &D_800BE358);
                func_151DD4E0(D_800BE900, next_index & 0xFF, &D_800BE358);
            }
            index++;
            flags++;
        } while (index != 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500707C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500707C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007168 CURRENT (9335) */
void func_15007168(void) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007168 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007168.s")
void func_15007168(void);
void func_151DD3A0(u8 *, s32, s16 *, s32);
extern s16 D_800BE2F0;
extern u8 D_800BE2F2;
extern u8 D_800BE2F3;
extern u8 D_800BE2F4;
extern u8 D_800BE900[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500727C CURRENT (1685) */
void func_1500727C(void) {
    s32 temp_t9;
    s32 var_v0;
    s32 var_v1;
    void *var_a0;

    func_151DD3A0(D_800BE900, 0x44, &D_800BE2F0, 0x70);
    var_a0 = &D_800BE2F4;
    var_v0 = ((D_800BE2F2 * 4) + 0xCC + (D_800BE2F3 * 8)) & 0xFFFF;
    var_v1 = 4;
loop:
        temp_t9 = (var_v0 +
                   (*(u8 *)((u8 *)var_a0 + 0) << (var_v1 & 3)) +
                   (*(u8 *)((u8 *)var_a0 + 1) << ((var_v1 + 1) & 3)) +
                   (*(u8 *)((u8 *)var_a0 + 2) << ((var_v1 + 2) & 3)) +
                   (*(u8 *)((u8 *)var_a0 + 3) << ((var_v1 + 3) & 3))) & 0xFFFF;
        var_v1 += 4;
        var_v0 = temp_t9;
        var_a0 = (u8 *)var_a0 + 4;
    if (var_v1 != 0x68) {
        goto loop;
    }
    if (temp_t9 != (u16)D_800BE2F0) {
        func_15007168();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500727C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500727C.s")
s32 func_151DCEF0(u8 *, s32, s16 *, s32);
extern u8 D_8002AC5C;
extern s16 D_800BE2F0;
extern u8 D_800BE2F2;
extern u8 D_800BE2F3;
extern u8 D_800BE2F4;
extern u8 D_800BE900[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007360 CURRENT (1689) */
void func_15007360(void) {
    volatile s32 result;
    void *current;
    s32 value;
    s32 next;
    s32 shift;

    current = &D_800BE2F4;
    value = ((D_800BE2F2 * 4) + 0xCC + (D_800BE2F3 * 8)) & 0xFFFF;
    shift = 4;
loop:
        next = (value +
                (*(u8 *)((u8 *)current + 0) << (shift & 3)) +
                (*(u8 *)((u8 *)current + 1) << ((shift + 1) & 3)) +
                (*(u8 *)((u8 *)current + 2) << ((shift + 2) & 3)) +
                (*(u8 *)((u8 *)current + 3) << ((shift + 3) & 3))) & 0xFFFF;
        shift += 4;
        value = next;
        current = (u8 *)current + 4;
    if (shift != 0x68) {
        goto loop;
    }
    D_800BE2F0 = next;
    if (D_8002AC5C == 0) {
        result = func_151DCEF0(D_800BE900, 0x44, &D_800BE2F0, 0x70);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007360 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007360.s")
extern u8 D_800BE35A;
extern s8 D_800E0BE0;
extern s8 D_800E0BFC;
extern s8 D_8008FE30;
void func_151DD9E4(s8 *, s8, s8 *);
void func_151E7EF8(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007440 CURRENT (3625) */
void func_15007440(void) {
    s32 shift;
    s32 checksum;
    s32 next;
    s32 saved;
    u8 *checksum_source;
    u8 *copy_source;
    s8 *destination;

    func_151DD3A0(D_800BE900, 0, (s16 *)&D_800BE358, 0x20);
    checksum = 0xCC;
    checksum_source = &D_800BE35A;
    shift = 2;
checksum_loop:
    next = (checksum + (*checksum_source << (shift & 3))) & 0xFFFF;
    checksum = next;
    shift++;
    checksum_source++;
    if (shift < 0x1E) {
        goto checksum_loop;
    }

    saved = *(&D_800E0BE0 + 0x10);
    if (next != D_800BE358) {
        destination = &D_800E0BE0;
clear_loop:
        destination += 4;
        destination[-4] = -1;
        destination[-3] = -1;
        destination[-2] = -1;
        destination[-1] = -1;
        if (destination != &D_800E0BFC) {
            goto clear_loop;
        }
    } else {
        destination = &D_800E0BE0;
        copy_source = (u8 *)&D_800BE358;
copy_loop:
        destination += 4;
        copy_source += 4;
        destination[-4] = copy_source[-2];
        destination[-3] = copy_source[-1];
        destination[-2] = copy_source[0];
        destination[-1] = copy_source[1];
        if (destination != &D_800E0BFC) {
            goto copy_loop;
        }
    }
    *(&D_800E0BE0 + 0x10) = saved;
    func_151DD9E4(&D_800E0BFC, saved, &D_800E0BE0);
    func_151E7EF8();
    D_8008FE30 = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007440 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007440.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007558 CURRENT (1859) */
void func_15007558(void) {
    volatile s32 result;
    s8 *src;
    u8 *dst;
    void *data;
    s32 checksum;
    s32 next;
    s32 shift;
    s8 value;

    src = &D_800E0BE0;
    dst = &D_800BE358;
    do {
        value = *src;
        src++;
        dst++;
        dst[1] = value;
    } while ((u32)src < (u32)&D_800E0BFC);

    checksum = 0xCC;
    data = &D_800BE35A;
    shift = 2;
loop:
        next = (checksum +
                (((u8 *)data)[0] << (shift & 3)) +
                (((u8 *)data)[1] << ((shift + 1) & 3)) +
                (((u8 *)data)[2] << ((shift + 2) & 3)) +
                (((u8 *)data)[3] << ((shift + 3) & 3))) & 0xFFFF;
        shift += 4;
        checksum = next;
        data = (u8 *)data + 4;
    if (shift != 0x1E) {
        goto loop;
    }
    *(s16 *)&D_800BE358 = next;
    if (D_8002AC5C == 0) {
        result = func_151DCEF0(D_800BE900, 0, (s16 *)&D_800BE358, 0x20);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007558 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007558.s")
void func_15007644(void) {

}
extern s8 D_80082BB4;
extern s8 D_800BE3EC;

void func_1500764C(void) {
    D_80082BB4 = 6;
    D_800BE3EC = 0;
}
void func_15007668(void) {
    D_80082BB4 = 7;
    D_800BE3EC = 0;
}
void func_15007684(void) {
    D_80082BB4 = 4;
    D_800BE3EC = 0;
}
void func_150076A0(void) {
    D_80082BB4 = 5;
    D_800BE3EC = 0;
}
void func_150064E0(void);
extern u8 D_800BE616;

void func_150076BC(s32 arg0) {
    if (arg0 < 0) {
        func_150064E0();
    }
    if ((arg0 >= 0) && (arg0 < 4) && (D_800BE616 == 0)) {
        D_80082BB4 = 1;
        D_800BE3EC = arg0;
    }
}
void func_15007718(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3) && (D_800BE616 == 0)) {
        D_80082BB4 = 2;
        D_800BE3EC = arg0;
    }
}
void func_15007750(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80082BB4 = 3;
        D_800BE3EC = arg0;
    }
}
extern u8 D_800BE3F8[];
extern s16 D_800BE3DC;
extern s8 D_800BE3DE;
extern s8 D_80082BC0;
extern s8 D_800BE3DB;
extern u8 D_800BE3D8[];
extern u8 D_800D2E60[];
extern u8 D_800D2E69[];
extern u8 D_800D2E4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15007778 CURRENT (4215) */
void func_15007778(void) {
    u8 *dst;
    u8 *flags;
    s32 i;

    *(s32 *)(D_800BE3F8 + 8) = -1;
    *(s32 *)(D_800BE3F8 + 0x18) = -1;
    *(s32 *)(D_800BE3F8 + 0x28) = -1;
    D_800BE3F8[0xE] = 0xFF;
    D_800BE3F8[0x1E] = 0xFF;
    D_800BE3F8[0x2E] = 0xFF;
    D_800BE3DC = -1;
    D_800BE3DE = 0;
    D_80082BC0 = 1;
    for (i = 0; i < 0x1B; i++) {
        D_800D2E4C[i] = 0;
    }
    dst = D_800D2E60;
    while (++dst < D_800D2E69) {
        dst[-1] = 0;
    }
    flags = D_800BE3D8;
    flags[0] = 0xFF;
    flags[1] = 0xFF;
    flags[2] = 0xFF;
    flags[3] = 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15007778 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007778.s")
