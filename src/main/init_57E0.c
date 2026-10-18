#include "types.h"
#include "libultra_os.h"

/*
 * Reviewed source unit: src/main/init_57E0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_allocator_transfer_controller_boundaries.md
 */

typedef struct PakDevice {
    s32 status;
    OSMesgQueue *queue;
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

extern u8 D_8003BC30[][64];
extern u8 D_8003BD30[][64];

s32 func_80025870(OSMesgQueue *, s32, u16, u8 *, s32);
s32 func_80025C20(OSMesgQueue *, s32, u16, u8 *);
void func_80005948(s32, u16, u8 *, u8 *);
extern u8 D_8003BE30[32];
extern u8 D_8003BE50[32];

s32 func_800057E0(OSMesgQueue *queue, PakDevice *device, s32 channel) {
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
    func_80005948(channel, 0x600, D_8003BE50, D_8003BD30[channel]);
    func_80005948(channel, 0x600, D_8003BE30, D_8003BC30[channel]);
    return 0;
}
u8 func_80025FD0(u16);

void func_80005948(s32 channel, u16 address, u8 *data, u8 *command) {
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
