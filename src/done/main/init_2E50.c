#include "types.h"
#include "libultra_os.h"

/*
 * Reviewed source unit: src/main/init_2E50.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
 */

typedef struct ThreadState ThreadState;
typedef struct PiHandle PiHandle;

typedef struct DeviceManager {
    s32 active;
    ThreadState *thread;
    OSMesgQueue *commandQueue;
    OSMesgQueue *eventQueue;
    OSMesgQueue *accessQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*extendedDma)(PiHandle *, s32, u32, void *, u32);
} DeviceManager;

typedef struct IoMessage {
    u16 type;
    u8 priority;
    u8 status;
    OSMesgQueue *returnQueue;
    void *dramAddress;
    u32 deviceAddress;
    u32 size;
    PiHandle *handle;
} IoMessage;

void func_80022E00(ThreadState *);
extern ThreadState D_80035910;
extern volatile u8 D_8003A572;
extern volatile u8 D_8003A573;
extern volatile u8 D_8003A575;

void func_80002E50(void *argument) {
    IoMessage *message;
    void *event;
    void *dummy;
    s32 result;
    DeviceManager *manager;

    message = 0;
    manager = argument;
    while (1) {
        func_80023440(manager->commandQueue, (void **) &message, 1);
        switch (message->type) {
        case 0xB:
            if (D_8003A572 != 0) {
                D_8003A575 = 1;
                func_80022E00(&D_80035910);
                D_8003A575 = 0;
            }
            D_8003A573 = 1;
            func_80023440(manager->accessQueue, &dummy, 1);
            result = manager->dma(0, message->deviceAddress,
                                  message->dramAddress, message->size);
            break;
        case 0xC:
            func_80023440(manager->accessQueue, &dummy, 1);
            result = manager->dma(1, message->deviceAddress,
                                  message->dramAddress, message->size);
            break;
        case 0xF:
            func_80023440(manager->accessQueue, &dummy, 1);
            result = manager->extendedDma(message->handle, 0,
                                          message->deviceAddress,
                                          message->dramAddress, message->size);
            break;
        case 0x10:
            func_80023440(manager->accessQueue, &dummy, 1);
            result = manager->extendedDma(message->handle, 1,
                                          message->deviceAddress,
                                          message->dramAddress, message->size);
            break;
        case 0xA:
            func_80023580(message->returnQueue, message, 0);
            result = -1;
            break;
        default:
            result = -1;
            break;
        }
        if (result == 0) {
            func_80023440(manager->eventQueue, &event, 1);
            func_80023580(message->returnQueue, message, 0);
            func_80023580(manager->accessQueue, 0, 0);
            if (message->type == 0xB) {
                D_8003A573 = 0;
            }
        }
    }
}
