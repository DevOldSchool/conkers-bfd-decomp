#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_functions.h"
#include "game_view.h"

/*
 * Reviewed source unit: src/game/game_182C30.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15155CFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game182C30Effect {
    u8 pad0[0xE];
    s16 fieldE;
    s8 field10;
    u8 field11;
    u8 field12;
    u8 pad13;
    struct Game18A8F0ListNode *field14;
    u8 pad18[0x80];
    f32 field98;
} Game182C30Effect;

s32 func_1518C900(s32); /* extern */

Game182C30Effect *func_15155780(s32 arg0, s32 arg1) {
    Game182C30Effect *effect;

    effect = func_15167A68(0x50, 0, 0xA0, 1, arg1, 1);
    if (effect == 0) {
        return effect;
    }
    effect->field10 = arg0;
    effect->field11 = 0;
    effect->field14 = 0;
    effect->field98 = 0.0f;
    func_1518C900(0xA6);
    return effect;
}
void *func_15155FD4(s32);
extern u8 D_800CC37D[];

void func_151557FC(s32 arg0, s32 arg1, f32 arg2) {
    Game182C30Effect *effect;

    effect = func_15155FD4(arg0);
    if (effect == 0) {
        effect = func_15155780(arg0, 0xFF);
    }
    if (effect != 0) {
        effect->field98 = arg2;
        if (D_800CC37D[arg0 * 0x32C] != 0) {
            effect->fieldE = 0;
            effect->field11 = 0;
            return;
        }
        effect->field11 = 3;
        effect->fieldE = (s16)arg1;
    }
}
void func_10010F30(s32, s32, s32, s32, s32);
void *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);
extern s32 D_800BE9E4;
extern u8 D_800CC2D0[];
extern u8 D_800D2E68;

