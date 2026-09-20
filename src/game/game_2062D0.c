#include "types.h"

/*
 * Reviewed source unit: src/game/game_2062D0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D8F30
 * - func_151D9014
 * - func_151D93F4
 * - func_151D9450
 * - func_151D9534
 * - func_151D98D0
 * - func_151D9918
 * - func_151D9A20
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
 * - func_151DB5D0
 * - func_151DB97C
 * - func_151DBAA8
 * - func_151DBCBC
 * - func_151DBE80
 * - func_151DC034
 * - func_151DC260
 * - func_151DC484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150A29C8(s32 arg0, s32 arg1);
extern s32 D_800BE9F0;
extern u8 D_800E0A10;
extern u8 D_800AB344[];
extern s32 func_150ADA20();

u8 func_151D8E20(void) {
    if ((D_800BE9F0 == 0) && (func_150A29C8(0, 0x1C) == 0)) {
        return 0xA;
    }
    return D_800E0A10;
}
typedef struct {
    u8 field0;
    u8 field1;
    u8 field2;
} Func151D8E6CBytes;
extern Func151D8E6CBytes D_800AB340;
extern s32 func_150ADA20();

u8 func_151D8E6C(void) {
    Func151D8E6CBytes sp1C;

    sp1C = D_800AB340;
    return ((u8 *)&sp1C)[func_150ADA20() % 3U];
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8F30 CURRENT (425) */
u8 func_151D8F30(void) {
    u8 sp20[8];
    u8 *temp_t7;

    temp_t7 = D_800AB344;
    *(s32 *)(sp20 + 0) = *(s32 *)(temp_t7 + 0);
    *(u8 *)(sp20 + 4) = *(u8 *)(temp_t7 + 4);
    return sp20[func_150ADA20() % 5U];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8F30 */
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
extern s32 D_800AB34C;
s32 func_151D8FE0(void) {
    s32 sp1C;

    sp1C = D_800AB34C;
    return ((u8 *)&sp1C)[func_150ADA20() & 3];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")
s32 func_151D9450(s32, s32);                        /* extern */
s32 func_151D9534(s32, s32);                        /* extern */
extern s32 D_800BE9E4;
f32 func_151423D8(u8);

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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9450 CURRENT (1936) */
s32 func_151D9450(s32 arg0, s32 arg1) {
    s32 sp18;
    u8 temp_a0;
    s32 temp_v1;

    temp_v1 = arg0 + 0xA8;
    if (*(u8 *)(arg0 + 0xC1) & 1) {
        return 1;
    }
    temp_a0 = *(u8 *)(temp_v1 + 4) + (*(s8 *)(temp_v1 + 6) * D_800BE9E4);
    *(u8 *)(temp_v1 + 4) = temp_a0;
    *(u8 *)(temp_v1 + 5) = (u8)(*(u8 *)(temp_v1 + 5) + (*(s8 *)(temp_v1 + 7) * D_800BE9E4));
    sp18 = temp_v1;
    *(f32 *)(arg0 + 0x38) = (func_151423D8((temp_a0 - 0x40) & 0xFF) * *(f32 *)(temp_v1 + 8)) + *(f32 *)(arg0 + 0xA8);
    *(f32 *)(arg0 + 0x3C) = (func_151423D8((*(u8 *)(sp18 + 5) - 0x40) & 0xFF) * *(f32 *)(sp18 + 0xC)) + *(f32 *)(arg0 + 0xA8);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9450 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9450.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9534.s")
typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
} Game2062D0Septuple;

extern Game2062D0Septuple D_800AB350;

u8 func_151D97A8(void) {
    Game2062D0Septuple sp1C;

    sp1C = D_800AB350;
    return *((u8 *)&sp1C + ((func_150ADA20() % 7U) * 4) + 3);
}

typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
} Game2062D0Triple;

typedef union {
    struct {
        u32 field_0;
        u32 field_4;
        u32 field_8;
        u32 field_C;
    } fields;
    u64 alignment;
} Game2062D0Quad;

extern Game2062D0Triple D_800AB36C;
extern Game2062D0Triple D_800AB378;
extern Game2062D0Triple D_800AB3A8;
extern Game2062D0Triple D_800AB3BC;
extern Game2062D0Triple D_800AB3CC;
extern Game2062D0Quad D_800AB3D8;

u8 func_151D9820(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB36C;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
u8 func_151D9878(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB378;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
extern s32 func_150ADA20();
extern s32 D_800AB384[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D98D0 CURRENT (245) */
u8 func_151D98D0(void) {
    struct {
        u8 pad[8];
        s32 values[2];
    } sp20;

    sp20.values[0] = D_800AB384[0];
    sp20.values[1] = D_800AB384[1];
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D98D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D98D0.s")
extern s32 func_150ADA20();
extern s32 D_800AB38C[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9918 CURRENT (245) */
u8 func_151D9918(void) {
    struct {
        u8 pad[8];
        s32 values[2];
    } sp20;

    sp20.values[0] = D_800AB38C[0];
    sp20.values[1] = D_800AB38C[1];
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9918.s")
typedef struct Game2062D0Quint {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
} Game2062D0Quint;

extern Game2062D0Quint D_800AB394;

u8 func_151D9960(void) {
    Game2062D0Quint sp1C;

    sp1C = D_800AB394;
    return *((u8 *)&sp1C + ((func_150ADA20() % 5U) * 4) + 3);
}
u8 func_151D99C8(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3A8;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
extern s32 func_150ADA20();
extern s32 D_800AB3B4[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9A20 CURRENT (245) */
u8 func_151D9A20(void) {
    struct {
        u8 pad[8];
        s32 values[2];
    } sp20;

    sp20.values[0] = D_800AB3B4[0];
    sp20.values[1] = D_800AB3B4[1];
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9A20.s")
u8 func_151D9A68(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3BC;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
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
u8 func_151D9ADC(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3CC;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
u8 func_151D9B34(void) {
    Game2062D0Quad sp20;
    s32 pad;

    sp20 = D_800AB3D8;
    return *((u8 *)&sp20 + ((func_150ADA20() & 3) * 4) + 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9EB0.s")
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);
void func_151DA08C(u8, f32, s32, u8, s32, s32, f32 *, s32, s32);
extern f32 D_800AB46C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9FC0 CURRENT (1544) */
void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, f32 *arg4,
                   u8 arg5, s32 arg6) {
    register u8 kind;

    kind = arg0 & 0xFF;
    arg0 = kind;
    func_151DBCBC(kind, arg1 * 0.5f, arg2, arg3, arg4, (s32)arg5,
                  arg6);
    if ((arg0 != 5) && (arg0 != 2)) {
        func_151DA08C(arg0, arg1 * D_800AB46C, 0x3F8147AE, arg2, 0x64,
                      arg3, arg4, (s32)arg5, arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9FC0 */
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
void func_151D9FC0(u8, f32, u8, s32, f32 *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DAA88 CURRENT (653) */
s32 func_151DAA88(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                  s32 arg5) {
    typedef struct {
        f32 field_0;
        u8 pad_4[4];
        f32 field_8;
        u8 pad_C[8];
    } Entry;
    u8 *saved_state;
    f32 position[3];
    Entry *table;
    u8 *state;

    table = *(Entry **)((u8 *)arg0 + 0x94);
    state = *(u8 **)((u8 *)arg0 + 0x98);
    position[1] = arg4;
    position[0] = table[*(s8 *)((u8 *)arg0 + 0x2D)].field_0;
    position[2] = table[*(s8 *)((u8 *)arg0 + 0x2D)].field_8;
    saved_state = state;
    func_151D9FC0(state[0x50], (*(f32 *)state * 11.0f) *
                    *(f32 *)(state + 0x4C), state[0x1B], arg5, position,
                    *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    saved_state[0x20] = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DAA88 */
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
void func_151DB27C(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x14) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x15) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x16) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x18) = 0xB4;
    *(u8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x1A) = 0xC8;
}
void func_151DB2A8(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x14) = 0;
    *(u8 *)((u8 *)arg0 + 0x15) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x16) = 0;
    *(u8 *)((u8 *)arg0 + 0x18) = 0;
    *(u8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x1A) = 0;
}
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
f32 func_150ADA68(void);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 random_f;
    s32 random_i;
    u8 pad_8[7];
    u8 type;
    f32 position[3];
} Game2062D0Spawn;

void func_151DBBD4(f32 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4) {
    Game2062D0Spawn spawn;

    spawn.position[0] = arg0[0];
    spawn.position[1] = arg0[1] + 5.0f;
    spawn.position[2] = arg0[2];
    spawn.type = *arg2;
    spawn.random_f = func_150ADA68();
    spawn.random_i = func_150ADA20();
    func_151D9B8C(
        spawn.type,
        (spawn.random_f * 25.0f) + 10.0f,
        ((spawn.random_i % 56U) + 0xC8) & 0xFF,
        arg1 + 4,
        spawn.position,
        (func_150ADA20() % 151U) + 0x96,
        0,
        1,
        0,
        arg3,
        arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBCBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBE80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC484.s")
