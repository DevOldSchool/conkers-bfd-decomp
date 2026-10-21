#include "types.h"
#include "libultra_os.h"

/*
 * Reviewed source unit: src/main/init_5570.c
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

void func_80025750(void);
void func_80025794(void);
s32 func_800257C0(s32, void *);
extern u8 D_8003BC30[][64];
extern u8 D_8003BD30[][64];
extern u8 D_800429D0[64];
extern u8 D_80042A50;

s32 func_80005570(PakDevice *device) {
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
