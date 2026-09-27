#include "types.h"

/*
 * Reviewed source unit: src/game/game_20A990.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DD4E0
 * - func_151DD8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10025750(void);
void func_10025794(void);
/* __osSiRawStartDma: verified SDK address in config/game/us-sdk.ld. */
s32 func_100257C0(s32, void *);
s32 func_10023440(u8 *, s32, s32);
s32 func_151DD710(u8 *, u16 *);
void func_151DD65C(u8, const u8 *);
extern u8 D_80042A50;
extern u8 D_800E0A30[];
extern u8 D_800E0A34[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD4E0 CURRENT (1240) */
s32 func_151DD4E0(u8 *arg0, u8 arg1, u8 *arg2) {
    typedef struct { u8 bytes[12]; } Packet12;
    volatile s32 result;
    volatile u8 unused[8];
    Packet12 packet;
    u8 response[4];
    s32 status;

    func_10025750();
    status = func_151DD710(arg0, (u16 *)response);
    if (status == 0) {
        switch (*(u16 *)response & 0xC000) {
        case 0x8000:
            if (arg1 >= 0x40) {
                status = -1;
            }
            break;
        case 0xC000:
            if ((s32)arg1 >= 0x100) {
                status = -1;
            }
            break;
        default:
            status = 8;
            break;
        }
    }
    if (status != 0) {
        result = status;
        func_10025794();
    } else {
        while (response[2] & 0x80) {
            func_151DD710(arg0, (u16 *)response);
        }
        func_151DD65C(arg1, arg2);
        func_100257C0(1, D_800E0A30);
        func_10023440(arg0, 0, 1);
        func_100257C0(0, D_800E0A30);
        D_80042A50 = 5;
        func_10023440(arg0, 0, 1);
        packet = *(Packet12 *)D_800E0A34;
        result = (packet.bytes[1] & 0xC0) >> 4;
        func_10025794();
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD4E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD4E0.s")
extern u8 D_800E0A30[];
extern u8 D_800E0A31[];

void func_151DD65C(u8 arg0, const u8 *arg1) {
    typedef struct {
        u8 txsize;
        u8 rxsize;
        u8 command;
        u8 address;
        u8 data[8];
    } EepromPacket;
    u8 *dst = D_800E0A30;
    EepromPacket packet;
    s32 i;

    *(s32 *)(D_800E0A30 + 0x3C) = 1;
    packet.txsize = 0xA;
    packet.rxsize = 1;
    packet.command = 5;
    packet.address = (u8)arg0;
    for (i = 0; i < 8; i++) {
        packet.data[i] = *arg1++;
    }
    for (i = 0; i < 4; i++) {
        *dst++ = 0;
    }
    *(EepromPacket *)dst = packet;
    dst += sizeof(EepromPacket);
    *dst = 0xFE;
}
/* Byte layout of the SDK __OSContRequesFormat. */
typedef struct Game20A990Request {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 typeh;
    u8 typel;
    u8 status;
    u8 dummy1;
} Game20A990Request;
extern u8 *D_800E0A70;

s32 func_151DD710(u8 *arg0, u16 *arg1) {
    s32 result;
    s32 i;
    u8 *ptr;
    Game20A990Request request;

    for (i = 0; i < 16; i++) {
        ((u32 *)D_800E0A30)[i] = 0;
    }
    *(u32 *)(D_800E0A30 + 0x3C) = 1;
    ptr = D_800E0A30;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    request.dummy = 0xFF;
    request.txsize = 1;
    request.rxsize = 3;
    request.cmd = 0;
    request.typeh = 0xFF;
    request.typel = 0xFF;
    request.status = 0xFF;
    request.dummy1 = 0xFF;
    *(Game20A990Request *)ptr = request;
    ptr += sizeof(request);
    *ptr = 0xFE;
    result = func_100257C0(1, D_800E0A30);
    func_10023440(arg0, 0, 1);
    D_80042A50 = 0xFE;
    if (result != 0) {
        return result;
    }
    result = func_100257C0(0, D_800E0A30);
    func_10023440(arg0, 0, 1);
    if (result != 0) {
        return result;
    }
    ptr = D_800E0A30;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    request = *(Game20A990Request *)ptr;
    ((u8 *)arg1)[3] = (request.rxsize & 0xC0) >> 4;
    *arg1 = (request.typel << 8) | request.typeh;
    ((u8 *)arg1)[2] = request.status;
    return ((u8 *)arg1)[3];
}
extern u8 D_800BE748[];
extern s32 D_800BE9E4;
extern u8 *D_800E0A70;
extern s32 D_800E0A74;
extern s8 D_800E0BD2;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD8C0 CURRENT (695) */
void func_151DD8C0(void) {
    typedef struct { s8 x; s8 y; u16 time; u16 buttons; } Entry;
    typedef struct { u16 buttons; s8 x; s8 y; } Input;
    Input *input = (Input *)D_800BE748;
    s32 temp_t5;
    u16 temp_v0;
    Entry *temp_a0;

    temp_a0 = (Entry *)D_800E0A70 + D_800E0A74;
    input->x = temp_a0->x;
    input->y = temp_a0->y;
    D_800E0BD2 = 0;
    input->buttons = temp_a0->buttons | (input->buttons & 0x1000);
    if (D_800E0A74 < 0x1F3) {
        temp_v0 = temp_a0[1].time;
        if (D_800BE9E4 < (s32)temp_v0) {
            D_800E0BD2 = temp_v0 - D_800BE9E4;
        }
    }
    temp_t5 = D_800E0A74 + 1;
    D_800BE9E4 = temp_a0->time;
    D_800E0A74 = temp_t5;
    if (temp_t5 >= 0x1F3) {
        D_800E0A74 = 0x1F3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD8C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD8C0.s")
