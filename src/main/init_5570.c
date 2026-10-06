#include "types.h"

/*
 * Reviewed source unit: src/main/init_5570.c
 * Boundary evidence: docs/evidence/boundaries/main/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_800056A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define motor_pak_stop func_80005570
#define motor_pak_init func_800057E0
#define motor_pak_pack_write_command func_80005948

typedef struct MessageQueue MessageQueue;

typedef struct PakDevice {
    s32 status;
    MessageQueue *queue;
    s32 channel;
    u8 pad0C[0x59];
    u8 activeBank;
} PakDevice;

typedef struct PakReply {
    u8 dummy;
    u8 txSize;
    u8 rxSize;
    u8 command;
    u16 address;
    u8 data[32];
    u8 dataCrc;
} PakReply;

s32 func_80023440(MessageQueue *, void **, s32);
void func_80025750(void);
void func_80025794(void);
s32 func_800257C0(s32, void *);
extern u8 D_8003BC30[][64];
extern u8 D_8003BD30[][64];
extern u8 D_800429D0[64];
extern u8 D_80042A50;

s32 motor_pak_stop(PakDevice *device) {
    u8 *ptr;
    s32 result;
    s32 i;
    PakReply reply;

    func_80025750();
    D_80042A50 = 3;
    func_800257C0(1, D_8003BC30[device->channel]);
    func_80023440(device->queue, 0, 1);
    func_800257C0(0, D_800429D0);
    func_80023440(device->queue, 0, 1);
    ptr = D_800429D0;
    if (device->channel != 0) {
        for (i = 0; i < device->channel; i++) {
            ptr++;
        }
    }
    reply = *(PakReply *)ptr;
    result = (reply.rxSize & 0xC0) >> 4;
    if (result == 0 && reply.dataCrc != 0) {
        result = 4;
    }
    func_80025794();
    return result;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800056A0 CURRENT (600) */
s32 func_800056A0(PakDevice *device) {
    u8 *ptr;
    s32 result;
    s32 i;
    PakReply reply;

    func_80025750();
    D_80042A50 = 3;
    func_800257C0(1, D_8003BD30[device->channel]);
    func_80023440(device->queue, 0, 1);
    func_800257C0(0, D_800429D0);
    func_80023440(device->queue, 0, 1);
    ptr = D_800429D0;
    if (device->channel != 0) {
        for (i = 0; i < device->channel; i++) {
            ptr++;
        }
    }
    reply = *(PakReply *)ptr;
    result = (reply.rxSize & 0xC0) >> 4;
    if (result == 0 && reply.dataCrc != 0xEB) {
        result = 4;
    }
    func_80025794();
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800056A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5570/func_800056A0.s")
s32 func_80025870(MessageQueue *, s32, u16, u8 *, s32);
s32 func_80025C20(MessageQueue *, s32, u16, u8 *);
void motor_pak_pack_write_command(s32, u16, u8 *, u8 *);
extern u8 D_8003BE30[32];
extern u8 D_8003BE50[32];

s32 motor_pak_init(MessageQueue *queue, PakDevice *device, s32 channel) {
    s32 i;
    s32 result;
    u8 data[32];

    device->queue = queue;
    device->channel = channel;
    device->status = 0;
    device->activeBank = 0x80;
    for (i = 0; i < 32; i++) {
        data[i] = 0x80;
    }
    result = func_80025870(queue, channel, 0x400, data, 0);
    if (result == 2) {
        result = func_80025870(queue, channel, 0x400, data, 0);
    }
    if (result != 0) {
        return result;
    }
    result = func_80025C20(queue, channel, 0x400, data);
    if (result != 0) {
        return result;
    }
    if (data[31] != 0x80) {
        return 0xB;
    }
    for (i = 0; i < 32; i++) {
        D_8003BE50[i] = 1;
        D_8003BE30[i] = 0;
    }
    motor_pak_pack_write_command(channel, 0x600, D_8003BE50, D_8003BD30[channel]);
    motor_pak_pack_write_command(channel, 0x600, D_8003BE30, D_8003BC30[channel]);
    return 0;
}
u8 func_80025FD0(u16);

void motor_pak_pack_write_command(s32 channel, u16 address, u8 *data, u8 *command) {
    u8 *ptr = command;
    PakReply reply;
    s32 i;

    for (i = 0; i < 15; i++) {
        ((u32 *)command)[i] = 0;
    }
    ((u32 *)command)[15] = 1;
    reply.dummy = 0xFF;
    reply.txSize = 0x23;
    reply.rxSize = 1;
    reply.command = 3;
    reply.address = (address << 5) | func_80025FD0(address);
    reply.dataCrc = 0xFF;
    for (i = 0; i < 32; i++) {
        reply.data[i] = *data++;
    }
    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(PakReply *)ptr = reply;
    ptr += sizeof(PakReply);
    *ptr = 0xFE;
}
