#include "types.h"

/*
 * Reviewed source unit: src/game/game_33660.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 */

typedef struct Game33660Table {
    void *items[4];
} Game33660Table;

void func_10023790(void *, void *, s32);
void func_100237C0(s32, void *, s32);
void func_15007644(void);
extern u8 D_800BE900[];
extern u8 D_800BE2D0[];
extern s32 D_800BE9E0;
extern Game33660Table D_800BE730;
extern u8 D_800BE748[];
extern u8 D_800BE74E[];
extern u8 D_800BE754[];
extern u8 D_800BE75A[];

void func_150061B0(void) {
    func_10023790(D_800BE900, D_800BE2D0, 8);
    func_100237C0(5, D_800BE900, D_800BE9E0);
    D_800BE730.items[0] = D_800BE748;
    D_800BE730.items[1] = D_800BE74E;
    D_800BE730.items[2] = D_800BE754;
    D_800BE730.items[3] = D_800BE75A;
    func_15007644();
}
/* SDK controller status and Pak storage, four independent channel lanes. */
typedef struct Game33660ControllerStatus {
    u16 type;
    u8 status;
    u8 error;
} Game33660ControllerStatus;

typedef struct Game33660Pak {
    s32 status;
    void *queue;
    s32 channel;
    u8 id[32];
    u8 label[32];
    s32 version;
    s32 directorySize;
    s32 inodeTable;
    s32 mirrorInodeTable;
    s32 directoryTable;
    s32 inodeStartPage;
    u8 banks;
    u8 activeBank;
} Game33660Pak;

s32 func_10025340(void *, u8 *, Game33660ControllerStatus *);
s32 func_10027660(void *, Game33660Pak *, s32);
s32 func_100057E0(void *, Game33660Pak *, s32);
s32 func_10005570(Game33660Pak *);
extern u8 D_8002AAE4;
extern Game33660ControllerStatus D_800BE2C0[4];
extern s16 D_800BE720[4];
extern s32 D_800BE72C;
extern u8 D_800BE740;
extern Game33660Pak D_800BE760[4];
extern u8 D_800BE93C[4];
extern u8 D_800BE940[4];
extern u8 D_800BE944[4];
extern u8 D_800BE948[4];
extern f32 D_800BE950[4];
extern f32 D_800BE960[4];
extern f32 D_800BE970[4];
extern f32 D_800BE980[4];

void func_15006234(void) {
    s32 channel;
    s32 result;
    u8 present;

    while (func_10025340(D_800BE900, &present, D_800BE2C0) != 0) {
    }
    D_800BE72C = 0;
    for (channel = 0; channel != 4; channel++) {
        D_800BE944[channel] = 0;
        D_800BE93C[channel] = 0;
        D_800BE940[channel] = 0;
        D_800BE948[channel] = 0;
        D_800BE950[channel] = 0.0f;
        D_800BE960[channel] = 1.0f;
        D_800BE970[channel] = 1.0f;
        D_800BE980[channel] = D_800BE960[channel] + D_800BE970[channel];
        D_800BE720[channel] = 0;
        if (present & (1 << channel)) {
            if (!(D_800BE2C0[channel].error & 8)) {
                D_800BE740 |= 1 << channel;
                D_800BE72C++;
                if ((D_800BE2C0[channel].type & 4) && (D_800BE2C0[channel].status & 1)) {
                    result = func_10027660(D_800BE900, &D_800BE760[channel], channel);
                    if (result == 10 || result == 11) {
                        if (func_100057E0(D_800BE900, &D_800BE760[channel], channel) == 0) {
                            D_800BE944[channel] = 1;
                            func_10005570(&D_800BE760[channel]);
                        }
                    }
                }
            }
        }
    }
    D_8002AAE4 = 1;
}
