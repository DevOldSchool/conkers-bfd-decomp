#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_77BE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1504A730
 * - func_1504B0FC
 * - func_1504BE2C
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

void func_1504ADD0(void) {
    s32 i;
    u8 *p;
    u8 sp48[6];

    if (D_800C35EA != 1) {
        for (i = 0; i < 25; i++) {
            p = &D_800CC2D0[i * 0x32C];
            if (*(s32 *)p == 0) {
                continue;
            }
            D_800C3E78 = i;
            D_800D154C = p;
            if (i < D_8008FD8C) {
                if (i < 4) {
                    D_800CC284 = D_800BE728[i];
                } else {
                    func_100226F0(sp48, 6);
                    D_800CC284 = sp48;
                }
            }
            switch (p[4]) {
            case 0x28:
            case 0x77:
                func_150ED578(p);
                break;
            }
        }
    }
}
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

void func_1504AF10(Game77BE0AttachmentActor *arg0, s32 arg1, s32 arg2) {
    s32 selected;
    s32 index;
    s32 type;
    Game77BE0Attachment *entry;

    if (arg0->attachment && ((arg1 != 0) || ((arg0->attachment >> 15) == 0))) {
        selected = arg0->attachment & 0x7FFF;
        type = (arg0->attachment >> 12) & 7;
        if (type == 0) {
            type = func_1504AEF4(selected, (s32)&index);
            if (type != 0) {
                arg0->attachment = (type << 12) | index;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_77BE0/func_1504B0FC.s")
extern s8 D_80099140[];
extern f32 D_800991D4;

void func_1504BA38(void *arg0) {
    u8 i;
    s8 *entry;

    if (*(f32 *)((u8 *)arg0 + 0x28) > 10.0f) {
        *(s16 *)((u8 *)arg0 + 0xCE) = 0;
        return;
    }
    i = *(s32 *)((u8 *)arg0 + 0x184) & 0x1F;
    entry = &D_80099140[i * 3];
    if (entry[2] != 0 && *(u8 *)((u8 *)arg0 + 0xAA) == 0) {
        *(u8 *)((u8 *)arg0 + 0xAA) = entry[2];
    }
    if (entry[1] == 0) {
        *(s16 *)((u8 *)arg0 + 0xCE) = entry[0];
        return;
    }
    *(s16 *)((u8 *)arg0 + 0xCE) = (entry[0] - *(f32 *)((u8 *)arg0 + 0x3C)) * (entry[1] * D_800991D4);
}
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
extern void func_1505E650(u8 *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);

void func_1504BB88(u8 *arg0) {
    s32 var_v0;

    var_v0 = *(s32 *)(arg0 + 0x25C);
    if (var_v0 & 0x10) {
        arg0[0x83] = 0xFF;
        arg0[0x89] = 0xFF;
        if (*(s32 *)arg0 == 1) {
            func_1505E650(arg0, 0xD6, 1.15f, 3.0f, 0.0f, 0.0f, 0);
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

typedef struct Game77BE0State {
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

f32 func_150AD78C(f32);
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
void func_15064A14(void *);
s32 func_15064B94(u8 *, f32, f32, s32, f32);
extern f32 D_800991DC;
extern f32 D_800991E0;
extern f32 D_800991E4;
extern f32 D_800991E8;
extern f32 D_800991EC;
extern f32 D_800991F0;
extern f32 D_800991F4;
extern f32 D_800991F8;
extern f32 D_800991FC;
extern f32 D_80099200;
extern u8 D_800CC27C;
extern u8 D_800CC2B1;
extern s32 D_800CC2BC;
extern f32 D_800D1550;

void func_1504C0E8(u8 *arg0, s32 arg1, f32 arg2) {
    f32 blend;
    f32 start;
    f32 vel;
    s32 pressed;
    f32 speed;
    s32 anim;
    u8 *st;

    f32 diff;

    if ((s16)D_800CC2B2 == 0 && (st = *(u8 **)(arg0 + 0x31C), *(s16 *)(st + 0x12) >= -29) && *(s16 *)(st + 0x12) < 30) {
        *(s16 *)(st + 0x12) = 0;
    } else {
        st = *(u8 **)(arg0 + 0x31C);
        diff = (s16)D_800CC2B2 - *(s16 *)(st + 0x12);
        diff = (D_800D1550 / D_800CC2B4) * diff;
        *(s16 *)(st + 0x12) += (s16)(s32)diff;
    }
    st = *(u8 **)(arg0 + 0x31C);
    if (*(st + 0x6B) != 0) {
        return;
    }
    anim = 999;
    if (arg0[0x65] != 0 && arg0[0x104] == 0) {
        func_15064A14(arg0);
        return;
    }
    if (arg0[0x81] == 0 && arg0[0x104] == 0 && arg0[0xAD] == 0) {
        if (arg0[0x83] == 0 && *(st + 0x11A) != 3) {
            arg0[0x80] = 1;
            arg0[0x100] &= 0xF3;
            D_800CC2BC |= 0x80;
            speed = 1.0f;
            start = 0.0f;
            blend = 4.0f;
            vel = *(f32 *)(arg0 + 0x3C) * D_800991DC + arg2 * D_800991E0;
            st = *(u8 **)(arg0 + 0x31C);
            if (*(s16 *)(st + 0x46) > 0 || *(st + 0x4E) != 0 || arg0[0x13C] >= 100 || arg1 != 0 ||
                (*(u16 *)(st + 0x32) & 3) || *(st + 0x78) != 0 || *(st + 0x1A) != 0 ||
                *(s16 *)(st + 8) > 0 || *(st + 0x17) != 0) {
                if (func_15064B94(arg0, vel, vel, arg1, arg2) != 0) {
                    return;
                }
                st = *(u8 **)(arg0 + 0x31C);
            }
            pressed = *(u16 *)D_800CC284 & 0x2000;
            if (pressed == 0 || D_800CC2B1 != 0 || *(st + 0x78) != 0 || (*(st + 0x4E) & 0xF) == 1) {
                if (*(f32 *)(arg0 + 0x3C) > 4.0f) {
                    *(st + 0x37) = 0;
                    st = *(u8 **)(arg0 + 0x31C);
                }
                pressed = *(st + 0x4E);
                if ((*(st + 0x4E) == 1 || pressed == 0x81) && vel > 1.0f) {
                    arg2 = 10.0f;
                    anim = 0x302;
                    speed = *(f32 *)(arg0 + 0x3C) / 7.0f + D_800991E4;
                    if (*(f32 *)(arg0 + 0x3C) > 23.0f) {
                        anim = 0x303;
                        speed = *(f32 *)(arg0 + 0x3C) / 23.0f + D_800991E8;
                    }
                } else if (*(s8 *)(st + 0x4A) > 0 && vel >= 5.0f) {
                    anim = 0x2B;
                    speed = vel / 12.0f;
                } else if (*(s8 *)(st + 0x4B) > 0 && vel >= 5.0f) {
                    anim = 0xDF;
                    speed = vel / 12.0f;
                } else if (*(f32 *)(arg0 + 0x118) != D_800991EC && *(f32 *)(arg0 + 0x18) < *(f32 *)(arg0 + 0x118) &&
                           *(f32 *)(arg0 + 0x3C) >= 1.0f && *(st + 0x4E) == 0) {
                    speed = vel / 18.0f + D_800991F0;
                    anim = 0x8B;
                    arg0[0xAA] = 0x4B;
                } else if (vel > 14.0f) {
                    anim = (D_800BE9F0 != 4) ? 2 : 0x1B2;
                    speed = vel / 23.0f + D_800991F4;
                } else if (vel > 6.0f || (arg2 < 1.0f && *(f32 *)(arg0 + 0x3C) > 1.0f)) {
                    anim = 1;
                    speed = vel * 0.125f + D_800991F8;
                } else if (vel > 1.0f) {
                    blend = 15.0f;
                    anim = (arg0[4] == 0x80) ? 1 : 0;
                    speed = vel * 0.125f + D_800991FC;
                } else {
                    anim = func_1504C078();
                }
                if (*(f32 *)(arg0 + 0x28) > 60.0f && *(*(u8 **)(arg0 + 0x31C) + 0x4E) == 0) {
                    speed = 0.5f;
                    anim = 0x38;
                    arg0[0x100] |= 0x10;
                }
                if (*(f32 *)(arg0 + 0x3C) > 18.0f && *(*(u8 **)(arg0 + 0x31C) + 0x11A) != 1 && *(*(u8 **)(arg0 + 0x31C) + 0x11A) != 3 && arg2 == 0.0f &&
                    *(f32 *)(arg0 + 0x28) == 0.0f && D_800CC27C == 0) {
                    speed = 0.5f;
                    anim = 0x21;
                    blend = 3.0f;
                    arg0[0x89] = 8;
                    arg0[0x83] = 0x11;
                }
            } else if (pressed != 0) {
                if (*(f32 *)(arg0 + 0x3C) < 3.0f) {
                    *(st + 0x37) = 1;
                }
                if (*(f32 *)(arg0 + 0x44) > D_80099200 && *((st = *(u8 **)(arg0 + 0x31C)) + 0x37) != 0) {
                    *(s32 *)(st + 4) = 1;
                    arg0[0xAA] = 0x28;
                    blend = 5.0f;
                    speed = *(f32 *)(arg0 + 0x44) / 15.0f + 0.5f;
                    anim = func_1504C0B8();
                } else {
                    blend = 6.0f;
                    speed = 1.5f;
                    anim = 0x16;
                }
            }
        }
        if (anim != 999) {
            func_1505E650(arg0, anim & 0xFFFF, speed, blend, start, 0.0f, 0);
        }
    } else if (*(u16 *)(arg0 + 0x84) == 0x21 && D_800CC2B1 == 0 && *(f32 *)(arg0 + 0x44) == 0.0f &&
               (*(u16 *)D_800CC284 & 0x2000)) {
        func_1505E650(arg0, 0x16, 1.5f, 6.0f, 0.0f, 0.0f, 0);
    }
}

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

s32 func_1504C8BC(void *arg0) {
    void *temp_v1;

    temp_v1 = ((Game77BE0State *)arg0)->field_31C;
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
            D_800BE9E4 += (u32)*((u8 *)((Game77BE0State *)arg0)->field_31C + 0x1A8);
            D_800BE9A4 = (f32)D_800BE9E4 * 0.5f;
            if (D_800BE9A4 != 0.0f) {
                D_800BE9A8 = 1.0f / D_800BE9A4;
            } else {
                D_800BE9A8 = 0.0f;
            }
            *((u8 *)((Game77BE0State *)arg0)->field_31C + 0x1A8) = 0;
            return 2;
        }
        return 1;
    }
    *((u8 *)temp_v1 + 0x1A8) += (u32)D_800BE9E4;
    return 0;
}
void func_1504C9E4(void *arg0, s8 arg1, u8 arg2) {
    s32 diff;
    s32 old;
    s32 step;

    diff = ((*(s8 *)((u8 *)arg0 + 0x1D1) - arg1) & 0xFF);
    if (diff != 0) {
        step = 3;
        if (arg2 == 0x10) {
            step = 6;
        }
        old = diff;
        if (diff >= 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) += step;
        } else {
            *(s8 *)((u8 *)arg0 + 0x1D1) -= step;
        }
        diff = (*(s8 *)((u8 *)arg0 + 0x1D1) - arg1) & 0xFF;
        if ((old ^ diff) & 0x80) {
            *(s8 *)((u8 *)arg0 + 0x1D1) = arg1;
        }
    }
}
