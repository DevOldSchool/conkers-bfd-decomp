#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/effects/characterflamethrower.c
 * Boundary evidence: docs/evidence/boundaries/effects/effects_characterflamethrower.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151957B0
 * - func_1519582C
 * - func_15195868
 * - func_15195AA8
 * - func_15195DD4
 * - func_15195FF0
 * - func_15196438
 * - func_15196748
 * - func_15196B4C
 * - func_15197148
 * - func_15197AB4
 * - func_15197C10
 * - func_15198110
 * - func_15198570
 * - func_151987CC
 * - func_1519897C
 * - func_15198D88
 * - func_151990AC
 * - func_151994B8
 * - func_15199A10
 * - func_15199C34
 * - func_1519A9A4
 * - func_1519B4B8
 * - func_1519C26C
 * - func_1519C4E4
 * - func_1519C56C
 * - func_1519C9C4
 * - func_1519CDB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800A8AA4;
extern struct CharacterFlamethrowerListNode *D_800E08E0;
extern struct CharacterFlamethrowerListNode *D_800E08E4;
extern struct CharacterFlamethrowerListNode *D_800E08E8;
extern struct CharacterFlamethrowerListNode *D_800E08EC;
extern s32 D_800E08F0;

struct CharacterFlamethrowerActor;
void func_1519CDB0(struct CharacterFlamethrowerActor *arg0, f32 arg1, s32 arg2);
void func_10010F30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void (*D_8008F88C[])(void *);
extern void (*D_8008F898[])(void *);
extern void (*D_8008F8B4[])(void *);
extern void (*D_8008F8C0[])(void);
void func_15199980(void *arg0);
void func_100111C8(u16 arg0);
struct CharacterFlamethrowerPanel;
struct CharacterFlamethrowerPanel *func_15195DD4(s32, s32, s32, s32, s32, s32, s32);

typedef struct CharacterFlamethrowerDispatch {
    char pad0[0x18];
    struct CharacterFlamethrowerBinding *bindings;
    s32 unk1C;
} CharacterFlamethrowerDispatch;

typedef struct CharacterFlamethrowerIdentity {
    char pad0[0x3B];
    u8 unk3B;
    char pad3C[0x3A];
    u16 unk76;
    char pad78[0xC];
    u16 unk84;
} CharacterFlamethrowerIdentity;

typedef struct CharacterFlamethrowerSlot {
    char pad0[0x14];
    u8 active;
} CharacterFlamethrowerSlot;

typedef struct CharacterFlamethrowerVec3 {
    f32 x;
    f32 y;
    f32 z;
} CharacterFlamethrowerVec3;

typedef struct CharacterFlamethrowerState {
    CharacterFlamethrowerIdentity *identity;
    u8 generation;
    char pad5[0x1];
    u8 flags6;
    char pad7[0x19];
    f32 gravity;
    char pad24[0xC];
    f32 size_rate;
    char pad34[2];
    s8 unk36;
    char pad37;
    s8 callback38;
    s8 unk39;
    char pad3A[0xE];
    s8 callback48;
    char pad49[0x1D];
    u16 unk66;
    char pad68[0xC8];
    u16 unk130;
    char pad132[0x16];
    void *unk148;
    f32 spacing;
    u8 flags150;
    char pad151[7];
    s32 unk158;
    s32 unk15C;
} CharacterFlamethrowerState;

typedef struct CharacterFlamethrowerActor {
    char pad0[0x10];
    f32 position[3];
    char pad1C[0x2];
    u16 flags1E;
    char pad20[0x5];
    u8 point_capacity;
    char pad26[0x6];
    s8 unk2C;
    s8 point_index;
    s8 point_end;
    char pad2F[0x1];
    s8 unk30;
    char pad31[0xA];
    u8 unk3B;
    char pad3C[0x18];
    CharacterFlamethrowerVec3 last_position;
    char pad60[0x34];
    void *points;
    CharacterFlamethrowerState *state;
} CharacterFlamethrowerActor;

typedef struct CharacterFlamethrowerContext {
    char pad0[0x38];
    CharacterFlamethrowerActor *actor;
} CharacterFlamethrowerContext;

typedef struct CharacterFlamethrowerControl {
    char pad0[0x12];
    char unk12;
    char unk13;
} CharacterFlamethrowerControl;

typedef struct CharacterFlamethrowerLocal {
    CharacterFlamethrowerActor *actor;
    u8 unk4;
} CharacterFlamethrowerLocal;

void func_15147D64(void *arg0, s32 arg1, CharacterFlamethrowerActor *arg2);

void func_1519C258(CharacterFlamethrowerContext *arg0);

typedef struct CharacterFlamethrowerListNode {
    struct CharacterFlamethrowerListNode *next;
    struct CharacterFlamethrowerListNode *previous;
} CharacterFlamethrowerListNode;

