#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D770.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 */

typedef struct Game11D770Inner {
    u8 pad0[0x134];
    s32 field_134;
} Game11D770Inner;

typedef struct Game11D770Object {
    u8 pad0[0x28];
    Game11D770Inner *inner;
} Game11D770Object;

Game11D770Inner *func_150F0318(Game11D770Object *arg0);
void func_1514933C(s32 arg0);
void func_15149368(Game11D770Object *arg0);
void func_150F0380(s32 arg0);
void func_151411A4(s32 arg0);
void func_151411C4(s32 arg0);

void func_150F02C0(Game11D770Object *arg0) {
    func_150F0318(arg0);
    func_1514933C((s32) arg0);
}
void func_150F02EC(Game11D770Object *arg0) {
    func_150F0318(arg0);
    func_15149368(arg0);
}
Game11D770Inner *func_150F0318(Game11D770Object *arg0) {
    Game11D770Inner *inner = arg0->inner;

    inner->field_134 = 0;
    return inner;
}
void func_150F0328(s32 arg0) {
    func_150F0380(arg0);
    func_151411A4(arg0);
}
void func_150F0354(s32 arg0) {
    func_150F0380(arg0);
    func_151411C4(arg0);
}