void func_1515589C(Game182C30Effect *arg0) {
    u32 index;
    u8 *actor;
    u8 *owner;
    s32 kind;
    s32 timer;

    actor = D_800CC2D0 + (u8)arg0->field10 * 0x32C;
    index = (u8)arg0->field10;
    switch (arg0->field11) {
    case 0:
        owner = *(u8 **)(D_800CC2D0 + index * 0x32C + 0x31C);
        if (owner != NULL) {
            kind = owner[0x75];
        } else {
            kind = 0;
        }
        if (!(kind & 0x80) && kind != 0x2A && kind != 0x2B && (kind != 0x42 || !(D_800D2E68 & 4)) &&
            kind != 0x2C && owner[0x197] == 0 && kind != 0 && kind != 0x1F && actor[0xAD] == 0) {
            arg0->field11 = 1;
            arg0->fieldE = 0x78;
            func_10010F30(0x1EB, 0x7FFF, 0x40, 0, 0);
        } else if (arg0->field14 != NULL) {
            func_1515F10C(arg0->field14);
            arg0->field14 = NULL;
        }
        break;
    case 1:
        timer = arg0->fieldE;
        timer -= D_800BE9E4;
        if (timer <= 0 || (*(u8 **)(D_800CC2D0 + index * 0x32C + 0x31C))[0x75] == 0) {
            arg0->field11 = 2;
            timer = 0;
        }
        arg0->fieldE = timer;
        arg0->field12 += D_800BE9E4 * 2;
        if (arg0->field14 != NULL) {
            f32 height;

            if ((*(u8 **)(D_800CC2D0 + index * 0x32C + 0x31C))[0x75] == 5) {
                height = 85.0f;
            } else {
                height = 0.0f;
            }
            *(s16 *)((u8 *)arg0->field14 + 0xE) = *(f32 *)(actor + 0x14);
            *(s16 *)((u8 *)arg0->field14 + 0x10) =
                (*(f32 *)(actor + 0x18) + 160.0f + arg0->field98 + height) + func_15048A40(arg0->field12) * 15.0f;
            *(s16 *)((u8 *)arg0->field14 + 0x12) = *(f32 *)(actor + 0x1C);
        } else {
            arg0->field14 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
        }
        break;
    case 2:
        if ((*(u8 **)(D_800CC2D0 + index * 0x32C + 0x31C))[0x75] == 0) {
            arg0->field11 = 0;
        }
        if (arg0->field14 != NULL) {
            func_1515F10C(arg0->field14);
            arg0->field14 = NULL;
        }
        break;
    case 3:
        timer = arg0->fieldE;
        timer -= D_800BE9E4;
        if (timer <= 0) {
            arg0->field11 = 2;
            arg0->fieldE = 0;
            break;
        }
        arg0->fieldE = timer;
        arg0->field12 += D_800BE9E4 * 2;
        if (arg0->field14 != NULL) {
            *(s16 *)((u8 *)arg0->field14 + 0xE) = *(f32 *)(actor + 0x14);
            *(s16 *)((u8 *)arg0->field14 + 0x10) =
                (*(f32 *)(actor + 0x18) + 160.0f) + func_15048A40(arg0->field12) * 15.0f;
            *(s16 *)((u8 *)arg0->field14 + 0x12) = *(f32 *)(actor + 0x1C);
        } else {
            arg0->field14 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
        }
        break;
    }
}
void *func_15096934(void *);
void func_15043D90(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern u8 D_800BE9C0;
extern u8 D_800CC2D0[];
extern s32 *D_800E03E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155CFC */
Gfx *func_15155CFC(Gfx *gdl, Game182C30Effect *arg1, s16 arg2) {
    u8 state;
    f32 scale;
    f32 angle;
    u8 index;
    f32 height;

    state = arg1->field11;
    index = arg1->field10;
    if (state == 1 || state == 3) {
        if ((*(u8 **)(D_800CC2D0 + index * 0x32C + 0x31C))[0x75] == 5) {
            height = 85.0f;
        } else {
            height = 0.0f;
        }
        scale = 2.25f;
        angle = D_800DBFF0[arg2].unk380;
        gdl = func_15096934(gdl);
        func_15043D90((s32)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x18),
            0.0f, angle, 0.0f, scale, scale, scale,
            *(f32 *)(D_800CC2D0 + index * 0x32C + 0x14),
            (*(f32 *)(D_800CC2D0 + index * 0x32C + 0x18) + 160.0f + height + arg1->field98) + func_15048A40(arg1->field12) * 15.0f,
            *(f32 *)(D_800CC2D0 + index * 0x32C + 0x1C));
        gSPMatrix(gdl++, (u8 *)arg1 + (D_800BE9C0 << 6) + 0x18, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPClearGeometryMode(gdl++, G_ZBUFFER);
        gSPDisplayList(gdl++, *D_800E03E0);
        gSPSetGeometryMode(gdl++, G_ZBUFFER);
    }
    return gdl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155CFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155CFC.s")

extern void func_1518CA04(s32 arg0);

void func_15155EF8(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0;
    if (*(void **)((u8 *)temp_a1 + 0x14) != 0) {
        func_1515F10C(*(void **)((u8 *)temp_a1 + 0x14));
    }
    func_15169804(temp_a1);
    func_1518CA04(0xA6);
}
/* Call context: func_15155FD4: unique active project prototype */
void * func_15155FD4(s32);
extern u8 D_800C3E78;

void func_15155F3C(void) {
    Game182C30Effect *effect;

    effect = func_15155FD4(D_800C3E78);
    if (effect != 0) {
        if (effect->field11 == 2) {
            effect->field11 = 0;
            return;
        }
        if (effect->field11 == 3) {
            effect->field11 = 2;
        }
    }
}
void *func_15155FD4(s32);                           /* extern */
extern u8 D_800C3E78;

void func_15155F90(void) {
    void *temp_v0;

    temp_v0 = func_15155FD4(D_800C3E78);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11) == 3)) {
        *(u8 *)((u8 *)temp_v0 + 0x11) = 1U;
    }
}
typedef struct Game182C30Node {
    u8 pad_0[8];
    struct Game182C30Node *next;
    u8 pad_C[4];
    u8 field_10;
} Game182C30Node;

typedef struct {
    u8 pad_0[0x140];
    Game182C30Node *field_140;
    u8 pad_144[0x5C];
} Game182C30Block;

extern Game182C30Block D_800DCE50;
extern Game182C30Block D_800DD190;

void *func_15155FD4(s32 arg0) {
    Game182C30Node *node;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (node = (&D_800DCE50)[i].field_140; node != 0; node = node->next) {
            if (arg0 == node->field_10) {
                return node;
            }
        }
    }
    return 0;
}
extern u8 D_800CC2D0[];

void func_15156028(u8 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 index = (arg1[0] - D_800CC2D0) / 0x32C;

        if (index >= 0 && index < 25 && index == arg0[0x10]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 first = (arg1[0] - D_800CC2D0) / 0x32C;
        s32 second = (arg1[1] - D_800CC2D0) / 0x32C;

        if (first >= 0 && first < 25 && second >= 0 && second < 25) {
            if (first == arg0[0x10]) {
                arg0[0x10] = second;
            } else if (second == arg0[0x10]) {
                arg0[0x10] = first;
            }
        }
    }
}
