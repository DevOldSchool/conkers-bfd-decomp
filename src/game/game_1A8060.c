#include "types.h"
#include <PR/gbi.h>
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A8060.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517ABB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */


typedef struct {
    f32 blend;
    f32 rate;
    u8 prev;
    u8 cur;
    u8 hold;
} Game1A8060Blend;

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[0x1C8 - 0x5];
    u8 unk1C8;
    u8 pad1C9[0x260 - 0x1C9];
    Game1A8060Blend *blend;
    u8 pad264[0x28C - 0x264];
    s32 unk28C[2][2];
    u8 pad29C[0x32C - 0x29C];
} Game1A8060Actor;

typedef struct {
    u8 set;
    u8 slots;
    u16 vertexCounts[3];
} Game1A8060Config;

typedef struct {
    s32 resource;
    u8 timer;
} Game1A8060Entry;

extern Game1A8060Entry **D_800DD460[];
extern Game1A8060Actor D_800CC2D0[];
extern s32 D_800D19A0[];
extern s32 *D_800C4020[];
extern u8 D_800BE9C0;
extern s32 D_800BE9E4;
extern u8 D_800BEAC0;
void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
void func_10023D20(void *, s32);
s32 func_1502B5C8(s32 *, s32, ...);

extern u8 D_800A7230[];
extern u16 D_800C4310[];
void func_10004074(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517ABB0 CURRENT (2305) */
void func_1517ABB0(void) {
    u8 **groups = D_800DD460;
    u8 *configs = D_800A7230;
    u16 *counts = D_800C4310;
    s32 groupIndex = 0;

    do {
        u8 *config = configs + groupIndex * 8;
        if (*groups != 0) {
            s32 setIndex = 0;
            u16 setCount = counts[config[0]];
            if (setCount > 0) {
                do {
                    s32 entryIndex = 0;
                    u8 slotCount = config[1];
                    if (slotCount > 0) {
                        s32 setOffset = setIndex * 4;
                        s32 entryOffset = 0;
                        do {
                            u8 *entry = *(u8 **)(*groups + setOffset) + entryOffset;
                            s32 resource = *(s32 *)entry;
                            if (resource != 0) {
                                u8 timer = entry[4];
                                if (timer != 0) {
                                    entry[4] = timer - 1;
                                    slotCount = config[1];
                                } else {
                                    func_10004074(resource);
                                    *(s32 *)(*(u8 **)(*groups + setOffset) + entryOffset) = 0;
                                    slotCount = config[1];
                                }
                            }
                            entryIndex++;
                            entryOffset += 8;
                        } while (entryIndex < slotCount);
                        setCount = counts[config[0]];
                    }
                    setIndex++;
                } while (setIndex < setCount);
            }
        }
        groupIndex++;
        groups++;
    } while (groupIndex != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517ABB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A8060/func_1517ABB0.s")
s32 func_1517AD00(s32 arg0, s32 arg1, s32 arg2) {
    Game1A8060Blend *blend;
    Game1A8060Config *config;
    s32 type;
    s32 size;
    s32 kind;
    s32 index;
    s32 i;
    s32 j;
    Vtx *vtx;
    s32 group;
    s16 (*a)[3];
    s16 (*b)[3];
    Vtx *vtxBase;

    type = D_800CC2D0[arg2].unk4;
    kind = func_150849A0(&D_800CC2D0[arg2]);
    index = D_800CC2D0[arg2].unk1C8;
    config = NULL;
    for (i = 0; i < 2; i++) {
        if (kind == D_800A7230[i * 8]) {
            config = (Game1A8060Config *)&D_800A7230[i * 8];
            group = i;
            break;
        }
    }
    if (config == NULL) {
        return -1;
    }
    blend = D_800CC2D0[arg2].blend;
    if (index != 0) {
        index = 0;
        type = kind;
        if (D_800CC2D0[arg2].unk28C[index][D_800BE9C0] == 0 || D_800D19A0[type] == 0) {
            if (arg0 == blend->cur) {
                if (D_800BEAC0 == 0) {
                    blend->blend += blend->rate * D_800BE9E4;
                }
                if (blend->blend > 1.0f) {
                    blend->blend = 1.0f;
                }
            } else {
                if (blend->cur != 0xFF) {
                    blend->prev = blend->cur;
                }
                blend->cur = arg0;
                blend->blend = 0.0f;
                if (arg1 <= 0) {
                    arg1 = 1;
                }
                blend->rate = 1.0f / arg1;
            }
            blend->hold = 3;
            return -1;
        }
    }
    if (D_800D19A0[type] == 0) {
        return -1;
    }
    if (D_800CC2D0[arg2].unk28C[index][D_800BE9C0] == 0) {
        return -1;
    }
    if (arg0 == blend->cur && blend->hold == 0) {
        blend->prev = blend->cur;
        return 0;
    }
    if (arg0 != blend->cur) {
        if (blend->cur != 0xFF) {
            blend->prev = blend->cur;
        }
        blend->cur = arg0;
        blend->blend = 0.0f;
        if (arg1 <= 0) {
            arg1 = 1;
        }
        blend->hold = 3;
        blend->rate = 1.0f / arg1;
    }
    if (D_800DD460[group] == NULL) {
        s32 failed;

        D_800DD460[group] = func_10003C40(D_800C4310[config->set] * 4, 1, 0, 2);
        if (D_800DD460[group] == NULL) {
            return -1;
        }
        failed = 0;
        for (i = 0; i < D_800C4310[config->set]; i++) {
            D_800DD460[group][i] = func_10003C40(config->slots * 8, 1, 0, 2);
            if (D_800DD460[group][i] != NULL) {
                func_100226F0(D_800DD460[group][i], config->slots * 8);
            } else {
                failed = 1;
            }
        }
        if (failed) {
            for (i = 0; i < D_800C4310[config->set]; i++) {
                if (D_800DD460[group][i] != NULL) {
                    func_10004074((s32)D_800DD460[group][i]);
                }
            }
            return -1;
        }
    }
    if (D_800BEAC0 == 0) {
        blend->blend += blend->rate * D_800BE9E4;
    }
    if (blend->blend > 1.0f) {
        blend->blend = 1.0f;
    }
    vtxBase = (Vtx *)D_800CC2D0[arg2].unk28C[index][D_800BE9C0];
    for (j = 0; j < D_800C4310[config->set]; j++) {
        if (D_800DD460[group][j][blend->cur].resource == 0) {
            D_800DD460[group][j][blend->cur].resource = func_1502B5C8(&size, 4, 0x13, group, j, blend->cur);
            if (D_800DD460[group][j][blend->cur].resource == 0) {
                return -1;
            }
        }
        if (D_800DD460[group][j][blend->prev].resource == 0) {
            D_800DD460[group][j][blend->prev].resource = func_1502B5C8(&size, 4, 0x13, group, j, blend->prev);
            if (D_800DD460[group][j][blend->prev].resource == 0) {
                func_10004074(D_800DD460[group][j][blend->cur].resource);
                D_800DD460[group][j][blend->cur].resource = 0;
                return -1;
            }
        }
        D_800DD460[group][j][blend->cur].timer = 3;
        D_800DD460[group][j][blend->prev].timer = 3;
        a = (s16 (*)[3])D_800DD460[group][j][blend->prev].resource;
        b = (s16 (*)[3])D_800DD460[group][j][blend->cur].resource;
        vtx = &vtxBase[D_800C4020[type][j]];
        for (i = 0; i < config->vertexCounts[j]; i++) {
            vtx[i].v.ob[0] = a[i][0] + ((f32)b[i][0] - a[i][0]) * blend->blend;
            vtx[i].v.ob[1] = a[i][1] + ((f32)b[i][1] - a[i][1]) * blend->blend;
            vtx[i].v.ob[2] = a[i][2] + ((f32)b[i][2] - a[i][2]) * blend->blend;
        }
        func_10023D20(vtx, config->vertexCounts[j] * 0x10);
    }
    if (blend->blend == 1.0f) {
        blend->hold--;
    } else {
        blend->hold = 3;
    }
    return 0;
}