void *func_10003C40(s32, s32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151957B0 CURRENT (400) */
CharacterFlamethrowerListNode *func_151957B0(
    s32 arg0,
    CharacterFlamethrowerListNode **arg1,
    CharacterFlamethrowerListNode **arg2
) {
    CharacterFlamethrowerListNode *node;
    CharacterFlamethrowerListNode *head;

    node = func_10003C40(arg0, 1, 0, 0);
    if (node != 0) {
        node->previous = 0;
        head = *arg2;
        if (head != 0) {
            node->next = head;
            (*arg2)->previous = node;
            *arg2 = node;
        } else {
            node->next = 0;
            *arg2 = node;
            *arg1 = node;
        }
    }
    return node;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151957B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151957B0.s")
CharacterFlamethrowerListNode *func_151957B0(s32, CharacterFlamethrowerListNode **, CharacterFlamethrowerListNode **);
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519582C CURRENT (450) */
void func_1519582C(void) {
    D_800E08E4 = 0;
    D_800E08E0 = 0;
    D_800E08EC = 0;
    D_800E08E8 = 0;
    D_800E08F0 = -2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519582C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519582C.s")
extern u32 D_800B0E58[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15195868 CURRENT (5715) */
s32 func_15195868(s32 commands, s32 texture, s32 occurrence, s32 *count) {
    s32 first;
    s32 remaining;
    s32 scan;
    s32 index;
    s8 tile;
    s8 opcode;

    remaining = occurrence;
    *count = 0;
    index = -1;
scan_image:
    index++;
    opcode = *(s8 *)(index * 8 + commands);
    if (opcode != -3 && opcode != -0x21) {
scan_command:
        index++;
        opcode = *(s8 *)(index * 8 + commands);
        if (opcode != -3) {
            if (opcode != -0x21) {
                goto scan_command;
            }
        }
    }
    if (opcode == -0x21) {
        return -1;
    }
    if (*(u32 *)(commands + index * 8 + 4) == D_800B0E58[texture] || texture == 0) {
        if (remaining-- < 1) {
            if (opcode != -0xE) {
        do {
                    index++;
                } while (*(s8 *)(index * 8 + commands) != -0xE);
            }
            scan = index;
scan_tile:
            first = scan + 1;
            (*count)++;
            tile = *(s8 *)(first * 8 + commands);
            scan = first + 1;
            if (tile == -0xB) {
                if (*(s8 *)(scan * 8 + commands) == -0xE) {
                    goto scan_tile;
                }
            }
            return index;
        }
    }
    goto scan_image;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15195868 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195868.s")
typedef struct CharacterFlamethrowerPanel {
    CharacterFlamethrowerListNode links;
    s16 identity;
    s16 width;
    s16 height;
    u16 position[2];
    u8 control12;
    u8 control13;
    u8 active;
    u8 pad15[3];
    struct CharacterFlamethrowerBinding *bindings;
    s16 first[5];
    s16 second[5];
    u8 pad30[0xC];
} CharacterFlamethrowerPanel;

CharacterFlamethrowerPanel *func_15195984(s32 identity, s32 dimensions, s32 position, s32 doubled) {
    CharacterFlamethrowerPanel *node;
    CharacterFlamethrowerPanel *result;
    register s32 scaled_width;
    register s32 width;
    register s32 scaled_height;
    register s32 height;
    s32 index;

    node = (CharacterFlamethrowerPanel *)func_151957B0(sizeof(CharacterFlamethrowerPanel), &D_800E08E8, &D_800E08EC);
    result = node;
    if (node != 0) {
        node->bindings = 0;
        for (index = 0; index < 5; index++) {
            node->first[index] = -1;
        }
        for (index = 0; index < 5; index++) {
            node->second[index] = -1;
        }
        node->identity = identity;
        scaled_width = ((dimensions >> 12) & 0xFFF) + 2;
        scaled_height = (dimensions & 0xFFF) + 2;
        width = scaled_width;
        height = scaled_height;
        if (doubled != 0) {
            scaled_width = width * 2;
            scaled_height = height * 2;
        }
        node->position[0] = (position >> 12) & 0xFFF;
        node->position[1] = position & 0xFFF;
        node->width = scaled_width;
        node->height = scaled_height;
        node->position[0] *= 8;
        node->position[1] *= 8;
        node->active = 1;
    }
    return result;
}
s16 func_15195A84(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}
s32 func_15195868(s32, s32, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15195AA8 CURRENT (1786) */
s32 func_15195AA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  volatile s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 count;
    CharacterFlamethrowerPanel *created;
    register CharacterFlamethrowerPanel *panel;
    register s32 dimensions;
    register s32 index;
    register s32 identity;
    register s32 occurrence;
    register s32 status;
    register s32 selection;
    s32 first_slot;
    s32 second_slot;
    s32 position;

    identity = arg1;
    selection = arg3;
    occurrence = selection;
    panel = 0;
    if (arg0 == 0) {
        return 0;
    }
    status = arg4;
    if (selection == -1) {
        occurrence = 0;
    }
    do {
        index = func_15195868(arg0, identity, occurrence, &count);
        if (index == -1) {
            selection = 0;
        } else {
            if (identity == 0) {
                identity = D_800E08F0;
            }
            panel = (CharacterFlamethrowerPanel *)D_800E08E8;
            dimensions = *(s32 *)(arg0 + index * 8 + 4);
            position = *(s32 *)(arg0 + index * 8);
            while (panel != 0 && panel->identity != 0) {
                panel = (CharacterFlamethrowerPanel *)panel->links.previous;
            }
            if (panel == 0) {
                created = func_15195984(identity, dimensions, position, arg2);
                panel = created;
                if (created == 0) {
                    return 0;
                }
                status = 0;
                created->control12 = arg6;
                created->control13 = arg7;
            } else {
                status = 0;
                index = func_15195A84((s16)index, (s32)panel, dimensions, arg2);
            }
            occurrence++;
            if (panel->active < count) {
                panel->active = count;
            }
            if (arg5 == 0) {
                first_slot = 0;
                while (first_slot < 5 && panel->first[first_slot] != -1) {
                    first_slot++;
                }
                if (first_slot < 5) {
                    panel->first[first_slot] = index;
                    panel->pad30[first_slot] = count;
                }
            } else {
                second_slot = 0;
                while (second_slot < 5 && panel->second[second_slot] != -1) {
                    second_slot++;
                }
                if (second_slot < 5) {
                    panel->second[second_slot] = index;
                    panel->pad30[second_slot + 5] = count;
                }
            }
        }
    } while (selection == -1);
    arg4 = status;
    if (identity == D_800E08F0) {
        D_800E08F0--;
    }
    return (s32)panel;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15195AA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195AA8.s")
typedef struct CharacterFlamethrowerBinding {
    CharacterFlamethrowerListNode links;
    s32 identity;
    u16 kind;
    u8 flags;
    u8 padF;
    struct CharacterFlamethrowerBinding *next;
} CharacterFlamethrowerBinding;

void func_15195D00(CharacterFlamethrowerDispatch *owner, s32 identity, s32 kind, s32 flags) {
    CharacterFlamethrowerBinding *tail;
    CharacterFlamethrowerBinding *node;

    node = owner->bindings;
    if (node != 0) {
        tail = node;
        do {
            if (identity == tail->identity && kind == tail->kind) {
                return;
            }
            node = tail->next;
            if (node != 0) {
                tail = node;
                node = node->next;
            }
        } while (node != 0);
        node = (CharacterFlamethrowerBinding *)func_151957B0(sizeof(CharacterFlamethrowerBinding), &D_800E08E0, &D_800E08E4);
        tail->next = node;
    } else {
        node = (CharacterFlamethrowerBinding *)func_151957B0(sizeof(CharacterFlamethrowerBinding), &D_800E08E0, &D_800E08E4);
        owner->bindings = node;
    }
    node->identity = identity;
    node->kind = kind;
    node->flags = flags;
    node->next = 0;
}
extern u8 D_800BEAC0;
s32 func_15195868(s32, s32, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15195DD4 CURRENT (1720) */
CharacterFlamethrowerPanel *func_15195DD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 dimensions;
    s32 index;
    s16 short_index;
    s32 count;
    s32 occurrence;
    s32 key;
    CharacterFlamethrowerPanel *panel;

    occurrence = arg3;
    if (arg0 == 0) {
        return 0;
    }
    if (D_800BEAC0 != 0) {
        return 0;
    }
    if (arg3 == -1) {
        occurrence = 0;
    }
scan:
    index = func_15195868(arg0, arg1, occurrence, &count);
    if (index == -1) {
        arg3 = 0;
        goto next;
    }
    if (arg1 == 0) {
        arg1 = D_800E08F0;
    }
    if (arg4 != 0) {
        key = -1;
    } else {
        key = arg1;
    }
    panel = (CharacterFlamethrowerPanel *)D_800E08E8;
    short_index = index;
    if (panel != 0 && key != panel->identity) {
search:
        panel = (CharacterFlamethrowerPanel *)panel->links.previous;
        if (panel != 0) {
            if (key != panel->identity) {
                goto search;
            }
        }
    }
    key = arg0 + index * 8;
    dimensions = *(s32 *)(key + 4);
    key = *(s32 *)key;
    if (panel == 0) {
        panel = func_15195984(arg1, dimensions, key, arg2);
        if (panel != 0) {
            arg4 = 0;
            panel->control12 = arg5;
            panel->control13 = arg6;
            goto bind;
        }
        return 0;
    }
    arg4 = 0;
    index = func_15195A84(short_index, (s32)panel, dimensions, arg2);
bind:
    if (panel->active < count) {
        panel->active = count;
    }
    func_15195D00((CharacterFlamethrowerDispatch *)panel, arg0, index, count);
    occurrence++;
next:
    if (arg3 != -1) {
        if (arg1 == D_800E08F0) {
            D_800E08F0--;
        }
        return panel;
    }
    goto scan;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15195DD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195DD4.s")


void func_15195FB0(
    CharacterFlamethrowerDispatch *arg0,
    s32 arg1,
    s32 arg2,
    s32 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6
) {
    func_15195DD4(arg0->unk1C, arg1, arg2, arg3, arg4, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15195FF0.s")
void func_15196318(CharacterFlamethrowerControl *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        arg0->unk12 = arg1;
        arg0->unk13 = arg2;
    }
}
void func_15196330(void *arg0) {
    void *temp_v0;
    s8 temp_v1;
    s8 temp_v1_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_v1 = *(s8 *)((u8 *)temp_v0 + 0x65);
    if (temp_v1 != -1) {
        D_8008F898[temp_v1](arg0);
    }
    temp_v1_2 = *(s8 *)((u8 *)temp_v0 + 0x62);
    if (temp_v1_2 != -1) {
        D_8008F88C[temp_v1_2](arg0);
    }
    func_151478F4(arg0);
}
void func_151963B4(void *arg0) {
    void *temp_v0;
    s8 temp_v1;
    s8 temp_v1_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_v1 = *(s8 *)((u8 *)temp_v0 + 0x65);
    if (temp_v1 != -1) {
        D_8008F898[temp_v1](arg0);
    }
    temp_v1_2 = *(s8 *)((u8 *)temp_v0 + 0x62);
    if (temp_v1_2 != -1) {
        D_8008F88C[temp_v1_2](arg0);
    }
    func_15147928(arg0);
}
typedef struct CharacterFlamethrowerJetTemplate {
    s16 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    s32 unk10;
    u8 unk14;
    CharacterFlamethrowerVec3 unk18;
    CharacterFlamethrowerVec3 unk24;
    s8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    f32 unk34;
    f32 unk38;
    s8 unk3C;
    s8 unk3D;
    s8 unk3E;
    s8 unk3F;
    s8 unk40;
    s8 unk41;
    s8 unk42;
    u16 unk44;
    u8 unk46;
    u8 unk47;
    f32 unk48;
    u8 unk4C;
    f32 unk50;
    u8 unk54;
    f32 unk58;
    u8 unk5C;
    u8 unk5D;
    u8 unk5E;
    u8 unk5F;
} CharacterFlamethrowerJetTemplate;

typedef struct CharacterFlamethrowerJet {
    void *owner;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    s8 unk7;
    CharacterFlamethrowerVec3 unk8;
    CharacterFlamethrowerVec3 unk14;
    CharacterFlamethrowerVec3 unk20;
    CharacterFlamethrowerVec3 unk2C;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    f32 unk58;
    f32 unk5C;
    s8 unk60;
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s16 unk66;
    s8 unk68;
    u8 unk69;
    u8 unk6A;
    f32 unk6C;
    f32 unk70;
    u8 unk74;
    f32 unk78;
    f32 unk7C;
    u8 unk80;
    f32 unk84;
    f32 unk88;
    u8 unk8C;
    u8 unk8D;
    u8 unk8E;
    u8 unk8F;
} CharacterFlamethrowerJet;

typedef struct CharacterFlamethrowerJetSpawn {
    f32 position[3];
    s16 unkC;
    u16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
} CharacterFlamethrowerJetSpawn;

extern CharacterFlamethrowerJetTemplate D_800A87A0[];
extern f32 (*D_8008F870[])(void *, s32);
extern void (*D_8008F87C[])(void *);
extern s16 (*D_8008F890[])(void);
void func_15143134(f32 *, f32 *, s32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32,
                    s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15196438 CURRENT (1324) */
void *func_15196438(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s8 kind;
    CharacterFlamethrowerJetSpawn spawn;
    CharacterFlamethrowerJet local;
    void *result;
    s32 matrix;
    CharacterFlamethrowerJetTemplate *entry;
    CharacterFlamethrowerJet *jet;

    if (arg0 == NULL) {
        return NULL;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return NULL;
    }
    local.owner = arg0;
    entry = &D_800A87A0[arg1];
    local.unk4 = *(u8 *)((u8 *)arg0 + 0x3B);
    local.unk6 = 2;
    local.unk50 = 0;
    local.unk4C = 0.0f;
    local.unk70 = 0.0f;
    local.unk7C = 0.0f;
    local.unk88 = 0.0f;
    local.unk60 = entry->unk3C;
    local.unk61 = entry->unk3D;
    local.unk62 = entry->unk3E;
    spawn.unkC = entry->unk0;
    local.unk40 = entry->unk4;
    local.unk48 = entry->unk8;
    local.unk51 = entry->unkC;
    spawn.unk15 = entry->unk10;
    local.unk5 = entry->unk14;
    local.unk8 = entry->unk18;
    local.unk14 = entry->unk24;
    local.unk80 = entry->unk54;
    local.unk63 = entry->unk3F;
    local.unk7 = entry->unk30;
    local.unk52 = entry->unk31;
    local.unk53 = entry->unk32;
    local.unk54 = entry->unk33;
    spawn.unkE = entry->unk44;
    local.unk6A = entry->unk47;
    local.unk74 = entry->unk4C;
    local.unk58 = entry->unk34;
    local.unk5C = entry->unk38;
    local.unk6C = entry->unk48;
    local.unk78 = entry->unk50;
    local.unk84 = entry->unk58;
    local.unk64 = entry->unk40;
    local.unk65 = entry->unk41;
    local.unk68 = entry->unk42;
    local.unk69 = entry->unk46;
    local.unk8C = entry->unk5C;
    local.unk8D = entry->unk5D;
    local.unk8E = entry->unk5E;
    local.unk8F = entry->unk5F;
    if (local.unk63 != -1) {
        local.unk66 = D_8008F890[local.unk63]();
    } else {
        local.unk66 = 0;
    }
    matrix = *(s32 *)((u8 *)local.owner + 0x1D4) + (local.unk5 << 6);
    func_15143134(&local.unk8.x, &local.unk20.x, matrix);
    func_15143134(&local.unk14.x, &local.unk2C.x, matrix);
    spawn.unk10 = 3;
    spawn.position[0] = local.unk20.x;
    spawn.position[1] = local.unk20.y;
    spawn.position[2] = local.unk20.z;
    local.unk3C = 0.0f;
    result = func_15147A80(&spawn, (void *)0x90, 0x24, 2, 2, 2, 0, 0, 0,
                           arg2, arg3);
    if (result != NULL) {
        jet = *(CharacterFlamethrowerJet **)((u8 *)result + 0x98);
        func_10022EC0(jet, &local, 0x90);
        kind = jet->unk7;
        if (kind != -1) {
            jet->unk38 = D_8008F870[kind](result, kind);
        } else {
            jet->unk38 = 0.0f;
        }
        if (local.unk60 != -1) {
            D_8008F87C[local.unk60](result);
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15196438 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196438.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196748.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15196B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197148.s")
f32 func_151979F8(s32 arg0) {
    return D_800A8AA4;
}
s32 func_151422C0(s32, s32, s32, s32, s32, s32);
extern s32 D_800A8A40;
extern s32 D_800A8A48;
extern f32 D_800A8AA8;

f32 func_15197A0C(s32 arg0) {
    return (f32)func_151422C0(0xA, (s32)&D_800A8A40, 1, 0x1F4, (s32)&D_800A8A48, 0x8CC) * D_800A8AA8;
}

extern f32 D_800A8AAC;

f32 func_15197A68(s32 arg0) {
    return D_800A8AAC;
}

void func_15197A7C(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerLocal sp18;

    if (arg0 != 0) {
        sp18.actor = arg0;
        sp18.unk4 = arg0->unk3B;
        func_15147D64(&sp18, 8, arg0);
    }
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15197AB4 CURRENT (990) */
s32 func_15197AB4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x15C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x158);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x160);
    *(f32 *)((u8 *)arg0 + 0x140) = (f32) (*(f32 *)((u8 *)arg0 + 0x140) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x148) = (f32) (*(f32 *)((u8 *)arg0 + 0x148) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x144) = (f32) (*(f32 *)((u8 *)arg0 + 0x144) + (temp_fv1 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x14C) = (f32) (*(f32 *)((u8 *)arg0 + 0x14C) * temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x154) = (f32) (*(f32 *)((u8 *)arg0 + 0x154) * temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x150) = (f32) (*(f32 *)((u8 *)arg0 + 0x150) + (temp_fv1 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg0 + 0x140) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x144) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg0 + 0x148) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x14C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x150) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + (*(f32 *)((u8 *)arg0 + 0x154) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15197AB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197AB4.s")
s32 func_15197BBC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x164);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (*(s16 *)((u8 *)arg0 + 0x1C) < *(s16 *)((u8 *)arg0 + 0x168)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (*(s16 *)((u8 *)arg0 + 0x16A) * *(s16 *)((u8 *)arg0 + 0x1C));
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15197C10.s")
typedef union CharacterFlamethrowerEvent {
    struct {
        CharacterFlamethrowerIdentity *identity;
        u8 generation;
    } removed;
    struct {
        CharacterFlamethrowerIdentity *first;
        CharacterFlamethrowerIdentity *second;
        u8 first_generation;
        u8 second_generation;
    } replaced;
} CharacterFlamethrowerEvent;

void func_151993B4(CharacterFlamethrowerActor *);

void func_15198054(CharacterFlamethrowerActor *actor, CharacterFlamethrowerEvent *event, u8 kind) {
    s32 key;
    CharacterFlamethrowerState *state = actor->state;

    if (kind == 0 || kind == 2 || kind == 8) {
        if (event->removed.identity == state->identity || event->removed.generation == state->generation) {
            func_151993B4(actor);
        }
    } else if (kind == 0x2D) {
        actor = (CharacterFlamethrowerActor *)event->replaced.first;
        key = (s32)state->identity;
        if ((s32)actor == key) {
            state->identity = event->replaced.second;
            state->generation = event->replaced.second_generation;
            return;
        }
        key = (s32)event->replaced.second ^ key;
        if (key == 0) {
            state->identity = (CharacterFlamethrowerIdentity *)actor;
            state->generation = event->replaced.first_generation;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198110.s")
typedef struct CharacterFlamethrowerPosition {
    f32 x;
    f32 y;
    f32 z;
} CharacterFlamethrowerPosition;

typedef struct CharacterFlamethrowerPoint {
    CharacterFlamethrowerPosition position;
    u8 padC[0x18];
} CharacterFlamethrowerPoint;

typedef struct CharacterFlamethrowerCollisionActor {
    s32 active;
    u8 pad4[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x1B];
    u8 generation;
    u8 pad3C[0x29];
    u8 disabled;
    u8 pad66[0x7E];
    s16 radius;
    s16 height;
    s16 y_offset;
    u8 padEA[0x242];
} CharacterFlamethrowerCollisionActor;

extern CharacterFlamethrowerCollisionActor D_800CC2D0[];
extern CharacterFlamethrowerCollisionActor D_800D121C;

s32 func_1505D024(void *, s32, s32, s32);
s32 func_1518D1C0(void *, s32, s32, s32, s32, s32, void *);
extern u8 D_800A8A84;
extern f32 D_800CC2E4;
extern f32 D_800CC2E8;
extern f32 D_800CC2EC;
extern u16 D_800CC34A;
extern s16 D_800CC3B4;
extern s16 D_800CC3B6;
extern s16 D_800CC3B8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15198570 CURRENT (9204) */
s32 func_15198570(CharacterFlamethrowerActor *arg0) {
    volatile CharacterFlamethrowerPosition position;
    CharacterFlamethrowerState *state;
    u8 *points;
    s32 index;
    s32 ring_index;
    f32 radius;
    f32 height;
    f32 x;
    f32 z;
    f32 y;

    points = arg0->points;
    state = arg0->state;
    index = arg0->point_end;
    if (index != arg0->point_index) {
        do {
            index -= 1;
            if (index < 0) index = arg0->point_capacity - 1;
            position = *(CharacterFlamethrowerPosition *)(points + index * 0x24);
            radius = D_800CC3B4;
            height = D_800CC3B6;
            x = position.x - D_800CC2E4;
            z = position.z - D_800CC2EC;
            y = (position.y - (D_800CC2E8 + (f32)D_800CC3B8)) *
                ((1.0f + radius / height) * 0.5f);
            if ((x * x + y * y + z * z) < radius * radius) {
                func_1505D024(D_800CC2D0, 0x60006, D_800CC34A,
                    ((u8 *)state->identity - (u8 *)D_800CC2D0) / 0x32C);
                func_1518D1C0(D_800CC2D0, 0xB, 0, 1,
                    ((u8 *)arg0)[0xC], ((u8 *)arg0)[1], &D_800A8A84);
                ring_index = arg0->point_index;
                if (index != ring_index) {
                    do {
                        *(volatile s8 *)&arg0->point_index = ring_index + 1;
                        ring_index = *(volatile s8 *)&arg0->point_index;
                        if (arg0->point_capacity == ring_index) {
                            *(volatile s8 *)&arg0->point_index = 0;
                            ring_index = *(volatile s8 *)&arg0->point_index;
                        }
                        arg0->unk2C -= 1;
                    } while (index != ring_index);
                }
            }
        } while (index != arg0->point_index);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15198570 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198570.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151987CC CURRENT (1088) */
s32 func_151987CC(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerPosition position;
    s32 index;
    CharacterFlamethrowerCollisionActor *actor;
    f32 x;
    f32 z;
    f32 y;
    f32 radius;
    f32 height;
    CharacterFlamethrowerState *state;
    CharacterFlamethrowerPoint *points;
    CharacterFlamethrowerPosition *point;

    state = arg0->state;
    points = arg0->points;
    actor = D_800CC2D0;
    do {
        if (actor->active != 0 && actor->disabled == 0 &&
            state->identity->unk3B != actor->generation) {
            index = arg0->point_end;
            if (index != arg0->point_index) {
        do {
                    index--;
                    if (index < 0) {
                        index = arg0->point_capacity - 1;
                    }
                    radius = actor->radius;
                    height = actor->height;
                    point = (CharacterFlamethrowerPosition *)((u8 *)points + index * 0x24);
                    position = *point;
                    x = position.x - actor->x;
                    z = position.z - actor->z;
                    y = (position.y - (actor->y + (f32)actor->y_offset)) *
                        ((1.0f + radius / height) * 0.5f);
                    if (x * x + y * y + z * z < radius * radius + 2500.0f &&
                        index != arg0->point_index) {
                do {
                            arg0->point_index++;
                            if (arg0->point_capacity == arg0->point_index) {
                                arg0->point_index = 0;
                            }
                            arg0->unk2C--;
                        } while (index != arg0->point_index);
                    }
                } while (index != arg0->point_index);
            }
        }
        actor++;
    } while (actor != &D_800D121C);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151987CC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151987CC.s")

typedef struct CharacterFlamethrowerGroups {
    u8 ids[3];
} CharacterFlamethrowerGroups;

extern CharacterFlamethrowerGroups D_8008F8A0;
extern u8 D_800DCE50[];
extern s8 D_800DD190;
extern void *D_800DD198[];
extern u8 D_800DDE80[];
void func_15183ACC(s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519897C CURRENT (3849) */
s32 func_1519897C(CharacterFlamethrowerActor *arg0) {
    s32 points;
    CharacterFlamethrowerGroups groups;
    CharacterFlamethrowerPosition position;
    u8 *group;
    register CharacterFlamethrowerIdentity *owner;
    register void *control;
    register void *node;
    register void **slot;
    register s32 index;
    register s32 depth;
    register f32 x;
    register f32 y;
    register f32 z;
    register f32 dx;
    register f32 dy;
    register f32 dz;
    register f32 radius;
    register u8 *point;

    points = (s32)arg0->points;
    groups = D_8008F8A0;
    owner = arg0->state->identity;
    control = *(void **)((u8 *)owner + 0x31C);
    if (control == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)control + 0x58) != 1) {
        *(u16 *)((u8 *)owner + 0x2F8) &= 0xFEFF;
        return 0;
    }
    group = groups.ids;
    do {
        control = *(void **)(D_800DCE50 + *group * 4);
        node = control;
        if (control != 0) {
            index = arg0->point_end;
            depth = D_800DD190 + 1;
            D_800DD190 = depth;
            if (control != 0) {
                slot = &D_800DD198[(s8)depth];
                do {
                    *slot = *(void **)((u8 *)node + 8);
                    x = *(f32 *)((u8 *)node + 0x98);
                    y = *(f32 *)((u8 *)node + 0x9C);
                    z = *(f32 *)((u8 *)node + 0xA0);
                    if (index != arg0->point_index) {
                        do {
                            index--;
                            if (index < 0) {
                                index = arg0->point_capacity - 1;
                            }
                            point = (u8 *)(points + index * 0x24);
                            position = *(CharacterFlamethrowerPosition *)point;
                            dx = position.x - x;
                            radius = *(f32 *)(point + 0x18);
                            dy = position.y - y;
                            dz = position.z - z;
                            if (dx * dx + dy * dy + dz * dz < radius * radius + 900.0f) {
                                func_15183ACC(5);
                                func_15168B10((s32)node, 0x18);
                                dx = *(f32 *)((u8 *)node + 0x98);
                                dy = *(f32 *)((u8 *)node + 0x9C);
                                dz = *(f32 *)((u8 *)node + 0xA0);
                                *(s8 *)((u8 *)node + 0xED) = 5;
                                *(s16 *)((u8 *)node + 0x92) = 9;
                                *(f32 *)((u8 *)node + 0xB8) = 40.0f;
                                *(f32 *)((u8 *)node + 0xA8) = 40.0f;
                                *(f32 *)((u8 *)node + 0xB4) = 0.0f;
                                *(s32 *)((u8 *)node + 0x94) = *(s32 *)(D_800DDE80 + 0x6C);
                                depth = func_1510F8D8((s32)dx, (s32)dy, (s32)dz, 0);
                                *(s8 *)((u8 *)node + 0x91) = 4;
                                *(f32 *)((u8 *)node + 0xC8) = (f32)depth;
                            }
                        } while (index != arg0->point_index);
                        slot = &D_800DD198[D_800DD190];
                    }
                    node = *slot;
                } while (node != 0);
            }
            D_800DD190--;
        }
        group++;
    } while (group != groups.ids + 3);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519897C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519897C.s")
void func_15198C60(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
void func_1000F91C(u16, s32, s16, s32, s32, s32, s32, s32, s32, s32);

void func_15198C90(CharacterFlamethrowerActor *actor) {
    CharacterFlamethrowerState *state = actor->state;
    f32 (*points)[9] = actor->points;
    u16 sound;

    if (actor->unk2C != 0) {
        sound = state->unk66;
        if (sound != 0) {
            func_1000F91C(sound, 0x7FFF, 0, 0, 0,
                         (s32)points[actor->point_index][0], (s32)points[actor->point_index][1], (s32)points[actor->point_index][2],
                         500, 5000);
        }
    }
}
void func_15198D40(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *temp_v0 = arg0->state;
    u16 temp_a0;

    if (arg0->unk2C != 0) {
        temp_a0 = temp_v0->unk66;
        if (temp_a0 != 0) {
            func_100111C8(temp_a0);
        }
    }
}

void func_15198D7C(s32 arg0) {

}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15198D88.s")
typedef struct CharacterFlamethrowerEmissionPreset {
    f32 radius;
    f32 speed;
    f32 speed_range;
    s16 acceleration;
    s16 acceleration_range;
    s16 fade;
    s16 fade_range;
    s16 size;
    s16 size_range;
} CharacterFlamethrowerEmissionPreset;

typedef struct CharacterFlamethrowerEmission {
    void *texture;
    char pad4[8]; /* Read only with flags 0x100 or negative size; absent here. */
    s16 frame;
    s16 frame_rate;
    s16 position[3];
    s16 velocity_x;
    s16 velocity_z;
    char pad1A[2];
    u8 fraction_x;
    u8 fraction_y;
    u8 fraction_z;
    s8 callback;
    s16 velocity_y;
    s16 acceleration;
    s16 width;
    s16 height;
    s16 lifetime;
    s8 fade;
    char pad2B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 environment[3];
    char pad33;
    u16 flags;
    char pad36[2];
} CharacterFlamethrowerEmission;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern u8 D_80090514[];
extern CharacterFlamethrowerEmissionPreset D_800A8770[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151990AC CURRENT (5250) */
void func_151990AC(CharacterFlamethrowerActor *arg0, CharacterFlamethrowerVec3 *arg1) {
    CharacterFlamethrowerEmission packet;
    f32 speed;
    f32 cosine1;
    f32 sine1;
    f32 cosine2;
    register f32 sine2;
    f32 radius;
    f32 scale;
    register f32 x;
    register f32 y;
    register f32 z;
    s16 size;
    s32 angle1;
    s32 angle2;
    CharacterFlamethrowerEmissionPreset *preset;
    CharacterFlamethrowerState *state;

    state = arg0->state;
    packet.position[0] = (s16)(s32)arg0->position[0];
    preset = &D_800A8770[*((u8 *)state + 0x80)];
    packet.position[1] = (s16)(s32)arg0->position[1];
    packet.fraction_x = 0;
    packet.fraction_z = 0;
    packet.fraction_y = 0;
    packet.red = 0xFF;
    packet.green = 0xFF;
    packet.blue = 0xFF;
    packet.environment[0] = 0;
    packet.environment[1] = 0;
    packet.environment[2] = 0;
    packet.alpha = 0xFF;
    packet.callback = -1;
    packet.flags = 0x12;
    packet.frame = 0;
    packet.frame_rate = 0;
    packet.texture = D_80090514;
    packet.lifetime = 300;
    packet.position[2] = (s16)(s32)arg0->position[2];
    do {
        speed = func_150ADA68() * preset->speed_range + preset->speed;
        angle1 = func_150ADA20();
        angle1 &= 0xFF;
        angle2 = func_150ADA20();
        angle2 &= 0xFF;
        cosine1 = func_151423D8((angle1 - 64) & 0xFF);
        sine1 = func_151423D8(angle1 & 0xFF);
        cosine2 = func_151423D8((angle2 - 64) & 0xFF);
        sine2 = func_151423D8(angle2 & 0xFF);
        radius = preset->radius;
        scale = radius * sine2;
        x = arg1->x + scale * cosine1;
        y = arg1->y - radius * cosine2;
        z = arg1->z + scale * sine1;
        packet.velocity_x = (s16)(s32)((x - arg0->position[0]) * speed);
        packet.velocity_y = (s16)(s32)((y - arg0->position[1]) * speed);
        packet.velocity_z = (s16)(s32)((z - arg0->position[2]) * speed);
        packet.acceleration = func_150ADA20() % (u32)(preset->acceleration_range + 1) + preset->acceleration;
        packet.fade = func_150ADA20() % (u32)(preset->fade_range + 1) + preset->fade;
        size = func_150ADA20() % (u32)(preset->size_range + 1) + preset->size;
        packet.height = size;
        packet.width = size;
        func_15167D84(&packet, 0, 0, -1, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
        *(f32 *)((u8 *)state + 0x88) -= 1.0f;
    } while (*(f32 *)((u8 *)state + 0x88) > 1.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151990AC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151990AC.s")
void func_151993B4(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *state = arg0->state;

    arg0->unk30 = 0;
    arg0->flags1E &= 0xFFFD;
    state->flags6 |= 1;
    state->flags6 |= 4;
}
extern u8 D_800A8A9C;
extern CharacterFlamethrowerSlot *D_800E0900[];

void func_151993E4(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *temp_v0;
    CharacterFlamethrowerIdentity *temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *var_t0;
    s32 temp_a3;

    temp_v0 = arg0->state;
    temp_v1 = temp_v0->identity;
    var_a1 = 0;
    var_a2 = 0;
    temp_a3 = temp_v1->unk3B;
    var_t0 = &D_800A8A9C;
    do {
        if (temp_a3 == *var_t0) {
            var_a2 = 1;
        } else {
            var_a1++;
            var_t0++;
        }
    } while ((var_a2 == 0) && (var_a1 < 6));
    if (var_a2 != 0) {
        D_800E0900[var_a1]->active = 0;
    }
}
void func_1519944C(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *temp_v0;
    CharacterFlamethrowerIdentity *temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *var_t0;
    s32 temp_a3;

    temp_v0 = arg0->state;
    temp_v1 = temp_v0->identity;
    var_a1 = 0;
    var_a2 = 0;
    temp_a3 = temp_v1->unk3B;
    var_t0 = &D_800A8A9C;
    do {
        if (temp_a3 == *var_t0) {
            var_a2 = 1;
        } else {
            var_a1++;
            var_t0++;
        }
    } while ((var_a2 == 0) && (var_a1 < 6));
    if (var_a2 != 0) {
        D_800E0900[var_a1]->active = 1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_151994B8.s")
void func_15199834(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerLocal sp18;

    if (arg0 != 0) {
        sp18.actor = arg0;
        sp18.unk4 = arg0->unk3B;
        func_15147D64(&sp18, 0x26, arg0);
    }
}
void func_1519986C(CharacterFlamethrowerActor *actor, CharacterFlamethrowerEvent *event, u8 kind) {
    s32 key;
    CharacterFlamethrowerState *state = actor->state;

    if (kind == 0 || kind == 2 || kind == 0x26) {
        if (event->removed.identity == state->identity || event->removed.generation == state->generation) {
            func_1516972C(actor);
        }
    } else if (kind == 0x2D) {
        actor = (CharacterFlamethrowerActor *)event->replaced.first;
        key = (s32)state->identity;
        if ((s32)actor == key) {
            state->identity = event->replaced.second;
            state->generation = event->replaced.second_generation;
            return;
        }
        key = (s32)event->replaced.second ^ key;
        if (key == 0) {
            state->identity = (CharacterFlamethrowerIdentity *)actor;
            state->generation = event->replaced.first_generation;
        }
    }
}
void func_15199928(void *arg0) {
    func_15199980(arg0);
    func_151478F4(arg0);
}
void func_15199954(void *arg0) {
    func_15199980(arg0);
    func_15147928(arg0);
}
void func_15199980(void *arg0) {
    CharacterFlamethrowerState *var_v1;
    s8 temp_v0;
    s8 temp_v0_2;
    void *temp_a0;

    var_v1 = ((CharacterFlamethrowerActor *)arg0)->state;
    temp_v0 = var_v1->unk39;
    if (temp_v0 != -1) {
        D_8008F8C0[temp_v0]();
    }
    temp_v0_2 = var_v1->unk36;
    if (temp_v0_2 != -1) {
        D_8008F8B4[temp_v0_2](arg0);
    }
    temp_a0 = var_v1->unk148;
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
    return;
}
typedef struct CharacterFlamethrowerMovingPoint {
    CharacterFlamethrowerVec3 position;
    CharacterFlamethrowerVec3 velocity;
    f32 size;
    u8 pad1C[0xC];
} CharacterFlamethrowerMovingPoint;

typedef struct CharacterFlamethrowerShortPosition {
    u8 pad0[0xE];
    s16 x;
    s16 y;
    s16 z;
} CharacterFlamethrowerShortPosition;

typedef struct CharacterFlamethrowerAttachment {
    u8 pad0[0x14];
    CharacterFlamethrowerShortPosition *position;
} CharacterFlamethrowerAttachment;

extern s32 (*D_8008F8C4[])(CharacterFlamethrowerActor *);
extern void (*D_8008F8BC[])(CharacterFlamethrowerActor *);
void func_1519BE1C(CharacterFlamethrowerVec3 *, CharacterFlamethrowerVec3 *, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15199A10 CURRENT (215) */
s32 func_15199A10(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerMovingPoint *point;
    s32 index;
    CharacterFlamethrowerState *state;
    u8 *points;
    CharacterFlamethrowerAttachment *attachment;
    CharacterFlamethrowerShortPosition *position;
    CharacterFlamethrowerMovingPoint *head;

    state = arg0->state;
    points = arg0->points;
    state->flags150 &= ~0x10;
    if ((arg0->unk2C < 2) && (arg0->flags1E & 8)) {
        return 0;
    }
    if ((state->callback48 != -1) && (D_8008F8C4[state->callback48](arg0) == 0)) {
        return 0;
    }
    index = arg0->point_end;
    if (index != arg0->point_index) {
        do {
            index--;
            if (index < 0) {
                index = arg0->point_capacity - 1;
            }
            point = (CharacterFlamethrowerMovingPoint *)(index * 0x28 + points);
            func_1519BE1C(&point->position, &point->velocity, state->gravity, D_800BE9A4);
            point->size += state->size_rate * D_800BE9A4;
        } while (index != arg0->point_index);
    }
    attachment = (CharacterFlamethrowerAttachment *)state->unk148;
    if ((attachment != 0) && (arg0->unk2C >= 2)) {
        position = attachment->position;
        head = (CharacterFlamethrowerMovingPoint *)(arg0->point_index * 0x28 + points);
        position->x = (s16)(s32)head->position.x;
        position->y = (s16)(s32)head->position.y;
        position->z = (s16)(s32)head->position.z;
    }
    if (state->callback38 != -1) {
        D_8008F8BC[state->callback38](arg0);
    }
    state->flags150 &= ~1;
    if (arg0->unk2C > 0) {
        arg0->last_position = ((CharacterFlamethrowerMovingPoint *)points)[arg0->point_index].position;
    } else {
        arg0->last_position.x = 0.0f;
        arg0->last_position.y = 0.0f;
        arg0->last_position.z = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15199A10 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199A10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_15199C34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519A9A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519B4B8.s")
void func_1519BE1C(CharacterFlamethrowerVec3 *arg0, CharacterFlamethrowerVec3 *arg1, f32 arg2, f32 arg3) {
    CharacterFlamethrowerVec3 temp;

    temp = *arg1;
    arg1->y = (f32) (arg1->y + (arg2 * arg3));
    arg0->x = (f32) (arg0->x + (temp.x * arg3));
    arg0->y = (f32) (arg0->y + ((temp.y * arg3) + (0.5f * arg2 * arg3 * arg3)));
    arg0->z = (f32) (arg0->z + (temp.z * arg3));
}
void func_1519BEB8(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *temp_v0;
    CharacterFlamethrowerIdentity *temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *var_t0;
    s32 temp_a3;

    temp_v0 = arg0->state;
    temp_v1 = temp_v0->identity;
    var_a1 = 0;
    var_a2 = 0;
    temp_a3 = temp_v1->unk3B;
    var_t0 = &D_800A8A9C;
    do {
        if (temp_a3 == *var_t0) {
            var_a2 = 1;
        } else {
            var_a1++;
            var_t0++;
        }
    } while ((var_a2 == 0) && (var_a1 < 6));
    if (var_a2 != 0) {
        D_800E0900[var_a1]->active = 0;
    }
}
void func_1519BF20(CharacterFlamethrowerActor *arg0) {
    CharacterFlamethrowerState *temp_v0;
    CharacterFlamethrowerIdentity *temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *var_t0;
    s32 temp_a3;

    temp_v0 = arg0->state;
    temp_v1 = temp_v0->identity;
    var_a1 = 0;
    var_a2 = 0;
    temp_a3 = temp_v1->unk3B;
    var_t0 = &D_800A8A9C;
    do {
        if (temp_a3 == *var_t0) {
            var_a2 = 1;
        } else {
            var_a1++;
            var_t0++;
        }
    } while ((var_a2 == 0) && (var_a1 < 6));
    if (var_a2 != 0) {
        D_800E0900[var_a1]->active = 1;
    }
}
void func_1519BF8C(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
void func_1519BFBC(CharacterFlamethrowerActor *actor) {
    CharacterFlamethrowerState *state = actor->state;
    f32 (*points)[10] = actor->points;
    u16 sound;

    if (actor->unk2C != 0) {
        sound = state->unk130;
        if (sound != 0) {
            func_1000F91C(sound, 0x7FFF, 0, 0, 0,
                         (s32)points[actor->point_index][0], (s32)points[actor->point_index][1], (s32)points[actor->point_index][2],
                         500, 5000);
        }
    }
}
void func_1519C06C(CharacterFlamethrowerActor *arg0) {
    register CharacterFlamethrowerState *temp_v0 = arg0->state;
    register u16 temp_a1 = temp_v0->unk130;

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}
typedef struct CharacterFlamethrowerLightDescriptor {
    u8 field0;
    s8 field1;
    s16 field2;
    s8 field4;
} CharacterFlamethrowerLightDescriptor;

void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A8AF8;

s32 func_1519C09C(s32 arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4,
                 u8 arg5, u8 arg6, s32 arg7) {
    s32 result;
    CharacterFlamethrowerLightDescriptor descriptor;
    s32 position[3];
    s32 owner;
    f32 values[8];

    values[0] = 35.0f;
    values[1] = 5.0f;
    owner = arg0;
    descriptor.field0 = 2;
    descriptor.field1 = 2;
    descriptor.field2 = 0x12C;
    descriptor.field4 = 0x22;
    values[2] = 110.0f;
    values[3] = 1.0f;
    values[4] = 0.0f;
    values[5] = 7.0f;
    values[6] = D_800A8AF8;
    values[7] = 127.0f;
    position[0] = (s32)arg1[0];
    position[1] = (s32)arg1[1];
    position[2] = (s32)arg1[2];
    result = func_151602C0((u8 *)&descriptor, position, arg2, arg3, arg4,
                          arg5, 0xFF, 0, 0x24, arg6, arg7);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, values, 0x20);
        func_10022EC0((u8 *)result + 0x38, &owner, 4);
    }
    return result;
}
void func_1519C200(CharacterFlamethrowerContext *arg0) {
    func_1519C258(arg0);
    func_151617C4(arg0);
}
void func_1519C22C(CharacterFlamethrowerContext *arg0) {
    func_1519C258(arg0);
    func_151617E4(arg0);
}
void func_1519C258(CharacterFlamethrowerContext *arg0) {
    void *state = arg0->actor->state;

    ((CharacterFlamethrowerState *)state)->unk148 = 0;
}
typedef struct CharacterFlamethrowerVelocity {
    CharacterFlamethrowerPosition first;
    CharacterFlamethrowerPosition second;
    f32 gravity;
    f32 damping;
    f32 second_damping;
} CharacterFlamethrowerVelocity;

typedef struct CharacterFlamethrowerMotion {
    u8 pad0[0x34];
    CharacterFlamethrowerPosition position;
    CharacterFlamethrowerPosition second_position;
    u8 pad4C[0xC4];
    CharacterFlamethrowerVelocity motion;
} CharacterFlamethrowerMotion;

extern f32 D_800BE9A8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519C26C CURRENT (400) */
s32 func_1519C26C(CharacterFlamethrowerMotion *arg0) {
    f32 time_squared;
    CharacterFlamethrowerPosition first;
    CharacterFlamethrowerPosition second;
    CharacterFlamethrowerPosition first_acceleration;
    CharacterFlamethrowerPosition second_acceleration;
    s32 steps;
    CharacterFlamethrowerVelocity *velocity;

    velocity = &arg0->motion;
    time_squared = D_800BE9A4 * D_800BE9A4;
    first = velocity->first;
    second = arg0->motion.second;
    arg0->motion.first.y += arg0->motion.gravity * D_800BE9A4;
    arg0->motion.second.y += arg0->motion.gravity * D_800BE9A4;
    steps = D_800BE9E4;
    if (steps > 0) {
        do {
            steps--;
            velocity->first.x *= velocity->damping;
            velocity->first.y *= velocity->damping;
            velocity->first.z *= velocity->damping;
            velocity->second.x *= velocity->second_damping;
            velocity->second.y *= velocity->second_damping;
            velocity->second.z *= velocity->second_damping;
        } while (steps > 0);
    }
    first_acceleration.x = (velocity->first.x - first.x) * D_800BE9A8;
    first_acceleration.y = (velocity->first.y - first.y) * D_800BE9A8;
    first_acceleration.z = (velocity->first.z - first.z) * D_800BE9A8;
    second_acceleration.x = (velocity->second.x - second.x) * D_800BE9A8;
    second_acceleration.y = (velocity->second.y - second.y) * D_800BE9A8;
    second_acceleration.z = (velocity->second.z - second.z) * D_800BE9A8;
    arg0->position.x += first.x * D_800BE9A4 + 0.5f * first_acceleration.x * time_squared;
    arg0->position.y += first.y * D_800BE9A4 + 0.5f * first_acceleration.y * time_squared;
    arg0->position.z += first.z * D_800BE9A4 + 0.5f * first_acceleration.z * time_squared;
    arg0->second_position.x += second.x * D_800BE9A4 + 0.5f * second_acceleration.x * time_squared;
    arg0->second_position.y += second.y * D_800BE9A4 + 0.5f * second_acceleration.y * time_squared;
    arg0->second_position.z += second.z * D_800BE9A4 + 0.5f * second_acceleration.z * time_squared;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519C26C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C26C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519C4E4 CURRENT (540) */
s32 func_1519C4E4(u8 *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v1;
    s32 temp_lo;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = D_800BE9E4;
    temp_v0 = (void *)(arg0 + 0x110);
    if (var_v1 > 0) {
        do {
            temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
            temp_fv1 = *(f32 *)((u8 *)arg0 + 0x30);
            var_v1 -= 1;
            *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * *(f32 *)((u8 *)temp_v0 + 0x24)));
            *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv1 - (temp_fv1 * *(f32 *)((u8 *)temp_v0 + 0x24)));
        } while (var_v1 > 0);
    }
    temp_v0_2 = (void *)(arg0 + 0x110);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v1 < *(s16 *)((u8 *)temp_v0_2 + 0x28)) {
        temp_lo = temp_v1 * *(s16 *)((u8 *)temp_v0_2 + 0x2A);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_lo;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519C4E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C4E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C56C.s")
s32 func_1519C910(CharacterFlamethrowerActor *arg0) {
    register CharacterFlamethrowerState *temp_v0 = arg0->state;
    register CharacterFlamethrowerIdentity *temp_v1 = temp_v0->identity;
    u16 temp_a1 = temp_v1->unk84;

    if ((temp_a1 != temp_v0->unk158) && (temp_a1 != temp_v0->unk15C)) {
        return 0;
    }
    return 1;
}
s32 func_1519C948(s32 arg0) {
    func_1519CDB0((CharacterFlamethrowerActor *)arg0, 0.25f, 0x1C);
    return 0;
}
s32 func_1519C970(s32 arg0) {
    func_1519CDB0((CharacterFlamethrowerActor *)arg0, 0.5f, 0x1D);
    return 0;
}
s32 func_1519C998(s32 arg0) {
    func_1519CDB0((CharacterFlamethrowerActor *)arg0, 0.2f, 0x1D);
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519C9C4.s")
void func_1519CD64(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x28);
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) == 0xFF) || (*(u8 *)((u8 *)arg0 + 0x2C) != *(u8 *)((u8 *)temp_v0 + 0x3B))) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        ((u8 *)arg0)[0xD] |= 1;
    }
}
typedef struct CharacterFlamethrowerTrailPoint {
    f32 position[3];
    u8 padC[0x10];
    f32 distance;
    u8 pad20[0x8];
} CharacterFlamethrowerTrailPoint;

s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519CDB0 CURRENT (970) */
void func_1519CDB0(CharacterFlamethrowerActor *arg0, f32 arg1, s32 arg2) {
    f32 interpolated_z;
    f32 distance;
    f32 spacing;
    f32 factor;
    f32 total;
    f32 next;
    u8 *points;
    s32 index;
    CharacterFlamethrowerState *state;
    CharacterFlamethrowerTrailPoint *point;
    CharacterFlamethrowerIdentity *identity;
    f32 *previous;

    state = arg0->state;
    points = arg0->points;
    previous = arg0->position;
    if (arg0->unk2C >= 2) {
        total = 0.0f;
        spacing = state->spacing * arg1;
        index = arg0->point_end;
        next = 0.0f;
        do {
            index--;
            if (index < 0) {
                index = arg0->point_capacity - 1;
            }
            point = (CharacterFlamethrowerTrailPoint *)(index * 0x28 + points);
            distance = point->distance;
            total += distance;
            if (next <= total) {
                identity = state->identity;
                factor = (total - next) / distance;
                func_1505D1C4(point->position[0] + ((previous[0] - point->position[0]) * factor),
                    point->position[1] + ((previous[1] - point->position[1]) * factor),
                    (interpolated_z = point->position[2] + ((previous[2] - point->position[2]) * factor)), arg2,
                    ((s32)identity - (s32)D_800CC2D0) / 0x32C,
                    identity->unk76, 0, 0);
                next += spacing;
            }
            previous = point->position;
        } while (index != arg0->point_index);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519CDB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/characterflamethrower/func_1519CDB0.s")
