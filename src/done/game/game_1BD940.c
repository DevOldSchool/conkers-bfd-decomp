#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BD940.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 */

void func_1000FD38(void *, void *, s32);
void func_151D2B4C(s32);

void func_15190490(void *arg0) {
    func_15190454(arg0);
    func_151617E4(arg0);
}
void func_151904BC(void *arg0) {
    void *sp18 = (u8 *)arg0 + 0x30;

    if (*(s32 *)((u8 *)sp18 + 0x54) != 0) {
        func_1516972C(*(void **)((u8 *)sp18 + 0x54));
    }
    func_1000FD38(&func_1518E298, arg0, *(s32 *)((u8 *)arg0 + 0x10));
    func_151D2B4C(*(s32 *)((u8 *)sp18 + 0x48));
}
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8);

void func_15190518(void *arg0) {
    struct {
        void *object;
        u8 kind;
    } descriptor;

    descriptor.object = arg0;
    descriptor.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    func_1516944C(0x3E, (s8 *)&descriptor, 0x2A);
}
