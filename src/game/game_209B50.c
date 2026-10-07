#include "types.h"

/*
 * Reviewed source unit: src/game/game_209B50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DC6A0
 * - func_151DC97C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game209B50Vector {
    f32 values[3];
} Game209B50Vector;

typedef struct Game209B50Packet {
    Game209B50Vector position;
    s16 fieldC, fieldE;
    f32 field10, field14;
    s16 field18, field1A;
    f32 field1C, field20;
    u8 field24, field25;
    u8 pad26[2];
    f32 field28, field2C;
    u8 field30, field31;
    u8 pad32[2];
    f32 field34;
    u8 field38;
    u8 pad39[3];
    f32 field3C;
} Game209B50Packet;

void func_15103254(s32, s32, f32, void *, s32, s32, s32);
void func_15150178(s16 *, f32 *, s32, u8, s32);
void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);
void func_151D3F14(void *, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800AB518, D_800AB51C, D_800AB520, D_800AB524;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DC6A0 CURRENT (330) */
void func_151DC6A0(void *arg0, s32 arg1, s32 arg2) {
    Game209B50Packet packet;
    s16 angles[4];
    f32 fraction;
    u32 sp30;
    u32 sp2C;

    sp2C = func_150ADA20();
    sp30 = func_150ADA20();
    fraction = func_150ADA68();
    func_15103254((s16)((sp2C % 5U) + 0xC), ((sp30 % 56U) + 0xC8) & 0xFF,
                 (fraction * 600.0f) + D_800AB518, arg0, 0xFF, ((u8 *)&arg1)[3], arg2);
    packet.position = *(Game209B50Vector *)arg0;
    packet.field10 = 8.0f;
    packet.fieldC = 0xC;
    packet.field14 = 10.0f;
    packet.fieldE = 7;
    angles[0] = 0;
    angles[1] = 0xFF;
    angles[2] = -0x40;
    angles[3] = 0x3C;
    packet.field18 = 0x24;
    packet.field1A = 0x3C;
    packet.field24 = 0xC8;
    packet.field25 = 0x37;
    packet.field30 = 0;
    packet.field31 = 0xC;
    packet.field38 = 1;
    packet.field1C = D_800AB51C;
    packet.field20 = D_800AB520;
    packet.field28 = 280.0f;
    packet.field2C = 390.0f;
    packet.field34 = D_800AB524;
    packet.field3C = 1.0f;
    func_15150178(angles, packet.position.values, 0, ((u8 *)&arg1)[3], arg2);
    func_151D3F14(arg0, ((u8 *)&arg1)[3], arg2);
    sp2C = func_150ADA20();
    func_15182670(0xFF, 0xFF, 0xFF, ((sp2C % 51U) + 0x96) & 0xFF,
                 (func_150ADA20() % 5U) + 8, 0, ((u8 *)&arg1)[3], arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DC6A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC6A0.s")

void func_151DC6A0(void *, s32, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151DC8BC(void *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        Copy3 header;
        f32 value;
        u8 byte;
    } packet;
    s32 temp_v0;

    if (arg2 != 0) {
        func_151DC6A0(arg0, arg4, arg5);
    }
    packet.header = *(Copy3 *)arg0;
    packet.value = 0.0f;
    packet.byte = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, (s32)arg4, arg5);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x14U);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_209B50/func_151DC97C.s")
