#include "types.h"

/*
 * Reviewed source unit: src/game/game_15AA10.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 */

extern s32 D_800DC2B0;

void func_1512D560(void *arg0, s32 arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[*(u8 *)((u8 *)arg0 + 0x23D)];
    *(s32 *)(((u8 (*)[8])temp_v0)[*(s32 *)((u8 *)temp_v0 + 0xAC)]) = arg1;
    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[*(u8 *)((u8 *)arg0 + 0x23D)];
    *(s32 *)(((u8 (*)[8])temp_v0)[*(s32 *)((u8 *)temp_v0 + 0xAC)] + 4) = arg2;
    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[*(u8 *)((u8 *)arg0 + 0x23D)];
    *(s32 *)((u8 *)temp_v0 + 0xAC) = *(s32 *)((u8 *)temp_v0 + 0xAC) + 1;
    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[*(u8 *)((u8 *)arg0 + 0x23D)];
    if (*(s32 *)((u8 *)temp_v0 + 0xAC) == 0x14) {
        *(s32 *)((u8 *)temp_v0 + 0xAC) = 0;
    }
}

void *func_1512D604(u8 *arg0) {
    u8 *temp_v0;
    u8 *result;

    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[arg0[0x23D]];
    result = ((u8 (*)[8])temp_v0)[(*(s32 *)(temp_v0 + 0xA8))++];
    temp_v0 = ((u8 (*)[0xB0])D_800DC2B0)[arg0[0x23D]];
    if (*(s32 *)((u8 *)temp_v0 + 0xA8) == 0x14) {
        *(s32 *)((u8 *)temp_v0 + 0xA8) = 0;
    }
    return result;
}
void func_1512D66C(void *arg0) {
    s32 *temp_t6;

    temp_t6 = &D_800DC2B0;
    *(s32 *)(((u8 (*)[0xB0])*temp_t6)[*(u8 *)((u8 *)arg0 + 0x23D)] + 0xA8) = 0;
    *(s32 *)(((u8 (*)[0xB0])*temp_t6)[*(u8 *)((u8 *)arg0 + 0x23D)] + 0xAC) = 0;
}
extern s32 D_800DC2B0;

s32 func_1512D6B0(void *arg0) {
    u8 *temp_v1;

    temp_v1 = ((u8 (*)[0xB0])D_800DC2B0)[*(u8 *)((u8 *)arg0 + 0x23D)];
    return *(s32 *)((u8 *)temp_v1 + 0xA8) == *(s32 *)((u8 *)temp_v1 + 0xAC);
}
