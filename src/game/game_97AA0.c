#include "types.h"

/*
 * Reviewed source unit: src/game/game_97AA0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506A5F0
 * - func_1506A79C
 * - func_1506A864
 * - func_1506A968
 * - func_1506AA48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A5F0.s")
void func_150E0348(s32 arg0, s32 arg1, s32 arg2);

void func_1506A6FC(s32 arg0, u8 arg1) {
    func_150E0348(arg0, 0xFF, 1);
}
void func_151BB61C(void *, void *, void *, s32, s32);
extern f32 D_800D1560[];
extern f32 D_800D1570[];

void func_1506A724(void *arg0, s32 arg1) {
    func_151BB61C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
void func_151BBA9C(void *, void *, void *, s32, s32);

void func_1506A760(void *arg0, s32 arg1) {
    func_151BBA9C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
void func_151D3480(f32 *, f32 *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A79C CURRENT (545) */
void func_1506A79C(void *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)((u8 *)arg0 + 0x14);
    sp2C[1] = *(f32 *)((u8 *)arg0 + 0x18);
    sp20[0] = D_800D1570[0] - D_800D1560[0];
    sp2C[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    sp20[1] = D_800D1570[1] - D_800D1560[1];
    sp20[2] = D_800D1570[2] - D_800D1560[2];
    func_151D3480(sp2C, sp20, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A79C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A79C.s")
void func_151BC104(s32 arg0, s32 arg1, s32 arg2);

void func_1506A83C(s32 arg0, u8 arg1) {
    func_151BC104(arg0, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A864.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A968 CURRENT (545) */
void func_1506A968(void *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)((u8 *)arg0 + 0x14);
    sp2C[1] = *(f32 *)((u8 *)arg0 + 0x18);
    sp20[0] = D_800D1570[0] - D_800D1560[0];
    sp2C[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    sp20[1] = D_800D1570[1] - D_800D1560[1];
    sp20[2] = D_800D1570[2] - D_800D1560[2];
    func_151D3480(sp2C, sp20, 0, 1, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A968 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A968.s")
extern void func_151B6320(s32 arg0, s32 arg1, s32 arg2);
extern void func_151B7144(s32 arg0, s32 arg1, s32 arg2);

void func_1506AA08(s32 arg0, s32 arg1) {
    func_151B7144(arg0, 0xFF, 1);
    func_151B6320(arg0, 0xFF, 1);
}
void func_10022EC0(void *, void *, s32);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct Game97AA0Packet {
    void *arg0;
    u8 byte;
    u8 pad[3];
    s32 values[2];
} Game97AA0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506AA48 CURRENT (859) */
void func_1506AA48(void *arg0, void *arg1) {
    Game97AA0Packet packet;
    void *temp_v0;

    packet.arg0 = arg0;
    packet.byte = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.values[0] = *(s32 *)arg1;
    packet.values[1] = *(s32 *)((u8 *)arg1 + 4);
    temp_v0 = func_15149130(0xA, 7, 0x23, -1, 1, 0x21, 0x10, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506AA48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506AA48.s")
