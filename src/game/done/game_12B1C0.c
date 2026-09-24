#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B1C0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

typedef struct Game12B1C0Actor {
    u8 pad0[4];
    u8 field4;
    u8 pad5[0x327];
} Game12B1C0Actor;

void func_15103828(void);
void func_150ED638(void *, s32, s32);
extern u8 D_800C35EA;
extern Game12B1C0Actor D_800CC2D0[];
extern Game12B1C0Actor D_800D121C;

void func_150FDD10(s32 arg0) {
    Game12B1C0Actor *var_s0;

    func_15103828();
    if (D_800C35EA == 1) {
        var_s0 = D_800CC2D0;
        do {
            if (var_s0->field4 == 0x28) {
                func_150ED638(var_s0, 0x14, 0x14);
            }
            var_s0++;
        } while (var_s0 != &D_800D121C);
    }
}
