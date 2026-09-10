#include "types.h"

/*
 * Reviewed source unit: src/game/game_2062D0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D8E20
 * - func_151D8E6C
 * - func_151D8F30
 * - func_151D8FE0
 * - func_151D9014
 * - func_151D93F4
 * - func_151D9450
 * - func_151D9534
 * - func_151D97A8
 * - func_151D9820
 * - func_151D9878
 * - func_151D98D0
 * - func_151D9918
 * - func_151D9960
 * - func_151D99C8
 * - func_151D9A20
 * - func_151D9A68
 * - func_151D9ADC
 * - func_151D9B34
 * - func_151D9B8C
 * - func_151D9EB0
 * - func_151D9FC0
 * - func_151DA08C
 * - func_151DA368
 * - func_151DA6A8
 * - func_151DA6F8
 * - func_151DA938
 * - func_151DAA88
 * - func_151DAB58
 * - func_151DADA0
 * - func_151DAE28
 * - func_151DB27C
 * - func_151DB2A8
 * - func_151DB5D0
 * - func_151DB97C
 * - func_151DBAA8
 * - func_151DBBD4
 * - func_151DBCBC
 * - func_151DBE80
 * - func_151DC034
 * - func_151DC260
 * - func_151DC484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D8E20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D8E6C.s")
s32 func_151D8EB0(void) {
    return 0x75;
}
s32 func_151D8EBC(void) {
    return 0x1D;
}
s32 func_150ADA20();                                /* extern */

s32 func_151D8EC8(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x11;
    } else {
        var_v1 = 0x93;
    }
    return var_v1 & 0xFF;
}
s32 func_151D8EFC(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x5A;
    } else {
        var_v1 = 0x5B;
    }
    return var_v1 & 0xFF;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D8F30.s")
s32 func_151D8F7C(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x66;
    } else {
        var_v1 = 0x67;
    }
    return var_v1 & 0xFF;
}
s32 func_151D8FB0(void) {
    return 0x95;
}
s32 func_151D8FBC(void) {
    return 0x9F;
}
s32 func_151D8FC8(void) {
    return 0xB3;
}
s32 func_151D8FD4(void) {
    return 0x75;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D8FE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")
s32 func_151D9450(s32, s32);                        /* extern */
s32 func_151D9534(s32, s32);                        /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D93F4 CURRENT (973) */
s32 func_151D93F4(s32 arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (func_151D9450(arg0, arg1) != 0) {
        if (func_151D9534(arg0, arg1) != 0) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D93F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D93F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9450.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D97A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9820.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9878.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D98D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9960.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D99C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9A20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9A68.s")
typedef union Game2062D0Word {
    s32 value;
    u8 bytes[4];
} Game2062D0Word;

extern s32 D_800AB3C8;

u8 func_151D9AC0(void) {
    Game2062D0Word word;

    word.value = D_800AB3C8;
    return word.bytes[3];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9ADC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9EB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA08C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA368.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DA6A8 CURRENT (4880) */
s32 func_151DA6A8(u8 *arg0) {
    s32 var_v1;
    u8 *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v0 = (void *)(arg0 + 0x128);
        var_v1 = D_800BE9E4 - 1;
        if (D_800BE9E4 != 0) {
            do {
                *(f32 *)((u8 *)temp_v0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x10) * *(f32 *)((u8 *)temp_v0 + 0x14));
                var_v1 -= 1;
            } while (var_v1 != 0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DA6A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA938.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAA88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAB58.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern f32 D_800AB4B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DADA0 CURRENT (680) */
s32 func_151DADA0(u8 *arg0) {
    f32 temp_fv0;
    u8 temp_a0;
    u8 *temp_v1;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0x110) + (*(s8 *)((u8 *)arg0 + 0x111) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0x110) = temp_a0;
    temp_fv0 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_v1 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) ((*(f32 *)((u8 *)temp_v1 + 4) * temp_fv0) + 1.0f);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (D_800AB4B0 - (*(f32 *)((u8 *)temp_v1 + 8) * temp_fv0));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DADA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DADA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAE28.s")
void func_151DB004(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = 0;
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20(arg0) % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = 0;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB068(void *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;

    temp_v1 = (func_150ADA20() % 56U) + 0x64;
    *(s8 *)((u8 *)arg0 + 0x15) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x14) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    temp_v1_2 = (func_150ADA20(arg0) % 46U) + 0xB4;
    *(s8 *)((u8 *)arg0 + 0x19) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x18) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB0CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB15C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB1EC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DB27C CURRENT (15) */
void func_151DB27C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x15) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x16) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x18) = 0xB4;
    *(s8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0xC8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DB27C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB27C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DB2A8 CURRENT (5) */
void func_151DB2A8(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = 0;
    *(s8 *)((u8 *)arg0 + 0x15) = 0xC8;
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = 0;
    *(s8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DB2A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB2A8.s")
void func_151DB2CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = 0;
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = 0;
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20(arg0) % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB330(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 21U) + 0x5F);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 21U) + 0x5F);
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 11U) + 0x2D);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() & 0xF) + 0x3A);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() & 0xF) + 0x3C);
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 11U) + 0x19);
}
void func_151DB3D8(void *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;

    *(s8 *)((u8 *)arg0 + 0x14) = 0;
    temp_v1 = (func_150ADA20() % 56U) + 0x50;
    *(s8 *)((u8 *)arg0 + 0x16) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x15) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x18) = 0;
    temp_v1_2 = (func_150ADA20(arg0) % 46U) + 0xB4;
    *(s8 *)((u8 *)arg0 + 0x1A) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x19) = temp_v1_2;
}
void func_151DB43C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = 0;
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = 0;
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 46U) + 0xB4);
}
void func_151DB4CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 56U) + 0xC8);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB5D0.s")
/* Call context: func_15131918: unique active project prototype */
/* Call context: func_151423D8: unique active project prototype */
void func_15131918(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DB97C CURRENT (1870) */
s32 func_151DB97C(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    u8 *temp_s0;
    f32 sp24;
    f32 sp20;

    if (*(u8 *)((u8 *)arg0 + 0xA8) & 2) {
        func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xAC));
    }
    temp_s0 = (void *)(arg0 + 0xA8);
    if (*(u8 *)((u8 *)arg0 + 0xA8) & 1) {
        *(u8 *)((u8 *)temp_s0 + 8) = (u8) (*(u8 *)((u8 *)temp_s0 + 8) + (*(u8 *)((u8 *)temp_s0 + 0xB) * D_800BE9E4));
        *(u8 *)((u8 *)temp_s0 + 9) = (u8) (*(u8 *)((u8 *)temp_s0 + 9) + (*(u8 *)((u8 *)temp_s0 + 0xC) * D_800BE9E4));
        *(u8 *)((u8 *)temp_s0 + 0xA) = (u8) (*(u8 *)((u8 *)temp_s0 + 0xA) + (*(u8 *)((u8 *)temp_s0 + 0xD) * D_800BE9E4));
        sp20 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 8) - 0x40) & 0xFF);
        sp24 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 9) - 0x40) & 0xFF);
        temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 0xA) - 0x40) & 0xFF);
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) * sp20);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x14) * sp24);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) * temp_fv0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DB97C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB97C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBAA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBBD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBCBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBE80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC484.s")
