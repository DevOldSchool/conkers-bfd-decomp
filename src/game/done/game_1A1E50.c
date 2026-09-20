#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A1E50.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 */

extern s32 D_800BE9E4;
extern u8 D_800DD405;
extern u8 D_800DD406;

void func_151749A0(s32 arg0, s32 arg1) {
    D_800DD406 += D_800BE9E4;
    if (D_800DD406 > arg0) {
        D_800DD405++;
        if (D_800DD405 >= arg1) {
            D_800DD405 = 0;
        }
        D_800DD406 = 0;
    }
}
typedef struct {
    u8 pad_0[0xB];
    u8 update_callback;
    u8 first_draw_callback;
    u8 second_draw_callback;
} Game1A1E50State;

extern void *D_800B0DF0;
extern s32 D_800B0E00[];
extern u8 D_800BE616;
extern u16 D_800CBD4E;
extern void (*D_8008CD04[])(s32);
void func_15165F70(void);
void func_15195FF0(s32, s32);
void func_1510C8A8(void);
void func_1517DE5C(void);
void func_151880C0(void);

void func_151749F8(s32 arg0, s32 arg1) {
    u8 callback;

    func_15165F70();
    func_15195FF0(D_800B0E00[0], D_800B0E00[1]);
    func_1510C8A8();
    callback = ((Game1A1E50State *)D_800B0DF0)->update_callback;
    if (callback != 0) {
        D_8008CD04[callback](arg1);
    }
    if (D_800BE616 == 0) {
        func_1517DE5C();
        func_151880C0();
    }
    D_800CBD4E += D_800BE9E4 << 6;
}
typedef union Game1A1E50DisplayCommand {
    struct {
        u32 word0;
        u32 word1;
    } words;
    u64 alignment;
} Game1A1E50DisplayCommand;

typedef Game1A1E50DisplayCommand *(*Game1A1E50Callback)(Game1A1E50DisplayCommand *, s32);

extern s32 D_80089470;
extern Game1A1E50Callback D_8008CD74[];
extern Game1A1E50Callback D_8008CD7C[];

/* Packet macros preserve the IDO instruction ordering of the display-list writes. */
#define GAME1A1E50_PIPE_SYNC(pkt)                               \
{                                                              \
    Game1A1E50DisplayCommand *command = (pkt);                   \
    command->words.word0 = 0xE7000000;                          \
    command->words.word1 = 0;                                   \
}
#define GAME1A1E50_MATRIX(pkt)                                  \
{                                                              \
    Game1A1E50DisplayCommand *command = (pkt);                   \
    command->words.word0 = 0xDA380003;                          \
    command->words.word1 = (u32)&D_80089470;                     \
}

Game1A1E50DisplayCommand *func_15174AA4(Game1A1E50DisplayCommand *arg0, s32 arg1, s32 arg2) {
    GAME1A1E50_PIPE_SYNC(arg0++);
    GAME1A1E50_MATRIX(arg0++);
    if (((Game1A1E50State *)D_800B0DF0)->first_draw_callback != 0) {
        arg0 = D_8008CD74[((Game1A1E50State *)D_800B0DF0)->first_draw_callback](arg0, arg2);
    }
    GAME1A1E50_MATRIX(arg0++);
    return arg0;
}

Game1A1E50DisplayCommand *func_15174B48(Game1A1E50DisplayCommand *arg0, s32 arg1, s32 arg2) {
    GAME1A1E50_PIPE_SYNC(arg0++);
    GAME1A1E50_MATRIX(arg0++);
    if (((Game1A1E50State *)D_800B0DF0)->second_draw_callback != 0) {
        arg0 = D_8008CD7C[((Game1A1E50State *)D_800B0DF0)->second_draw_callback](arg0, arg2);
    }
    GAME1A1E50_MATRIX(arg0++);
    return arg0;
}
