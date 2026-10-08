#include "types.h"
#include "libultra_os.h"

/*
 * Reviewed source unit: src/main/init_30A0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define pi_dma_manager_init func_800030A0

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

s32 func_80022DC0(void);
void func_80022DE0(s32);
void func_800037F0(ThreadState *, s32, void (*)(void *), void *, void *, s32);
void func_80022A60(ThreadState *);
void func_80022BB0(ThreadState *, s32);
void func_800236D0(void);
s32 func_80023830(ThreadState *);
void D_10002E50(void *);
s32 D_10023850(s32, u32, void *, u32);
s32 D_10023930(PiHandle *, s32, u32, void *, u32);
extern DeviceManager D_8002AB50;
extern u32 D_8002BD60;
extern ThreadState D_80035910;
extern OSMesgQueue D_80036B40;
extern void *D_80036B58[1];
extern OSMesgQueue D_800428F8;

void pi_dma_manager_init(s32 priority, OSMesgQueue *commandQueue,
                   void **commandBuffer, s32 commandCount) {
    s32 savedMask;
    s32 oldPriority;
    s32 currentPriority;

    if (D_8002AB50.active != 0) {
        return;
    }
    func_80023790(commandQueue, commandBuffer, commandCount);
    func_80023790(&D_80036B40, D_80036B58, 1);
    if (D_8002BD60 == 0) {
        func_800236D0();
    }
    func_800237C0(8, &D_80036B40, (void *) 0x22222222);
    oldPriority = -1;
    currentPriority = func_80023830(0);
    if (currentPriority < priority) {
        oldPriority = currentPriority;
        func_80022BB0(0, priority);
    }
    savedMask = func_80022DC0();
    D_8002AB50.active = 1;
    D_8002AB50.thread = &D_80035910;
    D_8002AB50.commandQueue = commandQueue;
    D_8002AB50.eventQueue = &D_80036B40;
    D_8002AB50.accessQueue = &D_800428F8;
    D_8002AB50.dma = D_10023850;
    D_8002AB50.extendedDma = D_10023930;
    func_800037F0(&D_80035910, 0, D_10002E50, &D_8002AB50,
                  &D_80036B40, priority);
    func_80022A60(&D_80035910);
    func_80022DE0(savedMask);
    if (oldPriority != -1) {
        func_80022BB0(0, oldPriority);
    }
}
