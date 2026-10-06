#include "types.h"

/*
 * Reviewed source unit: src/game/game_77BE0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1504A730
 * - func_1504ADD0
 * - func_1504AF10
 * - func_1504B0FC
 * - func_1504BA38
 * - func_1504BE2C
 * - func_1504C0E8
 * - func_1504C8BC
 * - func_1504C9E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504A730.s")
void func_100226F0(void *, s32);
void func_150ED578(void *);
extern s8 D_8008FD8C;
extern void **D_800BE728;
extern u8 D_800C35EA;
extern s8 D_800C3E78;
extern u8 D_800CC2D0[];
extern void *D_800CC284;
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504ADD0 CURRENT (900) */
void func_1504ADD0(void) {
    u8 sp48[6];
    s32 var_s0;
    u8 *var_s1;
    u8 temp_v0;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = D_800CC2D0;
        do {
            if (*(s32 *)var_s1 != 0) {
                D_800C3E78 = var_s0;
                D_800D154C = var_s1;
                if (var_s0 < D_8008FD8C) {
                    if (var_s0 < 4) {
                        D_800CC284 = D_800BE728[var_s0];
                    } else {
                        func_100226F0(&sp48, 6);
                        D_800CC284 = &sp48;
                    }
                }
                temp_v0 = var_s1[4];
                if ((temp_v0 == 0x28) || (temp_v0 == 0x77)) {
                    func_150ED578(var_s1);
                }
            }
            var_s0++;
            var_s1 += 0x32C;
        } while (var_s0 != 0x19);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504ADD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504ADD0.s")
s32 func_1504AEF4(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    return 0;
}
typedef struct Game77BE0AttachmentActor {
    u8 pad0[0x14];
    f32 position[3];
    u8 pad20[0x70];
    s16 height;
    u16 attachment;
} Game77BE0AttachmentActor;

typedef struct Game77BE0Attachment {
    u8 pad0[0x10];
    s16 position[3];
    u8 pad16[0x38];
    s8 owner;
    u8 flags;
    u8 pad50[0x50];
} Game77BE0Attachment;

extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504AF10 CURRENT (680) */
void func_1504AF10(Game77BE0AttachmentActor *arg0, s32 arg1, s32 arg2) {
    s32 selected;
    s32 index;
    s32 type;
    s32 attachment;
    Game77BE0Attachment *entry;

    attachment = arg0->attachment;
    if ((attachment != 0) && ((arg1 != 0) || ((attachment >> 15) == 0))) {
        type = attachment >> 12;
        type &= 7;
        selected = attachment & 0x7FFF;
        if (type == 0) {
            selected = func_1504AEF4(selected, (s32)&index);
            type = selected;
            if (selected != 0) {
                arg0->attachment = (selected << 12) | index;
            }
        }
        index = arg0->attachment & 0xFFF;
        if (type == 3) {
            if (arg2 != 0) {
                ((Game77BE0Attachment *)D_800DBEF4)[index].owner = 0;
                arg0->attachment = 0;
                return;
            }
            ((Game77BE0Attachment *)D_800DBEF4)[index].owner =
                ((u8 *)arg0 - D_800CC2D0) / 0x32C + 0x64;
            if (arg1 != 0) {
                ((Game77BE0Attachment *)D_800DBEF4)[index].owner = 0;
                return;
            }
            entry = &((Game77BE0Attachment *)D_800DBEF4)[index];
            entry->flags &= 0xFF9F;
            entry = &((Game77BE0Attachment *)D_800DBEF4)[index];
            entry->flags |= 0x20;
            ((Game77BE0Attachment *)D_800DBEF4)[index].position[0] = (s32)arg0->position[0];
            ((Game77BE0Attachment *)D_800DBEF4)[index].position[1] = (s32)(arg0->position[1] + arg0->height);
            ((Game77BE0Attachment *)D_800DBEF4)[index].position[2] = (s32)arg0->position[2];
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504AF10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504AF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504B0FC.s")
extern s8 D_80099140[];
extern f32 D_800991D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504BA38 CURRENT (150) */
void func_1504BA38(void *arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s8 *entry;
    f32 scale;

    if (*(f32 *)((u8 *)arg0 + 0x28) > 10.0f) {
        *(s16 *)((u8 *)arg0 + 0xCE) = 0;
        return;
    }
    entry = D_80099140 + ((*(s32 *)((u8 *)arg0 + 0x184) & 0x1F) * 3);
    temp_a1 = entry[2];
    if ((temp_a1 != 0) && (*(u8 *)((u8 *)arg0 + 0xAA) == 0)) {
        *(u8 *)((u8 *)arg0 + 0xAA) = temp_a1;
    }
    temp_v0 = entry[1];
    if (temp_v0 == 0) {
        *(s16 *)((u8 *)arg0 + 0xCE) = entry[0];
        return;
    }
    scale = (f32)temp_v0 * D_800991D4;
    *(s16 *)((u8 *)arg0 + 0xCE) = (s16)(s32)(scale *
        ((f32)entry[0] - *(f32 *)((u8 *)arg0 + 0x3C)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504BA38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BA38.s")
void func_1506EBC0(void);
void func_1507490C(void);
extern u8 D_800CC2D0[];
extern s32 D_800D1580;

void func_1504BAF0(void *arg0) {
    s16 temp_v0;
    u8 temp_v0_2;
    u8 *temp_v1;

    temp_v0 = (s16)(*(u8 *)((u8 *)arg0 + 0x13C) - 0x64);
    if (temp_v0 >= 0) {
        temp_v1 = D_800CC2D0 + (temp_v0 * 0x32C);
        if ((*(u8 *)(temp_v1 + 0x13D) >= 0x64) &&
            ((temp_v0_2 = *(u8 *)(temp_v1 + 4), temp_v0_2 == 0xA8) || (temp_v0_2 == 0xA9))) {
            D_800D1580 = 3;
            func_1507490C();
        }
    }
    func_1506EBC0();
}
extern void func_1504BAF0(void *arg0);
extern void func_1505E650(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

void func_1504BB88(u8 *arg0) {
    s32 var_v0;

    var_v0 = *(s32 *)(arg0 + 0x25C);
    if (var_v0 & 0x10) {
        arg0[0x83] = 0xFF;
        arg0[0x89] = 0xFF;
        if (*(s32 *)arg0 == 1) {
            func_1505E650(arg0, 0xD6, 0x3F933333, 0x40400000, 0.0f, 0.0f, 0);
        }
        var_v0 = (*(s32 *)(arg0 + 0x25C) &= ~0x10);
    }
    if (var_v0 & 2) {
        if (arg0[0x13C] != 0) {
            func_1504BAF0(arg0);
            var_v0 = *(s32 *)(arg0 + 0x25C);
        }
        *(s32 *)(arg0 + 0x25C) = var_v0 & ~2;
    }
}
typedef struct {
    u8 pad0[0x44];
    s8 field44;
    u8 pad45[5];
    s8 field4A;
    s8 field4B;
    u8 pad4C[6];
    u8 field52;
    u8 pad53;
    s8 field54;
    s8 field55;
    u8 pad56[0x34];
    s16 field_8A;
    u16 field_8C;
    s8 field_8E;
    s8 field_8F;
    u8 pad90[0x10E];
    u16 field19E;
    u16 field1A0;
} Game77BE0TimerState;

typedef struct {
    u8 pad0[0x89];
    u8 field89;
    u8 field8A;
    u8 pad8B[0x23];
    u8 fieldAE;
    u8 padAF[0x58];
    u8 field107;
    u8 pad108[0x1D];
    u8 field125;
    u8 pad126[0xAA];
    s8 field1D0;
    u8 pad1D1[0x57];
    u8 field228;
    u8 pad229[0xF3];
    Game77BE0TimerState *field_31C;
} Game77BE0State;

extern u8 D_800BE9A0;
extern s32 D_800BE9E4;

void func_1504BC38(Game77BE0State *arg0) {

    if (arg0->field89 != 0 && arg0->field89 < 250) {
        if (D_800BE9A0 >= arg0->field89) arg0->field89 = 0;
        else arg0->field89 = arg0->field89 - D_800BE9A0;
    }
    if (arg0->field228 != 0) {
        s32 timer = arg0->field228;
        if (D_800BE9A0 >= arg0->field228) arg0->field228 = 0;
        else arg0->field228 = timer - D_800BE9A0;
    }
    if (arg0->fieldAE != 0) arg0->fieldAE = arg0->fieldAE - 1;
    if (arg0->field8A != 255) {
        if (D_800BE9A0 >= arg0->field8A) arg0->field8A = 0;
        else arg0->field8A = arg0->field8A - D_800BE9A0;
    }
    if (arg0->field125 != 255) {
        if (D_800BE9A0 >= arg0->field125) arg0->field125 = 0;
        else arg0->field125 = arg0->field125 - D_800BE9A0;
    }
    if (arg0->field_31C->field4A > 0) arg0->field_31C->field4A = arg0->field_31C->field4A - D_800BE9A0;
    if (arg0->field_31C->field4B > 0) arg0->field_31C->field4B = arg0->field_31C->field4B - D_800BE9A0;
    if (arg0->field_31C->field44 > 0) arg0->field_31C->field44 = arg0->field_31C->field44 - D_800BE9A0;
    if (arg0->field107 != 0) arg0->field107 = arg0->field107 - 1;
    if (arg0->field1D0 > 0) arg0->field1D0 = arg0->field1D0 - D_800BE9A0;
    if (arg0->field_31C->field54 > 0) arg0->field_31C->field54 = arg0->field_31C->field54 - D_800BE9A0;
    if (arg0->field_31C->field55 != 0) arg0->field_31C->field55 = arg0->field_31C->field55 - 1;
    arg0->field_31C->field52 >>= 1;
    if (arg0->field_31C->field19E != 0) {
        if (D_800BE9E4 < arg0->field_31C->field19E) arg0->field_31C->field19E = arg0->field_31C->field19E - D_800BE9E4;
        else arg0->field_31C->field19E = 0;
    }
    if (arg0->field_31C->field1A0 != 0) {
        if (D_800BE9E4 < arg0->field_31C->field1A0) {
            arg0->field_31C->field1A0 = arg0->field_31C->field1A0 - D_800BE9E4;
            return;
        }
        arg0->field_31C->field1A0 = 0;
    }
}

void func_1507EB2C(void *);
f32 func_150AD78C(f32);
u32 func_150ADA20(void);
extern f32 D_800991D8;
extern u16 D_800CC2B2;
extern f32 D_800CC2B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504BE2C CURRENT (1853) */
void func_1504BE2C(Game77BE0State *arg0, u16 *arg1, f32 *arg2, s8 *arg3) {
    f32 phase;
    u8 *state;
    u16 type;

    phase = (f32)(u32)*((u8 *)arg0->field_31C + 0xB) * D_800991D8;
    D_800CC2B4 = 16.0f;
    if (*((u8 *)arg0->field_31C + 0x16) != 0) {
        if (*((u8 *)arg0->field_31C + 0x16) == 0) {
            func_1507EB2C(arg0);
            *(s16 *)((u8 *)arg0->field_31C + 8) = 0;
        }
    }
    if (*(u16 *)((u8 *)arg0->field_31C + 0xE) == 0) {
        *(u16 *)((u8 *)arg0->field_31C + 0xE) = 0xA6;
    }
    *((u8 *)arg0->field_31C + 0x3C) = 5;
    if ((*arg2 > 4.0f) && (*(u16 *)((u8 *)arg0 + 0x84) == 0xAA)) {
        *((u8 *)arg0->field_31C + 0x3C) = 1;
        *(u16 *)((u8 *)arg0->field_31C + 0x10) = *arg1;
    }
    func_150AD78C(phase);
    state = (u8 *)arg0->field_31C;
    state[0xB] += 2;
    if (*((u8 *)arg0->field_31C + 0x16) != 0) {
        *((u8 *)arg0 + 0xAA) = 0x19;
    } else if (*(u16 *)((u8 *)arg0 + 0x84) == 0xA7) {
        *((u8 *)arg0 + 0xAA) = 0x32;
    } else {
        *((u8 *)arg0 + 0xAA) = 0x20;
    }
    type = *(u16 *)((u8 *)arg0 + 0x84);
    *(f32 *)((u8 *)arg0 + 0x54) *= 0.5f;
    if ((type == 0x2C) || (type == 0xE0)) {
        *arg3 = *((s8 *)D_800CC284 + 3) >> 1;
    } else {
        if (!(func_150ADA20() & 0x3F)) {
            *(s16 *)((u8 *)arg0->field_31C + 0x14) = func_150ADA20() % 25000U - 0x30D4;
        }
        D_800CC2B2 = *(u16 *)((u8 *)arg0->field_31C + 0x14);
        if (*((u8 *)arg0->field_31C + 0x16) != 0) {
            D_800CC2B2 = (s16)D_800CC2B2 / 3;
        }
    }
    if ((D_800C35EA == 0) && (*((u8 *)arg0->field_31C + 0x16) == 0)) {
        *(s16 *)((u8 *)arg0 + 0x282) = 0x1E;
        *((u8 *)arg0 + 0x276) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504BE2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504BE2C.s")

void func_1507F640(void);
extern void *D_800D154C;

s32 func_1504C078(void) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)D_800D154C + 0x31C);
    if (*(u8 *)((u8 *)temp_v0 + 0x58) != 1) {
        *(s8 *)((u8 *)temp_v0 + 0x59) = 0;
        func_1507F640();
    }
    return 0x3E7;
}
extern s32 D_800BE9F0;

s32 func_1504C0B8(void) {
    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E)) {
        return 0x18B;
    }
    return 0x1B;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C0E8.s")
extern u8 D_800BE9A0;
extern s32 D_800CC288;

void func_1504C854(Game77BE0State *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;
    Game77BE0TimerState *temp_v0;
    Game77BE0TimerState *temp_v0_2;

    D_800CC288 = arg0->field_31C->field_8C;
    temp_v0 = arg0->field_31C;
    temp_v1 = temp_v0->field_8E;
    if (temp_v1 > 0) {
        temp_v0->field_8E = temp_v1 - D_800BE9A0;
    } else {
        temp_v0->field_8A = 0;
    }
    temp_v0_2 = arg0->field_31C;
    temp_v1_2 = temp_v0_2->field_8F;
    if (temp_v1_2 > 0) {
        temp_v0_2->field_8F = temp_v1_2 - D_800BE9A0;
        return;
    }
    temp_v0_2->field_8C = 0;
}
extern f32 D_800BE9A4;
extern f32 D_800BE9A8;
extern s32 D_800BE9E4;
extern u8 D_800CC2B8;
extern s16 D_800CC2BA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504C8BC CURRENT (90) */
s32 func_1504C8BC(void *arg0) {
    void *temp_v1;
    s32 temp_t6;

    temp_v1 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v1 == 0) {
        return 1;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0 || D_800BE9F0 == 0x33 || *(s32 *)arg0 == 0x25) {
        *((u8 *)temp_v1 + 0x1A8) = 0;
        return 1;
    }
    if (D_800CC2B8 == (*((u8 *)arg0 + 0x127) & 1)) {
        if (*((u8 *)temp_v1 + 0x1A8) != 0) {
            D_800CC2BA = (s16)D_800BE9E4;
            temp_t6 = D_800BE9E4 + *((u8 *)*(void **)((u8 *)arg0 + 0x31C) + 0x1A8);
            D_800BE9E4 = temp_t6;
            D_800BE9A4 = (f32)temp_t6 * 0.5f;
            if (D_800BE9A4 != 0.0f) {
                D_800BE9A8 = 1.0f / D_800BE9A4;
            } else {
                D_800BE9A8 = 0.0f;
            }
            *((u8 *)*(void **)((u8 *)arg0 + 0x31C) + 0x1A8) = 0;
            return 2;
        }
        return 1;
    }
    *((u8 *)temp_v1 + 0x1A8) += D_800BE9E4;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504C8BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C8BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504C9E4 CURRENT (450) */
void func_1504C9E4(void *arg0, s8 arg1, u8 arg2) {
    s32 temp_t8;
    s32 var_a2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)arg0 + 0x1D1);
    temp_t8 = (temp_v1 - arg1) & 0xFF;
    if (temp_t8 != 0) {
        var_a2 = 3;
        if (arg2 == 0x10) {
            var_a2 = 6;
        }
        if (temp_t8 >= 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) = (s8) (temp_v1 + var_a2);
        } else {
            *(s8 *)((u8 *)arg0 + 0x1D1) = (s8) (temp_v1 - var_a2);
        }
        if ((temp_t8 ^ (*(s8 *)((u8 *)arg0 + 0x1D1) - arg1)) & 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) = arg1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504C9E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504C9E4.s")
