#include "types.h"

/*
 * Reviewed source unit: src/game/game_43880.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct {
    s32 offset;
    s32 other;
} Game43880Record;

s32 func_1502B7F0(s32 **, s32, s32, s32, s32);
extern s32 *D_800D18B0;

void func_150163D0(s32 arg0) {
    s32 count;
    s32 i;

    if (func_1502B7F0(&D_800D18B0, 3, 0xC, arg0, 9) > 0) {
        count = 1;
        i = 0;
        while (((Game43880Record *) D_800D18B0)[i].offset != 0) {
            count++;
            i++;
        }
        for (i = 0; i < count - 1; i++) {
            ((Game43880Record *) D_800D18B0)[i].offset += (s32) D_800D18B0;
        }
    } else {
        D_800D18B0 = 0;
    }
}
