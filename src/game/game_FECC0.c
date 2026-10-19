#include "types.h"

/*
 * Reviewed source unit: src/game/game_FECC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1810
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFECC0Command { u32 w0, w1; } GameFECC0Command;
typedef struct GameFECC0Vertex {
    s16 position[3];
    u16 flag;
    s16 texcoord[2];
    u8 color[4];
} GameFECC0Vertex;
typedef struct GameFECC0View {
    u8 pad0[0xB8];
    u16 normalization;
    u8 padBA[2];
    f32 matrix[16];
    u8 padFC[0x180 - 0xFC];
} GameFECC0View;
typedef union GameFECC0Index {
    s32 word;
    struct { s16 high, low; } halves;
} GameFECC0Index;
struct GameC2350Output {
    void *data;
    s16 width, height;
    u8 format, size, flags;
};
void *func_1501A490(void *, s16, s32, s32, s32, s32);
void *func_1501A680(void *);
s32 func_150950D4(s32, struct GameC2350Output *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150A7790(void *, s32);
void func_150A7A48(void *, void *, void *);
void func_151102CC(void *, f32, f32, f32);
extern GameFECC0Index D_80082FA4;
extern u8 D_80089470[];
extern GameFECC0View *D_800BE628;
extern u8 D_800BE9C0;
extern s32 D_800BE9F0;
extern void *D_800DBE80;
extern GameFECC0Vertex *D_800DBE88[][2];
extern u8 *D_800DBEB0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1810 CURRENT (1399) */
GameFECC0Command *func_150D1810(GameFECC0Command *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, f32 arg6) {
    f32 spC0[16];
    f32 sp80[16];
    s32 sp7C;
    s32 sp78;
    struct GameC2350Output sp64;
    s16 temp_a3;
    s16 temp_t0;
    s32 temp_ft3;
    GameFECC0Vertex *temp_a2;

    if ((D_800BE9F0 == 0x33) || (D_800BE9F0 == 0x32) || (D_800BE9F0 == 0x3F)) {
        sp7C = -0x62;
        sp78 = 0x27;
    } else {
        sp7C = -0x13;
        sp78 = 0x65;
    }
    sp64.width = 4;
    sp64.height = 0x100;
    sp64.format = 0;
    sp64.size = 3;
    sp64.flags = 0;
    sp64.data = D_800DBE80;
    { GameFECC0Command *command = arg0++; command->w0 = 0xD7000002; command->w1 = 0xFFFFFFFF; }
    { GameFECC0Command *command = arg0++; command->w0 = 0xE7000000; command->w1 = 0; }
    { GameFECC0Command *command = arg0++; command->w0 = 0xEF082C0F; command->w1 = 0x0F0A4004; }
    { GameFECC0Command *command = arg0++; command->w0 = 0xFCFFFFFF; command->w1 = 0xFFFCF279; }
    arg0 = (GameFECC0Command *) func_150950D4((s32) func_1501A680(func_1501A490(arg0, D_80082FA4.halves.low, 0, 0, 0, 0)), &sp64, 0, 0, 0, 0, 2, 0x100, 0x100, 3);
    func_151102CC(spC0, 0.0f, 0.0f, arg6);
    func_150A7A48(spC0, D_800BE628[D_80082FA4.word].matrix, sp80);
    func_150A7790(sp80, (s32) (D_800DBEB0 + (((D_80082FA4.word * 2) + D_800BE9C0) << 6)));
    { GameFECC0Command *command = arg0++; command->w0 = 0xDA380007; command->w1 = (u32) (D_800DBEB0 + (((D_80082FA4.word * 2) + D_800BE9C0) << 6)); }
    { GameFECC0Command *command = arg0++; command->w0 = 0xDA380003; command->w1 = (u32) D_80089470; }
    { GameFECC0Command *command = arg0++; command->w0 = 0xDB0E0000; command->w1 = D_800BE628[D_80082FA4.word].normalization; }
    temp_ft3 = (s32) (arg4 * 81.0f);
    temp_a2 = D_800DBE88[D_80082FA4.word][D_800BE9C0];
    temp_a3 = ((sp7C + 0x100) << 5) + temp_ft3;
    temp_a2[1].texcoord[1] = temp_a3;
    temp_a2[0].texcoord[1] = temp_a3;
    temp_t0 = ((sp78 + 0x1FF) << 5) + temp_ft3;
    temp_a2[3].texcoord[1] = temp_t0;
    temp_a2[2].texcoord[1] = temp_t0;
    { GameFECC0Command *command = arg0++; command->w0 = 0x01004008; command->w1 = (u32) temp_a2; }
    { GameFECC0Command *command = arg0++; command->w0 = 0x06000204; command->w1 = 0x406; }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FECC0/func_150D1810.s")
