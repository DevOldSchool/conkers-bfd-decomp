#include "types.h"

/*
 * Reviewed source unit: src/game/game_11FF10.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F2A60
 * - func_150F2D14
 * - func_150F3214
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11FF10Actor {
    u8 pad0[0x120];
    u8 disabled;
    u8 pad121[0x1C3];
    s32 scroll;
    u8 pad2E8[0x44];
} Game11FF10Actor;

void func_10010630(u16, void *, s32, s16, u16);
void func_15060F28(u8 *, s32);
void func_1507CD64(void *, s32);
void *func_15083E90(u8);
s32 func_151149AC(u8);
void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void func_15145A50(u8 *);
void func_15196318(void *, s32, s32);
extern void **D_800BE4F0;
extern u8 D_800CC2D0;
extern u8 D_800CC40C;
extern s8 D_800CC49A;
extern void *D_800CC5EC;
extern s32 D_800DBEF4;
extern s32 D_800DBF94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2A60 CURRENT (3125) */
void func_150F2A60(s32 arg0) {
    s32 negative;
    s32 resource;
    s32 i;
    s32 index;
    Game11FF10Actor *actor;

    if (D_800CC5EC != 0) {
        i = 0;
        if (((Game11FF10Actor *)D_800CC5EC)->disabled == 0) {
loop:
            {
                resource = func_151149AC((u8)(0xFA - i));
                i++;
                index = (resource - D_800DBEF4) / 160;
                if (*(s32 *)(D_800DBF94 + index * 4) & 1) {
                    if (D_800CC40C != 0) {
                        func_15060F28((u8 *)(D_800CC40C * 0x32C - 81200 + (u32)&D_800CC2D0), 0);
                    }
                    D_800CC49A = 0;
                    func_15136C3C(&D_800CC2D0, 0, 0, 1, 1, 0, 0xFF, 1);
                    func_10010630(0x627, &D_800CC2D0, 0x6D60, 0x1F4, 0x3E8);
                    func_15145A50(&D_800CC2D0);
                    func_1507CD64(&D_800CC2D0, 6);
                } else if (i < 2) {
                    goto loop;
                }
            }
            actor = func_15083E90(0xE);
            if (actor != 0) {
                i = actor->scroll;
            } else {
                i = 0;
            }
            func_15196318(D_800BE4F0[0], i, 0);
            negative = -i;
            func_15196318(D_800BE4F0[1], 0, negative);
            func_15196318(D_800BE4F0[2], i, 0);
            func_15196318(D_800BE4F0[3], negative, 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FF10/func_150F2A60.s")
void func_10022EC0(void *, void *, s32);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct Game11FF10F2C8CPacket {
    void *owner;
    u8 type;
    s8 field5;
    u8 pad6[2];
    f32 value;
    s8 fieldC;
    u8 padD[3];
} Game11FF10F2C8CPacket;

void func_150F2C8C(void *arg0) {
    Game11FF10F2C8CPacket packet;
    s32 temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field5 = 0;
    packet.fieldC = 0;
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x5C, -1, 0, 0x44, 0x10, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x10);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FF10/func_150F2D14.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F3194(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_150F31D4(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}
void func_15143134(f32 *, f32 *, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A1950;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F3214 CURRENT (36) */
s32 func_150F3214(void *arg0) {
    u8 *owner = (u8 *)arg0;
    u8 *link;
    u8 *slot;
    s32 transform;

    link = *(u8 **)(owner + 0x110);
    slot = owner + 0x110;
    if (*(s32 *)link == 0 || slot[4] != link[0x3B] ||
        (transform = *(s32 *)(link + 0x1D4)) == 0) {
        return 0;
    }
    func_15143134(&D_800A1950, (f32 *)(owner + 0x34), (s32)((u32)transform + 0x3C0U));
    *(f32 *)(owner + 0x2C) = *(f32 *)(owner + 0x30) =
        *(f32 *)(slot + 0x10) * sqrtf(*(f32 *)(slot + 8));
    *(s8 *)(owner + 0x5C) = (s8)(u32)(*(f32 *)(slot + 0x14) -
        (*(f32 *)(slot + 8) * (*(f32 *)(slot + 0x18) * *(f32 *)(slot + 8))));
    *(f32 *)(slot + 8) += D_800BE9A4;
    if (*(f32 *)(slot + 0xC) < *(f32 *)(slot + 8)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F3214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FF10/func_150F3214.s")
s32 func_15140410(s32, s32, s32, s16);

void func_150F337C(s32 arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}
