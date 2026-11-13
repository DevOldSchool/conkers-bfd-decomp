#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>

/*
 * Reviewed source unit: src/game/game_623D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15035808
 * - func_15036148
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_800C3F00;

void func_15034F20(void) {
    D_800C3F00 = 0;
}
void func_10023A10(void *, void *, s32);
void func_150A7A48(void *, void *, void *);
void func_151EFD00(void *, void *);
void func_151EFEB8(void *, void *);
void func_15034728(void *);
void func_150A7BC0(void *);
void func_150A8050(void *, f32, f32, f32);
s32 func_150AD960(s32, s32, s32, s32);

void func_15034F30(u8 *arg0, u8 *arg1, s32 arg2, f32 (*arg3)[4][4], f32 (*arg4)[4][4], s32 arg5,
                   f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12,
                   f32 arg13, f32 arg14, f32 arg15, f32 arg16, s32 arg17, s32 arg18) {
    f32 flip[4][4];
    f32 rotA[4][4];
    f32 rotB[4][4];
    s32 i;
    f32 (*src)[4];
    f32 dist;
    f32 temp[4][4];
    void *saved;

    func_150A7BC0(flip);
    if (arg2 == 1 || arg2 == 0) {
        flip[1][1] = -1.0f;
        for (i = 0; i < arg5; i++) {
            if (arg17 != 0) {
                func_151EFEB8(temp, (i << 6) + (u8 *)arg3);
                src = temp;
            } else {
                arg3[i][0][3] = 0.0f;
                arg3[i][1][3] = 0.0f;
                arg3[i][2][3] = 0.0f;
                arg3[i][3][3] = 1.0f;
                src = (void *)((i << 6) + (u8 *)arg3);
            }
            func_150A7A48(src, flip, arg4[i]);
            arg4[i][3][1] = src[3][1] - 2.0f * (src[3][1] - arg7);
            if (arg18 != 0) {
                func_10023A10((i << 6) + (u8 *)arg4, temp, 0x40);
                func_151EFD00(temp, (i << 6) + (u8 *)arg4);
            }
        }
        dist = arg12 - arg7;
        if (arg15 < dist) {
            arg1[4] = 0;
        } else if (dist < arg14) {
            if (arg2 == 0) {
                if (dist < 10.0f) {
                    arg1[4] = arg16 / 10.0f * dist;
                } else {
                    arg1[4] = arg16;
                }
            } else {
                arg1[4] = arg16;
            }
        } else {
            dist -= arg14;
            dist = arg16 * dist / (arg15 - arg14);
            dist = arg16 - dist;
            arg1[4] = dist;
        }
    } else if (arg2 == 2) {
        flip[0][0] = -1.0f;
        func_150A8050(rotA, 0.0f, -arg10, 0.0f);
        func_150A8050(rotB, 0.0f, arg10, 0.0f);
        for (i = 0; i < arg5; i++) {
            if (arg17 != 0) {
                func_151EFEB8(temp, (i << 6) + (u8 *)arg3);
                src = temp;
            } else {
                arg3[i][0][3] = 0.0f;
                arg3[i][1][3] = 0.0f;
                arg3[i][2][3] = 0.0f;
                arg3[i][3][3] = 1.0f;
                src = (void *)((i << 6) + (u8 *)arg3);
            }
            func_10023A10(src, arg4[i], 0x40);
            arg4[i][3][0] -= arg6;
            arg4[i][3][1] -= arg7;
            arg4[i][3][2] -= arg8;
            func_150A7A48(arg4[i], rotA, arg4[i]);
            func_150A7A48(arg4[i], flip, arg4[i]);
            func_150A7A48(arg4[i], rotB, arg4[i]);
            arg4[i][3][0] += arg6;
            arg4[i][3][1] += arg7;
            arg4[i][3][2] += arg8;
            if (arg18 != 0) {
                func_10023A10((i << 6) + (u8 *)arg4, temp, 0x40);
                func_151EFD00(temp, (i << 6) + (u8 *)arg4);
            }
        }
        dist = func_150AD960(arg6, arg8, arg11, arg13);
        if (arg15 < dist) {
            arg1[4] = 0;
        } else if (dist < arg14) {
            arg1[4] = arg16;
        } else {
            dist -= arg14;
            dist = arg16 * dist / (arg15 - arg14);
            dist = arg16 - dist;
            arg1[4] = dist;
        }
    } else {
        return;
    }
    if (arg0 != NULL && *(s32 *)(arg0 + 0x9C) != 0) {
        saved = *(void **)(arg0 + 0x1D4);
        *(void **)(arg0 + 0x1D4) = arg4;
        func_15034728(arg0);
        *(void **)(arg0 + 0x1D4) = saved;
    }
}
extern u8 D_800C3F08[];

void *func_150356C8(void) {
    u8 count;

    count = D_800C3F00;
    if (count == 0xF) return 0;
    D_800C3F00 = count + 1;
    return ((u8)D_800C3F00 * 0xC) - 0xC + D_800C3F08;
}
s32 func_150A6360(void *, void *, f32, f32, f32, f32, f32, f32);
extern f32 D_80097D70;
extern s32 D_800BE628;
extern void *D_800D1C90[];
extern u8 D_800D9C10;

s32 func_15035714(s32 arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 var_fv0;
    f32 var_fv1;
    s32 sp28;
    u8 *temp_v0;
    s32 index;
    f32 delta;

    sp28 = D_800BE628;
    index = arg1[4];
    temp_v0 = D_800D1C90[index];
    var_fv0 = (f32)(u32)*(u16 *)(temp_v0 + 0xE);
    temp_ft4 = var_fv0;
    temp_ft5 = var_fv0;
    temp_ft4 *= *(f32 *)(arg1 + 0x14C);
    temp_ft5 *= *(f32 *)(arg1 + 0x150);
    temp_fa0 = *(f32 *)(arg1 + 0x150) * (f32)*(s16 *)(temp_v0 + 0x10);
    if ((arg0 == 1) || (arg0 == 0)) {
        delta = (*(f32 *)(arg1 + 0x18) + temp_fa0) - arg3;
        var_fv1 = arg3 - delta;
    } else {
        var_fv1 = *(f32 *)(arg1 + 0x18) + temp_fa0;
    }
    if (func_150A6360((void *)sp28, &D_800D9C10,
                      *(f32 *)(arg2 + 0x30), var_fv1,
                      *(f32 *)(arg2 + 0x38), temp_ft4, temp_ft5,
                      D_80097D70) == 0) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035808.s")
typedef struct Game35D6CCommand { u32 word0, word1; } Game35D6CCommand;
extern u8 D_80082FC0[], D_80083140[];

Gfx *func_15035D6C(Gfx *gdl, u8 *arg1, s32 r, s32 g, s32 b) {
    u8 *entry;
    s32 alpha;
    s32 i;
    s32 j;

    if ((u8)D_800C3F00 == 0) {
        return gdl;
    }
    gSPSetGeometryMode(gdl++, 0x200);
    for (i = 0; i < (u8)D_800C3F00; i++) {
        entry = &D_800C3F08[i * 12];
        if (entry[11] != 1) {
            continue;
        }
        if (arg1[0] != entry[9]) {
            continue;
        }
        if (arg1[6] != entry[10]) {
            continue;
        }
        alpha = (arg1[3] * entry[4]) >> 8;
        gDPPipeSync(gdl++);
        gSPSegment(gdl++, 3, *(u32 *)entry);
        gDPSetEnvColor(gdl++, r, g, b, alpha);
        if (alpha < 255) {
            gSPSegment(gdl++, 8, D_80082FC0);
        } else {
            gSPSegment(gdl++, 8, D_80083140);
        }
        for (j = 0; j < arg1[0x14]; j++) {
            if (!(arg1[0x13] & (1 << j))) {
                gSPDisplayList(gdl++, (*(Gfx ***)(arg1 + 0x24))[j]);
            }
        }
    }
    gSPClearGeometryMode(gdl++, 0x200);
    return gdl;
}

typedef struct Game623D0Entry {
    s32 word;
    u8 field4;
    u8 field5;
    u8 field6;
    u8 field7;
    u8 field8;
    u8 pad9[2];
    u8 fieldB;
} Game623D0Entry;

void *func_1502CCFC(void *, u8, void *, s32, s32, s32 *, s32, s32);

void *func_15035FE8(Game35D6CCommand *gfx, void *arg1) {
    Game623D0Entry *entry;
    s32 colors[4];
    s32 i;

    if ((u8)D_800C3F00 == 0) {
        return gfx;
    }
    { Game35D6CCommand *g = gfx++; g->word0 = 0xD9FFFFFF; g->word1 = 0x200004; }
    { Game35D6CCommand *g = gfx++; g->word0 = 0xD9EEFFFF; g->word1 = 0; }
    { Game35D6CCommand *g = gfx++; g->word0 = 0xE2001E01; g->word1 = 0; }
    for (i = 0; i < (u8)D_800C3F00; i++) {
        entry = &((Game623D0Entry *)D_800C3F08)[i];
        if (entry->fieldB != 0) {
            continue;
        }
        colors[0] = entry->field5;
        colors[1] = entry->field6;
        colors[2] = entry->field7;
        colors[3] = 0xFF;
        gfx = func_1502CCFC(gfx, entry->field8, arg1, entry->word, entry->field4, colors, 0, 1);
    }
    return gfx;
}
typedef struct Game623D0Actor {
    s32 active;
    u8 pad4;
    u8 kind;
    u8 pad6[0xE];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[8];
    f32 speed;
    u8 pad2C[0xEC];
    f32 surface;
    u8 pad11C[0x64];
    f32 floor;
} Game623D0Actor;

void func_15035808(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
extern f32 D_80097D74;
extern u8 D_800CC2D0[];
extern u8 *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15036148 CURRENT (328) */
void func_15036148(void) {
    Game623D0Actor *actor;
    s16 height;
    s16 output1;
    s16 output2;
    f32 missingSurface;
    s32 index;

    actor = (Game623D0Actor *)D_800CC2D0;
    index = 0;
    if (!(*(s32 *)(D_800DBFF0 + 0x5F0) & 1)) {
        missingSurface = -10000.0f;
        do {
            if (actor->active != 0 && (actor->kind == 0 || actor->kind == 1)) {
                if (missingSurface != actor->surface && actor->surface < actor->y &&
                    actor->floor < actor->surface && actor->speed > 5.0f) {
                    func_1507C3E0(actor, &height, &output1, &output2);
                    if ((f32)height < actor->surface - actor->floor) {
                        func_15035808(1, index, actor->x, actor->surface,
                                       actor->z, 0.0f, 0.0f, 100.0f,
                                       150.0f, 127.0f);
                    }
                }
            }
            index++;
            actor = (Game623D0Actor *)((u8 *)actor + 0x32C);
        } while (index != 25);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15036148 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15036148.s")
